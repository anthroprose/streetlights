/// @dir rfRangeRX
/// Receive sketch used to report quality of reception.
// 2011-05-14 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// Based on a sample implementation by Steve Evans (@tankslappa).

#include <JeeLib.h>
#include "HughesyShiftBrite.h"

HughesyShiftBrite sb;

void setup () {
  
  Serial.begin(57600);
  rf12_initialize(1, RF12_915MHZ, 44);
  
  Serial.println("Setup");
  
  //(int dataPin, int latchPin, int enablePin, int clockPin)
  sb = HughesyShiftBrite(7,6,5,4);
  
  sb.sendColour(255,0,0);
  sb.sendColour(255,0,0);
  delay(1000);
  sb.sendColour(0,255,0);
  sb.sendColour(0,255,0);
  delay(1000);
  sb.sendColour(0,0,255);
  sb.sendColour(0,0,255);
  delay(1000);
  
}

void loop () {
  
  if (rf12_recvDone() && rf12_crc == 0 && rf12_len == 3) {
    
    sb.sendColour(rf12_data[0]*3,rf12_data[1]*3,rf12_data[2]*3);
    sb.sendColour(rf12_data[0]*3,rf12_data[1]*3,rf12_data[2]*3);

    Serial.print((int) rf12_hdr);
    Serial.print(':'); 
    Serial.print((int) rf12_grp);
    Serial.print(':'); 
    Serial.print((int) RF12_HDR_DST);
    Serial.print(':'); 
    Serial.print((int) RF12_HDR_ACK);
    
    Serial.print(" - Colors: ");
    Serial.print(rf12_data[0]);
    Serial.print(",");
    Serial.print(rf12_data[1]);
    Serial.print(",");
    Serial.print(rf12_data[2]);
    Serial.println("");
    
  }

}
