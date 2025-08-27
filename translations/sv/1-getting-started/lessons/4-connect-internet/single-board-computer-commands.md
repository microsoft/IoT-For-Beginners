<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T21:52:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "sv"
}
-->
# Styr din nattlampa över Internet - Virtuell IoT-hårdvara och Raspberry Pi

I den här delen av lektionen kommer du att prenumerera på kommandon som skickas från en MQTT-broker till din Raspberry Pi eller virtuella IoT-enhet.

## Prenumerera på kommandon

Nästa steg är att prenumerera på de kommandon som skickas från MQTT-brokern och svara på dem.

### Uppgift

Prenumerera på kommandon.

1. Öppna nattlampa-projektet i VS Code.

1. Om du använder en virtuell IoT-enhet, se till att terminalen kör den virtuella miljön. Om du använder en Raspberry Pi behöver du inte använda en virtuell miljö.

1. Lägg till följande kod efter definitionerna av `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` är MQTT-ämnet som enheten kommer att prenumerera på för att ta emot LED-kommandon.

1. Lägg till följande kod precis ovanför huvudloopen, efter raden `mqtt_client.loop_start()`:

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

    Den här koden definierar en funktion, `handle_command`, som läser ett meddelande som ett JSON-dokument och letar efter värdet på egenskapen `led_on`. Om den är inställd på `True` tänds LED-lampan, annars släcks den.

    MQTT-klienten prenumererar på ämnet som servern kommer att skicka meddelanden på och ställer in funktionen `handle_command` att anropas när ett meddelande tas emot.

    > 💁 Händelsehanteraren `on_message` anropas för alla ämnen som det prenumereras på. Om du senare skriver kod som lyssnar på flera ämnen kan du få ämnet som meddelandet skickades till från `message`-objektet som skickas till hanterarfunktionen.

1. Kör koden på samma sätt som du körde koden från den föregående delen av uppgiften. Om du använder en virtuell IoT-enhet, se till att CounterFit-appen körs och att ljussensorn och LED-lampan har skapats på rätt pinnar.

1. Justera ljusnivåerna som detekteras av din fysiska eller virtuella enhet. Meddelanden som tas emot och kommandon som skickas kommer att skrivas ut i terminalen. LED-lampan kommer också att tändas och släckas beroende på ljusnivån.

> 💁 Du kan hitta den här koden i mappen [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) eller mappen [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Du har framgångsrikt programmerat din enhet att svara på kommandon från en MQTT-broker.

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, vänligen notera att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.