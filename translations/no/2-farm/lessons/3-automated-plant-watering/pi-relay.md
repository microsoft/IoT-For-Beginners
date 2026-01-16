<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T22:57:44+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "no"
}
-->
# Kontrollere et relé - Raspberry Pi

I denne delen av leksjonen skal du legge til et relé på din Raspberry Pi i tillegg til jordfuktighetssensoren, og styre det basert på jordfuktighetsnivået.

## Maskinvare

Raspberry Pi trenger et relé.

Reléet du skal bruke er et [Grove-relé](https://www.seeedstudio.com/Grove-Relay.html), et normalt åpent relé (som betyr at utgangskretsen er åpen, eller frakoblet, når det ikke sendes signal til reléet) som kan håndtere utgangskretser opptil 250V og 10A.

Dette er en digital aktuator, så det kobles til en digital pinne på Grove Base Hat.

### Koble til reléet

Grove-reléet kan kobles til Raspberry Pi.

#### Oppgave

Koble til reléet.

![Et Grove-relé](../../../../../translated_images/no/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på reléet. Den vil kun gå inn på én måte.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til den digitale kontakten merket **D5** på Grove Base Hat som er festet til Pi. Denne kontakten er den andre fra venstre, på raden av kontakter ved siden av GPIO-pinnene. La jordfuktighetssensoren være koblet til **A0**-kontakten.

![Grove-reléet koblet til D5-kontakten, og jordfuktighetssensoren koblet til A0-kontakten](../../../../../translated_images/no/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. Sett jordfuktighetssensoren inn i jorden, hvis den ikke allerede er det fra forrige leksjon.

## Programmer reléet

Raspberry Pi kan nå programmeres til å bruke det tilkoblede reléet.

### Oppgave

Programmer enheten.

1. Slå på Pi og vent til den starter opp.

1. Åpne `soil-moisture-sensor`-prosjektet fra forrige leksjon i VS Code hvis det ikke allerede er åpent. Du skal legge til dette prosjektet.

1. Legg til følgende kode i `app.py`-filen under de eksisterende importene:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    Denne erklæringen importerer `GroveRelay` fra Grove Python-bibliotekene for å interagere med Grove-reléet.

1. Legg til følgende kode under deklarasjonen av `ADC`-klassen for å opprette en `GroveRelay`-instans:

    ```python
    relay = GroveRelay(5)
    ```

    Dette oppretter et relé ved bruk av pinne **D5**, den digitale pinnen du koblet reléet til.

1. For å teste at reléet fungerer, legg til følgende i `while True:`-løkka:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koden slår reléet på, venter 0,5 sekunder, og slår deretter reléet av.

1. Kjør Python-appen. Reléet vil slå seg av og på hvert 10. sekund, med en halv sekunds forsinkelse mellom av og på. Du vil høre reléet klikke på og deretter klikke av. En LED på Grove-kortet vil lyse når reléet er på, og slukke når reléet er av.

    ![Reléet slår seg av og på](../../../../../images/relay-turn-on-off.gif)

## Kontrollere reléet basert på jordfuktighet

Nå som reléet fungerer, kan det styres basert på jordfuktighetsavlesninger.

### Oppgave

Kontroller reléet.

1. Slett de 3 linjene med kode som du la til for å teste reléet. Erstatt dem med følgende kode:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Denne koden sjekker jordfuktighetsnivået fra jordfuktighetssensoren. Hvis det er over 450, slår den på reléet, og slår det av når det går under 450.

    > 💁 Husk at den kapasitive jordfuktighetssensoren leser slik at jo lavere jordfuktighetsnivået er, desto mer fuktighet er det i jorden, og vice versa.

1. Kjør Python-appen. Du vil se reléet slå seg av eller på avhengig av jordfuktighetsnivået. Prøv i tørr jord, og tilsett deretter vann.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du finner denne koden i [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi)-mappen.

😀 Programmet ditt for å kontrollere et relé basert på jordfuktighetssensoren var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.