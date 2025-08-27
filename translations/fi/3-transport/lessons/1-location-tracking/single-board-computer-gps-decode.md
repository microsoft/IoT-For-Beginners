<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T22:54:35+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "fi"
}
-->
# Dekoodaa GPS-data - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä oppitunnin osassa dekoodaat NMEA-viestit, jotka Raspberry Pi tai virtuaalinen IoT-laite lukee GPS-anturista, ja poimit niistä leveys- ja pituusasteet.

## Dekoodaa GPS-data

Kun raakadata NMEA-muodossa on luettu sarjaportista, se voidaan dekoodata avoimen lähdekoodin NMEA-kirjaston avulla.

### Tehtävä - dekoodaa GPS-data

Ohjelmoi laite dekoodaamaan GPS-data.

1. Avaa `gps-sensor`-sovellusprojekti, jos se ei ole jo avoinna.

1. Asenna `pynmea2`-Pip-paketti. Tämä paketti sisältää koodin NMEA-viestien dekoodaamiseen.

    ```sh
    pip3 install pynmea2
    ```

1. Lisää seuraava koodi `app.py`-tiedoston tuontiosioon tuodaksesi `pynmea2`-moduulin:

    ```python
    import pynmea2
    ```

1. Korvaa `print_gps_data`-funktion sisältö seuraavalla koodilla:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    Tämä koodi käyttää `pynmea2`-kirjastoa jäsentämään UART-sarjaportista luetun rivin.

    Jos viestin lauseen tyyppi on `GGA`, kyseessä on sijaintitietoviesti, ja se käsitellään. Viestistä luetaan leveys- ja pituusasteet, jotka muunnetaan desimaaliasteiksi NMEA-muodosta `(d)ddmm.mmmm`. `dm_to_sd`-funktio suorittaa tämän muunnoksen.

    Tämän jälkeen tarkistetaan leveysasteen suunta, ja jos leveysaste on etelässä, arvo muunnetaan negatiiviseksi. Sama pätee pituusasteeseen: jos se on lännessä, se muunnetaan negatiiviseksi.

    Lopuksi koordinaatit tulostetaan konsoliin yhdessä sijainnin määrittämiseen käytettyjen satelliittien lukumäärän kanssa.

1. Suorita koodi. Jos käytät virtuaalista IoT-laitetta, varmista, että CounterFit-sovellus on käynnissä ja GPS-dataa lähetetään.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Löydät tämän koodin [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device)-kansiosta tai [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi)-kansiosta.

😀 GPS-anturin ohjelmasi datan dekoodauksella onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.