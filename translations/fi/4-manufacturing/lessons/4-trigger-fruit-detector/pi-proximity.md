<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T20:56:14+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "fi"
}
-->
# Tunnista läheisyys - Raspberry Pi

Tässä osassa oppituntia lisäät läheisyyssensorin Raspberry Pi:hin ja luet etäisyyden siitä.

## Laitteisto

Raspberry Pi tarvitsee läheisyyssensorin.

Käytettävä sensori on [Grove Time of Flight -etäisyyssensori](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Tämä sensori käyttää lasermittaustekniikkaa etäisyyden havaitsemiseen. Sensorin mittausalue on 10mm - 2000mm (1cm - 2m), ja se raportoi arvot tällä alueella melko tarkasti. Etäisyydet yli 1000mm raportoidaan arvolla 8109mm.

Laseretäisyysmittari sijaitsee sensorin takapuolella, vastakkaisella puolella Grove-liitintä.

Tämä on I²C-sensori.

### Yhdistä Time of Flight -sensori

Grove Time of Flight -sensori voidaan liittää Raspberry Pi:hin.

#### Tehtävä - yhdistä Time of Flight -sensori

Yhdistä Time of Flight -sensori.

![Grove Time of Flight -sensori](../../../../../translated_images/fi/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Työnnä Grove-kaapelin toinen pää Time of Flight -sensorin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Raspberry Pi on sammutettu, yhdistä Grove-kaapelin toinen pää yhteen I²C-liittimistä, jotka on merkitty **I²C** Grove Base -hatissa, joka on kiinnitetty Pi:hin. Nämä liittimet sijaitsevat alarivissä, vastakkaisessa päässä GPIO-pinneistä ja kamerakaapelin liittimen vieressä.

![Grove Time of Flight -sensori yhdistettynä I²C-liittimeen](../../../../../translated_images/fi/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Ohjelmoi Time of Flight -sensori

Raspberry Pi voidaan nyt ohjelmoida käyttämään liitettyä Time of Flight -sensoria.

### Tehtävä - ohjelmoi Time of Flight -sensori

Ohjelmoi laite.

1. Käynnistä Pi ja odota, että se käynnistyy.

1. Avaa `fruit-quality-detector`-koodi VS Codessa joko suoraan Pi:llä tai yhdistä Remote SSH -laajennuksen kautta.

1. Asenna rpi-vl53l0x Pip-paketti, Python-paketti, joka kommunikoi VL53L0X Time of Flight -etäisyyssensorin kanssa. Asenna se käyttämällä tätä pip-komentoa:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Luo uusi tiedosto tähän projektiin nimeltä `distance-sensor.py`.

    > 💁 Helppo tapa simuloida useita IoT-laitteita on tehdä jokainen eri Python-tiedostossa ja ajaa ne samanaikaisesti.

1. Lisää seuraava koodi tähän tiedostoon:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Tämä tuo käyttöön Grove I²C-väyläkirjaston ja sensorikirjaston, joka on rakennettu Grove Time of Flight -sensorin ydinlaitteistolle.

1. Tämän alle lisää seuraava koodi sensorin käyttämiseksi:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Tämä koodi määrittää etäisyyssensorin käyttämällä Grove I²C-väylää ja käynnistää sensorin.

1. Lopuksi lisää ääretön silmukka etäisyyksien lukemiseen:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Tämä koodi odottaa, että sensorista on saatavilla arvo, ja tulostaa sen konsoliin.

1. Aja tämä koodi.

    > 💁 Muista, että tämä tiedosto on nimeltään `distance-sensor.py`! Varmista, että ajat sen Pythonilla, et `app.py`:llä.

1. Näet etäisyysmittaukset konsolissa. Aseta esineitä sensorin lähelle ja näet etäisyysmittauksen:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Etäisyysmittari sijaitsee sensorin takapuolella, joten varmista, että käytät oikeaa puolta etäisyyden mittaamiseen.

    ![Etäisyysmittari Time of Flight -sensorin takapuolella osoittaa banaania](../../../../../translated_images/fi/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Löydät tämän koodin [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) -kansiosta.

😀 Läheisyyssensorin ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.