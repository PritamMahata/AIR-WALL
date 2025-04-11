---
sidebar_position: 7
---

# 🛡️ Device Safety & Handling

Proper care of your AIR-WALL hardware ensures long-term reliability.

## ⚡ Power & Ratings

| Component      | Recommended Voltage | Notes                        |
|----------------|---------------------|------------------------------|
| ESP32          | 5V                  | Power via USB or adapter     |
| OLED Display   | 3.3V / 5V           | Compatible with ESP32        |
| SD Card Module | 5V                  | Ensure proper wiring         |

> ❗ *Always double-check wiring before powering on.*

## 💾 SD Card Handling Tips

- Use a **formatted FAT32** SD card.
- Keep the SD card size below **32GB** for compatibility.
- Insert/remove card only when the device is **powered off**.

## 🔌 General Handling Tips

- Avoid touching ESP32 pins during operation.
- Do not expose the board to water/moisture.
- Secure connections using a breadboard or soldering for final builds.
