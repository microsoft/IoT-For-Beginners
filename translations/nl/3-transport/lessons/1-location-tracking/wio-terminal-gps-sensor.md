<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T22:49:27+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "nl"
}
-->
# Lees GPS-gegevens - Wio Terminal

In dit deel van de les voeg je een GPS-sensor toe aan je Wio Terminal en lees je gegevens ervan uit.

## Hardware

De Wio Terminal heeft een GPS-sensor nodig.

De sensor die je gaat gebruiken is een [Grove GPS Air530 sensor](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). Deze sensor kan verbinding maken met meerdere GPS-systemen voor een snelle en nauwkeurige positiebepaling. De sensor bestaat uit twee delen: de kern van de elektronica en een externe antenne die via een dunne draad is verbonden om radiosignalen van satellieten op te vangen.

Dit is een UART-sensor, wat betekent dat GPS-gegevens via UART worden verzonden.

### Verbind de GPS-sensor

De Grove GPS-sensor kan worden aangesloten op de Wio Terminal.

#### Taak - verbind de GPS-sensor

Verbind de GPS-sensor.

![Een Grove GPS-sensor](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.nl.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de GPS-sensor. De kabel past maar op één manier.

1. Zorg ervoor dat de Wio Terminal niet is aangesloten op je computer of een andere stroombron. Verbind het andere uiteinde van de Grove-kabel met de linker Grove-aansluiting op de Wio Terminal (als je naar het scherm kijkt). Dit is de aansluiting die het dichtst bij de aan/uit-knop zit.

    ![De Grove GPS-sensor aangesloten op de linker aansluiting](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.nl.png)

1. Plaats de GPS-sensor zo dat de aangesloten antenne zicht heeft op de lucht - bij voorkeur naast een open raam of buiten. Het is makkelijker om een duidelijk signaal te krijgen als er niets tussen de antenne en de lucht zit.

1. Je kunt nu de Wio Terminal aansluiten op je computer.

1. De GPS-sensor heeft twee LED's: een blauwe LED die knippert wanneer gegevens worden verzonden, en een groene LED die elke seconde knippert wanneer gegevens van satellieten worden ontvangen. Zorg ervoor dat de blauwe LED knippert wanneer je de Wio Terminal inschakelt. Na een paar minuten zal de groene LED gaan knipperen - als dit niet gebeurt, moet je mogelijk de antenne verplaatsen.

## Programmeer de GPS-sensor

De Wio Terminal kan nu worden geprogrammeerd om de aangesloten GPS-sensor te gebruiken.

### Taak - programmeer de GPS-sensor

Programmeur het apparaat.

1. Maak een nieuw Wio Terminal-project aan met PlatformIO. Noem dit project `gps-sensor`. Voeg code toe in de `setup`-functie om de seriële poort te configureren.

1. Voeg de volgende include-richtlijn toe aan de bovenkant van het bestand `main.cpp`. Hiermee wordt een headerbestand opgenomen met functies om de linker Grove-poort voor UART te configureren.

    ```cpp
    #include <wiring_private.h>
    ```

1. Voeg hieronder de volgende regel code toe om een seriële poortverbinding met de UART-poort te declareren:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. Je moet wat code toevoegen om enkele interne signaalhandlers naar deze seriële poort te leiden. Voeg de volgende code toe onder de `Serial3`-declaratie:

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

1. Configureer in de `setup`-functie, onder de configuratie van de `Serial`-poort, de UART-seriële poort met de volgende code:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. Voeg hieronder in de `setup`-functie de volgende code toe om de Grove-pin met de seriële poort te verbinden:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. Voeg de volgende functie toe vóór de `loop`-functie om de GPS-gegevens naar de seriële monitor te sturen:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. Voeg in de `loop`-functie de volgende code toe om gegevens van de UART-seriële poort te lezen en deze naar de seriële monitor te sturen:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    Deze code leest gegevens van de UART-seriële poort. De functie `readStringUntil` leest tot een afsluitend teken, in dit geval een nieuwe regel. Dit leest een volledige NMEA-zin (NMEA-zinnen worden afgesloten met een nieuwe regel). Zolang er gegevens van de UART-seriële poort kunnen worden gelezen, worden deze gelezen en via de `printGPSData`-functie naar de seriële monitor gestuurd. Zodra er geen gegevens meer kunnen worden gelezen, wacht de `loop`-functie 1 seconde (1.000 ms).

1. Bouw en upload de code naar de Wio Terminal.

1. Zodra de code is geüpload, kun je de GPS-gegevens bekijken met de seriële monitor.

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

> 💁 Je kunt deze code vinden in de map [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 Je GPS-sensorprogramma is een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.