<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T21:40:57+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "sw"
}
-->
# Kufasiri Data za GPS - Wio Terminal

Katika sehemu hii ya somo, utatafsiri ujumbe wa NMEA uliosomwa kutoka kwa kihisi cha GPS na Wio Terminal, na kutoa latitudo na longitudo.

## Kufasiri Data za GPS

Baada ya data ghafi ya NMEA kusomwa kutoka kwa serial port, inaweza kufasiriwa kwa kutumia maktaba ya NMEA ya chanzo huria.

### Kazi - kufasiri data za GPS

Programu kifaa ili kufasiri data za GPS.

1. Fungua mradi wa programu ya `gps-sensor` ikiwa haujafunguliwa tayari.

1. Ongeza utegemezi wa maktaba ya [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) kwenye faili ya `platformio.ini` ya mradi. Maktaba hii ina msimbo wa kufasiri data ya NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Katika `main.cpp`, ongeza agizo la kujumuisha maktaba ya TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Chini ya tamko la `Serial3`, tamka kitu cha TinyGPSPlus ili kushughulikia sentensi za NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Badilisha yaliyomo ya kazi ya `printGPSData` na yafuatayo:

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

    Msimbo huu unasoma herufi inayofuata kutoka kwa serial port ya UART kwenye kifasiri cha NMEA cha `gps`. Baada ya kila herufi, itakagua kuona kama kifasiri kimesoma sentensi halali, kisha kagua kuona kama kimesoma eneo halali. Ikiwa eneo ni halali, itaituma kwenye serial monitor, pamoja na idadi ya satelaiti zilizochangia katika kurekebisha hii.

1. Jenga na pakia msimbo kwenye Wio Terminal.

1. Baada ya kupakiwa, unaweza kufuatilia data ya eneo la GPS kwa kutumia serial monitor.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Unaweza kupata msimbo huu katika folda ya [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Programu yako ya kihisi cha GPS na kufasiri data imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.