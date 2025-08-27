<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T22:34:47+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "no"
}
-->
# Legg til manuell kontroll av relé

## Instruksjoner

Serverløs kode kan utløses av mange forskjellige ting, inkludert HTTP-forespørsler. Du kan bruke HTTP-utløsere for å legge til en manuell overstyring av relékontrollen, slik at noen kan slå reléet av eller på via en webforespørsel.

For denne oppgaven må du legge til to HTTP-utløsere i din Functions App for å slå reléet av og på, og gjenbruke det du har lært i denne leksjonen for å sende kommandoer til enheten.

Noen tips:

* Du kan legge til en HTTP-utløser i din eksisterende Functions App med følgende kommando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Erstatt `<trigger name>` med navnet på din HTTP-utløser. Bruk noe som `relay_on` og `relay_off`.

* HTTP-utløsere kan ha tilgangskontroll. Som standard krever de en funksjonsspesifikk API-nøkkel som må sendes med URL-en for å kjøre. For denne oppgaven kan du fjerne denne begrensningen slik at hvem som helst kan kjøre funksjonen. For å gjøre dette, oppdater `authLevel`-innstillingen i `function.json`-filen for HTTP-utløserne til følgende:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Du kan lese mer om denne tilgangskontrollen i [Funksjonsnøkler-dokumentasjonen](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP-utløsere støtter som standard GET- og POST-forespørsler. Dette betyr at du kan kalle dem ved hjelp av nettleseren din - nettlesere sender GET-forespørsler.

    Når du kjører din Functions App lokalt, vil du se URL-en til utløseren:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Lim inn URL-en i nettleseren din og trykk `return`, eller `Ctrl+klikk` (`Cmd+klikk` på macOS) på lenken i terminalvinduet i VS Code for å åpne den i din standard nettleser. Dette vil kjøre utløseren.

    > 💁 Legg merke til at URL-en har `/api` i seg - HTTP-utløsere er som standard i `api`-underdomenet.

* Når du distribuerer Functions App, vil HTTP-utløserens URL være:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Hvor `<functions app name>` er navnet på din Functions App, og `<trigger name>` er navnet på din utløser.

## Vurderingskriterier

| Kriterier | Fremragende | Tilfredsstillende | Trenger forbedring |
| --------- | ----------- | ----------------- | ------------------ |
| Opprett HTTP-utløsere | Opprettet 2 utløsere for å slå reléet av og på, med passende navn | Opprettet én utløser med et passende navn | Klarte ikke å opprette noen utløsere |
| Kontrollere reléet fra HTTP-utløsere | Klarte å koble begge utløsere til IoT Hub og kontrollere reléet riktig | Klarte å koble én utløser til IoT Hub og kontrollere reléet riktig | Klarte ikke å koble utløsere til IoT Hub |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.