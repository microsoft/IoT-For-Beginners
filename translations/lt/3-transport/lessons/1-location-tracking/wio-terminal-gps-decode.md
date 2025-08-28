<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T19:37:46+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "lt"
}
-->
# Dekoduokite GPS duomenis - Wio Terminal

Šioje pamokos dalyje jūs dekoduosite NMEA pranešimus, gautus iš GPS jutiklio naudojant Wio Terminal, ir ištrauksite platumos bei ilgumos koordinates.

## GPS duomenų dekodavimas

Kai neapdoroti NMEA duomenys yra nuskaityti iš nuosekliojo prievado, juos galima dekoduoti naudojant atvirojo kodo NMEA biblioteką.

### Užduotis - dekoduoti GPS duomenis

Užprogramuokite įrenginį, kad jis galėtų dekoduoti GPS duomenis.

1. Atidarykite `gps-sensor` programos projektą, jei jis dar neatidarytas.

1. Pridėkite bibliotekos priklausomybę [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) bibliotekai į projekto `platformio.ini` failą. Ši biblioteka turi kodą, skirtą NMEA duomenų dekodavimui.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Faile `main.cpp` pridėkite `include` direktyvą TinyGPSPlus bibliotekai:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Po `Serial3` deklaracijos, deklaruokite TinyGPSPlus objektą, skirtą NMEA sakinių apdorojimui:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Pakeiskite `printGPSData` funkcijos turinį į šį:

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

    Šis kodas nuskaito kitą simbolį iš UART nuosekliojo prievado į `gps` NMEA dekoderį. Po kiekvieno simbolio jis patikrina, ar dekoderis perskaitė galiojantį sakinį, tada patikrina, ar buvo perskaityta galiojanti vieta. Jei vieta yra galiojanti, ji siunčiama į nuoseklųjį monitorių kartu su palydovų, kurie prisidėjo prie šio fiksavimo, skaičiumi.

1. Sukurkite ir įkelkite kodą į Wio Terminal.

1. Kai kodas bus įkeltas, galite stebėti GPS vietos duomenis naudodami nuoseklųjį monitorių.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Šį kodą galite rasti [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal) aplanke.

😀 Jūsų GPS jutiklio programa su duomenų dekodavimu buvo sėkminga!

---

**Atsakomybės apribojimas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Dėl svarbios informacijos rekomenduojama profesionali žmogaus vertimo paslauga. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius naudojant šį vertimą.