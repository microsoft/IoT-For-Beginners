# צילום תמונה - Wio Terminal

בחלק זה של השיעור, תוסיף מצלמה ל-Wio Terminal שלך ותצלם תמונות ממנה.

## חומרה

ה-Wio Terminal זקוק למצלמה.

המצלמה שבה תשתמש היא [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). זו מצלמה של 2 מגה-פיקסל המבוססת על חיישן תמונה OV2640. היא מתקשרת באמצעות ממשק SPI לצילום תמונות ומשתמשת ב-I2C כדי להגדיר את החיישן.

## חיבור המצלמה

ל-ArduCam אין שקע Grove, במקום זאת היא מתחברת גם ל-SPI וגם ל-I2C דרך פיני GPIO ב-Wio Terminal.

### משימה - חיבור המצלמה

חבר את המצלמה.

![חיישן ArduCam](../../../../../translated_images/he/arducam.20e4e4cbb2682965.webp)

1. הפינים בבסיס ה-ArduCam צריכים להיות מחוברים לפיני GPIO ב-Wio Terminal. כדי להקל על מציאת הפינים הנכונים, הצמד את מדבקת פיני GPIO שמגיעה עם ה-Wio Terminal סביב הפינים:

    ![ה-Wio Terminal עם מדבקת פיני GPIO](../../../../../translated_images/he/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. באמצעות חוטי ג'אמפר, בצע את החיבורים הבאים:

    | פין ArduCAM | פין Wio Terminal | תיאור                                   |
    | ----------- | ---------------- | --------------------------------------- |
    | CS          | 24 (SPI_CS)      | בחירת שבב SPI                           |
    | MOSI        | 19 (SPI_MOSI)    | יציאת בקר SPI, כניסת התקן היקפי         |
    | MISO        | 21 (SPI_MISO)    | כניסת בקר SPI, יציאת התקן היקפי         |
    | SCK         | 23 (SPI_SCLK)    | שעון סדרתי SPI                          |
    | GND         | 6 (GND)          | אדמה - 0V                               |
    | VCC         | 4 (5V)           | ספק כוח 5V                              |
    | SDA         | 3 (I2C1_SDA)     | נתונים סדרתיים I2C                     |
    | SCL         | 5 (I2C1_SCL)     | שעון סדרתי I2C                          |

    ![ה-Wio Terminal מחובר ל-ArduCam עם חוטי ג'אמפר](../../../../../translated_images/he/arducam-wio-terminal-connections.a4d5a4049bdb5ab8.webp)

    חיבורי GND ו-VCC מספקים ספק כוח של 5V ל-ArduCam. הוא פועל ב-5V, בניגוד לחיישני Grove שפועלים ב-3V. כוח זה מגיע ישירות מחיבור ה-USB-C שמספק כוח למכשיר.

    > 💁 עבור חיבור SPI, תוויות הפינים ב-ArduCam ושמות הפינים ב-Wio Terminal המשמשים בקוד עדיין משתמשים במוסכמת השמות הישנה. ההוראות בשיעור זה ישתמשו במוסכמת השמות החדשה, למעט כאשר שמות הפינים משמשים בקוד.

1. כעת תוכל לחבר את ה-Wio Terminal למחשב שלך.

## תכנות המכשיר להתחבר למצלמה

כעת ניתן לתכנת את ה-Wio Terminal להשתמש במצלמת ArduCAM המחוברת.

### משימה - תכנות המכשיר להתחבר למצלמה

1. צור פרויקט חדש ל-Wio Terminal באמצעות PlatformIO. קרא לפרויקט זה `fruit-quality-detector`. הוסף קוד לפונקציית `setup` כדי להגדיר את יציאת הסריאל.

1. הוסף קוד להתחברות ל-WiFi, עם פרטי ה-WiFi שלך בקובץ שנקרא `config.h`. אל תשכח להוסיף את הספריות הנדרשות לקובץ `platformio.ini`.

1. ספריית ArduCam אינה זמינה כספריית Arduino שניתן להתקין מקובץ `platformio.ini`. במקום זאת, יש להתקין אותה ממקור בעמוד GitHub שלהם. ניתן להשיג זאת על ידי:

    * שיבוט הריפו מ-[https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * מעבר לריפו ב-GitHub בכתובת [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) והורדת הקוד כקובץ zip מכפתור **Code**

1. אתה זקוק רק לתיקיית `ArduCAM` מהקוד הזה. העתק את כל התיקייה לתוך תיקיית `lib` בפרויקט שלך.

    > ⚠️ יש להעתיק את כל התיקייה, כך שהקוד יהיה ב-`lib/ArduCam`. אל תעתיק רק את התוכן של תיקיית `ArduCam` לתוך תיקיית `lib`, העתק את כל התיקייה.

1. קוד ספריית ArduCam עובד עבור סוגים שונים של מצלמות. סוג המצלמה שברצונך להשתמש בו מוגדר באמצעות דגלי קומפילציה - זה שומר על הספרייה הבנויה קטנה ככל האפשר על ידי הסרת קוד עבור מצלמות שאינך משתמש בהן. כדי להגדיר את הספרייה עבור מצלמת OV2640, הוסף את הדברים הבאים לסוף קובץ `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    זה מגדיר שני דגלי קומפילציה:

      * `ARDUCAM_SHIELD_V2` כדי להודיע לספרייה שהמצלמה נמצאת על לוח Arduino, המכונה מגן.
      * `OV2640_CAM` כדי להודיע לספרייה לכלול רק קוד עבור מצלמת OV2640.

1. הוסף קובץ כותרת לתיקיית `src` בשם `camera.h`. קובץ זה יכיל קוד לתקשורת עם המצלמה. הוסף את הקוד הבא לקובץ זה:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    זהו קוד ברמה נמוכה שמגדיר את המצלמה באמצעות ספריות ArduCam ומוציא את התמונות כאשר נדרש באמצעות אוטובוס SPI. קוד זה מאוד ספציפי ל-ArduCam, כך שאין צורך לדאוג כיצד הוא עובד בשלב זה.

1. ב-`main.cpp`, הוסף את הקוד הבא מתחת להצהרות `include` האחרות כדי לכלול את הקובץ החדש וליצור מופע של מחלקת המצלמה:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    זה יוצר `Camera` ששומר את התמונות כ-JPEG ברזולוציה של 640 על 480. למרות שתומכים ברזולוציות גבוהות יותר (עד 3280x2464), מסווג התמונות עובד על תמונות קטנות בהרבה (227x227), כך שאין צורך לצלם ולשלוח תמונות גדולות יותר.

1. הוסף את הקוד הבא מתחת לכך כדי להגדיר פונקציה להגדרת המצלמה:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    פונקציית `setupCamera` מתחילה בהגדרת פין בחירת השבב של SPI (`PIN_SPI_SS`) כגבוה, מה שהופך את ה-Wio Terminal לבקר SPI. לאחר מכן היא מתחילה את אוטובוסי I2C ו-SPI. לבסוף היא מאתחלת את מחלקת המצלמה שמגדירה את הגדרות חיישן המצלמה ומוודאת שהכל מחובר כראוי.

1. קרא לפונקציה זו בסוף פונקציית `setup`:

    ```cpp
    setupCamera();
    ```

1. בנה והעלה את הקוד הזה, ובדוק את הפלט ממוניטור הסריאל. אם אתה רואה `Error setting up the camera!`, בדוק את החיווט כדי לוודא שכל הכבלים מחברים את הפינים הנכונים ב-ArduCam לפינים הנכונים ב-GPIO ב-Wio Terminal, וכל כבלי הג'אמפר מחוברים כראוי.

## צילום תמונה

כעת ניתן לתכנת את ה-Wio Terminal לצלם תמונה כאשר לוחצים על כפתור.

### משימה - צילום תמונה

1. מיקרו-בקרים מריצים את הקוד שלך ברציפות, כך שלא קל להפעיל משהו כמו צילום תמונה מבלי להגיב לחיישן. ל-Wio Terminal יש כפתורים, כך שניתן להגדיר את המצלמה להיות מופעלת על ידי אחד הכפתורים. הוסף את הקוד הבא לסוף פונקציית `setup` כדי להגדיר את כפתור C (אחד משלושת הכפתורים בחלק העליון, הקרוב ביותר למתג ההפעלה).

    ![כפתור C בחלק העליון הקרוב ביותר למתג ההפעלה](../../../../../translated_images/he/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    מצב `INPUT_PULLUP` למעשה הופך קלט. לדוגמה, בדרך כלל כפתור ישלח אות נמוך כאשר אינו נלחץ, ואות גבוה כאשר נלחץ. כאשר מוגדר ל-`INPUT_PULLUP`, הם שולחים אות גבוה כאשר אינם נלחצים, ואות נמוך כאשר נלחצים.

1. הוסף פונקציה ריקה להגיב ללחיצת הכפתור לפני פונקציית `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. קרא לפונקציה זו בפונקציית `loop` כאשר הכפתור נלחץ:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    מפתח זה בודק אם הכפתור נלחץ. אם הוא נלחץ, פונקציית `buttonPressed` נקראת, והלולאה מתעכבת למשך 2 שניות. זה כדי לאפשר זמן לשחרור הכפתור כך שלחיצה ארוכה לא תירשם פעמיים.

    > 💁 הכפתור ב-Wio Terminal מוגדר ל-`INPUT_PULLUP`, כך שהוא שולח אות גבוה כאשר אינו נלחץ, ואות נמוך כאשר נלחץ.

1. הוסף את הקוד הבא לפונקציית `buttonPressed`:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    קוד זה מתחיל את צילום המצלמה על ידי קריאה ל-`startCapture`. החומרה של המצלמה אינה עובדת על ידי החזרת הנתונים כאשר אתה מבקש אותם, במקום זאת אתה שולח הוראה להתחיל לצלם, והמצלמה תעבוד ברקע לצלם את התמונה, להמיר אותה ל-JPEG, ולאחסן אותה במאגר מקומי על המצלמה עצמה. קריאה ל-`captureReady` לאחר מכן בודקת אם צילום התמונה הסתיים.

    לאחר שהצילום הסתיים, נתוני התמונה מועתקים מהמאגר על המצלמה למאגר מקומי (מערך של בתים) עם קריאה ל-`readImageToBuffer`. אורך המאגר נשלח לאחר מכן למוניטור הסריאל.

1. בנה והעלה את הקוד הזה, ובדוק את הפלט במוניטור הסריאל. בכל פעם שתלחץ על כפתור C, תמונה תצולם ותראה את גודל התמונה נשלח למוניטור הסריאל.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    תמונות שונות יהיו בעלות גדלים שונים. הן נדחסות כ-JPEG וגודל קובץ JPEG עבור רזולוציה נתונה תלוי במה שיש בתמונה.

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 הצלחת לצלם תמונות עם ה-Wio Terminal שלך.

## אופציונלי - אימות תמונות המצלמה באמצעות כרטיס SD

הדרך הקלה ביותר לראות את התמונות שצולמו על ידי המצלמה היא לכתוב אותן לכרטיס SD ב-Wio Terminal ואז לצפות בהן במחשב שלך. בצע שלב זה אם יש לך כרטיס microSD פנוי ושקע microSD במחשב שלך או מתאם.

ה-Wio Terminal תומך רק בכרטיסי microSD בגודל של עד 16GB. אם יש לך כרטיס SD גדול יותר, הוא לא יעבוד.

### משימה - אימות תמונות המצלמה באמצעות כרטיס SD

1. פרמט כרטיס microSD כ-FAT32 או exFAT באמצעות היישומים הרלוונטיים במחשב שלך (Disk Utility ב-macOS, File Explorer ב-Windows, או באמצעות כלי שורת פקודה ב-Linux).

1. הכנס את כרטיס ה-microSD לשקע ממש מתחת למתג ההפעלה. ודא שהוא נכנס עד הסוף עד שהוא נלחץ ונשאר במקום, ייתכן שתצטרך לדחוף אותו באמצעות ציפורן או כלי דק.

1. הוסף את הצהרות ה-include הבאות בראש קובץ `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. הוסף את הפונקציה הבאה לפני פונקציית `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    פונקציה זו מגדירה את כרטיס ה-SD באמצעות אוטובוס SPI.

1. קרא לפונקציה זו מפונקציית `setup`:

    ```cpp
    setupSDCard();
    ```

1. הוסף את הקוד הבא מעל פונקציית `buttonPressed`:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    זה מגדיר משתנה גלובלי למספר קבצים. זה משמש לשמות קבצי התמונות כך שניתן לצלם תמונות מרובות עם שמות קבצים עוקבים - `1.jpg`, `2.jpg` וכן הלאה.

    לאחר מכן הוא מגדיר את הפונקציה `saveToSDCard` שלוקחת מאגר נתוני בתים ואת אורך המאגר. שם קובץ נוצר באמצעות מספר הקבצים, ומספר הקבצים מוגדל מוכן לקובץ הבא. הנתונים הבינאריים מהמאגר נכתבים לקובץ.

1. קרא לפונקציה `saveToSDCard` מפונקציית `buttonPressed`. הקריאה צריכה להיות **לפני** שהמאגר נמחק:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. בנה והעלה את הקוד הזה, ובדוק את הפלט במוניטור הסריאל. בכל פעם שתלחץ על כפתור C, תמונה תצולם ותישמר בכרטיס ה-SD.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. כבה את כרטיס ה-microSD והוצא אותו על ידי לחיצה קלה ושחרור, והוא יקפוץ החוצה. ייתכן שתצטרך להשתמש בכלי דק כדי לעשות זאת. חבר את כרטיס ה-microSD למחשב שלך כדי לצפות בתמונות.

    ![תמונה של בננה שצולמה באמצעות ArduCam](../../../../../translated_images/he/banana-arducam.be1b32d4267a8194.webp)
💁 ייתכן שייקח כמה תמונות עד שהאיזון הלבן של המצלמה יתאים את עצמו. תבחינו בכך על סמך הצבע של התמונות שצולמו, הראשונות עשויות להיראות בצבע שגוי. תמיד תוכלו לעקוף זאת על ידי שינוי הקוד כך שיצלם כמה תמונות שמתעלמים מהן בפונקציית `setup`.


---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור הסמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.