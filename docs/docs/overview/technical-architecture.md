---
sidebar_position: 3
---


# 🧠 Technical Architecture
> A comprehensive overview of how the Anti-Deauthentication CyberSec-IoT Toolkit works behind the scenes using ESP32.

---

## ⚙️ 1. System Components

| Component         | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| **ESP32**         | Core microcontroller with Wi-Fi sniffing and web server capabilities.      |
| **Wi-Fi Interface** | Captures real-time packets to identify deauthentication and jamming.      |
| **Web Dashboard** | A local HTML+JS interface for user control and log visualization.          |
| **Packet Sniffer**| Detects anomalies in Wi-Fi traffic like deauth frames or jamming signals.  |
| **Logging System**| Stores detected attacks in memory or SD card for later inspection.         |
| **Optional Modules** | RTC (time tracking), GPS (location), SD Card (persistent storage).       |

---

## 🔄 2. System Workflow

```mermaid
flowchart TD
    A[Wi-Fi Network Environment] --> B[ESP32 Packet Interceptor]
    B --> C{Detects Deauth / PMF / Jam}
    C -->|Yes| D[Log Event to Memory / SD Card]
    C -->|Yes| E[Send JSON to Web Dashboard]
    C -->|Yes| F[Trigger Auto Countermeasures]
    E --> G[HTML/JS Dashboard View]
    G --> H[User Interacts: Restart / Sleep / View Logs]
    H --> I[Send Commands to ESP32 Server]
