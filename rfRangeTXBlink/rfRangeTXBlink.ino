#include <JeeLib.h>
#define numNodes 5
byte outData[numNodes][3];

void setup() {
  
  Serial.begin(57600);
  rf12_initialize(26, RF12_915MHZ, 44);
  
}

void sendAll() {

  rf12_recvDone();
      
  for (int i = 1; i <= numNodes; i++) {
  
    if (rf12_canSend()) {
      
      byte header = 0;
      
      if (i)
            header |= RF12_HDR_DST | i;
            
      rf12_sendStart(header, &outData[i-1], sizeof outData[i-1], 1);
      delay(10);
      rf12_recvDone();

    }
      
  }

  rf12_recvDone();
  
}

void sendOne(byte a, byte r, byte g, byte b) {

  byte od[3] = { r, g, b};
  
  rf12_recvDone();
      
  if (rf12_canSend()) {
    
    byte header = 0;
    
    if (a)
          header |= RF12_HDR_DST | a;
          
    rf12_sendStart(header, &od, sizeof od, 1);
    delay(10);
    rf12_recvDone();

  }

  rf12_recvDone();
  
}


void loop() {
  
  while (Serial.available() > 0) {

    byte nodeID = Serial.parseInt();
    byte red = Serial.parseInt();
    byte green = Serial.parseInt();
    byte blue = Serial.parseInt();

    if (Serial.read() == '\n') {

        sendOne(nodeID,red,green,blue);
        Serial.print("Sent: ");
        Serial.print(nodeID);
        Serial.print(':');
        Serial.print(red);
        Serial.print(',');
        Serial.print(green);
        Serial.print(',');
        Serial.print(blue);
        Serial.println("");
        
    }
    
    delay(50);
    
  }

}

void rainbowCycle() {
  
  int i, j;
  
  for (j=0; j < 256; j++) {
  
    for (i=1; i <= numNodes; i++) {
      
      setPixelColor(i, Wheel( ((i * 256 / numNodes) + j) % 256) );
       
    }  
    
    sendAll(); 
    delay(1000);
    
  }
  
}

// Set pixel color from 'packed' 32-bit RGB value:
void setPixelColor(uint16_t n, uint32_t c) {
  
  if (n < numNodes) { // Arrays are 0-indexed, thus NOT '<='
      outData[n][0] = c >>  8; // Green
      outData[n][1] = c >> 16; // Red
      outData[n][2] = c;       // Blue
  }
}

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
