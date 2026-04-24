# Mäta jordfuktighet - Wio Terminal

I den här delen av lektionen kommer du att lägga till en kapacitiv jordfuktighetssensor till din Wio Terminal och läsa värden från den.

## Hårdvara

Wio Terminal behöver en kapacitiv jordfuktighetssensor.

Sensorn du kommer att använda är en [Kapacitiv Jordfuktighetssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), som mäter jordfuktighet genom att detektera jordens kapacitans, en egenskap som förändras när jordens fuktighet ändras. När jordfuktigheten ökar, minskar spänningen.

Detta är en analog sensor, så den ansluts till analoga stift på Wio Terminal och använder en inbyggd ADC för att skapa ett värde mellan 0-1 023.

### Anslut jordfuktighetssensorn

Grove jordfuktighetssensorn kan anslutas till Wio Terminals konfigurerbara analog/digital-port.

#### Uppgift - anslut jordfuktighetssensorn

Anslut jordfuktighetssensorn.

![En Grove jordfuktighetssensor](../../../../../translated_images/sv/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Sätt ena änden av en Grove-kabel i uttaget på jordfuktighetssensorn. Den går bara att sätta i på ett sätt.

1. Med Wio Terminal frånkopplad från din dator eller annan strömkälla, anslut den andra änden av Grove-kabeln till det högra Grove-uttaget på Wio Terminal när du tittar på skärmen. Detta är uttaget längst bort från strömknappen.

![Grove jordfuktighetssensor ansluten till det högra uttaget](../../../../../translated_images/sv/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Sätt jordfuktighetssensorn i jorden. Den har en "högsta positionslinje" - en vit linje tvärs över sensorn. Sätt sensorn upp till, men inte förbi, denna linje.

![Grove jordfuktighetssensor i jord](../../../../../translated_images/sv/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Du kan nu ansluta Wio Terminal till din dator.

## Programmera jordfuktighetssensorn

Wio Terminal kan nu programmeras för att använda den anslutna jordfuktighetssensorn.

### Uppgift - programmera jordfuktighetssensorn

Programmera enheten.

1. Skapa ett helt nytt Wio Terminal-projekt med PlatformIO. Kalla detta projekt `soil-moisture-sensor`. Lägg till kod i funktionen `setup` för att konfigurera den seriella porten.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa ett PlatformIO-projekt i projekt 1, lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Det finns inget bibliotek för denna sensor, istället kan du läsa från den analoga stiftet med den inbyggda Arduino-funktionen [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Börja med att konfigurera det analoga stiftet för inmatning så att värden kan läsas från det genom att lägga till följande i funktionen `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Detta ställer in stiftet `A0`, det kombinerade analog/digital-stiftet, som ett inmatningsstift som spänning kan läsas från.

1. Lägg till följande i funktionen `loop` för att läsa spänningen från detta stift:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Nedanför denna kod, lägg till följande kod för att skriva ut värdet till den seriella porten:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Lägg slutligen till en fördröjning på 10 sekunder i slutet:

    ```cpp
    delay(10000);
    ```

1. Bygg och ladda upp koden till Wio Terminal.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa ett PlatformIO-projekt i projekt 1, lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. När koden har laddats upp kan du övervaka jordfuktigheten med den seriella monitorn. Tillsätt lite vatten i jorden eller ta bort sensorn från jorden och se hur värdet ändras.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    I exempelutdata ovan kan du se hur spänningen sjunker när vatten tillsätts.

> 💁 Du kan hitta denna kod i mappen [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 Ditt program för jordfuktighetssensorn blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiska översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.