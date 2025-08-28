<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T13:17:54+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "sl"
}
-->
# Dekodiranje GPS podatkov - Wio Terminal

V tem delu lekcije boste dekodirali NMEA sporočila, ki jih prebere GPS senzor na Wio Terminalu, in iz njih pridobili zemljepisno širino ter dolžino.

## Dekodiranje GPS podatkov

Ko so surovi NMEA podatki prebrani iz serijskega porta, jih je mogoče dekodirati z uporabo odprtokodne NMEA knjižnice.

### Naloga - dekodiranje GPS podatkov

Programirajte napravo za dekodiranje GPS podatkov.

1. Odprite projekt aplikacije `gps-sensor`, če še ni odprt.

1. Dodajte knjižnično odvisnost za knjižnico [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) v datoteko `platformio.ini` projekta. Ta knjižnica vsebuje kodo za dekodiranje NMEA podatkov.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. V datoteki `main.cpp` dodajte direktivo za vključitev knjižnice TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Pod deklaracijo `Serial3` deklarirajte objekt TinyGPSPlus za obdelavo NMEA stavkov:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Spremenite vsebino funkcije `printGPSData` v naslednje:

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

    Ta koda prebere naslednji znak iz serijskega porta UART v NMEA dekoder `gps`. Po vsakem znaku preveri, ali je dekoder prebral veljaven stavek, nato pa preveri, ali je prebral veljavno lokacijo. Če je lokacija veljavna, jo pošlje na serijski monitor skupaj s številom satelitov, ki so prispevali k tej rešitvi.

1. Sestavite in naložite kodo na Wio Terminal.

1. Ko je koda naložena, lahko spremljate podatke o GPS lokaciji z uporabo serijskega monitorja.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 To kodo lahko najdete v mapi [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Vaš program za GPS senzor z dekodiranjem podatkov je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.