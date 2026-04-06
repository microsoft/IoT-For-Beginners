# Rakenna yövalo - Raspberry Pi

Tässä osassa oppituntia lisäät valosensorin Raspberry Pi:hin.

## Laitteisto

Tämän oppitunnin sensori on **valosensori**, joka käyttää [valodiodia](https://wikipedia.org/wiki/Photodiode) muuntamaan valon sähköiseksi signaaliksi. Tämä on analoginen sensori, joka lähettää kokonaislukuarvon välillä 0–1 000, ilmaisten suhteellisen valon määrän, joka ei vastaa mitään standardoitua mittayksikköä, kuten [luksia](https://wikipedia.org/wiki/Lux).

Valosensori on ulkoinen Grove-sensori, ja se täytyy liittää Raspberry Pi:n Grove Base -hattuun.

### Liitä valosensori

Grove-valosensori, jota käytetään valotason havaitsemiseen, täytyy liittää Raspberry Pi:hin.

#### Tehtävä - liitä valosensori

Liitä valosensori

![Grove-valosensori](../../../../../translated_images/fi/grove-light-sensor.b8127b7c434e632d.webp)

1. Työnnä Grove-kaapelin toinen pää valosensorimoduulin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Raspberry Pi on sammutettu, liitä Grove-kaapelin toinen pää Grove Base -hatun analogiseen liittimeen, joka on merkitty **A0**. Tämä liitin on toinen oikealta GPIO-pinnien vieressä olevassa liitinrivissä.

![Grove-valosensori liitettynä liittimeen A0](../../../../../translated_images/fi/pi-light-sensor.66cc1e31fa48cd7d.webp)

## Ohjelmoi valosensori

Laite voidaan nyt ohjelmoida käyttämällä Grove-valosensoria.

### Tehtävä - ohjelmoi valosensori

Ohjelmoi laite.

1. Käynnistä Pi ja odota, että se käynnistyy.

1. Avaa yövaloprojekti VS Code -editorissa, jonka loit tämän tehtävän aiemmassa osassa, joko suoraan Pi:llä tai käyttämällä Remote SSH -laajennusta.

1. Avaa `app.py`-tiedosto ja poista siitä kaikki koodi.

1. Lisää seuraava koodi `app.py`-tiedostoon tarvittavien kirjastojen tuomiseksi:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time` -lause tuo `time`-moduulin, jota käytetään myöhemmin tässä tehtävässä.

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor` -lause tuo `GroveLightSensor`-luokan Grove Python -kirjastoista. Tämä kirjasto sisältää koodin Grove-valosensorin kanssa toimimiseen ja asennettiin globaalisti Pi:n asennuksen aikana.

1. Lisää seuraava koodi edellisen koodin jälkeen luodaksesi instanssin luokasta, joka hallitsee valosensoria:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Rivi `light_sensor = GroveLightSensor(0)` luo instanssin `GroveLightSensor`-luokasta, joka on yhdistetty pinniin **A0** – analogiseen Grove-pinniin, johon valosensori on liitetty.

1. Lisää loputtomasti toistuva silmukka edellisen koodin jälkeen, jotta valosensorin arvo voidaan kysyä ja tulostaa konsoliin:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Tämä lukee nykyisen valotason asteikolla 0–1 023 käyttämällä `light`-ominaisuutta `GroveLightSensor`-luokasta. Tämä ominaisuus lukee analogisen arvon pinnistä. Tämä arvo tulostetaan sitten konsoliin.

1. Lisää pieni yhden sekunnin viive silmukan loppuun, koska valotasoja ei tarvitse tarkistaa jatkuvasti. Viive vähentää laitteen virrankulutusta.

    ```python
    time.sleep(1)
    ```

1. Aja seuraava komento VS Code -editorin terminaalista käynnistääksesi Python-sovelluksesi:

    ```sh
    python3 app.py
    ```

    Valoarvot tulostuvat konsoliin. Peitä ja paljasta valosensori, ja arvot muuttuvat:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Löydät tämän koodin [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi) -kansiosta.

😀 Sensorin lisääminen yövaloprojektiisi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.