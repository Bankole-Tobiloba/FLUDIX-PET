# FLUDIX – Smart Automated Infusion Pump

*FLUDIX* is a cutting-edge automated infusion pump designed to revolutionize IV fluid therapy by integrating real-time monitoring, automation, and precision delivery. The system uses a custom-built infusion unit paired with a wearable Vital Band to monitor critical patient vitals and adjust fluid flow in real time minimizing human error and saving lives.

![FLUDIX](images/Fludix3D.png)

**Team Members:**
- **Tobiloba Bankole** – Embedded Systems, Firmware, Hardware Integration  
- **Phoebe Arome** – Health Research, Clinical Parameters, Medical Standards  
- **Eziamachukwu Celestine** – Software / website / mobile app developer,

## Table of Contents
- [What It Does](#what-it-does)
- [Key Features](#key-features)
- [How It Was Built](#how-it-was-built)
- [Technologies Used](#technologies-used)
- [Achievements](#achievements)
- [What We Learned](#what-we-learned)
- [What's Next](#whats-next)
- [Resources & Build Guides](#resources--build-guides)
- [Contact Us](#contact-us)

  
## What It Does

FLUDIX solves the problem of unsafe and manually controlled IV therapy in critical health emergencies (e.g., heart disease, stroke, trauma, infection). With its wearable Vital Band and integrated sensors (SpO₂, BP, Temp, Heart Rate), the system provides intelligent infusion control that adapts to each patient's condition in real-time.

## Key Features

- **Automated Infusion Regulation** via sensor-driven input
- **Vital Band** for real-time SpO₂, BP, Temp & Heart Rate tracking
- **Dual Power Supply**: Rechargeable LiPo + Solar panel charging
- **Wi-Fi & Bluetooth Connectivity** for remote control & alerts
- **Flutter-based App** for nurses/doctors to monitor infusion
- **Offline Functionality** for use in remote/rural environments
- **Custom Built Hardware** – includes 3D printed case, syringe & peristaltic pump

## How It Was Built

We hand-built the system from scratch using:
- CAD modeling and 3D printing for the frame
- ESP32 and 3 Arduino Uno boards for control and data processing
- Custom-built syringe and peristaltic pumps
- Flutter + Firebase for app and data interaction
- Solar and AC charging for field reliability

Programming was done in **C++** via Arduino IDE and integrated using **Wi-Fi** with SSH remote access.

## Technologies Used

**Languages:**  
- C++ (Firmware), Dart (Flutter), HTML (Docs)

**Frameworks & Platforms:**  
- Arduino IDE, Flutter, Firebase, Wokwi, Fritzing, Fusion360

**Cloud Services:**  
- Firebase, Google Cloud Platform

**Design & Hardware Tools:**  
- Fusion360, Fritzing


**Databases:**  
- Firebase Realtime Database

**APIs:**  
- HTTP APIs for alert pushing (in-app)

## Achievements

- Winner – RAIN Health-Tech Challenge 2024
- Top 4 – Nigerian Academy of Engineering Hackathon 2024 (Only undergraduate team among PhDs & Professors)

## What We Learned

Building FLUDIX taught us real-world systems integration, human-centered medical design, and the importance of iterative prototyping. We learned how to align engineering with medical protocols and deliver value under tight resource constraints.

## What's Next

- Pilot testing with local clinics and rural hospitals  
- Integration of real-time analytics dashboard for remote health monitoring  
- Improving power efficiency & reducing size for large-scale production  

## Resources & Build Guides

You’ll find all schematics, source code, diagrams, and component sourcing links in the [resources folder](./resources).

## Contact Us

For collaborations, feedback, or inquiries:  
bankoletobi8005@gmail.com

https://github.com/Bankole-Tobiloba/FLUDIX


