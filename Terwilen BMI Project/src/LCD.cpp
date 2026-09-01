#include "LCD.h"

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// Membuat I2C bus kedua ESP32
TwoWire I2C_LCD = TwoWire(1);

// Alamat LCD
LiquidCrystal_PCF8574 lcd(0x27);


void initLCD()
{
    // LCD menggunakan GPIO 4 sebagai SDA
    // dan GPIO 5 sebagai SCL
    I2C_LCD.begin(4, 5);

    // Inisialisasi LCD menggunakan I2C bus kedua
    lcd.begin(16, 2, I2C_LCD);

    // Cek apakah LCD terdeteksi
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


void showMeasurement(float tinggi, float berat)
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("TB:");
    lcd.print(tinggi, 1);
    lcd.print(" cm");

    lcd.setCursor(0, 1);
    lcd.print("BB:");
    lcd.print(berat, 1);
    lcd.print(" kg");
}


void showMessage(String baris1, String baris2)
{
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(baris1);

    lcd.setCursor(0, 1);
    lcd.print(baris2);
}