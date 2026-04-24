# Hardvér

**T** v IoT znamená **Things** (Veci) a odkazuje na zariadenia, ktoré interagujú s okolím. Každý projekt je založený na reálnom hardvéri, ktorý je dostupný pre študentov a nadšencov. Máme dve možnosti IoT hardvéru, ktoré môžete použiť v závislosti od vašich preferencií, znalostí programovacích jazykov, cieľov učenia a dostupnosti. Poskytli sme aj verziu „virtuálneho hardvéru“ pre tých, ktorí nemajú prístup k fyzickému hardvéru alebo sa chcú najprv naučiť viac, než sa rozhodnú pre kúpu.

> 💁 Na dokončenie úloh nie je potrebné zakúpiť žiadny IoT hardvér. Všetko môžete urobiť pomocou virtuálneho IoT hardvéru.

Fyzické hardvérové možnosti sú Arduino alebo Raspberry Pi. Každá platforma má svoje výhody a nevýhody, ktoré sú podrobne vysvetlené v jednej z úvodných lekcií. Ak ste sa ešte nerozhodli pre konkrétnu hardvérovú platformu, môžete si pozrieť [druhú lekciu prvého projektu](./1-getting-started/lessons/2-deeper-dive/README.md), aby ste zistili, ktorá platforma vás najviac zaujíma.

Konkrétny hardvér bol vybraný tak, aby znížil zložitosť lekcií a úloh. Aj keď iný hardvér môže fungovať, nemôžeme zaručiť, že všetky úlohy budú podporované na vašom zariadení bez dodatočného hardvéru. Napríklad veľa zariadení Arduino nemá WiFi, ktoré je potrebné na pripojenie ku cloudu – Wio terminál bol vybraný, pretože má WiFi zabudované.

Budete tiež potrebovať niekoľko netechnických položiek, ako je pôda alebo črepníková rastlina a ovocie alebo zelenina.

## Kúpa súprav

![Logo Seeed studios](../../translated_images/sk/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios veľmi láskavo sprístupnili všetok hardvér vo forme ľahko zakúpiteľných súprav:

### Arduino - Wio Terminal

**[IoT pre začiatočníkov so Seeed a Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Hardvérová súprava Wio Terminal](../../translated_images/sk/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT pre začiatočníkov so Seeed a Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Hardvérová súprava Raspberry Pi](../../translated_images/sk/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Všetok kód pre zariadenia Arduino je napísaný v jazyku C++. Na dokončenie všetkých úloh budete potrebovať nasledujúce:

### Hardvér pre Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Voliteľné* - USB-C kábel alebo USB-A na USB-C adaptér. Wio terminál má USB-C port a dodáva sa s USB-C na USB-A káblom. Ak váš PC alebo Mac má iba USB-C porty, budete potrebovať USB-C kábel alebo USB-A na USB-C adaptér.

### Špecifické senzory a akčné členy pre Arduino

Tieto sú špecifické pre zariadenie Wio Terminal Arduino a nie sú relevantné pre Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Prepojovacie vodiče pre breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Slúchadlá alebo iný reproduktor s 3,5mm konektorom, alebo JST reproduktor, napríklad:
  * [Mono uzavretý reproduktor - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD karta s kapacitou 16GB alebo menej, spolu s adaptérom na použitie SD karty s vaším počítačom, ak nemáte zabudovaný slot. **POZNÁMKA** - Wio Terminal podporuje iba SD karty do 16GB, vyššie kapacity nie sú podporované.

## Raspberry Pi

Všetok kód pre zariadenia Raspberry Pi je napísaný v jazyku Python. Na dokončenie všetkých úloh budete potrebovať nasledujúce:

### Hardvér pre Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Verzie od Pi 2B a vyššie by mali fungovať s úlohami v týchto lekciách. Ak plánujete spustiť VS Code priamo na Pi, potom je potrebné Pi 4 s 2GB alebo viac RAM. Ak budete k Pi pristupovať vzdialene, bude fungovať akékoľvek Pi 2B a vyššie.
* microSD karta (Môžete si zakúpiť Raspberry Pi súpravy, ktoré obsahujú microSD kartu), spolu s adaptérom na použitie SD karty s vaším počítačom, ak nemáte zabudovaný slot.
* USB napájací zdroj (Môžete si zakúpiť Raspberry Pi 4 súpravy, ktoré obsahujú napájací zdroj). Ak používate Raspberry Pi 4, potrebujete USB-C napájací zdroj, staršie zariadenia potrebujú micro-USB napájací zdroj.

### Špecifické senzory a akčné členy pre Raspberry Pi

Tieto sú špecifické pre Raspberry Pi a nie sú relevantné pre zariadenie Arduino.

* [Grove Pi základný HAT](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Kamera modul pre Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofón a reproduktor:

  Použite jedno z nasledujúcich (alebo ekvivalent):
  * Akýkoľvek USB mikrofón s akýmkoľvek USB reproduktorom, alebo reproduktor s 3,5mm jack káblom, alebo použitie HDMI audio výstupu, ak je vaše Raspberry Pi pripojené k monitoru alebo TV s reproduktormi
  * Akékoľvek USB slúchadlá s integrovaným mikrofónom
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) s
    * Slúchadlami alebo iným reproduktorom s 3,5mm konektorom, alebo JST reproduktorom, napríklad:
    * [Mono uzavretý reproduktor - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove svetelný senzor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove tlačidlo](https://www.seeedstudio.com/Grove-Button.html)

## Senzory a akčné členy

Väčšina senzorov a akčných členov potrebných pre lekcie sa používa v oboch učebných cestách pre Arduino aj Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove senzor vlhkosti a teploty](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapacitný senzor vlhkosti pôdy](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relé](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove senzor vzdialenosti Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Voliteľný hardvér

Lekcie o automatickom zavlažovaní fungujú pomocou relé. Ako možnosť môžete toto relé pripojiť k vodnému čerpadlu napájanému cez USB pomocou nižšie uvedeného hardvéru.

* [6V vodné čerpadlo](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminál](https://www.adafruit.com/product/3628)
* Silikónové hadičky
* Červené a čierne vodiče
* Malý plochý skrutkovač

## Virtuálny hardvér

Virtuálna hardvérová cesta poskytne simulátory pre senzory a akčné členy, implementované v jazyku Python. V závislosti od dostupnosti vášho hardvéru môžete toto spustiť na vašom bežnom vývojovom zariadení, ako je Mac, PC, alebo na Raspberry Pi a simulovať iba hardvér, ktorý nemáte. Napríklad, ak máte kameru Raspberry Pi, ale nie Grove senzory, budete môcť spustiť kód virtuálneho zariadenia na vašom Pi a simulovať Grove senzory, ale použiť fyzickú kameru.

Virtuálny hardvér bude používať [projekt CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Na dokončenie týchto lekcií budete potrebovať webovú kameru, mikrofón a audio výstup, ako sú reproduktory alebo slúchadlá. Tieto môžu byť zabudované alebo externé a musia byť nakonfigurované tak, aby fungovali s vaším operačným systémom a boli dostupné pre všetky aplikácie.

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.