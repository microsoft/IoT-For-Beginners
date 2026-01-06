<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T20:31:08+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "da"
}
-->
# Registrer nærhed - Raspberry Pi

I denne del af lektionen vil du tilføje en nærhedssensor til din Raspberry Pi og aflæse afstande fra den.

## Hardware

Raspberry Pi'en har brug for en nærhedssensor.

Den sensor, du skal bruge, er en [Grove Time of Flight afstandssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Denne sensor bruger et laserafstandsmåler-modul til at registrere afstand. Sensoren har en rækkevidde fra 10 mm til 2000 mm (1 cm - 2 m) og rapporterer værdier inden for dette område ret præcist, hvor afstande over 1000 mm rapporteres som 8109 mm.

Laserafstandsmåleren sidder på bagsiden af sensoren, modsat siden med Grove-stikket.

Dette er en I²C-sensor.

### Tilslut time of flight-sensoren

Grove time of flight-sensoren kan tilsluttes Raspberry Pi'en.

#### Opgave - tilslut time of flight-sensoren

Tilslut time of flight-sensoren.

![En Grove time of flight-sensor](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.da.png)

1. Sæt den ene ende af et Grove-kabel i stikket på time of flight-sensoren. Det kan kun sættes i på én måde.

1. Med Raspberry Pi'en slukket, tilslut den anden ende af Grove-kablet til en af I²C-stikkene markeret **I²C** på Grove Base-hatten, der er tilsluttet Pi'en. Disse stik er på den nederste række, i den modsatte ende af GPIO-pindene og ved siden af kamera-kabelslottet.

![Grove time of flight-sensoren tilsluttet I²C-stikket](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57.da.png)

## Programmer time of flight-sensoren

Raspberry Pi'en kan nu programmeres til at bruge den tilsluttede time of flight-sensor.

### Opgave - programmer time of flight-sensoren

Programmer enheden.

1. Tænd for Pi'en og vent, til den er startet op.

1. Åbn `fruit-quality-detector`-koden i VS Code, enten direkte på Pi'en eller ved at forbinde via Remote SSH-udvidelsen.

1. Installer rpi-vl53l0x Pip-pakken, en Python-pakke, der interagerer med en VL53L0X time-of-flight afstandssensor. Installer den ved hjælp af denne pip-kommando:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Opret en ny fil i dette projekt kaldet `distance-sensor.py`.

    > 💁 En nem måde at simulere flere IoT-enheder på er at lave hver enhed i en separat Python-fil og derefter køre dem samtidig.

1. Tilføj følgende kode til denne fil:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dette importerer Grove I²C-bus-biblioteket og et sensorbibliotek til kernesensorhardwaren, der er indbygget i Grove time of flight-sensoren.

1. Tilføj derefter følgende kode for at få adgang til sensoren:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Denne kode erklærer en afstandssensor ved hjælp af Grove I²C-bussen og starter derefter sensoren.

1. Til sidst tilføj en uendelig løkke for at aflæse afstande:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Denne kode venter på, at en værdi er klar til at blive aflæst fra sensoren, og udskriver den derefter i konsollen.

1. Kør denne kode.

    > 💁 Husk, at denne fil hedder `distance-sensor.py`! Sørg for at køre den via Python og ikke `app.py`.

1. Du vil se afstandsmålinger dukke op i konsollen. Placer objekter tæt på sensoren, og du vil se afstandsmålingen:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Afstandsmåleren sidder på bagsiden af sensoren, så sørg for at bruge den korrekte side, når du måler afstand.

    ![Afstandsmåleren på bagsiden af time of flight-sensoren peger på en banan](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.da.png)

> 💁 Du kan finde denne kode i [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi)-mappen.

😀 Dit program til nærhedssensoren var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.