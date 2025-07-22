#include <Arduino.h>
#include <WebServer.h>
#include <LittleFS.h>
#include "time.h"

#include "forge32-protocol.h"
#include "forge32-wifi.h"
#include "passwords.h"
#include "logger.h"

#define FORMAT_LITTLEFS_IF_FAILED true
#define WIFI_STATUS_PIN BUILTIN_LED

#define NTP_SERVER "pool.ntp.org"
#define NTP_SERVER_2 "time.nist.gov"
#define TIMEZONE_OFFSET -28800

#define OUTPUT_0 GPIO_NUM_23

WebServer server(80);

void InitLittleFS();
void InitWebServer();
void InitTime();

String getLocalTimeString();

void setup() {
    // Initialize serial communication
    InitSerial();
    Log("SYSTEM", "Starting Forge32 Hub");

    //Initialize GPIO
    pinMode(WIFI_STATUS_PIN, OUTPUT);
    pinMode(OUTPUT_0, OUTPUT);

    // GPIO Default State
    digitalWrite(WIFI_STATUS_PIN, LOW);
    digitalWrite(OUTPUT_0, LOW);

    // Initialize TCP connection
    bool wifiStatus = ConnectToWifi(
        TH_SSID, 
        TH_PASSWORD, 
        IPAddress(192, 168, 1, 2), 
        IPAddress(192, 168, 1, 1), 
        IPAddress(255, 255, 255, 0)
    );
    if (wifiStatus) { digitalWrite(WIFI_STATUS_PIN, HIGH); }

    // Initialize time
    InitTime();

    // Initialize LittleFS
    InitLittleFS();

    // // Initialize web server
    InitWebServer();

    Log("SYSTEM", "ESP Setup complete");
}

#pragma region Init Functions
void InitTime() {
    configTime(TIMEZONE_OFFSET, 3600, NTP_SERVER, NTP_SERVER_2);
    Log("TIME", "NTP Time Configured");
    Log("TIME", getLocalTimeString());
}

void InitLittleFS() {
    if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
        Log("LITTLEFS", "Failed to mount file system");
    } else {
        Log("LITTLEFS", "File system mounted successfully");
    }
}

void InitWebServer() {

    server.on("/", HTTP_GET, []() {
        Log("HTTP", "Serving index.html");
        File f = LittleFS.open("/index.html", "r");
        server.send(200, "text/html", f.readString());
        f.close();
    });

    server.on("/style.css", HTTP_GET, []() {
        Log("HTTP", "Serving style.css");
        File f = LittleFS.open("/style.css", "r");
        server.send(200, "text/css", f.readString());
        f.close();
    });

    server.on("/script.js", HTTP_GET, []() {
        Log("HTTP", "Serving script.js");
        File f = LittleFS.open("/script.js", "r");
        server.send(200, "application/javascript", f.readString());
        f.close();
    });

    server.on("/jquery-3.7.1.min.js", HTTP_GET, []() {
        Log("HTTP", "Serving jquery-3.7.1.min.js");
        File f = LittleFS.open("/jquery-3.7.1.min.js", "r");
        server.send(200, "text/javascript", f.readString());
        f.close();
    });

    server.on("/servertime", HTTP_GET, []() {
        Log("HTTP", "Serving servertime.");
        String currentTime = getLocalTimeString();
        if (currentTime.isEmpty()) {
            server.send(500, "text/plain", "N/A");
        } else {
            server.send(200, "text/plain", currentTime);
        }
    });

    server.on("/connect_click", HTTP_GET, []() {
        Log("HTTP", "Connect clicked");
        server.send(200, "text/plain", "Connect clicked successfully");
        digitalWrite(OUTPUT_0, HIGH); 
    });

    server.on("/disconnect_click", HTTP_GET, []() {
        Log("HTTP", "Disconnect clicked");
        server.send(200, "text/plain", "Disconnected clicked successfully");
        digitalWrite(OUTPUT_0, LOW); 
    });

    server.onNotFound([](){
        server.send(404, "text/plain", "404: Not Found");
    });
    
    // Initialize the web server
    server.begin();
    Log("HTTP", "HTTP server started on port 80");
}

#pragma region General Functions
String getLocalTimeString() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "";
    }
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%A, %B %d %Y %H:%M:%S", &timeinfo);
    return String(buffer);
}

void loop() {
    server.handleClient();
}
