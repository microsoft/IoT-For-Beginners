<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-25T00:26:55+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "ko"
}
-->
# 오디오 캡처 - Wio Terminal

이 수업의 이 부분에서는 Wio Terminal에서 오디오를 캡처하는 코드를 작성합니다. 오디오 캡처는 Wio Terminal 상단의 버튼 중 하나로 제어됩니다.

## 오디오 캡처를 위한 장치 프로그래밍

C++ 코드를 사용하여 마이크에서 오디오를 캡처할 수 있습니다. Wio Terminal은 192KB의 RAM만 가지고 있어 몇 초 이상의 오디오를 캡처하기에는 충분하지 않습니다. 하지만 4MB의 플래시 메모리가 있으므로 이를 사용하여 캡처된 오디오를 플래시 메모리에 저장할 수 있습니다.

내장 마이크는 아날로그 신호를 캡처하며, 이는 Wio Terminal에서 사용할 수 있는 디지털 신호로 변환됩니다. 오디오를 캡처할 때 데이터는 정확한 시간에 캡처되어야 합니다. 예를 들어, 16KHz로 오디오를 캡처하려면 초당 정확히 16,000번의 샘플을 동일한 간격으로 캡처해야 합니다. 이를 코드로 처리하는 대신, 직접 메모리 액세스 컨트롤러(DMAC)를 사용할 수 있습니다. DMAC는 신호를 캡처하여 메모리에 기록하는 회로로, 프로세서에서 실행 중인 코드를 방해하지 않습니다.

