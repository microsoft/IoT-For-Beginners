<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T03:52:33+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "pa"
}
-->
# Troubleshooting Guide

This guide helps you solve common problems when working with the IoT for Beginners curriculum. Issues are organized by category for easy navigation.

## Table of Contents

- [Installation Issues](../..)
  - [Python Installation](../..)
  - [VS Code and Extensions](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove Libraries](../..)
- [Hardware Issues](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtual Device (CounterFit)](../..)
- [Connectivity Issues](../..)
  - [WiFi Connection](../..)
  - [Cloud Services](../..)
  - [MQTT](../..)
- [Sensor and Actuator Issues](../..)
  - [Grove Sensors](../..)
  - [Camera](../..)
  - [Microphone and Speaker](../..)
- [Development Environment Issues](../..)
  - [VS Code](../..)
  - [Python Virtual Environments](../..)
  - [Dependencies](../..)
- [Performance Issues](../..)
- [Common Error Messages](../..)
- [Getting Help](../..)

---

## Installation Issues

### Python Installation

#### Problem: Python version is too old
**Error:** `Python 3.6 or higher is required`

**Solution:**
1. Download the latest Python 3 from [python.org](https://www.python.org/downloads/)
2. During installation on Windows, check "Add Python to PATH"
3. Verify installation:
   ```bash
   python3 --version
   ```

#### Problem: Multiple Python versions causing conflicts
**Symptoms:** Wrong Python version runs, packages install to wrong location

**Solution:**
- **Windows:** Use `py -3` instead of `python` to explicitly call Python 3
- **macOS/Linux:** Use `python3` instead of `python`
- Always create and use virtual environments for projects

#### Problem: pip command not found
**Error:** `'pip' is not recognized as an internal or external command`

**Solution:**
1. Try `pip3` instead of `pip`
2. Or use `python -m pip` or `python3 -m pip`
3. Ensure Python is added to PATH (reinstall Python and check the option)

### VS Code and Extensions

#### Problem: Pylance extension not working
**Symptoms:** No Python IntelliSense, code completion, or type checking

**Solution:**
1. Open VS Code Command Palette (`Ctrl+Shift+P` or `Cmd+Shift+P`)
2. Run "Python: Select Interpreter"
3. Choose the correct Python interpreter (virtual environment if using one)
4. Reload VS Code window

#### Problem: VS Code not detecting virtual environment
**Symptoms:** Wrong Python interpreter selected

**Solution:**
1. Ensure you've activated the virtual environment in the terminal
2. Open Command Palette and run "Python: Select Interpreter"
3. Select the interpreter from `.venv` folder
4. Check the status bar (bottom left) shows the correct Python version

### PlatformIO (Wio Terminal)

#### Problem: PlatformIO installation fails
**Error:** Various errors during PlatformIO installation

**Solution:**
1. Ensure VS Code is up to date
2. Install the C/C++ extension first
3. Restart VS Code after installing PlatformIO
4. Check your internet connection (PlatformIO downloads large files)

#### Problem: Board not detected by PlatformIO
**Symptoms:** Cannot upload code to Wio Terminal

**Solution:**
1. Try a different USB cable (some cables are charge-only)
2. Check Device Manager (Windows) or `ls /dev/tty*` (macOS/Linux)
3. Install or update USB drivers
4. Try a different USB port
5. Slide the power switch on the Wio Terminal twice quickly to enter bootloader mode

#### Problem: Compilation errors in PlatformIO
**Error:** `fatal error: Arduino.h: No such file or directory`

**Solution:**
1. Delete `.pio` folder in your project
2. Run "PlatformIO: Rebuild" from Command Palette
3. Ensure `platformio.ini` has correct board configuration:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove Libraries

#### Problem: Grove library import fails on Raspberry Pi
**Error:** `ModuleNotFoundError: No module named 'grove'`

**Solution:**
1. Reinstall Grove libraries:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. If using virtual environment, you may need to install globally or copy libraries
3. Verify I2C is enabled: `sudo raspi-config nonint do_i2c 0`

#### Problem: Grove sensor not detected
**Error:** `IOError: [Errno 121] Remote I/O error`

**Solution:**
1. Check physical connections (ensure Grove cable is fully inserted)
2. Verify sensor is connected to correct port (analog, digital, I2C, UART)
3. Run `i2cdetect -y 1` to see if device appears on I2C bus
4. Try a different Grove cable
5. Ensure Grove Base Hat is properly seated on Raspberry Pi GPIO pins

---

## Hardware Issues

### Raspberry Pi

#### Problem: Raspberry Pi won't boot
**Symptoms:** No display, no LED activity, or rainbow screen

**Solution:**
1. **Check power supply:** Use official 5V 3A USB-C power supply for Pi 4
2. **SD card issues:** 
   - Reformat SD card and reinstall Raspberry Pi OS
   - Try a different SD card (use recommended brands)
   - Ensure SD card is properly inserted
3. **Check HDMI connection:** Try both HDMI ports on Pi 4, use HDMI port closest to power

#### Problem: Cannot SSH to Raspberry Pi
**Symptoms:** Connection refused or timeout

**Solution:**
1. Enable SSH:
   - When flashing SD card with Raspberry Pi Imager, configure SSH in advanced options
   - Or create empty file named `ssh` (no extension) in boot partition
2. Find Pi's IP address:
   - Check your router's connected devices
   - Use `ping raspberrypi.local` (if mDNS works)
   - Use network scanning tools like `nmap` or Angry IP Scanner
3. Check network:
   - Ensure Pi is on same network as your computer
   - Try ethernet connection instead of WiFi
4. Verify username/password (default: username `pi`, password `raspberry`)

#### Problem: Grove Base Hat not recognized
**Symptoms:** Sensors not working, I2C errors

**Solution:**
1. Ensure Base Hat is properly seated on all GPIO pins
2. Check for bent pins on Pi or Base Hat
3. Enable I2C interface:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Verify I2C is working: `i2cdetect -y 1`

#### Problem: Raspberry Pi running slow
**Symptoms:** Laggy UI, slow response

**Solution:**
1. Check SD card speed (use Class 10 or better, or SSD via USB)
2. Free up disk space: `df -h` to check, delete unnecessary files
3. Reduce GPU memory in `raspi-config` if not using camera/display heavily
4. Close unnecessary applications
5. Consider upgrading to Pi 4 with more RAM if using Pi 3 or older

### Wio Terminal

#### Problem: Wio Terminal screen stays blank
**Symptoms:** No display output after uploading code

**Solution:**
1. Check if code initializes the display (TFT_eSPI library)
2. Update Wio Terminal firmware from [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Add display initialization code:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Try uploading example sketch from PlatformIO to test hardware

#### Problem: WiFi not working on Wio Terminal
**Symptoms:** Cannot connect to WiFi, network errors

**Solution:**
1. **Update WiFi firmware:** Follow [Wio Terminal WiFi firmware update guide](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Check WiFi credentials:** Ensure SSID and password are correct
3. **WiFi band:** Wio Terminal only supports 2.4GHz WiFi (not 5GHz)
4. **Signal strength:** Move closer to router
5. **Router settings:** Some enterprise/WPA-Enterprise networks may not work

#### Problem: Wio Terminal not recognized by computer
**Symptoms:** USB device not detected

**Solution:**
1. **Try different USB cable:** Use data cable, not charge-only cable
2. **Enter bootloader mode:** Slide power switch down twice quickly
   - Blue LED should pulse, device appears as "Arduino" in Device Manager
3. **Install drivers (Windows):**
   - Download and install [Seeed USB driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Try different USB port:** Avoid USB hubs, use direct connection
5. **Update system USB drivers**

#### Problem: Sensors not working on Wio Terminal
**Symptoms:** Grove sensors not reading data

**Solution:**
1. Check Grove cable connections
2. Verify you're using correct Grove port (left or right)
3. Include correct libraries for sensor
4. Check sensor power requirements
5. Test sensor with example code from library

### Virtual Device (CounterFit)

#### Problem: CounterFit app won't start
**Error:** Various Python errors when starting CounterFit

**Solution:**
1. Ensure virtual environment is activated
2. Install/reinstall CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Check port 5000 is not already in use:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Kill process using port 5000 or use different port:
   ```bash
   counterfit --port 5001
   ```

#### Problem: Cannot connect to CounterFit from code
**Error:** Connection refused or timeout

**Solution:**
1. Verify CounterFit is running: Open browser to `http://127.0.0.1:5000`
2. Check connection URL in code matches CounterFit address
3. Ensure firewall isn't blocking connection
4. Try restarting both CounterFit app and your code

#### Problem: Sensors not appearing in CounterFit
**Symptoms:** Created sensors don't show in CounterFit UI

**Solution:**
1. Create sensors in CounterFit UI before running code
2. Refresh browser page
3. Check sensor type matches what code expects
4. Clear browser cache

---

## Connectivity Issues

### WiFi Connection

#### Problem: Device can't connect to WiFi
**Symptoms:** Connection timeout, authentication failed

**Solution:**
1. **Check SSID and password:** Verify credentials are correct
2. **WiFi band:** Most IoT devices only support 2.4GHz (not 5GHz)
3. **Router settings:**
   - Disable AP isolation if enabled
   - Use WPA2-PSK security (avoid WPA3, WEP, or open networks)
   - Ensure DHCP is enabled
4. **Hidden networks:** If SSID is hidden, you may need to explicitly configure it
5. **Signal strength:** Move device closer to router
6. **Interference:** Other devices, microwaves, or walls can interfere

#### Problem: WiFi connection drops frequently
**Symptoms:** Intermittent connectivity

**Solution:**
1. Check router stability and consider reboot
2. Update device firmware
3. Use static IP instead of DHCP
4. Reduce distance to router or add WiFi extender
5. Check for interference from other devices
6. Verify power supply is adequate (especially for Raspberry Pi)

### Cloud Services

#### Problem: Cannot connect to Azure IoT Hub
**Error:** Authentication failed, connection refused

**Solution:**
1. **Verify credentials:**
   - Check connection string is correct
   - Ensure no extra spaces or line breaks in connection string
2. **Check device registration:** Device must be registered in IoT Hub
3. **Firewall/proxy:** Ensure outbound MQTT (port 8883) or HTTPS (port 443) is allowed
4. **IoT Hub region:** Ensure IoT Hub is running and not in different region causing latency
5. **Quota limits:** Check if free tier limits are exceeded
6. **Test connection:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problem: Azure Functions not triggering
**Symptoms:** Messages sent but function doesn't execute

**Solution:**
1. Check Function App is running (not stopped)
2. Verify connection string in Function App settings
3. Check function logs in Azure Portal
4. Ensure Event Hub compatible endpoint is configured correctly
5. Verify message format matches function expectations
6. Check Function App service plan (consumption vs. dedicated)

### MQTT
#### ਸਮੱਸਿਆ: MQTT ਕਨੈਕਸ਼ਨ ਫੇਲ
**ਗਲਤੀ:** ਕਨੈਕਸ਼ਨ ਵਾਪਸ ਠੁੱਕੀ ਗਈ, ਪ੍ਰਮਾਣਿਕਤਾ ਅਸਫਲ

**ਹੱਲ:**
1. **ਬ੍ਰੋਕਰ ਐਡਰੈੱਸ:** ਬ੍ਰੋਕਰ URL/IP ਸਹੀ ਹੈ ਜਾਂ ਨਹੀਂ ਜਾਂਚੋ
2. **ਪੋਰਟ:** ਪੋਰਟ ਨੰਬਰ ਚੈੱਕ ਕਰੋ (1883 ਗੇੜਾ ਲੇਖਨ ਲਈ, 8883 TLS ਲਈ)
3. **ਪ੍ਰਮਾਣਿਕਤਾ:** ਜੇ ਲੋੜ ਹੈ ਤਾਂ ਯੂਜ਼ਰਨਾਮ/ਪਾਸਵਰਡ ਦੀ ਜਾਂਚ ਕਰੋ
4. **TLS/SSL:** ਸਰਟੀਫਿਕੇਟ ਵੈਧ ਅਤੇ ਭਰੋਸੇਯੋਗ ਹੋਣ ਯਕੀਨੀ ਬਣਾਓ
5. **ਫਾਇਰਵਾਲ:** ਪੋਰਟ ਰੋਕਿਆ ਨਹੀਂ ਗਿਆ ਹੈ ਜਾਂ ਨਹੀਂ ਜਾਂਚੋ
6. **MQTT ਕਲਾਇੰਟ ਨਾਲ ਟੈਸਟ ਕਰੋ:** MQTT Explorer ਜਾਂ mosquitto_pub/sub ਨਾਲ ਟੈਸਟ ਕਰੋ

#### ਸਮੱਸਿਆ: MQTT ਸੁਨੇਹੇ ਪ੍ਰਾਪਤ ਨਹੀਂ ਹੋ ਰਹੇ
**ਲੱਛਣ:** ਸੁਨੇਹੇ ਪ੍ਰਕਾਸ਼ਿਤ ਕੀਤੇ ਗਏ ਪਰ ਗ੍ਰਾਹਕਾਂ ਨੂੰ ਨਹੀਂ ਮਿਲ ਰਹੇ

**ਹੱਲ:**
1. **ਟਾਪਿਕ ਨਾਮ:** ਗ੍ਰਾਹਕ ਟਾਪਿਕ ਪਬਲਿਸ਼ਰ ਟਾਪਿਕ ਨਾਲ ਬਿਲਕੁਲ ਮੇਲ ਖਾਂਦਾ ਹੈ ਜਾਂ ਨਹੀਂ
2. **QoS ਸਤਰ:** 0 ਦੀ ਬਜਾਏ QoS 1 ਜਾਂ 2 ਦੀ ਕੋਸ਼ਿਸ਼ ਕਰੋ
3. **ਵਾਈਲਡਕਾਰਡ:** ਟਾਪਿਕ ਵਾਈਲਡਕਾਰਡ ਸਹੀ ਵਰਤੇ ਗਏ ਹਨ ਜਾਂ ਨਹੀਂ ਜਾਂਚੋ (`+` ਇੱਕ ਪੱਧਰ ਲਈ, `#` ਕਈ ਪੱਧਰਾਂ ਲਈ)
4. **ਰਿਟੇਨ ਕੀਤਾ ਸੁਨੇਹਾ:** ਪਬਲਿਸ਼ਰ ਅਖੀਰਲਾ ਸੁਨੇਹਾ ਰੱਖਣ ਲਈ ਰਿਟੇਨ ਫਲੈਗ ਸੈਟ ਕਰ ਸਕਦਾ ਹੈ
5. **ਕਨੈਕਸ਼ਨ ਸਮਾਂ:** ਸੂਨਹੇ ਪ੍ਰਕਾਸ਼ਿਤ ਹੋਣ ਤੋਂ ਪਹਿਲਾਂ ਗ੍ਰਾਹਕ ਜੁੜਿਆ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ

---

## ਸੈਂਸਰ ਅਤੇ ਐਕਚੁਏਟਰ ਸਮੱਸਿਆਵਾਂ

### Grove ਸੈਂਸਰ

#### ਸਮੱਸਿਆ: ਸੈਂਸਰ ਗਲਤ ਮੁੱਲ ਵਾਪਸ ਕਰਦਾ ਹੈ
**ਲੱਛਣ:** ਪੜ੍ਹਤਿਆਂ ਦਾ ਮੁੱਲ 0, -1 ਜਾਂ ਬੇਤੱਤੂਕ ਹੈ

**ਹੱਲ:**
1. **ਕਨੈਕਸ਼ਨ ਚੈੱਕ ਕਰੋ:** ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਸੈਂਸਰ ਠੀਕ ਤਰ੍ਹਾਂ ਜੁੜਿਆ ਹੈ
2. **ਸਹੀ ਪੋਰਟ:** ਸੈਂਸਰ ਸਹੀ ਕਿਸਮ ਦੇ ਪੋਰਟ ਵਿੱਚ ਹੈ ਜਾਂ ਨਹੀਂ:
   - ਐਨਾਲੋਗ ਸੈਂਸਰ → ਐਨਾਲੋਗ ਪੋਰਟ (A0, A2, A4)
   - ਡਿਜੀਟਲ ਸੈਂਸਰ → ਡਿਜੀਟਲ ਪੋਰਟ (D5, D16, D18, ਆਦਿ)
   - I2C ਸੈਂਸਰ → I2C ਪੋਰਟ
3. **ਕੈਲਿਬ੍ਰੇਸ਼ਨ:** ਕੁਝ ਸੈਂਸਰਾਂ ਨੂੰ ਕੈਲਿਬ੍ਰੇਸ਼ਨ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ (ਮਿੱਟੀ ਦੀ ਨਮਤਾ, ਰੋਸ਼ਨੀ)
4. **ਪਾਵਰ ਸਾਈਕਲ ਕਰੋ:** ਸੈਂਸਰ ਨੂੰ ਅਣਜوڑ ਕੇ ਦੁਬਾਰਾ ਜੋੜੋ
5. **ਸੈਂਸਰ ਡੇਟਾਸ਼ੀਟ:** ਸੈਂਸਰ ਦੇ ਨਿਰਦੇਸ਼ ਅਤੇ ਲੋੜਾਂ ਦੀ ਜਾਂਚ ਕਰੋ

#### ਸਮੱਸਿਆ: Capacitive soil moisture sensor ਹਮੇਸ਼ਾ ਗਿੱਲਾ ਪੜ੍ਹਦਾ ਹੈ
**ਲੱਛਣ:** ਸੈਂਸਰ ਸੁੱਕਾ ਹੋਣ ਦੇ ਬਾਵਜੂਦ ਉੱਚੀ ਨਮਤਾ ਪੜ੍ਹਦਾ ਹੈ

**ਹੱਲ:**
1. **ਕੈਲਿਬ੍ਰੇਸ਼ਨ ਲੋੜੀਂਦੀ:** ਮਿੱਟੀ ਦੇ ਸੈਂਸਰਾਂ ਨੂੰ ਕੈਲਿਬ੍ਰੇਸ਼ਨ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ:
   - ਹਵਾ ਵਿੱਚ ਪੜ੍ਹਤਾਂ ਲਵੋ (ਸੁੱਕਾ ਮੂਲ–ਮਾਪ)
   - ਪਾਣੀ ਵਿੱਚ ਪੜ੍ਹਤਾਂ ਲਵੋ (ਗੀਲਾ ਮੂਲ–ਮਾਪ)
   - ਇਨ੍ਹਾਂ ਮੁੱਲਾਂ ਵਿਚਕਾਰ ਪੜ੍ਹਤਾਂ ਨੂੰ ਮੈਪ ਕਰੋ
2. **ਸੈਂਸਰ ਕੋਟਿੰਗ ਚੈੱਕ ਕਰੋ:** ਨਮਤਾ ਸੈਂਸਰ ਦਾ ਕੋਟਿੰਗ ਖ਼ਰਾਬ ਹੋ ਸਕਦਾ ਹੈ
3. **ਥਾਂ:** ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਸੈਂਸਰ ਮਿੱਟੀ ਵਿੱਚ ਪੂਰੀ ਤਰ੍ਹਾਂ ਲੱਗਿਆ ਹੋਇਆ ਹੈ

#### ਸਮੱਸਿਆ: ਤਾਪਮਾਨ/ਨਮੀ ਸੈਂਸਰ ਦੀ ਪੜ੍ਹਾਈ ਗਲਤ ਹੈ
**ਲੱਛਣ:** DHT11/DHT22 ਗਲਤ ਤਾਪਮਾਨ ਜਾਂ ਨਮੀ ਦਿਖਾਉਂਦਾ ਹੈ

**ਹੱਲ:**
1. **ਸੈਂਸਰ ਦੀ ਥਾਂ:** ਸਿੱਧੀ ਧੂਪ, ਗਰਮੀ ਦੇ ਸ੍ਰੋਤ ਜਾਂ ਹਵਾ ਬਾਹਰ ਰਹਿਣ ਤੋਂ ਬਚੋ
2. **ਵਾਰਮ-ਅਪ ਸਮਾਂ:** ਪਾਵਰ-ਆਨ ਤੋਂ ਬਾਅਦ ਸੈਂਸਰ ਨੂੰ 2 ਸਕਿੰਟ ਦਿਓ
3. **ਪੜ੍ਹਾਈ ਦੀ ਆਵਿਰਤੀ:** DHT ਸੈਂਸਰਾਂ ਨੂੰ ਪੜ੍ਹਾਈਆਂ ਵਿੱਚ ਕਮੋ ਤੋਂ ਕਮ 2 ਸਕਿੰਟ ਦੀ ਦੂਰੀ ਚਾਹੀਦੀ ਹੈ
4. **ਕਾਂਡੇਨਸੇਸ਼ਨ ਲਈ ਜਾਂਚ:** ਕਾਂਡੇਨਸੇਸ਼ਨ ਪੜ੍ਹਾਈਆਂ 'ਤੇ ਅਸਰ ਪਾ ਸਕਦਾ ਹੈ
5. **ਸੈਂਸਰ ਗੁਣਵੱਤਾ:** DHT11 DHT22 ਨਾਲੋਂ ਘੱਟ ਸਹੀ ਹੈ

### ਕੈਮਰਾ

#### ਸਮੱਸਿਆ: Raspberry Pi ਤੇ ਕੈਮਰਾ ਨਹੀਂ ਪਹਿਚਾਣਿਆ ਗਿਆ
**ਗਲਤੀ:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**ਹੱਲ:**
1. **ਕੈਮਰਾ ਇੰਟਰਫੇਸ ਨੂੰ ਇनेਬਲ ਕਰੋ:**
   ```bash
   sudo raspi-config
   ```
   Interface Options → Camera → Enable ਜਾਓ
2. **ਰਿਬਨ ਕੇਬਲ ਦੀ ਜਾਂਚ ਕਰੋ:** ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਕੈਮਰਾ ਕੇਬਲ ਠੀਕ ਤਰ੍ਹਾਂ ਲੱਗਿਆ ਹੈ
   - ਪਾਈ ਜ਼ੀਰੋ 'ਤੇ ਨੀਲਾ ਪਾਸਾ USB ਪੋਰਟ ਦੀ ਓਰ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ
   - ਪਾਈ 4 'ਤੇ ਨੀਲਾ ਪਾਸਾ USB ਪੋਰਟ ਤੋਂ ਦੂਰ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ
3. **Firmware ਨੂੰ ਅਪਡੇਟ ਕਰੋ:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **ਕੈਮਰਾ ਦੀ ਜਾਂਚ ਕਰੋ:**
   ```bash
   raspistill -o test.jpg
   ```

#### ਸਮੱਸਿਆ: ਕੈਮਰਾ ਕੀ ਵਿੱਤਰ ਕੁਆਲਿਟੀ ਖ਼ਰਾਬ ਹੈ
**ਲੱਛਣ:** ਧੁੰਦਲੀ, ਹਨੇਰੀ ਜਾਂ ਫਿਕੀ ਤਸਵੀਰਾਂ

**ਹੱਲ:**
1. **ਫੋਕਸ:** ਲੈਂਸ ਤੋਂ सुरक्षात्मक ਫਿਲਮ ਹਟਾਓ, ਜੇ ਫੋਕਸ ਸੈਟਿੰਗ ਯੋਗ ਹੈ ਤਦ ਸੰਸੋਧਨ ਕਰੋ
2. **ਰੋਸ਼ਨੀ:** ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਪਰਯਾਪਤ ਰੋਸ਼ਨੀ ਹੈ
3. **ਕੈਮਰਾ ਸੈਟਿੰਗ:** ਕੋਡ ਵਿੱਚ ਐਕਸਪੋਜ਼ਰ, ISO, ਵ੍ਹਾਈਟ ਬੈਲੈਂਸ ਨੂੰ ਸੈਟ ਕਰੋ
4. **ਸਥਿਰਤਾ:** ਕੈਮਰਾ ਨੂੰ тұрақты ਰੱਖੋ, ਜੇ ਜ਼ਰੂਰੀ ਹੋਵੇ ਤਰਿਬੋਡ ਵਰਤੋਂ
5. **ਰੀਜ਼ੋਲੀਉਸ਼ਨ:** ਕੈਮਰਾ ਦੀ ਵੱਧ ਤੋਂ ਵੱਧ ਰੀਜ਼ੋਲੀਉਸ਼ਨ ਤੋਂ ਬਹੁਤ ਜ਼ਿਆਦਾ ਨਾ ਕਰੋ

### ਮਾਈਕ੍ਰੋਫੋਨ ਅਤੇ ਸਪੀਕਰ

#### ਸਮੱਸਿਆ: ਆਡੀਓ ਇਨਪੁੱਟ/ਆਉਟਪੁੱਟ ਨਹੀਂ
**ਲੱਛਣ:** ਮਾਈਕ੍ਰੋਫੋਨ ਰਿਕਾਰਡ ਨਹੀਂ ਕਰ ਰਿਹਾ, ਸਪੀਕਰ ਆਵਾਜ਼ ਨਹੀੰ ਬਜਾ ਰਿਹਾ

**ਹੱਲ:**
1. **ਕਨੈਕਸ਼ਨ ਚੈੱਕ ਕਰੋ:** ਆਡੀਓ ਡਿਵਾਈਸ ਠੀਕ ਜੁੜੇ ਹੋਏ ਹਨ ਜਾਂ ਨਹੀਂ ਜਾਂਚੋ
2. **ਹਾਰਡਵੇਅਰ ਟੈਸਟ ਕਰੋ:**
   - ਸਪੀਕਰ: `speaker-test -t wav -c 2`
   - ਮਾਈਕ੍ਰੋਫੋਨ: `arecord -l` ਗਿਆਨਸੂਚੀ ਕਰਨ ਲਈ, `arecord test.wav` ਰਿਕਾਰਡ ਕਰਨ ਲਈ
3. **ਵਾਲੀਅਮ ਸੈਟਿੰਗਜ਼:** ਵਾਲੀਅਮ ਜਾਂਚੋ ਅਤੇ ਸੰਸੋਧਨ ਕਰੋ:
   ```bash
   alsamixer
   ```
4. **ਆਡੀਓ ਡਿਵਾਈਸ ਚੁਣੋ:** ਕੋਡ ਵਿੱਚ ਸਹੀ ਆਡੀਓ ਡਿਵਾਈਸ ਦਰਜ ਕਰੋ
5. **ਡ੍ਰਾਇਵਰ ਸਮੱਸਿਆਵਾਂ:** ALSA ਅਪਡੇਟ ਕਰੋ ਜਾਂ ਆਡੀਓ ਡ੍ਰਾਇਵਰ ਮੁੜ ਇੰਸਟਾਲ ਕਰੋ

#### ਸਮੱਸਿਆ: ReSpeaker ਹੈਟ ਕੰਮ ਨਹੀਂ ਕਰ ਰਿਹਾ
**ਲੱਛਣ:** ਆਡੀਓ ਡਿਵਾਈਸ ਪਹਿਚਾਣੀ ਨਹੀਂ ਜਾ ਰਹੀ

**ਹੱਲ:**
1. **ਡ੍ਰਾਇਵਰ ਇੰਸਟਾਲ ਕਰੋ:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **ਇੰਸਟਾਲੇਸ਼ਨ ਦੀ ਜਾਂਚ ਕਰੋ:** `arecord -l` ਵਿੱਚ ReSpeaker ਦਿੱਖਣਾ ਚਾਹੀਦਾ ਹੈ
3. **Firmware ਅਪਡੇਟ ਕਰੋ:** ਕੁਝ ਪਾਈ OS ਵਰਜ਼ਨ ਨੂੰ ਡਰਾਇਵਰ ਅਪਡੇਟ ਦੀ ਲੋੜ ਹੁੰਦੀ ਹੈ
4. **ਹੈਟ ਦੀ ਬੈਠਕ ਚੈੱਕ ਕਰੋ:** ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਹੈਟ GPIO ਪਿੰਸਨ ਨਾਲ ਠੀਕ ਤਰ੍ਹਾਂ ਜੁੜੀ ਹੈ

---

## ਵਿਕਾਸ ਮਾਹੌਲ ਸਮੱਸਿਆਵਾਂ

### VS ਕੋਡ

#### ਸਮੱਸਿਆ: ਟਰਮੀਨਲ ਆਪਮੈਟਿਕ ਤੌਰ ਤੇ ਵਰਚੁਅਲ මහੌਲ ਐਕਟੀਵੇਟ ਨਹੀਂ ਕਰ ਰਿਹਾ
**ਲੱਛਣ:** ਟਰਮੀਨਲ ਖੁਲਦਾ ਹੈ ਪਰ ਵੈਨਵ ਐਕਟੀਵੇਟ ਨਹੀਂ ਹੁੰਦਾ

**ਹੱਲ:**
1. **ਪਾਇਥਨ ਇੰਟਰਪ੍ਰੀਟਰ ਸੈੱਟ ਕਰੋ:** Command Palette → "Python: Select Interpreter" → ਵੈਨਵ ਚੁਣੋ
2. **VS ਕੋਡ ਨੂੰ ਰੀਸਟਾਰਟ ਕਰੋ** ਇੰਟਰਪ੍ਰੀਟਰ ਚੁਣਣ ਦੇ ਬਾਅਦ
3. **ਸੈਟਿੰਗਜ਼ ਚੈੱਕ ਕਰੋ:** `settings.json` ਵਿੱਚ ਸ਼ਾਮਿਲ ਕਰੋ:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### ਸਮੱਸਿਆ: ਕੋਡ ਡਿਵਾਈਸ ਤੇ ਨਹੀਂ ਚੱਲ ਰਿਹਾ
**ਲੱਛਣ:** ਕੋਡ ਚੱਲਦਾ ਹੈ ਪਰ ਡਿਵਾਈਸ ਤੇ ਕੁਝ ਨਹੀਂ ਹੁੰਦਾ

**ਹੱਲ:**
1. **ਕੋਡ ਸੇਵ ਹੈ ਜਾਂ ਨਹੀਂ ਜਾਂਚੋ** (ਫਾਇਲ ਟੈਬ 'ਤੇ ਡਾਟ ਦੇਖੋ)
2. **ਕੋਨਸਾ ਪਾਇਥਨ ਚੱਲ ਰਿਹਾ ਹੈ ਜਾਂਚੋ:** `which python` ਜਾਂ `where python`
3. **Wio Terminal ਲਈ:** ਕੋਡ ਨੂੰ PlatformIO ਨਾਲ ਅਪਲੋਡ ਕਰੋ (ਅਪਲੋਡ ਬਟਨ ਕਲਿੱਕ ਕਰੋ)
4. **Raspberry Pi ਲਈ:** Pi ਵਿੱਚ SSH ਕਰਕੇ ਕੋਡ ਚਲਾੋ
5. **ਆਉਟਪੁੱਟ ਵਿੰਡੋ ਨੂੰ ਚੈੱਕ ਕਰੋ** ਗਲਤੀਆਂ ਲਈ

#### ਸਮੱਸਿਆ: IntelliSense ਲਾਇਬ੍ਰੇਰੀ ਫੰਕਸ਼ਨ ਨਹੀਂ ਦਿਖਾ ਰਿਹਾ
**ਲੱਛਣ:** ਇੰਪੋਰਟ ਕੀਤੇ ਮਾਡਿਊਲਾਂ ਲਈ ਆਟੋਕੰਪਲੀਟ ਨਹੀਂ

**ਹੱਲ:**
1. ਯਕੀਨੀ ਬਣਾਓ ਕਿ ਲਾਇਬ੍ਰੇਰੀ ਮੌਜੂਦਾ ਵਾਤਾਵਰਣ ਵਿੱਚ ਇੰਸਟਾਲ ਕੀਤੀ ਗਈ ਹੈ
2. VS ਕੋਡ ਵਿੰਡੋ ਨੂੰ ਰੀਲੋਡ ਕਰੋ
3. ਪਾਇਥਨ ਇੰਟਰਪ੍ਰੀਟਰ ਸਹੀ ਹੈ ਜਾਂ ਨਹੀਂ ਜਾਂਚੋ
4. ਜੇ ਉਪਲਬਧ ਹੋਵੇ ਤਾਂ ਟਾਈਪ ਸਟੱਬਸ ਇੰਸਟਾਲ ਕਰੋ: `pip install types-<library-name>`

### ਪਾਇਥਨ ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ

#### ਸਮੱਸਿਆ: ਵਰਚੁਅਲ ਮਾਹੌਲ ਬਣਾਉਣ ਵਿੱਚ ਅਸਫਲ
**ਗਲਤੀ:** `The virtual environment was not created successfully`

**ਹੱਲ:**
1. **venv ਮਾਡਿਊਲ ਇੰਸਟਾਲ ਕਰੋ:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Python ਨਾਲ ਸ਼ਾਮਿਲ ਹੁੰਦਾ ਹੈ
   - Windows: ਸਾਰੇ ਕੰਪੋਨੇਟਸ ਨਾਲ ਪਾਇਥਨ ਮੁੜ ਇੰਸਟਾਲ ਕਰੋ
2. **ਪਾਇਥਨ ਇੰਸਟਾਲੇਸ਼ਨ ਚੈੱਕ ਕਰੋ:** ਪਾਇਥਨ ਠੀਕ ਤਰ੍ਹਾਂ ਇੰਸਟਾਲ ਹੈ ਜਾਂ ਨਹੀਂ
3. **ਪੂਰਾ ਪਾਥ ਵਰਤੋਂ:** `python3 -m venv .venv` ਵਰਤ ਕੇ

#### ਸਮੱਸਿਆ: ਪੈਕੇਜ ਗਲਤ ਥਾਂ ਤੇ ਇੰਸਟਾਲ ਹੋਏ
**ਲੱਛਣ:** ਪੈਕਜ ਇੰਸਟਾਲ ਕਰਨ ਤੋਂ ਬਾਅਦ ਇੰਪੋਰਟ ਗਲਤੀ

**ਹੱਲ:**
1. **venv ਐਕਟੀਵੇਟ ਹੈ ਜਾਂ ਨਹੀਂ ਚੈੱਕ ਕਰੋ:** ਕਮਾਂਡ ਪ੍ਰਾਂਪਟ `(.venv)` ਦਿਖਾਏ
2. **pip ਦੀ ਥਾਂ ਚੈੱਕ ਕਰੋ:** `which pip` `.venv/bin/pip` ਵੱਲ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ
3. **ਵੈਨਵ ਵਿਚ ਮੁੜ ਇੰਸਟਾਲ ਕਰੋ:** ਵੈਨਵ ਐਕਟੀਵੇਟ ਕਰੋ ਅਤੇ ਫਿਰ `pip install <package>`
4. **ਵੈਨਵ ਵਿੱਚ sudo ਦੇ ਨਾਲ pip ਦਾ ਇਸਤੇਮਾਲ ਨਾ ਕਰੋ**

#### ਸਮੱਸਿਆ: ਵਰਚੁਅਲ ਵਾਤਾਵਰਣ ਪੋਰਟੇਬਲ ਨਹੀਂ ਹੈ
**ਲੱਛਣ:** ਵੈਨਵ ਹਿਲਦੇ ਜਾਂ ਵੱਖਰੇ ਕੰਪਿਊਟਰ ‘ਤੇ ਕੰਮ ਨਹੀਂ ਕਰਦਾ

**ਹੱਲ:**
1. **ਵੈਨਵ ਨੂੰ ਨਹੀਂ ਹਿਲਾਓ:** ਹਟਾ ਕੇ ਨਵੀਂ ਥਾਂ ਬਣਾਓ
2. **requirements.txt ਵਰਤੋ:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **ਵੈਨਵ ਮੁੜ ਬਣਾਓ:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # ਜਾਂ Windows 'ਤੇ activate.bat
   pip install -r requirements.txt
   ```

### ਡੀਪੈਂਡੈਂਸੀਜ਼

#### ਸਮੱਸਿਆ: ਪੈਕੇਜ ਇੰਸਟਾਲੇਸ਼ਨ ਫੇਲ
**ਗਲਤੀ:** ਇੰਸਟਾਲੇਸ਼ਨ ਦੌਰਾਨ ਵੱਖ-ਵੱਖ pip ਗਲਤੀਆਂ

**ਹੱਲ:**
1. **pip ਅਪਡੇਟ ਕਰੋ:**
   ```bash
   pip install --upgrade pip
   ```
2. **ਬਿਲਡ ਟੂਲਜ਼ ਇੰਸਟਾਲ ਕਰੋ:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Visual Studio Build Tools ਇੰਸਟਾਲ ਕਰੋ
3. **ਇੰਟਰਨੈੱਟ ਕਨੈਕਸ਼ਨ ਚੈੱਕ ਕਰੋ**
4. **ਵੱਖਰਾ ਪੈਕੇਜ ਇੰਡੈਕਸ ਕੋਸ਼ਿਸ਼ ਕਰੋ:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **ਵਿਸ਼ੇਸ਼ ਵਰਜ਼ਨ ਇੰਸਟਾਲ ਕਰੋ:** `pip install <package>==<version>`

#### ਸਮੱਸਿਆ: ਡੀਪੈਂਡੈਂਸੀ ਸੰਘਰਸ਼
**ਗਲਤੀ:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**ਹੱਲ:**
1. **ਹਰ ਪ੍ਰਾਜੈਕਟ ਲਈ ਨਵੀਆਂ ਵਰਚੁਅਲ ਐਨਵਾਇਰਨਮੈਂਟ ਵਰਤੋਂ**
2. **ਪੈਕੇਜ ਅਪਡੇਟ ਕਰੋ:** `pip install --upgrade <package>`
3. **ਡਿਪੈਂਡੈਂਸੀ ਸੰਘਰਸ਼ ਲਈ ਜਾਂਚ ਕਰੋ:** `pip check`
4. **ਮਿਲਦੀਆਂ ਵਰਜ਼ਨ ਇੰਸਟਾਲ ਕਰੋ:** requirements.txt ਵਿੱਚ ਵਰਜ਼ਨ ਰੇਂਜ ਦਿਓ

---

## ਕਾਰਗੁਜ਼ਾਰੀ ਸਮੱਸਿਆਵਾਂ

### ਸਮੱਸਿਆ: ਕੋਡ ਹੌਲੀ ਚੱਲਦਾ ਹੈ
**ਲੱਛਣ:** ਦੇਰੀ, ਟਾਈਮਆਉਟ, ਬੇਹੋਸ਼ੀ

**ਹੱਲ:**
1. **ਸੈਂਸਰ ਪੜ੍ਹਾਈ ਫ੍ਰੀਕਵੇਂਸੀ ਘਟਾਓ:** ਬਹੁਤ ਜ਼ਿਆਦਾ ਪੜ੍ਹਾਈ ਨਾ ਕਰੋ
2. **ਲੂਪਾਂ ਡਿੱਠੀ ਕਰੋ:** ਬਿਜੀ-ਵੇਟਿੰਗ ਤੋਂ ਬਚੋ, sleep() ਜਾਂ ਡਿੱਲੇ ਵਰਤੋਂ
3. **ਮੈਮੋਰੀ ਸਮੱਸਿਆਵਾਂ:**
   - ਲੋੜ ਨਹੀਂ ਐਪਸ ਬੰਦ ਕਰੋ
   - ਸਟੋਰੇਜ ਖਾਲੀ ਕਰੋ
   - Pi ‘ਤੇ `top` ਜਾਂ `htop` ਨਾਲ ਨਿਗਰਾਨੀ ਕਰੋ
4. **SD ਕਾਰਡ ਦੀ ਗਤੀ:** ਤੇਜ਼ SD ਕਾਰਡ ਜਾਂ SSD ਵਰਤੋਂ Raspberry Pi ਲਈ
5. **ਨੈਟਵਰਕ ਦੇਰੀ:** ਨੈਟਵਰਕ ਕਾਲਾਂ ਲਈ ਐਸਿੰਕ ਆਪਰੇਸ਼ਨ ਵਰਤੋਂ

### ਸਮੱਸਿਆ: ਮੈਮੋਰੀ ਭਰ ਗਈ ਗਲਤੀਆਂ
**ਗਲਤੀ:** `MemoryError` ਜਾਂ ਸਿਸਟਮ ਫ੍ਰੀਜ਼

**ਹੱਲ:**
1. **Raspberry Pi ਲਈ:**
   - ਲੋੜਵੰ ਜ ਐਪਲੀਕੇਸ਼ਨ ਬੰਦ ਕਰੋ
   - ਸਵੈਪ ਸਪੇਸ ਵਧਾਓ
   - ਹਲਕਾ OS ਵਰਤੋਂ (Lite ਵਰਜ਼ਨ)
   - ਰੈਮ ਅਪਗਰੇਡ ਕਰੋ (Pi 4 ਚ 2/4/8GB ਚੋਣ)
2. **Wio Terminal ਲਈ:**
   - ਬਫਰ ਆਕਾਰ ਘਟਾਓ
   - ਛੋਟੀਆਂ ਤਸਵੀਰਾਂ ਵਰਤੋਂ
   - ਸਤਰਾਂ ਦੀ ਵਰਤੋਂ ਸਧਾਰੋ
   - ਮੈਮੋਰੀ ਲੀਕ ਜਾਂਚੋ (ਅਨਰਿਲੀਜ਼ਡ ਮੈਮੋਰੀ)

### ਸਮੱਸਿਆ: ਡਾਟਾ ਖੋਣਾ ਜਾਂ ਖਰਾਬ ਹੋਣਾ
**ਲੱਛਣ:** ਸੁਨੇਹੇ ਗਾਇਬ, ਫਾਇਲ ਖਰਾਬ

**ਹੱਲ:**
1. **SD ਕਾਰਡ ਸਮੱਸਿਆਵਾਂ:**
   - ਵਧੀਆ SD ਕਾਰਡ ਵਰਤੋਂ (ਸਸਤੇ ਜਾਂ ਨਕਲੀ ਤੋਂ ਬਚੋ)
   - ਨਿਯਮਤ ਬੈਕਅੱਪ ਕਰੋ
   - ਸੇਟਿੰਗਬੰਦ ਸ਼ਟਡਾਊਨ (ਪਾਵਰ ਨਾ ਖਿੱਚੋ)
2. **ਬਫਰ ਓਵਰਫਲੋ:** ਕੋਡ ਵਿੱਚ ਬਫਰ ਆਕਾਰ ਵਧਾਓ
3. **ਨੈਟਵਰਕ ਭਰੋਸੇਯੋਗਤਾ:** ਮੁੜ ਕੋਸ਼ਿਸ਼ ਲਈ ਲੋਜਿਕ ਅਤੇ ਗਲਤੀ ਸੰਭਾਲ ਬਣਾੋ
4. **ਸੇਵਾ ਦੀ ਕਵਾਲਟੀ:** ਜਰੂਰੀ ਸੁਨੇਹਿਆਂ ਲਈ MQTT QoS 1 ਜਾਂ 2 ਵਰਤੋਂ

---

## ਆਮ ਗਲਤੀ ਸੁਨੇਹੇ

### `ModuleNotFoundError: No module named 'X'`
**ਕਾਰਨ:** ਪੈਕੇਜ ਇੰਸਟਾਲ ਨਹੀਂ ਹੈ ਜਾਂ ਵੈਨਵ ਐਕਟੀਵੇਟ ਨਹੀਂ ਹੈ

**ਹੱਲ:**
```bash
pip install X
```
ਵੈਨਵ ਪਹਿਲਾਂ ਐਕਟੀਵੇਟ ਹੈ ਜਾਂ ਨਹੀਂ ਯਕੀਨੀ ਬਣਾਓ।

### `Permission denied` Linux/macOS ‘ਤੇ
**ਕਾਰਨ:** ਉੱਚ ਅਧਿਕਾਰ ਜਾਂ ਫਾਇਲ ਪਰਮਿਸ਼ਨ ਸਮੱਸਿਆ

**ਹੱਲ:**
- ਸਿਸਟਮ ਕਾਰਜ ਲਈ: `sudo` ਵਰਤੋਂ
- pip ਲਈ: ਵੈਨਵ ਐਕਟੀਵੇਟ ਕਰਕੇ sudo ਨਾ ਵਰਤੋਂ
- ਸਿਰੀਅਲ ਪੋਰਟ ਲਈ: ਯੂਜ਼ਰ ਨੂੰ dialout ਗਰੁੱਪ ਵਿੱਚ ਸ਼ਾਮਿਲ ਕਰੋ: `sudo usermod -a -G dialout $USER`, ਫਿਰ ਲੋਗਆਊਟ/ਲੋਗਇਨ

### `OSError: [Errno 98] Address already in use`
**ਕਾਰਨ:** ਪੋਰਟ ਕਿਸੇ ਹੋਰ ਪ੍ਰਕਿਰਿਆ ਵੱਲੋਂ ਵਰਤਿਆ ਜਾ ਰਿਹਾ ਹੈ

**ਹੱਲ:**
1. ਕਿਸ ਪ੍ਰਕਿਰਿਆ ਪੋਰਟ ਵਰਤ ਰਹੀ ਹੈ ਉਹ ਲੱਭੋ: `lsof -i :<port>` ਜਾਂ `netstat -ano | findstr :<port>`
2. ਪ੍ਰਕਿਰਿਆ ਨੂੰ ਮਾਰੋ ਜਾਂ ਆਪਣੀ ਕੋਡ ਵਿੱਚ ਵੱਖਰਾ ਪੋਰਟ ਵਰਤੋਂ

### `SSL: CERTIFICATE_VERIFY_FAILED`
**ਕਾਰਨ:** SSL ਸਰਟੀਫਿਕੇਟ ਪਰਖ ਅਸਫਲ

**ਹੱਲ:**
1. ਸਰਟੀਫਿਕੇਟ ਅਪਡੇਟ ਕਰੋ: `pip install --upgrade certifi`
2. ਸਿਸਟਮ ਸਮਾਂ ਸਹੀ ਹੈ ਜਾਂ ਨਹੀਂ ਜਾਂਚੋ: `date`
3. ਵਿਅਕਾਸ ਲਈ ਹੀ (ਉਤਪਾਦਨ ਲਈ ਨਹੀਂ): ਕੋਡ ਵਿੱਚ ਪਰਖ ਅਣਇਨੇਬਲ ਕਰੋ

### `IndentationError: unexpected indent`
**ਕਾਰਨ:** ਪਾਇਥਨ ਇੰਡੇਨਟੇਸ਼ਨ ਗਲਤੀਆਂ (ਟੈਬ/ਸਪੇਸ ਮਿਲਾਓਣਾ)

**ਹੱਲ:**
1. ਇੱਕਸਾਰ ਇੰਡੇਨਟੇਸ਼ਨ ਵਰਤੋਂ (4 ਸਪੇਸ ਪਾਇਥਨ ਮਿਆਰੀ)
2. ਐਡੀਟਰ ਨੂੰ ਟੈਬ ਦੀ ਥਾਂ ਸਪੇਸ ਵਰਤਣ ਲਈ ਸੈਟ ਕਰੋ
3. VS ਕੋਡ ਵਿੱਚ `"editor.insertSpaces": true` ਅਤੇ `"editor.tabSize": 4` ਦਿਓ

### `UnicodeDecodeError` ਜਾਂ `UnicodeEncodeError`
**ਕਾਰਨ:** ਕੈਰੈਕਟਰ ਇੰਕੋਡਿੰਗ ਸਮੱਸਿਆ

**ਹੱਲ:**
```python
# ਜਦੋਂ ਫਾਇਲਾਂ ਪੜ੍ਹ ਰਹੇ ਹੋਵੋ
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# ਜਦੋਂ ਫਾਇਲਾਂ ਲਿਖ ਰਹੇ ਹੋਵੋ
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## ਮਦਦ ਲੈਣਾ

ਜੇ ਤੁਸੀਂ ਇਹ ਟ੍ਰਬਲਸ਼ੂਟਿੰਗ ਕਦਮ ਅਜ਼ਮਾਏ ਹਨ ਪਰ ਅਜੇ ਵੀ ਸਮੱਸਿਆ ਹੈ:

### 1. ਮੌਜੂਦਾ ਸਰੋਤ ਜਾਂਚੋ
- **ਦਸਤਾਵੇਜ਼:** [README](README.md) ਅਤੇ ਲੈਸਨ ਨਿਰਦੇਸ਼ ਪੜ੍ਹੋ
- **ਹਾਰਡਵੇਅਰ ਗਾਇਡਜ਼:** [hardware.md](hardware.md) ਵਿੱਚ ਹਾਰਡਵੇਅਰ-ਵਿਸ਼ੇਸ਼ ਜਾਣਕਾਰੀ ਵੇਖੋ
- **Seeed Studio Wiki:** Grove ਕੰਪੋਨੈਂਟ ਲਈ [Seeed Studio Wiki](https://wiki.seeedstudio.com/) ਵੇਖੋ

### 2. ਮਿਲਦੀਆਂ ਸਮੱਸਿਆਵਾਂ ਖੋਜੋ
- **GitHub Issues:** [ਮੌਜੂਦਾ ਸਮੱਸਿਆਵਾਂ](https://github.com/microsoft/IoT-For-Beginners/issues) ਖੋਜੋ
- **Stack Overflow:** ਗਲਤੀ ਸੁਨੇਹੇ ਖੋਜੋ
- **ਡਿਵਾਈਸ ਫੋਰਮ:** Raspberry Pi ਜਾਂ Arduino ਫੋਰਮ ਚੈੱਕ ਕਰੋ

### 3. GitHub ਇਸ਼ੂ ਬਣਾਓ
ਜੇ ਹੱਲ ਨਾ ਮਿਲੇ:
1. [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues) 'ਤੇ ਜਾਓ
2. "New Issue" 'ਤੇ ਕਲਿੱਕ ਕਰੋ
3. ਦਿੱਤੀਆਂ ਜਾਣਕਾਰੀਆਂ ਦਿਓ:
   - ਸਮੱਸਿਆ ਦਾ ਸਪਸ਼ਟ ਵੇਰਵਾ
   - ਦੁਹਰਾਉਣ ਵਾਲੇ ਕਦਮ
   - ਗਲਤੀ ਸੁਨੇਹੇ (ਪੂਰਾ ਟੈਕਸਟ)
   - ਹਾਰਡਵੇਅਰ/ਸਾਫਟਵੇਅਰ ਵਰਜ਼ਨ
   - ਜੋ ਤੁਸੀਂ ਪਹਿਲਾਂ ਕੋਸ਼ਿਸ਼ ਕੀਤਾ
   - ਜੇ ਲੋੜ ਹੋਵੇ ਤਾਂ ਸਕ੍ਰੀਨਸ਼ਾਟ

### 4. ਕਮਿਊਨਿਟੀ ਨਾਲ ਜੁੜੋ
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. ਚੰਗੇ ਬੱਗ ਰਿਪੋਰਟ ਪ੍ਰਦਾਨ ਕਰੋ
ਇੱਕ ਚੰਗਾ ਬੱਗ ਰਿਪੋਰਟ ਸ਼ਾਮਿਲ ਹੁੰਦਾ ਹੈ:
- **ਵਾਤਾਵਰਣ:** ਓਐਸ, ਪਾਇਥਨ ਵਰਜਨ, ਵਰਤੇ ਗਏ ਹਾਰਡਵੇਅਰ  
- **ਮਸਲੇ ਨੂੰ ਦੁਹਰਾਉਣ ਦੇ ਕਦਮ:** ਉਹ ਸਹੀ ਕਦਮ ਜੋ ਮੁੱਦਾ ਪੈਦਾ ਕਰਦੇ ਹਨ  
- **ਉਮੀਦ ਕੀਤੀ ਗਈ ਵਰਤੋਂ:** ਕੀ ਹੋਣਾ ਚਾਹੀਦਾ ਹੈ  
- **ਅਸਲ ਵਰਤੋਂ:** ਅਸਲ ਵਿੱਚ ਕੀ ਹੁੰਦਾ ਹੈ  
- **ਗਲਤੀ ਸੁਨੇਹੇ:** ਪੂਰਾ ਗਲਤੀ ਟੈਕਸਟ, ਸਕਰੀਨਸ਼ਾਟ ਨਹੀਂ  
- **ਕੋਡ:** ਘੱਟੋ ਘੱਟ ਕੋਡ ਉਦਾਹਰਨ ਜੋ ਮੁੱਦਾ ਦੁਹਰਾਉਂਦੀ ਹੈ  

---

## ਰੋਕਥਾਮ ਲਈ ਸੁਝਾਵ

### ਆਮ ਸਧਾਰਣ ਅਮਲ  
1. **ਬੈਕਅੱਪ ਸੁਰੱਖਿਅਤ ਕਰੋ:** ਕੰਮ ਕਰਨ ਵਾਲੇ SD ਕਾਰਡ/ਕੋਡ ਬੈਕਅੱਪ ਪੱਕਾ ਕਰੋ  
2. **ਬਦਲਾਵ ਦਸਤਾਵੇਜ਼ੀਕਰਨ:** ਟਿੱਪਣੀਆਂ ਵਿੱਚ ਕੀ ਕੰਮ ਕਰਦਾ ਹੈ ਦਰਜ ਕਰੋ  
3. **ਵਰਜਨ ਕੰਟਰੋਲ:** ਕੋਡ ਬਦਲਾਵ ਲਈ git ਵਰਤੋਂ  
4. **ਛੋਟੇ ਬਦਲਾਵਾਂ ਦੀ ਜਾਂਚ ਕਰੋ:** ਮਿਲਾਉਣ ਤੋਂ ਪਹਿਲਾਂ ਛੋਟੇ ਬਦਲਾਵਾਂ ਦੀ ਜਾਂਚ ਕਰੋ  
5. **ਗਲਤੀ ਸੁਨੇਹੇ ਪੜ੍ਹੋ:** ਇਹ ਆਮ ਤੌਰ 'ਤੇ ਦੱਸਦੇ ਹਨ ਕਿ ਸਹੀ ਸਮੱਸਿਆ ਕੀ ਹੈ  
6. **ਨਿਯਮਤ ਅਪਡੇਟ ਕਰੋ:** ਸੌਫਟਵੇਅਰ/ਫਿਰਮਵੇਅਰ ਨੂੰ ਹਮੇਸ਼ਾ ਅਪਡੇਟ ਰੱਖੋ  
7. **ਗੁਣਵੱਤਾ ਵਾਲੇ ਹਿੱਸੇ ਵਰਤੋਂ:** ਸਸਤੇ ਕੇਬਲ/ਬਿਜਲੀ ਸਪਲਾਈ ਤੋਂ ਬਚੋ  
8. **ਸਥਿਰ ਬਿਜਲੀ ਸਪਲਾਈ:** ਉਚਿਤ ਬਿਜਲੀ ਸਪਲਾਈ ਵਰਤੋਂ (ਖਾਸ ਤੌਰ ਤੇ ਪਾਈ ਲਈ)  

### ਵਿਕਾਸ ਕੰਮਕਾਜ  
1. **ਸਰਲ ਸ਼ੁਰੂਆਤ ਕਰੋ:** ਕੰਮ ਕਰਨ ਵਾਲੇ ਉਦਾਹਰਨ ਕੋਡ ਤੋਂ ਸ਼ੁਰੂ ਕਰੋ  
2. **ਇੱਕ ਵਾਰੀ ਇੱਕ ਤਬਦੀਲੀ:** ਇਸ ਨਾਲ ਟੁੱਟਣ ਵਾਲੀ ਗਲਤੀ ਮਿਲਣਾ ਆਸਾਨ ਹੁੰਦਾ ਹੈ  
3. **ਅਕਸਰ ਜਾਂਚ ਕਰੋ:** ਮੁੱਦਿਆਂ ਨੂੰ ਜਲਦੀ ਫੜੋ  
4. **ਸਾਫ਼ ਸਾਫ਼ ਰੱਖੋ:** ਫਾਇਲਾਂ ਅਤੇ ਕੋਡ ਨੂੰ ਤਰਤੀਬਬੱਧ ਰੱਖੋ  
5. **ਕੋਡ 'ਤੇ ਟਿੱਪਣੀ ਕਰੋ:** ਭਵਿੱਖ ਵਿਚ ਤੁਸੀਂ ਇਸ ਦੀ ਕਦਰ ਕਰੋਗੇ  

---

*ਇਹ ਸਮੱਸਿਆ ਸੁਲਝਾਉਣ ਵਾਲਾ ਮਾਰਗਦਰਸ਼ਕ ਕਮਿਊਨਿਟੀ ਵਲੋਂ ਸੰਭਾਲਿਆ ਜਾਂਦਾ ਹੈ। ਜੇ ਤੁਸੀਂ ਇੱਥੇ ਦਰਜ ਨਾ ਹੋਏ ਸਮੱਸਿਆ ਲਈ ਕੋਈ ਹੱਲ ਲੱਭਦੇ ਹੋ, ਤਾਂ ਕਿਰਪਾ ਕਰਕੇ ਹੋਰਾਂ ਦੀ ਮਦਦ ਲਈ [ਯੋਗਦਾਨ ਪਾਉਣਾ](CONTRIBUTING.md) ਬਾਰੇ ਸੋਚੋ!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ਅਸਪਸ਼ਟੀਕਰਨ**:  
ਇਸ ਦਸਤਾਵੇਜ਼ ਦਾ ਅਨੁਵਾਦ AI ਅਨੁਵਾਦ ਸੇਵਾ [Co-op Translator](https://github.com/Azure/co-op-translator) ਦੀ ਵਰਤੋਂ ਕਰਕੇ ਕੀਤਾ ਗਿਆ ਹੈ। ਜਦੋਂ ਕਿ ਅਸੀਂ ਸਹੀਅਤ ਲਈ ਯਤਨ ਕਰਦੇ ਹਾਂ, ਕਿਰਪਾ ਕਰਕੇ ਇਹ ਜਾਣੋ ਕਿ ਸੁਚਾਲਿਤ ਅਨੁਵਾਦਾਂ ਵਿੱਚ ਗਲਤੀਆਂ ਜਾਂ ਅਸਮਰਥਾਵਾਂ ਹੋ ਸਕਦੀਆਂ ਹਨ। ਮੂਲ ਦਸਤਾਵੇਜ਼ ਆਪਣੀ ਮੂਲ ਭਾਸ਼ਾ ਵਿੱਚ ਪ੍ਰਮਾਣਿਕ ਸਰੋਤ ਵਜੋਂ ਮੰਨਿਆ ਜਾਣਾ ਚਾਹੀਦਾ ਹੈ। ਮਹੱਤਵਪੂਰਨ ਜਾਣਕਾਰੀ ਲਈ, ਪ੍ਰੋਫੈਸ਼ਨਲ ਮਨੁੱਖੀ ਅਨੁਵਾਦ ਦੀ ਸਿਫਾਰਸ਼ ਕੀਤੀ ਜਾਂਦੀ ਹੈ। ਅਸੀਂ ਇਸ ਅਨੁਵਾਦ ਦੀ ਵਰਤੋਂ ਕਾਰਨ ਉਤਪੰਨ ਕਿਸੇ ਵੀ ਗਲਤਫਹਮੀ ਜਾਂ ਗਲਤ ਸਮਝ ਦੀ ਜ਼ਿੰਮੇਵਾਰੀ ਨਹੀਂ ਲੈਂਦੇ।
<!-- CO-OP TRANSLATOR DISCLAIMER END -->