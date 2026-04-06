# Upptäck närhet - Wio Terminal

I den här delen av lektionen kommer du att lägga till en närhetssensor till din Wio Terminal och läsa avstånd från den.

## Hårdvara

Wio Terminal behöver en närhetssensor.

Sensorn du kommer att använda är en [Grove Time of Flight-avståndssensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html). Den här sensorn använder en laseravståndsmätare för att upptäcka avstånd. Sensorn har ett intervall på 10mm till 2000mm (1cm - 2m) och rapporterar värden inom det intervallet ganska exakt, med avstånd över 1000mm rapporterade som 8109mm.

Laseravståndsmätaren sitter på baksidan av sensorn, motsatt sida till Grove-uttaget.

Detta är en I2C-sensor.

### Anslut Time of Flight-sensorn

Grove Time of Flight-sensorn kan anslutas till Wio Terminal.

#### Uppgift - anslut Time of Flight-sensorn

Anslut Time of Flight-sensorn.

![En Grove Time of Flight-sensor](../../../../../translated_images/sv/grove-time-of-flight-sensor.d82ff2165bfded9f.webp)

1. Sätt ena änden av en Grove-kabel i uttaget på Time of Flight-sensorn. Den går bara in på ett sätt.

1. Med Wio Terminal frånkopplad från din dator eller annan strömkälla, anslut den andra änden av Grove-kabeln till det vänstra Grove-uttaget på Wio Terminal när du tittar på skärmen. Detta är uttaget närmast strömknappen. Det är ett kombinerat digitalt och I2C-uttag.

![Grove Time of Flight-sensorn ansluten till det vänstra uttaget](../../../../../translated_images/sv/wio-time-of-flight-sensor.c4c182131d2ea73d.webp)

1. Du kan nu ansluta Wio Terminal till din dator.

## Programmera Time of Flight-sensorn

Wio Terminal kan nu programmeras för att använda den anslutna Time of Flight-sensorn.

### Uppgift - programmera Time of Flight-sensorn

1. Skapa ett helt nytt Wio Terminal-projekt med PlatformIO. Kalla detta projekt `distance-sensor`. Lägg till kod i `setup`-funktionen för att konfigurera seriell port.

1. Lägg till ett biblioteksberoende för Seeed Grove Time of Flight-avståndssensorbiblioteket i projektets `platformio.ini`-fil:

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. I `main.cpp`, lägg till följande under de befintliga inkluderingsdirektiven för att deklarera en instans av klassen `Seeed_vl53l0x` för att interagera med Time of Flight-sensorn:

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. Lägg till följande längst ner i `setup`-funktionen för att initiera sensorn:

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. I `loop`-funktionen, läs ett värde från sensorn:

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    Den här koden initierar en datastruktur för att läsa in data, och skickar den sedan till metoden `PerformSingleRangingMeasurement` där den fylls med avståndsmätningen.

1. Skriv ut avståndsmätningen under detta och lägg till en fördröjning på 1 sekund:

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. Bygg, ladda upp och kör denna kod. Du kommer att kunna se avståndsmätningar med den seriella monitorn. Placera objekt nära sensorn och du kommer att se avståndsmätningen:

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    Avståndsmätaren sitter på baksidan av sensorn, så se till att du använder rätt sida när du mäter avstånd.

    ![Avståndsmätaren på baksidan av Time of Flight-sensorn pekar på en banan](../../../../../translated_images/sv/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 Du kan hitta denna kod i [code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal)-mappen.

😀 Ditt program för närhetssensorn var en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som kan uppstå vid användning av denna översättning.