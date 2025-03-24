#include "wifi_handler.h"
#include "../../storage/sd_handler.h"
#include "../../utils/logging/logger.h"
#include <WiFi.h>
#include <SD.h>

void connectWiFi() {
    String ssid, password;

    if (!initSD()) {
        Serial.println("SD Card init failed");
    } else if (!readConfig(ssid, password)) {
        Serial.println("Failed to read WiFi config");
    }

    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
}
