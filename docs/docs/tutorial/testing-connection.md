---
sidebar_position: 4
---

# 🧪 Testing the Connection

After powering up your AIR-WALL device and inserting the SD card with `config.json`, follow the steps below to ensure it's connected properly:

## ✅ Verifying Wi-Fi Connection

- Once powered, the OLED display should show:
  - 📡 **Connected WiFi Name**
  - 🌐 **Device IP Address**
- If you see an IP address, your device is connected successfully.

## 🔍 Troubleshooting: No IP on OLED?

- ❌ Check if `config.json` exists and is correctly formatted.
- ❌ Ensure SD card is inserted properly.
- 🔌 Confirm your ESP32 is powered.
- 💾 Try reformatting the SD card and re-uploading the JSON.

## 🌐 Ping Test via Browser

1. Open your browser.
2. Type in the IP shown on the OLED (e.g., `http://192.168.1.100`).
3. You should see the AIR-WALL dashboard.
4. If not:
   - Check if your PC/phone is connected to the same network.
   - Try pinging the IP using terminal/command prompt.
