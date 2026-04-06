# Læs GPS-data - Wio Terminal

I denne del af lektionen vil du tilføje en GPS-sensor til din Wio Terminal og læse værdier fra den.

## Hardware

Wio Terminal kræver en GPS-sensor.

Den sensor, du skal bruge, er en [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Denne sensor kan forbinde til flere GPS-systemer for en hurtig og præcis positionering. Sensoren består af to dele - selve sensorelektronikken og en ekstern antenne, der er forbundet med en tynd ledning for at opfange radiosignaler fra satellitterne.

Dette er en UART-sensor, så den sender GPS-data via UART.

### Tilslut GPS-sensoren

Grove GPS-sensoren kan tilsluttes Wio Terminal.

#### Opgave - tilslut GPS-sensoren

Tilslut GPS-sensoren.

![En Grove GPS-sensor](../../../../../translated_images/da/grove-gps-sensor.247943bf69b03f0d.webp)

1. Sæt den ene ende af et Grove-kabel i stikket på GPS-sensoren. Det kan kun sættes i på én måde.

1. Med Wio Terminal frakoblet din computer eller anden strømkilde, tilslut den anden ende af Grove-kablet til det venstre Grove-stik på Wio Terminal, når du ser på skærmen. Dette er stikket tættest på tænd/sluk-knappen.

    ![Grove GPS-sensoren tilsluttet det venstre stik](../../../../../translated_images/da/wio-gps-sensor.19fd52b81ce58095.webp)

1. Placer GPS-sensoren, så den tilkoblede antenne har frit udsyn til himlen - ideelt set ved et åbent vindue eller udenfor. Det er nemmere at få et klart signal, hvis der ikke er noget, der blokerer for antennen.

1. Du kan nu tilslutte Wio Terminal til din computer.

1. GPS-sensoren har 2 LED'er - en blå LED, der blinker, når data overføres, og en grøn LED, der blinker hvert sekund, når den modtager data fra satellitter. Sørg for, at den blå LED blinker, når du tænder for Wio Terminal. Efter et par minutter vil den grønne LED begynde at blinke - hvis ikke, kan det være nødvendigt at flytte antennen.

## Programmer GPS-sensoren

Wio Terminal kan nu programmeres til at bruge den tilsluttede GPS-sensor.

### Opgave - programmer GPS-sensoren

Programmer enheden.

1. Opret et helt nyt Wio Terminal-projekt ved hjælp af PlatformIO. Kald dette projekt `gps-sensor`. Tilføj kode i `setup`-funktionen for at konfigurere serielporten.

1. Tilføj følgende include-direktiv øverst i `main.cpp`-filen. Dette inkluderer en headerfil med funktioner til at konfigurere det venstre Grove-stik til UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Tilføj derefter følgende linje kode for at erklære en seriel portforbindelse til UART-porten:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Du skal tilføje noget kode for at omdirigere nogle interne signalhåndterere til denne serielport. Tilføj følgende kode under `Serial3`-deklarationen:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. I `setup`-funktionen, under hvor `Serial`-porten er konfigureret, skal du konfigurere UART-serielporten med følgende kode:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Tilføj derefter følgende kode i `setup`-funktionen for at forbinde Grove-pinden til serielporten:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Tilføj følgende funktion før `loop`-funktionen for at sende GPS-data til serielmonitoren:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. I `loop`-funktionen skal du tilføje følgende kode for at læse fra UART-serielporten og udskrive output til serielmonitoren:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Denne kode læser fra UART-serielporten. Funktionen `readStringUntil` læser op til et terminator-tegn, i dette tilfælde en ny linje. Dette vil læse en hel NMEA-sætning (NMEA-sætninger afsluttes med et nyt linjetegn). Så længe der kan læses data fra UART-serielporten, læses det og sendes til serielmonitoren via `printGPSData`-funktionen. Når der ikke kan læses mere data, forsinkes `loop` i 1 sekund (1.000 ms).

1. Byg og upload koden til Wio Terminal.

1. Når koden er uploadet, kan du overvåge GPS-dataene ved hjælp af serielmonitoren.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 Du kan finde denne kode i [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal)-mappen.

😀 Dit GPS-sensorprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på at opnå nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi påtager os ikke ansvar for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.