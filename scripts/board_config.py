#!/usr/bin/env python3
"""
ESP32 Board Configuration Tool
Dynamically configures platformio.ini for different ESP32 boards and chipsets
"""

import json
import os
import sys
from pathlib import Path
import argparse

# Supported ESP32 boards and their configurations
BOARD_CONFIGS = {
    "esp32dev": {
        "name": "ESP32 Development Board (Generic)",
        "platform": "espressif32",
        "board": "esp32dev",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "4MB",
        "psram": False,
        "led_pin": 2,
        "description": "Generic ESP32 development board (NodeMCU-32S, DevKit, etc.)"
    },
    "esp32-s2-saola-1": {
        "name": "ESP32-S2-Saola-1",
        "platform": "espressif32",
        "board": "esp32-s2-saola-1",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "4MB",
        "psram": False,
        "led_pin": 18,
        "description": "ESP32-S2 development board with USB-OTG support"
    },
    "esp32-s3-devkitc-1": {
        "name": "ESP32-S3-DevKitC-1",
        "platform": "espressif32",
        "board": "esp32-s3-devkitc-1",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "8MB",
        "psram": True,
        "led_pin": 48,
        "description": "ESP32-S3 development board with WiFi, Bluetooth, and AI acceleration"
    },
    "esp32-c3-devkitm-1": {
        "name": "ESP32-C3-DevKitM-1",
        "platform": "espressif32",
        "board": "esp32-c3-devkitm-1",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "4MB",
        "psram": False,
        "led_pin": 8,
        "description": "ESP32-C3 RISC-V development board with WiFi and Bluetooth 5"
    },
    "esp32-c6-devkitc-1": {
        "name": "ESP32-C6-DevKitC-1",
        "platform": "espressif32",
        "board": "esp32-c6-devkitc-1",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "8MB",
        "psram": False,
        "led_pin": 8,
        "description": "ESP32-C6 RISC-V development board with WiFi 6, Bluetooth 5, and Zigbee/Thread"
    },
    "esp32-s3-box": {
        "name": "ESP32-S3-BOX",
        "platform": "espressif32",
        "board": "esp32-s3-box",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "16MB",
        "psram": True,
        "led_pin": 47,
        "description": "ESP32-S3-BOX AI development board with display and audio"
    },
    "esp32-wrover-kit": {
        "name": "ESP32-WROVER-KIT",
        "platform": "espressif32",
        "board": "esp32-wrover-kit",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "4MB",
        "psram": True,
        "led_pin": 2,
        "description": "ESP32-WROVER development board with PSRAM and camera support"
    },
    "ttgo-t-display": {
        "name": "TTGO T-Display",
        "platform": "espressif32",
        "board": "ttgo-t1",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "4MB",
        "psram": False,
        "led_pin": 2,
        "description": "TTGO T-Display ESP32 with built-in TFT display"
    },
    "m5stack-core-esp32": {
        "name": "M5Stack Core",
        "platform": "espressif32",
        "board": "m5stack-core-esp32",
        "framework": "arduino",
        "upload_speed": 921600,
        "monitor_speed": 115200,
        "flash_size": "16MB",
        "psram": True,
        "led_pin": 2,
        "description": "M5Stack Core development kit with display, buttons, and speaker"
    }
}

def list_boards():
    """List all available board configurations"""
    print("Available ESP32 Boards:")
    print("=" * 50)
    
    for board_id, config in BOARD_CONFIGS.items():
        print(f"🔧 {board_id}")
        print(f"   Name: {config['name']}")
        print(f"   Flash: {config['flash_size']}")
        print(f"   PSRAM: {'Yes' if config['psram'] else 'No'}")
        print(f"   LED Pin: GPIO{config['led_pin']}")
        print(f"   Description: {config['description']}")
        print()

