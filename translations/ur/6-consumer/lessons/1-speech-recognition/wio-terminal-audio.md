<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T00:25:44+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "ur"
}
-->
# آڈیو کیپچر - وائیو ٹرمینل

اس سبق کے اس حصے میں، آپ کوڈ لکھیں گے تاکہ اپنے وائیو ٹرمینل پر آڈیو کیپچر کر سکیں۔ آڈیو کیپچر وائیو ٹرمینل کے اوپر موجود ایک بٹن کے ذریعے کنٹرول کیا جائے گا۔

## ڈیوائس کو آڈیو کیپچر کرنے کے لیے پروگرام کریں

آپ مائیکروفون سے آڈیو C++ کوڈ کے ذریعے کیپچر کر سکتے ہیں۔ وائیو ٹرمینل میں صرف 192KB کی RAM ہے، جو چند سیکنڈ سے زیادہ آڈیو کیپچر کرنے کے لیے کافی نہیں ہے۔ اس میں 4MB کی فلیش میموری بھی ہے، جسے استعمال کیا جا سکتا ہے، اور کیپچر شدہ آڈیو کو فلیش میموری میں محفوظ کیا جا سکتا ہے۔

بلٹ ان مائیکروفون ایک اینالاگ سگنل کیپچر کرتا ہے، جو ڈیجیٹل سگنل میں تبدیل ہوتا ہے جسے وائیو ٹرمینل استعمال کر سکتا ہے۔ آڈیو کیپچر کرتے وقت، ڈیٹا کو صحیح وقت پر کیپچر کرنا ضروری ہے - مثال کے طور پر، 16KHz پر آڈیو کیپچر کرنے کے لیے، آڈیو کو بالکل 16,000 بار فی سیکنڈ کیپچر کرنا ہوگا، ہر سیمپل کے درمیان برابر وقفوں کے ساتھ۔ آپ کے کوڈ کے ذریعے ایسا کرنے کے بجائے، آپ ڈائریکٹ میموری ایکسیس کنٹرولر (DMAC) استعمال کر سکتے ہیں۔ یہ ایک سرکٹ ہے جو کسی جگہ سے سگنل کیپچر کر سکتا ہے اور میموری میں لکھ سکتا ہے، بغیر آپ کے پروسیسر پر چلنے والے کوڈ میں خلل ڈالے۔

