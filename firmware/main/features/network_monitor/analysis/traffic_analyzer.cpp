#include "traffic_analyzer.h"
#include <map>

std::map<String, int> deviceTraffic; // Store MAC traffic data

void analyzeTraffic(String mac, int packetSize) {
    deviceTraffic[mac] += packetSize;
    Serial.print("📊 Device: ");
    Serial.print(mac);
    Serial.print(" - Data Used: ");
    Serial.println(deviceTraffic[mac]);
}

// for graph display
