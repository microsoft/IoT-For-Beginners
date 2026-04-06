# Hardware

**T**'et i IoT står for **Things** og refererer til enheder, der interagerer med verden omkring os. Hvert projekt er baseret på fysisk hardware, som er tilgængelig for studerende og hobbyister. Vi har to valgmuligheder for IoT-hardware, afhængigt af personlig præference, programmeringssprog, læringsmål og tilgængelighed. Vi har også en 'virtuel hardware'-version til dem, der ikke har adgang til hardware, eller som ønsker at lære mere, før de investerer i et køb.

> 💁 Du behøver ikke købe nogen IoT-hardware for at gennemføre opgaverne. Du kan klare det hele med virtuel IoT-hardware.

De fysiske hardwaremuligheder er Arduino eller Raspberry Pi. Hver platform har sine egne fordele og ulemper, som alle bliver gennemgået i en af de første lektioner. Hvis du endnu ikke har besluttet dig for en hardwareplatform, kan du gennemgå [lektion to i det første projekt](./1-getting-started/lessons/2-deeper-dive/README.md) for at finde ud af, hvilken hardwareplatform du er mest interesseret i at lære om.

Den specifikke hardware er valgt for at reducere kompleksiteten i lektionerne og opgaverne. Selvom anden hardware måske også kan bruges, kan vi ikke garantere, at alle opgaver vil fungere på din enhed uden ekstra hardware. For eksempel har mange Arduino-enheder ikke WiFi, som er nødvendigt for at oprette forbindelse til skyen – Wio-terminalen blev valgt, fordi den har indbygget WiFi.

Du vil også få brug for nogle ikke-tekniske genstande, såsom jord eller en potteplante samt frugt eller grøntsager.

## Køb kitsene

![Seeed studios logo](../../translated_images/da/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios har venligst gjort al hardware tilgængelig som letkøbte kits:

### Arduino - Wio Terminal

**[IoT for begyndere med Seeed og Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal hardware kit](../../translated_images/da/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT for begyndere med Seeed og Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi Terminal hardware kit](../../translated_images/da/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Al kode til Arduino-enheder er skrevet i C++. For at gennemføre alle opgaverne skal du bruge følgende:

### Arduino-hardware

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Valgfrit* - USB-C-kabel eller USB-A til USB-C-adapter. Wio-terminalen har en USB-C-port og leveres med et USB-C til USB-A-kabel. Hvis din PC eller Mac kun har USB-C-porte, skal du bruge et USB-C-kabel eller en USB-A til USB-C-adapter.

### Arduino-specifikke sensorer og aktuatorer

Disse er specifikke for brugen af Wio-terminalen og er ikke relevante for brugen af Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Hovedtelefoner eller anden højttaler med et 3,5 mm jackstik, eller en JST-højttaler som:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD-kort på 16GB eller mindre samt en adapter til at bruge SD-kortet med din computer, hvis du ikke har en indbygget kortlæser. **NOTE** - Wio-terminalen understøtter kun SD-kort op til 16GB og ikke større kapaciteter.

## Raspberry Pi

Al kode til Raspberry Pi-enheder er skrevet i Python. For at gennemføre alle opgaverne skal du bruge følgende:

### Raspberry Pi-hardware

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versioner fra Pi 2B og nyere bør fungere med opgaverne i disse lektioner. Hvis du planlægger at køre VS Code direkte på Pi'en, skal du bruge en Pi 4 med 2GB RAM eller mere. Hvis du vil tilgå Pi'en eksternt, fungerer enhver Pi 2B eller nyere.
* microSD-kort (Du kan få Raspberry Pi-kits, der leveres med et microSD-kort) samt en adapter til at bruge SD-kortet med din computer, hvis du ikke har en indbygget kortlæser.
* USB-strømforsyning (Du kan få Raspberry Pi 4-kits, der leveres med en strømforsyning). Hvis du bruger en Raspberry Pi 4, skal du bruge en USB-C-strømforsyning; ældre enheder kræver en micro-USB-strømforsyning.

### Raspberry Pi-specifikke sensorer og aktuatorer

Disse er specifikke for brugen af Raspberry Pi og er ikke relevante for brugen af Arduino-enheder.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon og højttaler:

  Brug en af følgende (eller tilsvarende):
  * Enhver USB-mikrofon med enhver USB-højttaler, eller højttaler med et 3,5 mm jackkabel, eller brug HDMI-lydudgang, hvis din Raspberry Pi er tilsluttet en skærm eller TV med højttalere.
  * Ethvert USB-headset med indbygget mikrofon.
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) med
    * Hovedtelefoner eller anden højttaler med et 3,5 mm jackstik, eller en JST-højttaler som:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Sensorer og aktuatorer

De fleste af de sensorer og aktuatorer, der er nødvendige, bruges både i Arduino- og Raspberry Pi-læringsforløbene:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove fugtigheds- og temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapacitiv jordfugtighedssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relæ](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Valgfri hardware

Lektionerne om automatisk vanding fungerer ved hjælp af et relæ. Som en mulighed kan du tilslutte dette relæ til en vandpumpe, der drives af USB, ved hjælp af nedenstående hardware.

* [6V vandpumpe](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB-terminal](https://www.adafruit.com/product/3628)
* Silikoneslanger
* Røde og sorte ledninger
* Lille flad skruetrækker

## Virtuel hardware

Den virtuelle hardwaremulighed giver simulatorer for sensorer og aktuatorer, implementeret i Python. Afhængigt af din hardwaretilgængelighed kan du køre dette på din normale udviklingsenhed, såsom en Mac, PC, eller på en Raspberry Pi og kun simulere den hardware, du ikke har. For eksempel, hvis du har Raspberry Pi-kameraet, men ikke Grove-sensorerne, vil du kunne køre den virtuelle enhedskode på din Pi og simulere Grove-sensorerne, men bruge et fysisk kamera.

Den virtuelle hardware vil bruge [CounterFit-projektet](https://github.com/CounterFit-IoT/CounterFit).

For at gennemføre disse lektioner skal du have et webcam, mikrofon og lydudgang såsom højttalere eller hovedtelefoner. Disse kan være indbyggede eller eksterne og skal være konfigureret til at fungere med dit operativsystem og tilgængelige for brug i alle applikationer.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.