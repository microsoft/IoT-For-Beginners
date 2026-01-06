<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T15:54:22+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "cs"
}
-->
# Průvodce řešením problémů

Tento průvodce vám pomůže vyřešit běžné problémy při práci s kurzem IoT pro začátečníky. Problémy jsou uspořádány podle kategorií pro snadnou orientaci.

## Obsah

- [Problémy s instalací](../..)
  - [Instalace Pythonu](../..)
  - [VS Code a rozšíření](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Knihovny Grove](../..)
- [Hardwarové problémy](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuální zařízení (CounterFit)](../..)
- [Problémy s připojením](../..)
  - [Připojení k WiFi](../..)
  - [Cloudové služby](../..)
  - [MQTT](../..)
- [Problémy se senzory a akčními členy](../..)
  - [Senzory Grove](../..)
  - [Kamera](../..)
  - [Mikrofon a reproduktor](../..)
- [Problémy s vývojovým prostředím](../..)
  - [VS Code](../..)
  - [Virtuální prostředí Pythonu](../..)
  - [Závislosti](../..)
- [Problémy s výkonem](../..)
- [Běžné chybové zprávy](../..)
- [Jak získat pomoc](../..)

---

## Problémy s instalací

### Instalace Pythonu

#### Problém: Verze Pythonu je příliš stará
**Chyba:** `Je potřeba Python 3.6 nebo vyšší`

