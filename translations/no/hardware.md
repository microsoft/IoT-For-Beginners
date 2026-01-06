<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T20:19:47+00:00",
  "source_file": "hardware.md",
  "language_code": "no"
}
-->
# Maskinvare

**T** i IoT står for **Ting** og refererer til enheter som samhandler med omgivelsene. Hvert prosjekt er basert på ekte maskinvare som er tilgjengelig for studenter og hobbyister. Vi har to valg av IoT-maskinvare, avhengig av personlig preferanse, kunnskap eller preferanser for programmeringsspråk, læringsmål og tilgjengelighet. Vi har også laget en 'virtuell maskinvare'-versjon for de som ikke har tilgang til maskinvare, eller som ønsker å lære mer før de bestemmer seg for et kjøp.

> 💁 Du trenger ikke kjøpe noen IoT-maskinvare for å fullføre oppgavene. Du kan gjøre alt ved hjelp av virtuell IoT-maskinvare.

De fysiske maskinvarevalgene er Arduino eller Raspberry Pi. Hver plattform har sine egne fordeler og ulemper, og disse dekkes i en av de første leksjonene. Hvis du ikke allerede har bestemt deg for en maskinvareplattform, kan du se gjennom [leksjon to i det første prosjektet](./1-getting-started/lessons/2-deeper-dive/README.md) for å finne ut hvilken maskinvareplattform du er mest interessert i å lære.

Den spesifikke maskinvaren er valgt for å redusere kompleksiteten i leksjonene og oppgavene. Selv om annen maskinvare kan fungere, kan vi ikke garantere at alle oppgavene vil støttes på din enhet uten ekstra maskinvare. For eksempel har mange Arduino-enheter ikke WiFi, som er nødvendig for å koble til skyen – Wio-terminalen ble valgt fordi den har innebygd WiFi.

Du vil også trenge noen ikke-tekniske ting, som jord eller en potteplante, og frukt eller grønnsaker.

## Kjøp settene

![Seeed studios-logoen](../../translated_images/seeed-logo.74732b6b482b6e8e.no.png)

Seeed Studios har veldig vennlig gjort all maskinvaren tilgjengelig som lettkjøpte sett:

### Arduino - Wio Terminal

**[IoT for nybegynnere med Seeed og Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal-maskinvarekit](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.no.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT for nybegynnere med Seeed og Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi-maskinvarekit](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.no.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

All enhetskode for Arduino er skrevet i C++. For å fullføre alle oppgavene trenger du følgende:

### Arduino-maskinvare

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Valgfritt* - USB-C-kabel eller USB-A til USB-C-adapter. Wio-terminalen har en USB-C-port og leveres med en USB-C til USB-A-kabel. Hvis PC-en eller Mac-en din kun har USB-C-porter, trenger du en USB-C-kabel eller en USB-A til USB-C-adapter.

### Arduino-spesifikke sensorer og aktuatorer

Disse er spesifikke for bruk av Wio-terminalen med Arduino og er ikke relevante for bruk med Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Hodetelefoner eller annen høyttaler med 3,5 mm jack, eller en JST-høyttaler som:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD-kort på 16 GB eller mindre, sammen med en kortleser for å bruke SD-kortet med datamaskinen din hvis du ikke har en innebygd. **MERK** - Wio-terminalen støtter kun SD-kort opptil 16 GB, den støtter ikke høyere kapasiteter.

## Raspberry Pi

All enhetskode for Raspberry Pi er skrevet i Python. For å fullføre alle oppgavene trenger du følgende:

### Raspberry Pi-maskinvare

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versjoner fra Pi 2B og oppover bør fungere med oppgavene i disse leksjonene. Hvis du planlegger å kjøre VS Code direkte på Pi-en, trenger du en Pi 4 med 2 GB eller mer RAM. Hvis du skal få tilgang til Pi-en eksternt, vil enhver Pi 2B og oppover fungere.
* microSD-kort (Du kan få Raspberry Pi-sett som leveres med et microSD-kort), sammen med en kortleser for å bruke SD-kortet med datamaskinen din hvis du ikke har en innebygd.
* USB-strømforsyning (Du kan få Raspberry Pi 4-sett som leveres med en strømforsyning). Hvis du bruker en Raspberry Pi 4, trenger du en USB-C-strømforsyning, tidligere enheter trenger en mikro-USB-strømforsyning.

### Raspberry Pi-spesifikke sensorer og aktuatorer

Disse er spesifikke for bruk med Raspberry Pi og er ikke relevante for bruk med Arduino-enheter.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon og høyttaler:

  Bruk en av følgende (eller tilsvarende):
  * Enhver USB-mikrofon med hvilken som helst USB-høyttaler, eller høyttaler med en 3,5 mm jack-kabel, eller bruk HDMI-lydutgang hvis Raspberry Pi-en din er koblet til en skjerm eller TV med høyttalere
  * Ethvert USB-headset med innebygd mikrofon
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) med
    * Hodetelefoner eller annen høyttaler med 3,5 mm jack, eller en JST-høyttaler som:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Sensorer og aktuatorer

De fleste sensorene og aktuatorene som trengs, brukes av både Arduino- og Raspberry Pi-læringsstiene:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove fuktighets- og temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapasitiv jordfuktighetssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relé](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Valgfri maskinvare

Leksjonene om automatisert vanning fungerer ved bruk av et relé. Som et alternativ kan du koble dette reléet til en vannpumpe drevet av USB ved hjelp av maskinvaren nedenfor.

* [6V vannpumpe](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB-terminal](https://www.adafruit.com/product/3628)
* Silikonrør
* Røde og svarte ledninger
* Liten flat skrutrekker

## Virtuell maskinvare

Den virtuelle maskinvareveien vil tilby simulatorer for sensorene og aktuatorene, implementert i Python. Avhengig av tilgjengeligheten av maskinvaren din, kan du kjøre dette på din vanlige utviklingsenhet, som en Mac, PC, eller kjøre det på en Raspberry Pi og simulere bare maskinvaren du ikke har. For eksempel, hvis du har Raspberry Pi-kameraet, men ikke Grove-sensorene, vil du kunne kjøre den virtuelle enhetskoden på Pi-en din og simulere Grove-sensorene, men bruke et fysisk kamera.

Den virtuelle maskinvaren vil bruke [CounterFit-prosjektet](https://github.com/CounterFit-IoT/CounterFit).

For å fullføre disse leksjonene må du ha et webkamera, mikrofon og lydutgang som høyttalere eller hodetelefoner. Disse kan være innebygd eller eksterne, og må være konfigurert til å fungere med operativsystemet ditt og tilgjengelig for bruk fra alle applikasjoner.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.