#ifndef MAIN_H
#define MAIN_H

// all necessary header files
#include <Wire.h>
#include <WiFi.h>
#include <Arduino.h>

#include <WebServer.h>
#include <WebSocketsServer.h>
#include <esp_system.h>
#include <esp_spi_flash.h>
#include <ArduinoJson.h>
#include "esp_wifi.h"
#include "esp_heap_caps.h"

// Define switch pins (update according to your wiring)
const int switch1Pin = 12;
const int switch2Pin = 13;
const int LED_RED_PIN = 14;
const int LED_GREEN_PIN = 27;
const int LED_BLUE_PIN = 26;
const int BUZZER_PIN = 25;

// Debounce settings
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
const unsigned long debounceDelay = 200;

// Current screen variable
int currentScreen = 1;

const int deauthThreshold = 20; // Threshold for deauth detection

// Include all the header files in the project



#include "features/hardware/oled_display/oled_display.h"
#include "features/hardware/oled_display/oled_display.cpp"
extern OLED_Display display;  // declared in main.h or oled_display.h

#include "features/connectivity/wifi_handler.h"
#include "features/connectivity/wifi_handler.cpp"

#include "storage/sd_handler.h"
#include "storage/sd_handler.cpp"

#include "utils/logging/logger.h"
#include "utils/logging/logger.cpp"

#include "features/network_monitor/port_scanner/port_scanner.cpp"
#include "features/network_monitor/port_scanner/port_scanner.h"

#include "features/security/deauth_detector/deauth_detector.cpp"
#include "features/security/deauth_detector/deauth_detector.h"

#include "features/security/network_sniffer/network_sniffer.cpp"
#include "features/security/network_sniffer/network_sniffer.h"

#include "server/api/api_handler.h"
#include "server/api/api_handler.cpp"

#include "server/core/server.h"
#include "server/core/server.cpp"

#include "server/encryptor.h"
#include "server/encryptor.cpp"
//done


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

// // Web server and WebSocket objects
// extern WebServer server;
// extern WebSocketsServer webSocket;

#endif
