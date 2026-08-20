#include "WeightSensor.h"
#include <HX711.h>

#define DOUT 19
#define CLK 18

HX711 scale;

// Hasil kalibrasi berdasarkan beban 58 kg
const float SCALE_FACTOR = -21241.4;

// Filter
const int SAMPLE_COUNT = 10;

void initWeightSensor()
{
    scale.begin(DOUT, CLK);

    Serial.println("================================");
    Serial.println("       LOAD CELL SIAP");
    Serial.println("================================");

    Serial.println("Pastikan load cell TANPA BEBAN.");
    Serial.println("Tare dalam 5 detik...");

    delay(5000);

    scale.tare();

    scale.set_scale(SCALE_FACTOR);

    Serial.println("Tare selesai.");
    Serial.println("HX711 siap.");
    Serial.println();
}

float readWeight()
{
    // Ambil rata-rata 10 pembacaan
    float berat = scale.get_units(SAMPLE_COUNT);

    // Hilangkan nilai kecil akibat noise
    if (abs(berat) < 0.5)
    {
        berat = 0;
    }

    // Batas bawah
    if (berat < 0)
    {
        berat = 0;
    }

    return berat;
}