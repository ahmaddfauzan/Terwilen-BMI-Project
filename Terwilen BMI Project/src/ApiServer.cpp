#include "ApiServer.h"
#include <WebServer.h>
#include <WiFi.h>

// ======================================================
// WEB SERVER
// ======================================================

WebServer server(80);


// ======================================================
// DATA SENSOR TERAKHIR
// ======================================================

float tinggiTerakhir = 0.0;
float beratTerakhir = 0.0;


// ======================================================
// HALAMAN UTAMA
// Untuk pengecekan melalui browser
// ======================================================

void handleRoot()
{
    String html = "";

    html += "<!DOCTYPE html>";
    html += "<html>";
    html += "<head>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    html += "<title>Posyandu BMI</title>";
    html += "</head>";

    html += "<body>";

    html += "<h1>POSYANDU BMI</h1>";

    html += "<p>Tinggi Badan: ";
    html += String(tinggiTerakhir, 1);
    html += " cm</p>";

    html += "<p>Berat Badan: ";
    html += String(beratTerakhir, 1);
    html += " kg</p>";

    html += "</body>";
    html += "</html>";

    server.send(
        200,
        "text/html",
        html
    );
}


// ======================================================
// API DATA SENSOR
// URL:
// http://192.168.4.1/data
// ======================================================

void handleData()
{
    String json = "{";

    json += "\"tinggi\":";
    json += String(tinggiTerakhir, 1);

    json += ",";

    json += "\"berat\":";
    json += String(beratTerakhir, 1);

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );
}


// ======================================================
// INISIALISASI API SERVER
// ======================================================

void initApiServer()
{
    // Halaman utama
    server.on(
        "/",
        HTTP_GET,
        handleRoot
    );

    // API data sensor
    server.on(
        "/data",
        HTTP_GET,
        handleData
    );

    // Jalankan server
    server.begin();

    Serial.println();
    Serial.println("=================================");
    Serial.println("HTTP SERVER BERHASIL DIMULAI");
    Serial.println("=================================");

    Serial.print("API DATA : http://");
    Serial.print(WiFi.softAPIP());
    Serial.println("/data");

    Serial.println("=================================");
    Serial.println();
}


// ======================================================
// UPDATE DATA SENSOR
// ======================================================

void updateApiServer(
    float tinggi,
    float berat
)
{
    // Simpan tinggi jika valid
    if (!isnan(tinggi) && tinggi > 0)
    {
        tinggiTerakhir = tinggi;
    }

    // Simpan berat jika valid
    if (!isnan(berat))
    {
        beratTerakhir = berat;
    }

    // Menangani request dari Android
    server.handleClient();
}