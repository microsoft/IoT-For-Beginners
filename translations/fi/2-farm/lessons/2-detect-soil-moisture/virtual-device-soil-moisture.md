<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T21:26:49+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "fi"
}
-->
# Mittaa maaperän kosteutta - Virtuaalinen IoT-laitteisto

Tässä osassa oppituntia lisäät kapasitiivisen maaperän kosteusanturin virtuaaliseen IoT-laitteeseesi ja luet siitä arvoja.

## Virtuaalinen laitteisto

Virtuaalinen IoT-laite käyttää simuloitua Grove-kapasitiivista maaperän kosteusanturia. Tämä pitää tämän harjoituksen samanlaisena kuin fyysisen Grove-kapasitiivisen maaperän kosteusanturin käyttäminen Raspberry Pi:llä.

Fyysisessä IoT-laitteessa maaperän kosteusanturi olisi kapasitiivinen anturi, joka mittaa maaperän kosteutta havaitsemalla maaperän kapasitanssin, joka muuttuu maaperän kosteuden muuttuessa. Kun maaperän kosteus kasvaa, jännite pienenee.

Tämä on analoginen anturi, joten se käyttää simuloitua 10-bittistä ADC:tä raportoidakseen arvon välillä 1–1 023.

### Lisää maaperän kosteusanturi CounterFitiin

Virtuaalisen maaperän kosteusanturin käyttämiseksi sinun täytyy lisätä se CounterFit-sovellukseen.

#### Tehtävä - Lisää maaperän kosteusanturi CounterFitiin

Lisää maaperän kosteusanturi CounterFit-sovellukseen.

1. Luo uusi Python-sovellus tietokoneellesi kansioon nimeltä `soil-moisture-sensor`, jossa on yksi tiedosto nimeltä `app.py`, sekä Python-virtuaaliympäristö, ja lisää CounterFit-pip-paketit.

    > ⚠️ Voit tarvittaessa viitata [ohjeisiin CounterFit Python -projektin luomisesta ja asettamisesta oppitunnilla 1](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Varmista, että CounterFit-verkkosovellus on käynnissä.

1. Luo maaperän kosteusanturi:

    1. *Create sensor* -ruudussa *Sensors*-paneelissa avaa *Sensor type* -valikko ja valitse *Soil Moisture*.

    1. Jätä *Units* asetukseksi *NoUnits*.

    1. Varmista, että *Pin* on asetettu arvoon *0*.

    1. Valitse **Add**-painike luodaksesi *Soil Moisture* -anturin Pin 0:aan.

    ![Maaperän kosteusanturin asetukset](../../../../../translated_images/fi/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Maaperän kosteusanturi luodaan ja se näkyy anturilistassa.

    ![Luotu maaperän kosteusanturi](../../../../../translated_images/fi/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Ohjelmoi maaperän kosteusanturisovellus

Nyt voit ohjelmoida maaperän kosteusanturisovelluksen käyttämällä CounterFit-antureita.

### Tehtävä - Ohjelmoi maaperän kosteusanturisovellus

Ohjelmoi maaperän kosteusanturisovellus.

1. Varmista, että `soil-moisture-sensor`-sovellus on auki VS Code -editorissa.

1. Avaa `app.py`-tiedosto.

1. Lisää seuraava koodi `app.py`-tiedoston alkuun yhdistääksesi sovelluksen CounterFitiin:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lisää seuraava koodi `app.py`-tiedostoon tarvittavien kirjastojen tuomiseksi:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time` -lause tuo `time`-moduulin, jota käytetään myöhemmin tässä tehtävässä.

    `from counterfit_shims_grove.adc import ADC` -lause tuo `ADC`-luokan, jonka avulla voidaan olla vuorovaikutuksessa virtuaalisen analogi-digitaalimuuntimen kanssa, joka voi yhdistää CounterFit-anturiin.

1. Lisää tämän alle seuraava koodi luodaksesi `ADC`-luokan instanssin:

    ```python
    adc = ADC()
    ```

1. Lisää loputon silmukka, joka lukee tämän ADC:n arvoja pinistä 0 ja kirjoittaa tuloksen konsoliin. Tämä silmukka voi sitten odottaa 10 sekuntia lukemien välillä.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Muuta CounterFit-sovelluksessa maaperän kosteusanturin arvoa, jonka sovellus lukee. Voit tehdä tämän kahdella tavalla:

    * Syötä numero *Value*-kenttään maaperän kosteusanturille ja valitse **Set**-painike. Syöttämäsi numero on arvo, jonka anturi palauttaa.

    * Valitse *Random*-valintaruutu ja syötä *Min*- ja *Max*-arvot, sitten valitse **Set**-painike. Joka kerta, kun anturi lukee arvon, se lukee satunnaisen numeron *Min*- ja *Max*-arvojen väliltä.

1. Suorita Python-sovellus. Näet maaperän kosteusmittaukset kirjoitettuna konsoliin. Muuta *Value*- tai *Random*-asetuksia nähdäksesi arvon muuttuvan.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Löydät tämän koodin [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device) -kansiosta.

😀 Maaperän kosteusanturisovelluksesi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.