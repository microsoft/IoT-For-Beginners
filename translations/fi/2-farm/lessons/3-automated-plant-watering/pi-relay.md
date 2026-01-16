<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T21:13:35+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "fi"
}
-->
# Ohjaa relettä - Raspberry Pi

Tässä oppitunnin osassa lisäät releen Raspberry Pi:hin maankosteusanturin lisäksi ja ohjaat sitä maankosteustason perusteella.

## Laitteisto

Raspberry Pi tarvitsee releen.

Käytettävä rele on [Grove-rele](https://www.seeedstudio.com/Grove-Relay.html), normaalisti avoin rele (eli lähtöpiiri on avoin tai irtikytketty, kun releelle ei lähetetä signaalia), joka kestää jopa 250V ja 10A lähtöpiireissä.

Tämä on digitaalinen toimilaite, joten se liitetään Grove Base Hatin digitaaliseen pinniin.

### Liitä rele

Grove-rele voidaan liittää Raspberry Pi:hin.

#### Tehtävä

Liitä rele.

![Grove-rele](../../../../../translated_images/fi/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Työnnä Grove-kaapelin toinen pää releen liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Raspberry Pi on sammutettu, liitä Grove-kaapelin toinen pää Grove Base Hatin digitaaliseen liittimeen, joka on merkitty **D5**. Tämä liitin on toinen vasemmalta GPIO-pinnien vieressä olevassa liitinrivissä. Jätä maankosteusanturi liitetyksi **A0**-liittimeen.

![Grove-rele liitettynä D5-liittimeen ja maankosteusanturi liitettynä A0-liittimeen](../../../../../translated_images/fi/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Työnnä maankosteusanturi maahan, jos se ei ole jo siellä edellisen oppitunnin jäljiltä.

## Ohjelmoi rele

Nyt Raspberry Pi voidaan ohjelmoida käyttämään liitettyä relettä.

### Tehtävä

Ohjelmoi laite.

1. Käynnistä Pi ja odota, että se käynnistyy.

1. Avaa edellisen oppitunnin `soil-moisture-sensor`-projekti VS Codessa, jos se ei ole jo auki. Lisäät tähän projektiin.

1. Lisää seuraava koodi `app.py`-tiedostoon olemassa olevien tuontien alle:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Tämä lause tuo `GroveRelay`-luokan Grove Python -kirjastoista, jotta voit käyttää Grove-relettä.

1. Lisää seuraava koodi `ADC`-luokan määrittelyn alle luodaksesi `GroveRelay`-instanssin:

    ```python
    relay = GroveRelay(5)
    ```

    Tämä luo releen käyttäen pinniä **D5**, digitaalista pinniä, johon liitit releen.

1. Testataksesi, että rele toimii, lisää seuraava koodi `while True:` -silmukkaan:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koodi kytkee releen päälle, odottaa 0,5 sekuntia ja kytkee sen sitten pois päältä.

1. Suorita Python-sovellus. Rele kytkeytyy päälle ja pois päältä 10 sekunnin välein, puolen sekunnin viiveellä päälle- ja poiskytkennän välillä. Kuuluu releen napsahdus, kun se kytkeytyy päälle ja pois. Grove-laudan LED syttyy, kun rele on päällä, ja sammuu, kun rele on pois päältä.

    ![Rele kytkeytyy päälle ja pois päältä](../../../../../images/relay-turn-on-off.gif)

## Ohjaa relettä maankosteuden perusteella

Nyt kun rele toimii, sitä voidaan ohjata maankosteuslukemien perusteella.

### Tehtävä

Ohjaa relettä.

1. Poista äsken lisäämäsi 3 riviä koodia, joilla testasit relettä. Korvaa ne seuraavalla koodilla:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Tämä koodi tarkistaa maankosteustason maankosteusanturista. Jos taso on yli 450, rele kytketään päälle, ja se kytketään pois päältä, kun taso laskee alle 450.

    > 💁 Muista, että kapasitiivinen maankosteusanturi toimii siten, että mitä alhaisempi maankosteuslukema, sitä kosteampi maa on, ja päinvastoin.

1. Suorita Python-sovellus. Näet releen kytkeytyvän päälle tai pois päältä maankosteustason mukaan. Kokeile kuivassa maassa ja lisää sitten vettä.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Löydät tämän koodin [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) -kansiosta.

😀 Onnittelut! Ohjelmasi, joka ohjaa relettä maankosteusanturin avulla, toimii!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.