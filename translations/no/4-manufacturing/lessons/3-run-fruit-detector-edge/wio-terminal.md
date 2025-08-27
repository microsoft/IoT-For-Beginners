<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:39:54+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "no"
}
-->
# Klassifiser et bilde ved hjelp av en IoT Edge-basert bildekategoriserer - Wio Terminal

I denne delen av leksjonen skal du bruke bildekategorisereren som kjører på IoT Edge-enheten.

## Bruk IoT Edge-kategorisereren

IoT-enheten kan omdirigeres til å bruke IoT Edge-bildekategorisereren. URL-en for bildekategorisereren er `http://<IP-adresse eller navn>/image`, der `<IP-adresse eller navn>` erstattes med IP-adressen eller vertsnavnet til datamaskinen som kjører IoT Edge.

### Oppgave - bruk IoT Edge-kategorisereren

1. Åpne prosjektet for appen `fruit-quality-detector` hvis det ikke allerede er åpent.

1. Bildekategorisereren kjører som en REST API ved bruk av HTTP, ikke HTTPS, så kallene må bruke en WiFi-klient som kun fungerer med HTTP-kall. Dette betyr at sertifikatet ikke er nødvendig. Slett `CERTIFICATE` fra filen `config.h`.

1. Prediksjons-URL-en i filen `config.h` må oppdateres til den nye URL-en. Du kan også slette `PREDICTION_KEY`, da denne ikke er nødvendig.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Erstatt `<URL>` med URL-en til din kategoriserer.

1. I `main.cpp`, endre include-direktivet for WiFi Client Secure til å importere standard HTTP-versjonen:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Endre deklarasjonen av `WiFiClient` til å være HTTP-versjonen:

    ```cpp
    WiFiClient client;
    ```

1. Finn linjen som setter sertifikatet på WiFi-klienten. Fjern linjen `client.setCACert(CERTIFICATE);` fra funksjonen `connectWiFi`.

1. I funksjonen `classifyImage`, fjern linjen `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` som setter prediksjonsnøkkelen i headeren.

1. Last opp og kjør koden din. Rett kameraet mot en frukt og trykk på C-knappen. Du vil se resultatet i den serielle monitoren:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Du finner denne koden i mappen [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Programmet ditt for klassifisering av fruktkvalitet var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.