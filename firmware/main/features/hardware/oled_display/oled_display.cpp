#include "oled_display.h"

OLED_Display::OLED_Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void OLED_Display::init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
        while (true)
            ;
    }
    Serial.println("SSD1306 allocation successfull");
    display.clearDisplay();
    display.display();
}

void OLED_Display::clearScreen(int setClean)
{
    if (cleanCount == 0 && setClean == 1)
    {
        display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 21, SSD1306_BLACK);
        cleanCount++;
    }
    else
        display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 21, SSD1306_BLACK);
}

void OLED_Display::showSplashScreen()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 25);
    display.println("AIR WALL");
    display.display();
    delay(1000);
    display.clearDisplay();
}

void OLED_Display::displayYellowText()
{
    display.fillRect(0, 0, SCREEN_WIDTH, 16, SSD1306_BLACK);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 0);
    display.println("AIR WALL");
    display.display();
}

void OLED_Display::displayScreenIndicator()
{
    cleanCount = 0;
    display.fillRect(0, SCREEN_HEIGHT - 4, SCREEN_WIDTH, 4, SSD1306_BLACK);
    int baseX = 53;
    int y = SCREEN_HEIGHT - 3;
    int spacing = 10;

    for (int i = 1; i <= screenCount; i++)
    {
        if (i == currentScreen)
            display.fillCircle(baseX + (i * spacing), y, 2, SSD1306_WHITE);
        else
            display.drawCircle(baseX + (i * spacing), y, 2, SSD1306_WHITE);
    }
    display.display();
}

void OLED_Display::displayScreen(int screen)
{
    currentScreen = screen;
    displayYellowText();
    clearScreen(1);

    if (screen == 1)
    {
        display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 26, SSD1306_BLACK);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 18);

        if (WiFi.status() == WL_CONNECTED)
        {
            display.print("IP: ");
            display.println(WiFi.localIP());
            display.print("SSID: ");
            display.println(WiFi.SSID());
            display.println("Mode: " + currentMode);
        }
        else
        {
            display.println("Connecting...");
        }
    }
    else if (screen == 2)
    {
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(1, 16);
        display.println("LOG:");
        displayLogs();
    }
    else if (screen == 3)
    {
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 18);
        display.println("Screen 3");
        display.println("This is the third screen.");
    }
    display.display();
    displayScreenIndicator();
}

void OLED_Display::displayLogs()
{
    int yPosition = 20;
    for (int i = 0; i < 4; i++)
    {
        int index = (logIndex + i) % 20;
        display.setCursor(2, yPosition + i * 10);
        display.print(logEntries[index]);
    }
    display.display();
}

void OLED_Display::displayText(String text, int x, int y)
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(text);
    display.display();
}

void OLED_Display::drawGraph(int rssiValues[], int count)
{
    display.clearDisplay();
    display.drawLine(0, 32, 128, 32, SSD1306_WHITE);
    for (int i = 0; i < count - 1; i++)
    {
        int x1 = i * (SCREEN_WIDTH / count);
        int y1 = map(rssiValues[i], -100, -30, SCREEN_HEIGHT, 0);
        int x2 = (i + 1) * (SCREEN_WIDTH / count);
        int y2 = map(rssiValues[i + 1], -100, -30, SCREEN_HEIGHT, 0);
        display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
    }
    display.display();
}

void OLED_Display::addLog(String log)
{
    logEntries[logIndex] = log;
    logIndex = (logIndex + 1) % 20;
}

void OLED_Display::displayError(const String &error)
{
    clearScreen(1);
    displayYellowText();

    display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 26, SSD1306_BLACK);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 18);

    display.print("System Alert:");
    display.println(error);

    display.display();
    displayScreenIndicator();
}

void OLED_Display::displayMode(const String &mode)
{
    setMode(mode); // ensure the internal mode is updated
    clearScreen(1);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5, 10);
    display.println("Mode: " + currentMode); // now it works
    display.display();
}

void OLED_Display::setMode(const String &mode) { currentMode = mode; }