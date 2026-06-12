#include <Adafruit_BNO08x.h>

#define BNO085_CS 32
#define BNO085_INT 2
#define BNO085_RESET 3

Adafruit_BNO08x bno085(BNO085_RESET);
sh2_SensorValue_t sensorValue;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  delay(100);

  Serial.println("Initializing BNO085...");
  if (!bno085.begin_I2C()) {
    Serial.println("Failed to connect BNO085");
    while (1) {
      delay(10);
    }
  }

  Serial.println("BNO085 found!");
  setReports();
}

void setReports() {
  if (!bno085.enableReport(SH2_ACCELEROMETER)) {
    Serial.println("Accelrometer not reporting");
  }
  if (!bno085.enableReport(SH2_GYROSCOPE_CALIBRATED)) {
    Serial.println("Could not enable gyroscope");
  }
  if (!bno085.enableReport(SH2_ROTATION_VECTOR)) {
    Serial.println("Could not enable rotation vector");
  }
}

void loop() {
  delay(10);

  if (bno085.wasReset()) {
    setReports();
  }

  if (!bno085.getSensorEvent(&sensorValue)) {
    return;
  }

  Serial.print(sensorValue.un.accelerometer.y);
/*
  switch (sensorValue.sensorId) {
    case SH2_ACCELEROMETER:
      Serial.print("Accelerometer - x: ");
      Serial.print(sensorValue.un.accelerometer.x);
      Serial.print(" y: ");
      Serial.print(sensorValue.un.accelerometer.y);
      Serial.print(" z: ");
      Serial.println(sensorValue.un.accelerometer.z);
      break;
    case SH2_GYROSCOPE_CALIBRATED:
      Serial.print("Gyro - x: ");
      Serial.print(sensorValue.un.gyroscope.x);
      Serial.print(" y: ");
      Serial.print(sensorValue.un.gyroscope.y);
      Serial.print(" z: ");
      Serial.println(sensorValue.un.gyroscope.z);
      break;
    case SH2_ROTATION_VECTOR:
      Serial.print("Rotation Vector - r: ");
      Serial.print(sensorValue.un.rotationVector.real);
      Serial.print(" i: ");
      Serial.print(sensorValue.un.rotationVector.i);
      Serial.print(" j: ");
      Serial.print(sensorValue.un.rotationVector.j);
      Serial.print(" k: ");
      Serial.println(sensorValue.un.rotationVector.k);
      break;
  }
  */
}