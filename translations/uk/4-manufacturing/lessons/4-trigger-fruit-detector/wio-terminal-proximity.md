# Виявлення близькості - Wio Terminal

У цій частині уроку ви додасте датчик близькості до вашого Wio Terminal і зчитуватимете відстань із нього.

## Апаратне забезпечення

Для Wio Terminal потрібен датчик близькості.

Датчик, який ви будете використовувати, це [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Цей датчик використовує лазерний модуль для вимірювання відстані. Він має діапазон від 10 мм до 2000 мм (1 см - 2 м) і досить точно повідомляє значення в цьому діапазоні, при цьому відстані понад 1000 мм повідомляються як 8109 мм.

Лазерний далекомір знаходиться на зворотному боці датчика, на протилежному боці від роз'єму Grove.

Це I²C датчик.

### Підключення датчика Time of Flight

Датчик Grove Time of Flight можна підключити до Wio Terminal.

#### Завдання - підключення датчика Time of Flight

Підключіть датчик Time of Flight.

![Датчик Grove Time of Flight](../../../../../translated_images/uk/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Вставте один кінець кабелю Grove у роз'єм на датчику Time of Flight. Він вставляється лише в одному напрямку.

1. Вимкнувши Wio Terminal від комп'ютера або іншого джерела живлення, підключіть інший кінець кабелю Grove до лівого роз'єму Grove на Wio Terminal, якщо дивитися на екран. Це роз'єм, найближчий до кнопки живлення. Це комбінований цифровий і I²C роз'єм.

![Датчик Grove Time of Flight підключений до лівого роз'єму](../../../../../translated_images/uk/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Тепер ви можете підключити Wio Terminal до комп'ютера.

## Програмування датчика Time of Flight

Тепер Wio Terminal можна запрограмувати для використання підключеного датчика Time of Flight.

### Завдання - програмування датчика Time of Flight

1. Створіть новий проєкт для Wio Terminal за допомогою PlatformIO. Назвіть цей проєкт `distance-sensor`. Додайте код у функцію `setup` для налаштування послідовного порту.

1. Додайте залежність бібліотеки для датчика відстані Seeed Grove Time of Flight до файлу `platformio.ini` проєкту:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. У файлі `main.cpp` додайте наступне під існуючими директивами include, щоб оголосити екземпляр класу `Seeed_vl53l0x` для взаємодії з датчиком Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Додайте наступне в кінець функції `setup`, щоб ініціалізувати датчик:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. У функції `loop` зчитайте значення з датчика:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Цей код ініціалізує структуру даних для зчитування даних, а потім передає її в метод `PerformSingleRangingMeasurement`, де вона буде заповнена вимірюванням відстані.

1. Після цього виведіть вимірювання відстані, а потім зробіть затримку на 1 секунду:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Зберіть, завантажте та запустіть цей код. Ви зможете побачити вимірювання відстані в серійному моніторі. Розміщуйте об'єкти поруч із датчиком, і ви побачите вимірювання відстані:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Далекомір знаходиться на зворотному боці датчика, тому переконайтеся, що ви використовуєте правильну сторону під час вимірювання відстані.

    ![Далекомір на зворотному боці датчика Time of Flight, спрямований на банан](../../../../../translated_images/uk/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Ви можете знайти цей код у папці [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Ваше програмування датчика близькості було успішним!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.