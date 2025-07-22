#include <Arduino.h>
#include <WiFiMulti.h>

#include <forge32-protocol.h>
#include <logger.h>

bool ConnectToWifi(
    String ssid, 
    String password, 
    IPAddress ipAddress, 
    IPAddress gateway = IPAddress(192, 168, 1, 1), 
    IPAddress subnet = IPAddress(255, 255, 255, 0)) {
    
    if (WiFi.status() == WL_CONNECTED) { return true; }

    // Attempt to connect to WIFI up to three times.
    WiFi.config(ipAddress, gateway, subnet);
    for (int i = 0; i < 3; i++) {
        Log("WIFI", "Attempting to connect to: \"" + ssid + "\"");
        WiFi.begin(ssid, password);
        delay(500);
        if (WiFi.status() == WL_CONNECTED) { break; }
    }
    
    // Display relevant status messages and return results.
    switch (WiFi.status()) {
        case WL_CONNECTED:
            Log("WIFI", "Successfully connected to: \"" + ssid + "\"");
            Log("WIFI", "IP: " + WiFi.localIP().toString());
            return true;
        case WL_NO_SSID_AVAIL: Log("WIFI", "Unable to find: \"" + ssid + "\"");
        case WL_CONNECT_FAILED: Log("WIFI", "Unable to connect to: \"" + ssid + "\"");
        default: Log("WIFI", "Unknown status: " + WiFi.status());
    }
    return false;
}