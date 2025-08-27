<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:45:42+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "sv"
}
-->
# Svara på klassificeringsresultat

## Instruktioner

Din enhet har klassificerat bilder och har värden för förutsägelserna. Din enhet kan använda denna information för att göra något - den kan skicka den till IoT Hub för bearbetning av andra system, eller den kan styra en aktor, till exempel en LED, som tänds när frukten är omogen.

Lägg till kod i din enhet för att svara på ett sätt som du väljer - antingen skicka data till en IoT Hub, kontrollera en aktor, eller kombinera de två och skicka data till en IoT Hub med serverlös kod som avgör om frukten är mogen eller inte och skickar tillbaka ett kommando för att styra en aktor.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Svara på förutsägelser | Kunde implementera ett svar på förutsägelser som fungerar konsekvent med förutsägelser av samma värde. | Kunde implementera ett svar som inte är beroende av förutsägelserna, till exempel bara skicka rådata till en IoT Hub. | Kunde inte programmera enheten att svara på förutsägelserna. |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.