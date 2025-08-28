<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T16:46:28+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "uk"
}
-->
# Розшифрування даних GPS - Wio Terminal

У цій частині уроку ви розшифруєте повідомлення NMEA, отримані від GPS-датчика за допомогою Wio Terminal, і витягнете широту та довготу.

## Розшифрування даних GPS

Після того, як необроблені дані NMEA були отримані з послідовного порту, їх можна розшифрувати за допомогою бібліотеки NMEA з відкритим кодом.

### Завдання - розшифрувати дані GPS

Програмуйте пристрій для розшифрування даних GPS.

1. Відкрийте проект додатка `gps-sensor`, якщо він ще не відкритий.

1. Додайте залежність бібліотеки [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) до файлу `platformio.ini` проекту. Ця бібліотека містить код для розшифрування даних NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. У файлі `main.cpp` додайте директиву включення для бібліотеки TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Під оголошенням `Serial3` оголосіть об'єкт TinyGPSPlus для обробки речень NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Змініть вміст функції `printGPSData` на наступний:

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

    Цей код зчитує наступний символ із послідовного порту UART у декодер NMEA `gps`. Після кожного символу він перевіряє, чи декодер прочитав дійсне речення, а потім перевіряє, чи було прочитано дійсне місцезнаходження. Якщо місцезнаходження дійсне, він надсилає його до серійного монітора разом із кількістю супутників, які сприяли цьому визначенню.

1. Зберіть і завантажте код на Wio Terminal.

1. Після завантаження ви можете відстежувати дані про місцезнаходження GPS за допомогою серійного монітора.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Ви можете знайти цей код у папці [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Ваше програмування GPS-датчика з розшифруванням даних пройшло успішно!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.