# Zachytávanie zvuku - Wio Terminal

V tejto časti lekcie napíšete kód na zachytávanie zvuku na vašom zariadení Wio Terminal. Zachytávanie zvuku bude ovládané jedným z tlačidiel na vrchnej strane Wio Terminalu.

## Naprogramujte zariadenie na zachytávanie zvuku

Zvuk môžete zachytávať z mikrofónu pomocou kódu v jazyku C++. Wio Terminal má iba 192 KB RAM, čo nestačí na zachytenie viac ako niekoľkých sekúnd zvuku. Má však 4 MB flash pamäte, ktorá sa dá použiť na uloženie zachyteného zvuku.

Vstavaný mikrofón zachytáva analógový signál, ktorý sa konvertuje na digitálny signál, ktorý môže Wio Terminal spracovať. Pri zachytávaní zvuku je potrebné dáta zachytávať v správnych časových intervaloch – napríklad na zachytávanie zvuku pri 16 kHz je potrebné zachytávať zvuk presne 16 000-krát za sekundu, s rovnakými intervalmi medzi jednotlivými vzorkami. Namiesto toho, aby ste na to použili svoj kód, môžete využiť radič priameho prístupu do pamäte (DMAC). Ide o obvod, ktorý dokáže zachytiť signál a zapísať ho do pamäte bez prerušenia kódu bežiaceho na procesore.

