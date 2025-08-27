<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bded364fc06ce37d7a76aed3be1ba73a",
  "translation_date": "2025-08-27T21:28:00+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/assignment.md",
  "language_code": "sv"
}
-->
# Undersök annan GPS-data

## Instruktioner

NMEA-meddelandena från din GPS-sensor innehåller annan data utöver platsinformation. Undersök den extra datan och använd den i din IoT-enhet.

Till exempel - kan du få aktuell datum och tid? Om du använder en mikrokontroller, kan du ställa in klockan med GPS-data på samma sätt som du gjorde med NTP-signaler i det tidigare projektet? Kan du få höjd (din höjd över havet) eller din aktuella hastighet?

Om du använder en virtuell IoT-enhet kan du få en del av denna data genom att skicka NMEA-meddelanden som genereras med verktyg från [nmeagen.org](https://www.nmeagen.org).

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Få mer GPS-data | Kan få och använda mer GPS-data, antingen som telemetri eller för att konfigurera IoT-enheten | Kan få mer GPS-data, men kan inte använda den | Kan inte få mer GPS-data |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.