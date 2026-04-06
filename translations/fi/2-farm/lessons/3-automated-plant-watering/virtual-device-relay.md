# Ohjaa relettä - Virtuaalinen IoT-laitteisto

Tässä oppitunnin osassa lisäät releen virtuaaliseen IoT-laitteeseesi maankosteusanturin lisäksi ja ohjaat sitä maankosteustason perusteella.

## Virtuaalinen laitteisto

Virtuaalinen IoT-laite käyttää simuloitua Grove-relettä. Tämä pitää tämän laboratorion samanlaisena kuin fyysisen Grove-releen käyttäminen Raspberry Pi:n kanssa.

Fyysisessä IoT-laitteessa rele olisi normaalisti avoin rele (eli lähtöpiiri on avoin tai irrotettu, kun releelle ei lähetetä signaalia). Tällainen rele voi käsitellä lähtöpiirejä jopa 250V ja 10A asti.

### Lisää rele CounterFit-sovellukseen

Virtuaalisen releen käyttämiseksi sinun täytyy lisätä se CounterFit-sovellukseen.

#### Tehtävä

Lisää rele CounterFit-sovellukseen.

1. Avaa `soil-moisture-sensor`-projekti viime oppitunnilta VS Code:ssa, jos se ei ole jo auki. Tulet lisäämään tähän projektiin.

1. Varmista, että CounterFit-verkkosovellus on käynnissä.

1. Luo rele:

    1. *Create actuator* -laatikossa *Actuators*-paneelissa, avaa *Actuator type* -valikko ja valitse *Relay*.

    1. Aseta *Pin* arvoksi *5*.

    1. Valitse **Add**-painike luodaksesi releen Pin 5:lle.

    ![Releen asetukset](../../../../../translated_images/fi/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    Rele luodaan ja se näkyy aktuaattorilistassa.

    ![Luotu rele](../../../../../translated_images/fi/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Ohjelmoi rele

Maankosteusanturisovellus voidaan nyt ohjelmoida käyttämään virtuaalista relettä.

### Tehtävä

Ohjelmoi virtuaalinen laite.

1. Avaa `soil-moisture-sensor`-projekti viime oppitunnilta VS Code:ssa, jos se ei ole jo auki. Tulet lisäämään tähän projektiin.

1. Lisää seuraava koodi `app.py`-tiedostoon olemassa olevien tuontien alapuolelle:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Tämä lause tuo `GroveRelay`-luokan Grove Python -kirjastosta, jotta voidaan käyttää virtuaalista Grove-relettä.

1. Lisää seuraava koodi `ADC`-luokan määrittelyn alapuolelle luodaksesi `GroveRelay`-instanssin:

    ```python
    relay = GroveRelay(5)
    ```

    Tämä luo releen käyttäen pinniä **5**, johon rele on kytketty.

1. Testataksesi, että rele toimii, lisää seuraava koodi `while True:`-silmukan sisälle:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koodi kytkee releen päälle, odottaa 0,5 sekuntia ja kytkee sen pois päältä.

1. Suorita Python-sovellus. Rele kytkeytyy päälle ja pois päältä 10 sekunnin välein, puolen sekunnin viiveellä päälle ja pois päältä kytkemisen välillä. Näet virtuaalisen releen CounterFit-sovelluksessa sulkeutuvan ja avautuvan releen kytkeytyessä päälle ja pois päältä.

    ![Virtuaalinen rele kytkeytyy päälle ja pois päältä](../../../../../images/virtual-relay-turn-on-off.gif)

## Ohjaa relettä maankosteuden perusteella

Nyt kun rele toimii, sitä voidaan ohjata maankosteuslukemien perusteella.

### Tehtävä

Ohjaa relettä.

1. Poista 3 koodiriviä, jotka lisäsit testataksesi relettä. Korvaa ne seuraavalla koodilla:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Tämä koodi tarkistaa maankosteustason maankosteusanturista. Jos taso on yli 450, se kytkee releen päälle, ja jos taso laskee alle 450, se kytkee releen pois päältä.

    > 💁 Muista, että kapasitiivinen maankosteusanturi lukee: mitä alhaisempi maankosteustaso, sitä enemmän kosteutta maassa on ja päinvastoin.

1. Suorita Python-sovellus. Näet releen kytkeytyvän päälle tai pois päältä maankosteustasojen mukaan. Muuta *Value*- tai *Random*-asetuksia maankosteusanturille nähdäksesi arvon muuttuvan.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Löydät tämän koodin [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) -kansiosta.

😀 Virtuaalinen maankosteusanturi, joka ohjaa relettä, onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.