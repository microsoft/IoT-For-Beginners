<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-25T22:47:13+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "fa"
}
-->
# ضبط صدا - Wio Terminal

در این بخش از درس، شما کدی خواهید نوشت تا بتوانید صدا را روی Wio Terminal ضبط کنید. ضبط صدا توسط یکی از دکمه‌های بالای Wio Terminal کنترل خواهد شد.

## برنامه‌ریزی دستگاه برای ضبط صدا

شما می‌توانید با استفاده از کد C++ صدا را از میکروفون ضبط کنید. Wio Terminal تنها 192KB رم دارد، که برای ضبط بیش از چند ثانیه صدا کافی نیست. همچنین این دستگاه دارای 4MB حافظه فلش است که می‌توان از آن برای ذخیره صدای ضبط‌شده استفاده کرد.

میکروفون داخلی یک سیگنال آنالوگ را ضبط می‌کند که به سیگنال دیجیتال تبدیل می‌شود تا Wio Terminal بتواند از آن استفاده کند. هنگام ضبط صدا، داده‌ها باید در زمان مناسب ضبط شوند - برای مثال، برای ضبط صدا با نرخ 16KHz، صدا باید دقیقاً 16,000 بار در ثانیه و با فاصله‌های مساوی بین هر نمونه ضبط شود. به جای استفاده از کد خود برای این کار، می‌توانید از کنترل‌کننده دسترسی مستقیم به حافظه (DMAC) استفاده کنید. این یک مدار است که می‌تواند سیگنالی را از جایی دریافت کرده و به حافظه بنویسد، بدون اینکه کد شما که روی پردازنده اجرا می‌شود، مختل شود.

