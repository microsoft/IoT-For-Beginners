<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T21:06:10+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "nl"
}
-->
# Publiceer temperatuur - Wio Terminal

In dit deel van de les ga je de temperatuurwaarden die door de Wio Terminal worden gedetecteerd publiceren via MQTT, zodat ze later kunnen worden gebruikt om GDD te berekenen.

## Publiceer de temperatuur

Zodra de temperatuur is gemeten, kan deze via MQTT worden gepubliceerd naar een 'server'-code die de waarden leest en opslaat, klaar om te worden gebruikt voor een GDD-berekening. Microcontrollers lezen standaard geen tijd van het internet en houden de tijd niet bij met een real-time klok. Het apparaat moet hiervoor worden geprogrammeerd, ervan uitgaande dat het over de benodigde hardware beschikt.

Om het eenvoudiger te maken voor deze les, wordt de tijd niet samen met de sensorgegevens verzonden. In plaats daarvan kan de tijd later door de servercode worden toegevoegd wanneer deze de berichten ontvangt.

### Taak

Programmeer het apparaat om de temperatuurgegevens te publiceren.

1. Open het `temperature-sensor` Wio Terminal-project.

1. Herhaal de stappen die je in les 4 hebt uitgevoerd om verbinding te maken met MQTT en telemetrie te verzenden. Je zult dezelfde openbare Mosquitto-broker gebruiken.

    De stappen hiervoor zijn:

    - Voeg de Seeed WiFi- en MQTT-bibliotheken toe aan het `.ini`-bestand.
    - Voeg het configuratiebestand en de code toe om verbinding te maken met WiFi.
    - Voeg de code toe om verbinding te maken met de MQTT-broker.
    - Voeg de code toe om telemetrie te publiceren.

    > ⚠️ Raadpleeg de [instructies voor verbinding maken met MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) en de [instructies voor het verzenden van telemetrie](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) uit les 4 indien nodig.

1. Zorg ervoor dat de `CLIENT_NAME` in het `config.h`-headerbestand dit project weerspiegelt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. Voor de telemetrie, in plaats van een lichtwaarde te verzenden, stuur je de temperatuurwaarde die is gemeten door de DHT-sensor in een eigenschap in het JSON-document genaamd `temperature` door de `loop`-functie in `main.cpp` te wijzigen:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. De temperatuurwaarde hoeft niet vaak te worden gemeten - deze verandert niet veel in korte tijd. Stel daarom de `delay` in de `loop`-functie in op 10 minuten:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 De `delay`-functie neemt de tijd in milliseconden, dus om het gemakkelijker te maken wordt de waarde doorgegeven als het resultaat van een berekening. 1.000ms in een seconde, 60s in een minuut, dus 10 x (60s in een minuut) x (1000ms in een seconde) geeft een vertraging van 10 minuten.

1. Upload dit naar je Wio Terminal en gebruik de seriële monitor om te zien hoe de temperatuur naar de MQTT-broker wordt verzonden.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 Je kunt deze code vinden in de [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) map.

😀 Je hebt de temperatuur succesvol gepubliceerd als telemetrie vanaf je apparaat.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.