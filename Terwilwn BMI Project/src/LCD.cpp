#include "LCD.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD()
{
    Wire.begin(21, 22);

    lcd.init();
    lcd.backlight();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BMI PROJECT");

    lcd.setCursor(0, 1);
    lcd.print("Initializing");

    delay(2000);
    lcd.clear();
}

void showMeasurement(float tinggi, float berat)
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("TB:");
    lcd.print(tinggi, 1);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("BB:");
    lcd.print(berat, 1);
    lcd.print("kg");
}

void showMessage(String baris1, String baris2)
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(baris1);

    lcd.setCursor(0, 1);
    lcd.print(baris2);
}