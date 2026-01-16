<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:11:01+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "da"
}
-->
# Tilføj en sensor - Wio Terminal

I denne del af lektionen vil du bruge lyssensoren på din Wio Terminal.

## Hardware

Sensoren til denne lektion er en **lyssensor**, der bruger en [fotodiode](https://wikipedia.org/wiki/Photodiode) til at omdanne lys til et elektrisk signal. Dette er en analog sensor, der sender en heltalsværdi fra 0 til 1.023, som angiver en relativ mængde lys, der ikke svarer til nogen standard måleenhed som [lux](https://wikipedia.org/wiki/Lux).

Lyssensoren er indbygget i Wio Terminal og er synlig gennem det klare plastvindue på bagsiden.

![Lyssensoren på bagsiden af Wio Terminal](../../../../../translated_images/da/wio-light-sensor.b1f529f3c95f5165.png)

## Programmer lyssensoren

Enheden kan nu programmeres til at bruge den indbyggede lyssensor.

### Opgave

Programmer enheden.

1. Åbn natlyset-projektet i VS Code, som du oprettede i den tidligere del af denne opgave.

1. Tilføj følgende linje nederst i `setup`-funktionen:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Denne linje konfigurerer de pins, der bruges til at kommunikere med sensorens hardware.

    `WIO_LIGHT`-pinnen er nummeret på GPIO-pinnen, der er forbundet til den indbyggede lyssensor. Denne pin er sat til `INPUT`, hvilket betyder, at den er forbundet til en sensor, og data vil blive læst fra pinnen.

1. Slet indholdet af `loop`-funktionen.

1. Tilføj følgende kode til den nu tomme `loop`-funktion.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Denne kode læser en analog værdi fra `WIO_LIGHT`-pinnen. Den læser en værdi fra 0-1.023 fra den indbyggede lyssensor. Denne værdi sendes derefter til den serielle port, så du kan læse den i Serial Monitor, når denne kode kører. `Serial.print` skriver teksten uden en ny linje i slutningen, så hver linje starter med `Light value:` og slutter med den faktiske lysværdi.

1. Tilføj en lille forsinkelse på et sekund (1.000ms) i slutningen af `loop`, da lysniveauerne ikke behøver at blive kontrolleret kontinuerligt. En forsinkelse reducerer enhedens strømforbrug.

    ```cpp
    delay(1000);
    ```

1. Tilslut Wio Terminal til din computer igen, og upload den nye kode, som du gjorde før.

1. Tilslut Serial Monitor. Lysværdier vil blive output til terminalen. Dæk og afdæk lyssensoren på bagsiden af Wio Terminal, og værdierne vil ændre sig.

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

> 💁 Du kan finde denne kode i [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal)-mappen.

😀 Det var en succes at tilføje en sensor til dit natlyset-program!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.