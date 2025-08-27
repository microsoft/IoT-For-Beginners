<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T21:04:05+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "nl"
}
-->
# Publiceer temperatuur - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les ga je de temperatuurwaarden die door de Raspberry Pi of het Virtuele IoT-apparaat worden gedetecteerd, publiceren via MQTT, zodat ze later kunnen worden gebruikt om de GDD te berekenen.

## Publiceer de temperatuur

Zodra de temperatuur is uitgelezen, kan deze via MQTT worden gepubliceerd naar een 'server'-code die de waarden leest en opslaat, zodat ze klaar zijn voor een GDD-berekening.

### Taak - publiceer de temperatuur

Programmeur het apparaat om de temperatuurgegevens te publiceren.

1. Open het project van de app `temperature-sensor` als het nog niet geopend is.

1. Herhaal de stappen die je in les 4 hebt uitgevoerd om verbinding te maken met MQTT en telemetrie te verzenden. Je gebruikt dezelfde openbare Mosquitto-broker.

    De stappen hiervoor zijn:

    - Voeg het MQTT pip-pakket toe
    - Voeg de code toe om verbinding te maken met de MQTT-broker
    - Voeg de code toe om telemetrie te publiceren

    > ⚠️ Raadpleeg de [instructies voor verbinding maken met MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) en de [instructies voor het verzenden van telemetrie](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) uit les 4 indien nodig.

1. Zorg ervoor dat de `client_name` de naam van dit project weerspiegelt:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. Voor de telemetrie, in plaats van een lichtwaarde te verzenden, stuur je de temperatuurwaarde die is uitgelezen van de DHT-sensor in een eigenschap in het JSON-document genaamd `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. De temperatuurwaarde hoeft niet vaak te worden uitgelezen - deze verandert niet veel in korte tijd, dus stel de `time.sleep` in op 10 minuten:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 De functie `sleep` neemt de tijd in seconden, dus om het makkelijker leesbaar te maken wordt de waarde doorgegeven als het resultaat van een berekening. 60 seconden in een minuut, dus 10 x (60 seconden in een minuut) geeft een vertraging van 10 minuten.

1. Voer de code uit op dezelfde manier als je de code uit het vorige deel van de opdracht hebt uitgevoerd. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de CounterFit-app actief is en dat de vochtigheids- en temperatuursensoren op de juiste pinnen zijn aangemaakt.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 Je kunt deze code vinden in de map [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) of de map [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 Je hebt de temperatuur met succes gepubliceerd als telemetrie vanaf je apparaat.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.