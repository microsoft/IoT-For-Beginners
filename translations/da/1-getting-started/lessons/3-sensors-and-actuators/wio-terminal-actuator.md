# Byg en natlampe - Wio Terminal

I denne del af lektionen vil du tilføje en LED til din Wio Terminal og bruge den til at lave en natlampe.

## Hardware

Natlampen har nu brug for en aktuator.

Aktuatoren er en **LED**, en [lysemitterende diode](https://wikipedia.org/wiki/Light-emitting_diode), der udsender lys, når strøm løber igennem den. Dette er en digital aktuator, der har to tilstande: tændt og slukket. Hvis du sender en værdi på 1, tændes LED'en, og hvis du sender en værdi på 0, slukkes den. Dette er en ekstern Grove-aktuator, som skal tilsluttes Wio Terminal.

Logikken for natlampen i pseudokode er:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Tilslut LED'en

Grove LED'en kommer som en modul med et udvalg af LED'er, så du kan vælge farven.

#### Opgave - tilslut LED'en

Tilslut LED'en.

![En Grove LED](../../../../../translated_images/da/grove-led.6c853be93f473cf2.webp)

1. Vælg din favorit LED og indsæt benene i de to huller på LED-modulet.

    LED'er er lysemitterende dioder, og dioder er elektroniske komponenter, der kun kan føre strøm i én retning. Det betyder, at LED'en skal tilsluttes korrekt, ellers virker den ikke.

    Et af benene på LED'en er den positive pin, og det andet er den negative pin. LED'en er ikke helt rund og er lidt fladere på den ene side. Den lidt fladere side er den negative pin. Når du tilslutter LED'en til modulet, skal du sørge for, at benet ved den runde side er tilsluttet stikket markeret med **+** på ydersiden af modulet, og den fladere side er tilsluttet stikket tættere på midten af modulet.

1. LED-modulet har en drejeknap, der giver dig mulighed for at kontrollere lysstyrken. Drej denne helt op til at starte med ved at rotere den mod uret så langt som muligt med en lille stjerneskruetrækker.

1. Indsæt den ene ende af et Grove-kabel i stikket på LED-modulet. Det kan kun indsættes på én måde.

1. Med Wio Terminal frakoblet fra din computer eller anden strømkilde, tilslut den anden ende af Grove-kablet til det højre Grove-stik på Wio Terminal, når du ser på skærmen. Dette er stikket længst væk fra tænd/sluk-knappen.

    > 💁 Det højre Grove-stik kan bruges med analoge eller digitale sensorer og aktuatorer. Det venstre stik er kun til digitale sensorer og aktuatorer. C vil blive dækket i en senere lektion.

![Grove LED tilsluttet det højre stik](../../../../../translated_images/da/wio-led.265a1897e72d7f21.webp)

## Programmer natlampen

Natlampen kan nu programmeres ved hjælp af den indbyggede lyssensor og Grove LED'en.

### Opgave - programmer natlampen

Programmer natlampen.

1. Åbn natlampeprojektet i VS Code, som du oprettede i den tidligere del af denne opgave.

1. Tilføj følgende linje nederst i `setup`-funktionen:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Denne linje konfigurerer den pin, der bruges til at kommunikere med LED'en via Grove-porten.

    `D0`-pinnen er den digitale pin for det højre Grove-stik. Denne pin er sat til `OUTPUT`, hvilket betyder, at den er forbundet til en aktuator, og data vil blive skrevet til pinnen.

1. Tilføj følgende kode umiddelbart før `delay` i loop-funktionen:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Denne kode kontrollerer `light`-værdien. Hvis denne er mindre end 300, sendes en `HIGH`-værdi til den digitale pin `D0`. Denne `HIGH` er en værdi på 1, som tænder LED'en. Hvis lyset er større end eller lig med 300, sendes en `LOW`-værdi på 0 til pinnen, hvilket slukker LED'en.

    > 💁 Når der sendes digitale værdier til aktuatorer, er en LOW-værdi 0v, og en HIGH-værdi er den maksimale spænding for enheden. For Wio Terminal er den høje spænding 3.3V.

1. Tilslut Wio Terminal til din computer igen, og upload den nye kode, som du gjorde før.

1. Tilslut Serial Monitor. Lysværdier vil blive vist i terminalen.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Dæk og afdæk lyssensoren. Bemærk, hvordan LED'en lyser op, hvis lysniveauet er 300 eller mindre, og slukker, når lysniveauet er større end 300.

![LED'en tilsluttet Wio Terminal tænder og slukker, når lysniveauet ændrer sig](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Du kan finde denne kode i [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal)-mappen.

😀 Dit natlampeprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der opstår som følge af brugen af denne oversættelse.