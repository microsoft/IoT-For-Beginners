<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T21:40:03+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "sv"
}
-->
# Undersök funktionsbindningar

## Instruktioner

Funktionsbindningar gör det möjligt för din kod att spara blobbar till bloblagring genom att returnera dem från `main`-funktionen. Azure Storage-kontot, samlingen och andra detaljer konfigureras i filen `function.json`.

När du arbetar med Azure eller andra Microsoft-teknologier är den bästa informationskällan [Microsoft-dokumentationen på docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). I den här uppgiften behöver du läsa dokumentationen om Azure Functions-bindningar för att ta reda på hur du ställer in utdata-bindningen.

Några sidor att börja med är:

* [Azure Functions triggers och bindningskoncept](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Översikt över Azure Blob-lagringsbindningar för Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob-lagringsutdata-bindning för Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------- |
| Konfigurera utdata-bindningen för bloblagring | Kunde konfigurera utdata-bindningen, returnera blobben och få den lagrad i bloblagring framgångsrikt | Kunde konfigurera utdata-bindningen eller returnera blobben men kunde inte få den lagrad i bloblagring framgångsrikt | Kunde inte konfigurera utdata-bindningen |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.