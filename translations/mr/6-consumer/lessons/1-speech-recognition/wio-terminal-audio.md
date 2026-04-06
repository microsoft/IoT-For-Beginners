# ऑडिओ कॅप्चर करा - Wio Terminal

या धड्याच्या भागात, तुम्ही Wio Terminal वर ऑडिओ कॅप्चर करण्यासाठी कोड लिहाल. ऑडिओ कॅप्चर Wio Terminal च्या वरच्या बाजूला असलेल्या बटणांपैकी एका बटणाद्वारे नियंत्रित केले जाईल.

## डिव्हाइस प्रोग्राम करा ऑडिओ कॅप्चर करण्यासाठी

तुम्ही मायक्रोफोनमधून C++ कोड वापरून ऑडिओ कॅप्चर करू शकता. Wio Terminal मध्ये फक्त 192KB RAM आहे, जे काही सेकंदांपेक्षा जास्त ऑडिओ कॅप्चर करण्यासाठी पुरेसे नाही. यामध्ये 4MB फ्लॅश मेमरी देखील आहे, जी त्याऐवजी वापरली जाऊ शकते, कॅप्चर केलेला ऑडिओ फ्लॅश मेमरीमध्ये सेव्ह करण्यासाठी.

अंगभूत मायक्रोफोन अॅनालॉग सिग्नल कॅप्चर करतो, जो डिजिटल सिग्नलमध्ये रूपांतरित होतो ज्याचा Wio Terminal वापर करू शकतो. ऑडिओ कॅप्चर करताना, डेटा योग्य वेळी कॅप्चर करणे आवश्यक आहे - उदाहरणार्थ, 16KHz वर ऑडिओ कॅप्चर करण्यासाठी, ऑडिओ अचूकपणे प्रति सेकंद 16,000 वेळा कॅप्चर करणे आवश्यक आहे, प्रत्येक नमुन्यादरम्यान समान अंतरासह. तुमचा कोड वापरण्याऐवजी, तुम्ही डायरेक्ट मेमरी ऍक्सेस कंट्रोलर (DMAC) वापरू शकता. हे सर्किटरी आहे जे कुठून तरी सिग्नल कॅप्चर करू शकते आणि मेमरीमध्ये लिहू शकते, तुमचा कोड प्रोसेसरवर चालत असताना व्यत्यय न आणता.

