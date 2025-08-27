<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:39:29+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "sv"
}
-->
# Klassificera en bild med en IoT Edge-baserad bildklassificerare - Wio Terminal

I den här delen av lektionen kommer du att använda bildklassificeraren som körs på IoT Edge-enheten.

## Använd IoT Edge-klassificeraren

IoT-enheten kan omdirigeras för att använda IoT Edge-bildklassificeraren. URL:en för bildklassificeraren är `http://<IP address or name>/image`, där `<IP address or name>` ersätts med IP-adressen eller värdnamnet för datorn som kör IoT Edge.

### Uppgift - använd IoT Edge-klassificeraren

1. Öppna projektet `fruit-quality-detector` om det inte redan är öppet.

1. Bildklassificeraren körs som ett REST API med HTTP, inte HTTPS, så anropet måste använda en WiFi-klient som endast fungerar med HTTP-anrop. Detta innebär att certifikatet inte behövs. Ta bort `CERTIFICATE` från filen `config.h`.

1. URL:en för prediktionen i filen `config.h` måste uppdateras till den nya URL:en. Du kan också ta bort `PREDICTION_KEY` eftersom den inte behövs.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Ersätt `<URL>` med URL:en för din klassificerare.

1. I `main.cpp`, ändra include-direktivet för WiFi Client Secure till att importera standardversionen för HTTP:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Ändra deklarationen av `WiFiClient` till att vara HTTP-versionen:

    ```cpp
    WiFiClient client;
    ```

1. Leta upp raden som sätter certifikatet på WiFi-klienten. Ta bort raden `client.setCACert(CERTIFICATE);` från funktionen `connectWiFi`.

1. I funktionen `classifyImage`, ta bort raden `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` som sätter prediktionsnyckeln i headern.

1. Ladda upp och kör din kod. Rikta kameran mot någon frukt och tryck på C-knappen. Du kommer att se resultatet i seriemonitorn:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Du hittar denna kod i mappen [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal).

😀 Ditt program för att klassificera fruktkvalitet blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.