#ifndef PORT_SCANNER_H
#define PORT_SCANNER_H

#include <vector>
#include <string>

// Function Declarations
void initPortScanner(const char* ip);             
void scanRiskyPorts();                            
bool isPortOpen(int port);                        
void logVulnerablePorts(int port);
void scanPorts(int startPort, int endPort);                
std::vector<int> getOpenPorts();                  

#endif  // PORT_SCANNER_H
