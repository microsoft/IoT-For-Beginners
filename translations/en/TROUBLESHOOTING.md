<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-05T12:31:46+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "en"
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
#### Problem: MQTT connection fails
**Error:** Connection refused, authentication failed

**Solution:**
1. **Broker address:** Verify broker URL/IP is correct
2. **Port:** Check port number (1883 for unencrypted, 8883 for TLS)
3. **Authentication:** Verify username/password if required
4. **TLS/SSL:** Ensure certificates are valid and trusted
5. **Firewall:** Check port is not blocked
6. **Test with MQTT client:** Use MQTT Explorer or mosquitto_pub/sub to test

#### Problem: MQTT messages not received
**Symptoms:** Messages published but not received by subscribers

**Solution:**
1. **Topic names:** Verify subscriber topic matches publisher topic exactly
2. **QoS level:** Try QoS 1 or 2 instead of 0
3. **Wildcards:** Check topic wildcards are used correctly (`+` for single level, `#` for multi-level)
4. **Retained messages:** Publisher can set retain flag to keep last message
5. **Connection timing:** Ensure subscriber connects before messages are published

---

## Sensor and Actuator Issues

### Grove Sensors

#### Problem: Sensor returns incorrect values
**Symptoms:** Readings are 0, -1, or nonsensical values

**Solution:**
1. **Check connections:** Ensure sensor is properly connected
2. **Correct port:** Verify sensor is in correct port type:
   - Analog sensors → Analog ports (A0, A2, A4)
   - Digital sensors → Digital ports (D5, D16, D18, etc.)
   - I2C sensors → I2C ports
3. **Calibration:** Some sensors need calibration (soil moisture, light)
4. **Power cycle:** Disconnect and reconnect sensor
5. **Sensor datasheet:** Check sensor specifications and requirements

#### Problem: Capacitive soil moisture sensor always reads wet
**Symptoms:** Sensor reads high moisture even when dry

**Solution:**
1. **Calibration needed:** Soil sensors require calibration:
   - Read value in air (dry baseline)
   - Read value in water (wet baseline)
   - Map readings between these values
2. **Check sensor coating:** Moisture sensors can degrade if coating damaged
3. **Placement:** Ensure sensor is fully inserted in soil

#### Problem: Temperature/humidity sensor readings incorrect
**Symptoms:** DHT11/DHT22 shows wrong temperature or humidity

**Solution:**
1. **Sensor placement:** Avoid direct sunlight, heat sources, or airflow
2. **Warm-up time:** Allow sensor 2 seconds after power-on before reading
3. **Read frequency:** DHT sensors need time between reads (at least 2 seconds)
4. **Check for condensation:** Can affect readings
5. **Sensor quality:** DHT11 is less accurate than DHT22

### Camera

#### Problem: Camera not detected on Raspberry Pi
**Error:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Solution:**
1. **Enable camera interface:**
   ```bash
   sudo raspi-config
   ```
   Go to Interface Options → Camera → Enable
2. **Check ribbon cable:** Ensure camera cable is properly inserted
   - Blue side faces USB ports on Pi Zero
   - Blue side faces away from USB ports on Pi 4
3. **Update firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Test camera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problem: Camera images are poor quality
**Symptoms:** Blurry, dark, or washed out images

**Solution:**
1. **Focus:** Remove protective film from lens, adjust focus if adjustable
2. **Lighting:** Ensure adequate lighting
3. **Camera settings:** Adjust exposure, ISO, white balance in code
4. **Stability:** Keep camera steady, use tripod if needed
5. **Resolution:** Don't exceed camera's maximum resolution

### Microphone and Speaker

#### Problem: No audio input/output
**Symptoms:** Microphone not recording, speaker not playing

**Solution:**
1. **Check connections:** Verify audio devices are properly connected
2. **Test hardware:**
   - Speaker: `speaker-test -t wav -c 2`
   - Microphone: `arecord -l` to list, `arecord test.wav` to record
3. **Volume settings:** Check and adjust volume:
   ```bash
   alsamixer
   ```
4. **Select audio device:** Specify correct audio device in code
5. **Driver issues:** Update ALSA or reinstall audio drivers

