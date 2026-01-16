<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-27T20:56:27+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "nl"
}
-->
# Detecteer nabijheid - Raspberry Pi

In dit deel van de les voeg je een nabijheidssensor toe aan je Raspberry Pi en lees je de afstand ervan af.

## Hardware

De Raspberry Pi heeft een nabijheidssensor nodig.

De sensor die je gaat gebruiken is een [Grove Time of Flight afstandssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Deze sensor gebruikt een laserafstandsmodule om afstanden te detecteren. De sensor heeft een bereik van 10mm tot 2000mm (1cm - 2m) en rapporteert waarden binnen dat bereik vrij nauwkeurig, waarbij afstanden boven 1000mm worden gerapporteerd als 8109mm.

De laserafstandsmeter bevindt zich aan de achterkant van de sensor, tegenover de Grove-aansluiting.

Dit is een I²C-sensor.

### Verbind de Time of Flight-sensor

De Grove Time of Flight-sensor kan worden aangesloten op de Raspberry Pi.

#### Taak - verbind de Time of Flight-sensor

Verbind de Time of Flight-sensor.

![Een Grove Time of Flight-sensor](../../../../../translated_images/nl/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de Time of Flight-sensor. De kabel past maar op één manier.

1. Schakel de Raspberry Pi uit en verbind het andere uiteinde van de Grove-kabel met een van de I²C-aansluitingen gemarkeerd als **I²C** op de Grove Base Hat die aan de Pi is bevestigd. Deze aansluitingen bevinden zich op de onderste rij, aan de tegenovergestelde kant van de GPIO-pinnen en naast de aansluiting voor de camerakabel.

![De Grove Time of Flight-sensor verbonden met de I²C-aansluiting](../../../../../translated_images/nl/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programmeer de Time of Flight-sensor

De Raspberry Pi kan nu worden geprogrammeerd om de aangesloten Time of Flight-sensor te gebruiken.

### Taak - programmeer de Time of Flight-sensor

Programmeer het apparaat.

1. Zet de Pi aan en wacht tot deze is opgestart.

1. Open de `fruit-quality-detector` code in VS Code, direct op de Pi of via de Remote SSH-extensie.

1. Installeer het rpi-vl53l0x Pip-pakket, een Python-pakket dat interacteert met een VL53L0X Time of Flight-afstandssensor. Installeer het met dit pip-commando:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Maak een nieuw bestand in dit project genaamd `distance-sensor.py`.

    > 💁 Een eenvoudige manier om meerdere IoT-apparaten te simuleren is om elk apparaat in een apart Python-bestand te plaatsen en ze tegelijkertijd uit te voeren.

1. Voeg de volgende code toe aan dit bestand:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dit importeert de Grove I²C-busbibliotheek en een sensorbibliotheek voor de kernhardware die in de Grove Time of Flight-sensor is ingebouwd.

1. Voeg hieronder de volgende code toe om toegang te krijgen tot de sensor:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Deze code declareert een afstandssensor met behulp van de Grove I²C-bus en start vervolgens de sensor.

1. Voeg ten slotte een oneindige lus toe om afstanden te lezen:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Deze code wacht tot er een waarde beschikbaar is om te lezen van de sensor en print deze vervolgens naar de console.

1. Voer deze code uit.

    > 💁 Vergeet niet dat dit bestand `distance-sensor.py` heet! Zorg ervoor dat je dit uitvoert via Python en niet via `app.py`.

1. Je zult afstandsmetingen in de console zien verschijnen. Plaats objecten in de buurt van de sensor en je zult de afstandsmeting zien:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    De afstandsmeter bevindt zich aan de achterkant van de sensor, dus zorg ervoor dat je de juiste kant gebruikt bij het meten van afstanden.

    ![De afstandsmeter aan de achterkant van de Time of Flight-sensor gericht op een banaan](../../../../../translated_images/nl/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Je kunt deze code vinden in de [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) map.

😀 Je programma voor de nabijheidssensor is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we ons best doen voor nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.