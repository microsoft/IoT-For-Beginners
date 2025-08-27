<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "022e21f8629b721424c1de25195fff67",
  "translation_date": "2025-08-27T20:45:49+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/assignment.md",
  "language_code": "da"
}
-->
# Reager på klassifikationsresultater

## Instruktioner

Din enhed har klassificeret billeder og har værdierne for forudsigelserne. Din enhed kan bruge denne information til at gøre noget - den kan sende det til IoT Hub for behandling af andre systemer, eller den kan styre en aktuator, såsom en LED, der lyser op, når frugten er umoden.

Tilføj kode til din enhed, så den reagerer på en måde, du vælger - enten ved at sende data til en IoT Hub, styre en aktuator, eller kombinere de to og sende data til en IoT Hub med noget serverløs kode, der afgør, om frugten er moden eller ej, og sender en kommando tilbage for at styre en aktuator.

## Bedømmelseskriterier

| Kriterier | Fremragende | Tilstrækkelig | Kræver forbedring |
| --------- | ----------- | ------------- | ----------------- |
| Reager på forudsigelser | Var i stand til at implementere en reaktion på forudsigelser, der fungerer konsekvent med forudsigelser af samme værdi. | Var i stand til at implementere en reaktion, der ikke er afhængig af forudsigelserne, såsom blot at sende rå data til en IoT Hub. | Var ikke i stand til at programmere enheden til at reagere på forudsigelserne. |

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.