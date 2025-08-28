<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-28T09:37:42+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ro"
}
-->
# Decodifică datele GPS - Wio Terminal

În această parte a lecției, vei decodifica mesajele NMEA citite de senzorul GPS de către Wio Terminal și vei extrage latitudinea și longitudinea.

## Decodifică datele GPS

După ce datele brute NMEA au fost citite de pe portul serial, acestea pot fi decodificate folosind o bibliotecă NMEA open source.

### Sarcină - decodifică datele GPS

Programează dispozitivul pentru a decodifica datele GPS.

1. Deschide proiectul aplicației `gps-sensor` dacă nu este deja deschis.

1. Adaugă o dependență de bibliotecă pentru biblioteca [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) în fișierul `platformio.ini` al proiectului. Această bibliotecă conține cod pentru decodificarea datelor NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. În `main.cpp`, adaugă o directivă include pentru biblioteca TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Sub declarația `Serial3`, declară un obiect TinyGPSPlus pentru procesarea propozițiilor NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Modifică conținutul funcției `printGPSData` astfel încât să fie următorul:

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

    Acest cod citește următorul caracter de pe portul serial UART în decodorul NMEA `gps`. După fiecare caracter, va verifica dacă decodorul a citit o propoziție validă, apoi va verifica dacă a citit o locație validă. Dacă locația este validă, o trimite către monitorul serial, împreună cu numărul de sateliți care au contribuit la această fixare.

1. Construiește și încarcă codul pe Wio Terminal.

1. După ce codul a fost încărcat, poți monitoriza datele de locație GPS folosind monitorul serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Poți găsi acest cod în folderul [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Programul senzorului GPS cu decodificarea datelor a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să fiți conștienți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.