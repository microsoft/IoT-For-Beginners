<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T06:34:15+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "da"
}
-->
# Fejlfinding

Denne guide hjælper dig med at løse almindelige problemer, når du arbejder med IoT for Beginners pensum. Problemer er organiseret efter kategori for nem navigation.

## Indholdsfortegnelse

- [Installationsproblemer](../..)
  - [Python Installation](../..)
  - [VS Code og Udvidelser](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove Biblioteker](../..)
- [Hardwareproblemer](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuel Enhed (CounterFit)](../..)
- [Forbindelsesproblemer](../..)
  - [WiFi Forbindelse](../..)
  - [Cloud Services](../..)
  - [MQTT](../..)
- [Sensor- og Aktuatorproblemer](../..)
  - [Grove Sensorer](../..)
  - [Kamera](../..)
  - [Mikrofon og Højttaler](../..)
- [Udviklingsmiljøproblemer](../..)
  - [VS Code](../..)
  - [Python Virtuelle Miljøer](../..)
  - [Afhængigheder](../..)
- [Ydeevneproblemer](../..)
- [Almindelige Fejlmeddelelser](../..)
- [Få Hjælp](../..)

---

## Installationsproblemer

### Python Installation

#### Problem: Python-version er for gammel
**Fejl:** `Python 3.6 eller højere er påkrævet`

