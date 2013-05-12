#include <JeeLib.h>
#define numNodes 5
byte outData[numNodes][3];

void setup() {
  Serial.begin(57600);
  rf12_initialize(26, RF12_915MHZ, 44);
  Serial.println("Setup");
}

void sendSig() {

  rf12_recvDone();
      
  for (int i = 1; i <= numNodes; i++) {
  
    if (rf12_canSend()) {
      
      byte header = 0;
      
      if (i)
            header |= RF12_HDR_DST | i;
            
      rf12_sendStart(header, &outData[i-1], sizeof outData[i-1], 1);
      delay(50);
      Serial.print("Sending node:");  
      Serial.print(i);  
      Serial.print(" rgb:");  
      Serial.print(outData[i-1][0]);  
      Serial.print(",");  
      Serial.print(outData[i-1][1]);
      Serial.print(",");  
      Serial.print(outData[i-1][2]);
      Serial.println("");  
      rf12_recvDone();

    }
      
  }

  rf12_recvDone();
  
}

void loop() {
  
  outData[0][0] = 200;
  outData[0][1] = 0;
  outData[0][2] = 0;
  
  outData[1][0] = 0;
  outData[1][1] = 200;
  outData[1][2] = 0;
  
  outData[2][0] = 0;
  outData[2][1] = 0;
  outData[2][2] = 200;
  
  outData[3][0] = 200;
  outData[3][1] = 0;
  outData[3][2] = 0;

  outData[4][0] = 0;
  outData[4][1] = 200;
  outData[4][2] = 0;

  sendSig();
  delay(1000);
  
  outData[0][0] = 0;
  outData[0][1] = 200;
  outData[0][2] = 0;
  
  outData[1][0] = 0;
  outData[1][1] = 0;
  outData[1][2] = 200;
  
  outData[2][0] = 200;
  outData[2][1] = 0;
  outData[2][2] = 0;

  outData[3][0] = 0;
  outData[3][1] = 200;
  outData[3][2] = 0;

  outData[4][0] = 200;
  outData[4][1] = 0;
  outData[4][2] = 0;

  sendSig();
  delay(1000);
  
  outData[0][0] = 0;
  outData[0][1] = 0;
  outData[0][2] = 200;
  
  outData[1][0] = 200;
  outData[1][1] = 0;
  outData[1][2] = 0;

  outData[2][0] = 0;
  outData[2][1] = 200;
  outData[2][2] = 0;

  outData[3][0] = 200;
  outData[3][1] = 0;
  outData[3][2] = 0;

  outData[4][0] = 0;
  outData[4][1] = 200;
  outData[4][2] = 0;

  sendSig();
  delay(1000);
  
}

void rainbowCycle() {
  
  int i, j;
  
  for (j=0; j < 256; j++) {
  
    for (i=1; i <= numNodes; i++) {
      
      setPixelColor(i, Wheel( ((i * 256 / numNodes) + j) % 256) );
       
    }  
    
    sendSig(); 
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
