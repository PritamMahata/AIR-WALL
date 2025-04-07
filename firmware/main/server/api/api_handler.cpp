#include "api_handler.h"
#include "../encryptor.h"
#include "../../features/network_monitor/port_scanner/port_scanner.h"
#include "../../features/network_monitor/core/network_manager.h"
#include "../../utils/logging/logger.h"
#include <ArduinoJson.h>

extern Logger logger;
const String AES_KEY = "1234567890123456"; // 16-byte key

void setupAPI(AsyncWebServer &server)
{
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        DynamicJsonDocument doc(200);
        doc["status"] = "Online";
        doc["ip"] = WiFi.localIP().toString();

        String json;
        serializeJson(doc, json);

        String encrypted = encryptAES(json, AES_KEY);
        request->send(200, "application/octet-stream", encrypted); });

    server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        int startPort = 20, endPort = 100;
        scanPorts(startPort, endPort);

        DynamicJsonDocument doc(1024);
        doc["message"] = "Port scan completed";

        JsonArray portArray = doc.createNestedArray("open_ports");
        std::vector<int> ports = getOpenPorts();
        for (int port : ports)
        {
            portArray.add(port);
        }

        String json;
        serializeJson(doc, json);

        String encrypted = encryptAES(json, AES_KEY);
        request->send(200, "application/octet-stream", encrypted); });

    server.on("/decrypt", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("data", true)) {
            String encryptedData = request->getParam("data", true)->value();
            String decrypted = decryptAES(encryptedData, AES_KEY);
            request->send(200, "text/plain", decrypted);
        } else {
            request->send(400, "text/plain", "Missing data");
        } });

    server.on("/log", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String logs = logger.getLogs();
        String encrypted = encryptAES(logs, AES_KEY);
        request->send(200, "application/octet-stream", encrypted); });
}
