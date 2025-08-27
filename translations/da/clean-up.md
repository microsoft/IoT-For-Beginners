<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:22:17+00:00",
  "source_file": "clean-up.md",
  "language_code": "da"
}
-->
# Ryd op i dit projekt

Når du har afsluttet hvert projekt, er det en god idé at slette dine cloudressourcer.

I lektionerne for hvert projekt kan du have oprettet nogle af følgende:

* En Resource Group
* En IoT Hub
* IoT-enhedsregistreringer
* En Storage Account
* En Functions App
* En Azure Maps-konto
* Et custom vision-projekt
* Et Azure Container Registry
* En cognitive services-ressource

De fleste af disse ressourcer vil ikke have nogen omkostninger - enten er de helt gratis, eller du bruger en gratis plan. For tjenester, der kræver en betalt plan, har du sandsynligvis brugt dem på et niveau, der er inkluderet i den gratis kvote, eller som kun koster få øre.

Selv med de relativt lave omkostninger er det værd at slette disse ressourcer, når du er færdig. Du kan for eksempel kun have én IoT Hub, der bruger den gratis plan, så hvis du vil oprette en ny, skal du bruge en betalt plan.

Alle dine tjenester blev oprettet inden for Resource Groups, hvilket gør det nemmere at administrere. Du kan slette Resource Group, og alle tjenester i den Resource Group vil blive slettet sammen med den.

For at slette Resource Group skal du køre følgende kommando i din terminal eller kommandoprompt:

```sh
az group delete --name <resource-group-name>
```

Erstat `<resource-group-name>` med navnet på den Resource Group, du er interesseret i.

En bekræftelse vil dukke op:

```output
Are you sure you want to perform this operation? (y/n): 
```

Indtast `y` for at bekræfte og slette Resource Group.

Det vil tage lidt tid at slette alle tjenesterne.

> 💁 Du kan læse mere om sletning af Resource Groups i [Azure Resource Manager-dokumentationen om sletning af resource groups og ressourcer på Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.