#### Problem: ReSpeaker hat not working
**Symptoms:** Audio device not detected

**Solution:**
1. **Install drivers:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Check installation:** `arecord -l` should list ReSpeaker
3. **Update firmware:** Some Pi OS versions need driver updates
4. **Check seating:** Ensure hat is properly connected to GPIO pins

---

## Development Environment Issues

### VS Code

#### Problem: Terminal not activating virtual environment automatically
**Symptoms:** Terminal opens but venv not activated

**Solution:**
1. **Set Python interpreter:** Command Palette → "Python: Select Interpreter" → Choose venv
2. **Restart VS Code** after selecting interpreter
3. **Check settings:** In `settings.json`, add:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Code not running on device
**Symptoms:** Code runs but nothing happens on device

**Solution:**
1. **Verify code is saved** (check dot on file tab)
2. **Check which Python is running:** `which python` or `where python`
3. **For Wio Terminal:** Ensure code is uploaded via PlatformIO (click upload button)
4. **For Raspberry Pi:** SSH into Pi and run code there
5. **Check output window** for errors

#### Problem: IntelliSense not showing library functions
**Symptoms:** No autocomplete for imported modules

**Solution:**
1. Ensure library is installed in current environment
2. Reload VS Code window
3. Check Python interpreter is correct
4. Install type stubs if available: `pip install types-<library-name>`

### Python Virtual Environments

#### Problem: Cannot create virtual environment
**Error:** `The virtual environment was not created successfully`

**Solution:**
1. **Install venv module:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Should be included with Python
   - Windows: Reinstall Python with all components
2. **Check Python installation:** Verify Python is properly installed
3. **Use full path:** Try `python3 -m venv .venv` with explicit python3 call

#### Problem: Packages installed in wrong location
**Symptoms:** Import error after installing package

**Solution:**
1. **Verify venv is activated:** Command prompt should show `(.venv)`
2. **Check pip location:** `which pip` should point to `.venv/bin/pip`
3. **Reinstall in venv:** Activate venv, then `pip install <package>`
4. **Don't use sudo with pip** in virtual environment

#### Problem: Virtual environment not portable
**Symptoms:** Venv doesn't work after moving or on different computer

**Solution:**
1. **Don't move venvs:** Delete and recreate in new location
2. **Use requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Recreate venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # or activate.bat on Windows
   pip install -r requirements.txt
   ```

### Dependencies

#### Problem: Package installation fails
**Error:** Various pip errors during installation

**Solution:**
1. **Update pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Install build tools:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Install Visual Studio Build Tools
3. **Check internet connection**
4. **Try different package index:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **Install specific version:** `pip install <package>==<version>`

#### Problem: Dependency conflicts
**Error:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Solution:**
1. **Use fresh virtual environment** for each project
2. **Update packages:** `pip install --upgrade <package>`
3. **Check requirements:** Use `pip check` to find conflicts
4. **Install compatible versions:** Specify version ranges in requirements.txt

---

## Performance Issues

### Problem: Code runs slowly
**Symptoms:** Delays, timeouts, unresponsive behavior

**Solution:**
1. **Reduce sensor read frequency:** Don't read sensors too often
2. **Optimize loops:** Avoid busy-waiting, use sleep() or delays
3. **Memory issues:**
   - Close unnecessary applications
   - Free up storage space
   - Monitor with `top` or `htop` on Pi
4. **SD card speed:** Use faster SD card or SSD for Raspberry Pi
5. **Network delays:** Use async operations for network calls

### Problem: Out of memory errors
**Error:** `MemoryError` or system freezing

**Solution:**
1. **For Raspberry Pi:**
   - Close unnecessary applications
   - Increase swap space
   - Use lighter OS (Lite version)
   - Upgrade RAM (Pi 4 has 2/4/8GB options)
2. **For Wio Terminal:**
   - Reduce buffer sizes
   - Use smaller images
   - Optimize string usage
   - Check for memory leaks (unreleased memory)

### Problem: Data loss or corruption
**Symptoms:** Missing messages, corrupted files

**Solution:**
1. **SD card issues:**
   - Use quality SD cards (avoid cheap/counterfeit)
   - Regular backups
   - Clean shutdown (don't pull power)
2. **Buffer overflow:** Increase buffer sizes in code
3. **Network reliability:** Implement retry logic and error handling
4. **Quality of Service:** Use MQTT QoS 1 or 2 for important messages

---

## Common Error Messages

### `ModuleNotFoundError: No module named 'X'`
**Cause:** Package not installed or virtual environment not activated

**Solution:**
```bash
pip install X
```
Ensure virtual environment is activated first.

### `Permission denied` on Linux/macOS
**Cause:** Need elevated permissions or file permissions issue

**Solution:**
- For system operations: Use `sudo`
- For pip: DON'T use sudo with venv, activate venv first
- For serial port: Add user to dialout group: `sudo usermod -a -G dialout $USER`, then logout/login

### `OSError: [Errno 98] Address already in use`
**Cause:** Port is already being used by another process

**Solution:**
1. Find process using port: `lsof -i :<port>` or `netstat -ano | findstr :<port>`
2. Kill process or use different port in your code

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Cause:** SSL certificate validation failing

**Solution:**
1. Update certificates: `pip install --upgrade certifi`
2. Check system time is correct: `date`
3. For development only (not production): Disable verification in code

### `IndentationError: unexpected indent`
**Cause:** Python indentation issues (mixing tabs/spaces)

**Solution:**
1. Use consistent indentation (4 spaces is Python standard)
2. Configure editor to use spaces instead of tabs
3. VS Code: Set `"editor.insertSpaces": true` and `"editor.tabSize": 4`

### `UnicodeDecodeError` or `UnicodeEncodeError`
**Cause:** Character encoding issues

**Solution:**
```python
# When reading files
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# When writing files
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Getting Help

