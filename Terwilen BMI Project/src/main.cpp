#include <Arduino.h>

#include "HeightSensor.h"
#include "WeightSensor.h"
#include "LCD.h"

void setup()
{
    Serial.begin(115200);

    initLCD();

    initHeightSensor();

    initWeightSensor();
}

void loop()
{
    float tinggi = readHeightCM();
    float berat = readWeight();

    showMeasurement(tinggi, berat);

    Serial.print("TB : ");
    Serial.print(tinggi);
    Serial.println(" cm");

    Serial.print("BB : ");
    Serial.print(berat);
    Serial.println(" kg");

    Serial.println("-------------------");

    delay(500);
}