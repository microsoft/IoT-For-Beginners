# Fånga ljud - Wio Terminal

I den här delen av lektionen kommer du att skriva kod för att fånga ljud på din Wio Terminal. Ljudinspelningen kommer att styras av en av knapparna på ovansidan av Wio Terminal.

## Programmera enheten för att fånga ljud

Du kan fånga ljud från mikrofonen med hjälp av C++-kod. Wio Terminal har endast 192KB RAM, vilket inte räcker för att fånga mer än ett par sekunder av ljud. Den har dock 4MB flashminne, vilket kan användas istället för att spara inspelat ljud.

Den inbyggda mikrofonen fångar en analog signal som omvandlas till en digital signal som Wio Terminal kan använda. När ljud fångas måste datan samlas in vid rätt tidpunkt – till exempel, för att fånga ljud vid 16KHz måste ljudet samplas exakt 16 000 gånger per sekund, med lika stora intervall mellan varje prov. Istället för att använda din kod för detta kan du använda Direct Memory Access Controller (DMAC). Detta är en krets som kan fånga en signal från en källa och skriva till minnet utan att avbryta koden som körs på processorn.

✅ Läs mer om DMA på [Wikipedia-sidan om direktminnesåtkomst](https://wikipedia.org/wiki/Direct_memory_access).

![Ljud från mikrofonen går till en ADC och sedan till DMAC. Detta skriver till en buffert. När denna buffert är full bearbetas den och DMAC skriver till en andra buffert](../../../../../translated_images/sv/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC kan fånga ljud från ADC vid fasta intervall, till exempel 16 000 gånger per sekund för 16KHz-ljud. Den kan skriva denna inspelade data till en förallokerad minnesbuffert, och när denna är full görs den tillgänglig för din kod att bearbeta. Användning av detta minne kan fördröja ljudinspelningen, men du kan ställa in flera buffertar. DMAC skriver till buffert 1, och när den är full meddelar den din kod att bearbeta buffert 1, medan DMAC skriver till buffert 2. När buffert 2 är full meddelar den din kod och går tillbaka till att skriva till buffert 1. På så sätt, så länge du bearbetar varje buffert snabbare än det tar att fylla en, kommer du inte att förlora någon data.

När varje buffert har fångats kan den skrivas till flashminnet. Flashminne måste skrivas till med definierade adresser, där du specificerar var och hur mycket som ska skrivas, liknande att uppdatera en array av bytes i minnet. Flashminne har granularitet, vilket innebär att raderings- och skrivoperationer inte bara måste vara av en fast storlek utan också anpassas till den storleken. Till exempel, om granulariteten är 4096 bytes och du begär en radering vid adress 4200, kan det radera all data från adress 4096 till 8192. Detta innebär att när du skriver ljuddata till flashminnet måste det ske i rätt storleksblock.

### Uppgift - konfigurera flashminne

1. Skapa ett helt nytt Wio Terminal-projekt med PlatformIO. Kalla detta projekt `smart-timer`. Lägg till kod i `setup`-funktionen för att konfigurera seriell port.

1. Lägg till följande biblioteksberoenden i `platformio.ini`-filen för att få åtkomst till flashminnet:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Öppna filen `main.cpp` och lägg till följande inkluderingsdirektiv för flashminnesbiblioteket högst upp i filen:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD står för Serial Flash Universal Driver och är ett bibliotek designat för att fungera med alla flashminneskretsar.

1. I `setup`-funktionen, lägg till följande kod för att konfigurera flashlagringsbiblioteket:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Detta loopar tills SFUD-biblioteket är initierat och aktiverar sedan snabba läsningar. Det inbyggda flashminnet kan nås med hjälp av ett Queued Serial Peripheral Interface (QSPI), en typ av SPI-kontroller som möjliggör kontinuerlig åtkomst via en kö med minimal processoranvändning. Detta gör det snabbare att läsa och skriva till flashminnet.

1. Skapa en ny fil i mappen `src` som heter `flash_writer.h`.

1. Lägg till följande högst upp i denna fil:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Detta inkluderar några nödvändiga headerfiler, inklusive headerfilen för SFUD-biblioteket för att interagera med flashminnet.

1. Definiera en klass i denna nya headerfil som heter `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. I den privata sektionen, lägg till följande kod:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Detta definierar några fält för bufferten som används för att lagra data innan den skrivs till flashminnet. Det finns en byte-array, `_sfudBuffer`, för att skriva data till, och när denna är full skrivs datan till flashminnet. Fältet `_sfudBufferPos` lagrar den aktuella positionen att skriva till i denna buffert, och `_sfudBufferWritePos` lagrar positionen i flashminnet att skriva till. `_flash` är en pekare till flashminnet att skriva till – vissa mikrokontroller har flera flashminneskretsar.

1. Lägg till följande metod i den publika sektionen för att initiera denna klass:

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

    Detta konfigurerar flashminnet på Wio Terminal för att skriva till och ställer in buffertarna baserat på flashminnets granularitet. Detta är i en `init`-metod istället för en konstruktor eftersom detta måste anropas efter att flashminnet har konfigurerats i `setup`-funktionen.

1. Lägg till följande kod i den publika sektionen:

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

    Denna kod definierar metoder för att skriva bytes till flashlagringssystemet. Det fungerar genom att skriva till en minnesbuffert som har rätt storlek för flashminnet, och när denna är full skrivs den till flashminnet, vilket raderar eventuell befintlig data på den platsen. Det finns också en `flushSfudBuffer` för att skriva en ofullständig buffert, eftersom den data som fångas inte kommer att vara exakta multiplar av granulariteten, så den sista delen av datan måste skrivas.

    > 💁 Den sista delen av datan kommer att skriva ytterligare oönskad data, men detta är okej eftersom endast den data som behövs kommer att läsas.

### Uppgift - konfigurera ljudinspelning

1. Skapa en ny fil i mappen `src` som heter `config.h`.

1. Lägg till följande högst upp i denna fil:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Denna kod ställer in några konstanter för ljudinspelningen.

    | Konstant              | Värde  | Beskrivning |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Samplingsfrekvensen för ljudet. 16 000 är 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Längden på ljudet som ska spelas in. Detta är inställt på 4 sekunder. För att spela in längre ljud, öka detta. |
    | SAMPLES               | 64000  | Det totala antalet ljudprover som kommer att spelas in. Inställt på samplingsfrekvensen * antalet sekunder |
    | BUFFER_SIZE           | 128044 | Storleken på ljudbufferten som ska fångas. Ljudet kommer att spelas in som en WAV-fil, som är 44 bytes header och sedan 128 000 bytes ljuddata (varje prov är 2 bytes) |
    | ADC_BUF_LEN           | 1600   | Storleken på buffertarna som används för att fånga ljud från DMAC |

    > 💁 Om du tycker att 4 sekunder är för kort för att begära en timer kan du öka värdet på `SAMPLE_LENGTH_SECONDS`, och alla andra värden kommer att räknas om.

1. Skapa en ny fil i mappen `src` som heter `mic.h`.

1. Lägg till följande högst upp i denna fil:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Detta inkluderar några nödvändiga headerfiler, inklusive `config.h` och `FlashWriter`-headerfilerna.

1. Lägg till följande för att definiera en `Mic`-klass som kan fånga från mikrofonen:

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

    Denna klass har för närvarande endast ett par fält för att spåra om inspelningen har startat och om en inspelning är redo att användas. När DMAC är konfigurerad skriver den kontinuerligt till minnesbuffertar, så flaggan `_isRecording` avgör om dessa ska bearbetas eller ignoreras. Flaggan `_isRecordingReady` kommer att sättas när de nödvändiga 4 sekunderna av ljud har spelats in. Fältet `_writer` används för att spara ljuddata till flashminnet.

    En global variabel deklareras sedan för en instans av `Mic`-klassen.

1. Lägg till följande kod i den privata sektionen av `Mic`-klassen:

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

    Denna kod definierar en `configureDmaAdc`-metod som konfigurerar DMAC, kopplar den till ADC och ställer in den för att fylla två olika alternerande buffertar, `_adc_buf_0` och `_adc_buf_1`.

    > 💁 En av nackdelarna med mikrokontrollerutveckling är komplexiteten i koden som behövs för att interagera med hårdvaran, eftersom din kod körs på en mycket låg nivå och interagerar direkt med hårdvaran. Denna kod är mer komplex än vad du skulle skriva för en enkortsdator eller stationär dator eftersom det inte finns något operativsystem som hjälper till. Det finns vissa bibliotek som kan förenkla detta, men det finns fortfarande mycket komplexitet.

1. Nedanför detta, lägg till följande kod:

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

    Denna kod definierar WAV-headern som en struktur som tar upp 44 bytes minne. Den skriver detaljer till den om ljudfilens frekvens, storlek och antal kanaler. Denna header skrivs sedan till flashminnet.

1. Nedanför denna kod, lägg till följande för att deklarera en metod som ska anropas när ljudbuffertarna är redo att bearbetas:

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

    Ljudbuffertarna är arrayer av 16-bitars heltal som innehåller ljudet från ADC. ADC returnerar 12-bitars osignerade värden (0-1023), så dessa måste konverteras till 16-bitars signerade värden och sedan konverteras till 2 bytes för att lagras som rå binär data.

    Dessa bytes skrivs till flashminnesbuffertarna. Skrivningen börjar vid index 44 – detta är offseten från de 44 bytes som skrivits som WAV-filens header. När alla bytes som behövs för den önskade ljudlängden har fångats skrivs den återstående datan till flashminnet.

1. I den publika sektionen av `Mic`-klassen, lägg till följande kod:

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

    Denna kod kommer att anropas av DMAC för att meddela din kod att bearbeta buffertarna. Den kontrollerar att det finns data att bearbeta och anropar metoden `audioCallback` med relevant buffert.

1. Utanför klassen, efter deklarationen `Mic mic;`, lägg till följande kod:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` kommer att anropas av DMAC när buffertarna är redo att bearbetas. Denna funktion hittas via namn, så den behöver bara existera för att anropas.

1. Lägg till följande två metoder i den publika sektionen av `Mic`-klassen:

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

    `init`-metoden innehåller kod för att initiera `Mic`-klassen. Denna metod ställer in rätt spänning för Mic-pinnen, konfigurerar flashminnesskrivaren, skriver WAV-filens header och konfigurerar DMAC. `reset`-metoden återställer flashminnet och skriver om headern efter att ljudet har fångats och använts.

### Uppgift - fånga ljud

1. I filen `main.cpp`, lägg till ett inkluderingsdirektiv för headerfilen `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. I `setup`-funktionen, initiera C-knappen. Ljudinspelningen startar när denna knapp trycks in och fortsätter i 4 sekunder:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Nedanför detta, initiera mikrofonen och skriv sedan till konsolen att ljud är redo att fångas:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Ovanför `loop`-funktionen, definiera en funktion för att bearbeta det inspelade ljudet. För tillfället gör denna funktion ingenting, men senare i lektionen kommer den att skicka talet för att omvandlas till text:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Lägg till följande i `loop`-funktionen:

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

    Denna kod kontrollerar C-knappen, och om denna trycks in och inspelningen inte har startat, sätts fältet `_isRecording` i `Mic`-klassen till true. Detta kommer att göra att metoden `audioCallback` i `Mic`-klassen lagrar ljud tills 4 sekunder har spelats in. När 4 sekunder av ljud har spelats in sätts fältet `_isRecording` till false och fältet `_isRecordingReady` till true. Detta kontrolleras sedan i `loop`-funktionen, och när det är sant anropas funktionen `processAudio`, och sedan återställs `Mic`-klassen.

1. Bygg denna kod, ladda upp den till din Wio Terminal och testa den via seriell monitor. Tryck på C-knappen (den till vänster, närmast strömbrytaren) och prata. 4 sekunder av ljud kommer att spelas in.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 Du kan hitta denna kod i mappen [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Ditt ljudinspelningsprogram blev en framgång!

---

**Ansvarsfriskrivning**:  
Detta dokument har översatts med hjälp av AI-översättningstjänsten [Co-op Translator](https://github.com/Azure/co-op-translator). Även om vi strävar efter noggrannhet, bör det noteras att automatiska översättningar kan innehålla fel eller inexaktheter. Det ursprungliga dokumentet på dess originalspråk bör betraktas som den auktoritativa källan. För kritisk information rekommenderas professionell mänsklig översättning. Vi ansvarar inte för eventuella missförstånd eller feltolkningar som uppstår vid användning av denna översättning.