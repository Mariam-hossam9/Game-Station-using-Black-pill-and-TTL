# 🎮 BlackPill-TFT-Games

### A Mini Embedded Game Console on STM32 Black Pill

---

## 🧩 Overview
**BlackPill-TFT-Games** is an embedded gaming system built on the **STM32F103C8T6 (Black Pill)** microcontroller.  
It features **three interactive games** displayed on a **TFT screen** and controlled using **hardware switches**.  
The desired game is selected by sending a **character command (L, M, or S)** over **TTL serial communication**.

---

## ⚙️ Features
- Three built-in games running directly on the STM32 Black Pill  
- Real-time graphics on TFT display  
- Physical switches for control  
- TTL serial interface for game selection  
- Modular driver-based architecture (GPIO, SPI, Systick, USART, TFT, etc.)  
- Fully written in C (no HAL libraries)  
- GUI to interact with TTL for sending the commands

---

## 🕹️ Games Included
| Command | Game | Description |
|----------|------|-------------|
| **L** | **LED Memory** | Tests the player's memory by showing LED patterns that must be repeated correctly. |
| **M** | **Math Quiz** | Displays arithmetic questions — the player answers using the buttons before time runs out. |
| **S** | **Snake** | Classic snake game where the player controls movement to collect food and avoid collisions. |

---

## 🧠 How It Works
1. The system waits for a **TTL command** from the serial interface.  
2. Depending on the command:
   - `L` → Starts **LED Memory**
   - `M` → Starts **Math Quiz**
   - `S` → Starts **Snake**
3. The selected game initializes on the **TFT display**.  
4. The player uses **switches** connected to GPIO pins for movement and actions.  
5. Each game runs independently with its own logic and timing.  

---

## 🧱 Software Structure
├── Core/
│ ├── main.c
│ ├── MSTK/ # Systick driver
│ ├── MUSART/ # UART driver for TTL communication
│ ├── MGPIO/ # GPIO driver
│ ├── MSPI/ # SPI driver
│ ├── HTFT/ # TFT display driver
│ └── Games/ # Game logic (LED Memory, Math Quiz, Snake)
│
├── Inc/ # Header files
├── GUI/ # GUI code for TTL
├── media/ # Demo video
└── README.md

---

## 🧪 How to Run
1. Flash the firmware to the **STM32 Black Pill** using **ST-Link** or **USB-UART**.  
2. Connect the **TFT display** and **control switches**.  
3. Open a **serial terminal (e.g., PuTTY, TeraTerm)** at **9600 baud**.  
4. Send one of the following characters:
   - `L` → Play **LED Memory**
   - `M` → Play **Math Quiz**
   - `S` → Play **Snake**
5. Use the switches to control gameplay.

---

## 🧰 Development Tools
- **IDE:** STM32CubeIDE / Keil uVision / PlatformIO  
- **Language:** C  
- **Debugger:** ST-Link V2  
- **Serial Monitor:** PuTTY / RealTerm / TeraTerm  
- **Display Driver:** SPI-based TFT (ST7735 / ILI9341 compatible)

---
## 🎥 Demo Video

Click below to watch the gameplay demo of the three games (LED Memory, Math Quiz, and Snake):

🎮 [▶️ Watch Demo (MP4)](media/Demo.mp4)

