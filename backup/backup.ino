/*
  Time interval: https://stackoverflow.com/a/10773464
  SD: https://docs.arduino.cc/learn/programming/sd-guide/ & https://github.com/PaulStoffregen/Teensyduino_Examples/blob/master/USB_Media_Transfer/Basic_SD_Card/Basic_SD_Card.ino
  BNO085: https://adafruit.github.io/Adafruit_BNO08x/html/class_adafruit___b_n_o08x.html & https://github.com/adafruit/Adafruit_BNO08x/tree/master/examples
*/

#include <iostream>
#include <string>
#include <SD.h>
#include <Adafruit_BNO08x.h>
#include <Adafruit_BMP280.h>

#define BNO085_INT 2
#define BNO085_RESET -1

Adafruit_BNO08x bno085(BNO085_RESET);
sh2_SensorValue_t sensorValue;

unsigned long previousMillis = 0;
long interval = 100;

void setup() {
  Serial.begin(9600);
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Failed to connect SD card")
    while (1) {
      delay(10);
    }
  }
  Serial.println("SD card found!")

  Serial.println("Initializing BNO085...");
  if (!bno085.begin_I2C()) {
    Serial.println("Failed to connect BNO085");
    while (1) {
      delay(10);
    }
  }
  Serial.println("BNO085 found!");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    IMU();

    //if (accelerationThreshold()) {
    //  parachute();
    //}
  }
}

void setReports() {
  if (!bno085.enableReport(SH2_ACCELEROMETER)) {
    Serial.println("Could not enable accelerometer");
  }
  if (!bno085.enableReport(SH2_GYROSCOPE_CALIBRATED)) {
    Serial.println("Could not enable gyroscope");
  }
  if (!bno085.enableReport(SH2_ROTATION_VECTOR)) {
    Serial.println("Could not enable rotation vector");
  }
}

//bool accelerationThreshold() {
//  // Perform checks to return true or false
//  accelerometer();
//}

void IMU() {
  if (bno085.wasReset()) {
    setReports();
  }

  if (!bno085.getSensorEvent(&sensorValue)) {
    return;
  }

  accelerometer();
  gyroscope();
  angular();
}

void accelerometer() {
  accelerometerFile = SD.open("accelerometer.txt", FILE_WRITE);
  if (accelerometerFile) {
    accelerometerFile.println()
  }
}

void gyroscope() {

}
void angular() {

}
//void parachute() {
//  // Detach parachute
//}