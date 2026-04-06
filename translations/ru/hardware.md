# Аппаратное обеспечение

**T** в IoT означает **Things** (вещи) и относится к устройствам, которые взаимодействуют с окружающим миром. Каждый проект основан на реальном оборудовании, доступном для студентов и любителей. У нас есть два варианта аппаратного обеспечения IoT, которые можно использовать в зависимости от личных предпочтений, знаний или предпочтений в программировании, учебных целей и доступности. Также мы предоставили версию с "виртуальным оборудованием" для тех, у кого нет доступа к физическому оборудованию, или кто хочет узнать больше перед покупкой.

> 💁 Вам не нужно приобретать какое-либо оборудование IoT для выполнения заданий. Вы можете сделать всё, используя виртуальное оборудование IoT.

Физические варианты оборудования — это Arduino или Raspberry Pi. У каждой платформы есть свои плюсы и минусы, которые рассматриваются в одном из начальных уроков. Если вы ещё не выбрали платформу, вы можете ознакомиться с [вторым уроком первого проекта](./1-getting-started/lessons/2-deeper-dive/README.md), чтобы решить, какое оборудование вам интереснее изучать.

Конкретное оборудование было выбрано для упрощения уроков и заданий. Хотя другое оборудование может работать, мы не можем гарантировать, что все задания будут поддерживаться на вашем устройстве без дополнительного оборудования. Например, многие устройства Arduino не имеют WiFi, который необходим для подключения к облаку — Wio Terminal был выбран, потому что WiFi встроен.

Вам также понадобятся несколько нетехнических предметов, таких как почва или комнатное растение, а также фрукты или овощи.

## Покупка наборов

![Логотип Seeed Studios](../../translated_images/ru/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios любезно предоставили всё оборудование в виде удобных для покупки наборов:

### Arduino - Wio Terminal

**[IoT для начинающих с Seeed и Microsoft - стартовый набор Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Набор оборудования Wio Terminal](../../translated_images/ru/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT для начинающих с Seeed и Microsoft - стартовый набор Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Набор оборудования Raspberry Pi Terminal](../../translated_images/ru/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Весь код для устройств Arduino написан на C++. Для выполнения всех заданий вам понадобится следующее:

### Аппаратное обеспечение Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Опционально* - кабель USB-C или адаптер USB-A на USB-C. Wio Terminal имеет порт USB-C и поставляется с кабелем USB-C на USB-A. Если на вашем ПК или Mac только порты USB-C, вам понадобится кабель USB-C или адаптер USB-A на USB-C.

### Специфические датчики и исполнительные устройства для Arduino

Эти устройства специфичны для использования с Wio Terminal и не применимы для Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Провода для макетной платы](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Наушники или другой динамик с разъёмом 3.5 мм, или динамик JST, например:
  * [Моно-динамик в корпусе - 2W 6 Ом](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Карта microSD объёмом 16 ГБ или меньше, а также адаптер для подключения карты к компьютеру, если у вас нет встроенного слота. **NOTE** - Wio Terminal поддерживает только карты SD до 16 ГБ, более ёмкие карты не поддерживаются.

## Raspberry Pi

Весь код для устройств Raspberry Pi написан на Python. Для выполнения всех заданий вам понадобится следующее:

### Аппаратное обеспечение Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Версии начиная с Pi 2B и выше должны работать с заданиями в этих уроках. Если вы планируете запускать VS Code непосредственно на Pi, то потребуется Pi 4 с 2 ГБ или более оперативной памяти. Если вы будете подключаться к Pi удалённо, то подойдёт любая версия начиная с Pi 2B.
* Карта microSD (можно приобрести наборы Raspberry Pi, которые включают карту microSD), а также адаптер для подключения карты к компьютеру, если у вас нет встроенного слота.
* USB-адаптер питания (можно приобрести наборы Raspberry Pi 4, которые включают адаптер питания). Если вы используете Raspberry Pi 4, вам понадобится адаптер питания USB-C, для более ранних устройств — адаптер micro-USB.

### Специфические датчики и исполнительные устройства для Raspberry Pi

Эти устройства специфичны для использования с Raspberry Pi и не применимы для Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Модуль камеры Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Микрофон и динамик:

  Используйте одно из следующих устройств (или эквивалент):
  * Любой USB-микрофон с любым USB-динамиком, или динамик с кабелем 3.5 мм, или HDMI-аудиовыход, если ваш Raspberry Pi подключён к монитору или телевизору с динамиками
  * Любая USB-гарнитура с встроенным микрофоном
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) с
    * Наушниками или другим динамиком с разъёмом 3.5 мм, или динамиком JST, например:
    * [Моно-динамик в корпусе - 2W 6 Ом](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB-спикерфон](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Датчик освещённости Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Кнопка Grove](https://www.seeedstudio.com/Grove-Button.html)

## Датчики и исполнительные устройства

Большинство датчиков и исполнительных устройств используются как в обучении Arduino, так и Raspberry Pi:

* [Светодиод Grove](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Датчик влажности и температуры Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Емкостной датчик влажности почвы Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Реле Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Датчик расстояния Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Опциональное оборудование

Уроки по автоматическому поливу работают с использованием реле. В качестве опции вы можете подключить это реле к водяному насосу, работающему от USB, используя оборудование, указанное ниже.

* [6V водяной насос](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB-терминал](https://www.adafruit.com/product/3628)
* Силиконовые трубки
* Красные и чёрные провода
* Маленькая плоская отвёртка

## Виртуальное оборудование

Виртуальный путь предоставляет симуляторы для датчиков и исполнительных устройств, реализованных на Python. В зависимости от доступности оборудования, вы можете запускать это на своём обычном устройстве для разработки, таком как Mac, ПК, или на Raspberry Pi, симулируя только то оборудование, которого у вас нет. Например, если у вас есть камера Raspberry Pi, но нет датчиков Grove, вы сможете запустить виртуальный код устройства на вашем Pi и симулировать датчики Grove, но использовать физическую камеру.

Виртуальное оборудование будет использовать проект [CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Для выполнения этих уроков вам понадобится веб-камера, микрофон и аудиовыход, такие как динамики или наушники. Они могут быть встроенными или внешними, и должны быть настроены для работы с вашей операционной системой и доступны для использования во всех приложениях.

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.