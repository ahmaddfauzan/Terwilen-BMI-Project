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

float tinggiHold = 0.0;
float beratHold = 0.0;
float imtHold = 0.0;


// =====================================================
// TARE
// =====================================================

// Berat yang dijadikan titik nol sementara.
//
// Contoh:
//
// Ibu = 55 kg
// TARE
// tareWeight = 55 kg
//
// Anak + ibu = 67 kg
// berat bersih = 67 - 55 = 12 kg
//
float tareWeight = 0.0;


// =====================================================
// STATUS INDIKATOR TARE
// =====================================================

// TRUE hanya selama indikator T ditampilkan
bool isTare = false;

// Waktu ketika TARE ditekan
unsigned long tareStartTime = 0;

// Durasi indikator TARE
const unsigned long TARE_DISPLAY_TIME = 1000;


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


    // =================================================
    // BUTTON
    // =================================================

    pinMode(
        BUTTON_HOLD,
        INPUT_PULLUP
    );

    pinMode(
        BUTTON_RESET,
        INPUT_PULLUP
    );

    pinMode(
        BUTTON_TARE,
        INPUT_PULLUP
    );


    // =================================================
    // INIT SYSTEM
    // =================================================

    initLCD();

    initHeightSensor();

    initWeightSensor();

    initWiFiAP();

    initApiServer();


    Serial.println();
    Serial.println("======================");
    Serial.println("    SISTEM SIAP");
    Serial.println("======================");
    Serial.println();
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
    // =================================================
    // BACA SENSOR
    // =================================================

    float tinggiSensor =
        readHeightCM();

    float beratSensor =
        readWeight();


    // =================================================
    // BACA BUTTON
    // =================================================

    bool holdButton =
        digitalRead(BUTTON_HOLD);

    bool resetButton =
        digitalRead(BUTTON_RESET);

    bool tareButton =
        digitalRead(BUTTON_TARE);


    // =================================================
    // BUTTON TARE
    // HIGH -> LOW
    // =================================================

    if (lastTareButton == HIGH &&
        tareButton == LOW)
    {
        // =============================================
        // SIMPAN BERAT SEBAGAI TITIK NOL
        // =============================================

        tareWeight =
            beratSensor;


        // =============================================
        // AKTIFKAN INDIKATOR TARE
        // =============================================

        isTare = true;

        tareStartTime = millis();


        // =============================================
        // SERIAL
        // =============================================

        Serial.println();
        Serial.println(">>> TARE <<<");

        Serial.print("Tare Weight : ");
        Serial.print(
            tareWeight,
            2
        );

        Serial.println(" kg");
    }


    // =================================================
    // MATIKAN INDIKATOR TARE
    // SETELAH 1 DETIK
    // =================================================

    if (isTare)
    {
        if (
            millis() - tareStartTime
            >= TARE_DISPLAY_TIME
        )
        {
            isTare = false;
        }
    }


    // =================================================
    // HITUNG BERAT BERSIH
    // =================================================

    float beratBersih =
        beratSensor - tareWeight;


    // Jangan tampilkan berat negatif
    if (beratBersih < 0)
    {
        beratBersih = 0;
    }


    // =================================================
    // BUTTON HOLD
    // HIGH -> LOW
    // =================================================

    if (lastHoldButton == HIGH &&
        holdButton == LOW)
    {
        // HOLD hanya boleh mengambil nilai
        // ketika belum HOLD

        if (!isHold)
        {
            // =========================================
            // SIMPAN TINGGI
            // =========================================

            tinggiHold =
                tinggiSensor;


            // =========================================
            // SIMPAN BERAT BERSIH
            // =========================================

            beratHold =
                beratBersih;


            // =========================================
            // HITUNG IMT
            // =========================================

            if (tinggiHold > 0)
            {
                float tinggiMeter =
                    tinggiHold / 100.0;

                imtHold =
                    beratHold /
                    (
                        tinggiMeter *
                        tinggiMeter
                    );
            }
            else
            {
                imtHold = 0;
            }


            // =========================================
            // AKTIFKAN HOLD
            // =========================================

            isHold = true;


            Serial.println();
            Serial.println(">>> HOLD AKTIF <<<");

            Serial.print("TB : ");
            Serial.print(
                tinggiHold,
                1
            );

            Serial.println(" cm");

            Serial.print("BB : ");
            Serial.print(
                beratHold,
                2
            );

            Serial.println(" kg");

            Serial.print("IMT: ");
            Serial.println(
                imtHold,
                2
            );
        }
    }


    // =================================================
    // BUTTON RESET
    // HIGH -> LOW
    // =================================================

    if (lastResetButton == HIGH &&
        resetButton == LOW)
    {
        // =============================================
        // RESET HANYA UNTUK HOLD
        // =============================================

        isHold = false;

        tinggiHold = 0.0;
        beratHold = 0.0;
        imtHold = 0.0;


        // =============================================
        // JANGAN RESET tareWeight !!!
        // =============================================

        Serial.println();
        Serial.println(">>> RESET HOLD <<<");

        Serial.print(
            "Tare tetap: "
        );

        Serial.print(
            tareWeight,
            2
        );

        Serial.println(" kg");
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
    // DATA DISPLAY
    // =================================================

    float tinggiDisplay;
    float beratDisplay;
    float imtDisplay;


    if (isHold)
    {
        // =============================================
        // HOLD
        // =============================================

        tinggiDisplay =
            tinggiHold;

        beratDisplay =
            beratHold;

        imtDisplay =
            imtHold;
    }
    else
    {
        // =============================================
        // LIVE
        // =============================================

        tinggiDisplay =
            tinggiSensor;

        beratDisplay =
            beratBersih;


        // =============================================
        // HITUNG IMT
        // =============================================

        if (tinggiDisplay > 0)
        {
            float tinggiMeter =
                tinggiDisplay / 100.0;

            imtDisplay =
                beratDisplay /
                (
                    tinggiMeter *
                    tinggiMeter
                );
        }
        else
        {
            imtDisplay = 0;
        }
    }


    // =================================================
    // LCD
    // =================================================

    showMeasurement(
        tinggiDisplay,
        beratDisplay,
        imtDisplay,
        isHold,
        isTare
    );


    // =================================================
    // SERIAL MONITOR
    // =================================================

    Serial.print("TB : ");
    Serial.print(
        tinggiDisplay,
        1
    );

    Serial.println(" cm");


    Serial.print("BB : ");
    Serial.print(
        beratDisplay,
        2
    );

    Serial.println(" kg");


    Serial.print("IMT: ");
    Serial.println(
        imtDisplay,
        2
    );


    Serial.print("TARE: ");
    Serial.print(
        tareWeight,
        2
    );

    Serial.println(" kg");


    Serial.print("HOLD: ");

    if (isHold)
        Serial.println("ON");
    else
        Serial.println("OFF");


    Serial.print("T INDICATOR: ");

    if (isTare)
        Serial.println("ON");
    else
        Serial.println("OFF");


    Serial.println("-------------------");


    // =================================================
    // API
    // =================================================

    updateApiServer(
        tinggiDisplay,
        beratDisplay
    );


    delay(100);
}