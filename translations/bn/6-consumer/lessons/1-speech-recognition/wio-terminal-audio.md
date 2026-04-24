# অডিও ধারণ - Wio Terminal

এই পাঠের এই অংশে, আপনি Wio Terminal-এ অডিও ধারণ করার জন্য কোড লিখবেন। অডিও ধারণ Wio Terminal-এর উপরের একটি বোতামের মাধ্যমে নিয়ন্ত্রিত হবে।

## ডিভাইসটি অডিও ধারণের জন্য প্রোগ্রাম করুন

আপনি মাইক্রোফোন থেকে অডিও ধারণ করতে C++ কোড ব্যবহার করতে পারেন। Wio Terminal-এ মাত্র ১৯২KB RAM রয়েছে, যা কয়েক সেকেন্ডের বেশি অডিও ধারণ করার জন্য যথেষ্ট নয়। তবে এতে ৪MB ফ্ল্যাশ মেমোরি রয়েছে, যা ব্যবহার করা যেতে পারে, ধারণকৃত অডিও ফ্ল্যাশ মেমোরিতে সংরক্ষণ করার জন্য।

বিল্ট-ইন মাইক্রোফোন একটি অ্যানালগ সিগন্যাল ধারণ করে, যা ডিজিটাল সিগন্যাল-এ রূপান্তরিত হয় যা Wio Terminal ব্যবহার করতে পারে। অডিও ধারণ করার সময়, ডেটা সঠিক সময়ে ধারণ করতে হবে - উদাহরণস্বরূপ, ১৬KHz-এ অডিও ধারণ করতে হলে, প্রতি সেকেন্ডে ঠিক ১৬,০০০ বার সমান ব্যবধানে অডিও ধারণ করতে হবে। আপনার কোড ব্যবহার না করে এটি করার জন্য, আপনি ডাইরেক্ট মেমোরি অ্যাক্সেস কন্ট্রোলার (DMAC) ব্যবহার করতে পারেন। এটি এমন একটি সার্কিট যা প্রসেসরে আপনার কোডে বাধা না দিয়ে কোথাও থেকে সিগন্যাল ধারণ করে এবং মেমোরিতে লিখতে পারে।

