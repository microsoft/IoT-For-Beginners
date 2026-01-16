<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T23:24:16+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "vi"
}
-->
# Ghi âm - Wio Terminal

Trong phần này của bài học, bạn sẽ viết mã để ghi âm trên Wio Terminal của mình. Việc ghi âm sẽ được điều khiển bởi một trong các nút trên đỉnh của Wio Terminal.

## Lập trình thiết bị để ghi âm

Bạn có thể ghi âm từ micro bằng cách sử dụng mã C++. Wio Terminal chỉ có 192KB RAM, không đủ để ghi âm dài hơn vài giây. Tuy nhiên, nó có 4MB bộ nhớ flash, vì vậy bạn có thể sử dụng bộ nhớ này để lưu trữ âm thanh đã ghi.

Micro tích hợp ghi lại tín hiệu analog, sau đó được chuyển đổi thành tín hiệu số mà Wio Terminal có thể sử dụng. Khi ghi âm, dữ liệu cần được ghi lại đúng thời điểm - ví dụ, để ghi âm ở tần số 16KHz, âm thanh cần được ghi lại chính xác 16.000 lần mỗi giây, với các khoảng thời gian đều nhau giữa mỗi mẫu. Thay vì sử dụng mã của bạn để làm điều này, bạn có thể sử dụng bộ điều khiển truy cập bộ nhớ trực tiếp (DMAC). Đây là một mạch có thể ghi lại tín hiệu từ một nguồn nào đó và ghi vào bộ nhớ mà không làm gián đoạn mã của bạn đang chạy trên bộ xử lý.

