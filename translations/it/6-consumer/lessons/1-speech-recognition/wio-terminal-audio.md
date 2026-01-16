<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-25T17:54:33+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "it"
}
-->
# Cattura audio - Wio Terminal

In questa parte della lezione, scriverai del codice per catturare l'audio sul tuo Wio Terminal. La cattura dell'audio sarà controllata da uno dei pulsanti sulla parte superiore del Wio Terminal.

## Programmare il dispositivo per catturare l'audio

Puoi catturare l'audio dal microfono utilizzando codice C++. Il Wio Terminal ha solo 192KB di RAM, non abbastanza per catturare più di qualche secondo di audio. Tuttavia, dispone di 4MB di memoria flash, che può essere utilizzata per salvare l'audio catturato.

Il microfono integrato cattura un segnale analogico, che viene convertito in un segnale digitale utilizzabile dal Wio Terminal. Durante la cattura dell'audio, i dati devono essere acquisiti al momento giusto - ad esempio, per catturare audio a 16KHz, l'audio deve essere acquisito esattamente 16.000 volte al secondo, con intervalli uguali tra ogni campione. Invece di utilizzare il tuo codice per fare ciò, puoi utilizzare il controller di accesso diretto alla memoria (DMAC). Questo è un circuito che può catturare un segnale da una sorgente e scriverlo in memoria, senza interrompere il codice in esecuzione sul processore.

