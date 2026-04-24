# Апаратне забезпечення

**T** в IoT означає **Речі** і стосується пристроїв, які взаємодіють із навколишнім світом. Кожен проєкт базується на реальному апаратному забезпеченні, доступному для студентів і любителів. Ми пропонуємо два варіанти апаратного забезпечення IoT, які можна використовувати залежно від особистих уподобань, знань програмування, навчальних цілей та доступності. Також ми надали версію "віртуального апаратного забезпечення" для тих, хто не має доступу до фізичного обладнання або хоче більше дізнатися перед покупкою.

> 💁 Вам не потрібно купувати апаратне забезпечення IoT для виконання завдань. Усе можна зробити за допомогою віртуального апаратного забезпечення IoT.

Фізичні варіанти апаратного забезпечення — це Arduino або Raspberry Pi. Кожна платформа має свої переваги та недоліки, які розглядаються в одному з початкових уроків. Якщо ви ще не визначилися з платформою, ви можете переглянути [другий урок першого проєкту](./1-getting-started/lessons/2-deeper-dive/README.md), щоб вирішити, яке апаратне забезпечення вам найбільше цікаве.

Конкретне апаратне забезпечення було обрано для зменшення складності уроків і завдань. Хоча інше обладнання може працювати, ми не можемо гарантувати, що всі завдання будуть підтримуватися вашим пристроєм без додаткового обладнання. Наприклад, багато пристроїв Arduino не мають WiFi, який потрібен для підключення до хмари — Wio Terminal був обраний, оскільки він має вбудований WiFi.

Вам також знадобляться кілька нетехнічних предметів, таких як ґрунт або кімнатна рослина, а також фрукти чи овочі.

## Купівля комплектів

![Логотип Seeed Studios](../../translated_images/uk/seeed-logo.74732b6b482b6e8e.webp)

Seeed Studios люб’язно зробили все апаратне забезпечення доступним у вигляді легкодоступних комплектів:

### Arduino - Wio Terminal

**[IoT для початківців із Seeed та Microsoft - стартовий комплект Wio Terminal](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Комплект апаратного забезпечення Wio Terminal](../../translated_images/uk/wio-hardware-kit.4c70c48b85e4283a.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT для початківців із Seeed та Microsoft - стартовий комплект Raspberry Pi 4](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Комплект апаратного забезпечення Raspberry Pi Terminal](../../translated_images/uk/pi-hardware-kit.26dbadaedb7dd44c.webp)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Увесь код для пристроїв Arduino написаний на C++. Для виконання всіх завдань вам знадобиться наступне:

### Апаратне забезпечення Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Опціонально* - кабель USB-C або адаптер USB-A до USB-C. Wio Terminal має порт USB-C і постачається з кабелем USB-C до USB-A. Якщо ваш ПК або Mac має лише порти USB-C, вам знадобиться кабель USB-C або адаптер USB-A до USB-C.

### Специфічні датчики та виконавчі пристрої для Arduino

Ці компоненти специфічні для пристрою Wio Terminal Arduino і не стосуються використання Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Проводи для макетної плати](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Навушники або інший динамік із роз'ємом 3.5 мм, або динамік JST, наприклад:
  * [Моно динамік у корпусі - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Карта microSD до 16GB, а також адаптер для використання карти SD із вашим комп’ютером, якщо у вас немає вбудованого. **NOTE** - Wio Terminal підтримує лише карти SD до 16GB, більші обсяги не підтримуються.

## Raspberry Pi

Увесь код для пристроїв Raspberry Pi написаний на Python. Для виконання всіх завдань вам знадобиться наступне:

### Апаратне забезпечення Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Версії від Pi 2B і вище повинні працювати з завданнями в цих уроках. Якщо ви плануєте запускати VS Code безпосередньо на Pi, то потрібен Pi 4 із 2GB або більше оперативної пам’яті. Якщо ви будете отримувати доступ до Pi віддалено, то будь-який Pi 2B і вище підійде.
* Карта microSD (можна придбати комплекти Raspberry Pi, які постачаються з картою microSD), а також адаптер для використання карти SD із вашим комп’ютером, якщо у вас немає вбудованого.
* USB блок живлення (можна придбати комплекти Raspberry Pi 4, які постачаються з блоком живлення). Якщо ви використовуєте Raspberry Pi 4, вам потрібен блок живлення USB-C, для попередніх пристроїв потрібен блок живлення micro-USB.

### Специфічні датчики та виконавчі пристрої для Raspberry Pi

Ці компоненти специфічні для використання Raspberry Pi і не стосуються пристроїв Arduino.

* [Grove Pi базовий модуль](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Модуль камери Raspberry Pi](https://www.raspberrypi.org/products/camera-module-v2/)
* Мікрофон і динамік:

  Використовуйте один із наступних (або еквівалент):
  * Будь-який USB мікрофон із будь-яким USB динаміком, або динамік із кабелем 3.5 мм, або використовуйте HDMI аудіовихід, якщо ваш Raspberry Pi підключений до монітора або телевізора з динаміками
  * Будь-яка USB гарнітура з вбудованим мікрофоном
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) із
    * Навушниками або іншим динаміком із роз'ємом 3.5 мм, або динаміком JST, наприклад:
    * [Моно динамік у корпусі - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB спікерфон](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Датчик світла Grove](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Кнопка Grove](https://www.seeedstudio.com/Grove-Button.html)

## Датчики та виконавчі пристрої

Більшість датчиків і виконавчих пристроїв потрібні для обох навчальних шляхів — Arduino і Raspberry Pi:

* [Світлодіод Grove](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Датчик вологості та температури Grove](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Ємнісний датчик вологості ґрунту Grove](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Реле Grove](https://www.seeedstudio.com/Grove-Relay.html)
* [GPS Grove (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Датчик відстані Grove Time of Flight](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Опціональне апаратне забезпечення

Уроки з автоматизованого поливу працюють за допомогою реле. Як опцію, ви можете підключити це реле до водяного насоса, що працює через USB, використовуючи наведене нижче обладнання.

* [Водяний насос 6V](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB термінал](https://www.adafruit.com/product/3628)
* Силіконові трубки
* Червоні та чорні дроти
* Маленька плоска викрутка

## Віртуальне апаратне забезпечення

Віртуальний шлях апаратного забезпечення надасть симулятори для датчиків і виконавчих пристроїв, реалізованих на Python. Залежно від доступності вашого обладнання, ви можете запускати це на вашому звичайному пристрої для розробки, наприклад Mac, ПК, або на Raspberry Pi, симулюючи лише те обладнання, якого у вас немає. Наприклад, якщо у вас є камера Raspberry Pi, але немає датчиків Grove, ви зможете запустити код віртуального пристрою на вашому Pi і симулювати датчики Grove, але використовувати фізичну камеру.

Віртуальне апаратне забезпечення використовуватиме [проєкт CounterFit](https://github.com/CounterFit-IoT/CounterFit).

Для виконання цих уроків вам знадобиться веб-камера, мікрофон і аудіовихід, наприклад динаміки або навушники. Вони можуть бути вбудованими або зовнішніми, і повинні бути налаштовані для роботи з вашою операційною системою та доступні для використання у всіх додатках.

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критично важливої інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.