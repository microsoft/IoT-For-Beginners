# Hardware

**T** v IoT znamená **Things** (věci) a odkazuje na zařízení, která interagují s okolním světem. Každý projekt je založen na reálném hardwaru dostupném studentům a nadšencům. Máme dvě možnosti IoT hardwaru, které lze použít v závislosti na osobních preferencích, znalostech programovacích jazyků, cílech učení a dostupnosti. Pro ty, kteří nemají přístup k hardwaru nebo se chtějí nejprve více naučit, než se rozhodnou pro nákup, jsme také poskytli verzi „virtuálního hardwaru“.

> 💁 K dokončení úkolů není nutné kupovat žádný IoT hardware. Vše můžete provést pomocí virtuálního IoT hardwaru.

Fyzické hardwarové možnosti jsou Arduino nebo Raspberry Pi. Každá platforma má své výhody a nevýhody, které jsou podrobně popsány v jedné z úvodních lekcí. Pokud jste se ještě nerozhodli pro konkrétní hardwarovou platformu, můžete si projít [druhou lekci prvního projektu](./1-getting-started/lessons/2-deeper-dive/README.md), abyste zjistili, která platforma vás nejvíce zajímá.

Konkrétní hardware byl vybrán tak, aby se snížila složitost lekcí a úkolů. Ačkoli jiný hardware může fungovat, nemůžeme zaručit, že všechny úkoly budou podporovány na vašem zařízení bez dodatečného hardwaru. Například mnoho zařízení Arduino nemá WiFi, což je potřeba pro připojení ke cloudu – Wio terminal byl vybrán, protože má WiFi integrované.

Budete také potřebovat několik netechnických položek, jako je půda nebo květináč, a ovoce nebo zeleninu.

## Koupit sady

![Logo Seeed Studios](../../translated_images/cs/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios velmi laskavě zpřístupnili veškerý hardware jako snadno zakoupitelné sady:

### Arduino - Wio Terminal

**[IoT pro začátečníky se Seeed a Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Sada hardwaru Wio Terminal](../../translated_images/cs/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT pro začátečníky se Seeed a Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Sada hardwaru Raspberry Pi Terminal](../../translated_images/cs/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Veškerý kód zařízení pro Arduino je napsán v C++. K dokončení všech úkolů budete potřebovat následující:

### Hardware Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Volitelné* - USB-C kabel nebo adaptér USB-A na USB-C. Wio terminal má USB-C port a je dodáván s USB-C na USB-A kabelem. Pokud váš PC nebo Mac má pouze USB-C porty, budete potřebovat USB-C kabel nebo adaptér USB-A na USB-C.

### Specifické senzory a akční členy pro Arduino

Tyto komponenty jsou specifické pro zařízení Arduino Wio terminal a nejsou relevantní pro použití Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Propojovací vodiče pro breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Sluchátka nebo jiný reproduktor s 3,5mm jackem, nebo reproduktor JST, například:
  * [Mono uzavřený reproduktor - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD karta 16GB nebo méně, spolu s konektorem pro použití SD karty s vaším počítačem, pokud nemáte vestavěný. **POZNÁMKA** - Wio Terminal podporuje pouze SD karty do 16GB, vyšší kapacity nejsou podporovány.

## Raspberry Pi

Veškerý kód zařízení pro Raspberry Pi je napsán v Pythonu. K dokončení všech úkolů budete potřebovat následující:

### Hardware Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Verze od Pi 2B a výše by měly fungovat s úkoly v těchto lekcích. Pokud plánujete spouštět VS Code přímo na Pi, pak je potřeba Pi 4 s 2GB nebo více RAM. Pokud budete k Pi přistupovat vzdáleně, pak bude fungovat jakékoli Pi 2B a výše.
* microSD karta (Můžete získat sady Raspberry Pi, které obsahují microSD kartu), spolu s konektorem pro použití SD karty s vaším počítačem, pokud nemáte vestavěný.
* USB napájecí zdroj (Můžete získat sady Raspberry Pi 4, které obsahují napájecí zdroj). Pokud používáte Raspberry Pi 4, potřebujete USB-C napájecí zdroj, starší zařízení potřebují micro-USB napájecí zdroj.

### Specifické senzory a akční členy pro Raspberry Pi

Tyto komponenty jsou specifické pro použití Raspberry Pi a nejsou relevantní pro zařízení Arduino.

* [Grove Pi základní HAT](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Kamera modul Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon a reproduktor:

  Použijte jednu z následujících možností (nebo ekvivalent):
  * Jakýkoli USB mikrofon s jakýmkoli USB reproduktorem, nebo reproduktor s 3,5mm jackem, nebo použití HDMI audio výstupu, pokud je vaše Raspberry Pi připojeno k monitoru nebo TV s reproduktory
  * Jakákoli USB náhlavní souprava s vestavěným mikrofonem
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) s
    * Sluchátka nebo jiný reproduktor s 3,5mm jackem, nebo reproduktor JST, například:
    * [Mono uzavřený reproduktor - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove světelný senzor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove tlačítko](https://www.seeedstudio.com/Grove-Button.html)

## Senzory a akční členy

Většina senzorů a akčních členů potřebných je používána jak v Arduino, tak v Raspberry Pi učebních cestách:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove senzor vlhkosti a teploty](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapacitní senzor vlhkosti půdy](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relé](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove senzor vzdálenosti Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Volitelný hardware

Lekce o automatickém zavlažování fungují pomocí relé. Jako volitelnou možnost můžete toto relé připojit k vodnímu čerpadlu napájenému přes USB pomocí níže uvedeného hardwaru.

* [6V vodní čerpadlo](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminál](https://www.adafruit.com/product/3628)
* Silikonové trubky
* Červené a černé vodiče
* Malý plochý šroubovák

## Virtuální hardware

Virtuální hardwarová cesta poskytne simulátory pro senzory a akční členy, implementované v Pythonu. V závislosti na dostupnosti vašeho hardwaru můžete toto spustit na vašem běžném vývojovém zařízení, jako je Mac, PC, nebo na Raspberry Pi a simulovat pouze hardware, který nemáte. Například pokud máte kameru Raspberry Pi, ale nemáte Grove senzory, budete moci spustit virtuální kód zařízení na vašem Pi a simulovat Grove senzory, ale použít fyzickou kameru.

Virtuální hardware bude používat projekt [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

K dokončení těchto lekcí budete potřebovat webovou kameru, mikrofon a audio výstup, jako jsou reproduktory nebo sluchátka. Tyto komponenty mohou být vestavěné nebo externí a musí být nakonfigurovány tak, aby fungovaly s vaším operačním systémem a byly dostupné pro použití ve všech aplikacích.

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.