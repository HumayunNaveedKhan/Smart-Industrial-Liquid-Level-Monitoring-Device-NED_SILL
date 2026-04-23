# NED-SILL — Smart Industrial Liquid Level Monitor

> Patented industrial IoT system for real-time non-contact 
> liquid level monitoring — commercially deployed at 
> J&P Coats (MNC), Karachi, Pakistan.

---

## Overview

NED-SILL is an indigenously designed and developed Industrial 
IoT device for non-contact ultrasonic liquid level monitoring 
in large-scale industrial tank systems — textile, garment, 
and process industries where hundreds of tanks require 
continuous oversight for liquid level, volume, flow, and 
plant capacity.

Developed at the Haptics, Human-Robotics & Condition 
Monitoring Lab (HHRCM), NCRA-NEDUET, under the mentorship 
of Prof. Dr. Riaz Uddin (Professor, Director NCRA & 
Director ORIC, NEDUET).

**Status:** Commercially deployed at J&P Coats (MNC), Karachi  
**Patent:** Filed — IPO Pakistan Application No. **965/2025**  
**Award:** PKR 500,000 — Sindh Innovation Startups 2025 by **Sindh Higher Education Commission (SHEC)** and **Federation of Pakistan Chamber of Commerce and Industry (FPCCI)**   
**Range:** Up to 6 metres (19.6 feet) | **Operation:** 24/7  

---

## Problem It Solves

Industrial facilities managing hundreds of tanks rely on 
manual dipsticks, sight glasses, and graduated scales — 
labour-intensive, error-prone, and hazardous when handling 
caustics, acids, fuels, or high-temperature liquids.

NED-SILL replaces manual measurement with automated, 
non-contact, cloud-connected real-time level intelligence.

---

## System Architecture

<img width="1536" height="1024" alt="Architecture-NED-SILL" src="https://github.com/user-attachments/assets/40f18b7d-48f8-4b61-909b-622ecfa68813" />


---

## Key Features

- **Non-contact ultrasonic measurement** — AJ-SR04T 
  waterproof sensor, zero liquid contamination risk
- **Kalman filter** — suppresses environmental noise, 
  stabilises readings across industrial conditions
- **Real-time OLED display** — local level label 
  (Full / Half / Empty) with live distance in feet
- **Cloud dashboard** — Google Sheets with timestamped 
  logs, multi-unit conversion (ft / in / cm), 
  and volume/flow analytics
- **Captive portal configuration** — field Wi-Fi setup 
  via browser, no proprietary app required
- **Battery backup** — Li-Po 1250mAh + TP4057 BMS, 
  USB Type-C charging
- **3D-printed industrial housing** — SolidWorks-designed 
  enclosure for robust field deployment
- **Multi-liquid compatible** — caustics, acids, bases, 
  oils, fuels, no contamination

---

## Hardware Stack

| Component | Details |
|---|---|
| Microcontroller | ESP8266 (Wi-Fi enabled) |
| Sensor | AJ-SR04T waterproof ultrasonic (time-of-flight) |
| Display | 0.96" OLED — I²C communication |
| Battery | Li-Po 1250 mAh |
| Charging IC | TP4057 battery management module |
| Power input | USB Type-C |
| Enclosure | Custom 3D-printed (SolidWorks) |
| Range | Up to 6 m / 19.6 ft |
| Operating temp | -20°C to 70°C |



<img width="1428" height="1600" alt="NED-SILL" src="https://github.com/user-attachments/assets/3324c0de-7d3e-4b76-a93d-cc6212760ff4" />

---

## Software & Communication Stack

| Layer | Technology |
|---|---|
| Firmware | Embedded C (ESP8266 Arduino) |
| Noise filtering | Kalman Filter |
| Protocol | HTTPS → Google Apps Script |
| Cloud | Google Sheets API |
| Dashboard | Google Sheets + Mobile Application |
| Configuration | Captive Portal (AP mode) |
| Storage | EEPROM (Wi-Fi credentials) |


<img width="947" height="920" alt="NED-SILL-Hardware" src="https://github.com/user-attachments/assets/e4f8b694-2656-42da-8bb2-f84448aa8e3c" />

---

## Source Code