✅ اطلاعات بیشتر درباره DMA را در [صفحه دسترسی مستقیم به حافظه در ویکی‌پدیا](https://wikipedia.org/wiki/Direct_memory_access) بخوانید.

![صدا از میکروفون به ADC می‌رود و سپس به DMAC. این داده‌ها را به یک بافر می‌نویسد. وقتی این بافر پر شد، پردازش می‌شود و DMAC به بافر دوم می‌نویسد](../../../../../translated_images/fa/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC می‌تواند صدا را از ADC در فواصل ثابت ضبط کند، مانند 16,000 بار در ثانیه برای صدای 16KHz. این داده‌های ضبط‌شده را می‌تواند به یک بافر حافظه از پیش تخصیص‌یافته بنویسد، و وقتی این بافر پر شد، آن را برای پردازش در اختیار کد شما قرار دهد. استفاده از این حافظه ممکن است ضبط صدا را به تأخیر بیندازد، اما می‌توانید چندین بافر تنظیم کنید. DMAC به بافر 1 می‌نویسد، سپس وقتی پر شد، کد شما را برای پردازش بافر 1 مطلع می‌کند، در حالی که DMAC به بافر 2 می‌نویسد. وقتی بافر 2 پر شد، کد شما را مطلع می‌کند و دوباره به نوشتن در بافر 1 بازمی‌گردد. به این ترتیب، تا زمانی که هر بافر را در زمانی کمتر از زمان پر شدن آن پردازش کنید، هیچ داده‌ای از دست نخواهد رفت.

پس از ضبط هر بافر، می‌توان آن را به حافظه فلش نوشت. حافظه فلش باید با استفاده از آدرس‌های تعریف‌شده نوشته شود، مشخص کند که کجا و چه مقدار بنویسد، مشابه به‌روزرسانی یک آرایه بایت در حافظه. حافظه فلش دارای گرانولاریتی است، به این معنی که عملیات پاک کردن و نوشتن نه تنها باید اندازه ثابتی داشته باشد، بلکه باید با آن اندازه هماهنگ باشد. برای مثال، اگر گرانولاریتی 4096 بایت باشد و شما درخواست پاک کردن در آدرس 4200 را بدهید، ممکن است تمام داده‌ها از آدرس 4096 تا 8192 پاک شود. این بدان معناست که وقتی داده‌های صوتی را به حافظه فلش می‌نویسید، باید در قطعاتی با اندازه صحیح باشد.

### وظیفه - پیکربندی حافظه فلش

1. یک پروژه جدید Wio Terminal با استفاده از PlatformIO ایجاد کنید. این پروژه را `smart-timer` نام‌گذاری کنید. کدی را در تابع `setup` اضافه کنید تا پورت سریال را پیکربندی کند.

1. وابستگی‌های کتابخانه زیر را به فایل `platformio.ini` اضافه کنید تا به حافظه فلش دسترسی داشته باشید:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. فایل `main.cpp` را باز کنید و دستور `include` زیر را برای کتابخانه حافظه فلش به بالای فایل اضافه کنید:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD مخفف Serial Flash Universal Driver است و یک کتابخانه طراحی‌شده برای کار با تمام چیپ‌های حافظه فلش است.

1. در تابع `setup`، کد زیر را اضافه کنید تا کتابخانه ذخیره‌سازی فلش را تنظیم کنید:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    این کد تا زمانی که کتابخانه SFUD مقداردهی اولیه شود، حلقه می‌زند، سپس خواندن سریع را فعال می‌کند. حافظه فلش داخلی می‌تواند با استفاده از یک رابط سریال محیطی صف‌بندی‌شده (QSPI) دسترسی پیدا کند، نوعی کنترل‌کننده SPI که امکان دسترسی مداوم از طریق صف را با حداقل استفاده از پردازنده فراهم می‌کند. این باعث می‌شود خواندن و نوشتن در حافظه فلش سریع‌تر شود.

1. یک فایل جدید در پوشه `src` ایجاد کنید و آن را `flash_writer.h` نام‌گذاری کنید.

1. موارد زیر را به بالای این فایل اضافه کنید:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    این کد شامل برخی فایل‌های هدر مورد نیاز، از جمله فایل هدر کتابخانه SFUD برای تعامل با حافظه فلش است.

1. یک کلاس در این فایل هدر جدید به نام `FlashWriter` تعریف کنید:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. در بخش `private`، کد زیر را اضافه کنید:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    این کد برخی فیلدها را برای بافری که برای ذخیره داده‌ها قبل از نوشتن آن‌ها در حافظه فلش استفاده می‌شود، تعریف می‌کند. یک آرایه بایت به نام `_sfudBuffer` وجود دارد که داده‌ها در آن نوشته می‌شوند، و وقتی این بافر پر شد، داده‌ها در حافظه فلش نوشته می‌شوند. فیلد `_sfudBufferPos` مکان فعلی برای نوشتن در این بافر را ذخیره می‌کند، و `_sfudBufferWritePos` مکان در حافظه فلش برای نوشتن را ذخیره می‌کند. `_flash` یک اشاره‌گر به حافظه فلش برای نوشتن است - برخی میکروکنترلرها دارای چندین چیپ حافظه فلش هستند.

1. متد زیر را به بخش `public` برای مقداردهی اولیه این کلاس اضافه کنید:

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

    این کد حافظه فلش روی Wio Terminal را برای نوشتن پیکربندی می‌کند و بافرها را بر اساس اندازه گرانولاریتی حافظه فلش تنظیم می‌کند. این کد در یک متد `init` قرار دارد، نه یک سازنده، زیرا باید پس از تنظیم حافظه فلش در تابع `setup` فراخوانی شود.

1. کد زیر را به بخش `public` اضافه کنید:

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

    این کد متدهایی را برای نوشتن بایت‌ها در سیستم ذخیره‌سازی فلش تعریف می‌کند. این کار با نوشتن در یک بافر در حافظه انجام می‌شود که اندازه مناسب برای حافظه فلش دارد، و وقتی این بافر پر شد، در حافظه فلش نوشته می‌شود و هر داده موجود در آن مکان پاک می‌شود. همچنین یک متد `flushSfudBuffer` وجود دارد تا یک بافر ناقص را بنویسد، زیرا داده‌های ضبط‌شده دقیقاً مضرب‌های اندازه گرانولاریتی نخواهند بود، بنابراین بخش پایانی داده‌ها باید نوشته شود.

    > 💁 بخش پایانی داده‌ها داده‌های اضافی ناخواسته را می‌نویسد، اما این مشکلی ندارد زیرا فقط داده‌های مورد نیاز خوانده خواهند شد.

### وظیفه - تنظیم ضبط صدا

1. یک فایل جدید در پوشه `src` ایجاد کنید و آن را `config.h` نام‌گذاری کنید.

1. موارد زیر را به بالای این فایل اضافه کنید:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    این کد برخی ثابت‌ها را برای ضبط صدا تنظیم می‌کند.

    | ثابت                 | مقدار  | توضیحات |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | نرخ نمونه‌برداری برای صدا. 16,000 برابر با 16KHz است |
    | SAMPLE_LENGTH_SECONDS | 4      | طول صدای ضبط‌شده. این مقدار به 4 ثانیه تنظیم شده است. برای ضبط صدای طولانی‌تر، این مقدار را افزایش دهید. |
    | SAMPLES               | 64000  | تعداد کل نمونه‌های صوتی که ضبط خواهند شد. تنظیم‌شده به نرخ نمونه‌برداری * تعداد ثانیه‌ها |
    | BUFFER_SIZE           | 128044 | اندازه بافر صوتی برای ضبط. صدا به‌صورت فایل WAV ضبط خواهد شد، که شامل 44 بایت هدر و سپس 128,000 بایت داده صوتی (هر نمونه 2 بایت است) |
    | ADC_BUF_LEN           | 1600   | اندازه بافرهایی که برای ضبط صدا از DMAC استفاده می‌شوند |

    > 💁 اگر 4 ثانیه برای درخواست تایمر خیلی کوتاه است، می‌توانید مقدار `SAMPLE_LENGTH_SECONDS` را افزایش دهید و تمام مقادیر دیگر به‌طور خودکار محاسبه خواهند شد.

1. یک فایل جدید در پوشه `src` ایجاد کنید و آن را `mic.h` نام‌گذاری کنید.

1. موارد زیر را به بالای این فایل اضافه کنید:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    این کد شامل برخی فایل‌های هدر مورد نیاز، از جمله فایل‌های هدر `config.h` و `FlashWriter` است.

1. موارد زیر را برای تعریف یک کلاس `Mic` که می‌تواند از میکروفون ضبط کند، اضافه کنید:

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

    این کلاس در حال حاضر فقط چند فیلد دارد تا مشخص کند آیا ضبط شروع شده است یا خیر، و آیا ضبط آماده استفاده است یا خیر. وقتی DMAC تنظیم شود، به‌طور مداوم به بافرهای حافظه می‌نویسد، بنابراین فلگ `_isRecording` تعیین می‌کند که آیا این بافرها باید پردازش شوند یا نادیده گرفته شوند. فلگ `_isRecordingReady` زمانی تنظیم می‌شود که 4 ثانیه صدای مورد نیاز ضبط شده باشد. فیلد `_writer` برای ذخیره داده‌های صوتی در حافظه فلش استفاده می‌شود.

    یک متغیر جهانی برای یک نمونه از کلاس `Mic` اعلام می‌شود.

1. کد زیر را به بخش `private` کلاس `Mic` اضافه کنید:

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

    این کد یک متد `configureDmaAdc` را تعریف می‌کند که DMAC را پیکربندی می‌کند، آن را به ADC متصل می‌کند و تنظیم می‌کند تا دو بافر متناوب `_adc_buf_0` و `_adc_buf_1` را پر کند.

    > 💁 یکی از معایب توسعه میکروکنترلر پیچیدگی کدی است که برای تعامل با سخت‌افزار نیاز است، زیرا کد شما در سطح بسیار پایین اجرا می‌شود و مستقیماً با سخت‌افزار تعامل دارد. این کد پیچیده‌تر از چیزی است که برای یک کامپیوتر تک‌برد یا کامپیوتر دسکتاپ می‌نویسید، زیرا سیستم‌عاملی وجود ندارد که کمک کند. برخی کتابخانه‌ها موجود هستند که می‌توانند این کار را ساده‌تر کنند، اما هنوز هم پیچیدگی زیادی وجود دارد.

1. کد زیر را در زیر این بخش اضافه کنید:

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

    این کد هدر WAV را به‌عنوان یک ساختار تعریف می‌کند که 44 بایت حافظه اشغال می‌کند. جزئیاتی درباره نرخ فایل صوتی، اندازه و تعداد کانال‌ها را در آن می‌نویسد. این هدر سپس در حافظه فلش نوشته می‌شود.

1. کد زیر را در زیر این بخش اضافه کنید تا یک متد برای فراخوانی زمانی که بافرهای صوتی آماده پردازش هستند، اعلام شود:

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

    بافرهای صوتی آرایه‌هایی از اعداد صحیح 16 بیتی هستند که صدا را از ADC دریافت می‌کنند. ADC مقادیر 12 بیتی بدون علامت (0-1023) را برمی‌گرداند، بنابراین این مقادیر باید به مقادیر 16 بیتی با علامت تبدیل شوند و سپس به 2 بایت تبدیل شوند تا به‌صورت داده‌های باینری خام ذخیره شوند.

    این بایت‌ها در بافرهای حافظه فلش نوشته می‌شوند. نوشتن از شاخص 44 شروع می‌شود - این آفست از 44 بایت نوشته‌شده به‌عنوان هدر فایل WAV است. وقتی تمام بایت‌های مورد نیاز برای طول صدای مورد نظر ضبط شدند، داده‌های باقی‌مانده در حافظه فلش نوشته می‌شوند.

1. کد زیر را به بخش `public` کلاس `Mic` اضافه کنید:

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

    این کد توسط DMAC فراخوانی خواهد شد تا به کد شما بگوید که بافرها را پردازش کند. این کد بررسی می‌کند که داده‌ای برای پردازش وجود دارد و متد `audioCallback` را با بافر مربوطه فراخوانی می‌کند.

1. خارج از کلاس، پس از اعلام `Mic mic;`، کد زیر را اضافه کنید:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` توسط DMAC فراخوانی خواهد شد وقتی بافرها آماده پردازش باشند. این تابع با نام پیدا می‌شود، بنابراین فقط باید وجود داشته باشد تا فراخوانی شود.

1. دو متد زیر را به بخش `public` کلاس `Mic` اضافه کنید:

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

    متد `init` شامل کدی برای مقداردهی اولیه کلاس `Mic` است. این متد ولتاژ صحیح برای پین میکروفون را تنظیم می‌کند، نویسنده حافظه فلش را تنظیم می‌کند، هدر فایل WAV را می‌نویسد و DMAC را پیکربندی می‌کند. متد `reset` حافظه فلش را بازنشانی می‌کند و هدر را پس از ضبط و استفاده از صدا دوباره می‌نویسد.

### وظیفه - ضبط صدا

1. در فایل `main.cpp`، یک دستور `include` برای فایل هدر `mic.h` اضافه کنید:

    ```cpp
    #include "mic.h"
    ```

1. در تابع `setup`، دکمه C را مقداردهی اولیه کنید. ضبط صدا زمانی شروع خواهد شد که این دکمه فشار داده شود و به مدت 4 ثانیه ادامه خواهد داشت:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. در زیر این بخش، میکروفون را مقداردهی اولیه کنید، سپس در کنسول چاپ کنید که صدا آماده ضبط است:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. بالای تابع `loop`، یک تابع برای پردازش صدای ضبط‌شده تعریف کنید. فعلاً این تابع کاری انجام نمی‌دهد، اما بعداً در این درس صدا را برای تبدیل به متن ارسال خواهد کرد:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. کد زیر را به تابع `loop` اضافه کنید:

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

    این کد دکمه C را بررسی می‌کند، و اگر این دکمه فشار داده شود و ضبط شروع نشده باشد، فلگ `_isRecording` کلاس `Mic` به true تنظیم می‌شود. این باعث می‌شود متد `audioCallback` کلاس `Mic` صدا را ذخیره کند تا زمانی که 4 ثانیه ضبط شود. وقتی 4 ثانیه صدا ضبط شد، فلگ `_isRecording` به false تنظیم می‌شود و فلگ `_isRecordingReady` به true تنظیم می‌شود. این فلگ سپس در تابع `loop` بررسی می‌شود، و وقتی true باشد، تابع `processAudio` فراخوانی می‌شود و سپس کلاس mic بازنشانی می‌شود.

1. این کد را بسازید، آن را روی Wio Terminal آپلود کنید و از طریق مانیتور سریال آن را آزمایش کنید. دکمه C (دکمه سمت چپ، نزدیک به کلید پاور) را فشار دهید و صحبت کنید. 4 ثانیه صدا ضبط خواهد شد.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 شما می‌توانید این کد را در پوشه [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) پیدا کنید.
😀 برنامه ضبط صدای شما موفقیت‌آمیز بود!

**سلب مسئولیت**:  
این سند با استفاده از سرویس ترجمه هوش مصنوعی [Co-op Translator](https://github.com/Azure/co-op-translator) ترجمه شده است. در حالی که ما تلاش می‌کنیم دقت را حفظ کنیم، لطفاً توجه داشته باشید که ترجمه‌های خودکار ممکن است شامل خطاها یا نادرستی‌ها باشند. سند اصلی به زبان اصلی آن باید به عنوان منبع معتبر در نظر گرفته شود. برای اطلاعات حساس، توصیه می‌شود از ترجمه حرفه‌ای انسانی استفاده کنید. ما مسئولیتی در قبال سوء تفاهم‌ها یا تفسیرهای نادرست ناشی از استفاده از این ترجمه نداریم.