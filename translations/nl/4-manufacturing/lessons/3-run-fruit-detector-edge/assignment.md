<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:50:52+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "nl"
}
-->
# Andere services op de edge uitvoeren

## Instructies

Het zijn niet alleen beeldclassificatiemodellen die op de edge kunnen worden uitgevoerd; alles wat in een container kan worden verpakt, kan worden ingezet op een IoT Edge-apparaat. Serverloze code die als Azure Functions draait, zoals de triggers die je in eerdere lessen hebt gemaakt, kan in containers worden uitgevoerd en dus op IoT Edge.

Kies een van de eerdere lessen en probeer de Azure Functions-app in een IoT Edge-container te draaien. Je kunt een handleiding vinden die laat zien hoe je dit doet met een ander Functions-app-project in de [Tutorial: Azure Functions implementeren als IoT Edge-modules op Microsoft Docs](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## Beoordelingscriteria

| Criteria | Uitzonderlijk | Voldoende | Verbetering Nodig |
| -------- | ------------- | --------- | ----------------- |
| Een Azure Functions-app implementeren op IoT Edge | Heeft een Azure Functions-app succesvol geïmplementeerd op IoT Edge en gebruikt met een IoT-apparaat om een trigger te activeren vanuit IoT-gegevens | Heeft een Functions-app succesvol geïmplementeerd op IoT Edge, maar kon de trigger niet activeren | Was niet in staat om een Functions-app te implementeren op IoT Edge |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.