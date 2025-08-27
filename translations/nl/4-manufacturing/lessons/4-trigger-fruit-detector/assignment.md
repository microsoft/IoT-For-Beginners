<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T20:55:56+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "nl"
}
-->
# Bouw een detector voor fruitkwaliteit

## Instructies

Bouw de detector voor fruitkwaliteit!

Gebruik alles wat je tot nu toe hebt geleerd om een prototype van de fruitkwaliteitsdetector te bouwen. Activeer beeldclassificatie op basis van nabijheid met behulp van een AI-model dat lokaal draait, sla de resultaten van de classificatie op in opslag, en bedien een LED op basis van de rijpheid van het fruit.

Je zou dit moeten kunnen samenstellen met code die je eerder hebt geschreven in alle lessen tot nu toe.

## Beoordelingscriteria

| Criteria | Uitmuntend | Voldoende | Verbetering nodig |
| -------- | ---------- | --------- | ----------------- |
| Configureer alle services | Kon een IoT Hub, Azure Functions-applicatie en Azure-opslag instellen | Kon de IoT Hub instellen, maar niet de Azure Functions-app of Azure-opslag | Kon geen enkele internet-IoT-service instellen |
| Monitor nabijheid en stuur de gegevens naar IoT Hub als een object dichterbij is dan een vooraf gedefinieerde afstand en activeer de camera via een opdracht | Kon afstand meten en een bericht naar een IoT Hub sturen wanneer een object dichtbij genoeg was, en een opdracht sturen om de camera te activeren | Kon nabijheid meten en naar IoT Hub sturen, maar kon geen opdracht naar de camera sturen | Kon afstand niet meten en geen bericht naar IoT Hub sturen, of een opdracht activeren |
| Maak een foto, classificeer deze en stuur de resultaten naar IoT Hub | Kon een foto maken, deze classificeren met een edge-apparaat en de resultaten naar IoT Hub sturen | Kon de foto classificeren maar niet met een edge-apparaat, of kon de resultaten niet naar IoT Hub sturen | Kon geen foto classificeren |
| Zet de LED aan of uit afhankelijk van de resultaten van de classificatie via een opdracht die naar een apparaat wordt gestuurd | Kon een LED aanzetten via een opdracht als het fruit onrijp was | Kon de opdracht naar het apparaat sturen maar de LED niet bedienen | Kon geen opdracht sturen om de LED te bedienen |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.