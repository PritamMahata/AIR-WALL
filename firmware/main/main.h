#ifndef MAIN_H
#define MAIN_H

// all necessary header files
// #include <Wire.h>
#include <WiFi.h>
#include <Arduino.h>

// #include <WebServer.h>
// #include <WebSocketsServer.h>
// #include <esp_system.h>
// #include <esp_spi_flash.h>
// #include <ArduinoJson.h>
#include "esp_wifi.h"
#include "esp_heap_caps.h"



// Include all the header files in the project

#include "features/hardware/oled_display/oled_display.h"
#include "features/hardware/oled_display/oled_display.cpp"

// #include "features/connectivity/wifi_handler.h"
// #include "features/connectivity/wifi_handler.cpp"

// #include "storage/sd_handler.h"
// #include "storage/sd_handler.cpp"

// #include "utils/logging/logger.h"
// #include "utils/logging/logger.cpp"

// #include "features/network_monitor/port_scanner/port_scanner.cpp"
// #include "features/network_monitor/port_scanner/port_scanner.h"

// #include "features/security/deauth_detector/deauth_detector.cpp"
// #include "features/security/deauth_detector/deauth_detector.h"

#include "features/security/network_sniffer/network_sniffer.cpp"
#include "features/security/network_sniffer/network_sniffer.h"




// #include "features/networktraffic/networktraffic.h"
// #include "features/networktraffic/networktraffic.cpp"

// #include "C:/Users/prita/Desktop/AIR-WALL/backend/server/api_handler.h"
// #include "C:/Users/prita/Desktop/AIR-WALL/backend/server/server.h"

// // Password settings
// extern const int passwordLength;
// extern const String charset;

// // Pin assignments
// extern const int switch1Pin;
// extern const int switch2Pin;
// extern const int ledPin;

// // State variables
// extern int currentScreen;
// extern int cleanCount;
// extern int logIndex;
// extern int visibleLogOffset;
// extern int deauthTrying;

// // Data log buffer
// extern String logEntries[20];

// // LED states
// extern bool led1State;
// extern bool led2State;

// // Debounce variables
// extern unsigned long lastDebounceTime1;
// extern unsigned long lastDebounceTime2;
// extern const unsigned long debounceDelay;

// // OLED display object
// extern Adafruit_SSD1306 display;

// // Web server and WebSocket objects
// extern WebServer server;
// extern WebSocketsServer webSocket;

#endif
