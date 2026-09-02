#include <Arduino.h>

#include "HeightSensor.h"
#include "WeightSensor.h"
#include "LCD.h"
#include "WiFiAP.h"
#include "ApiServer.h"


// =====================================================
// PIN BUTTON
// =====================================================

#define BUTTON_HOLD   25
#define BUTTON_RESET  26
#define BUTTON_TARE   27


// =====================================================
// STATUS HOLD
// =====================================================

bool isHold = false;

float tinggiHold = 0;
float beratHold = 0;
float tareWeight = 0;


// =====================================================
// STATUS BUTTON SEBELUMNYA
// =====================================================

bool lastHoldButton = HIGH;
bool lastResetButton = HIGH;
bool lastTareButton = HIGH;


// =====================================================
// SETUP
// =====================================================

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_HOLD, INPUT_PULLUP);
    pinMode(BUTTON_RESET, INPUT_PULLUP);
    pinMode(BUTTON_TARE, INPUT_PULLUP);


    initLCD();

    initHeightSensor();

    initWeightSensor();

    initWiFiAP();

    initApiServer();

    Serial.println("SISTEM SIAP");
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
    // =================================================
    // BACA SENSOR
    // =================================================

    float tinggiSensor = readHeightCM();

    float beratSensor = readWeight();


    // =================================================
    // BACA STATUS BUTTON
    // =================================================

    bool holdButton =
        digitalRead(BUTTON_HOLD);

    bool resetButton =
        digitalRead(BUTTON_RESET);

    bool tareButton =
        digitalRead(BUTTON_TARE);


    // =================================================
    // BUTTON HOLD
    // Deteksi HIGH -> LOW
    // =================================================

    if (lastHoldButton == HIGH &&
        holdButton == LOW)
    {
        if (!isHold)
        {
            tinggiHold = tinggiSensor;

            beratHold =
                beratSensor - tareWeight;

            if (beratHold < 0)
            {
                beratHold = 0;
            }

            isHold = true;

            Serial.println(">>> HOLD AKTIF <<<");
        }
    }


    // =================================================
    // BUTTON TARE
    // =================================================

    if (lastTareButton == HIGH &&
        tareButton == LOW)
    {
        tareWeight = beratSensor;

        Serial.print(">>> TARE: ");

        Serial.print(
            tareWeight,
            2
        );

        Serial.println(" kg <<<");
    }


    // =================================================
    // BUTTON RESET
    // =================================================

    if (lastResetButton == HIGH &&
        resetButton == LOW)
    {
        // Lepaskan HOLD
        isHold = false;

        tinggiHold = 0;
        beratHold = 0;
        tareWeight = 0;


        Serial.println(
            ">>> RESET <<<"
        );
    }


    // =================================================
    // SIMPAN STATUS BUTTON
    // =================================================

    lastHoldButton =
        holdButton;

    lastResetButton =
        resetButton;

    lastTareButton =
        tareButton;


    // =================================================
    // HITUNG BERAT BERSIH
    // =================================================

    float beratBersih =
        beratSensor - tareWeight;


    if (beratBersih < 0)
    {
        beratBersih = 0;
    }


    // =================================================
    // DATA DISPLAY
    // =================================================

    float tinggiDisplay;
    float beratDisplay;


    if (isHold)
    {
        tinggiDisplay =
            tinggiHold;

        beratDisplay =
            beratHold;
    }
    else
    {
        tinggiDisplay =
            tinggiSensor;

        beratDisplay =
            beratBersih;
    }


    // =================================================
    // TAMPILKAN KE LCD
    // =================================================

    showMeasurement(
        tinggiDisplay,
        beratDisplay,
        isHold
    );


    // =================================================
    // SERIAL MONITOR
    // =================================================

    Serial.print("TB : ");
    Serial.print(tinggiDisplay, 1);
    Serial.println(" cm");

    Serial.print("BB : ");
    Serial.print(beratDisplay, 2);
    Serial.println(" kg");


    Serial.print("HOLD : ");

    if (isHold)
        Serial.println("ON");
    else
        Serial.println("OFF");

    Serial.println("-------------------");


    // =================================================
    // UPDATE API
    // =================================================

    updateApiServer(
        tinggiDisplay,
        beratDisplay
    );


    delay(100);
}