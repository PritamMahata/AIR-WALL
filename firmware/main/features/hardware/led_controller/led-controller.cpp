#include "data_processor.h"

unsigned long previousMillis = 0;  // Stores the last time the LED pattern was updated
int ledState = LOW;                // Current state of the LED
int patternStep = 0;               // Step in the LED pattern
const long interval = 100;         // Interval between pattern steps (100 milliseconds)

void ledPattern(int pid) {
  unsigned long currentMillis = millis();  // Get the current time

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the LED was updated
    previousMillis = currentMillis;

    // Pattern 1: Blink
    if (pid == 1) {
      ledState = (ledState == LOW) ? HIGH : LOW;  // Toggle LED state
      digitalWrite(2, ledState);                  // Update LED state
    }
    // Pattern 2: Breathing effect
    else if (pid == 2) {
      if (patternStep <= 255) {
        analogWrite(2, patternStep);  // Fade in (0 to 255)
        patternStep++;
      } else if (patternStep <= 510) {
        analogWrite(2, 510 - patternStep);  // Fade out (255 to 0)
        patternStep++;
      }
      if (patternStep > 510) {
        patternStep = 0;  // Reset pattern step
      }
    }
    // Pattern 3: Chasing effect (3 steps)
    else if (pid == 3) {
      if (patternStep == 0) {
        digitalWrite(2, HIGH);  // LED ON
      } else if (patternStep == 1) {
        digitalWrite(2, LOW);  // LED OFF
      } else if (patternStep == 2) {
        digitalWrite(2, HIGH);  // LED ON
      }
      patternStep = (patternStep + 1) % 3;  // Loop over 3 steps
    }
  }
}

void boot_led_pattern(){
  
}

