/**
 * ESP32 PlatformIO Template - Example with Custom Library
 * 
 * This example demonstrates:
 * - Using custom libraries from the lib/ directory
 * - Sensor reading and data processing
 * - Web interface with sensor data
 * - JSON data formatting
 * 
 * To use this example:
 * 1. Rename this file to main.cpp
 * 2. Build and upload: .\build.ps1 deploy
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "ExampleSensor.h"  // Custom library from lib/

// Configuration
#define LED_PIN 2
#define SENSOR_PIN A0
#define SERIAL_BAUD 115200

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Web server and sensor objects
WebServer server(80);
ExampleSensor sensor(SENSOR_PIN);

// Variables
bool ledState = false;
unsigned long lastSensorRead = 0;
unsigned long lastBlink = 0;
const unsigned long sensorInterval = 5000;  // Read sensor every 5 seconds
const unsigned long blinkInterval = 1000;

void handleRoot() {
    String html = "<!DOCTYPE html><html><head>";
    html += "<title>ESP32 Sensor Dashboard</title>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<style>body{font-family:Arial;margin:40px;} .sensor{background:#f0f0f0;padding:20px;margin:10px;border-radius:5px;}</style>";
    html += "</head><body>";
    html += "<h1>ESP32 Sensor Dashboard</h1>";
    
    if (sensor.isReady()) {
        html += "<div class='sensor'>";
        html += "<h2>Sensor Reading</h2>";
        html += "<p>Current Value: " + String(sensor.getLastReading(), 2) + "%</p>";
        html += "<p>Last Update: " + String(sensor.getTimeSinceUpdate() / 1000) + " seconds ago</p>";
        html += "</div>";
    } else {
        html += "<div class='sensor'><p>Sensor not initialized</p></div>";
    }
    
    html += "<div class='sensor'>";
    html += "<h2>System Status</h2>";
    html += "<p>LED State: " + String(ledState ? "ON" : "OFF") + "</p>";
    html += "<p>Uptime: " + String(millis() / 1000) + " seconds</p>";
    html += "<p>Free Heap: " + String(ESP.getFreeHeap()) + " bytes</p>";
    html += "<p><a href='/toggle'>Toggle LED</a> | <a href='/api/sensor'>JSON API</a></p>";
    html += "</div>";
    
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleAPI() {
    // Create JSON response
    JsonDocument doc;
    doc["timestamp"] = millis();
    doc["uptime"] = millis() / 1000;
    doc["led_state"] = ledState;
    doc["free_heap"] = ESP.getFreeHeap();
    
    if (sensor.isReady()) {
        doc["sensor"]["value"] = sensor.getLastReading();
        doc["sensor"]["last_update"] = sensor.getTimeSinceUpdate();
        doc["sensor"]["status"] = "ready";
    } else {
        doc["sensor"]["status"] = "not_initialized";
    }
    
    String jsonString;
    serializeJson(doc, jsonString);
    
    server.send(200, "application/json", jsonString);
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
    
    Serial.println("\n=== ESP32 Sensor Dashboard ===");
    Serial.println("Version: 1.0.0 (with custom library)");
    
    // Initialize LED pin
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
    
    // Initialize sensor
    if (sensor.begin()) {
        Serial.println("✅ Sensor initialized successfully");
    } else {
        Serial.println("❌ Sensor initialization failed");
    }
    
    // Connect to WiFi
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✅ WiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        
        // Setup web server routes
        server.on("/", handleRoot);
        server.on("/api/sensor", handleAPI);
        server.on("/toggle", handleToggle);
        server.onNotFound(handleNotFound);
        
        // Start web server
        server.begin();
        Serial.println("🌐 Web server started");
        Serial.println("Visit http://" + WiFi.localIP().toString() + " in your browser");
    } else {
        Serial.println("\n❌ WiFi connection failed - running in offline mode");
    }
    
    Serial.println("🚀 Setup complete!");
}

void loop() {
    // Handle web server requests
    if (WiFi.status() == WL_CONNECTED) {
        server.handleClient();
    }
    
    // Read sensor periodically
    unsigned long currentTime = millis();
    if (currentTime - lastSensorRead >= sensorInterval) {
        if (sensor.isReady()) {
            float reading = sensor.read();
            Serial.println("📊 Sensor reading: " + String(reading, 2) + "%");
        }
        lastSensorRead = currentTime;
    }
    
    // Blink LED
    if (currentTime - lastBlink >= blinkInterval) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        lastBlink = currentTime;
        
        // Status report every 30 seconds
        static int blinkCount = 0;
        blinkCount++;
        if (blinkCount >= 30) {
            Serial.println("💡 Status: Running - Uptime: " + String(millis() / 1000) + "s");
            if (WiFi.status() == WL_CONNECTED) {
                Serial.println("🌐 WiFi: Connected (" + WiFi.localIP().toString() + ")");
            }
            if (sensor.isReady()) {
                Serial.println("📊 Sensor: " + String(sensor.getLastReading(), 2) + "%");
            }
            blinkCount = 0;
        }
    }
    
    // Small delay to prevent watchdog issues
    delay(10);
}