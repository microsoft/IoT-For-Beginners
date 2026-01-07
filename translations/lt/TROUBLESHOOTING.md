<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T21:46:21+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "lt"
}
-->
# Trikčių šalinimo vadovas

Šis vadovas padės jums išspręsti dažniausias problemas dirbant su IoT for Beginners mokymosi medžiaga. Problemų kategorijos suskirstytos patogiam naršymui.

## Turinys

- [Įdiegimo problemos](../..)
  - [Python įdiegimas](../..)
  - [VS Code ir plėtiniai](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove bibliotekos](../..)
- [Techninės įrangos problemos](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtualus įrenginys (CounterFit)](../..)
- [Ryšio problemos](../..)
  - [WiFi ryšys](../..)
  - [Debesų paslaugos](../..)
  - [MQTT](../..)
- [Jutiklių ir aktuatorių problemos](../..)
  - [Grove jutikliai](../..)
  - [Kamera](../..)
  - [Mikrofonas ir garsiakalbis](../..)
- [Kūrimo aplinkos problemos](../..)
  - [VS Code](../..)
  - [Python virtualios aplinkos](../..)
  - [Priklausomybės](../..)
- [Veikimo problemos](../..)
- [Dažnos klaidų žinutės](../..)
- [Pagalbos gavimas](../..)

---

## Įdiegimo problemos

### Python įdiegimas

#### Problema: Python versija per sena
**Klaida:** `Reikalinga Python 3.6 arba naujesnė versija`

