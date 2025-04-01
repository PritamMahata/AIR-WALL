#include "deauth_detector.h"
#include <esp_wifi.h>

volatile int deauthCount = 0;

// Callback function to process incoming packets
void promiscuous_rx(void *buf, wifi_promiscuous_pkt_type_t type)
{
    Serial.println("inside callback function1");
    if (type != WIFI_PKT_MGMT)
        return;

    const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
    const uint8_t *payload = pkt->payload;

    // Check if it's a Deauthentication (0xC0) or Disassociation (0xA0) frame
    if (payload[0] == 0xC0 || payload[0] == 0xA0)
    {
        deauthCount++;
        Serial.println("[ALERT] Deauthentication/Disassociation Attack Detected!");
    }
}

// Initialize the Deauth Detector
void initDeauthDetector()
{
    Serial.println("[INFO] Initializing Deauth Detector...");

    // Set Wi-Fi to monitor mode
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_mode(WIFI_MODE_NULL);
    esp_wifi_start();
    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx);

    Serial.println("[OK] Deauth Detector Initialized.");
}

// Get the current number of detected attacks
int getDeauthCount()
{
    return deauthCount;
}
