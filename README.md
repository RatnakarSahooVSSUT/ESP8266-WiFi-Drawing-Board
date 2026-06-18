# 🎨 ESP8266 Wi-Fi Drawing Board

<p align="center">
  <img src="https://img.shields.io/badge/ESP8266-NodeMCU-red?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/TFT-ILI9341-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/WiFi-Web%20Interface-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Embedded-Systems-orange?style=for-the-badge" />
</p>

---

## 📌 Overview

A simple Wi-Fi Drawing Board built using an **ESP8266 NodeMCU** and a **2.8" SPI TFT Display**.

The project allows users to connect to the ESP8266 through a web browser, draw sketches using a phone or laptop, select different colors, and send the drawing directly to the TFT display over Wi-Fi.

---

## ✨ Features

- Browser-based drawing interface
- Multiple color selection
- Smooth drawing experience
- Wireless communication over Wi-Fi
- TFT display rendering
- Touch and mouse support
- Embedded web server hosted on ESP8266
- Portable and standalone operation

---

## 🛠️ Tech Stack

### Hardware

![ESP8266](https://img.shields.io/badge/ESP8266-NodeMCU-red?style=flat-square)
![TFT](https://img.shields.io/badge/TFT-ILI9341-blue?style=flat-square)
![WiFi](https://img.shields.io/badge/WiFi-Enabled-green?style=flat-square)

### Software

![Arduino IDE](https://img.shields.io/badge/Arduino-IDE-00979D?style=flat-square&logo=arduino)
![C++](https://img.shields.io/badge/C++-Embedded-00599C?style=flat-square&logo=cplusplus)
![HTML5](https://img.shields.io/badge/HTML5-Web_Interface-E34F26?style=flat-square&logo=html5)
![JavaScript](https://img.shields.io/badge/JavaScript-Canvas-F7DF1E?style=flat-square&logo=javascript)

---

## 📂 Repository Structure

```text
ESP8266-WiFi-Drawing-Board/
│
├── ESP8266_WiFi_Drawing_Board.ino
├── README.md
│
├── images/
│   ├── setup.jpg
│   ├── output.jpg
│   └── demo.gif
│
└── docs/
    └── circuit_diagram.png
```

---

## 🔌 Hardware Connections

| TFT Display | ESP8266 NodeMCU |
|------------|----------------|
| VCC | 3.3V |
| GND | GND |
| CS | D8 |
| DC | D4 |
| RESET | D0 |
| MOSI | D7 |
| MISO | D6 |
| SCK | D5 |
| LED | 3.3V |

---

## 🚀 How It Works

```text
Phone / Laptop
       │
       ▼
 Web Drawing Interface
       │
       ▼
      Wi-Fi
       │
       ▼
   ESP8266 Server
       │
       ▼
   TFT Display
```

1. ESP8266 creates a Wi-Fi Access Point.
2. User connects using a phone or laptop.
3. A browser-based drawing canvas is opened.
4. Drawings are created using touch or mouse input.
5. The drawing data is sent to the ESP8266.
6. The ESP8266 renders the sketch on the TFT display.

---

## 🎯 Applications

- Wireless Drawing Board
- Embedded Graphics Experiments
- Web-to-Hardware Communication
- Educational IoT Demonstrations
- Human Machine Interface (HMI) Prototyping

---

## 🔮 Future Improvements

- Real-time drawing updates
- Adjustable brush sizes
- Collaborative drawing mode
- Touch-enabled TFT interaction
- Saving sketches to memory
- OTA firmware updates

---

## 📸 Demonstration

Add project images, screenshots, or GIFs here.

```markdown
![Demo](images/demo.gif)
```

---

## 📚 Libraries Used

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <Ucglib.h>
```

---

## ⭐ Support

If you found this project interesting, consider giving it a ⭐ on GitHub.

---

### Made with ESP8266, TFT Graphics, and a bit of curiosity. 🚀
