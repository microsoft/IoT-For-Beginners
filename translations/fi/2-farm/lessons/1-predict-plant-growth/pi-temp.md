<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-27T21:07:51+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "fi"
}
-->
# Mittaa lämpötila - Raspberry Pi

Tässä oppitunnin osassa lisäät lämpötila-anturin Raspberry Pi:hin.

## Laitteisto

Anturi, jota käytät, on [DHT11 kosteus- ja lämpötila-anturi](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), joka yhdistää kaksi anturia yhteen pakettiin. Tämä on melko suosittu, ja markkinoilla on saatavilla useita antureita, jotka yhdistävät lämpötilan, kosteuden ja joskus myös ilmanpaineen. Lämpötila-anturikomponentti on negatiivisen lämpötilakertoimen (NTC) termistori, eli termistori, jonka vastus pienenee lämpötilan noustessa.

Tämä on digitaalinen anturi, joten siinä on sisäänrakennettu ADC, joka luo digitaalisen signaalin sisältäen lämpötila- ja kosteustiedot, joita mikrokontrolleri voi lukea.

### Yhdistä lämpötila-anturi

Grove-lämpötila-anturi voidaan liittää Raspberry Pi:hin.

#### Tehtävä

Yhdistä lämpötila-anturi

![Grove-lämpötila-anturi](../../../../../translated_images/fi/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Työnnä Grove-kaapelin toinen pää kosteus- ja lämpötila-anturin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Raspberry Pi on sammutettu, liitä Grove-kaapelin toinen pää digitaaliseen liittimeen, joka on merkitty **D5** Grove Base hatissa, joka on kiinnitetty Pi:hin. Tämä liitin on toinen vasemmalta rivissä, joka on GPIO-pinnien vieressä.

![Grove-lämpötila-anturi liitettynä liittimeen A0](../../../../../translated_images/fi/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## Ohjelmoi lämpötila-anturi

Laite voidaan nyt ohjelmoida käyttämään liitettyä lämpötila-anturia.

### Tehtävä

Ohjelmoi laite.

1. Käynnistä Pi ja odota sen käynnistymistä.

1. Käynnistä VS Code joko suoraan Pi:ssä tai yhdistä Remote SSH -laajennuksen kautta.

    > ⚠️ Voit tarvittaessa viitata [ohjeisiin VS Coden asennuksesta ja käynnistämisestä oppitunnissa 1](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. Luo terminaalista uusi kansio `pi`-käyttäjän kotihakemistoon nimeltä `temperature-sensor`. Luo tähän kansioon tiedosto nimeltä `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Avaa tämä kansio VS Codessa.

1. Lämpötila- ja kosteusanturin käyttämiseksi tarvitaan lisä-Pip-paketti. Asenna tämä Pip-paketti Pi:lle suorittamalla seuraava komento VS Coden terminaalista:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Lisää seuraava koodi `app.py`-tiedostoon tarvittavien kirjastojen tuomiseksi:

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` -lause tuo `DHT`-anturin luokan, joka mahdollistaa vuorovaikutuksen Grove-lämpötila-anturin kanssa `seeed_dht`-moduulista.

1. Lisää seuraava koodi edellisen koodin jälkeen luodaksesi instanssin luokasta, joka hallitsee lämpötila-anturia:

    ```python
    sensor = DHT("11", 5)
    ```

    Tämä määrittää instanssin `DHT`-luokasta, joka hallitsee **D**igitaalisia **H**umidity- ja **T**emperature-antureita. Ensimmäinen parametri kertoo koodille, että käytettävä anturi on *DHT11*-anturi - käyttämäsi kirjasto tukee tämän anturin muita versioita. Toinen parametri kertoo koodille, että anturi on liitetty digitaaliseen porttiin `D5` Grove Base hatissa.

    > ✅ Muista, että kaikilla liittimillä on yksilölliset pinninumerot. Pinnit 0, 2, 4 ja 6 ovat analogisia pinnejä, pinnit 5, 16, 18, 22, 24 ja 26 ovat digitaalisia pinnejä.

1. Lisää loputon silmukka edellisen koodin jälkeen, joka kysyy lämpötila-anturin arvoa ja tulostaa sen konsoliin:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()`-kutsu palauttaa tuple-muotoisen arvon, joka sisältää kosteuden ja lämpötilan. Tarvitset vain lämpötilan, joten kosteus jätetään huomiotta. Lämpötila-arvo tulostetaan konsoliin.

1. Lisää pieni kymmenen sekunnin viive silmukan loppuun, koska lämpötilatasoja ei tarvitse tarkistaa jatkuvasti. Viive vähentää laitteen virrankulutusta.

    ```python
    time.sleep(10)
    ```

1. Suorita seuraava komento VS Coden terminaalista käynnistääksesi Python-sovelluksesi:

    ```sh
    python3 app.py
    ```

    Sinun pitäisi nähdä lämpötila-arvoja tulostettuna konsoliin. Käytä jotain anturin lämmittämiseen, kuten paina peukaloa sen päälle tai käytä tuuletinta nähdäksesi arvojen muuttuvan:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Löydät tämän koodin [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) -kansiosta.

😀 Lämpötila-anturin ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.