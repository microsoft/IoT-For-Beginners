<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:23:12+00:00",
  "source_file": "clean-up.md",
  "language_code": "nl"
}
-->
# Ruim je project op

Nadat je elk project hebt afgerond, is het verstandig om je cloudresources te verwijderen.

Tijdens de lessen voor elk project heb je mogelijk enkele van de volgende resources aangemaakt:

* Een Resource Group
* Een IoT Hub
* IoT-apparaatregistraties
* Een Storage Account
* Een Functions App
* Een Azure Maps-account
* Een custom vision-project
* Een Azure Container Registry
* Een cognitive services-resource

De meeste van deze resources brengen geen kosten met zich mee - ze zijn volledig gratis of je gebruikt een gratis niveau. Voor services die een betaald niveau vereisen, heb je ze waarschijnlijk gebruikt op een niveau dat binnen de gratis limiet valt, of ze kosten slechts een paar cent.

Zelfs met de relatief lage kosten is het de moeite waard om deze resources te verwijderen wanneer je klaar bent. Je kunt bijvoorbeeld maar één IoT Hub gebruiken op het gratis niveau, dus als je een nieuwe wilt maken, moet je een betaald niveau gebruiken.

Al je services zijn aangemaakt binnen Resource Groups, wat het beheer eenvoudiger maakt. Je kunt de Resource Group verwijderen, en alle services in die Resource Group worden daarmee ook verwijderd.

Om de Resource Group te verwijderen, voer je de volgende opdracht uit in je terminal of command prompt:

```sh
az group delete --name <resource-group-name>
```

Vervang `<resource-group-name>` door de naam van de Resource Group waarin je geïnteresseerd bent.

Er verschijnt een bevestiging:

```output
Are you sure you want to perform this operation? (y/n): 
```

Voer `y` in om te bevestigen en de Resource Group te verwijderen.

Het kan even duren voordat alle services zijn verwijderd.

> 💁 Je kunt meer lezen over het verwijderen van resource groups in de [Azure Resource Manager documentatie over het verwijderen van resource groups en resources op Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.