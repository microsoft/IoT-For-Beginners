<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-25T00:24:20+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "zh"
}
-->
# 捕获音频 - Wio Terminal

在本课程的这一部分中，您将编写代码以在 Wio Terminal 上捕获音频。音频捕获将由 Wio Terminal 顶部的一个按钮控制。

## 编程设备以捕获音频

您可以使用 C++ 代码从麦克风捕获音频。Wio Terminal 只有 192KB 的 RAM，不足以捕获超过几秒的音频。它还具有 4MB 的闪存，因此可以用来保存捕获的音频。

内置麦克风捕获模拟信号，并将其转换为 Wio Terminal 可用的数字信号。在捕获音频时，数据需要在正确的时间点进行捕获——例如，要以 16KHz 捕获音频，音频需要每秒精确捕获 16,000 次，并且每次采样之间的间隔相等。与其使用代码来完成此操作，您可以使用直接内存访问控制器 (DMAC)。这是一个电路，可以从某处捕获信号并写入内存，而不会中断处理器上运行的代码。

✅ 在 [Wikipedia 的直接内存访问页面](https://wikipedia.org/wiki/Direct_memory_access) 上了解更多关于 DMA 的信息。

![音频从麦克风进入 ADC，然后到 DMAC。DMAC 将数据写入一个缓冲区。当该缓冲区满时，数据被处理，DMAC 写入第二个缓冲区](../../../../../translated_images/zh/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC 可以以固定间隔从 ADC 捕获音频，例如以每秒 16,000 次的速率捕获 16KHz 音频。它可以将捕获的数据写入预分配的内存缓冲区，当缓冲区满时，通知您的代码进行处理。使用此内存可能会延迟音频捕获，但您可以设置多个缓冲区。DMAC 写入缓冲区 1，当缓冲区 1 满时，通知您的代码处理缓冲区 1，同时 DMAC 写入缓冲区 2。当缓冲区 2 满时，它通知您的代码，然后返回写入缓冲区 1。这样，只要您在填满一个缓冲区所需的时间内处理每个缓冲区，就不会丢失任何数据。

每个缓冲区捕获完成后，可以将其写入闪存。写入闪存需要使用定义的地址，指定写入位置和写入大小，类似于更新内存中的字节数组。闪存具有粒度，这意味着擦除和写入操作不仅需要固定大小，还需要对齐到该大小。例如，如果粒度为 4096 字节，而您请求在地址 4200 处擦除，它可能会擦除地址 4096 到 8192 的所有数据。这意味着当您将音频数据写入闪存时，必须以正确大小的块进行写入。

### 任务 - 配置闪存

1. 使用 PlatformIO 创建一个全新的 Wio Terminal 项目。将此项目命名为 `smart-timer`。在 `setup` 函数中添加代码以配置串口。

1. 在 `platformio.ini` 文件中添加以下库依赖项，以提供对闪存的访问：

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. 打开 `main.cpp` 文件，并在文件顶部添加以下闪存库的 include 指令：

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD 代表串行闪存通用驱动程序，是一个设计用于所有闪存芯片的库。

1. 在 `setup` 函数中，添加以下代码以设置闪存存储库：

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    此代码循环直到 SFUD 库初始化完成，然后开启快速读取。内置闪存可以通过队列串行外设接口 (QSPI) 访问，这是一种 SPI 控制器，允许通过队列进行连续访问，处理器使用率最低。这使得读取和写入闪存更快。

1. 在 `src` 文件夹中创建一个名为 `flash_writer.h` 的新文件。

1. 在此文件顶部添加以下内容：

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    这包括一些所需的头文件，包括用于与闪存交互的 SFUD 库头文件。

1. 在此新头文件中定义一个名为 `FlashWriter` 的类：

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. 在 `private` 部分中，添加以下代码：

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    这定义了一些字段，用于在写入闪存之前存储数据的缓冲区。有一个字节数组 `_sfudBuffer` 用于写入数据，当缓冲区满时，数据会写入闪存。字段 `_sfudBufferPos` 存储当前写入缓冲区的位置，`_sfudBufferWritePos` 存储写入闪存的位置。`_flash` 是指向要写入的闪存的指针——一些微控制器有多个闪存芯片。

1. 在 `public` 部分添加以下方法以初始化此类：

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

    此方法配置 Wio Terminal 上的闪存以进行写入，并根据闪存的粒度大小设置缓冲区。这是在 `init` 方法中，而不是构造函数中，因为需要在 `setup` 函数中设置闪存后调用此方法。

1. 在 `public` 部分添加以下代码：

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

    此代码定义了将字节写入闪存存储系统的方法。它通过写入内存缓冲区来工作，该缓冲区大小与闪存的粒度大小一致，当缓冲区满时，数据会写入闪存，并擦除该位置的任何现有数据。还有一个 `flushSfudBuffer` 方法，用于写入不完整的缓冲区，因为捕获的数据不会是粒度大小的整数倍，因此需要写入数据的末尾部分。

    > 💁 数据末尾部分可能会写入一些额外的无用数据，但这没关系，因为只会读取所需的数据。

### 任务 - 设置音频捕获

1. 在 `src` 文件夹中创建一个名为 `config.h` 的新文件。

1. 在此文件顶部添加以下内容：

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    此代码设置了一些音频捕获的常量。

    | 常量                  | 值    | 描述 |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | 音频的采样率。16,000 表示 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | 要捕获的音频长度。设置为 4 秒。如果需要录制更长的音频，可以增加此值。 |
    | SAMPLES               | 64000  | 将要捕获的音频样本总数。设置为采样率 * 秒数 |
    | BUFFER_SIZE           | 128044 | 捕获音频的缓冲区大小。音频将以 WAV 文件格式捕获，其中 44 字节为头部，128,000 字节为音频数据（每个样本为 2 字节） |
    | ADC_BUF_LEN           | 1600   | 用于从 DMAC 捕获音频的缓冲区大小 |

    > 💁 如果您发现 4 秒太短以请求计时器，可以增加 `SAMPLE_LENGTH_SECONDS` 值，所有其他值将重新计算。

1. 在 `src` 文件夹中创建一个名为 `mic.h` 的新文件。

1. 在此文件顶部添加以下内容：

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    这包括一些所需的头文件，包括 `config.h` 和 `FlashWriter` 头文件。

1. 添加以下内容以定义一个可以从麦克风捕获的 `Mic` 类：

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

    此类目前只有几个字段，用于跟踪录音是否已开始，以及录音是否已准备好使用。当 DMAC 设置完成后，它会持续写入内存缓冲区，因此 `_isRecording` 标志决定是否处理这些缓冲区或忽略它们。`_isRecordingReady` 标志将在捕获所需的 4 秒音频后设置。`_writer` 字段用于将音频数据保存到闪存。

    然后声明一个全局变量，用于 `Mic` 类的实例。

1. 在 `Mic` 类的 `private` 部分添加以下代码：

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

    此代码定义了一个 `configureDmaAdc` 方法，用于配置 DMAC，将其连接到 ADC，并设置为填充两个不同的交替缓冲区 `_adc_buf_0` 和 `_adc_buf_1`。

    > 💁 微控制器开发的一个缺点是与硬件交互所需代码的复杂性，因为您的代码直接与硬件交互运行在非常低的级别。这段代码比您为单板计算机或桌面计算机编写的代码更复杂，因为没有操作系统提供帮助。虽然有一些库可以简化这一过程，但仍然存在很多复杂性。

1. 在此代码下方添加以下内容：

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

    此代码将 WAV 文件头定义为一个占用 44 字节内存的结构。它向头部写入有关音频文件速率、大小和通道数量的详细信息。然后将此头部写入闪存。

1. 在此代码下方添加以下内容以声明一个方法，当音频缓冲区准备好处理时调用：

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

    音频缓冲区是包含来自 ADC 的音频的 16 位整数数组。ADC 返回 12 位无符号值（0-1023），因此需要将其转换为 16 位有符号值，然后转换为 2 字节以存储为原始二进制数据。

    这些字节被写入闪存缓冲区。写入从索引 44 开始——这是 WAV 文件头部写入的 44 字节偏移量。一旦捕获了所需音频长度的所有字节，剩余数据会写入闪存。

1. 在 `Mic` 类的 `public` 部分添加以下代码：

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

    此代码将由 DMAC 调用，以通知您的代码处理缓冲区。它检查是否有数据需要处理，并调用 `audioCallback` 方法处理相关缓冲区。

1. 在类外部，在 `Mic mic;` 声明之后添加以下代码：

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` 将由 DMAC 调用，当缓冲区准备好处理时。此函数通过名称找到，因此只需存在即可被调用。

1. 在 `Mic` 类的 `public` 部分添加以下两个方法：

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

    `init` 方法包含初始化 `Mic` 类的代码。此方法设置麦克风引脚的正确电压，设置闪存写入器，写入 WAV 文件头部，并配置 DMAC。`reset` 方法在音频捕获并使用后重置闪存并重新写入头部。

### 任务 - 捕获音频

1. 在 `main.cpp` 文件中，为 `mic.h` 头文件添加一个 include 指令：

    ```cpp
    #include "mic.h"
    ```

1. 在 `setup` 函数中，初始化 C 按钮。当按下此按钮时，将开始音频捕获，并持续 4 秒：

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. 在此代码下方，初始化麦克风，然后在控制台打印音频已准备好捕获：

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. 在 `loop` 函数上方定义一个函数以处理捕获的音频。目前此函数不执行任何操作，但稍后在课程中它会将语音发送以转换为文本：

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. 在 `loop` 函数中添加以下内容：

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

    此代码检查 C 按钮，如果按下并且录音尚未开始，则将 `Mic` 类的 `_isRecording` 字段设置为 true。这将导致 `Mic` 类的 `audioCallback` 方法存储音频，直到捕获了 4 秒的音频。一旦捕获了 4 秒的音频，`_isRecording` 字段将设置为 false，`_isRecordingReady` 字段将设置为 true。然后在 `loop` 函数中检查此字段，当为 true 时调用 `processAudio` 函数，然后重置 `Mic` 类。

1. 构建此代码，将其上传到您的 Wio Terminal，并通过串行监视器进行测试。按下 C 按钮（左侧靠近电源开关的按钮），然后说话。将捕获 4 秒的音频。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 你可以在 [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) 文件夹中找到此代码。
😀 您的音频录制程序大获成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原文档的原始语言版本为权威来源。对于关键信息，建议使用专业人工翻译。我们对因使用本翻译而引起的任何误解或误读不承担责任。