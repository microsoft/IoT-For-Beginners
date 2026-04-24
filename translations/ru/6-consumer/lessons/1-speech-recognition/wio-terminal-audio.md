# Захват аудио - Wio Terminal

В этой части урока вы напишете код для захвата аудио на вашем Wio Terminal. Управление захватом аудио будет осуществляться одной из кнопок на верхней части Wio Terminal.

## Программирование устройства для захвата аудио

Вы можете захватывать аудио с микрофона, используя код на C++. Wio Terminal имеет всего 192 КБ оперативной памяти, чего недостаточно для захвата более чем нескольких секунд аудио. Однако он также оснащен 4 МБ флэш-памяти, которую можно использовать для сохранения захваченного аудио.

Встроенный микрофон захватывает аналоговый сигнал, который преобразуется в цифровой сигнал, пригодный для использования Wio Terminal. При захвате аудио данные должны быть захвачены в нужный момент времени — например, для захвата аудио с частотой 16 кГц данные должны захватываться ровно 16 000 раз в секунду с равными интервалами между каждым образцом. Вместо того чтобы использовать ваш код для выполнения этой задачи, вы можете воспользоваться контроллером прямого доступа к памяти (DMAC). Это аппаратная схема, которая может захватывать сигнал и записывать его в память, не прерывая выполнение вашего кода на процессоре.

