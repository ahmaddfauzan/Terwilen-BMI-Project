#include "WeightSensor.h"
#include <HX711.h>

#define DOUT 19
#define CLK 18

HX711 scale;

// Ganti setelah kalibrasi
const long OFFSET = 0;
const float SCALE = -1000.0;

void initWeightSensor()
{
    scale.begin(DOUT, CLK);

    Serial.println("Tare...");

    scale.tare();

    scale.set_scale(SCALE);

    Serial.println("HX711 Siap");
}

float readWeight()
{
    float berat = scale.get_units(3); // rata-rata 3 pembacaan

    if (abs(berat) < 0.02)
        berat = 0;

    return berat;
}