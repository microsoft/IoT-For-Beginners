<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:23:58+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "sv"
}
-->
# Tillverkning och bearbetning - använda IoT för att förbättra bearbetningen av mat

När mat når en central hub eller bearbetningsanläggning skickas den inte alltid direkt till stormarknader. Ofta går maten igenom flera bearbetningssteg, som att sorteras efter kvalitet. Detta var tidigare en manuell process - det började på fältet där plockare endast plockade mogen frukt, och sedan på fabriken åkte frukten på ett transportband där anställda manuellt tog bort skadad eller rutten frukt. Efter att själv ha plockat och sorterat jordgubbar som sommarjobb under skoltiden kan jag intyga att detta inte är ett roligt jobb.

Mer moderna lösningar använder IoT för sortering. Några av de tidigaste enheterna, som sorteringsmaskinerna från [Weco](https://wecotek.com), använder optiska sensorer för att upptäcka kvaliteten på produkterna, till exempel för att sortera bort gröna tomater. Dessa kan användas både i skördemaskiner på själva gården och i bearbetningsanläggningar.

Med framsteg inom artificiell intelligens (AI) och maskininlärning (ML) kan dessa maskiner bli mer avancerade, med ML-modeller som tränats för att skilja mellan frukt och främmande föremål som stenar, jord eller insekter. Dessa modeller kan också tränas för att upptäcka fruktens kvalitet, inte bara skadad frukt utan även tidig upptäckt av sjukdomar eller andra problem med grödan.

> 🎓 Termen *ML-modell* hänvisar till resultatet av att träna mjukvara för maskininlärning på en uppsättning data. Till exempel kan du träna en ML-modell att skilja mellan mogna och omogna tomater och sedan använda modellen på nya bilder för att avgöra om tomaterna är mogna eller inte.

I dessa fyra lektioner kommer du att lära dig hur man tränar bildbaserade AI-modeller för att upptäcka fruktens kvalitet, hur man använder dessa från en IoT-enhet och hur man kör dem på kanten - det vill säga på en IoT-enhet istället för i molnet.

> 💁 Dessa lektioner kommer att använda vissa molnresurser. Om du inte slutför alla lektioner i detta projekt, se till att du [städar upp ditt projekt](../clean-up.md).

## Ämnen

1. [Träna en kvalitetsdetektor för frukt](./lessons/1-train-fruit-detector/README.md)
1. [Kontrollera fruktens kvalitet från en IoT-enhet](./lessons/2-check-fruit-from-device/README.md)
1. [Kör din fruktdetektor på kanten](./lessons/3-run-fruit-detector-edge/README.md)
1. [Starta kvalitetsdetektering av frukt från en sensor](./lessons/4-trigger-fruit-detector/README.md)

## Krediter

Alla lektioner är skrivna med ♥️ av [Jen Fox](https://github.com/jenfoxbot) och [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.