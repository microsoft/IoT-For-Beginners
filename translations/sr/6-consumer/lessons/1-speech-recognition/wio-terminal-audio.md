# Снимање звука - Wio Terminal

У овом делу лекције, написаћете код за снимање звука на вашем Wio Terminal-у. Снимање звука ће бити контролисано једним од дугмади на врху Wio Terminal-а.

## Програмирање уређаја за снимање звука

Можете снимати звук са микрофона користећи C++ код. Wio Terminal има само 192KB RAM-а, што није довољно за снимање више од неколико секунди звука. Такође има 4MB флеш меморије, која се може користити за чување снимљеног звука.

Уграђени микрофон снима аналогни сигнал, који се затим претвара у дигитални сигнал који Wio Terminal може да користи. Приликом снимања звука, подаци морају бити снимљени у тачно одређеним временским интервалима - на пример, за снимање звука на 16KHz, звук мора бити снимљен тачно 16.000 пута у секунди, са једнаким размацима између сваког узорка. Уместо да ваш код то ради, можете користити контролер директног приступа меморији (DMAC). Ово је хардвер који може снимити сигнал са неког извора и уписати га у меморију, без прекидања рада вашег кода на процесору.

✅ Прочитајте више о DMA на [страници о директном приступу меморији на Википедији](https://wikipedia.org/wiki/Direct_memory_access).

![Звук са микрофона иде у ADC, затим у DMAC. Ово се уписује у један бафер. Када се овај бафер напуни, он се обрађује, а DMAC уписује у други бафер](../../../../../translated_images/sr/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC може снимати звук са ADC-а у фиксним интервалима, као што је 16.000 пута у секунди за звук од 16KHz. Може уписивати ове снимљене податке у унапред алоцирани меморијски бафер, а када се он напуни, учинити га доступним вашем коду за обраду. Коришћење ове меморије може одложити снимање звука, али можете подесити више бафера. DMAC уписује у бафер 1, а када се он напуни, обавештава ваш код да обради бафер 1, док DMAC уписује у бафер 2. Када се бафер 2 напуни, обавештава ваш код и враћа се на уписивање у бафер 1. На тај начин, све док обрађујете сваки бафер у времену краћем од оног које је потребно да се један напуни, нећете изгубити ниједан податак.

Када се сваки бафер сними, може се уписати у флеш меморију. Флеш меморија мора бити уписана користећи дефинисане адресе, наводећи где и колико велико уписивање треба да буде, слично ажурирању низа бајтова у меморији. Флеш меморија има грануларност, што значи да операције брисања и уписивања зависе не само од фиксне величине, већ и од поравнања са том величином. На пример, ако је грануларност 4096 бајтова и затражите брисање на адреси 4200, могло би се обрисати све од адресе 4096 до 8192. Ово значи да када уписујете аудио податке у флеш меморију, то мора бити у деловима одговарајуће величине.

### Задатак - конфигурисање флеш меморије

1. Направите нови Wio Terminal пројекат користећи PlatformIO. Назовите овај пројекат `smart-timer`. Додајте код у функцију `setup` за конфигурисање серијског порта.

1. Додајте следеће библиотечке зависности у `platformio.ini` датотеку како бисте омогућили приступ флеш меморији:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Отворите `main.cpp` датотеку и додајте следећу директиву за укључивање библиотеке за флеш меморију на врх датотеке:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD означава Serial Flash Universal Driver, и то је библиотека дизајнирана за рад са свим чиповима флеш меморије.

1. У функцији `setup`, додајте следећи код за подешавање библиотеке за флеш меморију:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Ово се понавља док се SFUD библиотека не иницијализује, а затим укључује брзо читање. Уграђена флеш меморија може се приступити користећи Queued Serial Peripheral Interface (QSPI), врсту SPI контролера који омогућава континуирани приступ преко реда са минималним коришћењем процесора. Ово чини читање и уписивање у флеш меморију бржим.

1. Направите нову датотеку у фолдеру `src` под називом `flash_writer.h`.

1. Додајте следеће на врх ове датотеке:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Ово укључује неке потребне заглавне датотеке, укључујући заглавну датотеку за SFUD библиотеку за интеракцију са флеш меморијом.

1. Дефинишите класу у овој новој заглавној датотеци под називом `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. У `private` секцији, додајте следећи код:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Ово дефинише нека поља за бафер који се користи за чување података пре него што се упишу у флеш меморију. Постоји низ бајтова, `_sfudBuffer`, за уписивање података, а када се он напуни, подаци се уписују у флеш меморију. Поље `_sfudBufferPos` чува тренутну локацију за уписивање у овај бафер, а `_sfudBufferWritePos` чува локацију у флеш меморији за уписивање. `_flash` је показивач на флеш меморију у коју се уписује - неки микроконтролери имају више чипова флеш меморије.

1. Додајте следећи метод у `public` секцију за иницијализацију ове класе:

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

    Ово конфигурише флеш меморију на Wio Terminal-у за уписивање и подешава бафере на основу величине грануларности флеш меморије. Ово је у `init` методу, а не у конструктору, јер ово треба позвати након што је флеш меморија подешена у функцији `setup`.

1. Додајте следећи код у `public` секцију:

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

    Овај код дефинише методе за уписивање бајтова у систем флеш меморије. Ради тако што уписује у бафер у меморији који је одговарајуће величине за флеш меморију, а када се он напуни, уписује се у флеш меморију, бришући све постојеће податке на тој локацији. Постоји и `flushSfudBuffer` за уписивање непотпуног бафера, јер снимљени подаци неће бити тачно вишекратници величине грануларности, па крајњи део података треба уписати.

    > 💁 Крајњи део података ће уписати додатне нежељене податке, али то је у реду јер ће се читати само потребни подаци.

### Задатак - подешавање снимања звука

1. Направите нову датотеку у фолдеру `src` под називом `config.h`.

1. Додајте следеће на врх ове датотеке:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Овај код подешава неке константе за снимање звука.

    | Константа             | Вредност | Опис |
    | --------------------- | -------: | - |
    | RATE                  | 16000    | Брзина узорковања за звук. 16.000 је 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4        | Дужина звука за снимање. Ово је подешено на 4 секунде. За снимање дужег звука, повећајте ову вредност. |
    | SAMPLES               | 64000    | Укупно број узорака звука који ће бити снимљени. Подешено на брзину узорковања * број секунди |
    | BUFFER_SIZE           | 128044   | Величина бафера за снимање звука. Звук ће бити снимљен као WAV датотека, која има 44 бајта заглавља, затим 128.000 бајтова аудио података (сваки узорак је 2 бајта) |
    | ADC_BUF_LEN           | 1600     | Величина бафера који се користе за снимање звука са DMAC-а |

    > 💁 Ако вам се чини да су 4 секунде прекратке за захтев тајмера, можете повећати вредност `SAMPLE_LENGTH_SECONDS`, и све остале вредности ће се поново израчунати.

1. Направите нову датотеку у фолдеру `src` под називом `mic.h`.

1. Додајте следеће на врх ове датотеке:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Ово укључује неке потребне заглавне датотеке, укључујући `config.h` и `FlashWriter` заглавне датотеке.

1. Додајте следеће за дефинисање класе `Mic` која може снимати са микрофона:

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

    Ова класа тренутно има само неколико поља за праћење да ли је снимање почело и да ли је снимак спреман за коришћење. Када је DMAC подешен, он континуирано уписује у меморијске бафере, тако да застава `_isRecording` одређује да ли ови треба да се обрађују или игноришу. Застава `_isRecordingReady` ће бити постављена када је потребних 4 секунде звука снимљено. Поље `_writer` се користи за чување аудио података у флеш меморију.

    Глобална променљива се затим декларише за инстанцу класе `Mic`.

1. Додајте следећи код у `private` секцију класе `Mic`:

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

    Овај код дефинише метод `configureDmaAdc` који конфигурише DMAC, повезујући га са ADC-ом и подешавајући га да попуњава два различита наизменична бафера, `_adc_buf_0` и `_adc_buf_1`.

    > 💁 Један од недостатака развоја за микроконтролере је сложеност кода потребног за интеракцију са хардвером, јер ваш код ради на веома ниском нивоу директно комуницирајући са хардвером. Овај код је сложенији него што бисте писали за једноплочни рачунар или десктоп рачунар јер не постоји оперативни систем који би помогао. Постоје неке библиотеке које могу поједноставити ово, али и даље постоји доста сложености.

1. Испод овога, додајте следећи код:

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

    Овај код дефинише WAV заглавље као структуру која заузима 44 бајта меморије. У њега се уписују детаљи о брзини, величини и броју канала аудио датотеке. Ово заглавље се затим уписује у флеш меморију.

1. Испод овог кода, додајте следеће за декларисање метода који ће се позивати када су аудио бафери спремни за обраду:

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

    Аудио бафери су низови 16-битних целих бројева који садрже звук са ADC-а. ADC враћа 12-битне беззнаковне вредности (0-1023), тако да их треба претворити у 16-битне знаковне вредности, а затим претворити у 2 бајта за чување као сирове бинарне податке.

    Ови бајтови се уписују у флеш меморијске бафере. Упис почиње на индексу 44 - ово је померај од 44 бајта уписаних као WAV заглавље. Када се сниме сви бајтови потребни за тражену дужину звука, преостали подаци се уписују у флеш меморију.

1. У `public` секцији класе `Mic`, додајте следећи код:

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

    Овај код ће позивати DMAC да обавести ваш код да обради бафере. Проверава се да ли постоје подаци за обраду, и позива се метод `audioCallback` са одговарајућим бафером.

1. Изван класе, након декларације `Mic mic;`, додајте следећи код:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` ће позивати DMAC када су бафери спремни за обраду. Ова функција се проналази по имену, тако да само треба да постоји да би била позвана.

1. Додајте следећа два метода у `public` секцију класе `Mic`:

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

    Метод `init` садржи код за иницијализацију класе `Mic`. Овај метод подешава исправан напон за Mic пин, подешава флеш меморијски писач, уписује WAV заглавље и конфигурише DMAC. Метод `reset` ресетује флеш меморију и поново уписује заглавље након што је звук снимљен и коришћен.

### Задатак - снимање звука

1. У `main.cpp` датотеци, додајте директиву за укључивање заглавне датотеке `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. У функцији `setup`, иницијализујте C дугме. Снимање звука ће почети када се ово дугме притисне и трајаће 4 секунде:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Испод овога, иницијализујте микрофон, а затим испишите на конзолу да је звук спреман за снимање:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Изнад функције `loop`, дефинишите функцију за обраду снимљеног звука. За сада ова функција не ради ништа, али касније у лекцији ће слати говор на конверзију у текст:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Додајте следеће у функцију `loop`:

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

    Овај код проверава C дугме, и ако је притиснуто и снимање није почело, поље `_isRecording` класе `Mic` се поставља на true. Ово ће узроковати да метод `audioCallback` класе `Mic` чува звук док се не сними 4 секунде. Када се сними 4 секунде звука, поље `_isRecording` се поставља на false, а поље `_isRecordingReady` се поставља на true. Ово се затим проверава у функцији `loop`, и када је true, позива се функција `processAudio`, а затим се класа `Mic` ресетује.

1. Компилирајте овај код, отпремите га на ваш Wio Terminal и тестирајте га преко серијског монитора. Притисните C дугме (оно са леве стране, најближе прекидачу за напајање) и говорите. Снимиће се 4 секунде звука.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Овај код можете пронаћи у [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) фасцикли.
😀 Ваш програм за аудио снимање је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.