**Sprendimas:**
1. Atsisiųskite naujausią Python 3 versiją iš [python.org](https://www.python.org/downloads/)
2. Įdiegimo metu Windows sistemoje pažymėkite „Add Python to PATH“
3. Patikrinkite įdiegimą:
   ```bash
   python3 --version
   ```

#### Problema: kelios Python versijos kelia konfliktų
**Simptomai:** Paleidžiama netinkama Python versija, paketai įdiegiami netikroje vietoje

**Sprendimas:**
- **Windows:** naudokite `py -3` vietoje `python`, kad aiškiai paleisti Python 3
- **macOS/Linux:** naudokite `python3` vietoje `python`
- Visada kurkite ir naudokite virtualias aplinkas projektams

#### Problema: nėra pip komandos
**Klaida:** `'pip' nėra atpažinta kaip vidinė ar išorinė komanda`

**Sprendimas:**
1. Pabandykite vietoje `pip` naudoti `pip3`
2. Arba naudokite `python -m pip` arba `python3 -m pip`
3. Įsitikinkite, kad Python yra pridėtas prie PATH (perkurdami Python ir pažymėdami parinktį)

### VS Code ir plėtiniai

#### Problema: neveikia Pylance plėtinys
**Simptomai:** nėra Python IntelliSense, kodo užbaigimo ar tipų tikrinimo

**Sprendimas:**
1. Atidarykite VS Code komandų paletę (`Ctrl+Shift+P` arba `Cmd+Shift+P`)
2. Vykdykite „Python: Select Interpreter“
3. Pasirinkite tinkamą Python interpretatorių (virtualią aplinką, jei naudojate)
4. Perkraukite VS Code langą

#### Problema: VS Code nemato virtualios aplinkos
**Simptomai:** pasirinktas netinkamas Python interpretatorius

**Sprendimas:**
1. Įsitikinkite, kad terminale suaktyvinote virtualią aplinką
2. Atidarykite komandų paletę ir įvykdykite „Python: Select Interpreter“
3. Pasirinkite interpretatorių iš `.venv` aplanko
4. Patikrinkite, ar būsenos juostoje (apatinėje kairėje) rodoma tinkama Python versija

### PlatformIO (Wio Terminal)

#### Problema: nepavyksta įdiegti PlatformIO
**Klaida:** įvairios klaidos įdiegimo metu

**Sprendimas:**
1. Įsitikinkite, kad VS Code yra atnaujintas
2. Pirmiausia įdiekite C/C++ plėtinį
3. Po PlatformIO diegimo perkraukite VS Code
4. Patikrinkite interneto ryšį (PlatformIO atsisiunčia didelius failus)

#### Problema: PlatformIO nemato plokštės
**Simptomai:** negalima įkelti kodo į Wio Terminal

**Sprendimas:**
1. Išbandykite kitą USB laidą (kai kurie laidai tik įkrovimui)
2. Patikrinkite Įrenginių tvarkytuvę (Windows) arba `ls /dev/tty*` (macOS/Linux)
3. Įdiekite arba atnaujinkite USB tvarkykles
4. Išbandykite kitą USB lizdą
5. Du kartus greitai perstumkite Wio Terminal įjungimo jungiklį, kad įeinant į bootloader režimą

#### Problema: PlatformIO kompiliavimo klaidos
**Klaida:** `fatal error: Arduino.h: No such file or directory`

**Sprendimas:**
1. Ištrinkite `.pio` aplanką projekte
2. Vykdykite „PlatformIO: Rebuild“ komandą per komandų paletę
3. Įsitikinkite, kad `platformio.ini` turi teisingą plokštės konfigūraciją:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove bibliotekos

#### Problema: Grove bibliotekos importas nepavyksta Raspberry Pi
**Klaida:** `ModuleNotFoundError: No module named 'grove'`

**Sprendimas:**
1. Perinstaliuokite Grove bibliotekas:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Jei naudojate virtualią aplinką, gali prireikti įdiegti globaliai arba nukopijuoti bibliotekas
3. Įsitikinkite, kad I2C įjungtas: `sudo raspi-config nonint do_i2c 0`

#### Problema: Grove jutiklis neaptinkamas
**Klaida:** `IOError: [Errno 121] Remote I/O error`

**Sprendimas:**
1. Patikrinkite fizinius ryšius (įsitikinkite, kad Grove laidas pilnai įkištas)
2. Įsitikinkite, kad jutiklis prijungtas prie teisingo prievado (analoginio, skaitmeninio, I2C, UART)
3. Vykdykite `i2cdetect -y 1`, kad pamatytumėte ar prietaisas rodomas I2C autobuse
4. Išbandykite kitą Grove laidą
5. Įsitikinkite, kad Grove Base Hat tinkamai sėdi ant Raspberry Pi GPIO jungčių

---

## Techninės įrangos problemos

### Raspberry Pi

#### Problema: Raspberry Pi neužsikrauna
**Simptomai:** nėra vaizdo, LED neveikia arba rodomas vaivorykštės ekranas

**Sprendimas:**
1. **Patikrinkite maitinimą:** naudokite oficialų 5V 3A USB-C maitinimo šaltinį Pi 4 modeliui
2. **SD kortelės problemos:**
   - Performatuokite SD kortelę ir iš naujo įdiekite Raspberry Pi OS
   - Išbandykite kitą SD kortelę (naudokite rekomenduojamas markes)
   - Įsitikinkite, kad SD kortelė tinkamai įstatyta
3. **Patikrinkite HDMI ryšį:** išbandykite abu HDMI lizdus Pi 4, naudokite lizdą arčiau maitinimo

#### Problema: negalima prisijungti prie Raspberry Pi per SSH
**Simptomai:** atmetimas arba laiko limitas

**Sprendimas:**
1. Įjunkite SSH:
   - Naudodami Raspberry Pi Imager, konfigūruokite SSH papildomuose nustatymuose
   - Arba sukurkite tuščią failą pavadinimu `ssh` (be plėtinio) įkrovos skaidinyje
2. Suraskite Pi IP adresą:
   - Patikrinkite maršrutizatoriaus prijungtų įrenginių sąrašą
   - Vykdykite `ping raspberrypi.local` (jei veikia mDNS)
   - Naudokite tinklo skaitymo įrankius, pvz., `nmap` arba Angry IP Scanner
3. Patikrinkite tinklą:
   - Įsitikinkite, kad Pi ir jūsų kompiuteris yra tame pačiame tinkle
   - Išbandykite laidinį ryšį vietoje WiFi
4. Patikrinkite vartotojo vardą ir slaptažodį (numatytasis: vartotojas `pi`, slaptažodis `raspberry`)

#### Problema: Grove Base Hat neatpažįstamas
**Simptomai:** jutikliai neveikia, I2C klaidos

**Sprendimas:**
1. Įsitikinkite, kad Base Hat tinkamai pritvirtintas prie visų GPIO kontaktų
2. Patikrinkite ar nėra sulenktų kontaktų ant Pi arba Base Hat
3. Įjunkite I2C sąsają:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Patikrinkite, ar I2C veikia: `i2cdetect -y 1`

#### Problema: Raspberry Pi veikia lėtai
**Simptomai:** sąsaja stringa, lėtas atsakas

**Sprendimas:**
1. Patikrinkite SD kortelės greitį (naudokite Class 10 ar greitesnę, arba SSD per USB)
2. Atlaisvinkite vietos diske: naudokite `df -h`, ištrinkite nereikalingus failus
3. Sumažinkite GPU atmintį per `raspi-config`, jei nenaudojate daug kameros/vaizdo
4. Uždarykite nereikalingas programas
5. Jei naudojate Pi 3 ar senesnį, apsvarstykite atnaujinimą į Pi 4 su didesne atmintimi

### Wio Terminal

#### Problema: Wio Terminal ekranas lieka tuščias
**Simptomai:** nėra vaizdo po kodo įkėlimo

**Sprendimas:**
1. Patikrinkite, ar kodas inicijuoja ekraną (TFT_eSPI biblioteka)
2. Atnaujinkite Wio Terminal programinę įrangą iš [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Pridėkite ekrano inicijavimo kodą:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Išbandykite pavyzdinį sketch'ą iš PlatformIO, kad patikrintumėte aparatūrą

#### Problema: Wio Terminal neveikia WiFi
**Simptomai:** negalima prisijungti prie WiFi, tinklo klaidos

**Sprendimas:**
1. **Atnaujinkite WiFi programinę įrangą:** vadovaukitės [Wio Terminal WiFi programinės įrangos atnaujinimo gidu](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Patikrinkite WiFi prisijungimo duomenis:** įsitikinkite, kad SSID ir slaptažodis teisingi
3. **WiFi dažnis:** Wio Terminal palaiko tik 2.4GHz WiFi (ne 5GHz)
4. **Signalio stiprumas:** priartinkite prie maršrutizatoriaus
5. **Maršrutizatoriaus nustatymai:** kai kurios įmonių/WPA-Enterprise tinklai gali neveikti

#### Problema: Kompiuteris neaptinka Wio Terminal
**Simptomai:** USB įrenginio nemato

**Sprendimas:**
1. **Išbandykite kitą USB laidą:** naudokite duomenų kabelį, ne tik įkrovimui skirtą
2. **Įjunkite bootloader režimą:** greitai perstumkite maitinimo jungiklį žemyn du kartus
   - Mėlyna LED turėtų pulsoti, įrenginys matomas kaip „Arduino“ Įrenginių tvarkytuvėje
3. **Įdiekite tvarkykles (Windows):**
   - Atsisiųskite ir įdiekite [Seeed USB tvarkyklę](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Pabandykite kitą USB lizdą:** venkite USB šakotuvų, naudokite tiesioginį ryšį
5. **Atnaujinkite sistemos USB tvarkykles**

#### Problema: Wio Terminal jutikliai neveikia
**Simptomai:** Grove jutikliai nepateikia duomenų

**Sprendimas:**
1. Patikrinkite Grove laido jungtis
2. Įsitikinkite, kad naudojate tinkamą Grove prievadą (kairį arba dešinį)
3. Įtraukite tinkamas jutiklio bibliotekas
4. Patikrinkite jutiklio maitinimo reikalavimus
5. Testuokite jutiklį su pavyzdiniu bibliotekos kodu

### Virtualus įrenginys (CounterFit)

#### Problema: negalima paleisti CounterFit programėlės
**Klaida:** įvairios Python klaidos paleidimo metu

**Sprendimas:**
1. Įsitikinkite, kad virtuali aplinka suaktyvinta
2. Įdiekite arba perinstaliuokite CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Patikrinkite, ar prievadas 5000 nėra jau naudojamas:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Nutraukite procesą, naudojantį prievadą 5000 arba naudokite kitą prievadą:
   ```bash
   counterfit --port 5001
   ```

#### Problema: negalima prisijungti prie CounterFit iš kodo
**Klaida:** prisijungimas užblokuotas arba laiko limitas

**Sprendimas:**
1. Patikrinkite, ar CounterFit veikia: atidarykite naršyklę `http://127.0.0.1:5000`
2. Patikrinkite, ar kodo URL atitinka CounterFit adresą
3. Įsitikinkite, kad ugniasienė neužblokuoja ryšio
4. Pabandykite paleisti iš naujo tiek CounterFit programėlę, tiek savo kodą

#### Problema: sensoriai nepasirodo CounterFit
**Simptomai:** sukurti sensoriai nerodomi CounterFit sąsajoje

**Sprendimas:**
1. Sukurkite sensorius CounterFit vartotojo sąsajoje prieš paleidžiant kodą
2. Atnaujinkite naršyklės puslapį
3. Patikrinkite, ar sensoriaus tipas atitinka kodo lūkesčius
4. Išvalykite naršyklės talpyklą

---

## Ryšio problemos

### WiFi ryšys

#### Problema: įrenginys negali prisijungti prie WiFi
**Simptomai:** prisijungimo laiko limitas, autentifikacijos klaida

**Sprendimas:**
1. **Patikrinkite SSID ir slaptažodį:** įsitikinkite, kad prisijungimo duomenys teisingi
2. **WiFi dažnis:** dauguma IoT įrenginių palaiko tik 2.4GHz (ne 5GHz)
3. **Maršrutizatoriaus nustatymai:**
   - Jei įjungta, išjunkite AP izoliuotumą
   - Naudokite WPA2-PSK saugumą (venkite WPA3, WEP ar atvirų tinklų)
   - Įsitikinkite, kad DHCP įjungtas
4. **Paslėpti tinklai:** jei SSID paslėptas, gali reikėti jį aiškiai sukonfigūruoti
5. **Signalo stiprumas:** priartinkite įrenginį prie maršrutizatoriaus
6. **Trukdžiai:** kiti įrenginiai, mikrobangų krosnelės ar sienos gali trukdyti

#### Problema: WiFi ryšys dažnai nutrūksta
**Simptomai:** nepastovus ryšys

**Sprendimas:**
1. Patikrinkite maršrutizatoriaus stabilumą, apsvarstykite perkrovimą
2. Atnaujinkite įrenginio programinę įrangą
3. Naudokite statinį IP vietoje DHCP
4. Sumažinkite atstumą iki maršrutizatoriaus arba įdiekite WiFi kartotuvą
5. Patikrinkite trukdžius iš kitų įrenginių
6. Įsitikinkite, kad maitinimas tinkamas (ypač Raspberry Pi)

### Debesų paslaugos

#### Problema: negalima prisijungti prie Azure IoT Hub
**Klaida:** autentifikacija nepavyko, prisijungimas atmestas

**Sprendimas:**
1. **Patikrinkite prisijungimo duomenis:**
   - Įsitikinkite, kad prisijungimo eilutė teisinga
   - Įsitikinkite, kad nėra papildomų tarpų ar eilučių pertraukų prisijungimo eilutėje
2. **Patikrinkite įrenginio registraciją:** įrenginys turi būti užregistruotas IoT Hub
3. **Ugniasienė/proxy:** įsitikinkite, kad išeinantis MQTT (prievadas 8883) arba HTTPS (prievadas 443) ryšys leidžiamas
4. **IoT Hub regionas:** įsitikinkite, kad IoT Hub veikia ir nėra kitame regione, kuris gali sukelti vėlavimus
5. **Kvotų ribos:** patikrinkite, ar nemokamo plano apribojimai neviršyti
6. **Patikrinkite ryšį:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problema: Azure Functions nesugeba paleisti funkcijos
**Simptomai:** žinutės siunčiamos, bet funkcija neįvykdoma

**Sprendimas:**
1. Patikrinkite, ar Function App veikia (nenustatyta sustabdyta)
2. Patikrinkite prisijungimo eilutę Function App nustatymuose
3. Peržiūrėkite funkcijų žurnalus Azure portale
4. Įsitikinkite, kad Event Hub suderinamas galutinis taškas yra teisingai sukonfigūruotas
5. Patikrinkite, ar žinutės formatas atitinka funkcijos lūkesčius
6. Patikrinkite Function App paslaugų planą (vartojimo arba dedikuotą)

### MQTT
#### Problema: MQTT ryšys nepavyksta
**Klaida:** Prisijungimas atmestas, autentifikacija nepavyko

**Sprendimas:**
1. **Brokerio adresas:** Patikrinkite, ar brokerio URL/IP yra teisingas
2. **Prievadas:** Patikrinkite prievado numerį (1883 šifravimui nešifruotam, 8883 TLS)
3. **Autentifikacija:** Patikrinkite vartotojo vardą/slaptažodį, jei reikia
4. **TLS/SSL:** Įsitikinkite, kad sertifikatai yra galiojantys ir patikimi
5. **Ugnies siena:** Patikrinkite, ar prievadas nėra užblokuotas
6. **Bandymas su MQTT klientu:** Naudokite MQTT Explorer arba mosquitto_pub/sub bandymams

#### Problema: MQTT žinutės negaunamos
**Simptomai:** Žinutės paskelbtos, bet prenumeratoriai jų negauna

**Sprendimas:**
1. **Temų pavadinimai:** Patikrinkite, ar prenumeratoriaus tema tiksliai atitinka leidėjo temą
2. **QoS lygis:** Pabandykite QoS 1 arba 2 vietoje 0
3. **Džokeriai:** Patikrinkite, ar temų džokeriai naudojami teisingai (`+` vienam lygiui, `#` daugeliui lygių)
4. **Laikomos žinutės:** Leidėjas gali nustatyti išlaikymo žymą, kad išlaikytų paskutinę žinutę
5. **Ryšio laikas:** Įsitikinkite, kad prenumeratorius prisijungia prieš paskelbiant žinutes

---

## Jutiklių ir veiksmų įrenginių problemos

### Grove jutikliai

#### Problema: Jutiklis grąžina neteisingas reikšmes
**Simptomai:** Skaitymai yra 0, -1 ar nesąmoningi

**Sprendimas:**
1. **Patikrinkite jungtis:** Įsitikinkite, kad jutiklis tinkamai prijungtas
2. **Tinkamas prievadas:** Patikrinkite, ar jutiklis prijungtas prie tinkamo prievado tipo:
   - Analoginiai jutikliai → Analoginiai prievadai (A0, A2, A4)
   - Skaitmeniniai jutikliai → Skaitmeniniai prievadai (D5, D16, D18 ir kt.)
   - I2C jutikliai → I2C prievadai
3. **Kalibracija:** Kai kurie jutikliai reikalinga kalibracija (dirvožemio drėgmės, šviesos)
4. **Perkrovimas:** Atjunkite ir vėl prijunkite jutiklį
5. **Jutiklio dokumentacija:** Patikrinkite jutiklio specifikacijas ir reikalavimus

#### Problema: Kapacinis dirvožemio drėgmės jutiklis visada rodo drėgną
**Simptomai:** Jutiklis rodo didelę drėgmę net kai yra sausas

**Sprendimas:**
1. **Reikia kalibracijos:** Dirvožemio jutikliams reikalinga kalibracija:
   - Nuskaitomas reikšmė ore (sausas pagrindas)
   - Nuskaitomas reikšmė vandenyje (drėgnas pagrindas)
   - Skaitymai priskiriami tarp šių verčių
2. **Patikrinkite jutiklio dangą:** Drėgmės jutikliai gali gesti, jei danga pažeista
3. **Vieta:** Įsitikinkite, kad jutiklis visiškai įstatytas į dirvą

#### Problema: Temperatūros/drėgmės jutiklio skaitymai netikslūs
**Simptomai:** DHT11/DHT22 rodo neteisingą temperatūrą ar drėgmę

**Sprendimas:**
1. **Jutiklio padėtis:** Venkite tiesioginių saulės spindulių, šilumos šaltinių ar oro srauto
2. **Įšilimo laikas:** Leiskite jutikliui 2 sekundes įšilti po įjungimo prieš skaitymą
3. **Skaitymo dažnis:** DHT jutikliams reikia laiko tarp skaitymų (bent 2 sekundės)
4. **Patikrinkite kondensaciją:** Gali paveikti skaitymus
5. **Jutiklio kokybė:** DHT11 mažiau tikslus nei DHT22

### Kamera

#### Problema: Kamera nerandama Raspberry Pi
**Klaida:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Sprendimas:**
1. **Įjunkite kameros sąsają:**
   ```bash
   sudo raspi-config
   ```
   Eikite į Interface Options → Camera → Enable
2. **Patikrinkite plokščią kabelį:** Įsitikinkite, kad kameros kabelis tinkamai įdėtas
   - Mėlyna pusė žiūri į USB prievadus ant Pi Zero
   - Mėlyna pusė žiūri nuo USB prievadų ant Pi 4
3. **Atnaujinkite programinę įrangą:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Išbandykite kamerą:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problema: Kameros nuotraukos prastos kokybės
**Simptomai:** Neryškios, tamsios arba išplautos nuotraukos

**Sprendimas:**
1. **Fokusas:** Nuimkite apsauginę plėvelę nuo objektyvo, reguliuokite fokusą jei įmanoma
2. **Apšvietimas:** Užtikrinkite pakankamą apšvietimą
3. **Kameros nustatymai:** Reguliuokite ekspoziciją, ISO, baltos spalvos balansą programoje
4. **Stabilumas:** Laikykite kamerą stabiliai, naudokite trikojį jei reikia
5. **Rezoliucija:** Nepersijunkite į aukštesnę negu kameros maksimalus rezoliucijos lygį

### Mikrofonas ir garsiakalbis

#### Problema: Garsas neveikia įvesti/išvesti
**Simptomai:** Mikrofonas neregiistruoja, garsiakalbis negarsina

**Sprendimas:**
1. **Patikrinkite jungtis:** Įsitikinkite, kad garso įrenginiai tinkamai prijungti
2. **Bandykite aparatūrą:**
   - Garsiakalbis: `speaker-test -t wav -c 2`
   - Mikrofonas: `arecord -l` sąrašui, `arecord test.wav` įrašymui
3. **Garso nustatymai:** Patikrinkite ir reguliuokite garsumą:
   ```bash
   alsamixer
   ```
4. **Pasirinkite garso įrenginį:** Nustatykite tinkamą garso įrenginį programoje
5. **Tvarkyklių problemos:** Atnaujinkite ALSA arba perinstaliuokite garso tvarkykles

#### Problema: ReSpeaker hat neveikia
**Simptomai:** Garso įrenginys nerandamas

**Sprendimas:**
1. **Įdiekite tvarkykles:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Patikrinkite įdiegimą:** `arecord -l` turėtų rodyti ReSpeaker
3. **Atnaujinkite programinę įrangą:** Kai kurios Pi OS versijos reikalauja tvarkyklių atnaujinimų
4. **Patikrinkite tvirtumą:** Įsitikinkite, kad hat yra tinkamai prijungtas prie GPIO

---

## Kūrimo aplinkos problemos

### VS Code

#### Problema: Terminalas automatiškai neaktyvuoja virtualios aplinkos
**Simptomai:** Terminalas atsidaro, bet venv neaktyvuotas

**Sprendimas:**
1. **Nustatykite Python interpretatorių:** Command Palette → "Python: Select Interpreter" → Pasirinkite venv
2. **Perkraukite VS Code** po interpretatoriaus pasirinkimo
3. **Patikrinkite nustatymus:** Pridėkite į `settings.json`:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problema: Kodo aplinkoje nepaleidžiamas įrenginyje
**Simptomai:** Kodas paleidžiamas, bet įrenginys nereaguoja

**Sprendimas:**
1. **Įsitikinkite, kad kodas išsaugotas** (patikrinkite tašką ant failo skirtuko)
2. **Patikrinkite, kuri Python versija veikia:** `which python` arba `where python`
3. **Wio Terminal naudojimas:** Įkelkite kodą per PlatformIO (spauskite įkėlimo mygtuką)
4. **Raspberry Pi:** Prisijunkite per SSH į Pi ir paleiskite kodą ten
5. **Patikrinkite išvesties langą** dėl klaidų

#### Problema: IntelliSense nerodo bibliotekų funkcijų
**Simptomai:** Nėra automatinio užbaigimo importuotoms modulėms

**Sprendimas:**
1. Įsitikinkite, kad biblioteka įdiegta dabartinėje aplinkoje
2. Perkraukite VS Code langą
3. Patikrinkite, ar teisingas Python interpretatorius
4. Įdiekite tipų aprašų paketus jei yra: `pip install types-<library-name>`

### Python virtualios aplinkos

#### Problema: Nepavyksta sukurti virtualios aplinkos
**Klaida:** `The virtual environment was not created successfully`

**Sprendimas:**
1. **Įdiekite venv modulį:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Tai turėtų būti įtraukta į Python
   - Windows: Perinstaliuokite Python su visais komponentais
2. **Patikrinkite Python diegimą:** Įsitikinkite, kad Python yra tinkamai įdiegtas
3. **Naudokite pilną kelią:** Išbandykite `python3 -m venv .venv` su aiškiu python3 kvietimu

#### Problema: Paketai įdiegti netinkamoje vietoje
**Simptomai:** Importavimo klaida po paketo įdiegimo

**Sprendimas:**
1. **Įsitikinkite, kad venv yra aktyvuota:** Komandinė eilutė turi rodyti `(.venv)`
2. **Patikrinkite pip vietą:** `which pip` turėtų rodyti `.venv/bin/pip`
3. **Perinstaliuokite venv aplinkoje:** Aktyvuokite venv, tada `pip install <package>`
4. **Nenaudokite sudo su pip** virtualioje aplinkoje

#### Problema: Virtuali aplinka neperkeliamas
**Simptomai:** Venv neveikia po perkelimo arba kitame kompiuteryje

**Sprendimas:**
1. **Nekelkite venv aplinkų:** Ištrinkite ir sukurkite iš naujo naujoje vietoje
2. **Naudokite requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Sukurkite venv iš naujo:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # arba activate.bat Windows operacinėje sistemoje
   pip install -r requirements.txt
   ```

### Priklausomybės

#### Problema: Paketo diegimas nepavyksta
**Klaida:** Įvairios pip klaidos diegimo metu

**Sprendimas:**
1. **Atnaujinkite pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Įdiekite kūrimo įrankius:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Įdiekite Visual Studio Build Tools
3. **Patikrinkite interneto ryšį**
4. **Išbandykite kitą paketo indeksą:** `pip install --index-url https://pypi.org/simple/ <package>`
5. **Įdiekite konkrečią versiją:** `pip install <package>==<version>`

#### Problema: Priklausomybių konfliktai
**Klaida:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Sprendimas:**
1. **Naudokite naują virtualią aplinką** kiekvienam projektui
2. **Atnaujinkite paketus:** `pip install --upgrade <package>`
3. **Patikrinkite priklausomybes:** Naudokite `pip check` konfliktams rasti
4. **Įdiekite suderinamas versijas:** Nurodykite versijų ribas requirements.txt

---

## Veikimo problemos

### Problema: Kodas veikia lėtai
**Simptomai:** Užlaikymas, laiko praleidimai, nereaguojantis elgesys

**Sprendimas:**
1. **Sumažinkite jutiklių skaitymo dažnį:** Neskaitykite jutiklių per dažnai
2. **Optimizuokite ciklus:** Venkite užimtumo laukimo, naudokite sleep() arba uždelsimus
3. **Atminties problemos:**
   - Uždarykite nereikalingas programas
   - Atlaisvinkite saugojimo vietą
   - Stebėkite su `top` arba `htop` ant Pi
4. **SD kortelės greitis:** Naudokite greitesnę SD kortelę arba SSD Raspberry Pi
5. **Tinklo atsilikimai:** Naudokite asinchroninius veiksmus tinklo skambučiams

### Problema: Trūksta atminties klaidos
**Klaida:** `MemoryError` arba sistemos užšalimas

**Sprendimas:**
1. **Raspberry Pi atveju:**
   - Uždarykite nereikalingas programas
   - Padidinkite mainų (swap) vietą
   - Naudokite lengvesnę OS (Lite versiją)
   - Atnaujinkite RAM (Pi 4 turi 2/4/8GB variantus)
2. **Wio Terminal:**
   - Mažinkite buferių dydžius
   - Naudokite mažesnes nuotraukas
   - Optimizuokite tekstų naudojimą
   - Patikrinkite atminties nutekėjimą (neatlaisvintos atminties)

### Problema: Duomenų praradimas arba sugadinimas
**Simptomai:** Trūksta žinučių, sugadinti failai

**Sprendimas:**
1. **SD kortelės problemos:**
   - Naudokite kokybiškas SD korteles (venkite pigias/padlapiuotas)
   - Reguliarios atsarginės kopijos
   - Tvarkingas išjungimas (nenutraukite maitinimo)
2. **Buferio perpildymas:** Padidinkite buferio dydžius kode
3. **Tinklo patikimumas:** Įgyvendinkite pakartojimo logiką ir klaidų apdorojimą
4. **Paslaugų kokybė:** Naudokite MQTT QoS 1 arba 2 svarbioms žinutėms

---

## Dažniausios klaidų žinutės

### `ModuleNotFoundError: No module named 'X'`
**Priežastis:** Paketas neįdiegtas arba virtuali aplinka neaktyvuota

**Sprendimas:**
```bash
pip install X
```
Pirmiausia įsitikinkite, kad virtuali aplinka aktyvuota.

### `Permission denied` Linux/macOS
**Priežastis:** Reikia aukštesnių teisių arba failų leidimų problema

**Sprendimas:**
- Sistemos operacijoms: naudokite `sudo`
- Pip: NESINAUDOKITE sudo su venv, pirmiausia aktyvinkite venv
- Serijiniam prievadui: pridėkite vartotoją į dialout grupę: `sudo usermod -a -G dialout $USER`, po to atsijunkite/prisijunkite iš naujo

### `OSError: [Errno 98] Address already in use`
**Priežastis:** Prievadas jau naudojamas kitų procesų

**Sprendimas:**
1. Suraskite procesą, naudojantį prievadą: `lsof -i :<port>` arba `netstat -ano | findstr :<port>`
2. Nutraukite procesą arba naudokite kitą prievadą savo kode

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Priežastis:** SSL sertifikato patvirtinimas nepavyko

**Sprendimas:**
1. Atnaujinkite sertifikatus: `pip install --upgrade certifi`
2. Patikrinkite, ar sistemos laikas teisingas: `date`
3. Tik kūrimui (ne gamybai): išjunkite patvirtinimą kode

### `IndentationError: unexpected indent`
**Priežastis:** Python įtraukimo klaidos (mišinys tabuliavimo ir tarpų)

**Sprendimas:**
1. Naudokite nuoseklų įtraukimą (4 tarpai yra Python standartas)
2. Konfigūruokite redaktorių naudoti tarpus vietoje tabuliavimo
3. VS Code: Nustatykite `"editor.insertSpaces": true` ir `"editor.tabSize": 4`

### `UnicodeDecodeError` arba `UnicodeEncodeError`
**Priežastis:** Simbolių kodavimo problemos

**Sprendimas:**
```python
# Kai skaitomi failai
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Kai rašomi failai
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Pagalbos gavimas

Jei išbandėte šiuos trikčių šalinimo veiksmus ir vis dar turite problemų:

### 1. Patikrinkite esamus išteklius
- **Dokumentacija:** Peržiūrėkite [README](README.md) ir pamokos instrukcijas
- **Aparatūros vadovai:** Patikrinkite [hardware.md](hardware.md) dėl specifinės aparatūros informacijos
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) Grove komponentams

### 2. Ieškokite panašių problemų
- **GitHub Issues:** Ieškokite [esamų problemų](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Ieškokite klaidų žinučių
- **Įrenginių forumai:** Patikrinkite Raspberry Pi arba Arduino forumus

### 3. Sukurkite GitHub problemą (issue)
Jei negalite rasti sprendimo:
1. Eikite į [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Spauskite „New Issue“
3. Nurodykite:
   - Aiškų problemos aprašymą
   - Veiksmus, kaip problemą atkartoja
   - Klaidos pranešimus (pilnas tekstas)
   - Aparatūros/programinės įrangos versijas
   - Ką jau bandėte
   - Jei įmanoma, ekrano kopijas

### 4. Prisijunkite prie bendruomenės
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Pateikite gerus klaidų pranešimus
Geras klaidų pranešimas apima:
- **Aplinka:** OS, Python versija, naudojama įranga
- **Veiksmai reprodukcijai:** Tikslios problemą sukeliančios veiksmų eilės
- **Laukiama elgsena:** Kas turėtų įvykti
- **Faktinė elgsena:** Kas iš tikrųjų vyksta
- **Klaidos pranešimai:** Pilnas klaidos tekstas, ne ekrano nuotraukos
- **Kodas:** Minimalus kodo pavyzdys, kuris atkuria problemą

---

## Patarimai prevencijai

### Bendrosios geros praktikos
1. **Laikykite atsargines kopijas:** Reguliarios veikiančių SD kortelių/kodo atsarginės kopijos
2. **Dokumentuokite pakeitimus:** Užfiksuokite komentarais, kas veikia
3. **Versijų kontrolė:** Naudokite git kode pokyčių sekimui
4. **Testuokite palaipsniui:** Išbandykite smulkius pakeitimus prieš juos apjungiant
5. **Skaitykite klaidos pranešimus:** Dažnai jie tiksliai nurodo, kas negerai
6. **Reguliariai atnaujinkite:** Laikykite programinę įrangą/firmware atnaujintą
7. **Naudokite kokybiškas dalis:** Venkite pigių kabelių/maitinimo šaltinių
8. **Stabilus maitinimas:** Naudokite tinkamą maitinimo šaltinį (ypač Pi)

### Kūrimo darbo eiga
1. **Pradėkite paprastai:** Pradėkite nuo veikiančio pavyzdinio kodo
2. **Vienas pakeitimas vienu metu:** Lengviau rasti, kas sukelia klaidą
3. **Dažnai testuokite:** Anksti pastebėkite problemas
4. **Laikykite tvarką:** Logiškai organizuokite failus ir kodą
5. **Komentuokite kodą:** Ateities Jūs tai įvertinsite

---

*Ši trikčių šalinimo vadovė yra bendruomenės prižiūrima. Jei radote sprendimą problemai, kurios čia nėra, prašome apsvarstyti galimybę [prisidėti](CONTRIBUTING.md), kad padėtumėte kitiems!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Atsakomybės apribojimas**:
Šis dokumentas buvo išverstas naudojant dirbtinio intelekto vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors stengiamės užtikrinti tikslumą, atkreipkite dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas gimtąja kalba turėtų būti laikomas pagrindiniu ir autoritetingu šaltiniu. Svarbiai informacijai rekomenduojamas profesionalus vertimas žmogiškuoju būdu. Mes neatsakome už bet kokius nesusipratimus ar klaidingą interpretavimą, kilusį dėl šio vertimo naudojimo.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->