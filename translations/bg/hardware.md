# Хардуер

**T** в IoT означава **Things** (неща) и се отнася до устройства, които взаимодействат със света около нас. Всеки проект е базиран на реален хардуер, достъпен за студенти и любители. Имаме два избора за IoT хардуер, които да използваме, в зависимост от личните предпочитания, знанията или предпочитанията за програмен език, учебните цели и наличността. Освен това сме предоставили версия с „виртуален хардуер“ за тези, които нямат достъп до хардуер или искат да научат повече, преди да се ангажират с покупка.

> 💁 Не е необходимо да закупувате IoT хардуер, за да завършите задачите. Всичко може да се направи с виртуален IoT хардуер.

Физическите хардуерни опции са Arduino или Raspberry Pi. Всяка платформа има своите предимства и недостатъци, които са разгледани в един от началните уроци. Ако все още не сте решили коя хардуерна платформа да използвате, можете да прегледате [урок две от първия проект](./1-getting-started/lessons/2-deeper-dive/README.md), за да решите коя платформа ви интересува най-много.

Конкретният хардуер е избран, за да се намали сложността на уроците и задачите. Въпреки че друг хардуер може да работи, не можем да гарантираме, че всички задачи ще бъдат поддържани на вашето устройство без допълнителен хардуер. Например, много устройства Arduino нямат WiFi, което е необходимо за свързване към облака - Wio терминалът е избран, защото има вграден WiFi.

Ще ви трябват и някои нетехнически предмети, като почва или саксийно растение, както и плодове или зеленчуци.

## Купете комплектите

![Логото на Seeed Studios](../../translated_images/bg/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios любезно предоставиха целия хардуер като лесно достъпни комплекти:

### Arduino - Wio Terminal

**[IoT за начинаещи със Seeed и Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Комплектът хардуер Wio Terminal](../../translated_images/bg/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT за начинаещи със Seeed и Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Комплектът хардуер Raspberry Pi Terminal](../../translated_images/bg/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Целият код за устройства Arduino е написан на C++. За да завършите всички задачи, ще ви трябват следните компоненти:

### Хардуер за Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *По избор* - USB-C кабел или USB-A към USB-C адаптер. Wio терминалът има USB-C порт и идва с USB-C към USB-A кабел. Ако вашият компютър или Mac има само USB-C портове, ще ви трябва USB-C кабел или USB-A към USB-C адаптер.

### Специфични сензори и изпълнителни устройства за Arduino

Тези компоненти са специфични за използването на устройството Wio Terminal Arduino и не са приложими за Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Слушалки или друг говорител с 3.5mm жак, или JST говорител като:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* microSD карта 16GB или по-малко, заедно с конектор за използване на SD картата с вашия компютър, ако нямате вграден такъв. **ЗАБЕЛЕЖКА** - Wio терминалът поддържа само SD карти до 16GB, не поддържа по-големи капацитети.

## Raspberry Pi

Целият код за устройства Raspberry Pi е написан на Python. За да завършите всички задачи, ще ви трябват следните компоненти:

### Хардуер за Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Версиите от Pi 2B и нагоре трябва да работят с задачите в тези уроци. Ако планирате да използвате VS Code директно на Pi, тогава е необходим Pi 4 с 2GB или повече RAM. Ако ще достъпвате Pi дистанционно, тогава всяка версия от Pi 2B и нагоре ще работи.
* microSD карта (Можете да закупите комплекти Raspberry Pi, които включват microSD карта), заедно с конектор за използване на SD картата с вашия компютър, ако нямате вграден такъв.
* USB захранване (Можете да закупите комплекти Raspberry Pi 4, които включват захранване). Ако използвате Raspberry Pi 4, ще ви трябва USB-C захранване, по-ранните устройства изискват micro-USB захранване.

### Специфични сензори и изпълнителни устройства за Raspberry Pi

Тези компоненти са специфични за използването на Raspberry Pi и не са приложими за устройството Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Микрофон и говорител:

  Използвайте едно от следните (или еквивалентно):
  * Всеки USB микрофон с всеки USB говорител, или говорител с 3.5mm жак кабел, или използване на HDMI аудио изход, ако вашият Raspberry Pi е свързан към монитор или телевизор с говорители
  * Всеки USB слушалки с вграден микрофон
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) с
    * Слушалки или друг говорител с 3.5mm жак, или JST говорител като:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Сензори и изпълнителни устройства

Повечето от необходимите сензори и изпълнителни устройства се използват както от Arduino, така и от Raspberry Pi учебните пътеки:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove capacitive soil moisture sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relay](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## По избор хардуер

Уроците за автоматизирано поливане работят с реле. Като опция, можете да свържете това реле към водна помпа, захранвана чрез USB, използвайки изброения хардуер по-долу.

* [6V водна помпа](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB терминал](https://www.adafruit.com/product/3628)
* Силиконови тръби
* Червени и черни кабели
* Малка плоска отвертка

## Виртуален хардуер

Виртуалният хардуерен подход предоставя симулатори за сензорите и изпълнителните устройства, реализирани в Python. В зависимост от наличността на вашия хардуер, можете да го стартирате на вашето нормално устройство за разработка, като Mac, PC, или да го стартирате на Raspberry Pi и да симулирате само хардуера, който нямате. Например, ако имате камерата Raspberry Pi, но не и сензорите Grove, ще можете да стартирате виртуалния код на вашия Pi и да симулирате сензорите Grove, но да използвате физическа камера.

Виртуалният хардуер ще използва [CounterFit проекта](https://github.com/CounterFit-IoT/CounterFit).

За да завършите тези уроци, ще трябва да имате уеб камера, микрофон и аудио изход, като говорители или слушалки. Те могат да бъдат вградени или външни и трябва да бъдат конфигурирани да работят с вашата операционна система и да са достъпни за използване от всички приложения.

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.