# ऑडियो कैप्चर करें - Wio Terminal

इस पाठ के इस भाग में, आप अपने Wio Terminal पर ऑडियो कैप्चर करने के लिए कोड लिखेंगे। ऑडियो कैप्चर Wio Terminal के ऊपर दिए गए बटन में से एक द्वारा नियंत्रित किया जाएगा।

## डिवाइस को ऑडियो कैप्चर करने के लिए प्रोग्राम करें

आप माइक्रोफोन से ऑडियो C++ कोड का उपयोग करके कैप्चर कर सकते हैं। Wio Terminal में केवल 192KB RAM है, जो कुछ सेकंड से अधिक ऑडियो कैप्चर करने के लिए पर्याप्त नहीं है। इसमें 4MB फ्लैश मेमोरी भी है, जिसे इसके बजाय उपयोग किया जा सकता है, और कैप्चर किए गए ऑडियो को फ्लैश मेमोरी में सेव किया जा सकता है।

बिल्ट-इन माइक्रोफोन एक एनालॉग सिग्नल कैप्चर करता है, जिसे डिजिटल सिग्नल में परिवर्तित किया जाता है जिसे Wio Terminal उपयोग कर सकता है। जब ऑडियो कैप्चर किया जाता है, तो डेटा को सही समय पर कैप्चर करने की आवश्यकता होती है - उदाहरण के लिए, 16KHz पर ऑडियो कैप्चर करने के लिए, ऑडियो को ठीक 16,000 बार प्रति सेकंड कैप्चर करना होगा, प्रत्येक सैंपल के बीच समान अंतराल के साथ। आपके कोड का उपयोग करने के बजाय, आप डायरेक्ट मेमोरी एक्सेस कंट्रोलर (DMAC) का उपयोग कर सकते हैं। यह एक सर्किट्री है जो कहीं से सिग्नल कैप्चर कर सकती है और मेमोरी में लिख सकती है, बिना आपके प्रोसेसर पर चल रहे कोड को बाधित किए।

