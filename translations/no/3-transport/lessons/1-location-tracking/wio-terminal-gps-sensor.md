# Les GPS-data - Wio Terminal

I denne delen av leksjonen skal du legge til en GPS-sensor på din Wio Terminal og lese verdier fra den.

## Maskinvare

Wio Terminal trenger en GPS-sensor.

Sensoren du skal bruke er en [Grove GPS Air530-sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Denne sensoren kan koble seg til flere GPS-systemer for en rask og nøyaktig posisjonsbestemmelse. Sensoren består av to deler - de elektroniske komponentene i sensoren og en ekstern antenne som er koblet til med en tynn ledning for å motta radiosignaler fra satellittene.

Dette er en UART-sensor, som sender GPS-data via UART.

### Koble til GPS-sensoren

Grove GPS-sensoren kan kobles til Wio Terminal.

#### Oppgave - koble til GPS-sensoren

Koble til GPS-sensoren.

![En Grove GPS-sensor](../../../../../translated_images/no/grove-gps-sensor.247943bf69b03f0d.webp)

1. Sett den ene enden av en Grove-kabel inn i kontakten på GPS-sensoren. Den kan kun settes inn på én måte.

1. Med Wio Terminal frakoblet fra datamaskinen eller annen strømkilde, koble den andre enden av Grove-kabelen til den venstre Grove-kontakten på Wio Terminal, sett fra skjermen. Dette er kontakten nærmest av/på-knappen.

    ![Grove GPS-sensoren koblet til venstre kontakt](../../../../../translated_images/no/wio-gps-sensor.19fd52b81ce58095.webp)

1. Plasser GPS-sensoren slik at den tilkoblede antennen har fri sikt til himmelen - helst ved et åpent vindu eller utendørs. Det er lettere å få et klart signal uten hindringer foran antennen.

1. Du kan nå koble Wio Terminal til datamaskinen.

1. GPS-sensoren har to LED-lys - en blå LED som blinker når data overføres, og en grønn LED som blinker hvert sekund når den mottar data fra satellitter. Sørg for at den blå LED-en blinker når du slår på Wio Terminal. Etter noen minutter vil den grønne LED-en begynne å blinke - hvis ikke, kan det være nødvendig å justere antennens plassering.

## Programmer GPS-sensoren

Wio Terminal kan nå programmeres til å bruke den tilkoblede GPS-sensoren.

### Oppgave - programmer GPS-sensoren

Programmer enheten.

1. Opprett et helt nytt Wio Terminal-prosjekt ved hjelp av PlatformIO. Kall dette prosjektet `gps-sensor`. Legg til kode i `setup`-funksjonen for å konfigurere seriellporten.

1. Legg til følgende `include`-direktiv øverst i `main.cpp`-filen. Dette inkluderer en header-fil med funksjoner for å konfigurere den venstre Grove-porten for UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. Under dette, legg til følgende linje med kode for å deklarere en seriellport-tilkobling til UART-porten:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Du må legge til litt kode for å omdirigere noen interne signalhåndterere til denne seriellporten. Legg til følgende kode under `Serial3`-deklarasjonen:

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

1. I `setup`-funksjonen, under der `Serial`-porten er konfigurert, konfigurer UART-seriellporten med følgende kode:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Under denne koden i `setup`-funksjonen, legg til følgende kode for å koble Grove-pinnen til seriellporten:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Legg til følgende funksjon før `loop`-funksjonen for å sende GPS-data til den serielle monitoren:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. I `loop`-funksjonen, legg til følgende kode for å lese fra UART-seriellporten og skrive ut dataene til den serielle monitoren:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Denne koden leser fra UART-seriellporten. Funksjonen `readStringUntil` leser opp til et terminator-tegn, i dette tilfellet en ny linje. Dette vil lese en hel NMEA-setning (NMEA-setninger avsluttes med et ny linje-tegn). Så lenge data kan leses fra UART-seriellporten, leses de og sendes til den serielle monitoren via `printGPSData`-funksjonen. Når det ikke er mer data å lese, venter `loop` i 1 sekund (1 000 ms).

1. Bygg og last opp koden til Wio Terminal.

1. Når koden er lastet opp, kan du overvåke GPS-dataene ved hjelp av den serielle monitoren.

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

> 💁 Du finner denne koden i [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal)-mappen.

😀 GPS-sensorprogrammet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi tilstreber nøyaktighet, vær oppmerksom på at automatiserte oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for eventuelle misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.