#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.h"


// #define LOG_BOX_X 5
// #define LOG_BOX_Y 24
// #define LOG_BOX_WIDTH 115
// #define LOG_BOX_HEIGHT 35
// #define LINE_SPACING 8  // Space between log lines

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64
// #define OLED_RESET -1
// // Initialize OLED display
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//   Serial.println(F("SSD1306 allocation failed"));
//   while (true);
// }

// void clearScreen(int setClean) {
//   if (cleanCount == 0 && setClean == 1) {
//     display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 21, SSD1306_BLACK);
//     cleanCount++;
//   } else if (cleanCount != 0 || setClean != 1) {
//     display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 21, SSD1306_BLACK);
//   }
// }

// void showSplashScreen() {
//   display.clearDisplay();
//   display.setTextSize(2);
//   display.setTextColor(SSD1306_WHITE);
//   display.setCursor(20, 25);
//   display.println("AIR WALL");
//   display.display();
// }
void showSplashScreen() {
  Serial.println("Hello from greetings.cpp!");
}