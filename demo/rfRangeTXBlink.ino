/// @dir rfRangeTX
/// Transmit sketch used to report quality of reception.
// 2011-05-14 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// Based on a sample implementation by Steve Evans (@tankslappa).

#include <JeeLib.h>

byte outData, pending;
MilliTimer sendTimer;

void setup() {
  Serial.begin(57600);
  rf12_initialize('T', RF12_868MHZ, 88);
  Serial.println("Setup");
}

void loop() {
  rf12_recvDone();

  if (sendTimer.poll(100)) {
    ++outData;
    pending = 1;
  }

  if (pending && rf12_canSend()) {
    rf12_sendStart('R', &outData, sizeof outData);
    Serial.println("Sending");  
    pending = 0;
  }
}
