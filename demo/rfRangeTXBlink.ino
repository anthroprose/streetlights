/// @dir rfRangeTX
/// Transmit sketch used to report quality of reception.
// 2011-05-14 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// Based on a sample implementation by Steve Evans (@tankslappa).

#include <JeeLib.h>

byte outData, pending;
MilliTimer sendTimer;

void setup() {
  Serial.begin(57600);
  rf12_initialize(13, RF12_868MHZ, 88);
  Serial.println("Setup");
}

void loop() {
  rf12_recvDone();

  if (outData > 255) { outData = 0; }
    
  if (sendTimer.poll(100)) {
    ++outData;
    pending = 1;
  }

  for (int i = 1; i<4;i++) {
  
    if (pending && rf12_canSend()) {
      rf12_sendStart(i, &outData, sizeof outData);
      Serial.println("Sending");  
    }
  
    pending = 0;
        
  }
}
