#include "api_handler.h"
#include "../encryptor.h"
#include "../../features/network_monitor/port_scanner/port_scanner.h"
#include "../../features/network_monitor/core/network_manager.h"
#include "../../utils/logging/logger.h"
#include <ArduinoJson.h>

extern Logger logger;
const String AES_KEY = "1234567890123456"; // 16-byte AES key

// Encrypt and Base64 encode helper using encryptAES from encryptor.cpp
String encryptAndBase64(const String &plainText, const String &key) {
    return encryptAES(plainText, key); // Handles AES + Base64 internally
}

// Helper to add CORS headers to all responses
void addCORSHeaders(AsyncWebServerResponse *response) {
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    response->addHeader("Access-Control-Allow-Headers", "Content-Type");
}

void setupAPI(AsyncWebServer &server) {
    // /status endpoint
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(200);
        doc["status"] = "Online";
        doc["ip"] = WiFi.localIP().toString();

        String json;
        serializeJson(doc, json);

        String encryptedBase64 = encryptAndBase64(json, AES_KEY);
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", encryptedBase64);
        addCORSHeaders(response);
        request->send(response);
    });

    // /scan endpoint
    server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
        int startPort = 20, endPort = 100;
        scanPorts(startPort, endPort);

        DynamicJsonDocument doc(1024);
        doc["message"] = "Port scan completed";

        JsonArray portArray = doc.createNestedArray("open_ports");
        for (int port : getOpenPorts()) {
            portArray.add(port);
        }

        String json;
        serializeJson(doc, json);

        String encryptedBase64 = encryptAndBase64(json, AES_KEY);
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", encryptedBase64);
        addCORSHeaders(response);
        request->send(response);
    });

    // /log endpoint
    server.on("/log", HTTP_GET, [](AsyncWebServerRequest *request) {
        String logs = logger.getLogs();
        String encryptedBase64 = encryptAndBase64(logs, AES_KEY);
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", encryptedBase64);
        addCORSHeaders(response);
        request->send(response);
    });


    // /decrypt POST
    server.on("/decrypt", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("data", true)) {
            String encryptedData = request->getParam("data", true)->value();
            String decrypted = decryptAES(encryptedData, AES_KEY);
            AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", decrypted);
            addCORSHeaders(response);
            request->send(response);
        } else {
            AsyncWebServerResponse *response = request->beginResponse(400, "text/plain", "Missing data");
            addCORSHeaders(response);
            request->send(response);
        }
    });

    // /network endpoint
    server.on("/network", HTTP_GET, [](AsyncWebServerRequest *request) {
        DynamicJsonDocument doc(512);
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
        doc["connected"] = (WiFi.status() == WL_CONNECTED);
        doc["scan_count"] = WiFi.scanComplete();
        doc["scan_time"] = WiFi.scanNetworks(true);
        doc["scan_result"] = WiFi.scanNetworks(false, true);
        doc["scan_result_count"] = WiFi.scanComplete();
        doc["scan_result_time"] = WiFi.scanNetworks(true, true);

        String json;
        serializeJson(doc, json);

        String encryptedBase64 = encryptAndBase64(json, AES_KEY);
        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", encryptedBase64);
        addCORSHeaders(response);
        request->send(response);
    });

    // Catch-all 404
    server.onNotFound([](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(404, "text/plain", "Not Found");
        addCORSHeaders(response);
        request->send(response);
    });
}
