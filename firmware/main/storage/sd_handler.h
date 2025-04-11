#ifndef SD_HANDLER_H
#define SD_HANDLER_H

#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include "../features/hardware/oled_display/oled_display.h"

class SDHandler
{
public:
    SDHandler(OLED_Display &oledDisplay, int csPin = 5);
    bool init();
    bool readConfig(String &ssid, String &password);
    bool readMode(String &mode);
    bool writeMode(const String &mode);

private:
    int _csPin;
    OLED_Display &_display;
};

#endif