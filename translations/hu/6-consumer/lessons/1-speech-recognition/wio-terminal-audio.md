<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T21:26:16+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "hu"
}
-->
# Hangrögzítés - Wio Terminal

Ebben a leckében kódot fogsz írni, hogy hangot rögzíts a Wio Terminal eszközön. A hangrögzítést a Wio Terminal tetején található egyik gomb fogja vezérelni.

## Programozd az eszközt hangrögzítésre

A mikrofonról hangot C++ kóddal lehet rögzíteni. A Wio Terminal csak 192KB RAM-mal rendelkezik, ami nem elég több mint néhány másodpercnyi hang rögzítésére. Viszont van 4MB flash memóriája, amelyet használhatsz a rögzített hang tárolására.

A beépített mikrofon analóg jelet rögzít, amelyet digitális jellé alakít át, amit a Wio Terminal használni tud. Hangrögzítéskor az adatokat megfelelő időben kell rögzíteni - például 16KHz-es hang rögzítéséhez pontosan 16,000-szer másodpercenként kell mintát venni, egyenlő időközönként. Ahelyett, hogy a kódod végezné ezt, használhatod a közvetlen memória-hozzáférés vezérlőt (DMAC). Ez egy olyan áramkör, amely jelet tud rögzíteni és memóriába írni anélkül, hogy megszakítaná a processzoron futó kódot.

