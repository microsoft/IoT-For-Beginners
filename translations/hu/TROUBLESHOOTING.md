<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-06T15:52:01+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "hu"
}
-->
# Hibakeresési útmutató

Ez az útmutató segít megoldani a gyakori problémákat az IoT for Beginners tananyag használata során. A problémák kategóriák szerint vannak rendezve a könnyű navigáció érdekében.

## Tartalomjegyzék

- [Telepítési problémák](../..)
  - [Python telepítése](../..)
  - [VS Code és bővítmények](../..)
  - [PlatformIO (Wio Terminal)](../..)
  - [Grove könyvtárak](../..)
- [Hardver problémák](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [Virtuális eszköz (CounterFit)](../..)
- [Kapcsolódási problémák](../..)
  - [WiFi kapcsolat](../..)
  - [Felhőszolgáltatások](../..)
  - [MQTT](../..)
- [Érzékelő és aktuátor problémák](../..)
  - [Grove érzékelők](../..)
  - [Kamera](../..)
  - [Mikrofon és hangszóró](../..)
- [Fejlesztői környezet problémák](../..)
  - [VS Code](../..)
  - [Python virtuális környezetek](../..)
  - [Függőségek](../..)
- [Teljesítmény problémák](../..)
- [Gyakori hibák üzenetei](../..)
- [Segítségkérés](../..)

---

## Telepítési problémák

### Python telepítése

#### Probléma: A Python verzió túl régi  
**Hiba:** `Python 3.6 vagy újabb szükséges`

**Megoldás:**  
1. Töltse le a legújabb Python 3 verziót a [python.org](https://www.python.org/downloads/) oldalról  
2. Windows telepítéskor jelölje be a "Add Python to PATH" opciót  
3. Ellenőrizze a telepítést:  
   ```bash
   python3 --version
   ```
  
#### Probléma: Több Python verzió ütközik  
**Tünetek:** Rossz Python verzió indul el, a csomagok rossz helyre települnek

**Megoldás:**  
- **Windows:** Használja a `py -3` parancsot a `python` helyett a Python 3 meghívásához  
- **macOS/Linux:** Használja a `python3` parancsot a `python` helyett  
- Mindig hozzon létre és használjon virtuális környezeteket a projektekhez

#### Probléma: pip parancs nem található  
**Hiba:** `'pip' nem ismerhető fel belső vagy külső parancsként`

**Megoldás:**  
1. Próbálja a `pip3` parancsot a `pip` helyett  
2. Vagy használja a `python -m pip` vagy `python3 -m pip` parancsot  
3. Győződjön meg róla, hogy a Python hozzá van adva a PATH-hoz (telepítse újra a Pythont, és ellenőrizze a beállítást)

### VS Code és bővítmények

#### Probléma: Pylance bővítmény nem működik  
**Tünetek:** Nincs Python IntelliSense, kódkiegészítés vagy típusellenőrzés

**Megoldás:**  
1. Nyissa meg a VS Code Parancspalettáját (`Ctrl+Shift+P` vagy `Cmd+Shift+P`)  
2. Futtassa a "Python: Select Interpreter" parancsot  
3. Válassza ki a megfelelő Python értelmezőt (virtuális környezetet ha használ)  
4. Töltse újra a VS Code ablakot

#### Probléma: VS Code nem érzékeli a virtuális környezetet  
**Tünetek:** Hibás Python értelmező van kiválasztva

**Megoldás:**  
1. Győződjön meg arról, hogy aktiválta a virtuális környezetet a terminálban  
2. Nyissa meg a Parancspalettát és futtassa a "Python: Select Interpreter" parancsot  
3. Válassza ki az értelmezőt a `.venv` mappából  
4. Ellenőrizze, hogy az állapotsáv (bal alsó sarok) a megfelelő Python verziót mutatja

### PlatformIO (Wio Terminal)

#### Probléma: PlatformIO telepítés sikertelen  
**Hiba:** Különböző hibák a PlatformIO telepítése közben

**Megoldás:**  
1. Győződjön meg róla, hogy a VS Code naprakész  
2. Először telepítse a C/C++ bővítményt  
3. Telepítés után indítsa újra a VS Code-ot  
4. Ellenőrizze az internetkapcsolatot (a PlatformIO nagy fájlokat tölt le)

#### Probléma: PlatformIO nem érzékeli a lapkát  
**Tünetek:** Nem lehet feltölteni kódot a Wio Terminalra

**Megoldás:**  
1. Próbáljon meg másik USB kábelt (némely kábel csak töltésre jó)  
2. Ellenőrizze az Eszközkezelőt (Windows) vagy `ls /dev/tty*` (macOS/Linux)  
3. Telepítse vagy frissítse az USB illesztőprogramokat  
4. Próbáljon meg másik USB portot  
5. Csúsztassa le kétszer gyorsan a Wio Terminal bekapcsoló gombját, hogy bootloader módba lépjen

#### Probléma: Fordítási hibák a PlatformIO-ban  
**Hiba:** `fatal error: Arduino.h: Nincs ilyen fájl vagy könyvtár`

**Megoldás:**  
1. Törölje a `.pio` mappát a projektben  
2. Futtassa a "PlatformIO: Rebuild" parancsot a Parancspalettából  
3. Győződjön meg róla, hogy a `platformio.ini` helyesen van beállítva a board konfigurációval:  
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```
  
### Grove könyvtárak

#### Probléma: Grove könyvtár importálása sikertelen Raspberry Pi-n  
**Hiba:** `ModuleNotFoundError: No module named 'grove'`

**Megoldás:**  
1. Telepítse újra a Grove könyvtárakat:  
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. Ha virtuális környezetet használ, előfordulhat, hogy globálisan kell telepíteni vagy másolni a könyvtárakat  
3. Ellenőrizze, hogy az I2C engedélyezve van-e: `sudo raspi-config nonint do_i2c 0`

#### Probléma: Grove érzékelő nem érzékelhető  
**Hiba:** `IOError: [Errno 121] Távoli I/O hiba`

**Megoldás:**  
1. Ellenőrizze a fizikai csatlakozásokat (győződjön meg róla, hogy a Grove kábel teljesen be van dugva)  
2. Ellenőrizze, hogy az érzékelő a megfelelő porthoz csatlakozik (analóg, digitális, I2C, UART)  
3. Futtassa a `i2cdetect -y 1` parancsot, hogy lássa, megjelenik-e az eszköz az I2C buszon  
4. Próbáljon ki másik Grove kábelt  
5. Győződjön meg róla, hogy a Grove Base Hat megfelelően illeszkedik a Raspberry Pi GPIO tüskéire

---

## Hardver problémák

### Raspberry Pi

#### Probléma: A Raspberry Pi nem indul el  
**Tünetek:** Nincs kijelző, nincs LED aktivitás vagy szivárvány színű képernyő

**Megoldás:**  
1. **Ellenőrizze a tápegységet:** Használjon hivatalos 5V 3A USB-C tápegységet Pi 4-hez  
2. **SD kártya problémák:**  
   - Formázza újra az SD kártyát és telepítse újra a Raspberry Pi OS-t  
   - Próbáljon ki másik SD kártyát (ajánlott márkákat használjon)  
   - Győződjön meg róla, hogy az SD kártya megfelelően van behelyezve  
3. **Ellenőrizze az HDMI csatlakozást:** Próbálja ki mindkét HDMI portot Pi 4-en, használja a tápegységhez közelebbi HDMI portot

#### Probléma: Nem lehet SSH-val kapcsolódni a Raspberry Pi-hez  
**Tünetek:** Kapcsolat megtagadva vagy időtúllépés

**Megoldás:**  
1. Engedélyezze az SSH-t:  
   - Amikor az SD kártyát a Raspberry Pi Imager-rel írja, az SSH-t az speciális opciókban kapcsolja be  
   - Vagy hozzon létre egy `ssh` nevű üres fájlt (kiterjesztés nélkül) a boot partíción  
2. Keresse meg a Pi IP-címét:  
   - Ellenőrizze az útválasztó csatlakoztatott eszközeit  
   - Használja a `ping raspberrypi.local` parancsot (ha az mDNS működik)  
   - Használjon hálózati szkennelő eszközöket, mint az `nmap` vagy Angry IP Scanner  
3. Ellenőrizze a hálózatot:  
   - Győződjön meg róla, hogy a Pi ugyanazon a hálózaton van, mint a számítógép  
   - Próbálja meg ethernet kapcsolattal a WiFi helyett  
4. Ellenőrizze a felhasználónevet/jelszót (alapértelmezett: felhasználó `pi`, jelszó `raspberry`)

#### Probléma: Grove Base Hat nem ismerhető fel  
**Tünetek:** Az érzékelők nem működnek, I2C hibák

**Megoldás:**  
1. Győződjön meg arról, hogy a Base Hat megfelelően ül mind a GPIO tüskén  
2. Ellenőrizze, hogy nincs-e meghajlott tüske a Pi-n vagy a Base Haton  
3. Engedélyezze az I2C interfészt:  
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
  
4. Ellenőrizze, hogy az I2C működik: `i2cdetect -y 1`

#### Probléma: A Raspberry Pi lassan működik  
**Tünetek:** Akadozó felhasználói felület, lassú válasz

**Megoldás:**  
1. Ellenőrizze az SD kártya sebességét (használjon Class 10 vagy jobb kártyát, vagy SSD-t USB-n keresztül)  
2. Szabadítson fel helyet: `df -h` parancsal ellenőrizze, törölje a felesleges fájlokat  
3. Csökkentse a GPU memóriát a `raspi-config` segítségével, ha nem használ kamerát vagy kijelzőt nagy erőforrással  
4. Zárja be a felesleges alkalmazásokat  
5. Ha Pi 3 vagy régebbi verziót használ, fontolja meg a Pi 4-re való frissítést nagyobb RAM-mal

### Wio Terminal

#### Probléma: Wio Terminal képernyője fekete marad  
**Tünetek:** Nincs kép a kód feltöltése után

**Megoldás:**  
1. Ellenőrizze, hogy a kód inicializálja-e a kijelzőt (TFT_eSPI könyvtár)  
2. Frissítse a Wio Terminal firmware-t a [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/) oldalról  
3. Adjon hozzá kijelző inicializáló kódot:  
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
  
4. Próbálja felölteni a PlatformIO példaskicset a hardver tesztelésére

#### Probléma: Nem működik a WiFi a Wio Terminalon  
**Tünetek:** Nem lehet WiFi-re csatlakozni, hálózati hibák

**Megoldás:**  
1. **Frissítse a WiFi firmware-t:** Kövesse a [Wio Terminal WiFi firmware frissítési útmutatót](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)  
2. **Ellenőrizze a WiFi hitelesítő adatokat:** Győződjön meg arról, hogy az SSID és a jelszó helyes  
3. **WiFi sáv:** A Wio Terminal csak 2.4GHz-es WiFi-t támogat (nem 5GHz-et)  
4. **Jelerősség:** Helyezze közelebb az eszközt az útválasztóhoz  
5. **Router beállítások:** Egyes vállalati/WPA-Enterprise hálózatok nem működhetnek

#### Probléma: Wio Terminal nem ismerhető fel a számítógép által  
**Tünetek:** Nem jelenik meg USB eszközként

**Megoldás:**  
1. **Próbáljon másik USB kábelt:** Használjon adatkábel, ne csak töltésre alkalmas kábelt  
2. **Lépjen bootloader módba:** Csúsztassa le kétszer gyorsan a bekapcsoló gombot  
   - A kék LED pulzál, az eszköz "Arduino" néven jelenik meg az Eszközkezelőben  
3. **Telepítse az illesztőprogramokat (Windows):**  
   - Töltse le és telepítse a [Seeed USB drivert](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)  
4. **Próbáljon másik USB portot:** Kerülje az USB hubokat, használjon közvetlen kapcsolatot  
5. **Frissítse az USB illesztőprogramokat a rendszeren**

#### Probléma: Az érzékelők nem működnek a Wio Terminalon  
**Tünetek:** A Grove érzékelők nem olvasnak adatot

**Megoldás:**  
1. Ellenőrizze a Grove kábel csatlakozásokat  
2. Győződjön meg róla, hogy a megfelelő Grove portot használja (bal vagy jobb)  
3. Tartalmazza a megfelelő könyvtárakat az érzékelőhöz  
4. Ellenőrizze az érzékelő áramellátási igényeit  
5. Tesztelje az érzékelőt a könyvtári példakód segítségével

### Virtuális eszköz (CounterFit)

#### Probléma: A CounterFit alkalmazás nem indul  
**Hiba:** Különféle Python hibák a CounterFit indításakor

**Megoldás:**  
1. Győződjön meg arról, hogy a virtuális környezet aktív  
2. Telepítse újra a CounterFitet:  
   ```bash
   pip install CounterFit
   ```
3. Ellenőrizze, hogy a 5000-es port nem használatban van:  
   - Windows: `netstat -ano | findstr :5000`  
   - macOS/Linux: `lsof -i :5000`  
4. Állítsa le a 5000-es portot használó folyamatot vagy használjon másik portot:  
   ```bash
   counterfit --port 5001
   ```
  
#### Probléma: Nem lehet kapcsolódni a CounterFithez a kódból  
**Hiba:** Kapcsolat megtagadva vagy időtúllépés

**Megoldás:**  
1. Ellenőrizze, hogy a CounterFit fut-e: Nyissa meg böngészőben a `http://127.0.0.1:5000` címet  
2. Ellenőrizze, hogy a kódban megadott URL megegyezik-e a CounterFit címével  
3. Győződjön meg róla, hogy a tűzfal nem blokkolja a kapcsolatot  
4. Próbálja meg újraindítani mind a CounterFit alkalmazást, mind a kódot

#### Probléma: Az érzékelők nem jelennek meg a CounterFitben  
**Tünetek:** A létrehozott érzékelők nem látszanak a CounterFit felhasználói felületén

**Megoldás:**  
1. Hozza létre az érzékelőket a CounterFit felületen a kód futtatása előtt  
2. Frissítse a böngésző oldalát  
3. Ellenőrizze, hogy az érzékelőtípus megegyezik a kódban elvárt típussal  
4. Törölje a böngésző gyorsítótárát

---

## Kapcsolódási problémák

### WiFi kapcsolat

#### Probléma: Az eszköz nem tud csatlakozni a WiFi hálózatra  
**Tünetek:** Kapcsolódás időtúllépés miatt sikertelen, hitelesítés sikertelen

**Megoldás:**  
1. **Ellenőrizze az SSID-t és a jelszót:** Győződjön meg róla, hogy a hitelesítő adatok helyesek  
2. **WiFi sáv:** A legtöbb IoT eszköz csak 2.4GHz-es sávot támogat (nem 5GHz-et)  
3. **Router beállítások:**  
   - Kapcsolja ki az AP izolációt, ha be van kapcsolva  
   - Használja a WPA2-PSK titkosítást (kerülje a WPA3-at, WEP-et vagy nyílt hálózatokat)  
   - Győződjön meg arról, hogy a DHCP engedélyezve van  
4. **Rejtett hálózatok:** Ha az SSID rejtett, explicit konfigurálás szükséges  
5. **Jelerősség:** Húzza közelebb az eszközt az útválasztóhoz  
6. **Zavaró tényezők:** Más eszközök, mikrohullámú sütők vagy falak zavarhatják a jelet

#### Probléma: A WiFi kapcsolat gyakran megszakad  
**Tünetek:** Időszakos kapcsolódási problémák

**Megoldás:**  
1. Ellenőrizze az útválasztó stabilitását, szükség esetén indítsa újra  
2. Frissítse az eszköz firmware-jét  
3. Használjon statikus IP címet DHCP helyett  
4. Csökkentse a távolságot az útválasztótól vagy használjon WiFi jelerősítőt  
5. Ellenőrizze, hogy nincs-e zavaró más eszközökből  
6. Győződjön meg erről, hogy az energiaellátás megfelelő (különösen Raspberry Pi esetében)

### Felhőszolgáltatások

#### Probléma: Nem lehet csatlakozni az Azure IoT Hubhoz  
**Hiba:** Hitelesítés sikertelen, kapcsolat megtagadva

**Megoldás:**  
1. **Ellenőrizze a hitelesítő adatokat:**  
   - Ellenőrizze, hogy a kapcsolati karakterlánc helyes  
   - Győződjön meg róla, hogy nincs extra szóköz vagy sortörés a kapcsolati karakterláncban  
2. **Eszköz regisztráció:** Az eszköznek regisztrálva kell lennie az IoT Hubban  
3. **Tűzfal/proxy:** Engedélyezze a kimenő MQTT (port 8883) vagy HTTPS (port 443) forgalmat  
4. **IoT Hub régió:** Ellenőrizze, hogy az IoT Hub fut-e és nincs-e más régióban, ami késleltetést okozhat  
5. **Kvóta korlátok:** Ellenőrizze, hogy nem lépte-e túl az ingyenes csomag korlátait  
6. **Tesztelje a kapcsolatot:**  
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```
  
#### Probléma: Azure Functions nem indulnak el  
**Tünetek:** Üzenetek elküldve, de a függvény nem fut

**Megoldás:**  
1. Ellenőrizze, hogy a Function App fut-e (nem áll le)  
2. Ellenőrizze a kapcsolati karakterláncot a Function App beállítások között  
3. Nézze meg a függvény naplóit az Azure Portalon  
4. Győződjön meg róla, hogy az Event Hub kompatibilis végpont helyesen van konfigurálva  
5. Ellenőrizze, hogy az üzenet formátuma megfelel-e a függvény elvárásainak  
6. Ellenőrizze a Function App szolgáltatási tervét (fogyasztás vs. dedikált)

### MQTT
#### Probléma: MQTT kapcsolat sikertelen
**Hiba:** Kapcsolat visszautasítva, hitelesítés sikertelen

**Megoldás:**
1. **Broker címe:** Ellenőrizze, hogy a broker URL/IP helyes-e
2. **Port:** Ellenőrizze a port számát (1883 titkosítatlan, 8883 TLS-hez)
3. **Hitelesítés:** Ellenőrizze a felhasználónevet/jelszót, ha szükséges
4. **TLS/SSL:** Biztosítsa, hogy a tanúsítványok érvényesek és megbízhatóak
5. **Tűzfal:** Ellenőrizze, hogy a port nincs blokkolva
6. **Teszt MQTT klienssel:** Használja az MQTT Explorer-t vagy mosquitto_pub/sub-t a teszthez

#### Probléma: MQTT üzenetek nem érkeznek meg
**Tünetek:** Üzenetek meg vannak jelenítve, de a feliratkozók nem kapják meg őket

**Megoldás:**
1. **Téma nevek:** Ellenőrizze, hogy a feliratkozó témája pontosan megegyezik a kiadó témájával
2. **QoS szint:** Próbálja QoS 1 vagy 2 szinten a 0 helyett
3. **Helyettesítők:** Ellenőrizze, hogy a témában a helyettesítők helyesen vannak-e használva (`+` egyszintű, `#` többszintű)
4. **Megőrzött üzenetek:** A kiadó beállíthatja a megőrzés (retain) flag-et az utolsó üzenet megtartásához
5. **Kapcsolat időzítése:** Biztosítsa, hogy a feliratkozó csatlakozik, mielőtt az üzenetek kiadásra kerülnek

---

## Szenzor és Aktuátor problémák

### Grove szenzorok

#### Probléma: A szenzor helytelen értékeket ad vissza
**Tünetek:** Az értékek 0, -1, vagy értelmetlenek

**Megoldás:**
1. **Ellenőrizze a csatlakozásokat:** Biztosítsa, hogy a szenzor megfelelően van csatlakoztatva
2. **Megfelelő port:** Ellenőrizze, hogy a szenzor a megfelelő port típusban van:
   - Analóg szenzorok → Analóg portok (A0, A2, A4)
   - Digitális szenzorok → Digitális portok (D5, D16, D18 stb.)
   - I2C szenzorok → I2C portok
3. **Kalibráció:** Néhány szenzornak szüksége van kalibrációra (talajnedvesség, fény)
4. **Áramtalanítás:** Húzza ki és csatlakoztassa újra a szenzort
5. **Szenzor adatlap:** Ellenőrizze a szenzor specifikációit és követelményeit

#### Probléma: A kapacitív talajnedvesség szenzor mindig vizes értéket mutat
**Tünetek:** A szenzor magas nedvességet jelez, még ha száraz is

**Megoldás:**
1. **Kalibráció szükséges:** A talaj szenzorokat kalibrálni kell:
   - Olvassa le levegőben (száraz alapérték)
   - Olvassa le vízben (nedves alapérték)
   - Térképezze fel az értékeket ezek között
2. **Ellenőrizze a szenzor bevonatát:** A nedvesség szenzorok tönkremehetnek, ha a bevonat megsérül
3. **Elhelyezés:** Biztosítsa, hogy a szenzor teljesen a talajba van szúrva

#### Probléma: A hőmérséklet/páratartalom szenzor rossz értékeket ad
**Tünetek:** DHT11/DHT22 hibás hőmérsékletet vagy páratartalmat mutat

**Megoldás:**
1. **Szenzor elhelyezés:** Kerülje a közvetlen napfényt, hőforrásokat vagy áramlást
2. **Bemelegedési idő:** Adjon a szenzornak 2 másodpercet a bekapcsolás után az olvasáshoz
3. **Olvasási gyakoriság:** A DHT szenzoroknak idő kell az olvasások között (legalább 2 mp)
4. **Kondenzáció ellenőrzése:** Kondenzáció befolyásolhatja a mérést
5. **Szenzor minőség:** A DHT11 kevésbé pontos, mint a DHT22

### Kamera

#### Probléma: Kamera nem észlelhető Raspberry Pi-n
**Hiba:** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**Megoldás:**
1. **Kamera interfész engedélyezése:**
   ```bash
   sudo raspi-config
   ```
   Menjen az Interface Options → Camera → Enable opcióhoz
2. **Szalagkábel ellenőrzése:** Biztosítsa, hogy a kamera kábel megfelelően van bedugva
   - A kék oldal nézzen a Pi Zero USB portjai felé
   - A kék oldal nézzen el az USB portoktól Pi 4 esetén
3. **Firmware frissítés:**
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **Kamera tesztelése:**
   ```bash
   raspistill -o test.jpg
   ```

#### Probléma: A kamera képek rossz minőségűek
**Tünetek:** Homályos, sötét vagy kifakult képek

**Megoldás:**
1. **Fókusz:** Távolítsa el a védőfóliát az objektívről, állítsa be a fókuszt, ha állítható
2. **Világítás:** Biztosítson megfelelő világítást
3. **Kamera beállítások:** Állítsa be az expozíciót, ISO-t, fehéregyensúlyt a kódban
4. **Stabilitás:** Tartsa stabilan a kamerát, szükség esetén használjon állványt
5. **Felbontás:** Ne lépje túl a kamera maximális felbontását

### Mikrofon és Hangszóró

#### Probléma: Nincs hang bemenet/kimenet
**Tünetek:** A mikrofon nem rögzít, a hangszóró nem szólal meg

**Megoldás:**
1. **Csatlakozások ellenőrzése:** Vizsgálja meg, hogy a hangeszközök helyesen vannak-e csatlakoztatva
2. **Hardver tesztelése:**
   - Hangszóró: `speaker-test -t wav -c 2`
   - Mikrofon: `arecord -l` listázáshoz, `arecord test.wav` felvételhez
3. **Hangerő beállítások:** Ellenőrizze és állítsa be a hangerőt:
   ```bash
   alsamixer
   ```
4. **Hang eszköz kiválasztása:** Adja meg a helyes hang eszközt a kódban
5. **Illesztőprogram problémák:** Frissítse az ALSA-t vagy telepítse újra a hangillesztőket

#### Probléma: ReSpeaker hat nem működik
**Tünetek:** Hang eszköz nem érzékelhető

**Megoldás:**
1. **Illesztőprogramok telepítése:**
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **Telepítés ellenőrzése:** Az `arecord -l` listázza a ReSpeaker-t
3. **Firmware frissítés:** Egyes Pi OS verzióknál szükséges az illesztőprogram frissítés
4. **Csatlakozás ellenőrzése:** Biztosítsa, hogy a hat helyesen csatlakozik a GPIO pin-ekhez

---

## Fejlesztői környezeti problémák

### VS Code

#### Probléma: A terminál nem aktiválja automatikusan a virtuális környezetet
**Tünetek:** A terminál megnyílik, de a venv nincs aktiválva

**Megoldás:**
1. **Python értelmező beállítása:** Command Palette → "Python: Select Interpreter" → Válassza ki a venv-et
2. **Indítsa újra a VS Code-ot** az értelmező kiválasztása után
3. **Beállítások ellenőrzése:** A `settings.json`-ban adja hozzá:
   ```json
   "python.terminal.activateEnvironment": true
   ```

#### Probléma: A kód nem fut az eszközön
**Tünetek:** A kód fut, de az eszközön nem történik semmi

**Megoldás:**
1. **Győződjön meg róla, hogy a kód mentve van** (ellenőrizze az aktív fül pontját)
2. **Ellenőrizze, melyik Python fut:** `which python` vagy `where python`
3. **Wio Terminal esetén:** Feltöltés PlatformIO-val (töltés gomb megnyomása)
4. **Raspberry Pi esetén:** SSH-zzen be a Pi-be és futtassa ott a kódot
5. **Ellenőrizze a kimeneti ablakot** hibákért

#### Probléma: IntelliSense nem jeleníti meg a könyvtárfüggvényeket
**Tünetek:** Nincs automatikus kiegészítés a betöltött modulokhoz

**Megoldás:**
1. Győződjön meg arról, hogy a könyvtár telepítve van az aktuális környezetben
2. Töltse újra a VS Code ablakot
3. Ellenőrizze, hogy a helyes Python értelmező van kiválasztva
4. Telepítsen típus stub-okat, ha elérhető: `pip install types-<library-name>`

### Python Virtuális Környezetek

#### Probléma: Nem létrehozható virtuális környezet
**Hiba:** `The virtual environment was not created successfully`

**Megoldás:**
1. **Telepítse a venv modult:**
   - Ubuntu/Debian: `sudo apt install python3-venv`
   - macOS: A Python része kell legyen
   - Windows: Telepítse újra a Pythont minden komponenssel
2. **Ellenőrizze a Python telepítést:** Győződjön meg a helyes telepítésről
3. **Használja a teljes elérési utat:** Próbálja meg `python3 -m venv .venv` paranccsal expliciten a python3-at

#### Probléma: Csomagok rossz helyre települnek
**Tünetek:** Import hiba egy csomag telepítése után

**Megoldás:**
1. **Ellenőrizze, hogy a venv aktív:** A parancssorban meg kell jelennie a `(.venv)`-nek
2. **Ellenőrizze a pip helyét:** `which pip` mutassa a `.venv/bin/pip`-et
3. **Telepítés újra a venv-ben:** Aktiválja a venv-et, majd `pip install <csomag>`
4. **Ne használja a sudo pip-et** virtuális környezetben

#### Probléma: Virtuális környezet nem hordozható
**Tünetek:** A venv nem működik áthelyezés vagy más számítógépen

**Megoldás:**
1. **Ne mozgassa a venv-eket:** Törölje és hozza létre újra az új helyen
2. **Használja a requirements.txt fájlt:**
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **Hozza létre újra a venv-et:**
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # vagy activate.bat Windows rendszeren
   pip install -r requirements.txt
   ```

### Függőségek

#### Probléma: Csomag telepítés sikertelen
**Hiba:** Különféle pip hibák telepítés közben

**Megoldás:**
1. **Frissítse a pip-et:**
   ```bash
   pip install --upgrade pip
   ```
2. **Telepítse az építő eszközöket:**
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`
   - macOS: `xcode-select --install`
   - Windows: Telepítse a Visual Studio Build Tools-ot
3. **Ellenőrizze az internetkapcsolatot**
4. **Használjon másik csomag indexet:** `pip install --index-url https://pypi.org/simple/ <csomag>`
5. **Telepítsen konkrét verziót:** `pip install <csomag>==<verzió>`

#### Probléma: Függőségi konfliktusok
**Hiba:** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**Megoldás:**
1. **Használjon friss virtuális környezetet** minden projekthez
2. **Frissítse a csomagokat:** `pip install --upgrade <csomag>`
3. **Ellenőrizze a függőségeket:** `pip check` a konfliktusok ellenőrzéséhez
4. **Telepítsen kompatibilis verziókat:** Verzió tartományokat adjon meg a requirements.txt-ben

---

## Teljesítmény problémák

### Probléma: A kód lassan fut
**Tünetek:** Késések, időtúllépések, válaszképtelenség

**Megoldás:**
1. **Csökkentse a szenzor olvasási gyakoriságát:** Ne olvasson túl gyakran szenzorokat
2. **Optimalizálja a ciklusokat:** Kerülje a várakozás nélküli foglaltságot, használjon sleep()-et vagy késleltetést
3. **Memória problémák:**
   - Zárja be a nem szükséges alkalmazásokat
   - Szabadítson fel tárhelyet
   - Használja a `top` vagy `htop` parancsokat a Pi-n
4. **SD kártya sebesség:** Használjon gyorsabb SD kártyát vagy SSD-t a Raspberry Pi-hez
5. **Hálózati késések:** Használjon aszinkron műveleteket a hálózati hívásokhoz

### Probléma: Memória kifogyás hibák
**Hiba:** `MemoryError` vagy rendszer lefagyás

**Megoldás:**
1. **Raspberry Pi esetén:**
   - Zárja be a nem szükséges alkalmazásokat
   - Növelje a swap területet
   - Használjon könnyebb operációs rendszert (Lite verzió)
   - Növelje a RAM-ot (Pi 4 esetén 2/4/8GB opciók)
2. **Wio Terminal esetén:**
   - Csökkentse a puffer méreteket
   - Használjon kisebb képeket
   - Optimalizálja a sztring használatot
   - Ellenőrizze a memória szivárgást (nem feloldott memória)

### Probléma: Adatvesztés vagy adatkárosodás
**Tünetek:** Hiányzó üzenetek, sérült fájlok

**Megoldás:**
1. **SD kártya problémák:**
   - Használjon minőségi SD kártyákat (kerülje az olcsó/hamisítottakat)
   - Rendszeres biztonsági mentések
   - Tiszta leállítás (ne húzza ki a tápkábelt)
2. **Puffer túlcsordulás:** Növelje a puffer méretet a kódban
3. **Hálózati megbízhatóság:** Valósítson meg újrapróbálkozási logikát és hibakezelést
4. **Szolgáltatás minősége:** Használja a MQTT QoS 1 vagy 2 szinteket fontos üzenetekhez

---

## Gyakori hibaüzenetek

### `ModuleNotFoundError: No module named 'X'`
**Oka:** Csomag nincs telepítve vagy a virtuális környezet nincs aktiválva

**Megoldás:**
```bash
pip install X
```
Először aktiválja a virtuális környezetet.

### `Permission denied` Linux/macOS rendszereken
**Oka:** Magasabb jogosultság szükséges vagy fájl jogosultság hiba

**Megoldás:**
- Rendszer műveletekhez: Használja a `sudo` parancsot
- Pip esetén: NE használja a sudo pip-et venv alatt, előbb aktiválja a venv-et
- Soros port esetén: Adja a felhasználót a dialout csoporthoz: `sudo usermod -a -G dialout $USER`, majd lépjen ki és be

### `OSError: [Errno 98] Address already in use`
**Oka:** A portot már egy másik folyamat használja

**Megoldás:**
1. Keresse meg a portot használó folyamatot: `lsof -i :<port>` vagy `netstat -ano | findstr :<port>`
2. Állítsa le a folyamatot vagy használjon másik portot a kódban

### `SSL: CERTIFICATE_VERIFY_FAILED`
**Oka:** Az SSL tanúsítvány érvényesítés sikertelen

**Megoldás:**
1. Frissítse a tanúsítványokat: `pip install --upgrade certifi`
2. Ellenőrizze a rendszeridőt: `date`
3. Csak fejlesztéshez (nem élesben): Tiltsa le az ellenőrzést a kódban

### `IndentationError: unexpected indent`
**Oka:** Python behúzási hiba (tab és szóköz keverése)

**Megoldás:**
1. Használjon konzisztens behúzást (4 szóköz a Python szabvány)
2. Állítsa be a szerkesztőt, hogy szóközt használjon tab helyett
3. VS Code-ban: Állítsa be `"editor.insertSpaces": true` és `"editor.tabSize": 4`

### `UnicodeDecodeError` vagy `UnicodeEncodeError`
**Oka:** Karakterkódolási hibák

**Megoldás:**
```python
# Fájlok olvasásakor
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# Fájlok írásakor
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```

---

## Segítségkérés

Ha kipróbálta ezeket a hibakeresési lépéseket és mégis problémái vannak:

### 1. Ellenőrizze a meglévő erőforrásokat
- **Dokumentáció:** Nézze át a [README](README.md) és az órák utasításait
- **Hardver útmutatók:** Nézze meg a [hardware.md](hardware.md) fájlt hardverspecifikus információkért
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) a Grove komponensekhez

### 2. Keressen hasonló problémákat
- **GitHub Issues:** Keressen [létező issue-k között](https://github.com/microsoft/IoT-For-Beginners/issues)
- **Stack Overflow:** Keressen hibaüzenetekre
- **Eszköz fórumok:** Ellenőrizze a Raspberry Pi vagy Arduino fórumokat

### 3. Hozzon létre GitHub Issue-t
Ha nem talál megoldást:
1. Menjen a [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues) oldalra
2. Kattintson az "New Issue" gombra
3. Adja meg:
   - Világos problémaleírást
   - A reprodukció lépéseit
   - Hibaüzenetek teljes szövegét
   - Hardver/szoftver verziókat
   - Mit próbált már meg
   - Képeket, ha releváns

### 4. Csatlakozzon a közösséghez
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. Küldjön jó hibajelentést
Egy jó hibajelentés tartalmazza:
- **Környezet:** Operációs rendszer, Python verzió, használt hardver
- **Lépések a hiba reprodukálásához:** Pontos lépések, amelyek előidézik a problémát
- **Várható viselkedés:** Mi történne elvileg
- **Tényleges viselkedés:** Mi történik valójában
- **Hibajelzések:** Teljes hibaüzenet szövege, nem képernyőképek
- **Kód:** Minimális kódpélda, amely reprodukálja a hibát

---

## Megelőzési tippek

### Általános legjobb gyakorlatok
1. **Készíts biztonsági mentést:** Rendszeresen mentsd le a működő SD kártyákat/kódokat
2. **Dokumentáld a változásokat:** Jegyezd fel, mi működik a kommentekben
3. **Használj verziókezelést:** Kövesd nyomon a kódváltoztatásokat git segítségével
4. **Tesztelj fokozatosan:** Próbáld ki a kisebb változtatásokat, mielőtt összevonod őket
5. **Olvasd el a hibajelzéseket:** Gyakran pontosan megmondják, mi a gond
6. **Frissíts rendszeresen:** Tartsd naprakészen a szoftvert/firmware-t
7. **Használj minőségi alkatrészeket:** Kerüld az olcsó kábeleket/tápegységeket
8. **Biztosíts stabil áramellátást:** Használj megfelelő tápegységet (különösen Pi esetén)

### Fejlesztési munkafolyamat
1. **Kezdj egyszerűvel:** Indulj működő példakóddal
2. **Egyszerre csak egy változtatást végezz:** Könnyebb megtalálni, mi törik el
3. **Gyakran tesztelj:** Így korán észreveheted a problémákat
4. **Tarts rendet:** Strukturáld logikusan a fájlokat és a kódot
5. **Kommentáld a kódot:** A jövőbeni önmagad hálás lesz érte

---

*Ezt a hibakeresési útmutatót a közösség tartja karban. Ha találsz megoldást olyan problémára, amely itt nincs felsorolva, kérjük, fontold meg, hogy [hozzájárulsz](CONTRIBUTING.md), hogy másoknak is segíts!*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**Figyelmeztetés**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével készült. Bár a pontosságra törekszünk, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az anyanyelvén tekintendő hivatalos forrásnak. Fontos információk esetén szakmai, emberi fordítást javaslunk. Nem vállalunk felelősséget a fordítás használatából eredő félreértésekért vagy értelmezési hibákért.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->