<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ed0fbd6aed084bfba7d5e2f206968c50",
  "translation_date": "2025-08-27T21:12:27+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/assignment.md",
  "language_code": "nl"
}
-->
# Bouw een efficiëntere bewateringscyclus

## Instructies

In deze les hebben we besproken hoe je een relais kunt aansturen met behulp van sensorgegevens. Dat relais kan op zijn beurt een pomp aansturen voor een irrigatiesysteem. Voor een bepaald stuk grond heeft het draaien van een pomp gedurende een vaste tijd altijd dezelfde invloed op het bodemvocht. Dit betekent dat je een idee kunt krijgen van hoeveel seconden irrigatie overeenkomen met een bepaalde daling in de bodemvochtmeting. Met deze gegevens kun je een beter gecontroleerd irrigatiesysteem bouwen.

Voor deze opdracht bereken je hoe lang de pomp moet draaien om een specifieke stijging in het bodemvocht te bereiken.

> ⚠️ Als je virtuele IoT-hardware gebruikt, kun je dit proces doorlopen, maar simuleer de resultaten door de bodemvochtmeting handmatig met een vaste hoeveelheid per seconde te verhogen terwijl het relais aan staat.

1. Begin met droge grond. Meet het bodemvocht.

1. Voeg een vaste hoeveelheid water toe, ofwel door de pomp 1 seconde te laten draaien of door een vaste hoeveelheid water te gieten.

    > De pomp moet altijd met een constante snelheid werken, zodat elke seconde dat de pomp draait dezelfde hoeveelheid water wordt geleverd.

1. Wacht tot het bodemvochtgehalte stabiliseert en neem een meting.

1. Herhaal dit meerdere keren en maak een tabel van de resultaten. Een voorbeeld van zo'n tabel is hieronder gegeven.

    | Totale pomptijd | Bodemvocht | Daling |
    | --- | --: | -: |
    | Droog | 643 |  0 |
    | 1s  | 621 | 22 |
    | 2s  | 601 | 20 |
    | 3s  | 579 | 22 |
    | 4s  | 560 | 19 |
    | 5s  | 539 | 21 |
    | 6s  | 521 | 18 |

1. Bereken een gemiddelde stijging in bodemvocht per seconde water. In het bovenstaande voorbeeld verlaagt elke seconde water de meting gemiddeld met 20,3.

1. Gebruik deze gegevens om de efficiëntie van je servercode te verbeteren door de pomp de benodigde tijd te laten draaien om het bodemvocht naar het gewenste niveau te brengen.

## Beoordelingscriteria

| Criteria | Uitmuntend | Voldoende | Verbetering Nodig |
| -------- | ---------- | --------- | ----------------- |
| Vastleggen van bodemvochtgegevens | Kan meerdere metingen vastleggen na het toevoegen van vaste hoeveelheden water | Kan enkele metingen vastleggen met vaste hoeveelheden water | Kan slechts één of twee metingen vastleggen, of kan geen vaste hoeveelheden water gebruiken |
| Kalibreren van de servercode | Kan een gemiddelde daling in bodemvocht berekenen en de servercode hiermee bijwerken | Kan een gemiddelde daling berekenen, maar kan de servercode niet bijwerken, of kan geen gemiddelde correct berekenen, maar gebruikt deze waarde wel om de servercode correct bij te werken | Kan geen gemiddelde berekenen of de servercode bijwerken |

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.