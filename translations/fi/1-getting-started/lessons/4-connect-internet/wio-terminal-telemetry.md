<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:45:28+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "fi"
}
-->
# Hallitse yövaloa Internetin kautta - Wio Terminal

Tässä osassa oppituntia lähetät telemetriatietoja valotasoista Wio Terminal -laitteestasi MQTT-välityspalvelimelle.

## Asenna JSON Arduino -kirjastot

Yksi suosittu tapa lähettää viestejä MQTT:n kautta on käyttää JSON-muotoa. Arduino tarjoaa JSON-kirjaston, joka helpottaa JSON-dokumenttien lukemista ja kirjoittamista.

### Tehtävä

Asenna Arduino JSON -kirjasto.

1. Avaa yövaloprojekti VS Codessa.

1. Lisää seuraava rivi `lib_deps`-listaan `platformio.ini`-tiedostossa:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Tämä tuo käyttöön [ArduinoJson](https://arduinojson.org)-kirjaston, joka on Arduino JSON -kirjasto.

## Telemetrian julkaiseminen

Seuraava vaihe on luoda JSON-dokumentti telemetriatiedoista ja lähettää se MQTT-välityspalvelimelle.

### Tehtävä - telemetrian julkaiseminen

Julkaise telemetria MQTT-välityspalvelimelle.

1. Lisää seuraava koodi `config.h`-tiedoston loppuun määrittääksesi telemetria-aiheen nimen MQTT-välityspalvelimelle:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` on aihe, johon laite julkaisee valotasotiedot.

1. Avaa `main.cpp`-tiedosto.

1. Lisää seuraava `#include`-direktiivi tiedoston alkuun:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Lisää seuraava koodi `loop`-funktion sisään, juuri ennen `delay`-komentoa:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Tämä koodi lukee valotason ja luo JSON-dokumentin, joka sisältää tämän tason käyttäen ArduinoJson-kirjastoa. JSON-dokumentti sarjoitetaan merkkijonoksi ja julkaistaan telemetria-MQTT-aiheeseen MQTT-asiakkaan avulla.

1. Lataa koodi Wio Terminal -laitteeseesi ja käytä sarjamonitoria nähdäksesi, kuinka valotasot lähetetään MQTT-välityspalvelimelle.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Löydät tämän koodin [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) -kansiosta.

😀 Olet onnistuneesti lähettänyt telemetriatietoja laitteestasi.

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.