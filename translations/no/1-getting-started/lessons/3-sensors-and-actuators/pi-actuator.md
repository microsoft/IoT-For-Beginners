# Bygg en nattlampe - Raspberry Pi

I denne delen av leksjonen skal du legge til en LED på din Raspberry Pi og bruke den til å lage en nattlampe.

## Maskinvare

Nattlampen trenger nå en aktuator.

Aktuatoren er en **LED**, en [lysdioder](https://wikipedia.org/wiki/Light-emitting_diode) som lyser når strøm går gjennom den. Dette er en digital aktuator som har to tilstander, på og av. Å sende en verdi på 1 slår på LED-en, og 0 slår den av. LED-en er en ekstern Grove-aktuator og må kobles til Grove Base-hatten på Raspberry Pi.

Logikken for nattlampen i pseudokode er:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Koble til LED-en

Grove LED-en kommer som en modul med et utvalg av lysdioder, slik at du kan velge fargen.

#### Oppgave - koble til LED-en

Koble til LED-en.

![En Grove LED](../../../../../translated_images/no/grove-led.6c853be93f473cf2.webp)

1. Velg din favoritt-LED og sett beina inn i de to hullene på LED-modulen.

    Lysdioder er dioder, og dioder er elektroniske komponenter som kun kan føre strøm én vei. Dette betyr at LED-en må kobles riktig vei, ellers vil den ikke fungere.

    Ett av beina på LED-en er den positive pinnen, det andre er den negative pinnen. LED-en er ikke helt rund og er litt flatere på den ene siden. Den litt flatere siden er den negative pinnen. Når du kobler LED-en til modulen, sørg for at pinnen ved den avrundede siden er koblet til kontakten merket **+** på utsiden av modulen, og den flatere siden er koblet til kontakten nærmere midten av modulen.

1. LED-modulen har en dreieknapp som lar deg kontrollere lysstyrken. Skru denne helt opp til å begynne med ved å rotere den mot klokken så langt den går med en liten stjerneskrutrekker.

1. Sett den ene enden av en Grove-kabel inn i kontakten på LED-modulen. Den vil kun gå inn én vei.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til den digitale kontakten merket **D5** på Grove Base-hatten som er festet til Pi-en. Denne kontakten er den andre fra venstre, på raden av kontakter ved siden av GPIO-pinnene.

![Grove LED koblet til kontakt D5](../../../../../translated_images/no/pi-led.97f1d474981dc35d.webp)

## Programmer nattlampen

Nattlampen kan nå programmeres ved hjelp av Grove-lyssensoren og Grove LED-en.

### Oppgave - programmer nattlampen

Programmer nattlampen.

1. Slå på Pi-en og vent til den starter opp.

1. Åpne nattlampe-prosjektet i VS Code som du opprettet i forrige del av denne oppgaven, enten direkte på Pi-en eller ved å bruke Remote SSH-utvidelsen.

1. Legg til følgende kode i `app.py`-filen for å importere et nødvendig bibliotek. Dette skal legges til øverst, under de andre `import`-linjene.

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed`-setningen importerer `GroveLed` fra Grove Python-bibliotekene. Dette biblioteket inneholder kode for å samhandle med en Grove LED.

1. Legg til følgende kode etter `light_sensor`-deklarasjonen for å opprette en instans av klassen som styrer LED-en:

    ```python
    led = GroveLed(5)
    ```

    Linjen `led = GroveLed(5)` oppretter en instans av `GroveLed`-klassen som kobles til pin **D5** - den digitale Grove-pinnen som LED-en er koblet til.

    > 💁 Alle kontaktene har unike pinnummer. Pinnene 0, 2, 4 og 6 er analoge pinner, mens pinnene 5, 16, 18, 22, 24 og 26 er digitale pinner.

1. Legg til en sjekk inne i `while`-løkken, og før `time.sleep`, for å sjekke lysnivåene og slå LED-en av eller på:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Denne koden sjekker `light`-verdien. Hvis denne er mindre enn 300, kaller den `on`-metoden til `GroveLed`-klassen, som sender en digital verdi på 1 til LED-en og slår den på. Hvis lysverdien er større enn eller lik 300, kaller den `off`-metoden, som sender en digital verdi på 0 til LED-en og slår den av.

    > 💁 Denne koden skal ha samme innrykk som linjen `print('Light level:', light)` for å være inne i while-løkken!

    > 💁 Når digitale verdier sendes til aktuatorer, er en verdi på 0 lik 0V, og en verdi på 1 er maksimal spenning for enheten. For Raspberry Pi med Grove-sensorer og -aktuatorer er spenningen for 1 lik 3,3V.

1. Fra VS Code-terminalen, kjør følgende for å kjøre Python-appen din:

    ```sh
    python3 app.py
    ```

    Lysverdier vil bli skrevet ut til konsollen.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Dekk til og avdekk lyssensoren. Legg merke til hvordan LED-en lyser opp hvis lysnivået er 300 eller mindre, og slår seg av når lysnivået er større enn 300.

    > 💁 Hvis LED-en ikke lyser, sørg for at den er koblet riktig vei, og at dreieknappen er satt til full styrke.

![LED-en koblet til Pi-en som slår seg av og på etter lysnivået](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Du finner denne koden i [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi)-mappen.

😀 Nattlampe-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.