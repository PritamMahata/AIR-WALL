#ifndef API_HANDLER_H
#define API_HANDLER_H

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

void setupAPI(AsyncWebServer &server);  // Initialize API endpoints

#endif
