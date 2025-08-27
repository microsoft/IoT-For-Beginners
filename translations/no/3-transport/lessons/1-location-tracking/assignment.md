<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bded364fc06ce37d7a76aed3be1ba73a",
  "translation_date": "2025-08-27T21:28:15+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/assignment.md",
  "language_code": "no"
}
-->
# Undersøk annen GPS-data

## Instruksjoner

NMEA-setningene fra GPS-sensoren din inneholder annen data i tillegg til posisjon. Undersøk den ekstra dataen, og bruk den i IoT-enheten din.

For eksempel - kan du hente gjeldende dato og tid? Hvis du bruker en mikrokontroller, kan du sette klokken ved hjelp av GPS-data på samme måte som du gjorde med NTP-signaler i det forrige prosjektet? Kan du hente høyde (din høyde over havet), eller din nåværende hastighet?

Hvis du bruker en virtuell IoT-enhet, kan du få noe av denne dataen ved å sende NMEA-setninger generert ved hjelp av verktøyet [nmeagen.org](https://www.nmeagen.org).

## Vurderingskriterier

| Kriterier | Fremragende | Tilfredsstillende | Trenger forbedring |
| --------- | ----------- | ----------------- | ------------------ |
| Hente mer GPS-data | Klarer å hente og bruke mer GPS-data, enten som telemetri eller for å konfigurere IoT-enheten | Klarer å hente mer GPS-data, men klarer ikke å bruke det | Klarer ikke å hente mer GPS-data |

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vennligst vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør betraktes som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.