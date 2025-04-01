#include "network_manager.h"
#include <vector>

std::vector<String> whitelist = {"00:11:22:33:44:55"};  // Trusted devices
std::vector<String> blacklist; // Suspicious devices

void blockDevice(String mac) {
    blacklist.push_back(mac);
    Serial.print("❌ Blacklisted: ");
    Serial.println(mac);
}

bool isWhitelisted(String mac) {
    return std::find(whitelist.begin(), whitelist.end(), mac) != whitelist.end();
}
