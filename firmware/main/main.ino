#include "main.h"

OLED_Display display;
Logger logger;
SDHandler sd(display);
WiFiHandler wifi(sd, logger);
String currentMode;
int switchPin = 13; // GPIO pin for the mode switch
bool buzzerState = false;

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);  // Define this in main.h
    pinMode(LED_RED_PIN, OUTPUT); // Define this too
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

    sd.readMode(currentMode); // always returns a valid mode
    display.setMode(currentMode);
    display.displayMode(currentMode);
}

void loop()
{
    Serial.println("Current mode: " + currentMode);             // testing
    Serial.println("Current screen: " + String(currentScreen)); // testing
    if (currentMode == "active")
        initDeauthDetector();
    else if (currentMode == "passive")
        startPassiveFeatures();
    display.displayScreen(currentScreen);
    handleSwitchInput();
    broadcastEncrypted("{\"temp\":28.5,\"alert\":false}");

    Serial.println("Deauth count: " + String(getDeauthCount())); // testing
    if (currentMode == "active" && getDeauthCount() > deauthThreshold)
    {
        if (!buzzerState)
        {
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(LED_RED_PIN, HIGH);
            buzzerState = true;
        }
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_RED_PIN, LOW);
        buzzerState = false;
    }
}

void handleSwitchInput()
{
    bool switch1State = digitalRead(switch1Pin);
    bool switch2State = digitalRead(switch2Pin);

    if (switch1State == LOW && (millis() - lastDebounceTime1 > debounceDelay))
    {
        currentScreen++;
        if (currentScreen > display.screenCount)
            currentScreen = 1;
        lastDebounceTime1 = millis();
        Serial.println("Switch 1 pressed."); // testing
        Serial.println(currentScreen);       // testing
    }

    if (switch2State == LOW && (millis() - lastDebounceTime2 > debounceDelay))
    {
        lastDebounceTime2 = millis();
        // Cycle mode
        if (currentMode == "active")
        {
            currentMode = "passive";
            sd.writeMode(currentMode);
            esp_restart();
        }
        else if (currentMode == "passive")
            currentMode = "smart";
        else
            currentMode = "active";
        sd.writeMode(currentMode);
        display.setMode(currentMode);
        display.displayMode(currentMode);
        Serial.println("Mode changed to: " + currentMode);
    }
}

void startPassiveFeatures()
{
    // Initialize passive features here
    // initNetworkSniffer();
    // initPortScanner();
    Serial.println("Passive mode running......");
    // Add any other passive features you want to initialize
}