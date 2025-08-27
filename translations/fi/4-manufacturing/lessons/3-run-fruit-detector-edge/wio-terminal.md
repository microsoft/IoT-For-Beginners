<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:52:00+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "fi"
}
-->
# Luokittele kuva IoT Edge -pohjaisella kuvantunnistimella - Wio Terminal

Tässä osassa oppituntia käytät IoT Edge -laitteella toimivaa kuvantunnistinta.

## Käytä IoT Edge -luokittelijaa

IoT-laite voidaan ohjata käyttämään IoT Edge -kuvantunnistinta. Kuvantunnistimen URL-osoite on `http://<IP-osoite tai nimi>/image`, jossa `<IP-osoite tai nimi>` korvataan IoT Edge -laitetta isännöivän tietokoneen IP-osoitteella tai isäntänimellä.

### Tehtävä - käytä IoT Edge -luokittelijaa

1. Avaa `fruit-quality-detector`-sovellusprojekti, jos se ei ole jo avoinna.

1. Kuvantunnistin toimii REST API:n kautta HTTP-protokollalla, ei HTTPS:llä, joten kutsu täytyy tehdä WiFi-asiakkaalla, joka tukee vain HTTP-kutsuja. Tämä tarkoittaa, että sertifikaattia ei tarvita. Poista `CERTIFICATE` tiedostosta `config.h`.

1. Päivitä `config.h`-tiedostossa oleva ennusteen URL-osoite uuteen URL-osoitteeseen. Voit myös poistaa `PREDICTION_KEY`, koska sitä ei tarvita.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Korvaa `<URL>` luokittelijasi URL-osoitteella.

1. Muuta `main.cpp`-tiedostossa WiFi Client Secure -sisällytysdirektiivi tuomaan standardi HTTP-versio:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Muuta `WiFiClient`-määrittely HTTP-versioksi:

    ```cpp
    WiFiClient client;
    ```

1. Etsi rivi, joka asettaa sertifikaatin WiFi-asiakkaalle. Poista rivi `client.setCACert(CERTIFICATE);` `connectWiFi`-funktiosta.

1. Poista `classifyImage`-funktiossa rivi `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, joka asettaa ennusteen avaimen otsikkoon.

1. Lataa ja suorita koodisi. Suuntaa kamera hedelmään ja paina C-painiketta. Näet tuloksen sarjamonitorissa:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Löydät tämän koodin [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) -kansiosta.

😀 Hedelmän laadun luokittelijaohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäinen asiakirja sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.