| File | Description |
|---|---|
| [`src/NED-SILL-main_v1.0.ino`](src/NED-SILL-main_v1.0.ino) | ESP8266 firmware — ultrasonic sensing, Kalman filter, OLED display, HTTPS push, captive portal |
| [`src/NED-SILL-AppScript_v1.0.gs`](src/NED-SILL-AppScript_v1.0.gs) | Google Apps Script — data logging, unit conversion, level labels |

> ⚠️ Replace `defaultSSID`, `defaultPassword`, `GAS_ID`, 
> and `sheet_id` with your own credentials before deployment.  
> PCB design files are proprietary and protected under 
> IPO Pakistan Patent Application No. 965/2025.

---

## Deployment

**Client:** J&P Coats (MNC) — Karachi, Pakistan  
**Environment:** Active industrial production facility  
**Tanks monitored:** Large-scale storage tanks  
**Status:** Operational  
**Outcome:** Replaced manual dipstick measurements with 
real-time non-contact cloud visibility across factory floor

> 📌 Dashboard screenshots and test results shown in this 
> repository are from lab testing at HHRCM Lab, NCRA-NEDUET.  
> Production data from J&P Coats deployment is confidential 
> and not included in this repository.


<img width="480" height="560" alt="NED-SILL-deployment-1" src="https://github.com/user-attachments/assets/43b65019-ba28-4d20-987d-f0815d87d7ac" />
<img width="960" height="747" alt="NED-SILL-deployment-2" src="https://github.com/user-attachments/assets/21f4f970-8813-4c15-b139-659c8e86fd21" />
<img width="960" height="747" alt="Plant pics for NED-SILL" src="https://github.com/user-attachments/assets/69303109-337c-4ded-b9d2-e108ca108b0b" />
<img width="960" height="747" alt="NED-SILL-deployment-3 1" src="https://github.com/user-attachments/assets/292700ba-6fa4-4c84-8837-2f5e42b13c6d" />
<img width="960" height="66" alt="image" src="https://github.com/user-attachments/assets/bf1f68ac-2d49-4607-bcf6-f2f2ed87625e" />

<img width="960" height="813" alt="image" src="https://github.com/user-attachments/assets/4e20652d-54ed-4e5f-ab0b-53f3ea92e2ba" />

<img width="720" height="1200" alt="NED-SILL-App-2" src="https://github.com/user-attachments/assets/a4c2d604-b90d-4a65-985d-57753fd0bc0e" />
<img width="720" height="1200" alt="NED-SILL-App-1" src="https://github.com/user-attachments/assets/2678bc2f-ff6e-4bc2-b9b0-fc7027281720" />




---

## Patent & IP

**Patent filed with IPO Pakistan**  
Application No. **965/2025**  
Filing Date: 12 December 2025  
Status: Under Review  

<img width="963" height="673" alt="Patent Receipt-SILL-965-2025" src="https://github.com/user-attachments/assets/f2a22628-f272-4f2c-a431-c2d75c1491a8" />


> Note: Firmware source code and PCB design files are 
> proprietary and protected under the filed patent. 
> They are not included in this repository.

---

## Publication

H. Khan, F. Sheikh, H. Waqar, and R. Uddin, "Smart Industrial Liquid Level Solution for Textile and Process Industry," in Proceedings of the 7th International Conference on Robotics and Automation in Industry (ICRAI), Islamabad, Pakistan, May 2026.

---

## Related Products (Same Lab)

- [NED-EIoT](https://github.com/HumayunNaveedKhan/Embedded-Industrial-Energy-Monitoring-Device-NED_EIoT) 
  — Industrial Energy & Equipment Health Monitor 
  (also deployed at J&P Coats)

---

## Author

**Humayun Khan**  
Team Lead, HHRCM Lab, NCRA-NEDUET  
Co-Founder, Haptronica & RobAutoStem (NIC Karachi, Cohort 12)

📧 humayunnaveedkhan@gmail.com  
🔗 [LinkedIn](https://linkedin.com/in/humayunnaveedkhan)  
🌐 [Portfolio](https://humayunnaveedkhan.github.io/portfolio)

---

## License

© 2025 Humayun Khan, HHRCM Lab NCRA-NEDUET.  
Patent pending. All rights reserved.  
No part of this repository may be reproduced or used 
commercially without written permission.
