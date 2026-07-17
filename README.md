<div align="center">

# 🔐 Embedded Smart Door Lock System with Non-Volatile EEPROM Memory

### 4x4 Matrix Keypad Scan • 16x2 LCD UI Panel • Micro Servo Actuator • EEPROM Flash Backup

<img src="https://img.shields.io/badge/Language-C++%20%2F%20Arduino-blue?style=for-the-badge&logo=arduino">
<img src="https://img.shields.io/badge/Hardware-Microcontroller-red?style=for-the-badge">
<img src="https://img.shields.io/badge/Memory-Non--Volatile%20EEPROM-success?style=for-the-badge">
<img src="https://img.shields.io/badge/Type-Embedded%20Systems-orange?style=for-the-badge">
<img src="https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge">

<br>

*A high-level embedded security application utilizing an Arduino microcontroller to drive an automated physical barrier lock. The system integrates a dynamic user credential database with direct flash memory persistence and anti-brute-force defense protocols.*

</div>

---

# 📖 Project Overview

Access control systems are fundamental pillars of modern physical security infrastructure. Transitioning mechanical latching assemblies into automated, digital security systems requires reliable electronic human-machine interfaces (HMIs) and fail-safe data storage.

This project introduces the **design, schematic validation, and programmatic architecture of a Smart Door Lock System**. The system consists of three foundational structural layers:

- **Multiplexed Input & Visual Output Interfaces (4x4 Matrix Keypad & 16x2 LCD)**
- **Non-Volatile Static State Storage (Internal Microcontroller EEPROM)**
- **Mechanical Servo Latching & Active Audio-Visual Alert Arrays**

During standard operation, the controller scans human tactile input through a multiplexed 4x4 keypad matrix and echoes masked security metrics on a 16x2 alphanumeric display. If the matching algorithm validates the structural data array against the pre-loaded primary security array, a pulse-width modulation (PWM) servo motor disengages the mechanical door bolt mechanism. 

To ensure long-term stability and residential reliability, custom user configurations are committed directly to non-volatile EEPROM memory cells, preserving custom passcodes across power blackouts without relying on auxiliary backup batteries.

---

# 🎯 Project Objectives

The primary engineering benchmarks established for this architecture include:

- Design a standalone, human-interactive digital security enclosure.
- Process matrix keypad arrays to implement real-time debounce filtering.
- Drive parallel 4-bit alphanumeric visual data updates onto an LCD panel.
- Implement an automated fallback procedure to load passwords from flash storage upon cold boots.
- Build an on-the-fly secondary credential management system protected by active validation challenges.
- Engineer an anti-brute-force mechanism enforcing a 30-second hardware blackout loop on a 3-strike failure limit.
- Reconstruct the physical input terminal trace assignments to safely isolate row-scanning operations from hardware serial transceivers (`TX/RX`).

---

# 📦 Component Bill of Materials (BOM)

| Designator | Quantity | Component | Description / Role |
| :--- | :---: | :--- | :--- |
| **U1** | 1 | Arduino Uno R3 | Central microcontroller system processing logic units |
| **U2** | 1 | LCD 16 x 2 | Alphanumeric UI system display module |
| **R1** | 1 | 1 kΩ Resistor | Pull-down configuration resistor |
| **R2** | 1 | 220 Ω Resistor | Inline current limiter for signaling nodes |
| **KEYPAD1** | 1 | Keypad 4x4 | Matrix input tactile user scanning array |
| **SERVO01** | 1 | Positional Micro Servo | Mechanical lock actuator assembly |
| **D1** | 1 | Red LED | Visual notification light for access denial or lockouts |
| **D2** | 1 | Green LED | Visual notification light for authorized entry access |
| **PIEZO01** | 1 | Piezo | Audio feedback active buzzer chime sound generator |

---

# 🗺️ System Visuals & Schematics

### 1. Schematics (Tinkercad)
Detailed architectural schematic layout showcasing internal electrical paths, signal dividers, and logic pathways.

![Tinkercad Schematic](circuit_tinkercad_schemtic.png)

### 2. Circuit Diagram (Tinkercad Simulation)
Virtual breadboard layout demonstrating initial component spacing and interactive trace routing.

![Tinkercad Circuit](circuit_tinkercad.png)

### 3. Physical Hardware Construction
The deployed physical circuit assembly demonstrating exact terminal wiring and final hardware placement.

![Physical Circuit Pic](circuit-schematic.jpeg)

