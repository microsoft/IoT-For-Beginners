<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T21:25:27+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "sw"
}
-->
# Kurekodi Sauti - Wio Terminal

Katika sehemu hii ya somo, utaandika msimbo wa kurekodi sauti kwenye Wio Terminal yako. Kurekodi sauti kutadhibitiwa na moja ya vitufe vilivyo juu ya Wio Terminal.

## Programu kifaa kurekodi sauti

Unaweza kurekodi sauti kutoka kwa kipaza sauti kwa kutumia msimbo wa C++. Wio Terminal ina RAM ya 192KB pekee, ambayo haitoshi kurekodi zaidi ya sekunde chache za sauti. Pia ina kumbukumbu ya flash ya 4MB, ambayo inaweza kutumika badala yake, kuhifadhi sauti iliyorekodiwa kwenye kumbukumbu ya flash.

Kipaza sauti kilichojengwa ndani hurekodi ishara ya analojia, ambayo hubadilishwa kuwa ishara ya kidijitali ambayo Wio Terminal inaweza kutumia. Wakati wa kurekodi sauti, data inahitaji kurekodiwa kwa wakati sahihi - kwa mfano, ili kurekodi sauti kwa 16KHz, sauti inahitaji kurekodiwa mara 16,000 kwa sekunde, kwa vipindi sawa kati ya kila sampuli. Badala ya kutumia msimbo wako kufanya hivi, unaweza kutumia kidhibiti cha ufikiaji wa kumbukumbu moja kwa moja (DMAC). Hii ni mzunguko wa umeme unaoweza kurekodi ishara kutoka mahali fulani na kuiandika kwenye kumbukumbu, bila kuingilia msimbo wako unaoendesha kwenye processor.

