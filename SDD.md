## 1. 📘 System Overview

**Project Name**: Forge32  
**Purpose**:  
Forge32 is a modular IoT framework built on a network of ESP32 microcontrollers. It enables real-time monitoring and control of distributed sensors and output devices through a dynamically generated web dashboard, hosted on a central ESP32 hub.

**Key Features**:

- Custom TCP protocol for efficient node-hub communication
- Dynamic dashboard generation based on registered capabilities
- Historical data queries and real-time output control
- Event broadcasting from nodes to hub
- Rolling buffer strategy for local data storage

**Target Users**:  
Engineers, technicians, and hobbyists seeking a scalable, low-cost IoT control and monitoring platform.

---

## 2. 🏗️ Architecture Design

### High-Level Architecture

```
+-----------------+       Wi-Fi       +-------------------+       SPI/I2C       +------------------+
|  Sensor Node(s) | <---------------> |   Hub ESP32 Unit  | <-----------------> |  Sensors/Outputs |
| (ESP32 Devices) |   (Custom TCP)    | (Web Server + Hub)|                     | (Local Devices)  |
+-----------------+                   +-------------------+                     +------------------+
                                              |
                                              | Serves HTTP
                                              v
                                      +-------------------+
                                      |  User Web Browser |
                                      | (Dashboard Access)|
                                      +-------------------+
```

### Core Components

- **Hub ESP32**:
    - Hosts the web dashboard (HTML/CSS/JS)
    - Communicates with nodes via [Forge32 TCP Protocol](/TCP%20Protocol.md)
    - Performs minimal data processing
    - Handles real-time output control and event reception
    
- **Sensor/Output Nodes**:
    - Register with the hub on boot
    - Declare capabilities and supported events
    - Handles the majority of data processing to reduce hub bottle necks.
    - Store historical data in a rolling buffer
    - Broadcast events and respond to queries
    
- **Web Dashboard**:
    - Served from the hub
    - Dynamically generated based on registered nodes
    - Displays sensor data and provides output controls

---

## 3. 🧰 Technology Stack

|Layer              |Stack / Tool                       |
|-------------------|-----------------------------------|
|Micro-Controller   |ESP32 (Hub + Nodes)                |
|Language           |C++ (Arduino Framework)            |
|Communication      |Custom TCP Protocol over Wi-Fi     |
|Dashboard          |HTML/CSS/JS served via HTTP        |
|JSON Parsing       |ArduinoJson (StaticJsonDocument)   |
|File Storage       |LittleFS                           |
|IDE                |PlatformIO (recommended)           |

---

## 4. 🗂️ File Structure

### Hub ESP32

```
forge32-hub/
├── src/
│   └── main.cpp
├── data/
│   ├── index.html
│   ├── style.css
│   └── script.js   
├── include/
|   ├── tcp_server.cpp
│   ├── dashboard_server.cpp
│   ├── node_registry.cpp
│   └── protocol.h
└── platformio.ini
```

### Node ESP32

```
forge32-node/
├── src/
│   ├── main.cpp
│   ├── tcp_client.cpp
│   ├── sensor_manager.cpp
│   ├── output_controller.cpp
│   ├── event_trigger.cpp
│   └── register_message.cpp
├── include/
│   └── protocol.h
└── platformio.ini
```

---

## 5. 📈 Scalability & Extensibility

- Nodes register automatically on boot.
- Dashboard generation is modular and reflects new capabilities.
- Rolling buffer strategy ensures efficient memory use on nodes.
- Protocol is extensible for future features (e.g., OTA, cloud sync, auth).