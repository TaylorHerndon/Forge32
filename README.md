# 🏭 Forge32

**Forge32** is a modular, scalable IoT framework built on a network of ESP32 microcontrollers. It enables real-time monitoring and control of distributed sensors and output devices through a dynamically generated web dashboard — all hosted on a central ESP32 hub.

---
## 📌 Features

- 📡 Custom TCP protocol for efficient node-hub communication
- 🌐 Web dashboard served directly from the hub ESP32
- 📊 Historical data queries from sensor nodes
- ⚙️ Real-time control of output devices
- 🔁 Rolling buffer strategy for local data storage
- 🔔 Event broadcasting from nodes to hub
- 🧱 Easily extensible with new sensor/output types

---
## 🗂️ Project Structure

### Hub ESP32

```
forge32-hub/
├── src/
│   |── main.cpp
|   |── forge32-protocol.cpp
|   |── forge32-wifi.cpp
|   └── logger.cpp
├── data/
│   ├── index.html
│   ├── style.css
│   └── script.js   
├── include/
|   |── forge32-protocol.h
|   |── forge32-wifi.h
|   |── logger.h
│   └── passwords.h           # Must be added by user
└── platformio.ini
```

### Node ESP32

```
forge32-node/
├── include/
│   └── protocol.h              # Shared protocol definitions
├── src/
│   ├── main.cpp                # Entry point: initializes sensors/outputs
│   ├── tcp_client.cpp          # Handles TCP connection to hub
│   ├── sensor_manager.cpp      # Reads and buffers sensor data
│   ├── output_controller.cpp   # Executes control commands
│   ├── event_trigger.cpp       # Monitors and broadcasts events
│   └── register_message.cpp    # Builds and sends REGISTER message
├── platformio.ini              # PlatformIO project config
└── README.md
```

---
## 🚀 Getting Started

### Prerequisites
- [ESP32 IDF]([Get Started - ESP32 - — ESP-IDF Programming Guide latest documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/))
- [VSCode]([Visual Studio Code - Code Editing. Redefined](https://code.visualstudio.com/))
- [PlatformIO]([PlatformIO IDE for VSCode — PlatformIO latest documentation](https://docs.platformio.org/en/latest/integration/ide/vscode.html))
- ESP32 development boards
- Sensors and output devices (e.g., DHT22, PIR, LEDs, servos)

### Build & Upload

1. Clone the repository:
```bash
   git clone https://github.com/yourusername/forge32.git
```

2. Open in PlatformIO and select either `forge32-hub` or `forge32-node`.
    
3. Connect your ESP32 and upload:
    

---
# Software Design

- 📘 [SDD](/SDD.md)
- 📡 [Forge32 TCP Protocol](/TCP%20Protocol.md)

---
## 📄 License

This project is licensed under the MIT License.