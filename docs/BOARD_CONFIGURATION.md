# ESP32 Board Configuration Guide

This template supports multiple ESP32 boards and chipsets with automatic configuration. The board configuration tool updates `platformio.ini`, `include/config.h`, and `project.json` to match your specific hardware.

## 🚀 Quick Start

### Interactive Configuration
```bash
# PowerShell
.\build.ps1 board

# Make
make board

# Python directly
python scripts/board_config.py --interactive
```

### Command Line Configuration
```bash
# List available boards
python scripts/board_config.py --list

# Configure specific board
python scripts/board_config.py --board esp32-s3-devkitc-1
```

## 📋 Supported Boards

### ESP32 (Original)
- **esp32dev** - Generic ESP32 development board
- **esp32-wrover-kit** - ESP32-WROVER with PSRAM and camera support
- **m5stack-core-esp32** - M5Stack Core with display and peripherals
- **ttgo-t-display** - TTGO T-Display with built-in TFT

### ESP32-S2 (USB-OTG, Single Core)
- **esp32-s2-saola-1** - ESP32-S2 development board with USB-OTG

### ESP32-S3 (Dual Core + AI)
- **esp32-s3-devkitc-1** - ESP32-S3 with WiFi, Bluetooth, and AI acceleration
- **esp32-s3-box** - ESP32-S3-BOX AI development board with display

### ESP32-C3 (RISC-V)
- **esp32-c3-devkitm-1** - ESP32-C3 RISC-V with WiFi and Bluetooth 5

### ESP32-C6 (RISC-V + WiFi 6)
- **esp32-c6-devkitc-1** - ESP32-C6 with WiFi 6, Bluetooth 5, Zigbee/Thread

## 🔧 What Gets Updated

### platformio.ini
- Board type and platform
- Upload and monitor speeds
- PSRAM configuration (if supported)
- Build flags and optimizations
- Environment names

### include/config.h
- LED pin definitions
- Board-specific constants
- Hardware feature flags

### project.json
- Hardware specifications
- Board metadata
- Development environment names

## 📊 Board Comparison

| Board | Chipset | Cores | WiFi | Bluetooth | PSRAM | Flash | Special Features |
|-------|---------|-------|------|-----------|-------|-------|------------------|
| ESP32 Dev | ESP32 | 2 | 2.4GHz | Classic + BLE | Optional | 4MB | General purpose |
| ESP32-S2 | ESP32-S2 | 1 | 2.4GHz | No | No | 4MB | USB-OTG, Security |
| ESP32-S3 | ESP32-S3 | 2 | 2.4GHz | BLE 5.0 | Yes | 8MB | AI acceleration |
| ESP32-C3 | ESP32-C3 | 1 | 2.4GHz | BLE 5.0 | No | 4MB | RISC-V, Small size |
| ESP32-C6 | ESP32-C6 | 1 | WiFi 6 | BLE 5.0 | No | 8MB | WiFi 6, Zigbee/Thread |

## 🎯 Board Selection Guide

### Choose ESP32 (Original) if:
- ✅ You need dual-core processing
- ✅ Maximum compatibility with libraries
- ✅ General-purpose IoT projects
- ✅ Cost-effective solution

### Choose ESP32-S2 if:
- ✅ You need USB-OTG functionality
- ✅ Security features are important
- ✅ Single-core is sufficient
- ✅ Lower power consumption needed

### Choose ESP32-S3 if:
- ✅ You need AI/ML acceleration
- ✅ Camera or image processing
- ✅ High-performance applications
- ✅ Large PSRAM requirements

### Choose ESP32-C3 if:
- ✅ You prefer RISC-V architecture
- ✅ Small form factor needed
- ✅ Cost optimization important
- ✅ Simple IoT applications

### Choose ESP32-C6 if:
- ✅ You need WiFi 6 support
- ✅ Zigbee/Thread connectivity
- ✅ Future-proof networking
- ✅ Matter/Thread applications

## 🔌 Pin Configurations

### LED Pins by Board
- **ESP32 Dev**: GPIO2 (built-in LED)
- **ESP32-S2**: GPIO18
- **ESP32-S3**: GPIO48 (RGB LED)
- **ESP32-C3**: GPIO8
- **ESP32-C6**: GPIO8
- **M5Stack**: GPIO2
- **TTGO T-Display**: GPIO2

### Common GPIO Usage
```cpp
// The config.h file is automatically updated with correct pins
#include "config.h"

void setup() {
    pinMode(LED_PIN, OUTPUT);  // Automatically correct for your board
    // LED_PIN is defined based on selected board
}
```

## 🛠️ Advanced Configuration

### Custom Board Addition
To add a new board, edit `scripts/board_config.py`:

```python
BOARD_CONFIGS["your-board"] = {
    "name": "Your Custom Board",
    "platform": "espressif32",
    "board": "your-platformio-board-id",
    "framework": "arduino",
    "upload_speed": 921600,
    "monitor_speed": 115200,
    "flash_size": "4MB",
    "psram": False,
    "led_pin": 2,
    "description": "Your board description"
}
```

### Manual Configuration
If you prefer manual configuration, edit `platformio.ini` directly:

```ini
[env:custom-board]
platform = espressif32
board = your-board-id
framework = arduino
build_flags = 
    -DCORE_DEBUG_LEVEL=0
    ; Add PSRAM flags if needed:
    ; -DBOARD_HAS_PSRAM
    ; -mfix-esp32-psram-cache-issue
```

## 🚨 Troubleshooting

### Board Not Detected
```bash
# Check available boards in PlatformIO
pio boards espressif32

# List boards supported by this template
python scripts/board_config.py --list
```

### Upload Issues
1. **Check USB drivers** - Install CP210x or CH340 drivers
2. **Verify port** - Update `upload_port` in platformio.ini
3. **Boot mode** - Hold BOOT button while uploading (some boards)
4. **Reset after upload** - Press RESET button after successful upload

### Compilation Errors
1. **Update PlatformIO** - `pio upgrade`
2. **Clean build** - `pio run --target clean`
3. **Check board compatibility** - Some libraries may not support all boards
4. **PSRAM issues** - Disable PSRAM flags if not needed

## 📚 Examples

### Basic Board Configuration
```bash
# Interactive selection
python scripts/board_config.py --interactive

# Select ESP32-S3
# Updates all configuration files automatically
# Ready to build and upload
```

### Development Workflow
```bash
# 1. Configure board
.\build.ps1 board

# 2. Build for selected board
.\build.ps1 build

# 3. Upload to device
.\build.ps1 upload

# 4. Monitor output
.\build.ps1 monitor
```

### Multi-Board Development
```bash
# Configure for ESP32-S3
python scripts/board_config.py --board esp32-s3-devkitc-1

# Build and test
pio run -e esp32-s3-devkitc-1

# Switch to ESP32-C3
python scripts/board_config.py --board esp32-c3-devkitm-1

# Build for different target
pio run -e esp32-c3-devkitm-1
```

## 🔗 Resources

- [ESP32 Series Comparison](https://www.espressif.com/en/products/socs)
- [PlatformIO Board Explorer](https://platformio.org/boards/espressif32)
- [ESP32 Hardware Design Guidelines](https://www.espressif.com/sites/default/files/documentation/esp32_hardware_design_guidelines_en.pdf)
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)

---

The board configuration system makes it easy to switch between different ESP32 variants while maintaining a consistent development experience. Choose the right board for your project needs and let the tool handle the configuration details!