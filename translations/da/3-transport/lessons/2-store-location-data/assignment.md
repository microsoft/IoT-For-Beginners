<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T21:40:11+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "da"
}
-->
# Undersøg funktion bindings

## Instruktioner

Funktion bindings giver din kode mulighed for at gemme blobs i blob-lageret ved at returnere dem fra `main`-funktionen. Azure Storage-kontoen, samlingen og andre detaljer er konfigureret i `function.json`-filen.

Når du arbejder med Azure eller andre Microsoft-teknologier, er den bedste kilde til information [Microsoft-dokumentationen på docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). I denne opgave skal du læse dokumentationen om Azure Functions bindings for at finde ud af, hvordan du opsætter output-bindingen.

Nogle sider, du kan starte med, er:

* [Azure Functions triggers og bindings koncepter](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [Azure Blob storage bindings for Azure Functions oversigt](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [Azure Blob storage output binding for Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## Vurderingskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Konfigurer blob-lagerets output-binding | Kunne konfigurere output-bindingen, returnere blobben og få den gemt i blob-lageret med succes | Kunne konfigurere output-bindingen eller returnere blobben, men kunne ikke få den gemt i blob-lageret med succes | Kunne ikke konfigurere output-bindingen |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.