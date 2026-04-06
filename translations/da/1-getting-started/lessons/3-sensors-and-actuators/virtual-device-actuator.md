# Byg en natlampe - Virtuel IoT-hardware

I denne del af lektionen vil du tilføje en LED til din virtuelle IoT-enhed og bruge den til at skabe en natlampe.

## Virtuel hardware

Natlampen kræver én aktuator, som oprettes i CounterFit-appen.

Aktuatoren er en **LED**. På en fysisk IoT-enhed ville det være en [lysdiod](https://wikipedia.org/wiki/Light-emitting_diode), der udsender lys, når strøm løber igennem den. Dette er en digital aktuator, der har to tilstande: tændt og slukket. Hvis du sender en værdi på 1, tændes LED'en, og hvis du sender en værdi på 0, slukkes den.

Natlampens logik i pseudo-kode er:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Tilføj aktuatoren til CounterFit

For at bruge en virtuel LED skal du tilføje den til CounterFit-appen.

#### Opgave - tilføj aktuatoren til CounterFit

Tilføj LED'en til CounterFit-appen.

1. Sørg for, at CounterFit-webappen kører fra den tidligere del af denne opgave. Hvis ikke, start den og tilføj lyssensoren igen.

1. Opret en LED:

    1. I boksen *Create actuator* i panelet *Actuator*, klik på rullemenuen *Actuator type* og vælg *LED*.

    1. Sæt *Pin* til *5*.

    1. Vælg knappen **Add** for at oprette LED'en på Pin 5.

    ![LED-indstillingerne](../../../../../translated_images/da/counterfit-create-led.ba9db1c9b8c622a6.webp)

    LED'en vil blive oprettet og vises i listen over aktuatorer.

    ![LED'en oprettet](../../../../../translated_images/da/counterfit-led.c0ab02de6d256ad8.webp)

    Når LED'en er oprettet, kan du ændre farven ved hjælp af *Color*-vælgeren. Vælg knappen **Set** for at ændre farven, efter du har valgt den.

### Programmer natlampen

Natlampen kan nu programmeres ved hjælp af CounterFit-lyssensoren og LED'en.

#### Opgave - programmer natlampen

Programmer natlampen.

1. Åbn natlampeprojektet i VS Code, som du oprettede i den tidligere del af denne opgave. Luk og genopret terminalen for at sikre, at den kører med det virtuelle miljø, hvis nødvendigt.

1. Åbn filen `app.py`.

1. Tilføj følgende kode til filen `app.py` for at importere et nødvendigt bibliotek. Dette skal tilføjes øverst, under de andre `import`-linjer.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Sætningen `from counterfit_shims_grove.grove_led import GroveLed` importerer `GroveLed` fra CounterFit Grove shim Python-bibliotekerne. Dette bibliotek indeholder kode til at interagere med en LED, der er oprettet i CounterFit-appen.

1. Tilføj følgende kode efter `light_sensor`-deklarationen for at oprette en instans af klassen, der styrer LED'en:

    ```python
    led = GroveLed(5)
    ```

    Linjen `led = GroveLed(5)` opretter en instans af klassen `GroveLed`, der forbinder til pin **5** - CounterFit Grove-pinnen, som LED'en er tilsluttet.

1. Tilføj en kontrol inde i `while`-løkken og før `time.sleep` for at kontrollere lysniveauerne og tænde eller slukke LED'en:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Denne kode kontrollerer værdien `light`. Hvis denne er mindre end 300, kalder den metoden `on` fra klassen `GroveLed`, som sender en digital værdi på 1 til LED'en og tænder den. Hvis lysværdien er større end eller lig med 300, kalder den metoden `off`, som sender en digital værdi på 0 til LED'en og slukker den.

    > 💁 Denne kode skal indrykkes på samme niveau som linjen `print('Light level:', light)` for at være inde i while-løkken!

1. Fra VS Code-terminalen skal du køre følgende for at køre din Python-app:

    ```sh
    python3 app.py
    ```

    Lysværdier vil blive vist i konsollen.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Ændr indstillingen *Value* eller *Random* for at variere lysniveauet over og under 300. LED'en vil tænde og slukke.

![LED'en i CounterFit-appen tænder og slukker, når lysniveauet ændrer sig](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Du kan finde denne kode i mappen [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Dit natlampeprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.