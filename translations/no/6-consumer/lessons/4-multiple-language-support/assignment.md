<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T21:18:00+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "no"
}
-->
# Bygg en universell oversetter

## Instruksjoner

En universell oversetter er en enhet som kan oversette mellom flere språk, slik at folk som snakker forskjellige språk kan kommunisere. Bruk det du har lært i de siste leksjonene til å bygge en universell oversetter ved hjelp av 2 IoT-enheter.

> Hvis du ikke har 2 enheter, følg trinnene i de siste leksjonene for å sette opp en virtuell IoT-enhet som en av IoT-enhetene.

Du bør konfigurere én enhet for ett språk, og en annen for et annet. Hver enhet skal kunne ta imot tale, konvertere det til tekst, sende det til den andre enheten via IoT Hub og en Functions-app, deretter oversette det og spille av den oversatte talen.

> 💁 Tips: Når du sender talen fra én enhet til en annen, send også språket det er på, slik at det blir enklere å oversette. Du kan til og med la hver enhet registrere seg via IoT Hub og en Functions-app først, og sende språket de støtter for å lagres i Azure Storage. Deretter kan du bruke en Functions-app til å utføre oversettelsene og sende den oversatte teksten til IoT-enheten.

## Vurderingskriterier

| Kriterier | Fremragende | Tilfredsstillende | Trenger forbedring |
| --------- | ----------- | ----------------- | ------------------ |
| Lag en universell oversetter | Klarte å bygge en universell oversetter som konverterer tale oppdaget av én enhet til tale spilt av en annen enhet på et annet språk | Klarte å få noen komponenter til å fungere, som å fange opp tale eller oversette, men klarte ikke å bygge en helhetlig løsning | Klarte ikke å bygge noen deler av en fungerende universell oversetter |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.