<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-07T01:07:55+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "pcm"
}
-->
# Troubleshooting Guide

Dis guide go help you solve common wahala wen you dey work wit di IoT for Beginners curriculum. Wahala dem dey organized by category so e go easy to waka through dem.

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

#### Problem: Python version dey too old
**Error:** `Python 3.6 or higher is required`

**Solution:**
1. Download di latest Python 3 from [python.org](https://www.python.org/downloads/)
2. For Windows installation, make sure say you check "Add Python to PATH"
3. Verify di installation:
   ```bash
   python3 --version
   ```

#### Problem: Plenty Python versions dey cause wahala
**Symptoms:** Di wrong Python version dey run, packages dey install for wrong place

**Solution:**
- **Windows:** Use `py -3` instead of `python` to explicitly call Python 3
- **macOS/Linux:** Use `python3` instead of `python`
- Always create and use virtual environments for projects

#### Problem: pip command no dey work
**Error:** `'pip' is not recognized as an internal or external command`

**Solution:**
1. Try `pip3` instead of `pip`
2. Or use `python -m pip` or `python3 -m pip`
3. Make sure say Python dey added to PATH (reinstall Python and check di option)

### VS Code and Extensions

#### Problem: Pylance extension no dey work
**Symptoms:** No Python IntelliSense, code completion, or type checking

**Solution:**
1. Open VS Code Command Palette (`Ctrl+Shift+P` or `Cmd+Shift+P`)
2. Run "Python: Select Interpreter"
3. Choose di correct Python interpreter (virtual environment if you dey use one)
4. Reload VS Code window

#### Problem: VS Code no dey detect virtual environment
**Symptoms:** Wrong Python interpreter selected

**Solution:**
1. Make sure say you don activate di virtual environment for terminal
2. Open Command Palette and run "Python: Select Interpreter"
3. Select di interpreter from `.venv` folder
4. Check di status bar (bottom left) make e show di correct Python version

### PlatformIO (Wio Terminal)

#### Problem: PlatformIO installation dey fail
**Error:** Different errors dey happen during PlatformIO installation

**Solution:**
1. Make sure say VS Code dey up to date
2. Install di C/C++ extension first
3. Restart VS Code after you don install PlatformIO
4. Check your internet connection (PlatformIO dey download big big files)

#### Problem: Board no dey detected by PlatformIO
**Symptoms:** You no fit upload code to Wio Terminal

**Solution:**
1. Try different USB cable (some cables na charge-only)
2. Check Device Manager (Windows) or `ls /dev/tty*` (macOS/Linux)
3. Install or update USB drivers
4. Try different USB port
5. Slide di power switch for Wio Terminal two times sharp sharp to enter bootloader mode

#### Problem: Compilation errors for PlatformIO
**Error:** `fatal error: Arduino.h: No such file or directory`

**Solution:**
1. Delete di `.pio` folder inside your project
2. Run "PlatformIO: Rebuild" from Command Palette
3. Make sure di `platformio.ini` get correct board configuration:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove Libraries

#### Problem: Grove library no dey import for Raspberry Pi
**Error:** `ModuleNotFoundError: No module named 'grove'`

**Solution:**
1. Reinstall Grove libraries:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. If you dey use virtual environment, you fit need install am globally or copy libraries
3. Check if I2C don enable: `sudo raspi-config nonint do_i2c 0`

#### Problem: Grove sensor no dey detected
**Error:** `IOError: [Errno 121] Remote I/O error`

**Solution:**
1. Check physical connections (make sure say Grove cable full ground)
2. Verify sensor dey connected to correct port (analog, digital, I2C, UART)
3. Run `i2cdetect -y 1` to check if device dey show for I2C bus
4. Try different Grove cable
5. Make sure Grove Base Hat dey properly sit for Raspberry Pi GPIO pins

---

## Hardware Issues

### Raspberry Pi

#### Problem: Raspberry Pi no go boot
**Symptoms:** No display, no LED light dey blink, or rainbow screen

**Solution:**
1. **Check power supply:** Use official 5V 3A USB-C power supply for Pi 4
2. **SD card wahala:** 
   - Reformat SD card and reinstall Raspberry Pi OS
   - Try different SD card (use recommended brands)
   - Make sure SD card properly insert
3. **Check HDMI connection:** Try both HDMI ports for Pi 4, use di one wey near power

#### Problem: You no fit SSH go Raspberry Pi
**Symptoms:** Connection refused or timeout

**Solution:**
1. Enable SSH:
   - When you dey flash SD card with Raspberry Pi Imager, configure SSH for advanced options
   - Or create empty file wey dem call `ssh` (no extension) for boot partition
2. Find Pi IP address:
   - Check your router connected devices
   - Use `ping raspberrypi.local` (if mDNS dey work)
   - Use network scanning tools like `nmap` or Angry IP Scanner
3. Check network:
   - Make sure Pi dey for same network wit your computer
   - Try ethernet connection instead of WiFi
4. Verify username/password (default: username `pi`, password `raspberry`)

#### Problem: Grove Base Hat no dey recognized
**Symptoms:** Sensors no dey work, I2C errors

**Solution:**
1. Make sure Base Hat properly sit on all GPIO pins
2. Check for bent pins on Pi or Base Hat
3. Enable I2C interface:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Verify I2C dey work: `i2cdetect -y 1`

#### Problem: Raspberry Pi dey slow
**Symptoms:** Laggy UI, slow response

**Solution:**
1. Check SD card speed (use Class 10 or better, or SSD via USB)
2. Free up disk space: `df -h` check am, delete unnecessary files
3. Reduce GPU memory inside `raspi-config` if you no too dey use camera/display
4. Close apps wey no need
5. Try upgrade to Pi 4 with more RAM if you still dey use Pi 3 or older one

### Wio Terminal

#### Problem: Wio Terminal screen dey blank
**Symptoms:** No display output after you upload code

**Solution:**
1. Check if code dey initialize di display (TFT_eSPI library)
2. Update Wio Terminal firmware from [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Add display initialization code:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Try upload example sketch from PlatformIO to test hardware

#### Problem: WiFi no dey work for Wio Terminal
**Symptoms:** No fit connect WiFi, network errors

**Solution:**
1. **Update WiFi firmware:** Follow [Wio Terminal WiFi firmware update guide](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Check WiFi credentials:** Make sure SSID and password correct
3. **WiFi band:** Wio Terminal only fit use 2.4GHz WiFi (no 5GHz)
4. **Signal strength:** Move closer to router
5. **Router settings:** Some enterprise/WPA-Enterprise networks no dey work

#### Problem: Wio Terminal no dey recognized by computer
**Symptoms:** USB device no dey detected

**Solution:**
1. **Try different USB cable:** Use data cable, no be charge-only cable
2. **Enter bootloader mode:** Slide power switch down two times sharp sharp
   - Blue LED go pulse, device go show as "Arduino" for Device Manager
3. **Install drivers (Windows):**
   - Download and install [Seeed USB driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Try different USB port:** No use USB hubs, use direct connection
5. **Update system USB drivers**

#### Problem: Sensors no dey work for Wio Terminal
**Symptoms:** Grove sensors no dey read data

**Solution:**
1. Check Grove cable connections
2. Make sure you dey use correct Grove port (left or right)
3. Include correct libraries for sensor
4. Check sensor power requirements
5. Test sensor with example code from library

### Virtual Device (CounterFit)

#### Problem: CounterFit app no go start
**Error:** Different Python errors when you start CounterFit

**Solution:**
1. Make sure virtual environment don activate
2. Install or reinstall CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Check if port 5000 no dey already use:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Kill process wey dey use port 5000 or use different port:
   ```bash
   counterfit --port 5001
   ```

#### Problem: No fit connect to CounterFit from code
**Error:** Connection refused or timeout

**Solution:**
1. Verify say CounterFit dey run: Open browser go `http://127.0.0.1:5000`
2. Check connection URL inside code match CounterFit address
3. Make sure firewall no dey block connection
4. Try restart both CounterFit app and your code

#### Problem: Sensors no dey show for CounterFit
**Symptoms:** Created sensors no dey show for CounterFit UI

**Solution:**
1. Create sensors for CounterFit UI before you run code
2. Refresh browser page
3. Check sensor type match wetin code expect
4. Clear browser cache

---

## Connectivity Issues

### WiFi Connection

#### Problem: Device no fit connect to WiFi
**Symptoms:** Connection timeout, authentication fail

**Solution:**
1. **Check SSID and password:** Make sure credentials correct
2. **WiFi band:** Most IoT devices only support 2.4GHz (no 5GHz)
3. **Router settings:**
   - Disable AP isolation if e enable
   - Use WPA2-PSK security (no use WPA3, WEP, or open network)
   - Make sure DHCP dey enable
4. **Hidden networks:** If SSID hidden, you fit need explicitly configure am
5. **Signal strength:** Move device closer to router
6. **Interference:** Other devices, microwaves, or walls fit interfere

#### Problem: WiFi connection dey drop often
**Symptoms:** Connection dey come and go

**Solution:**
1. Check router stability and consider restart am
2. Update device firmware
3. Use static IP instead DHCP
4. Reduce distance to router or add WiFi extender
5. Check interference from other devices
6. Make sure power supply steady (especially for Raspberry Pi)

### Cloud Services

#### Problem: No fit connect to Azure IoT Hub
**Error:** Authentication fail, connection refused

**Solution:**
1. **Verify credentials:**
   - Check say connection string correct
   - Make sure no extra spaces or line breaks inside connection string
2. **Check device registration:** Device must register for IoT Hub
3. **Firewall/proxy:** Make sure outbound MQTT (port 8883) or HTTPS (port 443) dey allowed
4. **IoT Hub region:** Make sure IoT Hub dey run and no dey different region wey dey cause latency
5. **Quota limits:** Check if free tier limit don pass
6. **Test connection:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problem: Azure Functions no dey trigger
**Symptoms:** Messages dey send but function no dey run

**Solution:**
1. Check say Function App dey run (no stop)
2. Verify connection string for Function App settings
3. Check function logs for Azure Portal
4. Make sure Event Hub compatible endpoint configure correct
5. Verify message format match function expectations
6. Check Function App service plan (consumption or dedicated)

### MQTT
#### Problem: MQTT connection no fit connect
**Error:** Connection refused, authentication fail

**Solution:**
1. **Broker address:** Make sure broker URL/IP dey correct
2. **Port:** Check port number (1883 if no encryption, 8883 for TLS)
3. **Authentication:** Make sure username/password dey correct if dem need am
4. **TLS/SSL:** Make sure certificates valid and dem trust am
5. **Firewall:** Check say port no block
6. **Test with MQTT client:** Use MQTT Explorer or mosquitto_pub/sub test am

#### Problem: MQTT messages no dey reach
**Symptoms:** Messages publish but subscribers no receive

**Solution:**
1. **Topic names:** Make sure subscriber topic and publisher topic match well well
2. **QoS level:** Try QoS 1 or 2 no be 0
3. **Wildcards:** Check say topic wildcards dem use correct (`+` for one level, `#` for multiple levels)
4. **Retained messages:** Publisher fit set retain flag to keep last message
5. **Connection timing:** Make sure subscriber connect before messages publish

---

## Sensor and Actuator Wahala

### Grove Sensors

#### Problem: Sensor dey give wrong values
**Symptoms:** Readings na 0, -1, or nonsense values

**Solution:**
1. **Check connections:** Make sure sensor connect well
2. **Correct port:** Make sure sensor dey correct port type:
   - Analog sensors → Analog ports (A0, A2, A4)
   - Digital sensors → Digital ports (D5, D16, D18, etc.)
   - I2C sensors → I2C ports
3. **Calibration:** Some sensors need calibration (soil moisture, light)
4. **Power cycle:** Unplug and plug sensor back
5. **Sensor datasheet:** Check sensor specs and wetin e need

#### Problem: Capacitive soil moisture sensor always say wet
**Symptoms:** Sensor dey read high moisture even if soil dry

**Solution:**
1. **Calibration needed:** Soil sensors need calibration:
   - Read value for air (dry baseline)
   - Read value for water (wet baseline)
   - Map readings between these values
2. **Check sensor coating:** Moisture sensors fit spoil if coating damage
3. **Placement:** Make sure sensor fully put insi soil

#### Problem: Temperature/humidity sensor readings no correct
**Symptoms:** DHT11/DHT22 dey show wrong temperature or humidity

**Solution:**
1. **Sensor placement:** Avoid direct sunlight, heat, or strong airflow
2. **Warm-up time:** Allow sensor 2 seconds after power on before read
3. **Read frequency:** DHT sensors need time between reads (at least 2 seconds)
4. **Check for condensation:** Fit affect readings
5. **Sensor quality:** DHT11 no too accurate like DHT22

### Camera

#### Problem: Camera no dey detect for Raspberry Pi
**Error:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Solution:**
1. **Enable camera interface:**
   ```bash
   sudo raspi-config
   ```
   Go Interface Options → Camera → Enable
2. **Check ribbon cable:** Make sure camera cable correctly insert
   - Blue side face USB ports for Pi Zero
   - Blue side face away from USB ports for Pi 4
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

#### Problem: Camera pictures no clear
**Symptoms:** Blurry, dark, or washed-out pictures

**Solution:**
1. **Focus:** Remove protective film from lens, adjust focus if fit adjust
2. **Lighting:** Make sure light enuf
3. **Camera settings:** Adjust exposure, ISO, white balance for code
4. **Stability:** Keep camera steady, use tripod if need
5. **Resolution:** No exceed camera max resolution

### Microphone and Speaker

#### Problem: No sound input/output
**Symptoms:** Microphone no record, speaker no play sound

**Solution:**
1. **Check connections:** Make sure audio devices well connect
2. **Test hardware:**
   - Speaker: `speaker-test -t wav -c 2`
   - Microphone: `arecord -l` to list, `arecord test.wav` to record
3. **Volume settings:** Check and adjust volume:
   ```bash
   alsamixer
   ```
4. **Select audio device:** Specify correct audio device for code
5. **Driver issues:** Update ALSA or reinstall audio drivers

#### Problem: ReSpeaker hat no dey work
**Symptoms:** Audio device no detect

**Solution:**
1. **Install drivers:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Check installation:** `arecord -l` suppose list ReSpeaker
3. **Update firmware:** Some Pi OS versions need driver updates
4. **Check seating:** Make sure hat proper connect to GPIO pins

---

## Development Environment Wahala

### VS Code

#### Problem: Terminal no dey activate virtual environment automatically
**Symptoms:** Terminal open but venv no activate

**Solution:**
1. **Set Python interpreter:** Command Palette → "Python: Select Interpreter" → Choose venv
2. **Restart VS Code** after selecting interpreter
3. **Check settings:** For `settings.json`, add:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Code no dey run for device
**Symptoms:** Code dey run but nothing happen for device

**Solution:**
1. **Make sure code save** (check dot for file tab)
2. **Check which Python dey run:** `which python` or `where python`
3. **For Wio Terminal:** Make sure code upload via PlatformIO (click upload button)
4. **For Raspberry Pi:** SSH into Pi and run code there
5. **Check output window** for errors

#### Problem: IntelliSense no dey show library functions
**Symptoms:** No autocomplete for imported modules

**Solution:**
1. Make sure library dey install for current environment
2. Reload VS Code window
3. Check Python interpreter dey correct
4. Install type stubs if dey: `pip install types-<library-name>`

### Python Virtual Environments

#### Problem: No fit create virtual environment
**Error:** `The virtual environment was not created successfully`

**Solution:**
1. **Install venv module:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: E suppose dey inside Python
   - Windows: Reinstall Python with all components
2. **Check Python installation:** Make sure Python well install
3. **Use full path:** Try `python3 -m venv .venv` with explicit python3 command

#### Problem: Packages install for wrong place
**Symptoms:** Import error after package install

**Solution:**
1. **Make sure venv activate:** Command prompt go show `(.venv)`
2. **Check pip location:** `which pip` suppose point to `.venv/bin/pip`
3. **Reinstall for venv:** Activate venv, then `pip install <package>`
4. **No use sudo with pip** inside virtual environment

#### Problem: Virtual environment no portable
**Symptoms:** Venv no dey work after move or for different computer

**Solution:**
1. **No move venvs:** Delete and recreate for new location
2. **Use requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Recreate venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # or run activate.bat for Windows
   pip install -r requirements.txt
   ```

### Dependencies

#### Problem: Package installation fail
**Error:** Different pip errors during installation

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
1. **Use fresh virtual environment** for every project
2. **Update packages:** `pip install --upgrade <package>`
3. **Check requirements:** Use `pip check` to find conflicts
4. **Install compatible versions:** Specify version ranges for requirements.txt

---

## Performance Wahala

### Problem: Code dey run slow
**Symptoms:** Delays, timeouts, e no dey respond well

**Solution:**
1. **Reduce sensor read frequency:** No read sensors too many times
2. **Optimize loops:** No busy-wait, use sleep() or delay
3. **Memory wahala:**
   - Close apps wey no need
   - Free storage space
   - Monitor with `top` or `htop` for Pi
4. **SD card speed:** Use faster SD card or SSD for Raspberry Pi
5. **Network delays:** Use async operations for network calls

### Problem: Out of memory errors
**Error:** `MemoryError` or system freeze

**Solution:**
1. **For Raspberry Pi:**
   - Close unneeded apps
   - Increase swap space
   - Use lighter OS (Lite version)
   - Upgrade RAM (Pi 4 get 2/4/8GB options)
2. **For Wio Terminal:**
   - Reduce buffer sizes
   - Use smaller images
   - Optimize string usage
   - Check for memory leaks (unreleased memory)

### Problem: Data loss or corruption
**Symptoms:** Messages missing, files corrupted

**Solution:**
1. **SD card wahala:**
   - Use quality SD cards (no cheap or fake ones)
   - Backup regularly
   - Clean shutdown (no unplug directly)
2. **Buffer overflow:** Increase buffer sizes for code
3. **Network reliability:** Use retry logic and error handling
4. **Quality of Service:** Use MQTT QoS 1 or 2 for important messages

---

## Common Error Messages

### `ModuleNotFoundError: No module named 'X'`
**Cause:** Package no install or virtual environment no activate

**Solution:**
```bash
pip install X
```
Make sure virtual environment don activate first.

### `Permission denied` on Linux/macOS
**Cause:** Need elevated permissions or file permission problem

**Solution:**
- For system commands: Use `sudo`
- For pip: NO use sudo with venv, activate venv first
- For serial port: Add user to dialout group: `sudo usermod -a -G dialout $USER`, then logout/login

### `OSError: [Errno 98] Address already in use`
**Cause:** Port don already dey use by another process

**Solution:**
1. Find process wey dey use port: `lsof -i :<port>` or `netstat -ano | findstr :<port>`
2. Kill process or use different port inside your code

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Cause:** SSL certificate validation fail

**Solution:**
1. Update certificates: `pip install --upgrade certifi`
2. Check system time correct: `date`
3. For development only (no production): Disable verification for code

### `IndentationError: unexpected indent`
**Cause:** Python indentation wahala (mix tabs and spaces)

**Solution:**
1. Use consistent indentation (4 spaces na Python standard)
2. Configure editor to use spaces not tabs
3. VS Code: Set `"editor.insertSpaces": true` and `"editor.tabSize": 4`

### `UnicodeDecodeError` or `UnicodeEncodeError`
**Cause:** Character encoding wahala

**Solution:**
```python
# Wen you dey read files
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Wen you dey write files
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## How to Get Help

If you don try all these troubleshooting steps and you still get wahala:

### 1. Check Existing Resources
- **Documentation:** Read [README](README.md) and lesson instructions
- **Hardware guides:** Check [hardware.md](hardware.md) for hardware info
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) for Grove parts

### 2. Search for Similar Issues
- **GitHub Issues:** Search [existing issues](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Search error messages
- **Device forums:** Check Raspberry Pi or Arduino forums

### 3. Create a GitHub Issue
If you no fit find solution:
1. Go [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Click "New Issue"
3. Give:
   - Clear description of problem
   - Steps to reproduce
   - Error messages (full text)
   - Hardware/software versions
   - Wetin you don try before
   - Screenshots if e fit help

### 4. Join the Community
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Provide Good Bug Reports
Good bug report gots to get:
- **Environment:** OS, Python version, hardware wey dem use
- **Steps to reproduce:** Exact steps wey dey cause the mata
- **Expected behavior:** Wetin suppose happen
- **Actual behavior:** Wetin really dey happen
- **Error messages:** Complete error text, no screenshots
- **Code:** Small code example wey fit produce the matter

---

## Tips for Prevention

### General Best Practices
1. **Keep backups:** Regular backup of working SD cards/code
2. **Document changes:** Write down wetin dey work inside comments
3. **Version control:** Use git to track code changes
4. **Test incrementally:** Test small small changes before you join dem together
5. **Read error messages:** Dem dey usually yan you exactly wetin wrong
6. **Update regularly:** Keep software/firmware up to date
7. **Use quality components:** No use cheap cables/power supplies
8. **Stable power:** Use correct power supply (especially Pi)

### Development Workflow
1. **Start simple:** Begin with example code wey dey work
2. **One change at a time:** E go easier to find wetin break
3. **Test frequently:** Catch problems early
4. **Keep it clean:** Arrange files and code well well
5. **Comment code:** Future you go appreciate am

---

*Dis troubleshooting guide na community dey maintain am. If you find solution to problem wey no dey here, abeg consider [contributing](CONTRIBUTING.md) to help others!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclaimer**:
Dis dokiment na di one wey AI translation service [Co-op Translator](https://github.com/Azure/co-op-translator) translate. Even though we try make e correct, abeg sabi say automated translation fit get some mistakes or gbege. Di original dokiment wey e dey for im own language na di correct one wey you suppose trust. If na serious mata, na professional human translation you suppose use. We no go carry any blame if people no understand well or dem knack wrong meaning from dis translation.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->