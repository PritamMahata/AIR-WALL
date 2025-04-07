#include "server.h"
#include "../api/api_handler.h"

AsyncWebServer server(80);

void startServer() {
    setupAPI(server);
    server.begin();
    Serial.println("🚀 Web Server Started!");
}
