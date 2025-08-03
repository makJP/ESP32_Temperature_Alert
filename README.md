# ESP32 Temperature Alert with DHT11 and 7-Segment Display

## Overview
This project uses an **ESP32** microcontroller to continuously monitor temperature with a **DHT11** sensor. The current temperature is displayed on a 2-digit 7-segment display (using a MAX7219 driver).
If the temperature rises above 25°C, the ESP32 sends an alert email.

---

## Features
- Reads temperature from DHT11 sensor every 2 seconds
- Displays temperature on a 2-digit 7-segment display
- Sends an email alert when temperature exceeds 25°C
- Prevents spam by sending email only once per alert condition

---

## Hardware Required
- ESP32 development board
- DHT11 temperature and humidity sensor
- 2-digit 7-segment display module with MAX7219 driver
- Jumper wires and breadboard (optional for connections)

---

## Wiring
| Component         | ESP32 Pin  |
|-------------------|------------|
| DHT11 Data Pin    | GPIO17     |
| 7-Segment DIN     | GPIO15     |
| 7-Segment CS      | GPIO13     |
| 7-Segment CLK     | GPIO14     |
| GND (common)      | GND        |
| 5V / 3.3V         | 5V / 3.3V  |

*Note:* Make sure all grounds are connected together.

---

## Software Setup

### Arduino Libraries Required
- **DHT sensor library** (by Adafruit)
- **LedController** (supports MAX7219 7-segment displays)
- **ESP_Mail_Client** (for sending emails via SMTP)

Install these libraries via Arduino IDE Library Manager.

---

## How to Use

1. Clone or download this repository.
2. Open the Arduino sketch `esp32_temp_alert.ino`.
3. Replace the placeholders in the code with your information:
   - WiFi SSID and password
   - Email account and SMTP credentials (e.g., Gmail app password)
   - Recipient email address
4. Connect your hardware as per the wiring diagram above.
5. Upload the code to your ESP32.
6. Monitor temperature readings on the 7-segment display.
7. If temperature > 25°C, an alert email will be sent.

---

## Email Alert Configuration

- The project uses SMTP to send email alerts.
- For Gmail, generate an **App Password** using Google Account settings and use it in the code.
- Modify the SMTP server settings if you are using other email providers.

---

## Notes
- Make sure your ESP32 can connect to the internet.
- The code throttles email sending to avoid spam.
- For other 7-segment displays without MAX7219, you will need to adjust wiring and code.

---

## Author  
Contact: mayank.jp11@gmail.com

