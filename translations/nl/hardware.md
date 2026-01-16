<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T20:24:13+00:00",
  "source_file": "hardware.md",
  "language_code": "nl"
}
-->
# Hardware

De **T** in IoT staat voor **Things** en verwijst naar apparaten die interactie hebben met de wereld om ons heen. Elk project is gebaseerd op fysieke hardware die beschikbaar is voor studenten en hobbyisten. We hebben twee keuzes voor IoT-hardware, afhankelijk van persoonlijke voorkeur, programmeertaalkennis of voorkeuren, leerdoelen en beschikbaarheid. Daarnaast hebben we een 'virtuele hardware'-versie beschikbaar gesteld voor degenen die geen toegang hebben tot hardware, of meer willen leren voordat ze een aankoop doen.

> 💁 Je hoeft geen IoT-hardware aan te schaffen om de opdrachten te voltooien. Alles kan gedaan worden met virtuele IoT-hardware.

De fysieke hardware-opties zijn Arduino of Raspberry Pi. Elk platform heeft zijn eigen voordelen en nadelen, die allemaal worden behandeld in een van de eerste lessen. Als je nog niet hebt besloten welk hardwareplatform je wilt gebruiken, kun je [les twee van het eerste project](./1-getting-started/lessons/2-deeper-dive/README.md) bekijken om te bepalen welk platform je het meest interesseert.

De specifieke hardware is gekozen om de complexiteit van de lessen en opdrachten te verminderen. Hoewel andere hardware mogelijk werkt, kunnen we niet garanderen dat alle opdrachten worden ondersteund op jouw apparaat zonder extra hardware. Bijvoorbeeld, veel Arduino-apparaten hebben geen WiFi, wat nodig is om verbinding te maken met de cloud - de Wio Terminal is gekozen omdat deze WiFi ingebouwd heeft.

Je hebt ook een paar niet-technische items nodig, zoals aarde of een kamerplant, en fruit of groenten.

## Koop de kits

![Het logo van Seeed Studios](../../translated_images/nl/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios heeft heel vriendelijk alle hardware beschikbaar gemaakt als eenvoudig te kopen kits:

### Arduino - Wio Terminal

**[IoT voor beginners met Seeed en Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![De Wio Terminal hardware kit](../../translated_images/nl/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT voor beginners met Seeed en Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![De Raspberry Pi Terminal hardware kit](../../translated_images/nl/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Alle apparaatcode voor Arduino is geschreven in C++. Om alle opdrachten te voltooien heb je het volgende nodig:

### Arduino hardware

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Optioneel* - USB-C kabel of USB-A naar USB-C adapter. De Wio Terminal heeft een USB-C poort en wordt geleverd met een USB-C naar USB-A kabel. Als je PC of Mac alleen USB-C poorten heeft, heb je een USB-C kabel of een USB-A naar USB-C adapter nodig.

### Arduino specifieke sensoren en actuatoren

Deze zijn specifiek voor het gebruik van het Wio Terminal Arduino-apparaat en zijn niet relevant voor het gebruik van de Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Koptelefoon of andere speaker met een 3.5mm jack, of een JST speaker zoals:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD-kaart van 16GB of minder, samen met een connector om de SD-kaart te gebruiken met je computer als je geen ingebouwde kaartlezer hebt. **NOTE** - de Wio Terminal ondersteunt alleen SD-kaarten tot 16GB, hogere capaciteiten worden niet ondersteund.

## Raspberry Pi

Alle apparaatcode voor Raspberry Pi is geschreven in Python. Om alle opdrachten te voltooien heb je het volgende nodig:

### Raspberry Pi hardware

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versies vanaf de Pi 2B en hoger zouden moeten werken met de opdrachten in deze lessen. Als je van plan bent om VS Code direct op de Pi te draaien, dan is een Pi 4 met 2GB of meer RAM nodig. Als je de Pi op afstand gaat benaderen, dan werkt elke Pi 2B en hoger.
* microSD-kaart (Je kunt Raspberry Pi-kits krijgen die worden geleverd met een microSD-kaart), samen met een connector om de SD-kaart te gebruiken met je computer als je geen ingebouwde kaartlezer hebt.
* USB-voeding (Je kunt Raspberry Pi 4-kits krijgen die worden geleverd met een voeding). Als je een Raspberry Pi 4 gebruikt, heb je een USB-C voeding nodig, eerdere apparaten hebben een micro-USB voeding nodig.

### Raspberry Pi specifieke sensoren en actuatoren

Deze zijn specifiek voor het gebruik van de Raspberry Pi en zijn niet relevant voor het gebruik van het Arduino-apparaat.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Microfoon en speaker:

  Gebruik een van de volgende (of een equivalent):
  * Elke USB-microfoon met elke USB-speaker, of een speaker met een 3.5mm jack kabel, of gebruik HDMI-audio-uitgang als je Raspberry Pi is aangesloten op een monitor of TV met speakers
  * Elke USB-headset met ingebouwde microfoon
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) met
    * Koptelefoon of andere speaker met een 3.5mm jack, of een JST speaker zoals:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Sensoren en actuatoren

De meeste sensoren en actuatoren die nodig zijn, worden gebruikt door zowel de Arduino- als Raspberry Pi-leertrajecten:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove vochtigheids- en temperatuursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove capacitieve bodemvochtigheidssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relais](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Optionele hardware

De lessen over geautomatiseerd water geven werken met een relais. Als optie kun je dit relais aansluiten op een waterpomp die wordt aangedreven via USB met de hieronder vermelde hardware.

* [6V waterpomp](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminal](https://www.adafruit.com/product/3628)
* Siliconen slangen
* Rode en zwarte draden
* Kleine platte schroevendraaier

## Virtuele hardware

De virtuele hardware-route biedt simulators voor de sensoren en actuatoren, geïmplementeerd in Python. Afhankelijk van je hardwarebeschikbaarheid kun je dit uitvoeren op je normale ontwikkelapparaat, zoals een Mac, PC, of op een Raspberry Pi en alleen de hardware simuleren die je niet hebt. Bijvoorbeeld, als je de Raspberry Pi-camera hebt maar niet de Grove-sensoren, kun je de virtuele apparaatcode op je Pi uitvoeren en de Grove-sensoren simuleren, maar een fysieke camera gebruiken.

De virtuele hardware maakt gebruik van het [CounterFit-project](https://github.com/CounterFit-IoT/CounterFit).

Om deze lessen te voltooien, heb je een webcam, microfoon en audio-uitgang zoals speakers of koptelefoon nodig. Deze kunnen ingebouwd of extern zijn en moeten geconfigureerd zijn om te werken met je besturingssysteem en beschikbaar zijn voor gebruik in alle applicaties.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.