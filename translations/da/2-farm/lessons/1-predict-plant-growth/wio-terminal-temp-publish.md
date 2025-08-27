<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T22:49:50+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "da"
}
-->
# Udgiv temperatur - Wio Terminal

I denne del af lektionen vil du udgive de temperaturværdier, som Wio Terminal registrerer, via MQTT, så de senere kan bruges til at beregne GDD.

## Udgiv temperaturen

Når temperaturen er blevet aflæst, kan den udgives via MQTT til noget 'server'-kode, der vil læse værdierne og gemme dem, så de er klar til at blive brugt til en GDD-beregning. Mikrocontrollere aflæser ikke tiden fra internettet og holder ikke styr på tiden med et realtidsur som standard. Enheden skal programmeres til dette, forudsat at den har det nødvendige hardware.

For at gøre tingene enklere i denne lektion vil tiden ikke blive sendt sammen med sensordataene. I stedet kan den tilføjes af serverkoden senere, når den modtager beskederne.

### Opgave

Programmer enheden til at udgive temperaturdata.

1. Åbn `temperature-sensor` Wio Terminal-projektet.

1. Gentag de trin, du udførte i lektion 4 for at oprette forbindelse til MQTT og sende telemetri. Du vil bruge den samme offentlige Mosquitto-broker.

    Trinnene er som følger:

    - Tilføj Seeed WiFi- og MQTT-bibliotekerne til `.ini`-filen
    - Tilføj konfigurationsfilen og koden til at oprette forbindelse til WiFi
    - Tilføj koden til at oprette forbindelse til MQTT-brokeren
    - Tilføj koden til at udgive telemetri

    > ⚠️ Se [instruktionerne for at oprette forbindelse til MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) og [instruktionerne for at sende telemetri](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) fra lektion 4, hvis det er nødvendigt.

1. Sørg for, at `CLIENT_NAME` i `config.h` header-filen afspejler dette projekt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. For telemetrien, i stedet for at sende en lysværdi, skal du sende temperaturværdien, der aflæses fra DHT-sensoren, i en egenskab i JSON-dokumentet kaldet `temperature` ved at ændre `loop`-funktionen i `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Temperaturværdien behøver ikke at blive aflæst særlig ofte - den ændrer sig ikke meget på kort tid, så sæt `delay` i `loop`-funktionen til 10 minutter:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay`-funktionen tager tiden i millisekunder, så for at gøre det lettere at læse bliver værdien givet som resultatet af en beregning. 1.000 ms i et sekund, 60 sekunder i et minut, så 10 x (60 sekunder i et minut) x (1.000 ms i et sekund) giver en forsinkelse på 10 minutter.

1. Upload dette til din Wio Terminal, og brug seriel monitor til at se temperaturen blive sendt til MQTT-brokeren.

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

> 💁 Du kan finde denne kode i [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal)-mappen.

😀 Du har med succes udgivet temperaturen som telemetri fra din enhed.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.