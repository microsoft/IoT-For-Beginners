<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T21:35:07+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "hr"
}
-->
# Vodič za rješavanje problema

Ovaj vodič pomaže vam u rješavanju uobičajenih problema pri radu s IoT curriculumom za početnike. Problemi su organizirani po kategorijama radi lakše navigacije.

## Sadržaj

- [Problemi s instalacijom](../..)
  - [Instalacija Pythona](../..)
  - [VS Code i dodaci](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove biblioteke](../..)
- [Problemi s hardverom](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtualni uređaj (CounterFit)](../..)
- [Problemi s povezivošću](../..)
  - [WiFi veza](../..)
  - [Cloud servisi](../..)
  - [MQTT](../..)
- [Problemi sa senzorima i aktuatorima](../..)
  - [Grove senzori](../..)
  - [Kamera](../..)
  - [Mikrofon i zvučnik](../..)
- [Problemi s razvojnom okolinom](../..)
  - [VS Code](../..)
  - [Python virtualna okruženja](../..)
  - [Ovisnosti](../..)
- [Problemi s performansama](../..)
- [Česte poruke o greškama](../..)
- [Dobivanje pomoći](../..)

---

## Problemi s instalacijom

### Instalacija Pythona

#### Problem: Verzija Pythona je prestara
**Greška:** `Potrebna je verzija Python 3.6 ili novija`

