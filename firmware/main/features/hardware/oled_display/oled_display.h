#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class OLED_Display
{
private:
    String currentMode = "passive";
    Adafruit_SSD1306 display;
    String logEntries[20]; // Circular buffer for log entries
    int logIndex = 0;
    int visibleLogOffset = 0;
    int cleanCount = 0;

    void clearScreen(int setClean);
    void displayYellowText();
    void displayScreenIndicator();
    void displayLogs();

public:
    int currentScreen;
    int screenCount = 3;
    OLED_Display();
    void init();
    void showSplashScreen();
    void displayScreen(int screen);
    void displayText(String text, int x, int y);
    void drawGraph(int rssiValues[], int count);
    void addLog(String log);
    void displayError(const String &error);
    void displayMode(const String &mode);
    void setMode(const String &mode); 
};

#endif
