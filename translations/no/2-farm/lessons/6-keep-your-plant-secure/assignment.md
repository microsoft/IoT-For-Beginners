<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "34010c663d96d5f419eda6ac2366a78d",
  "translation_date": "2025-08-27T22:39:25+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/assignment.md",
  "language_code": "no"
}
-->
# Bygg en ny IoT-enhet

## Instruksjoner

I løpet av de siste 6 leksjonene har du lært om digital landbruk og hvordan du kan bruke IoT-enheter til å samle inn data for å forutsi plantevekst, samt automatisere vanning basert på målinger av jordfuktighet.

Bruk det du har lært til å bygge en ny IoT-enhet ved hjelp av en sensor og en aktuator etter eget valg. Send telemetri til en IoT Hub, og bruk dette til å kontrollere en aktuator via serverløs kode. Du kan bruke en sensor og en aktuator du allerede har brukt i dette eller det forrige prosjektet, eller hvis du har annet utstyr, prøv noe nytt.

## Vurderingskriterier

| Kriterier | Fremragende | Tilfredsstillende | Trenger forbedring |
| --------- | ----------- | ----------------- | ------------------ |
| Kode en IoT-enhet som bruker en sensor og aktuator | Kodet en IoT-enhet som fungerer med både sensor og aktuator | Kodet en IoT-enhet som fungerer med enten sensor eller aktuator | Klarte ikke å kode en IoT-enhet som bruker sensor eller aktuator |
| Koble IoT-enheten til IoT Hub | Klarte å sette opp en IoT Hub og sende telemetri til den, samt motta kommandoer fra den | Klarte å sette opp en IoT Hub og enten sende telemetri eller motta kommandoer | Klarte ikke å sette opp en IoT Hub eller kommunisere med den fra en IoT-enhet |
| Kontrollere aktuatoren med serverløs kode | Klarte å sette opp en Azure Function for å kontrollere enheten utløst av telemetrihendelser | Klarte å sette opp en Azure Function utløst av telemetrihendelser, men klarte ikke å kontrollere aktuatoren | Klarte ikke å sette opp en Azure Function |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.