def update_platformio_ini(board_id):
    """Update platformio.ini with selected board configuration"""
    if board_id not in BOARD_CONFIGS:
        print(f"❌ Unknown board: {board_id}")
        return False
    
    config = BOARD_CONFIGS[board_id]
    platformio_ini = Path("platformio.ini")
    
    if not platformio_ini.exists():
        print("❌ platformio.ini not found!")
        return False
    
    # Read current platformio.ini
    with open(platformio_ini, 'r') as f:
        content = f.read()
    
    # Update the main environment section
    lines = content.split('\n')
    new_lines = []
    in_env_section = False
    
    for line in lines:
        if line.strip().startswith('[env:esp32dev]'):
            in_env_section = True
            new_lines.append(f'[env:{board_id}]')
        elif line.strip().startswith('[') and in_env_section:
            in_env_section = False
            new_lines.append(line)
        elif in_env_section:
            if line.startswith('platform ='):
                new_lines.append(f'platform = {config["platform"]}')
            elif line.startswith('board ='):
                new_lines.append(f'board = {config["board"]}')
            elif line.startswith('upload_speed ='):
                new_lines.append(f'upload_speed = {config["upload_speed"]}')
            elif line.startswith('monitor_speed ='):
                new_lines.append(f'monitor_speed = {config["monitor_speed"]}')
            else:
                new_lines.append(line)
        else:
            new_lines.append(line)
    
    # Update default environment
    for i, line in enumerate(new_lines):
        if line.startswith('default_envs ='):
            new_lines[i] = f'default_envs = {board_id}'
            break
    
    # Add PSRAM configuration if needed
    if config['psram']:
        for i, line in enumerate(new_lines):
            if 'build_flags =' in line and f'[env:{board_id}]' in new_lines[max(0, i-10):i]:
                # Find the build_flags section and add PSRAM flags
                j = i + 1
                while j < len(new_lines) and not new_lines[j].strip().startswith('['):
                    if new_lines[j].strip() and not new_lines[j].startswith(' ') and not new_lines[j].startswith('\t'):
                        break
                    j += 1
                
                # Insert PSRAM flags
                psram_flags = [
                    '    -DBOARD_HAS_PSRAM',
                    '    -mfix-esp32-psram-cache-issue'
                ]
                
                # Check if PSRAM flags already exist
                build_section = new_lines[i:j]
                has_psram = any('-DBOARD_HAS_PSRAM' in line for line in build_section)
                
                if not has_psram:
                    new_lines[i+1:i+1] = psram_flags
                break
    
    # Write updated platformio.ini
    with open(platformio_ini, 'w') as f:
        f.write('\n'.join(new_lines))
    
    print(f"✅ Updated platformio.ini for {config['name']}")
    return True

def update_config_header(board_id):
    """Update include/config.h with board-specific settings"""
    if board_id not in BOARD_CONFIGS:
        return False
    
    config = BOARD_CONFIGS[board_id]
    config_header = Path("include/config.h")
    
    if not config_header.exists():
        print("⚠️  include/config.h not found, skipping header update")
        return True
    
    # Read current config.h
    with open(config_header, 'r') as f:
        content = f.read()
    
    # Update LED pin definition
    content = content.replace(
        '#define LED_PIN 2',
        f'#define LED_PIN {config["led_pin"]}'
    )
    
    # Add board-specific comment
    board_comment = f'// Board: {config["name"]} (GPIO{config["led_pin"]})'
    if board_comment not in content:
        content = content.replace(
            f'#define LED_PIN {config["led_pin"]}',
            f'#define LED_PIN {config["led_pin"]}                    {board_comment}'
        )
    
    # Write updated config.h
    with open(config_header, 'w') as f:
        f.write(content)
    
    print(f"✅ Updated include/config.h for GPIO{config['led_pin']}")
    return True

