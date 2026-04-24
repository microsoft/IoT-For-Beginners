# Registrer nærhed - Virtuel IoT-hardware

I denne del af lektionen vil du tilføje en nærhedssensor til din virtuelle IoT-enhed og aflæse afstand fra den.

## Hardware

Den virtuelle IoT-enhed vil bruge en simuleret afstandssensor.

På en fysisk IoT-enhed ville du bruge en sensor med et laserafstandsmålemodul til at registrere afstand.

### Tilføj afstandssensoren til CounterFit

For at bruge en virtuel afstandssensor skal du tilføje en til CounterFit-appen.

#### Opgave - tilføj afstandssensoren til CounterFit

Tilføj afstandssensoren til CounterFit-appen.

1. Åbn koden `fruit-quality-detector` i VS Code, og sørg for, at det virtuelle miljø er aktiveret.

1. Installer en ekstra Pip-pakke for at installere en CounterFit shim, der kan kommunikere med afstandssensorer ved at simulere [rpi-vl53l0x Pip-pakken](https://pypi.org/project/rpi-vl53l0x/), en Python-pakke, der interagerer med [en VL53L0X time-of-flight afstandssensor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Sørg for at installere denne fra en terminal med det virtuelle miljø aktiveret.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Sørg for, at CounterFit-webappen kører.

1. Opret en afstandssensor:

    1. I boksen *Create sensor* i panelet *Sensors*, vælg *Distance* i rullemenuen *Sensor type*.

    1. Lad *Units* stå som `Millimeter`.

    1. Denne sensor er en I²C-sensor, så sæt adressen til `0x29`. Hvis du brugte en fysisk VL53L0X-sensor, ville den være hardkodet til denne adresse.

    1. Vælg knappen **Add** for at oprette afstandssensoren.

    ![Indstillinger for afstandssensoren](../../../../../translated_images/da/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Afstandssensoren vil blive oprettet og vises i sensorlisten.

    ![Afstandssensoren oprettet](../../../../../translated_images/da/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Programmer afstandssensoren

Den virtuelle IoT-enhed kan nu programmeres til at bruge den simulerede afstandssensor.

### Opgave - programmer time-of-flight-sensoren

1. Opret en ny fil i projektet `fruit-quality-detector` kaldet `distance-sensor.py`.

    > 💁 En nem måde at simulere flere IoT-enheder på er at gøre det i forskellige Python-filer og derefter køre dem samtidig.

1. Start en forbindelse til CounterFit med følgende kode:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Tilføj følgende kode nedenunder:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dette importerer sensorbibliotekets shim til VL53L0X time-of-flight-sensoren.

1. Tilføj derefter følgende kode for at få adgang til sensoren:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Denne kode erklærer en afstandssensor og starter derefter sensoren.

1. Til sidst tilføj en uendelig løkke for at aflæse afstande:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Denne kode venter på, at en værdi er klar til at blive aflæst fra sensoren, og udskriver den derefter til konsollen.

1. Kør denne kode.

    > 💁 Husk, at denne fil hedder `distance-sensor.py`! Sørg for at køre den via Python og ikke `app.py`.

1. Du vil se afstandsmålinger vises i konsollen. Ændr værdien i CounterFit for at se denne værdi ændre sig, eller brug tilfældige værdier.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Du kan finde denne kode i mappen [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Dit program til nærhedssensoren var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at sikre nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.