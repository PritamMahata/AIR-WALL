#include "port_scanner.h"
// #include "../../../utils/logger.h"
#include <WiFi.h>

// Global variables
static std::string targetIP;
static std::vector<int> openPorts;

static unsigned long lastScanTime = 0;
static unsigned long scanInterval = 50; // Scan interval in milliseconds
static int currentPortIndex = 0;        // Start from the first port in the riskyPorts array

// List of risky ports
int riskyPorts[] = {
    21,    // FTP
    22,    // SSH
    23,    // Telnet
    25,    // SMTP
    80,    // HTTP
    110,   // POP3
    139,   // NetBIOS
    445,   // SMB
    3306,  // MySQL
    3389,  // RDP
    8080   // HTTP-alt
};

// Initialize Port Scanner
void initPortScanner(const char *ip)
{
    targetIP = std::string(ip); // Convert to std::string
    openPorts.clear();
    currentPortIndex = 0; // Reset the index to the first port
}

// Scan Only Risky Ports
void scanRiskyPorts()
{
    unsigned long currentMillis = millis();

    // Only check ports at regular intervals
    if (currentMillis - lastScanTime >= scanInterval)
    {
        lastScanTime = currentMillis;

        // Check if there are still ports to scan
        if (currentPortIndex < sizeof(riskyPorts) / sizeof(riskyPorts[0]))
        {
            int port = riskyPorts[currentPortIndex];
            Serial.println("Scanning Port: " + String(port));

            // Check if the port is open
            if (isPortOpen(port))
            {
                openPorts.push_back(port);
                Serial.println("Open Port: " + String(port));
                logVulnerablePorts(port);
            }

            // Move to the next port in the list
            currentPortIndex++;
        }
        else
        {
            Serial.println("Port scan completed.");
        }
    }
}

// Check if Port is Open
bool isPortOpen(int port)
{
    WiFiClient client;
    if (client.connect(targetIP.c_str(), port))
    {
        client.stop();
        return true;
    }
    return false;
}

// Log Risky Ports
void logVulnerablePorts(int port)
{
    for (int i = 0; i < sizeof(riskyPorts) / sizeof(riskyPorts[0]); i++)
    {
        if (port == riskyPorts[i])
        {
            Serial.println("⚠️ Warning: Port " + String(port) + " is commonly exploited!");
        }
    }
}

// Get Open Ports
std::vector<int> getOpenPorts()
{
    return openPorts;
}

#include "port_scanner.h"

void scanPorts(int startPort, int endPort) {
    // Your port scanning logic here
    // E.g., iterating over the range [startPort, endPort] and checking which ports are open
    for (int port = startPort; port <= endPort; ++port) {
        if (isPortOpen(port)) {
            openPorts.push_back(port);  // Store the open ports
        }
    }
}
