# Byg en natlampe - Raspberry Pi

I denne del af lektionen vil du tilføje en LED til din Raspberry Pi og bruge den til at skabe en natlampe.

## Hardware

Natlampen har nu brug for en aktuator.

Aktuatoren er en **LED**, en [lysdioder](https://wikipedia.org/wiki/Light-emitting_diode), der udsender lys, når strøm løber igennem den. Dette er en digital aktuator, der har to tilstande: tændt og slukket. Ved at sende en værdi på 1 tændes LED'en, og ved at sende en værdi på 0 slukkes den. LED'en er en ekstern Grove-aktuator og skal tilsluttes Grove Base-hatten på Raspberry Pi.

Natlampens logik i pseudo-kode er:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Tilslut LED'en

Grove LED'en leveres som en modul med et udvalg af LED'er, så du kan vælge farven.

#### Opgave - tilslut LED'en

Tilslut LED'en.

![En Grove LED](../../../../../translated_images/da/grove-led.6c853be93f473cf2.webp)

1. Vælg din foretrukne LED, og indsæt benene i de to huller på LED-modulet.

    LED'er er lysdioder, og dioder er elektroniske komponenter, der kun kan føre strøm i én retning. Det betyder, at LED'en skal tilsluttes korrekt, ellers virker den ikke.

    Et af LED'ens ben er den positive pin, og det andet er den negative pin. LED'en er ikke helt rund og er en smule fladere på den ene side. Den lidt fladere side er den negative pin. Når du tilslutter LED'en til modulet, skal du sørge for, at benet ved den runde side er forbundet til stikket mærket **+** på ydersiden af modulet, og den fladere side er forbundet til stikket tættere på midten af modulet.

1. LED-modulet har en drejeknap, der giver dig mulighed for at justere lysstyrken. Drej denne helt op til at starte med ved at rotere den mod uret så langt som muligt med en lille stjerneskruetrækker.

1. Sæt den ene ende af et Grove-kabel i stikket på LED-modulet. Det kan kun sættes i på én måde.

1. Med Raspberry Pi slukket skal du tilslutte den anden ende af Grove-kablet til det digitale stik mærket **D5** på Grove Base-hatten, der er tilsluttet Pi'en. Dette stik er det andet fra venstre i rækken af stik ved siden af GPIO-pindene.

![Grove LED tilsluttet stik D5](../../../../../translated_images/da/pi-led.97f1d474981dc35d.webp)

## Programmer natlampen

Natlampen kan nu programmeres ved hjælp af Grove-lyssensoren og Grove LED'en.

### Opgave - programmer natlampen

Programmer natlampen.

1. Tænd for Pi'en, og vent på, at den starter op.

1. Åbn natlampeprojektet i VS Code, som du oprettede i den forrige del af denne opgave, enten direkte på Pi'en eller ved hjælp af Remote SSH-udvidelsen.

1. Tilføj følgende kode til `app.py`-filen for at importere et nødvendigt bibliotek. Dette skal tilføjes øverst, under de andre `import`-linjer.

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed`-sætningen importerer `GroveLed` fra Grove Python-bibliotekerne. Dette bibliotek indeholder kode til at interagere med en Grove LED.

1. Tilføj følgende kode efter `light_sensor`-deklarationen for at oprette en instans af klassen, der styrer LED'en:

    ```python
    led = GroveLed(5)
    ```

    Linjen `led = GroveLed(5)` opretter en instans af `GroveLed`-klassen, der forbinder til pin **D5** - den digitale Grove-pin, som LED'en er tilsluttet.

    > 💁 Alle stikkene har unikke pin-numre. Pins 0, 2, 4 og 6 er analoge pins, mens pins 5, 16, 18, 22, 24 og 26 er digitale pins.

1. Tilføj en kontrol inde i `while`-løkken, og før `time.sleep` for at tjekke lysniveauerne og tænde eller slukke LED'en:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Denne kode tjekker værdien `light`. Hvis denne er mindre end 300, kalder den `on`-metoden fra `GroveLed`-klassen, som sender en digital værdi på 1 til LED'en og tænder den. Hvis lysværdien er større end eller lig med 300, kalder den `off`-metoden, som sender en digital værdi på 0 til LED'en og slukker den.

    > 💁 Denne kode skal indrykkes på samme niveau som linjen `print('Light level:', light)` for at være inde i while-løkken!

    > 💁 Når der sendes digitale værdier til aktuatorer, er en værdi på 0 lig med 0V, og en værdi på 1 er den maksimale spænding for enheden. For Raspberry Pi med Grove-sensorer og -aktuatorer er spændingen for 1 3,3V.

1. Fra VS Code-terminalen skal du køre følgende for at køre din Python-app:

    ```sh
    python3 app.py
    ```

    Lysværdier vil blive vist i konsollen.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Dæk og afdæk lyssensoren. Bemærk, hvordan LED'en lyser op, hvis lysniveauet er 300 eller mindre, og slukker, når lysniveauet er større end 300.

    > 💁 Hvis LED'en ikke tænder, skal du sikre dig, at den er tilsluttet korrekt, og at drejeknappen er sat til fuld styrke.

![LED'en tilsluttet Pi'en tænder og slukker, når lysniveauet ændrer sig](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Du kan finde denne kode i [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi)-mappen.

😀 Dit natlampeprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os intet ansvar for misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.