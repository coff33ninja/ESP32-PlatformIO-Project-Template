/**
 * Project Configuration Header
 * 
 * Central configuration file for ESP32 project settings.
 * Modify these values to customize your project behavior.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// PROJECT INFORMATION
// ============================================================================
#define PROJECT_NAME "ESP32 PlatformIO Template"
#define PROJECT_VERSION "1.0.0"
#define PROJECT_AUTHOR "Developer"

// ============================================================================
// HARDWARE CONFIGURATION
// ============================================================================

// LED Configuration
#define LED_PIN 48                    // Board: ESP32-S3-DevKitC-1 (GPIO48)                    // Built-in LED pin (GPIO2 on most ESP32 boards)
#define LED_ACTIVE_HIGH true         // true if LED is active high, false if active low

// Serial Configuration
#define SERIAL_BAUD 115200          // Serial communication baud rate
#define SERIAL_TIMEOUT 1000         // Serial timeout in milliseconds

// ============================================================================
// WIFI CONFIGURATION
// ============================================================================

// Default WiFi credentials (override in wifi_config.h if generated)
#ifndef WIFI_SSID
#define WIFI_SSID "YOUR_WIFI_SSID"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#endif

// WiFi connection settings
#define WIFI_CONNECT_TIMEOUT 20000   // WiFi connection timeout (ms)
#define WIFI_RETRY_DELAY 500        // Delay between connection attempts (ms)
#define WIFI_MAX_RETRIES 40         // Maximum connection retry attempts

// Access Point fallback settings
#define AP_SSID "ESP32-Setup"       // Fallback AP SSID
#define AP_PASSWORD "esp32setup"    // Fallback AP password (min 8 chars)

// ============================================================================
// WEB SERVER CONFIGURATION
// ============================================================================
#define WEB_SERVER_PORT 80          // HTTP server port
#define WEB_SERVER_ENABLED true     // Enable/disable web server

// ============================================================================
// OTA (Over-The-Air) UPDATE CONFIGURATION
// ============================================================================
#define OTA_HOSTNAME "esp32-device" // OTA hostname
#define OTA_PASSWORD "admin"        // OTA update password
#define OTA_PORT 3232              // OTA port

// ============================================================================
// TIMING CONFIGURATION
// ============================================================================
#define LOOP_DELAY 10              // Main loop delay (ms)
#define STATUS_REPORT_INTERVAL 10000 // Status report interval (ms)
#define BLINK_INTERVAL 1000        // LED blink interval (ms)

// ============================================================================
// DEBUG CONFIGURATION
// ============================================================================
#ifdef DEBUG
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
    #define DEBUG_PRINTF(format, ...) Serial.printf(format, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
    #define DEBUG_PRINTF(format, ...)
#endif

// ============================================================================
// FEATURE TOGGLES
// ============================================================================
#define ENABLE_WIFI true           // Enable WiFi functionality
#define ENABLE_WEB_SERVER true     // Enable web server
#define ENABLE_OTA true            // Enable OTA updates
#define ENABLE_SPIFFS true         // Enable SPIFFS filesystem
#define ENABLE_MDNS true           // Enable mDNS responder

// ============================================================================
// SENSOR CONFIGURATION (if using sensors)
// ============================================================================
#define SENSOR_UPDATE_INTERVAL 5000 // Sensor reading interval (ms)
#define SENSOR_PIN A0              // Default analog sensor pin

// ============================================================================
// MEMORY CONFIGURATION
// ============================================================================
#define STACK_SIZE 8192            // Task stack size
#define HEAP_THRESHOLD 10000       // Minimum free heap warning threshold

// ============================================================================
// VALIDATION MACROS
// ============================================================================

// Validate configuration at compile time
#if WIFI_CONNECT_TIMEOUT < 5000
    #warning "WIFI_CONNECT_TIMEOUT is very low, connection may fail"
#endif

#if defined(ENABLE_WEB_SERVER) && ENABLE_WEB_SERVER && !defined(ENABLE_WIFI)
    #error "Web server requires WiFi to be enabled"
#endif

#if defined(ENABLE_OTA) && ENABLE_OTA && !defined(ENABLE_WIFI)
    #error "OTA updates require WiFi to be enabled"
#endif

// ============================================================================
// UTILITY MACROS
// ============================================================================
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// String helpers
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// ============================================================================
// VERSION INFORMATION
// ============================================================================
#define BUILD_TIMESTAMP __DATE__ " " __TIME__

// Create version string
#define VERSION_STRING PROJECT_NAME " v" PROJECT_VERSION " (" BUILD_TIMESTAMP ")"

#endif // CONFIG_H