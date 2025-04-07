#include "sd_handler.h"
#include "../features/hardware/oled_display/oled_display.h"

SDHandler::SDHandler(OLED_Display &oledDisplay, int csPin) : _csPin(csPin), _display(oledDisplay) {}

bool SDHandler::init()
{
    Serial.println("[INFO] Initializing SD card...");
    if (!SD.begin(_csPin))
    {
        Serial.println("[ERROR] SD Card initialization failed.");
        _display.displayError("SD Init Failed");
        return false;
    }

    Serial.println("[OK] SD Card initialized.");
    return true;
}

bool SDHandler::readConfig(String &ssid, String &password)
{
    File file = SD.open("/config.json");
    if (!file)
    {
        Serial.println("[ERROR] Failed to open /config.json");
        _display.displayError("Config File Missing");
        return false;
    }

    String content;
    while (file.available())
    {
        content += (char)file.read();
    }
    file.close();

    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, content);
    if (error)
    {
        Serial.println("[ERROR] Failed to parse config.json");
        _display.displayError("Invalid Config File");
        return false;
    }

    ssid = doc["ssid"].as<String>();
    password = doc["password"].as<String>();

    Serial.println("[OK] Config Loaded:");
    Serial.println("SSID: " + ssid);
    return true;
}