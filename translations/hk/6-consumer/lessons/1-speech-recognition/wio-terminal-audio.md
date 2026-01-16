<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-26T15:37:07+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "hk"
}
-->
# 捕捉音頻 - Wio Terminal

在這部分課程中，你將撰寫程式碼來在 Wio Terminal 上捕捉音頻。音頻捕捉將由 Wio Terminal 頂部的一個按鈕來控制。

## 編寫裝置程式以捕捉音頻

你可以使用 C++ 程式碼從麥克風捕捉音頻。Wio Terminal 只有 192KB 的 RAM，這不足以捕捉超過幾秒的音頻。不過，它有 4MB 的快閃記憶體，因此可以用來儲存捕捉到的音頻。

內建的麥克風捕捉的是類比信號，這些信號會被轉換為 Wio Terminal 可用的數位信號。在捕捉音頻時，數據需要以正確的時間間隔捕捉——例如，要以 16KHz 捕捉音頻，則需要每秒準確地捕捉 16,000 次，且每次取樣之間的間隔相等。與其用程式碼來完成這件事，你可以使用直接記憶體存取控制器（DMAC）。這是一種電路，可以從某處捕捉信號並寫入記憶體，而不會中斷處理器上正在執行的程式碼。

✅ 在 [維基百科的直接記憶體存取頁面](https://wikipedia.org/wiki/Direct_memory_access) 上了解更多關於 DMA 的資訊。

![音頻從麥克風進入 ADC，然後進入 DMAC。這會寫入一個緩衝區。當這個緩衝區滿了之後，它會被處理，DMAC 會寫入第二個緩衝區](../../../../../translated_images/hk/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC 可以以固定的間隔從 ADC 捕捉音頻，例如每秒 16,000 次以捕捉 16KHz 的音頻。它可以將捕捉到的數據寫入預先分配的記憶體緩衝區，當緩衝區滿了之後，將其提供給程式碼進行處理。使用這些記憶體可能會延遲音頻捕捉，但你可以設置多個緩衝區。DMAC 會先寫入緩衝區 1，當緩衝區 1 滿了之後，通知程式碼處理緩衝區 1，然後 DMAC 會寫入緩衝區 2。當緩衝區 2 滿了之後，它會通知程式碼，然後回到寫入緩衝區 1。這樣，只要你在填滿一個緩衝區的時間內處理完數據，就不會丟失任何數據。

每當捕捉到一個緩衝區後，它可以被寫入快閃記憶體。快閃記憶體需要使用定義的地址來寫入，指定寫入的位置和大小，類似於更新記憶體中的字節陣列。快閃記憶體具有粒度，這意味著擦除和寫入操作不僅需要固定大小，還需要對齊到該大小。例如，如果粒度是 4096 字節，而你請求在地址 4200 處擦除，它可能會擦除從地址 4096 到 8192 的所有數據。這意味著當你將音頻數據寫入快閃記憶體時，必須以正確大小的塊進行寫入。

### 任務 - 配置快閃記憶體

1. 使用 PlatformIO 創建一個全新的 Wio Terminal 專案。將此專案命名為 `smart-timer`。在 `setup` 函數中添加程式碼以配置序列埠。

1. 在 `platformio.ini` 文件中添加以下庫依賴項，以提供對快閃記憶體的訪問：

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. 打開 `main.cpp` 文件，並在文件頂部添加以下包含指令以使用快閃記憶體庫：

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD 代表 Serial Flash Universal Driver，是一個設計用於所有快閃記憶體晶片的庫。

1. 在 `setup` 函數中，添加以下程式碼以設置快閃儲存庫：

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    這段程式碼會循環直到 SFUD 庫初始化完成，然後啟用快速讀取。內建的快閃記憶體可以通過隊列式序列周邊介面（QSPI）訪問，這是一種 SPI 控制器，允許通過隊列進行連續訪問，並且對處理器的使用最小化。這使得讀取和寫入快閃記憶體的速度更快。

1. 在 `src` 資料夾中創建一個名為 `flash_writer.h` 的新文件。

1. 在該文件頂部添加以下內容：

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    這包括了一些必要的標頭文件，包括與快閃記憶體交互的 SFUD 庫的標頭文件。

1. 在這個新標頭文件中定義一個名為 `FlashWriter` 的類：

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. 在 `private` 區域中，添加以下程式碼：

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    這定義了一些欄位，用於在寫入快閃記憶體之前儲存數據的緩衝區。有一個字節陣列 `_sfudBuffer` 用於寫入數據，當這個緩衝區滿了之後，數據會被寫入快閃記憶體。`_sfudBufferPos` 欄位儲存當前在緩衝區中寫入的位置，而 `_sfudBufferWritePos` 儲存寫入快閃記憶體的位置。`_flash` 是一個指向快閃記憶體的指標——某些微控制器可能有多個快閃記憶體晶片。

1. 在 `public` 區域中添加以下方法以初始化該類：

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

    這會配置 Wio Terminal 上的快閃記憶體以進行寫入，並根據快閃記憶體的粒度設置緩衝區。這是在 `init` 方法中完成的，而不是構造函數，因為這需要在 `setup` 函數中設置快閃記憶體後調用。

1. 在 `public` 區域中添加以下程式碼：

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

    這段程式碼定義了將字節寫入快閃儲存系統的方法。它通過寫入與快閃記憶體大小匹配的記憶體緩衝區來工作，當緩衝區滿了之後，這些數據會被寫入快閃記憶體，並擦除該位置的任何現有數據。還有一個 `flushSfudBuffer` 方法，用於寫入不完整的緩衝區，因為捕捉的數據不會是粒度大小的整數倍，因此需要寫入數據的最後部分。

    > 💁 數據的最後部分會寫入一些額外的無用數據，但這沒關係，因為只會讀取需要的數據。

### 任務 - 設置音頻捕捉

1. 在 `src` 資料夾中創建一個名為 `config.h` 的新文件。

1. 在該文件頂部添加以下內容：

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    這段程式碼設置了一些用於音頻捕捉的常數。

    | 常數                  | 值     | 描述 |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | 音頻的取樣率。16,000 即 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | 要捕捉的音頻長度。這裡設置為 4 秒。如果需要錄製更長的音頻，可以增加這個值。 |
    | SAMPLES               | 64000  | 將捕捉的音頻取樣總數。設置為取樣率 * 秒數 |
    | BUFFER_SIZE           | 128044 | 捕捉音頻的緩衝區大小。音頻將以 WAV 文件格式捕捉，其中 44 字節為標頭，128,000 字節為音頻數據（每個取樣為 2 字節） |
    | ADC_BUF_LEN           | 1600   | 用於從 DMAC 捕捉音頻的緩衝區大小 |

    > 💁 如果你發現 4 秒太短，無法完成計時器請求，可以增加 `SAMPLE_LENGTH_SECONDS` 的值，其他值會自動重新計算。

1. 在 `src` 資料夾中創建一個名為 `mic.h` 的新文件。

1. 在該文件頂部添加以下內容：

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    這包括了一些必要的標頭文件，包括 `config.h` 和 `FlashWriter` 的標頭文件。

1. 添加以下內容以定義一個 `Mic` 類，用於從麥克風捕捉音頻：

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

    這個類目前只有幾個欄位，用於追蹤錄音是否已開始，以及錄音是否已準備好使用。DMAC 設置後，它會持續寫入記憶體緩衝區，因此 `_isRecording` 標誌決定這些數據是否應該被處理或忽略。當捕捉到所需的 4 秒音頻時，`_isRecordingReady` 標誌會被設置。`_writer` 欄位用於將音頻數據儲存到快閃記憶體。

    然後聲明一個全域變數作為 `Mic` 類的實例。

1. 在 `Mic` 類的 `private` 區域中添加以下程式碼：

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

    這段程式碼定義了一個 `configureDmaAdc` 方法，用於配置 DMAC，將其連接到 ADC，並設置為填充兩個交替的緩衝區 `_adc_buf_0` 和 `_adc_buf_1`。

    > 💁 微控制器開發的一個缺點是與硬體交互所需的程式碼非常複雜，因為你的程式碼在非常低的層級上直接與硬體交互。這段程式碼比你在單板電腦或桌面電腦上編寫的程式碼更複雜，因為沒有作業系統的幫助。雖然有一些庫可以簡化這個過程，但仍然存在很多複雜性。

1. 在這段程式碼下面，添加以下程式碼：

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

    這段程式碼將 WAV 文件的標頭定義為一個結構體，佔用 44 字節的記憶體。它會寫入關於音頻文件取樣率、大小和通道數的詳細資訊。然後將這個標頭寫入快閃記憶體。

1. 在這段程式碼下面，添加以下內容以聲明一個方法，該方法會在音頻緩衝區準備好處理時被調用：

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

    音頻緩衝區是包含來自 ADC 的音頻的 16 位整數陣列。ADC 返回的是 12 位無符號值（0-1023），因此需要將其轉換為 16 位有符號值，然後轉換為 2 個字節以作為原始二進位數據儲存。

    這些字節會被寫入快閃記憶體緩衝區。寫入從索引 44 開始——這是 WAV 文件標頭的 44 字節偏移量。一旦捕捉到所需長度的所有音頻數據，剩餘的數據會被寫入快閃記憶體。

1. 在 `Mic` 類的 `public` 區域中添加以下程式碼：

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

    這段程式碼會由 DMAC 調用，通知程式碼處理緩衝區。它檢查是否有數據需要處理，並調用 `audioCallback` 方法處理相關緩衝區。

1. 在類外部，在 `Mic mic;` 聲明之後，添加以下程式碼：

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` 是由 DMAC 調用的函數，當緩衝區準備好處理時會被調用。這個函數通過名稱找到，因此只需要存在即可被調用。

1. 在 `Mic` 類的 `public` 區域中添加以下兩個方法：

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

    `init` 方法包含初始化 `Mic` 類的程式碼。這個方法設置麥克風引腳的正確電壓，設置快閃記憶體寫入器，寫入 WAV 文件標頭，並配置 DMAC。`reset` 方法在音頻捕捉和使用後重置快閃記憶體並重新寫入標頭。

### 任務 - 捕捉音頻

1. 在 `main.cpp` 文件中，添加一個包含 `mic.h` 標頭文件的指令：

    ```cpp
    #include "mic.h"
    ```

1. 在 `setup` 函數中，初始化 C 按鈕。當按下此按鈕時，音頻捕捉將開始，並持續 4 秒：

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. 在此之下，初始化麥克風，然後在控制台上打印音頻已準備好捕捉的訊息：

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. 在 `loop` 函數上方，定義一個函數來處理捕捉到的音頻。目前這個函數什麼都不做，但在課程的後續部分，它會將語音發送進行文字轉換：

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. 在 `loop` 函數中添加以下內容：

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

    這段程式碼檢查 C 按鈕，如果按鈕被按下且錄音尚未開始，則將 `Mic` 類的 `_isRecording` 欄位設置為 true。這將導致 `Mic` 類的 `audioCallback` 方法儲存音頻，直到捕捉到 4 秒的音頻為止。一旦捕捉到 4 秒的音頻，`_isRecording` 欄位將設置為 false，`_isRecordingReady` 欄位將設置為 true。然後在 `loop` 函數中檢查該欄位，當其為 true 時，調用 `processAudio` 函數，然後重置 `Mic` 類。

1. 編譯這段程式碼，將其上傳到你的 Wio Terminal，並通過序列監視器測試。按下 C 按鈕（左側最靠近電源開關的按鈕），然後說話。將捕捉 4 秒的音頻。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 你可以在 [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) 資料夾中找到此程式碼。
😀 你的音頻錄製程式大獲成功！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。