## 📡 Forge32 TCP Protocol Overview

## 🔄 Data Flow Diagram

```
+-----------------+     1. Register    +--------------------+   5. HTTP Request  +-------------------+
|  Sensor Node(s) | -----------------> |   Hub ESP32 Unit   | <----------------- |  User Web Browser |
| (ESP32 Devices) |                    | (Web Server + Hub) |                    | (Dashboard Access)|
|                 | <--- 2. Query -----|                    |                    +-------------------+
|                 | ---> 3. Response ->|                    |
|                 | ---> 4. Event ---->|                    |
+-----------------+                    +--------------------+
```

### 🔢 Data Flow Steps

1. **Node Registration**
    - On boot, each ESP32 node connects to the local network and registers with the hub using the custom TCP protocol.
    - Registration includes device type, available sensors/outputs, and supported commands.
2. **Hub Queries Node**
    - When the dashboard is accessed or refreshed, the hub queries nodes for their latest sensor data (on-demand, not real-time).
3. **Node Responds with Data**
    - Nodes return processed sensor data to the hub in a standardized format.
4. **Node Sends Event (if triggered)**
    - If a node detects a pre-configured condition (e.g., motion detected), it sends an event broadcast to the hub.
5. **User Requests Dashboard**
    - The user accesses the dashboard via a browser.
    - The hub serves a dynamically generated HTML page with sensor data and control interfaces.

---
# </> Protocol Syntax
### 🔹Node → Hub: `REGISTER`
Describes node capabilities in JSON format.

`REGISTER`
```JSON
{
    "Node Name": {
        "tempSensor": {
            "type": "sensor",
            "dataType": "float",
            "range": [-40, 125],
            "history": {
                "interval": "1m",
                "duration": "24h"
            },
            "events": []
        },
        "motor1": {
            "type": "output",
            "dataType": "int",
            "range": [0, 180],
            "events": []
        },
        "motionSensor": {
            "type": "sensor",
            "dataType": "bool",
            "range": [0, 1],
            "events": ["motionDetected"]
        }
    }
}
```
### 🔹Hub → Node: `QUERY`
Requests historical data from a specific sensor.
````
QUERY id=node123;field=tempSensor;depth=60;\n
````
### 🔹Node → Hub: `DATA`
Returns a block of historical values.
```
DATA id=node123;field=tempSensor;values=23.5,23.6,23.7,...;\n
```
### 🔹Hub → Node: `CONTROL`
Sends a command to an output device.
```
CONTROL id=node456;field=motor1;value=90;\n
```
### 🔹Node → Hub: `EVENT`
Broadcasts a triggered event.
```
EVENT id=node123;field=motionSensor;event=motionDetected;\n
```