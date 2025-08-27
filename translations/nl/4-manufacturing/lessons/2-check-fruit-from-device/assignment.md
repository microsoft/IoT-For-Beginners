<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:40:43+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "nl"
}
-->
# Reageren op classificatieresultaten

## Instructies

Je apparaat heeft afbeeldingen geclassificeerd en beschikt over de waarden voor de voorspellingen. Je apparaat kan deze informatie gebruiken om iets te doen - het kan deze naar IoT Hub sturen voor verwerking door andere systemen, of het kan een actuator zoals een LED aansturen om te gaan branden wanneer het fruit onrijp is.

Voeg code toe aan je apparaat om op een manier naar keuze te reageren - stuur gegevens naar een IoT Hub, stuur een actuator aan, of combineer beide en stuur gegevens naar een IoT Hub met serverloze code die bepaalt of het fruit rijp is of niet en een opdracht terugstuurt om een actuator aan te sturen.

## Rubric

| Criteria | Uitmuntend | Voldoende | Verbetering nodig |
| -------- | ---------- | --------- | ----------------- |
| Reageren op voorspellingen | Was in staat om een reactie op voorspellingen te implementeren die consistent werkt met voorspellingen van dezelfde waarde. | Was in staat om een reactie te implementeren die niet afhankelijk is van de voorspellingen, zoals het simpelweg versturen van ruwe gegevens naar een IoT Hub. | Was niet in staat om het apparaat te programmeren om te reageren op de voorspellingen. |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.