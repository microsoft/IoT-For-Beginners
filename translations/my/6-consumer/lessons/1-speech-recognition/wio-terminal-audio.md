<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-28T16:32:45+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "my"
}
-->
# အသံဖမ်းယူခြင်း - Wio Terminal

ဒီသင်ခန်းစာအပိုင်းမှာ သင့်ရဲ့ Wio Terminal မှာ အသံဖမ်းယူဖို့ ကုဒ်ရေးသားပါမယ်။ အသံဖမ်းယူမှုကို Wio Terminal ရဲ့ အပေါ်ဘက်မှာရှိတဲ့ ခလုတ်တစ်ခုက ထိန်းချုပ်ပါမယ်။

## စက်ကို အသံဖမ်းယူဖို့ အစီအစဉ်ရေးသားပါ

C++ ကုဒ်ကို အသုံးပြုပြီး မိုက်ခရိုဖုန်းကနေ အသံဖမ်းယူနိုင်ပါတယ်။ Wio Terminal မှာ 192KB RAM ပဲရှိပြီး၊ ဒါက တစ်စက္ကန့်အနည်းငယ်သာ အသံဖမ်းယူနိုင်ပါတယ်။ ဒါ့အပြင် 4MB flash memory ပါရှိတဲ့အတွက် ဖမ်းယူထားတဲ့ အသံကို flash memory မှာ သိမ်းဆည်းနိုင်ပါတယ်။

ပေါင်းစပ်ထားတဲ့ မိုက်ခရိုဖုန်းက analog signal ကို ဖမ်းယူပြီး၊ Wio Terminal အသုံးပြုနိုင်တဲ့ digital signal အဖြစ် ပြောင်းလဲပေးပါတယ်။ အသံဖမ်းယူတဲ့အခါမှာ၊ ဒေတာကို မှန်ကန်တဲ့အချိန်မှာ ဖမ်းယူဖို့ လိုအပ်ပါတယ် - ဥပမာ 16KHz အသံဖမ်းယူဖို့ဆိုရင် တစ်စက္ကန့်ကို 16,000 ကြိမ် တိတိကျကျ interval တူညီစွာ ဖမ်းယူရပါမယ်။ သင့်ရဲ့ ကုဒ်ကို ဒီအလုပ်လုပ်စေမယ့်အစား၊ direct memory access controller (DMAC) ကို အသုံးပြုနိုင်ပါတယ်။ DMAC က signal ကို memory ထဲရေးဖို့ processor ကို မထိခိုက်ဘဲ လုပ်ဆောင်နိုင်တဲ့ စက်ကိရိယာတစ်ခုပါ။

