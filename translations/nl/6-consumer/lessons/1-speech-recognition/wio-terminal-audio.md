<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T22:38:01+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "nl"
}
-->
# Audio opnemen - Wio Terminal

In dit deel van de les ga je code schrijven om audio op te nemen met je Wio Terminal. Het opnemen van audio wordt bestuurd door een van de knoppen bovenop de Wio Terminal.

## Programmeer het apparaat om audio op te nemen

Je kunt audio opnemen via de microfoon met C++-code. De Wio Terminal heeft slechts 192KB RAM, wat niet genoeg is om meer dan een paar seconden audio op te nemen. Het apparaat heeft echter 4MB flashgeheugen, wat in plaats daarvan kan worden gebruikt om opgenomen audio op te slaan.

De ingebouwde microfoon neemt een analoog signaal op, dat wordt omgezet in een digitaal signaal dat de Wio Terminal kan gebruiken. Bij het opnemen van audio moet de data op het juiste moment worden vastgelegd - bijvoorbeeld, om audio op te nemen bij 16KHz, moet de audio precies 16.000 keer per seconde worden vastgelegd, met gelijke intervallen tussen elke sample. In plaats van je code hiervoor te gebruiken, kun je de Direct Memory Access Controller (DMAC) gebruiken. Dit is een circuit dat een signaal ergens vandaan kan opnemen en naar het geheugen kan schrijven, zonder je code op de processor te onderbreken.

