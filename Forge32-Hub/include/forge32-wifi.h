#include <Arduino.h>
#include <WiFi.h>

bool ConnectToWifi(
    String ssid, 
    String password, 
    IPAddress ipAddress, 
    IPAddress gateway, 
    IPAddress subnet);