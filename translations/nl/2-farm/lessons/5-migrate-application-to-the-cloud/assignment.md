<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T21:19:58+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "nl"
}
-->
# Voeg handmatige relaisbediening toe

## Instructies

Serverloze code kan door veel verschillende dingen worden geactiveerd, waaronder HTTP-verzoeken. Je kunt HTTP-triggers gebruiken om een handmatige override toe te voegen aan je relaisbediening, zodat iemand het relais aan of uit kan zetten via een webverzoek.

Voor deze opdracht moet je twee HTTP-triggers toevoegen aan je Functions App om het relais aan en uit te zetten, waarbij je hergebruikt wat je hebt geleerd in deze les om commando's naar het apparaat te sturen.

Enkele tips:

* Je kunt een HTTP-trigger toevoegen aan je bestaande Functions App met het volgende commando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Vervang `<trigger name>` door de naam van je HTTP-trigger. Gebruik bijvoorbeeld `relay_on` en `relay_off`.

* HTTP-triggers kunnen toegangscontrole hebben. Standaard vereisen ze dat een functie-specifieke API-sleutel wordt meegegeven met de URL om te kunnen draaien. Voor deze opdracht kun je deze beperking verwijderen zodat iedereen de functie kan uitvoeren. Om dit te doen, update je de `authLevel` instelling in het `function.json` bestand voor de HTTP-triggers naar het volgende:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Je kunt meer lezen over deze toegangscontrole in de [Function access keys documentatie](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP-triggers ondersteunen standaard GET- en POST-verzoeken. Dit betekent dat je ze kunt aanroepen via je webbrowser - webbrowsers maken GET-verzoeken.

    Wanneer je je Functions App lokaal uitvoert, zie je de URL van de trigger:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Plak de URL in je browser en druk op `return`, of `Ctrl+klik` (`Cmd+klik` op macOS) op de link in het terminalvenster in VS Code om deze te openen in je standaardbrowser. Dit zal de trigger uitvoeren.

    > 💁 Merk op dat de URL `/api` bevat - HTTP-triggers bevinden zich standaard in het `api` subdomein.

* Wanneer je de Functions App implementeert, zal de HTTP-trigger URL zijn:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Waar `<functions app name>` de naam van je Functions App is, en `<trigger name>` de naam van je trigger.

## Rubriek

| Criteria | Uitmuntend | Voldoende | Moet Verbeteren |
| -------- | ---------- | --------- | --------------- |
| HTTP-triggers maken | Heeft 2 triggers gemaakt om het relais aan en uit te zetten, met geschikte namen | Heeft één trigger gemaakt met een geschikte naam | Was niet in staat om triggers te maken |
| Het relais bedienen via de HTTP-triggers | Was in staat om beide triggers te verbinden met IoT Hub en het relais correct te bedienen | Was in staat om één trigger te verbinden met IoT Hub en het relais correct te bedienen | Was niet in staat om de triggers te verbinden met IoT Hub |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.