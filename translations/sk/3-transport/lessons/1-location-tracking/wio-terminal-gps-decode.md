<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T09:37:34+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "sk"
}
-->
# Dekódovanie GPS dát - Wio Terminal

V tejto časti lekcie budete dekódovať NMEA správy prečítané zo senzora GPS pomocou Wio Terminal a extrahovať zemepisnú šírku a dĺžku.

## Dekódovanie GPS dát

Keď sú surové NMEA dáta prečítané zo sériového portu, môžu byť dekódované pomocou open source knižnice NMEA.

### Úloha - dekódovanie GPS dát

Naprogramujte zariadenie na dekódovanie GPS dát.

1. Otvorte projekt aplikácie `gps-sensor`, ak ešte nie je otvorený.

1. Pridajte závislosť knižnice [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) do súboru `platformio.ini` projektu. Táto knižnica obsahuje kód na dekódovanie NMEA dát.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. V súbore `main.cpp` pridajte direktívu pre zahrnutie knižnice TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Pod deklaráciou `Serial3` deklarujte objekt TinyGPSPlus na spracovanie NMEA viet:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Zmeňte obsah funkcie `printGPSData` na nasledujúce:

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

    Tento kód číta ďalší znak zo sériového portu UART do dekodéra NMEA `gps`. Po každom znaku skontroluje, či dekodér prečítal platnú vetu, a potom skontroluje, či prečítal platnú polohu. Ak je poloha platná, odošle ju do sériového monitora spolu s počtom satelitov, ktoré prispeli k tomuto fixu.

1. Zostavte a nahrajte kód do Wio Terminal.

1. Po nahraní môžete monitorovať údaje o polohe GPS pomocou sériového monitora.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Tento kód nájdete v priečinku [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Váš program senzora GPS s dekódovaním dát bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.