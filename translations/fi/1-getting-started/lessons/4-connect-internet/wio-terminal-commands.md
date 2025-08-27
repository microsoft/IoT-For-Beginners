<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T21:48:16+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "fi"
}
-->
# Ohjaa yövaloa Internetin kautta - Wio Terminal

Tässä osassa oppituntia tilaat komentoja, jotka lähetetään MQTT-välittäjältä Wio Terminal -laitteellesi.

## Tilaa komennot

Seuraava vaihe on tilata MQTT-välittäjän lähettämät komennot ja vastata niihin.

### Tehtävä

Tilaa komennot.

1. Avaa yövaloprojekti VS Code -ohjelmassa.

1. Lisää seuraava koodi `config.h`-tiedoston loppuun määrittääksesi komentojen aiheen nimen:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` on aihe, johon laite tilaa saadakseen LED-komennot.

1. Lisää seuraava rivi `reconnectMQTTClient`-funktion loppuun, jotta komentoaihe tilataan, kun MQTT-asiakas yhdistetään uudelleen:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. Lisää seuraava koodi `reconnectMQTTClient`-funktion alapuolelle.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    Tämä funktio toimii palautteena, jonka MQTT-asiakas kutsuu, kun se vastaanottaa viestin palvelimelta.

    Viesti vastaanotetaan 8-bittisten kokonaislukujen taulukkona, joten se täytyy muuntaa merkkitaulukoksi, jotta sitä voidaan käsitellä tekstinä.

    Viesti sisältää JSON-dokumentin, joka dekoodataan ArduinoJson-kirjaston avulla. JSON-dokumentin `led_on`-ominaisuus luetaan, ja sen arvon perusteella LED sytytetään tai sammutetaan.

1. Lisää seuraava koodi `createMQTTClient`-funktioon:

    ```cpp
    client.setCallback(clientCallback);
    ```

    Tämä koodi asettaa `clientCallback`-funktion palautteeksi, joka kutsutaan, kun MQTT-välittäjältä vastaanotetaan viesti.

    > 💁 `clientCallback`-käsittelijä kutsutaan kaikille tilatuille aiheille. Jos myöhemmin kirjoitat koodia, joka kuuntelee useita aiheita, voit saada aiheen, johon viesti lähetettiin, `topic`-parametrista, joka välitetään palautefunktiolle.

1. Lataa koodi Wio Terminal -laitteellesi ja käytä sarjamonitoria nähdäksesi valotasot, jotka lähetetään MQTT-välittäjälle.

1. Säädä fyysisen tai virtuaalisen laitteen havaitsemia valotasoja. Näet viestien vastaanottamisen ja komentojen lähettämisen terminaalissa. Näet myös LEDin syttyvän ja sammuvan valotason mukaan.

> 💁 Löydät tämän koodin [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal) -kansiosta.

😀 Olet onnistuneesti ohjelmoinut laitteesi vastaamaan MQTT-välittäjän komentoihin.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.