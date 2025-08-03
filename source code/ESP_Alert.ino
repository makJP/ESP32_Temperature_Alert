#include <WiFi.h>
#include "DHT.h"
#include <LedController.hpp>
#include <ESP_Mail_Client.h>

// DHT11 Config
#define DHTPIN 17
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// 7-Segment MAX7219 Config
#define DIN 15
#define CS  13
#define CLK 14
LedController<1,1> lc(DIN, CLK, CS);

// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Email/SMTP Settings
#define emailSenderAccount    "YOUR_EMAIL@gmail.com"
#define emailSenderPassword   "YOUR_APP_PASSWORD"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "[ALERT] ESP32 Temperature"
const char* emailRecipient  = "RECIPIENT_EMAIL@gmail.com";

ESP_Mail_Session session;
SMTP_Message message;
SMTPSession smtp;

// Threshold
const float tempThreshold = 25.0;
bool emailSent = false;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Setup MAX7219 2-digit display
  lc.setIntensity(8);
  lc.clearMatrix();

  // WiFi connect
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  // Mail session setup
  session.server.host_name = smtpServer;
  session.server.port = smtpServerPort;
  session.login.email = emailSenderAccount;
  session.login.password = emailSenderPassword;
  session.login.user_domain = "";

  message.sender.name = "ESP32";
  message.sender.email = emailSenderAccount;
  message.subject = emailSubject;
  message.addRecipient("Alert", emailRecipient);
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;

  MailClient.networkReconnect(true);
}

void displayTemperature(int temp) {
  // Display on 2-digit 7-segment (assume temp 0...99)
  int tens = (temp / 10) % 10;
  int ones = temp % 10;
  lc.setDigit(0, 1, tens, false); // Left digit (digit 1)
  lc.setDigit(0, 0, ones, false); // Right digit (digit 0)
}

bool sendEmailNotification(float temp) {
  String body = "Temperature above threshold! Current temp: " + String(temp) + "C";
  message.text.content = body.c_str();
  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Email failed: " + smtp.errorReason());
    return false;
  }
  Serial.println("Email sent!");
  return true;
}

void loop() {
  float t = dht.readTemperature();

  if (!isnan(t)) {
    Serial.print("Temp: "); Serial.println(t);
    displayTemperature((int)t);

    if (t > tempThreshold && !emailSent) {
      if (sendEmailNotification(t)) emailSent = true;
    }
    if (t <= tempThreshold) emailSent = false;
  } else {
    Serial.println("Failed to read DHT11!");
  }
  delay(2000);
}
