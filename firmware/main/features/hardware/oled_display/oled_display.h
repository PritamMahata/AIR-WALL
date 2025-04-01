#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LOG_BOX_X 5
#define LOG_BOX_Y 24
#define LOG_BOX_WIDTH 115
#define LOG_BOX_HEIGHT 35
#define LINE_SPACING 8 // Space between log lines

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// #define Adafruit_SSD1306 display;

void initDisplay();
void clearScreen(int setClean);
void showSplashScreen();
void displayYellowText();
void displayScreen1();
void displayScreen2();
void displayScreen3();
#endif