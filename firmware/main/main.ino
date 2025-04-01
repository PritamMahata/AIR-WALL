#include "main.h"
// // void setup() {
// //     Serial.begin(115200);
// //     delay(1000);
// //     logMessage("[BOOT] System Starting...");
// //     connectWiFi();
// // }
// // void loop() {
// // }

// const char* ssid = "hotspot";
// const char* password = "@pritam123";

// void setup() {
//     // Serial.begin(115200);
//     // WiFi.begin(ssid, password);

//     // Serial.println("Connecting to WiFi...");
//     // while (WiFi.status() != WL_CONNECTED) {
//     //     delay(500);
//     //     Serial.print(".");
//     // }
//     // Serial.println("\nConnected to WiFi!");

//     // // Initialize and run port scanner
//     // initPortScanner("192.168.64.121");  // Ensure IP is passed as const char*
//     // scanPorts(20, 100);

//     // std::vector<int> openPorts = getOpenPorts();
//     // if (!openPorts.empty()) {
//     //     Serial.println("Open Ports Found:");
//     //     for (int port : openPorts) {
//     //         Serial.print("✅ Port ");
//     //         Serial.print(port);
//     //         Serial.println(" is open");
//     //     }
//     // } else {
//     //     Serial.println("No open ports found.");
//     // }
//     Serial.begin(115200);
//     delay(1000);
    
//     // Start Deauth Detector
//     initDeauthDetector();
// }

// void loop() {
//     Serial.print("🔍 Detected Attacks: ");
//     Serial.println(getDeauthCount());

//     delay(500);  // Adjust the delay as needed
// }


OLED_Display oled;

void setup() {
    Serial.begin(115200);
    oled.init();
    oled.showSplashScreen();
}

void loop() {
    static int screen = 1;
    oled.displayScreen(screen);

    if (Serial.available()) {
        char input = Serial.read();
        if (input == '1') screen = 1;
        else if (input == '2') screen = 2;
        else if (input == '3') screen = 3;
    }

    delay(1000);
}