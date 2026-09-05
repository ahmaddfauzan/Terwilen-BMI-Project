#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

void initLCD();

void showMeasurement(
    float tinggi,
    float berat,
    float imt,
    bool isHold,
    bool isTare
);

void showMessage(
    String baris1,
    String baris2
);

#endif