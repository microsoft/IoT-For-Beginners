<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-25T20:41:16+00:00",
  "source_file": "hardware.md",
  "language_code": "de"
}
-->
# Hardware

Das **T** in IoT steht für **Things** und bezieht sich auf Geräte, die mit der Umgebung interagieren. Jedes Projekt basiert auf realer Hardware, die für Studenten und Hobbyisten verfügbar ist. Wir haben zwei Optionen für IoT-Hardware, je nach persönlicher Vorliebe, Programmierkenntnissen, Lernzielen und Verfügbarkeit. Zusätzlich bieten wir eine 'virtuelle Hardware'-Version für diejenigen an, die keinen Zugang zu physischer Hardware haben oder sich vor einem Kauf genauer informieren möchten.

> 💁 Sie müssen keine IoT-Hardware kaufen, um die Aufgaben zu erledigen. Alles kann mit virtueller IoT-Hardware durchgeführt werden.

Die physische Hardware-Auswahl umfasst Arduino oder Raspberry Pi. Jede Plattform hat ihre eigenen Vor- und Nachteile, die in einer der ersten Lektionen behandelt werden. Falls Sie sich noch nicht für eine Hardware-Plattform entschieden haben, können Sie [Lektion zwei des ersten Projekts](./1-getting-started/lessons/2-deeper-dive/README.md) durchsehen, um herauszufinden, welche Plattform Sie am meisten interessiert.

Die spezifische Hardware wurde ausgewählt, um die Komplexität der Lektionen und Aufgaben zu reduzieren. Obwohl andere Hardware möglicherweise funktioniert, können wir nicht garantieren, dass alle Aufgaben auf Ihrem Gerät ohne zusätzliche Hardware unterstützt werden. Zum Beispiel haben viele Arduino-Geräte kein WLAN, das für die Verbindung mit der Cloud benötigt wird – das Wio Terminal wurde ausgewählt, da es über integriertes WLAN verfügt.

Sie benötigen außerdem einige nicht-technische Gegenstände, wie Erde oder eine Topfpflanze sowie Obst oder Gemüse.

## Kits kaufen

