#include "ssid_analyzer.h"
#include <WiFi.h>
#include "../../security/firewall_manager/firewall_controller.h"  // If prevent() is defined here

void checkDuplicateSSIDs() {
  WiFi.disconnect();
  int n = WiFi.scanNetworks();  // Scan for available networks
  Serial.println("Scan complete.");

  if (n == 0) {
    Serial.println("No networks found");
    return;
  }

  Serial.print(n);
  Serial.println(" networks found.");

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (WiFi.SSID(i) == WiFi.SSID(j)) {
        Serial.print("Duplicate SSID detected: ");
        Serial.println(WiFi.SSID(i));

        if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN || WiFi.encryptionType(j) == WIFI_AUTH_OPEN) {
          Serial.print("Open network detected for SSID: ");
          Serial.println(WiFi.SSID(i));
        }
      }
    }
  }

  WiFi.scanDelete();  // Free memory
}
