# अडियो क्याप्चर गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं आफ्नो Wio Terminal मा अडियो क्याप्चर गर्न कोड लेख्नुहुनेछ। अडियो क्याप्चर Wio Terminal को माथिल्लो भागमा रहेको बटनहरूमध्ये एकद्वारा नियन्त्रण गरिनेछ।

## उपकरणलाई अडियो क्याप्चर गर्न प्रोग्राम गर्नुहोस्

तपाईं C++ कोड प्रयोग गरेर माइक्रोफोनबाट अडियो क्याप्चर गर्न सक्नुहुन्छ। Wio Terminal मा केवल 192KB RAM छ, जसले केही सेकेन्डभन्दा बढी अडियो क्याप्चर गर्न पर्याप्त छैन। यसमा 4MB फ्ल्यास मेमोरी पनि छ, जसलाई क्याप्चर गरिएको अडियोलाई फ्ल्यास मेमोरीमा सुरक्षित गर्न प्रयोग गर्न सकिन्छ।

बिल्ट-इन माइक्रोफोनले एनालग सिग्नल क्याप्चर गर्छ, जुन डिजिटल सिग्नलमा रूपान्तरण हुन्छ, जसलाई Wio Terminal ले प्रयोग गर्न सक्छ। अडियो क्याप्चर गर्दा, डेटा सही समयमा क्याप्चर गर्न आवश्यक छ - उदाहरणका लागि, 16KHz मा अडियो क्याप्चर गर्न, अडियोलाई प्रति सेकेन्ड ठीक 16,000 पटक क्याप्चर गर्नुपर्छ, प्रत्येक नमुनाबीच समान अन्तरालमा। तपाईंको कोडले यो गर्नुभन्दा, तपाईंले डाइरेक्ट मेमोरी एक्सेस कन्ट्रोलर (DMAC) प्रयोग गर्न सक्नुहुन्छ। यो यस्तो सर्किट हो जसले कुनै सिग्नललाई क्याप्चर गरेर मेमोरीमा लेख्न सक्छ, तपाईंको प्रोसेसरमा चलिरहेको कोडलाई अवरोध नगरी।

