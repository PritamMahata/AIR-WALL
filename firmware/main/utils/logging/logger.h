#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
class Logger
{
public:
    Logger(const String &logFile = "/log.txt");
    void begin();                    // Optional: to ensure SD is ready
    void add(const String &message); // Add a log message
    String getLogs();                // Add this line
private:
    String logFilePath;
};

#endif
