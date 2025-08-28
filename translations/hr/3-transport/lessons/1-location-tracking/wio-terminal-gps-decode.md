<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T13:17:43+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "hr"
}
-->
# Dekodiranje GPS podataka - Wio Terminal

U ovom dijelu lekcije dekodirat ćete NMEA poruke koje čita GPS senzor na Wio Terminalu i izvući geografske širine i dužine.

## Dekodiranje GPS podataka

Nakon što se sirovi NMEA podaci pročitaju s serijskog porta, mogu se dekodirati pomoću otvorene NMEA biblioteke.

### Zadatak - dekodiranje GPS podataka

Programirajte uređaj za dekodiranje GPS podataka.

1. Otvorite projekt aplikacije `gps-sensor` ako već nije otvoren.

1. Dodajte ovisnost o biblioteci [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) u datoteku `platformio.ini` projekta. Ova biblioteka sadrži kod za dekodiranje NMEA podataka.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. U datoteci `main.cpp` dodajte direktivu za uključivanje biblioteke TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Ispod deklaracije `Serial3`, deklarirajte objekt TinyGPSPlus za obradu NMEA rečenica:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Promijenite sadržaj funkcije `printGPSData` na sljedeće:

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

    Ovaj kod čita sljedeći znak s UART serijskog porta u NMEA dekoder `gps`. Nakon svakog znaka provjerava je li dekoder pročitao valjanu rečenicu, a zatim provjerava je li pročitao valjanu lokaciju. Ako je lokacija valjana, šalje je na serijski monitor, zajedno s brojem satelita koji su doprinijeli ovom određivanju.

1. Izgradite i učitajte kod na Wio Terminal.

1. Nakon učitavanja, možete pratiti podatke o GPS lokaciji pomoću serijskog monitora.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Ovaj kod možete pronaći u mapi [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Vaš program za GPS senzor s dekodiranjem podataka bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za bilo kakva nesporazuma ili pogrešna tumačenja koja proizlaze iz korištenja ovog prijevoda.