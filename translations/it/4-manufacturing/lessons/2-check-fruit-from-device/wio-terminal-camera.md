<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-25T16:33:30+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "it"
}
-->
# Catturare un'immagine - Wio Terminal

In questa parte della lezione, aggiungerai una fotocamera al tuo Wio Terminal e catturerai immagini con essa.

## Hardware

Il Wio Terminal necessita di una fotocamera.

La fotocamera che utilizzerai è una [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Si tratta di una fotocamera da 2 megapixel basata sul sensore d'immagine OV2640. Comunica tramite un'interfaccia SPI per catturare immagini e utilizza I2C per configurare il sensore.

## Collegare la fotocamera

L'ArduCam non ha un connettore Grove, ma si collega ai bus SPI e I2C tramite i pin GPIO del Wio Terminal.

### Attività - collegare la fotocamera

Collega la fotocamera.

![Un sensore ArduCam](../../../../../translated_images/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.it.png)

1. I pin alla base dell'ArduCam devono essere collegati ai pin GPIO del Wio Terminal. Per facilitare l'individuazione dei pin corretti, applica l'adesivo dei pin GPIO fornito con il Wio Terminal attorno ai pin:

    ![Il Wio Terminal con l'adesivo dei pin GPIO applicato](../../../../../translated_images/wio-terminal-pin-sticker.b90b1535937b84bd.it.png)

1. Utilizzando dei cavi jumper, effettua i seguenti collegamenti:

    | Pin ArduCAM | Pin Wio Terminal | Descrizione                             |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | Selezione chip SPI                      |
    | MOSI        | 19 (SPI_MOSI)    | Uscita controller SPI, ingresso periferica |
    | MISO        | 21 (SPI_MISO)    | Ingresso controller SPI, uscita periferica |
    | SCK         | 23 (SPI_SCLK)    | Clock seriale SPI                       |
    | GND         | 6 (GND)          | Massa - 0V                              |
    | VCC         | 4 (5V)           | Alimentazione 5V                        |
    | SDA         | 3 (I2C1_SDA)     | Dati seriali I2C                        |
    | SCL         | 5 (I2C1_SCL)     | Clock seriale I2C                       |

    ![Il Wio Terminal collegato all'ArduCam con cavi jumper](../../../../../translated_images/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.it.png)

    I collegamenti GND e VCC forniscono un'alimentazione di 5V all'ArduCam. Funziona a 5V, a differenza dei sensori Grove che funzionano a 3V. Questa alimentazione proviene direttamente dalla connessione USB-C che alimenta il dispositivo.

    > 💁 Per la connessione SPI, le etichette dei pin sull'ArduCam e i nomi dei pin del Wio Terminal utilizzati nel codice seguono ancora la vecchia convenzione di denominazione. Le istruzioni in questa lezione utilizzeranno la nuova convenzione di denominazione, tranne quando i nomi dei pin sono usati nel codice.

1. Ora puoi collegare il Wio Terminal al tuo computer.

## Programmare il dispositivo per connettersi alla fotocamera

Ora il Wio Terminal può essere programmato per utilizzare la fotocamera ArduCAM collegata.

### Attività - programmare il dispositivo per connettersi alla fotocamera

1. Crea un nuovo progetto per il Wio Terminal utilizzando PlatformIO. Chiama questo progetto `fruit-quality-detector`. Aggiungi del codice nella funzione `setup` per configurare la porta seriale.

1. Aggiungi il codice per connetterti al WiFi, con le tue credenziali WiFi in un file chiamato `config.h`. Non dimenticare di aggiungere le librerie necessarie al file `platformio.ini`.

1. La libreria ArduCam non è disponibile come libreria Arduino installabile dal file `platformio.ini`. Dovrà essere installata dal loro repository GitHub. Puoi ottenerla in uno dei seguenti modi:

    * Clonando il repository da [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Visitando il repository su GitHub all'indirizzo [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) e scaricando il codice come file zip dal pulsante **Code**

1. Hai bisogno solo della cartella `ArduCAM` da questo codice. Copia l'intera cartella nella cartella `lib` del tuo progetto.

    > ⚠️ L'intera cartella deve essere copiata, quindi il codice deve trovarsi in `lib/ArduCam`. Non copiare solo il contenuto della cartella `ArduCam` nella cartella `lib`, copia l'intera cartella.

1. Il codice della libreria ArduCam funziona per diversi tipi di fotocamere. Il tipo di fotocamera che vuoi utilizzare è configurato tramite flag del compilatore, il che mantiene la libreria compilata il più piccola possibile rimuovendo il codice per fotocamere che non stai utilizzando. Per configurare la libreria per la fotocamera OV2640, aggiungi quanto segue alla fine del file `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Questo imposta 2 flag del compilatore:

      * `ARDUCAM_SHIELD_V2` per indicare alla libreria che la fotocamera è su una scheda Arduino, nota come shield.
      * `OV2640_CAM` per indicare alla libreria di includere solo il codice per la fotocamera OV2640.

1. Aggiungi un file di intestazione nella cartella `src` chiamato `camera.h`. Questo conterrà il codice per comunicare con la fotocamera. Aggiungi il seguente codice a questo file:

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

    Questo è codice a basso livello che configura la fotocamera utilizzando le librerie ArduCam e estrae le immagini quando necessario utilizzando il bus SPI. Questo codice è molto specifico per l'ArduCam, quindi non è necessario preoccuparsi di come funziona in questa fase.

1. In `main.cpp`, aggiungi il seguente codice sotto le altre dichiarazioni `include` per includere questo nuovo file e creare un'istanza della classe fotocamera:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Questo crea una `Camera` che salva le immagini come JPEG con una risoluzione di 640x480. Sebbene siano supportate risoluzioni più alte (fino a 3280x2464), il classificatore di immagini funziona su immagini molto più piccole (227x227), quindi non è necessario catturare e inviare immagini più grandi.

1. Aggiungi il seguente codice sotto questo per definire una funzione per configurare la fotocamera:

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

    Questa funzione `setupCamera` inizia configurando il pin di selezione chip SPI (`PIN_SPI_SS`) come alto, rendendo il Wio Terminal il controller SPI. Successivamente avvia i bus I2C e SPI. Infine, inizializza la classe fotocamera che configura le impostazioni del sensore della fotocamera e verifica che tutto sia collegato correttamente.

1. Chiama questa funzione alla fine della funzione `setup`:

    ```cpp
    setupCamera();
    ```

1. Compila e carica questo codice e controlla l'output dal monitor seriale. Se vedi `Error setting up the camera!`, controlla i collegamenti per assicurarti che tutti i cavi colleghino i pin corretti sull'ArduCam ai pin GPIO corretti sul Wio Terminal e che tutti i cavi jumper siano ben inseriti.

## Catturare un'immagine

Ora il Wio Terminal può essere programmato per catturare un'immagine quando viene premuto un pulsante.

### Attività - catturare un'immagine

1. I microcontrollori eseguono il tuo codice continuamente, quindi non è facile attivare qualcosa come scattare una foto senza reagire a un sensore. Il Wio Terminal ha dei pulsanti, quindi la fotocamera può essere configurata per essere attivata da uno di questi pulsanti. Aggiungi il seguente codice alla fine della funzione `setup` per configurare il pulsante C (uno dei tre pulsanti in alto, quello più vicino all'interruttore di accensione).

    ![Il pulsante C in alto vicino all'interruttore di accensione](../../../../../translated_images/wio-terminal-c-button.73df3cb1c1445ea0.it.png)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    La modalità `INPUT_PULLUP` inverte essenzialmente un input. Ad esempio, normalmente un pulsante invierebbe un segnale basso quando non premuto e un segnale alto quando premuto. Quando impostato su `INPUT_PULLUP`, invia un segnale alto quando non premuto e un segnale basso quando premuto.

1. Aggiungi una funzione vuota per rispondere alla pressione del pulsante prima della funzione `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Chiama questa funzione nel metodo `loop` quando il pulsante viene premuto:

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

    Questo codice verifica se il pulsante è premuto. Se lo è, viene chiamata la funzione `buttonPressed` e il ciclo si interrompe per 2 secondi. Questo serve per dare il tempo al pulsante di essere rilasciato in modo che una pressione lunga non venga registrata due volte.

    > 💁 Il pulsante sul Wio Terminal è impostato su `INPUT_PULLUP`, quindi invia un segnale alto quando non premuto e un segnale basso quando premuto.

1. Aggiungi il seguente codice alla funzione `buttonPressed`:

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

    Questo codice avvia la cattura della fotocamera chiamando `startCapture`. L'hardware della fotocamera non funziona restituendo i dati quando li richiedi, ma invii un'istruzione per avviare la cattura e la fotocamera lavorerà in background per catturare l'immagine, convertirla in un JPEG e memorizzarla in un buffer locale sulla fotocamera stessa. La chiamata `captureReady` verifica quindi se la cattura dell'immagine è terminata.

    Una volta terminata la cattura, i dati dell'immagine vengono copiati dal buffer della fotocamera in un buffer locale (array di byte) con la chiamata `readImageToBuffer`. La lunghezza del buffer viene quindi inviata al monitor seriale.

1. Compila e carica questo codice e controlla l'output sul monitor seriale. Ogni volta che premi il pulsante C, verrà catturata un'immagine e vedrai la dimensione dell'immagine inviata al monitor seriale.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Immagini diverse avranno dimensioni diverse. Sono compresse come JPEG e la dimensione di un file JPEG per una data risoluzione dipende da ciò che è presente nell'immagine.

> 💁 Puoi trovare questo codice nella cartella [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Hai catturato con successo immagini con il tuo Wio Terminal.

## Opzionale - verificare le immagini della fotocamera utilizzando una scheda SD

Il modo più semplice per vedere le immagini catturate dalla fotocamera è scriverle su una scheda SD nel Wio Terminal e poi visualizzarle sul tuo computer. Completa questo passaggio se hai una scheda microSD di riserva e un lettore di schede microSD nel tuo computer o un adattatore.

Il Wio Terminal supporta solo schede microSD fino a 16GB di capacità. Se hai una scheda SD più grande, non funzionerà.

### Attività - verificare le immagini della fotocamera utilizzando una scheda SD

1. Formatta una scheda microSD come FAT32 o exFAT utilizzando le applicazioni pertinenti sul tuo computer (Utility Disco su macOS, Esplora File su Windows o strumenti da riga di comando su Linux).

1. Inserisci la scheda microSD nello slot appena sotto l'interruttore di accensione. Assicurati che sia completamente inserita fino a quando non scatta e rimane in posizione; potresti doverla spingere con un'unghia o uno strumento sottile.

1. Aggiungi le seguenti dichiarazioni `include` all'inizio del file `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Aggiungi la seguente funzione prima della funzione `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Questa funzione configura la scheda SD utilizzando il bus SPI.

1. Chiama questa funzione dalla funzione `setup`:

    ```cpp
    setupSDCard();
    ```

1. Aggiungi il seguente codice sopra la funzione `buttonPressed`:

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

    Questo definisce una variabile globale per il conteggio dei file. Questa viene utilizzata per i nomi dei file immagine in modo che più immagini possano essere catturate con nomi di file incrementali - `1.jpg`, `2.jpg` e così via.

    Definisce quindi la funzione `saveToSDCard` che prende un buffer di dati byte e la lunghezza del buffer. Viene creato un nome file utilizzando il conteggio dei file, e il conteggio viene incrementato per il file successivo. I dati binari del buffer vengono quindi scritti nel file.

1. Chiama la funzione `saveToSDCard` dalla funzione `buttonPressed`. La chiamata dovrebbe essere **prima** che il buffer venga eliminato:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Compila e carica questo codice e controlla l'output sul monitor seriale. Ogni volta che premi il pulsante C, verrà catturata un'immagine e salvata sulla scheda SD.

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

1. Spegni il Wio Terminal e rimuovi la scheda microSD spingendola leggermente e rilasciandola, in modo che esca. Potresti dover utilizzare uno strumento sottile per farlo. Inserisci la scheda microSD nel tuo computer per visualizzare le immagini.

    ![Una foto di una banana catturata con l'ArduCam](../../../../../translated_images/banana-arducam.be1b32d4267a8194b0fd042362e56faa431da9cd4af172051b37243ea9be0256.it.jpg)
💁 Potrebbe essere necessario qualche scatto affinché il bilanciamento del bianco della fotocamera si regoli automaticamente. Noterai questo in base al colore delle immagini catturate, le prime potrebbero sembrare con colori alterati. Puoi sempre aggirare questo problema modificando il codice per catturare alcune immagini che vengono ignorate nella funzione `setup`.


**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche possono contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.