✅ Đọc thêm về DMA trên [trang truy cập bộ nhớ trực tiếp trên Wikipedia](https://wikipedia.org/wiki/Direct_memory_access).

![Âm thanh từ micro đi qua ADC rồi đến DMAC. DMAC ghi vào một bộ đệm. Khi bộ đệm này đầy, nó được xử lý và DMAC ghi vào bộ đệm thứ hai](../../../../../translated_images/vi/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC có thể ghi âm từ ADC ở các khoảng thời gian cố định, chẳng hạn như 16.000 lần mỗi giây cho âm thanh 16KHz. Nó có thể ghi dữ liệu đã ghi vào một bộ đệm bộ nhớ được phân bổ trước, và khi bộ đệm này đầy, nó sẽ thông báo cho mã của bạn xử lý. Việc sử dụng bộ nhớ này có thể làm chậm quá trình ghi âm, nhưng bạn có thể thiết lập nhiều bộ đệm. DMAC ghi vào bộ đệm 1, sau đó khi bộ đệm này đầy, nó thông báo cho mã của bạn xử lý bộ đệm 1, trong khi DMAC ghi vào bộ đệm 2. Khi bộ đệm 2 đầy, nó thông báo cho mã của bạn và quay lại ghi vào bộ đệm 1. Bằng cách này, miễn là bạn xử lý mỗi bộ đệm trong thời gian ngắn hơn thời gian cần để làm đầy một bộ đệm, bạn sẽ không mất dữ liệu.

Khi mỗi bộ đệm đã được ghi lại, nó có thể được ghi vào bộ nhớ flash. Bộ nhớ flash cần được ghi vào bằng các địa chỉ xác định, chỉ định nơi ghi và kích thước cần ghi, tương tự như cập nhật một mảng byte trong bộ nhớ. Bộ nhớ flash có tính hạt, nghĩa là các thao tác xóa và ghi phụ thuộc không chỉ vào kích thước cố định mà còn phải căn chỉnh với kích thước đó. Ví dụ, nếu tính hạt là 4096 byte và bạn yêu cầu xóa tại địa chỉ 4200, nó có thể xóa tất cả dữ liệu từ địa chỉ 4096 đến 8192. Điều này có nghĩa là khi bạn ghi dữ liệu âm thanh vào bộ nhớ flash, nó phải được chia thành các khối có kích thước phù hợp.

### Nhiệm vụ - cấu hình bộ nhớ flash

1. Tạo một dự án Wio Terminal mới bằng PlatformIO. Đặt tên dự án này là `smart-timer`. Thêm mã vào hàm `setup` để cấu hình cổng nối tiếp.

1. Thêm các thư viện phụ thuộc sau vào tệp `platformio.ini` để cung cấp quyền truy cập vào bộ nhớ flash:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. Mở tệp `main.cpp` và thêm chỉ thị `include` sau cho thư viện bộ nhớ flash vào đầu tệp:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD là viết tắt của Serial Flash Universal Driver, một thư viện được thiết kế để hoạt động với tất cả các chip bộ nhớ flash.

1. Trong hàm `setup`, thêm mã sau để thiết lập thư viện lưu trữ flash:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    Đoạn mã này lặp lại cho đến khi thư viện SFUD được khởi tạo, sau đó bật chế độ đọc nhanh. Bộ nhớ flash tích hợp có thể được truy cập bằng Giao diện Ngoại vi Nối tiếp Hàng đợi (QSPI), một loại bộ điều khiển SPI cho phép truy cập liên tục thông qua hàng đợi với mức sử dụng bộ xử lý tối thiểu. Điều này giúp việc đọc và ghi vào bộ nhớ flash nhanh hơn.

1. Tạo một tệp mới trong thư mục `src` có tên là `flash_writer.h`.

1. Thêm đoạn mã sau vào đầu tệp này:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    Đoạn mã này bao gồm một số tệp tiêu đề cần thiết, bao gồm tệp tiêu đề cho thư viện SFUD để tương tác với bộ nhớ flash.

1. Định nghĩa một lớp trong tệp tiêu đề mới này có tên là `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. Trong phần `private`, thêm đoạn mã sau:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    Đoạn mã này định nghĩa một số trường cho bộ đệm được sử dụng để lưu trữ dữ liệu trước khi ghi vào bộ nhớ flash. Có một mảng byte `_sfudBuffer` để ghi dữ liệu, và khi bộ đệm này đầy, dữ liệu sẽ được ghi vào bộ nhớ flash. Trường `_sfudBufferPos` lưu vị trí hiện tại để ghi vào bộ đệm này, và `_sfudBufferWritePos` lưu vị trí trong bộ nhớ flash để ghi vào. `_flash` là một con trỏ đến bộ nhớ flash để ghi - một số vi điều khiển có nhiều chip bộ nhớ flash.

1. Thêm phương thức sau vào phần `public` để khởi tạo lớp này:

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

    Phương thức này cấu hình bộ nhớ flash trên Wio Terminal để ghi vào, và thiết lập các bộ đệm dựa trên kích thước hạt của bộ nhớ flash. Phương thức này nằm trong một phương thức `init`, thay vì một constructor, vì nó cần được gọi sau khi bộ nhớ flash đã được thiết lập trong hàm `setup`.

1. Thêm đoạn mã sau vào phần `public`:

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

    Đoạn mã này định nghĩa các phương thức để ghi byte vào hệ thống lưu trữ flash. Nó hoạt động bằng cách ghi vào một bộ đệm trong bộ nhớ có kích thước phù hợp với bộ nhớ flash, và khi bộ đệm này đầy, nó sẽ được ghi vào bộ nhớ flash, xóa bất kỳ dữ liệu hiện có tại vị trí đó. Ngoài ra còn có một phương thức `flushSfudBuffer` để ghi một bộ đệm chưa đầy, vì dữ liệu được ghi lại sẽ không phải là bội số chính xác của kích thước hạt, nên phần cuối của dữ liệu cần được ghi.

    > 💁 Phần cuối của dữ liệu sẽ ghi thêm dữ liệu không mong muốn, nhưng điều này không sao vì chỉ dữ liệu cần thiết sẽ được đọc.

### Nhiệm vụ - thiết lập ghi âm

1. Tạo một tệp mới trong thư mục `src` có tên là `config.h`.

1. Thêm đoạn mã sau vào đầu tệp này:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    Đoạn mã này thiết lập một số hằng số cho việc ghi âm.

    | Hằng số               | Giá trị | Mô tả |
    | --------------------- | ------: | - |
    | RATE                  | 16000   | Tần số mẫu cho âm thanh. 16.000 là 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4       | Độ dài của âm thanh cần ghi. Được đặt là 4 giây. Để ghi âm lâu hơn, tăng giá trị này. |
    | SAMPLES               | 64000   | Tổng số mẫu âm thanh sẽ được ghi lại. Được đặt là tần số mẫu * số giây |
    | BUFFER_SIZE           | 128044  | Kích thước của bộ đệm âm thanh để ghi. Âm thanh sẽ được ghi dưới dạng tệp WAV, bao gồm 44 byte tiêu đề, sau đó là 128.000 byte dữ liệu âm thanh (mỗi mẫu là 2 byte) |
    | ADC_BUF_LEN           | 1600    | Kích thước của các bộ đệm được sử dụng để ghi âm từ DMAC |

    > 💁 Nếu bạn thấy 4 giây là quá ngắn để yêu cầu bộ đếm thời gian, bạn có thể tăng giá trị `SAMPLE_LENGTH_SECONDS`, và tất cả các giá trị khác sẽ được tính toán lại.

1. Tạo một tệp mới trong thư mục `src` có tên là `mic.h`.

1. Thêm đoạn mã sau vào đầu tệp này:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    Đoạn mã này bao gồm một số tệp tiêu đề cần thiết, bao gồm các tệp tiêu đề `config.h` và `FlashWriter`.

1. Thêm đoạn mã sau để định nghĩa một lớp `Mic` có thể ghi từ micro:

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

    Lớp này hiện chỉ có một vài trường để theo dõi xem việc ghi âm đã bắt đầu hay chưa, và liệu một bản ghi đã sẵn sàng để sử dụng hay chưa. Khi DMAC được thiết lập, nó liên tục ghi vào các bộ đệm bộ nhớ, vì vậy cờ `_isRecording` xác định liệu các bộ đệm này có nên được xử lý hay bỏ qua. Cờ `_isRecordingReady` sẽ được đặt khi 4 giây âm thanh cần thiết đã được ghi lại. Trường `_writer` được sử dụng để lưu dữ liệu âm thanh vào bộ nhớ flash.

    Một biến toàn cục sau đó được khai báo cho một thể hiện của lớp `Mic`.

1. Thêm đoạn mã sau vào phần `private` của lớp `Mic`:

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

    Đoạn mã này định nghĩa một phương thức `configureDmaAdc` để cấu hình DMAC, kết nối nó với ADC và thiết lập để điền vào hai bộ đệm xen kẽ, `_adc_buf_0` và `_adc_buf_1`.

    > 💁 Một trong những nhược điểm của phát triển vi điều khiển là sự phức tạp của mã cần thiết để tương tác với phần cứng, vì mã của bạn chạy ở mức rất thấp, tương tác trực tiếp với phần cứng. Mã này phức tạp hơn so với những gì bạn sẽ viết cho một máy tính đơn bo hoặc máy tính để bàn vì không có hệ điều hành hỗ trợ. Có một số thư viện có sẵn có thể đơn giản hóa điều này, nhưng vẫn có rất nhiều sự phức tạp.

1. Bên dưới đoạn mã này, thêm đoạn mã sau:

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

    Đoạn mã này định nghĩa tiêu đề WAV dưới dạng một cấu trúc chiếm 44 byte bộ nhớ. Nó ghi thông tin chi tiết vào tiêu đề về tần số, kích thước và số kênh của tệp âm thanh. Tiêu đề này sau đó được ghi vào bộ nhớ flash.

1. Bên dưới đoạn mã này, thêm đoạn mã sau để khai báo một phương thức được gọi khi các bộ đệm âm thanh sẵn sàng để xử lý:

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

    Các bộ đệm âm thanh là các mảng số nguyên 16-bit chứa âm thanh từ ADC. ADC trả về các giá trị không dấu 12-bit (0-1023), vì vậy các giá trị này cần được chuyển đổi thành các giá trị có dấu 16-bit, sau đó chuyển đổi thành 2 byte để lưu trữ dưới dạng dữ liệu nhị phân thô.

    Các byte này được ghi vào các bộ đệm bộ nhớ flash. Việc ghi bắt đầu từ chỉ số 44 - đây là độ lệch từ 44 byte đã được ghi dưới dạng tiêu đề tệp WAV. Khi tất cả các byte cần thiết cho độ dài âm thanh yêu cầu đã được ghi lại, dữ liệu còn lại sẽ được ghi vào bộ nhớ flash.

1. Trong phần `public` của lớp `Mic`, thêm đoạn mã sau:

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

    Đoạn mã này sẽ được DMAC gọi để thông báo cho mã của bạn xử lý các bộ đệm. Nó kiểm tra xem có dữ liệu để xử lý hay không, và gọi phương thức `audioCallback` với bộ đệm tương ứng.

1. Bên ngoài lớp, sau khai báo `Mic mic;`, thêm đoạn mã sau:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    Hàm `DMAC_1_Handler` sẽ được DMAC gọi khi các bộ đệm sẵn sàng để xử lý. Hàm này được tìm theo tên, vì vậy chỉ cần tồn tại để được gọi.

1. Thêm hai phương thức sau vào phần `public` của lớp `Mic`:

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

    Phương thức `init` chứa mã để khởi tạo lớp `Mic`. Phương thức này thiết lập điện áp chính xác cho chân Mic, thiết lập trình ghi bộ nhớ flash, ghi tiêu đề tệp WAV, và cấu hình DMAC. Phương thức `reset` đặt lại bộ nhớ flash và ghi lại tiêu đề sau khi âm thanh đã được ghi và sử dụng.

### Nhiệm vụ - ghi âm

1. Trong tệp `main.cpp`, thêm chỉ thị `include` cho tệp tiêu đề `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. Trong hàm `setup`, khởi tạo nút C. Việc ghi âm sẽ bắt đầu khi nút này được nhấn và tiếp tục trong 4 giây:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. Bên dưới đoạn mã này, khởi tạo micro, sau đó in ra console rằng âm thanh đã sẵn sàng để ghi:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. Phía trên hàm `loop`, định nghĩa một hàm để xử lý âm thanh đã ghi. Hiện tại hàm này không làm gì, nhưng sau này trong bài học, nó sẽ gửi âm thanh để chuyển đổi thành văn bản:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. Thêm đoạn mã sau vào hàm `loop`:

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

    Đoạn mã này kiểm tra nút C, và nếu nút này được nhấn và việc ghi âm chưa bắt đầu, thì trường `_isRecording` của lớp `Mic` được đặt thành true. Điều này sẽ khiến phương thức `audioCallback` của lớp `Mic` lưu trữ âm thanh cho đến khi 4 giây đã được ghi lại. Khi 4 giây âm thanh đã được ghi lại, trường `_isRecording` được đặt thành false, và trường `_isRecordingReady` được đặt thành true. Trường này sau đó được kiểm tra trong hàm `loop`, và khi đúng, hàm `processAudio` được gọi, sau đó lớp mic được đặt lại.

1. Biên dịch mã này, tải nó lên Wio Terminal của bạn và kiểm tra qua serial monitor. Nhấn nút C (nút ở phía bên trái, gần công tắc nguồn nhất), và nói. 4 giây âm thanh sẽ được ghi lại.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 Bạn có thể tìm thấy mã này trong thư mục [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
Chương trình ghi âm của bạn đã thành công!

---

**Tuyên bố miễn trừ trách nhiệm**:  
Tài liệu này đã được dịch bằng dịch vụ dịch thuật AI [Co-op Translator](https://github.com/Azure/co-op-translator). Mặc dù chúng tôi cố gắng đảm bảo độ chính xác, xin lưu ý rằng các bản dịch tự động có thể chứa lỗi hoặc không chính xác. Tài liệu gốc bằng ngôn ngữ bản địa nên được coi là nguồn thông tin chính thức. Đối với các thông tin quan trọng, khuyến nghị sử dụng dịch vụ dịch thuật chuyên nghiệp bởi con người. Chúng tôi không chịu trách nhiệm cho bất kỳ sự hiểu lầm hoặc diễn giải sai nào phát sinh từ việc sử dụng bản dịch này.