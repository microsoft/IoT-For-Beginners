<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T20:29:32+00:00",
  "source_file": "hardware.md",
  "language_code": "sw"
}
-->
# Vifaa vya Kifaa

**T** katika IoT inamaanisha **Vitu** na inahusu vifaa vinavyoshirikiana na mazingira yanayotuzunguka. Kila mradi unategemea vifaa halisi vinavyopatikana kwa wanafunzi na wapenda teknolojia. Tuna chaguo mbili za vifaa vya IoT kulingana na upendeleo wa mtu binafsi, ujuzi wa lugha ya programu au mapendeleo, malengo ya kujifunza, na upatikanaji. Pia tumetoa toleo la 'vifaa vya kidijitali' kwa wale ambao hawana ufikiaji wa vifaa, au wanataka kujifunza zaidi kabla ya kununua.

> 💁 Huna haja ya kununua vifaa vyovyote vya IoT ili kukamilisha kazi. Unaweza kufanya kila kitu ukitumia vifaa vya kidijitali vya IoT.

Chaguo za vifaa vya kimwili ni Arduino au Raspberry Pi. Kila jukwaa lina faida na hasara zake, na haya yote yameelezewa katika moja ya masomo ya awali. Ikiwa bado hujaamua jukwaa la vifaa, unaweza kupitia [somo la pili la mradi wa kwanza](./1-getting-started/lessons/2-deeper-dive/README.md) ili kuamua ni jukwaa gani la vifaa unalopenda kujifunza.

Vifaa maalum vilichaguliwa ili kupunguza ugumu wa masomo na kazi. Ingawa vifaa vingine vinaweza kufanya kazi, hatuwezi kuhakikisha kazi zote zitasaidiwa kwenye kifaa chako bila vifaa vya ziada. Kwa mfano, vifaa vingi vya Arduino havina WiFi, ambayo inahitajika kuunganishwa na wingu - Wio terminal ilichaguliwa kwa sababu ina WiFi iliyojengwa ndani.

Pia utahitaji vitu vichache visivyo vya kiufundi, kama udongo au mmea wa sufuria, na matunda au mboga.

## Nunua Vifurushi

![Nembo ya Seeed Studios](../../translated_images/seeed-logo.74732b6b482b6e8e.sw.png)

Seeed Studios wamefanya vifaa vyote kupatikana kwa urahisi kama vifurushi vya kununua:

### Arduino - Wio Terminal

