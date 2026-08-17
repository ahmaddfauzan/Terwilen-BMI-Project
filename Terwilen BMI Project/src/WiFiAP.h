#ifndef WIFI_AP_H
#define WIFI_AP_H

#include <Arduino.h>
#include <WiFi.h>

#define AP_SSID "POSYANDU_BMI"
#define AP_PASSWORD "12345678"

void initWiFiAP();
void printWiFiInfo();

#endif