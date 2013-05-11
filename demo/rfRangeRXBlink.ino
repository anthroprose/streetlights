/// @dir rfRangeRX
/// Receive sketch used to report quality of reception.
// 2011-05-14 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

// Based on a sample implementation by Steve Evans (@tankslappa).

#include <JeeLib.h>
#include "HughesyShiftBrite.h"

#define NODEID 1
#define BUFFER_SIZE 64
#define DISPLAY_INTERVAL 500 // ms

MilliTimer displayTimer;

byte timeBuf [BUFFER_SIZE]; // index is time slot, value is last packet
byte seqBuf [BUFFER_SIZE];  // index is last packet, value is time slot
char history [11];
byte lastSeq;
HughesyShiftBrite sb;

static void gotPacket () {
  byte tenths = millis() / 100;
  // remember for each time slot what the last received packet was
  timeBuf[tenths % BUFFER_SIZE] = lastSeq;
  // remember for the last BUFFER_SIZE packets when they arrived
  seqBuf[lastSeq % BUFFER_SIZE] = tenths;
}

static byte recvCount (byte period) {
  // tenths and diff are bytes, so they are automatically modulo 256
  byte tenths = millis() / 100;
  byte n = 0;
  for (byte i = 0; i < sizeof seqBuf; ++i) {
    byte diff = tenths - seqBuf[i];
    if (diff <= period)
      ++n;
  }
  return n;
}

static void updateHistory () {
  for (byte i = 1; i < 10; ++i)
    history[10-i] = history[9-i];
  history[0] = '0';
  // tenths and diff are bytes, so they are automatically modulo 256
  byte tenths = millis() / 100;
  for (byte i = 0; i < DISPLAY_INTERVAL / 100; ++i) {
    byte pos = (tenths - i - 1) % BUFFER_SIZE;
    byte diff = lastSeq - timeBuf[pos];
    if (diff < 5)
      ++history[0];
  }
}

void setup () {
  Serial.begin(57600);
  rf12_initialize(NODEID, RF12_868MHZ, 88);
  // synchronize the display to 0.1s clock transitions
  displayTimer.set(DISPLAY_INTERVAL - millis() % DISPLAY_INTERVAL - 1);
  Serial.println("Setup");
  sb = HughesyShiftBrite(8,11,12,13);
}

void loop () {
  
  if (rf12_recvDone() && rf12_crc == 0 && rf12_len == 3) {
    
    sb.sendColour(rf12_data[0],rf12_data[1],rf12_data[2]);
    sb.sendColour(rf12_data[0],rf12_data[1],rf12_data[2]);
    
    Serial.print("Colors: ");
    Serial.print(rf12_data[0]);
    Serial.print(",");
    Serial.print(rf12_data[1]);
    Serial.print(",");
    Serial.println(rf12_data[2]);
    
  }
  
}
