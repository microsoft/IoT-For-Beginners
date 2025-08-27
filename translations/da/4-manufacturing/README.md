<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:24:08+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "da"
}
-->
# Produktion og forarbejdning - brug af IoT til at forbedre fødevareforarbejdning

Når fødevarer når et centralt knudepunkt eller en forarbejdningsfabrik, bliver de ikke altid bare sendt videre til supermarkeder. Ofte gennemgår fødevarerne en række forarbejdningsprocesser, såsom sortering efter kvalitet. Dette var tidligere en manuel proces - det startede på marken, hvor plukkere kun plukkede modne frugter, og på fabrikken kørte frugten på et transportbånd, hvor medarbejdere manuelt fjernede beskadiget eller rådden frugt. Efter selv at have plukket og sorteret jordbær som sommerjob under skolegangen, kan jeg bekræfte, at det ikke er en sjov opgave.

Mere moderne opsætninger bruger IoT til sortering. Nogle af de tidligste enheder, som sorteringsmaskinerne fra [Weco](https://wecotek.com), anvender optiske sensorer til at vurdere kvaliteten af produkterne, for eksempel ved at afvise grønne tomater. Disse kan implementeres i høstmaskiner på selve gården eller i forarbejdningsanlæg.

Med fremskridt inden for kunstig intelligens (AI) og maskinlæring (ML) kan disse maskiner blive mere avancerede og bruge ML-modeller, der er trænet til at skelne mellem frugt og fremmedlegemer som sten, jord eller insekter. Disse modeller kan også trænes til at vurdere frugtkvalitet, ikke kun beskadiget frugt, men også tidlig opdagelse af sygdomme eller andre problemer med afgrøder.

> 🎓 Begrebet *ML-model* refererer til resultatet af at træne maskinlæringssoftware på et datasæt. For eksempel kan du træne en ML-model til at skelne mellem modne og umodne tomater og derefter bruge modellen på nye billeder for at afgøre, om tomaterne er modne eller ej.

I disse 4 lektioner vil du lære, hvordan man træner billedbaserede AI-modeller til at vurdere frugtkvalitet, hvordan man bruger dem fra en IoT-enhed, og hvordan man kører dem på kanten - det vil sige på en IoT-enhed i stedet for i skyen.

> 💁 Disse lektioner vil bruge nogle cloud-ressourcer. Hvis du ikke gennemfører alle lektionerne i dette projekt, skal du sørge for at [rydde op i dit projekt](../clean-up.md).

## Emner

1. [Træn en frugtkvalitetsdetektor](./lessons/1-train-fruit-detector/README.md)
1. [Kontrollér frugtkvalitet fra en IoT-enhed](./lessons/2-check-fruit-from-device/README.md)
1. [Kør din frugtdetektor på kanten](./lessons/3-run-fruit-detector-edge/README.md)
1. [Udløs frugtkvalitetsdetektion fra en sensor](./lessons/4-trigger-fruit-detector/README.md)

## Kreditering

Alle lektionerne er skrevet med ♥️ af [Jen Fox](https://github.com/jenfoxbot) og [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.