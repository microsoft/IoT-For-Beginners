# Reager på klassifiseringsresultater

## Instruksjoner

Enheten din har klassifisert bilder og har verdiene for prediksjonene. Enheten din kan bruke denne informasjonen til å gjøre noe - den kan sende det til IoT Hub for behandling av andre systemer, eller den kan kontrollere en aktuator, for eksempel en LED som lyser opp når frukten er umoden.

Legg til kode på enheten din for å reagere på en måte du velger - enten send data til en IoT Hub, kontroller en aktuator, eller kombiner de to og send data til en IoT Hub med noe serverløs kode som avgjør om frukten er moden eller ikke og sender tilbake en kommando for å kontrollere en aktuator.

## Vurderingskriterier

| Kriterier | Eksemplarisk | Tilfredsstillende | Trenger forbedring |
| --------- | ------------ | ----------------- | ------------------ |
| Reagere på prediksjoner | Klarte å implementere en respons på prediksjoner som fungerer konsekvent med prediksjoner av samme verdi. | Klarte å implementere en respons som ikke er avhengig av prediksjonene, for eksempel bare å sende rådata til en IoT Hub. | Klarte ikke å programmere enheten til å reagere på prediksjonene. |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.