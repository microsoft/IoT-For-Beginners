<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T21:40:18+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "fi"
}
-->
# Hallitse yövaloa Internetin kautta - Virtuaalinen IoT-laitteisto ja Raspberry Pi

Tässä oppitunnin osassa tilaat komentoja, jotka lähetetään MQTT-välityspalvelimelta Raspberry Pi -laitteeseesi tai virtuaaliseen IoT-laitteeseesi.

## Tilaa komennot

Seuraava vaihe on tilata MQTT-välityspalvelimelta lähetetyt komennot ja vastata niihin.

### Tehtävä

Tilaa komennot.

1. Avaa yövaloprojekti VS Codessa.

1. Jos käytät virtuaalista IoT-laitetta, varmista, että terminaali käyttää virtuaaliympäristöä. Jos käytät Raspberry Pi -laitetta, et käytä virtuaaliympäristöä.

1. Lisää seuraava koodi `client_telemetry_topic`-määrittelyjen jälkeen:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` on MQTT-aihe, johon laite tilaa vastaanottaakseen LED-komentoja.

1. Lisää seuraava koodi pääsilmukan yläpuolelle, `mqtt_client.loop_start()`-rivin jälkeen:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Tämä koodi määrittelee funktion `handle_command`, joka lukee viestin JSON-dokumenttina ja etsii `led_on`-ominaisuuden arvon. Jos arvo on `True`, LED sytytetään, muuten se sammutetaan.

    MQTT-asiakas tilaa aiheen, johon palvelin lähettää viestejä, ja asettaa `handle_command`-funktion kutsuttavaksi, kun viesti vastaanotetaan.

    > 💁 `on_message`-käsittelijä kutsutaan kaikille tilatuille aiheille. Jos myöhemmin kirjoitat koodia, joka kuuntelee useita aiheita, voit saada aiheen, johon viesti lähetettiin, `message`-objektista, joka välitetään käsittelijäfunktiolle.

1. Suorita koodi samalla tavalla kuin suoritat koodin tehtävän aiemmassa osassa. Jos käytät virtuaalista IoT-laitetta, varmista, että CounterFit-sovellus on käynnissä ja että valosensori ja LED on luotu oikeille pinneille.

1. Säädä fyysisen tai virtuaalisen laitteen havaitsemia valotasoja. Vastaanotetut viestit ja lähetetyt komennot kirjoitetaan terminaaliin. LED syttyy ja sammuu valotason mukaan.

> 💁 Löydät tämän koodin [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device)-kansiosta tai [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi)-kansiosta.

😀 Olet onnistuneesti ohjelmoinut laitteesi vastaamaan MQTT-välityspalvelimen komentoihin.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.