#ifndef NETWORK_TRAFFIC_H
#define NETWORK_TRAFFIC_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <ArduinoJson.h>
#include <WebSocketsServer.h>

#define WEBSOCKET_PORT 81

struct TrafficData {
    String macAddress;
    int packetCount;
    bool isUnknown;
};

void startNetworkMonitoring();
void sniffPacket(void* buf, wifi_promiscuous_pkt_type_t type);
void analyzeTraffic();
void sendTrafficDataToWeb();
void processWebSocket();

#endif
