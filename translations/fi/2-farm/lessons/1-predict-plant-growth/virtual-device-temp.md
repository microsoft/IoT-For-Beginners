<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-27T21:06:31+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "fi"
}
-->
# Mittaa lämpötila - Virtuaalinen IoT-laitteisto

Tässä oppitunnin osassa lisäät lämpötila-anturin virtuaaliseen IoT-laitteeseesi.

## Virtuaalinen laitteisto

Virtuaalinen IoT-laite käyttää simuloitua Grove Digital Humidity and Temperature -anturia. Tämä pitää tämän harjoituksen samanlaisena kuin fyysisen Grove DHT11 -anturin käyttäminen Raspberry Pi:ssä.

Anturi yhdistää **lämpötila-anturin** ja **kosteusanturin**, mutta tässä harjoituksessa keskitytään vain lämpötila-anturiin. Fyysisessä IoT-laitteessa lämpötila-anturi olisi [termistori](https://wikipedia.org/wiki/Thermistor), joka mittaa lämpötilaa havaitsemalla vastuksen muutoksen lämpötilan muuttuessa. Lämpötila-anturit ovat yleensä digitaalisia antureita, jotka muuntavat sisäisesti mitatun vastuksen lämpötilaksi Celsius-asteina (tai Kelvineinä tai Fahrenheit-asteina).

### Lisää anturit CounterFitiin

Virtuaalisen kosteus- ja lämpötila-anturin käyttämiseksi sinun täytyy lisätä nämä kaksi anturia CounterFit-sovellukseen.

#### Tehtävä - lisää anturit CounterFitiin

Lisää kosteus- ja lämpötila-anturit CounterFit-sovellukseen.

1. Luo tietokoneellesi uusi Python-sovellus kansioon nimeltä `temperature-sensor`, jossa on yksi tiedosto nimeltä `app.py`, sekä Python-virtuaaliympäristö, ja lisää CounterFit-pip-paketit.

    > ⚠️ Voit tarvittaessa viitata [ohjeisiin CounterFit Python -projektin luomisesta ja asettamisesta oppitunnissa 1](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Asenna lisäpaketti pipin kautta, jotta voit asentaa CounterFit-shimin DHT11-anturille. Varmista, että asennat tämän terminaalista, jossa virtuaaliympäristö on aktivoitu.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Varmista, että CounterFit-verkkosovellus on käynnissä.

1. Luo kosteusanturi:

    1. *Create sensor* -ruudussa *Sensors*-paneelissa avaa *Sensor type* -valikko ja valitse *Humidity*.

    1. Jätä *Units* asetukseksi *Percentage*.

    1. Varmista, että *Pin* on asetettu arvoon *5*.

    1. Valitse **Add**-painike luodaksesi kosteusanturin pinniin 5.

    ![Kosteusanturin asetukset](../../../../../translated_images/fi/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    Kosteusanturi luodaan ja se näkyy anturilistassa.

    ![Luotu kosteusanturi](../../../../../translated_images/fi/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. Luo lämpötila-anturi:

    1. *Create sensor* -ruudussa *Sensors*-paneelissa avaa *Sensor type* -valikko ja valitse *Temperature*.

    1. Jätä *Units* asetukseksi *Celsius*.

    1. Varmista, että *Pin* on asetettu arvoon *6*.

    1. Valitse **Add**-painike luodaksesi lämpötila-anturin pinniin 6.

    ![Lämpötila-anturin asetukset](../../../../../translated_images/fi/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    Lämpötila-anturi luodaan ja se näkyy anturilistassa.

    ![Luotu lämpötila-anturi](../../../../../translated_images/fi/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## Ohjelmoi lämpötila-anturisovellus

Nyt voit ohjelmoida lämpötila-anturisovelluksen käyttämällä CounterFit-antureita.

### Tehtävä - ohjelmoi lämpötila-anturisovellus

Ohjelmoi lämpötila-anturisovellus.

1. Varmista, että `temperature-sensor`-sovellus on auki VS Codessa.

1. Avaa `app.py`-tiedosto.

1. Lisää seuraava koodi `app.py`-tiedoston alkuun yhdistääksesi sovelluksen CounterFitiin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lisää seuraava koodi `app.py`-tiedostoon tarvittavien kirjastojen tuomiseksi:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT` -lause tuo `DHT`-anturiklassin, jonka avulla voidaan käyttää virtuaalista Grove-lämpötila-anturia `counterfit_shims_seeed_python_dht`-moduulin shimin kautta.

1. Lisää seuraava koodi edellisen koodin jälkeen luodaksesi instanssin, joka hallitsee virtuaalista kosteus- ja lämpötila-anturia:

    ```python
    sensor = DHT("11", 5)
    ```

    Tämä määrittää `DHT`-luokan instanssin, joka hallitsee virtuaalista **D**igitaali**H**umidity ja **T**emperature -anturia. Ensimmäinen parametri kertoo koodille, että käytettävä anturi on virtuaalinen *DHT11*-anturi. Toinen parametri kertoo koodille, että anturi on kytketty porttiin `5`.

    > 💁 CounterFit simuloi tätä yhdistettyä kosteus- ja lämpötila-anturia yhdistämällä kahteen anturiin: kosteusanturiin annetussa pinnissä ja lämpötila-anturiin, joka toimii seuraavassa pinnissä. Jos kosteusanturi on pinnissä 5, shim odottaa lämpötila-anturin olevan pinnissä 6.

1. Lisää loputon silmukka edellisen koodin jälkeen, jotta lämpötila-anturin arvo voidaan kysyä ja tulostaa konsoliin:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Kutsu `sensor.read()` palauttaa tuplen, joka sisältää kosteuden ja lämpötilan. Tarvitset vain lämpötilan arvon, joten kosteusarvo jätetään huomiotta. Lämpötilan arvo tulostetaan sitten konsoliin.

1. Lisää pieni kymmenen sekunnin viive silmukan loppuun, koska lämpötilatasoja ei tarvitse tarkistaa jatkuvasti. Viive vähentää laitteen virrankulutusta.

    ```python
    time.sleep(10)
    ```

1. Suorita seuraava komento aktivoidussa virtuaaliympäristössä VS Coden terminaalista ajaaksesi Python-sovelluksesi:

    ```sh
    python app.py
    ```

1. Muuta CounterFit-sovelluksessa lämpötila-anturin arvoa, jonka sovellus lukee. Voit tehdä tämän kahdella tavalla:

    * Syötä numero *Value*-kenttään lämpötila-anturia varten ja valitse **Set**-painike. Syöttämäsi numero on arvo, jonka anturi palauttaa.

    * Valitse *Random*-valintaruutu ja syötä *Min*- ja *Max*-arvot, sitten valitse **Set**-painike. Joka kerta, kun anturi lukee arvon, se lukee satunnaisen numeron *Min*- ja *Max*-arvojen väliltä.

    Näet konsolissa arvot, jotka olet asettanut. Muuta *Value*- tai *Random*-asetuksia nähdäksesi arvon muuttuvan.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Löydät tämän koodin [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device) -kansiosta.

😀 Lämpötila-anturiohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.