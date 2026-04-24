# Audio aufnehmen - Wio Terminal

In diesem Abschnitt der Lektion schreiben Sie Code, um Audio auf Ihrem Wio Terminal aufzunehmen. Die Audioaufnahme wird über eine der Tasten oben auf dem Wio Terminal gesteuert.

## Gerät programmieren, um Audio aufzunehmen

Sie können Audio mit C++-Code über das Mikrofon aufnehmen. Das Wio Terminal verfügt nur über 192 KB RAM, was nicht ausreicht, um mehr als ein paar Sekunden Audio aufzunehmen. Es hat jedoch 4 MB Flash-Speicher, der stattdessen verwendet werden kann, um die aufgenommenen Audiodaten zu speichern.

Das eingebaute Mikrofon erfasst ein analoges Signal, das in ein digitales Signal umgewandelt wird, das das Wio Terminal verwenden kann. Beim Aufnehmen von Audio müssen die Daten im richtigen Zeitintervall erfasst werden – beispielsweise bei einer Aufnahme mit 16 kHz muss das Audio exakt 16.000 Mal pro Sekunde mit gleichen Abständen zwischen den einzelnen Samples erfasst werden. Anstatt dies mit Ihrem Code zu steuern, können Sie den Direct Memory Access Controller (DMAC) verwenden. Dies ist eine Schaltung, die ein Signal erfassen und in den Speicher schreiben kann, ohne den auf dem Prozessor laufenden Code zu unterbrechen.

