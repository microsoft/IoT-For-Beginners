<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T13:17:31+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "sr"
}
-->
# Декодирање GPS података - Wio Terminal

У овом делу лекције, декодираћете NMEA поруке које GPS сензор чита преко Wio Terminal-а и извући географску ширину и дужину.

## Декодирање GPS података

Када се сирови NMEA подаци прочитају са серијског порта, могу се декодирати помоћу отворене библиотеке за NMEA.

### Задатак - декодирање GPS података

Програмирајте уређај да декодира GPS податке.

1. Отворите пројекат апликације `gps-sensor` ако већ није отворен.

1. Додајте зависност за библиотеку [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) у `platformio.ini` датотеку пројекта. Ова библиотека садржи код за декодирање NMEA података.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. У `main.cpp`, додајте директиву за укључивање библиотеке TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Испод декларације `Serial3`, декларишите објекат TinyGPSPlus за обраду NMEA реченица:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Промените садржај функције `printGPSData` у следеће:

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

    Овај код чита следећи карактер са UART серијског порта у `gps` NMEA декодер. Након сваког карактера, проверава да ли је декодер прочитао важећу реченицу, а затим проверава да ли је прочитао важећу локацију. Ако је локација важећа, шаље је на серијски монитор, заједно са бројем сателита који су допринели овом одређивању.

1. Компилирајте и отпремите код на Wio Terminal.

1. Када се код отпреми, можете пратити GPS податке о локацији помоћу серијског монитора.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Овај код можете пронаћи у фасцикли [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Ваш програм за GPS сензор са декодирањем података је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људског преводиоца. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.