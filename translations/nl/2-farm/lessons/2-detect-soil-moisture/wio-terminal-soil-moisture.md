<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T21:25:15+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "nl"
}
-->
# Meet bodemvocht - Wio Terminal

In dit deel van de les voeg je een capacitieve bodemvochtsensor toe aan je Wio Terminal en lees je waarden ervan uit.

## Hardware

De Wio Terminal heeft een capacitieve bodemvochtsensor nodig.

De sensor die je gaat gebruiken is een [Capacitieve Bodemvochtsensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), die bodemvocht meet door de capaciteit van de bodem te detecteren, een eigenschap die verandert naarmate het bodemvocht verandert. Naarmate het bodemvocht toeneemt, daalt de spanning.

Dit is een analoge sensor, dus deze wordt aangesloten op de analoge pinnen van de Wio Terminal, waarbij een ingebouwde ADC een waarde van 0-1.023 genereert.

### Verbind de bodemvochtsensor

De Grove bodemvochtsensor kan worden aangesloten op de configureerbare analoge/digitale poort van de Wio Terminal.

#### Taak - verbind de bodemvochtsensor

Verbind de bodemvochtsensor.

![Een Grove bodemvochtsensor](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.nl.png)

1. Steek één uiteinde van een Grove-kabel in de aansluiting op de bodemvochtsensor. Deze past maar op één manier.

1. Terwijl de Wio Terminal niet is aangesloten op je computer of een andere stroombron, verbind je het andere uiteinde van de Grove-kabel met de rechter Grove-aansluiting op de Wio Terminal, zoals je naar het scherm kijkt. Dit is de aansluiting die het verst van de aan/uit-knop verwijderd is.

![De Grove bodemvochtsensor aangesloten op de rechteraansluiting](../../../../../translated_images/wio-soil-moisture-sensor.46919b61c3f6cb74.nl.png)

1. Steek de bodemvochtsensor in de grond. De sensor heeft een 'hoogste positie lijn' - een witte lijn over de sensor. Steek de sensor in de grond tot aan, maar niet voorbij deze lijn.

![De Grove bodemvochtsensor in de grond](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.nl.png)

1. Je kunt nu de Wio Terminal aansluiten op je computer.

## Programmeer de bodemvochtsensor

De Wio Terminal kan nu worden geprogrammeerd om de aangesloten bodemvochtsensor te gebruiken.

### Taak - programmeer de bodemvochtsensor

Programmeer het apparaat.

1. Maak een gloednieuw Wio Terminal-project met PlatformIO. Noem dit project `soil-moisture-sensor`. Voeg code toe in de `setup`-functie om de seriële poort te configureren.

    > ⚠️ Je kunt [de instructies voor het maken van een PlatformIO-project in project 1, les 1 raadplegen indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. Er is geen bibliotheek voor deze sensor, maar je kunt de analoge pin uitlezen met de ingebouwde Arduino-functie [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/). Begin met het configureren van de analoge pin voor invoer zodat waarden kunnen worden uitgelezen door het volgende toe te voegen aan de `setup`-functie.

    ```cpp
    pinMode(A0, INPUT);
    ```

    Dit stelt de `A0`-pin, de gecombineerde analoge/digitale pin, in als een invoerpin waarvan de spanning kan worden uitgelezen.

1. Voeg het volgende toe aan de `loop`-functie om de spanning van deze pin uit te lezen:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. Voeg onder deze code de volgende code toe om de waarde naar de seriële poort te printen:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. Voeg tot slot een vertraging van 10 seconden toe aan het einde:

    ```cpp
    delay(10000);
    ```

1. Bouw en upload de code naar de Wio Terminal.

    > ⚠️ Je kunt [de instructies voor het maken van een PlatformIO-project in project 1, les 1 raadplegen indien nodig](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. Zodra de code is geüpload, kun je het bodemvocht monitoren met de seriële monitor. Voeg wat water toe aan de grond of haal de sensor uit de grond en zie de waarde veranderen.

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

    In het voorbeeld hierboven kun je zien dat de spanning daalt wanneer er water wordt toegevoegd.

> 💁 Je kunt deze code vinden in de [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal) map.

😀 Je programma voor de bodemvochtsensor was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.