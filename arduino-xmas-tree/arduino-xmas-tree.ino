// arduino-xmas-tree

// Currently in early-stage development/testing.
// The built-in LED (pin 13) should, on alternating boot-ups, blink or remain steady on.

#include <EEPROM.h>

int statusAddress = 0;
byte statusValue;

void setup() {
  // EEPROM.write(statusAddress, 0); // run this on a "fresh" board
  pinMode(13, OUTPUT);
  statusValue = EEPROM.read(statusAddress);
  // if we are in steady mode
  if (statusValue == 0) {
    // set to blink for next time
    EEPROM.write(statusAddress, 1);
    // steady light
    digitalWrite(13, HIGH);
  }
  // if we are in blink mode
  if (statusValue == 1) {
    // set to steady for next time
    EEPROM.write(statusAddress, 0);  
  }
}

void loop() {
  if (statusValue == 1) {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}
