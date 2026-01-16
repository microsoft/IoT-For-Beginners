<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-27T22:08:37+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "no"
}
-->
# Bygg en nattlampe - Raspberry Pi

I denne delen av leksjonen skal du legge til en lyssensor på din Raspberry Pi.

## Maskinvare

Sensoren for denne leksjonen er en **lyssensor** som bruker en [fotodiode](https://wikipedia.org/wiki/Photodiode) til å konvertere lys til et elektrisk signal. Dette er en analog sensor som sender en heltallsverdi fra 0 til 1 000 som indikerer en relativ mengde lys, men som ikke tilsvarer noen standard måleenhet som [lux](https://wikipedia.org/wiki/Lux).

Lyssensoren er en ekstern Grove-sensor og må kobles til Grove Base-hatten på Raspberry Pi.

### Koble til lyssensoren

Grove-lyssensoren som brukes til å måle lysnivåene må kobles til Raspberry Pi.

#### Oppgave - koble til lyssensoren

Koble til lyssensoren

![En Grove-lyssensor](../../../../../translated_images/no/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på lyssensormodulen. Den vil kun passe én vei.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til den analoge kontakten merket **A0** på Grove Base-hatten som er festet til Pi. Denne kontakten er den andre fra høyre, på raden av kontakter ved siden av GPIO-pinnene.

![Grove-lyssensoren koblet til kontakten A0](../../../../../translated_images/no/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Programmer lyssensoren

Enheten kan nå programmeres ved hjelp av Grove-lyssensoren.

### Oppgave - programmer lyssensoren

Programmer enheten.

1. Slå på Pi og vent til den starter opp.

1. Åpne nattlampe-prosjektet i VS Code som du opprettet i den forrige delen av oppgaven, enten direkte på Pi eller ved å bruke Remote SSH-utvidelsen.

1. Åpne `app.py`-filen og fjern all kode fra den.

1. Legg til følgende kode i `app.py`-filen for å importere noen nødvendige biblioteker:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time`-setningen importerer `time`-modulen som vil bli brukt senere i denne oppgaven.

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor`-setningen importerer `GroveLightSensor` fra Grove Python-bibliotekene. Dette biblioteket inneholder kode for å interagere med en Grove-lyssensor, og ble installert globalt under Pi-oppsettet.

1. Legg til følgende kode etter koden ovenfor for å opprette en instans av klassen som styrer lyssensoren:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linjen `light_sensor = GroveLightSensor(0)` oppretter en instans av `GroveLightSensor`-klassen som kobler til pin **A0** - den analoge Grove-pinnen som lyssensoren er koblet til.

1. Legg til en uendelig løkke etter koden ovenfor for å hente verdien fra lyssensoren og skrive den ut til konsollen:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    Dette vil lese det nåværende lysnivået på en skala fra 0-1 023 ved hjelp av `light`-egenskapen til `GroveLightSensor`-klassen. Denne egenskapen leser den analoge verdien fra pinnen. Verdien skrives deretter ut til konsollen.

1. Legg til en kort pause på ett sekund på slutten av `loop`, siden lysnivåene ikke trenger å sjekkes kontinuerlig. En pause reduserer strømforbruket til enheten.

    ```python
    time.sleep(1)
    ```

1. Fra VS Code-terminalen, kjør følgende for å kjøre Python-appen din:

    ```sh
    python3 app.py
    ```

    Lysverdier vil bli skrevet ut til konsollen. Dekk til og avdekk lyssensoren, og verdiene vil endre seg:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Du finner denne koden i [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi)-mappen.

😀 Å legge til en sensor i nattlampe-programmet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.