✅ Lesen Sie mehr über DMA auf der [Wikipedia-Seite zu Direct Memory Access](https://wikipedia.org/wiki/Direct_memory_access).

![Audio vom Mikrofon geht zu einem ADC und dann zum DMAC. Dieser schreibt in einen Puffer. Wenn dieser Puffer voll ist, wird er verarbeitet und der DMAC schreibt in einen zweiten Puffer](../../../../../translated_images/de/dmac-adc-buffers.4509aee49145c90b.webp)

Der DMAC kann Audio vom ADC in festen Intervallen erfassen, beispielsweise 16.000 Mal pro Sekunde für 16-kHz-Audio. Er kann diese erfassten Daten in einen vorab zugewiesenen Speicherpuffer schreiben und, wenn dieser voll ist, Ihrem Code zur Verarbeitung zur Verfügung stellen. Die Verwendung dieses Speichers kann die Audioaufnahme verzögern, aber Sie können mehrere Puffer einrichten. Der DMAC schreibt in Puffer 1, und wenn dieser voll ist, benachrichtigt er Ihren Code, um Puffer 1 zu verarbeiten, während der DMAC in Puffer 2 schreibt. Wenn Puffer 2 voll ist, benachrichtigt er Ihren Code und schreibt wieder in Puffer 1. Solange Sie jeden Puffer in weniger Zeit verarbeiten, als es dauert, einen zu füllen, gehen keine Daten verloren.

Sobald jeder Puffer erfasst wurde, kann er in den Flash-Speicher geschrieben werden. Flash-Speicher muss mit definierten Adressen beschrieben werden, wobei angegeben wird, wo und wie groß geschrieben werden soll, ähnlich wie beim Aktualisieren eines Byte-Arrays im Speicher. Flash-Speicher hat eine Granularität, was bedeutet, dass Lösch- und Schreibvorgänge nicht nur eine feste Größe haben, sondern auch an diese Größe ausgerichtet sein müssen. Wenn die Granularität beispielsweise 4096 Bytes beträgt und Sie ein Löschen bei Adresse 4200 anfordern, könnten alle Daten von Adresse 4096 bis 8192 gelöscht werden. Das bedeutet, dass beim Schreiben der Audiodaten in den Flash-Speicher die Daten in Blöcken der richtigen Größe geschrieben werden müssen.

### Aufgabe - Flash-Speicher konfigurieren

1. Erstellen Sie ein neues Wio Terminal-Projekt mit PlatformIO. Nennen Sie dieses Projekt `smart-timer`. Fügen Sie im `setup`-Funktionsblock Code hinzu, um die serielle Schnittstelle zu konfigurieren.

1. Fügen Sie die folgenden Bibliotheksabhängigkeiten zur Datei `platformio.ini` hinzu, um Zugriff auf den Flash-Speicher zu erhalten:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Öffnen Sie die Datei `main.cpp` und fügen Sie oben die folgende Include-Direktive für die Flash-Speicher-Bibliothek hinzu:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD steht für Serial Flash Universal Driver und ist eine Bibliothek, die mit allen Flash-Speicherchips funktioniert.

1. Fügen Sie in der `setup`-Funktion den folgenden Code hinzu, um die Flash-Speicher-Bibliothek einzurichten:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Diese Schleife läuft, bis die SFUD-Bibliothek initialisiert ist, und aktiviert dann schnelles Lesen. Der eingebaute Flash-Speicher kann über eine Queued Serial Peripheral Interface (QSPI) angesprochen werden, eine Art SPI-Controller, der kontinuierlichen Zugriff über eine Warteschlange mit minimaler Prozessorbelastung ermöglicht. Dadurch wird das Lesen und Schreiben im Flash-Speicher beschleunigt.

1. Erstellen Sie eine neue Datei im Ordner `src` mit dem Namen `flash_writer.h`.

1. Fügen Sie oben in dieser Datei Folgendes hinzu:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Dies schließt einige benötigte Header-Dateien ein, einschließlich der Header-Datei für die SFUD-Bibliothek, um mit dem Flash-Speicher zu interagieren.

1. Definieren Sie in dieser neuen Header-Datei eine Klasse namens `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Fügen Sie im Abschnitt `private` den folgenden Code hinzu:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Dies definiert einige Felder für den Puffer, der verwendet wird, um Daten vor dem Schreiben in den Flash-Speicher zu speichern. Es gibt ein Byte-Array `_sfudBuffer`, in das Daten geschrieben werden, und wenn dieses voll ist, werden die Daten in den Flash-Speicher geschrieben. Das Feld `_sfudBufferPos` speichert die aktuelle Position zum Schreiben in diesen Puffer, und `_sfudBufferWritePos` speichert die Position im Flash-Speicher, in die geschrieben werden soll. `_flash` ist ein Zeiger auf den Flash-Speicher, in den geschrieben werden soll – einige Mikrocontroller haben mehrere Flash-Speicherchips.

1. Fügen Sie der `public`-Sektion die folgende Methode hinzu, um diese Klasse zu initialisieren:

    ```cpp
    void init()
    {
        _flash = sfud_get_device_table() + 0;
        _sfudBufferSize = _flash->chip.erase_gran;
        _sfudBuffer = new byte[_sfudBufferSize];
        _sfudBufferPos = 0;
        _sfudBufferWritePos = 0;
    }
    ```

    Diese Methode konfiguriert den Flash-Speicher des Wio Terminals für Schreibvorgänge und richtet die Puffer basierend auf der Granularität des Flash-Speichers ein. Dies geschieht in einer `init`-Methode und nicht im Konstruktor, da diese Methode nach der Einrichtung des Flash-Speichers in der `setup`-Funktion aufgerufen werden muss.

1. Fügen Sie der `public`-Sektion den folgenden Code hinzu:

    ```cpp
    void writeSfudBuffer(byte b)
    {
        _sfudBuffer[_sfudBufferPos++] = b;
        if (_sfudBufferPos == _sfudBufferSize)
        {
            sfud_erase_write(_flash, _sfudBufferWritePos, _sfudBufferSize, _sfudBuffer);
            _sfudBufferWritePos += _sfudBufferSize;
            _sfudBufferPos = 0;
        }
    }

    void writeSfudBuffer(byte *b, size_t len)
    {
        for (size_t i = 0; i < len; ++i)
        {
            writeSfudBuffer(b[i]);
        }
    }

    void flushSfudBuffer()
    {
        if (_sfudBufferPos > 0)
        {
            sfud_erase_write(_flash, _sfudBufferWritePos, _sfudBufferSize, _sfudBuffer);
            _sfudBufferWritePos += _sfudBufferSize;
            _sfudBufferPos = 0;
        }
    }
    ```

    Dieser Code definiert Methoden, um Bytes in das Flash-Speichersystem zu schreiben. Es funktioniert, indem in einen Speicherpuffer geschrieben wird, der die richtige Größe für den Flash-Speicher hat, und wenn dieser voll ist, wird er in den Flash-Speicher geschrieben, wobei vorhandene Daten an dieser Stelle gelöscht werden. Es gibt auch eine Methode `flushSfudBuffer`, um einen unvollständigen Puffer zu schreiben, da die erfassten Daten keine exakten Vielfachen der Granularität sind, sodass der letzte Teil der Daten geschrieben werden muss.

    > 💁 Der letzte Teil der Daten wird zusätzliche unerwünschte Daten schreiben, aber das ist in Ordnung, da nur die benötigten Daten gelesen werden.

### Aufgabe - Audioaufnahme einrichten

1. Erstellen Sie eine neue Datei im Ordner `src` mit dem Namen `config.h`.

1. Fügen Sie oben in dieser Datei Folgendes hinzu:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Dieser Code legt einige Konstanten für die Audioaufnahme fest.

    | Konstante             | Wert   | Beschreibung |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Die Abtastrate für das Audio. 16.000 entspricht 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Die Länge der aufzunehmenden Audiodaten. Diese ist auf 4 Sekunden eingestellt. Um längere Audiodaten aufzunehmen, erhöhen Sie diesen Wert. |
    | SAMPLES               | 64000  | Die Gesamtanzahl der aufzunehmenden Audiodaten. Eingestellt auf die Abtastrate * die Anzahl der Sekunden |
    | BUFFER_SIZE           | 128044 | Die Größe des Audiopuffers für die Aufnahme. Audio wird als WAV-Datei aufgenommen, die 44 Bytes Header und 128.000 Bytes Audiodaten enthält (jedes Sample ist 2 Bytes groß) |
    | ADC_BUF_LEN           | 1600   | Die Größe der Puffer, die für die Audioaufnahme vom DMAC verwendet werden |

    > 💁 Wenn Sie feststellen, dass 4 Sekunden zu kurz sind, um einen Timer anzufordern, können Sie den Wert `SAMPLE_LENGTH_SECONDS` erhöhen, und alle anderen Werte werden neu berechnet.

1. Erstellen Sie eine neue Datei im Ordner `src` mit dem Namen `mic.h`.

1. Fügen Sie oben in dieser Datei Folgendes hinzu:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Dies schließt einige benötigte Header-Dateien ein, einschließlich der Header-Dateien `config.h` und `FlashWriter`.

1. Fügen Sie Folgendes hinzu, um eine `Mic`-Klasse zu definieren, die vom Mikrofon aufnehmen kann:

    ```cpp
    class Mic
    {
    public:
        Mic()
        {
            _isRecording = false;
            _isRecordingReady = false;
        }
    
        void startRecording()
        {
            _isRecording = true;
            _isRecordingReady = false;
        }
    
        bool isRecording()
        {
            return _isRecording;
        }
    
        bool isRecordingReady()
        {
            return _isRecordingReady;
        }
    
    private:
        volatile bool _isRecording;
        volatile bool _isRecordingReady;
        FlashWriter _writer;
    };
    
    Mic mic;
    ```

    Diese Klasse enthält derzeit nur ein paar Felder, um zu verfolgen, ob die Aufnahme gestartet wurde und ob eine Aufnahme zur Verfügung steht. Wenn der DMAC eingerichtet ist, schreibt er kontinuierlich in Speicherpuffer, sodass das Flag `_isRecording` bestimmt, ob diese verarbeitet oder ignoriert werden sollen. Das Flag `_isRecordingReady` wird gesetzt, wenn die erforderlichen 4 Sekunden Audio aufgenommen wurden. Das Feld `_writer` wird verwendet, um die Audiodaten im Flash-Speicher zu speichern.

    Eine globale Variable wird dann für eine Instanz der `Mic`-Klasse deklariert.

1. Fügen Sie im Abschnitt `private` der `Mic`-Klasse den folgenden Code hinzu:

    ```cpp
    typedef struct
    {
        uint16_t btctrl;
        uint16_t btcnt;
        uint32_t srcaddr;
        uint32_t dstaddr;
        uint32_t descaddr;
    } dmacdescriptor;

    // Globals - DMA and ADC
    volatile dmacdescriptor _wrb[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor_section[DMAC_CH_NUM] __attribute__((aligned(16)));
    dmacdescriptor _descriptor __attribute__((aligned(16)));

    void configureDmaAdc()
    {
        // Configure DMA to sample from ADC at a regular interval (triggered by timer/counter)
        DMAC->BASEADDR.reg = (uint32_t)_descriptor_section;                    // Specify the location of the descriptors
        DMAC->WRBADDR.reg = (uint32_t)_wrb;                                    // Specify the location of the write back descriptors
        DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);           // Enable the DMAC peripheral
        DMAC->Channel[1].CHCTRLA.reg = DMAC_CHCTRLA_TRIGSRC(TC5_DMAC_ID_OVF) | // Set DMAC to trigger on TC5 timer overflow
                                        DMAC_CHCTRLA_TRIGACT_BURST;             // DMAC burst transfer

        _descriptor.descaddr = (uint32_t)&_descriptor_section[1];                    // Set up a circular descriptor
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // Take the result from the ADC0 RESULT register
        _descriptor.dstaddr = (uint32_t)_adc_buf_0 + sizeof(uint16_t) * ADC_BUF_LEN; // Place it in the adc_buf_0 array
        _descriptor.btcnt = ADC_BUF_LEN;                                             // Beat count
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // Beat size is HWORD (16-bits)
                                DMAC_BTCTRL_DSTINC |                                    // Increment the destination address
                                DMAC_BTCTRL_VALID |                                     // Descriptor is valid
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // Suspend DMAC channel 0 after block transfer
        memcpy(&_descriptor_section[0], &_descriptor, sizeof(_descriptor));          // Copy the descriptor to the descriptor section

        _descriptor.descaddr = (uint32_t)&_descriptor_section[0];                    // Set up a circular descriptor
        _descriptor.srcaddr = (uint32_t)&ADC1->RESULT.reg;                           // Take the result from the ADC0 RESULT register
        _descriptor.dstaddr = (uint32_t)_adc_buf_1 + sizeof(uint16_t) * ADC_BUF_LEN; // Place it in the adc_buf_1 array
        _descriptor.btcnt = ADC_BUF_LEN;                                             // Beat count
        _descriptor.btctrl = DMAC_BTCTRL_BEATSIZE_HWORD |                            // Beat size is HWORD (16-bits)
                                DMAC_BTCTRL_DSTINC |                                    // Increment the destination address
                                DMAC_BTCTRL_VALID |                                     // Descriptor is valid
                                DMAC_BTCTRL_BLOCKACT_SUSPEND;                           // Suspend DMAC channel 0 after block transfer
        memcpy(&_descriptor_section[1], &_descriptor, sizeof(_descriptor));          // Copy the descriptor to the descriptor section

        // Configure NVIC
        NVIC_SetPriority(DMAC_1_IRQn, 0); // Set the Nested Vector Interrupt Controller (NVIC) priority for DMAC1 to 0 (highest)
        NVIC_EnableIRQ(DMAC_1_IRQn);      // Connect DMAC1 to Nested Vector Interrupt Controller (NVIC)

        // Activate the suspend (SUSP) interrupt on DMAC channel 1
        DMAC->Channel[1].CHINTENSET.reg = DMAC_CHINTENSET_SUSP;

        // Configure ADC
        ADC1->INPUTCTRL.bit.MUXPOS = ADC_INPUTCTRL_MUXPOS_AIN12_Val; // Set the analog input to ADC0/AIN2 (PB08 - A4 on Metro M4)
        while (ADC1->SYNCBUSY.bit.INPUTCTRL)
            ;                              // Wait for synchronization
        ADC1->SAMPCTRL.bit.SAMPLEN = 0x00; // Set max Sampling Time Length to half divided ADC clock pulse (2.66us)
        while (ADC1->SYNCBUSY.bit.SAMPCTRL)
            ;                                         // Wait for synchronization
        ADC1->CTRLA.reg = ADC_CTRLA_PRESCALER_DIV128; // Divide Clock ADC GCLK by 128 (48MHz/128 = 375kHz)
        ADC1->CTRLB.reg = ADC_CTRLB_RESSEL_12BIT |    // Set ADC resolution to 12 bits
                            ADC_CTRLB_FREERUN;          // Set ADC to free run mode
        while (ADC1->SYNCBUSY.bit.CTRLB)
            ;                       // Wait for synchronization
        ADC1->CTRLA.bit.ENABLE = 1; // Enable the ADC
        while (ADC1->SYNCBUSY.bit.ENABLE)
            ;                       // Wait for synchronization
        ADC1->SWTRIG.bit.START = 1; // Initiate a software trigger to start an ADC conversion
        while (ADC1->SYNCBUSY.bit.SWTRIG)
            ; // Wait for synchronization

        // Enable DMA channel 1
        DMAC->Channel[1].CHCTRLA.bit.ENABLE = 1;

        // Configure Timer/Counter 5
        GCLK->PCHCTRL[TC5_GCLK_ID].reg = GCLK_PCHCTRL_CHEN |     // Enable peripheral channel for TC5
                                            GCLK_PCHCTRL_GEN_GCLK1; // Connect generic clock 0 at 48MHz

        TC5->COUNT16.WAVE.reg = TC_WAVE_WAVEGEN_MFRQ; // Set TC5 to Match Frequency (MFRQ) mode
        TC5->COUNT16.CC[0].reg = 3000 - 1;            // Set the trigger to 16 kHz: (4Mhz / 16000) - 1
        while (TC5->COUNT16.SYNCBUSY.bit.CC0)
            ; // Wait for synchronization

        // Start Timer/Counter 5
        TC5->COUNT16.CTRLA.bit.ENABLE = 1; // Enable the TC5 timer
        while (TC5->COUNT16.SYNCBUSY.bit.ENABLE)
            ; // Wait for synchronization
    }

    uint16_t _adc_buf_0[ADC_BUF_LEN];
    uint16_t _adc_buf_1[ADC_BUF_LEN];
    ```

    Dieser Code definiert eine Methode `configureDmaAdc`, die den DMAC konfiguriert, ihn mit dem ADC verbindet und ihn so einrichtet, dass er zwei verschiedene, abwechselnde Puffer füllt: `_adc_buf_0` und `_adc_buf_1`.

    > 💁 Einer der Nachteile der Mikrocontroller-Entwicklung ist die Komplexität des Codes, der benötigt wird, um mit der Hardware zu interagieren, da Ihr Code auf einer sehr niedrigen Ebene direkt mit der Hardware arbeitet. Dieser Code ist komplexer als das, was Sie für einen Einplatinencomputer oder Desktop-Computer schreiben würden, da es kein Betriebssystem gibt, das hilft. Es gibt einige Bibliotheken, die dies vereinfachen können, aber es bleibt dennoch komplex.

1. Fügen Sie darunter den folgenden Code hinzu:

    ```cpp
    // WAV files have a header. This struct defines that header
    struct wavFileHeader
    {
        char riff[4];         /* "RIFF"                                  */
        long flength;         /* file length in bytes                    */
        char wave[4];         /* "WAVE"                                  */
        char fmt[4];          /* "fmt "                                  */
        long chunk_size;      /* size of FMT chunk in bytes (usually 16) */
        short format_tag;     /* 1=PCM, 257=Mu-Law, 258=A-Law, 259=ADPCM */
        short num_chans;      /* 1=mono, 2=stereo                        */
        long srate;           /* Sampling rate in samples per second     */
        long bytes_per_sec;   /* bytes per second = srate*bytes_per_samp */
        short bytes_per_samp; /* 2=16-bit mono, 4=16-bit stereo          */
        short bits_per_samp;  /* Number of bits per sample               */
        char data[4];         /* "data"                                  */
        long dlength;         /* data length in bytes (filelength - 44)  */
    };

    void initBufferHeader()
    {
        wavFileHeader wavh;

        strncpy(wavh.riff, "RIFF", 4);
        strncpy(wavh.wave, "WAVE", 4);
        strncpy(wavh.fmt, "fmt ", 4);
        strncpy(wavh.data, "data", 4);

        wavh.chunk_size = 16;
        wavh.format_tag = 1; // PCM
        wavh.num_chans = 1;  // mono
        wavh.srate = RATE;
        wavh.bytes_per_sec = (RATE * 1 * 16 * 1) / 8;
        wavh.bytes_per_samp = 2;
        wavh.bits_per_samp = 16;
        wavh.dlength = RATE * 2 * 1 * 16 / 2;
        wavh.flength = wavh.dlength + 44;

        _writer.writeSfudBuffer((byte *)&wavh, 44);
    }
    ```

    Dieser Code definiert den WAV-Header als eine Struktur, die 44 Bytes Speicher belegt. Es schreibt Details zur Abtastrate, Größe und Anzahl der Kanäle der Audiodatei. Dieser Header wird dann in den Flash-Speicher geschrieben.

1. Fügen Sie unter diesem Code Folgendes hinzu, um eine Methode zu deklarieren, die aufgerufen wird, wenn die Audiopuffer zur Verarbeitung bereit sind:

    ```cpp
    void audioCallback(uint16_t *buf, uint32_t buf_len)
    {
        static uint32_t idx = 44;

        if (_isRecording)
        {
            for (uint32_t i = 0; i < buf_len; i++)
            {
                int16_t audio_value = ((int16_t)buf[i] - 2048) * 16;

                _writer.writeSfudBuffer(audio_value & 0xFF);
                _writer.writeSfudBuffer((audio_value >> 8) & 0xFF);
            }

            idx += buf_len;
                
            if (idx >= BUFFER_SIZE)
            {
                _writer.flushSfudBuffer();
                idx = 44;
                _isRecording = false;
                _isRecordingReady = true;
            }
        }
    }
    ```

    Die Audiopuffer sind Arrays von 16-Bit-Ganzzahlen, die das Audio vom ADC enthalten. Der ADC gibt 12-Bit-unsigned-Werte (0-1023) zurück, daher müssen diese in 16-Bit-signed-Werte umgewandelt und dann in 2 Bytes konvertiert werden, um als rohe Binärdaten gespeichert zu werden.

    Diese Bytes werden in die Flash-Speicherpuffer geschrieben. Der Schreibvorgang beginnt bei Index 44 – dies ist der Offset von den 44 Bytes, die als WAV-Datei-Header geschrieben wurden. Sobald alle benötigten Bytes für die erforderliche Audiolänge erfasst wurden, werden die verbleibenden Daten in den Flash-Speicher geschrieben.

1. Fügen Sie der `public`-Sektion der `Mic`-Klasse den folgenden Code hinzu:

    ```cpp
    void dmaHandler()
    {
        static uint8_t count = 0;

        if (DMAC->Channel[1].CHINTFLAG.bit.SUSP)
        {
            DMAC->Channel[1].CHCTRLB.reg = DMAC_CHCTRLB_CMD_RESUME;
            DMAC->Channel[1].CHINTFLAG.bit.SUSP = 1;

            if (count)
            {
                audioCallback(_adc_buf_0, ADC_BUF_LEN);
            }
            else
            {
                audioCallback(_adc_buf_1, ADC_BUF_LEN);
            }

            count = (count + 1) % 2;
        }
    }
    ```

    Dieser Code wird vom DMAC aufgerufen, um Ihrem Code mitzuteilen, dass die Puffer zur Verarbeitung bereit sind. Es wird überprüft, ob Daten zur Verarbeitung vorliegen, und die Methode `audioCallback` wird mit dem entsprechenden Puffer aufgerufen.

1. Fügen Sie außerhalb der Klasse, nach der Deklaration `Mic mic;`, den folgenden Code hinzu:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Der `DMAC_1_Handler` wird vom DMAC aufgerufen, wenn die Puffer zur Verarbeitung bereit sind. Diese Funktion wird anhand ihres Namens gefunden und muss daher nur existieren, um aufgerufen zu werden.

1. Fügen Sie der `public`-Sektion der `Mic`-Klasse die folgenden zwei Methoden hinzu:

    ```cpp
    void init()
    {
        analogReference(AR_INTERNAL2V23);

        _writer.init();

        initBufferHeader();
        configureDmaAdc();
    }

    void reset()
    {
        _isRecordingReady = false;
        _isRecording = false;

        _writer.reset();

        initBufferHeader();
    }
    ```

    Die Methode `init` enthält Code, um die `Mic`-Klasse zu initialisieren. Diese Methode setzt die richtige Spannung für den Mic-Pin, richtet den Flash-Speicher-Writer ein, schreibt den WAV-Datei-Header und konfiguriert den DMAC. Die Methode `reset` setzt den Flash-Speicher zurück und schreibt den Header erneut, nachdem das Audio aufgenommen und verwendet wurde.

### Aufgabe - Audio aufnehmen

1. Fügen Sie in der Datei `main.cpp` eine Include-Direktive für die Header-Datei `mic.h` hinzu:

    ```cpp
    #include "mic.h"
    ```

1. Initialisieren Sie in der `setup`-Funktion die C-Taste. Die Audioaufnahme beginnt, wenn diese Taste gedrückt wird, und dauert 4 Sekunden:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Initialisieren Sie darunter das Mikrofon und geben Sie dann in der Konsole aus, dass Audio zur Aufnahme bereit ist:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Definieren Sie oberhalb der `loop`-Funktion eine Funktion, um das aufgenommene Audio zu verarbeiten. Diese Funktion tut vorerst nichts, wird aber später in dieser Lektion verwendet, um die Sprache in Text umzuwandeln:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Fügen Sie der `loop`-Funktion Folgendes hinzu:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW && !mic.isRecording())
        {
            Serial.println("Starting recording...");
            mic.startRecording();
        }
    
        if (!mic.isRecording() && mic.isRecordingReady())
        {
            Serial.println("Finished recording");
    
            processAudio();
    
            mic.reset();
        }
    }
    ```

    Dieser Code überprüft die C-Taste, und wenn diese gedrückt wird und die Aufnahme noch nicht gestartet wurde, wird das Feld `_isRecording` der `Mic`-Klasse auf `true` gesetzt. Dadurch speichert die Methode `audioCallback` der `Mic`-Klasse Audio, bis 4 Sekunden aufgenommen wurden. Sobald 4 Sekunden Audio aufgenommen wurden, wird das Feld `_isRecording` auf `false` gesetzt und das Feld `_isRecordingReady` auf `true`. Dies wird dann in der `loop`-Funktion überprüft, und wenn es wahr ist, wird die Funktion `processAudio` aufgerufen und die `Mic`-Klasse zurückgesetzt.

1. Bauen Sie diesen Code, laden Sie ihn auf Ihr Wio Terminal hoch und testen Sie ihn über den seriellen Monitor. Drücken Sie die C-Taste (die auf der linken Seite, am nächsten zum Netzschalter), und sprechen Sie. Es werden 4 Sekunden Audio aufgenommen.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Du findest diesen Code im Ordner [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Ihr Audioaufnahmeprogramm war ein Erfolg!

**Haftungsausschluss**:  
Dieses Dokument wurde mit dem KI-Übersetzungsdienst [Co-op Translator](https://github.com/Azure/co-op-translator) übersetzt. Obwohl wir uns um Genauigkeit bemühen, beachten Sie bitte, dass automatisierte Übersetzungen Fehler oder Ungenauigkeiten enthalten können. Das Originaldokument in seiner ursprünglichen Sprache sollte als maßgebliche Quelle betrachtet werden. Für kritische Informationen wird eine professionelle menschliche Übersetzung empfohlen. Wir übernehmen keine Haftung für Missverständnisse oder Fehlinterpretationen, die sich aus der Nutzung dieser Übersetzung ergeben.