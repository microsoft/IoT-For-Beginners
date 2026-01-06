<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T15:58:54+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "sk"
}
-->
# Sprievodca riešením problémov

Tento sprievodca vám pomôže vyriešiť bežné problémy pri práci s učebnicou IoT pre začiatočníkov. Problémy sú zorganizované podľa kategórií pre jednoduchú navigáciu.

## Obsah

- [Problémy s inštaláciou](../..)
  - [Inštalácia Pythonu](../..)
  - [VS Code a rozšírenia](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Knižnice Grove](../..)
- [Problémy so hardvérom](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuálne zariadenie (CounterFit)](../..)
- [Problémy s konektivitou](../..)
  - [WiFi pripojenie](../..)
  - [Cloudové služby](../..)
  - [MQTT](../..)
- [Problémy s čidlami a aktuatormi](../..)
  - [Grove senzory](../..)
  - [Kamera](../..)
  - [Mikrofón a reproduktor](../..)
- [Problémy s vývojovým prostredím](../..)
  - [VS Code](../..)
  - [Virtuálne prostredia Pythonu](../..)
  - [Závislosti](../..)
- [Problémy s výkonom](../..)
- [Bežné chybové hlásenia](../..)
- [Ako získať pomoc](../..)

---

## Problémy s inštaláciou

### Inštalácia Pythonu

#### Problém: Verzia Pythonu je príliš zastaralá
**Chyba:** `Python 3.6 alebo vyšší je potrebný`

