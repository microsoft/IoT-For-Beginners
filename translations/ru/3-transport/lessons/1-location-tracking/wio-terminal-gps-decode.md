<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T00:51:41+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ru"
}
-->
# Расшифровка данных GPS - Wio Terminal

В этой части урока вы расшифруете сообщения NMEA, полученные от GPS-датчика на Wio Terminal, и извлечете широту и долготу.

## Расшифровка данных GPS

После того как необработанные данные NMEA будут считаны с последовательного порта, их можно расшифровать с помощью библиотеки NMEA с открытым исходным кодом.

### Задание - расшифровка данных GPS

Запрограммируйте устройство для расшифровки данных GPS.

1. Откройте проект приложения `gps-sensor`, если он еще не открыт.

1. Добавьте зависимость от библиотеки [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) в файл `platformio.ini` проекта. Эта библиотека содержит код для расшифровки данных NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. В файле `main.cpp` добавьте директиву include для библиотеки TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Под объявлением `Serial3` объявите объект TinyGPSPlus для обработки предложений NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Измените содержимое функции `printGPSData` на следующее:

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

    Этот код считывает следующий символ из последовательного порта UART в декодер NMEA `gps`. После каждого символа он проверяет, прочитал ли декодер корректное предложение, а затем проверяет, была ли получена корректная локация. Если локация корректна, она отправляется в монитор порта вместе с количеством спутников, которые участвовали в определении местоположения.

1. Соберите и загрузите код на Wio Terminal.

1. После загрузки вы можете отслеживать данные о местоположении GPS с помощью монитора порта.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Этот код можно найти в папке [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Ваше приложение для работы с GPS-датчиком и расшифровки данных успешно заработало!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, имейте в виду, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.