<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T21:41:15+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "cs"
}
-->
# Dekódování GPS dat - Wio Terminal

V této části lekce budete dekódovat zprávy NMEA přečtené ze senzoru GPS pomocí Wio Terminalu a extrahovat zeměpisnou šířku a délku.

## Dekódování GPS dat

Jakmile jsou surová data NMEA přečtena ze sériového portu, mohou být dekódována pomocí open source knihovny NMEA.

### Úkol - dekódování GPS dat

Naprogramujte zařízení tak, aby dekódovalo GPS data.

1. Otevřete projekt aplikace `gps-sensor`, pokud již není otevřený.

1. Přidejte závislost na knihovnu [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) do souboru `platformio.ini` projektu. Tato knihovna obsahuje kód pro dekódování dat NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. V souboru `main.cpp` přidejte direktivu pro zahrnutí knihovny TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Pod deklarací `Serial3` deklarujte objekt TinyGPSPlus pro zpracování vět NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Změňte obsah funkce `printGPSData` na následující:

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

    Tento kód čte další znak ze sériového portu UART do dekodéru NMEA `gps`. Po každém znaku zkontroluje, zda dekodér přečetl platnou větu, a poté ověří, zda přečetl platnou polohu. Pokud je poloha platná, odešle ji do sériového monitoru spolu s počtem satelitů, které přispěly k této fixaci.

1. Sestavte a nahrajte kód do Wio Terminalu.

1. Po nahrání můžete sledovat data GPS polohy pomocí sériového monitoru.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Tento kód najdete ve složce [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Váš program pro senzor GPS s dekódováním dat byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte prosím na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádná nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.