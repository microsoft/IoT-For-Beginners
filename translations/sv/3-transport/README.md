<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-27T21:18:07+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "sv"
}
-->
# Transport från gård till fabrik - använda IoT för att spåra matleveranser

Många bönder odlar mat för att sälja - antingen är de kommersiella bönder som säljer allt de odlar, eller så är de självhushållande bönder som säljer sitt överskott för att köpa nödvändigheter. På något sätt måste maten transporteras från gården till konsumenten, och detta sker vanligtvis genom bulktransport från gårdar, till nav eller bearbetningsanläggningar, och sedan till butiker. Till exempel kommer en tomatodlare att skörda tomater, packa dem i lådor, lasta lådorna på en lastbil och sedan leverera dem till en bearbetningsanläggning. Tomaterna sorteras därefter och levereras till konsumenterna i form av bearbetad mat, detaljhandel eller serveras på restauranger.

IoT kan hjälpa till med denna leveranskedja genom att spåra maten under transport - säkerställa att chaufförerna kör dit de ska, övervaka fordonens positioner och få aviseringar när fordonen anländer så att maten kan lossas och vara redo för bearbetning så snart som möjligt.

> 🎓 En *leveranskedja* är sekvensen av aktiviteter för att skapa och leverera något. Till exempel, inom tomatodling omfattar det frön, jord, gödningsmedel och vattenförsörjning, odling av tomater, leverans av tomater till ett centralt nav, transport till en stormarknads lokala nav, transport till den enskilda stormarknaden, placering på hyllan, försäljning till en konsument och hemtransport för att ätas. Varje steg är som länkar i en kedja.

> 🎓 Transportdelen av leveranskedjan kallas *logistik*.

I dessa fyra lektioner kommer du att lära dig hur man tillämpar Internet of Things för att förbättra leveranskedjan genom att övervaka mat när den lastas på en (virtuell) lastbil, som spåras när den rör sig mot sin destination. Du kommer att lära dig om GPS-spårning, hur man lagrar och visualiserar GPS-data, och hur man får aviseringar när en lastbil anländer till sin destination.

> 💁 Dessa lektioner kommer att använda vissa molnresurser. Om du inte slutför alla lektioner i detta projekt, se till att du [Rensar upp ditt projekt](../clean-up.md).

## Ämnen

1. [Plats-spårning](lessons/1-location-tracking/README.md)
1. [Lagra platsdata](lessons/2-store-location-data/README.md)
1. [Visualisera platsdata](lessons/3-visualize-location-data/README.md)
1. [Geofences](lessons/4-geofences/README.md)

## Krediter

Alla lektioner skrevs med ♥️ av [Jen Looper](https://github.com/jlooper) och [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.