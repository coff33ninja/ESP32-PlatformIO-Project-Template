/**
 * @file mainformIO Project Template - Main Application
 * 
 * A working example demonstrating basic ESP32 functionality:
 * - Serial communication
 * - Built-in LED control
 * - WiFi connection capability
 * - Basic web server
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Configuration
#define LED_PIN 2
#define SERIAL_BAUD 115200

// WiFi credentials (replace with your own)
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Web server on port 80
WebServer server(80);

// Variables
bool ledState = false;
unsigned long lastBlink = 0;
const unsigned long blinkInterval = 1000;

void handleRoot() {
    String html = "<!DOCTYPE html><html><head><title>ESP32 Template</title></head><body>";
    html += "<h1>ESP32 PlatformIO Template</h1>";
    html += "<p>LED State: " + String(ledState ? "ON" : "OFF") + "</p>";
    html += "<p><a href='/toggle'>Toggle LED</a></p>";
    html += "<p>Uptime: " + String(millis() / 1000) + " seconds</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleToggle() {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", "");
}

void handleNotFound() {
    server.send(404, "text/plain", "Not found");
}

void setup() {
    // Initialize serial communication
    Serial.begin(SERIAL_BAUD);
    delay(1000);
    
    Serial.println("\n=== ESP32 PlatformIO Project Template ===");
    Serial.println("Version: 1.0.0");
    
    // Initialize LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    
    // Connect to WiFi (optional - will work without WiFi too)
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        
        // Setup web server routes
        server.on("/", handleRoot);
        server.on("/toggle", handleToggle);
        server.onNotFound(handleNotFound);
        
        // Start web server
        server.begin();
        Serial.println("Web server started");
        Serial.println("Visit http://" + WiFi.localIP().toString() + " in your browser");
    } else {
        Serial.println("\nWiFi connection failed - running in offline mode");
    }
    
    Serial.println("Setup complete!");
    Serial.println("LED will blink every " + String(blinkInterval) + "ms");
}

void loop() {
    // Handle web server requests (if WiFi connected)
    if (WiFi.status() == WL_CONNECTED) {
        server.handleClient();
    }
    
    // Blink LED at regular intervals
    unsigned long currentTime = millis();
    if (currentTime - lastBlink >= blinkInterval) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        lastBlink = currentTime;
        
        // Print status every 10 blinks
        static int blinkCount = 0;
        blinkCount++;
        if (blinkCount >= 10) {
            Serial.println("Status: Running - Blink count: " + String(blinkCount));
            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("WiFi: Connected (" + WiFi.localIP().toString() + ")");
            }
            blinkCount = 0;
        }
    }
    
    // Small delay to prevent watchdog issues
    delay(10);
}