#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  Wire.begin(21,22);

  Serial.println("VL53L0X Test");

  if (!lox.begin()) {
    Serial.println("Sensor tidak ditemukan!");
    while (1);
  }

  Serial.println("Sensor siap.");
}

void loop() {

  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {
    Serial.print("Jarak : ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Out of range");
  }

  delay(200);
}