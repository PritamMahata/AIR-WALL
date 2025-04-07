#include "wifi_handler.h"

WiFiHandler::WiFiHandler(SDHandler &sdHandler, Logger &logger) : sd(sdHandler), log(logger) {}

void WiFiHandler::connect()
{
    String ssid, password;

    if (!sd.init())
    {
        Serial.println("[ERROR] SD Card initialization failed.");
        log.add("[ERROR] SD Card initialization failed.");
        return;
    }

    if (!sd.readConfig(ssid, password))
    {
        Serial.println("[ERROR] Failed to read WiFi config.");
        log.add("[ERROR] Failed to read WiFi config.");
        return;
    }

    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("[INFO] Connecting to WiFi");
    log.add("[INFO] Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\n[OK] Connected to WiFi!");
    log.add("[OK] Connected to WiFi!");
}