**[IoT kwa wanaoanza na Seeed na Microsoft - Kifurushi cha Kuanza cha Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Kifurushi cha vifaa vya Wio Terminal](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.sw.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT kwa wanaoanza na Seeed na Microsoft - Kifurushi cha Kuanza cha Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Kifurushi cha vifaa vya Raspberry Pi Terminal](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.sw.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Msimbo wote wa kifaa cha Arduino uko katika C++. Ili kukamilisha kazi zote utahitaji yafuatayo:

### Vifaa vya Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Hiari* - Keboli ya USB-C au adapta ya USB-A hadi USB-C. Wio terminal ina bandari ya USB-C na huja na keboli ya USB-C hadi USB-A. Ikiwa PC au Mac yako ina bandari za USB-C pekee, utahitaji keboli ya USB-C, au adapta ya USB-A hadi USB-C.

### Vihisi na vihamasishi maalum vya Arduino

Hivi ni maalum kwa kutumia kifaa cha Arduino cha Wio terminal, na si muhimu kwa kutumia Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Waya za kuruka za Breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Vifaa vya sauti kama vile:
  * [Spika ya Mono iliyofungwa - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Kadi ya microSD 16GB au chini, pamoja na kiunganishi cha kutumia kadi ya SD na kompyuta yako ikiwa huna moja iliyojengwa ndani. **KUMBUKA** - Wio Terminal inasaidia kadi za SD hadi 16GB pekee, haziungi mkono uwezo wa juu zaidi.

## Raspberry Pi

Msimbo wote wa kifaa cha Raspberry Pi uko katika Python. Ili kukamilisha kazi zote utahitaji yafuatayo:

### Vifaa vya Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Toleo kuanzia Pi 2B na kuendelea linapaswa kufanya kazi na kazi katika masomo haya. Ikiwa unapanga kutumia VS Code moja kwa moja kwenye Pi, basi Pi 4 yenye RAM ya 2GB au zaidi inahitajika. Ikiwa utaifikia Pi kwa mbali basi Pi yoyote kuanzia 2B na kuendelea itafanya kazi.
* Kadi ya microSD (Unaweza kupata vifurushi vya Raspberry Pi vinavyokuja na kadi ya microSD), pamoja na kiunganishi cha kutumia kadi ya SD na kompyuta yako ikiwa huna moja iliyojengwa ndani.
* Ugavi wa umeme wa USB (Unaweza kupata vifurushi vya Raspberry Pi 4 vinavyokuja na ugavi wa umeme). Ikiwa unatumia Raspberry Pi 4 unahitaji ugavi wa umeme wa USB-C, vifaa vya awali vinahitaji ugavi wa umeme wa micro-USB.

### Vihisi na vihamasishi maalum vya Raspberry Pi

Hivi ni maalum kwa kutumia Raspberry Pi, na si muhimu kwa kutumia kifaa cha Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Moduli ya Kamera ya Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Kipaza sauti na spika:

  Tumia moja kati ya hizi (au sawa na hizi):
  * Kipaza sauti chochote cha USB na spika yoyote ya USB, au spika yenye keboli ya 3.5mm jack, au kutumia sauti ya HDMI ikiwa Raspberry Pi yako imeunganishwa na kioo au TV yenye spika
  * Headset yoyote ya USB yenye kipaza sauti kilichojengwa ndani
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) na
    * Vifaa vya sauti kama vile:
    * [Spika ya Mono iliyofungwa - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [Spika ya USB ya Mikutano](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Kihisi cha mwanga cha Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Kitufe cha Grove](https://www.seeedstudio.com/Grove-Button.html)

## Vihisi na vihamasishi

Vihisi na vihamasishi vingi vinavyohitajika vinatumika kwa njia zote za kujifunza za Arduino na Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Kihisi cha unyevu na joto cha Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Kihisi cha unyevu wa udongo cha Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Relay ya Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS ya Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Kihisi cha umbali cha Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Vifaa vya hiari

Masomo kuhusu umwagiliaji wa maji kiotomatiki hufanya kazi kwa kutumia relay. Kama chaguo, unaweza kuunganisha relay hii na pampu ya maji inayotumia USB kwa kutumia vifaa vilivyoorodheshwa hapa chini.

* [Pampu ya maji ya 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [Terminal ya USB](https://www.adafruit.com/product/3628)
* Mabomba ya silicone
* Waya nyekundu na nyeusi
* Screwdriver ndogo ya kichwa bapa

## Vifaa vya kidijitali

Njia ya vifaa vya kidijitali itatoa vionesha mfano vya vihisi na vihamasishi, vilivyotekelezwa kwa Python. Kulingana na upatikanaji wa vifaa vyako, unaweza kuendesha hii kwenye kifaa chako cha kawaida cha maendeleo, kama Mac, PC, au kuiendesha kwenye Raspberry Pi na kuonesha mfano wa vifaa ambavyo huna. Kwa mfano, ikiwa una kamera ya Raspberry Pi lakini huna vihisi vya Grove, utaweza kuendesha msimbo wa kifaa cha kidijitali kwenye Pi yako na kuonesha mfano wa vihisi vya Grove, lakini utumie kamera halisi.

Vifaa vya kidijitali vitatumia [mradi wa CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Ili kukamilisha masomo haya utahitaji kuwa na kamera ya wavuti, kipaza sauti, na sauti ya nje kama spika au headphones. Hizi zinaweza kuwa za ndani au za nje, na zinahitaji kusanidiwa kufanya kazi na mfumo wako wa uendeshaji na kupatikana kwa matumizi kutoka kwa programu zote.

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.