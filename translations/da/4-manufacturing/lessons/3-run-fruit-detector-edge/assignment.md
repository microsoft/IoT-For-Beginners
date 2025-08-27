<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:38:43+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "da"
}
-->
# Kør andre tjenester på kanten

## Instruktioner

Det er ikke kun billedklassifikatorer, der kan køre på kanten; alt, der kan pakkes i en container, kan implementeres på en IoT Edge-enhed. Serverløs kode, der kører som Azure Functions, såsom de triggere, du har oprettet i tidligere lektioner, kan køre i containere og dermed på IoT Edge.

Vælg en af de tidligere lektioner, og prøv at køre Azure Functions-appen i en IoT Edge-container. Du kan finde en vejledning, der viser, hvordan man gør dette ved hjælp af et andet Functions-app-projekt i [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Bedømmelseskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver Forbedring |
| --------- | ----------- | ------------- | ------------------ |
| Implementer en Azure Functions-app på IoT Edge | Kunne implementere en Azure Functions-app på IoT Edge og bruge den med en IoT-enhed til at køre en trigger fra IoT-data | Kunne implementere en Functions-app på IoT Edge, men kunne ikke få triggeren til at udløse | Kunne ikke implementere en Functions-app på IoT Edge |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.