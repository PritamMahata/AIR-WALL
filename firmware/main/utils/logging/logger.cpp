#include "logger.h"

Logger::Logger(const String &logFile) : logFilePath(logFile) {}

void Logger::begin()
{ // You can optionally add SD card check here if needed
    if (!SD.begin())
    {
        Serial.println("[ERROR] SD initialization failed in Logger.");
    }
}

void Logger::add(const String &message)
{
    Serial.println(message);

    File logFile = SD.open(logFilePath.c_str(), FILE_APPEND);
    if (logFile)
    {
        logFile.println(message);
        logFile.close();
    }
    else
    {
        Serial.println("[ERROR] Failed to open log file.");
    }
}

String Logger::getLogs()
{
    String logData;
    File logFile = SD.open(logFilePath.c_str(), FILE_READ);
    if (logFile)
    {
        while (logFile.available())
        {
            logData += (char)logFile.read();
        }
        logFile.close();
    }
    else
    {
        Serial.println("[ERROR] Failed to open log file for reading.");
    }
    return logData;
}