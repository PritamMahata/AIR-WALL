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

    server.on("/log", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String logs = logger.getLogs();
        String encrypted = encryptAES(logs, AES_KEY);
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

    server.on("/network", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        DynamicJsonDocument doc(200);
        doc["status"] = "Online";
        doc["ip"] = WiFi.localIP().toString();
        doc["gateway"] = WiFi.gatewayIP().toString();
        doc["subnet"] = WiFi.subnetMask().toString();
        doc["dns"] = WiFi.dnsIP().toString();
        doc["mac"] = WiFi.macAddress();
        doc["hostname"] = WiFi.getHostname();
        doc["ssid"] = WiFi.SSID();
        doc["rssi"] = WiFi.RSSI();
        doc["channel"] = WiFi.channel();
        doc["bssid"] = WiFi.BSSIDstr();
        doc["connected"] = WiFi.status() == WL_CONNECTED ? true : false;
        doc["scan_count"] = WiFi.scanComplete();
        doc["scan_time"] = WiFi.scanNetworks(true);
        doc["scan_result"] = WiFi.scanNetworks(false, true);
        doc["scan_result_count"] = WiFi.scanComplete();
        doc["scan_result_time"] = WiFi.scanNetworks(true, true);
        String json;
        serializeJson(doc, json);

        String encrypted = encryptAES(json, AES_KEY);
        request->send(200, "application/octet-stream", encrypted); });


    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404, "text/plain", "Not Found"); });

}
