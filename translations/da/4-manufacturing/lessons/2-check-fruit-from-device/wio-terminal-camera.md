<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-27T20:44:15+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "da"
}
-->
# Tag et billede - Wio Terminal

I denne del af lektionen vil du tilføje et kamera til din Wio Terminal og tage billeder med det.

## Hardware

Wio Terminalen har brug for et kamera.

Kameraet, du skal bruge, er en [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Dette er et 2 megapixel kamera baseret på OV2640 billedsensoren. Det kommunikerer via en SPI-grænseflade for at tage billeder og bruger I2C til at konfigurere sensoren.

## Tilslut kameraet

ArduCam har ikke en Grove-sokkel, men forbinder i stedet til både SPI- og I2C-busserne via GPIO-pindene på Wio Terminalen.

### Opgave - tilslut kameraet

Tilslut kameraet.

![En ArduCam sensor](../../../../../translated_images/da/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.png)

1. Pindene på bunden af ArduCam skal forbindes til GPIO-pindene på Wio Terminalen. For at gøre det nemmere at finde de rigtige pins, skal du sætte GPIO-pin-klistermærket, der følger med Wio Terminalen, rundt om pindene:

    ![Wio Terminal med GPIO-pin-klistermærket på](../../../../../translated_images/da/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Brug jumperkabler til at lave følgende forbindelser:

    | ArduCAM pin | Wio Terminal pin | Beskrivelse                             |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI Chip Select                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI Controller Output, Peripheral Input |
    | MISO        | 21 (SPI_MISO)    | SPI Controller Input, Peripheral Output |
    | SCK         | 23 (SPI_SCLK)    | SPI Serial Clock                        |
    | GND         | 6 (GND)          | Jord - 0V                               |
    | VCC         | 4 (5V)           | 5V strømforsyning                       |
    | SDA         | 3 (I2C1_SDA)     | I2C Serial Data                         |
    | SCL         | 5 (I2C1_SCL)     | I2C Serial Clock                        |

    ![Wio Terminal forbundet til ArduCam med jumperkabler](../../../../../translated_images/da/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.png)

    GND- og VCC-forbindelserne leverer en 5V strømforsyning til ArduCam. Det kører på 5V, i modsætning til Grove-sensorer, der kører på 3V. Denne strøm kommer direkte fra USB-C-forbindelsen, der forsyner enheden.

    > 💁 For SPI-forbindelsen bruger pin-navnene på ArduCam og Wio Terminalen stadig den gamle navngivningskonvention i koden. Instruktionerne i denne lektion vil bruge den nye navngivningskonvention, undtagen når pin-navnene bruges i koden.

1. Du kan nu forbinde Wio Terminalen til din computer.

## Programmer enheden til at forbinde til kameraet

Wio Terminalen kan nu programmeres til at bruge det tilsluttede ArduCAM-kamera.

### Opgave - programmer enheden til at forbinde til kameraet

1. Opret et helt nyt Wio Terminal-projekt ved hjælp af PlatformIO. Kald dette projekt `fruit-quality-detector`. Tilføj kode i `setup`-funktionen for at konfigurere den serielle port.

1. Tilføj kode for at forbinde til WiFi med dine WiFi-oplysninger i en fil kaldet `config.h`. Husk at tilføje de nødvendige biblioteker til `platformio.ini`-filen.

1. ArduCam-biblioteket er ikke tilgængeligt som et Arduino-bibliotek, der kan installeres fra `platformio.ini`-filen. I stedet skal det installeres fra kildekoden fra deres GitHub-side. Du kan få det ved enten at:

    * Klone repoen fra [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Gå til repoen på GitHub på [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) og downloade koden som en zip-fil fra **Code**-knappen

1. Du skal kun bruge `ArduCAM`-mappen fra denne kode. Kopier hele mappen ind i `lib`-mappen i dit projekt.

    > ⚠️ Hele mappen skal kopieres, så koden er i `lib/ArduCam`. Kopier ikke kun indholdet af `ArduCam`-mappen ind i `lib`-mappen, men kopier hele mappen.

1. ArduCam-bibliotekskoden fungerer for flere typer kameraer. Den type kamera, du vil bruge, konfigureres ved hjælp af compiler-flags - dette holder det kompilerede bibliotek så lille som muligt ved at fjerne kode for kameraer, du ikke bruger. For at konfigurere biblioteket til OV2640-kameraet skal du tilføje følgende til slutningen af `platformio.ini`-filen:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Dette sætter 2 compiler-flags:

      * `ARDUCAM_SHIELD_V2` for at fortælle biblioteket, at kameraet er på et Arduino-board, kendt som et shield.
      * `OV2640_CAM` for at fortælle biblioteket kun at inkludere kode til OV2640-kameraet.

1. Tilføj en headerfil i `src`-mappen kaldet `camera.h`. Denne vil indeholde kode til at kommunikere med kameraet. Tilføj følgende kode til denne fil:

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

    Dette er lav-niveau kode, der konfigurerer kameraet ved hjælp af ArduCam-bibliotekerne og henter billederne, når det er nødvendigt, ved hjælp af SPI-bussen. Denne kode er meget specifik for ArduCam, så du behøver ikke bekymre dig om, hvordan den fungerer på nuværende tidspunkt.

1. I `main.cpp` skal du tilføje følgende kode under de andre `include`-udsagn for at inkludere denne nye fil og oprette en instans af kamera-klassen:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Dette opretter et `Camera`, der gemmer billeder som JPEG'er i en opløsning på 640 x 480. Selvom højere opløsninger understøttes (op til 3280x2464), fungerer billedklassifikatoren på meget mindre billeder (227x227), så der er ingen grund til at tage og sende større billeder.

1. Tilføj følgende kode nedenfor for at definere en funktion til at konfigurere kameraet:

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

    Denne `setupCamera`-funktion starter med at konfigurere SPI chip select-pinden (`PIN_SPI_SS`) som høj, hvilket gør Wio Terminalen til SPI-controlleren. Derefter starter den I2C- og SPI-busserne. Til sidst initialiserer den kamera-klassen, som konfigurerer kameraets sensors indstillinger og sikrer, at alt er korrekt forbundet.

1. Kald denne funktion i slutningen af `setup`-funktionen:

    ```cpp
    setupCamera();
    ```

1. Byg og upload denne kode, og tjek outputtet fra den serielle monitor. Hvis du ser `Error setting up the camera!`, skal du tjekke ledningsforbindelserne for at sikre, at alle kabler forbinder de korrekte pins på ArduCam til de korrekte GPIO-pins på Wio Terminalen, og at alle jumperkabler sidder korrekt.

## Tag et billede

Wio Terminalen kan nu programmeres til at tage et billede, når en knap trykkes.

### Opgave - tag et billede

1. Mikrokontrollere kører din kode kontinuerligt, så det er ikke nemt at udløse noget som at tage et billede uden at reagere på en sensor. Wio Terminalen har knapper, så kameraet kan sættes op til at blive udløst af en af knapperne. Tilføj følgende kode til slutningen af `setup`-funktionen for at konfigurere C-knappen (en af de tre knapper på toppen, den der er tættest på tænd/sluk-knappen).

    ![C-knappen på toppen tættest på tænd/sluk-knappen](../../../../../translated_images/da/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Tilstanden `INPUT_PULLUP` inverterer i bund og grund en input. For eksempel vil en knap normalt sende et lavt signal, når den ikke er trykket, og et højt signal, når den er trykket. Når den er sat til `INPUT_PULLUP`, sender den et højt signal, når den ikke er trykket, og et lavt signal, når den er trykket.

1. Tilføj en tom funktion til at reagere på knaptrykket før `loop`-funktionen:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Kald denne funktion i `loop`-metoden, når knappen trykkes:

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

    Denne nøgle tjekker, om knappen er trykket. Hvis den er trykket, kaldes `buttonPressed`-funktionen, og loopet forsinkes i 2 sekunder. Dette er for at give tid til, at knappen kan frigives, så et langt tryk ikke registreres to gange.

    > 💁 Knapperne på Wio Terminalen er sat til `INPUT_PULLUP`, så de sender et højt signal, når de ikke er trykket, og et lavt signal, når de er trykket.

1. Tilføj følgende kode til `buttonPressed`-funktionen:

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

    Denne kode starter kameraoptagelsen ved at kalde `startCapture`. Kameraets hardware fungerer ikke ved at returnere data, når du anmoder om det. I stedet sender du en instruktion om at starte optagelsen, og kameraet arbejder i baggrunden for at tage billedet, konvertere det til en JPEG og gemme det i en lokal buffer på selve kameraet. Kaldet `captureReady` tjekker derefter, om billedoptagelsen er færdig.

    Når optagelsen er færdig, kopieres billeddataene fra bufferen på kameraet til en lokal buffer (en byte-array) med kaldet `readImageToBuffer`. Længden af bufferen sendes derefter til den serielle monitor.

1. Byg og upload denne kode, og tjek outputtet på den serielle monitor. Hver gang du trykker på C-knappen, tages et billede, og du vil se billedstørrelsen sendt til den serielle monitor.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Forskellige billeder vil have forskellige størrelser. De er komprimeret som JPEG'er, og størrelsen af en JPEG-fil for en given opløsning afhænger af, hvad der er i billedet.

> 💁 Du kan finde denne kode i [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal)-mappen.

😀 Du har med succes taget billeder med din Wio Terminal.

## Valgfrit - verificer kameraets billeder ved hjælp af et SD-kort

Den nemmeste måde at se de billeder, der blev taget af kameraet, er at skrive dem til et SD-kort i Wio Terminalen og derefter se dem på din computer. Gør dette trin, hvis du har et ekstra microSD-kort og en microSD-kortlæser i din computer eller en adapter.

Wio Terminalen understøtter kun microSD-kort på op til 16GB. Hvis du har et større SD-kort, vil det ikke fungere.

### Opgave - verificer kameraets billeder ved hjælp af et SD-kort

1. Formater et microSD-kort som FAT32 eller exFAT ved hjælp af de relevante applikationer på din computer (Disk Utility på macOS, File Explorer på Windows eller kommandolinjeværktøjer i Linux).

1. Indsæt microSD-kortet i soklen lige under tænd/sluk-knappen. Sørg for, at det er helt inde, indtil det klikker og bliver siddende. Du skal muligvis skubbe det ind med en negl eller et tyndt værktøj.

1. Tilføj følgende include-udsagn øverst i `main.cpp`-filen:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Tilføj følgende funktion før `setup`-funktionen:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Dette konfigurerer SD-kortet ved hjælp af SPI-bussen.

1. Kald denne fra `setup`-funktionen:

    ```cpp
    setupSDCard();
    ```

1. Tilføj følgende kode over `buttonPressed`-funktionen:

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

    Dette definerer en global variabel til en filtæller. Denne bruges til billedfilnavne, så flere billeder kan gemmes med stigende filnavne - `1.jpg`, `2.jpg` osv.

    Derefter defineres `saveToSDCard`, som tager en buffer af byte-data og længden af bufferen. Et filnavn oprettes ved hjælp af filtælleren, og filtælleren øges, så den er klar til næste fil. De binære data fra bufferen skrives derefter til filen.

1. Kald `saveToSDCard`-funktionen fra `buttonPressed`-funktionen. Kaldet skal være **før** bufferen slettes:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Byg og upload denne kode, og tjek outputtet på den serielle monitor. Hver gang du trykker på C-knappen, tages et billede og gemmes på SD-kortet.

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

1. Sluk for microSD-kortet og fjern det ved at skubbe det lidt ind og slippe, så det springer ud. Du skal muligvis bruge et tyndt værktøj til dette. Sæt microSD-kortet i din computer for at se billederne.

    ![Et billede af en banan taget med ArduCam](../../../../../translated_images/da/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.jpg)
> 💁 Det kan tage et par billeder, før kameraets hvidbalance justerer sig selv. Du vil bemærke dette baseret på farven på de billeder, der bliver taget, de første par kan se ud til at have forkert farve. Du kan altid omgå dette ved at ændre koden til at tage et par billeder, der ignoreres i `setup`-funktionen.


---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.