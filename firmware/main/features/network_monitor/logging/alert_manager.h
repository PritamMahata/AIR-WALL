#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <Arduino.h>

class AlertManager {
public:
    static void sendAlert(const String& mac);
};

#endif
