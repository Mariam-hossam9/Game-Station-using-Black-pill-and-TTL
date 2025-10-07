# 🎮 BlackPill-TFT-Games

### A Mini Embedded Game Console on STM32 Black Pill

---

## 🧩 Overview
**BlackPill-TFT-Games** is an embedded gaming system built on the **STM32F103C8T6 (Black Pill)** microcontroller.  
The system features **three mini-games** displayed on a **TFT screen** and controlled using **hardware switches**.  
Game selection is made through **TTL serial communication**, allowing the user to choose which game to play before the display starts.

---

## ⚙️ Features
- Three built-in games running directly on the Black Pill board  
- Real-time rendering on TFT display  
- Hardware button control for player actions  
- TTL serial interface for selecting games  
- Modular driver-based architecture (GPIO, SPI, Systick, USART, TFT, etc.)  
- Written in C using HAL-free direct register programming  

---

## 🧠 How It Works
1. The system waits for a **TTL serial command** indicating which game to start.  
2. Once a valid command is received, the selected game initializes and runs on the **TFT display**.  
3. The player uses **switches** connected to GPIO pins for movement and interaction.  
4. Each game runs independently, using Systick for timing and USART for communication.  

---

## 🕹️ Games Included
| Game | Description |
|------|--------------|
| **1. Bouncing Ball** | A ball moves across the screen — the player controls a paddle to keep it from falling. |
| **2. Dodge Blocks** | The player moves left or right to avoid falling blocks. |
| **3. Catch the Star** | The player must catch falling stars while avoiding obstacles. |

*(Names and mechanics can be adjusted if your games differ — let me know if you want me to customize this section.)*

---

## 🧰 Hardware Requirements
| Component | Description |
|------------|-------------|
| **MCU** | STM32F103C8T6 (Black Pill) |
| **Display** | 1.8" or 2.4" TFT (SPI interface) |
| **Buttons/Switches** | 4 push buttons (Up, Down, Left, Right) |
| **Serial Interface** | TTL (USB-to-TTL adapter for PC communication) |
| **Power Supply** | 3.3V regulated |

---

## 🔌 Pin Connections (Example)
| Peripheral | STM32 Pin | Description |
|-------------|-----------|-------------|
| **TFT_CS**  | PA4 | Chip Select |
| **TFT_RST** | PA1 | Reset |
| **TFT_A0**  | PA2 | Data/Command |
| **TFT_SCK** | PA5 | SPI Clock |
| **TFT_MOSI**| PA7 | SPI Data |
| **BTN_UP**  | PB0 | Switch Input |
| **BTN_DOWN**| PB1 | Switch Input |
| **BTN_LEFT**| PB10 | Switch Input |
| **BTN_RIGHT**| PB11 | Switch Input |
| **USART_TX**| PA9 | TTL Output |
| **USART_RX**| PA10 | TTL Input |

*(Adjust if your wiring differs.)*

---

## 🧱 Software Structure
├── Core/
│ ├── main.c
│ ├── MSTK/ # Systick driver
│ ├── MUSART/ # UART communication driver
│ ├── MGPIO/ # GPIO driver
│ ├── MSPI/ # SPI driver
│ ├── HTFT/ # TFT display driver
│ └── Games/ # Game logic files
│
├── Inc/ # Header files
├── README.md
└── Makefile / Keil project file

yaml
Copy code

---

## 🧪 How to Run
1. Flash the firmware using **ST-Link** or **USB-UART bootloader**.  
2. Connect the **TFT display** and **buttons** according to the pin mapping.  
3. Open a **serial terminal (e.g., PuTTY, RealTerm)** at 9600 baud.  
4. Send a number (e.g., `1`, `2`, or `3`) over TTL to select a game.  
5. Control the game using the switches.  

---

## 🧰 Development Tools
- **IDE:** STM32CubeIDE / Keil uVision / PlatformIO  
- **Language:** C  
- **Debugger:** ST-Link V2  
- **Serial Monitor:** PuTTY / TeraTerm  
- **Display Driver:** TFT SPI-based (ST7735 / ILI9341)  

---

## 📜 License
This project is licensed under the **MIT License** — feel free to modify and expand.

---

## 👩‍💻 Author
**Mariam Hossam**  
Embedded Systems Engineer  
Faculty of Engineering, Helwan University  

---
