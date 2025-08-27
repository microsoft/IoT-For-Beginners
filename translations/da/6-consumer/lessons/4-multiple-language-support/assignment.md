<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T21:17:50+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "da"
}
-->
# Byg en universel oversætter

## Instruktioner

En universel oversætter er en enhed, der kan oversætte mellem flere sprog, så folk, der taler forskellige sprog, kan kommunikere med hinanden. Brug det, du har lært i de seneste lektioner, til at bygge en universel oversætter ved hjælp af 2 IoT-enheder.

> Hvis du ikke har 2 enheder, skal du følge trinnene i de foregående lektioner for at opsætte en virtuel IoT-enhed som en af IoT-enhederne.

Du skal konfigurere én enhed til ét sprog og en anden til et andet. Hver enhed skal kunne modtage tale, konvertere det til tekst, sende det til den anden enhed via IoT Hub og en Functions-app, derefter oversætte det og afspille den oversatte tale.

> 💁 Tip: Når du sender talen fra én enhed til en anden, skal du også sende information om, hvilket sprog det er på, så det bliver nemmere at oversætte. Du kan endda lade hver enhed registrere sig via IoT Hub og en Functions-app først, hvor de angiver det sprog, de understøtter, så det kan gemmes i Azure Storage. Derefter kan du bruge en Functions-app til at udføre oversættelserne og sende den oversatte tekst til IoT-enheden.

## Bedømmelseskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Opret en universel oversætter | Formåede at bygge en universel oversætter, der konverterer tale opfanget af én enhed til tale afspillet af en anden enhed på et andet sprog | Formåede at få nogle komponenter til at fungere, såsom at opfange tale eller oversætte, men kunne ikke bygge en fuld løsning fra ende til anden | Formåede ikke at bygge nogen dele af en fungerende universel oversætter |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.