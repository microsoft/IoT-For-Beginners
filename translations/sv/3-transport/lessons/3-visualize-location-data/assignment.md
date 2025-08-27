<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ccdc1faa676a485c4c6ecbddb9f9067",
  "translation_date": "2025-08-27T21:35:16+00:00",
  "source_file": "3-transport/lessons/3-visualize-location-data/assignment.md",
  "language_code": "sv"
}
-->
# Distribuera din app

## Instruktioner

Det finns flera sätt att distribuera din app så att du kan dela den med världen, inklusive att använda GitHub Pages eller en av många tjänsteleverantörer. Ett riktigt bra sätt att göra detta är att använda Azure Static Web Apps. I denna uppgift ska du bygga din webbapp och distribuera den till molnet genom att följa [dessa instruktioner](https://github.com/Azure/static-web-apps-cli) eller titta på [dessa videor](https://www.youtube.com/watch?v=ADVGIXciYn8&list=PLlrxD0HtieHgMPeBaDQFx9yNuFxx6S1VG&index=3).  
En fördel med att använda Azure Static Web Apps är att du kan dölja API-nycklar i portalen, så ta tillfället i akt att omstrukturera din subscriptionKey som en variabel och lagra den i molnet.

## Bedömningskriterier

| Kriterier | Exemplariskt                                                                                                                           | Tillräckligt                                                                                                       | Behöver förbättras                                 |
| --------- | --------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------- |
|           | En fungerande webbapp presenteras i ett dokumenterat GitHub-repository med sin subscriptionKey lagrad i molnet och anropad via en variabel | En fungerande webbapp presenteras i ett dokumenterat GitHub-repository men dess subscriptionKey är inte lagrad i molnet | Webbappen innehåller buggar eller fungerar inte korrekt |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.