**Rješenje:**
1. Preuzmite najnoviji Python 3 s [python.org](https://www.python.org/downloads/)
2. Tijekom instalacije na Windowsu označite "Add Python to PATH"
3. Provjerite instalaciju:
   ```bash
   python3 --version
   ```

#### Problem: Više verzija Pythona uzrokuje konflikte
**Simptomi:** Pokreće se pogrešna verzija Pythona, paketi se instaliraju na krivu lokaciju

**Rješenje:**
- **Windows:** Koristite `py -3` umjesto `python` za eksplicitno pokretanje Python 3
- **macOS/Linux:** Koristite `python3` umjesto `python`
- Uvijek kreirajte i koristite virtualna okruženja za projekte

#### Problem: Naredba pip nije pronađena
**Greška:** `'pip' nije prepoznata kao interna ili vanjska naredba`

**Rješenje:**
1. Pokušajte s `pip3` umjesto `pip`
2. Ili koristite `python -m pip` ili `python3 -m pip`
3. Provjerite je li Python dodan u PATH (ponovno instalirajte i uključite opciju)

### VS Code i dodaci

#### Problem: Pylance dodatak ne radi
**Simptomi:** Nema Python IntelliSense, dovršetka koda ili provjere tipova

**Rješenje:**
1. Otvorite Command Palette u VS Code (`Ctrl+Shift+P` ili `Cmd+Shift+P`)
2. Pokrenite "Python: Select Interpreter"
3. Odaberite ispravan Python interpreter (virtualno okruženje ako koristite)
4. Ponovno učitajte VS Code prozor

#### Problem: VS Code ne prepoznaje virtualno okruženje
**Simptomi:** Odabrani je krivi Python interpreter

**Rješenje:**
1. Provjerite jeste li aktivirali virtualno okruženje u terminalu
2. Otvorite Command Palette i pokrenite "Python: Select Interpreter"
3. Odaberite interpreter iz `.venv` mape
4. Provjerite statusnu traku (dolje lijevo) gdje treba pisati ispravna verzija Pythona

### PlatformIO (Wio Terminal)

#### Problem: Instalacija PlatformIO ne uspijeva
**Greška:** Razne greške tijekom instalacije PlatformIO

**Rješenje:**
1. Provjerite je li VS Code ažuriran
2. Prvo instalirajte C/C++ dodatak
3. Ponovno pokrenite VS Code nakon instalacije PlatformIO
4. Provjerite internet vezu (PlatformIO preuzima velike datoteke)

#### Problem: PlatformIO ne prepoznaje ploču
**Simptomi:** Ne može se poslati kod na Wio Terminal

**Rješenje:**
1. Isprobajte drugi USB kabel (neki su samo za punjenje)
2. Provjerite Device Manager (Windows) ili `ls /dev/tty*` (macOS/Linux)
3. Instalirajte ili ažurirajte USB drivere
4. Isprobajte drugi USB port
5. Brzo dvaput pomaknite prekidač za napajanje na Wio Terminalu da uđete u bootloader mod

#### Problem: Greške u kompilaciji na PlatformIO
**Greška:** `fatal error: Arduino.h: No such file or directory`

**Rješenje:**
1. Obrišite `.pio` mapu u projektu
2. Pokrenite "PlatformIO: Rebuild" iz Command Palette
3. Provjerite je li `platformio.ini` s ispravnom konfiguracijom ploče:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove biblioteke

#### Problem: Neuspješan import Grove biblioteke na Raspberry Pi
**Greška:** `ModuleNotFoundError: No module named 'grove'`

**Rješenje:**
1. Ponovno instalirajte Grove biblioteke:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Ako koristite virtualno okruženje, možda trebate instalirati globalno ili kopirati biblioteke
3. Provjerite je li I2C omogućen: `sudo raspi-config nonint do_i2c 0`

#### Problem: Grove senzor nije prepoznat
**Greška:** `IOError: [Errno 121] Remote I/O error`

**Rješenje:**
1. Provjerite fizičke veze (provjerite je li Grove kabel potpuno umetnut)
2. Provjerite je li senzor povezan na ispravan port (analogni, digitalni, I2C, UART)
3. Pokrenite `i2cdetect -y 1` da vidite pojavljuje li se uređaj na I2C busu
4. Isprobajte drugi Grove kabel
5. Provjerite je li Grove Base Hat pravilno postavljen na GPIO pinove Raspberry Pi

---

## Problemi s hardverom

### Raspberry Pi

#### Problem: Raspberry Pi se ne pali
**Simptomi:** Nema prikaza, nema aktivnosti LED-a ili ekran je u duginim bojama

**Rješenje:**
1. **Provjerite napajanje:** Koristite službeni 5V 3A USB-C napajanje za Pi 4
2. **Problemi sa SD karticom:** 
   - Formatirajte SD karticu i ponovno instalirajte Raspberry Pi OS
   - Isprobajte drugu SD karticu (koristite preporučene marke)
   - Provjerite je li SD kartica pravilno umetnuta
3. **Provjerite HDMI vezu:** Isprobajte oba HDMI porta na Pi 4, koristite port bliže napajanju

#### Problem: Ne može se spojiti na Raspberry Pi putem SSH-a
**Simptomi:** Veza odbijena ili je isteklo vrijeme

**Rješenje:**
1. Omogućite SSH:
   - Prilikom pisanja OS na SD karticu uz Raspberry Pi Imager, konfigurirajte SSH u naprednim opcijama
   - Ili kreirajte praznu datoteku nazvanu `ssh` (bez ekstenzije) u boot particiji
2. Pronađite IP adresu Pi-ja:
   - Provjerite spojene uređaje na vašem routeru
   - Koristite `ping raspberrypi.local` (ako mDNS radi)
   - Koristite alate za skeniranje mreže kao `nmap` ili Angry IP Scanner
3. Provjerite mrežu:
   - Provjerite da je Pi na istoj mreži kao računalo
   - Pokušajte kabelsku vezu umjesto WiFi-ja
4. Provjerite korisničko ime/lozinku (zadano: korisnik `pi`, lozinka `raspberry`)

#### Problem: Grove Base Hat nije prepoznat
**Simptomi:** Senzori ne rade, I2C greške

**Rješenje:**
1. Provjerite je li Base Hat pravilno postavljen na sve GPIO pinove
2. Provjerite ima li savijenih pinova na Pi-ju ili Base Hatu
3. Omogućite I2C sučelje:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Provjerite radi li I2C: `i2cdetect -y 1`

#### Problem: Raspberry Pi radi sporo
**Simptomi:** Sučelje zaostaje, spora reakcija

**Rješenje:**
1. Provjerite brzinu SD kartice (koristite Class 10 ili bolju, ili SSD preko USB-a)
2. Oslobodite prostor na disku: `df -h` za provjeru, izbrišite nepotrebne datoteke
3. Smanjite memoriju za GPU u `raspi-config` ako ne koristite intenzivno kameru/prikaz
4. Zatvorite nepotrebne aplikacije
5. Razmislite o nadogradnji na Pi 4 s većom količinom RAM-a ako koristite Pi 3 ili stariji

### Wio Terminal

#### Problem: Ekran Wio Terminala ostaje prazan
**Simptomi:** Nema prikaza nakon učitavanja koda

**Rješenje:**
1. Provjerite pokreće li kod inicijalizaciju zaslona (TFT_eSPI knjižnica)
2. Ažurirajte firmver Wio Terminala s [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Dodajte kod za inicijalizaciju zaslona:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Pokušajte učitati primjer iz PlatformIO za testiranje hardvera

#### Problem: WiFi ne radi na Wio Terminalu
**Simptomi:** Ne može se spojiti na WiFi, mrežne greške

**Rješenje:**
1. **Ažurirajte WiFi firmver:** Slijedite [Wio Terminal WiFi firmver vodič](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Provjerite WiFi pristupne podatke:** Provjerite jesu li SSID i lozinka ispravni
3. **WiFi frekvencija:** Wio Terminal podržava samo 2.4GHz WiFi (ne 5GHz)
4. **Jačina signala:** Približite se routeru
5. **Postavke routera:** Neki enterprise/WPA-Enterprise mreže možda neće raditi

#### Problem: Wio Terminal nije prepoznat na računalu
**Simptomi:** USB uređaj nije detektiran

**Rješenje:**
1. **Isprobajte drugi USB kabel:** Koristite kabel za podatke, ne samo za punjenje
2. **Uđite u bootloader mod:** Brzo dvaput pomaknite prekidač za napajanje prema dolje
   - Plava LED treba pulsirati, uređaj se prikazuje kao "Arduino" u Device Manageru
3. **Instalirajte drivere (Windows):**
   - Preuzmite i instalirajte [Seeed USB driver](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Isprobajte drugi USB port:** Izbjegavajte USB hubove, koristite direktnu vezu
5. **Ažurirajte USB drivere sustava**

#### Problem: Senzori ne rade na Wio Terminalu
**Simptomi:** Grove senzori ne evidentiraju podatke

**Rješenje:**
1. Provjerite veze Grove kabela
2. Provjerite koristite li ispravan Grove port (lijevi ili desni)
3. Uključite odgovarajuće knjižnice za senzor
4. Provjerite zahtjeve senzora za napajanje
5. Testirajte senzor s primjerom iz knjižnice

### Virtualni uređaj (CounterFit)

#### Problem: CounterFit aplikacija se ne pokreće
**Greška:** Razne Python greške pri pokretanju CounterFit

**Rješenje:**
1. Provjerite je li virtualno okruženje aktivirano
2. Instalirajte/ponovno instalirajte CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Provjerite nije li port 5000 već zauzet:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Ubijte proces koji koristi port 5000 ili koristite drugi port:
   ```bash
   counterfit --port 5001
   ```

#### Problem: Ne može se spojiti na CounterFit iz koda
**Greška:** Veza odbijena ili isteklo vrijeme

**Rješenje:**
1. Provjerite radi li CounterFit: otvorite preglednik na `http://127.0.0.1:5000`
2. Provjerite URL veze u kodu da odgovara adresi CounterFit-a
3. Provjerite da firewall ne blokira vezu
4. Pokušajte ponovno pokrenuti CounterFit aplikaciju i vaš kod

#### Problem: Senzori se ne pojavljuju u CounterFitu
**Simptomi:** Kreirani senzori se ne prikazuju u korisničkom sučelju

**Rješenje:**
1. Kreirajte senzore u korisničkom sučelju CounterFit prije pokretanja koda
2. Osvježite stranicu preglednika
3. Provjerite odgovara li tip senzora onome što kod očekuje
4. Očistite cache preglednika

---

## Problemi s povezivošću

### WiFi veza

#### Problem: Uređaj se ne može spojiti na WiFi
**Simptomi:** Vremensko ograničenje veze, neuspjela autentikacija

**Rješenje:**
1. **Provjerite SSID i lozinku:** Provjerite jesu li pristupni podaci ispravni
2. **WiFi frekvencija:** Većina IoT uređaja podržava samo 2.4GHz (ne 5GHz)
3. **Postavke routera:**
   - Onemogućite AP izolaciju ako je uključena
   - Koristite WPA2-PSK zaštitu (izbjegavajte WPA3, WEP ili otvorene mreže)
   - Provjerite je li DHCP omogućen
4. **Skrivene mreže:** Ako je SSID skriven, možda ćete ga morati eksplicitno konfigurirati
5. **Jačina signala:** Približite uređaj routeru
6. **Interferencija:** Drugi uređaji, mikrovalne pećnice ili zidovi mogu smetati

#### Problem: WiFi veza često pada
**Simptomi:** Prekinuta i uspostavljena veza

**Rješenje:**
1. Provjerite stabilnost routera, razmislite o ponovnom pokretanju
2. Ažurirajte firmver uređaja
3. Koristite statičku IP adresu umjesto DHCP-a
4. Smanjite udaljenost do routera ili dodajte WiFi extender
5. Provjerite je li smetnja od drugih uređaja
6. Provjerite je li napajanje dovoljno (posebno za Raspberry Pi)

### Cloud servisi

#### Problem: Ne može se spojiti na Azure IoT Hub
**Greška:** Neuspjela autentikacija, veza odbijena

**Rješenje:**
1. **Provjerite pristupne podatke:**
   - Provjerite je li connection string ispravan
   - Provjerite da nema dodatnih razmaka ili prijeloma linije u connection stringu
2. **Provjerite registraciju uređaja:** Uređaj mora biti registriran u IoT Hubu
3. **Firewall/proxy:** Osigurajte dopuštenje izlaznog MQTT (port 8883) ili HTTPS (port 443)
4. **Regija IoT Huba:** Provjerite je li IoT Hub aktivan i nije u drugoj regiji koja uzrokuje latenciju
5. **Ograničenja kvota:** Provjerite niste li premašili limite besplatnog nivoa
6. **Testirajte vezu:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problem: Azure Functions se ne pokreću
**Simptomi:** Poruke se šalju, ali funkcija se ne izvršava

**Rješenje:**
1. Provjerite radi li Function App (nije zaustavljen)
2. Provjerite connection string u postavkama Function App-a
3. Provjerite zapise funkcije u Azure Portalu
4. Osigurajte ispravnu konfiguraciju endpointa kompatibilnog s Event Hubom
5. Provjerite format poruke odgovara očekivanjima funkcije
6. Provjerite plan usluge Function App-a (potrošnja vs. dedikirano)

### MQTT
#### Problem: MQTT veza ne uspijeva
**Greška:** Veza odbijena, autentikacija nije uspjela

**Rješenje:**
1. **Adresa brokera:** Provjerite je li URL/IP brokera točan
2. **Port:** Provjerite broj porta (1883 za nešifrirano, 8883 za TLS)
3. **Autentikacija:** Provjerite korisničko ime/lozinku ako je potrebno
4. **TLS/SSL:** Osigurajte da su certifikati važeći i pouzdani
5. **Vatrozid:** Provjerite da port nije blokiran
6. **Testirajte s MQTT klijentom:** Koristite MQTT Explorer ili mosquitto_pub/sub za testiranje

#### Problem: MQTT poruke se ne primaju
**Simptomi:** Poruke su objavljene, ali ih pretplatnici ne primaju

**Rješenje:**
1. **Nazivi tema:** Provjerite podudara li se tema pretplatnika točno s temom izdavača
2. **Razina QoS:** Pokušajte s QoS 1 ili 2 umjesto 0
3. **Wildcard znakovi:** Provjerite koriste li se wildcards ispravno (`+` za jednu razinu, `#` za višerazinsku)
4. **Zadržane poruke:** Izdavač može postaviti zastavicu retenzije za zadržavanje zadnje poruke
5. **Vrijeme veze:** Osigurajte da se pretplatnik spoji prije nego što su poruke objavljene

---

## Problemi sa senzorima i aktuatorima

### Grove senzori

#### Problem: Senzor vraća netočne vrijednosti
**Simptomi:** Očitavanja su 0, -1 ili besmislene vrijednosti

**Rješenje:**
1. **Provjerite veze:** Osigurajte da je senzor pravilno spojen
2. **Ispravan port:** Provjerite je li senzor na ispravnom tipu porta:
   - Analogni senzori → Analogni portovi (A0, A2, A4)
   - Digitalni senzori → Digitalni portovi (D5, D16, D18, itd.)
   - I2C senzori → I2C portovi
3. **Kalibracija:** Neki senzori trebaju kalibraciju (vlažnost tla, svjetlo)
4. **Isključivanje/uključivanje:** Isključite i ponovno priključite senzor
5. **Datasheet senzora:** Provjerite specifikacije i zahtjeve senzora

#### Problem: Kapacitivni senzor vlage tla uvijek čita vlažno
**Simptomi:** Senzor mjeri visoku vlažnost čak i kad je suho

**Rješenje:**
1. **Potrebna kalibracija:** Senzori tla zahtijevaju kalibraciju:
   - Očitati vrijednost na zraku (suha referenca)
   - Očitati vrijednost u vodi (vlažna referenca)
   - Mapirati očitanja između tih vrijednosti
2. **Provjerite zaštitni sloj senzora:** Vlažni senzori mogu se oštetiti ako je zaštita oštećena
3. **Postavljanje:** Osigurajte da je senzor u potpunosti umetnut u tlo

#### Problem: Netočna očitanja senzora temperature/vlage
**Simptomi:** DHT11/DHT22 prikazuje pogrešnu temperaturu ili vlažnost

**Rješenje:**
1. **Postavljanje senzora:** Izbjegavajte direktno sunčevo svjetlo, izvore topline ili protok zraka
2. **Vrijeme zagrijavanja:** Dajte senzoru 2 sekunde nakon uključivanja prije očitanja
3. **Učestalost očitanja:** DHT senzori trebaju vrijeme između očitanja (barem 2 sekunde)
4. **Provjerite kondenzaciju:** Može utjecati na očitanja
5. **Kvaliteta senzora:** DHT11 je manje precizan od DHT22

### Kamera

#### Problem: Kamera nije prepoznata na Raspberry Pi-ju
**Greška:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Rješenje:**
1. **Omogućite kameru:**
   ```bash
   sudo raspi-config
   ```
   Idite na Interface Options → Camera → Enable
2. **Provjerite vrpcu:** Provjerite je li kabel kamere pravilno umetnut
   - Plava strana okrenuta prema USB portovima na Pi Zero
   - Plava strana okrenuta od USB portova na Pi 4
3. **Ažurirajte firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Testirajte kameru:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problem: Slike s kamere su loše kvalitete
**Simptomi:** Mutne, tamne ili isprane slike

**Rješenje:**
1. **Fokus:** Uklonite zaštitnu foliju s leće, podesite fokus ako je moguće
2. **Osvjetljenje:** Osigurajte dovoljno svjetla
3. **Postavke kamere:** Podesite ekspoziciju, ISO, balans bijele u kodu
4. **Stabilnost:** Držite kameru mirno, koristite stalak ako je potrebno
5. **Rezolucija:** Nemojte prekoračiti maksimalnu rezoluciju kamere

### Mikrofon i zvučnik

#### Problem: Nema audio ulaza/izlaza
**Simptomi:** Mikrofon ne snima, zvučnik ne reproducira

**Rješenje:**
1. **Provjerite veze:** Provjerite jesu li audio uređaji ispravno spojeni
2. **Testirajte hardver:**
   - Zvučnik: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` za popis, `arecord test.wav` za snimanje
3. **Postavke glasnoće:** Provjerite i podesite glasnoću:
   ```bash
   alsamixer
   ```
4. **Izaberite audio uređaj:** Odredite ispravan audio uređaj u kodu
5. **Problemi s upravljačkim programima:** Ažurirajte ALSA ili ponovo instalirajte audio drivere

#### Problem: ReSpeaker hat ne radi
**Simptomi:** Audio uređaj nije prepoznat

**Rješenje:**
1. **Instalirajte drivere:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Provjerite instalaciju:** `arecord -l` bi trebao prikazati ReSpeaker
3. **Ažurirajte firmware:** Neke verzije Pi OS trebaju ažuriranje drivera
4. **Provjerite spajanje:** Osigurajte da je hat pravilno spojena na GPIO pinove

---

## Problemi razvojnog okruženja

### VS Code

#### Problem: Terminal automatski ne aktivira virtualno okruženje
**Simptomi:** Terminal se otvara, ali venv nije aktiviran

**Rješenje:**
1. **Postavite Python interpreter:** Command Palette → "Python: Select Interpreter" → Odaberite venv
2. **Ponovno pokrenite VS Code** nakon odabira interpretera
3. **Provjerite postavke:** U `settings.json` dodajte:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problem: Kod se ne izvršava na uređaju
**Simptomi:** Kod se pokreće, ali nema učinka na uređaju

**Rješenje:**
1. **Provjerite je li kod spremljen** (provjerite točku na kartici datoteke)
2. **Provjerite koji Python se koristi:** `which python` ili `where python`
3. **Za Wio Terminal:** Provjerite da je kod učitan preko PlatformIO-a (kliknite tipku za učitavanje)
4. **Za Raspberry Pi:** SSH na Pi i pokrenite kod tamo
5. **Provjerite izlazni prozor** za greške

#### Problem: IntelliSense ne prikazuje funkcije biblioteke
**Simptomi:** Nema automatskog dovršavanja za uvezene module

**Rješenje:**
1. Provjerite je li biblioteka instalirana u trenutno aktivnom okruženju
2. Ponovno učitajte VS Code prozor
3. Provjerite da je Python interpreter ispravan
4. Instalirajte tipove ako su dostupni: `pip install types-<naziv-biblioteke>`

### Python virtualna okruženja

#### Problem: Ne može kreirati virtualno okruženje
**Greška:** `The virtual environment was not created successfully`

**Rješenje:**
1. **Instalirajte modul venv:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Trebao bi biti uključen s Pythonom
   - Windows: Ponovno instalirajte Python sa svim komponentama
2. **Provjerite instalaciju Pythona:** Provjerite da je Python pravilno instaliran
3. **Koristite puni put:** Pokušajte `python3 -m venv .venv` s eksplicitnim pozivom python3

#### Problem: Paketi se instaliraju na krivo mjesto
**Simptomi:** Greška pri uvozu nakon instalacije paketa

**Rješenje:**
1. **Provjerite je li venv aktivan:** Prompt naredbenog retka treba prikazivati `(.venv)`
2. **Provjerite lokaciju pip-a:** `which pip` treba pokazivati na `.venv/bin/pip`
3. **Ponovno instalirajte u venv:** Aktivirajte venv pa `pip install <package>`
4. **Ne koristite sudo s pip** u virtualnom okruženju

#### Problem: Virtualno okruženje nije prenosivo
**Simptomi:** Venv ne radi nakon premještanja ili na drugom računalu

**Rješenje:**
1. **Nemojte premještati venv:** Izbrišite i ponovo napravite na novoj lokaciji
2. **Koristite requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Ponovo kreirajte venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # ili activate.bat na Windowsu
   pip install -r requirements.txt
   ```

### Ovisnosti

#### Problem: Instalacija paketa ne uspijeva
**Greška:** Razne pip greške tijekom instalacije

**Rješenje:**
1. **Ažurirajte pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Instalirajte alate za izgradnju:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Instalirajte Visual Studio Build Tools
3. **Provjerite internetsku vezu**
4. **Koristite drugi package index:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **Instalirajte specifičnu verziju:** `pip install <package>==<version>`

#### Problem: Sukobi ovisnosti
**Greška:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Rješenje:**
1. **Koristite novo virtualno okruženje** za svaki projekt
2. **Ažurirajte pakete:** `pip install --upgrade <package>`
3. **Provjerite zahtjeve:** Koristite `pip check` za pronalaženje sukoba
4. **Instalirajte kompatibilne verzije:** Navedite raspon verzija u requirements.txt

---

## Problemi s izvedbom

### Problem: Kod radi sporo
**Simptomi:** Kašnjenja, timeouti, neodzivno ponašanje

**Rješenje:**
1. **Smanjite učestalost očitanja senzora:** Nemojte osjetnike čitati prečesto
2. **Optimizirajte petlje:** Izbjegavajte aktivno čekanje, koristite sleep() ili kašnjenja
3. **Problemi s memorijom:**
   - Zatvorite nepotrebne aplikacije
   - Oslobodite prostor na disku
   - Pratite s `top` ili `htop` na Pi-ju
4. **Brzina SD kartice:** Koristite bržu SD karticu ili SSD za Raspberry Pi
5. **Mrežna kašnjenja:** Koristite asinhrone operacije za mrežne pozive

### Problem: Nedostatak memorije
**Greška:** `MemoryError` ili zamrzavanje sustava

**Rješenje:**
1. **Za Raspberry Pi:**
   - Zatvorite nepotrebne aplikacije
   - Povećajte swap prostor
   - Koristite laganiji OS (Lite verzija)
   - Nadogradite RAM (Pi 4 ima opcije 2/4/8GB)
2. **Za Wio Terminal:**
   - Smanjite veličine bafera
   - Koristite manje slike
   - Optimizirajte korištenje stringova
   - Provjerite curenje memorije (neoslobodjena memorija)

### Problem: Gubitak ili oštećenje podataka
**Simptomi:** Nedostajuće poruke, oštećene datoteke

**Rješenje:**
1. **Problemi sa SD karticom:**
   - Koristite kvalitetne SD kartice (izbjegavajte jeftine/lažne)
   - Redovito pravite sigurnosne kopije
   - Ispravno isključivanje (nemojte isključivati napajanje sile)
2. **Preljev bafera:** Povećajte veličine bafera u kodu
3. **Pouzdanost mreže:** Implementirajte logiku ponovnog pokušaja i obradu grešaka
4. **Kvaliteta usluge:** Koristite MQTT QoS 1 ili 2 za važne poruke

---

## Uobičajene poruke o greškama

### `ModuleNotFoundError: No module named 'X'`
**Uzrok:** Paket nije instaliran ili virtualno okruženje nije aktivirano

**Rješenje:**
```bash
pip install X
```
Prvo osigurajte da je virtualno okruženje aktivirano.

### `Permission denied` na Linux/macOS
**Uzrok:** Potrebna povišena dopuštenja ili problem s dopuštenjima datoteke

**Rješenje:**
- Za sistemske operacije: Koristite `sudo`
- Za pip: NE koristite sudo s venv, prvo aktivirajte venv
- Za serijski port: Dodajte korisnika u dialout grupu: `sudo usermod -a -G dialout $USER`, zatim odjavite/prijavite se

### `OSError: [Errno 98] Address already in use`
**Uzrok:** Port je već zauzet od strane drugog procesa

**Rješenje:**
1. Pronađite proces koji koristi port: `lsof -i :<port>` ili `netstat -ano | findstr :<port>`
2. Ubijte proces ili koristite drugačiji port u svom kodu

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Uzrok:** Neuspjeh verifikacije SSL certifikata

**Rješenje:**
1. Ažurirajte certifikate: `pip install --upgrade certifi`
2. Provjerite je li sustavno vrijeme točno: `date`
3. Samo za razvoj (ne za proizvodnju): Onemogućite verifikaciju u kodu

### `IndentationError: unexpected indent`
**Uzrok:** Problemi s indentacijom u Pythonu (miješanje tabova i razmaka)

**Rješenje:**
1. Koristite dosljednu indentaciju (4 razmaka je standard za Python)
2. Konfigurirajte uređivač da koristi razmake umjesto tabova
3. VS Code: Postavite `"editor.insertSpaces": true` i `"editor.tabSize": 4`

### `UnicodeDecodeError` ili `UnicodeEncodeError`
**Uzrok:** Problemi s kodiranjem znakova

**Rješenje:**
```python
# Prilikom čitanja datoteka
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Prilikom pisanja datoteka
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Dobivanje pomoći

Ako ste isprobali ove korake za rješavanje problema i još uvijek imate poteškoća:

### 1. Provjerite postojeće izvore
- **Dokumentacija:** Pregledajte [README](README.md) i upute za lekcije
- **Vodiči za hardver:** Provjerite [hardware.md](hardware.md) za hardverske informacije
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) za Grove komponente

### 2. Pretražite slične probleme
- **GitHub Issues:** Pretražite [postojeće probleme](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Pretražite poruke o greškama
- **Forumi uređaja:** Provjerite Raspberry Pi forume ili Arduino forume

### 3. Kreirajte GitHub Issue
Ako ne možete pronaći rješenje:
1. Idite na [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Kliknite "New Issue"
3. Navedite:
   - Jasni opis problema
   - Korake za reprodukciju
   - Poruke o greškama (puni tekst)
   - Verzije hardvera i softvera
   - Što ste već pokušali
   - Snimke zaslona ako su relevantne

### 4. Pridružite se zajednici
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Pružite dobre izvještaje o bugovima
Dobar izvještaj o bugovima uključuje:
- **Okruženje:** OS, verzija Pythona, korišteni hardver
- **Koraci za reproduciranje:** Točni koraci koji uzrokuju problem
- **Očekivano ponašanje:** Što bi se trebalo dogoditi
- **Stvarno ponašanje:** Što se zapravo događa
- **Poruke o pogrešci:** Kompletan tekst pogreške, ne snimke zaslona
- **Kod:** Minimalni primjer koda koji reproducira problem

---

## Savjeti za prevenciju

### Opće najbolje prakse
1. **Napravite sigurnosne kopije:** Redovite sigurnosne kopije radnih SD kartica/koda
2. **Dokumentirajte promjene:** Zabilježite što radi u komentarima
3. **Kontrola verzija:** Koristite git za praćenje promjena koda
4. **Testirajte inkrementalno:** Testirajte male promjene prije kombiniranja
5. **Čitajte poruke o pogrešci:** Često vam kažu točno što nije u redu
6. **Redovito ažurirajte:** Održavajte softver/firmware ažurnim
7. **Koristite kvalitetne komponente:** Izbjegavajte jeftine kabele/napajanja
8. **Stabilno napajanje:** Koristite odgovarajuće napajanje (posebno za Pi)

### Radni tijek razvoja
1. **Započnite jednostavno:** Počnite s primjerom koda koji radi
2. **Jedna promjena odjednom:** Lakše je pronaći što je uzrok problema
3. **Često testirajte:** Otkrivajte probleme rano
4. **Održavajte urednost:** Organizirajte datoteke i kod logično
5. **Komentirajte kod:** Vaša buduća verzija će vam biti zahvalna

---

*Ovaj vodič za rješavanje problema održava zajednica. Ako pronađete rješenje za problem koji ovdje nije naveden, razmislite o [doprinosu](CONTRIBUTING.md) kako biste pomogli drugima!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Izjava o odricanju od odgovornosti**:
Ovaj dokument preveden je korištenjem AI usluge prevođenja [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo postići točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za kritične informacije preporučuje se profesionalni ljudski prijevod. Ne snosimo odgovornost za bilo kakve nesporazume ili kriva tumačenja koja proizlaze iz korištenja ovog prijevoda.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->