<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:24:19+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "no"
}
-->
# Produksjon og bearbeiding - bruke IoT for å forbedre bearbeiding av mat

Når mat når et sentralt knutepunkt eller et bearbeidingsanlegg, blir det ikke alltid bare sendt videre til supermarkeder. Ofte går maten gjennom en rekke bearbeidingssteg, som for eksempel sortering etter kvalitet. Dette var tidligere en manuell prosess – det startet på åkeren der plukkere kun tok modne frukter, og deretter på fabrikken ble frukten transportert på et samlebånd hvor ansatte manuelt fjernet skadet eller råtten frukt. Etter å ha plukket og sortert jordbær selv som sommerjobb under skolegangen, kan jeg bekrefte at dette ikke er en morsom jobb.

Mer moderne oppsett bruker IoT for sortering. Noen av de tidligste enhetene, som sorteringsmaskinene fra [Weco](https://wecotek.com), bruker optiske sensorer for å oppdage kvaliteten på produktene, og avviser for eksempel grønne tomater. Disse kan brukes både i høstemaskiner på gården og i bearbeidingsanlegg.

Etter hvert som det skjer fremskritt innen kunstig intelligens (AI) og maskinlæring (ML), kan disse maskinene bli mer avanserte, ved å bruke ML-modeller som er trent til å skille mellom frukt og fremmedlegemer som steiner, jord eller insekter. Disse modellene kan også trenes til å oppdage fruktkvalitet, ikke bare skadet frukt, men også tidlig oppdagelse av sykdom eller andre avlingsproblemer.

> 🎓 Begrepet *ML-modell* refererer til resultatet av å trene maskinlæringsprogramvare på et datasett. For eksempel kan du trene en ML-modell til å skille mellom modne og umodne tomater, og deretter bruke modellen på nye bilder for å se om tomatene er modne eller ikke.

I disse 4 leksjonene vil du lære hvordan du trener bildebaserte AI-modeller for å oppdage fruktkvalitet, hvordan du bruker disse fra en IoT-enhet, og hvordan du kjører dem på kanten – det vil si på en IoT-enhet i stedet for i skyen.

> 💁 Disse leksjonene vil bruke noen skyeressurser. Hvis du ikke fullfører alle leksjonene i dette prosjektet, sørg for å [rydde opp i prosjektet ditt](../clean-up.md).

## Emner

1. [Tren en fruktkvalitetsdetektor](./lessons/1-train-fruit-detector/README.md)
1. [Sjekk fruktkvalitet fra en IoT-enhet](./lessons/2-check-fruit-from-device/README.md)
1. [Kjør fruktdetektoren din på kanten](./lessons/3-run-fruit-detector-edge/README.md)
1. [Utøs fruktkvalitetsdeteksjon fra en sensor](./lessons/4-trigger-fruit-detector/README.md)

## Kreditering

Alle leksjonene er skrevet med ♥️ av [Jen Fox](https://github.com/jenfoxbot) og [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.