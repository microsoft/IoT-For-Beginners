<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T21:40:29+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "nl"
}
-->
# Bedien je nachtlampje via het internet - Virtuele IoT-hardware en Raspberry Pi

In dit deel van de les leer je hoe je commando's kunt ontvangen die via een MQTT-broker naar je Raspberry Pi of virtuele IoT-apparaat worden gestuurd.

## Abonneren op commando's

De volgende stap is om je te abonneren op de commando's die door de MQTT-broker worden verzonden en hierop te reageren.

### Taak

Abonneer je op commando's.

1. Open het nachtlampjesproject in VS Code.

1. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de terminal de virtuele omgeving uitvoert. Als je een Raspberry Pi gebruikt, werk je niet met een virtuele omgeving.

1. Voeg de volgende code toe na de definities van de `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    De `server_command_topic` is het MQTT-topic waarop het apparaat zich abonneert om LED-commando's te ontvangen.

1. Voeg de volgende code toe net boven de hoofdloop, na de regel `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    Deze code definieert een functie, `handle_command`, die een bericht leest als een JSON-document en zoekt naar de waarde van de eigenschap `led_on`. Als deze is ingesteld op `True`, wordt de LED ingeschakeld; anders wordt deze uitgeschakeld.

    De MQTT-client abonneert zich op het topic waarop de server berichten zal sturen en stelt de functie `handle_command` in om te worden aangeroepen wanneer een bericht wordt ontvangen.

    > 💁 De `on_message` handler wordt aangeroepen voor alle topics waarop je bent geabonneerd. Als je later code schrijft die naar meerdere topics luistert, kun je het topic waarnaar het bericht is verzonden ophalen uit het `message` object dat aan de handlerfunctie wordt doorgegeven.

1. Voer de code uit op dezelfde manier als je de code uit het vorige deel van de opdracht hebt uitgevoerd. Als je een virtueel IoT-apparaat gebruikt, zorg er dan voor dat de CounterFit-app actief is en dat de lichtsensor en LED op de juiste pinnen zijn aangemaakt.

1. Pas de lichtniveaus aan die door je fysieke of virtuele apparaat worden gedetecteerd. Berichten die worden ontvangen en commando's die worden verzonden, worden in de terminal geschreven. De LED wordt ook in- en uitgeschakeld afhankelijk van het lichtniveau.

> 💁 Je kunt deze code vinden in de map [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) of de map [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Je hebt je apparaat succesvol geprogrammeerd om te reageren op commando's van een MQTT-broker.

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.