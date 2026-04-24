# บันทึกเสียง - Wio Terminal

ในส่วนนี้ของบทเรียน คุณจะเขียนโค้ดเพื่อบันทึกเสียงบน Wio Terminal ของคุณ การบันทึกเสียงจะถูกควบคุมโดยหนึ่งในปุ่มที่อยู่ด้านบนของ Wio Terminal

## เขียนโปรแกรมเพื่อบันทึกเสียง

คุณสามารถบันทึกเสียงจากไมโครโฟนโดยใช้โค้ด C++ Wio Terminal มี RAM เพียง 192KB ซึ่งไม่เพียงพอที่จะบันทึกเสียงได้นานเกินสองสามวินาที แต่มีหน่วยความจำแฟลชขนาด 4MB ซึ่งสามารถใช้แทนได้ โดยบันทึกเสียงที่บันทึกไว้ลงในหน่วยความจำแฟลช

ไมโครโฟนในตัวจะบันทึกสัญญาณอนาล็อก ซึ่งจะถูกแปลงเป็นสัญญาณดิจิทัลที่ Wio Terminal สามารถใช้งานได้ เมื่อบันทึกเสียง ข้อมูลจะต้องถูกบันทึกในเวลาที่เหมาะสม เช่น หากต้องการบันทึกเสียงที่ 16KHz จะต้องบันทึกเสียง 16,000 ครั้งต่อวินาที โดยมีช่วงเวลาที่เท่ากันระหว่างแต่ละตัวอย่าง แทนที่จะใช้โค้ดของคุณทำสิ่งนี้ คุณสามารถใช้ตัวควบคุมการเข้าถึงหน่วยความจำโดยตรง (DMAC) ซึ่งเป็นวงจรที่สามารถบันทึกสัญญาณจากที่ใดที่หนึ่งและเขียนลงในหน่วยความจำ โดยไม่รบกวนโค้ดที่กำลังทำงานบนโปรเซสเซอร์

