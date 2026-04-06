# Rakenna yövalo - Virtuaalinen IoT-laitteisto

Tässä oppitunnin osassa lisäät LED-valon virtuaaliseen IoT-laitteeseesi ja käytät sitä yövalon luomiseen.

## Virtuaalinen laitteisto

Yövalo tarvitsee yhden toimilaitteen, joka luodaan CounterFit-sovelluksessa.

Toimilaite on **LED**. Fyysisessä IoT-laitteessa se olisi [valoa emittoiva diodi](https://wikipedia.org/wiki/Light-emitting_diode), joka tuottaa valoa, kun sen läpi kulkee sähkövirta. Tämä on digitaalinen toimilaite, jolla on kaksi tilaa: päällä ja pois päältä. Arvon 1 lähettäminen kytkee LED-valon päälle, ja arvo 0 kytkee sen pois päältä.

Yövalon logiikka pseudokoodina:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Lisää toimilaite CounterFit-sovellukseen

Virtuaalisen LED-valon käyttämiseksi sinun täytyy lisätä se CounterFit-sovellukseen.

#### Tehtävä - lisää toimilaite CounterFit-sovellukseen

Lisää LED CounterFit-sovellukseen.

1. Varmista, että CounterFit-verkkosovellus on käynnissä edellisen tehtävän osan jäljiltä. Jos ei, käynnistä se uudelleen ja lisää valosensori uudelleen.

1. Luo LED:

    1. *Create actuator* -laatikossa *Actuator* -paneelissa, avaa *Actuator type* -valikko ja valitse *LED*.

    1. Aseta *Pin* arvoksi *5*.

    1. Valitse **Add**-painike luodaksesi LED Pin 5:lle.

    ![LED-asetukset](../../../../../translated_images/fi/counterfit-create-led.ba9db1c9b8c622a6.webp)

    LED luodaan ja se ilmestyy toimilaitteiden listaan.

    ![Luotu LED](../../../../../translated_images/fi/counterfit-led.c0ab02de6d256ad8.webp)

    Kun LED on luotu, voit muuttaa sen väriä *Color*-valitsimella. Valitse **Set**-painike muuttaaksesi väriä valinnan jälkeen.

### Ohjelmoi yövalo

Yövalo voidaan nyt ohjelmoida käyttämällä CounterFit-valosensoria ja LED-valoa.

#### Tehtävä - ohjelmoi yövalo

Ohjelmoi yövalo.

1. Avaa yövaloprojekti VS Code -editorissa, jonka loit edellisen tehtävän osassa. Sulje ja luo terminaali uudelleen varmistaaksesi, että se käyttää virtuaalista ympäristöä tarvittaessa.

1. Avaa `app.py`-tiedosto.

1. Lisää seuraava koodi `app.py`-tiedoston alkuun muiden `import`-rivien alle tuodaksesi tarvittavan kirjaston:

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed` -rivi tuo `GroveLed`-luokan CounterFit Grove -shim Python-kirjastoista. Tämä kirjasto sisältää koodin LED-valon hallintaan, joka on luotu CounterFit-sovelluksessa.

1. Lisää seuraava koodi `light_sensor`-määrittelyn jälkeen luodaksesi instanssin luokasta, joka hallitsee LED-valoa:

    ```python
    led = GroveLed(5)
    ```

    Rivi `led = GroveLed(5)` luo instanssin `GroveLed`-luokasta, joka yhdistetään pinniin **5** - CounterFit Grove -pinniin, johon LED on kytketty.

1. Lisää tarkistus `while`-silmukan sisään, ennen `time.sleep`-riviä, tarkistaaksesi valotasot ja kytkeäksesi LED-valon päälle tai pois päältä:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Tämä koodi tarkistaa `light`-arvon. Jos arvo on alle 300, se kutsuu `GroveLed`-luokan `on`-metodia, joka lähettää digitaalisen arvon 1 LED-valolle, kytkien sen päälle. Jos valon arvo on 300 tai suurempi, se kutsuu `off`-metodia, joka lähettää digitaalisen arvon 0 LED-valolle, kytkien sen pois päältä.

    > 💁 Tämä koodi tulee sisentää samalle tasolle kuin `print('Light level:', light)`-rivi, jotta se on `while`-silmukan sisällä!

1. Suorita seuraava komento VS Code -terminaalista ajaaksesi Python-sovelluksesi:

    ```sh
    python3 app.py
    ```

    Valoarvot tulostuvat konsoliin.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Muuta *Value*- tai *Random*-asetuksia vaihdellaksesi valotasoa yli ja alle 300. LED-valo kytkeytyy päälle ja pois päältä.

![LED CounterFit-sovelluksessa kytkeytymässä päälle ja pois päältä valotason muuttuessa](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Löydät tämän koodin [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device) -kansiosta.

😀 Yövalon ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.