✅ Wikipedia ရဲ့ [direct memory access စာမျက်နှာ](https://wikipedia.org/wiki/Direct_memory_access) မှာ DMA အကြောင်း ပိုမိုဖတ်ရှုနိုင်ပါတယ်။

![မိုက်ခရိုဖုန်းကနေ အသံကို ADC ကနေ DMAC သို့၊ DMAC က buffer တစ်ခုထဲရေး၊ buffer ပြည့်တဲ့အခါ process လုပ်ပြီး buffer နှစ်ခုကို အလှည့်ကျရေး](../../../../../translated_images/my/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

DMAC က ADC ကနေ အသံကို တိကျတဲ့ interval တွေမှာ ဖမ်းယူနိုင်ပါတယ်၊ ဥပမာ 16KHz အသံအတွက် တစ်စက္ကန့်ကို 16,000 ကြိမ်။ ဖမ်းယူထားတဲ့ ဒေတာကို memory buffer တစ်ခုထဲရေးနိုင်ပြီး၊ buffer ပြည့်တဲ့အခါ သင့်ရဲ့ ကုဒ်ကို process လုပ်ဖို့ အသိပေးပါတယ်။ ဒီ memory ကို အသုံးပြုရင် အသံဖမ်းယူမှုကို နှောင့်နှေးစေနိုင်ပါတယ်၊ ဒါပေမယ့် buffer အများအပြားကို စီစဉ်နိုင်ပါတယ်။ DMAC က buffer 1 ထဲရေး၊ ပြီးရင် buffer 1 ပြည့်တဲ့အခါ သင့်ရဲ့ ကုဒ်ကို အသိပေးပြီး buffer 2 ထဲရေး။ buffer 2 ပြည့်တဲ့အခါ buffer 1 ကို ပြန်ရေး။ ဒီလိုနဲ့ buffer တစ်ခု ပြည့်ဖို့ ကြာချိန်ထက် နည်းချိန်အတွင်း process လုပ်နိုင်ရင် ဒေတာမဆုံးရှုံးပါဘူး။

buffer တစ်ခုစီ ဖမ်းယူပြီးရင် flash memory ထဲရေးနိုင်ပါတယ်။ Flash memory ကို သတ်မှတ်ထားတဲ့ လိပ်စာတွေကို အသုံးပြုပြီးရေးရပါတယ်၊ ဘယ်မှာရေးမယ်၊ ဘယ်လောက်ရေးမယ်ဆိုတာ သတ်မှတ်ရပါတယ်၊ memory ထဲမှာ byte array တစ်ခု update လုပ်သလိုပဲ။ Flash memory မှာ granularity ရှိပါတယ်၊ ဒါက erase နဲ့ write လုပ်ငန်းတွေကို သတ်မှတ်ထားတဲ့ အရွယ်အစားနဲ့ အလျားလိုက်ညှိဖို့လိုအပ်ပါတယ်။ ဥပမာ granularity က 4096 bytes ဖြစ်ပြီး၊ address 4200 မှာ erase လုပ်ဖို့ တောင်းဆိုရင်၊ address 4096 ကနေ 8192 အထိ ဒေတာအားလုံးကို ဖျက်နိုင်ပါတယ်။ ဒါကြောင့် အသံဒေတာကို flash memory ထဲရေးတဲ့အခါ မှန်ကန်တဲ့ အရွယ်အစားနဲ့ alignment နဲ့ရေးဖို့လိုပါတယ်။

### လုပ်ငန်း - flash memory ကို configure လုပ်ပါ

1. PlatformIO ကို အသုံးပြုပြီး Wio Terminal project အသစ်တစ်ခု ဖန်တီးပါ။ ဒီ project ကို `smart-timer` လို့ အမည်ပေးပါ။ `setup` function ထဲမှာ serial port ကို configure လုပ်ဖို့ ကုဒ်ထည့်ပါ။

1. `platformio.ini` ဖိုင်ထဲမှာ အောက်ပါ library dependencies တွေထည့်ပါ၊ flash memory ကို အသုံးပြုဖို့လိုအပ်ပါတယ်။

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` ဖိုင်ကို ဖွင့်ပြီး flash memory library အတွက် အောက်ပါ include directive ကို ဖိုင်ရဲ့ အပေါ်ဆုံးမှာ ထည့်ပါ။

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD ဆိုတာ Serial Flash Universal Driver ကို ဆိုလိုပြီး၊ flash memory chips အားလုံးနဲ့ အလုပ်လုပ်ဖို့ ဒီဇိုင်းထုတ်ထားတဲ့ library တစ်ခုဖြစ်ပါတယ်။

1. `setup` function ထဲမှာ flash storage library ကို set up လုပ်ဖို့ အောက်ပါကုဒ်ထည့်ပါ။

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    ဒီကုဒ်က SFUD library ကို initialize လုပ်တဲ့အထိ loop လုပ်ပြီး၊ ပြီးရင် fast reads ကို ဖွင့်ပေးပါတယ်။ Built-in flash memory ကို Queued Serial Peripheral Interface (QSPI) ကို အသုံးပြုပြီး access လုပ်နိုင်ပါတယ်၊ ဒါက processor usage အနည်းငယ်နဲ့ queue မှတစ်ဆင့် ဆက်တိုက် access လုပ်နိုင်တဲ့ SPI controller တစ်မျိုးဖြစ်ပါတယ်။ ဒါကြောင့် flash memory ကို ဖတ်ခြင်းနဲ့ရေးခြင်း ပိုမြန်စေပါတယ်။

1. `src` folder ထဲမှာ `flash_writer.h` ဆိုတဲ့ ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။

1. ဒီဖိုင်ရဲ့ အပေါ်ဆုံးမှာ အောက်ပါကုဒ်ထည့်ပါ။

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    ဒီကုဒ်က လိုအပ်တဲ့ header ဖိုင်တွေကို ထည့်သွင်းပြီး၊ flash memory နဲ့ အလုပ်လုပ်ဖို့ SFUD library ရဲ့ header ဖိုင်ကိုလည်း ထည့်သွင်းပါတယ်။

1. ဒီ header ဖိုင်ထဲမှာ `FlashWriter` ဆိုတဲ့ class တစ်ခုကို သတ်မှတ်ပါ။

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` section ထဲမှာ အောက်ပါကုဒ်ထည့်ပါ။

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    ဒီကုဒ်က flash memory ထဲရေးမယ့် ဒေတာကို သိမ်းဆည်းဖို့ buffer တစ်ခု သတ်မှတ်ပါတယ်။ `_sfudBuffer` ဆိုတဲ့ byte array တစ်ခုကို ဒေတာရေးဖို့ သတ်မှတ်ပြီး၊ buffer ပြည့်တဲ့အခါ ဒေတာကို flash memory ထဲရေးပါတယ်။ `_sfudBufferPos` က buffer ထဲမှာရေးမယ့် လက်ရှိတည်နေရာကို သိမ်းဆည်းပြီး၊ `_sfudBufferWritePos` က flash memory ထဲမှာရေးမယ့် လက်ရှိတည်နေရာကို သိမ်းဆည်းပါတယ်။ `_flash` ကရေးမယ့် flash memory ကို pointer နဲ့ သတ်မှတ်ထားပါတယ် - microcontroller တချို့မှာ flash memory chips အများအပြားရှိနိုင်ပါတယ်။

1. `public` section ထဲမှာ ဒီ class ကို initialize လုပ်ဖို့ အောက်ပါ method ထည့်ပါ။

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

    ဒီကုဒ်က Wio Terminal ရဲ့ flash memory ကိုရေးဖို့ configure လုပ်ပြီး၊ flash memory ရဲ့ grain size အပေါ်မူတည်ပြီး buffer တွေကို set up လုပ်ပါတယ်။ Constructor အစား `init` method ထဲမှာ ဒီကုဒ်ကို ထည့်ထားတာက flash memory ကို `setup` function ထဲမှာ set up လုပ်ပြီးမှ ဒီ method ကို ခေါ်ဖို့လိုအပ်လို့ပါ။

1. `public` section ထဲမှာ အောက်ပါကုဒ်ထည့်ပါ။

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

    ဒီကုဒ်က flash storage system ထဲကို bytes တွေရေးဖို့ method တွေကို သတ်မှတ်ပါတယ်။ Memory buffer မှာရေးပြီး၊ buffer ပြည့်တဲ့အခါ flash memory ထဲရေးပါတယ်၊ buffer ပြည့်တဲ့နေရာမှာရှိတဲ့ ဒေတာကို ဖျက်ပြီးမှရေးပါတယ်။ `flushSfudBuffer` ဆိုတဲ့ method က အပြည့်မဖြစ်တဲ့ buffer ကိုရေးဖို့ သတ်မှတ်ထားပါတယ်၊ ဒါက data capture လုပ်တဲ့အခါ grain size ရဲ့ တိတိကျကျ မဟုတ်တဲ့ အပိုင်းကိုရေးဖို့လိုအပ်လို့ပါ။

    > 💁 အပိုဒေတာတွေကိုရေးမယ်၊ ဒါပေမယ့် လိုအပ်တဲ့ဒေတာကိုပဲ ဖတ်မယ်ဆိုတော့ အဆင်ပြေပါတယ်။

### လုပ်ငန်း - အသံဖမ်းယူမှုကို set up လုပ်ပါ

1. `src` folder ထဲမှာ `config.h` ဆိုတဲ့ ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။

1. ဒီဖိုင်ရဲ့ အပေါ်ဆုံးမှာ အောက်ပါကုဒ်ထည့်ပါ။

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    ဒီကုဒ်က အသံဖမ်းယူမှုအတွက် constant တွေကို သတ်မှတ်ပါတယ်။

    | Constant              | Value  | ဖော်ပြချက် |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | အသံရဲ့ sample rate. 16,000 ဆိုတာ 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | ဖမ်းယူမယ့် အသံရဲ့ အချိန်အတိုင်းအတာ။ ဒီကို 4 စက္ကန့်အဖြစ် သတ်မှတ်ထားပါတယ်။ အသံပိုကြာစေချင်ရင် ဒီကို တိုးချဲ့နိုင်ပါတယ်။ |
    | SAMPLES               | 64000  | ဖမ်းယူမယ့် အသံ sample အရေအတွက်။ sample rate * စက္ကန့်အရေအတွက် |
    | BUFFER_SIZE           | 128044 | အသံ buffer ရဲ့ အရွယ်အစား။ အသံကို WAV ဖိုင်အဖြစ် သိမ်းမယ်၊ 44 bytes header နဲ့ 128,000 bytes အသံဒေတာ (sample တစ်ခုကို 2 bytes) |
    | ADC_BUF_LEN           | 1600   | DMAC က အသံဖမ်းယူဖို့ အသုံးပြုမယ့် buffer ရဲ့ အရွယ်အစား |

    > 💁 4 စက္ကန့်က timer တောင်းဖို့အတွက် နည်းနေရင် `SAMPLE_LENGTH_SECONDS` ကို တိုးချဲ့နိုင်ပါတယ်၊ အခြား value တွေကိုလည်း ပြန်လည်တွက်ချက်ပေးပါမယ်။

1. `src` folder ထဲမှာ `mic.h` ဆိုတဲ့ ဖိုင်အသစ်တစ်ခု ဖန်တီးပါ။

1. ဒီဖိုင်ရဲ့ အပေါ်ဆုံးမှာ အောက်ပါကုဒ်ထည့်ပါ။

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    ဒီကုဒ်က လိုအပ်တဲ့ header ဖိုင်တွေကို ထည့်သွင်းပြီး၊ `config.h` နဲ့ `FlashWriter` header ဖိုင်တွေကိုလည်း ထည့်သွင်းပါတယ်။

1. မိုက်ခရိုဖုန်းကနေ အသံဖမ်းယူနိုင်တဲ့ `Mic` class ကို သတ်မှတ်ဖို့ အောက်ပါကုဒ်ထည့်ပါ။

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

    ဒီ class မှာ လက်ရှိတော့ အသံဖမ်းယူမှုစတင်ထားမထား၊ အသံဖမ်းယူပြီးပြီလားဆိုတာ track လုပ်ဖို့ field နှစ်ခုပဲ ရှိပါတယ်။ DMAC ကို set up လုပ်တဲ့အခါ၊ ဒါက memory buffer တွေကို ဆက်တိုက်ရေးပါတယ်၊ ဒါကြောင့် `_isRecording` flag က ဒီ buffer တွေကို process လုပ်မလား၊ မလုပ်ဘူးလားဆိုတာ သတ်မှတ်ပါတယ်။ `_isRecordingReady` flag က လိုအပ်တဲ့ 4 စက္ကန့်အသံ ဖမ်းယူပြီးပြီဆိုတာ သတ်မှတ်ပါတယ်။ `_writer` field က အသံဒေတာကို flash memory ထဲသိမ်းဖို့ အသုံးပြုပါတယ်။

    Global variable တစ်ခုကို `Mic` class ရဲ့ instance အဖြစ် သတ်မှတ်ထားပါတယ်။

1. `Mic` class ရဲ့ `private` section ထဲမှာ အောက်ပါကုဒ်ထည့်ပါ။

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

    ဒီကုဒ်က `configureDmaAdc` ဆိုတဲ့ method ကို သတ်မှတ်ပြီး၊ DMAC ကို configure လုပ်ပါတယ်၊ ADC နဲ့ ချိတ်ဆက်ပြီး buffer နှစ်ခု `_adc_buf_0` နဲ့ `_adc_buf_1` ကို အလှည့်ကျ populate လုပ်ပါတယ်။

    > 💁 Microcontroller development ရဲ့ downside တစ်ခုက hardware နဲ့ အလုပ်လုပ်ဖို့ လိုအပ်တဲ့ ကုဒ်ရဲ့ ရှုပ်ထွေးမှုပါ၊ သင့်ရဲ့ ကုဒ်က operating system မရှိတဲ့အတွက် hardware နဲ့ တိုက်ရိုက် အလုပ်လုပ်ပါတယ်။ ဒီကုဒ်က single-board computer သို့မဟုတ် desktop computer အတွက်ရေးတဲ့ ကုဒ်ထက် ပိုရှုပ်ထွေးပါတယ်၊ operating system က အကူအညီမပေးလို့ပါ။ Libraries တချို့က ဒီအလုပ်ကို လွယ်ကူစေနိုင်ပေမယ့် ရှုပ်ထွေးမှုတစ်ချို့တော့ ကျန်နေပါသေးတယ်။

1. ဒီကုဒ်အောက်မှာ အောက်ပါကုဒ်ထည့်ပါ။

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

    ဒီကုဒ်က WAV header ကို 44 bytes memory ကို အသုံးပြုတဲ့ struct အဖြစ် သတ်မှတ်ပါတယ်။ WAV ဖိုင်ရဲ့ rate, size, channel အရေအတွက် စသဖြင့် အသေးစိတ်ကိုရေးပါတယ်။ Header ကို flash memory ထဲရေးပါတယ်။

1. ဒီကုဒ်အောက်မှာ အသံ buffer တွေကို process လုပ်ဖို့ method တစ်ခု သတ်မှတ်ပါ။

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

    အသံ buffer တွေက ADC ကနေ 16-bit integer array တွေဖြစ်ပါတယ်။ ADC က 12-bit unsigned value (0-1023) တွေကို return ပြန်ပါတယ်၊ ဒါကြောင့် ဒီ value တွေကို 16-bit signed value တွေ (2 bytes) အဖြစ် ပြောင်းလဲဖို့လိုပါတယ်၊ ပြီးရင် raw binary data အဖြစ် သိမ်းဖို့ ပြောင်းလဲရပါတယ်။

    ဒီ bytes တွေကို flash memory buffer ထဲရေးပါတယ်။ ရေးမှုက index 44 မှစတင်ပါတယ် - ဒီဟာက WAV ဖိုင် header အတွက်ရေးထားတဲ့ 44 bytes ရဲ့ offset ဖြစ်ပါတယ်။ လိုအပ်တဲ့ အသံအချိန်အတိုင်းအတာအတွက် bytes အားလုံးဖမ်းယူပြီးရင်၊ ကျန်တဲ့ဒေတာကို flash memory ထဲရေးပါတယ်။

1. `Mic` class ရဲ့ `public` section ထဲမှာ အောက်ပါကုဒ်ထည့်ပါ။

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

    ဒီကုဒ်ကို DMAC က buffer တွေကို process လုပ်ဖို့ သင့်ရဲ့ ကုဒ်ကို အသိပေးတဲ့အခါ ခေါ်ပါတယ်။ Process လုပ်ဖို့ ဒေတာရှိမရှိ စစ်ပြီး၊ သက်ဆိုင်ရာ buffer နဲ့ `audioCallback` method ကို ခေါ်ပါတယ်။

1. Class အပြင်မှာ၊ `Mic mic;` သတ်မှတ်ချက်အောက်မှာ အောက်ပါကုဒ်ထည့်ပါ။

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` ကို DMAC က buffer တွေကို process လုပ်ဖို့ အသိပေးတဲ့အခါ ခေါ်ပါတယ်။ Function name နဲ့ပဲ DMAC က function ကို ရှာပြီး ခေါ်ပါတယ်၊ ဒါကြောင့် ရှိနေဖို့လိုပါတယ်။

1. `Mic` class ရဲ့ `public` section ထဲမှာ အောက်ပါ method နှစ်ခုထည့်ပါ။

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

    `init` method က `Mic` class ကို initialize လုပ်ဖို့ ကုဒ်ပါရှိပါတယ်။ ဒီ method က Mic pin အတွက် မှန်ကန်တဲ့ voltage ကို သတ်မှတ်ပြီး၊ flash memory writer ကို set up လုပ်ပါတယ်၊ WAV file header ကိုရေးပြီး၊ DMAC ကို configure လုပ်ပါတယ်။ `reset` method က အသံဖမ်းယူပြီး အသုံးပြုပြီးတဲ့အခါ flash memory ကို reset လုပ်ပြီး header ကို ပြန်ရေးပါတယ်။

### လုပ်ငန်း - အသံဖမ်းယူပါ

1. `main.cpp` ဖိုင်ထဲမှာ `mic.h` header ဖိုင်အတွက် include directive ထည့်ပါ။

    ```cpp
    #include "mic.h"
    ```

1. `setup` function ထဲမှာ C ခလုတ်ကို initialize လုပ်ပါ။ ဒီခလုတ်ကို နှိပ်တဲ့အခါ အသံဖမ်းယူမှုစတင်ပြီး၊ 4 စက္ကန့်အထိ ဆက်လုပ်ပါမယ်။

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. ဒီကုဒ်အောက်မှာ မိုက်ခရိုဖုန်းကို initialize လုပ်ပြီး၊ အသံဖမ်းယူဖို့ အဆင်သင့်ဖြစ်ပြီလို့ console မှာ print လုပ်ပါ။

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` function ရဲ့ အပေါ်မှာ အသံဖမ်းယူပြီးတဲ့အခါ process လုပ်ဖို့ function တစ်ခု သတ်မှတ်ပါ။ လက်ရှိအချိန်မှာတော့ ဒီ function က ဘာမှ မလုပ်သေးပါဘူး၊ ဒါပေမယ့် ဒီသင်ခန်းစာရဲ့ နောက်ပိုင်းမှာ အသံကို စာသားအဖြစ် ပြောင်းဖို့ အသုံးပြုပါမယ်။

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` function ထဲမှာ အောက်ပါကုဒ်
> 💁 ဒီကုဒ်ကို [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) ဖိုလ်ဒါမှာ ရှာဖွေနိုင်ပါတယ်။
😀 သင့်ရဲ့ အသံမှတ်တမ်းတင်မှု အစီအစဉ်အောင်မြင်ခဲ့ပါပြီ!

---

**အကြောင်းကြားချက်**:  
ဤစာရွက်စာတမ်းကို AI ဘာသာပြန်ဝန်ဆောင်မှု [Co-op Translator](https://github.com/Azure/co-op-translator) ကို အသုံးပြု၍ ဘာသာပြန်ထားပါသည်။ ကျွန်ုပ်တို့သည် တိကျမှုအတွက် ကြိုးစားနေသော်လည်း၊ အလိုအလျောက် ဘာသာပြန်မှုများတွင် အမှားများ သို့မဟုတ် မတိကျမှုများ ပါရှိနိုင်သည်ကို သတိပြုပါ။ မူရင်းဘာသာစကားဖြင့် ရေးသားထားသော စာရွက်စာတမ်းကို အာဏာရှိသော ရင်းမြစ်အဖြစ် သတ်မှတ်သင့်ပါသည်။ အရေးကြီးသော အချက်အလက်များအတွက် လူ့ဘာသာပြန်ပညာရှင်များမှ ပရော်ဖက်ရှင်နယ် ဘာသာပြန်မှုကို အကြံပြုပါသည်။ ဤဘာသာပြန်မှုကို အသုံးပြုခြင်းမှ ဖြစ်ပေါ်လာသော အလွဲအလွဲအချော်များ သို့မဟုတ် အနားလွဲမှုများအတွက် ကျွန်ုပ်တို့သည် တာဝန်မယူပါ။