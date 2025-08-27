<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T22:58:45+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "sv"
}
-->
# Bygg en mer effektiv bevattningscykel

## Instruktioner

Den här lektionen behandlade hur man styr ett relä via sensordata, och det reläet kan i sin tur styra en pump för ett bevattningssystem. För en definierad mängd jord bör körning av en pump under en fast tidsperiod alltid ha samma effekt på jordens fuktighet. Detta innebär att du kan få en uppfattning om hur många sekunder av bevattning som motsvarar en viss minskning i jordfuktighetsavläsning. Med hjälp av dessa data kan du bygga ett mer kontrollerat bevattningssystem.

I denna uppgift ska du beräkna hur länge pumpen ska köras för att uppnå en specifik ökning i jordfuktighet.

> ⚠️ Om du använder virtuell IoT-hårdvara kan du gå igenom denna process, men simulera resultaten genom att manuellt öka jordfuktighetsavläsningen med ett fast belopp per sekund som reläet är på.

1. Börja med torr jord. Mät jordens fuktighet.

1. Tillsätt en fast mängd vatten, antingen genom att köra pumpen i 1 sekund eller genom att hälla i en fast mängd.

    > Pumpen ska alltid köras med en konstant hastighet, så varje sekund pumpen körs ska den tillföra samma mängd vatten.

1. Vänta tills jordfuktighetsnivån stabiliseras och ta en avläsning.

1. Upprepa detta flera gånger och skapa en tabell med resultaten. Ett exempel på en sådan tabell ges nedan.

    | Total pumpningstid | Jordfuktighet | Minskning |
    | --- | --: | -: |
    | Torr | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Räkna ut en genomsnittlig ökning i jordfuktighet per sekund av vatten. I exemplet ovan minskar varje sekund av vatten avläsningen med i genomsnitt 20,3.

1. Använd dessa data för att förbättra effektiviteten i din serverkod, genom att köra pumpen under den tid som krävs för att få jordfuktigheten till önskad nivå.

## Bedömningskriterier

| Kriterier | Exemplariskt | Tillräckligt | Behöver förbättras |
| --------- | ------------ | ------------ | ------------------ |
| Registrera jordfuktighetsdata | Kan registrera flera avläsningar efter att ha tillsatt fasta mängder vatten | Kan registrera några avläsningar med fasta mängder vatten | Kan endast registrera en eller två avläsningar, eller kan inte använda fasta mängder vatten |
| Kalibrera serverkoden | Kan beräkna en genomsnittlig minskning i jordfuktighetsavläsning och uppdatera serverkoden för att använda detta | Kan beräkna en genomsnittlig minskning, men kan inte uppdatera serverkoden, eller kan inte korrekt beräkna ett genomsnitt, men använder detta värde för att korrekt uppdatera serverkoden | Kan inte beräkna ett genomsnitt eller uppdatera serverkoden |

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.