✅ อ่านเพิ่มเติมเกี่ยวกับ DMA ได้ที่ [หน้าการเข้าถึงหน่วยความจำโดยตรงบน Wikipedia](https://wikipedia.org/wiki/Direct_memory_access)

![เสียงจากไมโครโฟนไปยัง ADC แล้วไปยัง DMAC ซึ่งเขียนลงในบัฟเฟอร์ เมื่อบัฟเฟอร์นี้เต็ม จะถูกประมวลผลและ DMAC จะเขียนลงในบัฟเฟอร์ที่สอง](../../../../../translated_images/th/dmac-adc-buffers.4509aee49145c90b.webp)

DMAC สามารถบันทึกเสียงจาก ADC ในช่วงเวลาที่กำหนด เช่น 16,000 ครั้งต่อวินาทีสำหรับเสียง 16KHz มันสามารถเขียนข้อมูลที่บันทึกไว้ลงในบัฟเฟอร์หน่วยความจำที่จัดสรรไว้ล่วงหน้า และเมื่อบัฟเฟอร์นี้เต็ม จะทำให้โค้ดของคุณสามารถประมวลผลได้ การใช้หน่วยความจำนี้อาจทำให้การบันทึกเสียงล่าช้า แต่คุณสามารถตั้งค่าบัฟเฟอร์หลายตัวได้ DMAC จะเขียนลงในบัฟเฟอร์ 1 และเมื่อเต็ม จะส่งการแจ้งเตือนให้โค้ดของคุณประมวลผลบัฟเฟอร์ 1 ในขณะที่ DMAC เขียนลงในบัฟเฟอร์ 2 เมื่อบัฟเฟอร์ 2 เต็ม จะส่งการแจ้งเตือนให้โค้ดของคุณ และกลับไปเขียนลงในบัฟเฟอร์ 1 ด้วยวิธีนี้ ตราบใดที่คุณประมวลผลแต่ละบัฟเฟอร์ในเวลาที่น้อยกว่าที่ใช้ในการเติมบัฟเฟอร์ คุณจะไม่สูญเสียข้อมูลใดๆ

เมื่อแต่ละบัฟเฟอร์ถูกบันทึกแล้ว สามารถเขียนลงในหน่วยความจำแฟลชได้ หน่วยความจำแฟลชต้องเขียนโดยใช้ที่อยู่ที่กำหนด โดยระบุว่าจะเขียนที่ไหนและขนาดที่เขียน คล้ายกับการอัปเดตอาร์เรย์ของไบต์ในหน่วยความจำ หน่วยความจำแฟลชมีความละเอียด หมายความว่าการลบและการเขียนต้องไม่เพียงแต่มีขนาดคงที่ แต่ยังต้องจัดตำแหน่งให้ตรงกับขนาดนั้นด้วย ตัวอย่างเช่น หากความละเอียดคือ 4096 ไบต์ และคุณขอลบที่อยู่ 4200 อาจลบข้อมูลทั้งหมดตั้งแต่ที่อยู่ 4096 ถึง 8192 ซึ่งหมายความว่าเมื่อคุณเขียนข้อมูลเสียงลงในหน่วยความจำแฟลช จะต้องเป็นชิ้นส่วนที่มีขนาดถูกต้อง

### งาน - ตั้งค่าหน่วยความจำแฟลช

1. สร้างโปรเจกต์ Wio Terminal ใหม่โดยใช้ PlatformIO ตั้งชื่อโปรเจกต์นี้ว่า `smart-timer` เพิ่มโค้ดในฟังก์ชัน `setup` เพื่อกำหนดค่าพอร์ตอนุกรม

1. เพิ่มไลบรารีที่จำเป็นต่อไปนี้ลงในไฟล์ `platformio.ini` เพื่อให้สามารถเข้าถึงหน่วยความจำแฟลช:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. เปิดไฟล์ `main.cpp` และเพิ่มคำสั่ง include สำหรับไลบรารีหน่วยความจำแฟลชที่ด้านบนของไฟล์:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD ย่อมาจาก Serial Flash Universal Driver และเป็นไลบรารีที่ออกแบบมาเพื่อทำงานกับชิปหน่วยความจำแฟลชทุกประเภท

1. ในฟังก์ชัน `setup` เพิ่มโค้ดต่อไปนี้เพื่อกำหนดค่าไลบรารีหน่วยความจำแฟลช:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    โค้ดนี้จะวนซ้ำจนกว่าไลบรารี SFUD จะถูกเริ่มต้นใช้งาน จากนั้นเปิดการอ่านแบบรวดเร็ว หน่วยความจำแฟลชในตัวสามารถเข้าถึงได้โดยใช้ Queued Serial Peripheral Interface (QSPI) ซึ่งเป็นตัวควบคุม SPI ประเภทหนึ่งที่อนุญาตให้เข้าถึงอย่างต่อเนื่องผ่านคิวโดยใช้โปรเซสเซอร์น้อยที่สุด สิ่งนี้ทำให้การอ่านและเขียนหน่วยความจำแฟลชเร็วขึ้น

1. สร้างไฟล์ใหม่ในโฟลเดอร์ `src` ชื่อ `flash_writer.h`

1. เพิ่มโค้ดต่อไปนี้ที่ด้านบนของไฟล์นี้:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    โค้ดนี้รวมไฟล์ header ที่จำเป็นบางไฟล์ รวมถึงไฟล์ header สำหรับไลบรารี SFUD เพื่อโต้ตอบกับหน่วยความจำแฟลช

1. กำหนดคลาสในไฟล์ header ใหม่นี้ชื่อ `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. ในส่วน `private` เพิ่มโค้ดต่อไปนี้:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    โค้ดนี้กำหนดฟิลด์บางส่วนสำหรับบัฟเฟอร์ที่จะใช้ในการจัดเก็บข้อมูลก่อนที่จะเขียนลงในหน่วยความจำแฟลช มีอาร์เรย์ไบต์ `_sfudBuffer` เพื่อเขียนข้อมูล และเมื่อเต็ม ข้อมูลจะถูกเขียนลงในหน่วยความจำแฟลช ฟิลด์ `_sfudBufferPos` จะเก็บตำแหน่งปัจจุบันที่จะเขียนในบัฟเฟอร์นี้ และ `_sfudBufferWritePos` จะเก็บตำแหน่งในหน่วยความจำแฟลชที่จะเขียน `_flash` เป็นตัวชี้ไปยังหน่วยความจำแฟลชที่จะเขียน - ไมโครคอนโทรลเลอร์บางตัวมีชิปหน่วยความจำแฟลชหลายตัว

1. เพิ่มเมธอดต่อไปนี้ในส่วน `public` เพื่อเริ่มต้นคลาสนี้:

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

    โค้ดนี้กำหนดค่าหน่วยความจำแฟลชบน Wio Terminal เพื่อเขียน และตั้งค่าบัฟเฟอร์ตามขนาดของหน่วยความจำแฟลช โค้ดนี้อยู่ในเมธอด `init` แทนที่จะเป็น constructor เนื่องจากต้องเรียกใช้หลังจากหน่วยความจำแฟลชถูกตั้งค่าในฟังก์ชัน `setup`

1. เพิ่มโค้ดต่อไปนี้ในส่วน `public`:

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

    โค้ดนี้กำหนดเมธอดเพื่อเขียนไบต์ลงในระบบจัดเก็บข้อมูลแฟลช มันทำงานโดยการเขียนลงในบัฟเฟอร์ในหน่วยความจำที่มีขนาดเหมาะสมสำหรับหน่วยความจำแฟลช และเมื่อเต็ม จะเขียนลงในหน่วยความจำแฟลช โดยลบข้อมูลที่มีอยู่ในตำแหน่งนั้น นอกจากนี้ยังมี `flushSfudBuffer` เพื่อเขียนบัฟเฟอร์ที่ไม่สมบูรณ์ เนื่องจากข้อมูลที่บันทึกจะไม่เป็นจำนวนเท่าของขนาดหน่วยความจำแฟลช ดังนั้นส่วนท้ายของข้อมูลจะต้องถูกเขียน

    > 💁 ส่วนท้ายของข้อมูลจะเขียนข้อมูลที่ไม่ต้องการเพิ่มเติม แต่ไม่เป็นไรเพราะจะอ่านเฉพาะข้อมูลที่ต้องการเท่านั้น

### งาน - ตั้งค่าการบันทึกเสียง

1. สร้างไฟล์ใหม่ในโฟลเดอร์ `src` ชื่อ `config.h`

1. เพิ่มโค้ดต่อไปนี้ที่ด้านบนของไฟล์นี้:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    โค้ดนี้ตั้งค่าค่าคงที่บางอย่างสำหรับการบันทึกเสียง

    | ค่าคงที่              | ค่า    | คำอธิบาย |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | อัตราการสุ่มตัวอย่างสำหรับเสียง 16,000 คือ 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | ความยาวของเสียงที่จะบันทึก ตั้งค่าเป็น 4 วินาที หากต้องการบันทึกเสียงนานขึ้น ให้เพิ่มค่านี้ |
    | SAMPLES               | 64000  | จำนวนตัวอย่างเสียงทั้งหมดที่จะบันทึก ตั้งค่าเป็นอัตราการสุ่มตัวอย่าง * จำนวนวินาที |
    | BUFFER_SIZE           | 128044 | ขนาดของบัฟเฟอร์เสียงที่จะบันทึก เสียงจะถูกบันทึกเป็นไฟล์ WAV ซึ่งมีส่วนหัว 44 ไบต์ และข้อมูลเสียง 128,000 ไบต์ (แต่ละตัวอย่างมี 2 ไบต์) |
    | ADC_BUF_LEN           | 1600   | ขนาดของบัฟเฟอร์ที่จะใช้ในการบันทึกเสียงจาก DMAC |

    > 💁 หากคุณพบว่า 4 วินาทีสั้นเกินไปสำหรับการขอจับเวลา คุณสามารถเพิ่มค่าของ `SAMPLE_LENGTH_SECONDS` และค่าทั้งหมดจะถูกคำนวณใหม่

1. สร้างไฟล์ใหม่ในโฟลเดอร์ `src` ชื่อ `mic.h`

1. เพิ่มโค้ดต่อไปนี้ที่ด้านบนของไฟล์นี้:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    โค้ดนี้รวมไฟล์ header ที่จำเป็นบางไฟล์ รวมถึงไฟล์ header `config.h` และ `FlashWriter`

1. เพิ่มโค้ดต่อไปนี้เพื่อกำหนดคลาส `Mic` ที่สามารถบันทึกเสียงจากไมโครโฟน:

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

    คลาสนี้มีฟิลด์เพียงไม่กี่ตัวเพื่อบันทึกว่าการบันทึกเริ่มต้นหรือไม่ และการบันทึกพร้อมใช้งานหรือไม่ เมื่อ DMAC ถูกตั้งค่า มันจะเขียนลงในบัฟเฟอร์หน่วยความจำอย่างต่อเนื่อง ดังนั้นตัวแปร `_isRecording` จะกำหนดว่าควรประมวลผลหรือไม่ `_isRecordingReady` จะถูกตั้งค่าเมื่อบันทึกเสียงครบ 4 วินาที `_writer` ใช้ในการบันทึกข้อมูลเสียงลงในหน่วยความจำแฟลช

    จากนั้นตัวแปร global จะถูกประกาศสำหรับอินสแตนซ์ของคลาส `Mic`

1. เพิ่มโค้ดต่อไปนี้ในส่วน `private` ของคลาส `Mic`:

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

    โค้ดนี้กำหนดเมธอด `configureDmaAdc` เพื่อกำหนดค่า DMAC โดยเชื่อมต่อกับ ADC และตั้งค่าให้เติมบัฟเฟอร์สองตัวที่สลับกัน `_adc_buf_0` และ `_adc_buf_1`

    > 💁 หนึ่งในข้อเสียของการพัฒนาไมโครคอนโทรลเลอร์คือความซับซ้อนของโค้ดที่จำเป็นในการโต้ตอบกับฮาร์ดแวร์ เนื่องจากโค้ดของคุณทำงานในระดับต่ำมากที่โต้ตอบกับฮาร์ดแวร์โดยตรง โค้ดนี้ซับซ้อนกว่าที่คุณจะเขียนสำหรับคอมพิวเตอร์บอร์ดเดียวหรือคอมพิวเตอร์เดสก์ท็อป เนื่องจากไม่มีระบบปฏิบัติการช่วยเหลือ มีไลบรารีบางตัวที่สามารถทำให้สิ่งนี้ง่ายขึ้น แต่ก็ยังมีความซับซ้อนอยู่

1. ด้านล่างนี้ เพิ่มโค้ดต่อไปนี้:

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

    โค้ดนี้กำหนดส่วนหัว WAV เป็น struct ที่ใช้หน่วยความจำ 44 ไบต์ มันเขียนรายละเอียดเกี่ยวกับอัตราไฟล์เสียง ขนาด และจำนวนช่อง จากนั้นส่วนหัวนี้จะถูกเขียนลงในหน่วยความจำแฟลช

1. ด้านล่างโค้ดนี้ เพิ่มโค้ดต่อไปนี้เพื่อประกาศเมธอดที่จะถูกเรียกเมื่อบัฟเฟอร์เสียงพร้อมที่จะประมวลผล:

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

    บัฟเฟอร์เสียงเป็นอาร์เรย์ของตัวเลข 16 บิตที่มีเสียงจาก ADC ADC จะส่งคืนค่าที่ไม่ได้ลงนาม 12 บิต (0-1023) ดังนั้นค่าต้องถูกแปลงเป็นค่าที่ลงนาม 16 บิต และจากนั้นแปลงเป็น 2 ไบต์เพื่อจัดเก็บเป็นข้อมูลไบนารีดิบ

    ไบต์เหล่านี้จะถูกเขียนลงในบัฟเฟอร์หน่วยความจำแฟลช การเขียนเริ่มต้นที่ดัชนี 44 - นี่คือการชดเชยจาก 44 ไบต์ที่เขียนเป็นส่วนหัวไฟล์ WAV เมื่อบันทึกไบต์ทั้งหมดที่จำเป็นสำหรับความยาวเสียงที่ต้องการแล้ว ข้อมูลที่เหลือจะถูกเขียนลงในหน่วยความจำแฟลช

1. ในส่วน `public` ของคลาส `Mic` เพิ่มโค้ดต่อไปนี้:

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

    โค้ดนี้จะถูกเรียกโดย DMAC เพื่อบอกโค้ดของคุณให้ประมวลผลบัฟเฟอร์ มันตรวจสอบว่ามีข้อมูลให้ประมวลผลหรือไม่ และเรียกเมธอด `audioCallback` พร้อมบัฟเฟอร์ที่เกี่ยวข้อง

1. นอกคลาส หลังจากการประกาศ `Mic mic;` เพิ่มโค้ดต่อไปนี้:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    `DMAC_1_Handler` จะถูกเรียกโดย DMAC เมื่อบัฟเฟอร์พร้อมที่จะประมวลผล ฟังก์ชันนี้จะถูกค้นหาตามชื่อ ดังนั้นเพียงแค่ต้องมีอยู่เพื่อให้ถูกเรียก

1. เพิ่มเมธอดสองตัวต่อไปนี้ในส่วน `public` ของคลาส `Mic`:

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

    เมธอด `init` มีโค้ดเพื่อเริ่มต้นคลาส `Mic` เมธอดนี้ตั้งค่าแรงดันไฟฟ้าที่ถูกต้องสำหรับพินไมโครโฟน ตั้งค่าตัวเขียนหน่วยความจำแฟลช เขียนส่วนหัวไฟล์ WAV และกำหนดค่า DMAC เมธอด `reset` จะรีเซ็ตหน่วยความจำแฟลชและเขียนส่วนหัวใหม่หลังจากที่เสียงถูกบันทึกและใช้งานแล้ว

### งาน - บันทึกเสียง

1. ในไฟล์ `main.cpp` เพิ่มคำสั่ง include สำหรับไฟล์ header `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. ในฟังก์ชัน `setup` กำหนดค่าปุ่ม C การบันทึกเสียงจะเริ่มต้นเมื่อกดปุ่มนี้ และดำเนินต่อไปเป็นเวลา 4 วินาที:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. ด้านล่างนี้ เริ่มต้นไมโครโฟน จากนั้นพิมพ์ไปยังคอนโซลว่าเสียงพร้อมที่จะบันทึก:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. เหนือฟังก์ชัน `loop` กำหนดฟังก์ชันเพื่อประมวลผลเสียงที่บันทึกไว้ สำหรับตอนนี้ฟังก์ชันนี้จะไม่ทำอะไร แต่ในบทเรียนนี้จะส่งเสียงเพื่อแปลงเป็นข้อความ:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. เพิ่มโค้ดต่อไปนี้ในฟังก์ชัน `loop`:

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

    โค้ดนี้ตรวจสอบปุ่ม C และหากกดปุ่มนี้และยังไม่ได้เริ่มการบันทึก ตัวแปร `_isRecording` ของคลาส `Mic` จะถูกตั้งค่าเป็น true สิ่งนี้จะทำให้เมธอด `audioCallback` ของคลาส `Mic` จัดเก็บเสียงจนกว่าจะบันทึกครบ 4 วินาที เมื่อบันทึกเสียงครบ 4 วินาที ตัวแปร `_isRecording` จะถูกตั้งค่าเป็น false และตัวแปร `_isRecordingReady` จะถูกตั้งค่าเป็น true จากนั้นจะถูกตรวจสอบในฟังก์ชัน `loop` และเมื่อเป็น true ฟังก์ชัน `processAudio` จะถูกเรียก จากนั้นคลาส `Mic` จะถูกรีเซ็ต

1. สร้างโค้ดนี้ อัปโหลดไปยัง Wio Terminal ของคุณ และทดสอบผ่าน serial monitor กดปุ่ม C (ปุ่มที่อยู่ด้านซ้ายมือ ใกล้กับสวิตช์เปิดปิด) และพูด เสียง 4 วินาทีจะถูกบันทึก

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 คุณสามารถค้นหาโค้ดนี้ได้ในโฟลเดอร์ [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal)
😀 โปรแกรมบันทึกเสียงของคุณประสบความสำเร็จ!

---

**ข้อจำกัดความรับผิดชอบ**:  
เอกสารนี้ได้รับการแปลโดยใช้บริการแปลภาษา AI [Co-op Translator](https://github.com/Azure/co-op-translator) แม้ว่าเราจะพยายามให้การแปลมีความถูกต้องมากที่สุด แต่โปรดทราบว่าการแปลอัตโนมัติอาจมีข้อผิดพลาดหรือความไม่ถูกต้อง เอกสารต้นฉบับในภาษาดั้งเดิมควรถือเป็นแหล่งข้อมูลที่เชื่อถือได้ สำหรับข้อมูลที่สำคัญ ขอแนะนำให้ใช้บริการแปลภาษามืออาชีพ เราไม่รับผิดชอบต่อความเข้าใจผิดหรือการตีความผิดที่เกิดจากการใช้การแปลนี้