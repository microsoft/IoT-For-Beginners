# Kontrollere et relé - Virtuell IoT-maskinvare

I denne delen av leksjonen skal du legge til et relé til din virtuelle IoT-enhet i tillegg til jordfuktighetssensoren, og styre det basert på jordfuktighetsnivået.

## Virtuell maskinvare

Den virtuelle IoT-enheten vil bruke et simulert Grove-relé. Dette holder denne labben lik som å bruke en Raspberry Pi med et fysisk Grove-relé.

På en fysisk IoT-enhet ville reléet være et normalt åpent relé (som betyr at utgangskretsen er åpen, eller frakoblet, når det ikke sendes noe signal til reléet). Et slikt relé kan håndtere utgangskretser opp til 250V og 10A.

### Legg til reléet i CounterFit

For å bruke et virtuelt relé, må du legge det til i CounterFit-appen.

#### Oppgave

Legg til reléet i CounterFit-appen.

1. Åpne `soil-moisture-sensor`-prosjektet fra forrige leksjon i VS Code hvis det ikke allerede er åpent. Du vil legge til dette prosjektet.

1. Sørg for at CounterFit-nettappen kjører.

1. Opprett et relé:

    1. I *Create actuator*-boksen i *Actuators*-panelet, åpne rullegardinmenyen *Actuator type* og velg *Relay*.

    1. Sett *Pin* til *5*.

    1. Velg **Add**-knappen for å opprette reléet på Pin 5.

    ![Reléinnstillingene](../../../../../translated_images/no/counterfit-create-relay.fa7c40fd0f2f6afc.webp)

    Reléet vil bli opprettet og vises i listen over aktuatorer.

    ![Reléet opprettet](../../../../../translated_images/no/counterfit-relay.bbf74c1dbdc8b9ac.webp)

## Programmer reléet

Jordfuktighetssensor-appen kan nå programmeres til å bruke det virtuelle reléet.

### Oppgave

Programmer den virtuelle enheten.

1. Åpne `soil-moisture-sensor`-prosjektet fra forrige leksjon i VS Code hvis det ikke allerede er åpent. Du vil legge til dette prosjektet.

1. Legg til følgende kode i `app.py`-filen under de eksisterende importene:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    Denne kodelinjen importerer `GroveRelay` fra Grove Python shim-bibliotekene for å interagere med det virtuelle Grove-reléet.

1. Legg til følgende kode under deklarasjonen av `ADC`-klassen for å opprette en `GroveRelay`-instans:

    ```python
    relay = GroveRelay(5)
    ```

    Dette oppretter et relé ved bruk av pin **5**, pinnen du koblet reléet til.

1. For å teste at reléet fungerer, legg til følgende i `while True:`-løkka:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    Koden slår reléet på, venter 0,5 sekunder, og slår deretter reléet av.

1. Kjør Python-appen. Reléet vil slå seg på og av hvert 10. sekund, med en halv sekunds forsinkelse mellom på og av. Du vil se det virtuelle reléet i CounterFit-appen lukke og åpne seg når reléet slås på og av.

    ![Det virtuelle reléet slår seg på og av](../../../../../images/virtual-relay-turn-on-off.gif)

## Kontrollere reléet basert på jordfuktighet

Nå som reléet fungerer, kan det styres basert på jordfuktighetsavlesninger.

### Oppgave

Kontroller reléet.

1. Slett de 3 kodelinjene du la til for å teste reléet. Erstatt dem med følgende kode:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    Denne koden sjekker jordfuktighetsnivået fra jordfuktighetssensoren. Hvis det er over 450, slår den på reléet, og slår det av hvis det går under 450.

    > 💁 Husk at den kapasitive jordfuktighetssensoren leser lavere verdier jo mer fuktighet det er i jorden, og vice versa.

1. Kjør Python-appen. Du vil se reléet slå seg på eller av avhengig av jordfuktighetsnivåene. Endre *Value* eller *Random*-innstillingene for jordfuktighetssensoren for å se verdien endre seg.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 Du finner denne koden i [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device)-mappen.

😀 Programmet ditt for å kontrollere et relé med en virtuell jordfuktighetssensor var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.