✅ Подробнее о DMA можно прочитать на [странице прямого доступа к памяти в Википедии](https://wikipedia.org/wiki/Direct_memory_access).

![Аудио с микрофона поступает на АЦП, затем на DMAC. DMAC записывает данные в один буфер. Когда этот буфер заполняется, он обрабатывается, а DMAC записывает данные во второй буфер](../../../../../translated_images/ru/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC может захватывать аудио с АЦП через фиксированные интервалы, например, 16 000 раз в секунду для аудио с частотой 16 кГц. Он может записывать эти данные в заранее выделенный буфер памяти, а когда буфер заполняется, данные становятся доступными для обработки вашим кодом. Использование этой памяти может задерживать захват аудио, но вы можете настроить несколько буферов. DMAC записывает данные в буфер 1, затем, когда он заполняется, уведомляет ваш код о необходимости обработки буфера 1, в то время как DMAC записывает данные в буфер 2. Когда буфер 2 заполняется, он уведомляет ваш код и возвращается к записи данных в буфер 1. Таким образом, если вы обрабатываете каждый буфер быстрее, чем требуется для его заполнения, вы не потеряете данные.

После захвата каждого буфера его можно записать во флэш-память. Запись во флэш-память требует указания адресов, где нужно записывать данные и какого размера будет запись, аналогично обновлению массива байтов в памяти. Флэш-память имеет гранулярность, что означает, что операции стирания и записи зависят не только от фиксированного размера, но и от выравнивания по этому размеру. Например, если гранулярность составляет 4096 байт, а вы запрашиваете стирание по адресу 4200, это может стереть все данные с адреса 4096 до 8192. Это означает, что при записи аудио данных во флэш-память они должны быть разбиты на блоки правильного размера.

### Задача - настройка флэш-памяти

1. Создайте новый проект для Wio Terminal с использованием PlatformIO. Назовите этот проект `smart-timer`. Добавьте код в функцию `setup` для настройки последовательного порта.

1. Добавьте следующие зависимости библиотек в файл `platformio.ini`, чтобы получить доступ к флэш-памяти:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Откройте файл `main.cpp` и добавьте следующую директиву включения для библиотеки флэш-памяти в начало файла:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD означает Serial Flash Universal Driver, библиотеку, разработанную для работы со всеми чипами флэш-памяти.

1. В функции `setup` добавьте следующий код для настройки библиотеки флэш-хранилища:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Этот код выполняет цикл до тех пор, пока библиотека SFUD не будет инициализирована, затем включает быстрые чтения. Встроенная флэш-память может быть доступна через интерфейс Queued Serial Peripheral Interface (QSPI), тип SPI-контроллера, который позволяет непрерывный доступ через очередь с минимальной загрузкой процессора. Это делает чтение и запись во флэш-память быстрее.

1. Создайте новый файл в папке `src` с именем `flash_writer.h`.

1. Добавьте следующее в начало этого файла:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Это включает необходимые заголовочные файлы, включая заголовочный файл библиотеки SFUD для взаимодействия с флэш-памятью.

1. Определите класс в этом новом заголовочном файле с именем `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. В секции `private` добавьте следующий код:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Это определяет несколько полей для буфера, который будет использоваться для хранения данных перед записью их во флэш-память. Существует массив байтов `_sfudBuffer` для записи данных, и когда он заполняется, данные записываются во флэш-память. Поле `_sfudBufferPos` хранит текущую позицию для записи в этот буфер, а `_sfudBufferWritePos` хранит позицию во флэш-памяти для записи. `_flash` — это указатель на флэш-память для записи — некоторые микроконтроллеры имеют несколько чипов флэш-памяти.

1. Добавьте следующий метод в секцию `public` для инициализации этого класса:

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

    Этот метод настраивает флэш-память на Wio Terminal для записи и устанавливает буферы на основе размера зерна флэш-памяти. Это выполняется в методе `init`, а не в конструкторе, так как метод должен быть вызван после настройки флэш-памяти в функции `setup`.

1. Добавьте следующий код в секцию `public`:

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

    Этот код определяет методы для записи байтов в систему флэш-хранилища. Он работает, записывая данные в буфер в памяти, который имеет правильный размер для флэш-памяти, и когда он заполняется, данные записываются во флэш-память, стирая любые существующие данные в этом месте. Также есть метод `flushSfudBuffer` для записи неполного буфера, так как захваченные данные не будут точными кратными размеру зерна, поэтому конечная часть данных должна быть записана.

    > 💁 Конечная часть данных будет содержать дополнительные ненужные данные, но это нормально, так как будет прочитана только необходимая информация.

### Задача - настройка захвата аудио

1. Создайте новый файл в папке `src` с именем `config.h`.

1. Добавьте следующее в начало этого файла:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Этот код задает несколько констант для захвата аудио.

    | Константа             | Значение | Описание |
    | --------------------- | -------: | - |
    | RATE                  | 16000    | Частота выборки для аудио. 16 000 — это 16 кГц |
    | SAMPLE_LENGTH_SECONDS | 4        | Длина аудио для захвата. Установлено на 4 секунды. Чтобы записать более длинное аудио, увеличьте это значение. |
    | SAMPLES               | 64000    | Общее количество аудиовыборок, которые будут захвачены. Установлено как частота выборки * количество секунд |
    | BUFFER_SIZE           | 128044   | Размер буфера для захвата аудио. Аудио будет захвачено в формате WAV, который состоит из 44 байт заголовка и 128 000 байт аудиоданных (каждая выборка занимает 2 байта) |
    | ADC_BUF_LEN           | 1600     | Размер буферов для захвата аудио с DMAC |

    > 💁 Если вы считаете, что 4 секунды слишком мало для запроса таймера, вы можете увеличить значение `SAMPLE_LENGTH_SECONDS`, и все остальные значения будут пересчитаны.

1. Создайте новый файл в папке `src` с именем `mic.h`.

1. Добавьте следующее в начало этого файла:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Это включает необходимые заголовочные файлы, включая заголовочные файлы `config.h` и `FlashWriter`.

1. Добавьте следующее для определения класса `Mic`, который может захватывать данные с микрофона:

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

    Этот класс пока содержит только несколько полей для отслеживания, началась ли запись, и готова ли запись к использованию. Когда DMAC настроен, он непрерывно записывает данные в буферы памяти, поэтому флаг `_isRecording` определяет, должны ли они быть обработаны или проигнорированы. Флаг `_isRecordingReady` будет установлен, когда будет захвачено требуемое 4 секунды аудио. Поле `_writer` используется для сохранения аудиоданных во флэш-память.

    Затем объявляется глобальная переменная для экземпляра класса `Mic`.

1. Добавьте следующий код в секцию `private` класса `Mic`:

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

    Этот код определяет метод `configureDmaAdc`, который настраивает DMAC, подключая его к АЦП и устанавливая его для заполнения двух чередующихся буферов, `_adc_buf_0` и `_adc_buf_1`.

    > 💁 Одним из недостатков разработки для микроконтроллеров является сложность кода, необходимого для взаимодействия с оборудованием, так как ваш код работает на очень низком уровне, взаимодействуя непосредственно с оборудованием. Этот код сложнее, чем тот, который вы бы написали для одноплатного компьютера или настольного компьютера, так как здесь нет операционной системы, которая могла бы помочь. Существуют библиотеки, которые могут упростить эту задачу, но сложность все равно остается.

1. Ниже добавьте следующий код:

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

    Этот код определяет заголовок WAV как структуру, занимающую 44 байта памяти. В заголовок записываются детали о частоте аудиофайла, размере и количестве каналов. Этот заголовок затем записывается во флэш-память.

1. Ниже этого кода добавьте следующее для объявления метода, который будет вызываться, когда аудиобуферы готовы к обработке:

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

    Аудиобуферы представляют собой массивы 16-битных целых чисел, содержащих аудио с АЦП. АЦП возвращает 12-битные значения без знака (0-1023), поэтому их нужно преобразовать в 16-битные значения со знаком, а затем преобразовать в 2 байта для хранения в виде необработанных бинарных данных.

    Эти байты записываются в буферы флэш-памяти. Запись начинается с индекса 44 — это смещение от 44 байт, записанных как заголовок файла WAV. Как только все байты, необходимые для требуемой длины аудио, захвачены, оставшиеся данные записываются во флэш-память.

1. В секции `public` класса `Mic` добавьте следующий код:

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

    Этот код будет вызываться DMAC, чтобы уведомить ваш код о необходимости обработки буферов. Он проверяет, есть ли данные для обработки, и вызывает метод `audioCallback` с соответствующим буфером.

1. Вне класса, после объявления `Mic mic;`, добавьте следующий код:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Функция `DMAC_1_Handler` будет вызываться DMAC, когда буферы готовы к обработке. Эта функция определяется по имени, поэтому она просто должна существовать, чтобы быть вызванной.

1. Добавьте следующие два метода в секцию `public` класса `Mic`:

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

    Метод `init` содержит код для инициализации класса `Mic`. Этот метод устанавливает правильное напряжение для пина микрофона, настраивает флэш-память, записывает заголовок WAV и настраивает DMAC. Метод `reset` сбрасывает флэш-память и заново записывает заголовок после того, как аудио было захвачено и использовано.

### Задача - захват аудио

1. В файле `main.cpp` добавьте директиву включения для заголовочного файла `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. В функции `setup` инициализируйте кнопку C. Захват аудио начнется при нажатии этой кнопки и будет продолжаться 4 секунды:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Ниже этого инициализируйте микрофон, затем выведите в консоль сообщение о готовности к захвату аудио:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Над функцией `loop` определите функцию для обработки захваченного аудио. Пока она ничего не делает, но позже в этом уроке она будет отправлять речь для преобразования в текст:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Добавьте следующее в функцию `loop`:

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

    Этот код проверяет кнопку C, и если она нажата и запись еще не началась, то поле `_isRecording` класса `Mic` устанавливается в значение `true`. Это приведет к тому, что метод `audioCallback` класса `Mic` будет сохранять аудио до тех пор, пока не будет захвачено 4 секунды. После захвата 4 секунд аудио поле `_isRecording` устанавливается в значение `false`, а поле `_isRecordingReady` устанавливается в значение `true`. Это затем проверяется в функции `loop`, и когда значение равно `true`, вызывается функция `processAudio`, затем класс `Mic` сбрасывается.

1. Соберите этот код, загрузите его на ваш Wio Terminal и протестируйте через последовательный монитор. Нажмите кнопку C (ту, которая находится слева, ближе всего к переключателю питания) и говорите. Будет захвачено 4 секунды аудио.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 Вы можете найти этот код в папке [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
Ваше приложение для записи аудио стало успешным!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.