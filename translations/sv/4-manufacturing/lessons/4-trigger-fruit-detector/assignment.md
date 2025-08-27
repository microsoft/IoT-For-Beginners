<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T20:32:35+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "sv"
}
-->
# Bygg en detektor för fruktkvalitet

## Instruktioner

Bygg en detektor för fruktkvalitet!

Använd allt du har lärt dig hittills för att bygga en prototyp av en detektor för fruktkvalitet. Aktivera bildklassificering baserat på närhet med hjälp av en AI-modell som körs på kanten, lagra resultaten av klassificeringen i lagring, och styr en LED baserat på fruktens mognadsgrad.

Du bör kunna sätta ihop detta med kod du tidigare har skrivit i alla lektioner hittills.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Konfigurera alla tjänster | Kunde konfigurera en IoT Hub, Azure Functions-applikation och Azure-lagring | Kunde konfigurera IoT Hub, men inte Azure Functions-applikationen eller Azure-lagring | Kunde inte konfigurera några IoT-tjänster |
| Övervaka närhet och skicka data till IoT Hub om ett objekt är närmare än ett fördefinierat avstånd och aktivera kameran via ett kommando | Kunde mäta avstånd och skicka ett meddelande till IoT Hub när ett objekt var tillräckligt nära, och skicka ett kommando för att aktivera kameran | Kunde mäta närhet och skicka till IoT Hub, men kunde inte skicka ett kommando till kameran | Kunde inte mäta avstånd och skicka ett meddelande till IoT Hub eller aktivera ett kommando |
| Ta en bild, klassificera den och skicka resultaten till IoT Hub | Kunde ta en bild, klassificera den med en edge-enhet och skicka resultaten till IoT Hub | Kunde klassificera bilden men inte med en edge-enhet, eller kunde inte skicka resultaten till IoT Hub | Kunde inte klassificera en bild |
| Slå på eller av LED beroende på resultaten av klassificeringen med ett kommando som skickas till en enhet | Kunde slå på en LED via ett kommando om frukten var omogen | Kunde skicka kommandot till enheten men inte styra LED | Kunde inte skicka ett kommando för att styra LED |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.