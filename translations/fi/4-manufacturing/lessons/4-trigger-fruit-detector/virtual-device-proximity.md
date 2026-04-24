# Tunnista läheisyys - Virtuaalinen IoT-laitteisto

Tässä oppitunnin osassa lisäät läheisyyssensorin virtuaaliseen IoT-laitteeseesi ja luet sen mittaamia etäisyyksiä.

## Laitteisto

Virtuaalinen IoT-laite käyttää simuloitua etäisyyssensoria.

Fyysisessä IoT-laitteessa käyttäisit sensoria, jossa on lasermittausmoduuli etäisyyden havaitsemiseksi.

### Lisää etäisyyssensori CounterFitiin

Jotta voit käyttää virtuaalista etäisyyssensoria, sinun täytyy lisätä sellainen CounterFit-sovellukseen.

#### Tehtävä - lisää etäisyyssensori CounterFitiin

Lisää etäisyyssensori CounterFit-sovellukseen.

1. Avaa `fruit-quality-detector`-koodi VS Codessa ja varmista, että virtuaaliympäristö on aktivoitu.

1. Asenna lisäpaketti Pipin kautta, jotta voit asentaa CounterFit-shimin, joka simuloi [rpi-vl53l0x Pip -pakettia](https://pypi.org/project/rpi-vl53l0x/). Tämä Python-paketti on suunniteltu toimimaan [VL53L0X time-of-flight -etäisyyssensorin](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/) kanssa. Varmista, että asennat tämän terminaalista, jossa virtuaaliympäristö on aktivoitu.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Varmista, että CounterFit-verkkosovellus on käynnissä.

1. Luo etäisyyssensori:

    1. *Sensors*-paneelin *Create sensor* -laatikossa avaa *Sensor type* -valikko ja valitse *Distance*.

    1. Jätä *Units* arvoksi `Millimeter`.

    1. Tämä sensori on I²C-sensori, joten aseta osoitteeksi `0x29`. Jos käyttäisit fyysistä VL53L0X-sensoria, sen osoite olisi kovakoodattu tähän arvoon.

    1. Valitse **Add**-painike luodaksesi etäisyyssensorin.

    ![Etäisyyssensorin asetukset](../../../../../translated_images/fi/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Etäisyyssensori luodaan ja se näkyy sensorilistassa.

    ![Luotu etäisyyssensori](../../../../../translated_images/fi/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Ohjelmoi etäisyyssensori

Virtuaalinen IoT-laite voidaan nyt ohjelmoida käyttämään simuloitua etäisyyssensoria.

### Tehtävä - ohjelmoi time-of-flight -sensori

1. Luo uusi tiedosto `fruit-quality-detector`-projektissa nimeltä `distance-sensor.py`.

    > 💁 Helppo tapa simuloida useita IoT-laitteita on tehdä jokainen eri Python-tiedostossa ja ajaa ne samanaikaisesti.

1. Aloita yhteys CounterFitiin seuraavalla koodilla:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lisää tämän alle seuraava koodi:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Tämä tuo käyttöön VL53L0X time-of-flight -sensorin kirjastoshimin.

1. Lisää tämän alle seuraava koodi sensorin käyttämiseksi:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Tämä koodi määrittelee etäisyyssensorin ja käynnistää sen.

1. Lopuksi lisää loputon silmukka etäisyyksien lukemiseen:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Tämä koodi odottaa, että sensorilta on saatavilla arvo, ja tulostaa sen konsoliin.

1. Aja tämä koodi.

    > 💁 Muista, että tämä tiedosto on nimeltään `distance-sensor.py`! Varmista, että ajat sen Pythonilla, et `app.py`:llä.

1. Näet etäisyysmittauksia konsolissa. Muuta arvoa CounterFitissä nähdäksesi sen muuttuvan tai käytä satunnaisia arvoja.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Löydät tämän koodin [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) -kansiosta.

😀 Onnittelut, läheisyyssensorin ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.