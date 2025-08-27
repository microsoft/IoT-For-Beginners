<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T22:34:34+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "da"
}
-->
# Tilføj manuel relækontrol

## Instruktioner

Serverløs kode kan udløses af mange forskellige ting, herunder HTTP-forespørgsler. Du kan bruge HTTP-udløsere til at tilføje en manuel overstyring til din relækontrol, så nogen kan tænde eller slukke for relæet via en webforespørgsel.

Til denne opgave skal du tilføje to HTTP-udløsere til din Functions App for at tænde og slukke for relæet, og genbruge det, du har lært i denne lektion, til at sende kommandoer til enheden.

Nogle tips:

* Du kan tilføje en HTTP-udløser til din eksisterende Functions App med følgende kommando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Erstat `<trigger name>` med navnet på din HTTP-udløser. Brug noget som `relay_on` og `relay_off`.

* HTTP-udløsere kan have adgangskontrol. Som standard kræver de en funktionsspecifik API-nøgle, der skal sendes med URL'en for at køre. Til denne opgave kan du fjerne denne begrænsning, så alle kan køre funktionen. For at gøre dette skal du opdatere `authLevel`-indstillingen i `function.json`-filen for HTTP-udløserne til følgende:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Du kan læse mere om denne adgangskontrol i [Function access keys-dokumentationen](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP-udløsere understøtter som standard GET- og POST-forespørgsler. Det betyder, at du kan kalde dem ved hjælp af din webbrowser - webbrowsere laver GET-forespørgsler.

    Når du kører din Functions App lokalt, vil du se URL'en til udløseren:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Indsæt URL'en i din browser og tryk på `return`, eller `Ctrl+klik` (`Cmd+klik` på macOS) på linket i terminalvinduet i VS Code for at åbne det i din standardbrowser. Dette vil køre udløseren.

    > 💁 Bemærk, at URL'en har `/api` i sig - HTTP-udløsere er som standard i `api`-underdomænet.

* Når du implementerer Functions App, vil HTTP-udløserens URL være:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Hvor `<functions app name>` er navnet på din Functions App, og `<trigger name>` er navnet på din udløser.

## Bedømmelseskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver Forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Opret HTTP-udløsere | Oprettede 2 udløsere til at tænde og slukke for relæet med passende navne | Oprettede én udløser med et passende navn | Kunne ikke oprette nogen udløsere |
| Kontroller relæet fra HTTP-udløsere | Kunne forbinde begge udløsere til IoT Hub og kontrollere relæet korrekt | Kunne forbinde én udløser til IoT Hub og kontrollere relæet korrekt | Kunne ikke forbinde udløserne til IoT Hub |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.