/*
  Time interval: https://stackoverflow.com/a/10773464
  SD: https://docs.arduino.cc/learn/programming/sd-guide/ & https://github.com/PaulStoffregen/Teensyduino_Examples/blob/master/USB_Media_Transfer/Basic_SD_Card/Basic_SD_Card.ino
  GY-521: https://mschoeffler.com/2017/10/05/tutorial-how-to-use-the-gy-521-module-mpu-6050-breakout-board-with-the-arduino-uno/ & https://projecthub.arduino.cc/Nicholas_N/how-to-use-the-accelerometer-gyroscope-gy-521-647e65
*/

#include <iostream>
#include <string>
#include <SD.h>
#include <Wire.h>

unsigned long previousMillis = 0;
long interval = 100;

const int MPU_ADDR = 0x68; // I2C address of accelerometer

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;

void setup() {
  Serial.begin(9600);
  SD.begin(BUILTIN_SDCARD);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    accelerometer();

    //if (accelerationThreshold()) {
    //  parachute();
    //}
  }
}

//bool accelerationThreshold() {
//  // Perform checks to return true or false
//  accelerometer();
//}

//float accelerometer() {
void accelerometer() {
  // get acceleration and save to SD
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  accelerometer_x = Wire.read()<<8 | Wire.read();
  accelerometer_y = Wire.read()<<8 | Wire.read();
  accelerometer_z = Wire.read()<<8 | Wire.read();
  gyro_x = Wire.read()<<8 | Wire.read();
  gyro_y = Wire.read()<<8 | Wire.read();
  gyro_z = Wire.read()<<8 | Wire.read();
  temperature = Wire.read()<<8 | Wire.read();

  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(accelerometer_x);
  Serial.print(" | Y = "); Serial.print(accelerometer_y);
  Serial.print(" | Z = "); Serial.println(accelerometer_z);

  //Serial.print("Gyroscope: ");
  //Serial.print("X = "); Serial.print(gyro_x);
  //Serial.print(" | Y = "); Serial.print(gyro_y);
  //Serial.print(" | Z = "); Serial.println(gyro_z);

  //Serial.print("Temperature: ");
  //Serial.print("Temperature = "); Serial.print(temperature);

  Serial.println(" ");
}

//void transmit(const std::string& message) {
//  // send notifications to control system
//}

//void parachute() {
//  // Detach parachute
//}