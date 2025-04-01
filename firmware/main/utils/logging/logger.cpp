#include "logger.h"

#define LOG_FILE "/log.txt"

void logMessage(const String &message) {
    Serial.println(message);
    
    File logFile = SD.open(LOG_FILE, FILE_APPEND);
    if (logFile) {
        logFile.println(message);
        logFile.close();
    }
}
