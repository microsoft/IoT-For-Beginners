<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T20:31:24+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "no"
}
-->
# Oppdag nærhet - Raspberry Pi

I denne delen av leksjonen skal du legge til en nærhetssensor på din Raspberry Pi og lese avstand fra den.

## Maskinvare

Raspberry Pi trenger en nærhetssensor.

Sensoren du skal bruke er en [Grove Time of Flight avstandssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Denne sensoren bruker en laseravstandsmåler for å oppdage avstand. Sensoren har en rekkevidde fra 10mm til 2000mm (1cm - 2m) og rapporterer verdier innenfor dette området ganske nøyaktig, med avstander over 1000mm rapportert som 8109mm.

Laseravstandsmåleren er på baksiden av sensoren, motsatt side av Grove-kontakten.

Dette er en I²C-sensor.

### Koble til Time of Flight-sensoren

Grove Time of Flight-sensoren kan kobles til Raspberry Pi.

#### Oppgave - koble til Time of Flight-sensoren

Koble til Time of Flight-sensoren.

![En Grove Time of Flight-sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.no.png)

1. Sett den ene enden av en Grove-kabel inn i kontakten på Time of Flight-sensoren. Den vil kun passe én vei.

1. Med Raspberry Pi slått av, koble den andre enden av Grove-kabelen til en av I²C-kontaktene merket **I²C** på Grove Base-hatten som er festet til Pi. Disse kontaktene er på nederste rad, motsatt ende av GPIO-pinnene og ved siden av kamerakabelsporet.

![Grove Time of Flight-sensor koblet til I²C-kontakten](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57.no.png)

## Programmer Time of Flight-sensoren

Raspberry Pi kan nå programmeres til å bruke den tilkoblede Time of Flight-sensoren.

### Oppgave - programmer Time of Flight-sensoren

Programmer enheten.

1. Slå på Pi og vent til den starter opp.

1. Åpne `fruit-quality-detector`-koden i VS Code, enten direkte på Pi eller ved å koble til via Remote SSH-utvidelsen.

1. Installer rpi-vl53l0x Pip-pakken, en Python-pakke som interagerer med en VL53L0X Time of Flight-avstandssensor. Installer den ved å bruke denne pip-kommandoen:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Opprett en ny fil i dette prosjektet kalt `distance-sensor.py`.

    > 💁 En enkel måte å simulere flere IoT-enheter på er å gjøre hver enhet i en egen Python-fil og deretter kjøre dem samtidig.

1. Legg til følgende kode i denne filen:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dette importerer Grove I²C-biblioteket og et sensorbibliotek for kjernesensoren som er innebygd i Grove Time of Flight-sensoren.

1. Under dette, legg til følgende kode for å få tilgang til sensoren:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Denne koden erklærer en avstandssensor ved hjelp av Grove I²C-bussen og starter sensoren.

1. Til slutt, legg til en uendelig løkke for å lese avstander:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Denne koden venter på at en verdi skal være klar til å leses fra sensoren og skriver den deretter ut til konsollen.

1. Kjør denne koden.

    > 💁 Husk at denne filen heter `distance-sensor.py`! Sørg for å kjøre den via Python, ikke `app.py`.

1. Du vil se avstandsmålinger vises i konsollen. Plasser objekter nær sensoren, og du vil se avstandsmålingen:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Avstandsmåleren er på baksiden av sensoren, så sørg for å bruke riktig side når du måler avstand.

    ![Avstandsmåleren på baksiden av Time of Flight-sensoren peker mot en banan](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.no.png)

> 💁 Du finner denne koden i [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi)-mappen.

😀 Programmet for nærhetssensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.