✅ DMA के बारे में अधिक पढ़ें [Wikipedia पर डायरेक्ट मेमोरी एक्सेस पेज](https://wikipedia.org/wiki/Direct_memory_access) पर।

![माइक्रोफोन से ऑडियो ADC में जाता है और फिर DMAC में। यह एक बफर में लिखता है। जब यह बफर भर जाता है, तो इसे प्रोसेस किया जाता है और DMAC दूसरे बफर में लिखता है](../../../../../translated_images/hi/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC ADC से ऑडियो को निश्चित अंतराल पर कैप्चर कर सकता है, जैसे 16KHz ऑडियो के लिए प्रति सेकंड 16,000 बार। यह कैप्चर किए गए डेटा को एक प्री-अलोकेटेड मेमोरी बफर में लिख सकता है, और जब यह भर जाता है, तो इसे प्रोसेस करने के लिए आपके कोड को उपलब्ध कराता है। इस मेमोरी का उपयोग ऑडियो कैप्चर में देरी कर सकता है, लेकिन आप कई बफर सेट कर सकते हैं। DMAC बफर 1 में लिखता है, फिर जब यह भर जाता है, तो आपके कोड को बफर 1 को प्रोसेस करने के लिए सूचित करता है, जबकि DMAC बफर 2 में लिखता है। जब बफर 2 भर जाता है, तो यह आपके कोड को सूचित करता है, और फिर बफर 1 में लिखने के लिए वापस जाता है। इस तरह, जब तक आप प्रत्येक बफर को भरने में लगने वाले समय से कम समय में प्रोसेस करते हैं, आप कोई डेटा नहीं खोएंगे।

एक बार जब प्रत्येक बफर कैप्चर हो जाता है, तो इसे फ्लैश मेमोरी में लिखा जा सकता है। फ्लैश मेमोरी को परिभाषित एड्रेस का उपयोग करके लिखा जाना चाहिए, यह निर्दिष्ट करते हुए कि कहां लिखना है और कितना बड़ा लिखना है, मेमोरी में बाइट्स के एक एरे को अपडेट करने के समान। फ्लैश मेमोरी में ग्रैन्युलैरिटी होती है, जिसका अर्थ है कि इरेज़ और लिखने के ऑपरेशन न केवल एक निश्चित आकार के होने पर निर्भर करते हैं, बल्कि उस आकार के साथ संरेखित होने पर भी निर्भर करते हैं। उदाहरण के लिए, यदि ग्रैन्युलैरिटी 4096 बाइट्स है और आप एड्रेस 4200 पर इरेज़ का अनुरोध करते हैं, तो यह एड्रेस 4096 से 8192 तक का सारा डेटा मिटा सकता है। इसका मतलब है कि जब आप ऑडियो डेटा को फ्लैश मेमोरी में लिखते हैं, तो इसे सही आकार के चंक्स में होना चाहिए।

### कार्य - फ्लैश मेमोरी को कॉन्फ़िगर करें

1. PlatformIO का उपयोग करके एक नया Wio Terminal प्रोजेक्ट बनाएं। इस प्रोजेक्ट को `smart-timer` नाम दें। `setup` फ़ंक्शन में सीरियल पोर्ट को कॉन्फ़िगर करने के लिए कोड जोड़ें।

1. फ्लैश मेमोरी तक पहुंच प्रदान करने के लिए `platformio.ini` फ़ाइल में निम्नलिखित लाइब्रेरी डिपेंडेंसी जोड़ें:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` फ़ाइल खोलें और फ़ाइल के शीर्ष पर फ्लैश मेमोरी लाइब्रेरी के लिए निम्नलिखित इनक्लूड डायरेक्टिव जोड़ें:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD का मतलब है Serial Flash Universal Driver, और यह एक लाइब्रेरी है जो सभी फ्लैश मेमोरी चिप्स के साथ काम करने के लिए डिज़ाइन की गई है।

1. `setup` फ़ंक्शन में, फ्लैश स्टोरेज लाइब्रेरी को सेटअप करने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    यह तब तक लूप करता है जब तक SFUD लाइब्रेरी इनिशियलाइज़ नहीं हो जाती, फिर तेज़ रीड्स चालू करता है। बिल्ट-इन फ्लैश मेमोरी को Queued Serial Peripheral Interface (QSPI) का उपयोग करके एक्सेस किया जा सकता है, जो एक प्रकार का SPI कंट्रोलर है जो न्यूनतम प्रोसेसर उपयोग के साथ एक कतार के माध्यम से निरंतर एक्सेस की अनुमति देता है। इससे फ्लैश मेमोरी को पढ़ना और लिखना तेज़ हो जाता है।

1. `src` फ़ोल्डर में एक नई फ़ाइल बनाएं जिसका नाम `flash_writer.h` हो।

1. इस फ़ाइल के शीर्ष पर निम्नलिखित जोड़ें:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    इसमें कुछ आवश्यक हेडर फ़ाइलें शामिल हैं, जिनमें फ्लैश मेमोरी के साथ इंटरैक्ट करने के लिए SFUD लाइब्रेरी की हेडर फ़ाइल शामिल है।

1. इस नई हेडर फ़ाइल में `FlashWriter` नामक एक क्लास परिभाषित करें:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` सेक्शन में निम्नलिखित कोड जोड़ें:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    यह फ्लैश मेमोरी में लिखने से पहले डेटा को स्टोर करने के लिए उपयोग किए जाने वाले बफर के लिए कुछ फ़ील्ड्स को परिभाषित करता है। `_sfudBuffer` एक बाइट एरे है जिसमें डेटा लिखा जाता है, और जब यह भर जाता है, तो डेटा फ्लैश मेमोरी में लिखा जाता है। `_sfudBufferPos` फ़ील्ड इस बफर में लिखने के लिए वर्तमान स्थान को स्टोर करता है, और `_sfudBufferWritePos` फ्लैश मेमोरी में लिखने के स्थान को स्टोर करता है। `_flash` फ्लैश मेमोरी को लिखने के लिए एक पॉइंटर है - कुछ माइक्रोकंट्रोलर्स में कई फ्लैश मेमोरी चिप्स होते हैं।

1. इस क्लास को इनिशियलाइज़ करने के लिए `public` सेक्शन में निम्नलिखित मेथड जोड़ें:

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

    यह Wio Terminal पर फ्लैश मेमोरी को लिखने के लिए कॉन्फ़िगर करता है, और फ्लैश मेमोरी के ग्रेन साइज के आधार पर बफर सेट करता है। यह एक `init` मेथड में है, न कि एक कंस्ट्रक्टर में, क्योंकि इसे `setup` फ़ंक्शन में फ्लैश मेमोरी सेटअप के बाद कॉल करने की आवश्यकता होती है।

1. `public` सेक्शन में निम्नलिखित कोड जोड़ें:

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

    यह कोड फ्लैश स्टोरेज सिस्टम में बाइट्स लिखने के लिए मेथड्स को परिभाषित करता है। यह फ्लैश मेमोरी के लिए सही आकार के इन-मेमोरी बफर में लिखकर काम करता है, और जब यह भर जाता है, तो इसे फ्लैश मेमोरी में लिखा जाता है, उस स्थान पर किसी भी मौजूदा डेटा को मिटाते हुए। इसमें एक `flushSfudBuffer` भी है जो एक अधूरा बफर लिखता है, क्योंकि कैप्चर किया जा रहा डेटा फ्लैश मेमोरी के ग्रेन साइज के सटीक गुणज नहीं होगा, इसलिए डेटा का अंतिम भाग लिखने की आवश्यकता होती है।

    > 💁 डेटा का अंतिम भाग अतिरिक्त अवांछित डेटा लिखेगा, लेकिन यह ठीक है क्योंकि केवल आवश्यक डेटा ही पढ़ा जाएगा।

### कार्य - ऑडियो कैप्चर सेट करें

1. `src` फ़ोल्डर में एक नई फ़ाइल बनाएं जिसका नाम `config.h` हो।

1. इस फ़ाइल के शीर्ष पर निम्नलिखित जोड़ें:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    यह कोड ऑडियो कैप्चर के लिए कुछ कॉन्स्टेंट्स सेट करता है।

    | कॉन्स्टेंट              | मान  | विवरण |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | ऑडियो के लिए सैंपल रेट। 16,000 का मतलब है 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | कैप्चर करने के लिए ऑडियो की लंबाई। इसे 4 सेकंड पर सेट किया गया है। लंबे ऑडियो रिकॉर्ड करने के लिए, इसे बढ़ाएं। |
    | SAMPLES               | 64000  | कैप्चर किए जाने वाले ऑडियो सैंपल की कुल संख्या। इसे सैंपल रेट * सेकंड की संख्या पर सेट किया गया है। |
    | BUFFER_SIZE           | 128044 | ऑडियो बफर का आकार कैप्चर करने के लिए। ऑडियो को WAV फ़ाइल के रूप में कैप्चर किया जाएगा, जिसमें 44 बाइट्स का हेडर होगा, फिर 128,000 बाइट्स का ऑडियो डेटा (प्रत्येक सैंपल 2 बाइट्स का होता है)। |
    | ADC_BUF_LEN           | 1600   | DMAC से ऑडियो कैप्चर करने के लिए उपयोग किए जाने वाले बफर का आकार। |

    > 💁 यदि आपको लगता है कि 4 सेकंड टाइमर का अनुरोध करने के लिए बहुत कम है, तो आप `SAMPLE_LENGTH_SECONDS` मान बढ़ा सकते हैं, और अन्य सभी मान पुनः गणना करेंगे।

1. `src` फ़ोल्डर में एक नई फ़ाइल बनाएं जिसका नाम `mic.h` हो।

1. इस फ़ाइल के शीर्ष पर निम्नलिखित जोड़ें:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    इसमें कुछ आवश्यक हेडर फ़ाइलें शामिल हैं, जिनमें `config.h` और `FlashWriter` हेडर फ़ाइलें शामिल हैं।

1. माइक्रोफोन से कैप्चर करने के लिए एक `Mic` क्लास को परिभाषित करने के लिए निम्नलिखित जोड़ें:

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

    इस क्लास में वर्तमान में केवल कुछ फ़ील्ड्स हैं जो ट्रैक करते हैं कि रिकॉर्डिंग शुरू हुई है या नहीं, और क्या रिकॉर्डिंग उपयोग के लिए तैयार है। जब DMAC सेटअप होता है, तो यह लगातार मेमोरी बफर में लिखता है, इसलिए `_isRecording` फ्लैग यह निर्धारित करता है कि इन्हें प्रोसेस किया जाना चाहिए या अनदेखा किया जाना चाहिए। `_isRecordingReady` फ्लैग तब सेट किया जाएगा जब आवश्यक 4 सेकंड का ऑडियो कैप्चर किया गया हो। `_writer` फ़ील्ड ऑडियो डेटा को फ्लैश मेमोरी में सेव करने के लिए उपयोग किया जाता है।

    फिर `Mic` क्लास के एक इंस्टेंस के लिए एक ग्लोबल वेरिएबल घोषित किया जाता है।

1. `Mic` क्लास के `private` सेक्शन में निम्नलिखित कोड जोड़ें:

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

    यह कोड एक `configureDmaAdc` मेथड को परिभाषित करता है जो DMAC को कॉन्फ़िगर करता है, इसे ADC से जोड़ता है और इसे दो अलग-अलग वैकल्पिक बफर, `_adc_buf_0` और `_adc_buf_1` को पॉप्युलेट करने के लिए सेट करता है।

    > 💁 माइक्रोकंट्रोलर डेवलपमेंट की एक कमी हार्डवेयर के साथ इंटरैक्ट करने के लिए आवश्यक कोड की जटिलता है, क्योंकि आपका कोड हार्डवेयर के साथ सीधे बहुत निम्न स्तर पर इंटरैक्ट करता है। यह कोड एक सिंगल-बोर्ड कंप्यूटर या डेस्कटॉप कंप्यूटर के लिए लिखे गए कोड की तुलना में अधिक जटिल है क्योंकि कोई ऑपरेटिंग सिस्टम मदद करने के लिए नहीं है। कुछ लाइब्रेरीज़ उपलब्ध हैं जो इसे सरल बना सकती हैं, लेकिन फिर भी बहुत जटिलता होती है।

1. इसके नीचे, निम्नलिखित कोड जोड़ें:

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

    यह कोड WAV हेडर को एक स्ट्रक्चर के रूप में परिभाषित करता है जो मेमोरी में 44 बाइट्स लेता है। यह ऑडियो फ़ाइल रेट, आकार, और चैनलों की संख्या के बारे में विवरण लिखता है। फिर इस हेडर को फ्लैश मेमोरी में लिखा जाता है।

1. इस कोड के नीचे, ऑडियो बफर प्रोसेस करने के लिए तैयार होने पर कॉल किए जाने वाले मेथड को घोषित करने के लिए निम्नलिखित जोड़ें:

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

    ऑडियो बफर 16-बिट इंटीजर के एरे होते हैं जो ADC से ऑडियो को कैप्चर करते हैं। ADC 12-बिट अनसाइन वैल्यू (0-1023) लौटाता है, इसलिए इन्हें 16-बिट साइन वैल्यू में परिवर्तित करने की आवश्यकता होती है, और फिर इन्हें रॉ बाइनरी डेटा के रूप में स्टोर करने के लिए 2 बाइट्स में परिवर्तित किया जाता है।

    ये बाइट्स फ्लैश मेमोरी बफर में लिखे जाते हैं। लिखना इंडेक्स 44 से शुरू होता है - यह WAV फ़ाइल हेडर के रूप में लिखे गए 44 बाइट्स का ऑफसेट है। एक बार जब आवश्यक ऑडियो लंबाई के लिए सभी बाइट्स कैप्चर कर लिए जाते हैं, तो शेष डेटा फ्लैश मेमोरी में लिखा जाता है।

1. `Mic` क्लास के `public` सेक्शन में निम्नलिखित कोड जोड़ें:

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

    यह कोड DMAC द्वारा आपके कोड को बफर प्रोसेस करने के लिए कॉल करने के लिए उपयोग किया जाएगा। यह जांचता है कि प्रोसेस करने के लिए डेटा है, और संबंधित बफर के साथ `audioCallback` मेथड को कॉल करता है।

1. क्लास के बाहर, `Mic mic;` घोषणा के बाद, निम्नलिखित कोड जोड़ें:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` DMAC द्वारा तब कॉल किया जाएगा जब बफर प्रोसेस करने के लिए तैयार हों। इस फ़ंक्शन को नाम से पाया जाता है, इसलिए इसे केवल मौजूद होना चाहिए ताकि इसे कॉल किया जा सके।

1. `Mic` क्लास के `public` सेक्शन में निम्नलिखित दो मेथड जोड़ें:

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

    `init` मेथड में `Mic` क्लास को इनिशियलाइज़ करने के लिए कोड होता है। यह मेथड Mic पिन के लिए सही वोल्टेज सेट करता है, फ्लैश मेमोरी राइटर को सेट करता है, WAV फ़ाइल हेडर लिखता है, और DMAC को कॉन्फ़िगर करता है। `reset` मेथड फ्लैश मेमोरी को रीसेट करता है और ऑडियो कैप्चर और उपयोग के बाद हेडर को फिर से लिखता है।

### कार्य - ऑडियो कैप्चर करें

1. `main.cpp` फ़ाइल में, `mic.h` हेडर फ़ाइल के लिए एक इनक्लूड डायरेक्टिव जोड़ें:

    ```cpp
    #include "mic.h"
    ```

1. `setup` फ़ंक्शन में, C बटन को इनिशियलाइज़ करें। जब यह बटन दबाया जाएगा, तो ऑडियो कैप्चर शुरू होगा और 4 सेकंड तक जारी रहेगा:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. इसके नीचे, माइक्रोफोन को इनिशियलाइज़ करें, फिर कंसोल में प्रिंट करें कि ऑडियो कैप्चर करने के लिए तैयार है:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` फ़ंक्शन के ऊपर, कैप्चर किए गए ऑडियो को प्रोसेस करने के लिए एक फ़ंक्शन परिभाषित करें। फिलहाल यह कुछ नहीं करता है, लेकिन इस पाठ में बाद में यह स्पीच को टेक्स्ट में बदलने के लिए भेजेगा:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` फ़ंक्शन में निम्नलिखित जोड़ें:

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

    यह कोड C बटन की जांच करता है, और यदि यह दबाया गया है और रिकॉर्डिंग शुरू नहीं हुई है, तो `Mic` क्लास के `_isRecording` फ़ील्ड को true पर सेट करता है। यह `Mic` क्लास के `audioCallback` मेथड को तब तक ऑडियो स्टोर करने का कारण बनेगा जब तक कि 4 सेकंड का ऑडियो कैप्चर न हो जाए। एक बार जब 4 सेकंड का ऑडियो कैप्चर हो जाता है, तो `_isRecording` फ़ील्ड false पर सेट हो जाता है, और `_isRecordingReady` फ़ील्ड true पर सेट हो जाता है। फिर इसे `loop` फ़ंक्शन में जांचा जाता है, और जब true होता है, तो `processAudio` फ़ंक्शन को कॉल किया जाता है, फिर mic क्लास को रीसेट किया जाता है।

1. इस कोड को बनाएं, इसे अपने Wio Terminal पर अप
💁 आप इस कोड को [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) फ़ोल्डर में पा सकते हैं।
😀 आपका ऑडियो रिकॉर्डिंग प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।