✅ Olvass többet a DMA-ról a [közvetlen memória-hozzáférés Wikipedia oldalán](https://wikipedia.org/wiki/Direct_memory_access).

![A mikrofonból érkező hang az ADC-n keresztül a DMAC-hoz jut. Ez egy pufferbe ír. Amikor ez a puffer megtelik, feldolgozásra kerül, és a DMAC egy második pufferbe ír](../../../../../translated_images/hu/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

A DMAC képes hangot rögzíteni az ADC-től fix időközönként, például 16,000-szer másodpercenként 16KHz-es hang esetén. A rögzített adatokat egy előre lefoglalt memória pufferbe írja, és amikor ez megtelik, elérhetővé teszi a kódod számára feldolgozásra. A memória használata késleltetheti a hangrögzítést, de több puffert is beállíthatsz. A DMAC az 1-es pufferbe ír, majd amikor ez megtelik, értesíti a kódodat, hogy dolgozza fel az 1-es puffert, miközben a DMAC a 2-es pufferbe ír. Amikor a 2-es puffer megtelik, értesíti a kódodat, és visszatér az 1-es pufferbe íráshoz. Így, amíg minden puffert gyorsabban dolgozol fel, mint amennyi idő alatt megtelik, nem veszítesz adatot.

Miután minden puffer rögzítésre került, az flash memóriába írható. A flash memóriát meghatározott címekkel kell írni, megadva, hogy hova és mekkora méretben írjon, hasonlóan egy bájt tömb frissítéséhez a memóriában. A flash memóriának van granularitása, ami azt jelenti, hogy a törlési és írási műveletek nemcsak fix méretűek, hanem igazodniuk kell ehhez a mérethez. Például, ha a granularitás 4096 bájt, és törlést kérsz a 4200-as címen, akkor törölheti az összes adatot a 4096-tól 8192-ig terjedő címek között. Ez azt jelenti, hogy amikor a hangadatokat flash memóriába írod, megfelelő méretű darabokban kell írni.

### Feladat - flash memória konfigurálása

1. Hozz létre egy új Wio Terminal projektet a PlatformIO használatával. Nevezd el ezt a projektet `smart-timer`-nek. Adj hozzá kódot a `setup` függvényben a soros port konfigurálásához.

1. Add hozzá a következő könyvtárfüggőségeket a `platformio.ini` fájlhoz, hogy hozzáférj a flash memóriához:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Nyisd meg a `main.cpp` fájlt, és add hozzá a következő include direktívát a flash memória könyvtárhoz a fájl tetején:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 Az SFUD a Serial Flash Universal Driver rövidítése, amely egy könyvtár, amely minden flash memória chiphez használható.

1. A `setup` függvényben add hozzá a következő kódot a flash tároló könyvtár beállításához:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Ez addig ismétlődik, amíg az SFUD könyvtár inicializálódik, majd bekapcsolja a gyors olvasást. A beépített flash memória Queued Serial Peripheral Interface (QSPI) segítségével érhető el, amely egy olyan SPI vezérlő, amely minimális processzorhasználattal folyamatos hozzáférést biztosít egy soron keresztül. Ez gyorsabbá teszi a flash memóriába való olvasást és írást.

1. Hozz létre egy új fájlt a `src` mappában `flash_writer.h` néven.

1. Add hozzá a következőket a fájl tetejéhez:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Ez néhány szükséges fejlécfájlt tartalmaz, beleértve az SFUD könyvtár fejlécfájlját a flash memóriával való interakcióhoz.

1. Definiálj egy osztályt ebben az új fejlécfájlban `FlashWriter` néven:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. A `private` szekcióban add hozzá a következő kódot:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Ez néhány mezőt definiál a pufferhez, amelyet az adatok flash memóriába írása előtt használnak. Van egy bájt tömb, `_sfudBuffer`, amelybe adatokat írnak, és amikor ez megtelik, az adatokat flash memóriába írják. Az `_sfudBufferPos` mező tárolja az aktuális helyet, ahová írni kell ebben a pufferben, az `_sfudBufferWritePos` pedig azt a helyet tárolja, ahová flash memóriába kell írni. `_flash` egy mutató a flash memóriára, amelybe írni kell - néhány mikrokontroller több flash memória chipet is tartalmaz.

1. Add hozzá a következő metódust a `public` szekcióhoz az osztály inicializálásához:

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

    Ez konfigurálja a Wio Terminal flash memóriáját írásra, és beállítja a puffereket a flash memória granularitása alapján. Ez egy `init` metódusban van, nem pedig egy konstruktorban, mivel ezt a flash memória beállítása után kell meghívni a `setup` függvényben.

1. Add hozzá a következő kódot a `public` szekcióhoz:

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

    Ez a kód metódusokat definiál a bájtok flash tárolórendszerbe való írására. Ez úgy működik, hogy egy memóriapufferbe ír, amely megfelelő méretű a flash memóriához, és amikor ez megtelik, ezt írja a flash memóriába, törölve az adott helyen lévő meglévő adatokat. Van egy `flushSfudBuffer` is, amely egy nem teljes puffert ír, mivel a rögzített adatok nem lesznek pontosan a granularitás többszörösei, így az adatok végső része is írásra kerül.

    > 💁 Az adatok végső része további nem kívánt adatokat fog írni, de ez nem probléma, mivel csak a szükséges adatokat fogják olvasni.

### Feladat - hangrögzítés beállítása

1. Hozz létre egy új fájlt a `src` mappában `config.h` néven.

1. Add hozzá a következőket a fájl tetejéhez:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Ez a kód néhány konstansot állít be a hangrögzítéshez.

    | Konstans              | Érték  | Leírás |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | A hang mintavételi sebessége. 16,000 az 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | A rögzítendő hang hossza. Ez 4 másodpercre van állítva. Ha hosszabb hangot szeretnél rögzíteni, növeld ezt az értéket. |
    | SAMPLES               | 64000  | Az összes rögzítendő hangminta száma. A mintavételi sebesség * másodpercek száma |
    | BUFFER_SIZE           | 128044 | A hangpuffer mérete a rögzítéshez. A hang WAV fájlként lesz rögzítve, amely 44 bájt fejlécet, majd 128,000 bájt hangadatot tartalmaz (minden minta 2 bájt) |
    | ADC_BUF_LEN           | 1600   | A pufferek mérete, amelyeket a DMAC használ a hang rögzítéséhez |

    > 💁 Ha úgy találod, hogy 4 másodperc túl rövid egy időzítő kéréséhez, növelheted a `SAMPLE_LENGTH_SECONDS` értéket, és az összes többi érték újraszámolódik.

1. Hozz létre egy új fájlt a `src` mappában `mic.h` néven.

1. Add hozzá a következőket a fájl tetejéhez:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Ez néhány szükséges fejlécfájlt tartalmaz, beleértve a `config.h` és `FlashWriter` fejlécfájlokat.

1. Add hozzá a következőket, hogy definiálj egy `Mic` osztályt, amely képes a mikrofonról rögzíteni:

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

    Ez az osztály jelenleg csak néhány mezőt tartalmaz, amelyek nyomon követik, hogy elkezdődött-e a rögzítés, és hogy a rögzítés készen áll-e a használatra. Amikor a DMAC be van állítva, folyamatosan ír memóriapufferekbe, így az `_isRecording` jelző határozza meg, hogy ezeket feldolgozni kell-e vagy sem. Az `_isRecordingReady` jelző akkor lesz beállítva, amikor a szükséges 4 másodpercnyi hang rögzítésre került. A `_writer` mező a hangadatok flash memóriába való mentésére szolgál.

    Ezután egy globális változó kerül deklarálásra a `Mic` osztály egy példányához.

1. Add hozzá a következő kódot a `Mic` osztály `private` szekciójához:

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

    Ez a kód definiál egy `configureDmaAdc` metódust, amely konfigurálja a DMAC-t, csatlakoztatva az ADC-hez, és beállítva, hogy két különböző váltakozó puffert töltsön ki, `_adc_buf_0` és `_adc_buf_1`.

    > 💁 Az egyik hátránya a mikrokontroller fejlesztésnek a hardverrel való interakcióhoz szükséges kód összetettsége, mivel a kódod nagyon alacsony szinten fut, közvetlenül a hardverrel interakcióban. Ez a kód bonyolultabb, mint amit egy egykártyás számítógéphez vagy asztali számítógéphez írnál, mivel nincs operációs rendszer, amely segítene. Vannak elérhető könyvtárak, amelyek egyszerűsíthetik ezt, de még mindig sok a bonyolultság.

1. Ez alatt add hozzá a következő kódot:

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

    Ez a kód definiálja a WAV fejlécet egy 44 bájtos memóriát foglaló struktúraként. Részleteket ír bele a hangfájl sebességéről, méretéről és csatornáinak számáról. Ez a fejléc ezután flash memóriába kerül.

1. Ez alatt a kód alatt add hozzá a következőket, hogy deklarálj egy metódust, amelyet akkor hívnak meg, amikor a hangpufferek készen állnak a feldolgozásra:

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

    A hangpufferek 16 bites egész számok tömbjei, amelyek az ADC-től származó hangot tartalmazzák. Az ADC 12 bites előjel nélküli értékeket (0-1023) ad vissza, így ezeket 16 bites előjeles értékekké kell konvertálni, majd 2 bájttá alakítani, hogy nyers bináris adatként tárolhatók legyenek.

    Ezeket a bájtokat a flash memória puffereibe írják. Az írás a 44-es indexnél kezdődik - ez az eltolás a WAV fájl fejlécének 44 bájtjától. Miután az összes szükséges bájt rögzítésre került a kívánt hanghosszhoz, a fennmaradó adatokat flash memóriába írják.

1. A `Mic` osztály `public` szekciójában add hozzá a következő kódot:

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

    Ez a kódot a DMAC hívja meg, hogy értesítse a kódodat a pufferek feldolgozásáról. Ellenőrzi, hogy van-e adat feldolgozásra, és meghívja az `audioCallback` metódust a megfelelő pufferrel.

1. Az osztályon kívül, a `Mic mic;` deklaráció után add hozzá a következő kódot:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    A `DMAC_1_Handler`-t a DMAC hívja meg, amikor a pufferek készen állnak a feldolgozásra. Ez a függvény név alapján található meg, így csak léteznie kell, hogy meghívható legyen.

1. Add hozzá a következő két metódust a `Mic` osztály `public` szekciójához:

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

    Az `init` metódus tartalmazza a `Mic` osztály inicializálásához szükséges kódot. Ez a metódus beállítja a Mic pin megfelelő feszültségét, beállítja a flash memória írót, megírja a WAV fájl fejlécét, és konfigurálja a DMAC-t. A `reset` metódus visszaállítja a flash memóriát, és újraírja a fejlécet, miután a hang rögzítésre került és felhasználásra került.

### Feladat - hang rögzítése

1. A `main.cpp` fájlban adj hozzá egy include direktívát a `mic.h` fejlécfájlhoz:

    ```cpp
    #include "mic.h"
    ```

1. A `setup` függvényben inicializáld a C gombot. A hangrögzítés akkor kezdődik, amikor ezt a gombot megnyomják, és 4 másodpercig folytatódik:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Ez alatt inicializáld a mikrofont, majd írd ki a konzolra, hogy a hang rögzítésre kész:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. A `loop` függvény fölött definiálj egy függvényt a rögzített hang feldolgozására. Egyelőre ez nem csinál semmit, de később a leckében a beszéd szöveggé alakítására fogja küldeni:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Add hozzá a következőket a `loop` függvényhez:

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

    Ez a kód ellenőrzi a C gombot, és ha ezt megnyomják, és a rögzítés még nem kezdődött el, akkor a `Mic` osztály `_isRecording` mezője `true` értékre van állítva. Ez azt eredményezi, hogy a `Mic` osztály `audioCallback` metódusa hangot tárol, amíg 4 másodpercnyi hang rögzítésre nem kerül. Miután 4 másodpercnyi hang rögzítésre került, az `_isRecording` mező `false` értékre van állítva, és az `_isRecordingReady` mező `true` értékre van állítva. Ezután ezt ellenőrzi a `loop` függvény, és amikor igaz, meghívja a `processAudio` függvényt, majd visszaállítja a mic osztályt.

1. Építsd meg ezt a kódot, töltsd fel a Wio Terminal eszközre, és teszteld a soros monitoron keresztül. Nyomd meg a C gombot (a bal oldalon található, legközelebb a bekapcsoló kapcsolóhoz), és beszélj. 4 másodpercnyi hang rögzítésre kerül.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Ezt a kódot megtalálhatod a [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) mappában.
😀 Az audiofelvételi programod sikeres volt!

---

**Felelősség kizárása**:  
Ez a dokumentum az AI fordítási szolgáltatás, a [Co-op Translator](https://github.com/Azure/co-op-translator) segítségével lett lefordítva. Bár törekszünk a pontosságra, kérjük, vegye figyelembe, hogy az automatikus fordítások hibákat vagy pontatlanságokat tartalmazhatnak. Az eredeti dokumentum az eredeti nyelvén tekintendő hiteles forrásnak. Kritikus információk esetén javasolt professzionális emberi fordítást igénybe venni. Nem vállalunk felelősséget semmilyen félreértésért vagy téves értelmezésért, amely a fordítás használatából eredhet.