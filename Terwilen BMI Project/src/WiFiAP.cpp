#include "WiFiAP.h"

void initWiFiAP()
{
    WiFi.mode(WIFI_AP);

    bool success = WiFi.softAP(AP_SSID, AP_PASSWORD);

    if (success)
    {
        Serial.println();
        Serial.println("=================================");
        Serial.println("HOTSPOT ESP32 BERHASIL DIBUAT");
        Serial.println("=================================");

        Serial.print("SSID     : ");
        Serial.println(AP_SSID);

        Serial.print("Password : ");
        Serial.println(AP_PASSWORD);

        Serial.print("IP ESP32 : ");
        Serial.println(WiFi.softAPIP());

        Serial.println("=================================");
        Serial.println();
    }
    else
    {
        Serial.println("GAGAL membuat hotspot ESP32!");
    }
}

void printWiFiInfo()
{
    Serial.println();
    Serial.println("Status WiFi:");
    Serial.print("SSID : ");
    Serial.println(AP_SSID);

    Serial.print("IP   : ");
    Serial.println(WiFi.softAPIP());
}