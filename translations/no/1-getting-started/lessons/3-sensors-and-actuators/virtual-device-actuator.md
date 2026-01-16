<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-27T22:06:46+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "no"
}
-->
# Bygg en nattlampe - Virtuell IoT-maskinvare

I denne delen av leksjonen skal du legge til en LED på din virtuelle IoT-enhet og bruke den til å lage en nattlampe.

## Virtuell maskinvare

Nattlampen trenger én aktuator, opprettet i CounterFit-appen.

Aktuatoren er en **LED**. På en fysisk IoT-enhet ville dette vært en [lysdiod](https://wikipedia.org/wiki/Light-emitting_diode) som lyser når strøm går gjennom den. Dette er en digital aktuator som har to tilstander, på og av. Å sende verdien 1 slår LED-en på, og 0 slår den av.

Logikken for nattlampen i pseudokode er:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Legg til aktuatoren i CounterFit

For å bruke en virtuell LED må du legge den til i CounterFit-appen.

#### Oppgave - legg til aktuatoren i CounterFit

Legg til LED-en i CounterFit-appen.

1. Sørg for at CounterFit-nettappen kjører fra forrige del av oppgaven. Hvis ikke, start den og legg til lyssensoren på nytt.

1. Opprett en LED:

    1. I boksen *Create actuator* i *Actuator*-panelet, åpne rullegardinmenyen *Actuator type* og velg *LED*.

    1. Sett *Pin* til *5*.

    1. Velg **Add**-knappen for å opprette LED-en på Pin 5.

    ![LED-innstillingene](../../../../../translated_images/no/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LED-en vil bli opprettet og vises i listen over aktuatorer.

    ![LED-en opprettet](../../../../../translated_images/no/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Når LED-en er opprettet, kan du endre fargen ved hjelp av *Color*-velgeren. Velg **Set**-knappen for å endre fargen etter at du har valgt den.

### Programmer nattlampen

Nattlampen kan nå programmeres ved hjelp av CounterFit-lyssensoren og LED-en.

#### Oppgave - programmer nattlampen

Programmer nattlampen.

1. Åpne nattlampe-prosjektet i VS Code som du opprettet i forrige del av oppgaven. Avslutt og opprett terminalen på nytt for å sikre at den kjører med det virtuelle miljøet hvis nødvendig.

1. Åpne `app.py`-filen.

1. Legg til følgende kode i `app.py`-filen for å importere et nødvendig bibliotek. Dette skal legges til øverst, under de andre `import`-linjene.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Setningen `from counterfit_shims_grove.grove_led import GroveLed` importerer `GroveLed` fra CounterFit Grove shim Python-bibliotekene. Dette biblioteket inneholder kode for å interagere med en LED opprettet i CounterFit-appen.

1. Legg til følgende kode etter `light_sensor`-deklarasjonen for å opprette en instans av klassen som styrer LED-en:

    ```python
    led = GroveLed(5)
    ```

    Linjen `led = GroveLed(5)` oppretter en instans av `GroveLed`-klassen som kobler til pin **5** - CounterFit Grove-pinnen som LED-en er koblet til.

1. Legg til en sjekk inne i `while`-løkka, og før `time.sleep`, for å sjekke lysnivåene og slå LED-en av eller på:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Denne koden sjekker `light`-verdien. Hvis denne er mindre enn 300, kaller den `on`-metoden til `GroveLed`-klassen, som sender en digital verdi på 1 til LED-en og slår den på. Hvis lysverdien er større enn eller lik 300, kaller den `off`-metoden, som sender en digital verdi på 0 til LED-en og slår den av.

    > 💁 Denne koden skal være innrykket på samme nivå som linjen `print('Light level:', light)` for å være inne i while-løkka!

1. Fra VS Code-terminalen, kjør følgende for å kjøre Python-appen din:

    ```sh
    python3 app.py
    ```

    Lysverdier vil bli skrevet ut til konsollen.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Endre *Value* eller *Random*-innstillingene for å variere lysnivået over og under 300. LED-en vil slå seg av og på.

![LED-en i CounterFit-appen som slår seg av og på når lysnivået endres](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Du finner denne koden i [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device)-mappen.

😀 Nattlampe-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.