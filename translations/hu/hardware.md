# Hardver

Az IoT-ban a **T** a **Things** (Dolgok) szót jelenti, és azokra az eszközökre utal, amelyek kölcsönhatásba lépnek a körülöttünk lévő világgal. Minden projekt valós hardvereken alapul, amelyek elérhetők diákok és hobbi fejlesztők számára. Kétféle IoT hardver közül választhatunk, attól függően, hogy milyen személyes preferenciáink, programozási nyelvismeretünk vagy tanulási céljaink vannak, illetve mi érhető el számunkra. Emellett biztosítottunk egy "virtuális hardver" verziót is azok számára, akik nem férnek hozzá fizikai hardverhez, vagy többet szeretnének tanulni, mielőtt vásárlás mellett döntenének.

> 💁 Nem szükséges IoT hardvert vásárolnod a feladatok elvégzéséhez. Minden elvégezhető virtuális IoT hardver használatával.

A fizikai hardverek közül választható az Arduino vagy a Raspberry Pi. Mindegyik platformnak megvannak a maga előnyei és hátrányai, amelyeket az egyik kezdeti leckében részletesen tárgyalunk. Ha még nem döntöttél a hardverplatformról, átnézheted [az első projekt második leckéjét](./1-getting-started/lessons/2-deeper-dive/README.md), hogy eldöntsd, melyik hardverplatform érdekel leginkább.

A konkrét hardvereket úgy választottuk ki, hogy csökkentsük a leckék és feladatok bonyolultságát. Bár más hardverek is működhetnek, nem garantálhatjuk, hogy minden feladat támogatott lesz az eszközödön további hardver nélkül. Például sok Arduino eszköz nem rendelkezik WiFi-vel, amely szükséges a felhőhöz való csatlakozáshoz – a Wio terminált azért választottuk, mert beépített WiFi-vel rendelkezik.

Szükséged lesz néhány nem technikai elemre is, például földre vagy egy cserepes növényre, valamint gyümölcsre vagy zöldségre.

## Készletek vásárlása

![A Seeed Studios logója](../../translated_images/hu/seeed-logo.74732b6b482b6e8e.webp)

A Seeed Studios nagyon kedvesen elérhetővé tette az összes hardvert könnyen megvásárolható készletek formájában:

### Arduino - Wio Terminal

**[IoT kezdőknek a Seeed és a Microsoft segítségével - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![A Wio Terminal hardverkészlet](../../translated_images/hu/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT kezdőknek a Seeed és a Microsoft segítségével - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![A Raspberry Pi Terminal hardverkészlet](../../translated_images/hu/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Az Arduino eszközökhöz tartozó kód C++ nyelven íródott. Az összes feladat elvégzéséhez a következőkre lesz szükséged:

### Arduino hardver

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opcionális* - USB-C kábel vagy USB-A–USB-C adapter. A Wio terminál USB-C porttal rendelkezik, és USB-C–USB-A kábellel érkezik. Ha a számítógéped vagy Mac-ed csak USB-C portokkal rendelkezik, szükséged lesz egy USB-C kábelre vagy egy USB-A–USB-C adapterre.

### Arduino specifikus szenzorok és aktuátorok

Ezek kifejezetten a Wio terminál Arduino eszközhöz kapcsolódnak, és nem relevánsak a Raspberry Pi használata esetén.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Fejhallgató vagy más hangszóró 3,5 mm-es jack csatlakozóval, vagy egy JST hangszóró, például:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD kártya 16 GB vagy kisebb kapacitással, valamint egy csatlakozó, hogy a kártyát a számítógéppel használhasd, ha az nem rendelkezik beépített olvasóval. **MEGJEGYZÉS** - a Wio Terminal csak 16 GB-ig támogatja az SD kártyákat, nagyobb kapacitásokat nem.

## Raspberry Pi

A Raspberry Pi eszközökhöz tartozó kód Python nyelven íródott. Az összes feladat elvégzéséhez a következőkre lesz szükséged:

### Raspberry Pi hardver

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 A Pi 2B és újabb verziók működni fognak ezekkel a feladatokkal. Ha közvetlenül a Pi-n szeretnéd futtatni a VS Code-ot, akkor egy 2 GB vagy nagyobb RAM-mal rendelkező Pi 4-re lesz szükséged. Ha távolról szeretnéd elérni a Pi-t, akkor bármelyik Pi 2B vagy újabb verzió megfelelő.
* microSD kártya (Vannak Raspberry Pi készletek, amelyek tartalmaznak microSD kártyát), valamint egy csatlakozó, hogy a kártyát a számítógéppel használhasd, ha az nem rendelkezik beépített olvasóval.
* USB tápegység (Vannak Raspberry Pi 4 készletek, amelyek tartalmaznak tápegységet). Ha Raspberry Pi 4-et használsz, USB-C tápegységre lesz szükséged, korábbi eszközökhöz pedig micro-USB tápegységre.

### Raspberry Pi specifikus szenzorok és aktuátorok

Ezek kifejezetten a Raspberry Pi-hez kapcsolódnak, és nem relevánsak az Arduino eszköz használata esetén.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon és hangszóró:

  Használj egyet az alábbiak közül (vagy ezek megfelelőjét):
  * Bármilyen USB mikrofon bármilyen USB hangszóróval, vagy hangszóró 3,5 mm-es jack kábellel, vagy HDMI audio kimenet, ha a Raspberry Pi-t hangszóróval rendelkező monitorhoz vagy TV-hez csatlakoztatod
  * Bármilyen USB headset beépített mikrofonnal
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) a következőkkel:
    * Fejhallgató vagy más hangszóró 3,5 mm-es jack csatlakozóval, vagy egy JST hangszóró, például:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Szenzorok és aktuátorok

A legtöbb szükséges szenzor és aktuátor mind az Arduino, mind a Raspberry Pi tanulási útvonalakhoz használható:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove páratartalom- és hőmérséklet-érzékelő](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapacitív talajnedvesség-érzékelő](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relé](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight távolságérzékelő](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Opcionális hardver

Az automatikus öntözésről szóló leckék relét használnak. Opcionálisan csatlakoztathatod ezt a relét egy USB-ről működő vízpumpához az alábbi hardverek segítségével.

* [6V vízpumpa](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminál](https://www.adafruit.com/product/3628)
* Szilikon csövek
* Piros és fekete vezetékek
* Kis laposfejű csavarhúzó

## Virtuális hardver

A virtuális hardver útvonal szimulátorokat biztosít a szenzorokhoz és aktuátorokhoz, Pythonban megvalósítva. A rendelkezésre álló hardveredtől függően futtathatod ezt a normál fejlesztői eszközödön, például Mac-en vagy PC-n, vagy futtathatod Raspberry Pi-n, és csak azokat a hardvereket szimulálhatod, amelyekkel nem rendelkezel. Például, ha van Raspberry Pi kamerád, de nincsenek Grove szenzoraid, akkor futtathatod a virtuális eszközkódot a Pi-n, és szimulálhatod a Grove szenzorokat, miközben a fizikai kamerát használod.

A virtuális hardver a [CounterFit projektet](https://github.com/CounterFit-IoT/CounterFit) fogja használni.

Ezeknek a leckéknek az elvégzéséhez szükséged lesz egy webkamerára, mikrofonra és hangkimenetre, például hangszóróra vagy fejhallgatóra. Ezek lehetnek beépítettek vagy külsők, és úgy kell konfigurálni őket, hogy működjenek az operációs rendszereddel, és minden alkalmazás számára elérhetők legyenek.

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.