#ifndef WIFI_HANDLER_H 
#define WIFI_HANDLER_H

#include <WiFi.h> 
#include "../../storage/sd_handler.h"
#include "../../utils/logging/logger.h"

class WiFiHandler
{
public:
    WiFiHandler(SDHandler &sdHandler, Logger &logger);
    void connect();

private:
    SDHandler &sd;
    Logger &log;
};

#endif