<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-27T22:49:41+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "he"
}
-->
# קריאת נתוני GPS - Wio Terminal

בחלק זה של השיעור, תוסיף חיישן GPS ל-Wio Terminal שלך ותקריא ממנו נתונים.

## חומרה

ה-Wio Terminal זקוק לחיישן GPS.

החיישן שבו תשתמש הוא [חיישן Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). חיישן זה יכול להתחבר למערכות GPS מרובות כדי לספק מיקום מהיר ומדויק. החיישן מורכב משני חלקים - האלקטרוניקה המרכזית של החיישן ואנטנה חיצונית המחוברת באמצעות כבל דק כדי לקלוט גלי רדיו מהלוויינים.

זהו חיישן UART, ולכן הוא שולח נתוני GPS דרך UART.

### חיבור חיישן ה-GPS

ניתן לחבר את חיישן ה-GPS ל-Wio Terminal.

#### משימה - חיבור חיישן ה-GPS

חבר את חיישן ה-GPS.

![חיישן GPS מסוג Grove](../../../../../translated_images/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.he.png)

1. הכנס קצה אחד של כבל Grove לשקע שבחיישן ה-GPS. הכבל ייכנס רק בכיוון אחד.

1. כאשר ה-Wio Terminal מנותק מהמחשב שלך או מכל מקור כוח אחר, חבר את הקצה השני של כבל ה-Grove לשקע ה-Grove שבצד השמאלי של ה-Wio Terminal (כאשר המסך פונה אליך). זהו השקע הקרוב ביותר לכפתור ההפעלה.

    ![חיישן ה-GPS מחובר לשקע השמאלי](../../../../../translated_images/wio-gps-sensor.19fd52b81ce58095.he.png)

1. מקם את חיישן ה-GPS כך שהאנטנה המחוברת אליו תהיה חשופה לשמיים - רצוי ליד חלון פתוח או מחוץ לבית. קל יותר לקבל אות ברור כאשר אין מכשולים בין האנטנה לשמיים.

1. כעת תוכל לחבר את ה-Wio Terminal למחשב שלך.

1. לחיישן ה-GPS יש שני נורות LED - נורה כחולה מהבהבת כאשר נתונים מועברים, ונורה ירוקה מהבהבת בכל שנייה כאשר מתקבלים נתונים מהלוויינים. ודא שהנורה הכחולה מהבהבת כאשר אתה מפעיל את ה-Wio Terminal. לאחר מספר דקות, הנורה הירוקה תתחיל להבהב - אם לא, ייתכן שתצטרך למקם מחדש את האנטנה.

## תכנות חיישן ה-GPS

כעת ניתן לתכנת את ה-Wio Terminal לשימוש בחיישן ה-GPS המחובר.

### משימה - תכנות חיישן ה-GPS

תכנת את המכשיר.

1. צור פרויקט חדש עבור ה-Wio Terminal באמצעות PlatformIO. קרא לפרויקט `gps-sensor`. הוסף קוד בפונקציית `setup` כדי להגדיר את יציאת ה-serial.

1. הוסף את ההנחיה הבאה לראש קובץ `main.cpp`. זה כולל קובץ כותרת עם פונקציות להגדרת שקע ה-Grove השמאלי עבור UART.

    ```cpp
    #include <wiring_private.h>
    ```

1. מתחת לכך, הוסף את שורת הקוד הבאה כדי להכריז על חיבור יציאת serial ליציאת ה-UART:

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. עליך להוסיף קוד כדי להפנות כמה מטפלי אותות פנימיים ליציאת serial זו. הוסף את הקוד הבא מתחת להכרזה על `Serial3`:

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. בפונקציית `setup`, מתחת להגדרת יציאת ה-`Serial`, הגדר את יציאת ה-UART serial באמצעות הקוד הבא:

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. מתחת לקוד זה בפונקציית `setup`, הוסף את הקוד הבא כדי לחבר את פין ה-Grove ליציאת ה-serial:

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. הוסף את הפונקציה הבאה לפני פונקציית `loop` כדי לשלוח את נתוני ה-GPS לצג ה-serial:

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. בפונקציית `loop`, הוסף את הקוד הבא כדי לקרוא מיציאת ה-UART serial ולהדפיס את הפלט לצג ה-serial:

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    קוד זה קורא מיציאת ה-UART serial. הפונקציה `readStringUntil` קוראת עד תו מסיים, במקרה זה שורה חדשה. כך ניתן לקרוא משפט NMEA שלם (משפטי NMEA מסתיימים בתו שורה חדשה). כל עוד ניתן לקרוא נתונים מיציאת ה-UART serial, הם נקראים ונשלחים לצג ה-serial באמצעות הפונקציה `printGPSData`. ברגע שלא ניתן לקרוא עוד נתונים, הפונקציה `loop` מתעכבת למשך שנייה אחת (1,000ms).

1. בנה והעלה את הקוד ל-Wio Terminal.

1. לאחר ההעלאה, תוכל לעקוב אחר נתוני ה-GPS באמצעות צג ה-serial.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal).

😀 תוכנית חיישן ה-GPS שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.