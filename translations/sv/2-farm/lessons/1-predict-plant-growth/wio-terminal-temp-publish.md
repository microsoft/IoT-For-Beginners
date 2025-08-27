<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-27T22:49:37+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "sv"
}
-->
# Publicera temperatur - Wio Terminal

I den här delen av lektionen kommer du att publicera temperaturvärden som detekterats av Wio Terminal via MQTT, så att de senare kan användas för att beräkna GDD.

## Publicera temperaturen

När temperaturen har lästs av kan den publiceras via MQTT till någon "server"-kod som kommer att läsa värdena och lagra dem för att användas i en GDD-beräkning. Mikrokontrollers läser inte tiden från Internet och håller inte koll på tiden med en realtidsklocka som standard. Enheten måste programmeras för att göra detta, förutsatt att den har nödvändig hårdvara.

För att förenkla saker i den här lektionen kommer tiden inte att skickas med sensordatan. Istället kan den läggas till av serverkoden senare när den tar emot meddelandena.

### Uppgift

Programmera enheten att publicera temperaturdata.

1. Öppna Wio Terminal-projektet `temperature-sensor`.

1. Upprepa stegen du gjorde i lektion 4 för att ansluta till MQTT och skicka telemetri. Du kommer att använda samma publika Mosquitto-broker.

    Stegen för detta är:

    - Lägg till Seeed WiFi- och MQTT-biblioteken i `.ini`-filen
    - Lägg till konfigurationsfilen och koden för att ansluta till WiFi
    - Lägg till koden för att ansluta till MQTT-brokern
    - Lägg till koden för att publicera telemetri

    > ⚠️ Se [instruktionerna för att ansluta till MQTT](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) och [instruktionerna för att skicka telemetri](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md) från lektion 4 om det behövs.

1. Se till att `CLIENT_NAME` i headerfilen `config.h` återspeglar detta projekt:

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. För telemetrin, istället för att skicka ett ljusvärde, skicka temperaturvärdet som lästs av från DHT-sensorn i en egenskap i JSON-dokumentet kallad `temperature` genom att ändra `loop`-funktionen i `main.cpp`:

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. Temperaturvärdet behöver inte läsas av särskilt ofta – det kommer inte att ändras mycket på kort tid, så ställ in `delay` i `loop`-funktionen till 10 minuter:

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 Funktionen `delay` tar tiden i millisekunder, så för att göra det enklare att läsa skickas värdet som resultatet av en beräkning. 1 000 ms på en sekund, 60 sekunder på en minut, så 10 x (60 sekunder på en minut) x (1 000 ms på en sekund) ger en fördröjning på 10 minuter.

1. Ladda upp detta till din Wio Terminal och använd seriemonitorn för att se temperaturen skickas till MQTT-brokern.

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

> 💁 Du kan hitta denna kod i mappen [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal).

😀 Du har framgångsrikt publicerat temperaturen som telemetri från din enhet.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.