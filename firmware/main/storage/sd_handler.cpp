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

bool SDHandler::readMode(String &mode)
{
    File file = SD.open("/config.json", FILE_READ);
    if (!file)
    {
        Serial.println("[WARN] config.json not found. Creating default mode...");
        return writeMode("passive") && (mode = "passive", true);
    }

    DynamicJsonDocument doc(512);
    DeserializationError err = deserializeJson(doc, file);
    file.close();
    if (err || !doc.containsKey("mode"))
    {
        Serial.println("[WARN] Invalid config or missing 'mode'. Setting to passive...");
        return writeMode("passive") && (mode = "passive", true);
    }

    mode = doc["mode"].as<String>();
    return true;
}

bool SDHandler::writeMode(const String &mode)
{
    File file = SD.open("/config.json", FILE_READ);
    if (!file)
        return false;
    DynamicJsonDocument doc(512);
    deserializeJson(doc, file);
    file.close();

    doc["mode"] = mode;

    file = SD.open("/config.json", FILE_WRITE);
    if (!file)
        return false;
    serializeJson(doc, file);
    file.close();
    return true;
}
// This code is a simple SD card handler for an Arduino project. It initializes the SD card, reads configuration data (SSID and password) from a JSON file, and allows writing a mode back to the JSON file. The OLED display is used to show error messages when something goes wrong.
// The code uses the ArduinoJson library to handle JSON data and the SD library for SD card operations. The SDHandler class encapsulates all the functionality related to the SD card, making it easy to use in other parts of the project.