✅ Prečítajte si viac o DMA na [stránke o priamom prístupe do pamäte na Wikipédii](https://wikipedia.org/wiki/Direct_memory_access).

![Zvuk z mikrofónu prechádza do ADC a potom do DMAC. DMAC zapisuje do jedného bufferu. Keď je tento buffer plný, spracuje sa a DMAC zapisuje do druhého bufferu](../../../../../translated_images/sk/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC dokáže zachytávať zvuk z ADC v pevných intervaloch, napríklad 16 000-krát za sekundu pre zvuk pri 16 kHz. Zachytené dáta môže zapisovať do predalokovaného pamäťového bufferu, a keď je tento buffer plný, sprístupní ho vášmu kódu na spracovanie. Používanie tejto pamäte môže oneskoriť zachytávanie zvuku, ale môžete nastaviť viacero bufferov. DMAC zapisuje do bufferu 1, a keď je tento plný, upozorní váš kód na spracovanie bufferu 1, zatiaľ čo DMAC zapisuje do bufferu 2. Keď je buffer 2 plný, upozorní váš kód a vráti sa k zapisovaniu do bufferu 1. Takto, pokiaľ spracujete každý buffer rýchlejšie, než sa naplní, nestratíte žiadne dáta.

Keď je každý buffer zachytený, môže sa zapísať do flash pamäte. Flash pamäť je potrebné zapisovať pomocou definovaných adries, ktoré špecifikujú, kam a akú veľkú časť zapísať, podobne ako pri aktualizácii poľa bajtov v pamäti. Flash pamäť má granularitu, čo znamená, že operácie mazania a zapisovania závisia nielen od pevnej veľkosti, ale aj od zarovnania na túto veľkosť. Napríklad, ak je granularita 4096 bajtov a požiadate o vymazanie na adrese 4200, môže sa vymazať všetky dáta od adresy 4096 do 8192. To znamená, že keď zapisujete zvukové dáta do flash pamäte, musia byť v správne veľkých blokoch.

### Úloha - konfigurácia flash pamäte

1. Vytvorte nový projekt pre Wio Terminal pomocou PlatformIO. Nazvite tento projekt `smart-timer`. Pridajte kód do funkcie `setup` na konfiguráciu sériového portu.

1. Pridajte nasledujúce knižničné závislosti do súboru `platformio.ini`, aby ste získali prístup k flash pamäti:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Otvorte súbor `main.cpp` a pridajte nasledujúci príkaz `include` pre knižnicu flash pamäte na začiatok súboru:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD znamená Serial Flash Universal Driver, čo je knižnica navrhnutá na prácu so všetkými čipmi flash pamäte.

1. Vo funkcii `setup` pridajte nasledujúci kód na nastavenie knižnice pre flash pamäť:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Tento kód sa opakuje, kým sa knižnica SFUD neinitializuje, a potom zapne rýchle čítanie. Vstavaná flash pamäť môže byť prístupná pomocou Queued Serial Peripheral Interface (QSPI), čo je typ SPI radiča, ktorý umožňuje kontinuálny prístup cez frontu s minimálnym využitím procesora. To umožňuje rýchlejšie čítanie a zapisovanie do flash pamäte.

1. Vytvorte nový súbor v priečinku `src` s názvom `flash_writer.h`.

1. Pridajte nasledujúci kód na začiatok tohto súboru:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Tento kód obsahuje niektoré potrebné hlavičkové súbory, vrátane hlavičkového súboru pre knižnicu SFUD na interakciu s flash pamäťou.

1. Definujte triedu v tomto novom hlavičkovom súbore s názvom `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. V sekcii `private` pridajte nasledujúci kód:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Tento kód definuje niektoré polia pre buffer, ktorý sa použije na ukladanie dát pred ich zapisovaním do flash pamäte. Je tu pole bajtov `_sfudBuffer`, do ktorého sa zapisujú dáta, a keď je toto pole plné, dáta sa zapíšu do flash pamäte. Pole `_sfudBufferPos` uchováva aktuálnu pozíciu na zapisovanie v tomto buffere a `_sfudBufferWritePos` uchováva pozíciu vo flash pamäti na zapisovanie. `_flash` je ukazovateľ na flash pamäť, do ktorej sa zapisuje – niektoré mikrokontroléry majú viacero čipov flash pamäte.

1. Pridajte nasledujúcu metódu do sekcie `public` na inicializáciu tejto triedy:

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

    Tento kód konfiguruje flash pamäť na Wio Terminal na zapisovanie a nastavuje buffery na základe veľkosti zrna flash pamäte. Je to v metóde `init`, a nie v konštruktore, pretože táto metóda musí byť volaná po nastavení flash pamäte vo funkcii `setup`.

1. Pridajte nasledujúci kód do sekcie `public`:

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

    Tento kód definuje metódy na zapisovanie bajtov do systému flash pamäte. Funguje tak, že zapisuje do pamäťového bufferu, ktorý má správnu veľkosť pre flash pamäť, a keď je tento buffer plný, zapíše sa do flash pamäte, pričom sa vymažú všetky existujúce dáta na tejto pozícii. Je tu aj metóda `flushSfudBuffer` na zapisovanie neúplného bufferu, pretože zachytávané dáta nebudú presnými násobkami veľkosti zrna, takže koncová časť dát musí byť zapísaná.

    > 💁 Koncová časť dát zapíše aj ďalšie nechcené dáta, ale to je v poriadku, pretože sa prečíta iba potrebná časť dát.

### Úloha - nastavenie zachytávania zvuku

1. Vytvorte nový súbor v priečinku `src` s názvom `config.h`.

1. Pridajte nasledujúci kód na začiatok tohto súboru:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Tento kód nastavuje niektoré konštanty pre zachytávanie zvuku.

    | Konštanta             | Hodnota | Popis |
    | --------------------- | ------: | - |
    | RATE                  | 16000   | Vzorkovacia frekvencia zvuku. 16 000 je 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4       | Dĺžka zachytávaného zvuku. Nastavené na 4 sekundy. Ak chcete nahrávať dlhší zvuk, zvýšte túto hodnotu. |
    | SAMPLES               | 64000   | Celkový počet zvukových vzoriek, ktoré sa zachytia. Nastavené na vzorkovaciu frekvenciu * počet sekúnd |
    | BUFFER_SIZE           | 128044  | Veľkosť bufferu na zachytávanie zvuku. Zvuk sa bude zachytávať ako WAV súbor, ktorý má 44 bajtov hlavičky a 128 000 bajtov zvukových dát (každá vzorka má 2 bajty) |
    | ADC_BUF_LEN           | 1600    | Veľkosť bufferov na zachytávanie zvuku z DMAC |

    > 💁 Ak zistíte, že 4 sekundy sú príliš krátke na požiadanie časovača, môžete zvýšiť hodnotu `SAMPLE_LENGTH_SECONDS` a všetky ostatné hodnoty sa prepočítajú.

1. Vytvorte nový súbor v priečinku `src` s názvom `mic.h`.

1. Pridajte nasledujúci kód na začiatok tohto súboru:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Tento kód obsahuje niektoré potrebné hlavičkové súbory, vrátane `config.h` a hlavičkového súboru `FlashWriter`.

1. Pridajte nasledujúci kód na definovanie triedy `Mic`, ktorá dokáže zachytávať zvuk z mikrofónu:

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

    Táto trieda momentálne obsahuje iba niekoľko polí na sledovanie, či sa nahrávanie začalo, a či je nahrávka pripravená na použitie. Keď je DMAC nastavený, nepretržite zapisuje do pamäťových bufferov, takže príznak `_isRecording` určuje, či by sa tieto mali spracovať alebo ignorovať. Príznak `_isRecordingReady` sa nastaví, keď sa zachytí požadovaných 4 sekundy zvuku. Pole `_writer` sa používa na ukladanie zvukových dát do flash pamäte.

    Potom sa deklaruje globálna premenná pre inštanciu triedy `Mic`.

1. Pridajte nasledujúci kód do sekcie `private` triedy `Mic`:

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

    Tento kód definuje metódu `configureDmaAdc`, ktorá konfiguruje DMAC, pripojí ho k ADC a nastaví ho na striedavé vypĺňanie dvoch rôznych bufferov, `_adc_buf_0` a `_adc_buf_1`.

    > 💁 Jednou z nevýhod vývoja pre mikrokontroléry je zložitosť kódu potrebného na interakciu s hardvérom, pretože váš kód beží na veľmi nízkej úrovni a priamo komunikuje s hardvérom. Tento kód je zložitejší ako to, čo by ste napísali pre jednodeskový počítač alebo stolný počítač, pretože tu nie je operačný systém, ktorý by pomohol. Existujú niektoré knižnice, ktoré to môžu zjednodušiť, ale stále je tu veľa zložitostí.

1. Nižšie pridajte nasledujúci kód:

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

    Tento kód definuje hlavičku WAV ako štruktúru, ktorá zaberá 44 bajtov pamäte. Do tejto hlavičky sa zapisujú podrobnosti o vzorkovacej frekvencii, veľkosti a počte kanálov zvukového súboru. Táto hlavička sa potom zapíše do flash pamäte.

1. Nižšie pridajte nasledujúci kód na deklaráciu metódy, ktorá sa zavolá, keď sú zvukové buffery pripravené na spracovanie:

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

    Zvukové buffery sú polia 16-bitových celých čísel obsahujúcich zvuk z ADC. ADC vracia 12-bitové neznamienkové hodnoty (0-1023), takže tieto je potrebné konvertovať na 16-bitové znamienkové hodnoty a potom na 2 bajty, aby sa uložili ako surové binárne dáta.

    Tieto bajty sa zapisujú do bufferov flash pamäte. Zápis začína na indexe 44 – to je posun od 44 bajtov zapísaných ako hlavička WAV súboru. Keď sa zachytí všetky potrebné bajty pre požadovanú dĺžku zvuku, zvyšné dáta sa zapíšu do flash pamäte.

1. V sekcii `public` triedy `Mic` pridajte nasledujúci kód:

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

    Tento kód zavolá DMAC, aby oznámil vášmu kódu, že buffery sú pripravené na spracovanie. Skontroluje, či sú dáta na spracovanie, a zavolá metódu `audioCallback` s príslušným bufferom.

1. Mimo triedy, po deklarácii `Mic mic;`, pridajte nasledujúci kód:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Funkcia `DMAC_1_Handler` bude zavolaná DMAC, keď budú buffery pripravené na spracovanie. Táto funkcia je nájdená podľa názvu, takže stačí, aby existovala, aby bola zavolaná.

1. Pridajte nasledujúce dve metódy do sekcie `public` triedy `Mic`:

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

    Metóda `init` obsahuje kód na inicializáciu triedy `Mic`. Táto metóda nastaví správne napätie pre pin mikrofónu, nastaví zapisovač flash pamäte, zapíše hlavičku WAV súboru a nakonfiguruje DMAC. Metóda `reset` resetuje flash pamäť a znovu zapíše hlavičku po tom, čo sa zvuk zachytí a použije.

### Úloha - zachytávanie zvuku

1. V súbore `main.cpp` pridajte príkaz `include` pre hlavičkový súbor `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Vo funkcii `setup` inicializujte tlačidlo C. Zachytávanie zvuku sa začne, keď stlačíte toto tlačidlo, a bude pokračovať 4 sekundy:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Nižšie inicializujte mikrofón a potom vypíšte do konzoly, že zvuk je pripravený na zachytávanie:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Nad funkciou `loop` definujte funkciu na spracovanie zachyteného zvuku. Zatiaľ táto funkcia nič nerobí, ale neskôr v tejto lekcii pošle reč na konverziu na text:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Pridajte nasledujúci kód do funkcie `loop`:

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

    Tento kód kontroluje tlačidlo C, a ak je stlačené a nahrávanie sa ešte nezačalo, nastaví pole `_isRecording` triedy `Mic` na hodnotu true. To spôsobí, že metóda `audioCallback` triedy `Mic` bude ukladať zvuk, kým sa nezachytí 4 sekundy. Keď sa zachytí 4 sekundy zvuku, pole `_isRecording` sa nastaví na hodnotu false a pole `_isRecordingReady` sa nastaví na hodnotu true. Toto sa potom skontroluje vo funkcii `loop`, a keď je hodnota true, zavolá sa funkcia `processAudio` a potom sa trieda `Mic` resetuje.

1. Zostavte tento kód, nahrajte ho do vášho Wio Terminal a otestujte ho cez sériový monitor. Stlačte tlačidlo C (to na ľavej strane, najbližšie k vypínaču) a hovorte. Zachytí sa 4 sekundy zvuku.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Tento kód nájdete v priečinku [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Váš program na nahrávanie zvuku bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre dôležité informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.