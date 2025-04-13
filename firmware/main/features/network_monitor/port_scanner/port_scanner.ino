#include <WiFi.h>
#include "port_scanner.h"

const char* ssid = "hotspot";
const char* password = "@pritam123";

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected. IP: " + WiFi.localIP().toString());

  // 🔍 Test port scanner
  const char* targetIP = "192.168.43.61";  // 🔁 Replace with a local device's IP
  initPortScanner(targetIP);
  scanPorts(70, 100);

  // 🧾 Print Results
  std::vector<int> open = getOpenPorts();
  Serial.println("---- Open Ports ----");
  for (int port : open) {
    Serial.println("✅ Port: " + String(port));
  }
}

void loop() {
  // nothing here
}