✅ Soma zaidi kuhusu DMA kwenye [ukurasa wa ufikiaji wa kumbukumbu moja kwa moja kwenye Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Sauti kutoka kwa kipaza sauti huenda kwa ADC kisha kwa DMAC. Hii huandika kwenye buffer moja. Buffer hii inapojazwa, inachakatwa na DMAC huandika kwenye buffer ya pili](../../../../../translated_images/sw/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC inaweza kurekodi sauti kutoka kwa ADC kwa vipindi vilivyowekwa, kama vile mara 16,000 kwa sekunde kwa sauti ya 16KHz. Inaweza kuandika data hii iliyorekodiwa kwenye buffer ya kumbukumbu iliyotengwa mapema, na buffer hii inapojazwa, inapatikana kwa msimbo wako kuchakata. Kutumia kumbukumbu hii kunaweza kuchelewesha kurekodi sauti, lakini unaweza kusanidi buffers nyingi. DMAC huandika kwenye buffer 1, kisha inapojazwa, inaarifu msimbo wako kuchakata buffer 1, wakati DMAC huandika kwenye buffer 2. Buffer 2 inapojazwa, inaarifu msimbo wako, na kurudi kuandika kwenye buffer 1. Kwa njia hii, mradi unachakata kila buffer kwa muda mfupi kuliko inavyohitajika kujaza moja, hutapoteza data yoyote.

Kila buffer inaporekodiwa, inaweza kuandikwa kwenye kumbukumbu ya flash. Kumbukumbu ya flash inahitaji kuandikwa kwa kutumia anwani zilizobainishwa, ikieleza wapi kuandika na ukubwa wa kuandika, sawa na kusasisha safu ya byte kwenye kumbukumbu. Kumbukumbu ya flash ina granularity, ikimaanisha operesheni za kufuta na kuandika hutegemea sio tu kuwa na ukubwa maalum, bali pia kuendana na ukubwa huo. Kwa mfano, ikiwa granularity ni byte 4096 na unaomba kufuta kwenye anwani 4200, inaweza kufuta data yote kutoka anwani 4096 hadi 8192. Hii inamaanisha unapoweka data ya sauti kwenye kumbukumbu ya flash, inapaswa kuwa katika vipande vya ukubwa sahihi.

### Kazi - sanidi kumbukumbu ya flash

1. Unda mradi mpya wa Wio Terminal ukitumia PlatformIO. Uite mradi huu `smart-timer`. Ongeza msimbo kwenye kazi ya `setup` ili kusanidi mlango wa serial.

1. Ongeza maktaba zifuatazo za utegemezi kwenye faili ya `platformio.ini` ili kupata kumbukumbu ya flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Fungua faili ya `main.cpp` na ongeza agizo la kujumuisha maktaba ya kumbukumbu ya flash juu ya faili:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD inasimama kwa Serial Flash Universal Driver, na ni maktaba iliyoundwa kufanya kazi na chips zote za kumbukumbu ya flash.

1. Katika kazi ya `setup`, ongeza msimbo ufuatao kusanidi maktaba ya hifadhi ya flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Hii inazunguka hadi maktaba ya SFUD ianzishwe, kisha inawasha usomaji wa haraka. Kumbukumbu ya flash iliyojengwa ndani inaweza kufikiwa kwa kutumia Queued Serial Peripheral Interface (QSPI), aina ya kidhibiti cha SPI kinachoruhusu ufikiaji endelevu kupitia foleni kwa matumizi madogo ya processor. Hii inafanya iwe haraka kusoma na kuandika kwenye kumbukumbu ya flash.

1. Unda faili mpya kwenye folda ya `src` inayoitwa `flash_writer.h`.

1. Ongeza yafuatayo juu ya faili hii:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Hii inajumuisha baadhi ya faili za kichwa zinazohitajika, ikijumuisha faili ya kichwa ya maktaba ya SFUD ili kuingiliana na kumbukumbu ya flash.

1. Fafanua darasa kwenye faili hii mpya inayoitwa `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Katika sehemu ya `private`, ongeza msimbo ufuatao:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Hii inafafanua baadhi ya sehemu za buffer ya kutumia kuhifadhi data kabla ya kuiandika kwenye kumbukumbu ya flash. Kuna safu ya byte, `_sfudBuffer`, ya kuandika data, na buffer hii inapojazwa, data huandikwa kwenye kumbukumbu ya flash. Sehemu ya `_sfudBufferPos` huhifadhi eneo la sasa la kuandika kwenye buffer hii, na `_sfudBufferWritePos` huhifadhi eneo kwenye kumbukumbu ya flash la kuandika. `_flash` ni pointer ya kumbukumbu ya flash ya kuandika - baadhi ya microcontrollers zina chips nyingi za kumbukumbu ya flash.

1. Ongeza njia ifuatayo kwenye sehemu ya `public` ili kuanzisha darasa hili:

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

    Hii inasanidi kumbukumbu ya flash kwenye Wio Terminal ya kuandika, na kusanidi buffers kulingana na ukubwa wa granularity wa kumbukumbu ya flash. Hii iko kwenye njia ya `init`, badala ya constructor kwa kuwa hii inahitaji kuitwa baada ya kumbukumbu ya flash kusanidiwa kwenye kazi ya `setup`.

1. Ongeza msimbo ufuatao kwenye sehemu ya `public`:

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

    Msimbo huu unafafanua njia za kuandika byte kwenye mfumo wa hifadhi ya flash. Inafanya kazi kwa kuandika kwenye buffer ya kumbukumbu ambayo ni ya ukubwa sahihi kwa kumbukumbu ya flash, na buffer hii inapojazwa, hii huandikwa kwenye kumbukumbu ya flash, ikifuta data yoyote iliyopo kwenye eneo hilo. Pia kuna `flushSfudBuffer` ya kuandika buffer isiyokamilika, kwa kuwa data inayorekodiwa haitakuwa sawia na ukubwa wa granularity, hivyo sehemu ya mwisho ya data inahitaji kuandikwa.

    > 💁 Sehemu ya mwisho ya data itaandika data ya ziada isiyohitajika, lakini hili ni sawa kwa kuwa data inayohitajika pekee ndiyo itasomwa.

### Kazi - sanidi kurekodi sauti

1. Unda faili mpya kwenye folda ya `src` inayoitwa `config.h`.

1. Ongeza yafuatayo juu ya faili hii:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Msimbo huu unaseti baadhi ya constants kwa ajili ya kurekodi sauti.

    | Constant              | Thamani  | Maelezo |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Kiwango cha sampuli kwa sauti. 16,000 ni 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Urefu wa sauti ya kurekodi. Hii imewekwa kwa sekunde 4. Ili kurekodi sauti ndefu, ongeza thamani hii. |
    | SAMPLES               | 64000  | Jumla ya idadi ya sampuli za sauti zitakazorekodiwa. Imewekwa kwa kiwango cha sampuli * idadi ya sekunde |
    | BUFFER_SIZE           | 128044 | Ukubwa wa buffer ya sauti ya kurekodi. Sauti itarekodiwa kama faili ya WAV, ambayo ni byte 44 za kichwa, kisha byte 128,000 za data ya sauti (kila sampuli ni byte 2) |
    | ADC_BUF_LEN           | 1600   | Ukubwa wa buffers za kutumia kurekodi sauti kutoka DMAC |

    > 💁 Ikiwa unahisi sekunde 4 ni fupi sana kuomba timer, unaweza kuongeza thamani ya `SAMPLE_LENGTH_SECONDS`, na thamani zingine zote zitahesabiwa upya.

1. Unda faili mpya kwenye folda ya `src` inayoitwa `mic.h`.

1. Ongeza yafuatayo juu ya faili hii:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Hii inajumuisha baadhi ya faili za kichwa zinazohitajika, ikijumuisha faili za `config.h` na `FlashWriter`.

1. Ongeza yafuatayo kufafanua darasa la `Mic` ambalo linaweza kurekodi kutoka kwa kipaza sauti:

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

    Darasa hili kwa sasa lina sehemu chache tu za kufuatilia ikiwa kurekodi kumeanza, na ikiwa kurekodi kumeandaliwa tayari kutumika. DMAC inaposanidiwa, inaendelea kuandika kwenye buffers za kumbukumbu, hivyo bendera ya `_isRecording` huamua ikiwa hizi zinapaswa kuchakatwa au kupuuzwa. Bendera ya `_isRecordingReady` itawekwa wakati sekunde 4 zinazohitajika za sauti zimekamilika kurekodiwa. Sehemu ya `_writer` inatumika kuhifadhi data ya sauti kwenye kumbukumbu ya flash.

    Kisha, kutangazwa kwa variable ya kimataifa kwa mfano wa darasa la `Mic`.

1. Ongeza msimbo ufuatao kwenye sehemu ya `private` ya darasa la `Mic`:

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

    Msimbo huu unafafanua njia ya `configureDmaAdc` ambayo inasanidi DMAC, ikiunganisha na ADC na kuiweka kujaza buffers mbili tofauti zinazobadilishana, `_adc_buf_0` na `_adc_buf_1`.

    > 💁 Moja ya changamoto za maendeleo ya microcontroller ni ugumu wa msimbo unaohitajika kuingiliana na vifaa, kwa kuwa msimbo wako unaendesha kwa kiwango cha chini sana ukishughulika moja kwa moja na vifaa. Msimbo huu ni mgumu zaidi kuliko kile unachoweza kuandika kwa kompyuta ya bodi moja au kompyuta ya mezani kwa kuwa hakuna mfumo wa uendeshaji wa kusaidia. Kuna baadhi ya maktaba zinazopatikana ambazo zinaweza kurahisisha hili, lakini bado kuna ugumu mwingi.

1. Chini ya hii, ongeza msimbo ufuatao:

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

    Msimbo huu unafafanua kichwa cha WAV kama struct inayochukua byte 44 za kumbukumbu. Inaandika maelezo kwenye kiwango cha faili ya sauti, ukubwa, na idadi ya njia. Kichwa hiki kisha kinaandikwa kwenye kumbukumbu ya flash.

1. Chini ya msimbo huu, ongeza yafuatayo kutangaza njia ya kuitwa wakati buffers za sauti ziko tayari kuchakatwa:

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

    Buffers za sauti ni safu za namba za 16-bit zenye sauti kutoka kwa ADC. ADC inarudisha thamani zisizo na ishara za 12-bit (0-1023), hivyo hizi zinahitaji kubadilishwa kuwa thamani za 16-bit zenye ishara, kisha kubadilishwa kuwa byte 2 kuhifadhiwa kama data ghafi ya binary.

    Byte hizi zinaandikwa kwenye buffers za kumbukumbu ya flash. Uandishi huanza kwenye index 44 - hii ni offset kutoka byte 44 zilizoandikwa kama kichwa cha faili ya WAV. Mara byte zote zinazohitajika kwa urefu wa sauti uliowekwa zimekamilika kurekodiwa, data iliyobaki inaandikwa kwenye kumbukumbu ya flash.

1. Katika sehemu ya `public` ya darasa la `Mic`, ongeza msimbo ufuatao:

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

    Msimbo huu utaitwa na DMAC kuarifu msimbo wako kuchakata buffers. Unakagua ikiwa kuna data ya kuchakata, na kuita njia ya `audioCallback` na buffer husika.

1. Nje ya darasa, baada ya tangazo la `Mic mic;`, ongeza msimbo ufuatao:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` itaitwa na DMAC wakati buffers ziko tayari kuchakatwa. Kazi hii inapatikana kwa jina, hivyo inahitaji tu kuwepo ili kuitwa.

1. Ongeza njia mbili zifuatazo kwenye sehemu ya `public` ya darasa la `Mic`:

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

    Njia ya `init` ina msimbo wa kuanzisha darasa la `Mic`. Njia hii inasanidi voltage sahihi kwa pini ya Mic, inasanidi mwandishi wa kumbukumbu ya flash, inaandika kichwa cha faili ya WAV, na inasanidi DMAC. Njia ya `reset` inafuta kumbukumbu ya flash na kuandika upya kichwa baada ya sauti kurekodiwa na kutumika.

### Kazi - kurekodi sauti

1. Katika faili ya `main.cpp`, ongeza agizo la kujumuisha faili ya kichwa ya `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Katika kazi ya `setup`, sanidi kitufe cha C. Kurekodi sauti kutaanza kitufe hiki kitakapobonyezwa, na kuendelea kwa sekunde 4:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Chini ya hii, anzisha kipaza sauti, kisha chapisha kwenye koni kwamba sauti iko tayari kurekodiwa:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Juu ya kazi ya `loop`, fafanua kazi ya kuchakata sauti iliyorekodiwa. Kwa sasa hii haifanyi chochote, lakini baadaye katika somo hili itatuma hotuba kubadilishwa kuwa maandishi:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Ongeza yafuatayo kwenye kazi ya `loop`:

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

    Msimbo huu unakagua kitufe cha C, na ikiwa kitufe hiki kimebonyezwa na kurekodi hakujaanza, basi sehemu ya `_isRecording` ya darasa la `Mic` inakuwa `true`. Hii itasababisha njia ya `audioCallback` ya darasa la `Mic` kuhifadhi sauti hadi sekunde 4 zimekamilika kurekodiwa. Mara sekunde 4 za sauti zimekamilika kurekodiwa, sehemu ya `_isRecording` inakuwa `false`, na sehemu ya `_isRecordingReady` inakuwa `true`. Hii kisha inakaguliwa kwenye kazi ya `loop`, na inapokuwa `true` kazi ya `processAudio` inaitwa, kisha darasa la mic linaanzishwa upya.

1. Jenga msimbo huu, upakie kwenye Wio Terminal yako na ujaribu kupitia monitor ya serial. Bonyeza kitufe cha C (kile kilicho upande wa kushoto, karibu na swichi ya nguvu), na zungumza. Sekunde 4 za sauti zitarekodiwa.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 Unaweza kupata msimbo huu katika folda ya [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Programu yako ya kurekodi sauti imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.