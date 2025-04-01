#ifndef PORT_SCANNER_H
#define PORT_SCANNER_H

#include <vector>
#include <Arduino.h> // Required for ESP32 compatibility

// Function Declarations
void initPortScanner(const char* ip);
void scanPorts(int startPort, int endPort);
std::vector<int> getOpenPorts();
bool isPortOpen(int port);
void logVulnerablePorts(int port);

#endif // PORT_SCANNER_H
