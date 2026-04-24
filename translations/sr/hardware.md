# Хардвер

**Т** у IoT означава **ствари** и односи се на уређаје који интерагују са светом око нас. Сваки пројекат заснован је на стварном хардверу доступном студентима и ентузијастима. Имамо два избора IoT хардвера у зависности од личних преференција, знања или склоности ка програмским језицима, циљева учења и доступности. Такође смо обезбедили верзију „виртуелног хардвера“ за оне који немају приступ хардверу или желе да науче више пре него што се одлуче за куповину.

> 💁 Не морате куповати IoT хардвер да бисте завршили задатке. Све можете урадити користећи виртуелни IoT хардвер.

Физички хардверски избори су Arduino или Raspberry Pi. Свака платформа има своје предности и мане, које су обрађене у једној од почетних лекција. Ако се још нисте одлучили за хардверску платформу, можете прегледати [лекцију два првог пројекта](./1-getting-started/lessons/2-deeper-dive/README.md) како бисте одлучили која вас хардверска платформа највише занима.

Одређени хардвер је изабран како би се смањила сложеност лекција и задатака. Иако други хардвер може радити, не можемо гарантовати да ће сви задаци бити подржани на вашем уређају без додатног хардвера. На пример, многи Arduino уређаји немају WiFi, који је потребан за повезивање са облаком - Wio терминал је изабран јер има уграђен WiFi.

Такође ће вам бити потребно неколико нетехничких предмета, као што су земља или саксијска биљка, и воће или поврће.

## Куповина комплета

![Лого Seeed студија](../../translated_images/sr/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios су љубазно обезбедили сав хардвер у облику лако доступних комплета:

### Arduino - Wio Terminal

**[IoT за почетнике са Seeed и Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Wio Terminal хардверски комплет](../../translated_images/sr/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT за почетнике са Seeed и Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Raspberry Pi Terminal хардверски комплет](../../translated_images/sr/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Сав код за уређаје на Arduino платформи је написан у C++. Да бисте завршили све задатке, биће вам потребно следеће:

### Arduino хардвер

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Опционо* - USB-C кабл или USB-A на USB-C адаптер. Wio терминал има USB-C порт и долази са USB-C на USB-A каблом. Ако ваш рачунар или Mac има само USB-C портове, биће вам потребан USB-C кабл или USB-A на USB-C адаптер.

### Arduino специфични сензори и актуатори

Ови сензори и актуатори су специфични за коришћење Wio терминала на Arduino уређају и нису релевантни за коришћење Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Жице за breadboard](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Слушалице или други звучник са 3.5мм прикључком, или JST звучник као што је:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD картица од 16GB или мање, заједно са конектором за коришћење SD картице са вашим рачунаром ако немате уграђени. **НАПОМЕНА** - Wio терминал подржава само SD картице до 16GB, не подржава веће капацитете.

## Raspberry Pi

Сав код за уређаје на Raspberry Pi платформи је написан у Python-у. Да бисте завршили све задатке, биће вам потребно следеће:

### Raspberry Pi хардвер

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Верзије од Pi 2B и новије требало би да раде са задацима у овим лекцијама. Ако планирате да покрећете VS Code директно на Pi-ју, онда је потребан Pi 4 са 2GB или више RAM-а. Ако ћете приступати Pi-ју даљински, онда ће радити било који Pi 2B и новији.
* microSD картица (Можете набавити Raspberry Pi комплете који долазе са microSD картицом), заједно са конектором за коришћење SD картице са вашим рачунаром ако немате уграђени.
* USB напајање (Можете набавити Raspberry Pi 4 комплете који долазе са напајањем). Ако користите Raspberry Pi 4, потребно је USB-C напајање, старији уређаји захтевају micro-USB напајање.

### Raspberry Pi специфични сензори и актуатори

Ови сензори и актуатори су специфични за коришћење Raspberry Pi и нису релевантни за коришћење Arduino уређаја.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi камера модул](https://www.raspberrypi.org/products/camera-module-v2/)
* Микрофон и звучник:

  Користите једно од следећег (или еквивалентно):
  * Било који USB микрофон са било којим USB звучником, или звучник са 3.5мм прикључком, или коришћење HDMI аудио излаза ако је ваш Raspberry Pi повезан са монитором или ТВ-ом са звучницима
  * Било који USB слушалице са уграђеним микрофоном
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) са
    * Слушалицама или другим звучником са 3.5мм прикључком, или JST звучником као што је:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light сензор](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove дугме](https://www.seeedstudio.com/Grove-Button.html)

## Сензори и актуатори

Већина сензора и актуатора који су потребни користе се и у Arduino и у Raspberry Pi путевима учења:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove сензор влажности и температуре](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove капацитивни сензор влажности земљишта](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove релеј](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight сензор удаљености](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Опциони хардвер

Лекције о аутоматском заливању раде користећи релеј. Као опција, можете повезати овај релеј са пумпом за воду која се напаја преко USB-а користећи доле наведени хардвер.

* [6V пумпа за воду](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB терминал](https://www.adafruit.com/product/3628)
* Силиконске цеви
* Црвене и црне жице
* Мали равни одвијач

## Виртуелни хардвер

Пут виртуелног хардвера обезбедиће симулаторе за сензоре и актуаторе, имплементиране у Python-у. У зависности од доступности вашег хардвера, можете га покренути на вашем уобичајеном развојном уређају, као што је Mac, PC, или га покренути на Raspberry Pi и симулирати само хардвер који немате. На пример, ако имате Raspberry Pi камеру, али не и Grove сензоре, моћи ћете да покренете код виртуелног уређаја на вашем Pi-ју и симулирате Grove сензоре, али користите физичку камеру.

Виртуелни хардвер ће користити [CounterFit пројекат](https://github.com/CounterFit-IoT/CounterFit).

Да бисте завршили ове лекције, биће вам потребна веб камера, микрофон и аудио излаз као што су звучници или слушалице. Они могу бити уграђени или екстерни и морају бити конфигурисани да раде са вашим оперативним системом и доступни за коришћење у свим апликацијама.

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да превод буде тачан, молимо вас да имате у виду да аутоматизовани преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.