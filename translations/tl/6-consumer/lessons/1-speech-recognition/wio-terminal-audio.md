<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T23:26:06+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "tl"
}
-->
# Mag-record ng Audio - Wio Terminal

Sa bahaging ito ng aralin, magsusulat ka ng code upang mag-record ng audio gamit ang iyong Wio Terminal. Ang pag-record ng audio ay kokontrolin gamit ang isa sa mga button sa itaas ng Wio Terminal.

## I-program ang device upang mag-record ng audio

Maaari kang mag-record ng audio mula sa mikropono gamit ang C++ code. Ang Wio Terminal ay may 192KB lamang ng RAM, na hindi sapat upang mag-record ng higit sa ilang segundo ng audio. Mayroon din itong 4MB ng flash memory, kaya maaaring gamitin ito upang i-save ang na-record na audio.

Ang built-in na mikropono ay nagre-record ng analog signal, na kino-convert sa digital signal na magagamit ng Wio Terminal. Kapag nagre-record ng audio, kailangang makuha ang data sa tamang oras - halimbawa, upang mag-record ng audio sa 16KHz, kailangang mag-record ng audio nang eksaktong 16,000 beses bawat segundo, na may pantay na pagitan sa pagitan ng bawat sample. Sa halip na gamitin ang iyong code upang gawin ito, maaari mong gamitin ang direct memory access controller (DMAC). Ito ay isang circuitry na maaaring kumuha ng signal mula sa isang lugar at magsulat sa memorya, nang hindi naaabala ang code na tumatakbo sa processor.

