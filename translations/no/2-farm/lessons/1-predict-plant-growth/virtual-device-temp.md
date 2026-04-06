# Mål temperatur - Virtuell IoT-maskinvare

I denne delen av leksjonen skal du legge til en temperatursensor på din virtuelle IoT-enhet.

## Virtuell maskinvare

Den virtuelle IoT-enheten vil bruke en simulert Grove Digital Humidity and Temperature-sensor. Dette gjør at denne labben forblir lik som å bruke en Raspberry Pi med en fysisk Grove DHT11-sensor.

Sensoren kombinerer en **temperatursensor** med en **fuktighetssensor**, men i denne labben er du kun interessert i temperatursensoren. På en fysisk IoT-enhet ville temperatursensoren vært en [termistor](https://wikipedia.org/wiki/Thermistor) som måler temperatur ved å registrere endringer i motstand når temperaturen endres. Temperatursensorer er vanligvis digitale sensorer som internt konverterer den målte motstanden til en temperatur i grader Celsius (eller Kelvin, eller Fahrenheit).

### Legg til sensorer i CounterFit

For å bruke en virtuell fuktighets- og temperatursensor, må du legge til de to sensorene i CounterFit-appen.

#### Oppgave - legg til sensorer i CounterFit

Legg til fuktighets- og temperatursensorene i CounterFit-appen.

1. Opprett en ny Python-app på datamaskinen din i en mappe kalt `temperature-sensor` med en enkelt fil kalt `app.py` og et Python-virtuelt miljø, og legg til CounterFit pip-pakkene.

    > ⚠️ Du kan referere til [instruksjonene for å opprette og sette opp et CounterFit Python-prosjekt i leksjon 1 hvis nødvendig](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Installer en ekstra Pip-pakke for å installere en CounterFit shim for DHT11-sensoren. Sørg for at du installerer dette fra en terminal med det virtuelle miljøet aktivert.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Sørg for at CounterFit-nettappen kjører.

1. Opprett en fuktighetssensor:

    1. I *Create sensor*-boksen i *Sensors*-panelet, åpne rullegardinmenyen *Sensor type* og velg *Humidity*.

    1. La *Units* være satt til *Percentage*.

    1. Sørg for at *Pin* er satt til *5*.

    1. Velg **Add**-knappen for å opprette fuktighetssensoren på Pin 5.

    ![Innstillingene for fuktighetssensoren](../../../../../translated_images/no/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    Fuktighetssensoren vil bli opprettet og vises i sensorlisten.

    ![Fuktighetssensoren opprettet](../../../../../translated_images/no/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Opprett en temperatursensor:

    1. I *Create sensor*-boksen i *Sensors*-panelet, åpne rullegardinmenyen *Sensor type* og velg *Temperature*.

    1. La *Units* være satt til *Celsius*.

    1. Sørg for at *Pin* er satt til *6*.

    1. Velg **Add**-knappen for å opprette temperatursensoren på Pin 6.

    ![Innstillingene for temperatursensoren](../../../../../translated_images/no/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    Temperatursensoren vil bli opprettet og vises i sensorlisten.

    ![Temperatursensoren opprettet](../../../../../translated_images/no/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Programmer temperatursensor-appen

Temperatursensor-appen kan nå programmeres ved hjelp av CounterFit-sensorene.

### Oppgave - programmer temperatursensor-appen

Programmer temperatursensor-appen.

1. Sørg for at `temperature-sensor`-appen er åpen i VS Code.

1. Åpne `app.py`-filen.

1. Legg til følgende kode øverst i `app.py` for å koble appen til CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Legg til følgende kode i `app.py`-filen for å importere de nødvendige bibliotekene:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT`-setningen importerer `DHT`-sensor-klassen for å interagere med en virtuell Grove-temperatursensor ved hjelp av en shim fra `counterfit_shims_seeed_python_dht`-modulen.

1. Legg til følgende kode etter koden ovenfor for å opprette en instans av klassen som administrerer den virtuelle fuktighets- og temperatursensoren:

    ```python
    sensor = DHT("11", 5)
    ```

    Dette erklærer en instans av `DHT`-klassen som administrerer den virtuelle **D**igital **H**umidity og **T**emperature-sensoren. Den første parameteren forteller koden at sensoren som brukes er en virtuell *DHT11*-sensor. Den andre parameteren forteller koden at sensoren er koblet til port `5`.

    > 💁 CounterFit simulerer denne kombinerte fuktighets- og temperatursensoren ved å koble til 2 sensorer, en fuktighetssensor på pinnen som er angitt når `DHT`-klassen opprettes, og en temperatursensor som kjører på neste pin. Hvis fuktighetssensoren er på pin 5, forventer shimmen at temperatursensoren er på pin 6.

1. Legg til en uendelig løkke etter koden ovenfor for å hente verdien fra temperatursensoren og skrive den ut til konsollen:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Kallet til `sensor.read()` returnerer en tuple med fuktighet og temperatur. Du trenger bare temperaturverdien, så fuktigheten ignoreres. Temperaturverdien skrives deretter ut til konsollen.

1. Legg til en liten pause på ti sekunder på slutten av løkken, da temperaturverdiene ikke trenger å sjekkes kontinuerlig. En pause reduserer strømforbruket til enheten.

    ```python
    time.sleep(10)
    ```

1. Fra VS Code-terminalen med et aktivert virtuelt miljø, kjør følgende for å kjøre Python-appen din:

    ```sh
    python app.py
    ```

1. Fra CounterFit-appen, endre verdien til temperatursensoren som vil bli lest av appen. Du kan gjøre dette på to måter:

    * Skriv inn et tall i *Value*-boksen for temperatursensoren, og velg deretter **Set**-knappen. Tallet du skriver inn vil være verdien som returneres av sensoren.

    * Merk av i *Random*-boksen, og skriv inn en *Min*- og *Max*-verdi, og velg deretter **Set**-knappen. Hver gang sensoren leser en verdi, vil den lese et tilfeldig tall mellom *Min* og *Max*.

    Du bør se verdiene du angir vises i konsollen. Endre *Value* eller *Random*-innstillingene for å se verdien endre seg.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Du finner denne koden i [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device)-mappen.

😀 Programmet for temperatursensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.