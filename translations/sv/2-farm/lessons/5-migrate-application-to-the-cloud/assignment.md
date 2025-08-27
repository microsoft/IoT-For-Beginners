<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T22:34:22+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "sv"
}
-->
# Lägg till manuell reläkontroll

## Instruktioner

Serverlös kod kan triggas av många olika saker, inklusive HTTP-förfrågningar. Du kan använda HTTP-triggers för att lägga till en manuell överstyrning av din reläkontroll, vilket gör det möjligt för någon att slå på eller av reläet via en webbförfrågan.

För denna uppgift behöver du lägga till två HTTP-triggers till din Functions App för att slå på och av reläet, och återanvända det du har lärt dig från denna lektion för att skicka kommandon till enheten.

Några tips:

* Du kan lägga till en HTTP-trigger till din befintliga Functions App med följande kommando:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    Ersätt `<trigger name>` med namnet på din HTTP-trigger. Använd något som `relay_on` och `relay_off`.

* HTTP-triggers kan ha åtkomstkontroll. Som standard kräver de en funktionsspecifik API-nyckel som skickas med URL:en för att köras. För denna uppgift kan du ta bort denna begränsning så att vem som helst kan köra funktionen. För att göra detta, uppdatera inställningen `authLevel` i filen `function.json` för HTTP-triggers till följande:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 Du kan läsa mer om denna åtkomstkontroll i [dokumentationen för funktionsåtkomstnycklar](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* HTTP-triggers stöder som standard GET- och POST-förfrågningar. Detta innebär att du kan kalla dem via din webbläsare - webbläsare gör GET-förfrågningar.

    När du kör din Functions App lokalt kommer du att se URL:en för triggern:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    Klistra in URL:en i din webbläsare och tryck på `return`, eller `Ctrl+click` (`Cmd+click` på macOS) på länken i terminalfönstret i VS Code för att öppna den i din standardwebbläsare. Detta kommer att köra triggern.

    > 💁 Observera att URL:en har `/api` i sig - HTTP-triggers är som standard i subdomänen `api`.

* När du distribuerar Functions App kommer HTTP-triggerns URL att vara:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    Där `<functions app name>` är namnet på din Functions App, och `<trigger name>` är namnet på din trigger.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Skapa HTTP-triggers | Skapade 2 triggers för att slå på och av reläet, med lämpliga namn | Skapade en trigger med ett lämpligt namn | Kunde inte skapa några triggers |
| Kontrollera reläet från HTTP-triggers | Kunde koppla båda triggers till IoT Hub och kontrollera reläet korrekt | Kunde koppla en trigger till IoT Hub och kontrollera reläet korrekt | Kunde inte koppla triggers till IoT Hub |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.