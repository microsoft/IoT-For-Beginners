<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a7262a0c48dfacdfe1ff91b20bf16fd",
  "translation_date": "2025-08-27T20:52:25+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/assignment.md",
  "language_code": "no"
}
-->
# Avbryt timeren

## Instruksjoner

Så langt i denne leksjonen har du trent en modell til å forstå hvordan man setter en timer. En annen nyttig funksjon er å avbryte en timer – kanskje brødet ditt er ferdig og kan tas ut av ovnen før timeren går ut.

Legg til en ny intensjon i LUIS-appen din for å avbryte timeren. Den trenger ingen entiteter, men vil trenge noen eksempelsitater. Håndter dette i din serverløse kode hvis det er den høyeste intensjonen, logg at intensjonen ble gjenkjent og returner en passende respons.

## Vurderingskriterier

| Kriterier | Eksemplarisk | Tilfredsstillende | Trenger forbedring |
| --------- | ------------ | ----------------- | ------------------ |
| Legg til intensjonen for å avbryte timeren i LUIS-appen | Klarte å legge til intensjonen og trene modellen | Klarte å legge til intensjonen, men ikke trene modellen | Klarte ikke å legge til intensjonen og trene modellen |
| Håndter intensjonen i den serverløse appen | Klarte å oppdage intensjonen som den høyeste intensjonen og logge den | Klarte å oppdage intensjonen som den høyeste intensjonen | Klarte ikke å oppdage intensjonen som den høyeste intensjonen |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.