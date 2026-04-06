# Mål jordfuktighet - Virtuell IoT-maskinvare

I denne delen av leksjonen skal du legge til en kapasitansbasert jordfuktighetssensor til din virtuelle IoT-enhet og lese verdier fra den.

## Virtuell maskinvare

Den virtuelle IoT-enheten vil bruke en simulert Grove kapasitansbasert jordfuktighetssensor. Dette holder denne øvelsen lik som å bruke en Raspberry Pi med en fysisk Grove kapasitansbasert jordfuktighetssensor.

I en fysisk IoT-enhet ville jordfuktighetssensoren vært en kapasitanssensor som måler jordfuktighet ved å oppdage jordens kapasitans, en egenskap som endres når jordfuktigheten endres. Når jordfuktigheten øker, synker spenningen.

Dette er en analog sensor, så den bruker en simulert 10-bits ADC for å rapportere en verdi fra 1-1 023.

### Legg til jordfuktighetssensoren i CounterFit

For å bruke en virtuell jordfuktighetssensor må du legge den til i CounterFit-appen.

#### Oppgave - Legg til jordfuktighetssensoren i CounterFit

Legg til jordfuktighetssensoren i CounterFit-appen.

1. Opprett en ny Python-app på datamaskinen din i en mappe kalt `soil-moisture-sensor` med en enkelt fil kalt `app.py` og et Python-virtuelt miljø, og legg til CounterFit-pip-pakkene.

    > ⚠️ Du kan referere til [instruksjonene for å opprette og sette opp et CounterFit Python-prosjekt i leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Sørg for at CounterFit-nettappen kjører.

1. Opprett en jordfuktighetssensor:

    1. I boksen *Create sensor* i *Sensors*-panelet, åpne rullegardinmenyen *Sensor type* og velg *Soil Moisture*.

    1. La *Units* stå som *NoUnits*.

    1. Sørg for at *Pin* er satt til *0*.

    1. Velg **Add**-knappen for å opprette *Soil Moisture*-sensoren på Pin 0.

    ![Innstillingene for jordfuktighetssensoren](../../../../../translated_images/no/counterfit-create-soil-moisture-sensor.35266135a5e0ae68.webp)

    Jordfuktighetssensoren vil bli opprettet og vises i sensorlisten.

    ![Jordfuktighetssensoren opprettet](../../../../../translated_images/no/counterfit-soil-moisture-sensor.81742b2de0e9de60.webp)

## Programmer appen for jordfuktighetssensoren

Appen for jordfuktighetssensoren kan nå programmeres ved hjelp av CounterFit-sensorene.

### Oppgave - Programmer appen for jordfuktighetssensoren

Programmer appen for jordfuktighetssensoren.

1. Sørg for at `soil-moisture-sensor`-appen er åpen i VS Code.

1. Åpne filen `app.py`.

1. Legg til følgende kode øverst i `app.py` for å koble appen til CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Legg til følgende kode i `app.py`-filen for å importere noen nødvendige biblioteker:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    `import time`-setningen importerer `time`-modulen som vil bli brukt senere i denne oppgaven.

    `from counterfit_shims_grove.adc import ADC`-setningen importerer `ADC`-klassen for å samhandle med en virtuell analog-til-digital-omformer som kan kobles til en CounterFit-sensor.

1. Legg til følgende kode under dette for å opprette en instans av `ADC`-klassen:

    ```python
    adc = ADC()
    ```

1. Legg til en uendelig løkke som leser fra denne ADC-en på pin 0 og skriver resultatet til konsollen. Denne løkken kan deretter sove i 10 sekunder mellom hver lesing.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. Fra CounterFit-appen, endre verdien til jordfuktighetssensoren som vil bli lest av appen. Du kan gjøre dette på to måter:

    * Skriv inn et tall i *Value*-boksen for jordfuktighetssensoren, og velg deretter **Set**-knappen. Tallet du skriver inn vil være verdien som sensoren returnerer.

    * Merk av i *Random*-avkrysningsboksen, og skriv inn en *Min*- og *Max*-verdi, og velg deretter **Set**-knappen. Hver gang sensoren leser en verdi, vil den lese et tilfeldig tall mellom *Min* og *Max*.

1. Kjør Python-appen. Du vil se målingene av jordfuktighet skrevet til konsollen. Endre *Value* eller *Random*-innstillingene for å se verdien endre seg.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Du finner denne koden i [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device)-mappen.

😀 Programmet for jordfuktighetssensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.