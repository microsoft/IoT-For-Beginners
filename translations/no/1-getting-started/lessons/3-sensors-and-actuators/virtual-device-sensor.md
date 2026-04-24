# Bygg en nattlampe - Virtuell IoT-maskinvare

I denne delen av leksjonen skal du legge til en lyssensor i din virtuelle IoT-enhet.

## Virtuell maskinvare

Nattlampen trenger én sensor, som opprettes i CounterFit-appen.

Sensoren er en **lyssensor**. I en fysisk IoT-enhet ville dette vært en [fotodiode](https://wikipedia.org/wiki/Fotodiode) som konverterer lys til et elektrisk signal. Lyssensorer er analoge sensorer som sender en heltallsverdi som indikerer en relativ mengde lys, uten å være knyttet til noen standard måleenhet som [lux](https://wikipedia.org/wiki/Lux).

### Legg til sensorer i CounterFit

For å bruke en virtuell lyssensor må du legge den til i CounterFit-appen.

#### Oppgave - legg til sensorer i CounterFit

Legg til lyssensoren i CounterFit-appen.

1. Sørg for at CounterFit-nettappen kjører fra forrige del av oppgaven. Hvis ikke, start den.

1. Opprett en lyssensor:

    1. I boksen *Create sensor* i *Sensors*-panelet, åpne rullegardinmenyen *Sensor type* og velg *Light*.

    1. La *Units* stå som *NoUnits*.

    1. Sørg for at *Pin* er satt til *0*.

    1. Velg **Add**-knappen for å opprette lyssensoren på Pin 0.

    ![Innstillingene for lyssensoren](../../../../../translated_images/no/counterfit-create-light-sensor.9f36a5e0d4458d8d.webp)

    Lyssensoren vil bli opprettet og vises i sensorlisten.

    ![Lyssensoren opprettet](../../../../../translated_images/no/counterfit-light-sensor.5d0f5584df56b90f.webp)

## Programmer lyssensoren

Enheten kan nå programmeres til å bruke den innebygde lyssensoren.

### Oppgave - programmer lyssensoren

Programmer enheten.

1. Åpne nattlampe-prosjektet i VS Code som du opprettet i forrige del av oppgaven. Avslutt og opprett terminalen på nytt for å sikre at den kjører med det virtuelle miljøet om nødvendig.

1. Åpne `app.py`-filen.

1. Legg til følgende kode øverst i `app.py`-filen sammen med de andre `import`-setningene for å importere nødvendige biblioteker:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time`-setningen importerer Python-modulen `time`, som vil bli brukt senere i oppgaven.

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor`-setningen importerer `GroveLightSensor` fra CounterFit Grove shim Python-bibliotekene. Dette biblioteket inneholder kode for å samhandle med en lyssensor opprettet i CounterFit-appen.

1. Legg til følgende kode nederst i filen for å opprette instanser av klasser som håndterer lyssensoren:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linjen `light_sensor = GroveLightSensor(0)` oppretter en instans av klassen `GroveLightSensor` som kobles til pin **0** - CounterFit Grove-pinnen som lyssensoren er koblet til.

1. Legg til en uendelig løkke etter koden ovenfor for å hente verdien fra lyssensoren og skrive den ut til konsollen:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Dette vil lese det nåværende lysnivået ved hjelp av egenskapen `light` i klassen `GroveLightSensor`. Denne egenskapen leser den analoge verdien fra pinnen. Denne verdien skrives deretter ut til konsollen.

1. Legg til en liten pause på ett sekund på slutten av `while`-løkka, siden lysnivåene ikke trenger å sjekkes kontinuerlig. En pause reduserer strømforbruket til enheten.

    ```python
    time.sleep(1)
    ```

1. Fra VS Code-terminalen, kjør følgende for å kjøre Python-appen din:

    ```sh
    python3 app.py
    ```

    Lysverdier vil bli skrevet ut til konsollen. Opprinnelig vil denne verdien være 0.

1. Fra CounterFit-appen, endre verdien til lyssensoren som vil bli lest av appen. Du kan gjøre dette på to måter:

    * Skriv inn et tall i *Value*-boksen for lyssensoren, og velg deretter **Set**-knappen. Tallet du skriver inn vil være verdien som sensoren returnerer.

    * Merk av i boksen *Random*, og skriv inn en *Min*- og *Max*-verdi, og velg deretter **Set**-knappen. Hver gang sensoren leser en verdi, vil den lese et tilfeldig tall mellom *Min* og *Max*.

    Verdiene du angir vil bli skrevet ut til konsollen. Endre *Value* eller *Random*-innstillingene for å få verdien til å endre seg.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Du finner denne koden i [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device)-mappen.

😀 Nattlampe-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.