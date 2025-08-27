<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T22:50:45+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "sv"
}
-->
# Publicera temperatur - Virtuell IoT-hårdvara och Raspberry Pi

I denna del av lektionen kommer du att publicera temperaturvärden som upptäcks av Raspberry Pi eller Virtuell IoT-enhet via MQTT så att de senare kan användas för att beräkna GDD.

## Publicera temperaturen

När temperaturen har lästs kan den publiceras via MQTT till någon "server"-kod som kommer att läsa värdena och lagra dem redo att användas för en GDD-beräkning.

### Uppgift - publicera temperaturen

Programmera enheten att publicera temperaturdata.

1. Öppna projektet för appen `temperature-sensor` om det inte redan är öppet.

1. Upprepa stegen du gjorde i lektion 4 för att ansluta till MQTT och skicka telemetri. Du kommer att använda samma offentliga Mosquitto-broker.

    Stegen för detta är:

    - Lägg till MQTT pip-paketet
    - Lägg till koden för att ansluta till MQTT-brokern
    - Lägg till koden för att publicera telemetri

    > ⚠️ Se [instruktionerna för att ansluta till MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) och [instruktionerna för att skicka telemetri](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) från lektion 4 om det behövs.

1. Se till att `client_name` återspeglar namnet på detta projekt:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. För telemetrin, istället för att skicka ett ljusvärde, skicka temperaturvärdet som lästs från DHT-sensorn i en egenskap i JSON-dokumentet kallad `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. Temperaturvärdet behöver inte läsas särskilt ofta - det kommer inte att ändras mycket på kort tid, så ställ in `time.sleep` till 10 minuter:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 Funktionen `sleep` tar tiden i sekunder, så för att göra det lättare att läsa skickas värdet som resultatet av en beräkning. 60 sekunder på en minut, så 10 x (60 sekunder på en minut) ger en fördröjning på 10 minuter.

1. Kör koden på samma sätt som du körde koden från den tidigare delen av uppgiften. Om du använder en virtuell IoT-enhet, se till att CounterFit-appen körs och att fukt- och temperatursensorerna har skapats på rätt pinnar.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Du kan hitta denna kod i mappen [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) eller mappen [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Du har framgångsrikt publicerat temperaturen som telemetri från din enhet.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.