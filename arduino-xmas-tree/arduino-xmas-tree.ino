// arduino-xmas-tree

// Copyright (c) tti0 2021
// Licensed under the MIT License (/LICENSE)
// Hardware setup details in /README.md

// This sketch will, on alternating boot-ups of the Arduino:
//    (0) Set all of the pins in outputPins HIGH (steady on), or;
//    (1) Set a random pin to a random value (HIGH or LOW) every XXms (twinkling effect)

#include <EEPROM.h>

int outputPins[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5};

int statusAddress = 0;
byte statusValue;

void setup() {
  for (byte i = 0; i < 20; i = i + 1) {
    pinMode(outputPins[i], OUTPUT);
  }
  
  statusValue = EEPROM.read(statusAddress);
  if (statusValue == 0) {  // if we are in steady mode
    // set to blink for next time
    EEPROM.write(statusAddress, 1);
    // steady light
    for (byte i = 0; i < 20; i = i + 1) {
      digitalWrite(outputPins[i], HIGH);
    }
  } else if (statusValue == 1) {  // if we are in blink mode
    // set to steady for next time
    EEPROM.write(statusAddress, 0);
  } else {  // if the EEPROM has some other value
    EEPROM.write(statusAddress, 0);
    setup();
  }
}

void loop() {
  // if in blink mode
  if (statusValue == 1) {
    digitalWrite(outputPins[random(0, 20)], random(0, 2));
    delay(50);
  }
}
