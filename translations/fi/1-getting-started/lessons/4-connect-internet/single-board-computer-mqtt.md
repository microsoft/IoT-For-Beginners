<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T21:46:20+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "fi"
}
-->
# Ohjaa yövaloa Internetin kautta - Virtuaalinen IoT-laitteisto ja Raspberry Pi

IoT-laitteen täytyy olla ohjelmoitu kommunikoimaan *test.mosquitto.org*-palvelimen kanssa käyttäen MQTT-protokollaa, jotta se voi lähettää telemetriatietoja valosensorin lukemista ja vastaanottaa komentoja LED-valon ohjaamiseen.

Tässä oppitunnin osassa yhdistät Raspberry Pi -laitteesi tai virtuaalisen IoT-laitteesi MQTT-välityspalvelimeen.

## Asenna MQTT-asiakasohjelman paketti

Jotta voit kommunikoida MQTT-välityspalvelimen kanssa, sinun täytyy asentaa MQTT-kirjaston pip-paketti joko Pi-laitteellesi tai virtuaaliseen ympäristöön, jos käytät virtuaalista laitetta.

### Tehtävä

Asenna pip-paketti

1. Avaa yövaloprojekti VS Code -ohjelmassa.

1. Jos käytät virtuaalista IoT-laitetta, varmista, että terminaali käyttää virtuaalista ympäristöä. Jos käytät Raspberry Pi -laitetta, et käytä virtuaalista ympäristöä.

1. Suorita seuraava komento asentaaksesi MQTT-pip-paketin:

    ```sh
    pip3 install paho-mqtt
    ```

## Ohjelmoi laite

Laite on valmis ohjelmoitavaksi.

### Tehtävä

Kirjoita laitteen koodi.

1. Lisää seuraava tuonti `app.py`-tiedoston alkuun:

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client`-kirjasto mahdollistaa sovelluksesi kommunikoimisen MQTT:n kautta.

1. Lisää seuraava koodi valosensorin ja LED-valon määrittelyjen jälkeen:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    Korvaa `<ID>` ainutlaatuisella tunnisteella, jota käytetään tämän laitteen asiakasohjelman nimenä ja myöhemmin aiheissa, joita tämä laite julkaisee ja tilaa. *test.mosquitto.org*-välityspalvelin on julkinen ja sitä käyttää moni, mukaan lukien muut opiskelijat, jotka työskentelevät tämän tehtävän parissa. Ainutlaatuinen MQTT-asiakasohjelman nimi ja aiheiden nimet varmistavat, ettei koodisi aiheuta ristiriitoja muiden kanssa. Tarvitset myös tämän tunnisteen, kun luot palvelinkoodin myöhemmin tässä tehtävässä.

    > 💁 Voit käyttää verkkosivustoa kuten [GUIDGen](https://www.guidgen.com) luodaksesi ainutlaatuisen tunnisteen.

    `client_name` on ainutlaatuinen nimi tälle MQTT-asiakasohjelmalle välityspalvelimessa.

1. Lisää seuraava koodi tämän uuden koodin alle luodaksesi MQTT-asiakasohjelmaobjektin ja yhdistääksesi MQTT-välityspalvelimeen:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    Tämä koodi luo asiakasobjektin, yhdistää julkiseen MQTT-välityspalvelimeen ja käynnistää käsittelysilmukan, joka pyörii taustasäikeessä kuunnellen viestejä kaikista tilatuista aiheista.

1. Suorita koodi samalla tavalla kuin suoritat koodin edellisessä tehtävän osassa. Jos käytät virtuaalista IoT-laitetta, varmista, että CounterFit-sovellus on käynnissä ja valosensori sekä LED-valo on luotu oikeille pinneille.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 Löydät tämän koodin [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device)-kansiosta tai [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi)-kansiosta.

😀 Olet onnistuneesti yhdistänyt laitteesi MQTT-välityspalvelimeen.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.