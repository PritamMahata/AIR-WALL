#include "network_sniffer.h"
#include <set>

// Store unique MAC addresses to avoid duplicates
std::set<String> seenMacs;

// Callback function to process captured packets
void packetSniffer(void* buf, wifi_promiscuous_pkt_type_t type) {
    wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*) buf;
    uint8_t* payload = pkt->payload;

    if (type == WIFI_PKT_MGMT) { // Management frames (Beacon, Probe Request, etc.)
        if (payload[0] == 0x80) { // Beacon Frame
            char macAddr[18];
            snprintf(macAddr, sizeof(macAddr), "%02X:%02X:%02X:%02X:%02X:%02X",
                     payload[10], payload[11], payload[12], payload[13], payload[14], payload[15]);

            String macString = String(macAddr);

            if (seenMacs.find(macString) == seenMacs.end()) { // New MAC detected
                seenMacs.insert(macString);

                Serial.print("📡 Beacon Captured - RSSI: ");
                Serial.print(pkt->rx_ctrl.rssi);
                Serial.print(" dBm, MAC: ");
                Serial.print(macString);

                // Extract SSID length
                int ssid_length = payload[37];
                Serial.print(", SSID: ");

                if (ssid_length > 0 && ssid_length < 32) { // Valid SSID
                    for (int i = 0; i < ssid_length; i++) {
                        Serial.print((char)payload[38 + i]);
                    }
                } else {
                    Serial.print("(Hidden)");
                }

                Serial.println();
            }
        }
    }
}

// Start Wi-Fi Sniffing
void startSniffing() {
    seenMacs.clear();  // Clear old data before sniffing session
    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&packetSniffer);
    Serial.println("🔍 Sniffing Started...");
}

// Stop Wi-Fi Sniffing
void stopSniffing() {
    esp_wifi_set_promiscuous(false);
    Serial.println("🛑 Sniffing Stopped.");
}