**Riešenie:**
1. Stiahnite si najnovší Python 3 z [python.org](https://www.python.org/downloads/)
2. Počas inštalácie vo Windows zaškrtnite možnosť "Add Python to PATH"
3. Overte inštaláciu:
   ```bash
   python3 --version
   ```

#### Problém: Viaceré verzie Pythonu spôsobujú konflikty
**Príznaky:** Spúšťa sa nesprávna verzia Pythonu, balíky sa inštalujú na nesprávne miesto

**Riešenie:**
- **Windows:** Použite `py -3` namiesto `python` pre explicitné spustenie Pythonu 3
- **macOS/Linux:** Použite `python3` namiesto `python`
- Vždy vytvárajte a používajte virtuálne prostredia pre projekty

#### Problém: neznámy príkaz pip
**Chyba:** `'pip' nie je rozpoznaný ako interný alebo externý príkaz`

**Riešenie:**
1. Skúste `pip3` namiesto `pip`
2. Alebo použite `python -m pip` alebo `python3 -m pip`
3. Skontrolujte, či je Python pridaný do PATH (preinštalujte Python a zaškrtnite túto možnosť)

### VS Code a rozšírenia

#### Problém: Rozšírenie Pylance nefunguje
**Príznaky:** Žiadny IntelliSense pre Python, automatické dopĺňanie kódu ani kontrola typov

**Riešenie:**
1. Otvorte príkazový riadok VS Code (`Ctrl+Shift+P` alebo `Cmd+Shift+P`)
2. Spustite "Python: Select Interpreter"
3. Vyberte správny Python interpreter (virtuálne prostredie, ak používate)
4. Znovu načítajte okno VS Code

#### Problém: VS Code nevidí virtuálne prostredie
**Príznaky:** Vybraný nesprávny Python interpreter

**Riešenie:**
1. Uistite sa, že ste aktivovali virtuálne prostredie v termináli
2. Otvorte príkazový riadok a spustite "Python: Select Interpreter"
3. Vyberte interpreter z priečinka `.venv`
4. Skontrolujte, či stavový riadok (vľavo dole) zobrazuje správnu verziu Pythonu

### PlatformIO (Wio Terminal)

#### Problém: Inštalácia PlatformIO zlyháva
**Chyba:** Rôzne chyby počas inštalácie PlatformIO

**Riešenie:**
1. Uistite sa, že VS Code je aktuálne
2. Najskôr nainštalujte rozšírenie C/C++
3. Po inštalácii PlatformIO reštartujte VS Code
4. Skontrolujte internetové pripojenie (PlatformIO sťahuje veľké súbory)

#### Problém: PlatformIO nerozpozná dosku
**Príznaky:** Nie je možné nahrať kód do Wio Terminalu

**Riešenie:**
1. Skúste iný USB kábel (niektoré káble sú len na nabíjanie)
2. Skontrolujte Správcu zariadení (Windows) alebo `ls /dev/tty*` (macOS/Linux)
3. Nainštalujte alebo aktualizujte USB ovládače
4. Skúste iný USB port
5. Na Wio Terminale rýchlo dvakrát posuňte vypínač napájania do polohy Bootloaderu

#### Problém: Chyby kompilácie v PlatformIO
**Chyba:** `fatal error: Arduino.h: No such file or directory`

**Riešenie:**
1. Odstráňte priečinok `.pio` vo vašom projekte
2. Spustite "PlatformIO: Rebuild" z príkazového riadku
3. Uistite sa, že v `platformio.ini` je správna konfigurácia dosky:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Knižnice Grove

#### Problém: Import knižnice Grove zlyháva na Raspberry Pi
**Chyba:** `ModuleNotFoundError: No module named 'grove'`

**Riešenie:**
1. Preinštalujte knižnice Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Ak používate virtuálne prostredie, možno budete musieť knižnice nainštalovať globálne alebo skopírovať
3. Overte, či je povolený I2C: `sudo raspi-config nonint do_i2c 0`

#### Problém: Grove senzor sa nezistí
**Chyba:** `IOError: [Errno 121] Remote I/O error`

**Riešenie:**
1. Skontrolujte fyzické pripojenia (ujistite sa, že je Grove kábel plne zasunutý)
2. Overte, či je senzor pripojený do správneho portu (analógový, digitálny, I2C, UART)
3. Spustite `i2cdetect -y 1` a zistite, či sa zariadenie zobrazuje na I2C zbernici
4. Skúste iný Grove kábel
5. Uistite sa, že Grove Base Hat je správne osadený na pinoch GPIO Raspberry Pi

---

## Problémy so hardvérom

### Raspberry Pi

#### Problém: Raspberry Pi sa nezapína
**Príznaky:** Žiadny obraz, žiadna aktivita LED alebo dúhová obrazovka

**Riešenie:**
1. **Skontrolujte napájanie:** Použite oficiálny napájací zdroj 5V 3A USB-C pre Pi 4
2. **Problémy so SD kartou:**
   - Preformátujte SD kartu a znova nainštalujte Raspberry Pi OS
   - Vyskúšajte inú SD kartu (použite odporúčané značky)
   - Uistite sa, že SD karta je správne zasunutá
3. **Skontrolujte HDMI pripojenie:** Vyskúšajte oba HDMI porty na Pi 4, používajte port bližšie k napájaniu

#### Problém: Nie je možné sa pripojiť cez SSH na Raspberry Pi
**Príznaky:** Pripojenie odmietnuté alebo vypršal časový limit

**Riešenie:**
1. Povoliť SSH:
   - Pri vypaľovaní SD karty pomocou Raspberry Pi Imageru nakonfigurujte SSH v rozšírených nastaveniach
   - Alebo vytvorte prázdny súbor s názvom `ssh` (bez prípony) v bootovacom oddiele
2. Zistite IP adresu Pi:
   - Skontrolujte zariadenia pripojené k vášmu routeru
   - Použite `ping raspberrypi.local` (ak funguje mDNS)
   - Použite nástroje na skenovanie siete ako `nmap` alebo Angry IP Scanner
3. Skontrolujte sieť:
   - Uistite sa, že Pi je v rovnakej sieti ako váš počítač
   - Vyskúšajte ethernetové pripojenie namiesto WiFi
4. Overte prihlasovacie údaje (predvolené: používateľ `pi`, heslo `raspberry`)

#### Problém: Grove Base Hat nie je rozpoznaný
**Príznaky:** Senzory nefungujú, chyby I2C

**Riešenie:**
1. Uistite sa, že Base Hat je správne nasadený na všetky piny GPIO
2. Skontrolujte, či nie sú ohnuté piny na Pi alebo Base Hat
3. Povoliť rozhranie I2C:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Overte, či I2C funguje: `i2cdetect -y 1`

#### Problém: Raspberry Pi beží pomaly
**Príznaky:** Zasekávanie používateľského rozhrania, pomalá odozva

**Riešenie:**
1. Skontrolujte rýchlosť SD karty (použite triedu 10 alebo lepšiu, alebo SSD cez USB)
2. Uvoľnite miesto na disku: `df -h` na kontrolu, odstráňte nepotrebné súbory
3. Znížte pamäť GPU v `raspi-config`, ak kameru/displej nepoužívate intenzívne
4. Zatvorte nepotrebné aplikácie
5. Zvážte upgrade na Pi 4 s väčšou RAM, ak používate Pi 3 alebo starší model

### Wio Terminal

#### Problém: Obrazovka Wio Terminal zostáva prázdna
**Príznaky:** Žiadny výstup na obrazovku po nahraní kódu

**Riešenie:**
1. Skontrolujte, či kód inicializuje displej (knižnica TFT_eSPI)
2. Aktualizujte firmware Wio Terminal z [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Pridajte kód pre inicializáciu displeja:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Vyskúšajte nahrať ukážkový príklad z PlatformIO na test hardvéru

#### Problém: WiFi na Wio Terminal nefunguje
**Príznaky:** Neda sa pripojiť k WiFi, sieťové chyby

**Riešenie:**
1. **Aktualizujte WiFi firmware:** Postupujte podľa [návodu na aktualizáciu WiFi firmvéru Wio Terminalu](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Skontrolujte prihlasovacie údaje WiFi:** Uistite sa, že SSID a heslo sú správne
3. **WiFi pásmo:** Wio Terminal podporuje len 2,4 GHz WiFi (nie 5 GHz)
4. **Sila signálu:** Presuňte sa bližšie k routeru
5. **Nastavenia routera:** Niektoré podnikové siete / WPA-Enterprise nemusia fungovať

#### Problém: Počítač nerozpozná Wio Terminal
**Príznaky:** USB zariadenie nie je rozpoznané

**Riešenie:**
1. **Skúste iný USB kábel:** Použite dátový kábel, nie len kábel na nabíjanie
2. **Vstúpte do bootloader módu:** Rýchlo dvakrát posuňte vypínač napájania nadol
   - Modrá LED bude pulzovať, zariadenie sa zobrazí ako "Arduino" v Správcovi zariadení
3. **Nainštalujte ovládače (Windows):**
   - Stiahnite a nainštalujte [Seeed USB ovládač](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Skúste iný USB port:** Vyhnite sa USB hubom, použite priame pripojenie
5. **Aktualizujte systémové USB ovládače**

#### Problém: Senzory na Wio Terminal nefungujú
**Príznaky:** Grove senzory nečítajú dáta

**Riešenie:**
1. Skontrolujte pripojenia Grove káblov
2. Overte, či používate správny Grove port (ľavý alebo pravý)
3. Zahrňte do kódu správne knižnice pre senzor
4. Skontrolujte požiadavky senzora na napájanie
5. Otestujte senzor pomocou ukážkového kódu z knižnice

### Virtuálne zariadenie (CounterFit)

#### Problém: Aplikácia CounterFit sa nespustí
**Chyba:** Rôzne chyby Pythonu pri spustení CounterFit

**Riešenie:**
1. Uistite sa, že virtuálne prostredie je aktivované
2. Nainštalujte/preinštalujte CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Skontrolujte, či port 5000 nie je už obsadený:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Ukončite proces používajúci port 5000 alebo použiť iný port:
   ```bash
   counterfit --port 5001
   ```

#### Problém: Nie je možné sa pripojiť ku CounterFit z kódu
**Chyba:** Pripojenie odmietnuté alebo časový limit

**Riešenie:**
1. Overte, či CounterFit beží: Otvorte prehliadač na `http://127.0.0.1:5000`
2. Skontrolujte, či URL pripojenia v kóde zodpovedá adrese CounterFit
3. Uistite sa, že firewall neblokuje pripojenie
4. Skúste reštartovať ako CounterFit aplikáciu, tak váš kód

#### Problém: Senzory sa neobjavujú v CounterFit
**Príznaky:** Vytvorené senzory sa nezobrazujú v používateľskom rozhraní CounterFit

**Riešenie:**
1. Vytvorte senzory v používateľskom rozhraní CounterFit pred spustením kódu
2. Obnovte stránku v prehliadači
3. Skontrolujte, či typ senzora zodpovedá tomu, ktorý očakáva kód
4. Vymažte cache prehliadača

---

## Problémy s konektivitou

### WiFi pripojenie

#### Problém: Zariadenie sa nemôže pripojiť k WiFi
**Príznaky:** Vypršal časový limit pripojenia, overovanie neúspešné

**Riešenie:**
1. **Skontrolujte SSID a heslo:** Overte správnosť prihlasovacích údajov
2. **WiFi pásmo:** Väčšina IoT zariadení podporuje iba 2,4 GHz (nie 5 GHz)
3. **Nastavenie routera:**
   - Zakážte izoláciu AP, ak je zapnutá
   - Použite zabezpečenie WPA2-PSK (vyhnite sa WPA3, WEP alebo otvoreným sieťam)
   - Uistite sa, že DHCP je povolené
4. **Skryté siete:** Ak je SSID skryté, môže byť potrebné ho explicitne nakonfigurovať
5. **Sila signálu:** Presuňte zariadenie bližšie k routeru
6. **Rušenie:** Iné zariadenia, mikrovlnné rúry alebo steny môžu rušiť signál

#### Problém: WiFi pripojenie často vypadáva
**Príznaky:** Pripájanie sa prerušuje

**Riešenie:**
1. Skontrolujte stabilitu routera a zvážte jeho reštart
2. Aktualizujte firmware zariadenia
3. Použite statickú IP adresu namiesto DHCP
4. Znížte vzdialenosť k routeru alebo pridajte WiFi extender
5. Skontrolujte rušenie z iných zariadení
6. Overte, či je napájanie dostatočné (najmä pre Raspberry Pi)

### Cloudové služby

#### Problém: Nie je možné sa pripojiť k Azure IoT Hub
**Chyba:** Overenie zlyhalo, pripojenie odmietnuté

**Riešenie:**
1. **Overte prihlasovacie údaje:**
   - Skontrolujte správnosť connection stringu
   - Uistite sa, že connection string neobsahuje medzery alebo zalomenia riadkov
2. **Skontrolujte registráciu zariadenia:** Zariadenie musí byť zaregistrované v IoT Hub
3. **Firewall/proxy:** Povoliť odchádzajúce spojenia MQTT (port 8883) alebo HTTPS (port 443)
4. **Región IoT Hubu:** Uistite sa, že IoT Hub beží a nie je v inom regióne spôsobujúcom latenciu
5. **Limity kvót:** Skontrolujte, či neprekračujete limity bezplatnej úrovne
6. **Otestujte pripojenie:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problém: Azure Functions sa nespúšťajú
**Príznaky:** Správy sa posielajú, ale funkcia sa nevyvoláva

**Riešenie:**
1. Skontrolujte, či je Function App spustená (nie zastavená)
2. Overte connection string v nastaveniach Function App
3. Skontrolujte logy funkcií v Azure Portáli
4. Uistite sa, že je správne nakonfigurovaný kompatibilný koncový bod Event Hubu
5. Overte, či formát správy zodpovedá očakávaniam funkcie
6. Skontrolujte plán služby Function App (spotreba vs. dedikovaný)

### MQTT
#### Problém: Pripojenie MQTT zlyhalo  
**Chyba:** Pripojenie odmietnuté, autentifikácia zlyhala

**Riešenie:**  
1. **Adresa brokera:** Overte, či je URL/IP brokera správna  
2. **Port:** Skontrolujte číslo portu (1883 pre nešifrované, 8883 pre TLS)  
3. **Autentifikácia:** Overte užívateľské meno/heslo, ak je potrebné  
4. **TLS/SSL:** Uistite sa, že certifikáty sú platné a dôveryhodné  
5. **Firewall:** Skontrolujte, či port nie je blokovaný  
6. **Test pomocou MQTT klienta:** Použite MQTT Explorer alebo mosquitto_pub/sub na testovanie

#### Problém: Správy MQTT nie sú prijímané  
**Príznaky:** Správy sú publikované, ale nie sú prijímané odberateľmi

**Riešenie:**  
1. **Názvy tém:** Overte, či sa téma odberateľa zhoduje presne s témou vydavateľa  
2. **Úroveň QoS:** Skúste QoS 1 alebo 2 namiesto 0  
3. **Wildcardy:** Skontrolujte správne použitie wildcardov témy (`+` pre jednu úroveň, `#` pre viacúrovňové)  
4. **Uchované správy:** Vydavateľ môže nastaviť retain flag na uchovanie poslednej správy  
5. **Časovanie pripojenia:** Uistite sa, že sa odberateľ pripojí pred publikovaním správ

---

## Problémy so senzormi a aktuátormi

### Grove senzory

#### Problém: Senzor vracia nesprávne hodnoty  
**Príznaky:** Hodnoty sú 0, -1 alebo nezmyselné hodnoty

**Riešenie:**  
1. **Skontrolujte pripojenia:** Uistite sa, že senzor je správne pripojený  
2. **Správny port:** Overte, či je senzor v správnom type portu:  
   - Analógové senzory → Analógové porty (A0, A2, A4)  
   - Digitálne senzory → Digitálne porty (D5, D16, D18, atď.)  
   - I2C senzory → I2C porty  
3. **Kalibrácia:** Niektoré senzory vyžadujú kalibráciu (vlhkosť pôdy, svetlo)  
4. **Vypnutie a zapnutie:** Odpojte a znova pripojte senzor  
5. **Datasheet senzora:** Skontrolujte špecifikácie a požiadavky senzora

#### Problém: Kapacitný senzor vlhkosti pôdy stále ukazuje mokro  
**Príznaky:** Senzor číta vysokú vlhkosť aj keď je suchý

**Riešenie:**  
1. **Potrebná kalibrácia:** Pôdne senzory vyžadujú kalibráciu:  
   - Namerajte hodnotu vo vzduchu (suchý základ)  
   - Namerajte hodnotu vo vode (mokrý základ)  
   - Mapujte výsledky medzi týmito hodnotami  
2. **Skontrolujte povlak senzora:** Senzory vlhkosti môžu degradovať, ak je povlak poškodený  
3. **Umiestnenie:** Uistite sa, že senzor je úplne zasunutý v pôde

#### Problém: Nesprávne teplotné/vlhkostné hodnoty senzoru  
**Príznaky:** DHT11/DHT22 ukazuje nesprávnu teplotu alebo vlhkosť

**Riešenie:**  
1. **Umiestnenie senzora:** Vyhnite sa priamemu slnečnému žiareniu, zdrojom tepla alebo prievanu  
2. **Čas na zahriatie:** Senzoru povoľte 2 sekundy po zapnutí pred čítaním  
3. **Frekvencia čítania:** DHT senzory potrebujú čas medzi čítaniami (aspoň 2 sekundy)  
4. **Skontrolujte kondenzáciu:** Môže ovplyvniť čítania  
5. **Kvalita senzora:** DHT11 je menej presný než DHT22

### Kamera

#### Problém: Kamera nie je detekovaná na Raspberry Pi  
**Chyba:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Riešenie:**  
1. **Povolenie rozhrania kamery:**  
   ```bash
   sudo raspi-config
   ```
   Choďte na Interface Options → Camera → Enable  
2. **Skontrolujte plochý kábel:** Uistite sa, že kábel kamery je správne zapojený  
   - Modrá strana smeruje k USB portom na Pi Zero  
   - Modrá strana smeruje preč od USB portov na Pi 4  
3. **Aktualizujte firmvér:**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Otestujte kameru:**  
   ```bash
   raspistill -o test.jpg
   ```
  
#### Problém: Obrázky z kamery sú zlej kvality  
**Príznaky:** Rozmazané, tmavé alebo vyblednuté obrázky

**Riešenie:**  
1. **Zaostrenie:** Odstráňte ochrannú fóliu z objektívu, upravte zaostrenie, ak je nastaviteľné  
2. **Osvetlenie:** Zabezpečte dostatočné osvetlenie  
3. **Nastavenia kamery:** Upraviť expozíciu, ISO, vyváženie bielej v kóde  
4. **Stabilita:** Držte kameru stabilne, prípadne použite statív  
5. **Rozlíšenie:** Neprekračujte maximálne rozlíšenie kamery

### Mikrofón a reproduktor

#### Problém: Žiaden audio vstup/výstup  
**Príznaky:** Mikrofón nezaznamenáva, reproduktor nehrá

**Riešenie:**  
1. **Skontrolujte pripojenia:** Overte správne zapojenie audio zariadení  
2. **Otestujte hardvér:**  
   - Reproduktor: `speaker-test -t wav -c 2`  
   - Mikrofón: `arecord -l` pre zoznam, `arecord test.wav` na nahrávanie  
3. **Nastavenia hlasitosti:** Skontrolujte a upravte hlasitosť:  
   ```bash
   alsamixer
   ```
4. **Vyberte audio zariadenie:** Špecifikujte správne audio zariadenie v kóde  
5. **Problémy s ovládačmi:** Aktualizujte ALSA alebo preinštalujte audio ovládače

#### Problém: ReSpeaker hat nefunguje  
**Príznaky:** Audio zariadenie nie je detekované

**Riešenie:**  
1. **Nainštalujte ovládače:**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Skontrolujte inštaláciu:** `arecord -l` by mal zobraziť ReSpeaker  
3. **Aktualizujte firmvér:** Niektoré verzie Pi OS vyžadujú aktualizáciu ovládačov  
4. **Skontrolujte nasadenie:** Uistite sa, že hat je správne pripojený ku GPIO pinom

---

## Problémy s vývojovým prostredím

### VS Code

#### Problém: Terminál automaticky neaktivuje virtuálne prostredie  
**Príznaky:** Terminál sa otvorí, ale venv nie je aktivovaný

**Riešenie:**  
1. **Nastavte Python interpreter:** Command Palette → "Python: Select Interpreter" → Vyberte venv  
2. **Reštartujte VS Code** po výbere interpretera  
3. **Skontrolujte nastavenia:** V `settings.json` pridajte:  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### Problém: Kód na zariadení nebeží  
**Príznaky:** Kód sa spustí, ale na zariadení sa nič nedeje

**Riešenie:**  
1. **Overte, či je kód uložený** (skontrolujte bodku na záložke súboru)  
2. **Skontrolujte, ktorý Python beží:** `which python` alebo `where python`  
3. **Pre Wio Terminal:** Uistite sa, že kód je nahraný cez PlatformIO (kliknite na tlačidlo upload)  
4. **Pre Raspberry Pi:** Prihláste sa cez SSH do Pi a spustite tam kód  
5. **Skontrolujte výstupné okno** na chyby

#### Problém: IntelliSense nezobrazuje funkcie knižníc  
**Príznaky:** Žiadne automatické dokončovanie pre importované moduly

**Riešenie:**  
1. Uistite sa, že knižnica je nainštalovaná v aktuálnom prostredí  
2. Obnovte okno VS Code  
3. Skontrolujte, či je Python interpreter správny  
4. Nainštalujte typové stubs ak sú dostupné: `pip install types-<library-name>`

### Virtuálne prostredia v Pythone

#### Problém: Nemožno vytvoriť virtuálne prostredie  
**Chyba:** `The virtual environment was not created successfully`

**Riešenie:**  
1. **Nainštalujte modul venv:**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Súčasťou Pythonu  
   - Windows: Preinštalujte Python so všetkými komponentmi  
2. **Skontrolujte inštaláciu Pythonu:** Overte, že je Python správne nainštalovaný  
3. **Použite úplnú cestu:** Skúste `python3 -m venv .venv` s explicitným volaním python3

#### Problém: Balíky sú inštalované na nesprávne miesto  
**Príznaky:** Chyba importu po inštalácii balíka

**Riešenie:**  
1. **Overte, či je venv aktivovaný:** Príkazový riadok by mal ukazovať `(.venv)`  
2. **Skontrolujte umiestnenie pip:** `which pip` by mal ukazovať `.venv/bin/pip`  
3. **Preinštalujte vo venv:** Aktivujte venv a potom `pip install <package>`  
4. **Nepoužívajte sudo s pip** vo virtuálnom prostredí

#### Problém: Virtuálne prostredie nie je prenosné  
**Príznaky:** Venv nefunguje po presune alebo na inom počítači

**Riešenie:**  
1. **Nevyťahujte venv:** Vymažte a vytvorte nové v inom umiestnení  
2. **Použite requirements.txt:**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Znova vytvorte venv:**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # alebo activate.bat vo Windows
   pip install -r requirements.txt
   ```
  
### Závislosti

#### Problém: Inštalácia balíka zlyhá  
**Chyba:** Rôzne chyby pip počas inštalácie

**Riešenie:**  
1. **Aktualizujte pip:**  
   ```bash
   pip install --upgrade pip
   ```
2. **Nainštalujte build nástroje:**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: Nainštalujte Visual Studio Build Tools  
3. **Skontrolujte internetové pripojenie**  
4. **Skúste iný index balíkov:** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **Nainštalujte konkrétnu verziu:** `pip install <package>==<version>`

#### Problém: Konflikty závislostí  
**Chyba:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Riešenie:**  
1. **Používajte nové virtuálne prostredie** pre každý projekt  
2. **Aktualizujte balíky:** `pip install --upgrade <package>`  
3. **Skontrolujte požiadavky:** Použite `pip check` na nájdenie konfliktov  
4. **Inštalujte kompatibilné verzie:** Špecifikujte rozsahy verzií v requirements.txt

---

## Výkonnostné problémy

### Problém: Kód beží pomaly  
**Príznaky:** Omeškania, časové limity, neodpovedajúce správanie

**Riešenie:**  
1. **Znížte frekvenciu čítania senzorov:** Nečítajte senzory príliš často  
2. **Optimalizujte slučky:** Vyhnite sa aktívnemu čakaniu, používajte sleep() alebo oneskorenia  
3. **Problémy s pamäťou:**  
   - Zavrite nepotrebné aplikácie  
   - Uvoľnite miesto na disku  
   - Sledujte pomocou `top` alebo `htop` na Pi  
4. **Rýchlosť SD karty:** Použite rýchlejšiu SD kartu alebo SSD pre Raspberry Pi  
5. **Sieťové omeškania:** Použite asynchrónne operácie pre sieťové volania

### Problém: Chyby nedostatku pamäte  
**Chyba:** `MemoryError` alebo zamŕzanie systému

**Riešenie:**  
1. **Pre Raspberry Pi:**  
   - Zavrite nepotrebné aplikácie  
   - Zvýšte swapovací priestor  
   - Použite ľahšiu OS verziu (Lite)  
   - Rozšírte RAM (Pi 4 má verzie s 2/4/8GB)  
2. **Pre Wio Terminal:**  
   - Znížte veľkosti bufferov  
   - Používajte menšie obrázky  
   - Optimalizujte používanie reťazcov  
   - Skontrolujte únik pamäte (neuvoľnená pamäť)

### Problém: Strata alebo poškodenie dát  
**Príznaky:** Chýbajúce správy, poškodené súbory

**Riešenie:**  
1. **Problémy s SD kartou:**  
   - Používajte kvalitné SD karty (vyhnite sa lacným/falošným)  
   - Pravidelné zálohy  
   - Čisté vypnutie (nevypínajte náhle)  
2. **Pretečenie bufferu:** Zvýšte veľkosti bufferov v kóde  
3. **Spoľahlivosť siete:** Implementujte logiku opakovania a spracovanie chýb  
4. **Kvalita služby:** Používajte MQTT QoS 1 alebo 2 pre dôležité správy

---

## Bežné chybové hlásenia

### `ModuleNotFoundError: No module named 'X'`  
**Príčina:** Balík nie je nainštalovaný alebo virtuálne prostredie nie je aktivované

**Riešenie:**  
```bash
pip install X
```
Najskôr sa uistite, že je virtuálne prostredie aktivované.

### `Permission denied` na Linux/macOS  
**Príčina:** Potrebné oprávnenia s vyššou úrovňou alebo problém s právami súborov

**Riešenie:**  
- Pre systémové operácie: Používajte `sudo`  
- Pre pip: NEpoužívajte sudo vo venv, najskôr aktivujte venv  
- Pre sériový port: Pridajte užívateľa do skupiny dialout: `sudo usermod -a -G dialout $USER`, následne sa odhláste a prihláste

### `OSError: [Errno 98] Address already in use`  
**Príčina:** Port už používa iný proces

**Riešenie:**  
1. Nájdite proces používajúci port: `lsof -i :<port>` alebo `netstat -ano | findstr :<port>`  
2. Ukončite proces alebo použite iný port v kóde

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**Príčina:** Neúspešná validácia SSL certifikátu

**Riešenie:**  
1. Aktualizujte certifikáty: `pip install --upgrade certifi`  
2. Skontrolujte, či je nastavený správny čas systému: `date`  
3. Len pre vývoj (nie produkcia): Vypnite overovanie v kóde

### `IndentationError: unexpected indent`  
**Príčina:** Problémy s odsadením v Pythone (miešanie tabulátorov a medzier)

**Riešenie:**  
1. Používajte konzistentné odsadenie (4 medzery je štandard)  
2. Nastavte editor, aby používal medzery namiesto tabulátorov  
3. Vo VS Code nastavte `"editor.insertSpaces": true` a `"editor.tabSize": 4`

### `UnicodeDecodeError` alebo `UnicodeEncodeError`  
**Príčina:** Problémy s kódovaním znakov

**Riešenie:**  
```python
# Pri čítaní súborov
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Pri písaní súborov
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## Ako získať pomoc

Ak ste tieto kroky na odstránenie problémov vyskúšali a stále máte problémy:

### 1. Skontrolujte už existujúce zdroje  
- **Dokumentácia:** Prečítajte si [README](README.md) a pokyny k lekcii  
- **Príručky hardvéru:** Pozrite [hardware.md](hardware.md) pre špecifické info o hardvéri  
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) pre Grove komponenty

### 2. Vyhľadajte podobné problémy  
- **GitHub Issues:** Vyhľadajte [existujúce problémy](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow:** Vyhľadajte chybové hlásenia  
- **Fóra zariadení:** Skontrolujte fóra Raspberry Pi alebo Arduino

### 3. Vytvorte GitHub Issue  
Ak riešenie nenájdete:  
1. Choďte na [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. Kliknite na "New Issue"  
3. Uveďte:  
   - Jasný popis problému  
   - Kroky na reprodukciu  
   - Chybové hlásenia (plný text)  
   - Verzie hardvéru/software  
   - Čo ste už vyskúšali  
   - Screenshoty ak sú relevantné

### 4. Pridajte sa ku komunite  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Poskytujte dobré hlásenia o chybách  
Dobré hlásenie obsahuje:
- **Prostredie:** OS, verzia Pythonu, použitý hardvér  
- **Kroky na reprodukciu:** Presné kroky, ktoré spôsobujú problém  
- **Očakávané správanie:** Čo by sa malo stať  
- **Skutočné správanie:** Čo sa v skutočnosti deje  
- **Chybové hlásenia:** Kompletný text chyby, nie snímky obrazovky  
- **Kód:** Minimálny príklad kódu, ktorý problém reprodukuje  

---

## Tipy na prevenciu

### Všeobecné osvedčené postupy
1. **Robte zálohy:** Pravidelné zálohovanie funkčných SD kariet/kódu  
2. **Dokumentujte zmeny:** Poznačte, čo funguje v komentároch  
3. **Verzionovanie:** Používajte git na sledovanie zmien v kóde  
4. **Testujte postupne:** Testujte malé zmeny pred ich zlúčením  
5. **Čítajte chybové hlásenia:** Často presne povedia, čo je zlé  
6. **Pravidelne aktualizujte:** Majte softvér/firmvér aktuálny  
7. **Používajte kvalitné komponenty:** Vyhýbajte sa lacným káblom/zdrojom napájania  
8. **Stabilné napájanie:** Používajte vhodný zdroj napájania (najmä pre Pi)  

### Vývojový pracovný postup
1. **Začnite jednoducho:** Začnite so vzorovým kódom, ktorý funguje  
2. **Jedna zmena naraz:** Ľahšie nájsť, čo spôsobuje chybu  
3. **Testujte často:** Chyby tak odhalíte skôr  
4. **Udržiavajte poriadok:** Logicky organizujte súbory a kód  
5. **Komentujte kód:** Budúce ja vám poďakuje  

---

*Táto príručka na riešenie problémov je spravovaná komunitou. Ak nájdete riešenie problému, ktorý tu nie je uvedený, zvážte, prosím, [prispieť](CONTRIBUTING.md) a pomôcť tak ostatným!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Vyhlásenie o zodpovednosti**:
Tento dokument bol preložený pomocou AI prekladateľskej služby [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, majte prosím na pamäti, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny preklad vykonaný človekom. Nezodpovedáme za žiadne nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->