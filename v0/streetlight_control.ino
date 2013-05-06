#include <JeeLib.h>

int maxVal = 1023;
const int DELAY_VAL = 500;
byte c;


void setup() {
  
  Serial.begin(57600);
  rf12_initialize(1, RF12_915MHZ, 1);
  Serial.println("Setup");  

}

void loop() {
  
  Serial.println("Before Done");  
  rf12_recvDone();
  Serial.println("After Done");  
  
  for (int i = 0; i <= maxVal; i++)
  {
    c=0;//c[1]=0;c[2]=0;
    c++;
    
    if (rf12_canSend()) { 
    
      rf12_sendStart(2, &c, sizeof c); 
      rf12_sendWait(2); 
      Serial.print("Sending new Colors: ");
      Serial.println(c);
    
    }
    
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i--)
  {
    c=maxVal;//c[1]=0;c[2]=0;
    c--;
    if (rf12_canSend()) { 
      rf12_sendStart(2, &c, sizeof c); 
      rf12_sendWait(2); 
      Serial.print("Sending new Colors: ");
      Serial.println(c); 
  }
    delay(DELAY_VAL);
  }
   
}