✅ Leggi di più sul DMA nella [pagina di accesso diretto alla memoria su Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![L'audio dal microfono passa a un ADC e poi al DMAC. Questo scrive in un buffer. Quando questo buffer è pieno, viene elaborato e il DMAC scrive in un secondo buffer](../../../../../translated_images/it/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

Il DMAC può catturare audio dall'ADC a intervalli fissi, ad esempio 16.000 volte al secondo per audio a 16KHz. Può scrivere questi dati catturati in un buffer di memoria pre-allocato e, quando questo è pieno, renderlo disponibile al tuo codice per l'elaborazione. L'uso di questa memoria può ritardare la cattura dell'audio, ma puoi configurare più buffer. Il DMAC scrive nel buffer 1, quindi quando è pieno, notifica al tuo codice di elaborare il buffer 1, mentre il DMAC scrive nel buffer 2. Quando il buffer 2 è pieno, notifica al tuo codice e torna a scrivere nel buffer 1. In questo modo, finché elabori ogni buffer in meno tempo di quello necessario per riempirne uno, non perderai alcun dato.

Una volta catturato ogni buffer, può essere scritto nella memoria flash. La memoria flash deve essere scritta utilizzando indirizzi definiti, specificando dove scrivere e quanto grande deve essere la scrittura, in modo simile all'aggiornamento di un array di byte in memoria. La memoria flash ha una granularità, il che significa che le operazioni di cancellazione e scrittura dipendono non solo dalla dimensione fissa, ma anche dall'allineamento a tale dimensione. Ad esempio, se la granularità è di 4096 byte e richiedi una cancellazione all'indirizzo 4200, potrebbe cancellare tutti i dati dall'indirizzo 4096 a 8192. Questo significa che quando scrivi i dati audio nella memoria flash, devono essere in blocchi della dimensione corretta.

### Attività - configurare la memoria flash

1. Crea un nuovo progetto Wio Terminal utilizzando PlatformIO. Chiama questo progetto `smart-timer`. Aggiungi del codice nella funzione `setup` per configurare la porta seriale.

1. Aggiungi le seguenti dipendenze della libreria al file `platformio.ini` per fornire accesso alla memoria flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Apri il file `main.cpp` e aggiungi la seguente direttiva include per la libreria della memoria flash nella parte superiore del file:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD sta per Serial Flash Universal Driver, ed è una libreria progettata per funzionare con tutti i chip di memoria flash.

1. Nella funzione `setup`, aggiungi il seguente codice per configurare la libreria di archiviazione flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Questo ciclo continua fino a quando la libreria SFUD non è inizializzata, quindi attiva le letture rapide. La memoria flash integrata può essere accessibile utilizzando un'interfaccia seriale periferica in coda (QSPI), un tipo di controller SPI che consente un accesso continuo tramite una coda con un utilizzo minimo del processore. Questo rende più veloce leggere e scrivere nella memoria flash.

1. Crea un nuovo file nella cartella `src` chiamato `flash_writer.h`.

1. Aggiungi quanto segue nella parte superiore di questo file:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Questo include alcuni file header necessari, incluso il file header per la libreria SFUD per interagire con la memoria flash.

1. Definisci una classe in questo nuovo file header chiamata `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Nella sezione `private`, aggiungi il seguente codice:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Questo definisce alcuni campi per il buffer da utilizzare per memorizzare i dati prima di scriverli nella memoria flash. C'è un array di byte, `_sfudBuffer`, per scrivere i dati, e quando questo è pieno, i dati vengono scritti nella memoria flash. Il campo `_sfudBufferPos` memorizza la posizione corrente in cui scrivere in questo buffer, e `_sfudBufferWritePos` memorizza la posizione nella memoria flash in cui scrivere. `_flash` è un puntatore alla memoria flash in cui scrivere - alcuni microcontrollori hanno più chip di memoria flash.

1. Aggiungi il seguente metodo alla sezione `public` per inizializzare questa classe:

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

    Questo configura la memoria flash sul Wio Terminal per scrivere, e imposta i buffer in base alla dimensione del blocco della memoria flash. Questo è in un metodo `init`, piuttosto che in un costruttore, poiché deve essere chiamato dopo che la memoria flash è stata configurata nella funzione `setup`.

1. Aggiungi il seguente codice alla sezione `public`:

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

    Questo codice definisce metodi per scrivere byte nel sistema di archiviazione flash. Funziona scrivendo in un buffer in memoria che ha la dimensione corretta per la memoria flash, e quando questo è pieno, viene scritto nella memoria flash, cancellando eventuali dati esistenti in quella posizione. C'è anche un metodo `flushSfudBuffer` per scrivere un buffer incompleto, poiché i dati catturati non saranno multipli esatti della dimensione del blocco, quindi la parte finale dei dati deve essere scritta.

    > 💁 La parte finale dei dati scriverà dati aggiuntivi indesiderati, ma va bene poiché verranno letti solo i dati necessari.

### Attività - configurare la cattura audio

1. Crea un nuovo file nella cartella `src` chiamato `config.h`.

1. Aggiungi quanto segue nella parte superiore di questo file:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Questo codice imposta alcune costanti per la cattura audio.

    | Costante              | Valore  | Descrizione |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | La frequenza di campionamento per l'audio. 16.000 è 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | La durata dell'audio da catturare. Questo è impostato a 4 secondi. Per registrare audio più lungo, aumenta questo valore. |
    | SAMPLES               | 64000  | Il numero totale di campioni audio che verranno catturati. Impostato a frequenza di campionamento * numero di secondi |
    | BUFFER_SIZE           | 128044 | La dimensione del buffer audio da catturare. L'audio verrà catturato come file WAV, che è composto da 44 byte di intestazione, poi 128.000 byte di dati audio (ogni campione è di 2 byte) |
    | ADC_BUF_LEN           | 1600   | La dimensione dei buffer da utilizzare per catturare l'audio dal DMAC |

    > 💁 Se ritieni che 4 secondi siano troppo pochi per richiedere un timer, puoi aumentare il valore di `SAMPLE_LENGTH_SECONDS`, e tutti gli altri valori verranno ricalcolati.

1. Crea un nuovo file nella cartella `src` chiamato `mic.h`.

1. Aggiungi quanto segue nella parte superiore di questo file:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Questo include alcuni file header necessari, inclusi i file header `config.h` e `FlashWriter`.

1. Aggiungi quanto segue per definire una classe `Mic` che può catturare dal microfono:

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

    Questa classe attualmente ha solo un paio di campi per tracciare se la registrazione è iniziata e se una registrazione è pronta per essere utilizzata. Quando il DMAC è configurato, scrive continuamente nei buffer di memoria, quindi il flag `_isRecording` determina se questi devono essere elaborati o ignorati. Il flag `_isRecordingReady` verrà impostato quando i 4 secondi richiesti di audio saranno stati catturati. Il campo `_writer` viene utilizzato per salvare i dati audio nella memoria flash.

    Viene quindi dichiarata una variabile globale per un'istanza della classe `Mic`.

1. Aggiungi il seguente codice alla sezione `private` della classe `Mic`:

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

    Questo codice definisce un metodo `configureDmaAdc` che configura il DMAC, collegandolo all'ADC e impostandolo per popolare due buffer alternati, `_adc_buf_0` e `_adc_buf_1`.

    > 💁 Uno degli svantaggi dello sviluppo per microcontrollori è la complessità del codice necessario per interagire con l'hardware, poiché il tuo codice opera a un livello molto basso interagendo direttamente con l'hardware. Questo codice è più complesso rispetto a quello che scriveresti per un single-board computer o un computer desktop, poiché non c'è un sistema operativo che aiuti. Esistono alcune librerie disponibili che possono semplificare questo processo, ma c'è comunque molta complessità.

1. Sotto questo, aggiungi il seguente codice:

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

    Questo codice definisce l'intestazione WAV come una struttura che occupa 44 byte di memoria. Scrive dettagli sul file audio come frequenza, dimensione e numero di canali. Questa intestazione viene quindi scritta nella memoria flash.

1. Sotto questo codice, aggiungi quanto segue per dichiarare un metodo da chiamare quando i buffer audio sono pronti per essere elaborati:

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

    I buffer audio sono array di interi a 16 bit contenenti l'audio dall'ADC. L'ADC restituisce valori non firmati a 12 bit (0-1023), quindi questi devono essere convertiti in valori firmati a 16 bit, e poi convertiti in 2 byte per essere memorizzati come dati binari grezzi.

    Questi byte vengono scritti nei buffer di memoria flash. La scrittura inizia all'indice 44 - questo è l'offset dai 44 byte scritti come intestazione del file WAV. Una volta che tutti i byte necessari per la lunghezza audio richiesta sono stati catturati, i dati rimanenti vengono scritti nella memoria flash.

1. Nella sezione `public` della classe `Mic`, aggiungi il seguente codice:

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

    Questo codice verrà chiamato dal DMAC per informare il tuo codice che i buffer sono pronti per essere elaborati. Controlla che ci siano dati da elaborare e chiama il metodo `audioCallback` con il buffer rilevante.

1. Al di fuori della classe, dopo la dichiarazione `Mic mic;`, aggiungi il seguente codice:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Il `DMAC_1_Handler` verrà chiamato dal DMAC quando i buffer sono pronti per essere elaborati. Questa funzione viene trovata per nome, quindi deve solo esistere per essere chiamata.

1. Aggiungi i seguenti due metodi alla sezione `public` della classe `Mic`:

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

    Il metodo `init` contiene il codice per inizializzare la classe `Mic`. Questo metodo imposta la tensione corretta per il pin del microfono, configura il writer della memoria flash, scrive l'intestazione del file WAV e configura il DMAC. Il metodo `reset` reimposta la memoria flash e riscrive l'intestazione dopo che l'audio è stato catturato e utilizzato.

### Attività - catturare l'audio

1. Nel file `main.cpp`, aggiungi una direttiva include per il file header `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Nella funzione `setup`, inizializza il pulsante C. La cattura audio inizierà quando questo pulsante viene premuto e continuerà per 4 secondi:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Sotto questo, inizializza il microfono, quindi stampa sulla console che l'audio è pronto per essere catturato:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Sopra la funzione `loop`, definisci una funzione per elaborare l'audio catturato. Per ora non fa nulla, ma più avanti in questa lezione invierà il parlato per essere convertito in testo:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Aggiungi quanto segue alla funzione `loop`:

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

    Questo codice controlla il pulsante C e, se viene premuto e la registrazione non è iniziata, il campo `_isRecording` della classe `Mic` viene impostato su true. Questo farà sì che il metodo `audioCallback` della classe `Mic` memorizzi l'audio fino a quando non saranno stati catturati 4 secondi. Una volta catturati 4 secondi di audio, il campo `_isRecording` viene impostato su false e il campo `_isRecordingReady` viene impostato su true. Questo viene quindi controllato nella funzione `loop` e, quando è true, viene chiamata la funzione `processAudio`, quindi la classe `Mic` viene reimpostata.

1. Compila questo codice, caricalo sul tuo Wio Terminal e testalo tramite il monitor seriale. Premi il pulsante C (quello sul lato sinistro, più vicino all'interruttore di accensione) e parla. Verranno catturati 4 secondi di audio.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Puoi trovare questo codice nella cartella [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Il tuo programma di registrazione audio è stato un successo!

**Disclaimer**:  
Questo documento è stato tradotto utilizzando il servizio di traduzione automatica [Co-op Translator](https://github.com/Azure/co-op-translator). Sebbene ci impegniamo per garantire l'accuratezza, si prega di notare che le traduzioni automatiche potrebbero contenere errori o imprecisioni. Il documento originale nella sua lingua nativa dovrebbe essere considerato la fonte autorevole. Per informazioni critiche, si raccomanda una traduzione professionale effettuata da un traduttore umano. Non siamo responsabili per eventuali incomprensioni o interpretazioni errate derivanti dall'uso di questa traduzione.