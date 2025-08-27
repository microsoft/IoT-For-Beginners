<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-27T22:39:08+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "sv"
}
-->
# Bygg en ny IoT-enhet

## Instruktioner

Under de senaste 6 lektionerna har du lärt dig om digital jordbruk och hur man använder IoT-enheter för att samla in data för att förutsäga växttillväxt och automatisera bevattning baserat på avläsningar av jordfuktighet.

Använd det du har lärt dig för att bygga en ny IoT-enhet med en sensor och en aktuator som du väljer. Skicka telemetri till en IoT Hub och använd den för att styra en aktuator via serverlös kod. Du kan använda en sensor och en aktuator som du redan har använt i detta eller det föregående projektet, eller om du har annan hårdvara, prova något nytt.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Koda en IoT-enhet för att använda en sensor och aktuator | Kodade en IoT-enhet som fungerar med både en sensor och en aktuator | Kodade en IoT-enhet som fungerar med antingen en sensor eller en aktuator | Kunde inte koda en IoT-enhet för att använda en sensor eller en aktuator |
| Anslut IoT-enheten till IoT Hub | Kunde distribuera en IoT Hub och skicka telemetri till den, samt ta emot kommandon från den | Kunde distribuera en IoT Hub och antingen skicka telemetri eller ta emot kommandon | Kunde inte distribuera en IoT Hub eller kommunicera med den från en IoT-enhet |
| Styr aktuatorn med serverlös kod | Kunde distribuera en Azure Function för att styra enheten som triggas av telemetrihändelser | Kunde distribuera en Azure Function som triggas av telemetrihändelser men kunde inte styra aktuatorn | Kunde inte distribuera en Azure Function |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.