<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-07T01:06:25+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "et"
}
-->
# Tõrkeotsingu juhend

See juhend aitab teil lahendada tavalisi probleeme IoT for Beginners õppekava kasutamisel. Probleemid on kategooriate kaupa mugavaks navigeerimiseks organiseeritud.

## Sisukord

- [Paigaldusprobleemid](../..)
  - [Python'i paigaldus](../..)
  - [VS Code ja laiendused](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove teegid](../..)
- [Riistvaraprobleemid](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuaalseade (CounterFit)](../..)
- [Ühenduvusprobleemid](../..)
  - [WiFi ühendus](../..)
  - [Pilveteenused](../..)
  - [MQTT](../..)
- [Andurite ja täiturite probleemid](../..)
  - [Grove andurid](../..)
  - [Kaamera](../..)
  - [Mikrofon ja kõlar](../..)
- [Arenduskeskkonna probleemid](../..)
  - [VS Code](../..)
  - [Python virtuaal keskkonnad](../..)
  - [Sõltuvused](../..)
- [Töökindluse probleemid](../..)
- [Tavalised veateated](../..)
- [Abi saamine](../..)

---

## Paigaldusprobleemid

### Python'i paigaldus

#### Probleem: Python'i versioon on liiga vana
**Viga:** `On vaja Python 3.6 või uuemat`

**Lahendus:**
1. Laadige alla uusim Python 3 aadressilt [python.org](https://www.python.org/downloads/)
2. Windowsi paigalduse ajal märkige "Add Python to PATH"
3. Kontrollige paigaldust:
   ```bash
   python3 --version
   ```

#### Probleem: Mitme Python'i versiooni konfliktid
**Sümptomid:** Käivitub vale Python'i versioon, paketid installeeruvad valesse kohta

**Lahendus:**
- **Windows:** Kasutage `py -3` asemel `python` Python 3 käivitamiseks
- **macOS/Linux:** Kasutage `python3` asemel `python`
- Alati looge ja kasutage projektide jaoks virtuaalkeskkondi

#### Probleem: pip käsku ei leita
**Viga:** `'pip' ei ole sisemine ega väline käsk`

**Lahendus:**
1. Proovige `pip3` asemel `pip`
2. Või kasutage `python -m pip` või `python3 -m pip`
3. Veenduge, et Python on PATH-is (paigaldage Python uuesti ja märkige vastav valik)

### VS Code ja laiendused

#### Probleem: Pylance laiendus ei tööta
**Sümptomid:** Puudub Python IntelliSense, koodi lõpetamine või tüübikontroll

**Lahendus:**
1. Avage VS Code käsupalet (`Ctrl+Shift+P` või `Cmd+Shift+P`)
2. Käivitage "Python: Select Interpreter"
3. Valige õige Python tõlgendaja (virtuaalkeskkond, kui kasutatakse)
4. Laadige VS Code aken uuesti

#### Probleem: VS Code ei tuvasta virtuaalkeskkonda
**Sümptomid:** Vali Python tõlgendaja valitud

**Lahendus:**
1. Veenduge, et olete virtuaalkeskkonna terminalis aktiveerinud
2. Avage käsupalet ja käivitage "Python: Select Interpreter"
3. Valige `.venv` kaustast tõlgendaja
4. Kontrollige olekuribal (vasakus allosas) õige Python versiooni kuvamist

### PlatformIO (Wio Terminal)

#### Probleem: PlatformIO paigaldus ebaõnnestub
**Viga:** Mitmesugused vead PlatformIO paigalduse ajal

**Lahendus:**
1. Veenduge, et VS Code on ajakohane
2. Paigaldage esmalt C/C++ laiendus
3. Taaskäivitage VS Code pärast PlatformIO paigaldust
4. Kontrollige internetiühendust (PlatformIO laadib suuri faile)

#### Probleem: PlatformIO ei tuvasta plaati
**Sümptomid:** Ei saa koodi Wio Terminalile üles laadida

**Lahendus:**
1. Proovige teist USB kaablit (mõned kaablid on vaid laadimiseks)
2. Kontrollige seadmehaldurit (Windows) või `ls /dev/tty*` (macOS/Linux)
3. Paigaldage või uuendage USB draivereid
4. Proovige teist USB pesa
5. Lükake Wio Terminali toitenupp kaks korda kiiresti alla, et minna bootloader režiimi

#### Probleem: PlatformIO kompileerimise vead
**Viga:** `fatal error: Arduino.h: File not found`

**Lahendus:**
1. Kustutage projekti `.pio` kaust
2. Käivitage käsupaletilt "PlatformIO: Rebuild"
3. Kontrollige `platformio.ini` õigesti seadistatud plaadi puhul:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove teegid

#### Probleem: Grove teegi import ebaõnnestub Raspberry Pi-s
**Viga:** `ModuleNotFoundError: No module named 'grove'`

**Lahendus:**
1. Paigaldage Grove teegid uuesti:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Kui kasutate virtuaalkeskkonda, võib olla vaja installida globaalselt või kopeerida teegid
3. Kontrollige, et I2C on lubatud: `sudo raspi-config nonint do_i2c 0`

#### Probleem: Grove andurit ei tuvastata
**Viga:** `IOError: [Errno 121] Remote I/O error`

**Lahendus:**
1. Kontrollige füüsilisi ühendusi (veenduge, et Grove kaabel on korralikult ühendatud)
2. Veenduge, et andur on ühendatud õigele pordile (analoog, digitaalne, I2C, UART)
3. Käivitage `i2cdetect -y 1`, et näha, kas seade on I2C bussil nähtav
4. Proovige teist Grove kaablit
5. Veenduge, et Grove Base Hat on korrektselt ühendatud Raspberry Pi GPIO jalgadele

---

## Riistvaraprobleemid

### Raspberry Pi

#### Probleem: Raspberry Pi ei käivitu
**Sümptomid:** Puudub ekraanipilt, ei vilgu LED, või kuvatakse vikerkaare kuva

**Lahendus:**
1. **Kontrollige toiteallikat:** Kasutage ametlikku 5V 3A USB-C toiteallikat Pi 4 jaoks
2. **SD-kaardi probleemid:** 
   - Vormindage SD-kaart ja paigaldage Raspberry Pi OS uuesti
   - Proovige teist SD-kaarti (kasutage soovitatud tootjaid)
   - Veenduge, et SD-kaart on korralikult sisestatud
3. **Kontrollige HDMI ühendust:** Proovige mõlemat HDMI porti Pi 4-l, kasutage porti, mis on toite lähedal

#### Probleem: Ei saa SSH-ga Raspberry Pi-le ühendada
**Sümptomid:** Ühendus keelatud või aegumine

**Lahendus:**
1. Lülitage SSH sisse:
   - Raspberry Pi Imager'i abil koguge SSH seadeid täpsemates valikutes
   - Või looge boot partitsioonis tühi fail nimega `ssh` (ilma laiendita)
2. Leidke Pi IP aadress:
   - Kontrollige ruuteri ühendatud seadmeid
   - Kasutage `ping raspberrypi.local` (kui mDNS töötab)
   - Kasutage võrguskannimise tööriistu nagu `nmap` või Angry IP Scanner
3. Kontrollige võrku:
   - Veenduge, et Pi on samas võrgus arvutiga
   - Proovige Ethernet ühendust WiFi asemel
4. Kontrollige kasutajanime/parooli (vaikimisi: kasutaja `pi`, parool `raspberry`)

#### Probleem: Grove Base Hat ei tunnustata
**Sümptomid:** Andurid ei tööta, I2C vead

**Lahendus:**
1. Veenduge, et Base Hat on korrektselt ühendatud kõigile GPIO jalgadele
2. Kontrollige, kas Pi või Base Hatil on painutatud jalgasid
3. Lülitage I2C liides sisse:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Kontrollige I2C tööd: `i2cdetect -y 1`

#### Probleem: Raspberry Pi töötab aeglaselt
**Sümptomid:** Libisev kasutajaliides, aeglane reageerimine

**Lahendus:**
1. Kontrollige SD-kaardi kiirust (kasutage Class 10 või kiiremat, või SSD USB kaudu)
2. Vabastage kettaruumi: `df -h`, kustutage mittevajalikud failid
3. Vähendage GPU mälu `raspi-config` abil, kui kaamera/ekraani palju ei kasutata
4. Sulgege mittevajalikud rakendused
5. Mõelge Pi 3 või vanema asemel Pi 4 peale, mis on rohkem RAM-iga

### Wio Terminal

#### Probleem: Wio Terminali ekraan jääb mustaks
**Sümptomid:** Ekraanil ei kuvata pärast koodi üleslaadimist midagi

**Lahendus:**
1. Kontrollige, kas kood initsialiseerib ekraani (TFT_eSPI teek)
2. Uuendage Wio Terminali püsivara aadressilt [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Lisage ekraani initsialiseerimise kood:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Proovige laadida näidisprogramm PlatformIO-st riistvara testimiseks

#### Probleem: Wio Terminali WiFi ei tööta
**Sümptomid:** Ei saa WiFi-ga ühendust, võrguvead

**Lahendus:**
1. **Uuendage WiFi püsivara:** Järgige [Wio Terminal WiFi püsivara uuendamise juhendit](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Kontrollige WiFi sisselogimist:** Veenduge, et SSID ja parool on õiged
3. **WiFi sagedus:** Wio Terminal toetab ainult 2.4GHz WiFi-d (mitte 5GHz)
4. **Signaali tugevus:** Liikuge ruuteri lähedale
5. **Ruuteri sätted:** Mõned ettevõtte/WPA-Enterprise võrgud ei pruugi töötada

#### Probleem: Wio Terminali arvutis ei tunta ära
**Sümptomid:** USB seadet ei tunnustata

**Lahendus:**
1. **Proovige teist USB kaablit:** Kasutage andmekaablit, mitte ainult laadimiskaablit
2. **Mine bootloader režiimi:** Lükake toitenupp kiiresti kaks korda alla
   - Sinine LED vilgub, seade ilmub seadmehalduris nimega "Arduino"
3. **Paigaldage draiverid (Windows):**
   - Laadige alla ja paigaldage [Seeed USB draiver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Proovige teist USB porti:** Vältige USB keskusi, kasutage otsest ühendust
5. **Uuendage süsteemi USB draivereid**

#### Probleem: Wio Terminali andurid ei tööta
**Sümptomid:** Grove andurid ei loe andmeid

**Lahendus:**
1. Kontrollige Grove kaablite ühendusi
2. Veenduge, et kasutate õiget Grove porti (vasak või parem)
3. Lisage õige teek andurile
4. Kontrollige anduri toitevajadusi
5. Testige andurit teegist pärit näidiskoodiga

### Virtuaalseade (CounterFit)

#### Probleem: CounterFit rakendus ei käivitu
**Viga:** Mitmesugused Python vead CounterFit käivitamisel

**Lahendus:**
1. Veenduge, et virtuaalkeskkond on aktiveeritud
2. Installige/paigaldage CounterFit uuesti:
   ```bash
   pip install CounterFit
   ```
3. Kontrollige, kas port 5000 on vaba:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Tapke porti 5000 kasutav protsess või kasutage teist porti:
   ```bash
   counterfit --port 5001
   ```

#### Probleem: Ei saa CounterFitiga koodist ühendust
**Viga:** Ühendus keelatud või aegumine

**Lahendus:**
1. Veenduge, et CounterFit töötab: Avage brauser aadressil `http://127.0.0.1:5000`
2. Kontrollige, et koodi ühendus URL vastab CounterFit aadressile
3. Veenduge, et tulemüür ühendust ei blokeeri
4. Proovige taaskäivitada nii CounterFit rakendus kui ka kood

#### Probleem: Andurid ei ilmu CounterFit UI-sse
**Sümptomid:** Loodud andurid ei kuvata kasutajaliideses

**Lahendus:**
1. Looge andurid CounterFit kasutajaliideses enne koodi käivitamist
2. Värskendage brauseri lehte
3. Kontrollige, et anduri tüüp vastab koodis eeldatule
4. Tühjendage brauseri vahemälu

---

## Ühenduvusprobleemid

### WiFi ühendus

#### Probleem: Seade ei saa WiFi-ga ühendust
**Sümptomid:** Ühenduse aegumine, autentimine ebaõnnestus

**Lahendus:**
1. **Kontrollige SSID ja parooli:** Veenduge, et andmed on õiged
2. **WiFi sagedus:** Enamik IoT seadmeid toetab ainult 2.4GHz (mitte 5GHz)
3. **Ruuteri sätted:**
   - Lülitage AP isolatsioon välja, kui see on lubatud
   - Kasutage WPA2-PSK turvalisust (vältige WPA3, WEP või avatud võrke)
   - Veenduge, et DHCP on sisse lülitatud
4. **Peidetud võrgud:** Kui SSID on peidetud, pean selle seadistama käsitsi
5. **Signaali tugevus:** Liigutage seade lähemale ruuterile
6. **Segajad:** Teised seadmed, mikrolaineahi või seinad võivad häirida

#### Probleem: WiFi ühendus katkeb sageli
**Sümptomid:** Katkendlik ühendus

**Lahendus:**
1. Kontrollige ruuteri stabiilsust, mõelge taaskäivitamisele
2. Uuendage seadme püsivara
3. Kasutage staatilist IP-d DHCP asemel
4. Vähendage kaugust ruuterist või lisage WiFi kordusvahend
5. Kontrollige teiste seadmete segamist
6. Veenduge, et toiteallikas on piisav (eriti Raspberry Pi puhul)

### Pilveteenused

#### Probleem: Ei saa ühendust Azure IoT Hub-iga
**Viga:** Autentimine ebaõnnestus, ühendus keelatud

**Lahendus:**
1. **Kontrollige mandaate:**
   - Kontrollige ühendusstringi õigsust
   - Veenduge, et seotud stringis ei ole lisatühikuid ega reavahetusi
2. **Kontrollige seadme registreerimist:** Seade peab olema registreeritud IoT Hubis
3. **Tulemüür/proxy:** Lubage väljaminev MQTT (port 8883) või HTTPS (port 443)
4. **IoT Hub'i piirkond:** Veenduge, et IoT Hub töötab ja ei asu teises piirkonnas, mis põhjustab viivitust
5. **Kvoodi piirangud:** Kontrollige, kas tasuta teenusepiirangud on ületatud
6. **Testige ühendust:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Probleem: Azure Functions ei käivitu
**Sümptomid:** Sõnumeid saadetakse, kuid funktsioon ei käivitu

**Lahendus:**
1. Kontrollige, et Function App töötab (ei ole peatatud)
2. Kinnitage ühendusstring Function App seadetes
3. Kontrollige funktsiooni logisid Azure Portaalis
4. Veenduge, et Event Hub ühilduv lõpp-punkt on korrektselt seadistatud
5. Kontrollige, et sõnumi formaat vastab funktsiooni ootustele
6. Kontrollige Function App teenuseplaani (tarbimine vs. pühendatud)

### MQTT
#### Probleem: MQTT ühendus ebaõnnestub  
**Viga:** Ühendus keelatud, autentimine ebaõnnestus  

**Lahendus:**  
1. **Vahendaja aadress:** Kontrolli, kas vahendaja URL/IP on õige  
2. **Port:** Kontrolli pordinumbrit (1883 krüpteerimata jaoks, 8883 TLS-i jaoks)  
3. **Autentimine:** Kontrolli kasutajanime/parooli, kui nõutud  
4. **TLS/SSL:** Veendu, et sertifikaadid on kehtivad ja usaldusväärsed  
5. **Tulemüür:** Kontrolli, et port pole blokeeritud  
6. **Testi MQTT kliendiga:** Kasuta MQTT Explorer’i või mosquitto_pub/sub testimiseks  

#### Probleem: MQTT sõnumeid ei saa  
**Sümptomid:** Sõnumid on avaldatud, kuid tellijad neid ei saa  

**Lahendus:**  
1. **Teemade nimed:** Kontrolli, et tellija teema vastab täpselt avaldaja teemale  
2. **QoS tase:** Proovi QoS 1 või 2 asemel 0  
3. **Wildcards:** Kontrolli, et teema wildcardid on korralikult kasutatud (`+` ühe taseme jaoks, `#` mitme taseme jaoks)  
4. **Hoitud sõnumid:** Avaldaja saab seada retain-lipu, et hoida viimast sõnumit  
5. **Ühenduse ajastus:** Veendu, et tellija ühendub enne sõnumite avaldamist  

---

## Andurite ja täiturmehhanismide probleemid

### Grove andurid

#### Probleem: Andur tagastab vale väärtusi  
**Sümptomid:** Loeväärtused on 0, -1 või mõistmatud väärtused  

**Lahendus:**  
1. **Kontrolli ühendusi:** Veendu, et andur on korralikult ühendatud  
2. **Õige port:** Kontrolli, et andur on õiges porditüübis:  
   - Analoogsensorid → Analoogpordid (A0, A2, A4)  
   - Digitaalsensorid → Digitaalsed pordid (D5, D16, D18 jne)  
   - I2C andurid → I2C pordid  
3. **Kalibreerimine:** Mõned andurid vajavad kalibreerimist (mulla niiskus, valgus)  
4. **Toite väljalülitus:** Ühenda andur lahti ja uuesti  
5. **Anduri andmeleht:** Kontrolli anduri spetsifikatsioone ja nõudeid  

#### Probleem: Kapatsiivne mullaniiskuse andur näitab alati märga  
**Sümptomid:** Andur näitab kõrget niiskust isegi kuival ajal  

**Lahendus:**  
1. **Kalibreerimine vajalik:** Mullaniiskuse andurid vajavad kalibreerimist:  
   - Loe väärtus õhus (kuiv baasväärtus)  
   - Loe väärtus vees (märk baasväärtus)  
   - Kaardista loetud väärtused nende vahele  
2. **Kontrolli anduri katet:** Niiskuseandurid võivad degradeeruda, kui kate on kahjustatud  
3. **Paigutus:** Veendu, et andur on mullas täielikult sees  

#### Probleem: Temperatuuri/niiskuse anduri lugemised on valed  
**Sümptomid:** DHT11/DHT22 näitavad vale temperatuuri või niiskust  

**Lahendus:**  
1. **Anduri asukoht:** Väldi otsest päikesevalgust, soojusallikaid või õhuvoolu  
2. **Soojendus aeg:** Lase anduril pärast sisselülitamist 2 sekundit soojeneda enne lugemist  
3. **Lugemissagedus:** DHT andurid vajavad lugemise vahel aega (vähemalt 2 sekundit)  
4. **Kontrolli kondensatsiooni:** See võib lugemisi mõjutada  
5. **Anduri kvaliteet:** DHT11 on vähem täpne kui DHT22  

### Kaamera

#### Probleem: Kaamerat Raspberry Pi-s ei tuvastata  
**Viga:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`  

**Lahendus:**  
1. **Luba kaamera liides:**  
   ```bash
   sudo raspi-config
   ```
   Mine Interface Options → Camera → Enable  
2. **Kontrolli lintkaablit:** Veendu, et kaamerakaabel on õigesti ühendatud  
   - Sinine pool Pi Zero USB portide poole  
   - Sinine pool eemale USB portidest Pi 4 puhul  
3. **Uuenda püsivara:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Testi kaamerat:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Probleem: Kaamera pildid on kehva kvaliteediga  
**Sümptomid:** Udused, tumedad või pleekinud pildid  

**Lahendus:**  
1. **Fookus:** Eemalda objektiivilt kaitsekile, reguleeri fookust, kui võimalik  
2. **Valgustus:** Veendu, et on piisav valgustus  
3. **Kaamera seaded:** Kohanda säritust, ISO-d, valge tasakaalu koodi sees  
4. **Stabiilsus:** Hoia kaamerat paigal, vajadusel kasuta statiivi  
5. **Resolutsioon:** Ära ületa kaamera maksimaalset resolutsiooni  

### Mikrofon ja kõlar

#### Probleem: Helisisend/väljund puudub  
**Sümptomid:** Mikrofon ei salvesta, kõlar ei mängi heli  

**Lahendus:**  
1. **Kontrolli ühendusi:** Veendu, et heliseadmed on õigesti ühendatud  
2. **Testi riistvara:**  
   - Kõlar: `speaker-test -t wav -c 2`  
   - Mikrofon: `arecord -l` seadmeloend, `arecord test.wav` salvestamiseks  
3. **Helitugevuse sätted:** Kontrolli ja reguleeri helitugevust:  
   ```bash
   alsamixer
   ```
4. **Vali heliseade:** Määra koodis õige heliseade  
5. **Draiveri probleemid:** Uuenda ALSA-d või paigalda helidraiverid uuesti  

#### Probleem: ReSpeaker hat ei tööta  
**Sümptomid:** Heliseadet ei tuvastata  

**Lahendus:**  
1. **Paigalda draiverid:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Kontrolli paigaldust:** `arecord -l` peaks loetlema ReSpeakeri  
3. **Uuenda püsivara:** Mõned Pi OS versioonid vajavad draiveriuuendust  
4. **Kontrolli ühendust:** Veendu, et hat on korralikult GPIO külge ühendatud  

---

## Arenduskeskkonna probleemid

### VS Code

#### Probleem: Terminali virtuaalkeskkond ei aktiveeru automaatselt  
**Sümptomid:** Terminal avaneb, kuid venv ei aktiveeru  

**Lahendus:**  
1. **Määra Python interpreteerija:** Command Palette → "Python: Select Interpreter" → vali venv  
2. **Taaskäivita VS Code** pärast interpreteerija valimist  
3. **Kontrolli seadistusi:** Lisa `settings.json` faili:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Probleem: Kood ei käivitu seadmes  
**Sümptomid:** Kood jookseb, kuid seadmes ei juhtu midagi  

**Lahendus:**  
1. **Veendu, et kood on salvestatud** (kontrolli faili vahelehte punkti)  
2. **Kontrolli, milline Python jookseb:** `which python` või `where python`  
3. **Wio Terminali puhul:** Veendu, et kood on PlatformIO kaudu üles laaditud (klõpsa upload nuppu)  
4. **Raspberry Pi puhul:** Logi SSH-ga sisse Pi’sse ja käivita kood sealt  
5. **Vaata väljundakent** vigade jaoks  

#### Probleem: IntelliSense ei kuva teekide funktsioone  
**Sümptomid:** Automaattäide puudub imporditud moodulitele  

**Lahendus:**  
1. Veendu, et teek on installitud praeguses keskkonnas  
2. Laadi VS Code aken uuesti  
3. Kontrolli, et Python interpreteerija on õige  
4. Paigalda olemasolevad tüübistubid: `pip install types-<library-name>`  

### Python virtuaalkeskkonnad

#### Probleem: Virtuaalkeskkonda ei saa luua  
**Viga:** `The virtual environment was not created successfully`  

**Lahendus:**  
1. **Paigalda venv moodul:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: peaks olema Pythoniga kaasas  
   - Windows: paigalda Python uuesti kõigi komponentidega  
2. **Kontrolli Python’i paigaldust:** Veendu, et Python on korrektselt paigaldatud  
3. **Kasuta täielikku teed:** Proovi `python3 -m venv .venv` koos selge python3 käsuga  

#### Probleem: Paketid paigaldatakse valesse asukohta  
**Sümptomid:** Impordivead peale paketi paigaldust  

**Lahendus:**  
1. **Veendu, et venv on aktiveeritud:** Käsureal peaks olema `(.venv)`  
2. **Kontrolli pip asukohta:** `which pip` peaks osutama `.venv/bin/pip`-le  
3. **Paigalda uuesti venv-is:** Aktiviseeri venv ja paigalda `pip install <pakett>`  
4. **Ära kasuta sudo’t pip’iga** virtuaalkeskkonnas  

#### Probleem: Virtuaalkeskkond pole teisaldatav  
**Sümptomid:** Venv ei tööta pärast teisaldamist või teises arvutis  

**Lahendus:**  
1. **Ära liigu venge:** Kustuta ja loo uus asukohas  
2. **Kasuta requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Loo venv uuesti:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # või activate.bat Windowsis
   pip install -r requirements.txt
   ```
  
### Sõltuvused

#### Probleem: Paketi paigaldus ebaõnnestub  
**Viga:** Erinevad pip vead paigaldamisel  

**Lahendus:**  
1. **Uuenda pip:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Paigalda ehitustööriistad:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: paigalda Visual Studio Build Tools  
3. **Kontrolli internetiühendust**  
4. **Proovi teist paketi indeksit:** `pip install --index-url https://pypi.org/simple/ <pakett>`  
5. **Paigalda konkreetne versioon:** `pip install <pakett>==<versioon>`  

#### Probleem: Sõltuvuste konfliktid  
**Viga:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`  

**Lahendus:**  
1. **Kasuta iga projekti jaoks uut virtuaalkeskkonda**  
2. **Uuenda pakette:** `pip install --upgrade <pakett>`  
3. **Kontrolli nõudeid:** Kasuta `pip check` konfliktide leidmiseks  
4. **Paigalda sobivad versioonid:** Määra versioonivahemikud requirements.txt failis  

---

## Jõudlusprobleemid

### Probleem: Kood jookseb aeglaselt  
**Sümptomid:** Viivitused, ajalõpped, reageerimatus  

**Lahendus:**  
1. **Vähenda andurite lugemissagedust:** Ära loe andureid liiga sageli  
2. **Optimeeri tsükleid:** Väldi hõivatud ootust, kasuta sleep() või viivitusi  
3. **Mälu probleemid:**  
   - Sulge mittevajalikud rakendused  
   - Vabasta salvestusruumi  
   - Jälgi `top` või `htop` programmi abil Pi peal  
4. **SD kaardi kiirus:** Kasuta kiiremat SD kaarti või SSD-d Raspberry Pi jaoks  
5. **Võrgu viivitused:** Kasuta asünkroonseid toiminguid võrgukõnede jaoks  

### Probleem: Mälu puuduse vead  
**Viga:** `MemoryError` või süsteemi külmutamine  

**Lahendus:**  
1. **Raspberry Pi puhul:**  
   - Sulge mittevajalikud rakendused  
   - Suurenda swap ruumi  
   - Kasuta kergemat operatsioonisüsteemi (Lite versioon)  
   - Uuenda RAM-i (Pi 4-l on 2/4/8GB valikud)  
2. **Wio Terminali puhul:**  
   - Vähenda puhvrite suuruseid  
   - Kasuta väiksemaid pilte  
   - Optimeeri stringide kasutust  
   - Kontrolli mälulekkeid (vabastamata mälu)  

### Probleem: Andmete kadumine või kahjustumine  
**Sümptomid:** Puuduvad sõnumid, vigased failid  

**Lahendus:**  
1. **SD kaardi probleemid:**  
   - Kasuta kvaliteetseid SD kaarte (väldi odavaid või võltsitud)  
   - Tee regulaarselt varukoopiaid  
   - Tee korralik väljalülitus (ära tõmba toidet ootamatult)  
2. **Puhvripiirang:** Suurenda puhvrite suurust koodi sees  
3. **Võrgu töökindlus:** Rakenda korduslogika ja veahaldus  
4. **Teenuse Kvaliteet:** Kasuta MQTT QoS 1 või 2 oluliste sõnumite jaoks  

---

## Levinud veateated

### `ModuleNotFoundError: No module named 'X'`  
**Põhjus:** Paketti pole installitud või virtuaalkeskkond pole aktiveeritud  

**Lahendus:**  
```bash
pip install X
```
Veendu esmalt, et virtuaalkeskkond on aktiveeritud.  

### `Permission denied` Linux/macOS  
**Põhjus:** Vajalikud kõrgendatud õigused või failiõiguste probleem  

**Lahendus:**  
- Süsteemi toimingute puhul kasuta `sudo`  
- Pip’i puhul ÄRA KASUTA sudo’t koos venv’iga, aktiveeri venv esmalt  
- Sariipordi puhul lisa kasutaja dialout gruppi: `sudo usermod -a -G dialout $USER`, seejärel logi välja ja uuesti sisse  

### `OSError: [Errno 98] Address already in use`  
**Põhjus:** Port on juba teise protsessi poolt kasutusel  

**Lahendus:**  
1. Leia porti kasutav protsess: `lsof -i :<port>` või `netstat -ano | findstr :<port>`  
2. Lõpeta protsess või kasuta teist porti oma koodis  

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Põhjus:** SSL sertifikaadi valideerimine ebaõnnestus  

**Lahendus:**  
1. Uuenda sertifikaate: `pip install --upgrade certifi`  
2. Kontrolli süsteemi aega: `date`  
3. Ainult arendamiseks (mitte tootmiseks): loo koodis valideerimise keelamine  

### `IndentationError: unexpected indent`  
**Põhjus:** Python indentatsiooni probleemid (tabide ja tühikute segamine)  

**Lahendus:**  
1. Kasuta ühtlast indentatsiooni (4 tühikut on Python standard)  
2. Sea redaktoris tühikute kasutamine tabide asemel  
3. VS Code’is määra `"editor.insertSpaces": true` ja `"editor.tabSize": 4`  

### `UnicodeDecodeError` või `UnicodeEncodeError`  
**Põhjus:** Märgistiku kodeerimise probleemid  

**Lahendus:**  
```python
# Failide lugemisel
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Failide kirjutamisel
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Abi saamine

Kui oled proovinud neid tõrkeotsingu samme ja probleemid püsivad:

### 1. Kontrolli olemasolevaid ressursse  
- **Dokumentatsioon:** Tutvu [README](README.md) ja õppetükkide juhistega  
- **Riistvarajuhendid:** Vaata [hardware.md](hardware.md) riistvaraspetsiifilist infot  
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) Grove komponentide kohta  

### 2. Otsi sarnaseid probleeme  
- **GitHub’i probleemid:** Otsi [olemasolevaid probleeme](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Otsi veateatega seotud vastuseid  
- **Seadme foorumid:** Vaata Raspberry Pi või Arduino foorumeid  

### 3. Loo GitHub’is probleem (**Issue**)  
Kui lahendust ei leia:  
1. Mine [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Klõpsa "New Issue"  
3. Kirjelda:  
   - Selgelt probleemi sisu  
   - Sammud, kuidas probleemi tekitada  
   - Veateated (kogu tekst)  
   - Riistvara/tarkvara versioonid  
   - Mida oled juba proovinud  
   - Ekraanipildid, kui asjakohane  

### 4. Liitu kogukonnaga  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)  

### 5. Esita head veaaruannet  
Heas veaaruandes on:
- **Keskkond:** OS, Python versioon, kasutatud riistvara
- **Probleemi taasesituse sammud:** Täpsed sammud, mis põhjustavad vea
- **Oodatav käitumine:** Mida peaks juhtuma
- **Tegelik käitumine:** Mis tegelikult juhtub
- **Veateated:** Täielik veatekst, mitte ekraanipildid
- **Kood:** Minimaalne koodinäide, mis probleemi esile kutsub

---

## Ennetamiseks nõuanded

### Üldised parimad praktikad
1. **Hoia varukoopiaid:** Regulaarne töötavate SD kaartide/koodi backup
2. **Dokumenteeri muudatused:** Märgi kommentaarides, mis töötab
3. **Versioonihaldus:** Kasuta git'i koodi muudatuste jälgimiseks
4. **Testi järkjärgult:** Testi väikeseid muudatusi enne nende kombineerimist
5. **Loe veateateid:** Need ütlevad sageli täpselt, mis on valesti
6. **Uuenda regulaarselt:** Hoia tarkvara/firmware ajakohasena
7. **Kasuta kvaliteetseid komponente:** Väldi odavaid kaableid/toiteallikaid
8. **Stabiilne toide:** Kasuta sobivat toiteallikat (eriti Pi puhul)

### Arendusvoog
1. **Alusta lihtsalt:** Alusta näidiskoodiga, mis töötab
2. **Üks muudatus korraga:** Kergem leida, mis rikub
3. **Testi tihti:** Katsu vead varakult kinni püüda
4. **Hoidke korras:** Korralda failid ja kood loogiliselt
5. **Kommenteeri koodi:** Tuleviku sina hindab seda

---

*See tõrkeotsingu juhend on kogukonna hooldatud. Kui leiad lahenduse probleemile, mis siin loetletud pole, kaalu palun [panustamist](CONTRIBUTING.md), et aidata teisi!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Vastutusest loobumine**:
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palun arvestage, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Originaaldokument tema emakeeles tuleks pidada autoriteetseks allikaks. Kriitilise teabe puhul soovitatakse kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->