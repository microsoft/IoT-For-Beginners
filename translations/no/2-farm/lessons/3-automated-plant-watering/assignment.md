<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T22:59:09+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "no"
}
-->
# Bygg en mer effektiv vanningssyklus

## Instruksjoner

Denne leksjonen dekket hvordan man kan kontrollere et relé via sensordata, og det reléet kan i sin tur kontrollere en pumpe for et vanningssystem. For en definert mengde jord, vil det å kjøre en pumpe i en fast tidsperiode alltid ha samme effekt på jordfuktigheten. Dette betyr at du kan få en idé om hvor mange sekunder med vanning som tilsvarer en viss reduksjon i jordfuktighetsmålingen. Ved å bruke disse dataene kan du bygge et mer kontrollert vanningssystem.

I denne oppgaven skal du beregne hvor lenge pumpen skal kjøre for en spesifikk økning i jordfuktighet.

> ⚠️ Hvis du bruker virtuell IoT-maskinvare, kan du gå gjennom denne prosessen, men simulere resultatene ved manuelt å øke jordfuktighetsmålingen med en fast mengde per sekund reléet er på.

1. Start med tørr jord. Mål jordfuktigheten.

1. Tilsett en fast mengde vann, enten ved å kjøre pumpen i 1 sekund eller ved å helle en fast mengde vann.

    > Pumpen skal alltid kjøre med en konstant hastighet, så hvert sekund pumpen kjører skal den levere samme mengde vann.

1. Vent til jordfuktighetsnivået stabiliserer seg og ta en måling.

1. Gjenta dette flere ganger og lag en tabell med resultatene. Et eksempel på en slik tabell er gitt nedenfor.

    | Total pumpetid | Jordfuktighet | Reduksjon |
    | --- | --: | -: |
    | Tørr | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Beregn en gjennomsnittlig økning i jordfuktighet per sekund med vann. I eksempelet ovenfor reduserer hvert sekund med vann målingen med et gjennomsnitt på 20,3.

1. Bruk disse dataene til å forbedre effektiviteten til serverkoden din, og kjør pumpen i den nødvendige tiden for å få jordfuktigheten til ønsket nivå.

## Vurderingskriterier

| Kriterier | Eksemplarisk | Tilfredsstillende | Trenger forbedring |
| --------- | ------------ | ----------------- | ------------------ |
| Registrere jordfuktighetsdata | Klarer å registrere flere målinger etter å ha tilsatt faste mengder vann | Klarer å registrere noen målinger med faste mengder vann | Klarer kun å registrere én eller to målinger, eller klarer ikke å bruke faste mengder vann |
| Kalibrere serverkoden | Klarer å beregne en gjennomsnittlig reduksjon i jordfuktighetsmåling og oppdatere serverkoden for å bruke dette | Klarer å beregne en gjennomsnittlig reduksjon, men kan ikke oppdatere serverkoden, eller klarer ikke å beregne et korrekt gjennomsnitt, men bruker denne verdien til å oppdatere serverkoden korrekt | Klarer ikke å beregne et gjennomsnitt, eller oppdatere serverkoden |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.