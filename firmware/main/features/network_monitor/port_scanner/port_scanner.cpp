#include "port_scanner.h"
// #include "../../../utils/logger.h"
#include <WiFi.h>

// Global variables
static std::string targetIP;
static std::vector<int> openPorts;

// Initialize Port Scanner
void initPortScanner(const char* ip) {  
    targetIP = std::string(ip);  // Convert to std::string
    openPorts.clear();
}

// Scan Ports
void scanPorts(int startPort, int endPort) {
    openPorts.clear();
    for (int port = startPort; port <= endPort; port++) {
        Serial.println("Scanning Port: " + String(port));
        if (isPortOpen(port)) {
            openPorts.push_back(port);
            Serial.println("Open Port: " + String(port));
            logVulnerablePorts(port);
        }
    }
}

// Check if Port is Open
bool isPortOpen(int port) {
    WiFiClient client;
    if (client.connect(targetIP.c_str(), port)) {
        client.stop();
        return true;
    }
    return false;
}

// Log Risky Ports
void logVulnerablePorts(int port) {
    int riskyPorts[] = {21, 22, 23, 25, 80, 110, 139, 445, 3389};
    for (int i = 0; i < 9; i++) {
        if (port == riskyPorts[i]) {
            Serial.println("⚠️ Warning: Port " + String(port) + " is commonly exploited!");
        }
    }
}

// Get Open Ports
std::vector<int> getOpenPorts() {
    return openPorts;
}
