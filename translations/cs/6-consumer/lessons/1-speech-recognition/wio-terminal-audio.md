<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T21:27:04+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "cs"
}
-->
# Zachycení zvuku - Wio Terminal

V této části lekce napíšete kód pro zachycení zvuku na vašem Wio Terminalu. Zachycení zvuku bude ovládáno jedním z tlačítek na horní straně Wio Terminalu.

## Naprogramujte zařízení pro zachycení zvuku

Zvuk můžete zachytit z mikrofonu pomocí kódu v jazyce C++. Wio Terminal má pouze 192 KB RAM, což nestačí na zachycení více než několika sekund zvuku. Má však 4 MB flash paměti, kterou lze místo toho použít k ukládání zachyceného zvuku.

Vestavěný mikrofon zachycuje analogový signál, který je převeden na digitální signál, se kterým může Wio Terminal pracovat. Při zachycování zvuku je nutné data zachytit ve správném čase – například pro zachycení zvuku při 16 kHz je třeba zvuk zachytit přesně 16 000krát za sekundu, s rovnoměrnými intervaly mezi jednotlivými vzorky. Místo toho, abyste k tomu použili svůj kód, můžete využít řadič přímého přístupu do paměti (DMAC). Jedná se o obvod, který dokáže zachytit signál z určitého místa a zapsat jej do paměti, aniž by přerušil běh vašeho kódu na procesoru.

