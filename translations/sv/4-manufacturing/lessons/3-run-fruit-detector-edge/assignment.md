<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:38:36+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "sv"
}
-->
# Kör andra tjänster på kanten

## Instruktioner

Det är inte bara bildklassificerare som kan köras på kanten, allt som kan paketeras i en container kan distribueras till en IoT Edge-enhet. Serverlös kod som körs som Azure Functions, såsom de triggers du skapat i tidigare lektioner, kan köras i containrar och därmed på IoT Edge.

Välj en av de tidigare lektionerna och försök att köra Azure Functions-appen i en IoT Edge-container. Du kan hitta en guide som visar hur du gör detta med ett annat Functions-app-projekt i [Tutorial: Deploy Azure Functions as IoT Edge modules on Microsoft docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------- |
| Distribuera en Azure Functions-app till IoT Edge | Kunde distribuera en Azure Functions-app till IoT Edge och använda den med en IoT-enhet för att köra en trigger från IoT-data | Kunde distribuera en Functions-app till IoT Edge, men kunde inte få triggern att aktiveras | Kunde inte distribuera en Functions-app till IoT Edge |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.