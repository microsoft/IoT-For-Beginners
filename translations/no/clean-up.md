<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:22:25+00:00",
  "source_file": "clean-up.md",
  "language_code": "no"
}
-->
# Rydd opp i prosjektet ditt

Etter at du har fullført hvert prosjekt, er det lurt å slette skyressursene dine.

I leksjonene for hvert prosjekt kan det hende du har opprettet noen av følgende:

* En ressursgruppe  
* En IoT Hub  
* IoT-enhetsregistreringer  
* En lagringskonto  
* En Functions App  
* En Azure Maps-konto  
* Et Custom Vision-prosjekt  
* Et Azure Container Registry  
* En kognitiv tjeneste-ressurs  

De fleste av disse ressursene vil ikke ha noen kostnad – enten er de helt gratis, eller du bruker en gratis nivå. For tjenester som krever et betalt nivå, har du brukt dem på et nivå som er inkludert i gratis kvoten, eller som bare koster noen få øre.

Selv med de relativt lave kostnadene, er det verdt å slette disse ressursene når du er ferdig. Du kan for eksempel bare ha én IoT Hub som bruker gratisnivået, så hvis du vil opprette en ny, må du bruke et betalt nivå.

Alle tjenestene dine ble opprettet inne i ressursgrupper, og dette gjør det enklere å administrere. Du kan slette ressursgruppen, og alle tjenestene i den ressursgruppen vil bli slettet sammen med den.

For å slette ressursgruppen, kjør følgende kommando i terminalen eller kommandolinjen:

```sh
az group delete --name <resource-group-name>
```

Erstatt `<resource-group-name>` med navnet på ressursgruppen du er interessert i.

En bekreftelse vil vises:

```output
Are you sure you want to perform this operation? (y/n): 
```

Skriv inn `y` for å bekrefte og slette ressursgruppen.

Det vil ta litt tid å slette alle tjenestene.

> 💁 Du kan lese mer om sletting av ressursgrupper i [dokumentasjonen for sletting av ressursgrupper og ressurser i Azure Resource Manager på Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.