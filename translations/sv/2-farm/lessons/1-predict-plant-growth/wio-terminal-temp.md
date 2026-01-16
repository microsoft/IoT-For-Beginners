<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-27T22:52:23+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "sv"
}
-->
# Mäta temperatur - Wio Terminal

I den här delen av lektionen kommer du att lägga till en temperatursensor till din Wio Terminal och läsa av temperaturvärden från den.

## Hårdvara

Wio Terminal behöver en temperatursensor.

Sensorn du kommer att använda är en [DHT11 fukt- och temperatursensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), som kombinerar två sensorer i en enhet. Den är ganska populär och det finns flera kommersiellt tillgängliga sensorer som kombinerar temperatur, fuktighet och ibland även atmosfärstryck. Temperaturkomponenten är en negativ temperaturkoefficient (NTC) termistor, en termistor där resistansen minskar när temperaturen ökar.

Detta är en digital sensor, så den har en inbyggd ADC som skapar en digital signal med temperatur- och fuktdata som mikrokontrollern kan läsa av.

### Anslut temperatursensorn

Grove-temperatursensorn kan anslutas till Wio Terminals digitala port.

#### Uppgift - anslut temperatursensorn

Anslut temperatursensorn.

![En Grove-temperatursensor](../../../../../translated_images/sv/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Sätt ena änden av en Grove-kabel i uttaget på fukt- och temperatursensorn. Den går bara att sätta i på ett sätt.

1. Med Wio Terminal frånkopplad från din dator eller annan strömkälla, anslut den andra änden av Grove-kabeln till det högra Grove-uttaget på Wio Terminal när du tittar på skärmen. Detta är uttaget längst bort från strömbrytaren.

![Grove-temperatursensorn ansluten till det högra uttaget](../../../../../translated_images/sv/wio-temperature-sensor.2934928f38c7f79a.webp)

## Programmera temperatursensorn

Wio Terminal kan nu programmeras för att använda den anslutna temperatursensorn.

### Uppgift - programmera temperatursensorn

Programmera enheten.

1. Skapa ett helt nytt Wio Terminal-projekt med PlatformIO. Ge projektet namnet `temperature-sensor`. Lägg till kod i funktionen `setup` för att konfigurera den seriella porten.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa ett PlatformIO-projekt i projekt 1, lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Lägg till ett bibliotek för Seeed Grove Humidity and Temperature-sensorn i projektets `platformio.ini`-fil:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ Du kan hänvisa till [instruktionerna för att lägga till bibliotek i ett PlatformIO-projekt i projekt 1, lektion 4 om det behövs](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. Lägg till följande `#include`-direktiv högst upp i filen, under det befintliga `#include <Arduino.h>`:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    Detta importerar filer som behövs för att interagera med sensorn. Header-filen `DHT.h` innehåller koden för själva sensorn, och genom att lägga till `SPI.h` säkerställer du att koden som behövs för att kommunicera med sensorn länkas in när appen kompileras.

1. Före funktionen `setup`, deklarera DHT-sensorn:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    Detta deklarerar en instans av klassen `DHT` som hanterar den **D**igitala **H**umidity och **T**emperature-sensorn. Den är ansluten till port `D0`, det högra Grove-uttaget på Wio Terminal. Den andra parametern anger att sensorn som används är *DHT11* - biblioteket du använder stödjer andra varianter av denna sensor.

1. I funktionen `setup`, lägg till kod för att konfigurera den seriella anslutningen:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. I slutet av funktionen `setup`, efter den sista `delay`, lägg till ett anrop för att starta DHT-sensorn:

    ```cpp
    dht.begin();
    ```

1. I funktionen `loop`, lägg till kod för att anropa sensorn och skriva ut temperaturen till den seriella porten:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    Denna kod deklarerar en tom array med två flyttal och skickar den till anropet `readTempAndHumidity` på instansen `DHT`. Detta anrop fyller arrayen med två värden - fuktigheten placeras i det första elementet (index 0) och temperaturen placeras i det andra elementet (index 1).

    Temperaturen läses från det andra elementet i arrayen och skrivs ut till den seriella porten.

    > 🇺🇸 Temperaturen läses av i Celsius. För amerikaner, för att konvertera detta till Fahrenheit, dela Celsius-värdet med 5, multiplicera med 9 och lägg till 32. Till exempel blir en temperaturavläsning på 20°C ((20/5)*9) + 32 = 68°F.

1. Bygg och ladda upp koden till Wio Terminal.

    > ⚠️ Du kan hänvisa till [instruktionerna för att skapa ett PlatformIO-projekt i projekt 1, lektion 1 om det behövs](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. När koden har laddats upp kan du övervaka temperaturen med den seriella monitorn:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 Du kan hitta denna kod i mappen [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 Ditt program för temperatursensorn blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiserade översättningar kan innehålla fel eller brister. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.