<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T10:14:01+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "tl"
}
-->
# Gabay sa Pag-aayos ng Problema

Ang gabay na ito ay tutulong sa iyo na lutasin ang mga karaniwang problema kapag nagtatrabaho sa kurikulum ng IoT para sa mga Nagsisimula. Ang mga isyu ay inorganisa ayon sa kategorya para sa madaling pag-navigate.

## Talaan ng mga Nilalaman

- [Mga Isyu sa Instalasyon](../..)
  - [Instalasyon ng Python](../..)
  - [VS Code at mga Extension](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Mga Grove na Library](../..)
- [Mga Isyu sa Hardware](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtual na Device (CounterFit)](../..)
- [Mga Isyu sa Connectivity](../..)
  - [Koneksyon sa WiFi](../..)
  - [Mga Cloud Service](../..)
  - [MQTT](../..)
- [Mga Isyu sa Sensor at Actuator](../..)
  - [Mga Grove Sensor](../..)
  - [Kamera](../..)
  - [Mikropono at Speaker](../..)
- [Mga Isyu sa Development Environment](../..)
  - [VS Code](../..)
  - [Python Virtual Environments](../..)
  - [Mga Depedensiya](../..)
- [Mga Isyu sa Performance](../..)
- [Mga Karaniwang Mensahe ng Error](../..)
- [Paano Humingi ng Tulong](../..)

---

## Mga Isyu sa Instalasyon

### Instalasyon ng Python

#### Problema: Ang bersyon ng Python ay masyadong luma
**Error:** `Kinakailangan ang Python 3.6 o mas mataas`

