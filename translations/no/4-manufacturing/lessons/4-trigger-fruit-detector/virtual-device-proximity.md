<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T20:33:29+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "no"
}
-->
# Oppdag nærhet - Virtuell IoT-maskinvare

I denne delen av leksjonen skal du legge til en nærhetssensor på din virtuelle IoT-enhet og lese avstand fra den.

## Maskinvare

Den virtuelle IoT-enheten vil bruke en simulert avstandssensor.

På en fysisk IoT-enhet ville du brukt en sensor med et laserbasert målingsmodul for å oppdage avstand.

### Legg til avstandssensoren i CounterFit

For å bruke en virtuell avstandssensor, må du legge til en i CounterFit-appen.

#### Oppgave - legg til avstandssensoren i CounterFit

Legg til avstandssensoren i CounterFit-appen.

1. Åpne koden `fruit-quality-detector` i VS Code, og sørg for at det virtuelle miljøet er aktivert.

1. Installer en ekstra Pip-pakke for å installere en CounterFit shim som kan kommunisere med avstandssensorer ved å simulere [rpi-vl53l0x Pip-pakken](https://pypi.org/project/rpi-vl53l0x/), en Python-pakke som interagerer med [en VL53L0X time-of-flight avstandssensor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Sørg for at du installerer dette fra en terminal med det virtuelle miljøet aktivert.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Sørg for at CounterFit-nettappen kjører.

1. Opprett en avstandssensor:

    1. I boksen *Create sensor* i *Sensors*-panelet, åpne rullegardinmenyen *Sensor type* og velg *Distance*.

    1. La *Units* stå som `Millimeter`.

    1. Denne sensoren er en I²C-sensor, så sett adressen til `0x29`. Hvis du brukte en fysisk VL53L0X-sensor, ville den vært hardkodet til denne adressen.

    1. Velg **Add**-knappen for å opprette avstandssensoren.

    ![Innstillingene for avstandssensoren](../../../../../translated_images/no/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Avstandssensoren vil bli opprettet og vises i sensorlisten.

    ![Avstandssensoren opprettet](../../../../../translated_images/no/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Programmer avstandssensoren

Den virtuelle IoT-enheten kan nå programmeres til å bruke den simulerte avstandssensoren.

### Oppgave - programmer time-of-flight-sensoren

1. Opprett en ny fil i prosjektet `fruit-quality-detector` kalt `distance-sensor.py`.

    > 💁 En enkel måte å simulere flere IoT-enheter på er å gjøre hver enhet i en egen Python-fil, og deretter kjøre dem samtidig.

1. Start en tilkobling til CounterFit med følgende kode:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Legg til følgende kode under dette:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dette importerer sensorbiblioteket shim for VL53L0X time-of-flight-sensoren.

1. Under dette, legg til følgende kode for å få tilgang til sensoren:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Denne koden erklærer en avstandssensor og starter sensoren.

1. Til slutt, legg til en uendelig løkke for å lese avstander:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Denne koden venter på at en verdi skal være klar til å leses fra sensoren, og skriver den deretter ut til konsollen.

1. Kjør denne koden.

    > 💁 Husk at denne filen heter `distance-sensor.py`! Sørg for å kjøre den via Python, ikke `app.py`.

1. Du vil se avstandsmålinger vises i konsollen. Endre verdien i CounterFit for å se denne verdien endre seg, eller bruk tilfeldige verdier.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Du finner denne koden i mappen [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Programmet for nærhetssensoren din var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.