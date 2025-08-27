<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T21:52:23+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "da"
}
-->
# Styr din natlampe over internettet - Virtuel IoT-hardware og Raspberry Pi

I denne del af lektionen vil du abonnere på kommandoer sendt fra en MQTT-broker til din Raspberry Pi eller virtuelle IoT-enhed.

## Abonner på kommandoer

Næste trin er at abonnere på de kommandoer, der sendes fra MQTT-brokeren, og reagere på dem.

### Opgave

Abonner på kommandoer.

1. Åbn natlampeprojektet i VS Code.

1. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at terminalen kører det virtuelle miljø. Hvis du bruger en Raspberry Pi, vil du ikke bruge et virtuelt miljø.

1. Tilføj følgende kode efter definitionerne af `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` er MQTT-emnet, som enheden vil abonnere på for at modtage LED-kommandoer.

1. Tilføj følgende kode lige over hovedløkken, efter linjen `mqtt_client.loop_start()`:

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

    Denne kode definerer en funktion, `handle_command`, der læser en besked som et JSON-dokument og leder efter værdien af egenskaben `led_on`. Hvis den er sat til `True`, tændes LED'en, ellers slukkes den.

    MQTT-klienten abonnerer på det emne, som serveren vil sende beskeder på, og sætter funktionen `handle_command` til at blive kaldt, når en besked modtages.

    > 💁 `on_message`-handleren kaldes for alle emner, der abonneres på. Hvis du senere skriver kode, der lytter til flere emner, kan du få det emne, som beskeden blev sendt til, fra `message`-objektet, der sendes til handlerfunktionen.

1. Kør koden på samme måde som du kørte koden fra den tidligere del af opgaven. Hvis du bruger en virtuel IoT-enhed, skal du sikre dig, at CounterFit-appen kører, og at lyssensoren og LED'en er oprettet på de korrekte pins.

1. Juster lysniveauerne, der registreres af din fysiske eller virtuelle enhed. Beskeder, der modtages, og kommandoer, der sendes, vil blive skrevet til terminalen. LED'en vil også blive tændt og slukket afhængigt af lysniveauet.

> 💁 Du kan finde denne kode i mappen [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) eller mappen [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Du har med succes kodet din enhed til at reagere på kommandoer fra en MQTT-broker.

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.