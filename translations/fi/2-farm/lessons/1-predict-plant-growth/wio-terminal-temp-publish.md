<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T21:05:59+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "fi"
}
-->
# Julkaise lämpötila - Wio Terminal

Tässä oppitunnin osassa julkaiset Wio Terminalin havaitsemat lämpötilaarvot MQTT:n kautta, jotta niitä voidaan myöhemmin käyttää GDD:n laskemiseen.

## Julkaise lämpötila

Kun lämpötila on luettu, se voidaan julkaista MQTT:n kautta "palvelin"-koodille, joka lukee arvot ja tallentaa ne valmiiksi GDD-laskentaa varten. Mikro-ohjaimet eivät oletusarvoisesti lue aikaa Internetistä tai seuraa aikaa reaaliaikakellolla, vaan laite täytyy ohjelmoida tekemään tämä, olettaen että sillä on tarvittava laitteisto.

Tämän oppitunnin yksinkertaistamiseksi aikaa ei lähetetä anturidatan mukana, vaan se voidaan lisätä palvelinkoodissa myöhemmin, kun viestit vastaanotetaan.

### Tehtävä

Ohjelmoi laite julkaisemaan lämpötiladata.

1. Avaa `temperature-sensor` Wio Terminal -projekti

1. Toista oppitunnin 4 vaiheet MQTT-yhteyden muodostamiseksi ja telemetrian lähettämiseksi. Käytät samaa julkista Mosquitto-välittäjää.

    Vaiheet tähän ovat:

    - Lisää Seeed WiFi- ja MQTT-kirjastot `.ini`-tiedostoon
    - Lisää konfiguraatiotiedosto ja koodi WiFi-yhteyden muodostamiseksi
    - Lisää koodi MQTT-välittäjään yhdistämiseksi
    - Lisää koodi telemetrian julkaisemiseksi

    > ⚠️ Katso [ohjeet MQTT-yhteyden muodostamiseen](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) ja [ohjeet telemetrian lähettämiseen](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) oppitunnista 4 tarvittaessa.

1. Varmista, että `CLIENT_NAME` `config.h`-otsikkotiedostossa vastaa tätä projektia:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Telemetriaa varten, lähetä DHT-anturin lukema lämpötilaarvo JSON-dokumentin ominaisuudessa nimeltä `temperature` muuttamalla `loop`-funktiota tiedostossa `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Lämpötilaa ei tarvitse lukea kovin usein - se ei muutu merkittävästi lyhyessä ajassa, joten aseta `delay` `loop`-funktiossa 10 minuuttiin:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay`-funktio ottaa ajan millisekunteina, joten lukemisen helpottamiseksi arvo annetaan laskennan tuloksena. 1 000 ms sekunnissa, 60 s minuutissa, joten 10 x (60 s minuutissa) x (1 000 ms sekunnissa) antaa 10 minuutin viiveen.

1. Lataa tämä Wio Terminaliin ja käytä sarjamonitoria nähdäksesi lämpötilan lähettämisen MQTT-välittäjälle.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Löydät tämän koodin [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) -kansiosta.

😀 Olet onnistuneesti julkaissut lämpötilan telemetriana laitteestasi.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.