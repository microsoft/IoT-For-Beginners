<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T21:52:34+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "no"
}
-->
# Styr nattlampen din over Internett - Virtuell IoT-maskinvare og Raspberry Pi

I denne delen av leksjonen vil du abonnere på kommandoer sendt fra en MQTT-broker til din Raspberry Pi eller virtuelle IoT-enhet.

## Abonner på kommandoer

Neste steg er å abonnere på kommandoene som sendes fra MQTT-brokeren og reagere på dem.

### Oppgave

Abonner på kommandoer.

1. Åpne nattlampe-prosjektet i VS Code.

1. Hvis du bruker en virtuell IoT-enhet, sørg for at terminalen kjører det virtuelle miljøet. Hvis du bruker en Raspberry Pi, trenger du ikke bruke et virtuelt miljø.

1. Legg til følgende kode etter definisjonene av `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic` er MQTT-emnet som enheten vil abonnere på for å motta LED-kommandoer.

1. Legg til følgende kode rett over hovedløkken, etter linjen `mqtt_client.loop_start()`:

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

    Denne koden definerer en funksjon, `handle_command`, som leser en melding som et JSON-dokument og ser etter verdien av `led_on`-egenskapen. Hvis den er satt til `True`, slås LED-en på, ellers slås den av.

    MQTT-klienten abonnerer på emnet som serveren vil sende meldinger på og setter `handle_command`-funksjonen til å bli kalt når en melding mottas.

    > 💁 `on_message`-handleren kalles for alle emner det abonneres på. Hvis du senere skriver kode som lytter til flere emner, kan du hente emnet meldingen ble sendt til fra `message`-objektet som sendes til handler-funksjonen.

1. Kjør koden på samme måte som du kjørte koden fra forrige del av oppgaven. Hvis du bruker en virtuell IoT-enhet, sørg for at CounterFit-appen kjører og at lyssensoren og LED-en er opprettet på de riktige pinnene.

1. Juster lysnivåene som oppdages av din fysiske eller virtuelle enhet. Meldinger som mottas og kommandoer som sendes, vil bli skrevet til terminalen. LED-en vil også slås av og på avhengig av lysnivået.

> 💁 Du finner denne koden i mappen [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) eller [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 Du har nå kodet enheten din til å reagere på kommandoer fra en MQTT-broker.

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.