<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T22:56:07+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "fi"
}
-->
# Purkaa GPS-data - Wio Terminal

Tässä osassa oppituntia purat Wio Terminalin GPS-anturin lukemat NMEA-viestit ja poimit niistä leveys- ja pituusasteet.

## Purkaa GPS-data

Kun raaka NMEA-data on luettu sarjaportista, se voidaan purkaa avoimen lähdekoodin NMEA-kirjaston avulla.

### Tehtävä - purkaa GPS-data

Ohjelmoi laite purkamaan GPS-data.

1. Avaa `gps-sensor`-sovellusprojekti, jos se ei ole jo auki.

1. Lisää kirjastoriippuvuus [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)-kirjastolle projektin `platformio.ini`-tiedostoon. Tämä kirjasto sisältää koodin NMEA-datan purkamiseen.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Lisää `main.cpp`-tiedostoon include-direktiivi TinyGPSPlus-kirjastolle:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Julista `Serial3`-määrittelyn alapuolella TinyGPSPlus-olio NMEA-lauseiden käsittelyä varten:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Muuta `printGPSData`-funktion sisältö seuraavaksi:

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

    Tämä koodi lukee seuraavan merkin UART-sarjaportista `gps`-NMEA-dekooderiin. Jokaisen merkin jälkeen se tarkistaa, onko dekooderi lukenut kelvollisen lauseen, ja sen jälkeen tarkistaa, onko se lukenut kelvollisen sijainnin. Jos sijainti on kelvollinen, se lähettää sen sarjamonitoriin yhdessä niiden satelliittien lukumäärän kanssa, jotka osallistuivat tähän paikannukseen.

1. Käännä ja lataa koodi Wio Terminaliin.

1. Kun koodi on ladattu, voit tarkkailla GPS-sijaintidataa sarjamonitorin avulla.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Löydät tämän koodin [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal)-kansiosta.

😀 GPS-anturin ohjelmasi datan purkamisella onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.