#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int sensorHeight = 2000; // tinggi sensor dari lantai (mm)

void setup() {
  Serial.begin(9600);

  Wire.begin(21,22);

  Serial.println("VL53L0X Height Measurement");

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

    int jarak = measure.RangeMilliMeter;

    int tinggi = sensorHeight - jarak;

    // Hindari nilai negatif
    if (tinggi < 0)
      tinggi = 0;

    Serial.print("Jarak Sensor : ");
    Serial.print(jarak);
    Serial.println(" mm");

    Serial.print("Tinggi Badan : ");
    Serial.print(tinggi / 10.0);   // cm
    Serial.println(" cm");

    Serial.println("---------------------");

  } else {
    Serial.println("Out of range");
  }

  delay(200);
}