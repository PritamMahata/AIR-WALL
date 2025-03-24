#ifndef SD_HANDLER_H
#define SD_HANDLER_H

#include <ArduinoJson.h>

#define CONFIG_FILE "/config.json"

bool initSD();
bool readConfig(String &ssid, String &password);

#endif
