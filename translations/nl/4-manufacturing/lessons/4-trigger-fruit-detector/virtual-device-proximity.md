<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T20:57:55+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "nl"
}
-->
# Detecteer nabijheid - Virtuele IoT-hardware

In dit deel van de les voeg je een nabijheidssensor toe aan je virtuele IoT-apparaat en lees je de afstand ervan af.

## Hardware

Het virtuele IoT-apparaat zal gebruik maken van een gesimuleerde afstandssensor.

Bij een fysiek IoT-apparaat zou je een sensor met een lasermodule gebruiken om afstand te detecteren.

### Voeg de afstandssensor toe aan CounterFit

Om een virtuele afstandssensor te gebruiken, moet je er een toevoegen aan de CounterFit-app.

#### Taak - voeg de afstandssensor toe aan CounterFit

Voeg de afstandssensor toe aan de CounterFit-app.

1. Open de `fruit-quality-detector` code in VS Code en zorg ervoor dat de virtuele omgeving is geactiveerd.

1. Installeer een extra Pip-pakket om een CounterFit shim te installeren die kan communiceren met afstandssensoren door het [rpi-vl53l0x Pip-pakket](https://pypi.org/project/rpi-vl53l0x/) te simuleren, een Python-pakket dat interacteert met [een VL53L0X time-of-flight afstandssensor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Zorg ervoor dat je dit installeert vanuit een terminal met de virtuele omgeving geactiveerd.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Zorg ervoor dat de CounterFit-webapp actief is.

1. Maak een afstandssensor aan:

    1. In het *Create sensor* vak in het *Sensors* paneel, klik op het dropdown-menu *Sensor type* en selecteer *Distance*.

    1. Laat de *Units* staan op `Millimeter`.

    1. Deze sensor is een I²C-sensor, dus stel het adres in op `0x29`. Als je een fysieke VL53L0X-sensor zou gebruiken, zou dit adres hardcoded zijn.

    1. Selecteer de knop **Add** om de afstandssensor aan te maken.

    ![De instellingen van de afstandssensor](../../../../../translated_images/nl/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    De afstandssensor wordt aangemaakt en verschijnt in de sensorenlijst.

    ![De aangemaakte afstandssensor](../../../../../translated_images/nl/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Programmeer de afstandssensor

Het virtuele IoT-apparaat kan nu worden geprogrammeerd om de gesimuleerde afstandssensor te gebruiken.

### Taak - programmeer de time-of-flight sensor

1. Maak een nieuw bestand aan in het `fruit-quality-detector` project genaamd `distance-sensor.py`.

    > 💁 Een eenvoudige manier om meerdere IoT-apparaten te simuleren is om elk apparaat in een apart Python-bestand te doen en ze vervolgens tegelijkertijd uit te voeren.

1. Start een verbinding met CounterFit met de volgende code:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Voeg de volgende code hieronder toe:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Dit importeert de sensorbibliotheek shim voor de VL53L0X time-of-flight sensor.

1. Voeg hieronder de volgende code toe om toegang te krijgen tot de sensor:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Deze code declareert een afstandssensor en start vervolgens de sensor.

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

1. Je zult afstandsmetingen zien verschijnen in de console. Verander de waarde in CounterFit om deze waarde te zien veranderen, of gebruik willekeurige waarden.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Je kunt deze code vinden in de [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device) map.

😀 Je programma voor de nabijheidssensor is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.