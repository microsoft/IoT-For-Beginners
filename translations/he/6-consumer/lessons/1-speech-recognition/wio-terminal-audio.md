<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2f336726b9410e97c3aaed76cc89b0d8",
  "translation_date": "2025-08-27T22:38:37+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-audio.md",
  "language_code": "he"
}
-->
# לכידת שמע - Wio Terminal

בחלק זה של השיעור, תכתבו קוד ללכידת שמע ב-Wio Terminal שלכם. לכידת השמע תתבצע באמצעות אחד הכפתורים בחלק העליון של ה-Wio Terminal.

## תכנות המכשיר ללכידת שמע

ניתן ללכוד שמע מהמיקרופון באמצעות קוד C++. ל-Wio Terminal יש רק 192KB של זיכרון RAM, מה שלא מספיק ללכידת יותר מכמה שניות של שמע. עם זאת, יש לו 4MB של זיכרון פלאש, שניתן להשתמש בו במקום זאת, ולשמור את השמע שנלכד בזיכרון הפלאש.

המיקרופון המובנה לוכד אות אנלוגי, שמומר לאות דיגיטלי שה-Wio Terminal יכול להשתמש בו. בעת לכידת שמע, יש ללכוד את הנתונים בזמן הנכון - לדוגמה, כדי ללכוד שמע ב-16KHz, יש ללכוד את השמע בדיוק 16,000 פעמים בשנייה, עם מרווחים שווים בין כל דגימה. במקום להשתמש בקוד שלכם כדי לעשות זאת, ניתן להשתמש בבקר גישה ישירה לזיכרון (DMAC). זהו מעגל שמסוגל ללכוד אות ממקור מסוים ולכתוב אותו לזיכרון, מבלי להפריע לקוד שלכם שרץ על המעבד.

