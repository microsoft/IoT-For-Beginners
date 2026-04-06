# Optag lyd - Wio Terminal

I denne del af lektionen skal du skrive kode til at optage lyd på din Wio Terminal. Lydoptagelsen vil blive styret af en af knapperne på toppen af Wio Terminal.

## Programmer enheden til at optage lyd

Du kan optage lyd fra mikrofonen ved hjælp af C++-kode. Wio Terminal har kun 192KB RAM, hvilket ikke er nok til at optage mere end et par sekunders lyd. Den har dog 4MB flash-hukommelse, som i stedet kan bruges til at gemme den optagede lyd.

Den indbyggede mikrofon opfanger et analogt signal, som bliver konverteret til et digitalt signal, som Wio Terminal kan bruge. Når lyd optages, skal dataene fanges på det rigtige tidspunkt - for eksempel for at optage lyd ved 16KHz, skal lyden optages præcis 16.000 gange i sekundet med lige store intervaller mellem hver prøve. I stedet for at bruge din kode til dette, kan du bruge den direkte hukommelsesadgangskontroller (DMAC). Dette er kredsløb, der kan fange et signal fra et sted og skrive det til hukommelsen uden at afbryde din kode, der kører på processoren.

✅ Læs mere om DMA på [siden om direkte hukommelsesadgang på Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Lyd fra mikrofonen går til en ADC og derefter til DMAC. Dette skriver til en buffer. Når denne buffer er fuld, behandles den, og DMAC skriver til en anden buffer](../../../../../translated_images/da/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC kan optage lyd fra ADC'en med faste intervaller, for eksempel 16.000 gange i sekundet for 16KHz lyd. Den kan skrive disse optagede data til en forudallokeret hukommelsesbuffer, og når denne er fuld, gøre den tilgængelig for din kode til behandling. Brug af denne hukommelse kan forsinke lydoptagelsen, men du kan opsætte flere buffere. DMAC skriver til buffer 1, og når den er fuld, giver den besked til din kode om at behandle buffer 1, mens DMAC skriver til buffer 2. Når buffer 2 er fuld, giver den besked til din kode og går tilbage til at skrive til buffer 1. På den måde mister du ingen data, så længe du behandler hver buffer hurtigere, end det tager at fylde en.

Når hver buffer er blevet optaget, kan den skrives til flash-hukommelsen. Flash-hukommelse skal skrives til ved hjælp af definerede adresser, der angiver, hvor der skal skrives, og hvor meget der skal skrives, svarende til at opdatere et array af bytes i hukommelsen. Flash-hukommelse har granularitet, hvilket betyder, at slette- og skriveoperationer ikke kun afhænger af at være af en fast størrelse, men også af at være justeret til den størrelse. For eksempel, hvis granulariteten er 4096 bytes, og du anmoder om en sletning på adresse 4200, kan det slette alle data fra adresse 4096 til 8192. Dette betyder, at når du skriver lyddata til flash-hukommelsen, skal det være i stykker af den korrekte størrelse.

### Opgave - konfigurer flash-hukommelse

1. Opret et helt nyt Wio Terminal-projekt ved hjælp af PlatformIO. Kald dette projekt `smart-timer`. Tilføj kode i `setup`-funktionen for at konfigurere den serielle port.

1. Tilføj følgende biblioteksafhængigheder til `platformio.ini`-filen for at give adgang til flash-hukommelsen:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Åbn `main.cpp`-filen, og tilføj følgende include-direktiv for flash-hukommelsesbiblioteket øverst i filen:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD står for Serial Flash Universal Driver og er et bibliotek designet til at arbejde med alle flash-hukommelseschips.

1. I `setup`-funktionen skal du tilføje følgende kode for at opsætte flash-lagringsbiblioteket:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Dette gentages, indtil SFUD-biblioteket er initialiseret, og derefter aktiveres hurtige læsninger. Den indbyggede flash-hukommelse kan tilgås ved hjælp af en Queued Serial Peripheral Interface (QSPI), en type SPI-controller, der tillader kontinuerlig adgang via en kø med minimal processorbrug. Dette gør det hurtigere at læse og skrive til flash-hukommelsen.

1. Opret en ny fil i `src`-mappen kaldet `flash_writer.h`.

1. Tilføj følgende øverst i denne fil:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Dette inkluderer nogle nødvendige headerfiler, herunder headerfilen for SFUD-biblioteket til at interagere med flash-hukommelsen.

1. Definer en klasse i denne nye headerfil kaldet `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. I sektionen `private` skal du tilføje følgende kode:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Dette definerer nogle felter for bufferen, der skal bruges til at gemme data, før de skrives til flash-hukommelsen. Der er et byte-array, `_sfudBuffer`, til at skrive data til, og når dette er fuldt, skrives dataene til flash-hukommelsen. Feltet `_sfudBufferPos` gemmer den aktuelle placering, der skal skrives til i denne buffer, og `_sfudBufferWritePos` gemmer placeringen i flash-hukommelsen, der skal skrives til. `_flash` er en pointer til flash-hukommelsen, der skal skrives til - nogle mikrocontrollere har flere flash-hukommelseschips.

1. Tilføj følgende metode til sektionen `public` for at initialisere denne klasse:

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

    Dette konfigurerer flash-hukommelsen på Wio Terminal til at skrive til og opsætter buffere baseret på flash-hukommelsens granularitet. Dette er i en `init`-metode i stedet for en konstruktør, da dette skal kaldes, efter at flash-hukommelsen er blevet opsat i `setup`-funktionen.

1. Tilføj følgende kode til sektionen `public`:

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

    Denne kode definerer metoder til at skrive bytes til flash-lagringssystemet. Det fungerer ved at skrive til en buffer i hukommelsen, der har den rigtige størrelse til flash-hukommelsen, og når denne er fuld, skrives den til flash-hukommelsen, hvorved eksisterende data på det sted slettes. Der er også en `flushSfudBuffer` til at skrive en ufuldstændig buffer, da de data, der optages, ikke vil være præcise multipla af granulariteten, så den sidste del af dataene skal skrives.

    > 💁 Den sidste del af dataene vil skrive yderligere uønskede data, men det er ok, da kun de nødvendige data vil blive læst.

### Opgave - opsæt lydoptagelse

1. Opret en ny fil i `src`-mappen kaldet `config.h`.

1. Tilføj følgende øverst i denne fil:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Denne kode opsætter nogle konstanter til lydoptagelsen.

    | Konstant              | Værdi  | Beskrivelse |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Samplingsfrekvensen for lyden. 16.000 er 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Længden af lyden, der skal optages. Dette er sat til 4 sekunder. For at optage længere lyd skal du øge denne værdi. |
    | SAMPLES               | 64000  | Det samlede antal lydprøver, der vil blive optaget. Sat til samplingsfrekvensen * antallet af sekunder |
    | BUFFER_SIZE           | 128044 | Størrelsen af lydbufferen, der skal optages. Lyden vil blive optaget som en WAV-fil, som er 44 bytes header og derefter 128.000 bytes lyddata (hver prøve er 2 bytes) |
    | ADC_BUF_LEN           | 1600   | Størrelsen af buffere, der skal bruges til at optage lyd fra DMAC |

    > 💁 Hvis du synes, at 4 sekunder er for kort til at anmode om en timer, kan du øge værdien `SAMPLE_LENGTH_SECONDS`, og alle de andre værdier vil blive genberegnet.

1. Opret en ny fil i `src`-mappen kaldet `mic.h`.

1. Tilføj følgende øverst i denne fil:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Dette inkluderer nogle nødvendige headerfiler, herunder `config.h` og `FlashWriter`-headerfilerne.

1. Tilføj følgende for at definere en `Mic`-klasse, der kan optage fra mikrofonen:

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

    Denne klasse har i øjeblikket kun et par felter til at spore, om optagelsen er startet, og om en optagelse er klar til brug. Når DMAC er opsat, skriver den kontinuerligt til hukommelsesbuffere, så flaget `_isRecording` bestemmer, om disse skal behandles eller ignoreres. Flaget `_isRecordingReady` vil blive sat, når de nødvendige 4 sekunders lyd er blevet optaget. Feltet `_writer` bruges til at gemme lyddataene i flash-hukommelsen.

    En global variabel erklæres derefter for en instans af `Mic`-klassen.

1. Tilføj følgende kode til sektionen `private` i `Mic`-klassen:

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

    Denne kode definerer en `configureDmaAdc`-metode, der konfigurerer DMAC, forbinder den til ADC'en og sætter den til at udfylde to forskellige skiftende buffere, `_adc_buf_0` og `_adc_buf_1`.

    > 💁 En af ulemperne ved udvikling til mikrocontrollere er kompleksiteten af koden, der kræves for at interagere med hardware, da din kode kører på et meget lavt niveau og interagerer direkte med hardwaren. Denne kode er mere kompleks end det, du ville skrive til en enkeltkortcomputer eller en desktopcomputer, da der ikke er noget operativsystem til at hjælpe. Der findes nogle biblioteker, der kan forenkle dette, men der er stadig en del kompleksitet.

1. Tilføj nedenfor følgende kode:

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

    Denne kode definerer WAV-headeren som en struktur, der optager 44 bytes hukommelse. Den skriver detaljer til den om lydfilens hastighed, størrelse og antal kanaler. Denne header skrives derefter til flash-hukommelsen.

1. Tilføj nedenfor denne kode følgende for at erklære en metode, der skal kaldes, når lydbuffere er klar til behandling:

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

    Lydbuffere er arrays af 16-bit heltal, der indeholder lyden fra ADC'en. ADC'en returnerer 12-bit usignerede værdier (0-1023), så disse skal konverteres til 16-bit signerede værdier og derefter konverteres til 2 bytes for at blive gemt som rå binære data.

    Disse bytes skrives til flash-hukommelsesbuffere. Skrivningen starter ved indeks 44 - dette er forskydningen fra de 44 bytes, der er skrevet som WAV-filheader. Når alle de bytes, der er nødvendige for den krævede lydlængde, er blevet optaget, skrives de resterende data til flash-hukommelsen.

1. Tilføj følgende to metoder til sektionen `public` i `Mic`-klassen:

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

    Denne kode vil blive kaldt af DMAC for at fortælle din kode at behandle buffere. Den kontrollerer, at der er data at behandle, og kalder metoden `audioCallback` med den relevante buffer.

1. Uden for klassen, efter erklæringen `Mic mic;`, tilføj følgende kode:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` vil blive kaldt af DMAC, når buffere er klar til behandling. Denne funktion findes ved navn, så den skal bare eksistere for at blive kaldt.

1. Tilføj følgende to metoder til sektionen `public` i `Mic`-klassen:

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

    Metoden `init` indeholder kode til at initialisere `Mic`-klassen. Denne metode indstiller den korrekte spænding for Mic-pinnen, opsætter flash-hukommelsesskriveren, skriver WAV-filheaderen og konfigurerer DMAC. Metoden `reset` nulstiller flash-hukommelsen og gen-skriver headeren, efter at lyden er blevet optaget og brugt.

### Opgave - optag lyd

1. I `main.cpp`-filen skal du tilføje et include-direktiv for `mic.h`-headerfilen:

    ```cpp
    #include "mic.h"
    ```

1. I `setup`-funktionen skal du initialisere C-knappen. Lydoptagelsen starter, når denne knap trykkes, og fortsætter i 4 sekunder:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Tilføj nedenfor dette, initialiser mikrofonen, og udskriv til konsollen, at lyden er klar til at blive optaget:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Over `loop`-funktionen skal du definere en funktion til at behandle den optagede lyd. For nu gør denne funktion ikke noget, men senere i denne lektion vil den sende talen til at blive konverteret til tekst:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Tilføj følgende til `loop`-funktionen:

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

    Denne kode kontrollerer C-knappen, og hvis denne trykkes, og optagelsen ikke er startet, sættes feltet `_isRecording` i `Mic`-klassen til sandt. Dette vil få metoden `audioCallback` i `Mic`-klassen til at gemme lyd, indtil 4 sekunder er blevet optaget. Når 4 sekunder af lyd er blevet optaget, sættes feltet `_isRecording` til falsk, og feltet `_isRecordingReady` sættes til sandt. Dette kontrolleres derefter i `loop`-funktionen, og når det er sandt, kaldes funktionen `processAudio`, og derefter nulstilles `Mic`-klassen.

1. Byg denne kode, upload den til din Wio Terminal, og test den gennem den serielle monitor. Tryk på C-knappen (den på venstre side, tættest på tænd/sluk-knappen), og tal. 4 sekunders lyd vil blive optaget.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 Du kan finde denne kode i mappen [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Dit lydoptagelsesprogram var en succes!

---

**Ansvarsfraskrivelse**:  
Dette dokument er blevet oversat ved hjælp af AI-oversættelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selvom vi bestræber os på nøjagtighed, skal du være opmærksom på, at automatiserede oversættelser kan indeholde fejl eller unøjagtigheder. Det originale dokument på dets oprindelige sprog bør betragtes som den autoritative kilde. For kritisk information anbefales professionel menneskelig oversættelse. Vi er ikke ansvarlige for eventuelle misforståelser eller fejltolkninger, der måtte opstå som følge af brugen af denne oversættelse.