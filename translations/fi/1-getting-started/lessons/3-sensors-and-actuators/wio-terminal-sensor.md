<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T21:56:29+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "fi"
}
-->
# Lisää sensori - Wio Terminal

Tässä osassa oppituntia käytät Wio Terminalin valosensoria.

## Laitteisto

Tämän oppitunnin sensori on **valosensori**, joka käyttää [valodiodia](https://wikipedia.org/wiki/Photodiode) muuntaakseen valon sähköiseksi signaaliksi. Tämä on analoginen sensori, joka lähettää kokonaislukuarvon välillä 0–1 023, mikä ilmaisee suhteellisen valon määrän. Tämä arvo ei vastaa mitään standardoitua mittayksikköä, kuten [luksia](https://wikipedia.org/wiki/Lux).

Valosensori on sisäänrakennettu Wio Terminaliin ja näkyy laitteen takana olevan kirkkaan muovi-ikkunan läpi.

![Valosensori Wio Terminalin takana](../../../../../translated_images/wio-light-sensor.b1f529f3c95f5165.fi.png)

## Ohjelmoi valosensori

Laite voidaan nyt ohjelmoida käyttämään sisäänrakennettua valosensoria.

### Tehtävä

Ohjelmoi laite.

1. Avaa yövaloprojekti VS Codessa, jonka loit tämän tehtävän aiemmassa osassa.

1. Lisää seuraava rivi `setup`-funktion loppuun:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Tämä rivi määrittää sensorilaitteiston kanssa käytettävät pinnit.

    `WIO_LIGHT`-pinni on GPIO-pinni, joka on yhdistetty sisäänrakennettuun valosensoriin. Tämä pinni on asetettu tilaan `INPUT`, mikä tarkoittaa, että se on yhdistetty sensoriin ja dataa luetaan tästä pinnistä.

1. Poista `loop`-funktion sisältö.

1. Lisää seuraava koodi nyt tyhjään `loop`-funktioon.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Tämä koodi lukee analogisen arvon `WIO_LIGHT`-pinnistä. Se lukee arvon välillä 0–1 023 sisäänrakennetusta valosensorista. Tämä arvo lähetetään sitten sarjaporttiin, jotta voit lukea sen Serial Monitorista, kun koodi on käynnissä. `Serial.print` kirjoittaa tekstin ilman rivinvaihtoa, joten jokainen rivi alkaa tekstillä `Light value:` ja päättyy varsinaiseen valoarvoon.

1. Lisää pieni yhden sekunnin (1 000 ms) viive `loop`-funktion loppuun, koska valotasoja ei tarvitse tarkistaa jatkuvasti. Viive vähentää laitteen virrankulutusta.

    ```cpp
    delay(1000);
    ```

1. Kytke Wio Terminal uudelleen tietokoneeseesi ja lataa uusi koodi samalla tavalla kuin aiemmin.

1. Avaa Serial Monitor. Valoarvot tulostuvat terminaaliin. Peitä ja paljasta Wio Terminalin takana oleva valosensori, ja arvot muuttuvat.

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

> 💁 Löydät tämän koodin [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal) -kansiosta.

😀 Sensorin lisääminen yövaloprojektiisi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.