**Solusyon:**
1. I-download ang pinakabagong Python 3 mula sa [python.org](https://www.python.org/downloads/)
2. Sa panahon ng instalasyon sa Windows, tiyakin na naka-check ang "Add Python to PATH"
3. Beripikahin ang instalasyon:
   ```bash
   python3 --version
   ```

#### Problema: Maramihang bersyon ng Python ang nagdudulot ng salungatan
**Sintomas:** Mali ang bersyon ng Python na tumatakbo, ang mga package ay naiinstall sa maling lokasyon

**Solusyon:**
- **Windows:** Gamitin ang `py -3` sa halip na `python` upang ipatawag nang eksakto ang Python 3
- **macOS/Linux:** Gamitin ang `python3` sa halip ng `python`
- Palaging gumawa at gamitin ang mga virtual environment para sa mga proyekto

#### Problema: Hindi mahanap ang utos na pip
**Error:** `'pip' ay hindi kinikilala bilang internal o external na utos`

**Solusyon:**
1. Subukan ang `pip3` sa halip na `pip`
2. O gamitin ang `python -m pip` o `python3 -m pip`
3. Siguraduhing ang Python ay nadagdag sa PATH (i-reinstall ang Python at tiyaking naka-check ang opsyon)

### VS Code at mga Extension

#### Problema: Hindi gumagana ang Pylance extension
**Sintomas:** Walang Python IntelliSense, code completion, o type checking

**Solusyon:**
1. Buksan ang VS Code Command Palette (`Ctrl+Shift+P` o `Cmd+Shift+P`)
2. Patakbuhin ang "Python: Select Interpreter"
3. Piliin ang tamang Python interpreter (virtual environment kung gumagamit)
4. I-reload ang window ng VS Code

#### Problema: Hindi nadedetect ng VS Code ang virtual environment
**Sintomas:** Mali ang napiling Python interpreter

**Solusyon:**
1. Siguraduhing na-activate ang virtual environment sa terminal
2. Buksan ang Command Palette at patakbuhin ang "Python: Select Interpreter"
3. Piliin ang interpreter mula sa `.venv` na folder
4. Tingnan ang status bar (ibaba kaliwa) kung nagpapakita ng tamang bersyon ng Python

### PlatformIO (Wio Terminal)

#### Problema: Nabibigo ang instalasyon ng PlatformIO
**Error:** Iba't ibang error sa panahon ng instalasyon ng PlatformIO

**Solusyon:**
1. Siguraduhing up to date ang VS Code
2. I-install muna ang C/C++ extension
3. I-restart ang VS Code pagkatapos ma-install ang PlatformIO
4. Suriin ang iyong koneksyon sa internet (nagda-download ang PlatformIO ng malalaking file)

#### Problema: Hindi nadedetect ng PlatformIO ang board
**Sintomas:** Hindi ma-upload ang code sa Wio Terminal

**Solusyon:**
1. Subukan ang ibang USB cable (may mga kable na charging lang)
2. Tingnan ang Device Manager (Windows) o `ls /dev/tty*` (macOS/Linux)
3. I-install o i-update ang USB driver
4. Subukan ang ibang USB port
5. I-slide nang mabilis nang dalawang beses ang power switch sa Wio Terminal para pumasok sa bootloader mode

#### Problema: Mga error sa compilation sa PlatformIO
**Error:** `fatal error: Arduino.h: No such file or directory`

**Solusyon:**
1. Tanggalin ang `.pio` na folder sa iyong proyekto
2. Patakbuhin ang "PlatformIO: Rebuild" mula sa Command Palette
3. Siguraduhing tama ang konfigurasyon ng board sa `platformio.ini`:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove Libraries

#### Problema: Nabibigo ang pag-import ng Grove library sa Raspberry Pi
**Error:** `ModuleNotFoundError: No module named 'grove'`

**Solusyon:**
1. I-reinstall ang Grove libraries:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Kung gumagamit ng virtual environment, maaaring kailanganin mong i-install nang global o kopyahin ang mga library
3. Tiyaking naka-enable ang I2C: `sudo raspi-config nonint do_i2c 0`

#### Problema: Hindi nadedetect ang Grove sensor
**Error:** `IOError: [Errno 121] Remote I/O error`

**Solusyon:**
1. Suriin ang pisikal na koneksyon (siguraduhing tuluyang nakasaksak ang Grove cable)
2. Tiyaking nakakonekta ang sensor sa tamang port (analog, digital, I2C, UART)
3. Patakbuhin ang `i2cdetect -y 1` upang makita kung lumalabas ang device sa I2C bus
4. Subukan ang ibang Grove cable
5. Siguraduhin na maayos ang pagkakaupo ng Grove Base Hat sa Raspberry Pi GPIO pins

---

## Mga Isyu sa Hardware

### Raspberry Pi

#### Problema: Hindi nagbo-boot ang Raspberry Pi
**Sintomas:** Walang display, walang aktibidad ng LED, o rainbow screen

**Solusyon:**
1. **Suriin ang power supply:** Gamitin ang opisyal na 5V 3A USB-C power supply para sa Pi 4
2. **Mga isyu sa SD card:** 
   - I-reformat ang SD card at i-install muli ang Raspberry Pi OS
   - Subukan ang ibang SD card (gamitin ang mga rekomendadong brand)
   - Siguraduhing maayos ang pagkasaksak ng SD card
3. **Suriin ang HDMI connection:** Subukan ang parehong HDMI ports sa Pi 4, gamitin ang HDMI port na pinakamalapit sa power

#### Problema: Hindi makapag-SSH sa Raspberry Pi
**Sintomas:** Connection refused o timeout

**Solusyon:**
1. I-enable ang SSH:
   - Kapag nag-flash ng SD card gamit ang Raspberry Pi Imager, i-configure ang SSH sa advanced options
   - O gumawa ng walang lamang file na pinangalanang `ssh` (walang extension) sa boot partition
2. Hanapin ang IP address ng Pi:
   - Tingnan ang mga nakakonektang device sa iyong router
   - Gamitin ang `ping raspberrypi.local` (kung gumagana ang mDNS)
   - Gamitin ang network scanning tools tulad ng `nmap` o Angry IP Scanner
3. Suriin ang network:
   - Siguraduhing nasa parehong network ang Pi at ang iyong computer
   - Subukang gumamit ng ethernet connection sa halip na WiFi
4. Beripikahin ang username/password (default: username `pi`, password `raspberry`)

#### Problema: Hindi nare-recognize ang Grove Base Hat
**Sintomas:** Hindi gumagana ang sensors, mga error sa I2C

**Solusyon:**
1. Siguraduhing nakaupo nang maayos ang Base Hat sa lahat ng GPIO pins
2. Suriin kung may mga baluktot na pin sa Pi o Base Hat
3. I-enable ang I2C interface:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Beripikahin kung gumagana ang I2C: `i2cdetect -y 1`

#### Problema: Mabagal ang pagtakbo ng Raspberry Pi
**Sintomas:** Mabagal ang UI, matagal mag-responde

**Solusyon:**
1. Suriin ang bilis ng SD card (gamitin ang Class 10 o mas mataas, o SSD sa pamamagitan ng USB)
2. Magbakante ng espasyo sa disk: `df -h` para suriin, tanggalin ang mga hindi kailangan na file
3. Bawasan ang GPU memory sa `raspi-config` kung hindi mabigat gamitin ang camera/display
4. Isara ang mga hindi kailangang application
5. Isaalang-alang ang pag-upgrade sa Pi 4 na may mas maraming RAM kung gamit ang Pi 3 o mas luma pa

### Wio Terminal

#### Problema: Nanatiling blangko ang screen ng Wio Terminal
**Sintomas:** Walang display output pagkatapos mag-upload ng code

**Solusyon:**
1. Suriin kung ini-initialize ng code ang display (TFT_eSPI library)
2. I-update ang firmware ng Wio Terminal mula sa [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Idagdag ang code para sa pag-initialize ng display:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Subukang i-upload ang example sketch mula sa PlatformIO para subukan ang hardware

#### Problema: Hindi gumagana ang WiFi sa Wio Terminal
**Sintomas:** Hindi makakonekta sa WiFi, mga error sa network

**Solusyon:**
1. **I-update ang WiFi firmware:** Sundin ang [Wio Terminal WiFi firmware update guide](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Suriin ang WiFi credentials:** Siguraduhing tama ang SSID at password
3. **WiFi band:** Suportado lamang ng Wio Terminal ang 2.4GHz WiFi (hindi 5GHz)
4. **Lakas ng signal:** Lumapit sa router
5. **Mga setting ng router:** Posibleng hindi gumana ang ilang enterprise/WPA-Enterprise networks

#### Problema: Hindi nare-recognize ng computer ang Wio Terminal
**Sintomas:** Hindi nade-detect ang USB device

**Solusyon:**
1. **Subukan ang ibang USB cable:** Gamitin ang data cable, hindi charging-only cable
2. **Pumasok sa bootloader mode:** I-slide pababa ang power switch nang dalawang beses nang mabilis
   - Dapat pulsing blue LED, lalabas ang device bilang "Arduino" sa Device Manager
3. **I-install ang drivers (Windows):**
   - I-download at i-install ang [Seeed USB driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Subukan ang ibang USB port:** Iwasan ang USB hubs, direktang koneksyon ang gamitin
5. **I-update ang system USB drivers**

#### Problema: Hindi gumagana ang mga sensors sa Wio Terminal
**Sintomas:** Hindi nagbabasa ng data ang mga Grove sensors

**Solusyon:**
1. Suriin ang koneksyon ng Grove cable
2. Tiyaking tama ang ginagamit na Grove port (kaliwa o kanan)
3. Isama ang tamang mga library para sa sensor
4. Suriin ang mga pangangailangan sa kuryente ng sensor
5. Subukan ang sensor gamit ang example code mula sa library

### Virtual Device (CounterFit)

#### Problema: Hindi nagsisimula ang CounterFit app
**Error:** Iba't ibang Python error kapag sinimulan ang CounterFit

**Solusyon:**
1. Siguraduhing activated ang virtual environment
2. I-install o i-reinstall ang CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Suriin kung hindi pa nagagamit ang port 5000:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Patayin ang proseso na gumagamit ng port 5000 o gumamit ng ibang port:
   ```bash
   counterfit --port 5001
   ```

#### Problema: Hindi makakonekta sa CounterFit mula sa code
**Error:** Connection refused o timeout

**Solusyon:**
1. Beripikahin na tumatakbo ang CounterFit: Buksan ang browser sa `http://127.0.0.1:5000`
2. Suriin ang connection URL sa code kung tugma sa address ng CounterFit
3. Siguraduhing hindi hinaharang ng firewall ang koneksyon
4. Subukang i-restart ang parehong CounterFit app at ang iyong code

#### Problema: Hindi lumalabas ang mga sensor sa CounterFit
**Sintomas:** Hindi lumalabas sa CounterFit UI ang mga sensor na ginawa

**Solusyon:**
1. Gumawa ng mga sensor sa CounterFit UI bago patakbuhin ang code
2. I-refresh ang pahina ng browser
3. Tiyaking tugma ang uri ng sensor sa inaasahan ng code
4. I-clear ang cache ng browser

---

## Mga Isyu sa Connectivity

### Koneksyon sa WiFi

#### Problema: Hindi makakonekta ang device sa WiFi
**Sintomas:** Connection timeout, nabigong authentication

**Solusyon:**
1. **Suriin ang SSID at password:** Tiyaking tama ang mga kredensyal
2. **WiFi band:** Karamihan sa mga IoT device ay sumusuporta lamang sa 2.4GHz (hindi 5GHz)
3. **Mga setting ng router:**
   - I-disable ang AP isolation kung naka-enable
   - Gumamit ng WPA2-PSK na seguridad (iwasan ang WPA3, WEP, o open networks)
   - Tiyaking naka-enable ang DHCP
4. **Mga nakatagong network:** Kung naka-hide ang SSID, maaaring kailanganin itong i-configure nang hayagan
5. **Lakas ng signal:** Ilapit ang device sa router
6. **Interference:** Ang iba pang mga device, microwave, o mga pader ay maaaring magdulot ng interference

#### Problema: Madalas nawawala ang koneksyon sa WiFi
**Sintomas:** Paminsan-minsang pagkakakonekta

**Solusyon:**
1. Suriin ang katatagan ng router at isaalang-alang ang pag-reboot
2. I-update ang firmware ng device
3. Gumamit ng static IP sa halip na DHCP
4. Bawasan ang layo sa router o magdagdag ng WiFi extender
5. Suriin ang interference mula sa ibang mga device
6. Siguraduhin na sapat ang power supply (lalo na para sa Raspberry Pi)

### Mga Cloud Service

#### Problema: Hindi makakonekta sa Azure IoT Hub
**Error:** Nabigong authentication, connection refused

**Solusyon:**
1. **Beripikahin ang mga kredensyal:**
   - Suriin kung tama ang connection string
   - Tiyaking walang mga dagdag na espasyo o line breaks sa connection string
2. **Suriin ang pagrerehistro ng device:** Kailangang nakarehistro ang device sa IoT Hub
3. **Firewall/proxy:** Tiyaking pinapayagan ng outbound MQTT (port 8883) o HTTPS (port 443)
4. **Rehiyon ng IoT Hub:** Siguraduhing tumatakbo ang IoT Hub at hindi nasa ibang rehiyon na nagdudulot ng latency
5. **Quota limits:** Suriin kung naabot na ang mga limitasyon ng free tier
6. **Subukan ang koneksyon:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problema: Hindi nagti-trigger ang Azure Functions
**Sintomas:** Naipapadala ang mga mensahe ngunit hindi tumatakbo ang function

**Solusyon:**
1. Suriin kung tumatakbo ang Function App (hindi naka-stop)
2. Beripikahin ang connection string sa Function App settings
3. Tingnan ang mga log ng function sa Azure Portal
4. Siguraduhing tama ang konfigurasyon ng Event Hub compatible endpoint
5. Tiyaking tugma ang format ng mensahe sa inaasahan ng function
6. Suriin ang Function App service plan (consumption vs. dedicated)

### MQTT
#### Problem: Nabibigo ang MQTT connection
**Error:** Connection refused, authentication failed

**Solution:**
1. **Broker address:** Tiyaking tama ang URL/IP ng broker
2. **Port:** Suriin ang numero ng port (1883 para sa unencrypted, 8883 para sa TLS)
3. **Authentication:** Tiyaking tama ang username/password kung kinakailangan
4. **TLS/SSL:** Siguraduhing valid at pinagkakatiwalaan ang mga sertipiko
5. **Firewall:** Suriing hindi na-block ang port
6. **Test gamit ang MQTT client:** Gamitin ang MQTT Explorer o mosquitto_pub/sub para subukan

#### Problem: Hindi natatanggap ang MQTT messages
**Symptoms:** Nai-publish ang mga mensahe ngunit hindi natatanggap ng mga subscriber

**Solution:**
1. **Topic names:** Tiyakin na tumutugma ang subscriber topic sa publisher topic ng eksakto
2. **QoS level:** Subukan ang QoS 1 o 2 imbes na 0
3. **Wildcards:** Suriin na tama ang paggamit ng topic wildcards (`+` para sa single level, `#` para sa multi-level)
4. **Retained messages:** Maaaring i-set ng publisher ang retain flag upang mapanatili ang huling mensahe
5. **Connection timing:** Siguraduhing nakakonekta ang subscriber bago i-publish ang mga mensahe

---

## Mga Isyu sa Sensor at Actuator

### Grove Sensors

#### Problem: Mali ang binabalik na values ng sensor
**Symptoms:** Mga basang 0, -1, o mga walang katuturang values

**Solution:**
1. **Suriin ang mga koneksyon:** Siguraduhing maayos na nakakabit ang sensor
2. **Tamang port:** Tiyaking nasa tamang uri ng port ang sensor:
   - Analog sensors → Analog ports (A0, A2, A4)
   - Digital sensors → Digital ports (D5, D16, D18, atbp.)
   - I2C sensors → I2C ports
3. **Calibration:** May ilang sensor na nangangailangan ng kalibrasyon (soil moisture, light)
4. **Power cycle:** Idiskonekta at ikonekta muli ang sensor
5. **Sensor datasheet:** Suriin ang mga detalye at pangangailangan ng sensor

#### Problem: Laging basa ang capacitive soil moisture sensor
**Symptoms:** Mataas ang basang value ng sensor kahit tuyo

**Solution:**
1. **Kailangang kalibrasyon:** Nangangailangan ng kalibrasyon ang mga soil sensor:
   - Basahin ang value sa hangin (dry baseline)
   - Basahin ang value sa tubig (wet baseline)
   - I-map ang mga reading sa pagitan ng mga ito
2. **Suriin ang coating ng sensor:** Maaaring masira ang coating ng moisture sensor
3. **Pagkakalagay:** Siguraduhing nakausli nang husto ang sensor sa lupa

#### Problem: Mali ang reading ng temperature/humidity sensor
**Symptoms:** Mali ang ipinapakitang temperatura o humidity ng DHT11/DHT22

**Solution:**
1. **Pagkakapalagay ng sensor:** Iwasan ang direktang sikat ng araw, pinagmumulan ng init, o hangin
2. **Warm-up time:** Bigyan ng 2 segundo ang sensor pagkatapos ng power-on bago magbasa
3. **Frequency ng pagbabasa:** Kailangan ng DHT sensors ng pagitan ng huling pagbabasa (hindi bababa sa 2 segundo)
4. **Suriin ang condensation:** Maaaring makaapekto sa mga reading
5. **Kalidad ng sensor:** Mas mababa ang accuracy ng DHT11 kumpara sa DHT22

### Camera

#### Problem: Hindi nade-detect ang kamera sa Raspberry Pi
**Error:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Solution:**
1. **I-enable ang camera interface:**
   ```bash
   sudo raspi-config
   ```
   Pumunta sa Interface Options → Camera → Enable
2. **Suriin ang ribbon cable:** Siguraduhing maayos na naipasok ang camera cable
   - Nakaharap sa USB ports ng Pi Zero ang asul na bahagi
   - Nakaharap palayo sa USB ports ng Pi 4 ang asul na bahagi
3. **I-update ang firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Subukan ang kamera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problem: Mababa ang kalidad ng camera images
**Symptoms:** Malabo, madilim, o mapurol ang mga larawan

**Solution:**
1. **Focus:** Alisin ang protective film sa lens, ayusin ang focus kung maaaring i-adjust
2. **Ilaw:** Siguraduhing sapat ang ilaw
3. **Camera settings:** Ayusin ang exposure, ISO, white balance sa code
4. **Katatagan:** Panatilihing matatag ang camera, gumamit ng tripod kung kailangan
5. **Resolution:** Huwag lumabis sa maximum na resolution ng kamera

### Microphone at Speaker

#### Problem: Walang audio input/output
**Symptoms:** Hindi nakakarecord ang mikropono, hindi tumutugtog ang speaker

**Solution:**
1. **Suriin ang mga koneksyon:** Tiyaking maayos nakakabit ang mga audio device
2. **Subukan ang hardware:**
   - Speaker: `speaker-test -t wav -c 2`
   - Mikropono: `arecord -l` para makita, `arecord test.wav` para mag-record
3. **Volume settings:** Suriin at ayusin ang volume:
   ```bash
   alsamixer
   ```
4. **Piliin ang audio device:** Itakda ang tamang audio device sa code
5. **Driver issues:** I-update ang ALSA o i-reinstall ang audio drivers

#### Problem: Hindi gumagana ang ReSpeaker hat
**Symptoms:** Hindi nade-detect ang audio device

**Solution:**
1. **I-install ang mga driver:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Suriin ang installation:** Dapat makita ang ReSpeaker gamit ang `arecord -l`
3. **I-update ang firmware:** Kailangan ng ilang bersyon ng Pi OS ng pag-update ng driver
4. **Suriin ang pagkakakabit:** Siguraduhing maayos ang pagkakabit ng hat sa mga GPIO pins

---

## Mga Isyu sa Development Environment

### VS Code

#### Problem: Hindi awtomatikong naga-activate ang virtual environment sa terminal
**Symptoms:** Nagbubukas ang terminal pero hindi naka-activate ang venv

**Solution:**
1. **Itakda ang Python interpreter:** Command Palette → "Python: Select Interpreter" → Piliin ang venv
2. **I-restart ang VS Code** pagkatapos pumili ng interpreter
3. **Suriin ang mga setting:** Sa `settings.json`, idagdag:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Hindi tumatakbo ang code sa device
**Symptoms:** Tumatakbo ang code pero walang nangyayari sa device

**Solution:**
1. **Tiyaking naka-save ang code** (tingnan ang tuldok sa tab ng file)
2. **Suriin kung anong Python ang tumatakbo:** `which python` o `where python`
3. **Para sa Wio Terminal:** Siguraduhing na-upload ang code gamit ang PlatformIO (pindutin ang upload button)
4. **Para sa Raspberry Pi:** SSH sa Pi at patakbuhin dito ang code
5. **Tingnan ang output window** para sa mga error

#### Problem: Hindi nagpapakita ng library functions ang IntelliSense
**Symptoms:** Walang autocomplete para sa mga imported modules

**Solution:**
1. Siguraduhing naka-install ang library sa kasalukuyang environment
2. I-reload ang VS Code window
3. Tiyaking tama ang Python interpreter
4. Mag-install ng type stubs kung mayroon: `pip install types-<library-name>`

### Python Virtual Environments

#### Problem: Hindi makagawa ng virtual environment
**Error:** `The virtual environment was not created successfully`

**Solution:**
1. **I-install ang venv module:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Kasama na dapat ito sa Python
   - Windows: I-reinstall ang Python kasama lahat ng components
2. **Suriin ang Python installation:** Tiyaking maayos ang pagkaka-install ng Python
3. **Gamitin ang buong path:** Subukang `python3 -m venv .venv` gamit ang eksaktong tawag sa python3

#### Problem: Mga packages na-install sa maling lokasyon
**Symptoms:** Import error pagkatapos mag-install ng package

**Solution:**
1. **Tiyaking naka-activate ang venv:** Dapat nagpapakita sa prompt ang `(.venv)`
2. **Suriin ang lokasyon ng pip:** `which pip` ay dapat tumuro sa `.venv/bin/pip`
3. **I-reinstall sa venv:** I-activate ang venv, pagkatapos ay `pip install <package>`
4. **Huwag gumamit ng sudo sa pip** sa loob ng virtual environment

#### Problem: Hindi portable ang virtual environment
**Symptoms:** Hindi gumagana ang venv matapos ilipat o sa ibang computer

**Solution:**
1. **Huwag ilipat ang venv:** Burahin at gumawa muli sa bagong lokasyon
2. **Gamitin ang requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Gumawa muli ng venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # o activate.bat sa Windows
   pip install -r requirements.txt
   ```

### Dependencies

#### Problem: Nabibigo ang pag-install ng package
**Error:** Iba't ibang pip errors habang nag-iinstall

**Solution:**
1. **I-update ang pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **I-install ang build tools:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: I-install ang Visual Studio Build Tools
3. **Suriin ang koneksyon sa internet**
4. **Subukan ang ibang package index:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **Mag-install ng specific na bersyon:** `pip install <package>==<version>`

#### Problem: Conflict sa dependency
**Error:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Solution:**
1. **Gumamit ng bagong virtual environment** para sa bawat proyekto
2. **I-update ang mga packages:** `pip install --upgrade <package>`
3. **Suriin ang requirements:** Gumamit ng `pip check` para makita ang mga conflict
4. **Mag-install ng compatible na bersyon:** Magtakda ng version ranges sa requirements.txt

---

## Mga Isyu sa Performance

### Problem: Mabagal tumakbo ang code
**Symptoms:** Mga delay, timeout, hindi tumutugon

**Solution:**
1. **Bawasan ang frequency ng pagbabasa sa sensor:** Huwag basahin nang masyadong madalas
2. **I-optimize ang loops:** Iwasan ang busy-waiting, gumamit ng sleep() o delay
3. **Mga isyu sa memorya:**
   - Isara ang mga hindi kailangang application
   - Palayain ang espasyo sa storage
   - Monitor gamit ang `top` o `htop` sa Pi
4. **Bilis ng SD card:** Gumamit ng mas mabilis na SD card o SSD para sa Raspberry Pi
5. **Delay sa network:** Gumamit ng async operations para sa network calls

### Problem: Mga error na out of memory
**Error:** `MemoryError` o pag-hang ng system

**Solution:**
1. **Para sa Raspberry Pi:**
   - Isara ang mga hindi kailangang application
   - Palakihin ang swap space
   - Gumamit ng mas magaan na OS (Lite version)
   - Mag-upgrade ng RAM (meron ang Pi 4 ng 2/4/8GB options)
2. **Para sa Wio Terminal:**
   - Bawasan ang buffer sizes
   - Gumamit ng mas maliit na mga imahe
   - I-optimize ang paggamit ng strings
   - Suriin ang memory leaks (mga hindi nailalabas na memorya)

### Problem: Pagkawala o pagkasira ng data
**Symptoms:** Nawawalang mga mensahe, nasisirang mga files

**Solution:**
1. **Mga isyu sa SD card:**
   - Gumamit ng kalidad na SD cards (iwasan ang mura/peke)
   - Regular na backups
   - Malinis na shutdown (huwag basta tanggalin ang power)
2. **Buffer overflow:** Palakihin ang mga buffer sizes sa code
3. **Kalidad ng network:** Mag-implement ng retry logic at error handling
4. **Quality of Service:** Gumamit ng MQTT QoS 1 o 2 para sa mahahalagang mensahe

---

## Mga Karaniwang Error Messages

### `ModuleNotFoundError: No module named 'X'`
**Cause:** Hindi naka-install ang package o hindi naka-activate ang virtual environment

**Solution:**
```bash
pip install X
```
Siguraduhing naka-activate muna ang virtual environment.

### `Permission denied` sa Linux/macOS
**Cause:** Kailangan ng mataas na pahintulot o isyu sa mga permission ng file

**Solution:**
- Para sa system operations: Gumamit ng `sudo`
- Para sa pip: HUWAG gumamit ng sudo sa venv, i-activate muna ang venv
- Para sa serial port: Idagdag ang user sa dialout group: `sudo usermod -a -G dialout $USER`, pagkatapos ay logout/login

### `OSError: [Errno 98] Address already in use`
**Cause:** Ginagamit na ang port ng ibang proseso

**Solution:**
1. Hanapin ang prosesong gumagamit ng port: `lsof -i :<port>` o `netstat -ano | findstr :<port>`
2. Patayin ang proseso o gumamit ng ibang port sa iyong code

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Cause:** Nabibigo ang pag-validate ng SSL certificate

**Solution:**
1. I-update ang mga sertipiko: `pip install --upgrade certifi`
2. Suriin ang tamang oras ng system: `date`
3. Para lang sa development (hindi sa production): I-disable ang verification sa code

### `IndentationError: unexpected indent`
**Cause:** Problema sa indentation ng Python (halo ng tabs/spaces)

**Solution:**
1. Gumamit ng pantay-pantay na indentation (4 spaces ay standard sa Python)
2. I-configure ang editor na gumamit ng spaces imbes tabs
3. Sa VS Code: Itakda ang `"editor.insertSpaces": true` at `"editor.tabSize": 4`

### `UnicodeDecodeError` o `UnicodeEncodeError`
**Cause:** Problema sa character encoding

**Solution:**
```python
# Kapag nagbabasa ng mga file
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Kapag nagsusulat ng mga file
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Paghahanap ng Tulong

Kung sinubukan mo na ang mga troubleshooting steps na ito at may problema pa rin:

### 1. Suriin ang Umiiral na Mga Resources
- **Documentation:** Balikan ang [README](README.md) at mga instruksyon ng aralin
- **Hardware guides:** Tingnan ang [hardware.md](hardware.md) para sa impormasyon tungkol sa hardware
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) para sa mga Grove components

### 2. Maghanap ng Katulad na Mga Isyu
- **GitHub Issues:** Maghanap sa [existing issues](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Maghanap ng mga error message
- **Mga forum ng device:** Tingnan ang mga forum ng Raspberry Pi o Arduino

### 3. Gumawa ng Isyu sa GitHub
Kung hindi mo makita ang solusyon:
1. Pumunta sa [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Pindutin ang "New Issue"
3. Magbigay ng:
   - Malinaw na paglalarawan ng problema
   - Mga hakbang para maulit ang problema
   - Mga error message (buong teksto)
   - Mga bersyon ng hardware/software
   - Ano ang mga nasubukan mo na
   - Mga screenshot kung kinakailangan

### 4. Sumali sa Komunidad
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Magbigay ng Magandang Bug Reports
Ang magandang bug report ay naglalaman ng:
- **Kapaligiran:** OS, bersyon ng Python, hardware na ginamit
- **Mga hakbang upang makopya:** Eksaktong mga hakbang na nagdudulot ng isyu
- **Inaasahang pag-uugali:** Ano ang dapat mangyari
- **Aktwal na pag-uugali:** Ano talaga ang nangyayari
- **Mga mensahe ng error:** Kumpletong teksto ng error, hindi mga screenshot
- **Code:** Pinakamaliit na halimbawa ng code na nagpapakita ng isyu

---

## Mga Tip para sa Pag-iwas

### Pangkalahatang Pinakamahusay na Praktis
1. **Magpanatili ng backup:** Regular na backup ng gumaganang SD cards/code
2. **Idokumento ang mga pagbabago:** Itala kung ano ang gumagana sa mga komento
3. **Gamitin ang version control:** Gamitin ang git para subaybayan ang mga pagbabago sa code
4. **Subukan ng paunti-unti:** Subukan ang maliliit na pagbabago bago pagsamahin
5. **Basahin ang mga mensahe ng error:** Madalas itong nagsasabi nang eksakto kung ano ang mali
6. **Mag-update nang regular:** Panatilihing napapanahon ang software/firmware
7. **Gumamit ng kalidad na mga bahagi:** Iwasan ang mura at mahihinang mga kable/power supply
8. **Matatag na kuryente:** Gumamit ng angkop na power supply (lalong lalo na sa Pi)

### Daloy ng Pag-unlad
1. **Magsimula sa simple:** Magsimula sa halimbawa ng code na gumagana
2. **Isang pagbabago sa isang pagkakataon:** Mas madaling makita kung ano ang nasira
3. **Madalas na pagsusuri:** Agad makita ang mga isyu
4. **Panatilihing malinis:** Ayusin nang maayos ang mga file at code
5. **Magkomento sa code:** Magpapasalamat ang hinaharap na ikaw

---

*Ang gabay sa pagsasaayos na ito ay pinangangasiwaan ng komunidad. Kung makahanap ka ng solusyon sa isang problemang hindi nakalista dito, mangyaring isaalang-alang ang [pagsusumite](CONTRIBUTING.md) upang matulungan ang iba!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Paunawa**:
Ang dokumentong ito ay naisalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagamat nagsusumikap kami para sa katumpakan, mangyaring tandaan na ang mga awtomatikong pagsasalin ay maaaring magkaroon ng mga pagkakamali o hindi tumpak na bahagi. Ang orihinal na dokumento sa orihinal nitong wika ang dapat ituring na pinakapinagkakatiwalaang sanggunian. Para sa mahahalagang impormasyon, inirerekomenda ang propesyonal na pagsasaling-tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng salin na ito.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->