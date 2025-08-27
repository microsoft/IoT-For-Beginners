<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T20:52:10+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "sv"
}
-->
# Avbryt timern

## Instruktioner

Hittills i denna lektion har du tränat en modell för att förstå hur man ställer in en timer. En annan användbar funktion är att avbryta en timer - kanske är ditt bröd klart och kan tas ut ur ugnen innan timern har gått ut.

Lägg till en ny intent i din LUIS-app för att avbryta timern. Den behöver inga entiteter, men den behöver några exempelmeningar. Hantera detta i din serverlösa kod om det är den främsta intenten, logga att intenten har identifierats och returnera ett lämpligt svar.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Lägg till intenten för att avbryta timern i LUIS-appen | Kunde lägga till intenten och träna modellen | Kunde lägga till intenten men inte träna modellen | Kunde inte lägga till intenten och träna modellen |
| Hantera intenten i den serverlösa appen | Kunde identifiera intenten som den främsta och logga den | Kunde identifiera intenten som den främsta | Kunde inte identifiera intenten som den främsta |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.