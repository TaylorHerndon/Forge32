#include <Arduino.h>

void InitSerial() {
    Serial.begin(115200);
    Serial.println("[SYSTEM][LOG]: Serial Setup Complete");
}

void Log(String logTag, String logMessage) {
    logTag.toUpperCase();
    Serial.println("[" + logTag + "][LOG]: " + logMessage);
}

void Error(String logTag, String errorMessage) {
    logTag.toUpperCase();
    Serial.println("[" + logTag + "][ERROR]: " + errorMessage);
}