**Řešení:**
1. Stáhněte si nejnovější Python 3 z [python.org](https://www.python.org/downloads/)
2. Při instalaci na Windows zaškrtněte „Add Python to PATH“
3. Ověřte instalaci:
   ```bash
   python3 --version
   ```

#### Problém: Více verzí Pythonu způsobuje konflikty
**Příznaky:** Spustí se špatná verze Pythonu, balíčky se instalují na špatné místo

**Řešení:**
- **Windows:** Použijte `py -3` místo `python` pro explicitní zavolání Pythonu 3
- **macOS/Linux:** Použijte `python3` místo `python`
- Vždy vytvářejte a používejte virtuální prostředí pro projekty

#### Problém: Příkaz pip nebyl nalezen
**Chyba:** `'pip' není rozpoznán jako interní nebo externí příkaz`

**Řešení:**
1. Zkuste místo `pip` použít `pip3`
2. Nebo použijte `python -m pip` nebo `python3 -m pip`
3. Ujistěte se, že je Python přidán do PATH (přeinstalujte Python a zaškrtněte tuto volbu)

### VS Code a rozšíření

#### Problém: Rozšíření Pylance nefunguje
**Příznaky:** Nevidíte IntelliSense pro Python, dokončování kódu nebo kontrolu typů

**Řešení:**
1. Otevřete Command Palette ve VS Code (`Ctrl+Shift+P` nebo `Cmd+Shift+P`)
2. Spusťte „Python: Select Interpreter“
3. Vyberte správný Python interpreter (virtuální prostředí, pokud používáte)
4. Restartujte okno VS Code

#### Problém: VS Code nerozpoznává virtuální prostředí
**Příznaky:** Vybrán nesprávný Python interpreter

**Řešení:**
1. Ujistěte se, že jste ve terminálu aktivovali virtuální prostředí
2. Otevřete Command Palette a spusťte „Python: Select Interpreter“
3. Vyberte interpreter z adresáře `.venv`
4. Zkontrolujte, zda stavový řádek (vlevo dole) zobrazuje správnou verzi Pythonu

### PlatformIO (Wio Terminal)

#### Problém: Instalace PlatformIO selhává
**Chyba:** Různé chyby během instalace PlatformIO

**Řešení:**
1. Ujistěte se, že máte aktuální VS Code
2. Nejprve nainstalujte rozšíření C/C++
3. Po instalaci PlatformIO restartujte VS Code
4. Zkontrolujte připojení k internetu (PlatformIO stahuje velké soubory)

#### Problém: PlatformIO nerozpozná desku
**Příznaky:** Nelze nahrát kód do Wio Terminal

**Řešení:**
1. Vyzkoušejte jiný USB kabel (některé kabely slouží jen k nabíjení)
2. Zkontrolujte Správce zařízení (Windows) nebo příkaz `ls /dev/tty*` (macOS/Linux)
3. Nainstalujte nebo aktualizujte USB ovladače
4. Zkuste jiné USB porty
5. Posuňte dvakrát rychle vypínač napájení na Wio Terminalu pro vstup do bootloaderu

#### Problém: Chyby při kompilaci v PlatformIO
**Chyba:** `fatal error: Arduino.h: No such file or directory`

**Řešení:**
1. Smažte složku `.pio` ve svém projektu
2. Spusťte „PlatformIO: Rebuild“ z Command Palette
3. Ujistěte se, že `platformio.ini` obsahuje správnou konfiguraci desky:
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Knihovny Grove

#### Problém: Import knihovny Grove na Raspberry Pi selhává
**Chyba:** `ModuleNotFoundError: No module named 'grove'`

**Řešení:**
1. Přeinstalujte knihovny Grove:
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Pokud používáte virtuální prostředí, možná je potřeba knihovny nainstalovat globálně nebo zkopírovat
3. Ověřte, zda je I2C povoleno: `sudo raspi-config nonint do_i2c 0`

#### Problém: Senzor Grove není detekován
**Chyba:** `IOError: [Errno 121] Remote I/O error`

**Řešení:**
1. Zkontrolujte fyzická připojení (ujistěte se, že je Grove kabel plně zasunut)
2. Ujistěte se, že je senzor připojen do správného portu (analogový, digitální, I2C, UART)
3. Spusťte `i2cdetect -y 1` a ověřte, zda se zařízení zobrazuje na I2C sběrnici
4. Vyzkoušejte jiný Grove kabel
5. Ujistěte se, že Grove Base Hat je správně usazený na pinech GPIO Raspberry Pi

---

## Hardwarové problémy

### Raspberry Pi

#### Problém: Raspberry Pi nenabootuje
**Příznaky:** Žádný obraz, NIC nesvítí nebo duhová obrazovka

**Řešení:**
1. **Zkontrolujte zdroj napájení:** Použijte oficiální 5V 3A USB-C napájecí adaptér pro Pi 4
2. **Problémy se SD kartou:** 
   - Naformátujte SD kartu a znovu nainstalujte Raspberry Pi OS
   - Vyzkoušejte jinou SD kartu (doporučené značky)
   - Ujistěte se, že je SD karta správně vložena
3. **Zkontrolujte HDMI připojení:** Vyzkoušejte oba HDMI porty na Pi 4, použijte HDMI port blíže k napájení

#### Problém: Nelze se připojit přes SSH k Raspberry Pi
**Příznaky:** Připojení odmítnuto nebo časový limit

**Řešení:**
1. Povolit SSH:
   - Při vytváření SD karty s Raspberry Pi Imagerem nastavte SSH v rozšířených možnostech
   - Nebo na bootovací oddíl vytvořte prázdný soubor `ssh` (bez přípony)
2. Najděte IP adresu Pi:
   - Zkontrolujte připojená zařízení v routeru
   - Použijte `ping raspberrypi.local` (pokud mDNS funguje)
   - Použijte nástroje pro skenování sítě jako `nmap` nebo Angry IP Scanner
3. Zkontrolujte síť:
   - Pi musí být ve stejné síti jako váš počítač
   - Vyzkoušejte připojení přes ethernet místo WiFi
4. Ověřte uživatelské jméno/heslo (výchozí: uživatel `pi`, heslo `raspberry`)

#### Problém: Grove Base Hat není rozpoznán
**Příznaky:** Senzory nefungují, chyby I2C

**Řešení:**
1. Ujistěte se, že Base Hat je správně nasazen na všechny piny GPIO
2. Zkontrolujte, zda nejsou na Pi nebo Base Hat ohnuté piny
3. Povolit I2C rozhraní:
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. Ověřte funkčnost I2C: `i2cdetect -y 1`

#### Problém: Raspberry Pi běží pomalu
**Příznaky:** Zpoždění uživatelského rozhraní, pomalá odezva

**Řešení:**
1. Zkontrolujte rychlost SD karty (doporučujeme třídu 10 nebo rychlejší, případně SSD přes USB)
2. Uvolněte místo na disku: příkaz `df -h`, smažte nepotřebné soubory
3. Snížit paměť GPU v `raspi-config`, pokud nepoužíváte kameru nebo intenzivně displej
4. Zavřete zbytečné aplikace
5. Zvažte upgrade na Pi 4 s více pamětí RAM, pokud používáte Pi 3 nebo starší

### Wio Terminal

#### Problém: Obrazovka Wio Terminalu zůstává prázdná
**Příznaky:** Žádný výstup na displej po nahrání kódu

**Řešení:**
1. Zkontrolujte, zda kód inicializuje displej (knihovna TFT_eSPI)
2. Aktualizujte firmware Wio Terminalu z [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/)
3. Přidejte inicializační kód displeje:
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. Vyzkoušejte nahrát ukázkový sketch z PlatformIO pro test hardware

#### Problém: WiFi na Wio Terminalu nefunguje
**Příznaky:** Nelze se připojit k WiFi, chyby sítě

**Řešení:**
1. **Aktualizujte WiFi firmware:** Postupujte podle [návodu na aktualizaci WiFi firmware Wio Terminal](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **Zkontrolujte přihlašovací údaje WiFi:** Ujistěte se, že SSID a heslo jsou správné
3. **WiFi pásmo:** Wio Terminal podporuje pouze 2,4 GHz WiFi (ne 5 GHz)
4. **Síla signálu:** Přesuňte zařízení blíže k routeru
5. **Nastavení routeru:** Některé podnikové/WPA-Enterprise sítě nemusí fungovat

#### Problém: Wio Terminal není rozpoznán počítačem
**Příznaky:** USB zařízení není detekováno

**Řešení:**
1. **Vyzkoušejte jiný USB kabel:** Použijte datový kabel, ne pouze nabíjecí kabel
2. **Vstup do režimu bootloaderu:** Posuňte vypínač napájení dolů dvakrát rychle
   - Modrá LED by měla pulzovat, zařízení se objeví jako "Arduino" ve Správci zařízení
3. **Nainstalujte ovladače (Windows):**
   - Stáhněte a nainstalujte [Seeed USB ovladač](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **Vyzkoušejte jiný USB port:** Vyhněte se USB hubům, použijte přímé připojení
5. **Aktualizujte ovladače USB systému**

#### Problém: Senzory na Wio Terminalu nefungují
**Příznaky:** Grove senzory nečtou data

**Řešení:**
1. Zkontrolujte připojení Grove kabelů
2. Ujistěte se, že používáte správný Grove port (levý nebo pravý)
3. Zahrňte správné knihovny pro senzor
4. Zkontrolujte požadavky senzoru na napájení
5. Otestujte senzor pomocí ukázkového kódu z knihovny

### Virtuální zařízení (CounterFit)

#### Problém: Aplikace CounterFit se nespustí
**Chyba:** Různé chyby Pythonu při spuštění CounterFit

**Řešení:**
1. Ujistěte se, že máte aktivované virtuální prostředí
2. Nainstalujte nebo přeinstalujte CounterFit:
   ```bash
   pip install CounterFit
   ```
3. Zkontrolujte, že port 5000 není již používán:
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. Ukončete proces, který port 5000 používá, nebo použijte jiný port:
   ```bash
   counterfit --port 5001
   ```

#### Problém: Nelze se připojit ke CounterFit z kódu
**Chyba:** Připojení odmítnuto nebo vypršel časový limit

**Řešení:**
1. Ověřte, že CounterFit běží: Otevřete prohlížeč na adrese `http://127.0.0.1:5000`
2. Zkontrolujte, zda URL připojení v kódu odpovídá adrese CounterFit
3. Ujistěte se, že firewall neblokuje připojení
4. Zkuste restartovat jak aplikaci CounterFit, tak váš kód

#### Problém: Senzory se nezobrazují v CounterFit
**Příznaky:** Vytvořené senzory se nezobrazují v uživatelském rozhraní CounterFit

**Řešení:**
1. Vytvořte senzory v uživatelském rozhraní CounterFit před spuštěním kódu
2. Aktualizujte stránku v prohlížeči
3. Zkontrolujte, zda typ senzoru odpovídá tomu, co kód očekává
4. Vymažte cache prohlížeče

---

## Problémy s připojením

### Připojení k WiFi

#### Problém: Zařízení se nemůže připojit k WiFi
**Příznaky:** Časový limit připojení, selhání autentifikace

**Řešení:**
1. **Zkontrolujte SSID a heslo:** Ověřte správnost přihlašovacích údajů
2. **WiFi pásmo:** Většina IoT zařízení podporuje pouze 2,4 GHz (nikoli 5 GHz)
3. **Nastavení routeru:**
   - Vypněte izolaci AP, pokud je zapnutá
   - Používejte zabezpečení WPA2-PSK (vyhněte se WPA3, WEP nebo otevřeným sítím)
   - Ujistěte se, že je povolen DHCP
4. **Skryté sítě:** Pokud je SSID skryto, může být potřeba jej explicitně nastavit
5. **Síla signálu:** Přesuňte zařízení blíže k routeru
6. **Rušení:** Jiné zařízení, mikrovlnné trouby nebo zdi mohou rušit signál

#### Problém: Připojení k WiFi často padá
**Příznaky:** Přerušované spoje

**Řešení:**
1. Zkontrolujte stabilitu routeru a případně ho restartujte
2. Aktualizujte firmware zařízení
3. Použijte statickou IP místo DHCP
4. Snižte vzdálenost od routeru nebo přidejte WiFi extender
5. Zkontrolujte rušení jinými zařízeními
6. Ověřte dostatečné napájení (zejména pro Raspberry Pi)

### Cloudové služby

#### Problém: Nelze se připojit k Azure IoT Hub
**Chyba:** Selhání autentifikace, odmítnutí připojení

**Řešení:**
1. **Ověřte přihlašovací údaje:**
   - Zkontrolujte správnost připojovacího řetězce
   - Ujistěte se, že v řetězci nejsou mezery nebo nové řádky
2. **Zkontrolujte registraci zařízení:** Zařízení musí být zaregistrováno v IoT Hubu
3. **Firewall/proxy:** Povolit odchozí MQTT (port 8883) nebo HTTPS (port 443)
4. **Region IoT Hubu:** Ujistěte se, že IoT Hub běží a není v jiné oblasti, což by mohlo způsobovat latenci
5. **Limit kvóty:** Zkontrolujte, zda nejsou překročeny limity bezplatné úrovně
6. **Test připojení:**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### Problém: Azure Functions se nespouštějí
**Příznaky:** Zprávy odeslány, ale funkce se neprovede

**Řešení:**
1. Zkontrolujte, že Function App běží (není zastavená)
2. Ověřte připojovací řetězec v nastavení Function App
3. Podívejte se do logů funkcí v Azure Portalu
4. Ujistěte se, že je správně nakonfigurován kompatibilní konec Event Hubu
5. Ověřte formát zpráv, zda odpovídá očekávání funkce
6. Zkontrolujte plán služby Function App (spotřeba vs. dedikovaný)

### MQTT
#### Problém: Selhání připojení MQTT
**Chyba:** Připojení odmítnuto, selhání autentizace

**Řešení:**
1. **Adresa brokeru:** Ověřte, že URL/IP brokeru je správná
2. **Port:** Zkontrolujte číslo portu (1883 pro nešifrované, 8883 pro TLS)
3. **Autentizace:** Ověřte uživatelské jméno/heslo, pokud je vyžadováno
4. **TLS/SSL:** Ujistěte se, že certifikáty jsou platné a důvěryhodné
5. **Firewall:** Zkontrolujte, zda port není blokován
6. **Test s MQTT klientem:** Použijte MQTT Explorer nebo mosquitto_pub/sub pro testování

#### Problém: MQTT zprávy nejsou přijaty
**Příznaky:** Zprávy jsou publikovány, ale nejsou přijímány odběrateli

**Řešení:**
1. **Názvy témat:** Ověřte, že téma odběratele přesně odpovídá tématu vydavatele
2. **Úroveň QoS:** Zkuste QoS 1 nebo 2 místo 0
3. **Wildcardy:** Zkontrolujte správné použití zástupných znaků témat (`+` pro jednu úroveň, `#` pro více úrovní)
4. **Uložené zprávy:** Vydavatel může nastavit příznak retain pro uchování poslední zprávy
5. **Časování připojení:** Ujistěte se, že odběratel se připojuje před publikováním zpráv

---

## Problémy se senzory a pohony

### Grove senzory

#### Problém: Senzor vrací nesprávné hodnoty
**Příznaky:** Naměřené hodnoty jsou 0, -1 nebo nesmyslné

**Řešení:**
1. **Zkontrolujte připojení:** Ujistěte se, že je senzor správně připojen
2. **Správný port:** Ověřte, že senzor je ve správném typu portu:
   - Analogové senzory → Analogové porty (A0, A2, A4)
   - Digitální senzory → Digitální porty (D5, D16, D18, atd.)
   - I2C senzory → I2C porty
3. **Kalibrace:** Některé senzory vyžadují kalibraci (vlhkost půdy, světlo)
4. **Restart napájení:** Odpojte a znovu připojte senzor
5. **Datasheet senzoru:** Zkontrolujte specifikace a požadavky senzoru

#### Problém: Kapacitní senzor vlhkosti půdy stále ukazuje mokro
**Příznaky:** Senzor měří vysokou vlhkost i při suchu

**Řešení:**
1. **Vyžaduje kalibraci:** Půdní senzory vyžadují kalibraci:
   - Přečíst hodnotu na vzduchu (suchý základ)
   - Přečíst hodnotu ve vodě (mokrá hodnota)
   - Naměřené hodnoty mapovat mezi těmito hodnotami
2. **Zkontrolujte povlak senzoru:** Senzory vlhkosti mohou degradovat, pokud je povlak poškozen
3. **Umístění:** Ujistěte se, že senzor je zcela zasunut do půdy

#### Problém: Nesprávné hodnoty teploty/vlhkosti
**Příznaky:** DHT11/DHT22 ukazuje špatnou teplotu nebo vlhkost

**Řešení:**
1. **Umístění senzoru:** Vyhněte se přímému slunečnímu svitu, zdrojům tepla nebo průvanu
2. **Doba zahřátí:** Nechte senzor 2 sekundy po zapnutí před čtením
3. **Frekvence čtení:** DHT senzory potřebují čas mezi čteními (minimálně 2 sekundy)
4. **Kontrola kondenzace:** Kondenzace může ovlivnit naměřené hodnoty
5. **Kvalita senzoru:** DHT11 je méně přesný než DHT22

### Kamera

#### Problém: Kamera není detekována na Raspberry Pi
**Chyba:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Řešení:**
1. **Povolit rozhraní kamery:**
   ```bash
   sudo raspi-config
   ```
   Přejděte do Interface Options → Camera → Enable
2. **Zkontrolujte plochý kabel:** Ujistěte se, že je kabel kamery správně zapojen
   - Modrá strana směřuje k USB portům u Pi Zero
   - Modrá strana směřuje od USB portů u Pi 4
3. **Aktualizujte firmware:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Otestujte kameru:**
   ```bash
   raspistill -o test.jpg
   ```

#### Problém: Obrázky z kamery jsou špatné kvality
**Příznaky:** Rozmazané, tmavé nebo vybledlé obrázky

**Řešení:**
1. **Zaostření:** Sundejte ochrannou fólii z čočky, nastavte ostření pokud je možné
2. **Osvětlení:** Zajistěte dostatečné osvětlení
3. **Nastavení kamery:** Upravte expozici, ISO, vyvážení bílé v kódu
4. **Stabilita:** Udržujte kameru stabilní, použijte stativ pokud je potřeba
5. **Rozlišení:** Nepřekračujte maximální rozlišení kamery

### Mikrofon a reproduktor

#### Problém: Žádný zvukový vstup/výstup
**Příznaky:** Mikrofon nahrává, reproduktor nepřehrává

**Řešení:**
1. **Zkontrolujte připojení:** Ověřte správné připojení audio zařízení
2. **Test hardwaru:**
   - Reproduktor: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` pro seznam, `arecord test.wav` pro záznam
3. **Nastavení hlasitosti:** Zkontrolujte a upravte hlasitost:
   ```bash
   alsamixer
   ```
4. **Vyberte audio zařízení:** Určete správné zařízení v kódu
5. **Problémy s ovladači:** Aktualizujte ALSA nebo přeinstalujte audio ovladače

#### Problém: ReSpeaker hat nefunguje
**Příznaky:** Audio zařízení není detekováno

**Řešení:**
1. **Nainstalujte ovladače:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Zkontrolujte instalaci:** `arecord -l` by měl zobrazit ReSpeaker
3. **Aktualizujte firmware:** Některé verze Pi OS vyžadují aktualizaci ovladačů
4. **Kontrola upevnění:** Zajistěte správné připojení hatu k pinům GPIO

---

## Problémy s vývojovým prostředím

### VS Code

#### Problém: Terminál automaticky neaktivuje virtuální prostředí
**Příznaky:** Terminál se otevře, ale venv není aktivován

**Řešení:**
1. **Nastavte Python interpreter:** Command Palette → "Python: Select Interpreter" → vyberte venv
2. **Restartujte VS Code** po výběru interpreteru
3. **Zkontrolujte nastavení:** V `settings.json` přidejte:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Problém: Kód na zařízení neběží
**Příznaky:** Kód se spustí, ale na zařízení se nic neděje

**Řešení:**
1. **Ověřte, že je kód uložen** (zkontrolujte tečku na kartě souboru)
2. **Zkontrolujte běžící Python:** `which python` nebo `where python`
3. **Pro Wio Terminal:** Ujistěte se, že kód je nahrán přes PlatformIO (klikněte na tlačítko upload)
4. **Pro Raspberry Pi:** Přihlaste se přes SSH do Pi a spusťte kód tam
5. **Zkontrolujte výstupní okno** na chyby

#### Problém: IntelliSense nezobrazuje funkce knihoven
**Příznaky:** Autocomplete pro importované moduly nefunguje

**Řešení:**
1. Ujistěte se, že knihovna je nainstalovaná v aktuálním prostředí
2. Obnovte okno VS Code
3. Zkontrolujte správnost Python interpreteru
4. Nainstalujte typové nápovědy, pokud jsou dostupné: `pip install types-<název_knihovny>`

### Python virtuální prostředí

#### Problém: Nelze vytvořit virtuální prostředí
**Chyba:** `The virtual environment was not created successfully`

**Řešení:**
1. **Nainstalujte modul venv:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: Mělo by být součástí instalace Pythonu
   - Windows: Přeinstalujte Python se všemi komponenty
2. **Zkontrolujte instalaci Pythonu:** Ověřte správnou instalaci
3. **Použijte plnou cestu:** Zkuste `python3 -m venv .venv` s explicitním voláním python3

#### Problém: Balíčky nainstalovány na špatném místě
**Příznaky:** Import vyvolává chybu po instalaci balíčku

**Řešení:**
1. **Ověřte aktivaci venv:** Příkazový řádek by měl ukazovat `(.venv)`
2. **Zkontrolujte umístění pip:** `which pip` by měl ukazovat na `.venv/bin/pip`
3. **Přeinstalujte v rámci venv:** Aktivujte venv a spusťte `pip install <balíček>`
4. **Nepoužívejte sudo s pip** ve virtuálním prostředí

#### Problém: Virtuální prostředí není přenosné
**Příznaky:** Venv nefunguje po přesunu nebo na jiném počítači

**Řešení:**
1. **Nepřesouvejte venv:** Smažte a znovu vytvořte v novém umístění
2. **Použijte requirements.txt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Znovu vytvořte venv:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # nebo activate.bat na Windows
   pip install -r requirements.txt
   ```

### Závislosti

#### Problém: Selhání instalace balíčku
**Chyba:** Různé chyby pip během instalace

**Řešení:**
1. **Aktualizujte pip:**
   ```bash
   pip install --upgrade pip
   ```
2. **Nainstalujte nástroje pro sestavení:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Nainstalujte Visual Studio Build Tools
3. **Zkontrolujte internetové připojení**
4. **Zkuste jiný index balíčků:** `pip install --index-url https://pypi.org/simple/ <balíček>`
5. **Nainstalujte konkrétní verzi:** `pip install <balíček>==<verze>`

#### Problém: Konflikty závislostí
**Chyba:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Řešení:**
1. **Používejte nové virtuální prostředí** pro každý projekt
2. **Aktualizujte balíčky:** `pip install --upgrade <balíček>`
3. **Zkontrolujte požadavky:** Použijte `pip check` k nalezení konfliktů
4. **Nainstalujte kompatibilní verze:** Určete verze v rozsahu v requirements.txt

---

## Problémy s výkonem

### Problém: Kód běží pomalu
**Příznaky:** Zpoždění, časová omezení, neodpovídající chování

**Řešení:**
1. **Snižte frekvenci čtení senzorů:** Nečtěte senzory příliš často
2. **Optimalizujte smyčky:** Vyhněte se zbytečnému čekání, použijte sleep() nebo zpoždění
3. **Problémy s pamětí:**
   - Zavřete zbytečné programy
   - Uvolněte místo na disku
   - Sledujte pomocí `top` nebo `htop` na Pi
4. **Rychlost SD karty:** Použijte rychlejší SD kartu nebo SSD pro Raspberry Pi
5. **Síťové zpoždění:** Používejte asynchronní operace pro volání přes síť

### Problém: Chyby vyčerpání paměti
**Chyba:** `MemoryError` nebo zamrznutí systému

**Řešení:**
1. **Pro Raspberry Pi:**
   - Zavřete zbytečné aplikace
   - Zvýšte velikost swapu
   - Použijte lehčí OS (Lite verze)
   - Upgradujte RAM (Pi 4 má varianty 2/4/8GB)
2. **Pro Wio Terminal:**
   - Snižte velikost bufferů
   - Používejte menší obrázky
   - Optimalizujte práci s řetězci
   - Kontrolujte úniky paměti (nezpřístupněná paměť)

### Problém: Ztráta nebo poškození dat
**Příznaky:** Chybějící zprávy, poškozené soubory

**Řešení:**
1. **Problémy se SD kartou:**
   - Používejte kvalitní SD karty (vyhněte se levným/napodobeninám)
   - Pravidelné zálohy
   - Bezpečné vypínání (nevypínejte bezprostředně odpojením napájení)
2. **Přetečení bufferu:** Zvyšte velikost bufferů v kódu
3. **Spolehlivost sítě:** Implementujte logiku opakování a ošetření chyb
4. **Kvalita služby:** Používejte QoS MQTT 1 nebo 2 pro důležité zprávy

---

## Běžné chybové hlášky

### `ModuleNotFoundError: No module named 'X'`
**Příčina:** Balíček není nainstalován nebo virtuální prostředí není aktivováno

**Řešení:**
```bash
pip install X
```
Nejprve aktivujte virtuální prostředí.

### `Permission denied` na Linux/macOS
**Příčina:** Potřeba vyšších oprávnění nebo problém s právy souboru

**Řešení:**
- Pro systémové operace: Použijte `sudo`
- Pro pip: NEPOUŽÍVEJTE sudo s venv, nejprve aktivujte venv
- Pro sériový port: Přidejte uživatele do skupiny dialout: `sudo usermod -a -G dialout $USER`, poté odhlaste a přihlaste

### `OSError: [Errno 98] Address already in use`
**Příčina:** Port je již používán jiným procesem

**Řešení:**
1. Najděte proces používající port: `lsof -i :<port>` nebo `netstat -ano | findstr :<port>`
2. Zastavte proces nebo použijte jiný port v kódu

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Příčina:** Selhání ověření SSL certifikátu

**Řešení:**
1. Aktualizujte certifikáty: `pip install --upgrade certifi`
2. Zkontrolujte správný systémový čas: `date`
3. Pouze pro vývoj (ne produkci): Vypněte ověřování v kódu

### `IndentationError: unexpected indent`
**Příčina:** Problémy s odsazením v Pythonu (smíchání tabulátorů a mezer)

**Řešení:**
1. Používejte konzistentní odsazení (4 mezery jsou standard v Pythonu)
2. Nastavte editor na používání mezer místo tabulátorů
3. VS Code: Nastavte `"editor.insertSpaces": true` a `"editor.tabSize": 4`

### `UnicodeDecodeError` nebo `UnicodeEncodeError`
**Příčina:** Problémy se znakovou sadou/kódováním

**Řešení:**
```python
# Při čtení souborů
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Při zápisu souborů
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Získání pomoci

Pokud jste vyzkoušeli tyto kroky pro řešení problémů a stále máte potíže:

### 1. Zkontrolujte dostupné zdroje
- **Dokumentace:** Prohlédněte si [README](README.md) a instrukce lekce
- **Průvodce hardwarem:** Podívejte se na [hardware.md](hardware.md) pro informace o hardwaru
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) pro komponenty Grove

### 2. Vyhledejte podobné problémy
- **GitHub Issues:** Vyhledejte [existující problémy](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Vyhledejte chybové hlášky
- **Fóra zařízení:** Zkontrolujte fóra Raspberry Pi nebo Arduino

### 3. Vytvořte GitHub Issue
Pokud řešení nenajdete:
1. Jděte na [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)
2. Klikněte na "New Issue"
3. Uveďte:
   - Jasný popis problému
   - Kroky k reprodukci
   - Chybové zprávy (plný text)
   - Verze hardwaru/software
   - Co jste již vyzkoušeli
   - Snímky obrazovky, pokud jsou relevantní

### 4. Připojte se ke komunitě
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Poskytněte kvalitní hlášení chyb
Kvalitní hlášení chyb obsahuje:
- **Prostředí:** OS, verze Pythonu, použité zařízení
- **Kroky k reprodukci:** Přesné kroky, které způsobují problém
- **Očekávané chování:** Co by se mělo stát
- **Skutečné chování:** Co se ve skutečnosti děje
- **Chybové zprávy:** Kompletní text chyby, ne screenshoty
- **Kód:** Minimální příklad kódu, který problém reprodukuje

---

## Tipy pro prevenci

### Obecné osvědčené postupy
1. **Zálohujte:** Pravidelné zálohy fungujících SD karet/kódu
2. **Dokumentujte změny:** Poznamenejte, co funguje, v komentářích
3. **Verzovací systém:** Používejte git pro sledování změn v kódu
4. **Testujte postupně:** Testujte malé změny před jejich sloučením
5. **Čtěte chybové zprávy:** Často přesně řeknou, co je špatně
6. **Pravidelně aktualizujte:** Udržujte software/firmware aktuální
7. **Používejte kvalitní komponenty:** Vyhněte se levným kabelům/zdrojům napájení
8. **Stabilní napájení:** Používejte vhodný napájecí zdroj (zejména u Pi)

### Vývojový pracovní postup
1. **Začněte jednoduše:** Začněte s příkladem kódu, který funguje
2. **Jedna změna najednou:** Snazší najít, co způsobí chybu
3. **Často testujte:** Objevíte chyby brzy
4. **Udržujte pořádek:** Logicky organizujte soubory a kód
5. **Komentujte kód:** Budoucí vy to ocení

---

*Tento průvodce řešením problémů je udržován komunitou. Pokud najdete řešení problému, které zde není uvedeno, zvážte prosím [přispění](CONTRIBUTING.md), abyste pomohli ostatním!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Prohlášení o vyloučení odpovědnosti**:  
Tento dokument byl přeložen pomocí AI překladatelské služby [Co-op Translator](https://github.com/Azure/co-op-translator). Přestože usilujeme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Originální dokument v jeho mateřském jazyce by měl být považován za závazný zdroj. Pro zásadní informace se doporučuje profesionální lidský překlad. Nebereme na sebe odpovědnost za jakékoliv nedorozumění nebo chybné výklady vyplývající z použití tohoto překladu.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->