# Rakenna yövalo - Wio Terminal

Tässä osassa oppituntia lisäät LED-valon Wio Terminal -laitteeseesi ja käytät sitä yövalon luomiseen.

## Laitteisto

Yövalo tarvitsee nyt toimilaitteen.

Toimilaitteena toimii **LED**, [valoa emittoiva diodi](https://wikipedia.org/wiki/Light-emitting_diode), joka tuottaa valoa, kun sen läpi kulkee virta. Tämä on digitaalinen toimilaite, jolla on kaksi tilaa: päällä ja pois päältä. Arvon 1 lähettäminen kytkee LED-valon päälle, ja arvo 0 sammuttaa sen. Tämä on ulkoinen Grove-toimilaite, joka täytyy liittää Wio Terminal -laitteeseen.

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

![Grove LED](../../../../../translated_images/fi/grove-led.6c853be93f473cf2.webp)

1. Valitse suosikkisi LED-valo ja aseta sen jalat LED-moduulin kahteen reikään.

    LED-valot ovat valoa emittoivia diodeja, ja diodit ovat elektronisia komponentteja, jotka kuljettavat virtaa vain yhteen suuntaan. Tämä tarkoittaa, että LED-valo täytyy liittää oikein päin, muuten se ei toimi.

    Yksi LED-valon jaloista on positiivinen pinni, toinen negatiivinen pinni. LED-valo ei ole täysin pyöreä, vaan sen toinen puoli on hieman litteämpi. Litteämpi puoli on negatiivinen pinni. Kun liität LED-valon moduuliin, varmista, että pyöreämmän puolen pinni on liitetty moduulin ulkopuolella olevaan **+**-merkinnällä varustettuun liittimeen, ja litteämpi puoli on liitetty moduulin keskiosaa lähempänä olevaan liittimeen.

1. LED-moduulissa on pyörivä säätönappi, jolla voit säätää kirkkautta. Käännä tämä aluksi täysin auki kiertämällä sitä vastapäivään niin pitkälle kuin se menee pienellä ristipääruuvimeisselillä.

1. Aseta Grove-kaapelin toinen pää LED-moduulin liittimeen. Se menee sisään vain yhdellä tavalla.

1. Kun Wio Terminal ei ole liitetty tietokoneeseen tai muuhun virtalähteeseen, liitä Grove-kaapelin toinen pää Wio Terminal -laitteen oikeanpuoleiseen Grove-liittimeen, kun katsot näyttöä. Tämä liitin on kauimpana virtapainikkeesta.

    > 💁 Oikeanpuoleista Grove-liitintä voidaan käyttää analogisten tai digitaalisten antureiden ja toimilaitteiden kanssa. Vasemmanpuoleinen liitin on tarkoitettu vain digitaalisten antureiden ja toimilaitteiden käyttöön. C käsitellään myöhemmässä oppitunnissa.

![Grove LED liitetty oikeanpuoleiseen liittimeen](../../../../../translated_images/fi/wio-led.265a1897e72d7f21.webp)

## Ohjelmoi yövalo

Yövalo voidaan nyt ohjelmoida käyttämällä sisäänrakennettua valosensoria ja Grove LED-valoa.

### Tehtävä - ohjelmoi yövalo

Ohjelmoi yövalo.

1. Avaa yövaloprojekti VS Code -ohjelmassa, jonka loit tämän tehtävän aiemmassa osassa.

1. Lisää seuraava rivi `setup`-funktion loppuun:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Tämä rivi määrittää pinnin, jota käytetään LED-valon kanssa kommunikointiin Grove-portin kautta.

    `D0`-pinni on digitaalinen pinni oikeanpuoleiselle Grove-liittimelle. Tämä pinni asetetaan `OUTPUT`-tilaan, mikä tarkoittaa, että se yhdistetään toimilaitteeseen ja dataa kirjoitetaan pinnille.

1. Lisää seuraava koodi heti `delay`-kohdan eteen loop-funktiossa:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Tämä koodi tarkistaa `light`-arvon. Jos arvo on alle 300, se lähettää `HIGH`-arvon `D0`-digitaalipinnille. Tämä `HIGH`-arvo on 1, joka kytkee LED-valon päälle. Jos valo on 300 tai enemmän, pinnille lähetetään `LOW`-arvo, joka on 0, ja LED-valo sammuu.

    > 💁 Kun lähetetään digitaalisia arvoja toimilaitteille, LOW-arvo on 0v, ja HIGH-arvo on laitteen maksimijännite. Wio Terminal -laitteessa HIGH-jännite on 3.3V.

1. Liitä Wio Terminal uudelleen tietokoneeseesi ja lataa uusi koodi kuten aiemmin.

1. Liitä Serial Monitor. Valoarvot tulostuvat terminaaliin.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Peitä ja paljasta valosensori. Huomaa, kuinka LED-valo syttyy, jos valotaso on 300 tai vähemmän, ja sammuu, kun valotaso on yli 300.

![LED liitettynä Wio Terminal -laitteeseen, syttyy ja sammuu valotason muuttuessa](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Löydät tämän koodin [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal) -kansiosta.

😀 Yövalon ohjelmointi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.