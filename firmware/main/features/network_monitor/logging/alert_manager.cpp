#include "alert_manager.h"
#include "oled_display.h" // Assuming you have this class already initialized

extern OLED_Display oled; // Assuming this object is globally accessible or passed

namespace AlertManager {
    void raiseError(const String& source, const String& message) {
        Serial.println("🛑 Error from " + source + ": " + message);
        oled.displayError("[ERR] " + source + ": " + message);
    }

    void raiseWarning(const String& source, const String& message) {
        Serial.println("⚠️ Warning from " + source + ": " + message);
        oled.displayError("[WARN] " + source + ": " + message); // Optional: create displayWarning()
    }

    void clearAlert() {
        oled.clear(); // Optionally clear screen when things recover
    }
}