✅ [ডাইরেক্ট মেমোরি অ্যাক্সেস সম্পর্কিত উইকিপিডিয়া পৃষ্ঠায়](https://wikipedia.org/wiki/Direct_memory_access) আরও পড়ুন।

![মাইক্রোফোন থেকে অডিও ADC-তে যায়, তারপর DMAC-এ। এটি একটি বাফারে লেখে। যখন এই বাফার পূর্ণ হয়, এটি প্রক্রিয়াকরণ করা হয় এবং DMAC দ্বিতীয় বাফারে লেখে](../../../../../translated_images/bn/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC নির্দিষ্ট ব্যবধানে ADC থেকে অডিও ধারণ করতে পারে, যেমন ১৬KHz অডিওর জন্য প্রতি সেকেন্ডে ১৬,০০০ বার। এটি ধারণকৃত ডেটা একটি পূর্বনির্ধারিত মেমোরি বাফারে লিখতে পারে, এবং যখন এটি পূর্ণ হয়, তখন এটি আপনার কোডে প্রক্রিয়াকরণের জন্য উপলব্ধ করে। এই মেমোরি ব্যবহার অডিও ধারণে বিলম্ব ঘটাতে পারে, তবে আপনি একাধিক বাফার সেট আপ করতে পারেন। DMAC বাফার ১-এ লেখে, তারপর যখন এটি পূর্ণ হয়, আপনার কোডকে বাফার ১ প্রক্রিয়াকরণ করতে জানায়, এবং DMAC বাফার ২-এ লেখে। যখন বাফার ২ পূর্ণ হয়, এটি আপনার কোডকে জানায় এবং আবার বাফার ১-এ লেখে। এভাবে, যতক্ষণ আপনি প্রতিটি বাফার প্রক্রিয়াকরণ করতে বাফার পূর্ণ হওয়ার সময়ের চেয়ে কম সময় নেন, ততক্ষণ আপনি কোনো ডেটা হারাবেন না।

প্রতিটি বাফার ধারণ করার পরে, এটি ফ্ল্যাশ মেমোরিতে লেখা যেতে পারে। ফ্ল্যাশ মেমোরি নির্ধারিত ঠিকানা ব্যবহার করে লিখতে হয়, কোথায় লিখতে হবে এবং কত বড় লিখতে হবে তা নির্দিষ্ট করে, যা মেমোরিতে একটি বাইটের অ্যারে আপডেট করার মতো। ফ্ল্যাশ মেমোরি গ্রানুলারিটি রয়েছে, যার মানে মুছে ফেলা এবং লেখার অপারেশনগুলি নির্দিষ্ট আকারের হতে হবে এবং সেই আকারের সাথে সামঞ্জস্যপূর্ণ হতে হবে। উদাহরণস্বরূপ, যদি গ্রানুলারিটি ৪০৯৬ বাইট হয় এবং আপনি ঠিকানা ৪২০০-এ একটি মুছে ফেলার অনুরোধ করেন, এটি ঠিকানা ৪০৯৬ থেকে ৮১৯২ পর্যন্ত সমস্ত ডেটা মুছে ফেলতে পারে। এর মানে হল যখন আপনি অডিও ডেটা ফ্ল্যাশ মেমোরিতে লিখবেন, এটি সঠিক আকারের টুকরোতে হতে হবে।

### কাজ - ফ্ল্যাশ মেমোরি কনফিগার করুন

১. PlatformIO ব্যবহার করে একটি নতুন Wio Terminal প্রকল্প তৈরি করুন। এই প্রকল্পটির নাম দিন `smart-timer`। `setup` ফাংশনে সিরিয়াল পোর্ট কনফিগার করার জন্য কোড যোগ করুন।

১. ফ্ল্যাশ মেমোরি অ্যাক্সেস করার জন্য `platformio.ini` ফাইলে নিম্নলিখিত লাইব্রেরি নির্ভরতা যোগ করুন:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

১. `main.cpp` ফাইলটি খুলুন এবং ফ্ল্যাশ মেমোরি লাইব্রেরির জন্য শীর্ষে নিম্নলিখিত ইনক্লুড ডিরেক্টিভ যোগ করুন:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD এর পূর্ণরূপ হল Serial Flash Universal Driver, এবং এটি এমন একটি লাইব্রেরি যা সমস্ত ফ্ল্যাশ মেমোরি চিপের সাথে কাজ করার জন্য ডিজাইন করা হয়েছে।

১. `setup` ফাংশনে, ফ্ল্যাশ স্টোরেজ লাইব্রেরি সেট আপ করার জন্য নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    এটি SFUD লাইব্রেরি ইনিশিয়ালাইজ না হওয়া পর্যন্ত লুপ করে, তারপর দ্রুত পড়ার ফাংশন চালু করে। বিল্ট-ইন ফ্ল্যাশ মেমোরি Queued Serial Peripheral Interface (QSPI) ব্যবহার করে অ্যাক্সেস করা যেতে পারে, যা একটি ধরনের SPI কন্ট্রোলার যা প্রসেসরের কম ব্যবহার করে একটি কিউ-এর মাধ্যমে ক্রমাগত অ্যাক্সেসের অনুমতি দেয়। এটি ফ্ল্যাশ মেমোরি পড়া এবং লেখার গতি বাড়ায়।

১. `src` ফোল্ডারে একটি নতুন ফাইল তৈরি করুন যার নাম দিন `flash_writer.h`।

১. এই ফাইলের শীর্ষে নিম্নলিখিত যোগ করুন:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    এটি কিছু প্রয়োজনীয় হেডার ফাইল অন্তর্ভুক্ত করে, যার মধ্যে ফ্ল্যাশ মেমোরি ইন্টারঅ্যাক্ট করার জন্য SFUD লাইব্রেরির হেডার ফাইল রয়েছে।

১. এই নতুন হেডার ফাইলে `FlashWriter` নামে একটি ক্লাস সংজ্ঞায়িত করুন:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

১. `private` সেকশনে নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    এটি ডেটা ফ্ল্যাশ মেমোরিতে লেখার আগে সংরক্ষণ করার জন্য ব্যবহৃত বাফারের জন্য কিছু ফিল্ড সংজ্ঞায়িত করে। `_sfudBuffer` নামে একটি বাইট অ্যারে রয়েছে যেখানে ডেটা লেখা হয়, এবং যখন এটি পূর্ণ হয়, ডেটা ফ্ল্যাশ মেমোরিতে লেখা হয়। `_sfudBufferPos` ফিল্ডটি এই বাফারে লেখার বর্তমান অবস্থান সংরক্ষণ করে, এবং `_sfudBufferWritePos` ফ্ল্যাশ মেমোরিতে লেখার অবস্থান সংরক্ষণ করে। `_flash` হল ফ্ল্যাশ মেমোরি লেখার জন্য একটি পয়েন্টার - কিছু মাইক্রোকন্ট্রোলারে একাধিক ফ্ল্যাশ মেমোরি চিপ থাকে।

১. এই ক্লাসের `public` সেকশনে নিম্নলিখিত মেথড যোগ করুন:

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

    এটি Wio Terminal-এ ফ্ল্যাশ মেমোরি লেখার জন্য কনফিগার করে এবং ফ্ল্যাশ মেমোরির গ্রেন সাইজের উপর ভিত্তি করে বাফার সেট আপ করে। এটি একটি `init` মেথডে রয়েছে, কারণ এটি `setup` ফাংশনে ফ্ল্যাশ মেমোরি সেট আপ করার পরে কল করতে হবে।

১. `public` সেকশনে নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডটি ফ্ল্যাশ স্টোরেজ সিস্টেমে বাইট লেখার মেথড সংজ্ঞায়িত করে। এটি একটি ইন-মেমোরি বাফারে লেখার মাধ্যমে কাজ করে যা ফ্ল্যাশ মেমোরির সঠিক আকারের জন্য উপযুক্ত, এবং যখন এটি পূর্ণ হয়, এটি ফ্ল্যাশ মেমোরিতে লেখা হয়, সেই অবস্থানে বিদ্যমান ডেটা মুছে ফেলে। এছাড়াও একটি `flushSfudBuffer` রয়েছে যা অসম্পূর্ণ বাফার লেখার জন্য ব্যবহৃত হয়, কারণ ধারণকৃত ডেটা ফ্ল্যাশ মেমোরির গ্রেন সাইজের সঠিক গুণিতক নাও হতে পারে, তাই ডেটার শেষ অংশটি লিখতে হবে।

    > 💁 ডেটার শেষ অংশটি অতিরিক্ত অবাঞ্ছিত ডেটা লিখবে, তবে এটি ঠিক আছে কারণ শুধুমাত্র প্রয়োজনীয় ডেটাই পড়া হবে।

### কাজ - অডিও ধারণ সেট আপ করুন

১. `src` ফোল্ডারে একটি নতুন ফাইল তৈরি করুন যার নাম দিন `config.h`।

১. এই ফাইলের শীর্ষে নিম্নলিখিত যোগ করুন:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    এই কোডটি অডিও ধারণের জন্য কিছু কনস্ট্যান্ট সেট আপ করে।

    | কনস্ট্যান্ট              | মান    | বিবরণ |
    | --------------------- | -----: | - |
    | RATE                  | ১৬০০০  | অডিওর স্যাম্পল রেট। ১৬,০০০ মানে ১৬KHz |
    | SAMPLE_LENGTH_SECONDS | ৪      | ধারণ করার অডিওর দৈর্ঘ্য। এটি ৪ সেকেন্ডে সেট করা হয়েছে। দীর্ঘ অডিও রেকর্ড করতে চাইলে এটি বাড়ান। |
    | SAMPLES               | ৬৪০০০  | ধারণকৃত অডিও স্যাম্পলের মোট সংখ্যা। স্যাম্পল রেট * সেকেন্ডের সংখ্যা |
    | BUFFER_SIZE           | ১২৮০৪৪ | অডিও ধারণের জন্য বাফারের আকার। অডিও একটি WAV ফাইল হিসাবে ধারণ করা হবে, যা ৪৪ বাইটের হেডার, তারপর ১২৮,০০০ বাইটের অডিও ডেটা (প্রতিটি স্যাম্পল ২ বাইট) |
    | ADC_BUF_LEN           | ১৬০০   | DMAC থেকে অডিও ধারণের জন্য ব্যবহৃত বাফারের আকার |

    > 💁 যদি আপনি মনে করেন ৪ সেকেন্ড টাইমার অনুরোধ করার জন্য খুব কম, তবে আপনি `SAMPLE_LENGTH_SECONDS` মান বাড়াতে পারেন, এবং অন্যান্য মানগুলি পুনরায় গণনা হবে।

১. `src` ফোল্ডারে একটি নতুন ফাইল তৈরি করুন যার নাম দিন `mic.h`।

১. এই ফাইলের শীর্ষে নিম্নলিখিত যোগ করুন:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    এটি কিছু প্রয়োজনীয় হেডার ফাইল অন্তর্ভুক্ত করে, যার মধ্যে `config.h` এবং `FlashWriter` হেডার ফাইল রয়েছে।

১. একটি `Mic` ক্লাস সংজ্ঞায়িত করতে নিম্নলিখিত যোগ করুন যা মাইক্রোফোন থেকে ধারণ করতে পারে:

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

    এই ক্লাসে বর্তমানে কয়েকটি ফিল্ড রয়েছে যা রেকর্ডিং শুরু হয়েছে কিনা এবং একটি রেকর্ডিং ব্যবহারের জন্য প্রস্তুত কিনা তা ট্র্যাক করে। DMAC সেট আপ হলে, এটি ক্রমাগত মেমোরি বাফারে লেখে, তাই `_isRecording` ফ্ল্যাগটি নির্ধারণ করে যে এগুলি প্রক্রিয়াকরণ করা উচিত কিনা। `_isRecordingReady` ফ্ল্যাগটি সেট হবে যখন প্রয়োজনীয় ৪ সেকেন্ডের অডিও ধারণ করা হবে। `_writer` ফিল্ডটি অডিও ডেটা ফ্ল্যাশ মেমোরিতে সংরক্ষণ করতে ব্যবহৃত হয়।

    একটি গ্লোবাল ভেরিয়েবল তারপর `Mic` ক্লাসের একটি ইনস্ট্যান্সের জন্য ঘোষণা করা হয়।

১. `Mic` ক্লাসের `private` সেকশনে নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডটি একটি `configureDmaAdc` মেথড সংজ্ঞায়িত করে যা DMAC কনফিগার করে, এটিকে ADC-এর সাথে সংযুক্ত করে এবং এটি দুটি ভিন্ন বিকল্প বাফার `_adc_buf_0` এবং `_adc_buf_1` পূরণ করতে সেট করে।

    > 💁 মাইক্রোকন্ট্রোলার ডেভেলপমেন্টের একটি অসুবিধা হল হার্ডওয়্যারের সাথে ইন্টারঅ্যাক্ট করার জন্য প্রয়োজনীয় কোডের জটিলতা, কারণ আপনার কোড খুব নিম্ন স্তরে হার্ডওয়্যারের সাথে সরাসরি ইন্টারঅ্যাক্ট করে। এই কোডটি একটি সিঙ্গেল-বোর্ড কম্পিউটার বা ডেস্কটপ কম্পিউটারের জন্য আপনি যা লিখবেন তার চেয়ে বেশি জটিল কারণ এখানে কোনো অপারেটিং সিস্টেম সাহায্য করতে নেই। কিছু লাইব্রেরি উপলব্ধ রয়েছে যা এটি সহজ করতে পারে, তবে এখনও অনেক জটিলতা রয়েছে।

১. এর নিচে, নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডটি WAV হেডারকে একটি স্ট্রাক্ট হিসাবে সংজ্ঞায়িত করে যা ৪৪ বাইট মেমোরি নেয়। এটি অডিও ফাইলের রেট, আকার এবং চ্যানেলের সংখ্যা সম্পর্কে বিস্তারিত লিখে। এই হেডারটি তারপর ফ্ল্যাশ মেমোরিতে লেখা হয়।

১. এই কোডের নিচে, অডিও বাফার প্রস্তুত হলে প্রক্রিয়াকরণের জন্য একটি মেথড ঘোষণা করতে নিম্নলিখিত যোগ করুন:

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

    অডিও বাফারগুলি ১৬-বিট পূর্ণসংখ্যার অ্যারে যা ADC থেকে অডিও ধারণ করে। ADC ১২-বিট আনসাইনড মান (০-১০২৩) প্রদান করে, তাই এগুলি ১৬-বিট সাইনড মানে রূপান্তর করতে হবে, এবং তারপর কাঁচা বাইনারি ডেটা হিসাবে সংরক্ষণ করার জন্য ২ বাইটে রূপান্তর করতে হবে।

    এই বাইটগুলি ফ্ল্যাশ মেমোরি বাফারে লেখা হয়। লেখাটি ৪৪ নম্বর ইনডেক্স থেকে শুরু হয় - এটি WAV ফাইল হেডার হিসাবে লেখা ৪৪ বাইটের অফসেট। প্রয়োজনীয় অডিও দৈর্ঘ্যের জন্য প্রয়োজনীয় সমস্ত বাইট ধারণ করার পরে, অবশিষ্ট ডেটা ফ্ল্যাশ মেমোরিতে লেখা হয়।

১. `Mic` ক্লাসের `public` সেকশনে নিম্নলিখিত কোড যোগ করুন:

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

    এই কোডটি DMAC দ্বারা কল করা হবে আপনার কোডকে বাফার প্রক্রিয়াকরণ করতে বলার জন্য। এটি পরীক্ষা করে যে প্রক্রিয়াকরণের জন্য ডেটা আছে কিনা, এবং প্রাসঙ্গিক বাফার সহ `audioCallback` মেথড কল করে।

১. ক্লাসের বাইরে, `Mic mic;` ঘোষণার পরে, নিম্নলিখিত কোড যোগ করুন:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` DMAC দ্বারা কল করা হবে যখন বাফার প্রক্রিয়াকরণের জন্য প্রস্তুত থাকবে। এই ফাংশনটি নাম দ্বারা পাওয়া যায়, তাই এটি কেবল বিদ্যমান থাকলেই কল করা হবে।

১. `Mic` ক্লাসের `public` সেকশনে নিম্নলিখিত দুটি মেথড যোগ করুন:

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

    `init` মেথডে `Mic` ক্লাস ইনিশিয়ালাইজ করার জন্য কোড রয়েছে। এই মেথডটি মাইক্রোফোন পিনের জন্য সঠিক ভোল্টেজ সেট করে, ফ্ল্যাশ মেমোরি রাইটার সেট আপ করে, WAV ফাইল হেডার লেখে, এবং DMAC কনফিগার করে। `reset` মেথডটি অডিও ধারণ এবং ব্যবহারের পরে ফ্ল্যাশ মেমোরি রিসেট করে এবং হেডারটি পুনরায় লেখে।

### কাজ - অডিও ধারণ করুন

১. `main.cpp` ফাইলে, `mic.h` হেডার ফাইলের জন্য একটি ইনক্লুড ডিরেক্টিভ যোগ করুন:

    ```cpp
    #include "mic.h"
    ```

১. `setup` ফাংশনে, C বোতামটি ইনিশিয়ালাইজ করুন। এই বোতামটি চাপলে অডিও ধারণ শুরু হবে এবং ৪ সেকেন্ড ধরে চলবে:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

১. এর নিচে, মাইক্রোফোন ইনিশিয়ালাইজ করুন, তারপর কনসোলে প্রিন্ট করুন যে অডিও ধারণের জন্য প্রস্তুত:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

১. `loop` ফাংশনের উপরে, ধারণকৃত অডিও প্রক্রিয়াকরণের জন্য একটি ফাংশন সংজ্ঞায়িত করুন। আপাতত এটি কিছু করবে না, তবে এই পাঠের পরে এটি বক্তৃতাকে টেক্সটে রূপান্তর করার জন্য পাঠাবে:

    ```cpp
    void processAudio()
    {
    
    }
    ```

১. `loop` ফাংশনে নিম্নলিখিত যোগ করুন:

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

    এই কোডটি C বোতামটি পরীক্ষা করে, এবং যদি এটি চাপা হয় এবং রেকর্ডিং শুরু না হয়, তবে `Mic` ক্লাসের `_isRecording` ফিল্ডটি `true` সেট করা হয়। এটি `Mic` ক্লাসের `audioCallback` মেথডকে ৪ সেকেন্ডের অডিও ধারণ না হওয়া পর্যন্ত অডিও সংরক্ষণ করতে বাধ্য করবে। একবার ৪ সেকেন্ডের অডিও ধারণ করা হলে, `_isRecording` ফিল্ডটি `false` সেট করা হয়, এবং `_isRecordingReady` ফিল্ডটি `true` সেট করা হয়। এটি তারপর `loop` ফাংশনে পরীক্ষা করা হয়, এবং যখন এটি `true` হয়, তখন `processAudio` ফাংশন কল করা হয়, তারপর `mic` ক্লাসটি রিসেট করা হয়।

১. এই কোডটি তৈরি করুন, এটি আপনার Wio Terminal-এ আপলোড করুন এবং সিরিয়াল মনিটরের মাধ্যমে এটি পরীক্ষা করুন। C বোতামটি চাপুন (বাম দিকে, পাওয়ার সুইচের সবচ
💁 আপনি এই কোডটি [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) ফোল্ডারে খুঁজে পেতে পারেন।
গুরুত্বপূর্ণ নিয়মাবলী:  
1. '''markdown বা অন্য কোনো ট্যাগ অনুবাদের চারপাশে যোগ করবেন না  
2. নিশ্চিত করুন যে অনুবাদটি খুব বেশি আক্ষরিক শোনাচ্ছে না  
3. মন্তব্যগুলিও অনুবাদ করুন  
4. এই ফাইলটি Markdown ফরম্যাটে লেখা - এটিকে XML বা HTML হিসেবে বিবেচনা করবেন না  
5. অনুবাদ করবেন না:  
   - [!NOTE], [!WARNING], [!TIP], [!IMPORTANT], [!CAUTION]  
   - ভেরিয়েবল নাম, ফাংশন নাম, ক্লাস নাম  
   - @@INLINE_CODE_x@@ বা @@CODE_BLOCK_x@@ এর মতো প্লেসহোল্ডার  
   - URL বা পাথ  
6. সমস্ত মূল Markdown ফরম্যাটিং অক্ষত রাখুন  
7. কেবলমাত্র অনুবাদিত বিষয়বস্তু ফেরত দিন, কোনো অতিরিক্ত ট্যাগ বা মার্কআপ ছাড়াই  

😀 আপনার অডিও রেকর্ডিং প্রোগ্রামটি সফল হয়েছে!  

---

**অস্বীকৃতি**:  
এই নথিটি AI অনুবাদ পরিষেবা [Co-op Translator](https://github.com/Azure/co-op-translator) ব্যবহার করে অনুবাদ করা হয়েছে। আমরা যথাসম্ভব সঠিক অনুবাদের জন্য চেষ্টা করি, তবে অনুগ্রহ করে মনে রাখবেন যে স্বয়ংক্রিয় অনুবাদে ত্রুটি বা অসঙ্গতি থাকতে পারে। নথিটির মূল ভাষায় থাকা সংস্করণটিকেই প্রামাণিক উৎস হিসেবে বিবেচনা করা উচিত। গুরুত্বপূর্ণ তথ্যের জন্য, পেশাদার মানব অনুবাদ ব্যবহার করার পরামর্শ দেওয়া হচ্ছে। এই অনুবাদ ব্যবহারের ফলে সৃষ্ট কোনো ভুল বোঝাবুঝি বা ভুল ব্যাখ্যার জন্য আমরা দায়ী নই।