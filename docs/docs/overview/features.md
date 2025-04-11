---
sidebar_position: 0
---

# ✨ Detailed Feature List

## 1. Deauthentication Attack Detection
- Continuously scans for deauth frames over the air.
- Alerts and logs suspicious activities in real time.

## 2. Protected Management Frames (PMF)
- Enforces PMF to mitigate deauth and spoof attacks.
- Supported on modern routers with WPA2/WPA3.

## 3. Automatic Reconnection
- Automatically reconnects ESP32 and nearby clients during a deauth attack.

## 4. Jam Detection
- Detects abnormal channel noise and packet drops.
- Triggers protective actions like channel hopping or sleep.

## 5. Web Dashboard
- Real-time display of logs, attack info, and control commands.
- Accessible via IP on the same network.

## 6. Command Control
- Restart, Sleep Mode, Toggle Detection, and Status Check from dashboard.

## 7. MAC Logging
- Monitors connected MACs and stores them for verification.
- Blacklists known attacker devices.

## 8. SD Card Logging (Optional)
- Stores logs persistently for offline inspection and audits.
