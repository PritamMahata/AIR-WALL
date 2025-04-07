#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include <Arduino.h>

namespace AlertManager {
    void raiseError(const String& source, const String& message);
    void raiseWarning(const String& source, const String& message);
    void clearAlert(); // optional
}

#endif
