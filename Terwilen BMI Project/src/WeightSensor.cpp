#include "WeightSensor.h"
#include <HX711.h>

#define DOUT 19
#define CLK  18

HX711 scale;

const float ZERO_RAW = 41026.0;
const float SCALE_FACTOR = 20327.36;

long readAverageRaw(uint8_t samples)
{
    long sum = 0;

    for (uint8_t i = 0; i < samples; i++)
    {
        sum += scale.read();
        delay(50);
    }

    return sum / samples;
}

void setup()
{
    Serial.begin(115200);
    delay(2000);

    scale.begin(DOUT, CLK);

    Serial.println("Timbangan siap.");
}

void loop()
{
    long raw = readAverageRaw(10);

    float weight = (raw - ZERO_RAW) / SCALE_FACTOR;

    // Jangan tampilkan nilai negatif kecil akibat noise
    if (weight < 0.0)
        weight = 0.0;

    Serial.print("RAW    : ");
    Serial.println(raw);

    Serial.print("WEIGHT : ");
    Serial.print(weight, 2);
    Serial.println(" kg");

    Serial.println("----------------");

    delay(500);
}