<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T22:23:38+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "nl"
}
-->
# Timer annuleren

## Instructies

Tot nu toe heb je in deze les een model getraind om een timer in te stellen. Een andere handige functie is het annuleren van een timer - misschien is je brood al klaar en kan het uit de oven worden gehaald voordat de timer afloopt.

Voeg een nieuwe intent toe aan je LUIS-app om de timer te annuleren. Deze intent heeft geen entiteiten nodig, maar wel enkele voorbeeldzinnen. Verwerk dit in je serverless code als het de belangrijkste intent is, log dat de intent herkend is en geef een passende reactie terug.

## Rubric

| Criteria | Uitmuntend | Voldoende | Verbetering nodig |
| -------- | ---------- | --------- | ----------------- |
| Voeg de intent voor het annuleren van de timer toe aan de LUIS-app | Kon de intent toevoegen en het model trainen | Kon de intent toevoegen maar niet het model trainen | Kon de intent niet toevoegen en het model niet trainen |
| Verwerk de intent in de serverless app | Kon de intent als belangrijkste intent detecteren en loggen | Kon de intent als belangrijkste intent detecteren | Kon de intent niet als belangrijkste intent detecteren |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.