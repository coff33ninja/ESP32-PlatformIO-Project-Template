# ESPHome Configuration Directory

This directory contains ESPHome device configuration files for Home Assistant integration.

## Quick Start with ESPHome

### 1. Launch ESPHome Dashboard
```bash
# PowerShell
.\build.ps1 esphome

# Python
python scripts/esphome_dashboard.py
```

### 2. Access Web Interface
Open your browser to: `http://localhost:6052`

### 3. Create Your First Device
1. Click "New Device" in the web interface
2. Enter device name (e.g., "my-esp32")
3. Select "ESP32" as device type
4. Enter WiFi credentials
5. Click "Install" and choose "Manual download"

### 4. Configuration Files
ESPHome will create YAML files in this directory:
- `my-esp32.yaml` - Main device configuration
- `secrets.yaml` - WiFi passwords and API keys (auto-generated)

## Example Configuration

### Basic ESP32 Device (`example-device.yaml`)
```yaml
esphome:
  name: example-device
  platform: ESP32
  board: esp32dev

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  
  # Enable fallback hotspot
  ap:
    ssid: "Example-Device Fallback"
    password: !secret ap_password

# Enable logging
logger:

# Enable Home Assistant API
api:
  encryption:
    key: !secret api_encryption_key

# Enable over-the-air updates
ota:
  password: !secret ota_password

# Web server for device management
web_server:
  port: 80

# Example: Built-in LED control
light:
  - platform: monochromatic
    output: builtin_led
    name: "Built-in LED"

output:
  - platform: ledc
    pin: GPIO2
    id: builtin_led

# Example: Temperature sensor (if connected)
sensor:
  - platform: dht
    pin: GPIO4
    temperature:
      name: "Temperature"
    humidity:
      name: "Humidity"
    update_interval: 60s

# Example: Button input
binary_sensor:
  - platform: gpio
    pin:
      number: GPIO0
      inverted: true
    name: "Boot Button"
```

### Secrets File (`secrets.yaml`)
```yaml
# WiFi credentials
wifi_ssid: "Your_WiFi_Network"
wifi_password: "your_wifi_password"

# Access point fallback
ap_password: "fallback_password"

# API encryption key (auto-generated)
api_encryption_key: "your_32_character_encryption_key"

# OTA update password
ota_password: "your_ota_password"
```

## ESPHome vs PlatformIO

### When to Use ESPHome
- **Home Assistant integration**: Native HA discovery and control
- **Quick prototyping**: YAML-based configuration is faster
- **Standard sensors**: Built-in support for common components
- **Web interface**: Easy device management
- **OTA updates**: Wireless firmware updates

### When to Use PlatformIO
- **Custom logic**: Complex algorithms and custom protocols
- **Performance critical**: Low-level optimization needed
- **Third-party libraries**: Integration with specific libraries
- **Advanced debugging**: Full debugging capabilities
- **Custom hardware**: Unusual or custom hardware configurations

## Common Components

### Sensors
```yaml
sensor:
  # Temperature/Humidity
  - platform: dht
    pin: GPIO4
    temperature:
      name: "Temperature"
    humidity:
      name: "Humidity"
  
  # Analog input
  - platform: adc
    pin: A0
    name: "Analog Input"
    update_interval: 5s
```

### Switches and Lights
```yaml
switch:
  - platform: gpio
    pin: GPIO5
    name: "Relay 1"

light:
  - platform: rgb
    name: "RGB LED"
    red: pwm_r
    green: pwm_g
    blue: pwm_b
```

### Binary Sensors
```yaml
binary_sensor:
  - platform: gpio
    pin:
      number: GPIO0
      inverted: true
    name: "Button"
```

## Advanced Features

### Custom Components
```yaml
# Include custom C++ code
esphome:
  includes:
    - custom_component.h
  libraries:
    - "SomeLibrary"
```

### Automation
```yaml
# Device-level automation
automation:
  - trigger:
      - platform: state
        entity_id: binary_sensor.button
        to: 'on'
    action:
      - light.toggle: builtin_led
```

## Deployment Workflow

### 1. Development
1. Edit YAML configuration files
2. Use ESPHome dashboard for validation
3. Test with "Validate" button

### 2. Installation
1. **First install**: Use "Install" → "Manual download"
2. **Updates**: Use "Install" → "Wirelessly" (if OTA enabled)
3. **Manual flash**: Download .bin file and use esptool

### 3. Integration
1. Device appears in Home Assistant automatically
2. Configure entities in HA interface
3. Add to dashboards and automations

## Troubleshooting

### Common Issues
- **WiFi connection fails**: Check credentials in secrets.yaml
- **Compilation errors**: Validate YAML syntax
- **OTA fails**: Ensure device is on same network
- **HA integration missing**: Check API configuration

### Debug Tools
- **ESPHome logs**: View in dashboard during compilation
- **Device logs**: Use "Logs" button in dashboard
- **Serial monitor**: Connect via USB for direct debugging

## File Organization
```
config/
├── README.md              # This file
├── secrets.yaml           # WiFi and API credentials
├── device1.yaml          # First device configuration
├── device2.yaml          # Second device configuration
└── common/               # Shared configurations
    ├── wifi.yaml         # Common WiFi setup
    └── base.yaml         # Base device configuration
```

## Resources
- [ESPHome Documentation](https://esphome.io/)
- [Component Reference](https://esphome.io/components/)
- [Home Assistant Integration](https://www.home-assistant.io/integrations/esphome/)
- [Community Forum](https://community.home-assistant.io/c/esphome/)