**Løsning:**
1. Download den nyeste Python 3 fra [python.org](https://www.python.org/downloads/)
2. Under installationen på Windows, vælg "Add Python to PATH"
3. Bekræft installation:
   ```bash
   python3 --version
   ```

#### Problem: Flere Python-versioner skaber konflikter
**Symptomer:** Forkert Python-version kører, pakker installeres til forkert sted

**Løsning:**
- **Windows:** Brug `py -3` i stedet for `python` for eksplicit at køre Python 3
- **macOS/Linux:** Brug `python3` i stedet for `python`
- Opret og brug altid virtuelle miljøer til projekter

#### Problem: pip-kommando ikke fundet
**Fejl:** `'pip' genkendes ikke som intern eller ekstern kommando`

**Løsning:**
1. Prøv `pip3` i stedet for `pip`
2. Eller brug `python -m pip` eller `python3 -m pip`
3. Sørg for, at Python er tilføjet til PATH (geninstaller Python og vælg denne mulighed)

### VS Code og Udvidelser

#### Problem: Pylance-udvidelse virker ikke
**Symptomer:** Ingen Python IntelliSense, kodefuldførelse eller typekontrol

**Løsning:**
1. Åbn VS Code Command Palette (`Ctrl+Shift+P` eller `Cmd+Shift+P`)
2. Kør "Python: Select Interpreter"
3. Vælg den korrekte Python-tolk (virtuel miljø hvis brugt)
4. Genindlæs VS Code-vinduet

#### Problem: VS Code opdager ikke virtuelt miljø
**Symptomer:** Forkert Python-tolk valgt

**Løsning:**
1. Sørg for at have aktiveret det virtuelle miljø i terminalen
2. Åbn Command Palette og kør "Python: Select Interpreter"
3. Vælg tolk fra `.venv` mappen
4. Tjek statuslinjen (nederst til venstre) viser korrekt Python-version

### PlatformIO (Wio Terminal)

#### Problem: PlatformIO installation fejler
**Fejl:** Forskellige fejl under PlatformIO installation

**Løsning:**
1. Sørg for, at VS Code er opdateret
2. Installer C/C++ udvidelsen først
3. Genstart VS Code efter installation af PlatformIO
4. Tjek internetforbindelse (PlatformIO downloader store filer)

#### Problem: Board ikke detekteret af PlatformIO
**Symptomer:** Kan ikke uploade kode til Wio Terminal

**Løsning:**
1. Prøv et andet USB-kabel (nogle kabler er kun til opladning)
2. Tjek Enhedshåndtering (Windows) eller `ls /dev/tty*` (macOS/Linux)
3. Installer eller opdater USB-drivere
4. Prøv en anden USB-port
5. Skub strømafbryderen på Wio Terminal to gange hurtigt for at gå i bootloader-tilstand

#### Problem: Kompileringsfejl i PlatformIO
**Fejl:** `fatal error: Arduino.h: No such file or directory`

**Løsning:**
1. Slet `.pio` mappen i dit projekt
2. Kør "PlatformIO: Rebuild" fra Command Palette
3. Sørg for `platformio.ini` har korrekt board-konfiguration:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove Biblioteker

#### Problem: Grove bibliotek import fejler på Raspberry Pi
**Fejl:** `ModuleNotFoundError: No module named 'grove'`

**Løsning:**
1. Geninstaller Grove biblioteker:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Hvis du bruger virtuelt miljø, kan du være nødt til at installere globalt eller kopiere biblioteker
3. Bekræft at I2C er aktiveret: `sudo raspi-config nonint do_i2c 0`

#### Problem: Grove sensor ikke detekteret
**Fejl:** `IOError: [Errno 121] Remote I/O error`

**Løsning:**
1. Tjek fysiske forbindelser (sørg for at Grove-kablet er helt indsat)
2. Bekræft at sensor er tilsluttet korrekt port (analog, digital, I2C, UART)
3. Kør `i2cdetect -y 1` for at se, om enheden vises på I2C-bussen
4. Prøv et andet Grove-kabel
5. Sørg for at Grove Base Hat er korrekt placeret på Raspberry Pi GPIO-pins

---

## Hardwareproblemer

### Raspberry Pi

#### Problem: Raspberry Pi vil ikke starte
**Symptomer:** Ingen billede, ingen LED-aktivitet eller regnbueskærm

**Løsning:**
1. **Tjek strømforsyning:** Brug officiel 5V 3A USB-C strømforsyning til Pi 4
2. **SD-kort problemer:** 
   - Reformatér SD-kort og geninstaller Raspberry Pi OS
   - Prøv et andet SD-kort (brug anbefalede mærker)
   - Sørg for SD-kort er korrekt indsat
3. **Tjek HDMI-forbindelse:** Prøv begge HDMI-porte på Pi 4, brug HDMI-port nærmest strøm

#### Problem: Kan ikke SSH til Raspberry Pi
**Symptomer:** Forbindelse afvist eller timeout

**Løsning:**
1. Aktivér SSH:
   - Når du skriver SD-kort med Raspberry Pi Imager, konfigurer SSH i avancerede indstillinger
   - Eller opret en tom fil ved navn `ssh` (uden extension) i boot-partitionen
2. Find Pi’s IP-adresse:
   - Tjek din routers tilsluttede enheder
   - Brug `ping raspberrypi.local` (hvis mDNS virker)
   - Brug netværksscanningsværktøjer som `nmap` eller Angry IP Scanner
3. Tjek netværk:
   - Sørg for, at Pi er på samme netværk som din computer
   - Prøv kablet forbindelse i stedet for WiFi
4. Bekræft brugernavn/adgangskode (standard: brugernavn `pi`, adgangskode `raspberry`)

#### Problem: Grove Base Hat genkendes ikke
**Symptomer:** Sensorer virker ikke, I2C-fejl

**Løsning:**
1. Sørg for Base Hat sidder korrekt på alle GPIO-pins
2. Tjek for bøjede pins på Pi eller Base Hat
3. Aktivér I2C-interface:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Bekræft at I2C virker: `i2cdetect -y 1`

#### Problem: Raspberry Pi kører langsomt
**Symptomer:** Langsom brugerflade, langsom respons

**Løsning:**
1. Tjek SD-kort hastighed (brug Class 10 eller bedre, eller SSD via USB)
2. Frigør diskplads: `df -h` til at tjekke, slet unødvendige filer
3. Reducér GPU-hukommelse i `raspi-config` hvis du ikke bruger kamera/display kraftigt
4. Luk unødvendige programmer
5. Overvej opgradering til Pi 4 med mere RAM, hvis du bruger Pi 3 eller ældre

### Wio Terminal

#### Problem: Wio Terminal skærm forbliver sort
**Symptomer:** Ingen skærmudgang efter kode-upload

**Løsning:**
1. Tjek om koden initialiserer displayet (TFT_eSPI bibliotek)
2. Opdater Wio Terminal firmware fra [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Tilføj display initialiseringskode:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Prøv at uploade eksempel-sketch fra PlatformIO for at teste hardware

#### Problem: WiFi virker ikke på Wio Terminal
**Symptomer:** Kan ikke forbinde til WiFi, netværksfejl

**Løsning:**
1. **Opdater WiFi firmware:** Følg [Wio Terminal WiFi firmware opdateringsvejledning](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Tjek WiFi legitimationsoplysninger:** Sørg for SSID og adgangskode er korrekte
3. **WiFi bånd:** Wio Terminal understøtter kun 2.4GHz WiFi (ikke 5GHz)
4. **Signalstyrke:** Flyt tættere på routeren
5. **Router-indstillinger:** Nogle enterprise/WPA-Enterprise netværk virker ikke

#### Problem: Wio Terminal genkendes ikke af computeren
**Symptomer:** USB-enhed ikke detekteret

**Løsning:**
1. **Prøv et andet USB-kabel:** Brug datakabel, ikke kun opladningskabel
2. **Gå i bootloader-tilstand:** Skub tænd/sluk-knap ned to gange hurtigt
   - Blåt LED skal blinke, enheden dukker op som "Arduino" i Enhedshåndtering
3. **Installer drivere (Windows):**
   - Download og installer [Seeed USB-driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Prøv en anden USB-port:** Undgå USB-hubs, brug direkte port
5. **Opdater systemets USB-drivere**

#### Problem: Sensorer virker ikke på Wio Terminal
**Symptomer:** Grove sensorer læser ikke data

**Løsning:**
1. Tjek Grove-kabel forbindelser
2. Bekræft at du bruger korrekt Grove-port (venstre eller højre)
3. Inkluder korrekte biblioteker til sensoren
4. Tjek sensorens strømkrav
5. Test sensoren med eksempel-kode fra biblioteket

### Virtuel Enhed (CounterFit)

#### Problem: CounterFit app starter ikke
**Fejl:** Forskellige Python-fejl ved start af CounterFit

**Løsning:**
1. Sørg for virtuelt miljø er aktiveret
2. Installer/geninstaller CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Tjek at port 5000 ikke allerede er i brug:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Afslut processen, der bruger port 5000, eller brug en anden port:
   ```bash
   counterfit --port 5001
   ```

#### Problem: Kan ikke forbinde til CounterFit fra kode
**Fejl:** Forbindelse afvist eller timeout

**Løsning:**
1. Bekræft at CounterFit kører: Åbn browser på `http://127.0.0.1:5000`
2. Tjek at forbindelses-URL i koden matcher CounterFit adresse
3. Sørg for at firewall ikke blokerer for forbindelsen
4. Prøv at genstarte både CounterFit app og din kode

#### Problem: Sensorer vises ikke i CounterFit
**Symptomer:** Oprettede sensorer vises ikke i CounterFit UI

**Løsning:**
1. Opret sensorer i CounterFit UI før kørsel af kode
2. Opdater browser-side
3. Tjek sensortype matcher, hvad koden forventer
4. Ryd browser cache

---

## Forbindelsesproblemer

### WiFi Forbindelse

#### Problem: Enhed kan ikke oprette forbindelse til WiFi
**Symptomer:** Timeout, godkendelse mislykkedes

**Løsning:**
1. **Tjek SSID og adgangskode:** Bekræft at legitimationsoplysninger er korrekte
2. **WiFi bånd:** De fleste IoT-enheder understøtter kun 2.4GHz (ikke 5GHz)
3. **Router-indstillinger:**
   - Slå AP isolation fra, hvis aktiveret
   - Brug WPA2-PSK sikkerhed (undgå WPA3, WEP eller åbne netværk)
   - Sørg for DHCP er aktiveret
4. **Skjulte netværk:** Hvis SSID er skjult, kan du være nødt til at konfigurere det eksplicit
5. **Signalstyrke:** Flyt enheden tættere på routeren
6. **Interferens:** Andre enheder, mikrobølgeovne eller vægge kan forstyrre

#### Problem: WiFi forbindelsen falder ofte ud
**Symptomer:** Periodisk forbindelse

**Løsning:**
1. Tjek routerens stabilitet og overvej genstart
2. Opdater enhedens firmware
3. Brug statisk IP i stedet for DHCP
4. Reducér afstand til router eller tilføj WiFi-forlænger
5. Tjek for interferens fra andre enheder
6. Bekræft strømforsyning er tilstrækkelig (især for Raspberry Pi)

### Cloud Services

#### Problem: Kan ikke forbinde til Azure IoT Hub
**Fejl:** Godkendelse mislykkedes, forbindelse afvist

**Løsning:**
1. **Bekræft legitimationsoplysninger:**
   - Kontroller at forbindelsesstrengen er korrekt
   - Sikr at der ikke er ekstra mellemrum eller linjeskift i forbindelsesstrengen
2. **Tjek enhedsregistrering:** Enheden skal være registreret i IoT Hub
3. **Firewall/proxy:** Sørg for at outbound MQTT (port 8883) eller HTTPS (port 443) er tilladt
4. **IoT Hub region:** Sørg for IoT Hub kører og ikke i en anden region, der forårsager latency
5. **Kvotebegrænsninger:** Tjek om gratis niveau-grænser er overskredet
6. **Test forbindelse:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problem: Azure Functions trigges ikke
**Symptomer:** Beskeder sendes, men funktion kører ikke

**Løsning:**
1. Tjek at Function App kører (ikke stoppet)
2. Bekræft forbindelsesstreng i Function App-indstillinger
3. Tjek funktionslogs i Azure Portal
4. Sørg for at Event Hub kompatibelt endpoint er korrekt konfigureret
5. Bekræft beskedformat matcher funktionens forventninger
6. Tjek Function App serviceplan (consumption vs. dedicated)

### MQTT
#### Problem: MQTT-forbindelse mislykkes
**Fejl:** Forbindelse nægtet, godkendelse mislykkedes

**Løsning:**
1. **Broker adresse:** Bekræft at broker URL/IP er korrekt
2. **Port:** Tjek portnummer (1883 for ukrypteret, 8883 for TLS)
3. **Godkendelse:** Bekræft brugernavn/adgangskode hvis påkrævet
4. **TLS/SSL:** Sørg for at certifikater er gyldige og betroede
5. **Firewall:** Tjek at port ikke er blokeret
6. **Test med MQTT-klient:** Brug MQTT Explorer eller mosquitto_pub/sub til test

#### Problem: MQTT-beskeder modtages ikke
**Symptomer:** Beskeder er publiceret men ikke modtaget af abonnenter

**Løsning:**
1. **Emnenavne:** Bekræft at abonnentens emne matcher udgiverens emne præcist
2. **QoS niveau:** Prøv QoS 1 eller 2 i stedet for 0
3. **Wildcards:** Tjek at emne-wildcards bruges korrekt (`+` for enkelt niveau, `#` for flere niveauer)
4. **Bevarede beskeder:** Udgiver kan sætte retain-flag for at beholde sidste besked
5. **Forbindelsestidspunkt:** Sørg for at abonnent forbinder før beskeder publiceres

---

## Sensor- og Aktuatorproblemer

### Grove sensorer

#### Problem: Sensor returnerer forkerte værdier
**Symptomer:** Målinger er 0, -1 eller nonsensværdier

**Løsning:**
1. **Tjek forbindelser:** Sørg for at sensor er korrekt tilsluttet
2. **Korrekt port:** Bekræft at sensor er i korrekt porttype:
   - Analoge sensorer → Analoge porte (A0, A2, A4)
   - Digitale sensorer → Digitale porte (D5, D16, D18 osv.)
   - I2C sensorer → I2C porte
3. **Kalibrering:** Nogle sensorer kræver kalibrering (jordfugtighed, lys)
4. **Strømcyklus:** Frakobl og tilslut sensoren igen
5. **Sensor datablad:** Tjek sensorspecifikationer og krav

#### Problem: Kapacitiv jordfugtighedssensor læser altid våd
**Symptomer:** Sensor viser høj fugtighed selv når tør

**Løsning:**
1. **Kalibrering nødvendig:** Jordfugtighedssensorer kræver kalibrering:
   - Aflæs værdi i luft (tør basislinje)
   - Aflæs værdi i vand (våd basislinje)
   - Kortlæg aflæsninger mellem disse værdier
2. **Tjek sensorbelægning:** Fugtighedssensorer kan forringes hvis belægning er beskadiget
3. **Placering:** Sørg for sensoren er fuldt indsat i jorden

#### Problem: Temperaturs-/fugtighedssensor aflæsninger forkerte
**Symptomer:** DHT11/DHT22 viser forkert temperatur eller fugtighed

**Løsning:**
1. **Sensorplacering:** Undgå direkte sollys, varmekilder eller luftstrøm
2. **Opvarmningstid:** Giv sensor 2 sekunder efter tænding inden aflæsning
3. **Aflæsningsfrekvens:** DHT-sensorer kræver tid mellem aflæsninger (mindst 2 sekunder)
4. **Tjek kondensation:** Kan påvirke aflæsningerne
5. **Sensor kvalitet:** DHT11 er mindre præcis end DHT22

### Kamera

#### Problem: Kamera registreres ikke på Raspberry Pi
**Fejl:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Løsning:**
1. **Aktiver kamerainterface:**
   ```bash
   sudo raspi-config
   ```
   Gå til Interface Options → Camera → Enable
2. **Tjek båndkabel:** Sørg for at kameras kabel er korrekt isat
   - Blå side vender mod USB-porte på Pi Zero
   - Blå side vender væk fra USB-porte på Pi 4
3. **Opdater firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Test kamera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problem: Kamera billeder er af dårlig kvalitet
**Symptomer:** Slørede, mørke eller udvaskede billeder

**Løsning:**
1. **Fokus:** Fjern beskyttelsesfilm fra linse, juster fokus hvis muligt
2. **Belysning:** Sørg for tilstrækkelig belysning
3. **Kamerainstillinger:** Juster eksponering, ISO, hvidbalance i kode
4. **Stabilitet:** Hold kamera stabilt, brug stativ hvis nødvendigt
5. **Opløsning:** Overskrid ikke kameraets maksimale opløsning

### Mikrofon og Højttaler

#### Problem: Ingen lydindgang/udgang
**Symptomer:** Mikrofon optager ikke, højttaler spiller ikke

**Løsning:**
1. **Tjek forbindelser:** Bekræft at lydudstyr er korrekt tilsluttet
2. **Test hardware:**
   - Højttaler: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` for at liste, `arecord test.wav` for optagelse
3. **Lydstyrkeindstillinger:** Tjek og juster lydstyrke:
   ```bash
   alsamixer
   ```
4. **Vælg lyd enhed:** Angiv korrekt lyd enhed i kode
5. **Driverproblemer:** Opdater ALSA eller geninstaller lyd drivere

#### Problem: ReSpeaker hat virker ikke
**Symptomer:** Lyd enhed registreres ikke

**Løsning:**
1. **Installer drivere:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Tjek installation:** `arecord -l` skal vise ReSpeaker
3. **Opdater firmware:** Nogle Pi OS versioner kræver driveropdateringer
4. **Tjek tilslutning:** Sørg for hat sidder korrekt på GPIO pins

---

## Problemer med Udviklingsmiljø

### VS Code

#### Problem: Terminal aktiverer ikke automatisk virtuelt miljø
**Symptomer:** Terminal åbnes, men venv aktiveres ikke

**Løsning:**
1. **Sæt Python interpreter:** Command Palette → "Python: Select Interpreter" → Vælg venv
2. **Genstart VS Code** efter valg af interpreter
3. **Tjek indstillinger:** Tilføj i `settings.json`:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Kode kører ikke på enhed
**Symptomer:** Kode kører men intet sker på enheden

**Løsning:**
1. **Bekræft at kode er gemt** (tjek prik på fane)
2. **Tjek hvilken Python der kører:** `which python` eller `where python`
3. **For Wio Terminal:** Sørg for at kode uploades via PlatformIO (klik upload)
4. **For Raspberry Pi:** SSH ind på Pi og kør koden der
5. **Tjek output vindue** for fejl

#### Problem: IntelliSense viser ikke bibliotekfunktioner
**Symptomer:** Ingen autocomplete for importerede moduler

**Løsning:**
1. Sørg for bibliotek er installeret i aktivt miljø
2. Genindlæs VS Code vindue
3. Bekræft at Python interpreter er korrekt
4. Installer type stubs hvis tilgængeligt: `pip install types-<bibliotek-navn>`

### Python Virtuelle Miljøer

#### Problem: Kan ikke oprette virtuelt miljø
**Fejl:** `The virtual environment was not created successfully`

**Løsning:**
1. **Installer venv-modul:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Skal være inkluderet med Python
   - Windows: Geninstaller Python med alle komponenter
2. **Tjek Python installation:** Bekræft Python er korrekt installeret
3. **Brug fuld sti:** Prøv `python3 -m venv .venv` med eksplicit python3 kald

#### Problem: Pakker installeret forkert sted
**Symptomer:** Importfejl efter pakkeinstallation

**Løsning:**
1. **Bekræft venv er aktiveret:** Kommandoprompt skal vise `(.venv)`
2. **Tjek pip placering:** `which pip` skal pege på `.venv/bin/pip`
3. **Geninstaller i venv:** Aktiver venv, kør så `pip install <pakke>`
4. **Brug ikke sudo med pip** i virtuel miljø

#### Problem: Virtuelt miljø er ikke portabelt
**Symptomer:** Venv virker ikke efter flytning eller på anden maskine

**Løsning:**
1. **Flyt ikke venv:** Slet og opret nyt i ny placering
2. **Brug requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Genopret venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # eller activate.bat på Windows
   pip install -r requirements.txt
   ```

### Afhængigheder

#### Problem: Pakkeinstallation mislykkes
**Fejl:** Forskellige pip fejl under installation

**Løsning:**
1. **Opdater pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Installer build værktøjer:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Installer Visual Studio Build Tools
3. **Tjek internetforbindelse**
4. **Prøv andet pakkeindeks:** `pip install --index-url https://pypi.org/simple/ <pakke>`
5. **Installer specifik version:** `pip install <pakke>==<version>`

#### Problem: Afhængighedskonflikter
**Fejl:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Løsning:**
1. **Brug frisk virtuelt miljø** for hvert projekt
2. **Opdater pakker:** `pip install --upgrade <pakke>`
3. **Tjek krav:** Brug `pip check` for at finde konflikter
4. **Installer kompatible versioner:** Angiv versionsintervaller i requirements.txt

---

## Ydelsesproblemer

### Problem: Kode kører langsomt
**Symptomer:** Forsinkelser, timeouts, manglende respons

**Løsning:**
1. **Reducer sensor aflæsningsfrekvens:** Læs ikke sensorer for ofte
2. **Optimer løkker:** Undgå busy-wait, brug sleep() eller forsinkelser
3. **Hukommelsesproblemer:**
   - Luk unødvendige programmer
   - Frigør lagringsplads
   - Overvåg med `top` eller `htop` på Pi
4. **SD-kort hastighed:** Brug hurtigere SD-kort eller SSD til Raspberry Pi
5. **Netværksforsinkelser:** Brug asynkrone operationer til netværkskald

### Problem: Hukommelsesfejl
**Fejl:** `MemoryError` eller systemet fryser

**Løsning:**
1. **For Raspberry Pi:**
   - Luk unødvendige programmer
   - Forøg swap plads
   - Brug lettere OS (Lite version)
   - Opgrader RAM (Pi 4 har 2/4/8GB muligheder)
2. **For Wio Terminal:**
   - Reducer buffer størrelser
   - Brug mindre billeder
   - Optimer streng brug
   - Tjek for hukommelseslækager (frigivet hukommelse)

### Problem: Datatab eller korruption
**Symptomer:** Manglende beskeder, korrupte filer

**Løsning:**
1. **SD-kort problemer:**
   - Brug kvalitets SD-kort (undgå billige/imitater)
   - Regelmæssige backups
   - Luk korrekt ned (træk ikke strøm)
2. **Buffer overflow:** Forøg buffer størrelser i kode
3. **Netværk pålidelighed:** Implementer retry-logik og fejlhåndtering
4. **Servicekvalitet:** Brug MQTT QoS 1 eller 2 for vigtige beskeder

---

## Almindelige Fejlmeddelelser

### `ModuleNotFoundError: No module named 'X'`
**Årsag:** Pakke ikke installeret eller virtuelt miljø ikke aktiveret

**Løsning:**
```bash
pip install X
```
Sørg for at aktivere virtuelt miljø først.

### `Permission denied` på Linux/macOS
**Årsag:** Kræver forhøjede rettigheder eller filrettighedsproblem

**Løsning:**
- Til systemoperationer: Brug `sudo`
- Til pip: BRUG IKKE sudo med venv, aktiver venv først
- Til seriel port: Tilføj bruger til dialout gruppe: `sudo usermod -a -G dialout $USER`, log ud/ind igen

### `OSError: [Errno 98] Address already in use`
**Årsag:** Port er allerede brugt af en anden proces

**Løsning:**
1. Find proces der bruger port: `lsof -i :<port>` eller `netstat -ano | findstr :<port>`
2. Dræb processen eller brug en anden port i din kode

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Årsag:** SSL certifikat validering fejler

**Løsning:**
1. Opdater certifikater: `pip install --upgrade certifi`
2. Tjek systemtid er korrekt: `date`
3. Kun til udvikling (ikke produktion): Deaktiver verifikation i kode

### `IndentationError: unexpected indent`
**Årsag:** Python indrykningsproblemer (blanding af tabs/space)

**Løsning:**
1. Brug konsekvent indrykning (4 spaces er Python standard)
2. Sæt editor til at bruge spaces i stedet for tabs
3. VS Code: Sæt `"editor.insertSpaces": true` og `"editor.tabSize": 4`

### `UnicodeDecodeError` eller `UnicodeEncodeError`
**Årsag:** Tegnkodningsproblemer

**Løsning:**
```python
# Når du læser filer
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Når du skriver filer
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Få Hjælp

Hvis du har prøvet disse fejlfindingstrin og stadig har problemer:

### 1. Tjek eksisterende ressourcer
- **Dokumentation:** Gennemgå [README](README.md) og lektionsinstruktioner
- **Hardware guides:** Tjek [hardware.md](hardware.md) for hardware-specifik information
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) for Grove-komponenter

### 2. Søg efter lignende problemer
- **GitHub Issues:** Søg i [eksisterende issues](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Søg efter fejlmeddelelser
- **Enhedsfora:** Tjek Raspberry Pi fora eller Arduino fora

### 3. Opret en GitHub issue
Hvis du ikke kan finde en løsning:
1. Gå til [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Klik på "New Issue"
3. Angiv:
   - Klar beskrivelse af problemet
   - Fremgangsmåde til at genskabe fejlen
   - Fejlmeddelelser (fuld tekst)
   - Hardware/software versioner
   - Hvad du allerede har prøvet
   - Skærmbilleder hvis relevant

### 4. Deltag i fællesskabet
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Giv gode fejlrapporter
En god fejlrapport inkluderer:
- **Miljø:** OS, Python-version, hardware brugt  
- **Trin til reproduktion:** Nøjagtige trin der forårsager problemet  
- **Forventet adfærd:** Hvad der burde ske  
- **Faktisk adfærd:** Hvad der rent faktisk sker  
- **Fejlmeddelelser:** Fuldstændig fejllog, ikke screenshots  
- **Kode:** Minimalt kodeeksempel der reproducerer problemet  

---

## Tips til forebyggelse

### Generelle bedste praksis  
1. **Tag backup:** Regelmæssige backups af fungerende SD-kort/kode  
2. **Dokumenter ændringer:** Noter hvad der virker i kommentarer  
3. **Versionskontrol:** Brug git til at spore kodeændringer  
4. **Test trinvist:** Test små ændringer før sammensætning  
5. **Læs fejlmeddelelser:** De fortæller ofte præcis, hvad der er galt  
6. **Opdater regelmæssigt:** Hold software/firmware opdateret  
7. **Brug kvalitetkomponenter:** Undgå billige kabler/strømforsyninger  
8. **Stabil strøm:** Brug passende strømforsyning (især til Pi)  

### Udviklingsworkflow  
1. **Start simpelt:** Begynd med eksempelkode der virker  
2. **Én ændring ad gangen:** Nemmere at finde hvad der går galt  
3. **Test ofte:** Opdag problemer tidligt  
4. **Hold det ryddeligt:** Organiser filer og kode logisk  
5. **Kommenter kode:** Fremtidige dig vil sætte pris på det  

---

*Denne fejlsøgningsguide vedligeholdes af fællesskabet. Hvis du finder en løsning på et problem, der ikke er listet her, så overvej venligst at [bidrage](CONTRIBUTING.md) til at hjælpe andre!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Ansvarsfraskrivelse**:
Dette dokument er oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->