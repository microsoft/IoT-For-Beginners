<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T21:40:48+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "fi"
}
-->
# Hallitse yövaloa Internetin kautta - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä oppitunnin osassa lähetät telemetriatietoja valotasoista Raspberry Pi -laitteeltasi tai virtuaaliselta IoT-laitteeltasi MQTT-välityspalvelimelle.

## Telemetrian julkaiseminen

Seuraava vaihe on luoda JSON-dokumentti telemetriatiedoista ja lähettää se MQTT-välityspalvelimelle.

### Tehtävä

Julkaise telemetria MQTT-välityspalvelimelle.

1. Avaa yövaloprojekti VS Code -sovelluksessa.

1. Jos käytät virtuaalista IoT-laitetta, varmista, että terminaali käyttää virtuaaliympäristöä. Jos käytät Raspberry Pi:tä, et käytä virtuaaliympäristöä.

1. Lisää seuraava tuonti `app.py`-tiedoston alkuun:

    ```python
    import json
    ```

    `json`-kirjastoa käytetään telemetriatietojen koodaamiseen JSON-dokumentiksi.

1. Lisää seuraava `client_name`-määrittelyn jälkeen:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` on MQTT-aihe, johon laite julkaisee valotasot.

1. Korvaa tiedoston lopussa olevan `while True:` -silmukan sisältö seuraavalla:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Tämä koodi pakkaa valotason JSON-dokumentiksi ja julkaisee sen MQTT-välityspalvelimelle. Sen jälkeen se odottaa hetken vähentääkseen viestien lähetysfrekvenssiä.

1. Suorita koodi samalla tavalla kuin edellisen tehtävän osan koodi. Jos käytät virtuaalista IoT-laitetta, varmista, että CounterFit-sovellus on käynnissä ja että valosensori ja LED on luotu oikeille pinneille.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Löydät tämän koodin [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) -kansiosta tai [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) -kansiosta.

😀 Olet onnistuneesti lähettänyt telemetriatietoja laitteeltasi.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.