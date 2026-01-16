<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T21:10:22+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "no"
}
-->
# Fange lyd - Wio Terminal

I denne delen av leksjonen skal du skrive kode for å fange lyd på din Wio Terminal. Lydopptak vil bli kontrollert av en av knappene på toppen av Wio Terminal.

## Programmer enheten til å fange lyd

Du kan fange lyd fra mikrofonen ved hjelp av C++-kode. Wio Terminal har kun 192KB RAM, som ikke er nok til å fange mer enn et par sekunder med lyd. Den har også 4MB flashminne, som kan brukes i stedet, og lagre fanget lyd i flashminnet.

Den innebygde mikrofonen fanger et analogt signal, som blir konvertert til et digitalt signal som Wio Terminal kan bruke. Når du fanger lyd, må dataene fanges på riktig tidspunkt - for eksempel for å fange lyd ved 16KHz, må lyden fanges nøyaktig 16 000 ganger per sekund, med like intervaller mellom hver prøve. I stedet for å bruke koden din til å gjøre dette, kan du bruke Direct Memory Access Controller (DMAC). Dette er en krets som kan fange et signal fra et sted og skrive til minnet, uten å avbryte koden som kjører på prosessoren.

✅ Les mer om DMA på [Direct Memory Access-siden på Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Lyd fra mikrofonen går til en ADC og deretter til DMAC. Dette skriver til én buffer. Når denne bufferen er full, blir den behandlet, og DMAC skriver til en annen buffer](../../../../../translated_images/no/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC kan fange lyd fra ADC med faste intervaller, for eksempel 16 000 ganger i sekundet for 16KHz lyd. Den kan skrive disse fangede dataene til en forhåndsallokert minnebuffer, og når denne er full, gjøre den tilgjengelig for koden din for behandling. Bruk av dette minnet kan forsinke lydopptak, men du kan sette opp flere buffere. DMAC skriver til buffer 1, og når den er full, varsler den koden din om å behandle buffer 1, mens DMAC skriver til buffer 2. Når buffer 2 er full, varsler den koden din og går tilbake til å skrive til buffer 1. På den måten, så lenge du behandler hver buffer raskere enn det tar å fylle en, vil du ikke miste noen data.

Når hver buffer er fanget, kan den skrives til flashminnet. Flashminne må skrives til ved hjelp av definerte adresser, som spesifiserer hvor du skal skrive og hvor stort du skal skrive, på samme måte som å oppdatere en byte-array i minnet. Flashminne har granularitet, noe som betyr at slette- og skriveoperasjoner ikke bare må være av en fast størrelse, men også tilpasses den størrelsen. For eksempel, hvis granulariteten er 4096 bytes og du ber om en sletting på adresse 4200, kan det slette alle data fra adresse 4096 til 8192. Dette betyr at når du skriver lyddata til flashminnet, må det være i biter av riktig størrelse.

### Oppgave - konfigurer flashminne

1. Opprett et helt nytt Wio Terminal-prosjekt ved hjelp av PlatformIO. Kall dette prosjektet `smart-timer`. Legg til kode i `setup`-funksjonen for å konfigurere den serielle porten.

1. Legg til følgende biblioteksavhengigheter i `platformio.ini`-filen for å gi tilgang til flashminnet:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Åpne `main.cpp`-filen og legg til følgende inkluderingsdirektiv for flashminnebiblioteket øverst i filen:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD står for Serial Flash Universal Driver, og er et bibliotek designet for å fungere med alle flashminnebrikker.

1. I `setup`-funksjonen, legg til følgende kode for å sette opp flashlagringsbiblioteket:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Dette looper til SFUD-biblioteket er initialisert, og aktiverer deretter raske lesinger. Det innebygde flashminnet kan nås ved hjelp av en Queued Serial Peripheral Interface (QSPI), en type SPI-kontroller som tillater kontinuerlig tilgang via en kø med minimal prosessorbruk. Dette gjør det raskere å lese og skrive til flashminnet.

1. Opprett en ny fil i `src`-mappen kalt `flash_writer.h`.

1. Legg til følgende øverst i denne filen:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Dette inkluderer noen nødvendige headerfiler, inkludert headerfilen for SFUD-biblioteket for å samhandle med flashminnet.

1. Definer en klasse i denne nye headerfilen kalt `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. I `private`-seksjonen, legg til følgende kode:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Dette definerer noen felt for bufferen som skal brukes til å lagre data før de skrives til flashminnet. Det er en byte-array, `_sfudBuffer`, for å skrive data til, og når denne er full, blir dataene skrevet til flashminnet. Feltet `_sfudBufferPos` lagrer den nåværende posisjonen for å skrive til denne bufferen, og `_sfudBufferWritePos` lagrer posisjonen i flashminnet for å skrive til. `_flash` er en peker til flashminnet som skal skrives til - noen mikrokontrollere har flere flashminnebrikker.

1. Legg til følgende metode i `public`-seksjonen for å initialisere denne klassen:

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

    Dette konfigurerer flashminnet på Wio Terminal for å skrive til, og setter opp buffere basert på granulariteten til flashminnet. Dette er i en `init`-metode, i stedet for en konstruktør, da dette må kalles etter at flashminnet er satt opp i `setup`-funksjonen.

1. Legg til følgende kode i `public`-seksjonen:

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

    Denne koden definerer metoder for å skrive bytes til flashlagringssystemet. Det fungerer ved å skrive til en buffer i minnet som har riktig størrelse for flashminnet, og når denne er full, blir den skrevet til flashminnet, og sletter eventuelle eksisterende data på den posisjonen. Det er også en `flushSfudBuffer` for å skrive en ufullstendig buffer, da dataene som fanges ikke vil være eksakte multipler av granulariteten, så den siste delen av dataene må skrives.

    > 💁 Den siste delen av dataene vil skrive ekstra uønskede data, men dette er greit, da kun de nødvendige dataene vil bli lest.

### Oppgave - sett opp lydopptak

1. Opprett en ny fil i `src`-mappen kalt `config.h`.

1. Legg til følgende øverst i denne filen:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Denne koden setter opp noen konstanter for lydopptak.

    | Konstant              | Verdi  | Beskrivelse |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Samplingsfrekvensen for lyden. 16 000 er 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Lengden på lyden som skal fanges. Dette er satt til 4 sekunder. For å ta opp lengre lyd, øk denne verdien. |
    | SAMPLES               | 64000  | Totalt antall lydprøver som vil bli fanget. Satt til samplingsfrekvensen * antall sekunder |
    | BUFFER_SIZE           | 128044 | Størrelsen på lydbufferen som skal fanges. Lyden vil bli fanget som en WAV-fil, som er 44 bytes med header, deretter 128 000 bytes med lyddata (hver prøve er 2 bytes) |
    | ADC_BUF_LEN           | 1600   | Størrelsen på buffere som skal brukes til å fange lyd fra DMAC |

    > 💁 Hvis du synes 4 sekunder er for kort for å be om en timer, kan du øke verdien `SAMPLE_LENGTH_SECONDS`, og alle de andre verdiene vil bli rekalkulert.

1. Opprett en ny fil i `src`-mappen kalt `mic.h`.

1. Legg til følgende øverst i denne filen:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Dette inkluderer noen nødvendige headerfiler, inkludert `config.h` og `FlashWriter`-headerfilene.

1. Legg til følgende for å definere en `Mic`-klasse som kan fange fra mikrofonen:

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

    Denne klassen har foreløpig bare et par felt for å spore om opptak har startet, og om et opptak er klart til bruk. Når DMAC er satt opp, skriver den kontinuerlig til minnebuffere, så flagget `_isRecording` avgjør om disse skal behandles eller ignoreres. Flagget `_isRecordingReady` vil bli satt når de nødvendige 4 sekundene med lyd er fanget. Feltet `_writer` brukes til å lagre lyddataene til flashminnet.

    En global variabel blir deretter erklært for en instans av `Mic`-klassen.

1. Legg til følgende kode i `private`-seksjonen av `Mic`-klassen:

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

    Denne koden definerer en `configureDmaAdc`-metode som konfigurerer DMAC, kobler den til ADC og setter den til å fylle to forskjellige alternerende buffere, `_adc_buf_0` og `_adc_buf_1`.

    > 💁 En av ulempene med mikrokontrollerutvikling er kompleksiteten i koden som trengs for å samhandle med maskinvare, da koden din kjører på et veldig lavt nivå og samhandler direkte med maskinvaren. Denne koden er mer kompleks enn det du ville skrevet for en enkeltkortdatamaskin eller stasjonær datamaskin, da det ikke finnes noe operativsystem som hjelper til. Det finnes noen biblioteker som kan forenkle dette, men det er fortsatt mye kompleksitet.

1. Under dette, legg til følgende kode:

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

    Denne koden definerer WAV-headeren som en struktur som tar opp 44 bytes med minne. Den skriver detaljer til den om lydfilens frekvens, størrelse og antall kanaler. Denne headeren blir deretter skrevet til flashminnet.

1. Under denne koden, legg til følgende for å erklære en metode som skal kalles når lydbufferne er klare til behandling:

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

    Lydbufferne er arrays av 16-bit heltall som inneholder lyden fra ADC. ADC returnerer 12-bit usignerte verdier (0-1023), så disse må konverteres til 16-bit signerte verdier, og deretter konverteres til 2 bytes for å lagres som rå binærdata.

    Disse bytes blir skrevet til flashminnebuffere. Skrivingen starter på indeks 44 - dette er offset fra de 44 bytes som er skrevet som WAV-filheader. Når alle bytes som trengs for den nødvendige lydlengden er fanget, blir de resterende dataene skrevet til flashminnet.

1. I `public`-seksjonen av `Mic`-klassen, legg til følgende kode:

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

    Denne koden vil bli kalt av DMAC for å fortelle koden din å behandle bufferne. Den sjekker at det er data å behandle, og kaller `audioCallback`-metoden med den relevante bufferen.

1. Utenfor klassen, etter deklarasjonen `Mic mic;`, legg til følgende kode:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` vil bli kalt av DMAC når bufferne er klare til behandling. Denne funksjonen blir funnet ved navn, så den trenger bare å eksistere for å bli kalt.

1. Legg til følgende to metoder i `public`-seksjonen av `Mic`-klassen:

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

    `init`-metoden inneholder kode for å initialisere `Mic`-klassen. Denne metoden setter riktig spenning for Mic-pinnen, setter opp flashminneskriveren, skriver WAV-filheaderen, og konfigurerer DMAC. `reset`-metoden tilbakestiller flashminnet og skriver headeren på nytt etter at lyden er fanget og brukt.

### Oppgave - fang lyd

1. I `main.cpp`-filen, legg til et inkluderingsdirektiv for `mic.h`-headerfilen:

    ```cpp
    #include "mic.h"
    ```

1. I `setup`-funksjonen, initialiser C-knappen. Lydopptak vil starte når denne knappen trykkes, og fortsette i 4 sekunder:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Under dette, initialiser mikrofonen, og skriv deretter til konsollen at lyden er klar til å bli fanget:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Over `loop`-funksjonen, definer en funksjon for å behandle den fangede lyden. Foreløpig gjør denne ingenting, men senere i leksjonen vil den sende talen for å bli konvertert til tekst:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Legg til følgende i `loop`-funksjonen:

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

    Denne koden sjekker C-knappen, og hvis denne er trykket og opptak ikke har startet, settes feltet `_isRecording` i `Mic`-klassen til true. Dette vil føre til at `audioCallback`-metoden i `Mic`-klassen lagrer lyd til 4 sekunder er fanget. Når 4 sekunder med lyd er fanget, settes feltet `_isRecording` til false, og feltet `_isRecordingReady` settes til true. Dette sjekkes deretter i `loop`-funksjonen, og når det er true, kalles `processAudio`-funksjonen, og deretter tilbakestilles `Mic`-klassen.

1. Bygg denne koden, last den opp til din Wio Terminal og test den gjennom den serielle monitoren. Trykk på C-knappen (den på venstre side, nærmest strømbryteren), og snakk. 4 sekunder med lyd vil bli fanget.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 Du finner denne koden i [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal)-mappen.
😀 Lydopptaksprogrammet ditt var en suksess!

---

**Ansvarsfraskrivelse**:  
Dette dokumentet er oversatt ved hjelp av AI-oversettelsestjenesten [Co-op Translator](https://github.com/Azure/co-op-translator). Selv om vi streber etter nøyaktighet, vær oppmerksom på at automatiske oversettelser kan inneholde feil eller unøyaktigheter. Det originale dokumentet på sitt opprinnelige språk bør anses som den autoritative kilden. For kritisk informasjon anbefales profesjonell menneskelig oversettelse. Vi er ikke ansvarlige for misforståelser eller feiltolkninger som oppstår ved bruk av denne oversettelsen.