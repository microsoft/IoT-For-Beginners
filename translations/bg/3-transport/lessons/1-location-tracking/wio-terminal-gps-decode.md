<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T09:37:52+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "bg"
}
-->
# Декодиране на GPS данни - Wio Terminal

В тази част на урока ще декодирате NMEA съобщенията, прочетени от GPS сензора на Wio Terminal, и ще извлечете географската ширина и дължина.

## Декодиране на GPS данни

След като суровите NMEA данни бъдат прочетени от серийния порт, те могат да бъдат декодирани с помощта на библиотека с отворен код за NMEA.

### Задача - декодиране на GPS данни

Програмирайте устройството да декодира GPS данните.

1. Отворете проекта на приложението `gps-sensor`, ако вече не е отворен.

1. Добавете зависимост към библиотеката [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) в `platformio.ini` файла на проекта. Тази библиотека съдържа код за декодиране на NMEA данни.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. В `main.cpp` добавете директива за включване на библиотеката TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Под декларацията на `Serial3` декларирайте обект TinyGPSPlus за обработка на NMEA съобщенията:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Променете съдържанието на функцията `printGPSData` със следното:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Този код чете следващия символ от серийния порт на UART в декодера `gps` за NMEA. След всеки символ проверява дали декодерът е прочел валидно съобщение, след което проверява дали е прочел валидно местоположение. Ако местоположението е валидно, то се изпраща към серийния монитор заедно с броя на сателитите, които са допринесли за това определяне.

1. Компилирайте и качете кода на Wio Terminal.

1. След като качите, можете да наблюдавате данните за GPS местоположението чрез серийния монитор.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Можете да намерите този код в папката [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Вашата програма за GPS сензора с декодиране на данни беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.