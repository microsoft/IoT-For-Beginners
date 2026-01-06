<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T20:36:38+00:00",
  "source_file": "hardware.md",
  "language_code": "tl"
}
-->
# Hardware

Ang **T** sa IoT ay **Things** na tumutukoy sa mga device na nakikipag-ugnayan sa mundo sa paligid natin. Ang bawat proyekto ay nakabatay sa mga aktwal na hardware na magagamit ng mga estudyante at hobbyist. Mayroon tayong dalawang pagpipilian ng IoT hardware na maaaring gamitin depende sa personal na kagustuhan, kaalaman sa programming language, layunin sa pag-aaral, at availability. Nagbigay din kami ng 'virtual hardware' na bersyon para sa mga walang access sa hardware, o gustong matuto nang higit pa bago bumili.

> 💁 Hindi mo kailangang bumili ng anumang IoT hardware para makumpleto ang mga gawain. Magagawa mo ang lahat gamit ang virtual IoT hardware.

Ang mga pisikal na hardware na pagpipilian ay Arduino, o Raspberry Pi. Ang bawat platform ay may kani-kaniyang kalamangan at kahinaan, at ang mga ito ay tinalakay sa isa sa mga unang aralin. Kung hindi ka pa nakakapili ng hardware platform, maaari mong suriin ang [aralin dalawa ng unang proyekto](./1-getting-started/lessons/2-deeper-dive/README.md) upang magpasya kung aling hardware platform ang nais mong matutunan.

Ang partikular na hardware ay pinili upang mabawasan ang pagiging kumplikado ng mga aralin at gawain. Bagama't maaaring gumana ang ibang hardware, hindi namin magagarantiya na ang lahat ng mga gawain ay susuportahan sa iyong device nang walang karagdagang hardware. Halimbawa, maraming Arduino device ang walang WiFi, na kinakailangan upang makakonekta sa cloud - ang Wio terminal ay pinili dahil mayroon itong built-in na WiFi.

Kakailanganin mo rin ng ilang hindi teknikal na bagay, tulad ng lupa o halaman sa paso, at prutas o gulay.

## Bumili ng mga kit

![Ang logo ng Seeed Studios](../../translated_images/seeed-logo.74732b6b482b6e8e.tl.png)

Ang Seeed Studios ay napakabait na ginawang madali ang pagbili ng lahat ng hardware bilang mga kit:

### Arduino - Wio Terminal

**[IoT para sa mga nagsisimula kasama ang Seeed at Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Ang Wio Terminal hardware kit](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.tl.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT para sa mga nagsisimula kasama ang Seeed at Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Ang Raspberry Pi Terminal hardware kit](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.tl.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Ang lahat ng device code para sa Arduino ay nasa C++. Upang makumpleto ang lahat ng mga gawain, kakailanganin mo ang mga sumusunod:

### Arduino hardware

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Opsyonal* - USB-C cable o USB-A to USB-C adapter. Ang Wio terminal ay may USB-C port at may kasamang USB-C to USB-A cable. Kung ang iyong PC o Mac ay may USB-C ports lamang, kakailanganin mo ng USB-C cable, o isang USB-A to USB-C adapter.

### Mga partikular na sensor at actuator para sa Arduino

Ang mga ito ay partikular sa paggamit ng Wio terminal Arduino device, at hindi nauugnay sa paggamit ng Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Headphones o ibang speaker na may 3.5mm jack, o isang JST speaker tulad ng:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD Card 16GB o mas mababa, kasama ang connector upang magamit ang SD card sa iyong computer kung wala kang built-in. **NOTE** - Ang Wio Terminal ay sumusuporta lamang sa SD cards hanggang 16GB, hindi nito sinusuportahan ang mas mataas na kapasidad.

## Raspberry Pi

Ang lahat ng device code para sa Raspberry Pi ay nasa Python. Upang makumpleto ang lahat ng mga gawain, kakailanganin mo ang mga sumusunod:

### Raspberry Pi hardware

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Ang mga bersyon mula sa Pi 2B pataas ay dapat gumana sa mga gawain sa mga araling ito. Kung balak mong patakbuhin ang VS Code nang direkta sa Pi, kailangan ng Pi 4 na may 2GB o higit pang RAM. Kung remote mong maa-access ang Pi, anumang Pi 2B pataas ay gagana.
* microSD Card (Maaari kang makakuha ng Raspberry Pi kits na may kasamang microSD Card), kasama ang connector upang magamit ang SD card sa iyong computer kung wala kang built-in.
* USB power supply (Maaari kang makakuha ng Raspberry Pi 4 kits na may kasamang power supply). Kung gumagamit ka ng Raspberry Pi 4, kailangan mo ng USB-C power supply, ang mas naunang mga device ay nangangailangan ng micro-USB power supply.

### Mga partikular na sensor at actuator para sa Raspberry Pi

Ang mga ito ay partikular sa paggamit ng Raspberry Pi, at hindi nauugnay sa paggamit ng Arduino device.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Mikropono at speaker:

  Gumamit ng isa sa mga sumusunod (o katumbas):
  * Anumang USB Microphone na may anumang USB speaker, o speaker na may 3.5mm jack cable, o gamit ang HDMI audio output kung ang iyong Raspberry Pi ay nakakonekta sa monitor o TV na may mga speaker
  * Anumang USB headset na may built-in na mikropono
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) na may
    * Headphones o ibang speaker na may 3.5mm jack, o isang JST speaker tulad ng:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Mga sensor at actuator

Karamihan sa mga sensor at actuator na kinakailangan ay ginagamit sa parehong Arduino at Raspberry Pi learning paths:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove capacitive soil moisture sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relay](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Opsyonal na hardware

Ang mga aralin tungkol sa automated watering ay gumagana gamit ang relay. Bilang opsyon, maaari mong ikonekta ang relay na ito sa isang water pump na pinapagana ng USB gamit ang hardware na nakalista sa ibaba.

* [6V water pump](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminal](https://www.adafruit.com/product/3628)
* Silicone pipes
* Pula at itim na wires
* Maliit na flat-head screwdriver

## Virtual hardware

Ang ruta ng virtual hardware ay magbibigay ng mga simulator para sa mga sensor at actuator, na ipinatupad sa Python. Depende sa availability ng iyong hardware, maaari mong patakbuhin ito sa iyong normal na development device, tulad ng Mac, PC, o patakbuhin ito sa Raspberry Pi at i-simulate lamang ang hardware na wala ka. Halimbawa, kung mayroon kang Raspberry Pi camera ngunit wala ang Grove sensors, magagawa mong patakbuhin ang virtual device code sa iyong Pi at i-simulate ang Grove sensors, ngunit gumamit ng pisikal na camera.

Ang virtual hardware ay gagamit ng [CounterFit project](https://github.com/CounterFit-IoT/CounterFit).

Upang makumpleto ang mga araling ito, kailangan mong magkaroon ng web cam, mikropono, at audio output tulad ng mga speaker o headphones. Ang mga ito ay maaaring built-in o external, at kailangang i-configure upang gumana sa iyong operating system at magamit sa lahat ng application.

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.