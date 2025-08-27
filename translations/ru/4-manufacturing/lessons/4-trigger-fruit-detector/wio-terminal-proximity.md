<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-26T22:09:27+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "ru"
}
-->
# Обнаружение близости - Wio Terminal

В этой части урока вы добавите датчик близости к вашему Wio Terminal и будете считывать расстояние с него.

## Оборудование

Для Wio Terminal потребуется датчик близости.

Датчик, который вы будете использовать, — это [Grove Time of Flight distance sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Этот датчик использует лазерный модуль для измерения расстояния. Диапазон измерений датчика составляет от 10 мм до 2000 мм (1 см - 2 м), и он довольно точно передает значения в этом диапазоне. Расстояния выше 1000 мм будут отображаться как 8109 мм.

Лазерный дальномер находится на задней стороне датчика, противоположной стороне от разъема Grove.

Это I²C датчик.

### Подключение датчика Time of Flight

Датчик Grove Time of Flight можно подключить к Wio Terminal.

#### Задание - подключите датчик Time of Flight

Подключите датчик Time of Flight.

![Датчик Grove Time of Flight](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.ru.png)

1. Вставьте один конец кабеля Grove в разъем на датчике Time of Flight. Кабель вставляется только в одном направлении.

1. С отключенным от компьютера или другого источника питания Wio Terminal подключите другой конец кабеля Grove к левому разъему Grove на Wio Terminal, если смотреть на экран. Это разъем, который находится ближе всего к кнопке питания. Этот разъем поддерживает цифровой и I²C интерфейсы.

![Датчик Grove Time of Flight, подключенный к левому разъему](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73df67febd004dc0313d271013d016be9c47e7da4d77c6c20a8.ru.png)

1. Теперь вы можете подключить Wio Terminal к компьютеру.

## Программирование датчика Time of Flight

Теперь Wio Terminal можно запрограммировать для работы с подключенным датчиком Time of Flight.

### Задание - запрограммируйте датчик Time of Flight

1. Создайте новый проект для Wio Terminal с использованием PlatformIO. Назовите проект `distance-sensor`. Добавьте код в функцию `setup` для настройки последовательного порта.

1. Добавьте зависимость библиотеки для датчика расстояния Seeed Grove Time of Flight в файл `platformio.ini` проекта:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. В `main.cpp` добавьте следующий код ниже существующих директив include, чтобы объявить экземпляр класса `Seeed_vl53l0x` для взаимодействия с датчиком Time of Flight:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Добавьте следующий код в конец функции `setup` для инициализации датчика:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. В функции `loop` считайте значение с датчика:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Этот код инициализирует структуру данных для считывания информации, затем передает её в метод `PerformSingleRangingMeasurement`, где она будет заполнена измерением расстояния.

1. После этого выведите измерение расстояния, затем сделайте задержку на 1 секунду:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Соберите, загрузите и выполните этот код. Вы сможете увидеть измерения расстояния в последовательном мониторе. Размещайте объекты рядом с датчиком, и вы увидите измерение расстояния:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Дальномер находится на задней стороне датчика, поэтому убедитесь, что используете правильную сторону при измерении расстояния.

    ![Дальномер на задней стороне датчика Time of Flight, направленный на банан](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4525dc26b4cdc71a076407aba3e72ba113ba2e38febae92c5.ru.png)

> 💁 Вы можете найти этот код в папке [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal).

😀 Программа для датчика близости успешно выполнена!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.