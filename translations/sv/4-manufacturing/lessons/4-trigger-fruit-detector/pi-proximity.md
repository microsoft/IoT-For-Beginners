# Upptäck närhet - Raspberry Pi

I den här delen av lektionen kommer du att lägga till en närhetssensor till din Raspberry Pi och läsa avstånd från den.

## Hårdvara

Raspberry Pi behöver en närhetssensor.

Sensorn du kommer att använda är en [Grove Time of Flight-avståndssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Denna sensor använder en laseravståndsmätare för att upptäcka avstånd. Sensorn har ett mätområde på 10 mm till 2000 mm (1 cm - 2 m) och rapporterar värden inom detta intervall med hög noggrannhet. Avstånd över 1000 mm rapporteras som 8109 mm.

Laseravståndsmätaren sitter på baksidan av sensorn, motsatt sida till Grove-kontakten.

Detta är en I²C-sensor.

### Anslut Time of Flight-sensorn

Grove Time of Flight-sensorn kan anslutas till Raspberry Pi.

#### Uppgift - anslut Time of Flight-sensorn

Anslut Time of Flight-sensorn.

![En Grove Time of Flight-sensor](../../../../../translated_images/sv/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Sätt i ena änden av en Grove-kabel i kontakten på Time of Flight-sensorn. Den går bara att sätta i på ett sätt.

1. Med Raspberry Pi avstängd, anslut den andra änden av Grove-kabeln till en av I²C-kontakterna markerade **I²C** på Grove Base-hatten som är ansluten till Pi. Dessa kontakter finns på den nedre raden, motsatt sida till GPIO-stiften och bredvid kamerakabelns plats.

![Grove Time of Flight-sensorn ansluten till I²C-kontakten](../../../../../translated_images/sv/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## Programmera Time of Flight-sensorn

Raspberry Pi kan nu programmeras för att använda den anslutna Time of Flight-sensorn.

### Uppgift - programmera Time of Flight-sensorn

Programmera enheten.

1. Starta Pi och vänta tills den har startat upp.

1. Öppna koden `fruit-quality-detector` i VS Code, antingen direkt på Pi eller genom att ansluta via Remote SSH-tillägget.

1. Installera rpi-vl53l0x Pip-paketet, ett Python-paket som interagerar med en VL53L0X Time of Flight-avståndssensor. Installera det med följande pip-kommando:

    ```sh
    pip install rpi-vl53l0x
    ```

1. Skapa en ny fil i detta projekt som heter `distance-sensor.py`.

    > 💁 Ett enkelt sätt att simulera flera IoT-enheter är att skapa varje enhet i en separat Python-fil och sedan köra dem samtidigt.

1. Lägg till följande kod i denna fil:

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Detta importerar Grove I²C-biblioteket och ett sensorbibliotek för den grundläggande sensormodulen som är inbyggd i Grove Time of Flight-sensorn.

1. Lägg sedan till följande kod för att få åtkomst till sensorn:

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    Denna kod deklarerar en avståndssensor med hjälp av Grove I²C-bussen och startar sedan sensorn.

1. Slutligen, lägg till en oändlig loop för att läsa avstånd:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Denna kod väntar på att ett värde ska vara redo att läsas från sensorn och skriver sedan ut det i konsolen.

1. Kör denna kod.

    > 💁 Glöm inte att denna fil heter `distance-sensor.py`! Se till att köra den via Python, inte `app.py`.

1. Du kommer att se avståndsmätningar visas i konsolen. Placera objekt nära sensorn och du kommer att se avståndsmätningen:

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Avståndsmätaren sitter på baksidan av sensorn, så se till att använda rätt sida när du mäter avstånd.

    ![Avståndsmätaren på baksidan av Time of Flight-sensorn pekar på en banan](../../../../../translated_images/sv/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Du kan hitta denna kod i mappen [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi).

😀 Ditt program för närhetssensorn blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.