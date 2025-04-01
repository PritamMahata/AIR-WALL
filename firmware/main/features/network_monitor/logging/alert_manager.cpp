#include "alert_manager.h"
#include "../utils/logger.h"
#include "../server/api_handler.h"

void AlertManager::sendAlert(const String& mac) {
    Logger::log("🚨 ALERT: Unknown device detected - " + mac);
    
    // Send alert to web interface
    String alertJson = "{\"alert\": \"Unknown device detected: " + mac + "\"}";
    ApiHandler::sendDataToClient(alertJson);
}
