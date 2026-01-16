<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-25T00:26:08+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "ja"
}
-->
# 音声をキャプチャする - Wio Terminal

このレッスンでは、Wio Terminalで音声をキャプチャするコードを書きます。音声キャプチャは、Wio Terminalの上部にあるボタンの1つで制御されます。

## デバイスをプログラムして音声をキャプチャする

マイクから音声をキャプチャするには、C++コードを使用します。Wio Terminalには192KBのRAMしかないため、数秒以上の音声をキャプチャするには不十分です。ただし、4MBのフラッシュメモリがあるため、これを使用してキャプチャした音声を保存できます。

内蔵マイクはアナログ信号をキャプチャし、それをWio Terminalが使用できるデジタル信号に変換します。音声をキャプチャする際には、データを正確なタイミングでキャプチャする必要があります。例えば、16KHzで音声をキャプチャする場合、1秒間に16,000回、等間隔でサンプルを取得する必要があります。この処理をコードで行う代わりに、ダイレクトメモリアクセスコントローラ（DMAC）を使用できます。これは、プロセッサで実行中のコードを中断することなく、信号を取得してメモリに書き込む回路です。

✅ DMAについてさらに詳しくは、[Wikipediaのダイレクトメモリアクセスのページ](https://wikipedia.org/wiki/Direct_memory_access)をご覧ください。

![マイクからの音声がADCを通り、DMACに送られる。このデータは1つのバッファに書き込まれ、バッファが満杯になると処理され、DMACは2つ目のバッファに書き込む](../../../../../translated_images/ja/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMACは、ADCからの音声を固定間隔でキャプチャできます。例えば、16KHzの音声の場合、1秒間に16,000回キャプチャします。このキャプチャしたデータは、事前に割り当てられたメモリバッファに書き込まれ、バッファが満杯になるとコードで処理できるようになります。このメモリの使用により音声キャプチャが遅れる可能性がありますが、複数のバッファを設定することで対応できます。DMACはバッファ1に書き込み、満杯になるとコードに通知してバッファ1を処理させ、その間にDMACはバッファ2に書き込みます。バッファ2が満杯になるとコードに通知し、再びバッファ1に書き込みます。このようにして、各バッファを満杯になる前に処理できれば、データを失うことはありません。

各バッファがキャプチャされると、それをフラッシュメモリに書き込むことができます。フラッシュメモリに書き込むには、定義されたアドレスを使用して、どこに書き込むか、どのくらいのサイズで書き込むかを指定する必要があります。これは、メモリ内のバイト配列を更新するのと似ています。フラッシュメモリには粒度（granularity）があり、消去や書き込み操作は固定サイズで行われ、そのサイズに整列する必要があります。例えば、粒度が4096バイトの場合、アドレス4200で消去をリクエストすると、アドレス4096から8192までのデータがすべて消去される可能性があります。このため、音声データをフラッシュメモリに書き込む際には、正しいサイズのチャンクで書き込む必要があります。

### タスク - フラッシュメモリを設定する

1. PlatformIOを使用して新しいWio Terminalプロジェクトを作成します。このプロジェクトを`smart-timer`と名付け、`setup`関数にシリアルポートを設定するコードを追加します。

1. フラッシュメモリにアクセスするために、以下のライブラリ依存関係を`platformio.ini`ファイルに追加します：

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp`ファイルを開き、フラッシュメモリライブラリのインクルードディレクティブをファイルの先頭に追加します：

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUDはSerial Flash Universal Driverの略で、すべてのフラッシュメモリチップで動作するように設計されたライブラリです。

1. `setup`関数に以下のコードを追加して、フラッシュストレージライブラリを設定します：

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    このコードは、SFUDライブラリが初期化されるまでループし、その後高速読み取りを有効にします。内蔵フラッシュメモリは、Queued Serial Peripheral Interface（QSPI）を使用してアクセスできます。QSPIは、プロセッサの使用を最小限に抑えながら、キューを介して連続的にアクセスできるSPIコントローラの一種です。これにより、フラッシュメモリへの読み書きが高速化されます。

1. `src`フォルダに`flash_writer.h`という新しいファイルを作成します。

1. このファイルの先頭に以下を追加します：

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    これには必要なヘッダーファイルが含まれており、フラッシュメモリとやり取りするためのSFUDライブラリのヘッダーファイルも含まれています。

1. この新しいヘッダーファイルに`FlashWriter`というクラスを定義します：

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private`セクションに以下のコードを追加します：

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    このコードは、フラッシュメモリに書き込む前にデータを保存するためのバッファを定義します。バイト配列`_sfudBuffer`にデータを書き込み、これが満杯になるとフラッシュメモリにデータを書き込みます。`_sfudBufferPos`フィールドは、このバッファ内の現在の書き込み位置を格納し、`_sfudBufferWritePos`はフラッシュメモリ内の書き込み位置を格納します。`_flash`は書き込み先のフラッシュメモリへのポインタです。一部のマイクロコントローラには複数のフラッシュメモリチップがあります。

1. このクラスを初期化するための以下のメソッドを`public`セクションに追加します：

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

    このメソッドは、Wio Terminalのフラッシュメモリを設定し、フラッシュメモリの粒度に基づいてバッファを設定します。これはコンストラクタではなく`init`メソッドに含まれています。なぜなら、フラッシュメモリが`setup`関数で設定された後に呼び出す必要があるからです。

1. `public`セクションに以下のコードを追加します：

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

    このコードは、フラッシュストレージシステムにバイトを書き込むためのメソッドを定義します。これは、フラッシュメモリに適したサイズのメモリ内バッファに書き込み、このバッファが満杯になるとフラッシュメモリに書き込みます。既存のデータはその場所で消去されます。また、`flushSfudBuffer`メソッドは、不完全なバッファを書き込むためのものです。キャプチャされたデータはフラッシュメモリの粒度の正確な倍数ではないため、データの最後の部分をフラッシュメモリに書き込む必要があります。

    > 💁 データの最後の部分には不要なデータが追加されますが、必要なデータだけを読み取るため問題ありません。

### タスク - 音声キャプチャを設定する

1. `src`フォルダに`config.h`という新しいファイルを作成します。

1. このファイルの先頭に以下を追加します：

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    このコードは、音声キャプチャ用の定数を設定します。

    | 定数                  | 値     | 説明 |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | 音声のサンプルレート。16,000は16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | キャプチャする音声の長さ。これは4秒に設定されています。より長い音声を録音するには、この値を増やしてください。 |
    | SAMPLES               | 64000  | キャプチャされる音声サンプルの総数。この値はサンプルレート×秒数で設定されます |
    | BUFFER_SIZE           | 128044 | 音声をキャプチャするためのバッファサイズ。音声はWAVファイルとしてキャプチャされ、44バイトのヘッダーと128,000バイトの音声データ（各サンプルは2バイト）で構成されます |
    | ADC_BUF_LEN           | 1600   | DMACから音声をキャプチャするために使用するバッファのサイズ |

    > 💁 4秒がタイマーをリクエストするには短すぎると感じた場合、`SAMPLE_LENGTH_SECONDS`の値を増やすことで、他の値も再計算されます。

1. `src`フォルダに`mic.h`という新しいファイルを作成します。

1. このファイルの先頭に以下を追加します：

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    これには必要なヘッダーファイルが含まれており、`config.h`と`FlashWriter`のヘッダーファイルも含まれています。

1. 以下を追加して、マイクからキャプチャする`Mic`クラスを定義します：

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

    このクラスには現在、録音が開始されたかどうか、録音が使用可能かどうかを追跡するためのフィールドがいくつか含まれています。DMACが設定されると、メモリバッファに継続的に書き込みます。そのため、`_isRecording`フラグはこれらを処理するか無視するかを決定します。必要な4秒間の音声がキャプチャされると、`_isRecordingReady`フラグが設定されます。`_writer`フィールドは、音声データをフラッシュメモリに保存するために使用されます。

    グローバル変数として`Mic`クラスのインスタンスが宣言されます。

1. `Mic`クラスの`private`セクションに以下のコードを追加します：

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

    このコードは、DMACを設定する`configureDmaAdc`メソッドを定義します。DMACをADCに接続し、2つの異なる交互バッファ（`_adc_buf_0`と`_adc_buf_1`）を設定します。

    > 💁 マイクロコントローラ開発の欠点の1つは、ハードウェアと直接やり取りするために必要なコードの複雑さです。コードは非常に低レベルで動作し、ハードウェアと直接やり取りします。シングルボードコンピュータやデスクトップコンピュータで書くコードよりも複雑です。オペレーティングシステムが支援してくれるわけではないためです。一部のライブラリを使用することでこれを簡略化できますが、それでも多くの複雑さが残ります。

1. このコードの下に以下を追加します：

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

    このコードは、44バイトのメモリを占有するWAVヘッダーを構造体として定義します。このヘッダーには、音声ファイルのレート、サイズ、チャンネル数に関する詳細が書き込まれます。このヘッダーはフラッシュメモリに書き込まれます。

1. このコードの下に、音声バッファが処理可能になったときに呼び出されるメソッドを宣言する以下のコードを追加します：

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

    音声バッファは、ADCからの音声を含む16ビット整数の配列です。ADCは12ビットの符号なし値（0-1023）を返すため、これを16ビットの符号付き値に変換し、さらに2バイトに変換して生のバイナリデータとして保存します。

    これらのバイトはフラッシュメモリバッファに書き込まれます。書き込みはインデックス44から開始されます。これは、WAVファイルヘッダーとして書き込まれた44バイトのオフセットです。必要な音声長のバイトがすべてキャプチャされると、残りのデータがフラッシュメモリに書き込まれます。

1. `Mic`クラスの`public`セクションに以下のコードを追加します：

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

    このコードは、DMACがバッファを処理するようコードに通知するために呼び出されます。処理すべきデータがあるかどうかを確認し、該当するバッファを`audioCallback`メソッドに渡します。

1. クラスの外部で、`Mic mic;`の宣言の後に以下のコードを追加します：

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler`は、バッファが処理可能になったときにDMACによって呼び出されます。この関数は名前で見つけられるため、存在するだけで呼び出されます。

1. `Mic`クラスの`public`セクションに以下の2つのメソッドを追加します：

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

    `init`メソッドは`Mic`クラスを初期化するコードを含みます。このメソッドは、マイクピンの正しい電圧を設定し、フラッシュメモリライターを設定し、WAVファイルヘッダーを書き込み、DMACを設定します。`reset`メソッドは、音声がキャプチャされて使用された後にフラッシュメモリをリセットし、ヘッダーを書き直します。

### タスク - 音声をキャプチャする

1. `main.cpp`ファイルに`mic.h`ヘッダーファイルのインクルードディレクティブを追加します：

    ```cpp
    #include "mic.h"
    ```

1. `setup`関数で、Cボタンを初期化します。このボタンが押されると音声キャプチャが開始され、4秒間続きます：

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. このコードの下に、マイクを初期化し、音声キャプチャの準備ができたことをコンソールに出力します：

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop`関数の上に、キャプチャされた音声を処理する関数を定義します。この関数は現在何もしませんが、後のレッスンで音声をテキストに変換するために使用されます：

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop`関数に以下を追加します：

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

    このコードはCボタンをチェックし、録音が開始されていない場合にボタンが押されたら、`Mic`クラスの`_isRecording`フィールドを`true`に設定します。これにより、`Mic`クラスの`audioCallback`メソッドが4秒間音声を保存します。4秒間の音声がキャプチャされると、`_isRecording`フィールドが`false`に設定され、`_isRecordingReady`フィールドが`true`に設定されます。これが`loop`関数でチェックされ、`true`の場合に`processAudio`関数が呼び出され、その後マイククラスがリセットされます。

1. このコードをビルドし、Wio Terminalにアップロードしてシリアルモニタでテストします。Cボタン（左側で電源スイッチに最も近いボタン）を押して話しかけると、4秒間の音声がキャプチャされます。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 このコードは [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) フォルダーにあります。
😀 あなたの音声録音プログラムは大成功でした！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。