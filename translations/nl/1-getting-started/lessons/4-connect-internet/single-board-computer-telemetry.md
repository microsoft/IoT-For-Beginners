<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T21:40:58+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "nl"
}
-->
# Bedien je nachtlampje via het internet - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les stuur je telemetrie met lichtniveaus van je Raspberry Pi of virtuele IoT-apparaat naar een MQTT-broker.

## Telemetrie publiceren

De volgende stap is om een JSON-document met telemetrie te maken en dit naar de MQTT-broker te sturen.

### Taak

Publiceer telemetrie naar de MQTT-broker.

1. Open het nachtlampproject in VS Code.

1. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de terminal de virtuele omgeving uitvoert. Als je een Raspberry Pi gebruikt, werk je niet met een virtuele omgeving.

1. Voeg de volgende import toe aan de bovenkant van het bestand `app.py`:

    ```python
    import json
    ```

    De bibliotheek `json` wordt gebruikt om de telemetrie te coderen als een JSON-document.

1. Voeg het volgende toe na de declaratie van `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    De `client_telemetry_topic` is het MQTT-topic waar het apparaat lichtniveaus naar zal publiceren.

1. Vervang de inhoud van de `while True:`-lus aan het einde van het bestand door het volgende:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Deze code verpakt het lichtniveau in een JSON-document en publiceert het naar de MQTT-broker. Vervolgens wordt er een pauze ingelast om de frequentie van de verzonden berichten te verminderen.

1. Voer de code uit op dezelfde manier als je de code uit het vorige deel van de opdracht hebt uitgevoerd. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de CounterFit-app actief is en dat de lichtsensor en LED op de juiste pinnen zijn aangemaakt.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Je kunt deze code vinden in de map [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) of de map [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Je hebt met succes telemetrie vanaf je apparaat verzonden.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.