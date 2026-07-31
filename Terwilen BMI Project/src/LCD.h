#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

void initLCD();
void showMeasurement(float tinggi, float berat);
void showMessage(String baris1, String baris2);

#endif