✅ Basahin pa ang tungkol sa DMA sa [direct memory access page sa Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Ang audio mula sa mikropono ay dumadaan sa ADC papunta sa DMAC. Isinusulat ito sa isang buffer. Kapag puno na ang buffer na ito, ito ay pinoproseso at ang DMAC ay nagsusulat sa pangalawang buffer](../../../../../translated_images/tl/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

Ang DMAC ay maaaring mag-record ng audio mula sa ADC sa mga nakatakdang pagitan, tulad ng 16,000 beses bawat segundo para sa 16KHz na audio. Maaari nitong isulat ang na-record na data sa isang pre-allocated na memory buffer, at kapag puno na ito, gagawin itong available sa iyong code upang iproseso. Ang paggamit ng memoryang ito ay maaaring magdulot ng pagkaantala sa pag-record ng audio, ngunit maaari kang mag-set up ng maraming buffer. Ang DMAC ay nagsusulat sa buffer 1, pagkatapos kapag puno na ito, ipinaalam nito sa iyong code upang iproseso ang buffer 1, habang ang DMAC ay nagsusulat sa buffer 2. Kapag puno na ang buffer 2, ipinaalam nito sa iyong code, at bumabalik sa pagsusulat sa buffer 1. Sa ganitong paraan, hangga't napoproseso mo ang bawat buffer nang mas mabilis kaysa sa oras na kinakailangan upang mapuno ang isa, hindi ka mawawalan ng data.

Kapag na-record na ang bawat buffer, maaari itong isulat sa flash memory. Ang flash memory ay kailangang isulat gamit ang mga tinukoy na address, na nagsasaad kung saan isusulat at kung gaano kalaki ang isusulat, katulad ng pag-update ng isang array ng bytes sa memorya. Ang flash memory ay may granularity, ibig sabihin ang mga operasyon ng pag-erase at pagsusulat ay nakadepende hindi lamang sa pagiging fixed size, kundi pati na rin sa pag-align sa sukat na iyon. Halimbawa, kung ang granularity ay 4096 bytes at humiling ka ng pag-erase sa address 4200, maaaring ma-erase ang lahat ng data mula sa address 4096 hanggang 8192. Nangangahulugan ito na kapag isinulat mo ang audio data sa flash memory, kailangang ito ay nasa tamang laki ng mga chunks.

### Gawain - i-configure ang flash memory

1. Gumawa ng bagong Wio Terminal project gamit ang PlatformIO. Tawagin ang proyektong ito na `smart-timer`. Magdagdag ng code sa `setup` function upang i-configure ang serial port.

1. Idagdag ang sumusunod na mga library dependency sa `platformio.ini` file upang magkaroon ng access sa flash memory:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Buksan ang `main.cpp` file at idagdag ang sumusunod na include directive para sa flash memory library sa itaas ng file:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 Ang SFUD ay nangangahulugang Serial Flash Universal Driver, at ito ay isang library na idinisenyo upang gumana sa lahat ng flash memory chips.

1. Sa `setup` function, idagdag ang sumusunod na code upang i-set up ang flash storage library:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Ang code na ito ay mag-loop hanggang sa ma-initialize ang SFUD library, pagkatapos ay i-on ang fast reads. Ang built-in na flash memory ay maaaring ma-access gamit ang Queued Serial Peripheral Interface (QSPI), isang uri ng SPI controller na nagbibigay-daan sa tuloy-tuloy na pag-access sa pamamagitan ng queue na may minimal na paggamit ng processor. Ginagawa nitong mas mabilis ang pagbabasa at pagsusulat sa flash memory.

1. Gumawa ng bagong file sa `src` folder na tinatawag na `flash_writer.h`.

1. Idagdag ang sumusunod sa itaas ng file na ito:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Kasama rito ang ilang kinakailangang header files, kabilang ang header file para sa SFUD library upang makipag-ugnayan sa flash memory.

1. Mag-define ng isang class sa bagong header file na ito na tinatawag na `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Sa `private` section, idagdag ang sumusunod na code:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Ang code na ito ay nagde-define ng ilang fields para sa buffer na gagamitin upang mag-imbak ng data bago ito isulat sa flash memory. Mayroong byte array na `_sfudBuffer` upang isulat ang data, at kapag puno na ito, ang data ay isinusulat sa flash memory. Ang field na `_sfudBufferPos` ay nag-iimbak ng kasalukuyang lokasyon kung saan isusulat sa buffer na ito, at ang `_sfudBufferWritePos` ay nag-iimbak ng lokasyon sa flash memory kung saan isusulat. Ang `_flash` ay isang pointer sa flash memory kung saan isusulat - ang ilang microcontrollers ay may maraming flash memory chips.

1. Idagdag ang sumusunod na method sa `public` section upang i-initialize ang class na ito:

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

    Ang method na ito ay nagko-configure sa flash memory sa Wio Terminal upang isulat dito, at i-set up ang buffers base sa grain size ng flash memory. Ito ay nasa isang `init` method, sa halip na constructor dahil kailangang tawagin ito pagkatapos ma-set up ang flash memory sa `setup` function.

1. Idagdag ang sumusunod na code sa `public` section:

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

    Ang code na ito ay nagde-define ng mga method upang magsulat ng bytes sa flash storage system. Gumagana ito sa pamamagitan ng pagsusulat sa isang in-memory buffer na tamang laki para sa flash memory, at kapag puno na ito, ito ay isinusulat sa flash memory, binubura ang anumang umiiral na data sa lokasyong iyon. Mayroon ding `flushSfudBuffer` upang isulat ang hindi kumpletong buffer, dahil ang data na na-record ay hindi eksaktong multiples ng grain size, kaya kailangang isulat ang huling bahagi ng data.

    > 💁 Ang huling bahagi ng data ay magsusulat ng karagdagang hindi kinakailangang data, ngunit ayos lang ito dahil tanging ang kinakailangang data lamang ang babasahin.

### Gawain - i-set up ang pag-record ng audio

1. Gumawa ng bagong file sa `src` folder na tinatawag na `config.h`.

1. Idagdag ang sumusunod sa itaas ng file na ito:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Ang code na ito ay nagse-set up ng ilang constants para sa pag-record ng audio.

    | Constant              | Value  | Deskripsyon |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | Ang sample rate para sa audio. 16,000 ay 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | Ang haba ng audio na ire-record. Ito ay naka-set sa 4 na segundo. Upang mag-record ng mas mahabang audio, taasan ang value na ito. |
    | SAMPLES               | 64000  | Ang kabuuang bilang ng audio samples na ire-record. Naka-set sa sample rate * ang bilang ng segundo |
    | BUFFER_SIZE           | 128044 | Ang laki ng audio buffer upang mag-record. Ang audio ay ire-record bilang isang WAV file, na may 44 bytes ng header, pagkatapos ay 128,000 bytes ng audio data (ang bawat sample ay 2 bytes) |
    | ADC_BUF_LEN           | 1600   | Ang laki ng buffers na gagamitin upang mag-record ng audio mula sa DMAC |

    > 💁 Kung sa tingin mo ay masyadong maikli ang 4 na segundo upang mag-request ng timer, maaari mong taasan ang `SAMPLE_LENGTH_SECONDS` value, at ang lahat ng iba pang values ay muling kakalkulahin.

1. Gumawa ng bagong file sa `src` folder na tinatawag na `mic.h`.

1. Idagdag ang sumusunod sa itaas ng file na ito:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Kasama rito ang ilang kinakailangang header files, kabilang ang `config.h` at `FlashWriter` header files.

1. Idagdag ang sumusunod upang mag-define ng isang `Mic` class na maaaring mag-record mula sa mikropono:

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

    Ang class na ito ay kasalukuyang may ilang fields lamang upang subaybayan kung nagsimula na ang pag-record, at kung ang isang recording ay handa nang gamitin. Kapag na-set up ang DMAC, ito ay tuloy-tuloy na nagsusulat sa memory buffers, kaya ang `_isRecording` flag ay tumutukoy kung ang mga ito ay dapat iproseso o balewalain. Ang `_isRecordingReady` flag ay ise-set kapag ang kinakailangang 4 na segundo ng audio ay na-record na. Ang `_writer` field ay ginagamit upang i-save ang audio data sa flash memory.

    Isang global variable ang ide-declare para sa isang instance ng `Mic` class.

1. Idagdag ang sumusunod na code sa `private` section ng `Mic` class:

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

    Ang code na ito ay nagde-define ng isang `configureDmaAdc` method na nagko-configure sa DMAC, ikinokonekta ito sa ADC at sine-set ito upang mag-populate ng dalawang magkaibang alternating buffers, `_adc_buf_0` at `_adc_buf_1`.

    > 💁 Isa sa mga downside ng microcontroller development ay ang pagiging kumplikado ng code na kinakailangan upang makipag-ugnayan sa hardware, dahil ang iyong code ay tumatakbo sa napakababang antas na direktang nakikipag-ugnayan sa hardware. Ang code na ito ay mas kumplikado kaysa sa isusulat mo para sa isang single-board computer o desktop computer dahil walang operating system na tutulong. May ilang libraries na magpapadali nito, ngunit mayroon pa ring maraming kumplikasyon.

1. Sa ibaba nito, idagdag ang sumusunod na code:

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

    Ang code na ito ay nagde-define ng WAV header bilang isang struct na kumukuha ng 44 bytes ng memorya. Isinusulat nito ang mga detalye tungkol sa rate ng audio file, laki, at bilang ng mga channel. Ang header na ito ay pagkatapos ay isinusulat sa flash memory.

1. Sa ibaba ng code na ito, idagdag ang sumusunod upang magdeklara ng isang method na tatawagin kapag ang mga audio buffers ay handa nang iproseso:

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

    Ang mga audio buffers ay arrays ng 16-bit integers na naglalaman ng audio mula sa ADC. Ang ADC ay nagbabalik ng 12-bit unsigned values (0-1023), kaya kailangang i-convert ang mga ito sa 16-bit signed values, at pagkatapos ay i-convert sa 2 bytes upang ma-store bilang raw binary data.

    Ang mga bytes na ito ay isinusulat sa flash memory buffers. Ang pagsusulat ay nagsisimula sa index 44 - ito ang offset mula sa 44 bytes na isinulat bilang WAV file header. Kapag ang lahat ng bytes na kinakailangan para sa kinakailangang haba ng audio ay na-record na, ang natitirang data ay isinusulat sa flash memory.

1. Sa `public` section ng `Mic` class, idagdag ang sumusunod na code:

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

    Ang code na ito ay tatawagin ng DMAC upang ipaalam sa iyong code na iproseso ang buffers. Sinusuri nito kung may data na ipoproseso, at tinatawag ang `audioCallback` method gamit ang kaukulang buffer.

1. Sa labas ng class, pagkatapos ng `Mic mic;` declaration, idagdag ang sumusunod na code:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Ang `DMAC_1_Handler` ay tatawagin ng DMAC kapag ang buffers ay handa nang iproseso. Ang function na ito ay matatagpuan sa pamamagitan ng pangalan, kaya kailangan lamang itong umiral upang matawag.

1. Idagdag ang sumusunod na dalawang methods sa `public` section ng `Mic` class:

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

    Ang `init` method ay naglalaman ng code upang i-initialize ang `Mic` class. Ang method na ito ay sine-set ang tamang boltahe para sa Mic pin, sine-set up ang flash memory writer, isinusulat ang WAV file header, at kino-configure ang DMAC. Ang `reset` method ay nire-reset ang flash memory at muling isinusulat ang header pagkatapos magamit ang na-record na audio.

### Gawain - mag-record ng audio

1. Sa `main.cpp` file, magdagdag ng include directive para sa `mic.h` header file:

    ```cpp
    #include "mic.h"
    ```

1. Sa `setup` function, i-initialize ang C button. Ang pag-record ng audio ay magsisimula kapag pinindot ang button na ito, at magpapatuloy sa loob ng 4 na segundo:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Sa ibaba nito, i-initialize ang mikropono, pagkatapos ay mag-print sa console na handa nang mag-record ng audio:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Sa itaas ng `loop` function, magdeklara ng isang function upang iproseso ang na-record na audio. Sa ngayon, wala pa itong gagawin, ngunit sa susunod na bahagi ng aralin, ito ay magpapadala ng speech upang ma-convert sa text:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Idagdag ang sumusunod sa `loop` function:

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

    Ang code na ito ay sinusuri ang C button, at kung ito ay pinindot at hindi pa nagsisimula ang pag-record, ang `_isRecording` field ng `Mic` class ay sine-set sa true. Ito ay magdudulot sa `audioCallback` method ng `Mic` class na mag-store ng audio hanggang sa 4 na segundo ang ma-record. Kapag 4 na segundo ng audio ang na-record, ang `_isRecording` field ay sine-set sa false, at ang `_isRecordingReady` field ay sine-set sa true. Ito ay pagkatapos sinusuri sa `loop` function, at kapag true, ang `processAudio` function ay tatawagin, pagkatapos ang mic class ay ire-reset.

1. I-build ang code na ito, i-upload ito sa iyong Wio Terminal at subukan ito sa pamamagitan ng serial monitor. Pindutin ang C button (ang nasa kaliwang bahagi, pinakamalapit sa power switch), at magsalita. 4 na segundo ng audio ang mare-record.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Makikita mo ang code na ito sa [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) na folder.
😀 Ang iyong programa para sa pagre-record ng audio ay matagumpay!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.