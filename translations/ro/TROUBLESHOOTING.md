<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T16:03:59+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "ro"
}
-->
# Ghid de depanare

Acest ghid te ajută să rezolvi probleme comune când lucrezi cu curriculumul IoT for Beginners. Problemele sunt organizate pe categorii pentru o navigare ușoară.

## Cuprins

- [Probleme de instalare](../..)
  - [Instalarea Python](../..)
  - [VS Code și extensii](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Biblioteci Grove](../..)
- [Probleme hardware](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Dispozitiv virtual (CounterFit)](../..)
- [Probleme de conectivitate](../..)
  - [Conexiune WiFi](../..)
  - [Servicii cloud](../..)
  - [MQTT](../..)
- [Probleme cu senzori și actuatori](../..)
  - [Senzori Grove](../..)
  - [Camera](../..)
  - [Microfon și difuzor](../..)
- [Probleme de mediu de dezvoltare](../..)
  - [VS Code](../..)
  - [Mediile virtuale Python](../..)
  - [Dependențe](../..)
- [Probleme de performanță](../..)
- [Mesaje de eroare comune](../..)
- [Obținerea ajutorului](../..)

---

## Probleme de instalare

### Instalarea Python

#### Problemă: Versiunea Python este prea veche
**Eroare:** `Python 3.6 sau o versiune mai nouă este necesară`

