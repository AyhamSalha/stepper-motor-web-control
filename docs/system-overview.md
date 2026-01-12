## System Overview
This project implements a web-based stepper motor control system using an ESP32.

Main components:
- ESP32 microcontroller (Wi-Fi enabled)
- Stepper motor (e.g. NEMA series)
- Stepper motor driver (e.g. A4988 / DRV8825)
- Endstop switch for homing
- External power supply for motor

The ESP32 hosts a web interface that allows real-time motor control via a browser.

The firmware is written in C/C++ with a low-level approach, avoiding Arduino helper libraries where possible.

Key features:
- GPIO control via register-level access
- Hardware interrupt handling for endstop detection
- Web server running on ESP32
- Real-time motor speed and direction control
