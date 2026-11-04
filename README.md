# Edge AI to Cloud: Smart Occupancy Tracker Pipeline

A commercial-grade end-to-end IoT pipeline that bridges edge hardware with a real-time web dashboard. This system is designed to handle local sensor data acquisition, manage hardware power constraints during Wi-Fi transmission, and push low-latency telemetry to a Firebase Realtime Database.

## System Architecture

```mermaid
graph TD
    A[ESP32-CAM Edge Node] -->|Captures/Processes Data| B(Power-Optimized Wi-Fi Tx)
    B -->|HTTP PUT json| C[(Firebase Realtime Database)]
    C -->|Live Sync| D[Web Dashboard HTML/JS]
    D -->|Real-time UI| E((End User))