✅ Lees meer over DMA op de [Direct Memory Access-pagina op Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Audio van de microfoon gaat naar een ADC en vervolgens naar de DMAC. Deze schrijft naar een buffer. Wanneer deze buffer vol is, wordt deze verwerkt en schrijft de DMAC naar een tweede buffer](../../../../../translated_images/nl/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

De DMAC kan audio van de ADC opnemen op vaste intervallen, zoals 16.000 keer per seconde voor 16KHz audio. Het kan deze opgenomen data schrijven naar een vooraf toegewezen geheugenbuffer, en wanneer deze vol is, beschikbaar maken voor je code om te verwerken. Het gebruik van dit geheugen kan het opnemen van audio vertragen, maar je kunt meerdere buffers instellen. De DMAC schrijft naar buffer 1, en wanneer deze vol is, geeft het een melding aan je code om buffer 1 te verwerken, terwijl de DMAC naar buffer 2 schrijft. Wanneer buffer 2 vol is, geeft het een melding aan je code en gaat terug naar het schrijven naar buffer 1. Op deze manier verlies je geen data zolang je elke buffer sneller verwerkt dan het duurt om er een te vullen.

Zodra elke buffer is vastgelegd, kan deze worden geschreven naar het flashgeheugen. Flashgeheugen moet worden geschreven met gedefinieerde adressen, waarbij wordt aangegeven waar te schrijven en hoe groot de schrijfoperatie moet zijn, vergelijkbaar met het bijwerken van een array van bytes in het geheugen. Flashgeheugen heeft granulariteit, wat betekent dat wis- en schrijfoperaties niet alleen van een vaste grootte moeten zijn, maar ook moeten worden uitgelijnd op die grootte. Bijvoorbeeld, als de granulariteit 4096 bytes is en je een wisoperatie aanvraagt op adres 4200, kan het alle data wissen van adres 4096 tot 8192. Dit betekent dat wanneer je de audiogegevens naar het flashgeheugen schrijft, dit in blokken van de juiste grootte moet gebeuren.

### Taak - flashgeheugen configureren

1. Maak een nieuw Wio Terminal-project aan met PlatformIO. Noem dit project `smart-timer`. Voeg code toe in de `setup`-functie om de seriële poort te configureren.

1. Voeg de volgende bibliotheekafhankelijkheden toe aan het `platformio.ini`-bestand om toegang te krijgen tot het flashgeheugen:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Open het `main.cpp`-bestand en voeg de volgende include-richtlijn voor de flashgeheugenbibliotheek toe aan de bovenkant van het bestand:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD staat voor Serial Flash Universal Driver, en is een bibliotheek ontworpen om te werken met alle flashgeheugenchips.

1. Voeg in de `setup`-functie de volgende code toe om de flashopslagbibliotheek in te stellen:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Deze code blijft in een lus totdat de SFUD-bibliotheek is geïnitialiseerd en schakelt vervolgens snelle leesbewerkingen in. Het ingebouwde flashgeheugen kan worden benaderd met behulp van een Queued Serial Peripheral Interface (QSPI), een type SPI-controller die continue toegang via een wachtrij mogelijk maakt met minimale processorbelasting. Dit maakt het sneller om te lezen en te schrijven naar het flashgeheugen.

1. Maak een nieuw bestand in de `src`-map genaamd `flash_writer.h`.

1. Voeg het volgende toe aan de bovenkant van dit bestand:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Dit bevat enkele benodigde headerbestanden, waaronder het headerbestand voor de SFUD-bibliotheek om te communiceren met het flashgeheugen.

1. Definieer een klasse in dit nieuwe headerbestand genaamd `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Voeg in de `private`-sectie de volgende code toe:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Dit definieert enkele velden voor de buffer die wordt gebruikt om gegevens op te slaan voordat deze naar het flashgeheugen worden geschreven. Er is een byte-array, `_sfudBuffer`, om gegevens naar te schrijven, en wanneer deze vol is, worden de gegevens naar het flashgeheugen geschreven. Het veld `_sfudBufferPos` slaat de huidige locatie op om naar deze buffer te schrijven, en `_sfudBufferWritePos` slaat de locatie in het flashgeheugen op om naar te schrijven. `_flash` is een pointer naar het flashgeheugen om naar te schrijven - sommige microcontrollers hebben meerdere flashgeheugenchips.

1. Voeg de volgende methode toe aan de `public`-sectie om deze klasse te initialiseren:

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

    Dit configureert het flashgeheugen op de Wio Terminal om naar te schrijven en stelt de buffers in op basis van de korrelgrootte van het flashgeheugen. Dit bevindt zich in een `init`-methode in plaats van een constructor, omdat dit moet worden aangeroepen nadat het flashgeheugen is ingesteld in de `setup`-functie.

1. Voeg de volgende code toe aan de `public`-sectie:

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

    Deze code definieert methoden om bytes naar het flashopslagsysteem te schrijven. Het werkt door te schrijven naar een in-memory buffer die de juiste grootte heeft voor het flashgeheugen, en wanneer deze vol is, wordt deze geschreven naar het flashgeheugen, waarbij bestaande gegevens op die locatie worden gewist. Er is ook een `flushSfudBuffer` om een onvolledige buffer te schrijven, omdat de vastgelegde gegevens geen exacte veelvouden van de korrelgrootte zullen zijn, dus het laatste deel van de gegevens moet worden geschreven.

    > 💁 Het laatste deel van de gegevens zal extra ongewenste gegevens schrijven, maar dit is oké omdat alleen de benodigde gegevens worden gelezen.

### Taak - audio-opname instellen

1. Maak een nieuw bestand in de `src`-map genaamd `config.h`.

1. Voeg het volgende toe aan de bovenkant van dit bestand:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Deze code stelt enkele constanten in voor de audio-opname.

    | Constante             | Waarde | Beschrijving |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | De samplefrequentie voor de audio. 16.000 is 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | De lengte van de audio om op te nemen. Dit is ingesteld op 4 seconden. Om langere audio op te nemen, verhoog deze waarde. |
    | SAMPLES               | 64000  | Het totale aantal audiomonsters dat wordt vastgelegd. Ingesteld op de samplefrequentie * het aantal seconden |
    | BUFFER_SIZE           | 128044 | De grootte van de audiobuffer om vast te leggen. Audio wordt vastgelegd als een WAV-bestand, dat 44 bytes header bevat, gevolgd door 128.000 bytes audiogegevens (elke sample is 2 bytes) |
    | ADC_BUF_LEN           | 1600   | De grootte van de buffers die worden gebruikt om audio van de DMAC vast te leggen |

    > 💁 Als je merkt dat 4 seconden te kort is om een timer aan te vragen, kun je de waarde van `SAMPLE_LENGTH_SECONDS` verhogen, en alle andere waarden worden opnieuw berekend.

1. Maak een nieuw bestand in de `src`-map genaamd `mic.h`.

1. Voeg het volgende toe aan de bovenkant van dit bestand:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Dit bevat enkele benodigde headerbestanden, waaronder de `config.h`- en `FlashWriter`-headerbestanden.

1. Voeg het volgende toe om een `Mic`-klasse te definiëren die kan opnemen van de microfoon:

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

    Deze klasse heeft momenteel slechts een paar velden om bij te houden of de opname is gestart en of een opname klaar is om te worden gebruikt. Wanneer de DMAC is ingesteld, schrijft deze continu naar geheugenbuffers, dus de `_isRecording`-vlag bepaalt of deze moeten worden verwerkt of genegeerd. De `_isRecordingReady`-vlag wordt ingesteld wanneer de vereiste 4 seconden audio is vastgelegd. Het `_writer`-veld wordt gebruikt om de audiogegevens naar het flashgeheugen op te slaan.

    Een globale variabele wordt vervolgens gedeclareerd voor een instantie van de `Mic`-klasse.

1. Voeg de volgende code toe aan de `private`-sectie van de `Mic`-klasse:

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

    Deze code definieert een `configureDmaAdc`-methode die de DMAC configureert, deze verbindt met de ADC en instelt om twee verschillende afwisselende buffers te vullen, `_adc_buf_0` en `_adc_buf_1`.

    > 💁 Een van de nadelen van microcontrollerontwikkeling is de complexiteit van de code die nodig is om met hardware te communiceren, omdat je code op een zeer laag niveau direct met hardware werkt. Deze code is complexer dan wat je zou schrijven voor een single-board computer of desktopcomputer, omdat er geen besturingssysteem is dat helpt. Er zijn enkele bibliotheken beschikbaar die dit kunnen vereenvoudigen, maar er blijft veel complexiteit.

1. Voeg hieronder de volgende code toe:

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

    Deze code definieert de WAV-header als een struct die 44 bytes geheugen inneemt. Het schrijft details naar de header over de audiobestandssnelheid, grootte en aantal kanalen. Deze header wordt vervolgens geschreven naar het flashgeheugen.

1. Voeg hieronder de volgende code toe om een methode te declareren die wordt aangeroepen wanneer de audiobuffers klaar zijn om te worden verwerkt:

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

    De audiobuffers zijn arrays van 16-bits integers die de audio van de ADC bevatten. De ADC retourneert 12-bits unsigned waarden (0-1023), dus deze moeten worden geconverteerd naar 16-bits signed waarden en vervolgens worden omgezet in 2 bytes om te worden opgeslagen als ruwe binaire gegevens.

    Deze bytes worden geschreven naar de flashgeheugenbuffers. Het schrijven begint bij index 44 - dit is de offset van de 44 bytes die als de WAV-bestandheader zijn geschreven. Zodra alle bytes die nodig zijn voor de vereiste audiolengte zijn vastgelegd, worden de resterende gegevens geschreven naar het flashgeheugen.

1. Voeg de volgende code toe aan de `public`-sectie van de `Mic`-klasse:

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

    Deze code wordt aangeroepen door de DMAC om je code te vertellen dat de buffers klaar zijn om te worden verwerkt. Het controleert of er gegevens zijn om te verwerken en roept de `audioCallback`-methode aan met de relevante buffer.

1. Voeg buiten de klasse, na de `Mic mic;`-declaratie, de volgende code toe:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    De `DMAC_1_Handler` wordt aangeroepen door de DMAC wanneer de buffers klaar zijn om te worden verwerkt. Deze functie wordt op naam gevonden, dus hoeft alleen te bestaan om te worden aangeroepen.

1. Voeg de volgende twee methoden toe aan de `public`-sectie van de `Mic`-klasse:

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

    De `init`-methode bevat code om de `Mic`-klasse te initialiseren. Deze methode stelt de juiste spanning in voor de Mic-pin, stelt de flashgeheugenschrijver in, schrijft de WAV-bestandheader en configureert de DMAC. De `reset`-methode reset het flashgeheugen en schrijft de header opnieuw nadat de audio is vastgelegd en gebruikt.

### Taak - audio opnemen

1. Voeg in het `main.cpp`-bestand een include-richtlijn toe voor het `mic.h`-headerbestand:

    ```cpp
    #include "mic.h"
    ```

1. Initialiseer in de `setup`-functie de C-knop. Audio-opname start wanneer deze knop wordt ingedrukt en duurt 4 seconden:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Initialiseer hieronder de microfoon en print naar de console dat audio klaar is om te worden opgenomen:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Definieer boven de `loop`-functie een functie om de opgenomen audio te verwerken. Voor nu doet deze niets, maar later in deze les zal deze de spraak omzetten naar tekst:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Voeg het volgende toe aan de `loop`-functie:

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

    Deze code controleert de C-knop, en als deze wordt ingedrukt en de opname nog niet is gestart, wordt het `_isRecording`-veld van de `Mic`-klasse ingesteld op true. Dit zorgt ervoor dat de `audioCallback`-methode van de `Mic`-klasse audio opslaat totdat 4 seconden zijn vastgelegd. Zodra 4 seconden audio zijn vastgelegd, wordt het `_isRecording`-veld ingesteld op false en het `_isRecordingReady`-veld ingesteld op true. Dit wordt vervolgens gecontroleerd in de `loop`-functie, en wanneer true wordt de `processAudio`-functie aangeroepen, waarna de mic-klasse wordt gereset.

1. Bouw deze code, upload deze naar je Wio Terminal en test het via de seriële monitor. Druk op de C-knop (de knop aan de linkerkant, het dichtst bij de aan/uit-schakelaar) en spreek. Er wordt 4 seconden audio opgenomen.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Je kunt deze code vinden in de [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) map.
😀 Je audiorecorderprogramma was een succes!

---

**Disclaimer**:  
Dit document is vertaald met behulp van de AI-vertalingsservice [Co-op Translator](https://github.com/Azure/co-op-translator). Hoewel we streven naar nauwkeurigheid, dient u zich ervan bewust te zijn dat geautomatiseerde vertalingen fouten of onnauwkeurigheden kunnen bevatten. Het originele document in zijn oorspronkelijke taal moet worden beschouwd als de gezaghebbende bron. Voor cruciale informatie wordt professionele menselijke vertaling aanbevolen. Wij zijn niet aansprakelijk voor eventuele misverstanden of verkeerde interpretaties die voortvloeien uit het gebruik van deze vertaling.