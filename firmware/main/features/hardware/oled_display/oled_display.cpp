#include "oled_display.h"

// Data log buffer
String logEntries[20];    // Circular buffer for log entries (adjust size as needed)
int logIndex = 0;         // Circular buffer index
int visibleLogOffset = 0; // Index to manage scrolling of logs
int currentScreen = NULL;
int screenCount = 3;
int cleanCount = 0;

// Initialize OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      ;
  }
}

void clearScreen(int setClean)
{
  if (cleanCount == 0 && setClean == 1)
  {
    display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 21, SSD1306_BLACK);
    cleanCount++;
  }
  else if (cleanCount != 0 || setClean != 1)
  {
    display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 21, SSD1306_BLACK);
  }
}

void showSplashScreen()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 25);
  display.println("AIR WALL");
  display.display();
}

void displayYellowText()
{
  // Display "AIR WALL" in the yellow portion (top)
  display.fillRect(0, 0, SCREEN_WIDTH, 16, SSD1306_BLACK); // Clear yellow section
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 0);
  display.println("AIR WALL");
  display.display();
}

void displayScreenIndicator()
{
  cleanCount = 0;
  // Clear the bottom section for the indicator
  display.fillRect(0, SCREEN_HEIGHT - 4, SCREEN_WIDTH, 4, SSD1306_BLACK);

  // Draw three circles at the bottom center for screen indicators
  int baseX = 53;            // Center of the screen horizontally
  int y = SCREEN_HEIGHT - 3; // Vertical position for the indicators
  int spacing = 10;          // Space between circles

  for (int i = 1; i <= screenCount; i++)
  {
    if (i == currentScreen)
    {
      // Active screen: draw a filled circle
      display.fillCircle(baseX + (i * spacing), y, 2, SSD1306_WHITE);
    }
    else
    {
      // Inactive screens: draw an unfilled circle
      display.drawCircle(baseX + (i * spacing), y, 2, SSD1306_WHITE);
    }
  }
  display.display();
}

void displayScreen1()
{
  cleanCount = 0;
  displayYellowText(); // Always show "AIR WALL" in the yellow portion
  static unsigned long lastLogUpdate = 0;
  if (millis() - lastLogUpdate >= 50)
  { // Update logs every 1000ms
    lastLogUpdate = millis();
    // Show WiFi status in the blue portion
    display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 26, SSD1306_BLACK); // Clear blue section
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 18);

    if (WiFi.status() == WL_CONNECTED)
    {
      // Show IP address
      // display.println("WiFi Connected");
      display.print("IP:");
      display.println(WiFi.localIP());
      display.print("MAC:");
      display.println(WiFi.macAddress());
      display.print("SSID:");
      display.print(WiFi.SSID());
    }
    else
    {
      // Show connecting animation
      static int dotCount = 0;
      display.println("Connecting to WiFi");
      for (int i = 0; i < dotCount; i++)
      {
        display.print(".");
      }
      dotCount = (dotCount + 1) % 4; // Cycle between 0-3 dots
    }
    display.display();
  }
  // Show screen indicator
  displayScreenIndicator();
}

void displayScreen2()
{
  static unsigned long lastLogUpdate = 0;
  if (millis() - lastLogUpdate >= 1000)
  { // Update logs every 1000ms
    lastLogUpdate = millis();

    displayYellowText(); // Always show "AIR WALL" in the yellow portion
    clearScreen(2);      // Clear specific portions of the screen

    // Display the heading
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(1, 16);
    display.println("LOG:");

    // Scroll the logs in the visible log area
    int yPosition = LOG_BOX_Y + 2; // Start drawing a few pixels below the top of the box
    for (int i = 0; i < 4; i++)
    { // Display a maximum of 5 lines in the log box
      int index = (logIndex + i) % 20;
      display.setCursor(LOG_BOX_X + 2, yPosition + i * LINE_SPACING);
      display.print(logEntries[index]);
    }

    display.display();        // Commit changes to the display
    displayScreenIndicator(); // Show screen indicator
  }
}

void displayScreen3()
{
  displayYellowText(); // Always show "AIR WALL" in the yellow portion
  clearScreen(2);
  // Show content for Screen 2
  display.fillRect(0, 16, SCREEN_WIDTH, SCREEN_HEIGHT - 26, SSD1306_BLACK); // Clear blue section
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 18);
  display.println("Screen 2");
  display.println("This is the thrid screen.");
  display.display();

  // Show screen indicator
  displayScreenIndicator();
}