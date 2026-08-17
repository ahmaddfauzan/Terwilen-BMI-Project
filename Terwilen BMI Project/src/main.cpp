#include <Arduino.h>

#include <Arduino.h>

#include "HeightSensor.h"
#include "WeightSensor.h"
#include "LCD.h"
#include "WiFiAP.h"

void setup()
{
    Serial.begin(115200);

    // Inisialisasi LCD
    initLCD();

    // Inisialisasi sensor tinggi
    initHeightSensor();

    // Inisialisasi sensor berat
    initWeightSensor();

    // Membuat hotspot ESP32
    initWiFiAP();
}

void loop()
{
    float tinggi = readHeightCM();
    float berat = readWeight();

    // Tampilkan hasil ke LCD
    showMeasurement(tinggi, berat);

    // Tampilkan hasil ke Serial Monitor
    Serial.print("TB : ");
    Serial.print(tinggi);
    Serial.println(" cm");

    Serial.print("BB : ");
    Serial.print(berat);
    Serial.println(" kg");

    Serial.println("-------------------");

    delay(500);
}