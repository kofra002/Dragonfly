/*
  Interval: https://stackoverflow.com/a/10773464
  LED: https://www.pjrc.com/teensy/tutorial.html
  SD: https://docs.arduino.cc/learn/programming/sd-guide/ & https://github.com/PaulStoffregen/Teensyduino_Examples/blob/master/USB_Media_Transfer/Basic_SD_Card/Basic_SD_Card.ino
  BNO085: https://adafruit.github.io/Adafruit_BNO08x/html/class_adafruit___b_n_o08x.html & https://github.com/adafruit/Adafruit_BNO08x/tree/master/examples
  BMP280: https://projecthub.arduino.cc/SurtrTech/bmp280-measure-temperature-pressure-and-altitude-6002cd & https://simple-circuit.com/arduino-bmp280-ssd1306-i2c-oled/
*/

#include <Wire.h>
#include <SD.h>
#include <Adafruit_BNO08x.h>
#include <Adafruit_BMP280.h>

#define BNO085_RESET -1
Adafruit_BNO08x bno085(BNO085_RESET);
sh2_SensorValue_t sensorValue;

#define BMP280_I2C_ADDRESS 0x76
Adafruit_BMP280 bmp280;
float currentPressure;

unsigned long previousMillis = 0;
unsigned long currentMillis;
long interval = 100;

File accelerometerFile;
File gyroscopeFile;
File angularFile;
File temperatureFile;
File pressureFile;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Serial.println("Initializing SD card...");
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Failed to connect SD card");
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);
    }
  }
  Serial.println("SD card found!");

  Serial.println("Initializing BNO085...");
  if (!bno085.begin_I2C()) {
    Serial.println("Failed to connect BNO085");
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);
    }
  }
  Serial.println("BNO085 found!");
  setReports();

  Serial.println("Initializing BMP280...");
  if (!bmp280.begin(BMP280_I2C_ADDRESS)) {
    Serial.println("Failed to connect BMP280");
    while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(10);
    }
  }
  Serial.println("BMP280 found!");
}

void loop() {
  currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    IMU();
    pressureSensor();

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
    accelerometerFile.print(currentMillis);
    accelerometerFile.print("|");
    accelerometerFile.print(sensorValue.un.accelerometer.x);
    accelerometerFile.print(";");
    accelerometerFile.print(sensorValue.un.accelerometer.y);
    accelerometerFile.print(";");
    accelerometerFile.println(sensorValue.un.accelerometer.z);
    accelerometerFile.close();
  } else {
    Serial.println("Error opening accelerometer.txt");
  }
}

void gyroscope() {
  gyroscopeFile = SD.open("gyroscope.txt", FILE_WRITE);
  if (gyroscopeFile) {
    gyroscopeFile.print(currentMillis);
    gyroscopeFile.print("|");
    gyroscopeFile.print(sensorValue.un.gyroscope.x);
    gyroscopeFile.print(";");
    gyroscopeFile.print(sensorValue.un.gyroscope.y);
    gyroscopeFile.print(";");
    gyroscopeFile.println(sensorValue.un.gyroscope.z);
    gyroscopeFile.close();
  } else {
    Serial.println("Error opening gyroscope.txt");
  }
}

void angular() {
  angularFile = SD.open("angular.txt", FILE_WRITE);
  if (angularFile) {
    angularFile.print(currentMillis);
    angularFile.print("|");
    angularFile.print(sensorValue.un.rotationVector.real);
    angularFile.print(";");
    angularFile.print(sensorValue.un.rotationVector.i);
    angularFile.print(";");
    angularFile.print(sensorValue.un.rotationVector.j);
    angularFile.print(";");
    angularFile.println(sensorValue.un.rotationVector.k);
    angularFile.close();
  } else {
    Serial.println("Error opening angular.txt");
  }
}

void pressureSensor() {
  temperature();
  pressure();
}

void temperature() {
  temperatureFile = SD.open("temperature.txt", FILE_WRITE);
  if (temperatureFile) {
    temperatureFile.print(currentMillis);
    temperatureFile.print("|");
    temperatureFile.println(bmp280.readTemperature());
    temperatureFile.close();
  } else {
    Serial.println("Error opening temperature.txt");
  }
}

void pressure() {
  currentPressure = bmp280.readPressure();

  pressureFile = SD.open("pressure.txt", FILE_WRITE);
  if (pressureFile) {
    pressureFile.print(currentMillis);
    pressureFile.print("|");
    pressureFile.println(currentPressure);
    pressureFile.close();
  } else {
    Serial.println("Error opening pressure.txt");
  }
}

//bool accelerationThreshold() {
//  // Perform checks to return true or false
//  accelerometer();
//}

//void parachute() {
//  // Detach parachute
//}