✅ Přečtěte si více o DMA na [stránce o přímém přístupu do paměti na Wikipedii](https://wikipedia.org/wiki/Direct_memory_access).

![Zvuk z mikrofonu jde do ADC a poté do DMAC. Ten zapisuje do jednoho bufferu. Když je tento buffer plný, je zpracován a DMAC zapisuje do druhého bufferu](../../../../../translated_images/cs/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC může zachytit zvuk z ADC v pevných intervalech, například 16 000krát za sekundu pro zvuk o frekvenci 16 kHz. Tato zachycená data může zapsat do předem alokovaného paměťového bufferu, a když je tento buffer plný, zpřístupní je vašemu kódu ke zpracování. Použití této paměti může zpozdit zachycení zvuku, ale můžete nastavit více bufferů. DMAC zapisuje do bufferu 1, a když je plný, upozorní váš kód, aby zpracoval buffer 1, zatímco DMAC zapisuje do bufferu 2. Když je buffer 2 plný, upozorní váš kód a vrátí se k zápisu do bufferu 1. Tímto způsobem, pokud zpracujete každý buffer za kratší dobu, než je potřeba k naplnění jednoho, neztratíte žádná data.

Jakmile je každý buffer zachycen, může být zapsán do flash paměti. Flash paměť musí být zapisována pomocí definovaných adres, které určují, kam a jak velký blok dat zapsat, podobně jako při aktualizaci pole bajtů v paměti. Flash paměť má granularitu, což znamená, že operace mazání a zápisu závisí nejen na pevné velikosti, ale také na zarovnání na tuto velikost. Například pokud je granularita 4096 bajtů a požádáte o smazání na adrese 4200, může to smazat všechna data od adresy 4096 do 8192. To znamená, že při zápisu zvukových dat do flash paměti musí být data v blocích správné velikosti.

### Úkol - konfigurace flash paměti

1. Vytvořte nový projekt pro Wio Terminal pomocí PlatformIO. Tento projekt nazvěte `smart-timer`. Přidejte kód do funkce `setup` pro konfiguraci sériového portu.

1. Přidejte následující knihovní závislosti do souboru `platformio.ini`, abyste získali přístup k flash paměti:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Otevřete soubor `main.cpp` a přidejte následující direktivu `include` pro knihovnu flash paměti na začátek souboru:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD znamená Serial Flash Universal Driver, což je knihovna navržená pro práci se všemi čipy flash paměti.

1. Ve funkci `setup` přidejte následující kód pro nastavení knihovny flash paměti:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Tento kód se opakuje, dokud není inicializována knihovna SFUD, a poté zapne rychlé čtení. Vestavěná flash paměť může být přístupná pomocí Queued Serial Peripheral Interface (QSPI), což je typ SPI řadiče, který umožňuje nepřetržitý přístup prostřednictvím fronty s minimálním využitím procesoru. Díky tomu je čtení a zápis do flash paměti rychlejší.

1. Vytvořte nový soubor ve složce `src` s názvem `flash_writer.h`.

1. Přidejte následující na začátek tohoto souboru:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Tento kód zahrnuje potřebné hlavičkové soubory, včetně hlavičkového souboru pro knihovnu SFUD pro interakci s flash pamětí.

1. Definujte třídu v tomto novém hlavičkovém souboru s názvem `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. V sekci `private` přidejte následující kód:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Tento kód definuje některá pole pro buffer, který se používá k ukládání dat před jejich zápisem do flash paměti. Je zde pole bajtů `_sfudBuffer`, do kterého se zapisují data, a když je plné, data se zapíší do flash paměti. Pole `_sfudBufferPos` ukládá aktuální pozici pro zápis v tomto bufferu a `_sfudBufferWritePos` ukládá pozici ve flash paměti, kam se zapisuje. `_flash` je ukazatel na flash paměť, do které se zapisuje – některé mikrokontroléry mají více čipů flash paměti.

1. Přidejte následující metodu do sekce `public` pro inicializaci této třídy:

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

    Tento kód konfiguruje flash paměť na Wio Terminalu pro zápis a nastavuje buffery na základě velikosti zrna flash paměti. Je to v metodě `init`, nikoliv v konstruktoru, protože tato metoda musí být volána po nastavení flash paměti ve funkci `setup`.

1. Přidejte následující kód do sekce `public`:

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

    Tento kód definuje metody pro zápis bajtů do systému flash paměti. Pracuje tak, že zapisuje do paměťového bufferu, který má správnou velikost pro flash paměť, a když je tento buffer plný, zapíše se do flash paměti, přičemž se vymažou všechna existující data na daném místě. Je zde také metoda `flushSfudBuffer` pro zápis neúplného bufferu, protože zachycená data nebudou přesnými násobky velikosti zrna, takže je třeba zapsat i koncovou část dat.

    > 💁 Konečná část dat zapíše další nežádoucí data, ale to je v pořádku, protože se přečtou pouze potřebná data.

### Úkol - nastavení zachycení zvuku

1. Vytvořte nový soubor ve složce `src` s názvem `config.h`.

1. Přidejte následující na začátek tohoto souboru:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Tento kód nastavuje některé konstanty pro zachycení zvuku.

    | Konstantní hodnota    | Hodnota | Popis |
    | --------------------- | ------: | ----- |
    | RATE                  | 16000   | Vzorkovací frekvence zvuku. 16 000 je 16 kHz |
    | SAMPLE_LENGTH_SECONDS | 4       | Délka zvuku k zachycení. Nastaveno na 4 sekundy. Pro delší záznam zvyšte tuto hodnotu. |
    | SAMPLES               | 64000   | Celkový počet zvukových vzorků, které budou zachyceny. Nastaveno na vzorkovací frekvenci * počet sekund |
    | BUFFER_SIZE           | 128044  | Velikost bufferu pro zachycení zvuku. Zvuk bude zachycen jako WAV soubor, což je 44 bajtů hlavičky a 128 000 bajtů zvukových dat (každý vzorek má 2 bajty) |
    | ADC_BUF_LEN           | 1600    | Velikost bufferů pro zachycení zvuku z DMAC |

    > 💁 Pokud zjistíte, že 4 sekundy jsou příliš krátké pro požadavek na časovač, můžete zvýšit hodnotu `SAMPLE_LENGTH_SECONDS` a všechny ostatní hodnoty se přepočítají.

1. Vytvořte nový soubor ve složce `src` s názvem `mic.h`.

1. Přidejte následující na začátek tohoto souboru:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Tento kód zahrnuje potřebné hlavičkové soubory, včetně hlavičkových souborů `config.h` a `FlashWriter`.

1. Přidejte následující kód pro definici třídy `Mic`, která dokáže zachytit zvuk z mikrofonu:

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

    Tato třída aktuálně obsahuje pouze několik polí pro sledování, zda bylo nahrávání zahájeno, a zda je nahrávka připravena k použití. Když je DMAC nastaven, nepřetržitě zapisuje do paměťových bufferů, takže příznak `_isRecording` určuje, zda by měly být tyto buffery zpracovány nebo ignorovány. Příznak `_isRecordingReady` bude nastaven, když bude zachyceno požadovaných 4 sekundy zvuku. Pole `_writer` se používá k ukládání zvukových dat do flash paměti.

    Poté je deklarována globální proměnná pro instanci třídy `Mic`.

1. Přidejte následující kód do sekce `private` třídy `Mic`:

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

    Tento kód definuje metodu `configureDmaAdc`, která konfiguruje DMAC, připojuje jej k ADC a nastavuje jej tak, aby střídavě zapisoval do dvou různých bufferů, `_adc_buf_0` a `_adc_buf_1`.

    > 💁 Jednou z nevýhod vývoje pro mikrokontroléry je složitost kódu potřebného pro interakci s hardwarem, protože váš kód běží na velmi nízké úrovni a přímo komunikuje s hardwarem. Tento kód je složitější než to, co byste napsali pro jednodeskový počítač nebo stolní počítač, protože zde není operační systém, který by pomohl. Existují některé knihovny, které to mohou zjednodušit, ale stále je zde mnoho složitostí.

1. Níže přidejte následující kód:

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

    Tento kód definuje hlavičku WAV jako strukturu, která zabírá 44 bajtů paměti. Do této hlavičky zapisuje informace o vzorkovací frekvenci, velikosti a počtu kanálů zvukového souboru. Tato hlavička je poté zapsána do flash paměti.

1. Níže přidejte následující kód pro deklaraci metody, která bude volána, když budou zvukové buffery připraveny ke zpracování:

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

    Zvukové buffery jsou pole 16bitových celých čísel obsahujících zvuk z ADC. ADC vrací 12bitové neznaménkové hodnoty (0–1023), takže je třeba je převést na 16bitové znaménkové hodnoty a poté převést na 2 bajty, aby byly uloženy jako surová binární data.

    Tyto bajty jsou zapsány do bufferů flash paměti. Zápis začíná na indexu 44 – to je offset od 44 bajtů zapsaných jako hlavička WAV souboru. Jakmile jsou zachyceny všechny bajty potřebné pro požadovanou délku zvuku, zbývající data jsou zapsána do flash paměti.

1. V sekci `public` třídy `Mic` přidejte následující kód:

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

    Tento kód bude volán DMAC, aby informoval váš kód o zpracování bufferů. Kontroluje, zda jsou data ke zpracování, a volá metodu `audioCallback` s příslušným bufferem.

1. Mimo třídu, po deklaraci `Mic mic;`, přidejte následující kód:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Funkce `DMAC_1_Handler` bude volána DMAC, když budou buffery připraveny ke zpracování. Tato funkce je nalezena podle názvu, takže stačí, aby existovala, aby byla volána.

1. Přidejte následující dvě metody do sekce `public` třídy `Mic`:

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

    Metoda `init` obsahuje kód pro inicializaci třídy `Mic`. Tato metoda nastavuje správné napětí pro pin mikrofonu, nastavuje zapisovač flash paměti, zapisuje hlavičku WAV souboru a konfiguruje DMAC. Metoda `reset` resetuje flash paměť a znovu zapíše hlavičku po zachycení a použití zvuku.

### Úkol - zachycení zvuku

1. V souboru `main.cpp` přidejte direktivu `include` pro hlavičkový soubor `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Ve funkci `setup` inicializujte tlačítko C. Zachycení zvuku začne, když bude toto tlačítko stisknuto, a bude pokračovat po dobu 4 sekund:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Níže inicializujte mikrofon a poté vytiskněte do konzole, že zvuk je připraven k zachycení:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Nad funkcí `loop` definujte funkci pro zpracování zachyceného zvuku. Prozatím tato funkce nic nedělá, ale později v této lekci bude odesílat řeč k převodu na text:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Přidejte následující kód do funkce `loop`:

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

    Tento kód kontroluje tlačítko C, a pokud je stisknuto a nahrávání nebylo zahájeno, nastaví pole `_isRecording` třídy `Mic` na hodnotu true. To způsobí, že metoda `audioCallback` třídy `Mic` bude ukládat zvuk, dokud nebude zachyceno 4 sekundy. Jakmile je zachyceno 4 sekundy zvuku, pole `_isRecording` je nastaveno na hodnotu false a pole `_isRecordingReady` je nastaveno na hodnotu true. To je poté zkontrolováno ve funkci `loop`, a když je hodnota true, je volána funkce `processAudio` a poté je třída `Mic` resetována.

1. Sestavte tento kód, nahrajte jej do svého Wio Terminalu a otestujte jej prostřednictvím sériového monitoru. Stiskněte tlačítko C (to vlevo, nejblíže k vypínači) a mluvte. Bude zachyceno 4 sekundy zvuku.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Tento kód najdete ve složce [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Váš program pro nahrávání zvuku byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Ačkoli se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.