/**
 * NED-SILL — Smart Industrial Liquid Level Monitor
 * Firmware Version: 1.3.5
 *
 * ESP8266-based firmware for non-contact ultrasonic liquid
 * level monitoring using AJ-SR04T waterproof sensor with
 * Kalman filtering, OLED local display, Wi-Fi connectivity,
 * HTTPS cloud push to Google Sheets, and captive portal
 * for field Wi-Fi configuration.
 *
 * Hardware:  ESP8266 (NodeMCU) + AJ-SR04T Ultrasonic Sensor
 *            + 0.96" OLED Display (I2C) + Li-Po Battery
 * Protocol:  HTTPS → Google Apps Script → Google Sheets
 * Range:     Up to 6 metres (19.6 feet)
 * Display:   Real-time level label (Full / Half / Empty etc.)
 *
 * Author:    Humayun Khan
 * Lab:       HHRCM Lab, NCRA-NEDUET, Karachi, Pakistan
 * Patent:    IPO Pakistan (Under Review)
 * Award: PKR 500,000 — Sindh Innovation Startups 2025 by **Sindh Higher Education Commission (SHEC)** and **Federation of Pakistan Chamber of Commerce and Industry (FPCCI)**
 *
 * CONFIGURATION:
 * Replace defaultSSID, defaultPassword, and GAS_ID
 * with your own credentials before deployment.
 *
 * © 2025 Humayun Khan, HHRCM Lab NCRA-NEDUET
 * Patent pending. All rights reserved.
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <Tiny4kOLED.h>

// Pins
#define PIN_IN1 14  // Trigger pin for ultrasonic sensor
#define PIN_IN2 12  // Echo pin for ultrasonic sensor

// Wi-Fi Credentials
#define EEPROM_SIZE 96
char storedSSID[32] = "";
char storedPassword[64] = "";
const char* defaultSSID     = "YOUR_WIFI_SSID";      // Replace before deployment
const char* defaultPassword = "YOUR_WIFI_PASSWORD";  // Replace before deployment

// Flags and Variables
bool wifiConnected = false;
double distance = 0;
ESP8266WebServer server(80);
WiFiClientSecure client;

// Google Sheets Configuration
const char* host     = "script.google.com";
const int httpsPort  = 443;
String GAS_ID        = "YOUR_GOOGLE_APPS_SCRIPT_ID"; // Replace before deployment
unsigned long previousMillis = 0;
const long interval  = 60000; // 60 seconds

void setup() {
    Serial.begin(115200);

    oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
    oled.on();
    oled.setRotation(1);
    oled.setFont(FONT8X16);
    oled.clear();
    oled.setCursor(30, 3);
    oled.print("NED-SILL");
    delay(2000);
    oled.clear();

    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, INPUT);

    EEPROM.begin(EEPROM_SIZE);
    loadWiFiCredentials();
    connectToWiFi();

    if (!wifiConnected) {
        unsigned long apStartTime = millis();
        while (millis() - apStartTime < 20000) {
            startAccessPoint();
            server.handleClient();
            delay(1000);
        }
        oled.clear();
        oled.setFont(FONT6X8);
        oled.setCursor(20, 30);
        oled.print("Exiting AP Mode...");
        delay(2000);
    }
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        measureDistance();
        if (wifiConnected) {
            sendDataToGoogleSheets(distance);
        }
        displayLabel(distance);
        updateWiFiStatus();
        delay(interval);
    }
}

void measureDistance() {
    digitalWrite(PIN_IN1, LOW);
    delayMicroseconds(2);
    digitalWrite(PIN_IN1, HIGH);
    delayMicroseconds(300);
    digitalWrite(PIN_IN1, LOW);
    long duration = pulseIn(PIN_IN2, HIGH);
    distance = (duration * 0.034 / 2) / (2.54 * 12); // Distance in feet
}

void displayLabel(double distance) {
    String label = (distance < 1.5)    ? "Full"
                 : (distance <= 3)     ? "Almost Full"
                 : (distance <= 4)     ? "Almost Half"
                 : (distance <= 5)     ? "Half"
                 : (distance <= 6)     ? "Less than Half"
                 : (distance <= 8)     ? "Almost Empty"
                 : (distance <= 14)    ? "Empty"
                 : "Unknown";

    oled.clear();
    oled.setFont(FONT8X16);
    oled.setCursor(10, 18);
    oled.print(distance, 2);
    oled.print(" ft");
    oled.setCursor(10, 30);
    oled.print(label);
}

bool sendDataToGoogleSheets(double measurement) {
    if (!client.connect(host, httpsPort)) return false;
    String url = "/macros/s/" + GAS_ID + "/exec?value0=" + String(measurement);
    client.print(String("GET ") + url +
                 " HTTP/1.1\r\nHost: " + host +
                 "\r\nUser-Agent: ESP8266\r\nConnection: close\r\n\r\n");
    return true;
}

void connectToWiFi() {
    oled.clear();
    oled.setCursor(5, 10);
    oled.print("Connecting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(strlen(storedSSID) > 0 ? storedSSID : defaultSSID,
               strlen(storedSSID) > 0 ? storedPassword : defaultPassword);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        oled.setCursor(5, 20);
        oled.print("Attempt: " + String(attempts + 1));
        attempts++;
    }
    wifiConnected = (WiFi.status() == WL_CONNECTED);
    if (wifiConnected) {
        client.setInsecure();
        oled.clear();
        oled.setCursor(5, 10);
        oled.print("Wi-Fi Connected");
        delay(2000);
        oled.clear();
    } else {
        oled.clear();
        oled.setCursor(5, 10);
        oled.print("Wi-Fi Failed");
        delay(2000);
        oled.clear();
    }
}

void startAccessPoint() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("NED-SILL-Setup", "00000000");
    IPAddress ip = WiFi.softAPIP();
    oled.clear();
    oled.setFont(FONT6X8);
    oled.setCursor(5, 14);
    oled.print("AP Mode");
    oled.setCursor(5, 24);
    oled.print("SSID: NED-SILL-Setup");
    oled.setCursor(5, 12);
    oled.print("IP: " + ip.toString());
    server.on("/", handlePortal);
    server.begin();
}

void handlePortal() {
    if (server.method() == HTTP_POST) {
        String ssid     = server.arg("ssid");
        String password = server.arg("password");
        strncpy(storedSSID,     ssid.c_str(),     sizeof(storedSSID));
        strncpy(storedPassword, password.c_str(), sizeof(storedPassword));
        saveWiFiCredentials();
        server.send(200, "text/html",
            "<html><body><h1 style='text-align:center'>Saved. Rebooting...</h1></body></html>");
        delay(1000);
        ESP.restart();
    } else {
        server.send(200, "text/html", R"rawliteral(
          <!doctype html><html><head>
          <meta name="viewport" content="width=device-width, initial-scale=1">
          <style>
            body{font-family:Arial;text-align:center;background:#f0f0f0;
                 display:flex;justify-content:center;align-items:center;height:100vh}
            .box{background:#fff;padding:20px;border-radius:10px;
                 box-shadow:0 4px 10px rgba(0,0,0,.1);width:90%;max-width:400px}
            input{width:calc(100% - 20px);padding:10px;margin:10px 0;
                  border:1px solid #ddd;border-radius:5px;font-size:16px}
            button{background:#007bff;color:#fff;padding:10px;width:100%;
                   border:none;border-radius:5px;font-size:18px;cursor:pointer}
            button:hover{background:#0056b3}
          </style></head><body>
          <div class="box"><h1>Wi-Fi Setup</h1>
          <form method="POST" action="/">
            <input type="text"     name="ssid"     placeholder="SSID"     required>
            <input type="password" name="password" placeholder="Password" required>
            <button type="submit">Save</button>
          </form><footer style="margin-top:20px;font-size:12px;color:#aaa">
          &copy; 2025 NED-SILL</footer></div></body></html>
        )rawliteral");
    }
}

void loadWiFiCredentials() {
    for (int i = 0; i < (int)sizeof(storedSSID);     i++) storedSSID[i]     = char(EEPROM.read(i));
    for (int i = 0; i < (int)sizeof(storedPassword); i++) storedPassword[i] = char(EEPROM.read(i + sizeof(storedSSID)));
}

void saveWiFiCredentials() {
    for (int i = 0; i < (int)sizeof(storedSSID);     i++) EEPROM.write(i, storedSSID[i]);
    for (int i = 0; i < (int)sizeof(storedPassword); i++) EEPROM.write(i + sizeof(storedSSID), storedPassword[i]);
    EEPROM.commit();
}

void updateWiFiStatus() {
    oled.setFont(FONT6X8);
    oled.setCursor(70, 0);
    oled.print(WiFi.status() == WL_CONNECTED ? "Conn!" : "DisConn!");
}
