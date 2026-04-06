# Mål jordfugtighed - Wio Terminal

I denne del af lektionen vil du tilføje en kapacitiv jordfugtighedssensor til din Wio Terminal og aflæse værdier fra den.

## Hardware

Wio Terminalen kræver en kapacitiv jordfugtighedssensor.

Sensoren, du vil bruge, er en [Kapacitiv Jordfugtighedssensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), der måler jordfugtighed ved at registrere jordens kapacitans, en egenskab der ændrer sig, når jordens fugtighed ændrer sig. Når jordfugtigheden stiger, falder spændingen.

Dette er en analog sensor, så den forbindes til analoge pins på Wio Terminalen, der bruger en indbygget ADC til at skabe en værdi fra 0-1.023.

### Tilslut jordfugtighedssensoren

Grove jordfugtighedssensoren kan tilsluttes Wio Terminalens konfigurerbare analog/digital port.

#### Opgave - tilslut jordfugtighedssensoren

Tilslut jordfugtighedssensoren.

![En Grove jordfugtighedssensor](../../../../../translated_images/da/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78b.webp)

1. Sæt den ene ende af et Grove-kabel i stikket på jordfugtighedssensoren. Det kan kun sættes i på én måde.

1. Med Wio Terminalen frakoblet fra din computer eller anden strømkilde, tilslut den anden ende af Grove-kablet til det højre Grove-stik på Wio Terminalen, når du ser på skærmen. Dette er stikket længst væk fra tænd/sluk-knappen.

![Grove jordfugtighedssensor tilsluttet det højre stik](../../../../../translated_images/da/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. Sæt jordfugtighedssensoren i jorden. Den har en 'højeste positionslinje' - en hvid linje på tværs af sensoren. Sæt sensoren i jorden op til, men ikke over, denne linje.

![Grove jordfugtighedssensor i jord](../../../../../translated_images/da/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. Du kan nu tilslutte Wio Terminalen til din computer.

## Programmer jordfugtighedssensoren

Wio Terminalen kan nu programmeres til at bruge den tilsluttede jordfugtighedssensor.

### Opgave - programmer jordfugtighedssensoren

Programmer enheden.

1. Opret et helt nyt Wio Terminal-projekt ved hjælp af PlatformIO. Kald dette projekt `soil-moisture-sensor`. Tilføj kode i `setup`-funktionen for at konfigurere den serielle port.

    > ⚠️ Du kan henvise til [instruktionerne for at oprette et PlatformIO-projekt i projekt 1, lektion 1, hvis nødvendigt](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Der findes ikke et bibliotek til denne sensor, men du kan læse fra den analoge pin ved hjælp af den indbyggede Arduino-funktion [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Start med at konfigurere den analoge pin som input, så værdier kan aflæses fra den, ved at tilføje følgende til `setup`-funktionen.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Dette sætter `A0`-pinnen, den kombinerede analog/digital pin, som en inputpin, hvor spænding kan aflæses.

1. Tilføj følgende til `loop`-funktionen for at aflæse spændingen fra denne pin:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Tilføj derefter følgende kode for at udskrive værdien til den serielle port:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Til sidst tilføj en forsinkelse på 10 sekunder:

    ```cpp
    delay(10000);
    ```

1. Byg og upload koden til Wio Terminalen.

    > ⚠️ Du kan henvise til [instruktionerne for at oprette et PlatformIO-projekt i projekt 1, lektion 1, hvis nødvendigt](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Når koden er uploadet, kan du overvåge jordfugtigheden ved hjælp af den serielle monitor. Tilføj noget vand til jorden, eller fjern sensoren fra jorden, og se værdien ændre sig.

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

    I det viste eksempeloutput kan du se spændingen falde, når der tilføjes vand.

> 💁 Du kan finde denne kode i [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal)-mappen.

😀 Dit program til jordfugtighedssensoren var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal det bemærkes, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.