![Das Seeed Studios Logo](../../translated_images/de/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios haben freundlicherweise alle Hardware als einfach zu kaufende Kits bereitgestellt:

### Arduino - Wio Terminal

**[IoT für Anfänger mit Seeed und Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Das Wio Terminal Hardware Kit](../../translated_images/de/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT für Anfänger mit Seeed und Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Das Raspberry Pi Terminal Hardware Kit](../../translated_images/de/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Der gesamte Gerätecode für Arduino ist in C++. Um alle Aufgaben zu erledigen, benötigen Sie Folgendes:

### Arduino Hardware

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Optional* - USB-C-Kabel oder USB-A-zu-USB-C-Adapter. Das Wio Terminal hat einen USB-C-Anschluss und wird mit einem USB-C-zu-USB-A-Kabel geliefert. Wenn Ihr PC oder Mac nur USB-C-Anschlüsse hat, benötigen Sie ein USB-C-Kabel oder einen USB-A-zu-USB-C-Adapter.

### Arduino-spezifische Sensoren und Aktoren

Diese sind spezifisch für die Verwendung des Wio Terminal Arduino-Geräts und nicht relevant für die Verwendung des Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Kopfhörer oder andere Lautsprecher mit einem 3,5-mm-Stecker oder ein JST-Lautsprecher wie:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD-Karte mit 16 GB oder weniger sowie ein Adapter, um die SD-Karte mit Ihrem Computer zu verwenden, falls dieser keinen eingebauten Kartenleser hat. **HINWEIS** - Das Wio Terminal unterstützt nur SD-Karten bis zu 16 GB, größere Kapazitäten werden nicht unterstützt.

## Raspberry Pi

Der gesamte Gerätecode für Raspberry Pi ist in Python. Um alle Aufgaben zu erledigen, benötigen Sie Folgendes:

### Raspberry Pi Hardware

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versionen ab dem Pi 2B sollten mit den Aufgaben in diesen Lektionen funktionieren. Wenn Sie VS Code direkt auf dem Pi ausführen möchten, benötigen Sie einen Pi 4 mit 2 GB oder mehr RAM. Wenn Sie den Pi remote verwenden, funktioniert jeder Pi ab Version 2B.
* microSD-Karte (Es gibt Raspberry Pi Kits, die mit einer microSD-Karte geliefert werden) sowie ein Adapter, um die SD-Karte mit Ihrem Computer zu verwenden, falls dieser keinen eingebauten Kartenleser hat.
* USB-Stromversorgung (Es gibt Raspberry Pi 4 Kits, die mit einer Stromversorgung geliefert werden). Wenn Sie einen Raspberry Pi 4 verwenden, benötigen Sie eine USB-C-Stromversorgung, ältere Geräte benötigen eine micro-USB-Stromversorgung.

### Raspberry Pi-spezifische Sensoren und Aktoren

Diese sind spezifisch für die Verwendung des Raspberry Pi und nicht relevant für die Verwendung des Arduino-Geräts.

* [Grove Pi Base Hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Kamera-Modul](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon und Lautsprecher:

  Verwenden Sie eines der folgenden (oder ein Äquivalent):
  * Jedes USB-Mikrofon mit jedem USB-Lautsprecher oder Lautsprecher mit einem 3,5-mm-Kabel oder HDMI-Audioausgang, falls Ihr Raspberry Pi mit einem Monitor oder Fernseher mit Lautsprechern verbunden ist
  * Jedes USB-Headset mit eingebautem Mikrofon
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) mit
    * Kopfhörer oder andere Lautsprecher mit einem 3,5-mm-Stecker oder ein JST-Lautsprecher wie:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light Sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove Button](https://www.seeedstudio.com/Grove-Button.html)

## Sensoren und Aktoren

Die meisten der benötigten Sensoren und Aktoren werden sowohl in den Arduino- als auch in den Raspberry Pi-Lernpfaden verwendet:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove Feuchtigkeits- und Temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapazitiver Bodenfeuchtigkeitssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove Relais](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of Flight Distanzsensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Optionale Hardware

Die Lektionen zur automatisierten Bewässerung funktionieren mit einem Relais. Optional können Sie dieses Relais mit einer USB-betriebenen Wasserpumpe verbinden, indem Sie die unten aufgeführte Hardware verwenden.

* [6V Wasserpumpe](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB Terminal](https://www.adafruit.com/product/3628)
* Silikonschläuche
* Rote und schwarze Kabel
* Kleiner Schlitzschraubendreher

## Virtuelle Hardware

Die virtuelle Hardware-Option bietet Simulatoren für die Sensoren und Aktoren, die in Python implementiert sind. Je nach Verfügbarkeit Ihrer Hardware können Sie dies auf Ihrem normalen Entwicklungsgerät wie einem Mac oder PC ausführen oder auf einem Raspberry Pi, um nur die Hardware zu simulieren, die Sie nicht besitzen. Wenn Sie beispielsweise die Raspberry Pi Kamera haben, aber nicht die Grove-Sensoren, können Sie den virtuellen Gerätecode auf Ihrem Pi ausführen, die Grove-Sensoren simulieren und die physische Kamera verwenden.

Die virtuelle Hardware wird das [CounterFit Projekt](https://github.com/CounterFit-IoT/CounterFit) verwenden.

Um diese Lektionen abzuschließen, benötigen Sie eine Webcam, ein Mikrofon und Audioausgabe wie Lautsprecher oder Kopfhörer. Diese können eingebaut oder extern sein und müssen so konfiguriert sein, dass sie mit Ihrem Betriebssystem funktionieren und von allen Anwendungen genutzt werden können.

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.