✅ DMAC کے بارے میں مزید پڑھیں [ویکیپیڈیا پر ڈائریکٹ میموری ایکسیس صفحہ](https://wikipedia.org/wiki/Direct_memory_access)۔

![مائیک سے آڈیو ADC میں جاتا ہے پھر DMAC میں۔ یہ ایک بفر میں لکھتا ہے۔ جب یہ بفر بھر جاتا ہے، تو اسے پروسیس کیا جاتا ہے اور DMAC دوسرے بفر میں لکھتا ہے](../../../../../translated_images/ur/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC ADC سے آڈیو کو مقررہ وقفوں پر کیپچر کر سکتا ہے، جیسے 16KHz آڈیو کے لیے فی سیکنڈ 16,000 بار۔ یہ کیپچر شدہ ڈیٹا کو پہلے سے مختص میموری بفر میں لکھ سکتا ہے، اور جب یہ بھر جائے تو آپ کے کوڈ کو پروسیس کرنے کے لیے دستیاب کر سکتا ہے۔ اس میموری کا استعمال آڈیو کیپچر میں تاخیر کر سکتا ہے، لیکن آپ متعدد بفرز سیٹ کر سکتے ہیں۔ DMAC بفر 1 میں لکھتا ہے، پھر جب یہ بھر جاتا ہے، آپ کے کوڈ کو بفر 1 پروسیس کرنے کے لیے مطلع کرتا ہے، جبکہ DMAC بفر 2 میں لکھتا ہے۔ جب بفر 2 بھر جاتا ہے، تو یہ آپ کے کوڈ کو مطلع کرتا ہے، اور واپس بفر 1 میں لکھنے کے لیے جاتا ہے۔ اس طرح جب تک آپ ہر بفر کو بھرنے میں لگنے والے وقت سے کم وقت میں پروسیس کرتے ہیں، آپ کوئی ڈیٹا نہیں کھوئیں گے۔

جب ہر بفر کیپچر ہو جائے، تو اسے فلیش میموری میں لکھا جا سکتا ہے۔ فلیش میموری کو مخصوص ایڈریسز کا استعمال کرتے ہوئے لکھا جانا چاہیے، یہ بتاتے ہوئے کہ کہاں لکھنا ہے اور کتنی بڑی مقدار میں لکھنا ہے، بالکل میموری میں بائٹس کے ایک ارے کو اپ ڈیٹ کرنے کی طرح۔ فلیش میموری میں گرینولیریٹی ہوتی ہے، یعنی مٹانے اور لکھنے کے آپریشنز نہ صرف ایک مقررہ سائز کے ہونے پر منحصر ہوتے ہیں بلکہ اس سائز کے مطابق ہونے پر بھی۔ مثال کے طور پر، اگر گرینولیریٹی 4096 بائٹس ہے اور آپ ایڈریس 4200 پر مٹانے کی درخواست کرتے ہیں، تو یہ ایڈریس 4096 سے 8192 تک کا تمام ڈیٹا مٹا سکتا ہے۔ اس کا مطلب ہے کہ جب آپ آڈیو ڈیٹا کو فلیش میموری میں لکھتے ہیں، تو اسے صحیح سائز کے چنکس میں ہونا چاہیے۔

### کام - فلیش میموری کو ترتیب دیں

1. ایک نیا وائیو ٹرمینل پروجیکٹ پلیٹ فارم آئی او کا استعمال کرتے ہوئے بنائیں۔ اس پروجیکٹ کا نام `smart-timer` رکھیں۔ سیریل پورٹ کو ترتیب دینے کے لیے `setup` فنکشن میں کوڈ شامل کریں۔

1. فلیش میموری تک رسائی فراہم کرنے کے لیے درج ذیل لائبریری ڈیپینڈینسیز کو `platformio.ini` فائل میں شامل کریں:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` فائل کھولیں اور فلیش میموری لائبریری کے لیے درج ذیل انکلوڈ ڈائریکٹو کو فائل کے اوپر شامل کریں:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD کا مطلب ہے سیریل فلیش یونیورسل ڈرائیور، اور یہ ایک لائبریری ہے جو تمام فلیش میموری چپس کے ساتھ کام کرنے کے لیے ڈیزائن کی گئی ہے۔

1. `setup` فنکشن میں، فلیش اسٹوریج لائبریری کو ترتیب دینے کے لیے درج ذیل کوڈ شامل کریں:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    یہ اس وقت تک لوپ کرتا ہے جب تک SFUD لائبریری انیشیلائز نہ ہو جائے، پھر تیز رفتار پڑھنے کو آن کرتا ہے۔ بلٹ ان فلیش میموری کو کیوڈ سیریل پیریفرل انٹرفیس (QSPI) کا استعمال کرتے ہوئے رسائی حاصل کی جا سکتی ہے، جو SPI کنٹرولر کی ایک قسم ہے جو کم سے کم پروسیسر کے استعمال کے ساتھ قطار کے ذریعے مسلسل رسائی کی اجازت دیتا ہے۔ یہ فلیش میموری کو پڑھنے اور لکھنے کو تیز تر بناتا ہے۔

1. `src` فولڈر میں ایک نئی فائل بنائیں جس کا نام `flash_writer.h` ہو۔

1. اس فائل کے اوپر درج ذیل شامل کریں:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    اس میں کچھ ضروری ہیڈر فائلز شامل ہیں، جن میں فلیش میموری کے ساتھ تعامل کے لیے SFUD لائبریری کی ہیڈر فائل شامل ہے۔

1. اس نئی ہیڈر فائل میں `FlashWriter` نامی کلاس کی تعریف کریں:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` سیکشن میں درج ذیل کوڈ شامل کریں:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    یہ ڈیٹا کو فلیش میموری میں لکھنے سے پہلے اسٹور کرنے کے لیے استعمال کرنے کے لیے بفر کے لیے کچھ فیلڈز کی وضاحت کرتا ہے۔ ایک بائٹ ارے `_sfudBuffer` ہے، جس میں ڈیٹا لکھا جاتا ہے، اور جب یہ بھر جاتا ہے، تو ڈیٹا فلیش میموری میں لکھا جاتا ہے۔ `_sfudBufferPos` فیلڈ اس بفر میں لکھنے کے لیے موجودہ مقام کو اسٹور کرتا ہے، اور `_sfudBufferWritePos` فلیش میموری میں لکھنے کے مقام کو اسٹور کرتا ہے۔ `_flash` ایک پوائنٹر ہے جسے فلیش میموری میں لکھنا ہے - کچھ مائیکرو کنٹرولرز میں متعدد فلیش میموری چپس ہوتی ہیں۔

1. اس کلاس کو انیشیلائز کرنے کے لیے `public` سیکشن میں درج ذیل میتھڈ شامل کریں:

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

    یہ وائیو ٹرمینل پر فلیش میموری کو لکھنے کے لیے ترتیب دیتا ہے، اور فلیش میموری کے گرین سائز کی بنیاد پر بفرز کو سیٹ کرتا ہے۔ یہ ایک `init` میتھڈ میں ہے، کنسٹرکٹر کے بجائے، کیونکہ اسے `setup` فنکشن میں فلیش میموری سیٹ اپ ہونے کے بعد کال کرنے کی ضرورت ہے۔

1. `public` سیکشن میں درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ بائٹس کو فلیش اسٹوریج سسٹم میں لکھنے کے لیے میتھڈز کی وضاحت کرتا ہے۔ یہ ایک ان میموری بفر میں لکھ کر کام کرتا ہے جو فلیش میموری کے لیے صحیح سائز کا ہوتا ہے، اور جب یہ بھر جاتا ہے، تو یہ فلیش میموری میں لکھا جاتا ہے، اس مقام پر موجود کسی بھی موجودہ ڈیٹا کو مٹا دیتا ہے۔ ایک `flushSfudBuffer` بھی ہے تاکہ ایک نامکمل بفر لکھا جا سکے، کیونکہ کیپچر کیا گیا ڈیٹا گرین سائز کے عین مطابق ضرب نہیں ہوگا، اس لیے ڈیٹا کے آخری حصے کو لکھنے کی ضرورت ہے۔

    > 💁 ڈیٹا کے آخری حصے میں اضافی غیر ضروری ڈیٹا لکھا جائے گا، لیکن یہ ٹھیک ہے کیونکہ صرف مطلوبہ ڈیٹا ہی پڑھا جائے گا۔

### کام - آڈیو کیپچر سیٹ اپ کریں

1. `src` فولڈر میں ایک نئی فائل بنائیں جس کا نام `config.h` ہو۔

1. اس فائل کے اوپر درج ذیل شامل کریں:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    یہ کوڈ آڈیو کیپچر کے لیے کچھ کانسٹینٹس سیٹ کرتا ہے۔

    | کانسٹینٹ              | ویلیو  | وضاحت |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | آڈیو کے لیے سیمپل ریٹ۔ 16,000 یعنی 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | آڈیو کیپچر کی لمبائی۔ یہ 4 سیکنڈ پر سیٹ ہے۔ لمبے آڈیو ریکارڈ کرنے کے لیے، اس کو بڑھائیں۔ |
    | SAMPLES               | 64000  | کل آڈیو سیمپلز کی تعداد جو کیپچر کی جائے گی۔ سیمپل ریٹ * سیکنڈز کی تعداد پر سیٹ کریں |
    | BUFFER_SIZE           | 128044 | آڈیو بفر کا سائز کیپچر کرنے کے لیے۔ آڈیو کو WAV فائل کے طور پر کیپچر کیا جائے گا، جس میں 44 بائٹس کا ہیڈر ہوگا، پھر 128,000 بائٹس آڈیو ڈیٹا (ہر سیمپل 2 بائٹس ہے) |
    | ADC_BUF_LEN           | 1600   | بفرز کا سائز جو DMAC سے آڈیو کیپچر کرنے کے لیے استعمال ہوگا |

    > 💁 اگر آپ کو لگے کہ 4 سیکنڈ ٹائمر کی درخواست کے لیے بہت کم ہیں، تو آپ `SAMPLE_LENGTH_SECONDS` ویلیو کو بڑھا سکتے ہیں، اور باقی تمام ویلیوز دوبارہ کیلکولیٹ ہو جائیں گی۔

1. `src` فولڈر میں ایک نئی فائل بنائیں جس کا نام `mic.h` ہو۔

1. اس فائل کے اوپر درج ذیل شامل کریں:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    اس میں کچھ ضروری ہیڈر فائلز شامل ہیں، جن میں `config.h` اور `FlashWriter` ہیڈر فائلز شامل ہیں۔

1. مائیکروفون سے کیپچر کرنے کے لیے ایک `Mic` کلاس کی تعریف کریں:

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

    اس کلاس میں فی الحال صرف چند فیلڈز ہیں تاکہ ٹریک کیا جا سکے کہ ریکارڈنگ شروع ہوئی ہے یا نہیں، اور آیا ریکارڈنگ استعمال کے لیے تیار ہے یا نہیں۔ جب DMAC سیٹ اپ ہوتا ہے، تو یہ مسلسل میموری بفرز میں لکھتا ہے، اس لیے `_isRecording` فلیگ یہ طے کرتا ہے کہ ان کو پروسیس کیا جائے یا نظر انداز کیا جائے۔ `_isRecordingReady` فلیگ اس وقت سیٹ کیا جائے گا جب مطلوبہ 4 سیکنڈ کا آڈیو کیپچر ہو جائے۔ `_writer` فیلڈ آڈیو ڈیٹا کو فلیش میموری میں محفوظ کرنے کے لیے استعمال ہوتا ہے۔

    ایک گلوبل ویری ایبل پھر `Mic` کلاس کے ایک انسٹینس کے لیے ڈکلیئر کیا جاتا ہے۔

1. `Mic` کلاس کے `private` سیکشن میں درج ذیل کوڈ شامل کریں:

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

    یہ ایک `configureDmaAdc` میتھڈ کی وضاحت کرتا ہے جو DMAC کو ترتیب دیتا ہے، اسے ADC سے جوڑتا ہے اور اسے دو مختلف متبادل بفرز، `_adc_buf_0` اور `_adc_buf_0` کو پاپولیٹ کرنے کے لیے سیٹ کرتا ہے۔

    > 💁 مائیکرو کنٹرولر ڈیولپمنٹ کے نقصانات میں سے ایک ہارڈویئر کے ساتھ تعامل کے لیے درکار کوڈ کی پیچیدگی ہے، کیونکہ آپ کا کوڈ بہت کم سطح پر براہ راست ہارڈویئر کے ساتھ تعامل کرتا ہے۔ یہ کوڈ اس سے زیادہ پیچیدہ ہے جو آپ سنگل بورڈ کمپیوٹر یا ڈیسک ٹاپ کمپیوٹر کے لیے لکھیں گے کیونکہ یہاں کوئی آپریٹنگ سسٹم مدد کے لیے موجود نہیں ہے۔ کچھ لائبریریاں دستیاب ہیں جو اسے آسان بنا سکتی ہیں، لیکن پھر بھی بہت زیادہ پیچیدگی موجود ہے۔

1. اس کے نیچے درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ WAV ہیڈر کو ایک اسٹرک کے طور پر بیان کرتا ہے جو 44 بائٹس میموری لیتا ہے۔ یہ آڈیو فائل ریٹ، سائز، اور چینلز کے بارے میں تفصیلات اس میں لکھتا ہے۔ یہ ہیڈر پھر فلیش میموری میں لکھا جاتا ہے۔

1. اس کوڈ کے نیچے، آڈیو بفرز کے پروسیس ہونے کے لیے تیار ہونے پر کال کیے جانے والے میتھڈ کو ڈکلیئر کرنے کے لیے درج ذیل شامل کریں:

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

    آڈیو بفرز 16 بٹ انٹیجرز کے ارے ہیں جن میں ADC سے آڈیو ہوتا ہے۔ ADC 12 بٹ ان سائنڈ ویلیوز (0-1023) واپس کرتا ہے، اس لیے ان کو 16 بٹ سائنڈ ویلیوز میں تبدیل کرنے کی ضرورت ہے، اور پھر انہیں 2 بائٹس میں تبدیل کرنے کی ضرورت ہے تاکہ انہیں را بائنری ڈیٹا کے طور پر محفوظ کیا جا سکے۔

    یہ بائٹس فلیش میموری بفرز میں لکھی جاتی ہیں۔ لکھنا انڈیکس 44 پر شروع ہوتا ہے - یہ WAV فائل ہیڈر کے طور پر لکھے گئے 44 بائٹس سے آفسیٹ ہے۔ ایک بار جب مطلوبہ آڈیو لمبائی کے لیے درکار تمام بائٹس کیپچر ہو جائیں، تو باقی ڈیٹا فلیش میموری میں لکھا جاتا ہے۔

1. `Mic` کلاس کے `public` سیکشن میں درج ذیل کوڈ شامل کریں:

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

    یہ کوڈ DMAC کے ذریعے آپ کے کوڈ کو بفرز پروسیس کرنے کے لیے بتانے کے لیے کال کیا جائے گا۔ یہ چیک کرتا ہے کہ پروسیس کرنے کے لیے ڈیٹا موجود ہے، اور متعلقہ بفر کے ساتھ `audioCallback` میتھڈ کو کال کرتا ہے۔

1. کلاس کے باہر، `Mic mic;` ڈکلیریشن کے بعد، درج ذیل کوڈ شامل کریں:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` DMAC کے ذریعے اس وقت کال کیا جائے گا جب بفرز پروسیس کرنے کے لیے تیار ہوں۔ یہ فنکشن نام کے ذریعے پایا جاتا ہے، اس لیے صرف موجود ہونا کافی ہے تاکہ اسے کال کیا جا سکے۔

1. `Mic` کلاس کے `public` سیکشن میں درج ذیل دو میتھڈز شامل کریں:

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

    `init` میتھڈ `Mic` کلاس کو انیشیلائز کرنے کے لیے کوڈ پر مشتمل ہے۔ یہ میتھڈ مائیک پن کے لیے صحیح وولٹیج سیٹ کرتا ہے، فلیش میموری رائٹر کو سیٹ اپ کرتا ہے، WAV فائل ہیڈر لکھتا ہے، اور DMAC کو ترتیب دیتا ہے۔ `reset` میتھڈ فلیش میموری کو ری سیٹ کرتا ہے اور آڈیو کیپچر اور استعمال کے بعد ہیڈر کو دوبارہ لکھتا ہے۔

### کام - آڈیو کیپچر کریں

1. `main.cpp` فائل میں، `mic.h` ہیڈر فائل کے لیے ایک انکلوڈ ڈائریکٹو شامل کریں:

    ```cpp
    #include "mic.h"
    ```

1. `setup` فنکشن میں، C بٹن کو انیشیلائز کریں۔ آڈیو کیپچر اس بٹن کو دبانے پر شروع ہوگا، اور 4 سیکنڈ تک جاری رہے گا:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. اس کے نیچے، مائیکروفون کو انیشیلائز کریں، پھر کنسول پر پرنٹ کریں کہ آڈیو کیپچر کے لیے تیار ہے:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` فنکشن سے اوپر، کیپچر شدہ آڈیو کو پروسیس کرنے کے لیے ایک فنکشن ڈکلیئر کریں۔ فی الحال یہ کچھ نہیں کرتا، لیکن بعد میں اس سبق میں یہ تقریر کو متن میں تبدیل کرنے کے لیے بھیجے گا:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` فنکشن میں درج ذیل شامل کریں:

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

    یہ کوڈ C بٹن کو چیک کرتا ہے، اور اگر یہ دبایا گیا ہے اور ریکارڈنگ شروع نہیں ہوئی ہے، تو `Mic` کلاس کے `_isRecording` فیلڈ کو `true` پر سیٹ کرتا ہے۔ یہ `Mic` کلاس کے `audioCallback` میتھڈ کو 4 سیکنڈ تک آڈیو اسٹور کرنے کا سبب بنائے گا۔ ایک بار جب 4 سیکنڈ کا آڈیو کیپچر ہو جائے، `_isRecording` فیلڈ کو `false` پر سیٹ کیا جاتا ہے، اور `_isRecordingReady` فیلڈ کو `true` پر سیٹ کیا جاتا ہے۔ پھر `loop` فنکشن میں اس کی جانچ کی جاتی ہے، اور جب یہ `true` ہوتا ہے تو `processAudio` فنکشن کو کال کیا جاتا ہے، پھر مائیک کلاس کو ری سیٹ کیا جاتا ہے۔

1. اس کوڈ کو بنائیں، اسے اپنے وائیو ٹرمینل پر اپ لوڈ کریں اور
💁 آپ اس کوڈ کو [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) فولڈر میں تلاش کر سکتے ہیں۔
😀 آپ کا آڈیو ریکارڈنگ پروگرام کامیاب رہا!

---

**ڈسکلیمر**:  
یہ دستاویز AI ترجمہ سروس [Co-op Translator](https://github.com/Azure/co-op-translator) کا استعمال کرتے ہوئے ترجمہ کی گئی ہے۔ ہم درستگی کے لیے کوشش کرتے ہیں، لیکن براہ کرم آگاہ رہیں کہ خودکار ترجمے میں غلطیاں یا غیر درستیاں ہو سکتی ہیں۔ اصل دستاویز کو اس کی اصل زبان میں مستند ذریعہ سمجھا جانا چاہیے۔ اہم معلومات کے لیے، پیشہ ور انسانی ترجمہ کی سفارش کی جاتی ہے۔ ہم اس ترجمے کے استعمال سے پیدا ہونے والی کسی بھی غلط فہمی یا غلط تشریح کے ذمہ دار نہیں ہیں۔