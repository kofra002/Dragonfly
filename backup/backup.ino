/*
  Time interval: https://stackoverflow.com/a/10773464
  SD: https://docs.arduino.cc/learn/programming/sd-guide/ & https://github.com/PaulStoffregen/Teensyduino_Examples/blob/master/USB_Media_Transfer/Basic_SD_Card/Basic_SD_Card.ino
*/

#include <SD.h>

unsigned long previousMillis = 0;
long interval = 2000;

void setup() {
  Serial.begin(9600);
  SD.begin(BUILTIN_SDCARD);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (accelerometer()) {
      parachute();
    }
  }
}

bool accelerometer() {
  // get acceleration and perform checks to return true or false
}

void parachute() {
  // Detach parachute
}