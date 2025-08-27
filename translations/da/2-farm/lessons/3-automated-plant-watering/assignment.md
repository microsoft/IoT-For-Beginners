<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T22:58:56+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "da"
}
-->
# Byg en mere effektiv vandingscyklus

## Instruktioner

Denne lektion dækkede, hvordan man styrer et relæ via sensordata, og det relæ kunne igen styre en pumpe til et vandingssystem. For en defineret mængde jord bør det at køre en pumpe i en fastsat tidsperiode altid have den samme effekt på jordens fugtighed. Det betyder, at du kan få en idé om, hvor mange sekunders vanding der svarer til et bestemt fald i jordfugtighedsmålingen. Ved at bruge disse data kan du bygge et mere kontrolleret vandingssystem.

Til denne opgave skal du beregne, hvor længe pumpen skal køre for at opnå en bestemt stigning i jordens fugtighed.

> ⚠️ Hvis du bruger virtuel IoT-hardware, kan du gennemgå denne proces, men simulere resultaterne ved manuelt at øge jordfugtighedsmålingen med et fast beløb pr. sekund, relæet er tændt.

1. Start med tør jord. Mål jordens fugtighed.

1. Tilsæt en fast mængde vand, enten ved at køre pumpen i 1 sekund eller ved at hælde en fast mængde i.

    > Pumpen skal altid køre med en konstant hastighed, så hvert sekund pumpen kører, skal den levere den samme mængde vand.

1. Vent, indtil jordfugtighedsniveauet stabiliserer sig, og tag en måling.

1. Gentag dette flere gange og opret en tabel med resultaterne. Et eksempel på denne tabel er givet nedenfor.

    | Total pumpetid | Jordfugtighed | Fald |
    | --- | --: | -: |
    | Tør | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Beregn en gennemsnitlig stigning i jordfugtighed pr. sekund vand. I eksemplet ovenfor falder målingen med et gennemsnit på 20,3 pr. sekund.

1. Brug disse data til at forbedre effektiviteten af din serverkode, så pumpen kører i den nødvendige tid for at bringe jordfugtigheden til det ønskede niveau.

## Bedømmelseskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Indsamling af jordfugtighedsdata | Er i stand til at indsamle flere målinger efter at have tilføjet faste mængder vand | Er i stand til at indsamle nogle målinger med faste mængder vand | Kan kun indsamle en eller to målinger eller er ude af stand til at bruge faste mængder vand |
| Kalibrering af serverkode | Er i stand til at beregne et gennemsnitligt fald i jordfugtighedsmålingen og opdatere serverkoden til at bruge dette | Er i stand til at beregne et gennemsnitligt fald, men kan ikke opdatere serverkoden, eller er ude af stand til korrekt at beregne et gennemsnit, men bruger denne værdi til korrekt at opdatere serverkoden | Er ude af stand til at beregne et gennemsnit eller opdatere serverkoden |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.