def update_project_json(board_id):
    """Update project.json with board information"""
    if board_id not in BOARD_CONFIGS:
        return False
    
    config = BOARD_CONFIGS[board_id]
    project_json = Path("project.json")
    
    if not project_json.exists():
        print("⚠️  project.json not found, skipping project update")
        return True
    
    # Read and update project.json
    with open(project_json, 'r') as f:
        project_data = json.load(f)
    
    # Update hardware section
    if 'hardware' not in project_data:
        project_data['hardware'] = {}
    
    project_data['hardware'].update({
        'platform': config['platform'],
        'board': config['board'],
        'board_name': config['name'],
        'flash_size': config['flash_size'],
        'psram': config['psram'],
        'led_pin': config['led_pin']
    })
    
    # Update development environments
    if 'development' in project_data and 'environments' in project_data['development']:
        project_data['development']['environments'].update({
            'production': board_id,
            'debug': f'{board_id}_debug',
            'ota': f'{board_id}_ota'
        })
    
    # Write updated project.json
    with open(project_json, 'w') as f:
        json.dump(project_data, f, indent=2)
    
    print(f"✅ Updated project.json for {config['name']}")
    return True

def interactive_selection():
    """Interactive board selection"""
    print("🔧 ESP32 Board Configuration Tool")
    print("=" * 40)
    
    # Show available boards
    boards = list(BOARD_CONFIGS.keys())
    for i, board_id in enumerate(boards, 1):
        config = BOARD_CONFIGS[board_id]
        print(f"{i:2d}. {config['name']}")
        print(f"    ID: {board_id}")
        print(f"    Flash: {config['flash_size']}, PSRAM: {'Yes' if config['psram'] else 'No'}")
        print()
    
    while True:
        try:
            choice = input("Select board number (1-{}): ".format(len(boards)))
            if choice.lower() in ['q', 'quit', 'exit']:
                return None
            
            board_index = int(choice) - 1
            if 0 <= board_index < len(boards):
                return boards[board_index]
            else:
                print("❌ Invalid selection. Please try again.")
        except ValueError:
            print("❌ Please enter a valid number.")
        except KeyboardInterrupt:
            print("\n👋 Cancelled by user")
            return None

def main():
    """Main function"""
    parser = argparse.ArgumentParser(description="ESP32 Board Configuration Tool")
    parser.add_argument("--list", "-l", action="store_true", help="List available boards")
    parser.add_argument("--board", "-b", help="Board ID to configure")
    parser.add_argument("--interactive", "-i", action="store_true", help="Interactive board selection")
    
    args = parser.parse_args()
    
    if args.list:
        list_boards()
        return
    
    board_id = None
    
    if args.board:
        board_id = args.board
    elif args.interactive or len(sys.argv) == 1:
        board_id = interactive_selection()
    else:
        parser.print_help()
        return
    
    if not board_id:
        return
    
    if board_id not in BOARD_CONFIGS:
        print(f"❌ Unknown board: {board_id}")
        print("Use --list to see available boards")
        return
    
    config = BOARD_CONFIGS[board_id]
    print(f"\n🔧 Configuring for: {config['name']}")
    print(f"Board ID: {board_id}")
    print(f"Platform: {config['platform']}")
    print(f"Flash Size: {config['flash_size']}")
    print(f"PSRAM: {'Yes' if config['psram'] else 'No'}")
    print(f"LED Pin: GPIO{config['led_pin']}")
    print()
    
    # Update configuration files
    success = True
    success &= update_platformio_ini(board_id)
    success &= update_config_header(board_id)
    success &= update_project_json(board_id)
    
    if success:
        print(f"\n✅ Successfully configured for {config['name']}!")
        print("\nNext steps:")
        print(f"1. Build: pio run -e {board_id}")
        print(f"2. Upload: pio run -e {board_id} --target upload")
        print("3. Monitor: pio device monitor")
        print("\nOr use the build script:")
        print("  .\\build.ps1 build")
        print("  .\\build.ps1 upload")
    else:
        print("\n❌ Configuration failed!")
        sys.exit(1)

if __name__ == "__main__":
    main()