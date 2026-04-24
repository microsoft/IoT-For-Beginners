# Запис на аудио - Wio Terminal

В тази част от урока ще напишете код за запис на аудио с вашия Wio Terminal. Записът на аудио ще се контролира чрез един от бутоните в горната част на Wio Terminal.

## Програмиране на устройството за запис на аудио

Можете да записвате аудио от микрофона, използвайки C++ код. Wio Terminal разполага само със 192KB RAM, което не е достатъчно за запис на повече от няколко секунди аудио. Освен това има 4MB флаш памет, която може да се използва за съхранение на записаното аудио.

Вграденият микрофон улавя аналогов сигнал, който се преобразува в цифров сигнал, който Wio Terminal може да използва. При запис на аудио данните трябва да се улавят в правилния момент – например, за да се записва аудио на 16KHz, данните трябва да се улавят точно 16 000 пъти в секунда, с равни интервали между всяка извадка. Вместо да използвате кода си за това, можете да използвате контролера за директен достъп до паметта (DMAC). Това е схема, която може да улавя сигнал от определено място и да го записва в паметта, без да прекъсва изпълнението на кода на процесора.

✅ Прочетете повече за DMA на [страницата за директен достъп до паметта в Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Аудио от микрофона преминава през ADC, след това към DMAC. Това се записва в един буфер. Когато този буфер се запълни, той се обработва и DMAC записва във втори буфер](../../../../../translated_images/bg/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC може да записва аудио от ADC на фиксирани интервали, например 16 000 пъти в секунда за аудио на 16KHz. Той може да записва тези данни в предварително зададен паметен буфер, а когато този буфер се запълни, да го направи достъпен за обработка от вашия код. Използването на тази памет може да забави записването на аудио, но можете да настроите множество буфери. DMAC записва в буфер 1, след което, когато той се запълни, уведомява вашия код да обработи буфер 1, докато DMAC записва в буфер 2. Когато буфер 2 се запълни, той уведомява вашия код и се връща към записване в буфер 1. По този начин, стига да обработвате всеки буфер за по-малко време, отколкото е необходимо за запълването му, няма да загубите данни.

След като всеки буфер бъде записан, той може да бъде записан във флаш паметта. Флаш паметта трябва да се записва, използвайки определени адреси, като се посочва къде да се запише и колко голям да бъде записът, подобно на актуализиране на масив от байтове в паметта. Флаш паметта има грануларност, което означава, че операциите по изтриване и запис зависят не само от фиксирания размер, но и от подравняването към този размер. Например, ако грануларността е 4096 байта и поискате изтриване на адрес 4200, това може да изтрие всички данни от адрес 4096 до 8192. Това означава, че когато записвате аудио данни във флаш паметта, те трябва да бъдат на парчета с правилния размер.

### Задача - конфигуриране на флаш паметта

1. Създайте нов проект за Wio Terminal, използвайки PlatformIO. Наречете този проект `smart-timer`. Добавете код във функцията `setup`, за да конфигурирате серийния порт.

1. Добавете следните зависимости на библиотеката към файла `platformio.ini`, за да осигурите достъп до флаш паметта:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Отворете файла `main.cpp` и добавете следната директива за включване на библиотеката за флаш памет в началото на файла:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD означава Serial Flash Universal Driver и е библиотека, предназначена за работа с всички чипове за флаш памет.

1. Във функцията `setup` добавете следния код, за да настроите библиотеката за флаш памет:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Това се изпълнява в цикъл, докато библиотеката SFUD не бъде инициализирана, след което активира бързото четене. Вградената флаш памет може да бъде достъпна чрез Queued Serial Peripheral Interface (QSPI), вид SPI контролер, който позволява непрекъснат достъп чрез опашка с минимално използване на процесора. Това прави четенето и записването във флаш паметта по-бързо.

1. Създайте нов файл в папката `src`, наречен `flash_writer.h`.

1. Добавете следното в началото на този файл:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Това включва някои необходими заглавни файлове, включително заглавния файл за библиотеката SFUD за взаимодействие с флаш паметта.

1. Дефинирайте клас в този нов заглавен файл, наречен `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. В секцията `private` добавете следния код:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Това дефинира някои полета за буфера, който ще се използва за съхранение на данни преди записването им във флаш паметта. Има масив от байтове `_sfudBuffer`, в който се записват данни, а когато той се запълни, данните се записват във флаш паметта. Полето `_sfudBufferPos` съхранява текущото местоположение за запис в този буфер, а `_sfudBufferWritePos` съхранява местоположението във флаш паметта за запис. `_flash` е указател към флаш паметта, в която ще се записва – някои микроконтролери имат множество чипове за флаш памет.

1. Добавете следния метод в секцията `public`, за да инициализирате този клас:

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

    Това конфигурира флаш паметта на Wio Terminal за запис и настройва буферите въз основа на размера на грануларността на флаш паметта. Това е в метод `init`, а не в конструктор, тъй като трябва да бъде извикано след настройването на флаш паметта във функцията `setup`.

1. Добавете следния код в секцията `public`:

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

    Този код дефинира методи за запис на байтове във флаш паметта. Той работи, като записва в буфер в паметта, който е с правилния размер за флаш паметта, а когато този буфер се запълни, той се записва във флаш паметта, изтривайки всички съществуващи данни на това място. Има и метод `flushSfudBuffer`, за да се запише непълен буфер, тъй като записваните данни няма да са точни кратни на размера на грануларността, така че крайната част от данните трябва да бъде записана.

    > 💁 Крайната част от данните ще запише допълнителни нежелани данни, но това е приемливо, тъй като ще се чете само необходимата част от данните.

### Задача - настройка на запис на аудио

1. Създайте нов файл в папката `src`, наречен `config.h`.

1. Добавете следното в началото на този файл:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Този код задава някои константи за записа на аудио.

    | Константа             | Стойност | Описание |
    | --------------------- | -------: | -------- |
    | RATE                  | 16000    | Честотата на извадките за аудиото. 16 000 е 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4        | Продължителността на записа. Настроена е на 4 секунди. За по-дълъг запис увеличете тази стойност. |
    | SAMPLES               | 64000    | Общият брой аудио извадки, които ще бъдат записани. Настроено на честотата на извадките * броя секунди |
    | BUFFER_SIZE           | 128044   | Размерът на аудио буфера за запис. Аудиото ще бъде записано като WAV файл, който е 44 байта заглавие, след това 128 000 байта аудио данни (всяка извадка е 2 байта) |
    | ADC_BUF_LEN           | 1600     | Размерът на буферите, които ще се използват за запис на аудио от DMAC |

    > 💁 Ако смятате, че 4 секунди са твърде кратки, за да поискате таймер, можете да увеличите стойността на `SAMPLE_LENGTH_SECONDS`, и всички останали стойности ще се преизчислят.

1. Създайте нов файл в папката `src`, наречен `mic.h`.

1. Добавете следното в началото на този файл:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Това включва някои необходими заглавни файлове, включително заглавните файлове `config.h` и `FlashWriter`.

1. Добавете следното, за да дефинирате клас `Mic`, който може да записва от микрофона:

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

    Този клас в момента има само няколко полета, за да следи дали записът е започнал и дали записът е готов за използване. Когато DMAC е настроен, той непрекъснато записва в паметни буфери, така че флагът `_isRecording` определя дали тези буфери трябва да се обработват или игнорират. Флагът `_isRecordingReady` ще бъде зададен, когато необходимите 4 секунди аудио бъдат записани. Полето `_writer` се използва за съхранение на аудио данните във флаш паметта.

    След това се декларира глобална променлива за инстанция на класа `Mic`.

1. Добавете следния код в секцията `private` на класа `Mic`:

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

    Този код дефинира метод `configureDmaAdc`, който конфигурира DMAC, свързвайки го с ADC и настройвайки го да попълва два различни редуващи се буфера, `_adc_buf_0` и `_adc_buf_1`.

    > 💁 Един от недостатъците на разработката за микроконтролери е сложността на кода, необходим за взаимодействие с хардуера, тъй като вашият код работи на много ниско ниво, директно взаимодействайки с хардуера. Този код е по-сложен от това, което бихте написали за едноплатков компютър или настолен компютър, тъй като няма операционна система, която да помага. Съществуват някои библиотеки, които могат да опростят това, но все пак има много сложност.

1. Под този код добавете следното:

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

    Този код дефинира заглавието на WAV файла като структура, която заема 44 байта памет. Той записва подробности за честотата, размера и броя на каналите на аудио файла. Това заглавие след това се записва във флаш паметта.

1. Под този код добавете следното, за да декларирате метод, който ще се извиква, когато аудио буферите са готови за обработка:

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

    Аудио буферите са масиви от 16-битови цели числа, съдържащи аудиото от ADC. ADC връща 12-битови беззнакови стойности (0-1023), така че те трябва да бъдат преобразувани в 16-битови знакови стойности, а след това преобразувани в 2 байта, за да бъдат съхранени като сурови двоични данни.

    Тези байтове се записват във флаш паметта. Записът започва от индекс 44 – това е отместването от 44-те байта, записани като заглавие на WAV файла. След като всички необходими байтове за изискваната дължина на аудиото бъдат записани, останалите данни се записват във флаш паметта.

1. В секцията `public` на класа `Mic` добавете следния код:

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

    Този код ще бъде извикан от DMAC, за да уведоми вашия код, че буферите са готови за обработка. Той проверява дали има данни за обработка и извиква метода `audioCallback` с подходящия буфер.

1. Извън класа, след декларацията `Mic mic;`, добавете следния код:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` ще бъде извикан от DMAC, когато буферите са готови за обработка. Тази функция се намира по име, така че просто трябва да съществува, за да бъде извикана.

1. Добавете следните два метода в секцията `public` на класа `Mic`:

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

    Методът `init` съдържа код за инициализиране на класа `Mic`. Този метод задава правилното напрежение за пина на микрофона, настройва писателя за флаш паметта, записва заглавието на WAV файла и конфигурира DMAC. Методът `reset` нулира флаш паметта и презаписва заглавието, след като аудиото е записано и използвано.

### Задача - запис на аудио

1. Във файла `main.cpp` добавете директива за включване на заглавния файл `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Във функцията `setup` инициализирайте бутона C. Записът на аудио ще започне, когато този бутон бъде натиснат, и ще продължи 4 секунди:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Под това инициализирайте микрофона, след което отпечатайте в конзолата, че аудиото е готово за запис:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Над функцията `loop` дефинирайте функция за обработка на записаното аудио. Засега тя не прави нищо, но по-късно в урока ще изпрати речта за преобразуване в текст:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Добавете следното във функцията `loop`:

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

    Този код проверява бутона C и ако той е натиснат и записът не е започнал, полето `_isRecording` на класа `Mic` се задава на true. Това ще накара метода `audioCallback` на класа `Mic` да съхранява аудио, докато не бъдат записани 4 секунди. След като бъдат записани 4 секунди аудио, полето `_isRecording` се задава на false, а полето `_isRecordingReady` се задава на true. Това след това се проверява във функцията `loop`, и когато е true, се извиква функцията `processAudio`, след което класът `Mic` се нулира.

1. Компилирайте този код, качете го на вашия Wio Terminal и го тествайте през серийния монитор. Натиснете бутона C (този от лявата страна, най-близо до превключвателя за захранване) и говорете. Ще бъдат записани 4 секунди аудио.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Можете да намерите този код в папката [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 Вашата програма за аудио запис беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.