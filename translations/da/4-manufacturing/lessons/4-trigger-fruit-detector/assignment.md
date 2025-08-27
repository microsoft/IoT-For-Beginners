<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T20:32:44+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "da"
}
-->
# Byg en frugtkvalitetsdetektor

## Instruktioner

Byg frugtkvalitetsdetektoren!

Brug alt, hvad du har lært indtil nu, og byg en prototype af en frugtkvalitetsdetektor. Udløs billedklassifikation baseret på nærhed ved hjælp af en AI-model, der kører på kanten, gem resultaterne af klassifikationen i en lagringstjeneste, og styr en LED baseret på frugtens modenhed.

Du bør kunne samle dette ved hjælp af kode, du tidligere har skrevet i alle lektionerne indtil nu.

## Bedømmelseskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver Forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Konfigurer alle tjenester | Kunne opsætte en IoT Hub, Azure-funktionsapplikation og Azure-lagring | Kunne opsætte IoT Hub, men ikke enten Azure-funktionsapplikationen eller Azure-lagring | Kunne ikke opsætte nogen internetbaserede IoT-tjenester |
| Overvåg nærhed og send data til IoT Hub, hvis et objekt er tættere end en foruddefineret afstand, og udløs kameraet via en kommando | Kunne måle afstand og sende en besked til IoT Hub, når et objekt var tæt nok, og sende en kommando for at udløse kameraet | Kunne måle nærhed og sende til IoT Hub, men kunne ikke sende en kommando til kameraet | Kunne ikke måle afstand og sende en besked til IoT Hub eller udløse en kommando |
| Tag et billede, klassificer det og send resultaterne til IoT Hub | Kunne tage et billede, klassificere det ved hjælp af en edge-enhed og sende resultaterne til IoT Hub | Kunne klassificere billedet, men ikke ved hjælp af en edge-enhed, eller kunne ikke sende resultaterne til IoT Hub | Kunne ikke klassificere et billede |
| Tænd eller sluk LED'en afhængigt af klassifikationsresultaterne ved hjælp af en kommando sendt til en enhed | Kunne tænde en LED via en kommando, hvis frugten var umoden | Kunne sende kommandoen til enheden, men ikke styre LED'en | Kunne ikke sende en kommando for at styre LED'en |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.