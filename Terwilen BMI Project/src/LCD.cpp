#include "LCD.h"

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>


// =====================================================
// I2C LCD
// =====================================================

TwoWire I2C_LCD = TwoWire(1);

LiquidCrystal_PCF8574 lcd(0x27);


// =====================================================
// INIT LCD
// =====================================================

void initLCD()
{
    // SDA = GPIO 4
    // SCL = GPIO 5
    I2C_LCD.begin(4, 5);

    // LCD 16x2
    lcd.begin(16, 2, I2C_LCD);

    if (!lcd.isConnected())
    {
        Serial.println("LCD tidak terdeteksi!");
        return;
    }

    Serial.println("LCD siap!");

    lcd.setBacklight(255);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("BMI PROJECT");

    lcd.setCursor(0, 1);
    lcd.print("Initializing");

    delay(2000);

    lcd.clear();
}


// =====================================================
// TAMPILKAN DATA
// =====================================================

void showMeasurement(
    float tinggi,
    float berat,
    float imt,
    bool isHold,
    bool isTare
)
{
    // =================================================
    // BARIS 1
    //
    // TB:90.0   BB:12.0
    // =================================================

    lcd.setCursor(0, 0);

    lcd.print("TB:");

    lcd.print(tinggi, 1);

    lcd.print(" BB:");

    lcd.print(berat, 1);


    // Bersihkan sisa karakter
    lcd.print("   ");


    // =================================================
    // BARIS 2
    //
    // IMT:14.81   H
    // =================================================

    lcd.setCursor(0, 1);

    lcd.print("IMT:");

    lcd.print(imt, 2);

    lcd.print("   ");


    // =================================================
    // INDIKATOR
    // =================================================

    // HOLD di posisi 14
    if (isHold)
    {
        lcd.setCursor(14, 1);
        lcd.print("H");
    }
    else
    {
        lcd.setCursor(14, 1);
        lcd.print(" ");
    }


    // TARE di posisi 15
    if (isTare)
    {
        lcd.setCursor(15, 1);
        lcd.print("T");
    }
    else
    {
        lcd.setCursor(15, 1);
        lcd.print(" ");
    }
}


// =====================================================
// PESAN LCD
// =====================================================

void showMessage(
    String baris1,
    String baris2
)
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(baris1);

    lcd.setCursor(0, 1);
    lcd.print(baris2);
}