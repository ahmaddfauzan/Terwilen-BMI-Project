#include "WeightSensor.h"
#include <HX711_ADC.h>

const int HX711_dout = 19;
const int HX711_sck  = 18;

HX711_ADC LoadCell(HX711_dout, HX711_sck);

// Ganti nanti setelah proses kalibrasi
float calibrationFactor = 1.0;

void initWeightSensor()
{
    LoadCell.begin();

    LoadCell.start(2000);

    if (LoadCell.getTareTimeoutFlag()) {
        Serial.println("HX711 gagal melakukan tare!");
        while (1);
    }

    LoadCell.setCalFactor(calibrationFactor);

    Serial.println("HX711 siap");
}

float readWeight()
{
    static bool newDataReady = false;

    if (LoadCell.update()) {
        newDataReady = true;
    }

    if (newDataReady) {
        newDataReady = false;
        return LoadCell.getData();
    }

    return NAN;   // belum ada data baru
}