✅ DMAC को बारेमा थप पढ्नको लागि [विकिपेडियाको डाइरेक्ट मेमोरी एक्सेस पृष्ठ](https://wikipedia.org/wiki/Direct_memory_access) हेर्नुहोस्।

![माइक्रोफोनबाट अडियो ADC मा जान्छ, त्यसपछि DMAC मा। यसले एउटा बफरमा लेख्छ। जब यो बफर भरिन्छ, यो प्रोसेस गरिन्छ र DMAC ले दोस्रो बफरमा लेख्छ।](../../../../../translated_images/ne/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC ले ADC बाट निश्चित अन्तरालमा अडियो क्याप्चर गर्न सक्छ, जस्तै 16KHz अडियोको लागि प्रति सेकेन्ड 16,000 पटक। यसले क्याप्चर गरिएको डेटा पूर्व-निर्धारित मेमोरी बफरमा लेख्न सक्छ, र जब यो भरिन्छ, तपाईंको कोडलाई प्रोसेस गर्न उपलब्ध गराउँछ। यो मेमोरी प्रयोग गर्दा अडियो क्याप्चरमा ढिलाइ हुन सक्छ, तर तपाईंले धेरै बफरहरू सेटअप गर्न सक्नुहुन्छ। DMAC ले बफर 1 मा लेख्छ, त्यसपछि जब यो भरिन्छ, तपाईंको कोडलाई बफर 1 प्रोसेस गर्न सूचित गर्छ, जबकि DMAC ले बफर 2 मा लेख्छ। जब बफर 2 भरिन्छ, यो तपाईंको कोडलाई सूचित गर्छ, र फेरि बफर 1 मा लेख्न जान्छ। यसरी, जबसम्म तपाईं प्रत्येक बफरलाई भरिन लाग्ने समयभन्दा कम समयमा प्रोसेस गर्नुहुन्छ, तपाईंले कुनै डेटा गुमाउनुहुनेछैन।

प्रत्येक बफर क्याप्चर भएपछि, यसलाई फ्ल्यास मेमोरीमा लेख्न सकिन्छ। फ्ल्यास मेमोरीलाई परिभाषित ठेगानाहरू प्रयोग गरेर लेख्न आवश्यक छ, कहाँ लेख्ने र कति ठूलो लेख्ने निर्दिष्ट गर्दै, मेमोरीको बाइटहरूको एर्रे अपडेट गरेजस्तै। फ्ल्यास मेमोरीमा ग्रान्युलारिटी हुन्छ, जसको अर्थ मेटाउने र लेख्ने कार्यहरू निश्चित आकारको मात्रामा निर्भर हुन्छन्, र त्यस आकारसँग मिल्नुपर्छ। उदाहरणका लागि, यदि ग्रान्युलारिटी 4096 बाइट छ र तपाईंले ठेगाना 4200 मा मेटाउन अनुरोध गर्नुभयो भने, यसले ठेगाना 4096 देखि 8192 सम्मको सबै डेटा मेटाउन सक्छ। यसको अर्थ, जब तपाईं अडियो डेटा फ्ल्यास मेमोरीमा लेख्नुहुन्छ, यो सही आकारको टुक्रामा हुनुपर्छ।

### कार्य - फ्ल्यास मेमोरी कन्फिगर गर्नुहोस्

1. PlatformIO प्रयोग गरेर नयाँ Wio Terminal प्रोजेक्ट सिर्जना गर्नुहोस्। यस प्रोजेक्टलाई `smart-timer` नाम दिनुहोस्। `setup` फङ्सनमा सिरियल पोर्ट कन्फिगर गर्न कोड थप्नुहोस्।

1. फ्ल्यास मेमोरीमा पहुँच प्रदान गर्न `platformio.ini` फाइलमा निम्न पुस्तकालय निर्भरताहरू थप्नुहोस्:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` फाइल खोल्नुहोस् र फ्ल्यास मेमोरी पुस्तकालयको लागि निम्न इनक्लुड निर्देशन फाइलको शीर्षमा थप्नुहोस्:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD को अर्थ Serial Flash Universal Driver हो, र यो सबै फ्ल्यास मेमोरी चिपहरूसँग काम गर्न डिजाइन गरिएको पुस्तकालय हो।

1. `setup` फङ्सनमा, फ्ल्यास स्टोरेज पुस्तकालय सेटअप गर्न निम्न कोड थप्नुहोस्:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    यो लूप हुन्छ जबसम्म SFUD पुस्तकालय आरम्भ हुँदैन, त्यसपछि फास्ट रिड्स अन गर्दछ। बिल्ट-इन फ्ल्यास मेमोरीलाई Queued Serial Peripheral Interface (QSPI) प्रयोग गरेर पहुँच गर्न सकिन्छ, जुन SPI कन्ट्रोलरको प्रकार हो जसले न्यूनतम प्रोसेसर प्रयोग गरेर निरन्तर पहुँचको लागि क्यू प्रयोग गर्दछ। यसले फ्ल्यास मेमोरीमा पढ्न र लेख्न छिटो बनाउँछ।

1. `src` फोल्डरमा `flash_writer.h` नामक नयाँ फाइल सिर्जना गर्नुहोस्।

1. यस फाइलको शीर्षमा निम्न थप्नुहोस्:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    यसले आवश्यक हेडर फाइलहरू समावेश गर्दछ, जसमा फ्ल्यास मेमोरीसँग अन्तरक्रिया गर्न SFUD पुस्तकालयको हेडर फाइल पनि समावेश छ।

1. यस नयाँ हेडर फाइलमा `FlashWriter` नामक कक्षा परिभाषित गर्नुहोस्:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` सेक्सनमा निम्न कोड थप्नुहोस्:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    यसले फ्ल्यास मेमोरीमा लेख्न प्रयोग गर्न डेटा भण्डारण गर्न बफरको लागि केही फिल्डहरू परिभाषित गर्दछ। `_sfudBuffer` नामक बाइट एर्रेमा डेटा लेखिन्छ, र जब यो भरिन्छ, डेटा फ्ल्यास मेमोरीमा लेखिन्छ। `_sfudBufferPos` फिल्डले यस बफरमा लेख्नको लागि हालको स्थान भण्डारण गर्दछ, र `_sfudBufferWritePos` ले फ्ल्यास मेमोरीमा लेख्नको लागि स्थान भण्डारण गर्दछ। `_flash` फ्ल्यास मेमोरीमा लेख्नको लागि पोइन्टर हो - केही माइक्रोकन्ट्रोलरहरूमा धेरै फ्ल्यास मेमोरी चिपहरू हुन्छन्।

1. यो कक्षाको `public` सेक्सनमा यो कक्षा आरम्भ गर्न निम्न विधि थप्नुहोस्:

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

    यो Wio Terminal मा फ्ल्यास मेमोरी लेख्न कन्फिगर गर्दछ, र फ्ल्यास मेमोरीको ग्रेन साइजको आधारमा बफरहरू सेटअप गर्दछ। यो `init` विधिमा छ, कन्स्ट्रक्टरमा होइन, किनभने यो फ्ल्यास मेमोरी `setup` फङ्सनमा सेटअप भएपछि मात्र बोलाउन आवश्यक छ।

1. `public` सेक्सनमा निम्न कोड थप्नुहोस्:

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

    यो कोडले फ्ल्यास स्टोरेज प्रणालीमा बाइटहरू लेख्न विधिहरू परिभाषित गर्दछ। यो फ्ल्यास मेमोरीको सही आकारको इन-मेमोरी बफरमा लेखेर काम गर्दछ, र जब यो भरिन्छ, यो फ्ल्यास मेमोरीमा लेखिन्छ, त्यहाँको कुनै पनि अवस्थित डेटा मेटाउँदै। `flushSfudBuffer` पनि छ, जसले अधूरो बफर लेख्छ, किनभने क्याप्चर गरिएको डेटा फ्ल्यास मेमोरीको ग्रेन साइजको ठ्याक्कै गुणक हुँदैन, त्यसैले डेटा अन्त्यको भाग लेख्न आवश्यक छ।

    > 💁 डेटा अन्त्यको भागले अतिरिक्त अनावश्यक डेटा लेख्न सक्छ, तर यो ठीक छ किनभने केवल आवश्यक डेटा मात्र पढिनेछ।

### कार्य - अडियो क्याप्चर सेटअप गर्नुहोस्

1. `src` फोल्डरमा `config.h` नामक नयाँ फाइल सिर्जना गर्नुहोस्।

1. यस फाइलको शीर्षमा निम्न थप्नुहोस्:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    यो कोडले अडियो क्याप्चरका लागि केही स्थिरांकहरू सेटअप गर्दछ।

    | स्थिरांक              | मान  | विवरण |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | अडियोको नमूना दर। 16,000 भनेको 16KHz हो |
    | SAMPLE_LENGTH_SECONDS | 4      | क्याप्चर गर्न अडियोको लम्बाइ। यो 4 सेकेन्डमा सेट गरिएको छ। लामो अडियो रेकर्ड गर्न, यसलाई बढाउनुहोस्। |
    | SAMPLES               | 64000  | क्याप्चर गरिने अडियो नमूनाहरूको कुल संख्या। नमूना दर * सेकेन्डको संख्या |
    | BUFFER_SIZE           | 128044 | अडियो बफरको आकार क्याप्चर गर्न। अडियो WAV फाइलको रूपमा क्याप्चर गरिनेछ, जसमा 44 बाइटको हेडर, त्यसपछि 128,000 बाइटको अडियो डेटा (प्रत्येक नमूना 2 बाइट हो) |
    | ADC_BUF_LEN           | 1600   | DMAC बाट अडियो क्याप्चर गर्न प्रयोग गरिने बफरहरूको आकार |

    > 💁 यदि तपाईंलाई 4 सेकेन्ड छोटो लाग्छ टाइमर अनुरोध गर्न, तपाईं `SAMPLE_LENGTH_SECONDS` मान बढाउन सक्नुहुन्छ, र अन्य सबै मानहरू पुन: गणना गरिनेछ।

1. `src` फोल्डरमा `mic.h` नामक नयाँ फाइल सिर्जना गर्नुहोस्।

1. यस फाइलको शीर्षमा निम्न थप्नुहोस्:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    यसले आवश्यक हेडर फाइलहरू समावेश गर्दछ, जसमा `config.h` र `FlashWriter` हेडर फाइलहरू समावेश छन्।

1. माइक्रोफोनबाट क्याप्चर गर्न `Mic` कक्षा परिभाषित गर्न निम्न थप्नुहोस्:

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

    यो कक्षामा हाललाई केवल केही फिल्डहरू छन्, जसले रेकर्डिङ सुरु भएको छ कि छैन र रेकर्डिङ प्रयोग गर्न तयार छ कि छैन ट्र्याक गर्दछ। DMAC सेटअप भएपछि, यो लगातार मेमोरी बफरहरूमा लेख्छ, त्यसैले `_isRecording` फ्ल्यागले यी प्रोसेस गर्न वा बेवास्ता गर्न निर्धारण गर्दछ। `_isRecordingReady` फ्ल्याग आवश्यक 4 सेकेन्डको अडियो क्याप्चर भएपछि सेट गरिनेछ। `_writer` फिल्ड अडियो डेटा फ्ल्यास मेमोरीमा सुरक्षित गर्न प्रयोग गरिन्छ।

    त्यसपछि `Mic` कक्षाको उदाहरणको लागि एक ग्लोबल भेरिएबल घोषणा गरिन्छ।

1. `Mic` कक्षाको `private` सेक्सनमा निम्न कोड थप्नुहोस्:

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

    यो कोडले `configureDmaAdc` विधि परिभाषित गर्दछ, जसले DMAC कन्फिगर गर्दछ, यसलाई ADC सँग जडान गर्दछ र दुई फरक वैकल्पिक बफरहरू `_adc_buf_0` र `_adc_buf_1` मा डेटा भर्ने सेट गर्दछ।

    > 💁 माइक्रोकन्ट्रोलर विकासको एक कमजोरी भनेको हार्डवेयरसँग अन्तरक्रिया गर्न आवश्यक कोडको जटिलता हो, किनभने तपाईंको कोड हार्डवेयरसँग सिधै कम स्तरमा चल्छ। यो कोड सिंगल-बोर्ड कम्प्युटर वा डेस्कटप कम्प्युटरको लागि लेखिने कोडभन्दा बढी जटिल छ, किनभने यहाँ अपरेटिङ सिस्टमले सहयोग गर्दैन। केही पुस्तकालयहरू उपलब्ध छन् जसले यसलाई सरल बनाउन सक्छ, तर अझै धेरै जटिलता रहन्छ।

1. यसको तल, निम्न कोड थप्नुहोस्:

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

    यो कोडले WAV हेडरलाई 44 बाइटको मेमोरी ओगट्ने स्ट्रक्टको रूपमा परिभाषित गर्दछ। यसले अडियो फाइल दर, आकार, र च्यानलहरूको संख्या बारे विवरण लेख्छ। यो हेडर फ्ल्यास मेमोरीमा लेखिन्छ।

1. यस कोडको तल, अडियो बफरहरू प्रोसेस गर्न तयार हुँदा बोलाइने विधि घोषणा गर्न निम्न थप्नुहोस्:

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

    अडियो बफरहरू 16-बिट पूर्णांकहरूको एर्रे हुन्, जसमा ADC बाट अडियो हुन्छ। ADC ले 12-बिट असाइन गरिएको मानहरू (0-1023) फिर्ता गर्छ, त्यसैले यीलाई 16-बिट साइन गरिएको मानहरूमा रूपान्तरण गर्न आवश्यक छ, र त्यसपछि कच्चा बाइनरी डेटा रूपमा भण्डारण गर्न 2 बाइटमा रूपान्तरण गर्न आवश्यक छ।

    यी बाइटहरू फ्ल्यास मेमोरी बफरहरूमा लेखिन्छन्। लेखाइ 44 मा सुरु हुन्छ - यो WAV फाइल हेडरको रूपमा लेखिएका 44 बाइटहरूको अफसेट हो। आवश्यक अडियो लम्बाइको लागि आवश्यक सबै बाइटहरू क्याप्चर भएपछि, बाँकी डेटा फ्ल्यास मेमोरीमा लेखिन्छ।

1. `Mic` कक्षाको `public` सेक्सनमा निम्न कोड थप्नुहोस्:

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

    यो कोड DMAC द्वारा तपाईंको कोडलाई बफरहरू प्रोसेस गर्न भन्न बोलाइनेछ। यसले प्रोसेस गर्न डेटा छ कि छैन जाँच्छ, र सम्बन्धित बफरको साथ `audioCallback` विधि बोलाउँछ।

1. कक्षाको बाहिर, `Mic mic;` घोषणापछि, निम्न कोड थप्नुहोस्:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` DMAC द्वारा बोलाइनेछ जब बफरहरू प्रोसेस गर्न तयार हुन्छन्। यो फङ्सन नामद्वारा फेला पारिन्छ, त्यसैले केवल अस्तित्वमा हुन आवश्यक छ।

1. `Mic` कक्षाको `public` सेक्सनमा निम्न दुई विधिहरू थप्नुहोस्:

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

    `init` विधिमा `Mic` कक्षा आरम्भ गर्न कोड समावेश छ। यो विधिले Mic पिनको लागि सही भोल्टेज सेट गर्दछ, फ्ल्यास मेमोरी लेखक सेटअप गर्दछ, WAV फाइल हेडर लेख्छ, र DMAC कन्फिगर गर्दछ। `reset` विधिले अडियो क्याप्चर र प्रयोग भएपछि फ्ल्यास मेमोरी रिसेट गर्दछ र हेडर पुन: लेख्छ।

### कार्य - अडियो क्याप्चर गर्नुहोस्

1. `main.cpp` फाइलमा, `mic.h` हेडर फाइलको लागि इनक्लुड निर्देशन थप्नुहोस्:

    ```cpp
    #include "mic.h"
    ```

1. `setup` फङ्सनमा, C बटनलाई आरम्भ गर्नुहोस्। अडियो क्याप्चर यो बटन थिच्दा सुरु हुनेछ, र 4 सेकेन्डसम्म जारी रहनेछ:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. यसको तल, माइक्रोफोन आरम्भ गर्नुहोस्, त्यसपछि कन्सोलमा अडियो क्याप्चर गर्न तयार छ भनेर प्रिन्ट गर्नुहोस्:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` फङ्सनभन्दा माथि, क्याप्चर गरिएको अडियो प्रोसेस गर्न फङ्सन परिभाषित गर्नुहोस्। अहिलेका लागि यसले केही गर्दैन, तर यस पाठको पछि यो भाषणलाई पाठमा रूपान्तरण गर्न पठाउनेछ:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` फङ्सनमा निम्न थप्नुहोस्:

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

    यो कोडले C बटन जाँच्छ, र यदि यो थिचिएको छ र रेकर्डिङ सुरु भएको छैन भने, `Mic` कक्षाको `_isRecording` फिल्डलाई `true` मा सेट गर्दछ। यसले `Mic` कक्षाको `audioCallback` विधिलाई 4 सेकेन्डसम्म अडियो भण्डारण गर्न कारण बनाउँछ। एकपटक 4 सेकेन्डको अडियो क्याप्चर भएपछि, `_isRecording` फिल्डलाई `false` मा सेट गरिन्छ, र `_isRecordingReady` फिल्डलाई `true` मा सेट गरिन्छ। यो `loop` फङ्सनमा जाँचिन्छ, र जब `true` हुन्छ, `processAudio` फङ्सन बोलाइन्छ, त्यसपछि `Mic` कक्षा रिसेट गरिन्छ।

1. यो कोड बनाउनुहोस्, यसलाई आफ्नो Wio Terminal मा अपलोड गर्नुहोस् र सिरियल मोनिटर मार्फत परीक्षण गर्नुहोस्। C बटन थिच्नुहोस् (पावर स्विचको नजिकको बायाँपट्टि रहेको बटन), र बोल्नुहोस्। 4 सेकेन्डको अडियो क्याप्चर हुनेछ।

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
> 💁 तपाईंले यो कोड [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) फोल्डरमा फेला पार्न सक्नुहुन्छ।
😀 तपाईंको अडियो रेकर्डिङ कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरी अनुवाद गरिएको हो। हामी यथासम्भव शुद्धताको प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धि हुन सक्छ। यसको मूल भाषामा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्त्वपूर्ण जानकारीका लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याका लागि हामी जिम्मेवार हुने छैनौं।