✅ DMAC에 대한 자세한 내용은 [Wikipedia의 직접 메모리 액세스 페이지](https://wikipedia.org/wiki/Direct_memory_access)를 참조하세요.

![마이크에서 오디오가 ADC로 전달된 후 DMAC로 이동합니다. DMAC는 하나의 버퍼에 기록하고, 이 버퍼가 가득 차면 처리된 후 두 번째 버퍼에 기록합니다](../../../../../translated_images/ko/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC는 ADC에서 고정된 간격으로 오디오를 캡처할 수 있습니다. 예를 들어, 16KHz 오디오의 경우 초당 16,000번 캡처합니다. DMAC는 캡처된 데이터를 미리 할당된 메모리 버퍼에 기록하며, 이 버퍼가 가득 차면 코드에서 처리할 수 있도록 제공합니다. 메모리를 사용하는 동안 오디오 캡처가 지연될 수 있지만, 여러 버퍼를 설정할 수 있습니다. DMAC는 버퍼 1에 기록한 후 가득 차면 코드에 알리고, 코드가 버퍼 1을 처리하는 동안 DMAC는 버퍼 2에 기록합니다. 버퍼 2가 가득 차면 코드에 알리고 다시 버퍼 1에 기록합니다. 이렇게 하면 각 버퍼를 채우는 데 걸리는 시간보다 빠르게 처리하면 데이터 손실이 발생하지 않습니다.

각 버퍼가 캡처되면 플래시 메모리에 기록할 수 있습니다. 플래시 메모리는 정의된 주소를 사용하여 기록 위치와 크기를 지정해야 하며, 메모리의 바이트 배열을 업데이트하는 것과 유사합니다. 플래시 메모리는 세분성이 있어 지우기 및 쓰기 작업이 고정된 크기뿐만 아니라 해당 크기에 맞게 정렬되어야 합니다. 예를 들어, 세분성이 4096바이트이고 주소 4200에서 지우기를 요청하면 주소 4096에서 8192까지의 모든 데이터를 지울 수 있습니다. 따라서 오디오 데이터를 플래시 메모리에 기록할 때 올바른 크기의 청크로 기록해야 합니다.

### 작업 - 플래시 메모리 구성

1. PlatformIO를 사용하여 새로운 Wio Terminal 프로젝트를 생성합니다. 이 프로젝트의 이름을 `smart-timer`로 설정합니다. `setup` 함수에 시리얼 포트를 구성하는 코드를 추가하세요.

1. 플래시 메모리에 액세스할 수 있도록 `platformio.ini` 파일에 다음 라이브러리 종속성을 추가하세요:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` 파일을 열고 플래시 메모리 라이브러리를 포함하는 다음 지시문을 파일 상단에 추가하세요:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD는 Serial Flash Universal Driver의 약자로, 모든 플래시 메모리 칩과 작동하도록 설계된 라이브러리입니다.

1. `setup` 함수에 다음 코드를 추가하여 플래시 저장소 라이브러리를 설정하세요:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    이 코드는 SFUD 라이브러리가 초기화될 때까지 반복하며, 이후 빠른 읽기를 활성화합니다. 내장 플래시 메모리는 Queued Serial Peripheral Interface(QSPI)를 사용하여 액세스할 수 있습니다. QSPI는 최소한의 프로세서 사용으로 큐를 통해 지속적인 액세스를 허용하는 SPI 컨트롤러의 일종입니다. 이를 통해 플래시 메모리를 더 빠르게 읽고 쓸 수 있습니다.

1. `src` 폴더에 `flash_writer.h`라는 새 파일을 생성하세요.

1. 이 파일 상단에 다음을 추가하세요:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    필요한 헤더 파일과 플래시 메모리와 상호작용하기 위한 SFUD 라이브러리 헤더 파일을 포함합니다.

1. 이 새 헤더 파일에 `FlashWriter`라는 클래스를 정의하세요:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` 섹션에 다음 코드를 추가하세요:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    이 코드는 플래시 메모리에 데이터를 쓰기 전에 사용할 버퍼를 정의합니다. `_sfudBuffer`라는 바이트 배열이 있으며, 이 버퍼가 가득 차면 플래시 메모리에 데이터를 기록합니다. `_sfudBufferPos` 필드는 이 버퍼에 기록할 현재 위치를 저장하며, `_sfudBufferWritePos`는 플래시 메모리에 기록할 위치를 저장합니다. `_flash`는 기록할 플래시 메모리를 가리키는 포인터입니다. 일부 마이크로컨트롤러는 여러 플래시 메모리 칩을 가지고 있습니다.

1. 이 클래스의 `public` 섹션에 다음 메서드를 추가하여 초기화하세요:

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

    이 메서드는 Wio Terminal의 플래시 메모리를 기록하도록 구성하며, 플래시 메모리의 세분성 크기를 기준으로 버퍼를 설정합니다. 이는 생성자가 아닌 `init` 메서드에 포함되며, 플래시 메모리가 `setup` 함수에서 설정된 후 호출되어야 합니다.

1. `public` 섹션에 다음 코드를 추가하세요:

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

    이 코드는 플래시 저장소 시스템에 바이트를 기록하는 메서드를 정의합니다. 이는 플래시 메모리에 적합한 크기의 메모리 버퍼에 기록하며, 버퍼가 가득 차면 플래시 메모리에 기록하고 해당 위치의 기존 데이터를 지웁니다. 또한 캡처된 데이터가 세분성 크기의 정확한 배수가 아니므로 불완전한 버퍼를 기록하기 위한 `flushSfudBuffer` 메서드도 포함됩니다.

    > 💁 데이터의 끝 부분은 추가적인 불필요한 데이터를 기록할 수 있지만, 필요한 데이터만 읽기 때문에 문제가 되지 않습니다.

### 작업 - 오디오 캡처 설정

1. `src` 폴더에 `config.h`라는 새 파일을 생성하세요.

1. 이 파일 상단에 다음을 추가하세요:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    이 코드는 오디오 캡처를 위한 몇 가지 상수를 설정합니다.

    | 상수                  | 값    | 설명 |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | 오디오 샘플 속도. 16,000은 16KHz를 의미합니다. |
    | SAMPLE_LENGTH_SECONDS | 4      | 캡처할 오디오 길이. 4초로 설정되어 있습니다. 더 긴 오디오를 녹음하려면 이 값을 증가시키세요. |
    | SAMPLES               | 64000  | 캡처될 총 오디오 샘플 수. 샘플 속도 * 초 수로 설정됩니다. |
    | BUFFER_SIZE           | 128044 | 캡처할 오디오 버퍼 크기. 오디오는 WAV 파일로 캡처되며, 헤더는 44바이트, 오디오 데이터는 128,000바이트(각 샘플은 2바이트)입니다. |
    | ADC_BUF_LEN           | 1600   | DMAC에서 오디오를 캡처하기 위해 사용할 버퍼 크기입니다. |

    > 💁 4초가 타이머 요청에 너무 짧다고 느껴지면 `SAMPLE_LENGTH_SECONDS` 값을 증가시키면 다른 값들도 자동으로 재계산됩니다.

1. `src` 폴더에 `mic.h`라는 새 파일을 생성하세요.

1. 이 파일 상단에 다음을 추가하세요:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    필요한 헤더 파일과 `config.h`, `FlashWriter` 헤더 파일을 포함합니다.

1. 마이크에서 캡처할 수 있는 `Mic` 클래스를 정의하세요:

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

    이 클래스는 현재 녹음이 시작되었는지 여부와 녹음이 사용 가능한지 여부를 추적하는 몇 가지 필드만 포함합니다. DMAC가 설정되면 메모리 버퍼에 지속적으로 기록하므로 `_isRecording` 플래그는 이를 처리할지 무시할지를 결정합니다. `_isRecordingReady` 플래그는 필요한 4초의 오디오가 캡처되었을 때 설정됩니다. `_writer` 필드는 오디오 데이터를 플래시 메모리에 저장하는 데 사용됩니다.

    그런 다음 `Mic` 클래스의 인스턴스를 위한 전역 변수가 선언됩니다.

1. `Mic` 클래스의 `private` 섹션에 다음 코드를 추가하세요:

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

    이 코드는 DMAC를 구성하고 ADC에 연결하며 `_adc_buf_0` 및 `_adc_buf_1`이라는 두 개의 교대 버퍼를 채우도록 설정하는 `configureDmaAdc` 메서드를 정의합니다.

    > 💁 마이크로컨트롤러 개발의 단점 중 하나는 하드웨어와 상호작용하기 위해 필요한 코드의 복잡성입니다. 코드가 운영 체제 없이 하드웨어와 직접 상호작용하기 때문에 단일 보드 컴퓨터나 데스크톱 컴퓨터에서 작성하는 코드보다 더 복잡합니다. 이를 간소화할 수 있는 라이브러리가 있지만 여전히 많은 복잡성이 존재합니다.

1. 이 아래에 다음 코드를 추가하세요:

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

    이 코드는 WAV 헤더를 44바이트의 메모리를 차지하는 구조체로 정의합니다. 오디오 파일 속도, 크기, 채널 수에 대한 세부 정보를 기록합니다. 그런 다음 이 헤더를 플래시 메모리에 기록합니다.

1. 이 코드 아래에 오디오 버퍼가 처리 준비가 되었을 때 호출될 메서드를 선언하세요:

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

    오디오 버퍼는 ADC에서 가져온 오디오를 포함하는 16비트 정수 배열입니다. ADC는 12비트 부호 없는 값(0-1023)을 반환하므로 이를 16비트 부호 있는 값으로 변환한 다음 2바이트로 변환하여 원시 바이너리 데이터로 저장해야 합니다.

    이러한 바이트는 플래시 메모리 버퍼에 기록됩니다. 기록은 인덱스 44에서 시작합니다. 이는 WAV 파일 헤더로 기록된 44바이트의 오프셋입니다. 필요한 오디오 길이에 필요한 모든 바이트가 캡처되면 남은 데이터가 플래시 메모리에 기록됩니다.

1. `Mic` 클래스의 `public` 섹션에 다음 코드를 추가하세요:

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

    이 코드는 DMAC가 버퍼를 처리할 준비가 되었음을 코드에 알리기 위해 호출됩니다. 처리할 데이터가 있는지 확인하고 관련 버퍼와 함께 `audioCallback` 메서드를 호출합니다.

1. 클래스 외부에서 `Mic mic;` 선언 후 다음 코드를 추가하세요:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler`는 DMAC가 버퍼를 처리할 준비가 되었을 때 호출됩니다. 이 함수는 이름으로 찾을 수 있으므로 존재하기만 하면 호출됩니다.

1. `Mic` 클래스의 `public` 섹션에 다음 두 메서드를 추가하세요:

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

    `init` 메서드는 `Mic` 클래스를 초기화하는 코드를 포함합니다. 이 메서드는 Mic 핀의 올바른 전압을 설정하고, 플래시 메모리 작성기를 설정하며, WAV 파일 헤더를 기록하고 DMAC를 구성합니다. `reset` 메서드는 오디오가 캡처되고 사용된 후 플래시 메모리를 재설정하고 헤더를 다시 기록합니다.

### 작업 - 오디오 캡처

1. `main.cpp` 파일에서 `mic.h` 헤더 파일에 대한 포함 지시문을 추가하세요:

    ```cpp
    #include "mic.h"
    ```

1. `setup` 함수에서 C 버튼을 초기화하세요. 이 버튼을 누르면 오디오 캡처가 시작되며 4초 동안 계속됩니다:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. 이 아래에 마이크를 초기화한 다음 오디오 캡처 준비가 되었음을 콘솔에 출력하세요:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` 함수 위에 캡처된 오디오를 처리하는 함수를 정의하세요. 현재는 아무 작업도 하지 않지만, 이후 수업에서 음성을 텍스트로 변환하는 데 사용됩니다:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` 함수에 다음을 추가하세요:

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

    이 코드는 C 버튼을 확인하고, 버튼이 눌렸고 녹음이 시작되지 않은 경우 `Mic` 클래스의 `_isRecording` 필드를 true로 설정합니다. 그러면 `Mic` 클래스의 `audioCallback` 메서드가 4초 동안 오디오를 저장합니다. 4초의 오디오가 캡처되면 `_isRecording` 필드는 false로 설정되고 `_isRecordingReady` 필드는 true로 설정됩니다. 그런 다음 `loop` 함수에서 이를 확인하고 true일 때 `processAudio` 함수를 호출한 다음 mic 클래스를 재설정합니다.

1. 이 코드를 빌드하고 Wio Terminal에 업로드한 후 시리얼 모니터를 통해 테스트하세요. C 버튼(왼쪽에 있으며 전원 스위치에 가장 가까운 버튼)을 누르고 말하세요. 4초 동안 오디오가 캡처됩니다.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 이 코드는 [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) 폴더에서 확인할 수 있습니다.
😀 오디오 녹음 프로그램이 성공적으로 작동했습니다!

**면책 조항**:  
이 문서는 AI 번역 서비스 [Co-op Translator](https://github.com/Azure/co-op-translator)를 사용하여 번역되었습니다. 정확성을 위해 최선을 다하고 있으나, 자동 번역에는 오류나 부정확성이 포함될 수 있습니다. 원본 문서를 해당 언어로 작성된 상태에서 권위 있는 자료로 간주해야 합니다. 중요한 정보의 경우, 전문적인 인간 번역을 권장합니다. 이 번역 사용으로 인해 발생하는 오해나 잘못된 해석에 대해 당사는 책임을 지지 않습니다.