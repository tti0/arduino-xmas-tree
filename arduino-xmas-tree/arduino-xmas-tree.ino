// arduino-xmas-tree

// Currently in early-stage development/testing.
// The built-in LED (pin 13) should, on alternating boot-ups, blink or remain steady on.

#include <EEPROM.h>

int statusAddress = 0;
byte statusValue;

void setup() {
  // test LED for output
  pinMode(13, OUTPUT);
  
  statusValue = EEPROM.read(statusAddress);
  if (statusValue == 0) {  // if we are in steady mode
    // set to blink for next time
    EEPROM.write(statusAddress, 1);
    // steady light
    digitalWrite(13, HIGH);
  } else if (statusValue == 1) {  // if we are in blink mode
    // set to steady for next time
    EEPROM.write(statusAddress, 0);
  } else {  // if the EEPROM has some other value
    EEPROM.write(statusAddress, 0);
    setup();
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
