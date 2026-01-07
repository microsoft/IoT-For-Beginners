<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T21:36:48+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "sl"
}
-->
# Vodnik za odpravljanje težav

Ta vodnik vam pomaga rešiti pogoste težave pri delu s kurikulom IoT for Beginners. Težave so organizirane po kategorijah za lažjo navigacijo.

## Kazalo vsebine

- [Težave z namestitvijo](../..)
  - [Namestitev Pythona](../..)
  - [VS Code in razširitve](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove knjižnice](../..)
- [Težave s strojno opremo](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtualna naprava (CounterFit)](../..)
- [Težave s povezljivostjo](../..)
  - [WiFi povezava](../..)
  - [Oblačne storitve](../..)
  - [MQTT](../..)
- [Težave s senzorji in aktuatorji](../..)
  - [Grove senzorji](../..)
  - [Kamera](../..)
  - [Mikrofon in zvočnik](../..)
- [Težave z razvojnim okoljem](../..)
  - [VS Code](../..)
  - [Python virtualna okolja](../..)
  - [Odvisnosti](../..)
- [Težave z zmogljivostjo](../..)
- [Pogoste napake](../..)
- [Kako poiskati pomoč](../..)

---

## Težave z namestitvijo

### Namestitev Pythona

#### Težava: Verzija Pythona je prestara
**Napaka:** `Zaželen je Python 3.6 ali novejši`

