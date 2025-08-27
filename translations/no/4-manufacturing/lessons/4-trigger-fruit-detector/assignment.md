<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1a85e50c33c38dcd2cde2a97d132f248",
  "translation_date": "2025-08-27T20:32:53+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/assignment.md",
  "language_code": "no"
}
-->
# Bygg en fruktkvalitetsdetektor

## Instruksjoner

Bygg fruktkvalitetsdetektoren!

Bruk alt du har lært så langt til å bygge en prototype for fruktkvalitetsdetektoren. Utfør bildeklassifisering basert på nærhet ved hjelp av en AI-modell som kjører på kanten, lagre klassifiseringsresultatene i lagring, og kontroller en LED basert på fruktens modenhet.

Du bør kunne sette dette sammen ved å bruke kode du tidligere har skrevet i alle leksjonene så langt.

## Vurderingskriterier

| Kriterier | Eksemplarisk | Tilfredsstillende | Trenger forbedring |
| --------- | ------------ | ----------------- | ------------------ |
| Konfigurer alle tjenestene | Klarte å sette opp en IoT Hub, Azure Functions-applikasjon og Azure-lagring | Klarte å sette opp IoT Hub, men ikke enten Azure Functions-applikasjonen eller Azure-lagring | Klarte ikke å sette opp noen internettbaserte IoT-tjenester |
| Overvåk nærhet og send data til IoT Hub hvis et objekt er nærmere enn en forhåndsdefinert avstand, og utløse kameraet via en kommando | Klarte å måle avstand og sende en melding til IoT Hub når et objekt var nært nok, og sende en kommando for å utløse kameraet | Klarte å måle nærhet og sende til IoT Hub, men klarte ikke å sende en kommando til kameraet | Klarte ikke å måle avstand og sende en melding til IoT Hub, eller utløse en kommando |
| Ta et bilde, klassifiser det og send resultatene til IoT Hub | Klarte å ta et bilde, klassifisere det ved hjelp av en kant-enhet og sende resultatene til IoT Hub | Klarte å klassifisere bildet, men ikke ved hjelp av en kant-enhet, eller klarte ikke å sende resultatene til IoT Hub | Klarte ikke å klassifisere et bilde |
| Slå LED-en av eller på avhengig av klassifiseringsresultatene ved hjelp av en kommando sendt til en enhet | Klarte å slå på en LED via en kommando hvis frukten var umoden | Klarte å sende kommandoen til enheten, men ikke kontrollere LED-en | Klarte ikke å sende en kommando for å kontrollere LED-en |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.