**Soluție:**
1. Descarcă cea mai nouă versiune Python 3 de pe [python.org](https://www.python.org/downloads/)
2. La instalare pe Windows, bifează opțiunea "Add Python to PATH"
3. Verifică instalarea:
   ```bash
   python3 --version
   ```

#### Problemă: Mai multe versiuni Python cauzează conflicte
**Simptome:** Rulează o versiune greșită de Python, pachetele se instalează în locația greșită

**Soluție:**
- **Windows:** Folosește `py -3` în loc de `python` pentru a apela explicit Python 3
- **macOS/Linux:** Folosește `python3` în loc de `python`
- Creează și folosește întotdeauna medii virtuale pentru proiecte

#### Problemă: Comanda pip nu este recunoscută
**Eroare:** `'pip' nu este recunoscut ca o comandă internă sau externă`

**Soluție:**
1. Încearcă `pip3` în loc de `pip`
2. Sau folosește `python -m pip` sau `python3 -m pip`
3. Asigură-te că Python este adăugat în PATH (reinstalează Python și bifează opțiunea)

### VS Code și extensii

#### Problemă: Extensia Pylance nu funcționează
**Simptome:** Lipsă IntelliSense pentru Python, completare de cod sau verificare de tipuri

**Soluție:**
1. Deschide Paleta de comenzi VS Code (`Ctrl+Shift+P` sau `Cmd+Shift+P`)
2. Rulează "Python: Select Interpreter"
3. Alege interpretul Python corect (mediu virtual dacă folosești unul)
4. Reîncarcă fereastra VS Code

#### Problemă: VS Code nu detectează mediul virtual
**Simptome:** Interpretul Python greșit selectat

**Soluție:**
1. Asigură-te că ai activat mediul virtual în terminal
2. Deschide Paleta de comenzi și rulează "Python: Select Interpreter"
3. Selectează interpretul din folderul `.venv`
4. Verifică dacă bara de stare (colț stânga jos) afișează versiunea corectă de Python

### PlatformIO (Wio Terminal)

#### Problemă: Instalarea PlatformIO eșuează
**Eroare:** Diverse erori în timpul instalării PlatformIO

**Soluție:**
1. Asigură-te că VS Code este actualizat
2. Instalează mai întâi extensia C/C++
3. Repornește VS Code după instalarea PlatformIO
4. Verifică conexiunea la internet (PlatformIO descarcă fișiere mari)

#### Problemă: Placa nu este detectată de PlatformIO
**Simptome:** Nu poți încărca cod pe Wio Terminal

**Soluție:**
1. Încearcă un alt cablu USB (unele cabluri sunt doar pentru încărcare)
2. Verifică Device Manager (Windows) sau `ls /dev/tty*` (macOS/Linux)
3. Instalează sau actualizează driverele USB
4. Încearcă un alt port USB
5. Glisează comutatorul de alimentare de pe Wio Terminal de două ori rapid pentru a intra în modul bootloader

#### Problemă: Erori de compilare în PlatformIO
**Eroare:** `fatal error: Arduino.h: No such file or directory`

**Soluție:**
1. Șterge folderul `.pio` din proiectul tău
2. Rulează "PlatformIO: Rebuild" din Paleta de comenzi
3. Asigură-te că fișierul `platformio.ini` are configurația corectă pentru placa ta:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Biblioteci Grove

#### Problemă: Importul bibliotecii Grove eșuează pe Raspberry Pi
**Eroare:** `ModuleNotFoundError: No module named 'grove'`

**Soluție:**
1. Reinstalează bibliotecile Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Dacă folosești mediu virtual, poate fi necesar să instalezi global sau să copiezi bibliotecile
3. Verifică dacă I2C este activat: `sudo raspi-config nonint do_i2c 0`

#### Problemă: Senzor Grove nu este detectat
**Eroare:** `IOError: [Errno 121] Remote I/O error`

**Soluție:**
1. Verifică conexiunile fizice (asigură-te că cablul Grove este introdus complet)
2. Verifică dacă senzorul este conectat la portul corect (analog, digital, I2C, UART)
3. Rulează `i2cdetect -y 1` pentru a vedea dacă dispozitivul apare pe magistrala I2C
4. Încearcă un alt cablu Grove
5. Asigură-te că Grove Base Hat este bine fixat pe pini GPIO de pe Raspberry Pi

---

## Probleme hardware

### Raspberry Pi

#### Problemă: Raspberry Pi nu pornește
**Simptome:** Nu apare imagine, LED-urile nu se aprind sau apare ecran curcubeu

**Soluție:**
1. **Verifică alimentarea:** Folosește adaptorul oficial de 5V 3A USB-C pentru Pi 4
2. **Probleme cu cardul SD:** 
   - Reformatează cardul SD și reinstalează Raspberry Pi OS
   - Încearcă un alt card SD (folosește mărci recomandate)
   - Asigură-te că cardul SD este introdus corespunzător
3. **Verifică conexiunea HDMI:** Încearcă ambele porturi HDMI de pe Pi 4, folosește portul HDMI cel mai aproape de alimentare

#### Problemă: Nu poți face SSH către Raspberry Pi
**Simptome:** Conexiunea este refuzată sau expiră timpul de așteptare

**Soluție:**
1. Activează SSH:
   - La scrierea cardului SD cu Raspberry Pi Imager, configurează SSH în opțiunile avansate
   - Sau creează un fișier gol numit `ssh` (fără extensie) în partiția de boot
2. Găsește adresa IP a Pi-ului:
   - Verifică dispozitivele conectate pe router
   - Folosește `ping raspberrypi.local` (dacă funcționează mDNS)
   - Folosește un scaner de rețea ca `nmap` sau Angry IP Scanner
3. Verifică rețeaua:
   - Asigură-te că Pi este în aceeași rețea cu calculatorul tău
   - Încearcă conexiune prin ethernet în loc de WiFi
4. Verifică numele de utilizator/parola (implicit: utilizator `pi`, parolă `raspberry`)

#### Problemă: Grove Base Hat nu este recunoscut
**Simptome:** Senzorii nu funcționează, apar erori I2C

**Soluție:**
1. Asigură-te că Base Hat este bine fixat pe toți pinii GPIO
2. Verifică dacă există pini îndoiți pe Pi sau pe Base Hat
3. Activează interfața I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Verifică funcționarea I2C: `i2cdetect -y 1`

#### Problemă: Raspberry Pi rulează încet
**Simptome:** Interfață lentă, răspuns întârziat

**Soluție:**
1. Verifică viteza cardului SD (folosește Clasa 10 sau mai bun, sau SSD via USB)
2. Eliberează spațiu pe disc: `df -h` pentru verificare, șterge fișiere inutile
3. Redu memoria GPU în `raspi-config` dacă nu folosești intens camera sau ecranul
4. Închide aplicațiile nefolositoare
5. Ia în considerare upgrade la Pi 4 cu mai mult RAM dacă folosești Pi 3 sau mai vechi

### Wio Terminal

#### Problemă: Ecranul Wio Terminal rămâne negru
**Simptome:** Nu apare niciun afișaj după încărcarea codului

**Soluție:**
1. Verifică dacă codul inițializează afișajul (biblioteca TFT_eSPI)
2. Actualizează firmware-ul Wio Terminal de pe [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Adaugă cod pentru inițializarea afișajului:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Încearcă să încarci un sketch exemplu din PlatformIO pentru a testa hardware-ul

#### Problemă: WiFi nu funcționează pe Wio Terminal
**Simptome:** Nu se conectează la WiFi, apar erori de rețea

**Soluție:**
1. **Actualizează firmware-ul WiFi:** Urmează [ghidul de actualizare firmware WiFi pentru Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Verifică datele WiFi:** Confirmă că SSID și parola sunt corecte
3. **Bandă WiFi:** Wio Terminal suportă doar 2.4GHz (nu 5GHz)
4. **Putere semnal:** Mutați-l mai aproape de router
5. **Setările routerului:** Unele rețele enterprise/WPA-Enterprise pot să nu funcționeze

#### Problemă: Wio Terminal nu este recunoscut de calculator
**Simptome:** Dispozitivul USB nu este detectat

**Soluție:**
1. **Încearcă alt cablu USB:** Folosește cablu de date, nu doar cablu de încărcare
2. **Intră în modul bootloader:** Glisează comutatorul de alimentare în jos de două ori rapid
   - LED-ul albastru ar trebui să pulseze, dispozitivul apare ca "Arduino" în Device Manager
3. **Instalează driverele (Windows):**
   - Descarcă și instalează [driverul USB Seeed](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Încearcă alt port USB:** Evită hub-uri USB, conectează direct
5. Actualizează driverele USB ale sistemului

#### Problemă: Senzorii nu funcționează pe Wio Terminal
**Simptome:** Senzorii Grove nu citesc date

**Soluție:**
1. Verifică conexiunile cablului Grove
2. Confirmă că folosești portul Grove corect (stânga sau dreapta)
3. Include bibliotecile corecte pentru senzor
4. Verifică cerințele de alimentare ale senzorului
5. Testează senzorul cu cod exemplu din bibliotecă

### Dispozitiv virtual (CounterFit)

#### Problemă: Aplicația CounterFit nu pornește
**Eroare:** Diverse erori Python la pornirea CounterFit

**Soluție:**
1. Asigură-te că mediul virtual este activat
2. Instalează/reinstalează CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Verifică dacă portul 5000 nu este deja folosit:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Oprește procesul ce folosește portul 5000 sau folosește un port diferit:
   ```bash
   counterfit --port 5001
   ```

#### Problemă: Nu te poți conecta la CounterFit din cod
**Eroare:** Conexiune refuzată sau timeout

**Soluție:**
1. Verifică dacă CounterFit rulează: deschide browserul la `http://127.0.0.1:5000`
2. Confirmă că URL-ul de conexiune din cod corespunde adresei CounterFit
3. Asigură-te că firewall-ul nu blochează conexiunea
4. Încearcă să repornești atât aplicația CounterFit cât și codul tău

#### Problemă: Senzorii nu apar în CounterFit
**Simptome:** Senzorii creați nu apar în interfața CounterFit

**Soluție:**
1. Creează senzorii în interfața CounterFit înainte de a rula codul
2. Reîncarcă pagina în browser
3. Verifică dacă tipul senzorului corespunde cu ce așteaptă codul
4. Șterge memoria cache a browserului

---

## Probleme de conectivitate

### Conexiune WiFi

#### Problemă: Dispozitivul nu se conectează la WiFi
**Simptome:** Timeout conexiune, autentificare eșuată

**Soluție:**
1. **Verifică SSID și parola:** Confirmă că sunt corecte
2. **Bandă WiFi:** Majoritatea dispozitivelor IoT suportă doar 2.4GHz (nu 5GHz)
3. **Setările routerului:**
   - Dezactivează izolarea AP dacă este activată
   - Folosește securitate WPA2-PSK (evită WPA3, WEP sau rețele deschise)
   - Asigură-te că DHCP este activat
4. **Rețele ascunse:** Dacă SSID este ascuns, trebuie configurat explicit
5. **Puterea semnalului:** Mută dispozitivul mai aproape de router
6. **Interferențe:** Alte dispozitive, cuptoare cu microunde sau pereți pot cauza interferențe

#### Problemă: Conexiunea WiFi cade frecvent
**Simptome:** Conectivitate intermitentă

**Soluție:**
1. Verifică stabilitatea routerului și ia în considerare un restart
2. Actualizează firmware-ul dispozitivului
3. Folosește o adresă IP statică în loc de DHCP
4. Redu distanța față de router sau adaugă un extender WiFi
5. Verifică interferențele de la alte dispozitive
6. Asigură alimentarea adecvată (în special pentru Raspberry Pi)

### Servicii cloud

#### Problemă: Nu poți să te conectezi la Azure IoT Hub
**Eroare:** Autentificare eșuată, conexiune refuzată

**Soluție:**
1. **Verifică acreditările:**
   - Verifică dacă stringul de conexiune este corect
   - Asigură-te că nu există spații sau întreruperi de linie în stringul de conexiune
2. **Verifică înregistrarea dispozitivului:** Dispozitivul trebuie să fie înregistrat în IoT Hub
3. **Firewall/proxy:** Permite traficul outbound MQTT (port 8883) sau HTTPS (port 443)
4. **Regiunea IoT Hub:** Asigură-te că IoT Hub rulează și nu este într-o regiune diferită ce cauzează latență
5. **Limitele de cotă:** Verifică dacă limita nivelului gratuit este depășită
6. **Testează conexiunea:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problemă: Azure Functions nu se declanșează
**Simptome:** Mesajele sunt trimise, dar funcția nu execută

**Soluție:**
1. Verifică că Function App este pornit (nu oprit)
2. Verifică stringul de conexiune în setările Function App
3. Consultă jurnalele de funcții în portalul Azure
4. Asigură-te că endpoint-ul compatibil cu Event Hub este configurat corect
5. Verifică dacă formatul mesajelor corespunde așteptărilor funcției
6. Verifică planul de serviciu Function App (consum sau dedicat)

### MQTT
#### Problemă: Conexiunea MQTT eșuează  
**Eroare:** Conexiune refuzată, autentificare eșuată

**Soluție:**  
1. **Adresa broker-ului:** Verificați dacă URL-ul/IP-ul broker-ului este corect  
2. **Port:** Verificați numărul portului (1883 pentru necriptat, 8883 pentru TLS)  
3. **Autentificare:** Verificați username-ul/parola dacă este necesar  
4. **TLS/SSL:** Asigurați-vă că certificatele sunt valide și de încredere  
5. **Firewall:** Verificați dacă portul nu este blocat  
6. **Testați cu client MQTT:** Folosiți MQTT Explorer sau mosquitto_pub/sub pentru testare

#### Problemă: Mesajele MQTT nu sunt primite  
**Simptome:** Mesajele sunt publicate, dar nu sunt primite de abonați

**Soluție:**  
1. **Numele topicurilor:** Verificați dacă topicul abonatului corespunde exact cu topicul editorului  
2. **Nivel QoS:** Încercați QoS 1 sau 2 în loc de 0  
3. **Wildcard-uri:** Verificați utilizarea corectă a wildcard-urilor în topicuri (`+` pentru un singur nivel, `#` pentru mai multe niveluri)  
4. **Mesaje reținute:** Editorul poate seta flag de retain pentru a păstra ultimul mesaj  
5. **Timpul conexiunii:** Asigurați-vă că abonatul se conectează înainte de publicarea mesajelor

---

## Probleme cu Senzori și Actuatori

### Senzori Grove

#### Problemă: Senzorul returnează valori incorecte  
**Simptome:** Citirile sunt 0, -1 sau valori fără sens

**Soluție:**  
1. **Verificați conexiunile:** Asigurați-vă că senzorul este conectat corect  
2. **Port corect:** Verificați dacă senzorul este în portul corect:  
   - Senzori analogici → porturi analogice (A0, A2, A4)  
   - Senzori digitali → porturi digitale (D5, D16, D18 etc.)  
   - Senzori I2C → porturi I2C  
3. **Calibrare:** Anumiți senzori necesită calibrare (umiditate sol, lumină)  
4. **Repornire:** Deconectați și reconectați senzorul  
5. **Fișa tehnică:** Verificați specificațiile și cerințele senzorului

#### Problemă: Senzor capacitiv de umiditate a solului indică mereu umed  
**Simptome:** Senzorul indică umiditate ridicată chiar și când solul este uscat

**Soluție:**  
1. **Calibrare necesară:** Senzorii de sol trebuie calibrați:  
   - Citiți valoarea în aer (bază uscată)  
   - Citiți valoarea în apă (bază umedă)  
   - Maparea citirilor între aceste valori  
2. **Verificați învelișul senzorului:** Senzorii de umiditate pot degrada dacă stratul protector este deteriorat  
3. **Poziționare:** Asigurați-vă că senzorul este introdus complet în sol

#### Problemă: Citiri incorecte pentru senzor de temperatură/umiditate  
**Simptome:** DHT11/DHT22 afișează temperatură sau umiditate greșită

**Soluție:**  
1. **Poziționarea senzorului:** Evitați lumina directă a soarelui, sursele de căldură sau curenții de aer  
2. **Timp de încălzire:** Lăsați senzorul 2 secunde după pornire înainte de citire  
3. **Frecvența citirii:** Senzorii DHT necesită cel puțin 2 secunde între citiri  
4. **Verificați condensul:** Poate afecta citirile  
5. **Calitatea senzorului:** DHT11 este mai puțin precis decât DHT22

### Cameră

#### Problemă: Camera nu este detectată pe Raspberry Pi  
**Eroare:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Soluție:**  
1. **Activați interfața camerei:**  
   ```bash
   sudo raspi-config
   ```
   Mergeți la Interface Options → Camera → Enable  
2. **Verificați cablul panglică:** Asigurați-vă că cablul camerei este introdus corect  
   - Partea albastră către porturile USB pe Pi Zero  
   - Partea albastră orientată în direcția opusă porturilor USB pe Pi 4  
3. **Actualizați firmware-ul:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Testați camera:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Problemă: Imaginile camerei sunt de calitate slabă  
**Simptome:** Imagini neclare, întunecate sau estompate

**Soluție:**  
1. **Focalizare:** Îndepărtați folia protector de pe lentilă, reglați focalizarea dacă este posibil  
2. **Iluminare:** Asigurați iluminare adecvată  
3. **Setări cameră:** Ajustați expunerea, ISO, balansul de alb în cod  
4. **Stabilitate:** Mențineți camera fixă, folosiți trepied dacă este necesar  
5. **Rezoluție:** Nu depășiți rezoluția maximă a camerei

### Microfon și Difuzor

#### Problemă: Fără intrare/ieșire audio  
**Simptome:** Microfonul nu înregistrează, difuzorul nu redă sunet

**Soluție:**  
1. **Verificați conexiunile:** Confirmați că dispozitivele audio sunt conectate corect  
2. **Testați hardware-ul:**  
   - Difuzor: `speaker-test -t wav -c 2`  
   - Microfon: `arecord -l` pentru listare, `arecord test.wav` pentru înregistrare  
3. **Setări volum:** Verificați și ajustați volumul:  
   ```bash
   alsamixer
   ```
4. **Selectați dispozitivul audio:** Specificați dispozitivul corect în cod  
5. **Probleme drivere:** Actualizați ALSA sau reinstalați driverele audio

#### Problemă: Placa ReSpeaker nu funcționează  
**Simptome:** Dispozitivul audio nu este detectat

**Soluție:**  
1. **Instalați drivere:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Verificați instalarea:** `arecord -l` ar trebui să listeze ReSpeaker  
3. **Actualizați firmware-ul:** Unele versiuni Pi OS necesită actualizări de drivere  
4. **Verificați montarea:** Asigurați-vă că placa este conectată corect la pinii GPIO

---

## Probleme cu Mediul de Dezvoltare

### VS Code

#### Problemă: Terminalul nu activează automat mediul virtual  
**Simptome:** Terminalul se deschide, dar venv nu este activat

**Soluție:**  
1. **Setați interpretorul Python:** Command Palette → "Python: Select Interpreter" → Alegeți venv-ul  
2. **Reporniți VS Code** după selectarea interpretorului  
3. **Verificați setările:** În `settings.json`, adăugați:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Problemă: Codul nu rulează pe dispozitiv  
**Simptome:** Codul rulează, dar pe dispozitiv nu se întâmplă nimic

**Soluție:**  
1. **Verificați dacă codul este salvat** (verificați punctul din tab-ul fișier)  
2. **Verificați Python-ul rulat:** `which python` sau `where python`  
3. **Pentru Wio Terminal:** Asigurați-vă că codul este încărcat via PlatformIO (click pe butonul upload)  
4. **Pentru Raspberry Pi:** Conectați-vă prin SSH pe Pi și rulați codul acolo  
5. **Verificați fereastra de output** pentru erori

#### Problemă: IntelliSense nu afișează funcțiile bibliotecii  
**Simptome:** Fără completare automată pentru modulele importate

**Soluție:**  
1. Asigurați-vă că biblioteca este instalată în mediul curent  
2. Reîncărcați fereastra VS Code  
3. Verificați dacă interpretorul Python este corect  
4. Instalați tipurile (type stubs) dacă sunt disponibile: `pip install types-<library-name>`

### Medii virtuale Python

#### Problemă: Nu poate fi creat mediul virtual  
**Eroare:** `The virtual environment was not created successfully`

**Soluție:**  
1. **Instalați modulul venv:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Este inclus implicit cu Python  
   - Windows: Reinstalați Python cu toate componentele  
2. **Verificați instalarea Python:** Asigurați-vă că Python este instalat corect  
3. **Folosiți calea completă:** Încercați `python3 -m venv .venv` specificând explicit python3

#### Problemă: Pachetele se instalează în locație greșită  
**Simptome:** Eroare la import după instalarea pachetului

**Soluție:**  
1. **Verificați dacă venv este activat:** Prompt-ul ar trebui să arate `(.venv)`  
2. **Verificați locația pip:** `which pip` ar trebui să indice `.venv/bin/pip`  
3. **Reinstalați în venv:** Activați venv-ul, apoi `pip install <package>`  
4. **Nu folosiți sudo cu pip** în mediul virtual

#### Problemă: Mediul virtual nu este portabil  
**Simptome:** Venv nu funcționează după mutare sau pe alt calculator

**Soluție:**  
1. **Nu mutați venv-urile:** Ștergeți și recreați în noua locație  
2. **Folosiți requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Recreați venv-ul:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # sau activate.bat pe Windows
   pip install -r requirements.txt
   ```
  
### Dependențe

#### Problemă: Instalarea pachetului eșuează  
**Eroare:** Diverse erori pip în timpul instalării

**Soluție:**  
1. **Actualizați pip-ul:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Instalați unelte de compilare:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Instalați Visual Studio Build Tools  
3. **Verificați conexiunea la internet**  
4. **Încercați alt index de pachete:** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **Instalați o versiune specifică:** `pip install <package>==<version>`

#### Problemă: Conflicte de dependențe  
**Eroare:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Soluție:**  
1. **Folosiți un mediu virtual nou** pentru fiecare proiect  
2. **Actualizați pachetele:** `pip install --upgrade <package>`  
3. **Verificați cerințele:** Folosiți `pip check` pentru a găsi conflicte  
4. **Instalați versiuni compatibile:** Specificați intervale versionale în requirements.txt

---

## Probleme de Performanță

### Problemă: Codul rulează lent  
**Simptome:** Întârzieri, timeouts, comportament nefuncțional

**Soluție:**  
1. **Reduceți frecvența de citire a senzorilor:** Nu citiți senzorii prea des  
2. **Optimizați buclele:** Evitați așteptarea pasivă, folosiți sleep() sau delay-uri  
3. **Probleme de memorie:**  
   - Închideți aplicațiile inutile  
   - Eliberați spațiu de stocare  
   - Monitorizați cu `top` sau `htop` pe Pi  
4. **Viteză SD card:** Folosiți card SD mai rapid sau SSD pentru Raspberry Pi  
5. **Întârzieri de rețea:** Folosiți operații asincrone pentru apeluri în rețea

### Problemă: Erori de memorie insuficientă  
**Eroare:** `MemoryError` sau sistemul se blochează

**Soluție:**  
1. **Pentru Raspberry Pi:**  
   - Închideți aplicațiile inutile  
   - Măriți spațiul de swap  
   - Folosiți o versiune OS mai ușoară (Lite)  
   - Faceți upgrade la RAM (Pi 4 are opțiuni 2/4/8GB)  
2. **Pentru Wio Terminal:**  
   - Reduceți dimensiunea buffer-elor  
   - Folosiți imagini mai mici  
   - Optimizați utilizarea string-urilor  
   - Verificați pentru scurgeri de memorie (memorie neeliberată)

### Problemă: Pierdere sau corupere de date  
**Simptome:** Mesaje lipsă, fișiere corupte

**Soluție:**  
1. **Probleme SD card:**  
   - Folosiți carduri de calitate (evitați cele ieftine/frauduloase)  
   - Faceți backup-uri regulate  
   - Opriți în mod curat (nu scoateți alimentarea)  
2. **Overflow buffer:** Măriți dimensiunea bufferelor în cod  
3. **Fiabilitate rețea:** Implementați logică de retry și tratare erori  
4. **Calitatea serviciului:** Folosiți MQTT QoS 1 sau 2 pentru mesaje importante

---

## Mesaje Comune de Eroare

### `ModuleNotFoundError: No module named 'X'`  
**Cauză:** Pachetul nu este instalat sau mediul virtual nu este activat

**Soluție:**  
```bash
pip install X
```
Asigurați-vă că mediul virtual este activat mai întâi.

### `Permission denied` pe Linux/macOS  
**Cauză:** Necesare permisiuni elevate sau problemă cu permisiunile fișierelor

**Soluție:**  
- Pentru operațiuni de sistem: folosiți `sudo`  
- Pentru pip: NU folosiți sudo cu venv, activați mai întâi venv-ul  
- Pentru port serial: adăugați utilizatorul în grupul dialout: `sudo usermod -a -G dialout $USER`, apoi reconnectați-vă

### `OSError: [Errno 98] Address already in use`  
**Cauză:** Portul este deja utilizat de un alt proces

**Soluție:**  
1. Găsiți procesul care folosește portul: `lsof -i :<port>` sau `netstat -ano | findstr :<port>`  
2. Închideți procesul sau folosiți alt port în cod

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Cauză:** Eșec validare certificat SSL

**Soluție:**  
1. Actualizați certificatele: `pip install --upgrade certifi`  
2. Verificați dacă ora sistemului este corectă: `date`  
3. Doar pentru dezvoltare (nu producție): dezactivați verificarea în cod

### `IndentationError: unexpected indent`  
**Cauză:** Probleme cu indentarea în Python (amestecare tab-uri/spații)

**Soluție:**  
1. Folosiți indentare consecventă (4 spații este standardul Python)  
2. Configurați editorul să folosească spații în loc de tab-uri  
3. VS Code: setați `"editor.insertSpaces": true` și `"editor.tabSize": 4`

### `UnicodeDecodeError` sau `UnicodeEncodeError`  
**Cauză:** Probleme de codare a caracterelor

**Soluție:**  
```python
# Când se citesc fișiere
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Când se scriu fișiere
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Obținerea Ajutorului

Dacă ați încercat acești pași de depanare și tot aveți probleme:

### 1. Verificați resursele disponibile  
- **Documentație:** Consultați [README](README.md) și instrucțiunile lecției  
- **Ghiduri hardware:** Verificați [hardware.md](hardware.md) pentru info specifice hardware-ului  
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) pentru componente Grove

### 2. Căutați probleme similare  
- **GitHub Issues:** Căutați [probleme existente](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Căutați mesaje de eroare  
- **Forumuri dispozitive:** Verificați forumurile Raspberry Pi sau Arduino

### 3. Creați un issue pe GitHub  
Dacă nu găsiți o soluție:  
1. Mergeți la [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Click pe "New Issue"  
3. Oferiți:  
   - Descriere clară a problemei  
   - Pași pentru reproducere  
   - Mesaje de eroare (text complet)  
   - Versiuni hardware/software  
   - Ce ați încercat deja  
   - Capturi de ecran, dacă sunt relevante

### 4. Alăturați-vă comunității  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Oferiți rapoarte bune de bug-uri  
Un raport bun include:
- **Mediu:** OS, versiunea Python, hardware-ul folosit  
- **Pași pentru reproducere:** Pașii exacti care cauzează problema  
- **Comportament așteptat:** Ce ar trebui să se întâmple  
- **Comportament real:** Ce se întâmplă de fapt  
- **Mesaje de eroare:** Textul complet al erorii, nu capturi de ecran  
- **Cod:** Exemplu minimal de cod care reproduce problema  

---

## Sfaturi pentru prevenire

### Practici generale recomandate  
1. **Păstrează copii de siguranță:** Backup-uri regulate ale cardurilor SD/codurilor funcționale  
2. **Documentează modificările:** Notează ce funcționează în comentarii  
3. **Controlul versiunilor:** Folosește git pentru a urmări modificările codului  
4. **Testează incremental:** Testează modificări mici înainte de a le combina  
5. **Citește mesajele de eroare:** De multe ori spun exact ce nu e în regulă  
6. **Actualizează regulat:** Menține software-ul/firmware-ul la zi  
7. **Folosește componente de calitate:** Evită cabluri/alimentări ieftine  
8. **Alimentare stabilă:** Folosește sursă de alimentare adecvată (mai ales pentru Pi)  

### Flux de lucru în dezvoltare  
1. **Începe simplu:** Pornește de la cod exemplu care funcționează  
2. **O singură modificare la un moment dat:** E mai ușor să identifici ce stric  
3. **Testează des:** Identifică problemele devreme  
4. **Menține curat:** Organizează fișierele și codul logic  
5. **Comentează codul:** Tu, în viitor, o să apreciezi asta  

---

*Acest ghid de depanare este întreținut de comunitate. Dacă găsești o soluție la o problemă care nu este listată aici, te rugăm să iei în considerare [contribuirea](CONTRIBUTING.md) pentru a ajuta și alți utilizatori!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Declinarea răspunderii**:  
Acest document a fost tradus utilizând serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim pentru acuratețe, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original, în limba sa nativă, trebuie considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm răspunderea pentru orice neînțelegeri sau interpretări greșite rezultate din utilizarea acestei traduceri.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->