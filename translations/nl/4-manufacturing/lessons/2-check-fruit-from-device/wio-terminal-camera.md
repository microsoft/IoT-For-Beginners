<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-27T20:45:16+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "nl"
}
-->
# Maak een foto - Wio Terminal

In dit deel van de les voeg je een camera toe aan je Wio Terminal en maak je foto's met deze camera.

## Hardware

De Wio Terminal heeft een camera nodig.

De camera die je gaat gebruiken is een [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Dit is een 2 megapixel camera gebaseerd op de OV2640 beeldsensor. Hij communiceert via een SPI-interface om foto's te maken en gebruikt I²C om de sensor te configureren.

## Verbind de camera

De ArduCam heeft geen Grove-aansluiting, maar wordt in plaats daarvan verbonden met zowel de SPI- als de I²C-bussen via de GPIO-pinnen op de Wio Terminal.

### Taak - verbind de camera

Verbind de camera.

![Een ArduCam sensor](../../../../../translated_images/nl/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.png)

1. De pinnen aan de onderkant van de ArduCam moeten worden verbonden met de GPIO-pinnen op de Wio Terminal. Om het gemakkelijker te maken de juiste pinnen te vinden, plak je de GPIO-pinsticker die bij de Wio Terminal wordt geleverd rond de pinnen:

    ![De Wio Terminal met de GPIO-pinsticker](../../../../../translated_images/nl/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Gebruik jumperdraden om de volgende verbindingen te maken:

    | ArduCAM pin | Wio Terminal pin | Beschrijving                            |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI Chip Select                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI Controller Output, Peripheral Input |
    | MISO        | 21 (SPI_MISO)    | SPI Controller Input, Peripheral Output |
    | SCK         | 23 (SPI_SCLK)    | SPI Seriële Klok                        |
    | GND         | 6 (GND)          | Aarde - 0V                              |
    | VCC         | 4 (5V)           | 5V voedingsspanning                     |
    | SDA         | 3 (I2C1_SDA)     | I²C Seriële Data                        |
    | SCL         | 5 (I2C1_SCL)     | I²C Seriële Klok                        |

    ![De Wio Terminal verbonden met de ArduCam met jumperdraden](../../../../../translated_images/nl/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.png)

    De GND- en VCC-verbindingen leveren een 5V-voeding aan de ArduCam. Deze werkt op 5V, in tegenstelling tot Grove-sensoren die op 3V werken. Deze voeding komt rechtstreeks van de USB-C-aansluiting die het apparaat van stroom voorziet.

    > 💁 Voor de SPI-verbinding gebruiken de pinlabels op de ArduCam en de Wio Terminal-pinnamen in de code nog steeds de oude naamgevingsconventie. De instructies in deze les gebruiken de nieuwe naamgevingsconventie, behalve wanneer de pinnamen in de code worden gebruikt.

1. Je kunt nu de Wio Terminal aansluiten op je computer.

## Programmeer het apparaat om verbinding te maken met de camera

De Wio Terminal kan nu worden geprogrammeerd om de aangesloten ArduCAM-camera te gebruiken.

### Taak - programmeer het apparaat om verbinding te maken met de camera

1. Maak een nieuw Wio Terminal-project aan met PlatformIO. Noem dit project `fruit-quality-detector`. Voeg code toe in de `setup`-functie om de seriële poort te configureren.

1. Voeg code toe om verbinding te maken met WiFi, met je WiFi-inloggegevens in een bestand genaamd `config.h`. Vergeet niet de benodigde bibliotheken toe te voegen aan het `platformio.ini`-bestand.

1. De ArduCam-bibliotheek is niet beschikbaar als een Arduino-bibliotheek die kan worden geïnstalleerd via het `platformio.ini`-bestand. In plaats daarvan moet deze worden geïnstalleerd vanaf de bron op hun GitHub-pagina. Je kunt dit doen door:

    * De repo te klonen van [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Naar de repo op GitHub te gaan op [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) en de code als zip te downloaden via de **Code**-knop

1. Je hebt alleen de map `ArduCAM` uit deze code nodig. Kopieer de hele map naar de `lib`-map in je project.

    > ⚠️ De hele map moet worden gekopieerd, zodat de code in `lib/ArduCam` staat. Kopieer niet alleen de inhoud van de `ArduCam`-map naar de `lib`-map, maar kopieer de hele map.

1. De ArduCam-bibliotheekcode werkt voor meerdere soorten camera's. Het type camera dat je wilt gebruiken wordt geconfigureerd met compilerflags - dit houdt de gebouwde bibliotheek zo klein mogelijk door code voor camera's die je niet gebruikt te verwijderen. Om de bibliotheek te configureren voor de OV2640-camera, voeg je het volgende toe aan het einde van het `platformio.ini`-bestand:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Dit stelt 2 compilerflags in:

      * `ARDUCAM_SHIELD_V2` om de bibliotheek te vertellen dat de camera op een Arduino-bord zit, bekend als een shield.
      * `OV2640_CAM` om de bibliotheek te vertellen alleen code voor de OV2640-camera op te nemen.

1. Voeg een headerbestand toe in de `src`-map genaamd `camera.h`. Dit bevat code om te communiceren met de camera. Voeg de volgende code toe aan dit bestand:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    Dit is low-level code die de camera configureert met behulp van de ArduCam-bibliotheken en de afbeeldingen ophaalt wanneer nodig via de SPI-bus. Deze code is zeer specifiek voor de ArduCam, dus je hoeft je op dit moment geen zorgen te maken over hoe het werkt.

1. Voeg in `main.cpp` de volgende code toe onder de andere `include`-verklaringen om dit nieuwe bestand op te nemen en een instantie van de camera-klasse te maken:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Dit maakt een `Camera` die de afbeeldingen opslaat als JPEG's met een resolutie van 640 bij 480. Hoewel hogere resoluties worden ondersteund (tot 3280x2464), werkt de beeldclassificator met veel kleinere afbeeldingen (227x227), dus er is geen noodzaak om grotere afbeeldingen vast te leggen en te verzenden.

1. Voeg de volgende code hieronder toe om een functie te definiëren om de camera in te stellen:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    Deze `setupCamera`-functie begint met het configureren van de SPI-chipselectiepin (`PIN_SPI_SS`) als hoog, waardoor de Wio Terminal de SPI-controller wordt. Vervolgens start het de I²C- en SPI-bussen. Ten slotte initialiseert het de camera-klasse, die de instellingen van de camerasensor configureert en ervoor zorgt dat alles correct is aangesloten.

1. Roep deze functie aan aan het einde van de `setup`-functie:

    ```cpp
    setupCamera();
    ```

1. Bouw en upload deze code en controleer de uitvoer van de seriële monitor. Als je `Error setting up the camera!` ziet, controleer dan de bedrading om ervoor te zorgen dat alle kabels de juiste pinnen op de ArduCam verbinden met de juiste GPIO-pinnen op de Wio Terminal en dat alle jumperkabels goed vastzitten.

## Maak een foto

De Wio Terminal kan nu worden geprogrammeerd om een foto te maken wanneer een knop wordt ingedrukt.

### Taak - maak een foto

1. Microcontrollers voeren je code continu uit, dus het is niet eenvoudig om iets zoals het maken van een foto te activeren zonder te reageren op een sensor. De Wio Terminal heeft knoppen, dus de camera kan worden ingesteld om te worden geactiveerd door een van de knoppen. Voeg de volgende code toe aan het einde van de `setup`-functie om de C-knop (een van de drie knoppen bovenop, degene die het dichtst bij de aan/uit-schakelaar zit) te configureren.

    ![De C-knop bovenop, dicht bij de aan/uit-schakelaar](../../../../../translated_images/nl/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    De modus `INPUT_PULLUP` keert een invoer in feite om. Normaal gesproken zou een knop een laag signaal sturen wanneer niet ingedrukt en een hoog signaal wanneer ingedrukt. Wanneer ingesteld op `INPUT_PULLUP`, sturen ze een hoog signaal wanneer niet ingedrukt en een laag signaal wanneer ingedrukt.

1. Voeg een lege functie toe om te reageren op het indrukken van de knop vóór de `loop`-functie:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Roep deze functie aan in de `loop`-methode wanneer de knop wordt ingedrukt:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    Deze toets controleert of de knop is ingedrukt. Als dat het geval is, wordt de `buttonPressed`-functie aangeroepen en wacht de lus 2 seconden. Dit is om tijd te geven om de knop los te laten, zodat een lange druk niet twee keer wordt geregistreerd.

    > 💁 De knop op de Wio Terminal is ingesteld op `INPUT_PULLUP`, dus stuurt een hoog signaal wanneer niet ingedrukt en een laag signaal wanneer ingedrukt.

1. Voeg de volgende code toe aan de `buttonPressed`-functie:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    Deze code start de cameracapturing door `startCapture` aan te roepen. De camera-hardware werkt niet door de gegevens terug te geven wanneer je erom vraagt; in plaats daarvan stuur je een instructie om te beginnen met vastleggen, en de camera werkt op de achtergrond om de afbeelding vast te leggen, om te zetten naar een JPEG en op te slaan in een lokale buffer op de camera zelf. De `captureReady`-aanroep controleert vervolgens of het vastleggen van de afbeelding is voltooid.

    Zodra het vastleggen is voltooid, worden de afbeeldingsgegevens gekopieerd van de buffer op de camera naar een lokale buffer (een array van bytes) met de `readImageToBuffer`-aanroep. De lengte van de buffer wordt vervolgens naar de seriële monitor gestuurd.

1. Bouw en upload deze code en controleer de uitvoer op de seriële monitor. Elke keer dat je op de C-knop drukt, wordt een afbeelding vastgelegd en zie je de afbeeldingsgrootte op de seriële monitor.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Verschillende afbeeldingen hebben verschillende groottes. Ze worden gecomprimeerd als JPEG's en de grootte van een JPEG-bestand voor een bepaalde resolutie hangt af van wat er in de afbeelding staat.

> 💁 Je kunt deze code vinden in de map [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Je hebt met succes afbeeldingen vastgelegd met je Wio Terminal.

## Optioneel - controleer de camerabeelden met een SD-kaart

De eenvoudigste manier om de afbeeldingen te bekijken die door de camera zijn vastgelegd, is door ze op een SD-kaart in de Wio Terminal te schrijven en ze vervolgens op je computer te bekijken. Doe deze stap als je een reserve microSD-kaart en een microSD-kaartsleuf in je computer hebt, of een adapter.

De Wio Terminal ondersteunt alleen microSD-kaarten tot 16GB. Als je een grotere SD-kaart hebt, werkt deze niet.

### Taak - controleer de camerabeelden met een SD-kaart

1. Formatteer een microSD-kaart als FAT32 of exFAT met de relevante applicaties op je computer (Schijfhulpprogramma op macOS, Verkenner op Windows, of met opdrachtregeltools in Linux).

1. Plaats de microSD-kaart in de sleuf net onder de aan/uit-schakelaar. Zorg ervoor dat deze helemaal erin zit totdat deze klikt en op zijn plaats blijft. Mogelijk moet je deze met een vingernagel of een dun gereedschap aanduwen.

1. Voeg de volgende include-verklaringen toe bovenaan het `main.cpp`-bestand:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Voeg de volgende functie toe vóór de `setup`-functie:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Dit configureert de SD-kaart met behulp van de SPI-bus.

1. Roep dit aan vanuit de `setup`-functie:

    ```cpp
    setupSDCard();
    ```

1. Voeg de volgende code toe boven de `buttonPressed`-functie:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    Dit definieert een globale variabele voor een bestandsteller. Deze wordt gebruikt voor de bestandsnamen van de afbeeldingen, zodat meerdere afbeeldingen kunnen worden vastgelegd met oplopende bestandsnamen - `1.jpg`, `2.jpg`, enzovoort.

    Vervolgens definieert het de `saveToSDCard`-functie die een buffer met bytegegevens en de lengte van de buffer neemt. Een bestandsnaam wordt gemaakt met behulp van de bestandsteller en de teller wordt verhoogd voor het volgende bestand. De binaire gegevens uit de buffer worden vervolgens naar het bestand geschreven.

1. Roep de `saveToSDCard`-functie aan vanuit de `buttonPressed`-functie. De aanroep moet **voor** de buffer wordt verwijderd:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Bouw en upload deze code en controleer de uitvoer op de seriële monitor. Elke keer dat je op de C-knop drukt, wordt een afbeelding vastgelegd en opgeslagen op de SD-kaart.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. Schakel de microSD-kaart uit en verwijder deze door deze iets in te drukken en los te laten, waarna deze eruit springt. Mogelijk moet je hiervoor een dun gereedschap gebruiken. Steek de microSD-kaart in je computer om de afbeeldingen te bekijken.

    ![Een foto van een banaan gemaakt met de ArduCam](../../../../../translated_images/nl/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.jpg)
💁 Het kan enkele beelden duren voordat de witbalans van de camera zichzelf aanpast. Je zult dit merken aan de kleur van de vastgelegde beelden, de eerste paar kunnen er qua kleur afwijkend uitzien. Je kunt dit altijd omzeilen door de code aan te passen om enkele beelden vast te leggen die worden genegeerd in de `setup`-functie.


---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in de oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.