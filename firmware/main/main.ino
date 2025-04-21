#include "main.h"

OLED_Display display;
Logger logger;
SDHandler sd(display);
WiFiHandler wifi(sd, logger);
String currentMode;
bool buzzerState = false;
bool isBusy = false;
void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
    digitalWrite(LED_RED_PIN, LOW);   // default OFF
    digitalWrite(LED_GREEN_PIN, LOW); // default OFF
    digitalWrite(LED_BLUE_PIN, LOW);  // default OFF
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
    display.displayScreen(1); // Display the first screen
    // display.displayMode(currentMode);
}

void loop()
{
    Serial.println("Current mode: " + currentMode);             // testing
    Serial.println("Current screen: " + String(currentScreen)); // testing
    if (currentMode == "active")
    {
        initDeauthDetector();
        currentScreen = 2; // Set to the first screen for active mode
    }

    else if (currentMode == "passive")
    {
        startPassiveFeatures();
    }
    else if (currentMode == "smart")
    {
    }
    // checkDuplicateSSIDs(); // Call the analyzer
    display.displayScreen(currentScreen);
    handleSwitchInput();

    digitalWrite(LED_GREEN_PIN, HIGH);
    Serial.println("Deauth count: " + String(getDeauthCount())); // testing
    if (currentMode == "active" && getDeauthCount() > deauthThreshold)
    {
        if (!buzzerState)
        {
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(LED_RED_PIN, HIGH);
            digitalWrite(LED_GREEN_PIN, LOW);
            buzzerState = true;
        }
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_RED_PIN, LOW);
        buzzerState = false;
    }

    // Other processes here (e.g., WebSocket handling, monitoring, etc.)
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
        {
            currentMode = "active";
            sd.writeMode(currentMode);
            esp_restart();
        }
        sd.writeMode(currentMode);
        display.setMode(currentMode);
        // display.displayMode(currentMode);
        Serial.println("Mode changed to: " + currentMode);
    }
}

void startPassiveFeatures()
{
    static bool scanned = false;

    unsigned long lastSentTime = 0;
    const unsigned long sendInterval = 1000; // 1 second
    unsigned long currentMillis = millis();

    // Non-blocking send
    if (currentMillis - lastSentTime >= sendInterval)
    {
        lastSentTime = currentMillis;
        Serial.println("Sending data to web clients..."); // testing
        sendSerialToWebClients();
    }

    //this is port scanner code
    // if (!scanned)
    // {
    //     display.addLog("Starting port scan..."); // Log port scan start
    //     initPortScanner("192.168.94.121");       // Replace with your target IP
    //     scanned = true;
    // }

    // // Use non-blocking scan for risky ports
    // scanRiskyPorts(); // Scan the specified risky ports
    Serial.println("Passive mode running......");
}

void getSystemInfo()
{
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    chipInfo = "<p>Chip Model: <strong>" + String(ESP.getChipModel()) + "</strong></p>";
    chipInfo += "<p>Chip Revision: <strong>" + String(ESP.getChipRevision()) + "</strong></p>";
    chipInfo += "<p>Number of Cores: <strong>" + String(chip_info.cores) + "</strong></p>";
    chipInfo += "<p>CPU Frequency: <strong>" + String(ESP.getCpuFreqMHz()) + " MHz</strong></p>";
    chipInfo += "<p>Flash Size: <strong>" + String(spi_flash_get_chip_size() / (1024 * 1024)) + " MB</strong></p>";

    freeHeap = esp_get_free_heap_size();
    minFreeHeap = esp_get_minimum_free_heap_size();
    totalHeap = heap_caps_get_total_size(MALLOC_CAP_8BIT);

    netInfo = "<p>IP Address: <strong>" + WiFi.localIP().toString() + "</strong></p>";
    netInfo += "<p>MAC Address: <strong>" + WiFi.macAddress() + "</strong></p>";
    netInfo += "<p>SSID: <strong>" + WiFi.SSID() + "</strong></p>";

    signalStrength = WiFi.RSSI();

    runtimeInfo = millis() / 1000;
}

void sendSerialToWebClients()
{
    getSystemInfo();

    DynamicJsonDocument doc(256);
    doc["uptime"] = millis() / 1000;
    doc["mode"] = currentMode;
    doc["chipInfo"] = chipInfo;
    doc["freeHeap"] = freeHeap;
    doc["minFreeHeap"] = minFreeHeap;
    doc["totalHeap"] = totalHeap;
    doc["signalStrength"] = signalStrength;
    doc["netInfo"] = netInfo;
    doc["runtimeInfo"] = runtimeInfo;

    broadcastJson(doc);
    Serial.println("Data send done");
    // Clear buffer after sending
    chipInfo = "";
    netInfo = "";
    runtimeInfo = 0;
    signalStrength = 0;
}