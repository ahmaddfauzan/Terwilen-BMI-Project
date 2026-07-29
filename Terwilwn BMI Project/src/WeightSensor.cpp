#include "WeightSensor.h"

#include <HX711_ADC.h>

HX711_ADC LoadCell(19,18);

float calibrationFactor = 696.0;

void initWeightSensor()
{
    LoadCell.begin();

    LoadCell.start(2000);

    LoadCell.setCalFactor(calibrationFactor);

    Serial.println("HX711 siap");
}

float readWeight()
{
    LoadCell.update();

    return LoadCell.getData();
}