**Rešitev:**
1. Prenesite najnovejši Python 3 z [python.org](https://www.python.org/downloads/)
2. Med namestitvijo na Windows označite "Add Python to PATH"
3. Preverite namestitev:
   ```bash
   python3 --version
   ```

#### Težava: Več različic Pythona povzroča konflikte
**Simptomi:** Zažene se napačna verzija Pythona, paketi se nameščajo na napačno mesto

**Rešitev:**
- **Windows:** Uporabite `py -3` namesto `python` za eksplicitno uporabo Pythona 3
- **macOS/Linux:** Uporabite `python3` namesto `python`
- Vedno ustvarite in uporabljajte virtualna okolja za projekte

#### Težava: Ukaz pip ni najden
**Napaka:** `'pip' ni prepoznan kot notranji ali zunanji ukaz`

**Rešitev:**
1. Poskusite `pip3` namesto `pip`
2. Ali uporabite `python -m pip` ali `python3 -m pip`
3. Poskrbite, da je Python dodan v PATH (ponovno namestite Python in izberite možnost)

### VS Code in razširitve

#### Težava: Razširitev Pylance ne deluje
**Simptomi:** Ni Python IntelliSense, samodejnega dopolnjevanja kode ali preverjanja tipov

**Rešitev:**
1. Odprite ukazno paleto VS Code (`Ctrl+Shift+P` ali `Cmd+Shift+P`)
2. Zaženite "Python: Select Interpreter"
3. Izberite pravi Python interpreter (virtualno okolje, če ga uporabljate)
4. Znova naložite okno VS Code

#### Težava: VS Code ne zazna virtualnega okolja
**Simptomi:** Izbran napačen Python interpreter

**Rešitev:**
1. Poskrbite, da ste aktivirali virtualno okolje v terminalu
2. Odprite ukazno paleto in zaženite "Python: Select Interpreter"
3. Izberite interpreter iz mape `.venv`
4. Preverite, da spodnji levi status bar prikazuje pravilno verzijo Pythona

### PlatformIO (Wio Terminal)

#### Težava: Namestitev PlatformIO ne uspe
**Napaka:** Različne napake med namestitvijo PlatformIO

**Rešitev:**
1. Poskrbite, da je VS Code posodobljen
2. Najprej namestite C/C++ razširitev
3. Po namestitvi PlatformIO znova zaženite VS Code
4. Preverite internetno povezavo (PlatformIO prenaša velike datoteke)

#### Težava: PlatformIO ne zazna plošče
**Simptomi:** Ne morete prenesti kode na Wio Terminal

**Rešitev:**
1. Poskusite z drugim USB kablom (nekateri kabli so samo za polnjenje)
2. Preverite Upravitelja naprav (Windows) ali `ls /dev/tty*` (macOS/Linux)
3. Namestite ali posodobite USB gonilnike
4. Poskusite z drugim USB priključkom
5. Hitro dvakrat povlecite gumb za vklop na Wio Terminalu v položaj bootloaderja

#### Težava: Napake pri prevajanju v PlatformIO
**Napaka:** `fatal error: Arduino.h: No such file or directory`

**Rešitev:**
1. Izbrišite mapo `.pio` v vašem projektu
2. Iz ukazne palete poženite "PlatformIO: Rebuild"
3. Poskrbite, da `platformio.ini` vsebuje pravilno konfiguracijo plošče:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove knjižnice

#### Težava: Uvoz Grove knjižnice ne uspe na Raspberry Pi
**Napaka:** `ModuleNotFoundError: No module named 'grove'`

**Rešitev:**
1. Ponovno namestite Grove knjižnice:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Če uporabljate virtualno okolje, boste morda morali knjižnice namestiti globalno ali kopirati
3. Preverite, da je I2C omogočen: `sudo raspi-config nonint do_i2c 0`

#### Težava: Grove senzor ni zaznan
**Napaka:** `IOError: [Errno 121] Remote I/O error`

**Rešitev:**
1. Preverite fizične povezave (zagotovite, da je Grove kabel popolnoma vstavljen)
2. Potrdite, da je senzor povezan na pravilen vhod (analogni, digitalni, I2C, UART)
3. Zaženite `i2cdetect -y 1`, da preverite, ali se naprava pojavi na I2C vodilu
4. Poskusite z drugim Grove kablom
5. Preverite, da je Grove Base Hat pravilno nameščen na Raspberry Pi GPIO pinih

---

## Težave s strojno opremo

### Raspberry Pi

#### Težava: Raspberry Pi se ne zažene
**Simptomi:** Ni prikaza, ni aktivnosti LED, ali mavrični zaslon

**Rešitev:**
1. **Preverite napajanje:** Uporabite uradni 5V 3A USB-C napajalnik za Pi 4
2. **Težave z SD kartico:**
   - Formatirajte SD kartico in ponovno namestite Raspberry Pi OS
   - Poskusite z drugo SD kartico (uporabite priporočene znamke)
   - Preverite, da je SD kartica pravilno vstavljena
3. **Preverite HDMI povezavo:** Preizkusite oba HDMI priključka na Pi 4, uporabite HDMI priključek, ki je bližje napajanju

#### Težava: Ne morete se povezati preko SSH na Raspberry Pi
**Simptomi:** Povezava je zavrnjena ali poteče čas

**Rešitev:**
1. Omogočite SSH:
   - Pri pisanju SD kartice z Raspberry Pi Imagerjem konfigurirajte SSH v naprednih opcijah
   - Ali ustvarite prazno datoteko z imenom `ssh` (brez pripone) v zagonski particiji
2. Poiščite IP naslov Pi-ja:
   - Preverite naprave povezane na vaš usmerjevalnik
   - Uporabite `ping raspberrypi.local` (če deluje mDNS)
   - Uporabite orodja za skeniranje omrežja, kot so `nmap` ali Angry IP Scanner
3. Preverite omrežje:
   - Poskrbite, da je Pi na istem omrežju kot vaš računalnik
   - Poskusite z ethernet povezavo namesto WiFi
4. Preverite uporabniško ime in geslo (privzeto: uporabnik `pi`, geslo `raspberry`)

#### Težava: Grove Base Hat ni zaznan
**Simptomi:** Senzorji ne delujejo, napake I2C

**Rešitev:**
1. Poskrbite, da je Base Hat pravilno nameščen na vseh GPIO pinih
2. Preverite za upognjene pine na Pi-ju ali Base Hat-u
3. Omogočite I2C vmesnik:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Preverite, da I2C deluje: `i2cdetect -y 1`

#### Težava: Raspberry Pi deluje počasi
**Simptomi:** Počasna uporabniška lupina, počasni odzivi

**Rešitev:**
1. Preverite hitrost SD kartice (uporabite razred 10 ali boljšo, ali SSD preko USB)
2. Oprostite diskovni prostor: `df -h` za preverjanje, izbrišite nepotrebne datoteke
3. Zmanjšajte količino pomnilnika za GPU v `raspi-config`, če ne uporabljate intenzivno kamere/zaslona
4. Zaprite nepotrebne aplikacije
5. Razmislite o nadgradnji na Pi 4 z več RAM-a, če uporabljate Pi 3 ali starejši

### Wio Terminal

#### Težava: Zaslon Wio Terminal ostane prazen
**Simptomi:** Ni prikaza po nalaganju kode

**Rešitev:**
1. Preverite, ali koda inicializira zaslon (knjižnica TFT_eSPI)
2. Posodobite firmware Wio Terminala iz [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Dodajte kodo za inicializacijo zaslona:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Poskusite naložiti primer iz PlatformIO za test strojne opreme

#### Težava: WiFi ne deluje na Wio Terminalu
**Simptomi:** Ni mogoče vzpostaviti WiFi povezave, napake omrežja

**Rešitev:**
1. **Posodobite WiFi firmware:** Sledite [navodilu za posodobitev WiFi firmware Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Preverite WiFi podatke za prijavo:** Poskrbite, da sta SSID in geslo pravilna
3. **WiFi pas:** Wio Terminal podpira samo 2.4GHz WiFi (ne 5GHz)
4. **Jakost signala:** Premaknite se bližje usmerjevalniku
5. **Nastavitve usmerjevalnika:** Nekatera podjetniška/WPA-Enterprise omrežja morda ne delujejo

#### Težava: Računalnik ne zazna Wio Terminala
**Simptomi:** USB naprava ni zaznana

**Rešitev:**
1. **Poskusite z drugim USB kablom:** Uporabite podatkovni kabel, ne samo polnilnega
2. **Vstopite v način bootloaderja:** Hitro povlecite gumb za vklop dvakrat navzdol
   - Modra LED naj utripa, naprava se pojavi kot "Arduino" v Upravitelju naprav
3. **Namestite gonilnike (Windows):**
   - Prenesite in namestite [Seeed USB gonilnik](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Poskusite z drugim USB priključkom:** Izogibajte se USB stikalom, uporabite neposredno povezavo
5. **Posodobite sistemske USB gonilnike**

#### Težava: Senzorji na Wio Terminalu ne delujejo
**Simptomi:** Grove senzorji ne beležijo podatkov

**Rešitev:**
1. Preverite povezave Grove kabla
2. Preverite, da uporabljate pravilen Grove vhod (levo ali desno)
3. Vključite ustrezne knjižnice za senzor
4. Preverite zahteve napajanja senzorja
5. Testirajte senzor s primerom kode iz knjižnice

### Virtualna naprava (CounterFit)

#### Težava: Aplikacija CounterFit se ne zažene
**Napaka:** Različne Python napake ob zagonu CounterFit

**Rešitev:**
1. Poskrbite, da je virtualno okolje aktivirano
2. Namestite/ponovno namestite CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Preverite, da vrata 5000 niso že v uporabi:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Ubijte proces, ki uporablja vrata 5000, ali uporabite druga vrata:
   ```bash
   counterfit --port 5001
   ```

#### Težava: Povezava do CounterFit iz kode ne uspe
**Napaka:** Povezava zavrnjena ali potekel čas

**Rešitev:**
1. Preverite, da CounterFit teče: Odprite brskalnik na `http://127.0.0.1:5000`
2. Preverite, da URL povezave v kodi ustreza naslovu CounterFit
3. Preverite, da požarni zid ne blokira povezave
4. Poskusite znova zagnati tako CounterFit aplikacijo kot vašo kodo

#### Težava: Senzorji se ne prikažejo v CounterFit
**Simptomi:** Ustvarjeni senzorji se ne prikažejo v uporabniškem vmesniku CounterFit

**Rešitev:**
1. Ustvarite senzorje v uporabniškem vmesniku CounterFit pred zagonom kode
2. Osvežite stran brskalnika
3. Preverite, da tip senzorja ustreza temu, kar pričakuje koda
4. Počistite predpomnilnik brskalnika

---

## Težave s povezljivostjo

### WiFi povezava

#### Težava: Naprava se ne more povezati z WiFi
**Simptomi:** Povezava poteče, preverjanje pristnosti ni uspelo

**Rešitev:**
1. **Preverite SSID in geslo:** Preverite, da so podatki za prijavo pravilni
2. **WiFi pas:** Večina IoT naprav podpira samo 2.4GHz (ne 5GHz)
3. **Nastavitve usmerjevalnika:**
   - Onemogočite AP izolacijo, če je omogočena
   - Uporabite WPA2-PSK varnost (izogibajte se WPA3, WEP ali odprtim omrežjem)
   - Poskrbite, da je DHCP omogočen
4. **Skrito omrežje:** Če je SSID skrit, boste morda morali eksplicitno nastaviti omrežje
5. **Jakost signala:** Premaknite napravo bližje usmerjevalniku
6. **Motnje:** Druge naprave, mikrovalovne pečice ali stene lahko povzročajo motnje

#### Težava: WiFi povezava pogosto pade
**Simptomi:** Prekinjena povezava

**Rešitev:**
1. Preverite stabilnost usmerjevalnika in razmislite o ponovnem zagonu
2. Posodobite firmware naprave
3. Uporabljajte statični IP namesto DHCP
4. Zmanjšajte razdaljo do usmerjevalnika ali dodajte WiFi ojačevalnik
5. Preverite, ali motijo druge naprave
6. Preverite, da je napajanje ustrezno (še posebej za Raspberry Pi)

### Oblačne storitve

#### Težava: Ni mogoče povezati se do Azure IoT Hub
**Napaka:** Preverjanje pristnosti ni uspelo, povezava zavrnjena

**Rešitev:**
1. **Preverite poverilnice:**
   - Preverite, da je povezovalni niz pravilen
   - Poskrbite, da ni dodatnih presledkov ali prelomov vrstic v povezovalnem nizu
2. **Preverite registracijo naprave:** Naprava mora biti registrirana v IoT Hub-u
3. **Požarni zid/proxy:** Poskrbite, da je dovoljen odhodni promet MQTT (vrata 8883) ali HTTPS (vrata 443)
4. **Regija IoT Huba:** Poskrbite, da IoT Hub obratovalno deluje in ni v drugi regiji, ki povzroča zakasnitve
5. **Omejitve količine:** Preverite, ali so prekoračene omejitve brezplačne stopnje
6. **Preizkus povezave:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Težava: Azure Functions se ne sproži
**Simptomi:** Sporočila so poslana, funkcija pa ni izvršena

**Rešitev:**
1. Preverite, da applika funkcij deluje (ni ustavljena)
2. Preverite povezovalni niz v nastavitvah Azure Functions
3. Preverite dnevniške zapise funkcije v Azure portalu
4. Preverite, da je konfiguriran združljiv endpoint Event Huba
5. Preverite, da oblika sporočila ustreza pričakovanjem funkcije
6. Preverite načrt storitve Azure Functions (poraba ali namenski načrt)

### MQTT
#### Težava: Povezava MQTT ne uspe
**Napaka:** Povezava zavrnjena, preverjanje pristnosti spodletelo

**Rešitev:**
1. **Naslov posrednika:** Preverite, ali je URL/IP posrednika pravilen
2. **Vrata:** Preverite številko vrat (1883 za nešifrirano, 8883 za TLS)
3. **Preverjanje pristnosti:** Preverite uporabniško ime/geslo, če je zahtevano
4. **TLS/SSL:** Zagotovite, da so certifikati veljavni in zaupanja vredni
5. **Požarni zid:** Preverite, da vrata niso blokirana
6. **Test z MQTT odjemalcem:** Uporabite MQTT Explorer ali mosquitto_pub/sub za testiranje

#### Težava: Sporočila MQTT niso prejeta
**Simptomi:** Sporočila so bila objavljena, vendar jih naročniki niso prejeli

**Rešitev:**
1. **Imena tem:** Preverite, da se tema naročnika natančno ujema s temo založnika
2. **Raven QoS:** Poskusite QoS 1 ali 2 namesto 0
3. **Divje karte:** Preverite pravilno uporabo tematskih divjih kart (`+` za eno raven, `#` za več ravni)
4. **Zadržana sporočila:** Založnik lahko nastavi zastavico za zadrževanje, da ohrani zadnje sporočilo
5. **Čas povezave:** Zagotovite, da se naročnik poveže pred objavo sporočil

---

## Težave s senzorji in aktuatorji

### Grove Senzorji

#### Težava: Senzor vrača nepravilne vrednosti
**Simptomi:** Meritve so 0, -1 ali nesmiselne vrednosti

**Rešitev:**
1. **Preverite povezave:** Zagotovite, da je senzor pravilno povezan
2. **Prava vrata:** Preverite, da je senzor na pravem tipu vrat:
   - Analogni senzorji → Analogna vrata (A0, A2, A4)
   - Digitalni senzorji → Digitalna vrata (D5, D16, D18, itd.)
   - I2C senzorji → I2C vrata
3. **Kalibracija:** Nekateri senzorji potrebujejo kalibracijo (vlaga v tleh, svetloba)
4. **Ponovni zagon:** Odklopite in ponovno priklopite senzor
5. **Datasheet senzorja:** Preverite specifikacije in zahteve senzorja

#### Težava: Kapacitivni senzor vlage v tleh vedno meri mokro
**Simptomi:** Senzor meri visoko vlažnost tudi, ko je suho

**Rešitev:**
1. **Potrebna kalibracija:** Senzorji za zemeljsko vlago zahtevajo kalibracijo:
   - Meritev v zraku (suh referenčni nivo)
   - Meritev v vodi (mokri referenčni nivo)
   - Preslikava meritve med tema vrednostma
2. **Preverite zaščito senzorja:** Vlažni senzorji se lahko poslabšajo, če je prevleka poškodovana
3. **Postavitev:** Zagotovite, da je senzor popolnoma vstavljen v tla

#### Težava: Meritve temperature/vlage so nepravilne
**Simptomi:** DHT11/DHT22 prikazuje napačno temperaturo ali vlago

**Rešitev:**
1. **Postavitev senzorja:** Izogibajte se neposredni sončni svetlobi, virom toplote ali pretoku zraka
2. **Čas segrevanja:** Senzorju dovolite 2 sekundi po vklopu, preden berete
3. **Pogostost merjenja:** DHT senzorji potrebujejo čas med meritvami (vsaj 2 sekundi)
4. **Preverite kondenzacijo:** Lahko vpliva na meritve
5. **Kakovost senzorja:** DHT11 je manj natančen kot DHT22

### Kamera

#### Težava: Kamera ni zaznana na Raspberry Pi
**Napaka:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Rešitev:**
1. **Omogočite vmesnik kamere:**
   ```bash
   sudo raspi-config
   ```
   Pojdite na Interface Options → Camera → Enable
2. **Preverite trak kabla:** Zagotovite, da je kabel kamere pravilno vstavljen
   - Modra stran gleda proti USB priključkom na Pi Zero
   - Modra stran gleda stran od USB priključkov na Pi 4
3. **Posodobite firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Preizkusite kamero:**
   ```bash
   raspistill -o test.jpg
   ```

#### Težava: Slike iz kamere so nizke kakovosti
**Simptomi:** Zamegljene, temne ali izprane slike

**Rešitev:**
1. **Fokus:** Odstranite zaščitno folijo s leče, prilagodite fokus, če je nastavljiv
2. **Osvetlitev:** Zagotovite ustrezno osvetlitev
3. **Nastavitve kamere:** Prilagodite osvetlitev, ISO, bel balans v kodi
4. **Stabilnost:** Držite kamero mirno, uporabite stojalo, če je potrebno
5. **Ločljivost:** Ne presežite največje ločljivosti kamere

### Mikrofon in zvočnik

#### Težava: Ni avdio vhoda/izhoda
**Simptomi:** Mikrofon ne snema, zvočnik ne predvaja

**Rešitev:**
1. **Preverite povezave:** Preverite, ali so avdio naprave pravilno priključene
2. **Test strojne opreme:**
   - Zvočnik: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` za seznam, `arecord test.wav` za snemanje
3. **Nastavitve glasnosti:** Preverite in prilagodite glasnost:
   ```bash
   alsamixer
   ```
4. **Izberite avdio napravo:** V kodi navedite pravilno avdio napravo
5. **Težave z gonilniki:** Posodobite ALSA ali ponovno namestite avdio gonilnike

#### Težava: ReSpeaker hat ne deluje
**Simptomi:** Avdio naprava ni zaznana

**Rešitev:**
1. **Namestite gonilnike:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Preverite namestitev:** `arecord -l` bi moral našteti ReSpeaker
3. **Posodobite firmware:** Nekatere različice Pi OS potrebujejo posodobitve gonilnikov
4. **Preverite priklop:** Zagotovite, da je hat pravilno priključen na GPIO pin-e

---

## Težave z razvojnim okoljem

### VS Code

#### Težava: Terminal se ne aktivira samodejno v virtualnem okolju
**Simptomi:** Terminal se odpre, vendar virtualno okolje ni aktivirano

**Rešitev:**
1. **Nastavite Python interpreter:** Command Palette → "Python: Select Interpreter" → Izberite venv
2. **Ponovno zaženite VS Code** po izbiri interpreterja
3. **Preverite nastavitve:** V `settings.json` dodajte:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Težava: Koda ne teče na napravi
**Simptomi:** Koda teče, a na napravi se nič ne zgodi

**Rešitev:**
1. **Preverite, da je koda shranjena** (preverite piko na zavihku datoteke)
2. **Preverite, kateri Python teče:** `which python` ali `where python`
3. **Za Wio Terminal:** Zagotovite nalaganje kode preko PlatformIO (kliknite gumb za nalaganje)
4. **Za Raspberry Pi:** Prijavite se prek SSH na Pi in tam zaženite kodo
5. **Preverite okno z izhodom** za napake

#### Težava: IntelliSense ne prikazuje funkcij knjižnice
**Simptomi:** Ni samodejnega dopolnjevanja za uvožene module

**Rešitev:**
1. Zagotovite, da je knjižnica nameščena v tekočem okolju
2. Ponovno naložite okno VS Code
3. Preverite, da je Python interpreter pravilen
4. Namestite type stube, če so na voljo: `pip install types-<ime-knjižnice>`

### Python virtualna okolja

#### Težava: Ne morem ustvariti virtualnega okolja
**Napaka:** `The virtual environment was not created successfully`

**Rešitev:**
1. **Namestite venv modul:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Vključen v Python
   - Windows: Znova namestite Python z vsemi komponentami
2. **Preverite namestitev Pythona:** Zagotovite, da je Python pravilno nameščen
3. **Uporabite polno pot:** Poskusite `python3 -m venv .venv` z izrecnim klicem python3

#### Težava: Paketi nameščeni na napačnem mestu
**Simptomi:** Napaka pri uvozu po namestitvi paketa

**Rešitev:**
1. **Preverite aktivacijo venv:** Ukazna vrstica naj kaže `(.venv)`
2. **Preverite lokacijo pip:** `which pip` naj kaže na `.venv/bin/pip`
3. **Ponovno namestite v venv:** Aktivirajte venv, nato `pip install <package>`
4. **Ne uporabljajte sudo s pip** v virtualnem okolju

#### Težava: Virtualno okolje ni prenosljivo
**Simptomi:** Venv ne deluje po premiku ali na drugem računalniku

**Rešitev:**
1. **Ne premikajte venv:** Izbrišite ga in ustvarite novega na novi lokaciji
2. **Uporabite requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Znova ustvarite venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # ali activate.bat na Windows
   pip install -r requirements.txt
   ```

### Odvisnosti

#### Težava: Namestitev paketa ne uspe
**Napaka:** Različne napake pip med namestitvijo

**Rešitev:**
1. **Posodobite pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Namestite orodja za gradnjo:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Namestite Visual Studio Build Tools
3. **Preverite povezavo z internetom**
4. **Poskusite drug repozitorij paketov:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **Namestite specifično različico:** `pip install <package>==<version>`

#### Težava: Konflikti odvisnosti
**Napaka:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Rešitev:**
1. **Uporabite sveže virtualno okolje** za vsak projekt
2. **Posodobite pakete:** `pip install --upgrade <package>`
3. **Preverite zahteve:** Uporabite `pip check` za iskanje konfliktov
4. **Namestite združljive različice:** V zahtevah določite razpon različic v requirements.txt

---

## Težave s hitrostjo

### Težava: Koda teče počasi
**Simptomi:** Zamude, prekinitve, neodzivno vedenje

**Rešitev:**
1. **Zmanjšajte frekvenco branja senzorjev:** Ne berite senzorjev preveč pogosto
2. **Optimizirajte zanke:** Izogibajte se čakanju, uporabite sleep() ali zakasnitve
3. **Težave z pomnilnikom:**
   - Zaprite nepotrebne aplikacije
   - Oprostite prostor na disku
   - Spremljajte z `top` ali `htop` na Pi
4. **Hitrost SD kartice:** Uporabite hitrejšo SD kartico ali SSD za Raspberry Pi
5. **Odzivnost omrežja:** Uporabljajte asinhrone operacije za omrežne klice

### Težava: Napake zaradi pomanjkanja pomnilnika
**Napaka:** `MemoryError` ali zamrznitev sistema

**Rešitev:**
1. **Za Raspberry Pi:**
   - Zaprite nepotrebne aplikacije
   - Povečajte swap prostor
   - Uporabite lažjo različico OS (Lite verzija)
   - Nadgradite RAM (Pi 4 ima 2/4/8GB opcije)
2. **Za Wio Terminal:**
   - Zmanjšajte velikosti predpomnilnikov
   - Uporabljajte manjše slike
   - Optimizirajte uporabo nizov
   - Preverite puščanje pomnilnika (neprostejen pomnilnik)

### Težava: Izguba ali korupcija podatkov
**Simptomi:** Manjkajoča sporočila, poškodovane datoteke

**Rešitev:**
1. **Težave s SD kartico:**
   - Uporabljajte kakovostne SD kartice (izogibajte se poceni/ponarejenim)
   - Redni varnostni prenosi
   - Čisto zaustavitev (ne izključujte napajanja nenadoma)
2. **Prelivanje predpomnilnika:** Povečajte velikosti predpomnilnikov v kodi
3. **Zanesljivost omrežja:** Uvedite logiko ponovnih poskusov in obdelavo napak
4. **Kakovost storitve:** Za pomembna sporočila uporabite MQTT QoS 1 ali 2

---

## Pogoste napake

### `ModuleNotFoundError: No module named 'X'`
**Vzrok:** Paket ni nameščen ali virtualno okolje ni aktivirano

**Rešitev:**
```bash
pip install X
```
Najprej zagotovite aktivacijo virtualnega okolja.

### `Permission denied` na Linux/macOS
**Vzrok:** Potrebna so povišana dovoljenja ali težave z dovoljenji datotek

**Rešitev:**
- Za sistemske operacije: uporabite `sudo`
- Za pip: NE uporabljajte sudo z venv, najprej aktivirajte venv
- Za serijski port: Dodajte uporabnika v skupino dialout: `sudo usermod -a -G dialout $USER`, nato odjavite/prijavite se

### `OSError: [Errno 98] Address already in use`
**Vzrok:** Vrata že uporablja drug proces

**Rešitev:**
1. Poiščite proces, ki uporablja vrata: `lsof -i :<port>` ali `netstat -ano | findstr :<port>`
2. Ubijte proces ali v kodi uporabite drugačna vrata

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Vzrok:** Neuspešna preveritev SSL certifikata

**Rešitev:**
1. Posodobite certifikate: `pip install --upgrade certifi`
2. Preverite pravilen čas sistema: `date`
3. Samo za razvoj (ne produkcija): Onemogočite preverjanje v kodi

### `IndentationError: unexpected indent`
**Vzrok:** Težave z zamiki v Pythonu (mešanje tabulatorjev in presledkov)

**Rešitev:**
1. Uporabite dosledne zamike (4 presledki so standard v Pythonu)
2. Nastavite urejevalnik, da uporablja presledke namesto tabulatorjev
3. VS Code: Nastavite `"editor.insertSpaces": true` in `"editor.tabSize": 4`

### `UnicodeDecodeError` ali `UnicodeEncodeError`
**Vzrok:** Težave s kodiranjem znakov

**Rešitev:**
```python
# Med branjem datotek
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Med pisanjem datotek
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Iskanje pomoči

Če ste poskusili te korake za odpravljanje težav in še vedno imate težave:

### 1. Preverite obstoječe vire
- **Dokumentacija:** Preglejte [README](README.md) in navodila za lekcije
- **Vodiči za strojno opremo:** Preverite [hardware.md](hardware.md) za informacije, specifične za strojno opremo
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) za Grove komponente

### 2. Iščite podobne težave
- **GitHub Issues:** Iščite [obstoječe težave](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Iščite po sporočilih o napakah
- **Forumi za naprave:** Preverite forume Raspberry Pi ali Arduino

### 3. Ustvarite GitHub issue
Če ne najdete rešitve:
1. Pojdite na [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Kliknite "New Issue"
3. Navedite:
   - Jasno opis težave
   - Korake za ponovitev težave
   - Sporočila o napakah (celotno besedilo)
   - Verzije strojne/ programske opreme
   - Kaj ste že poskusili
   - Posnetke zaslona, če so pomembni

### 4. Pridružite se skupnosti
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Zagotovite dobre bug report-e
Dober bug report vsebuje:
- **Okolje:** OS, različica Pythona, uporabljena strojna oprema
- **Koraki za ponovitev:** Natančni koraki, ki povzročijo težavo
- **Pričakovano vedenje:** Kaj bi se moralo zgoditi
- **Dejansko vedenje:** Kaj se dejansko zgodi
- **Sporočila o napakah:** Celotno besedilo napake, brez posnetkov zaslona
- **Koda:** Minimalen primer kode, ki reproducira težavo

---

## Nasveti za preprečevanje

### Splošne dobre prakse
1. **Varnostne kopije:** Redno varnostno kopirajte delujoče SD kartice/kodo
2. **Dokumentirajte spremembe:** Zapišite, kaj deluje v komentarjih
3. **Nadzor različic:** Uporabljajte git za sledenje spremembam kode
4. **Testirajte postopoma:** Preizkušajte manjše spremembe pred združevanjem
5. **Berite sporočila o napakah:** Pogosto povedo natanko, kaj je narobe
6. **Redno posodabljajte:** Ohranjajte programsko opremo/firmware posodobljeno
7. **Uporabljajte kakovostne komponente:** Izogibajte se poceni kablom/napajalnikom
8. **Stabilna napetost:** Uporabljajte primerno napajanje (še posebej Pi)

### Razvojni potek dela
1. **Začnite preprosto:** Začnite z delujočo vzorčno kodo
2. **Po ena sprememba naenkrat:** Lažje je odkriti, kaj povzroča napako
3. **Pogosto testirajte:** Težave odpravite zgodaj
4. **Ohranite red:** Logično organizirajte datoteke in kodo
5. **Komentirajte kodo:** Vaša prihodnost vam bo hvaležna

---

*Ta vodič za odpravljanje težav vzdržuje skupnost. Če najdete rešitev za težavo, ki tukaj ni navedena, razmislite o tem, da [prispevate](CONTRIBUTING.md) in pomagate drugim!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Omejitev odgovornosti**:
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas opozarjamo, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Originalni dokument v njegovem izvirnem jeziku velja za avtoritativni vir. Za ključne informacije priporočamo strokovni človeški prevod. Nismo odgovorni za morebitna nesporazume ali napačne interpretacije, ki izhajajo iz uporabe tega prevoda.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->