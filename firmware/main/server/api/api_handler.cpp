#include "api_handler.h"
#include "../network_monitor/core/network_manager.h"
#include "../network_monitor/logging/logger.h"
#include "../network_monitor/analysis/port_scanner.h"

void setupAPI(AsyncWebServer &server) {
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(200);
        doc["status"] = "Online";
        doc["ip"] = WiFi.localIP().toString();

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
        int startPort = 20, endPort = 100;  // Define port range
        scanPorts(startPort, endPort);      // Call the scanner

        DynamicJsonDocument doc(500);
        doc["message"] = "Port scan completed";
        doc["open_ports"] = getOpenPorts();

        String response;
        serializeJson(doc, response);
        request->send(200, "application/json", response);
    });

    server.on("/log", HTTP_GET, [](AsyncWebServerRequest *request) {
        String logs = Logger::getLogs();  // Retrieve log data
        request->send(200, "text/plain", logs);
    });
}
