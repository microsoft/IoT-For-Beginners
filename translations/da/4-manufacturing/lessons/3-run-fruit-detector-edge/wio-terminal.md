<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:39:40+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "da"
}
-->
# Klassificér et billede ved hjælp af en IoT Edge-baseret billedklassificering - Wio Terminal

I denne del af lektionen vil du bruge billedklassificeringen, der kører på IoT Edge-enheden.

## Brug IoT Edge-klassificeringen

IoT-enheden kan omdirigeres til at bruge IoT Edge-billedklassificeringen. URL'en til billedklassificeringen er `http://<IP-adresse eller navn>/image`, hvor `<IP-adresse eller navn>` erstattes med IP-adressen eller værtsnavnet på computeren, der kører IoT Edge.

### Opgave - brug IoT Edge-klassificeringen

1. Åbn `fruit-quality-detector`-app-projektet, hvis det ikke allerede er åbent.

1. Billedklassificeringen kører som en REST API ved hjælp af HTTP, ikke HTTPS, så kaldet skal bruge en WiFi-klient, der kun fungerer med HTTP-kald. Dette betyder, at certifikatet ikke er nødvendigt. Slet `CERTIFICATE` fra `config.h`-filen.

1. Forudsigelses-URL'en i `config.h`-filen skal opdateres til den nye URL. Du kan også slette `PREDICTION_KEY`, da denne ikke er nødvendig.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Erstat `<URL>` med URL'en til din klassificering.

1. I `main.cpp` skal du ændre include-direktivet for WiFi Client Secure til at importere standard HTTP-versionen:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Ændr deklarationen af `WiFiClient` til at være HTTP-versionen:

    ```cpp
    WiFiClient client;
    ```

1. Find linjen, der sætter certifikatet på WiFi-klienten. Fjern linjen `client.setCACert(CERTIFICATE);` fra `connectWiFi`-funktionen.

1. I `classifyImage`-funktionen skal du fjerne linjen `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);`, der sætter forudsigelsesnøglen i headeren.

1. Upload og kør din kode. Peg kameraet mod noget frugt, og tryk på C-knappen. Du vil se outputtet i den serielle monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Du kan finde denne kode i [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal)-mappen.

😀 Dit program til klassificering af frugtkvalitet var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.