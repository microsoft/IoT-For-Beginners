# Bygg en nattlampe - Wio Terminal

I denne delen av leksjonen skal du legge til en LED til din Wio Terminal og bruke den til å lage en nattlampe.

## Maskinvare

Nattlampen trenger nå en aktuator.

Aktuatoren er en **LED**, en [lysdiod](https://wikipedia.org/wiki/Light-emitting_diode) som lyser når strøm går gjennom den. Dette er en digital aktuator som har to tilstander, på og av. Ved å sende en verdi på 1 slår du på LED-en, og 0 slår den av. Dette er en ekstern Grove-aktuator som må kobles til Wio Terminal.

Logikken for nattlampen i pseudokode er:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Koble til LED-en

Grove LED-en kommer som en modul med et utvalg av lysdioder, slik at du kan velge fargen selv.

#### Oppgave - koble til LED-en

Koble til LED-en.

![En Grove LED](../../../../../translated_images/no/grove-led.6c853be93f473cf2.webp)

1. Velg din favoritt-LED og sett bena inn i de to hullene på LED-modulen.

    LED-er er lysdioder, og dioder er elektroniske enheter som kun kan føre strøm én vei. Dette betyr at LED-en må kobles riktig vei, ellers vil den ikke fungere.

    Ett av bena på LED-en er den positive pinnen, det andre er den negative pinnen. LED-en er ikke helt rund og er litt flatere på den ene siden. Den litt flatere siden er den negative pinnen. Når du kobler LED-en til modulen, må du sørge for at pinnen ved den avrundede siden er koblet til kontakten merket **+** på utsiden av modulen, og den flatere siden er koblet til kontakten nærmere midten av modulen.

1. LED-modulen har en dreieknapp som lar deg kontrollere lysstyrken. Skru denne helt opp til å begynne med ved å rotere den mot klokken så langt den går med en liten stjerneskrutrekker.

1. Sett den ene enden av en Grove-kabel inn i kontakten på LED-modulen. Den vil kun gå inn én vei.

1. Med Wio Terminal frakoblet fra datamaskinen eller annen strømkilde, koble den andre enden av Grove-kabelen til den høyre Grove-kontakten på Wio Terminal når du ser på skjermen. Dette er kontakten lengst unna strømknappen.

    > 💁 Den høyre Grove-kontakten kan brukes med analoge eller digitale sensorer og aktuatorer. Den venstre kontakten er kun for I2C og digitale sensorer og aktuatorer.

![Grove LED koblet til den høyre kontakten](../../../../../translated_images/no/wio-led.265a1897e72d7f21.webp)

## Programmer nattlampen

Nattlampen kan nå programmeres ved hjelp av den innebygde lyssensoren og Grove LED-en.

### Oppgave - programmer nattlampen

Programmer nattlampen.

1. Åpne nattlampe-prosjektet i VS Code som du opprettet i den forrige delen av oppgaven.

1. Legg til følgende linje nederst i `setup`-funksjonen:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Denne linjen konfigurerer pinnen som brukes til å kommunisere med LED-en via Grove-porten.

    `D0`-pinnen er den digitale pinnen for den høyre Grove-kontakten. Denne pinnen settes til `OUTPUT`, som betyr at den kobles til en aktuator og data vil bli skrevet til pinnen.

1. Legg til følgende kode rett før `delay` i loop-funksjonen:

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

    Denne koden sjekker `light`-verdien. Hvis denne er mindre enn 300, sender den en `HIGH`-verdi til den digitale pinnen `D0`. Denne `HIGH`-verdien er 1, som slår på LED-en. Hvis lysnivået er større enn eller lik 300, sendes en `LOW`-verdi på 0 til pinnen, som slår av LED-en.

    > 💁 Når du sender digitale verdier til aktuatorer, er en LOW-verdi 0V, og en HIGH-verdi er maksimal spenning for enheten. For Wio Terminal er den HIGH-spenningen 3.3V.

1. Koble Wio Terminal til datamaskinen igjen, og last opp den nye koden slik du gjorde tidligere.

1. Koble til Serial Monitor. Lysverdier vil bli skrevet ut til terminalen.

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

1. Dekk til og avdekk lyssensoren. Legg merke til hvordan LED-en lyser opp hvis lysnivået er 300 eller mindre, og slår seg av når lysnivået er større enn 300.

![LED-en koblet til Wio som slår seg av og på etter lysnivået](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Du finner denne koden i [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal)-mappen.

😀 Nattlampe-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.