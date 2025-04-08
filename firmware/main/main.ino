#include "main.h"

OLED_Display display;
Logger logger;
SDHandler sd(display);
WiFiHandler wifi(sd, logger);

void setup()
{
    Serial.begin(115200);
    display.init();
    display.showSplashScreen();
    display.currentScreen = currentScreen;

    // Configure switch pins with internal pull-up resistors
    pinMode(switch1Pin, INPUT_PULLUP);
    pinMode(switch2Pin, INPUT_PULLUP);

    wifi.connect();
    startServer(); // server started
    logger.add("System startup...");
}

void loop()
{
    display.displayScreen(currentScreen);
    handleSwitchInput();
    broadcastEncrypted("{\"temp\":28.5,\"alert\":false}");
}

void handleSwitchInput()
{
    bool switch1State = digitalRead(switch1Pin);
    bool switch2State = digitalRead(switch2Pin);

    if (switch1State == LOW && (millis() - lastDebounceTime1 > debounceDelay))
    {
        currentScreen++;
        if (currentScreen > display.screenCount)
        {
            currentScreen = 1;
        }
        lastDebounceTime1 = millis();
        Serial.println("Switch 1 pressed."); // testing
        Serial.println(currentScreen);       // testing
    }

    if (switch2State == LOW && (millis() - lastDebounceTime2 > debounceDelay))
    {
        lastDebounceTime2 = millis();
        Serial.println("Switch 2 pressed."); // testing
    }
}



    