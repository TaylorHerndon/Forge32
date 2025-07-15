#include <Arduino.h>
#include <forge32-protocol.h>
#include <forge32-wifi.h>
#include <logger.h>
#include <passwords.h>
#include <WebServer.h>
#include <LittleFS.h>

#define FORMAT_LITTLEFS_IF_FAILED true
#define WIFI_STATUS_PIN BUILTIN_LED

#define OUTPUT_0 GPIO_NUM_23

WebServer server(80);

void InitLittleFS();
void InitWebServer();

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

    // Initialize LittleFS
    InitLittleFS();

    // // Initialize web server
    InitWebServer();
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
        File f = LittleFS.open("/index.html", "r");
        server.send(200, "text/html", f.readString());
        f.close();
    });

    server.on("/style.css", HTTP_GET, []() {
        File f = LittleFS.open("/style.css", "r");
        server.send(200, "text/css", f.readString());
        f.close();
    });

    server.on("/script.js", HTTP_GET, []() {
        File f = LittleFS.open("/script.js", "r");
        server.send(200, "application/javascript", f.readString());
        f.close();
    });

    server.on("/connect_click", HTTP_GET, []() {
        // Handle button click
        Log("HTTP", "Connect clicked");
        server.send(200, "text/plain", "Connect clicked successfully");
        digitalWrite(OUTPUT_0, HIGH); 
    });

    server.on("/disconnect_click", HTTP_GET, []() {
        // Handle disconnect button click
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


void loop() {
    server.handleClient();
}
