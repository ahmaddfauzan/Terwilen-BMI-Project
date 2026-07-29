#include "HeightSensor.h"

#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox;

const int sensorHeight = 2000; // mm

void initHeightSensor()
{
    Wire.begin(21,22);

    if(!lox.begin())
    {
        Serial.println("VL53L0X gagal!");
        while(1);
    }

    Serial.println("VL53L0X siap");
}

float readHeightCM()
{
    long total = 0;
    int count = 0;

    for(int i=0;i<10;i++)
    {
        VL53L0X_RangingMeasurementData_t measure;

        lox.rangingTest(&measure,false);

        if(measure.RangeStatus != 4)
        {
            total += measure.RangeMilliMeter;
            count++;
        }

        delay(20);
    }

    if(count==0)
        return -1;

    float jarak = total/(float)count;

    float tinggi = (sensorHeight - jarak)/10.0;

    if(tinggi<0)
        tinggi=0;

    return tinggi;
}