✅ DMA बद्दल अधिक वाचा [Wikipedia वरील डायरेक्ट मेमरी ऍक्सेस पृष्ठावर](https://wikipedia.org/wiki/Direct_memory_access).

![मायक्रोफोनमधून ऑडिओ ADC कडे जातो आणि नंतर DMAC कडे. हे एका बफरमध्ये लिहिते. जेव्हा हा बफर पूर्ण होतो, तेव्हा तो प्रक्रिया केली जाते आणि DMAC दुसऱ्या बफरमध्ये लिहिते](../../../../../translated_images/mr/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC ADC मधून ऑडिओ निश्चित अंतरावर कॅप्चर करू शकतो, जसे की 16KHz ऑडिओसाठी प्रति सेकंद 16,000 वेळा. हे कॅप्चर केलेला डेटा पूर्व-निर्धारित मेमरी बफरमध्ये लिहू शकते आणि जेव्हा हा पूर्ण होतो, तेव्हा तुमच्या कोडला प्रक्रिया करण्यासाठी उपलब्ध करून देते. ही मेमरी वापरणे ऑडिओ कॅप्चर करण्यास विलंब करू शकते, परंतु तुम्ही एकाधिक बफर सेट करू शकता. DMAC बफर 1 मध्ये लिहिते, नंतर जेव्हा ते पूर्ण होते, तुमच्या कोडला बफर 1 प्रक्रिया करण्यासाठी सूचित करते, तर DMAC बफर 2 मध्ये लिहिते. जेव्हा बफर 2 पूर्ण होते, तेव्हा तुमच्या कोडला सूचित करते आणि पुन्हा बफर 1 मध्ये लिहिण्यास जाते. अशा प्रकारे, जोपर्यंत तुम्ही प्रत्येक बफर प्रक्रिया करण्यासाठी लागणाऱ्या वेळेपेक्षा कमी वेळेत प्रक्रिया करता, तोपर्यंत तुम्ही कोणताही डेटा गमावणार नाही.

प्रत्येक बफर कॅप्चर झाल्यानंतर, ते फ्लॅश मेमरीमध्ये लिहिले जाऊ शकते. फ्लॅश मेमरीला परिभाषित पत्ते वापरून लिहिले जाणे आवश्यक आहे, कुठे लिहायचे आणि किती मोठे लिहायचे हे निर्दिष्ट करणे, मेमरीमधील बाइट्सच्या ऍरेला अपडेट करण्यासारखे. फ्लॅश मेमरीमध्ये ग्रॅन्युलॅरिटी असते, म्हणजेच मिटवणे आणि लिहिण्याच्या ऑपरेशन्स फक्त निश्चित आकाराचे असण्यावरच अवलंबून नसून त्या आकाराशी संरेखित असण्यावरही अवलंबून असते. उदाहरणार्थ, जर ग्रॅन्युलॅरिटी 4096 बाइट्स असेल आणि तुम्ही पत्ता 4200 वर मिटवण्याची विनंती केली, तर ते पत्ता 4096 ते 8192 पर्यंतचा सर्व डेटा मिटवू शकते. याचा अर्थ असा की जेव्हा तुम्ही ऑडिओ डेटा फ्लॅश मेमरीमध्ये लिहिता, तेव्हा ते योग्य आकाराच्या तुकड्यांमध्ये असले पाहिजे.

### कार्य - फ्लॅश मेमरी कॉन्फिगर करा

1. PlatformIO वापरून एक नवीन Wio Terminal प्रोजेक्ट तयार करा. या प्रोजेक्टला `smart-timer` असे नाव द्या. `setup` फंक्शनमध्ये सीरियल पोर्ट कॉन्फिगर करण्यासाठी कोड जोडा.

1. फ्लॅश मेमरीमध्ये प्रवेश प्रदान करण्यासाठी `platformio.ini` फाइलमध्ये खालील लायब्ररी डिपेंडन्सी जोडा:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. `main.cpp` फाइल उघडा आणि फ्लॅश मेमरी लायब्ररीसाठी खालील `include` निर्देश फाइलच्या शीर्षस्थानी जोडा:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD म्हणजे Serial Flash Universal Driver, आणि ही लायब्ररी सर्व फ्लॅश मेमरी चिप्ससाठी काम करण्यासाठी डिझाइन केली आहे.

1. `setup` फंक्शनमध्ये, फ्लॅश स्टोरेज लायब्ररी सेट करण्यासाठी खालील कोड जोडा:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    हे SFUD लायब्ररी इनिशियलाइझ होईपर्यंत लूप करते, नंतर फास्ट रीड्स चालू करते. अंगभूत फ्लॅश मेमरी Queued Serial Peripheral Interface (QSPI) वापरून ऍक्सेस केली जाऊ शकते, SPI कंट्रोलरचा एक प्रकार जो मिनिमल प्रोसेसर वापरासह सतत ऍक्सेस करण्यास अनुमती देतो. यामुळे फ्लॅश मेमरी वाचणे आणि लिहिणे वेगवान होते.

1. `src` फोल्डरमध्ये `flash_writer.h` नावाची नवीन फाइल तयार करा.

1. या फाइलच्या शीर्षस्थानी खालील जोडा:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    हे काही आवश्यक हेडर फाइल्स समाविष्ट करते, ज्यामध्ये फ्लॅश मेमरीशी संवाद साधण्यासाठी SFUD लायब्ररीसाठी हेडर फाइल समाविष्ट आहे.

1. या नवीन हेडर फाइलमध्ये `FlashWriter` नावाचा क्लास डिफाइन करा:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. `private` सेक्शनमध्ये खालील कोड जोडा:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    हे फ्लॅश मेमरीमध्ये डेटा लिहिण्यापूर्वी वापरण्यासाठी बफरसाठी काही फील्ड्स डिफाइन करते. `_sfudBuffer` नावाचा बाइट ऍरे आहे, ज्यामध्ये डेटा लिहिला जातो, आणि जेव्हा हा पूर्ण होतो, तेव्हा डेटा फ्लॅश मेमरीमध्ये लिहिला जातो. `_sfudBufferPos` फील्ड बफरमध्ये लिहिण्यासाठी वर्तमान स्थान साठवते, आणि `_sfudBufferWritePos` फ्लॅश मेमरीमध्ये लिहिण्यासाठी स्थान साठवते. `_flash` फ्लॅश मेमरी लिहिण्यासाठी पॉइंटर आहे - काही मायक्रोकंट्रोलर्समध्ये एकाधिक फ्लॅश मेमरी चिप्स असतात.

1. या क्लासच्या `public` सेक्शनमध्ये खालील मेथड जोडा:

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

    हे Wio Terminal वर फ्लॅश मेमरी लिहिण्यासाठी कॉन्फिगर करते आणि फ्लॅश मेमरीच्या ग्रेन साइजवर आधारित बफर सेट करते. हे `init` मेथडमध्ये आहे, कन्स्ट्रक्टरऐवजी कारण हे `setup` फंक्शनमध्ये फ्लॅश मेमरी सेट केल्यानंतर कॉल केले जाणे आवश्यक आहे.

1. `public` सेक्शनमध्ये खालील कोड जोडा:

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

    हे फ्लॅश स्टोरेज सिस्टममध्ये बाइट्स लिहिण्यासाठी मेथड्स डिफाइन करते. हे फ्लॅश मेमरीसाठी योग्य आकाराच्या इन-मेमरी बफरमध्ये लिहिण्याचे काम करते, आणि जेव्हा हा पूर्ण होतो, तेव्हा फ्लॅश मेमरीमध्ये लिहिले जाते, त्या ठिकाणी असलेला कोणताही विद्यमान डेटा मिटवून. `flushSfudBuffer` देखील आहे, जो अपूर्ण बफर लिहितो, कारण कॅप्चर केलेला डेटा फ्लॅश मेमरीच्या ग्रेन साइजच्या अचूक गुणाकारांमध्ये नसेल, त्यामुळे डेटाचा शेवटचा भाग लिहिला जाणे आवश्यक आहे.

    > 💁 डेटाचा शेवटचा भाग अतिरिक्त अवांछित डेटा लिहील, परंतु हे ठीक आहे कारण फक्त आवश्यक डेटा वाचला जाईल.

### कार्य - ऑडिओ कॅप्चर सेट करा

1. `src` फोल्डरमध्ये `config.h` नावाची नवीन फाइल तयार करा.

1. या फाइलच्या शीर्षस्थानी खालील जोडा:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    हे ऑडिओ कॅप्चरसाठी काही स्थिरांक सेट करते.

    | स्थिरांक              | मूल्य  | वर्णन |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | ऑडिओसाठी सॅम्पल रेट. 16,000 म्हणजे 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | कॅप्चर करण्यासाठी ऑडिओची लांबी. हे 4 सेकंदांवर सेट केले आहे. जास्त ऑडिओ रेकॉर्ड करण्यासाठी, हे वाढवा. |
    | SAMPLES               | 64000  | कॅप्चर केलेल्या ऑडिओ सॅम्पल्सची एकूण संख्या. सॅम्पल रेट * सेकंदांची संख्या |
    | BUFFER_SIZE           | 128044 | ऑडिओ कॅप्चर करण्यासाठी बफरचा आकार. ऑडिओ WAV फाइल म्हणून कॅप्चर केला जाईल, ज्यामध्ये 44 बाइट्स हेडर, नंतर 128,000 बाइट्स ऑडिओ डेटा (प्रत्येक सॅम्पल 2 बाइट्स आहे) |
    | ADC_BUF_LEN           | 1600   | DMAC मधून ऑडिओ कॅप्चर करण्यासाठी वापरण्यासाठी बफरचा आकार |

    > 💁 जर तुम्हाला 4 सेकंद खूप कमी वाटत असतील, तर `SAMPLE_LENGTH_SECONDS` मूल्य वाढवा, आणि इतर सर्व मूल्ये पुन्हा गणना होतील.

1. `src` फोल्डरमध्ये `mic.h` नावाची नवीन फाइल तयार करा.

1. या फाइलच्या शीर्षस्थानी खालील जोडा:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    हे काही आवश्यक हेडर फाइल्स समाविष्ट करते, ज्यामध्ये `config.h` आणि `FlashWriter` हेडर फाइल्स समाविष्ट आहेत.

1. मायक्रोफोनमधून कॅप्चर करू शकणारा `Mic` क्लास डिफाइन करण्यासाठी खालील जोडा:

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

    सध्या या क्लासमध्ये रेकॉर्डिंग सुरू झाले आहे का आणि रेकॉर्डिंग वापरण्यासाठी तयार आहे का हे ट्रॅक करण्यासाठी काही फील्ड्स आहेत. DMAC सेट केल्यावर, तो सतत मेमरी बफरमध्ये लिहित राहतो, त्यामुळे `_isRecording` फ्लॅग ठरवतो की हे प्रक्रिया करायचे की दुर्लक्ष करायचे. `_isRecordingReady` फ्लॅग आवश्यक 4 सेकंदांचा ऑडिओ कॅप्चर झाल्यावर सेट केला जाईल. `_writer` फील्ड ऑडिओ डेटा फ्लॅश मेमरीमध्ये सेव्ह करण्यासाठी वापरला जातो.

    नंतर `Mic` क्लासच्या उदाहरणासाठी एक ग्लोबल व्हेरिएबल घोषित केली जाते.

1. `Mic` क्लासच्या `private` सेक्शनमध्ये खालील कोड जोडा:

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

    हे `configureDmaAdc` मेथड डिफाइन करते जे DMAC कॉन्फिगर करते, ADC शी कनेक्ट करते आणि दोन वेगळ्या पर्यायी बफर `_adc_buf_0` आणि `_adc_buf_1` सेट करते.

    > 💁 मायक्रोकंट्रोलर डेव्हलपमेंटचा एक तोटा म्हणजे हार्डवेअरशी संवाद साधण्यासाठी आवश्यक असलेल्या कोडची गुंतागुंत, कारण तुमचा कोड हार्डवेअरशी थेट संवाद साधत खूप कमी स्तरावर चालतो. हे कोड सिंगल-बोर्ड कंप्यूटर किंवा डेस्कटॉप कंप्यूटरसाठी लिहिलेल्या कोडपेक्षा अधिक जटिल आहे कारण ऑपरेटिंग सिस्टम मदत करत नाही. काही लायब्ररी उपलब्ध आहेत ज्या हे सोपे करू शकतात, परंतु तरीही बरीच गुंतागुंत आहे.

1. खालील कोड जोडा:

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

    हे WAV हेडर 44 बाइट्स मेमरी घेणाऱ्या स्ट्रक्चर म्हणून डिफाइन करते. ऑडिओ फाइल रेट, आकार आणि चॅनेल्सबद्दल तपशील लिहिते. नंतर हा हेडर फ्लॅश मेमरीमध्ये लिहिला जातो.

1. खालील कोड जोडा, जेव्हा ऑडिओ बफर प्रक्रिया करण्यासाठी तयार असतील तेव्हा कॉल केले जाणारे मेथड घोषित करण्यासाठी:

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

    ऑडिओ बफर ADC मधून ऑडिओ असलेल्या 16-बिट पूर्णांकांच्या ऍरे आहेत. ADC 12-बिट अनसाइन व्हॅल्यू (0-1023) परत करते, त्यामुळे त्यांना 16-बिट साइन व्हॅल्यूमध्ये रूपांतरित करणे आवश्यक आहे, आणि नंतर कच्च्या बायनरी डेटामध्ये स्टोअर करण्यासाठी 2 बाइट्समध्ये रूपांतरित करणे आवश्यक आहे.

    हे बाइट्स फ्लॅश मेमरी बफरमध्ये लिहिले जातात. लेखन 44 वर सुरू होते - हे WAV फाइल हेडर म्हणून लिहिलेल्या 44 बाइट्सच्या ऑफसेट आहे. आवश्यक ऑडिओ लांबीसाठी आवश्यक असलेले सर्व बाइट्स कॅप्चर झाल्यानंतर, उर्वरित डेटा फ्लॅश मेमरीमध्ये लिहिला जातो.

1. `Mic` क्लासच्या `public` सेक्शनमध्ये खालील कोड जोडा:

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

    DMAC तुमच्या कोडला बफर प्रक्रिया करण्यास सांगण्यासाठी कॉल करेल. हे तपासते की प्रक्रिया करण्यासाठी डेटा आहे का, आणि संबंधित बफरसह `audioCallback` मेथड कॉल करते.

1. क्लासच्या बाहेर, `Mic mic;` घोषणेनंतर खालील कोड जोडा:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` DMAC द्वारे कॉल केला जाईल जेव्हा बफर प्रक्रिया करण्यासाठी तयार असतील. ही फंक्शन नावाने सापडते, त्यामुळे फक्त अस्तित्वात असणे आवश्यक आहे.

1. `Mic` क्लासच्या `public` सेक्शनमध्ये खालील दोन मेथड्स जोडा:

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

    `init` मेथड `Mic` क्लास इनिशियलाइझ करण्यासाठी कोड समाविष्ट करते. हे Mic पिनसाठी योग्य व्होल्टेज सेट करते, फ्लॅश मेमरी रायटर सेट करते, WAV फाइल हेडर लिहिते आणि DMAC कॉन्फिगर करते. `reset` मेथड फ्लॅश मेमरी रीसेट करते आणि ऑडिओ कॅप्चर आणि वापरला गेल्यानंतर हेडर पुन्हा लिहिते.

### कार्य - ऑडिओ कॅप्चर करा

1. `main.cpp` फाइलमध्ये `mic.h` हेडर फाइलसाठी `include` निर्देश जोडा:

    ```cpp
    #include "mic.h"
    ```

1. `setup` फंक्शनमध्ये, C बटण इनिशियलाइझ करा. हे बटण दाबल्यावर ऑडिओ कॅप्चर सुरू होईल आणि 4 सेकंद चालू राहील:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. याखाली मायक्रोफोन इनिशियलाइझ करा, नंतर कन्सोलवर प्रिंट करा की ऑडिओ कॅप्चर करण्यासाठी तयार आहे:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. `loop` फंक्शनच्या वर, कॅप्चर केलेला ऑडिओ प्रक्रिया करण्यासाठी एक फंक्शन डिफाइन करा. सध्या हे काहीही करत नाही, परंतु नंतरच्या धड्यात हे भाषण मजकूरात रूपांतरित करण्यासाठी पाठवेल:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. `loop` फंक्शनमध्ये खालील जोडा:

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

    हा कोड C बटण तपासतो, आणि जर हे दाबले गेले असेल आणि रेकॉर्डिंग सुरू झाले नसेल, तर `Mic` क्लासचा `_isRecording` फील्ड `true` सेट केला जातो. यामुळे `Mic` क्लासचा `audioCallback` मेथड 4 सेकंदांचा ऑडिओ स्टोअर करेल. एकदा 4 सेकंदांचा ऑडिओ कॅप्चर झाल्यावर, `_isRecording` फील्ड `false` सेट केला जातो, आणि `_isRecordingReady` फील्ड `true` सेट केला जातो. नंतर `loop` फंक्शनमध्ये हे तपासले जाते, आणि जेव्हा `true` असेल तेव्हा `processAudio` फंक्शन कॉल केला जातो, नंतर `mic` क्लास रीसेट केला जातो.

1. हा कोड तयार करा, Wio Terminal वर अपलोड करा आणि सीरियल मॉनिटरद्वारे तपासा. C
💁 तुम्ही हा कोड [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal) फोल्डरमध्ये शोधू शकता.
😀 तुमचा ऑडिओ रेकॉर्डिंग प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज AI भाषांतर सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) चा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी कृपया लक्षात ठेवा की स्वयंचलित भाषांतरे त्रुटी किंवा अचूकतेच्या अभावाने युक्त असू शकतात. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर करून उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.