# Läs GPS-data - Wio Terminal

I den här delen av lektionen kommer du att lägga till en GPS-sensor till din Wio Terminal och läsa värden från den.

## Hårdvara

Wio Terminal behöver en GPS-sensor.

Sensorn du kommer att använda är en [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Den här sensorn kan ansluta till flera GPS-system för en snabb och exakt positionering. Sensorn består av två delar - den elektroniska kärnan i sensorn och en extern antenn som är ansluten med en tunn kabel för att ta emot radiovågor från satelliterna.

Det här är en UART-sensor, så den skickar GPS-data via UART.

### Anslut GPS-sensorn

Grove GPS-sensorn kan anslutas till Wio Terminal.

#### Uppgift - anslut GPS-sensorn

Anslut GPS-sensorn.

![En Grove GPS-sensor](../../../../../translated_images/sv/grove-gps-sensor.247943bf69b03f0d.webp)

1. Sätt ena änden av en Grove-kabel i uttaget på GPS-sensorn. Den går bara att sätta i på ett sätt.

1. Med Wio Terminal frånkopplad från din dator eller annan strömkälla, anslut den andra änden av Grove-kabeln till det vänstra Grove-uttaget på Wio Terminal när du tittar på skärmen. Detta är uttaget som är närmast strömknappen.

    ![Grove GPS-sensorn ansluten till det vänstra uttaget](../../../../../translated_images/sv/wio-gps-sensor.19fd52b81ce58095.webp)

1. Placera GPS-sensorn så att den anslutna antennen har fri sikt mot himlen - helst nära ett öppet fönster eller utomhus. Det är lättare att få en tydligare signal utan hinder för antennen.

1. Du kan nu ansluta Wio Terminal till din dator.

1. GPS-sensorn har två lysdioder - en blå lysdiod som blinkar när data överförs och en grön lysdiod som blinkar varje sekund när den tar emot data från satelliter. Kontrollera att den blå lysdioden blinkar när du startar Wio Terminal. Efter några minuter kommer den gröna lysdioden att blinka - om inte, kan du behöva justera antennens position.

## Programmera GPS-sensorn

Wio Terminal kan nu programmeras för att använda den anslutna GPS-sensorn.

### Uppgift - programmera GPS-sensorn

Programmera enheten.

1. Skapa ett helt nytt Wio Terminal-projekt med PlatformIO. Namnge projektet `gps-sensor`. Lägg till kod i `setup`-funktionen för att konfigurera seriell port.

1. Lägg till följande include-direktiv högst upp i `main.cpp`-filen. Detta inkluderar en header-fil med funktioner för att konfigurera det vänstra Grove-uttaget för UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Nedanför detta, lägg till följande kodrad för att deklarera en seriell portanslutning till UART-porten:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Du behöver lägga till lite kod för att omdirigera några interna signalhanterare till denna seriella port. Lägg till följande kod under deklarationen av `Serial3`:

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

1. I `setup`-funktionen, under där den seriella porten `Serial` är konfigurerad, konfigurera UART-seriella porten med följande kod:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Under denna kod i `setup`-funktionen, lägg till följande kod för att ansluta Grove-pinnen till den seriella porten:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Lägg till följande funktion före `loop`-funktionen för att skicka GPS-data till den seriella monitorn:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. I `loop`-funktionen, lägg till följande kod för att läsa från UART-seriella porten och skriva ut resultatet till den seriella monitorn:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Denna kod läser från UART-seriella porten. Funktionen `readStringUntil` läser upp till en avslutande tecken, i detta fall en ny rad. Detta kommer att läsa en hel NMEA-sats (NMEA-satser avslutas med en ny rad). Så länge data kan läsas från UART-seriella porten, läses den och skickas till den seriella monitorn via funktionen `printGPSData`. När ingen mer data kan läsas, väntar `loop` i 1 sekund (1 000 ms).

1. Bygg och ladda upp koden till Wio Terminal.

1. När koden har laddats upp kan du övervaka GPS-data med den seriella monitorn.

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

> 💁 Du kan hitta denna kod i [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal)-mappen.

😀 Ditt GPS-sensorprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör du vara medveten om att automatiserade översättningar kan innehålla fel eller felaktigheter. Det ursprungliga dokumentet på dess ursprungliga språk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.