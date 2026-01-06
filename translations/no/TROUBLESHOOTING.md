<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T06:35:42+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "no"
}
-->
# Feilsøkingsguide

Denne guiden hjelper deg med å løse vanlige problemer når du jobber med IoT for Beginners-kurset. Problemer er organisert etter kategori for enkel navigering.

## Innholdsfortegnelse

- [Installasjonsproblemer](../..)
  - [Python-installasjon](../..)
  - [VS Code og utvidelser](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove-biblioteker](../..)
- [Maskinvareproblemer](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuell enhet (CounterFit)](../..)
- [Tilkoblingsproblemer](../..)
  - [WiFi-tilkobling](../..)
  - [Sky-tjenester](../..)
  - [MQTT](../..)
- [Sensor- og aktuatorproblemer](../..)
  - [Grove-sensorer](../..)
  - [Kamera](../..)
  - [Mikrofon og høyttaler](../..)
- [Problemer med utviklingsmiljø](../..)
  - [VS Code](../..)
  - [Python virtuelle miljøer](../..)
  - [Avhengigheter](../..)
- [Ytelsesproblemer](../..)
- [Vanlige feilmeldinger](../..)
- [Få hjelp](../..)

---

## Installasjonsproblemer

### Python-installasjon

#### Problem: Python-versjonen er for gammel
**Feil:** `Python 3.6 eller nyere kreves`

