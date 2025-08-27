<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-27T20:47:58+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "da"
}
-->
# Forbruger-IoT - byg en smart stemmeassistent

Maden er blevet dyrket, kørt til et forarbejdningsanlæg, sorteret for kvalitet, solgt i butikken, og nu er det tid til at lave mad! En af de vigtigste redskaber i ethvert køkken er en timer. Oprindeligt startede disse som timeglas - din mad var færdiglavet, når alt sandet var løbet ned i den nederste beholder. Derefter blev de mekaniske, og senere elektriske.

De nyeste versioner er nu en del af vores smarte enheder. I køkkener i hjem verden over hører man kokke råbe "Hey Siri - sæt en 10-minutters timer", eller "Alexa - annuller min brødtimer". Du behøver ikke længere gå tilbage til køkkenet for at tjekke en timer; du kan gøre det fra din telefon eller ved at råbe tværs over rummet.

I disse 4 lektioner lærer du, hvordan du bygger en smart timer, der bruger AI til at genkende din stemme, forstå hvad du beder om, og give dig information om din timer. Du vil også tilføje understøttelse af flere sprog.

> ⚠️ Arbejde med tale- og mikrofondata bruger meget hukommelse, hvilket betyder, at det er nemt at ramme grænser på mikrocontrollere. Projektet her omgår disse problemer, men vær opmærksom på, at Wio Terminal-laboratorierne er komplekse og kan tage længere tid end andre laboratorier i dette pensum.

> 💁 Disse lektioner vil bruge nogle cloud-ressourcer. Hvis du ikke fuldfører alle lektionerne i dette projekt, skal du sørge for at [rydde op i dit projekt](../clean-up.md).

## Emner

1. [Genkend tale med en IoT-enhed](./lessons/1-speech-recognition/README.md)
1. [Forstå sprog](./lessons/2-language-understanding/README.md)
1. [Sæt en timer og giv talebaseret feedback](./lessons/3-spoken-feedback/README.md)
1. [Understøt flere sprog](./lessons/4-multiple-language-support/README.md)

## Kreditering

Alle lektionerne er skrevet med ♥️ af [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.