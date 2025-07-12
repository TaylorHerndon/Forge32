#include <Arduino.h>
#include <forge32-protocol.h>
#include <forge32-wifi.h>
#include <logger.h>
#include <passwords.h>

#define WIFI_STATUS_PIN BUILTIN_LED

void setup() {
    // Initialize serial communication
    InitSerial();
    Log("SYSTEM", "Starting Forge32 Hub");

    //Initialize GPIO
    pinMode(WIFI_STATUS_PIN, OUTPUT);

    // GPIO Default State
    digitalWrite(WIFI_STATUS_PIN, LOW);

    // Initialize TCP connection
    bool wifiStatus = ConnectToWifi(
        TH_SSID, 
        TH_PASSWORD, 
        IPAddress(192, 168, 1, 2), 
        IPAddress(192, 168, 1, 1), 
        IPAddress(255, 255, 255, 0)
    );
    if (wifiStatus) { digitalWrite(WIFI_STATUS_PIN, HIGH); }
}

void loop() {
    
}
