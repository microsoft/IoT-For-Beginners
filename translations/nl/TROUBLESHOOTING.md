<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T10:03:54+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "nl"
}
-->
# Problemen oplossen Gids

Deze gids helpt je bij het oplossen van veelvoorkomende problemen bij het werken met het IoT for Beginners-curriculum. Problemen zijn per categorie georganiseerd voor gemakkelijke navigatie.

## Inhoudsopgave

- [Installatieproblemen](../..)
  - [Python Installatie](../..)
  - [VS Code en Extensies](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove Bibliotheken](../..)
- [Hardwareproblemen](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtueel Apparaat (CounterFit)](../..)
- [Connectiviteitsproblemen](../..)
  - [WiFi Verbinding](../..)
  - [Cloud Services](../..)
  - [MQTT](../..)
- [Sensor- en actuatorproblemen](../..)
  - [Grove Sensoren](../..)
  - [Camera](../..)
  - [Microfoon en Speaker](../..)
- [Ontwikkelomgeving problemen](../..)
  - [VS Code](../..)
  - [Python Virtuele Omgevingen](../..)
  - [Afhankelijkheden](../..)
- [Prestatieproblemen](../..)
- [Veelvoorkomende Foutmeldingen](../..)
- [Hulp Krijgen](../..)

---

## Installatieproblemen

### Python Installatie

#### Probleem: Python-versie is te oud
**Fout:** `Python 3.6 of hoger is vereist`

