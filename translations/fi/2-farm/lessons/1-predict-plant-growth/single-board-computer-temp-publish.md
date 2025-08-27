<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T21:03:53+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "fi"
}
-->
# Julkaise lämpötila - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä oppitunnin osassa julkaiset Raspberry Pi:n tai virtuaalisen IoT-laitteen havaitsemat lämpötilaarvot MQTT:n kautta, jotta niitä voidaan myöhemmin käyttää GDD:n laskemiseen.

## Julkaise lämpötila

Kun lämpötila on luettu, se voidaan julkaista MQTT:n kautta "palvelin"-koodille, joka lukee arvot ja tallentaa ne valmiiksi GDD-laskentaa varten.

### Tehtävä - julkaise lämpötila

Ohjelmoi laite julkaisemaan lämpötiladataa.

1. Avaa `temperature-sensor`-sovellusprojekti, jos se ei ole jo avoinna.

1. Toista oppitunnin 4 vaiheet MQTT-yhteyden muodostamiseksi ja telemetrian lähettämiseksi. Käytät samaa julkista Mosquitto-välittäjää.

    Vaiheet tähän ovat:

    - Lisää MQTT:n pip-paketti
    - Lisää koodi MQTT-välittäjään yhdistämiseksi
    - Lisää koodi telemetrian julkaisemiseksi

    > ⚠️ Katso [ohjeet MQTT-yhteyden muodostamiseen](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) ja [ohjeet telemetrian lähettämiseen](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) oppitunnista 4 tarvittaessa.

1. Varmista, että `client_name` heijastaa tämän projektin nimeä:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Telemetriaa varten, lähetä valon arvon sijasta DHT-anturin lukema lämpötilaarvo JSON-dokumentin ominaisuudessa nimeltä `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Lämpötilaa ei tarvitse lukea kovin usein - se ei muutu merkittävästi lyhyessä ajassa, joten aseta `time.sleep` 10 minuuttiin:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 `sleep`-funktio ottaa ajan sekunteina, joten arvon lukemisen helpottamiseksi aika annetaan laskennan tuloksena. 60 sekuntia minuutissa, joten 10 x (60 sekuntia minuutissa) antaa 10 minuutin viiveen.

1. Suorita koodi samalla tavalla kuin suoritat koodin edellisessä tehtävän osassa. Jos käytät virtuaalista IoT-laitetta, varmista, että CounterFit-sovellus on käynnissä ja kosteus- ja lämpötila-anturit on luotu oikeille pinneille.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Löydät tämän koodin [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device)-kansiosta tai [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi)-kansiosta.

😀 Olet onnistuneesti julkaissut lämpötilan telemetriana laitteestasi.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.