<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T06:32:54+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "sv"
}
-->
# Felsökningsguide

Denna guide hjälper dig att lösa vanliga problem när du arbetar med IoT for Beginners-kursplanen. Problem är organiserade efter kategori för enkel navigering.

## Innehållsförteckning

- [Installationsproblem](../..)
  - [Pythoninstallation](../..)
  - [VS Code och tillägg](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove-bibliotek](../..)
- [Hårdvaruproblem](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuell enhet (CounterFit)](../..)
- [Anslutningsproblem](../..)
  - [WiFi-anslutning](../..)
  - [Molntjänster](../..)
  - [MQTT](../..)
- [Sensor- och ställdonproblem](../..)
  - [Grove-sensorer](../..)
  - [Kamera](../..)
  - [Mikrofon och högtalare](../..)
- [Problem med utvecklingsmiljön](../..)
  - [VS Code](../..)
  - [Python-virtuella miljöer](../..)
  - [Beroenden](../..)
- [Prestandaproblem](../..)
- [Vanliga felmeddelanden](../..)
- [Få hjälp](../..)

---

## Installationsproblem

### Pythoninstallation

#### Problem: Pythonversionen är för gammal  
**Fel:** `Python 3.6 eller högre krävs`

**Lösning:**  
1. Ladda ner senaste Python 3 från [python.org](https://www.python.org/downloads/)  
2. Under installationen på Windows, markera "Add Python to PATH"  
3. Verifiera installation:  
   ```bash
   python3 --version
   ```
  
#### Problem: Flera Pythonversioner skapar konflikter  
**Symtom:** Fel Pythonversion körs, paket installeras på fel plats  

**Lösning:**  
- **Windows:** Använd `py -3` istället för `python` för att explicit anropa Python 3  
- **macOS/Linux:** Använd `python3` istället för `python`  
- Skapa och använd alltid virtuella miljöer för projekt  

#### Problem: pip-kommando hittas inte  
**Fel:** `'pip' är inte igenkänt som ett internt eller externt kommando`

**Lösning:**  
1. Prova `pip3` istället för `pip`  
2. Eller använd `python -m pip` eller `python3 -m pip`  
3. Kontrollera att Python är tillagt i PATH (installera om Python och markera alternativet)  

### VS Code och tillägg

#### Problem: Pylance-tillägg fungerar inte  
**Symtom:** Ingen Python IntelliSense, kodkomplettering eller typkontroll  

**Lösning:**  
1. Öppna VS Code Command Palette (`Ctrl+Shift+P` eller `Cmd+Shift+P`)  
2. Kör "Python: Select Interpreter"  
3. Välj rätt Pythoninterpreter (virtuell miljö om du använder en)  
4. Ladda om VS Code-fönstret  

#### Problem: VS Code hittar inte virtuell miljö  
**Symtom:** Fel Pythoninterpreter är vald  

**Lösning:**  
1. Se till att du aktiverat den virtuella miljön i terminalen  
2. Öppna Command Palette och kör "Python: Select Interpreter"  
3. Välj interpreter från `.venv`-mappen  
4. Kontrollera att statusfältet (nere till vänster) visar rätt Pythonversion  

### PlatformIO (Wio Terminal)

#### Problem: PlatformIO-installation misslyckas  
**Fel:** Olika fel under installation av PlatformIO  

**Lösning:**  
1. Säkerställ att VS Code är uppdaterat  
2. Installera C/C++-tillägget först  
3. Starta om VS Code efter installation av PlatformIO  
4. Kontrollera din internetanslutning (PlatformIO laddar stora filer)  

#### Problem: Kortet upptäcks inte av PlatformIO  
**Symtom:** Kan inte ladda upp kod till Wio Terminal  

**Lösning:**  
1. Prova annan USB-kabel (vissa kablar är endast för laddning)  
2. Kontrollera Enhetshanteraren (Windows) eller `ls /dev/tty*` (macOS/Linux)  
3. Installera eller uppdatera USB-drivrutiner  
4. Använd annan USB-port  
5. Skjut på strömbrytaren på Wio Terminal två gånger snabbt för att gå in i bootloader-läge  

#### Problem: Kompilationsfel i PlatformIO  
**Fel:** `fatal error: Arduino.h: No such file or directory`  

**Lösning:**  
1. Radera `.pio`-mappen i ditt projekt  
2. Kör "PlatformIO: Rebuild" från Command Palette  
3. Säkerställ att `platformio.ini` har rätt kortkonfiguration:  
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```
  
### Grove-bibliotek

#### Problem: Grove-bibliotek import misslyckas på Raspberry Pi  
**Fel:** `ModuleNotFoundError: No module named 'grove'`  

**Lösning:**  
1. Installera om Grove-biblioteken:  
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Om du använder virtuell miljö kan du behöva installera globalt eller kopiera bibliotek  
3. Kontrollera att I2C är aktiverat: `sudo raspi-config nonint do_i2c 0`  

#### Problem: Grove-sensor upptäcks inte  
**Fel:** `IOError: [Errno 121] Remote I/O error`  

**Lösning:**  
1. Kontrollera fysiska anslutningar (se till att Grove-kabeln är fullständigt insatt)  
2. Säkerställ att sensorn är kopplad till rätt port (analog, digital, I2C, UART)  
3. Kör `i2cdetect -y 1` för att se om enheten syns på I2C-bussen  
4. Prova annan Grove-kabel  
5. Kontrollera att Grove Base Hat sitter ordentligt på Raspberry Pi:s GPIO-stift  

---

## Hårdvaruproblem

### Raspberry Pi

#### Problem: Raspberry Pi startar inte  
**Symtom:** Ingen bild, ingen LED-aktivitet eller regnbågsskärm  

**Lösning:**  
1. **Kontrollera strömförsörjning:** Använd officiell 5V 3A USB-C strömadapter för Pi 4  
2. **SD-kortsproblem:**  
   - Formatera om SD-kort och installera Raspberry Pi OS på nytt  
   - Prova ett annat SD-kort (använd rekommenderade märken)  
   - Säkerställ att SD-kortet är korrekt insatt  
3. **Kontrollera HDMI-anslutning:** Testa båda HDMI-portarna på Pi 4, använd HDMI-port närmast ström  

#### Problem: Kan inte SSH till Raspberry Pi  
**Symtom:** Anslutning nekas eller timeout  

**Lösning:**  
1. Aktivera SSH:  
   - Vid flashning av SD-kort med Raspberry Pi Imager, konfigurera SSH i avancerade inställningar  
   - Eller skapa en tom fil med namnet `ssh` (utan filändelse) i boot-partitionen  
2. Hitta Pis IP-adress:  
   - Kolla anslutna enheter i din router  
   - Använd `ping raspberrypi.local` (om mDNS fungerar)  
   - Använd nätverksskanning som `nmap` eller Angry IP Scanner  
3. Kontrollera nätverk:  
   - Säkerställ att Pi är på samma nätverk som din dator  
   - Prova Ethernet-anslutning istället för WiFi  
4. Verifiera användarnamn/lösenord (standard: användare `pi`, lösen `raspberry`)  

#### Problem: Grove Base Hat känns inte igen  
**Symtom:** Sensorer fungerar inte, I2C-fel  

**Lösning:**  
1. Se till att Base Hat är ordentligt isatt på alla GPIO-stift  
2. Kontrollera att inga stift är böjda på Pi eller Base Hat  
3. Aktivera I2C-gränssnitt:  
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Kontrollera att I2C fungerar: `i2cdetect -y 1`  

#### Problem: Raspberry Pi går långsamt  
**Symtom:** Slö användargränssnitt, seg respons  

**Lösning:**  
1. Kontrollera SD-kortets hastighet (använd Klass 10 eller bättre, eller SSD via USB)  
2. Rensa diskutrymme: `df -h` för att kontrollera, ta bort onödiga filer  
3. Minska GPU-minne i `raspi-config` om du inte använder kamera/skärm mycket  
4. Stäng onödiga program  
5. Överväg att uppgradera till Pi 4 med mer RAM om du använder Pi 3 eller äldre  

### Wio Terminal

#### Problem: Wio Terminals skärm är svart  
**Symtom:** Ingen display visas efter uppladdning av kod  

**Lösning:**  
1. Kontrollera att koden initialiserar displayen (TFT_eSPI-biblioteket)  
2. Uppdatera Wio Terminal firmware från [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)  
3. Lägg till kod för displayinitialisering:  
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Prova att ladda upp exempelprogram från PlatformIO för att testa hårdvaran  

#### Problem: WiFi fungerar inte på Wio Terminal  
**Symtom:** Kan inte ansluta till WiFi, nätverksfel  

**Lösning:**  
1. **Uppdatera WiFi-firmware:** Följ [Wio Terminal WiFi firmware update guide](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)  
2. **Kontrollera WiFi-uppgifter:** Säkerställ att SSID och lösenord är korrekta  
3. **WiFi-band:** Wio Terminal stödjer bara 2.4GHz WiFi (inte 5GHz)  
4. **Signalstyrka:** Flytta närmare routern  
5. **Routerinställningar:** Vissa företags-/WPA-Enterprise-nätverk kan inte fungera  

#### Problem: Wio Terminal känns inte igen av datorn  
**Symtom:** USB-enheten upptäcks inte  

**Lösning:**  
1. **Prova annan USB-kabel:** Använd datakabel, inte laddningskabel  
2. **Gå in i bootloader-läge:** Skjut strömbrytaren ned två gånger snabbt  
   - Blå LED ska pulsera, enheten visas som "Arduino" i Enhetshanteraren  
3. **Installera drivrutiner (Windows):**  
   - Ladda ner och installera [Seeed USB driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)  
4. **Byt USB-port:** Undvik USB-hubbar, använd direktanslutning  
5. **Uppdatera systemets USB-drivrutiner**  

#### Problem: Sensorer fungerar inte på Wio Terminal  
**Symtom:** Grove-sensorer läser inte av data  

**Lösning:**  
1. Kontrollera Grove-kabelanslutningar  
2. Säkerställ att du använder rätt Grove-port (vänster eller höger)  
3. Inkludera korrekta bibliotek för sensorn  
4. Kontrollera sensorernas strömkrav  
5. Testa sensorn med exempelprogram från biblioteket  

### Virtuell enhet (CounterFit)

#### Problem: CounterFit-app startar inte  
**Fel:** Olika Python-fel vid start av CounterFit  

**Lösning:**  
1. Säkerställ att virtuell miljö är aktiverad  
2. Installera/Installera om CounterFit:  
   ```bash
   pip install CounterFit
   ```
3. Kontrollera att port 5000 inte redan används:  
   - Windows: `netstat -ano | findstr :5000`  
   - macOS/Linux: `lsof -i :5000`  
4. Stäng av processen som använder port 5000 eller använd annan port:  
   ```bash
   counterfit --port 5001
   ```
  
#### Problem: Kan inte ansluta till CounterFit från kod  
**Fel:** Anslutning nekas eller timeout  

**Lösning:**  
1. Verifiera att CounterFit körs: Öppna webbläsare till `http://127.0.0.1:5000`  
2. Kontrollera att anslutnings-URL i koden stämmer med CounterFit-adressen  
3. Se till att brandväggen inte blockerar anslutningen  
4. Försök starta om både CounterFit-appen och din kod  

#### Problem: Sensorer visas inte i CounterFit  
**Symtom:** Skapade sensorer syns inte i CounterFit-gränssnittet  

**Lösning:**  
1. Skapa sensorer i CounterFit UI innan du kör koden  
2. Uppdatera webbläsarens sida  
3. Kontrollera att sensortypen matchar vad koden förväntar sig  
4. Rensa webbläsarens cache  

---

## Anslutningsproblem

### WiFi-anslutning

#### Problem: Enheten kan inte ansluta till WiFi  
**Symtom:** Anslutningstid utgår, autentisering misslyckades  

**Lösning:**  
1. **Kontrollera SSID och lösenord:** Verifiera att uppgifterna är korrekta  
2. **WiFi-band:** De flesta IoT-enheter stödjer endast 2.4GHz (inte 5GHz)  
3. **Routerinställningar:**  
   - Inaktivera AP-isolering om det är aktiverat  
   - Använd WPA2-PSK-säkerhet (undvik WPA3, WEP eller öppna nätverk)  
   - Kontrollera att DHCP är aktiverat  
4. **Dolda nätverk:** Om SSID är dolt kan du behöva konfigurera det explicit  
5. **Signalstyrka:** Flytta enheten närmare routern  
6. **Störningar:** Andra enheter, mikrovågsugnar eller väggar kan störa  

#### Problem: WiFi-anslutningen bryts ofta  
**Symtom:** Intermittent anslutning  

**Lösning:**  
1. Kontrollera routerns stabilitet och överväg omstart  
2. Uppdatera enhetens firmware  
3. Använd statisk IP istället för DHCP  
4. Minska avståndet till routern eller lägg till WiFi-förstärkare  
5. Kontrollera störningar från andra enheter  
6. Verifiera att strömförsörjningen är tillräcklig (särskilt för Raspberry Pi)  

### Molntjänster

#### Problem: Kan inte ansluta till Azure IoT Hub  
**Fel:** Autentisering misslyckades, anslutning nekad  

**Lösning:**  
1. **Verifiera behörigheter:**  
   - Kontrollera att anslutningssträngen är korrekt  
   - Se till att det inte finns extra mellanslag eller radbrytningar i anslutningssträngen  
2. **Kontrollera enhetsregistrering:** Enheten måste vara registrerad i IoT Hub  
3. **Brandvägg/proxy:** Säkerställ att utgående MQTT (port 8883) eller HTTPS (port 443) är tillåtet  
4. **IoT Hub-region:** Kontrollera att IoT Hub körs och inte befinner sig i en annan region som orsakar fördröjning  
5. **Kvantitetsgränser:** Kontrollera om gratisnivån har överskridits  
6. **Testa anslutning:**  
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```
  
#### Problem: Azure Functions triggas inte  
**Symtom:** Meddelanden skickas men funktionen körs inte  

**Lösning:**  
1. Kontrollera att Function App är igång (inte stoppad)  
2. Verifiera anslutningssträngen i Function App-inställningarna  
3. Kontrollera funktionsloggar i Azure-portalen  
4. Säkerställ att Event Hub-kompatibel endpoint är korrekt konfigurerad  
5. Kontrollera att meddelandeformatet matchar funktionens förväntningar  
6. Kontrollera Function App-tjänsteplan (konsumtion vs. dedikerad)  

### MQTT
#### Problem: MQTT-anslutning misslyckas
**Fel:** Anslutning nekad, autentisering misslyckades

**Lösning:**
1. **Broker-adress:** Kontrollera att broker-URL/IP är korrekt
2. **Port:** Kontrollera portnummer (1883 för okrypterat, 8883 för TLS)
3. **Autentisering:** Kontrollera användarnamn/lösenord om det krävs
4. **TLS/SSL:** Säkerställ att certifikaten är giltiga och betrodda
5. **Brandvägg:** Kontrollera att porten inte är blockerad
6. **Testa med MQTT-klient:** Använd MQTT Explorer eller mosquitto_pub/sub för att testa

#### Problem: MQTT-meddelanden tas inte emot
**Symptom:** Meddelanden publiceras men tas inte emot av prenumeranter

**Lösning:**
1. **Ämnesnamn:** Kontrollera att prenumerantens ämne exakt matchar publicerande ämne
2. **QoS-nivå:** Prova QoS 1 eller 2 istället för 0
3. **Wildcard:** Kontrollera att ämneswildcards används korrekt (`+` för en nivå, `#` för flera nivåer)
4. **Behållna meddelanden:** Publiceraren kan sätta behåll-flagga för att behålla senaste meddelandet
5. **Anslutningstiming:** Säkerställ att prenumeranten ansluter innan meddelanden publiceras

---

## Sensor- och Aktuatorproblem

### Grove-sensorer

#### Problem: Sensor returnerar felaktiga värden
**Symptom:** Avläsningar är 0, -1 eller nonsensvärden

**Lösning:**
1. **Kontrollera anslutningar:** Säkerställ att sensorn är korrekt ansluten
2. **Rätt port:** Kontrollera att sensorn är i rätt porttyp:
   - Analoga sensorer → Analoga portar (A0, A2, A4)
   - Digitala sensorer → Digitala portar (D5, D16, D18, etc.)
   - I2C-sensorer → I2C-portar
3. **Kalibrering:** Vissa sensorer kräver kalibrering (jordfukt, ljus)
4. **Strömcykling:** Koppla från och koppla till sensorn
5. **Sensordatablad:** Kontrollera sensorspecifikationer och krav

#### Problem: Kapacitiv jordfuktighetssensor läser alltid "våt"
**Symptom:** Sensorn visar hög fuktighet även när torrt

**Lösning:**
1. **Kalibrering krävs:** Jordfuktsensorer kräver kalibrering:
   - Läs av värde i luft (torrt basvärde)
   - Läs av värde i vatten (vått basvärde)
   - Mappa mätningar mellan dessa värden
2. **Kontrollera sensorbeläggning:** Fuktsensorer kan försämras om beläggningen skadas
3. **Placering:** Säkerställ att sensorn är helt insatt i jorden

#### Problem: Temperatursensor/fuktighetssensor ger fel avläsningar
**Symptom:** DHT11/DHT22 visar fel temperatur eller fuktighet

**Lösning:**
1. **Sensorplacering:** Undvik direkt solljus, värmekällor eller drag
2. **Uppvärmningstid:** Låt sensor få 2 sekunder efter ström på innan avläsning
3. **Avläsningsfrekvens:** DHT-sensorer behöver tid mellan avläsningar (minst 2 sekunder)
4. **Kontrollera kondensation:** Kan påverka avläsningar
5. **Sensor Kvalitet:** DHT11 är mindre noggrann än DHT22

### Kamera

#### Problem: Kamera detekteras inte på Raspberry Pi
**Fel:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Lösning:**
1. **Aktivera kamerasnitt:**
   ```bash
   sudo raspi-config
   ```
   Gå till Interface Options → Camera → Enable
2. **Kontrollera flatkabel:** Säkerställ att kamerasladden är korrekt insatt
   - Blå sida vänd mot USB-portarna på Pi Zero
   - Blå sida bort från USB-portarna på Pi 4
3. **Uppdatera firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Testa kamera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problem: Kamera bilder är dålig kvalitet
**Symptom:** Oskärpa, mörka eller urblekta bilder

**Lösning:**
1. **Fokus:** Ta bort skyddsfilm från linsen, justera fokus om möjligt
2. **Belysning:** Säkerställ tillräcklig belysning
3. **Kamerainställningar:** Justera exponering, ISO, vitbalans i koden
4. **Stabilitet:** Håll kameran stilla, använd stativ vid behov
5. **Upplösning:** Överskrid inte kamerans maximala upplösning

### Mikrofon och Högtalare

#### Problem: Ingen ljudingång/utgång
**Symptom:** Mikrofon spelar inte in, högtalare spelar inte

**Lösning:**
1. **Kontrollera anslutningar:** Kontrollera att ljudenheterna är korrekt anslutna
2. **Testa hårdvara:**
   - Högtalare: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` lista, `arecord test.wav` spela in
3. **Volyminställningar:** Kontrollera och justera volym:
   ```bash
   alsamixer
   ```
4. **Välj ljudenhet:** Ange korrekt ljudenhet i koden
5. **Drivrutinsproblem:** Uppdatera ALSA eller installera om ljuddrivrutiner

#### Problem: ReSpeaker-hatt fungerar inte
**Symptom:** Ljudenhet detekteras ej

**Lösning:**
1. **Installera drivrutiner:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Kontrollera installation:** `arecord -l` ska lista ReSpeaker
3. **Uppdatera firmware:** Vissa Pi OS-versioner behöver drivrutinsuppdateringar
4. **Kontrollera anslutning:** Säkerställ att hatten sitter korrekt på GPIO-stiften

---

## Utvecklingsmiljöproblem

### VS Code

#### Problem: Terminal aktiverar inte virtuellt miljö automatiskt
**Symptom:** Terminal öppnas men venv aktiveras inte

**Lösning:**
1. **Ställ in Python interpreter:** Command Palette → "Python: Select Interpreter" → Välj venv
2. **Starta om VS Code** efter att interpreter valts
3. **Kontrollera inställningar:** I `settings.json`, lägg till:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Kod körs inte på enheten
**Symptom:** Kod körs men inget händer på enheten

**Lösning:**
1. **Verifiera att koden sparats** (kolla prick på flik)
2. **Kontrollera python-version:** `which python` eller `where python`
3. **För Wio Terminal:** Säkerställ kod uppladdning via PlatformIO (klicka på uppladdningsknapp)
4. **För Raspberry Pi:** SSH in i Pi och kör koden där
5. **Kontrollera utmatningsfönster** för felmeddelanden

#### Problem: IntelliSense visar inte biblioteksfunktioner
**Symptom:** Ingen autokomplettering för importerade moduler

**Lösning:**
1. Säkerställ att biblioteket är installerat i aktuellt miljö
2. Ladda om VS Code-fönster
3. Kontrollera att Python interpreter är korrekt
4. Installera typstilar om tillgängligt: `pip install types-<biblioteksnamn>`

### Python virtuella miljöer

#### Problem: Kan inte skapa virtuell miljö
**Fel:** `The virtual environment was not created successfully`

**Lösning:**
1. **Installera venv-modul:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Bör ingå med Python
   - Windows: Installera om Python med alla komponenter
2. **Kontrollera Python-installation:** Säkerställ att Python är rätt installerat
3. **Använd fullständig sökväg:** Prova `python3 -m venv .venv` med explicit python3

#### Problem: Paket installerade på fel plats
**Symptom:** Importfel efter paketinstallation

**Lösning:**
1. **Verifiera att venv är aktiverad:** Kommandoprompt ska visa `(.venv)`
2. **Kontrollera pip-plats:** `which pip` ska peka på `.venv/bin/pip`
3. **Installera om i venv:** Aktivera venv, sedan `pip install <paket>`
4. **Använd inte sudo med pip** i virtuell miljö

#### Problem: Virtuell miljö är inte portabel
**Symptom:** Venv fungerar inte efter flytt eller på annan dator

**Lösning:**
1. **Flytta inte venv:** Ta bort och skapa om i ny plats
2. **Använd requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Skapa om venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # eller activate.bat på Windows
   pip install -r requirements.txt
   ```

### Beroenden

#### Problem: Paketinstallation misslyckas
**Fel:** Olika pip-fel vid installation

**Lösning:**
1. **Uppdatera pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Installera byggverktyg:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Installera Visual Studio Build Tools
3. **Kontrollera internetanslutning**
4. **Testa annan paketindex:** `pip install --index-url https://pypi.org/simple/ <paket>`
5. **Installera specifik version:** `pip install <paket>==<version>`

#### Problem: Beroendekonflikter
**Fel:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Lösning:**
1. **Använd färsk virtuell miljö** för varje projekt
2. **Uppdatera paket:** `pip install --upgrade <paket>`
3. **Kontrollera krav:** Använd `pip check` för att hitta konflikter
4. **Installera kompatibla versioner:** Specificera versionsintervall i requirements.txt

---

## Prestandaproblem

### Problem: Kod körs långsamt
**Symptom:** Fördröjningar, timeout, svarar ej

**Lösning:**
1. **Minska sensoravläsningsfrekvens:** Läs inte sensorer för ofta
2. **Optimera loopar:** Undvik busy-wait, använd sleep() eller fördröjningar
3. **Minnesproblem:**
   - Stäng onödiga program
   - Frigör lagringsutrymme
   - Övervaka med `top` eller `htop` på Pi
4. **SD-korts hastighet:** Använd snabbare SD-kort eller SSD för Raspberry Pi
5. **Nätverksfördröjningar:** Använd asynkrona operationer för nätverksanrop

### Problem: Minnesfel
**Fel:** `MemoryError` eller systemfrysning

**Lösning:**
1. **För Raspberry Pi:**
   - Stäng onödiga program
   - Öka swap-minne
   - Använd lättare OS (Lite-version)
   - Uppgradera RAM (Pi 4 finns med 2/4/8GB)
2. **För Wio Terminal:**
   - Minska buffertstorlekar
   - Använd mindre bilder
   - Optimera stränghantering
   - Kontrollera minnesläckor (frigör ej minne)

### Problem: Dataförlust eller korruption
**Symptom:** Saknade meddelanden, korrupta filer

**Lösning:**
1. **SD-kortsproblem:**
   - Använd kvalitets-SD-kort (undvik billiga/fejkade)
   - Regelbundna backup
   - Säker avstängning (dra ej ström)
2. **Buffertöversvämning:** Öka buffertstorlekar i koden
3. **Nätverkets pålitlighet:** Implementera retry-logik och felhantering
4. **Tjänstekvalitet:** Använd MQTT QoS 1 eller 2 för viktiga meddelanden

---

## Vanliga felmeddelanden

### `ModuleNotFoundError: No module named 'X'`
**Orsak:** Paket ej installerat eller virtuell miljö ej aktiverad

**Lösning:**
```bash
pip install X
```
Säkerställ att virtuell miljö är aktiverad först.

### `Permission denied` på Linux/macOS
**Orsak:** Kräver förhöjda rättigheter eller filrättighetsproblem

**Lösning:**
- För systemoperationer: Använd `sudo`
- För pip: ANVÄND EJ sudo med venv, aktivera venv först
- För seriell port: Lägg till användare i dialout-gruppen: `sudo usermod -a -G dialout $USER`, logga ut/in

### `OSError: [Errno 98] Address already in use`
**Orsak:** Port används redan av annan process

**Lösning:**
1. Hitta process som använder port: `lsof -i :<port>` eller `netstat -ano | findstr :<port>`
2. Döda processen eller använd annan port i din kod

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Orsak:** SSL-certifikatvalidering misslyckas

**Lösning:**
1. Uppdatera certifikat: `pip install --upgrade certifi`
2. Kontrollera systemtid är korrekt: `date`
3. Endast för utveckling (ej produktion): Inaktivera verifiering i koden

### `IndentationError: unexpected indent`
**Orsak:** Python-indenteringsproblem (blandning av tabb/space)

**Lösning:**
1. Använd konsekvent indentering (4 mellanslag är Python-standard)
2. Konfigurera editor att använda mellanslag istället för tabb
3. VS Code: Ställ in `"editor.insertSpaces": true` och `"editor.tabSize": 4`

### `UnicodeDecodeError` eller `UnicodeEncodeError`
**Orsak:** Problem med teckenkodning

**Lösning:**
```python
# När du läser filer
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# När du skriver filer
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Få Hjälp

Om du har provat dessa felsökningssteg och fortfarande har problem:

### 1. Kontrollera befintliga resurser
- **Dokumentation:** Läs igenom [README](README.md) och lektionsinstruktioner
- **Hårdvaruguider:** Kolla [hardware.md](hardware.md) för hårdvaruspecifik info
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) för Grove-komponenter

### 2. Sök efter liknande problem
- **GitHub Issues:** Sök [befintliga issues](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Sök efter felmeddelanden
- **Enhetsforum:** Kolla Raspberry Pi-forum eller Arduino-forum

### 3. Skapa en GitHub Issue
Om du inte hittar en lösning:
1. Gå till [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Klicka på "New Issue"
3. Ange:
   - Tydlig beskrivning av problemet
   - Steg för att reproducera
   - Felmeddelanden (fullständig text)
   - Hårdvaru-/mjukvaruversioner
   - Vad du redan har försökt
   - Skärmbilder om relevant

### 4. Gå med i communityn
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Ge bra felrapporter
En bra felrapport inkluderar:
- **Miljö:** OS, Python-version, hårdvara som används  
- **Steg för att reproducera:** Exakta steg som orsakar problemet  
- **Förväntat beteende:** Vad som borde hända  
- **Faktiskt beteende:** Vad som faktiskt händer  
- **Felmeddelanden:** Komplett feltext, inga skärmdumpar  
- **Kod:** Minimalt kodexempel som reproducerar problemet  

---

## Tips för förebyggande

### Allmänna bästa praxis  
1. **Behåll säkerhetskopior:** Regelbundna säkerhetskopior av fungerande SD-kort/kod  
2. **Dokumentera ändringar:** Notera vad som fungerar i kommentarer  
3. **Versionshantering:** Använd git för att spåra kodändringar  
4. **Testa inkrementellt:** Testa små ändringar innan du kombinerar  
5. **Läs felmeddelanden:** De berättar ofta exakt vad som är fel  
6. **Uppdatera regelbundet:** Håll mjukvara/firmware uppdaterad  
7. **Använd kvalitetskomponenter:** Undvik billiga kablar/strömförsörjningar  
8. **Stabil ström:** Använd lämplig strömförsörjning (särskilt för Pi)  

### Utvecklingsarbetsflöde  
1. **Börja enkelt:** Starta med exempel som fungerar  
2. **En ändring i taget:** Lättare att hitta vad som går sönder  
3. **Testa ofta:** Fånga problem tidigt  
4. **Håll det organiserat:** Organisera filer och kod logiskt  
5. **Kommentera koden:** Framtida du kommer att uppskatta det  

---

*Denna felsökningsguide underhålls av communityn. Om du hittar en lösning på ett problem som inte finns med här, överväg att [bidra](CONTRIBUTING.md) för att hjälpa andra!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Ansvarsfriskrivning**:
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, vänligen observera att automatiska översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess modersmål bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för några missförstånd eller feltolkningar som uppstår från användningen av denna översättning.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->