**Oplossing:**
1. Download de nieuwste Python 3 van [python.org](https://www.python.org/downloads/)
2. Vink tijdens installatie op Windows "Add Python to PATH" aan
3. Controleer installatie:
   ```bash
   python3 --version
   ```

#### Probleem: Meerdere Python-versies veroorzaken conflicten
**Symptomen:** Verkeerde Python-versie wordt uitgevoerd, pakketten worden op verkeerde locatie geïnstalleerd

**Oplossing:**
- **Windows:** Gebruik `py -3` in plaats van `python` om expliciet Python 3 aan te roepen
- **macOS/Linux:** Gebruik `python3` in plaats van `python`
- Maak altijd virtuele omgevingen voor projecten en gebruik deze

#### Probleem: pip-commando niet gevonden
**Fout:** `'pip' is geen interne of externe opdracht`

**Oplossing:**
1. Probeer `pip3` in plaats van `pip`
2. Of gebruik `python -m pip` of `python3 -m pip`
3. Zorg dat Python aan PATH is toegevoegd (herinstalleer Python en vink optie aan)

### VS Code en Extensies

#### Probleem: Pylance-extensie werkt niet
**Symptomen:** Geen Python IntelliSense, code-aanvulling of typechecking

**Oplossing:**
1. Open VS Code Command Palette (`Ctrl+Shift+P` of `Cmd+Shift+P`)
2. Voer "Python: Select Interpreter" uit
3. Kies de juiste Python-interpreter (virtuele omgeving als je die gebruikt)
4. Herlaad VS Code-venster

#### Probleem: VS Code detecteert geen virtuele omgeving
**Symptomen:** Verkeerde Python-interpreter geselecteerd

**Oplossing:**
1. Zorg dat je de virtuele omgeving hebt geactiveerd in de terminal
2. Open Command Palette en voer "Python: Select Interpreter" uit
3. Selecteer de interpreter uit de `.venv`-map
4. Controleer of de statusbalk (linksonder) de juiste Python-versie toont

### PlatformIO (Wio Terminal)

#### Probleem: PlatformIO-installatie mislukt
**Fout:** Diverse fouten tijdens PlatformIO-installatie

**Oplossing:**
1. Zorg dat VS Code up-to-date is
2. Installeer eerst de C/C++ extensie
3. Start VS Code opnieuw na installeren van PlatformIO
4. Controleer je internetverbinding (PlatformIO downloadt grote bestanden)

#### Probleem: Board wordt niet gedetecteerd door PlatformIO
**Symptomen:** Kan code niet uploaden naar Wio Terminal

**Oplossing:**
1. Probeer een andere USB-kabel (sommige kabels zijn alleen voor opladen)
2. Controleer Apparaatbeheer (Windows) of `ls /dev/tty*` (macOS/Linux)
3. Installeer of update USB-drivers
4. Probeer een andere USB-poort
5. Schuif de aan/uit-schakelaar op de Wio Terminal twee keer snel om bootloader-modus te activeren

#### Probleem: Compileerfouten in PlatformIO
**Fout:** `fatal error: Arduino.h: No such file or directory`

**Oplossing:**
1. Verwijder `.pio`-map in je project
2. Voer "PlatformIO: Rebuild" uit via Command Palette
3. Zorg dat `platformio.ini` de juiste boardconfiguratie bevat:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove Bibliotheken

#### Probleem: Import van Grove bibliotheek mislukt op Raspberry Pi
**Fout:** `ModuleNotFoundError: No module named 'grove'`

**Oplossing:**
1. Herinstalleer Grove bibliotheken:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Als je een virtuele omgeving gebruikt, moet je mogelijk globaal installeren of bibliotheken kopiëren
3. Controleer of I2C is ingeschakeld: `sudo raspi-config nonint do_i2c 0`

#### Probleem: Grove sensor wordt niet gedetecteerd
**Fout:** `IOError: [Errno 121] Remote I/O error`

**Oplossing:**
1. Controleer fysieke verbindingen (zorg dat Grove-kabel volledig is geplaatst)
2. Controleer dat sensor op juiste poort is aangesloten (analoog, digitaal, I2C, UART)
3. Voer `i2cdetect -y 1` uit om te zien of apparaat op I2C-bus verschijnt
4. Probeer een andere Grove-kabel
5. Zorg dat Grove Base Hat goed op Raspberry Pi GPIO-pinnen is geplaatst

---

## Hardwareproblemen

### Raspberry Pi

#### Probleem: Raspberry Pi start niet op
**Symptomen:** Geen beeld, geen LED-activiteit, of regenboogscherm

**Oplossing:**
1. **Controleer voeding:** Gebruik officiële 5V 3A USB-C voeding voor Pi 4
2. **SD-kaart problemen:** 
   - Formatteer SD-kaart en installeer Raspberry Pi OS opnieuw
   - Probeer een andere SD-kaart (gebruik aanbevolen merken)
   - Zorg dat SD-kaart goed is geplaatst
3. **Controleer HDMI-verbinding:** Probeer beide HDMI-poorten op Pi 4, gebruik HDMI-poort dichtst bij voeding

#### Probleem: Kan niet SSH-en naar Raspberry Pi
**Symptomen:** Verbinding geweigerd of time-out

**Oplossing:**
1. SSH inschakelen:
   - Bij het flashen van SD-kaart met Raspberry Pi Imager, configureer SSH in geavanceerde opties
   - Of maak een leeg bestand genaamd `ssh` (zonder extensie) in boot-partitie
2. Vind IP-adres van Pi:
   - Controleer aangesloten apparaten op router
   - Gebruik `ping raspberrypi.local` (indien mDNS werkt)
   - Gebruik netwerk-scantools zoals `nmap` of Angry IP Scanner
3. Controleer netwerk:
   - Zorg dat Pi op hetzelfde netwerk zit als je computer
   - Probeer ethernetverbinding in plaats van WiFi
4. Controleer gebruikersnaam/wachtwoord (standaard: gebruiker `pi`, wachtwoord `raspberry`)

#### Probleem: Grove Base Hat wordt niet herkend
**Symptomen:** Sensoren werken niet, I2C fouten

**Oplossing:**
1. Zorg dat Base Hat goed op alle GPIO-pinnen zit
2. Controleer op verbogen pinnen op Pi of Base Hat
3. Schakel I2C-interface in:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Controleer of I2C werkt: `i2cdetect -y 1`

#### Probleem: Raspberry Pi werkt traag
**Symptomen:** Trage UI, vertraagde reacties

**Oplossing:**
1. Controleer SD-kaart snelheid (gebruik Class 10 of beter, of SSD via USB)
2. Maak schijfruimte vrij: `df -h` om te controleren, verwijder onnodige bestanden
3. Verminder GPU-geheugen in `raspi-config` als je camera/display niet veel gebruikt
4. Sluit onnodige programma's
5. Overweeg upgrade naar Pi 4 met meer RAM als je Pi 3 of ouder gebruikt

### Wio Terminal

#### Probleem: Wio Terminal scherm blijft zwart
**Symptomen:** Geen beeld na uploaden van code

**Oplossing:**
1. Controleer of code display initialiseert (TFT_eSPI library)
2. Update Wio Terminal firmware via [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Voeg display initialisatiecode toe:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Probeer voorbeeldschets vanuit PlatformIO te uploaden om hardware te testen

#### Probleem: WiFi werkt niet op Wio Terminal
**Symptomen:** Kan niet verbinden met WiFi, netwerkfouten

**Oplossing:**
1. **Update WiFi firmware:** Volg [Wio Terminal WiFi firmware update gids](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Controleer WiFi-inloggegevens:** Zorg dat SSID en wachtwoord correct zijn
3. **WiFi-band:** Wio Terminal ondersteunt alleen 2.4GHz WiFi (geen 5GHz)
4. **Signaalsterkte:** Verplaats dichter naar router
5. **Router instellingen:** Sommige enterprise/WPA-Enterprise-netwerken werken mogelijk niet

#### Probleem: Wio Terminal wordt niet herkend door computer
**Symptomen:** USB-apparaat wordt niet gedetecteerd

**Oplossing:**
1. **Probeer andere USB-kabel:** Gebruik datakabel, geen opladerkabel
2. **Ga in bootloader-modus:** Schuif aan/uit-schakelaar twee keer snel omlaag
   - Blauwe LED moet pulseren, apparaat wordt als "Arduino" herkend in Apparaatbeheer
3. **Installeer drivers (Windows):**
   - Download en installeer [Seeed USB driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Probeer andere USB-poort:** Vermijd USB-hubs, gebruik directe verbinding
5. **Update systeem USB-drivers**

#### Probleem: Sensoren werken niet op Wio Terminal
**Symptomen:** Grove sensoren lezen geen data

**Oplossing:**
1. Controleer Grove-kabelverbindingen
2. Controleer of je de juiste Grove-poort gebruikt (links of rechts)
3. Voeg juiste bibliotheken toe voor sensor
4. Controleer stroomvereisten van sensor
5. Test sensor met voorbeeldcode uit bibliotheek

### Virtueel Apparaat (CounterFit)

#### Probleem: CounterFit-app start niet
**Fout:** Diverse Python-fouten bij starten CounterFit

**Oplossing:**
1. Zorg dat virtuele omgeving is geactiveerd
2. Installeer/herinstalleer CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Controleer dat poort 5000 niet al in gebruik is:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Stop proces dat poort 5000 gebruikt of gebruik een andere poort:
   ```bash
   counterfit --port 5001
   ```

#### Probleem: Kan niet verbinden met CounterFit vanuit code
**Fout:** Verbinding geweigerd of time-out

**Oplossing:**
1. Controleer dat CounterFit draait: Open browser op `http://127.0.0.1:5000`
2. Controleer dat verbindings-URL in code overeenkomt met CounterFit-adres
3. Zorg dat firewall verbinding niet blokkeert
4. Probeer zowel CounterFit-app als je code opnieuw te starten

#### Probleem: Sensoren verschijnen niet in CounterFit
**Symptomen:** Gemaakte sensoren worden niet getoond in CounterFit UI

**Oplossing:**
1. Maak sensoren aan in CounterFit UI vóór het draaien van code
2. Vernieuw browserpagina
3. Controleer dat sensortype overeenkomt met wat code verwacht
4. Wis browsercache

---

## Connectiviteitsproblemen

### WiFi Verbinding

#### Probleem: Apparaat kan niet verbinden met WiFi
**Symptomen:** Verbindings time-out, authenticatie mislukt

**Oplossing:**
1. **Controleer SSID en wachtwoord:** Verifieer dat gegevens kloppen
2. **WiFi-band:** De meeste IoT-apparaten ondersteunen alleen 2.4GHz (geen 5GHz)
3. **Router instellingen:**
   - Schakel AP isolation uit indien ingeschakeld
   - Gebruik WPA2-PSK beveiliging (vermijd WPA3, WEP of open netwerken)
   - Zorg dat DHCP is ingeschakeld
4. **Verborgen netwerken:** Indien SSID verborgen is, moet je het mogelijk expliciet configureren
5. **Signaalsterkte:** Zet apparaat dichter bij router
6. **Storing:** Andere apparaten, magnetrons of muren kunnen storing veroorzaken

#### Probleem: WiFi-verbinding valt vaak uit
**Symptomen:** Periodieke verbindingen

**Oplossing:**
1. Controleer routerstabiliteit en overweeg herstart
2. Update apparaatfirmware
3. Gebruik statisch IP in plaats van DHCP
4. Verminder afstand tot router of gebruik WiFi-extender
5. Controleer op storing van andere apparaten
6. Controleer of voeding adequaat is (vooral bij Raspberry Pi)

### Cloud Services

#### Probleem: Kan niet verbinden met Azure IoT Hub
**Fout:** Authenticatie mislukt, verbinding geweigerd

**Oplossing:**
1. **Controleer inloggegevens:**
   - Controleer of verbindingsstring correct is
   - Zorg dat er geen spaties of regeleinden in verbindingsstring staan
2. **Controleer apparaatregistratie:** Apparaat moet geregistreerd zijn in IoT Hub
3. **Firewall/proxy:** Zorg dat uitgaande MQTT (poort 8883) of HTTPS (poort 443) is toegestaan
4. **IoT Hub regio:** Controleer dat IoT Hub actief is en niet in andere regio zit die latentie veroorzaakt
5. **Quota limieten:** Controleer of gratis limieten niet overschreden zijn
6. **Test verbinding:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Probleem: Azure Functions worden niet geactiveerd
**Symptomen:** Berichten worden verzonden maar functie wordt niet uitgevoerd

**Oplossing:**
1. Controleer of Function App draait (niet gestopt)
2. Verifieer verbindingsstring in Function App-instellingen
3. Controleer functielogs in Azure Portal
4. Zorg dat Event Hub compatibele endpoint correct is ingesteld
5. Controleer dat berichtformaat overeenkomt met functievereisten
6. Controleer Function App serviceplan (consumptie vs. dedicated)

### MQTT
#### Probleem: MQTT-verbinding mislukt  
**Fout:** Verbinding geweigerd, authenticatie mislukt  

**Oplossing:**  
1. **Brokeradres:** Controleer of de broker-URL/IP correct is  
2. **Poort:** Controleer het poortnummer (1883 voor niet-versleuteld, 8883 voor TLS)  
3. **Authenticatie:** Controleer gebruikersnaam/wachtwoord indien vereist  
4. **TLS/SSL:** Zorg dat certificaten geldig en vertrouwd zijn  
5. **Firewall:** Controleer of de poort niet geblokkeerd is  
6. **Test met MQTT-client:** Gebruik MQTT Explorer of mosquitto_pub/sub om te testen  

#### Probleem: MQTT-berichten worden niet ontvangen  
**Symptomen:** Berichten worden gepubliceerd maar niet door abonnees ontvangen  

**Oplossing:**  
1. **Topicnamen:** Controleer of het abonnee-topic exact overeenkomt met het uitgever-topic  
2. **QoS-niveau:** Probeer QoS 1 of 2 in plaats van 0  
3. **Wildcards:** Controleer of topic wildcards correct gebruikt worden (`+` voor één niveau, `#` voor meerdere niveaus)  
4. **Retained berichten:** Uitgever kan retain-flag zetten om laatste bericht te bewaren  
5. **Connectietiming:** Zorg dat abonnee al verbonden is voordat berichten worden gepubliceerd  

---

## Problemen met sensoren en actuatoren

### Grove-sensoren

#### Probleem: Sensor geeft onjuiste waarden terug  
**Symptomen:** Waarden zijn 0, -1 of onzinnige waarden  

**Oplossing:**  
1. **Controleer verbindingen:** Zorg dat sensor correct is aangesloten  
2. **Juiste poort:** Controleer of sensor is aangesloten op juiste poorttype:  
   - Analoge sensoren → Analoge poorten (A0, A2, A4)  
   - Digitale sensoren → Digitale poorten (D5, D16, D18, etc.)  
   - I2C-sensoren → I2C-poorten  
3. **Kalibratie:** Sommige sensoren vereisen kalibratie (bodemvocht, licht)  
4. **Stroomcyclus:** Koppel sensor los en weer aan  
5. **Sensor datasheet:** Controleer sensor specificaties en eisen  

#### Probleem: Capacitatieve bodemvochtsensor leest altijd nat  
**Symptomen:** Sensor geeft hoge vochtwaarde zelfs als droog  

**Oplossing:**  
1. **Kalibratie nodig:** Bodemsensoren moeten gekalibreerd worden:  
   - Waarde meten in lucht (droge basislijn)  
   - Waarde meten in water (natte basislijn)  
   - Waarden daartussen afstemmen  
2. **Controleer sensorcoating:** Vochtsensoren kunnen verslechteren als coating beschadigd is  
3. **Plaatsing:** Zorg dat sensor volledig in de bodem zit  

#### Probleem: Temperatuur-/vochtsensor geeft onjuiste waarden  
**Symptomen:** DHT11/DHT22 toont verkeerde temperatuur of vochtigheid  

**Oplossing:**  
1. **Sensorplaatsing:** Vermijd direct zonlicht, warmtebronnen of tocht  
2. **Opwarmtijd:** Geef sensor 2 seconden na inschakelen voordat je leest  
3. **Leessnelheid:** DHT-sensoren hebben tijd nodig tussen metingen (minimaal 2 seconden)  
4. **Controleer op condensatie:** Dit kan metingen beïnvloeden  
5. **Sensor kwaliteit:** DHT11 is minder nauwkeurig dan DHT22  

### Camera

#### Probleem: Camera wordt niet gedetecteerd op Raspberry Pi  
**Fout:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`  

**Oplossing:**  
1. **Zet camera-interface aan:**  
   ```bash
   sudo raspi-config
   ```
   Ga naar Interface-opties → Camera → Inschakelen  
2. **Controleer lintkabel:** Zorg dat camerakabel correct is aangesloten  
   - Blauwe zijde wijst naar USB-poorten op Pi Zero  
   - Blauwe zijde wijst weg van USB-poorten op Pi 4  
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
  
#### Probleem: Camerabeelden zijn van slechte kwaliteit  
**Symptomen:** Wazige, donkere of uitgebleekte beelden  

**Oplossing:**  
1. **Focus:** Verwijder beschermfolie van lens, stel scherp indien aanpasbaar  
2. **Verlichting:** Zorg voor voldoende licht  
3. **Camera-instellingen:** Pas belichting, ISO, witbalans aan in code  
4. **Stabiliteit:** Houd camera stil, gebruik statief indien nodig  
5. **Resolutie:** Overschrijd niet de maximale resolutie van de camera  

### Microfoon en luidspreker

#### Probleem: Geen audio-invoer/-uitvoer  
**Symptomen:** Microfoon neemt niet op, luidspreker speelt niet af  

**Oplossing:**  
1. **Controleer verbindingen:** Controleer of audioapparaten goed aangesloten zijn  
2. **Test hardware:**  
   - Luidspreker: `speaker-test -t wav -c 2`  
   - Microfoon: `arecord -l` om op te sommen, `arecord test.wav` om op te nemen  
3. **Volume-instellingen:** Controleer en pas volume aan:  
   ```bash
   alsamixer
   ```
4. **Selecteer audioapparaat:** Geef juiste audioapparaat op in code  
5. **Driverproblemen:** Update ALSA of installeer audio drivers opnieuw  

#### Probleem: ReSpeaker hat werkt niet  
**Symptomen:** Audioapparaat wordt niet gedetecteerd  

**Oplossing:**  
1. **Installeer drivers:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Controleer installatie:** `arecord -l` zou ReSpeaker moeten tonen  
3. **Update firmware:** Sommige Pi OS versies vereisen driver-updates  
4. **Controleer aansluiting:** Zorg dat hat correct verbonden is met GPIO-pinnen  

---

## Problemen in ontwikkelomgeving

### VS Code

#### Probleem: Terminal activeert virtuele omgeving niet automatisch  
**Symptomen:** Terminal opent maar venv wordt niet geactiveerd  

**Oplossing:**  
1. **Stel Python-interpreter in:** Command Palette → "Python: Select Interpreter" → Kies venv  
2. **Herstart VS Code** na het kiezen van de interpreter  
3. **Controleer instellingen:** Voeg toe in `settings.json`:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Probleem: Code draait niet op apparaat  
**Symptomen:** Code draait, maar er gebeurt niets op apparaat  

**Oplossing:**  
1. **Controleer dat code opgeslagen is** (check stip op tabblad)  
2. **Controleer welke Python draait:** `which python` of `where python`  
3. **Voor Wio Terminal:** Zorg dat code via PlatformIO is geüpload (klik op uploadknop)  
4. **Voor Raspberry Pi:** SSH naar Pi en draai code daar  
5. **Bekijk output-venster** op fouten  

#### Probleem: IntelliSense toont geen bibliotheekfuncties  
**Symptomen:** Geen autocompletie bij geïmporteerde modules  

**Oplossing:**  
1. Zorg dat bibliotheek is geïnstalleerd in huidige omgeving  
2. Herlaad VS Code-venster  
3. Controleer juiste Python-interpreter  
4. Installeer type stubs als beschikbaar: `pip install types-<bibliotheeknaam>`  

### Python virtuele omgevingen

#### Probleem: Kan geen virtuele omgeving creëren  
**Fout:** `The virtual environment was not created successfully`  

**Oplossing:**  
1. **Installeer venv-module:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Moet inbegrepen zijn bij Python  
   - Windows: Herinstalleer Python met alle onderdelen  
2. **Controleer Python-installatie:** Verify Python is correct geïnstalleerd  
3. **Gebruik volledig pad:** Probeer `python3 -m venv .venv` met expliciete python3-aanroep  

#### Probleem: Pakketten installeren op verkeerde locatie  
**Symptomen:** Importfout na installatie pakket  

**Oplossing:**  
1. **Controleer of venv actief is:** Prompt toont `(.venv)`  
2. **Controleer pip-locatie:** `which pip` moet wijzen naar `.venv/bin/pip`  
3. **Herinstalleer in venv:** Activeer venv, daarna `pip install <package>`  
4. **Gebruik geen sudo met pip** in virtuele omgeving  

#### Probleem: Virtuele omgeving is niet draagbaar  
**Symptomen:** Venv werkt niet na verplaatsen of op andere computer  

**Oplossing:**  
1. **Verplaats venv niet:** Verwijder en maak opnieuw aan op nieuwe locatie  
2. **Gebruik requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Maak venv opnieuw aan:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # of activate.bat op Windows
   pip install -r requirements.txt
   ```
  
### Afhankelijkheden

#### Probleem: Pakketinstallatie faalt  
**Fout:** Diverse pip-fouten tijdens installatie  

**Oplossing:**  
1. **Update pip:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Installeer bouwtools:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Installeer Visual Studio Build Tools  
3. **Controleer internetverbinding**  
4. **Probeer andere pakketindex:** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **Installeer specifieke versie:** `pip install <package>==<versie>`  

#### Probleem: Afhankelijkheidsconflicten  
**Fout:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`  

**Oplossing:**  
1. **Gebruik verse virtuele omgeving** voor elk project  
2. **Update pakketten:** `pip install --upgrade <package>`  
3. **Controleer requirements:** Gebruik `pip check` om conflicten te vinden  
4. **Installeer compatibele versies:** Specificeer versiebereik in requirements.txt  

---

## Prestatieproblemen

### Probleem: Code draait traag  
**Symptomen:** Vertraging, time-outs, niet reagerend gedrag  

**Oplossing:**  
1. **Verminder sensorleesfrequentie:** Lees sensoren niet te vaak uit  
2. **Optimaliseer lussen:** Vermijd busy-waiting, gebruik sleep() of vertragingen  
3. **Geheugenproblemen:**  
   - Sluit onnodige applicaties  
   - Maak opslagruimte vrij  
   - Monitor met `top` of `htop` op Pi  
4. **Snelheid SD-kaart:** Gebruik snellere SD-kaart of SSD voor Raspberry Pi  
5. **Netwerkvertragingen:** Gebruik async operaties voor netwerkverkeer  

### Probleem: Out of memory fouten  
**Fout:** `MemoryError` of vastlopend systeem  

**Oplossing:**  
1. **Voor Raspberry Pi:**  
   - Sluit onnodige applicaties  
   - Vergroot swapruimte  
   - Gebruik lichtere OS (Lite versie)  
   - Upgrade RAM (Pi 4 beschikbaar met 2/4/8GB)  
2. **Voor Wio Terminal:**  
   - Verminder bufferformaten  
   - Gebruik kleinere afbeeldingen  
   - Optimaliseer stringgebruik  
   - Controleer op geheugenlekken (niet vrijgegeven geheugen)  

### Probleem: Gegevensverlies of corruptie  
**Symptomen:** Missende berichten, corrupte bestanden  

**Oplossing:**  
1. **SD-kaartproblemen:**  
   - Gebruik kwaliteits-SD-kaarten (vermijd goedkope/nep)  
   - Maak regelmatige back-ups  
   - Zorg voor correcte afsluiting (geen stroom eruit halen)  
2. **Buffer overflow:** Verhoog buffers in code  
3. **Netwerk betrouwbaarheid:** Implementeer retry-logica en foutafhandeling  
4. **Kwaliteit van Dienst:** Gebruik MQTT QoS 1 of 2 voor belangrijke berichten  

---

## Veelvoorkomende foutmeldingen

### `ModuleNotFoundError: No module named 'X'`  
**Oorzaak:** Pakket niet geïnstalleerd of virtuele omgeving niet geactiveerd  

**Oplossing:**  
```bash
pip install X
```
Zorg dat virtuele omgeving eerst geactiveerd is.  

### `Permission denied` op Linux/macOS  
**Oorzaak:** Vereist verhoogde rechten of bestandstoegangprobleem  

**Oplossing:**  
- Voor systeemoperaties: Gebruik `sudo`  
- Voor pip: NIET sudo gebruiken met venv, activeer venv eerst  
- Voor seriële poort: Voeg gebruiker toe aan dialout groep: `sudo usermod -a -G dialout $USER`, vervolgens afmelden/aanmelden  

### `OSError: [Errno 98] Address already in use`  
**Oorzaak:** Poort wordt al door een ander proces gebruikt  

**Oplossing:**  
1. Zoek proces dat poort gebruikt: `lsof -i :<poort>` of `netstat -ano | findstr :<poort>`  
2. Stop proces of gebruik andere poort in code  

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Oorzaak:** SSL-certificaat validatie mislukt  

**Oplossing:**  
1. Update certificaten: `pip install --upgrade certifi`  
2. Controleer systeemtijd is correct: `date`  
3. Alleen voor ontwikkeling (niet productie): Schakel verificatie uit in code  

### `IndentationError: unexpected indent`  
**Oorzaak:** Python inspringfouten (mix van tabs/spaties)  

**Oplossing:**  
1. Gebruik consistente inspringing (4 spaties is Python-standaard)  
2. Stel editor in op spaties in plaats van tabs  
3. VS Code: Zet `"editor.insertSpaces": true` en `"editor.tabSize": 4`  

### `UnicodeDecodeError` of `UnicodeEncodeError`  
**Oorzaak:** Problemen met tekencodering  

**Oplossing:**  
```python
# Bij het lezen van bestanden
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Bij het schrijven van bestanden
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Hulp krijgen

Als je deze stappen hebt geprobeerd en nog steeds problemen hebt:

### 1. Controleer bestaande bronnen  
- **Documentatie:** Bekijk de [README](README.md) en lesinstructies  
- **Hardwarehandleidingen:** Bekijk [hardware.md](hardware.md) voor hardware-specifieke info  
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) voor Grove-componenten  

### 2. Zoek naar vergelijkbare problemen  
- **GitHub Issues:** Zoek in [bestaande issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Zoek op foutmeldingen  
- **Apparaatforums:** Bekijk Raspberry Pi forums of Arduino forums  

### 3. Maak een GitHub Issue aan  
Als je geen oplossing vindt:  
1. Ga naar [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Klik op "New Issue"  
3. Geef op:  
   - Duidelijke omschrijving van het probleem  
   - Stappen om te reproduceren  
   - Foutmeldingen (volledige tekst)  
   - Hardware-/softwareversies  
   - Wat je al geprobeerd hebt  
   - Screenshots indien relevant  

### 4. Word lid van de community  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)  

### 5. Lever goede bugrapporten aan  
Een goed bugrapport bevat:
- **Omgeving:** OS, Python-versie, gebruikte hardware
- **Stappen om te reproduceren:** Exacte stappen die het probleem veroorzaken
- **Verwacht gedrag:** Wat er zou moeten gebeuren
- **Eigenlijk gedrag:** Wat er daadwerkelijk gebeurt
- **Foutmeldingen:** Volledige fouttekst, geen schermafbeeldingen
- **Code:** Minimale codevoorbeeld die het probleem reproduceert

---

## Tips voor Preventie

### Algemene Beste Praktijken
1. **Maak back-ups:** Regelmatige back-ups van werkende SD-kaarten/code
2. **Documenteer veranderingen:** Noteer wat werkt in opmerkingen
3. **Versiebeheer:** Gebruik git om codewijzigingen bij te houden
4. **Test stapsgewijs:** Test kleine veranderingen voordat je ze combineert
5. **Lees foutmeldingen:** Ze vertellen vaak precies wat er mis is
6. **Werk regelmatig bij:** Houd software/firmware up-to-date
7. **Gebruik kwaliteitscomponenten:** Vermijd goedkope kabels/voedingen
8. **Stabiele voeding:** Gebruik een passende voeding (vooral bij Pi)

### Ontwikkelworkflow
1. **Begin simpel:** Start met voorbeeldcode die werkt
2. **Één verandering tegelijk:** Makkelijker te vinden wat het breekt
3. **Test vaak:** Ontdek problemen vroeg
4. **Houd het overzichtelijk:** Organiseer bestanden en code logisch
5. **Commentaar bij code:** Je toekomstige zelf zal het waarderen

---

*Deze handleiding voor probleemoplossing wordt onderhouden door de gemeenschap. Als je een oplossing vindt voor een probleem dat hier niet vermeld staat, overweeg dan alsjeblieft om [bij te dragen](CONTRIBUTING.md) om anderen te helpen!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Disclamer**:
Dit document is vertaald met behulp van de AI-vertalingsdienst [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u er rekening mee te houden dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het oorspronkelijke document in de oorspronkelijke taal moet als de gezaghebbende bron worden beschouwd. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->