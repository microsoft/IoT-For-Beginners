<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-25T21:02:27+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "de"
}
-->
# Ein Bild aufnehmen - Wio Terminal

In diesem Teil der Lektion fügen Sie Ihrem Wio Terminal eine Kamera hinzu und nehmen Bilder damit auf.

## Hardware

Das Wio Terminal benötigt eine Kamera.

Die Kamera, die Sie verwenden werden, ist eine [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Dies ist eine 2-Megapixel-Kamera, die auf dem OV2640-Bildsensor basiert. Sie kommuniziert über eine SPI-Schnittstelle, um Bilder aufzunehmen, und verwendet I2C, um den Sensor zu konfigurieren.

## Kamera anschließen

Die ArduCam hat keinen Grove-Anschluss, sondern wird über die GPIO-Pins des Wio Terminals sowohl mit den SPI- als auch den I2C-Bussen verbunden.

### Aufgabe - Kamera anschließen

Schließen Sie die Kamera an.

![Ein ArduCam-Sensor](../../../../../translated_images/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.de.png)

1. Die Pins an der Unterseite der ArduCam müssen mit den GPIO-Pins des Wio Terminals verbunden werden. Um die richtigen Pins leichter zu finden, befestigen Sie den GPIO-Pin-Aufkleber, der mit dem Wio Terminal geliefert wird, um die Pins:

    ![Das Wio Terminal mit dem GPIO-Pin-Aufkleber](../../../../../translated_images/wio-terminal-pin-sticker.b90b1535937b84bd.de.png)

1. Verwenden Sie Jumperkabel, um die folgenden Verbindungen herzustellen:

    | ArduCAM-Pin | Wio Terminal-Pin | Beschreibung                            |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | SPI Chip Select                         |
    | MOSI        | 19 (SPI_MOSI)    | SPI Controller Output, Peripheral Input |
    | MISO        | 21 (SPI_MISO)    | SPI Controller Input, Peripheral Output |
    | SCK         | 23 (SPI_SCLK)    | SPI Serial Clock                        |
    | GND         | 6 (GND)          | Masse - 0V                              |
    | VCC         | 4 (5V)           | 5V Stromversorgung                      |
    | SDA         | 3 (I2C1_SDA)     | I2C Serial Data                         |
    | SCL         | 5 (I2C1_SCL)     | I2C Serial Clock                        |

    ![Das Wio Terminal mit der ArduCam verbunden durch Jumperkabel](../../../../../translated_images/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.de.png)

    Die GND- und VCC-Verbindungen liefern eine 5V-Stromversorgung an die ArduCam. Sie läuft mit 5V, im Gegensatz zu Grove-Sensoren, die mit 3V betrieben werden. Diese Stromversorgung kommt direkt von der USB-C-Verbindung, die das Gerät mit Strom versorgt.

    > 💁 Für die SPI-Verbindung verwenden die Pin-Beschriftungen auf der ArduCam und die in Code verwendeten Wio Terminal-Pinnamen noch die alte Namenskonvention. Die Anweisungen in dieser Lektion verwenden die neue Namenskonvention, außer wenn die Pinnamen im Code verwendet werden.

1. Sie können das Wio Terminal jetzt mit Ihrem Computer verbinden.

## Gerät programmieren, um die Kamera zu verbinden

Das Wio Terminal kann jetzt so programmiert werden, dass es die angeschlossene ArduCAM-Kamera verwendet.

### Aufgabe - Gerät programmieren, um die Kamera zu verbinden

1. Erstellen Sie ein brandneues Wio Terminal-Projekt mit PlatformIO. Nennen Sie dieses Projekt `fruit-quality-detector`. Fügen Sie Code in die `setup`-Funktion ein, um die serielle Schnittstelle zu konfigurieren.

1. Fügen Sie Code hinzu, um eine Verbindung zu WiFi herzustellen, mit Ihren WiFi-Zugangsdaten in einer Datei namens `config.h`. Vergessen Sie nicht, die erforderlichen Bibliotheken in die Datei `platformio.ini` aufzunehmen.

1. Die ArduCam-Bibliothek ist nicht als Arduino-Bibliothek verfügbar, die über die Datei `platformio.ini` installiert werden kann. Stattdessen muss sie aus dem Quellcode von ihrer GitHub-Seite installiert werden. Sie können dies entweder tun, indem Sie:

    * Das Repository von [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git) klonen
    * Zur GitHub-Seite des Repos unter [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) gehen und den Code als ZIP-Datei über die **Code**-Schaltfläche herunterladen

1. Sie benötigen nur den Ordner `ArduCAM` aus diesem Code. Kopieren Sie den gesamten Ordner in den `lib`-Ordner Ihres Projekts.

    > ⚠️ Der gesamte Ordner muss kopiert werden, sodass der Code in `lib/ArduCam` liegt. Kopieren Sie nicht nur den Inhalt des Ordners `ArduCam` in den `lib`-Ordner, sondern den gesamten Ordner.

1. Der Code der ArduCam-Bibliothek funktioniert für mehrere Kameratypen. Der Kameratyp, den Sie verwenden möchten, wird mit Compiler-Flags konfiguriert – dies hält die Bibliothek so klein wie möglich, indem Code für Kameras entfernt wird, die Sie nicht verwenden. Um die Bibliothek für die OV2640-Kamera zu konfigurieren, fügen Sie Folgendes am Ende der Datei `platformio.ini` hinzu:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Dies setzt zwei Compiler-Flags:

      * `ARDUCAM_SHIELD_V2`, um der Bibliothek mitzuteilen, dass die Kamera auf einem Arduino-Board (Shield) ist.
      * `OV2640_CAM`, um der Bibliothek mitzuteilen, dass nur Code für die OV2640-Kamera enthalten sein soll.

1. Fügen Sie eine Header-Datei in den Ordner `src` ein, die `camera.h` heißt. Diese Datei enthält Code, um mit der Kamera zu kommunizieren. Fügen Sie den folgenden Code in diese Datei ein:

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

    Dies ist Low-Level-Code, der die Kamera mit den ArduCam-Bibliotheken konfiguriert und die Bilder bei Bedarf über den SPI-Bus extrahiert. Dieser Code ist sehr spezifisch für die ArduCam, sodass Sie sich an dieser Stelle keine Gedanken darüber machen müssen, wie er funktioniert.

1. Fügen Sie in `main.cpp` den folgenden Code unter den anderen `include`-Anweisungen ein, um diese neue Datei einzubinden und eine Instanz der Kamera-Klasse zu erstellen:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Dies erstellt eine `Camera`, die die Bilder als JPEGs mit einer Auflösung von 640 x 480 speichert. Obwohl höhere Auflösungen unterstützt werden (bis zu 3280x2464), arbeitet der Bildklassifikator mit viel kleineren Bildern (227x227), sodass es nicht notwendig ist, größere Bilder aufzunehmen und zu senden.

1. Fügen Sie den folgenden Code darunter ein, um eine Funktion zur Einrichtung der Kamera zu definieren:

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

    Diese Funktion `setupCamera` beginnt damit, den SPI-Chip-Select-Pin (`PIN_SPI_SS`) als hoch zu konfigurieren, wodurch das Wio Terminal zum SPI-Controller wird. Anschließend werden die I2C- und SPI-Busse gestartet. Schließlich initialisiert sie die Kamera-Klasse, die die Kamera-Sensoreinstellungen konfiguriert und sicherstellt, dass alles korrekt verdrahtet ist.

1. Rufen Sie diese Funktion am Ende der `setup`-Funktion auf:

    ```cpp
    setupCamera();
    ```

1. Bauen und laden Sie diesen Code hoch und überprüfen Sie die Ausgabe im seriellen Monitor. Wenn Sie `Error setting up the camera!` sehen, überprüfen Sie die Verkabelung, um sicherzustellen, dass alle Kabel die richtigen Pins auf der ArduCam mit den richtigen GPIO-Pins auf dem Wio Terminal verbinden und alle Jumperkabel korrekt sitzen.

## Ein Bild aufnehmen

Das Wio Terminal kann jetzt so programmiert werden, dass ein Bild aufgenommen wird, wenn eine Taste gedrückt wird.

### Aufgabe - Ein Bild aufnehmen

1. Mikrocontroller führen Ihren Code kontinuierlich aus, daher ist es nicht einfach, etwas wie das Aufnehmen eines Fotos auszulösen, ohne auf einen Sensor zu reagieren. Das Wio Terminal hat Tasten, sodass die Kamera so eingerichtet werden kann, dass sie durch eine der Tasten ausgelöst wird. Fügen Sie den folgenden Code am Ende der `setup`-Funktion hinzu, um die C-Taste (eine der drei Tasten oben, diejenige, die dem Netzschalter am nächsten ist) zu konfigurieren.

    ![Die C-Taste oben, die dem Netzschalter am nächsten ist](../../../../../translated_images/wio-terminal-c-button.73df3cb1c1445ea0.de.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Der Modus `INPUT_PULLUP` invertiert im Wesentlichen ein Eingangssignal. Zum Beispiel würde eine Taste normalerweise ein niedriges Signal senden, wenn sie nicht gedrückt wird, und ein hohes Signal, wenn sie gedrückt wird. Wenn sie auf `INPUT_PULLUP` gesetzt ist, sendet sie ein hohes Signal, wenn sie nicht gedrückt wird, und ein niedriges Signal, wenn sie gedrückt wird.

1. Fügen Sie vor der `loop`-Funktion eine leere Funktion hinzu, um auf das Drücken der Taste zu reagieren:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Rufen Sie diese Funktion in der `loop`-Methode auf, wenn die Taste gedrückt wird:

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

    Dieser Code prüft, ob die Taste gedrückt ist. Wenn sie gedrückt ist, wird die Funktion `buttonPressed` aufgerufen, und die Schleife verzögert sich um 2 Sekunden. Dies gibt Zeit, damit die Taste losgelassen wird, sodass ein langer Tastendruck nicht zweimal registriert wird.

    > 💁 Die Taste am Wio Terminal ist auf `INPUT_PULLUP` gesetzt, sodass sie ein hohes Signal sendet, wenn sie nicht gedrückt wird, und ein niedriges Signal, wenn sie gedrückt wird.

1. Fügen Sie der Funktion `buttonPressed` den folgenden Code hinzu:

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

    Dieser Code startet die Bildaufnahme, indem er `startCapture` aufruft. Die Kamera-Hardware funktioniert nicht, indem sie die Daten zurückgibt, wenn Sie sie anfordern. Stattdessen senden Sie eine Anweisung, um die Aufnahme zu starten, und die Kamera arbeitet im Hintergrund, um das Bild aufzunehmen, es in ein JPEG zu konvertieren und es in einem lokalen Puffer auf der Kamera selbst zu speichern. Der Aufruf `captureReady` prüft dann, ob die Bildaufnahme abgeschlossen ist.

    Sobald die Aufnahme abgeschlossen ist, werden die Bilddaten mit dem Aufruf `readImageToBuffer` aus dem Puffer der Kamera in einen lokalen Puffer (ein Byte-Array) kopiert. Die Länge des Puffers wird dann an den seriellen Monitor gesendet.

1. Bauen und laden Sie diesen Code hoch und überprüfen Sie die Ausgabe im seriellen Monitor. Jedes Mal, wenn Sie die C-Taste drücken, wird ein Bild aufgenommen, und Sie sehen die Bildgröße, die an den seriellen Monitor gesendet wird.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Unterschiedliche Bilder haben unterschiedliche Größen. Sie werden als JPEGs komprimiert, und die Größe einer JPEG-Datei für eine bestimmte Auflösung hängt davon ab, was im Bild enthalten ist.

> 💁 Sie finden diesen Code im Ordner [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Sie haben erfolgreich Bilder mit Ihrem Wio Terminal aufgenommen.

## Optional - Kamera-Bilder mit einer SD-Karte überprüfen

Der einfachste Weg, die von der Kamera aufgenommenen Bilder zu sehen, besteht darin, sie auf eine SD-Karte im Wio Terminal zu schreiben und sie dann auf Ihrem Computer anzusehen. Führen Sie diesen Schritt aus, wenn Sie eine freie microSD-Karte und einen microSD-Kartensteckplatz in Ihrem Computer oder einen Adapter haben.

Das Wio Terminal unterstützt nur microSD-Karten mit einer Größe von bis zu 16 GB. Wenn Sie eine größere SD-Karte haben, funktioniert sie nicht.

### Aufgabe - Kamera-Bilder mit einer SD-Karte überprüfen

1. Formatieren Sie eine microSD-Karte als FAT32 oder exFAT mit den entsprechenden Anwendungen auf Ihrem Computer (Festplattendienstprogramm auf macOS, Datei-Explorer auf Windows oder mit Befehlszeilentools unter Linux).

1. Legen Sie die microSD-Karte in den Steckplatz direkt unter dem Netzschalter ein. Stellen Sie sicher, dass sie vollständig eingesteckt ist, bis sie einrastet und an Ort und Stelle bleibt. Möglicherweise müssen Sie sie mit einem Fingernagel oder einem dünnen Werkzeug hineindrücken.

1. Fügen Sie die folgenden Include-Anweisungen oben in der Datei `main.cpp` hinzu:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Fügen Sie die folgende Funktion vor der `setup`-Funktion hinzu:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Diese Funktion konfiguriert die SD-Karte über den SPI-Bus.

1. Rufen Sie diese Funktion aus der `setup`-Funktion auf:

    ```cpp
    setupSDCard();
    ```

1. Fügen Sie den folgenden Code oberhalb der Funktion `buttonPressed` hinzu:

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

    Dies definiert eine globale Variable für eine Dateizählung. Diese wird für die Bilddateinamen verwendet, sodass mehrere Bilder mit aufsteigenden Dateinamen aufgenommen werden können – `1.jpg`, `2.jpg` und so weiter.

    Anschließend wird die Funktion `saveToSDCard` definiert, die einen Puffer mit Byte-Daten und die Länge des Puffers übernimmt. Ein Dateiname wird mit der Dateizählung erstellt, und die Dateizählung wird für die nächste Datei inkrementiert. Die Binärdaten aus dem Puffer werden dann in die Datei geschrieben.

1. Rufen Sie die Funktion `saveToSDCard` aus der Funktion `buttonPressed` auf. Der Aufruf sollte **vor** dem Löschen des Puffers erfolgen:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Bauen und laden Sie diesen Code hoch und überprüfen Sie die Ausgabe im seriellen Monitor. Jedes Mal, wenn Sie die C-Taste drücken, wird ein Bild aufgenommen und auf der SD-Karte gespeichert.

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

1. Schalten Sie das Gerät aus und entfernen Sie die microSD-Karte, indem Sie sie leicht hineindrücken und loslassen. Sie wird herausspringen. Möglicherweise müssen Sie ein dünnes Werkzeug verwenden, um dies zu tun. Stecken Sie die microSD-Karte in Ihren Computer, um die Bilder anzusehen.

    ![Ein Bild einer Banane, aufgenommen mit der ArduCam](../../../../../translated_images/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.de.jpg)
💁 Es kann einige Bilder dauern, bis sich der Weißabgleich der Kamera selbst eingestellt hat. Dies werden Sie anhand der Farbe der aufgenommenen Bilder bemerken, die ersten paar könnten farblich abweichen. Sie können dies umgehen, indem Sie den Code so ändern, dass einige Bilder aufgenommen werden, die in der `setup`-Funktion ignoriert werden.


**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.