/*
  Time interval: https://stackoverflow.com/a/10773464
  SD: https://docs.arduino.cc/learn/programming/sd-guide/ & https://github.com/PaulStoffregen/Teensyduino_Examples/blob/master/USB_Media_Transfer/Basic_SD_Card/Basic_SD_Card.ino
*/

#include <iostream>
#include <string>
#include <SD.h>

unsigned long previousMillis = 0;
long interval = 100;

void setup() {
  Serial.begin(9600);
  SD.begin(BUILTIN_SDCARD);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (accelerationThreshold()) {
      parachute();
    }
  }
}

bool accelerationThreshold() {
  // Perform checks to return true or false
  accelerometer();
}

float accelerometer() {
  // get acceleration and save to SD
}

void transmit(const std::string& message) {
  // send notifications to control system
}

void parachute() {
  // Detach parachute
}