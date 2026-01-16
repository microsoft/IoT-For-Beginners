<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-27T22:11:14+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "no"
}
-->
# Legg til en sensor - Wio Terminal

I denne delen av leksjonen skal du bruke lyssensoren på din Wio Terminal.

## Maskinvare

Sensoren for denne leksjonen er en **lyssensor** som bruker en [fotodiode](https://wikipedia.org/wiki/Photodiode) til å konvertere lys til et elektrisk signal. Dette er en analog sensor som sender en heltallsverdi fra 0 til 1 023, som indikerer en relativ mengde lys. Denne verdien tilsvarer ingen standard måleenhet som for eksempel [lux](https://wikipedia.org/wiki/Lux).

Lyssensoren er innebygd i Wio Terminal og er synlig gjennom det klare plastvinduet på baksiden.

![Lyssensoren på baksiden av Wio Terminal](../../../../../translated_images/no/wio-light-sensor.b1f529f3c95f5165.png)

## Programmer lyssensoren

Enheten kan nå programmeres til å bruke den innebygde lyssensoren.

### Oppgave

Programmer enheten.

1. Åpne nattlysprosjektet i VS Code som du opprettet i forrige del av denne oppgaven.

1. Legg til følgende linje nederst i `setup`-funksjonen:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Denne linjen konfigurerer pinnene som brukes til å kommunisere med sensorens maskinvare.

    `WIO_LIGHT`-pinnen er nummeret på GPIO-pinnen som er koblet til den innebygde lyssensoren. Denne pinnen settes til `INPUT`, noe som betyr at den kobles til en sensor og data vil bli lest fra pinnen.

1. Slett innholdet i `loop`-funksjonen.

1. Legg til følgende kode i den nå tomme `loop`-funksjonen.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Denne koden leser en analog verdi fra `WIO_LIGHT`-pinnen. Dette leser en verdi fra 0-1 023 fra den innebygde lyssensoren. Denne verdien sendes deretter til seriellporten slik at du kan lese den i Serial Monitor når denne koden kjører. `Serial.print` skriver teksten uten en ny linje på slutten, så hver linje vil starte med `Light value:` og avsluttes med den faktiske lysverdien.

1. Legg til en liten forsinkelse på ett sekund (1 000 ms) på slutten av `loop`, siden lysnivåene ikke trenger å sjekkes kontinuerlig. En forsinkelse reduserer strømforbruket til enheten.

    ```cpp
    delay(1000);
    ```

1. Koble Wio Terminal til datamaskinen din igjen, og last opp den nye koden slik du gjorde tidligere.

1. Koble til Serial Monitor. Lysverdier vil bli skrevet ut til terminalen. Dekk til og avdekk lyssensoren på baksiden av Wio Terminal, og verdiene vil endre seg.

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

> 💁 Du finner denne koden i [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal)-mappen.

😀 Å legge til en sensor i nattlysprogrammet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.