If you've tried these troubleshooting steps and still have issues:

### 1. Check Existing Resources
- **Documentation:** Review the [README](README.md) and lesson instructions
- **Hardware guides:** Check [hardware.md](hardware.md) for hardware-specific info
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) for Grove components

### 2. Search for Similar Issues
- **GitHub Issues:** Search [existing issues](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Search for error messages
- **Device forums:** Check Raspberry Pi forums or Arduino forums

### 3. Create a GitHub Issue
If you can't find a solution:
1. Go to [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Click "New Issue"
3. Provide:
   - Clear description of the problem
   - Steps to reproduce
   - Error messages (full text)
   - Hardware/software versions
   - What you've already tried
   - Screenshots if relevant

### 4. Join the Community
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Provide Good Bug Reports
A good bug report includes:
- **Environment:** OS, Python version, hardware used
- **Steps to reproduce:** Exact steps that cause the issue
- **Expected behavior:** What should happen
- **Actual behavior:** What actually happens
- **Error messages:** Complete error text, not screenshots
- **Code:** Minimal code example that reproduces the issue

---

## Tips for Prevention

### General Best Practices
1. **Keep backups:** Regular backups of working SD cards/code
2. **Document changes:** Note what works in comments
3. **Version control:** Use git to track code changes
4. **Test incrementally:** Test small changes before combining
5. **Read error messages:** They often tell you exactly what's wrong
6. **Update regularly:** Keep software/firmware up to date
7. **Use quality components:** Avoid cheap cables/power supplies
8. **Stable power:** Use appropriate power supply (especially Pi)

### Development Workflow
1. **Start simple:** Begin with example code that works
2. **One change at a time:** Easier to find what breaks
3. **Test frequently:** Catch issues early
4. **Keep it clean:** Organize files and code logically
5. **Comment code:** Future you will appreciate it

---

*This troubleshooting guide is maintained by the community. If you find a solution to a problem not listed here, please consider [contributing](CONTRIBUTING.md) to help others!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:
This document has been translated using the AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator). While we strive for accuracy, please be aware that automated translations may contain errors or inaccuracies. The original document in its native language should be considered the authoritative source. For critical information, professional human translation is recommended. We are not liable for any misunderstandings or misinterpretations arising from the use of this translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->