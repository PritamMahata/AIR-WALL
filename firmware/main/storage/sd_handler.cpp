#include "sd_handler.h"
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 5

bool initSD() {
    if (!SD.begin(SD_CS_PIN)) {  // Change 5 to your actual CS pin
        Serial.println("SD Card initialization failed!");
        return false;
    }
    Serial.println("SD Card initialized.");
    return true;
}

bool readConfig(String &ssid, String &password) {
    File file = SD.open("/config.json");
    if (!file) {
        Serial.println("Failed to open config file");
        return false;
    }

    // Read JSON content
    String content;
    while (file.available()) {
        content += (char)file.read();
    }
    file.close();

    // Parse JSON
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, content);
    if (error) {
        Serial.println("Failed to parse JSON");
        return false;
    }

    ssid = doc["ssid"].as<String>();
    password = doc["password"].as<String>();
    return true;
}
