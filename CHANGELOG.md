# Changelog

All notable changes to this project will be documented in this file.

## [1.1.0] - 2025-10-10

### 🚀 New Features

#### Multi-Board Support System
- **Board Configuration Tool** - Interactive selection of ESP32 variants
- **Automatic Configuration** - Updates platformio.ini, config.h, and project.json
- **9 Supported Boards** - ESP32, ESP32-S2, ESP32-S3, ESP32-C3, ESP32-C6, and specialty boards
- **Smart Pin Mapping** - Automatically configures LED pins for each board
- **PSRAM Detection** - Automatically adds PSRAM flags for supported boards

#### Supported ESP32 Variants
- **ESP32** (Original) - Generic development boards, WROVER-KIT, M5Stack, TTGO T-Display
- **ESP32-S2** - Saola-1 with USB-OTG support
- **ESP32-S3** - DevKitC-1 and BOX with AI acceleration and PSRAM
- **ESP32-C3** - RISC-V development board with WiFi and Bluetooth 5
- **ESP32-C6** - RISC-V with WiFi 6, Bluetooth 5, and Zigbee/Thread

#### Enhanced Development Workflow
- **Interactive Board Selection** - `.\build.ps1 board` for easy configuration
- **Command Line Options** - Direct board configuration and listing
- **Comprehensive Documentation** - Complete board configuration guide
- **Build System Integration** - Seamless integration with existing build tools

### 🔧 Technical Improvements

#### Configuration Management
- **Dynamic platformio.ini Updates** - Board-specific platform, upload speeds, and build flags
- **Smart LED Pin Configuration** - Automatic GPIO pin mapping per board
- **PSRAM Auto-Configuration** - Automatic PSRAM flags for supported boards
- **Project Metadata Updates** - Hardware specifications in project.json

#### Build System Enhancements
- **Source File Filtering** - Excludes example files from compilation
- **Multi-Environment Support** - Production, debug, and OTA builds for each board
- **Cross-Platform Tools** - PowerShell and Make integration

### 📚 Documentation

#### New Documentation
- **Board Configuration Guide** - Comprehensive guide with board comparison
- **Pin Configuration Reference** - LED pins and GPIO usage for each board
- **Board Selection Guide** - When to use each ESP32 variant
- **Troubleshooting Section** - Common issues and solutions

#### Updated Documentation
- **README.md** - Added board configuration to quick start
- **Build Commands** - Updated with board configuration options
- **Development Workflow** - Enhanced with multi-board support

### 🎯 Usage Examples

```bash
# Interactive board selection
.\build.ps1 board

# List available boards
python scripts/board_config.py --list

# Configure specific board
python scripts/board_config.py --board esp32-s3-devkitc-1

# Build for configured board
.\build.ps1 build
```

### 🔄 Backward Compatibility
- **Existing Projects** - Continue to work without changes
- **Default Configuration** - ESP32 development board remains default
- **Gradual Migration** - Optional upgrade to multi-board support

---

## [1.0.0] - 2025-10-10

### ✅ Fixed Critical Issues

#### Missing Core Components
- **Created working `src/main.cpp`** - Replaced broken example with functional ESP32 code
- **Added `lib/` directory structure** - Created custom library framework with example
- **Fixed compilation errors** - Resolved Arduino.h and dependency issues
- **Added proper library dependencies** - Updated platformio.ini with required libraries

#### Development Infrastructure
- **Complete GitHub Actions workflows** - Added CI/CD, release, PR validation, and dependency management
- **Contributing guidelines** - Added comprehensive CONTRIBUTING.md with development workflow
- **Issue and PR templates** - Created structured templates for bug reports and feature requests
- **Workflow validation** - Added script to validate GitHub Actions syntax

#### Documentation & Examples
- **Configuration header** - Added `include/config.h` with centralized project settings
- **Custom library example** - Created ExampleSensor library demonstrating proper structure
- **Advanced example** - Added sensor dashboard example with JSON API
- **Directory documentation** - Added README files for lib/, data/, and config/ directories

#### Project Structure
- **ESPHome integration** - Added config/ directory with ESPHome documentation
- **Data directory** - Created SPIFFS/LittleFS file structure
- **Build validation** - Verified all environments compile successfully

### 🚀 New Features

#### Working Examples
- **Basic LED blink with WiFi** - Simple web server with LED control
- **Sensor dashboard** - Advanced example with custom library integration
- **JSON API endpoint** - RESTful API for sensor data

#### Custom Library Framework
- **ExampleSensor library** - Demonstrates proper library structure
- **Library metadata** - Includes library.json for proper PlatformIO integration
- **Documentation** - Complete usage examples and API documentation

#### Development Tools
- **Build script enhancements** - All PowerShell commands now functional
- **Workflow validation** - Automated GitHub Actions syntax checking
- **Multi-environment builds** - Production, debug, and OTA builds working

#### CI/CD Pipeline
- **Automated builds** - All environments build on every commit
- **Security scanning** - Trivy vulnerability scanning
- **Code quality** - Python linting and formatting checks
- **Automated releases** - Binary artifacts with flash instructions
- **Dependency updates** - Weekly automated dependency management

### 🔧 Technical Improvements

#### Build System
- **Library dependencies** - Added ESP32WebServer and other required libraries
- **Build flags optimization** - Proper debug and production configurations
- **Memory analysis** - Build size and usage reporting
- **Source filtering** - Excludes example files from compilation

#### Code Quality
- **Configuration management** - Centralized config.h with validation macros
- **Error handling** - Proper error checking and recovery
- **Documentation** - Comprehensive code comments and examples

#### CI/CD Pipeline Fixes
- **Fixed GitHub Actions** - Resolved dependency and permission issues
- **Cross-platform testing** - Windows, Linux, and macOS compatibility
- **Updated action versions** - CodeQL v3, latest setup-python, upload-artifact v4
- **Minimal CI requirements** - Separate requirements-ci.txt for reliable builds
- **Proper permissions** - Security-events, contents, and pull-requests permissions

#### Project Organization
- **File structure** - Logical organization of source, libraries, and configuration
- **Template files** - Ready-to-use examples for common scenarios
- **Development workflow** - Clear setup and contribution guidelines

### 📋 What Was Missing (Now Fixed)

1. **No working main source file** ✅ Created functional main.cpp
2. **Missing lib/ directory** ✅ Added with example library
3. **Compilation errors** ✅ Fixed all Arduino.h and dependency issues
4. **No CI/CD workflows** ✅ Complete GitHub Actions pipeline
5. **Missing contributing guidelines** ✅ Comprehensive CONTRIBUTING.md
6. **No configuration examples** ✅ Added config.h and examples
7. **Incomplete setup process** ✅ Validated all build environments
8. **Missing library examples** ✅ ExampleSensor library with documentation

### 🎯 Ready to Use

The project is now fully functional with:
- ✅ Working ESP32 code that compiles and runs
- ✅ Complete development environment setup
- ✅ Professional CI/CD pipeline
- ✅ Comprehensive documentation
- ✅ Example custom library
- ✅ Multiple build environments
- ✅ Web interface and API examples

### 🚀 Quick Start

```bash
# 1. Setup environment
.\build.ps1 setup

# 2. Build project
.\build.ps1 build

# 3. Upload to ESP32
.\build.ps1 upload

# 4. Monitor output
.\build.ps1 monitor
```

The template is now production-ready for ESP32 development projects!