**Løsning:**
1. Last ned nyeste Python 3 fra [python.org](https://www.python.org/downloads/)
2. Under installasjon på Windows, huk av for "Add Python to PATH"
3. Verifiser installasjonen:
   ```bash
   python3 --version
   ```

#### Problem: Flere Python-versjoner forårsaker konflikter
**Symptomer:** Feil Python-versjon kjører, pakker installeres på feil sted

**Løsning:**
- **Windows:** Bruk `py -3` i stedet for `python` for å eksplisitt kjøre Python 3
- **macOS/Linux:** Bruk `python3` i stedet for `python`
- Lag alltid og bruk virtuelle miljøer for prosjekter

#### Problem: pip-kommando ikke funnet
**Feil:** `'pip' er ikke gjenkjent som en intern eller ekstern kommando`

**Løsning:**
1. Prøv `pip3` i stedet for `pip`
2. Eller bruk `python -m pip` eller `python3 -m pip`
3. Sørg for at Python er lagt til PATH (installer Python på nytt og huk av for alternativet)

### VS Code og utvidelser

#### Problem: Pylance-utvidelsen fungerer ikke
**Symptomer:** Ingen Python IntelliSense, kodefullføring eller typekontroll

**Løsning:**
1. Åpne VS Code Kommandomeny (`Ctrl+Shift+P` eller `Cmd+Shift+P`)
2. Kjør "Python: Select Interpreter"
3. Velg riktig Python-tolk (virtuelt miljø hvis du bruker det)
4. Last inn VS Code-vinduet på nytt

#### Problem: VS Code oppdager ikke virtuelt miljø
**Symptomer:** Feil Python-tolk valgt

**Løsning:**
1. Sørg for at du har aktivert det virtuelle miljøet i terminalen
2. Åpne Kommandomeny og kjør "Python: Select Interpreter"
3. Velg tolken fra `.venv`-mappen
4. Sjekk statuslinjen (nederst til venstre) for å se riktig Python-versjon

### PlatformIO (Wio Terminal)

#### Problem: PlatformIO-installasjon feiler
**Feil:** Ulike feil under installasjon av PlatformIO

**Løsning:**
1. Sørg for at VS Code er oppdatert
2. Installer C/C++-utvidelsen først
3. Start VS Code på nytt etter installasjon av PlatformIO
4. Sjekk internettforbindelsen (PlatformIO laster ned store filer)

#### Problem: Kort ikke oppdaget av PlatformIO
**Symptomer:** Kan ikke laste opp kode til Wio Terminal

**Løsning:**
1. Prøv en annen USB-kabel (noen kabler er kun for lading)
2. Sjekk Enhetsbehandling (Windows) eller `ls /dev/tty*` (macOS/Linux)
3. Installer eller oppdater USB-drivere
4. Prøv en annen USB-port
5. Skyv strømbryteren på Wio Terminal ned to ganger raskt for å gå inn i bootloader-modus

#### Problem: Kompileringsfeil i PlatformIO
**Feil:** `fatal error: Arduino.h: No such file or directory`

**Løsning:**
1. Slett `.pio`-mappen i prosjektet ditt
2. Kjør "PlatformIO: Rebuild" fra Kommandomenyen
3. Sørg for at `platformio.ini` har riktig kortkonfigurasjon:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove-biblioteker

#### Problem: Grove-biblioteket import feiler på Raspberry Pi
**Feil:** `ModuleNotFoundError: No module named 'grove'`

**Løsning:**
1. Installer Grove-bibliotekene på nytt:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Hvis du bruker virtuelt miljø, må du kanskje installere globalt eller kopiere bibliotekene
3. Kontroller at I2C er aktivert: `sudo raspi-config nonint do_i2c 0`

#### Problem: Grove-sensor oppdages ikke
**Feil:** `IOError: [Errno 121] Remote I/O error`

**Løsning:**
1. Sjekk fysiske tilkoblinger (sørg for at Grove-kabelen er helt satt inn)
2. Sjekk at sensoren er koblet til riktig port (analog, digital, I2C, UART)
3. Kjør `i2cdetect -y 1` for å se om enheten vises på I2C-bussen
4. Prøv en annen Grove-kabel
5. Sørg for at Grove Base Hat sitter riktig på Raspberry Pi GPIO-pinnene

---

## Maskinvareproblemer

### Raspberry Pi

#### Problem: Raspberry Pi starter ikke
**Symptomer:** Ingen skjerm, ingen LED-aktivitet eller regnbueskjerm

**Løsning:**
1. **Sjekk strømforsyning:** Bruk offisiell 5V 3A USB-C strømforsyning for Pi 4
2. **SD-kortproblemer:** 
   - Formater SD-kortet på nytt og installer Raspberry Pi OS
   - Prøv et annet SD-kort (bruk anbefalte merker)
   - Sørg for at SD-kortet er skikkelig satt inn
3. **Sjekk HDMI-tilkobling:** Prøv begge HDMI-portene på Pi 4, bruk HDMI-porten nærmest strømtilkoblingen

#### Problem: Kan ikke koble til Raspberry Pi via SSH
**Symptomer:** Tilkobling avvist eller tidtaker

**Løsning:**
1. Aktiver SSH:
   - Når du skriver SD-kort med Raspberry Pi Imager, konfigurer SSH i avanserte innstillinger
   - Eller lag en tom fil kalt `ssh` (uten filtype) i boot-partisjonen
2. Finn Pis IP-adresse:
   - Sjekk ruteren din for tilkoblede enheter
   - Bruk `ping raspberrypi.local` (hvis mDNS fungerer)
   - Bruk nettverksskannerverktøy som `nmap` eller Angry IP Scanner
3. Sjekk nettverket:
   - Sørg for at Pi er på samme nettverk som datamaskinen
   - Prøv ethernet-tilkobling i stedet for WiFi
4. Bekreft brukernavn/passord (standard: brukernavn `pi`, passord `raspberry`)

#### Problem: Grove Base Hat ikke gjenkjent
**Symptomer:** Sensorer fungerer ikke, I2C-feil

**Løsning:**
1. Sørg for at Base Hat sitter riktig på alle GPIO-pinner
2. Sjekk om det er bøyde pinner på Pi eller Base Hat
3. Aktiver I2C-grensesnitt:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Verifiser at I2C fungerer: `i2cdetect -y 1`

#### Problem: Raspberry Pi kjører tregt
**Symptomer:** Langsomt brukergrensesnitt, treg respons

**Løsning:**
1. Sjekk SD-korthastighet (bruk klasse 10 eller bedre, eller SSD via USB)
2. Frigjør diskplass: `df -h` for å sjekke, slett unødvendige filer
3. Reduser GPU-minne i `raspi-config` hvis du ikke bruker kamera/skjerm tungt
4. Lukk unødvendige applikasjoner
5. Vurder oppgradering til Pi 4 med mer RAM hvis du bruker Pi 3 eller eldre

### Wio Terminal

#### Problem: Wio Terminal-skjerm er svart
**Symptomer:** Ingen bilde etter opplasting av kode

**Løsning:**
1. Sjekk om kode initialiserer skjermen (TFT_eSPI-biblioteket)
2. Oppdater firmware for Wio Terminal fra [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Legg til skjerminitialiseringskode:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Prøv å laste opp eksempelprogram fra PlatformIO for å teste maskinvaren

#### Problem: WiFi fungerer ikke på Wio Terminal
**Symptomer:** Kan ikke koble til WiFi, nettverksfeil

**Løsning:**
1. **Oppdater WiFi-firmware:** Følg [Wio Terminal WiFi firmware update guide](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Sjekk WiFi-legitimasjon:** Sørg for at SSID og passord er riktige
3. **WiFi-bånd:** Wio Terminal støtter kun 2,4 GHz WiFi (ikke 5 GHz)
4. **Signalstyrke:** Flytt nærmere ruteren
5. **Ruterinnstillinger:** Noen bedrifts-/WPA-Enterprise-nettverk kan ikke fungere

#### Problem: Wio Terminal gjenkjennes ikke av datamaskin
**Symptomer:** USB-enhet oppdages ikke

**Løsning:**
1. **Prøv annen USB-kabel:** Bruk datakabel, ikke kun ladekabel
2. **Gå i bootloader-modus:** Skyv strømbryteren ned to ganger raskt
   - Blå LED skal blinke, enheten vises som "Arduino" i Enhetsbehandling
3. **Installer drivere (Windows):**
   - Last ned og installer [Seeed USB driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Prøv annen USB-port:** Unngå USB-hubber, bruk direkte tilkobling
5. **Oppdater systemets USB-drivere**

#### Problem: Sensorer fungerer ikke på Wio Terminal
**Symptomer:** Grove-sensorer leser ikke data

**Løsning:**
1. Sjekk Grove-kabeltilkoblinger
2. Bekreft at du bruker riktig Grove-port (venstre eller høyre)
3. Inkluder riktige biblioteker for sensoren
4. Sjekk sensoren sine strømkrevende krav
5. Test sensoren med eksempelprogram fra biblioteket

### Virtuell enhet (CounterFit)

#### Problem: CounterFit-app starter ikke
**Feil:** Ulike Python-feil ved oppstart av CounterFit

**Løsning:**
1. Sørg for at virtuelt miljø er aktivert
2. Installer/gjeninstaller CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Sjekk at port 5000 ikke allerede er i bruk:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Stopp prosess som bruker port 5000 eller bruk en annen port:
   ```bash
   counterfit --port 5001
   ```

#### Problem: Kan ikke koble til CounterFit fra kode
**Feil:** Tilkobling avvist eller tidtaker

**Løsning:**
1. Verifiser at CounterFit kjører: Åpne nettleser til `http://127.0.0.1:5000`
2. Sjekk at tilkoblings-URL i koden matcher CounterFit-adressen
3. Sørg for at brannmur ikke blokkerer tilkoblingen
4. Prøv å starte både CounterFit-app og koden på nytt

#### Problem: Sensorer vises ikke i CounterFit
**Symptomer:** Opprettede sensorer vises ikke i CounterFit-brukergrensesnitt

**Løsning:**
1. Opprett sensorer i CounterFit UI før du kjører koden
2. Oppdater nettlesersiden
3. Sjekk at sensortypen samsvarer med hva koden forventer
4. Tøm nettleserens cache

---

## Tilkoblingsproblemer

### WiFi-tilkobling

#### Problem: Enheten kan ikke koble til WiFi
**Symptomer:** Tidsavbrudd, feil autentisering

**Løsning:**
1. **Sjekk SSID og passord:** Verifiser at legitimasjon er korrekt
2. **WiFi-bånd:** De fleste IoT-enheter støtter kun 2,4 GHz (ikke 5 GHz)
3. **Ruterinnstillinger:**
   - Deaktiver AP-isolasjon hvis aktivert
   - Bruk WPA2-PSK sikkerhet (unngå WPA3, WEP eller åpne nettverk)
   - Sørg for at DHCP er aktivert
4. **Skjulte nettverk:** Hvis SSID er skjult kan det være nødvendig å konfigurere det eksplisitt
5. **Signalstyrke:** Flytt enheten nærmere ruteren
6. **Forstyrrelser:** Andre enheter, mikrobølgeovner eller vegger kan forstyrre

#### Problem: WiFi-tilkoblingen faller ofte ut
**Symptomer:** Intermitterende tilkobling

**Løsning:**
1. Sjekk ruteren for stabilitet og vurder omstart
2. Oppdater enhetens firmware
3. Bruk statisk IP i stedet for DHCP
4. Reduser avstand til ruteren eller legg til WiFi-repeater
5. Sjekk etter forstyrrelser fra andre enheter
6. Bekreft at strømforsyningen er tilstrekkelig (spesielt for Raspberry Pi)

### Sky-tjenester

#### Problem: Kan ikke koble til Azure IoT Hub
**Feil:** Autentisering feilet, tilkobling avvist

**Løsning:**
1. **Verifiser legitimasjon:**
   - Sjekk at tilkoblingsstreng er korrekt
   - Sørg for at det ikke er ekstra mellomrom eller linjeskift i tilkoblingsstrengen
2. **Sjekk enhetsregistrering:** Enheten må være registrert i IoT Hub
3. **Brannmur/proxy:** Sørg for at utgående MQTT (port 8883) eller HTTPS (port 443) er tillatt
4. **IoT Hub-region:** Sørg for at IoT Hub kjører og ikke er i en annen region som forårsaker forsinkelse
5. **Kvotegrenser:** Sjekk om gratisnivå grenser er overskredet
6. **Test tilkobling:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problem: Azure Functions trigges ikke
**Symptomer:** Meldinger sendes men funksjonen kjører ikke

**Løsning:**
1. Sjekk at Function App kjører (ikke stoppet)
2. Verifiser tilkoblingsstreng i Function App-innstillinger
3. Sjekk funksjonslogger i Azure Portalen
4. Sørg for at Event Hub-kompatibelt endepunkt er konfigurert riktig
5. Bekreft at meldingsformat stemmer overens med funksjonens forventninger
6. Sjekk Function App tjenesteplan (forbruk vs. dedikert)

### MQTT
#### Problem: MQTT-tilkobling mislykkes
**Feil:** Tilkobling nektet, autentisering mislyktes

**Løsning:**
1. **Broker-adresse:** Bekreft at broker-URL/IP er korrekt
2. **Port:** Sjekk portnummer (1883 for ukryptert, 8883 for TLS)
3. **Autentisering:** Bekreft brukernavn/passord hvis krevd
4. **TLS/SSL:** Sørg for at sertifikater er gyldige og pålitelige
5. **Brannmur:** Sjekk at port ikke er blokkert
6. **Test med MQTT-klient:** Bruk MQTT Explorer eller mosquitto_pub/sub for å teste

#### Problem: MQTT-meldinger mottas ikke
**Symptomer:** Meldinger publiseres, men mottas ikke av abonnenter

**Løsning:**
1. **Topic-navn:** Bekreft at abonnentens topic samsvarer helt med publisherens topic
2. **QoS-nivå:** Prøv QoS 1 eller 2 i stedet for 0
3. **Wildcards:** Sjekk at topic-wildcards brukes riktig (`+` for enkelt nivå, `#` for fler-nivå)
4. **Beholdte meldinger:** Publisher kan sette retain-flagget for å beholde siste melding
5. **Tilkoblingstiming:** Sørg for at abonnenten kobles til før meldingene publiseres

---

## Sensor- og aktuatorproblemer

### Grove-sensorer

#### Problem: Sensor returnerer feil verdier
**Symptomer:** Avlesninger er 0, -1 eller meningsløse verdier

**Løsning:**
1. **Sjekk tilkoblinger:** Sørg for at sensor er riktig tilkoblet
2. **Riktig port:** Bekreft at sensor er i riktig porttype:
   - Analoge sensorer → Analoge porter (A0, A2, A4)
   - Digitale sensorer → Digitale porter (D5, D16, D18, osv.)
   - I2C-sensorer → I2C-porter
3. **Kalibrering:** Noen sensorer krever kalibrering (jordfuktighet, lys)
4. **Strøm av/på:** Koble fra og tilkobbel sensor på nytt
5. **Sensordatablad:** Sjekk sensorens spesifikasjoner og krav

#### Problem: Kapasitiv jordfuktighetssensor leser alltid våt
**Symptomer:** Sensor leser høy fuktighet selv når den er tørr

**Løsning:**
1. **Kalibrering nødvendig:** Jordsensorer krever kalibrering:
   - Les verdi i luft (tørr basislinje)
   - Les verdi i vann (våt basislinje)
   - Kartlegg avlesningene mellom disse verdiene
2. **Sjekk sensorsjikt:** Fuktighetssensorer kan forringes hvis belegg er skadet
3. **Plassering:** Sørg for at sensor er helt satt inn i jorden

#### Problem: Temperatur/fuktighetssensor gir feil avlesninger
**Symptomer:** DHT11/DHT22 viser feil temperatur eller fuktighet

**Løsning:**
1. **Sensorplassering:** Unngå direkte sollys, varmekilder eller luftstrøm
2. **Oppvarmingstid:** Tillat sensor 2 sekunders oppvarming etter strøm på før avlesning
3. **Avlesningsfrekvens:** DHT-sensorer trenger tid mellom avlesninger (minst 2 sekunder)
4. **Sjekk kondens:** Kan påvirke avlesninger
5. **Sensorqualität:** DHT11 er mindre nøyaktig enn DHT22

### Kamera

#### Problem: Kamera ikke oppdaget på Raspberry Pi
**Feil:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Løsning:**
1. **Aktiver kameragrensesnitt:**
   ```bash
   sudo raspi-config
   ```
   Gå til Interface Options → Camera → Enable
2. **Sjekk båndkabel:** Sørg for at kameraets kabel er riktig tilkoblet
   - Blå side vender mot USB-portene på Pi Zero
   - Blå side vender bort fra USB-portene på Pi 4
3. **Oppdater firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Test kamera:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problem: Kamera bilder har dårlig kvalitet
**Symptomer:** Utydelige, mørke eller utvaskede bilder

**Løsning:**
1. **Fokus:** Fjern beskyttelsesfilm fra linsen, juster fokus hvis mulig
2. **Belysning:** Sørg for tilstrekkelig belysning
3. **Kamerainnstillinger:** Juster eksponering, ISO, hvitbalanse i kode
4. **Stabilitet:** Hold kamera stødig, bruk stativ hvis nødvendig
5. **Oppløsning:** Ikke overskrid kameraets maksimale oppløsning

### Mikrofon og høyttaler

#### Problem: Ingen lyd inn/ut
**Symptomer:** Mikrofon tar ikke opp, høyttaler spiller ikke

**Løsning:**
1. **Sjekk tilkoblinger:** Verifiser at lyd-enheter er riktig koblet til
2. **Test maskinvare:**
   - Høyttaler: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` for liste, `arecord test.wav` for å ta opp
3. **Voluminnstillinger:** Sjekk og juster volum:
   ```bash
   alsamixer
   ```
4. **Velg lyd-enhet:** Spesifiser korrekt lyd-enhet i koden
5. **Driverproblemer:** Oppdater ALSA eller installer lyd-drivere på nytt

#### Problem: ReSpeaker hat fungerer ikke
**Symptomer:** Lyd-enhet ikke oppdaget

**Løsning:**
1. **Installer drivere:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Sjekk installasjon:** `arecord -l` skal liste ReSpeaker
3. **Oppdater firmware:** Noen Pi OS-versjoner trenger driveroppdateringer
4. **Sjekk plassering:** Sørg for at hat er korrekt koblet til GPIO-pinnene

---

## Utviklingsmiljøproblemer

### VS Code

#### Problem: Terminal aktiverer ikke virtual environment automatisk
**Symptomer:** Terminal åpnes, men venv aktiveres ikke

**Løsning:**
1. **Sett Python-tolk:** Command Palette → "Python: Select Interpreter" → Velg venv
2. **Start VS Code på nytt** etter å ha valgt tolk
3. **Sjekk innstillinger:** I `settings.json`, legg til:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Kode kjører ikke på enheten
**Symptomer:** Koden kjører, men ingenting skjer på enheten

**Løsning:**
1. **Sjekk at koden er lagret** (sjekk prikk på filfanen)
2. **Sjekk hvilken Python som kjører:** `which python` eller `where python`
3. **For Wio Terminal:** Sørg for at koden lastes opp via PlatformIO (klikk last opp-knappen)
4. **For Raspberry Pi:** SSH inn på Pi og kjør koden der
5. **Sjekk utdata-vinduet** for feil

#### Problem: IntelliSense viser ikke biblioteksfunksjoner
**Symptomer:** Ingen autoutfylling for importerte moduler

**Løsning:**
1. Sørg for at biblioteket er installert i gjeldende miljø
2. Last inn VS Code-vinduet på nytt
3. Kontroller at Python-tolken er riktig
4. Installer type-stubber hvis tilgjengelig: `pip install types-<biblioteksnavn>`

### Python virtuelle miljøer

#### Problem: Kan ikke opprette virtual environment
**Feil:** `The virtual environment was not created successfully`

**Løsning:**
1. **Installer venv-modul:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Skal være inkludert med Python
   - Windows: Installer Python på nytt med alle komponenter
2. **Sjekk Python-installasjon:** Bekreft at Python er riktig installert
3. **Bruk full sti:** Prøv `python3 -m venv .venv` med eksplisitt python3-kall

#### Problem: Pakker installeres på feil sted
**Symptomer:** Import-feil etter installasjon

**Løsning:**
1. **Bekreft at venv er aktivert:** Kommando-prompt skal vise `(.venv)`
2. **Sjekk pip-lokasjon:** `which pip` skal peke til `.venv/bin/pip`
3. **Installer på nytt i venv:** Aktiver venv, kjør så `pip install <pakke>`
4. **Bruk ikke sudo med pip** i virtual environment

#### Problem: Virtual environment er ikke portabelt
**Symptomer:** Venv virker ikke etter flytting eller på annen maskin

**Løsning:**
1. **Ikke flytt venv:** Slett og opprett på nytt i ny lokasjon
2. **Bruk requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Opprett venv på nytt:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # eller activate.bat på Windows
   pip install -r requirements.txt
   ```

### Avhengigheter

#### Problem: Pakkeinstallasjon feiler
**Feil:** Ulike pip-feil under installasjon

**Løsning:**
1. **Oppdater pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Installer build-verktøy:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Installer Visual Studio Build Tools
3. **Sjekk internett-tilkobling**
4. **Prøv annen pakkeindeks:** `pip install --index-url https://pypi.org/simple/ <pakke>`
5. **Installer spesifikk versjon:** `pip install <pakke>==<versjon>`

#### Problem: Avhengighetskonflikter
**Feil:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Løsning:**
1. **Bruk ferskt virtual environment** for hvert prosjekt
2. **Oppdater pakker:** `pip install --upgrade <pakke>`
3. **Sjekk krav:** Bruk `pip check` for å finne konflikter
4. **Installer kompatible versjoner:** Spesifiser versjonsintervaller i requirements.txt

---

## Ytelsesproblemer

### Problem: Kode kjører sakte
**Symptomer:** Forsinkelser, tidsavbrudd, treg respons

**Løsning:**
1. **Reduser avlesningsfrekvens for sensorer:** Ikke les sensorer for ofte
2. **Optimaliser løkker:** Unngå busy-waiting, bruk sleep() eller forsinkelser
3. **Minneproblemer:**
   - Lukk unødvendige apper
   - Frigjør lagringsplass
   - Overvåk med `top` eller `htop` på Pi
4. **SD-korthastighet:** Bruk raskere SD-kort eller SSD for Raspberry Pi
5. **Nettverksforsinkelser:** Bruk asynkrone operasjoner for nettverkskall

### Problem: Ut av minne-feil
**Feil:** `MemoryError` eller system frysing

**Løsning:**
1. **For Raspberry Pi:**
   - Lukk unødvendige apper
   - Øk swap-plass
   - Bruk lettere OS (Lite-versjon)
   - Oppgrader RAM (Pi 4 har 2/4/8GB-alternativer)
2. **For Wio Terminal:**
   - Reduser bufferstørrelser
   - Bruk mindre bilder
   - Optimaliser strengbruk
   - Sjekk for minnelekkasjer (ikke frigjort minne)

### Problem: Datatap eller korrupsjon
**Symptomer:** Manglende meldinger, ødelagte filer

**Løsning:**
1. **SD-kort-problemer:**
   - Bruk kvalitets-SD-kort (unngå billige/forfalskede)
   - Regelmessige sikkerhetskopier
   - Riktig nedstenging (ikke trekk strømmen)
2. **Buffer overflow:** Øk bufferstørrelser i koden
3. **Nettverksstabilitet:** Implementer retry-logikk og feilhåndtering
4. **Kvalitet på tjenesten:** Bruk MQTT QoS 1 eller 2 for viktige meldinger

---

## Vanlige feilmeldinger

### `ModuleNotFoundError: No module named 'X'`
**Årsak:** Pakke ikke installert eller virtual environment ikke aktivert

**Løsning:**
```bash
pip install X
```
Sørg for at virtual environment er aktivert først.

### `Permission denied` på Linux/macOS
**Årsak:** Trenger forhøyede rettigheter eller filrettighetsproblem

**Løsning:**
- For systemoperasjoner: Bruk `sudo`
- For pip: IKKE bruk sudo med venv, aktiver venv først
- For seriellport: Legg bruker til dialout-gruppen: `sudo usermod -a -G dialout $USER`, logg ut/inn igjen

### `OSError: [Errno 98] Address already in use`
**Årsak:** Port er allerede i bruk av en annen prosess

**Løsning:**
1. Finn prosess som bruker port: `lsof -i :<port>` eller `netstat -ano | findstr :<port>`
2. Avslutt prosess eller bruk annen port i koden din

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Årsak:** SSL-sertifikatvalidering feiler

**Løsning:**
1. Oppdater sertifikater: `pip install --upgrade certifi`
2. Sjekk systemtid er korrekt: `date`
3. Kun for utvikling (ikke produksjon): Deaktiver verifikasjon i kode

### `IndentationError: unexpected indent`
**Årsak:** Python-innrykkproblemer (blanding av tab og space)

**Løsning:**
1. Bruk konsekvent innrykk (4 mellomrom er Python-standard)
2. Konfigurer editor til å bruke mellomrom i stedet for tab
3. VS Code: Sett `"editor.insertSpaces": true` og `"editor.tabSize": 4`

### `UnicodeDecodeError` eller `UnicodeEncodeError`
**Årsak:** Tegnkoding-problemer

**Løsning:**
```python
# Når du leser filer
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Når du skriver filer
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Hvordan få hjelp

Hvis du har prøvd disse feilsøkingstrinnene og fortsatt har problemer:

### 1. Sjekk eksisterende ressurser
- **Dokumentasjon:** Se gjennom [README](README.md) og leksjonsinstruksjoner
- **Maskinvareg Guider:** Se [hardware.md](hardware.md) for maskinvarespesifikk info
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) for Grove-komponenter

### 2. Søk etter lignende problemer
- **GitHub Issues:** Søk [eksisterende issues](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Søk etter feilmeldinger
- **Enhetsforum:** Sjekk Raspberry Pi-fora eller Arduino-fora

### 3. Opprett en GitHub Issue
Hvis du ikke finner en løsning:
1. Gå til [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Klikk "New Issue"
3. Oppgi:
   - Klar beskrivelse av problemet
   - Trinn for å gjenskape feilen
   - Feilmeldinger (full tekst)
   - Maskinvare-/programvareversjoner
   - Hva du allerede har prøvd
   - Skjermbilder om relevant

### 4. Bli med i fellesskapet
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Gi gode feilrapporter
En god feilrapport inkluderer:
- **Miljø:** OS, Python-versjon, maskinvare brukt
- **Trinn for å gjenskape:** Eksakte trinn som forårsaker problemet
- **Forventet oppførsel:** Hva som skal skje
- **Faktisk oppførsel:** Hva som faktisk skjer
- **Feilmeldinger:** Fullstendig feilmeldingstekst, ikke skjermbilder
- **Kode:** Minimalt kodeeksempel som gjenskaper problemet

---

## Tips for forebygging

### Generelle beste praksiser
1. **Hold sikkerhetskopier:** Regelmessige sikkerhetskopier av fungerende SD-kort/kode
2. **Dokumenter endringer:** Noter hva som fungerer i kommentarer
3. **Versjonskontroll:** Bruk git for å spore kodeendringer
4. **Test inkrementelt:** Test små endringer før du kombinerer
5. **Les feilmeldinger:** De forteller ofte nøyaktig hva som er feil
6. **Oppdater jevnlig:** Hold programvare/firmware oppdatert
7. **Bruk kvalitetskomponenter:** Unngå billige kabler/strømforsyninger
8. **Stabil strøm:** Bruk passende strømforsyning (spesielt Pi)

### Utviklingsflyt
1. **Start enkelt:** Begynn med eksempelcode som fungerer
2. **Én endring om gangen:** Lett å finne hva som brytes
3. **Test ofte:** Fang problemer tidlig
4. **Hold det ryddig:** Organiser filer og kode logisk
5. **Kommenter kode:** Fremtidige deg vil sette pris på det

---

*Denne feilsøkingsguiden vedlikeholdes av fellesskapet. Hvis du finner en løsning på et problem som ikke er oppført her, vennligst vurder å [bidra](CONTRIBUTING.md) for å hjelpe andre!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Ansvarsfraskrivelse**:
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi søker nøyaktighet, vennligst vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk skal anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->