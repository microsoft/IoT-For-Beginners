<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-27T20:33:02+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "sv"
}
-->
# Upptäck närhet - Virtuell IoT-hårdvara

I den här delen av lektionen kommer du att lägga till en närhetssensor till din virtuella IoT-enhet och läsa avstånd från den.

## Hårdvara

Den virtuella IoT-enheten kommer att använda en simulerad avståndssensor.

På en fysisk IoT-enhet skulle du använda en sensor med en lasermodul för att mäta avstånd.

### Lägg till avståndssensorn i CounterFit

För att använda en virtuell avståndssensor behöver du lägga till en i CounterFit-appen.

#### Uppgift - lägg till avståndssensorn i CounterFit

Lägg till avståndssensorn i CounterFit-appen.

1. Öppna koden `fruit-quality-detector` i VS Code och se till att den virtuella miljön är aktiverad.

1. Installera ett extra Pip-paket för att lägga till en CounterFit-shim som kan kommunicera med avståndssensorer genom att simulera [rpi-vl53l0x Pip-paketet](https://pypi.org/project/rpi-vl53l0x/), ett Python-paket som interagerar med [en VL53L0X time-of-flight avståndssensor](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Se till att du installerar detta från en terminal med den virtuella miljön aktiverad.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Se till att CounterFit-webbappen körs.

1. Skapa en avståndssensor:

    1. I rutan *Create sensor* i *Sensors*-panelen, öppna rullgardinsmenyn *Sensor type* och välj *Distance*.

    1. Lämna *Units* som `Millimeter`.

    1. Den här sensorn är en I²C-sensor, så ställ in adressen till `0x29`. Om du använde en fysisk VL53L0X-sensor skulle den vara hårdkodad till denna adress.

    1. Välj knappen **Add** för att skapa avståndssensorn.

    ![Inställningar för avståndssensorn](../../../../../translated_images/sv/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    Avståndssensorn kommer att skapas och visas i sensorlistan.

    ![Avståndssensorn skapad](../../../../../translated_images/sv/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## Programmera avståndssensorn

Den virtuella IoT-enheten kan nu programmeras för att använda den simulerade avståndssensorn.

### Uppgift - programmera time-of-flight-sensorn

1. Skapa en ny fil i projektet `fruit-quality-detector` som heter `distance-sensor.py`.

    > 💁 Ett enkelt sätt att simulera flera IoT-enheter är att göra varje enhet i en separat Python-fil och sedan köra dem samtidigt.

1. Starta en anslutning till CounterFit med följande kod:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Lägg till följande kod under detta:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Detta importerar sensorbibliotekets shim för VL53L0X time-of-flight-sensorn.

1. Lägg till följande kod under detta för att komma åt sensorn:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Denna kod deklarerar en avståndssensor och startar sensorn.

1. Slutligen, lägg till en oändlig loop för att läsa avstånd:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Denna kod väntar på att ett värde ska vara redo att läsas från sensorn och skriver sedan ut det till konsolen.

1. Kör denna kod.

    > 💁 Glöm inte att denna fil heter `distance-sensor.py`! Se till att köra den via Python, inte `app.py`.

1. Du kommer att se avståndsmätningar visas i konsolen. Ändra värdet i CounterFit för att se detta värde ändras, eller använd slumpmässiga värden.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Du kan hitta denna kod i mappen [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Ditt program för närhetssensorn var en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.