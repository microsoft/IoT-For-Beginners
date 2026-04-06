# Hårdvara

**T** i IoT står för **Things** och syftar på enheter som interagerar med omvärlden. Varje projekt bygger på verklig hårdvara som är tillgänglig för studenter och hobbyister. Vi har två val av IoT-hårdvara beroende på personlig preferens, programmeringskunskaper eller preferenser, inlärningsmål och tillgänglighet. Vi har också tillhandahållit en "virtuell hårdvara"-version för dem som inte har tillgång till hårdvara eller vill lära sig mer innan de köper något.

> 💁 Du behöver inte köpa någon IoT-hårdvara för att slutföra uppgifterna. Du kan göra allt med virtuell IoT-hårdvara.

De fysiska hårdvaruvalen är Arduino eller Raspberry Pi. Varje plattform har sina för- och nackdelar, och dessa täcks i en av de inledande lektionerna. Om du ännu inte har bestämt dig för en hårdvaruplattform kan du granska [lektion två i det första projektet](./1-getting-started/lessons/2-deeper-dive/README.md) för att avgöra vilken plattform du är mest intresserad av att lära dig.

Den specifika hårdvaran har valts för att minska komplexiteten i lektionerna och uppgifterna. Även om annan hårdvara kan fungera kan vi inte garantera att alla uppgifter stöds på din enhet utan ytterligare hårdvara. Till exempel har många Arduino-enheter inte WiFi, vilket behövs för att ansluta till molnet – Wio-terminalen valdes eftersom den har inbyggt WiFi.

Du kommer också att behöva några icke-tekniska föremål, som jord eller en krukväxt, samt frukt eller grönsaker.

## Köp kit

![Seeed studios logotyp](../../translated_images/sv/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios har vänligen gjort all hårdvara tillgänglig som lättköpta kit:

### Arduino - Wio Terminal

**[IoT för nybörjare med Seeed och Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal hårdvarukit](../../translated_images/sv/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT för nybörjare med Seeed och Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi Terminal hårdvarukit](../../translated_images/sv/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

All kod för Arduino-enheter är skriven i C++. För att slutföra alla uppgifter behöver du följande:

### Arduino-hårdvara

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Valfritt* - USB-C-kabel eller USB-A till USB-C-adapter. Wio-terminalen har en USB-C-port och levereras med en USB-C till USB-A-kabel. Om din PC eller Mac endast har USB-C-portar behöver du en USB-C-kabel eller en USB-A till USB-C-adapter.

### Arduino-specifika sensorer och aktuatorer

Dessa är specifika för att använda Wio-terminalen med Arduino och är inte relevanta för Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Hörlurar eller annan högtalare med 3,5 mm kontakt, eller en JST-högtalare som:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD-kort på 16GB eller mindre, samt en adapter för att använda SD-kortet med din dator om du inte har en inbyggd kortläsare. **NOTE** - Wio-terminalen stöder endast SD-kort upp till 16GB, högre kapacitet stöds inte.

## Raspberry Pi

All kod för Raspberry Pi-enheter är skriven i Python. För att slutföra alla uppgifter behöver du följande:

### Raspberry Pi-hårdvara

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Versioner från Pi 2B och senare bör fungera med uppgifterna i dessa lektioner. Om du planerar att köra VS Code direkt på Pi behöver du en Pi 4 med minst 2GB RAM. Om du ska ansluta till Pi:n på distans fungerar alla Pi 2B och senare.
* microSD-kort (Du kan köpa Raspberry Pi-kit som inkluderar ett microSD-kort), samt en adapter för att använda SD-kortet med din dator om du inte har en inbyggd kortläsare.
* USB-strömadapter (Du kan köpa Raspberry Pi 4-kit som inkluderar en strömadapter). Om du använder en Raspberry Pi 4 behöver du en USB-C-strömadapter, tidigare modeller kräver en micro-USB-strömadapter.

### Raspberry Pi-specifika sensorer och aktuatorer

Dessa är specifika för att använda Raspberry Pi och är inte relevanta för Arduino-enheter.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikrofon och högtalare:

  Använd något av följande (eller motsvarande):
  * Valfri USB-mikrofon med valfri USB-högtalare, eller högtalare med 3,5 mm kontakt, eller HDMI-ljudutgång om din Raspberry Pi är ansluten till en skärm eller TV med högtalare
  * Valfritt USB-headset med inbyggd mikrofon
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) med
    * Hörlurar eller annan högtalare med 3,5 mm kontakt, eller en JST-högtalare som:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Sensorer och aktuatorer

De flesta sensorer och aktuatorer som behövs används av både Arduino- och Raspberry Pi-lärvägarna:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove fukt- och temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove kapacitiv jordfuktighetssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relä](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Valfri hårdvara

Lektionerna om automatiserad bevattning fungerar med ett relä. Som ett alternativ kan du ansluta detta relä till en vattenpump som drivs via USB med hjälp av hårdvaran nedan.

* [6V vattenpump](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB-terminal](https://www.adafruit.com/product/3628)
* Silikonrör
* Röda och svarta kablar
* Liten skruvmejsel med platt huvud

## Virtuell hårdvara

Den virtuella hårdvaruvägen tillhandahåller simulatorer för sensorer och aktuatorer, implementerade i Python. Beroende på din hårdvarutillgänglighet kan du köra detta på din vanliga utvecklingsenhet, som en Mac eller PC, eller köra det på en Raspberry Pi och simulera endast den hårdvara du inte har. Till exempel, om du har Raspberry Pi-kameran men inte Grove-sensorerna, kan du köra den virtuella enhetskoden på din Pi och simulera Grove-sensorerna, men använda en fysisk kamera.

Den virtuella hårdvaran kommer att använda [CounterFit-projektet](https://github.com/CounterFit-IoT/CounterFit).

För att slutföra dessa lektioner behöver du en webbkamera, mikrofon och ljudutgång som högtalare eller hörlurar. Dessa kan vara inbyggda eller externa och måste vara konfigurerade för att fungera med ditt operativsystem och vara tillgängliga för användning i alla applikationer.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.