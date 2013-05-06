#include "HughesyShiftBrite.h"
#include <JeeLib.h>

#define LED_PIN     9   // activity LED, comment out to disable

int nodeID = 2;
byte c1, c2, c3;

HughesyShiftBrite sb;

static void activityLed (byte on) {
#ifdef LED_PIN
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, !on);
#endif
}

void setup() {
  
   Serial.begin(57600);
   rf12_initialize('A', RF12_915MHZ);
   rf12_config();
  
   sb = HughesyShiftBrite(8,11,12,13);
   
}

void loop() {
    
  if (rf12_recvDone()) { 
    
    activityLed(1); 
    c1 = (unsigned int)rf12_data[0];
    //c2 = (unsigned int)rf12_data[1];
    //c3 = (unsigned int)rf12_data[2];  
    sb.sendColour(c1,c1,c1);
//    sb.sendColour(c1,c2,c3);
    Serial.print("Writing new Colors: ");
    Serial.print(c1);
    Serial.print(" ");
    Serial.print(c2);
    Serial.print(" ");
    Serial.println(c3);
    activityLed(0);
    
  } 
   
}