✅ קראו עוד על DMA בעמוד [גישה ישירה לזיכרון בויקיפדיה](https://wikipedia.org/wiki/Direct_memory_access).

![שמע מהמיקרופון עובר ל-ADC ואז ל-DMAC. זה כותב למאגר אחד. כשהמאגר הזה מתמלא, הוא מעובד וה-DMAC כותב למאגר שני](../../../../../translated_images/he/dmac-adc-buffers.4509aee49145c90bc2e1be472b8ed2ddfcb2b6a81ad3e559114aca55f5fff759.png)

ה-DMAC יכול ללכוד שמע מה-ADC במרווחים קבועים, כמו 16,000 פעמים בשנייה עבור שמע ב-16KHz. הוא יכול לכתוב את הנתונים שנלכדו למאגר זיכרון שהוקצה מראש, וכשהמאגר הזה מתמלא, הוא הופך לזמין לקוד שלכם לעיבוד. שימוש בזיכרון זה יכול לעכב את לכידת השמע, אך ניתן להגדיר מספר מאגרים. ה-DMAC כותב למאגר 1, ואז כשהוא מתמלא, הוא מודיע לקוד שלכם לעבד את מאגר 1, בזמן שה-DMAC כותב למאגר 2. כשהמאגר השני מתמלא, הוא מודיע לקוד שלכם, וחוזר לכתיבה למאגר 1. כך, כל עוד אתם מעבדים כל מאגר בזמן קצר יותר מהזמן שלוקח למלא אחד, לא תאבדו נתונים.

לאחר שכל מאגר נלכד, ניתן לכתוב אותו לזיכרון הפלאש. יש לכתוב לזיכרון הפלאש באמצעות כתובות מוגדרות, המפרטות היכן לכתוב וכמה לכתוב, בדומה לעדכון מערך של בתים בזיכרון. לזיכרון הפלאש יש גרנולריות, כלומר פעולות מחיקה וכתיבה תלויות לא רק בגודל קבוע, אלא גם בהתאמה לגודל הזה. לדוגמה, אם הגרנולריות היא 4096 בתים ואתם מבקשים מחיקה בכתובת 4200, זה יכול למחוק את כל הנתונים מכתובת 4096 עד 8192. משמעות הדבר היא שכאשר אתם כותבים את נתוני השמע לזיכרון הפלאש, זה חייב להיות במקטעים בגודל הנכון.

### משימה - הגדרת זיכרון פלאש

1. צרו פרויקט חדש ל-Wio Terminal באמצעות PlatformIO. קראו לפרויקט הזה `smart-timer`. הוסיפו קוד בפונקציה `setup` כדי להגדיר את יציאת הסריאל.

1. הוסיפו את התלויות הבאות לקובץ `platformio.ini` כדי לספק גישה לזיכרון הפלאש:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
    ```

1. פתחו את הקובץ `main.cpp` והוסיפו את ההנחיה הבאה לכלול את ספריית זיכרון הפלאש בראש הקובץ:

    ```cpp
    #include <sfud.h>
    #include <SPI.h>
    ```

    > 🎓 SFUD מייצג את Serial Flash Universal Driver, והוא ספרייה שנועדה לעבוד עם כל שבבי זיכרון הפלאש.

1. בפונקציה `setup`, הוסיפו את הקוד הבא כדי להגדיר את ספריית אחסון הפלאש:

    ```cpp
    while (!(sfud_init() == SFUD_SUCCESS))
        ;

    sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
    ```

    הקוד הזה מבצע לולאה עד שהספרייה SFUD מאותחלת, ואז מפעיל קריאות מהירות. ניתן לגשת לזיכרון הפלאש המובנה באמצעות Queued Serial Peripheral Interface (QSPI), סוג של בקר SPI שמאפשר גישה רציפה דרך תור עם שימוש מינימלי במעבד. זה הופך את הקריאה והכתיבה לזיכרון הפלאש למהירות יותר.

1. צרו קובץ חדש בתיקיית `src` בשם `flash_writer.h`.

1. הוסיפו את הקוד הבא לראש הקובץ:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <sfud.h>
    ```

    הקוד הזה כולל כמה קבצי כותרת נחוצים, כולל קובץ הכותרת של ספריית SFUD כדי לתקשר עם זיכרון הפלאש.

1. הגדירו מחלקה חדשה בקובץ הכותרת הזה בשם `FlashWriter`:

    ```cpp
    class FlashWriter
    {
    public:
    
    private:
    };
    ```

1. בסעיף `private`, הוסיפו את הקוד הבא:

    ```cpp
    byte *_sfudBuffer;
    size_t _sfudBufferSize;
    size_t _sfudBufferPos;
    size_t _sfudBufferWritePos;

    const sfud_flash *_flash;
    ```

    הקוד הזה מגדיר כמה שדות עבור המאגר שישמש לאחסון נתונים לפני כתיבתם לזיכרון הפלאש. יש מערך בתים, `_sfudBuffer`, לכתיבת נתונים אליו, וכשהוא מתמלא, הנתונים נכתבים לזיכרון הפלאש. השדה `_sfudBufferPos` מאחסן את המיקום הנוכחי לכתיבה במאגר הזה, ו-`_sfudBufferWritePos` מאחסן את המיקום בזיכרון הפלאש לכתיבה. `_flash` הוא מצביע לזיכרון הפלאש לכתיבה - לחלק מהבקרים יש מספר שבבי זיכרון פלאש.

1. הוסיפו את השיטה הבאה לסעיף `public` כדי לאתחל את המחלקה הזו:

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

    הקוד הזה מגדיר את זיכרון הפלאש ב-Wio Terminal לכתיבה, ומגדיר את המאגרים בהתבסס על גודל הגרנולריות של זיכרון הפלאש. זה נמצא בשיטת `init`, ולא בבנאי, מכיוון שיש לקרוא לזה לאחר שזיכרון הפלאש הוגדר בפונקציה `setup`.

1. הוסיפו את הקוד הבא לסעיף `public`:

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

    הקוד הזה מגדיר שיטות לכתיבת בתים למערכת אחסון הפלאש. זה עובד על ידי כתיבה למאגר בזיכרון שהוא בגודל הנכון עבור זיכרון הפלאש, וכשהוא מתמלא, הוא נכתב לזיכרון הפלאש, תוך מחיקת כל נתונים קיימים במיקום הזה. יש גם `flushSfudBuffer` לכתיבת מאגר לא שלם, מכיוון שהנתונים שנלכדים לא יהיו כפולות מדויקות של גודל הגרנולריות, ולכן יש לכתוב את החלק האחרון של הנתונים.

    > 💁 החלק האחרון של הנתונים יכתוב נתונים נוספים לא רצויים, אבל זה בסדר מכיוון שרק הנתונים הדרושים ייקראו.

### משימה - הגדרת לכידת שמע

1. צרו קובץ חדש בתיקיית `src` בשם `config.h`.

1. הוסיפו את הקוד הבא לראש הקובץ:

    ```cpp
    #pragma once

    #define RATE 16000
    #define SAMPLE_LENGTH_SECONDS 4
    #define SAMPLES RATE * SAMPLE_LENGTH_SECONDS
    #define BUFFER_SIZE (SAMPLES * 2) + 44
    #define ADC_BUF_LEN 1600
    ```

    הקוד הזה מגדיר כמה קבועים עבור לכידת השמע.

    | קבוע                | ערך   | תיאור |
    | --------------------- | -----: | - |
    | RATE                  | 16000  | קצב הדגימה של השמע. 16,000 הוא 16KHz |
    | SAMPLE_LENGTH_SECONDS | 4      | אורך השמע ללכידה. זה מוגדר ל-4 שניות. כדי להקליט שמע ארוך יותר, הגדילו את הערך הזה. |
    | SAMPLES               | 64000  | המספר הכולל של דגימות שמע שיילכדו. מוגדר כקצב הדגימה * מספר השניות |
    | BUFFER_SIZE           | 128044 | גודל מאגר השמע ללכידה. השמע יילכד כקובץ WAV, שהוא 44 בתים של כותרת, ואז 128,000 בתים של נתוני שמע (כל דגימה היא 2 בתים) |
    | ADC_BUF_LEN           | 1600   | גודל המאגרים לשימוש ללכידת שמע מה-DMAC |

    > 💁 אם אתם מוצאים ש-4 שניות זה קצר מדי לבקשת טיימר, תוכלו להגדיל את הערך `SAMPLE_LENGTH_SECONDS`, וכל הערכים האחרים יחושבו מחדש.

1. צרו קובץ חדש בתיקיית `src` בשם `mic.h`.

1. הוסיפו את הקוד הבא לראש הקובץ:

    ```cpp
    #pragma once

    #include <Arduino.h>

    #include "config.h"
    #include "flash_writer.h"
    ```

    הקוד הזה כולל כמה קבצי כותרת נחוצים, כולל קובץ הכותרת `config.h` וקובץ הכותרת `FlashWriter`.

1. הוסיפו את הקוד הבא כדי להגדיר מחלקה `Mic` שיכולה ללכוד מהמיקרופון:

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

    למחלקה הזו יש כרגע רק כמה שדות למעקב אם ההקלטה התחילה, ואם הקלטה מוכנה לשימוש. כאשר ה-DMAC מוגדר, הוא כותב באופן רציף למאגרים בזיכרון, כך שהדגל `_isRecording` קובע אם יש לעבד אותם או להתעלם מהם. הדגל `_isRecordingReady` יוגדר כאשר 4 שניות של שמע נלכדו. השדה `_writer` משמש לשמירת נתוני השמע בזיכרון הפלאש.

    משתנה גלובלי מוגדר לאחר מכן עבור מופע של מחלקת `Mic`.

1. הוסיפו את הקוד הבא לסעיף `private` של מחלקת `Mic`:

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

    הקוד הזה מגדיר שיטה `configureDmaAdc` שמגדירה את ה-DMAC, מחברת אותו ל-ADC ומגדירה אותו לאכלס שני מאגרים מתחלפים, `_adc_buf_0` ו-`_adc_buf_1`.

    > 💁 אחד החסרונות בפיתוח בקרי מיקרו הוא המורכבות של הקוד הדרוש לאינטראקציה עם חומרה, מכיוון שהקוד שלכם פועל ברמה נמוכה מאוד ומתקשר ישירות עם החומרה. הקוד הזה מורכב יותר ממה שהייתם כותבים עבור מחשב לוח יחיד או מחשב שולחני מכיוון שאין מערכת הפעלה שתעזור. ישנן ספריות זמינות שיכולות לפשט זאת, אך עדיין יש הרבה מורכבות.

1. מתחת לזה, הוסיפו את הקוד הבא:

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

    הקוד הזה מגדיר את כותרת קובץ ה-WAV כ-struct שתופס 44 בתים בזיכרון. הוא כותב פרטים לכותרת על קצב הקובץ, גודל ומספר הערוצים. הכותרת הזו נכתבת לאחר מכן לזיכרון הפלאש.

1. מתחת לקוד הזה, הוסיפו את הקוד הבא כדי להכריז על שיטה שתיקרא כאשר המאגרים מוכנים לעיבוד:

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

    המאגרים הם מערכים של מספרים שלמים בגודל 16 ביט המכילים את השמע מה-ADC. ה-ADC מחזיר ערכים לא חתומים בגודל 12 ביט (0-1023), ולכן יש להמיר אותם לערכים חתומים בגודל 16 ביט, ואז להמיר אותם ל-2 בתים כדי לאחסן אותם כנתונים בינאריים גולמיים.

    בתים אלו נכתבים למאגרים בזיכרון הפלאש. הכתיבה מתחילה באינדקס 44 - זהו ההיסט מ-44 בתים שנכתבו ככותרת קובץ ה-WAV. לאחר שכל הבתים הדרושים לאורך השמע הנדרש נלכדו, הנתונים הנותרים נכתבים לזיכרון הפלאש.

1. בסעיף `public` של מחלקת `Mic`, הוסיפו את הקוד הבא:

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

    הקוד הזה ייקרא על ידי ה-DMAC כדי להודיע לקוד שלכם לעבד את המאגרים. הוא בודק שיש נתונים לעיבוד, וקורא לשיטה `audioCallback` עם המאגר הרלוונטי.

1. מחוץ למחלקה, לאחר ההכרזה `Mic mic;`, הוסיפו את הקוד הבא:

    ```cpp
    void DMAC_1_Handler()
    {
        mic.dmaHandler();
    }
    ```

    הפונקציה `DMAC_1_Handler` תיקרא על ידי ה-DMAC כאשר המאגרים מוכנים לעיבוד. הפונקציה הזו נמצאת לפי שם, ולכן רק צריכה להתקיים כדי להיקרא.

1. הוסיפו את שתי השיטות הבאות לסעיף `public` של מחלקת `Mic`:

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

    שיטת `init` מכילה קוד לאתחול מחלקת `Mic`. השיטה הזו מגדירה את המתח הנכון עבור פין המיקרופון, מגדירה את כותב זיכרון הפלאש, כותבת את כותרת קובץ ה-WAV, ומגדירה את ה-DMAC. שיטת `reset` מאפסת את זיכרון הפלאש וכותבת מחדש את הכותרת לאחר שהשמע נלכד ושומש.

### משימה - לכידת שמע

1. בקובץ `main.cpp`, הוסיפו הנחיה לכלול את קובץ הכותרת `mic.h`:

    ```cpp
    #include "mic.h"
    ```

1. בפונקציה `setup`, אתחלו את כפתור C. לכידת השמע תתחיל כאשר הכפתור הזה נלחץ, ותימשך 4 שניות:

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

1. מתחת לזה, אתחלו את המיקרופון, ואז הדפיסו לקונסולה שהשמע מוכן ללכידה:

    ```cpp
    mic.init();

    Serial.println("Ready.");
    ```

1. מעל הפונקציה `loop`, הגדירו פונקציה לעיבוד השמע שנלכד. כרגע הפונקציה הזו לא עושה כלום, אך בהמשך השיעור היא תשלח את הדיבור להמרה לטקסט:

    ```cpp
    void processAudio()
    {
    
    }
    ```

1. הוסיפו את הקוד הבא לפונקציה `loop`:

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

    הקוד הזה בודק את כפתור C, ואם הוא נלחץ וההקלטה לא התחילה, אז השדה `_isRecording` של מחלקת `Mic` מוגדר ל-true. זה יגרום לשיטה `audioCallback` של מחלקת `Mic` לאחסן שמע עד ש-4 שניות נלכדו. לאחר ש-4 שניות של שמע נלכדו, השדה `_isRecording` מוגדר ל-false, והשדה `_isRecordingReady` מוגדר ל-true. זה נבדק בפונקציה `loop`, וכאשר הוא true, הפונקציה `processAudio` נקראת, ואז מחלקת המיקרופון מאופסת.

1. בנו את הקוד הזה, העלו אותו ל-Wio Terminal שלכם ובדקו אותו דרך המוניטור הסריאלי. לחצו על כפתור C (זה שבצד שמאל, הקרוב ביותר למתג ההפעלה), ודברו. 4 שניות של שמע יילכדו.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Ready.
    Starting recording...
    Finished recording
    ```
💁 ניתן למצוא את הקוד בתיקיית [code-record/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-record/wio-terminal).
😀 תוכנת הקלטת האודיו שלך הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.