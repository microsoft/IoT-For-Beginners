<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-27T21:53:05+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "fi"
}
-->
# Rakenna yövalo - Raspberry Pi

Tässä osassa oppituntia lisäät LED-valon Raspberry Pi:hin ja käytät sitä yövalon luomiseen.

## Laitteisto

Yövalo tarvitsee nyt toimilaitteen.

Toimilaite on **LED**, [valoa emittoiva diodi](https://wikipedia.org/wiki/Light-emitting_diode), joka tuottaa valoa, kun sen läpi kulkee virta. Tämä on digitaalinen toimilaite, jolla on kaksi tilaa: päällä ja pois päältä. Arvon 1 lähettäminen kytkee LED-valon päälle, ja arvo 0 kytkee sen pois päältä. LED on ulkoinen Grove-toimilaite, joka täytyy liittää Grove Base -hattuun Raspberry Pi:ssä.

Yövalon logiikka pseudokoodina:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Liitä LED

Grove LED tulee moduulina, jossa on valikoima LED-valoja, joten voit valita haluamasi värin.

#### Tehtävä - liitä LED

Liitä LED.

![Grove LED](../../../../../translated_images/fi/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Valitse suosikkisi LED-valo ja aseta sen jalat LED-moduulin kahteen reikään.

    LED-valot ovat valoa emittoivia diodeja, ja diodit ovat elektronisia komponentteja, jotka voivat kuljettaa virtaa vain yhteen suuntaan. Tämä tarkoittaa, että LED täytyy liittää oikein päin, muuten se ei toimi.

    Yksi LED-valon jaloista on positiivinen pinni, toinen negatiivinen pinni. LED ei ole täysin pyöreä ja on hieman litteämpi toiselta puolelta. Litteämpi puoli on negatiivinen pinni. Kun liität LED-valon moduuliin, varmista, että pyöreämmän puolen pinni on liitetty moduulin ulkopuolella olevaan **+**-merkittyyn liittimeen ja litteämpi puoli on liitetty moduulin keskellä olevaan liittimeen.

1. LED-moduulissa on pyörityspainike, jolla voi säätää kirkkautta. Käännä tämä aluksi täysin auki kiertämällä sitä vastapäivään niin pitkälle kuin se menee pienellä ristipääruuvimeisselillä.

1. Aseta Grove-kaapelin toinen pää LED-moduulin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Raspberry Pi on sammutettu, liitä Grove-kaapelin toinen pää Grove Base -hatun digitaaliseen liittimeen, joka on merkitty **D5**. Tämä liitin on toinen vasemmalta GPIO-pinnien vieressä olevassa liitinrivissä.

![Grove LED liitettynä D5-liittimeen](../../../../../translated_images/fi/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## Ohjelmoi yövalo

Yövalo voidaan nyt ohjelmoida käyttämällä Grove-valoanturia ja Grove-LED-valoa.

### Tehtävä - ohjelmoi yövalo

Ohjelmoi yövalo.

1. Käynnistä Pi ja odota, että se käynnistyy.

1. Avaa yövaloprojekti VS Code -editorissa, jonka loit tämän tehtävän aiemmassa osassa, joko suoraan Pi:llä tai Remote SSH -laajennuksen avulla.

1. Lisää seuraava koodi `app.py`-tiedostoon tuodaksesi tarvittavan kirjaston. Tämä tulisi lisätä yläosaan muiden `import`-rivien alle.

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed` -lause tuo `GroveLed`-luokan Grove Python -kirjastoista. Tämä kirjasto sisältää koodia Grove-LED-valon kanssa toimimiseen.

1. Lisää seuraava koodi `light_sensor`-määrittelyn jälkeen luodaksesi instanssin luokasta, joka hallitsee LED-valoa:

    ```python
    led = GroveLed(5)
    ```

    Rivi `led = GroveLed(5)` luo instanssin `GroveLed`-luokasta, joka on liitetty pinniin **D5** - digitaaliseen Grove-pinniin, johon LED on liitetty.

    > 💁 Kaikilla liittimillä on yksilölliset pinninumerot. Pinnit 0, 2, 4 ja 6 ovat analogisia pinnejä, pinnit 5, 16, 18, 22, 24 ja 26 ovat digitaalisia pinnejä.

1. Lisää tarkistus `while`-silmukan sisään ja ennen `time.sleep`-riviä tarkistaaksesi valotasot ja kytkeäksesi LED-valon päälle tai pois päältä:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Tämä koodi tarkistaa `light`-arvon. Jos arvo on alle 300, se kutsuu `GroveLed`-luokan `on`-metodia, joka lähettää digitaalisen arvon 1 LED-valolle, kytkien sen päälle. Jos valon arvo on 300 tai enemmän, se kutsuu `off`-metodia, joka lähettää digitaalisen arvon 0 LED-valolle, kytkien sen pois päältä.

    > 💁 Tämä koodi tulisi sisentää samalle tasolle kuin `print('Light level:', light)`-rivi, jotta se on `while`-silmukan sisällä!

    > 💁 Kun digitaalisia arvoja lähetetään toimilaitteille, arvo 0 vastaa 0V, ja arvo 1 vastaa laitteen maksimijännitettä. Raspberry Pi:ssä Grove-antureiden ja -toimilaitteiden kanssa arvo 1 vastaa 3.3V.

1. Suorita seuraava komento VS Code -editorin terminaalista käynnistääksesi Python-sovelluksesi:

    ```sh
    python3 app.py
    ```

    Valoarvot tulostuvat konsoliin.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Peitä ja paljasta valoanturi. Huomaa, kuinka LED-valo syttyy, jos valotaso on 300 tai vähemmän, ja sammuu, kun valotaso on yli 300.

    > 💁 Jos LED ei syty, varmista, että se on liitetty oikein päin ja pyörityspainike on asetettu täysille.

![LED liitettynä Pi:hin syttyy ja sammuu valotason muuttuessa](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Löydät tämän koodin [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi) -kansiosta.

😀 Yövaloprojektisi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.