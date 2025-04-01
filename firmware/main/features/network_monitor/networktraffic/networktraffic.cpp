#include "networktraffic.h"
#include "../storage/sd_handler.h"
#include "../network_monitor/alert_manager.h"
#include "../utils/logger.h"
#include <ArduinoJson.h>
#include <WebSocketsServer.h>

WebSocketsServer webSocket(WEBSOCKET_PORT);
std::vector<String> knownDevices = {"00:1A:2B:3C:4D:5E"}; 
std::vector<TrafficData> trafficStats;

// 🟢 Initialize Network Sniffing
void startNetworkMonitoring() {
    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(sniffPacket);
    esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);
    webSocket.begin();
    Serial.println("📡 Network Traffic Monitoring Started...");
}

// 🟡 Packet Sniffer Callback
void sniffPacket(void* buf, wifi_promiscuous_pkt_type_t type) {
    if (type != WIFI_PKT_MGMT && type != WIFI_PKT_DATA) return;

    wifi_promiscuous_pkt_t* packet = (wifi_promiscuous_pkt_t*)buf;
    uint8_t* macAddr = packet->payload + 10;

    char macStr[18];
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", 
            macAddr[0], macAddr[1], macAddr[2], 
            macAddr[3], macAddr[4], macAddr[5]);

    bool found = false;
    for (auto &data : trafficStats) {
        if (data.macAddress == String(macStr)) {
            data.packetCount++;
            found = true;
            break;
        }
    }

    if (!found) {
        bool isUnknown = (std::find(knownDevices.begin(), knownDevices.end(), String(macStr)) == knownDevices.end());
        trafficStats.push_back({String(macStr), 1, isUnknown});
        if (isUnknown) {
            Serial.println("🚨 ALERT: Unknown device detected → " + String(macStr));
        }
    }
}

// 🔵 Analyze Traffic
void analyzeTraffic() {
    for (const auto& data : trafficStats) {
        String status = data.isUnknown ? "🚨 Unknown" : "✅ Known";
        Serial.println("🔹 " + data.macAddress + " → Packets: " + String(data.packetCount) + " (" + status + ")");
    }
}

// 🟣 Send Data to Web Clients
void sendTrafficDataToWeb() {
    DynamicJsonDocument doc(1024);
    JsonArray trafficArray = doc.createNestedArray("traffic");

    for (const auto& data : trafficStats) {
        JsonObject entry = trafficArray.createNestedObject();
        entry["mac"] = data.macAddress;
        entry["packets"] = data.packetCount;
        entry["status"] = data.isUnknown ? "Unknown" : "Known";
    }

    String jsonString;
    serializeJson(doc, jsonString);
    webSocket.broadcastTXT(jsonString);
}

// Process WebSocket Data
void processWebSocket() {
    webSocket.loop();
}
