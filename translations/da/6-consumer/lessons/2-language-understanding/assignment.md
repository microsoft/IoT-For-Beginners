# Annuller timeren

## Instruktioner

Indtil videre i denne lektion har du trænet en model til at forstå, hvordan man sætter en timer. En anden nyttig funktion er at annullere en timer - måske er dit brød færdigt og kan tages ud af ovnen, før timeren udløber.

Tilføj en ny intent til din LUIS-app for at annullere timeren. Den behøver ikke nogen entiteter, men vil kræve nogle eksempelsætninger. Håndter dette i din serverløse kode, hvis det er den øverste intent, log at intenten blev genkendt, og returner et passende svar.

## Bedømmelseskriterier

| Kriterier | Eksemplarisk | Tilstrækkelig | Kræver forbedring |
| --------- | ------------ | ------------- | ----------------- |
| Tilføj intenten til at annullere timeren i LUIS-appen | Kunne tilføje intenten og træne modellen | Kunne tilføje intenten, men ikke træne modellen | Kunne ikke tilføje intenten og træne modellen |
| Håndter intenten i den serverløse app | Kunne registrere intenten som den øverste intent og logge den | Kunne registrere intenten som den øverste intent | Kunne ikke registrere intenten som den øverste intent |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.