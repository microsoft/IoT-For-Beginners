<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "48ac21ec80329c930db7b84bd6b592ec",
  "translation_date": "2025-08-27T20:52:10+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/wio-terminal.md",
  "language_code": "nl"
}
-->
# Classificeer een afbeelding met een IoT Edge-gebaseerde afbeeldingsclassifier - Wio Terminal

In dit deel van de les ga je de Image Classifier gebruiken die draait op het IoT Edge-apparaat.

## Gebruik de IoT Edge classifier

Het IoT-apparaat kan worden omgeleid om de IoT Edge afbeeldingsclassifier te gebruiken. De URL voor de Image Classifier is `http://<IP adres of naam>/image`, waarbij `<IP adres of naam>` wordt vervangen door het IP-adres of de hostnaam van de computer waarop IoT Edge draait.

### Taak - gebruik de IoT Edge classifier

1. Open het `fruit-quality-detector` app-project als het nog niet geopend is.

1. De afbeeldingsclassifier draait als een REST API via HTTP, niet HTTPS, dus de oproep moet een WiFi-client gebruiken die alleen met HTTP-oproepen werkt. Dit betekent dat het certificaat niet nodig is. Verwijder het `CERTIFICATE` uit het `config.h` bestand.

1. De voorspellings-URL in het `config.h` bestand moet worden bijgewerkt naar de nieuwe URL. Je kunt ook de `PREDICTION_KEY` verwijderen, aangezien deze niet nodig is.

    ```cpp
    const char *PREDICTION_URL = "<URL>";
    ```

    Vervang `<URL>` door de URL van je classifier.

1. In `main.cpp`, wijzig de include-richtlijn voor de WiFi Client Secure om de standaard HTTP-versie te importeren:

    ```cpp
    #include <WiFiClient.h>
    ```

1. Wijzig de declaratie van `WiFiClient` naar de HTTP-versie:

    ```cpp
    WiFiClient client;
    ```

1. Selecteer de regel die het certificaat instelt op de WiFi-client. Verwijder de regel `client.setCACert(CERTIFICATE);` uit de `connectWiFi` functie.

1. Verwijder in de `classifyImage` functie de regel `httpClient.addHeader("Prediction-Key", PREDICTION_KEY);` die de voorspellingssleutel in de header instelt.

1. Upload en voer je code uit. Richt de camera op wat fruit en druk op de C-knop. Je ziet de output in de seriële monitor:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Je kunt deze code vinden in de [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/wio-terminal) map.

😀 Je fruitkwaliteitsclassifierprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor kritieke informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.