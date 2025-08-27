<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-27T22:39:17+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "da"
}
-->
# Byg en ny IoT-enhed

## Instruktioner

I løbet af de sidste 6 lektioner har du lært om digital landbrug og hvordan man bruger IoT-enheder til at indsamle data for at forudsige plantevækst og automatisere vanding baseret på målinger af jordfugtighed.

Brug det, du har lært, til at bygge en ny IoT-enhed ved hjælp af en sensor og aktuator efter eget valg. Send telemetri til en IoT Hub, og brug den til at styre en aktuator via serverløs kode. Du kan bruge en sensor og en aktuator, som du allerede har brugt i dette eller det tidligere projekt, eller hvis du har andet hardware, kan du prøve noget nyt.

## Vurderingskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Kod en IoT-enhed til at bruge en sensor og aktuator | Kodede en IoT-enhed, der fungerer med både sensor og aktuator | Kodede en IoT-enhed, der fungerer med enten sensor eller aktuator | Kunne ikke kode en IoT-enhed til at bruge sensor eller aktuator |
| Forbind IoT-enheden til IoT Hub | Kunne implementere en IoT Hub og sende telemetri til den samt modtage kommandoer fra den | Kunne implementere en IoT Hub og enten sende telemetri eller modtage kommandoer | Kunne ikke implementere en IoT Hub og kommunikere med den fra en IoT-enhed |
| Styr aktuatoren ved hjælp af serverløs kode | Kunne implementere en Azure Function til at styre enheden udløst af telemetrihændelser | Kunne implementere en Azure Function udløst af telemetrihændelser, men kunne ikke styre aktuatoren | Kunne ikke implementere en Azure Function |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.