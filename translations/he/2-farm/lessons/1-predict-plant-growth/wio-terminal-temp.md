# מדידת טמפרטורה - Wio Terminal

בחלק זה של השיעור, תוסיף חיישן טמפרטורה ל-Wio Terminal שלך ותקריא ממנו ערכי טמפרטורה.

## חומרה

ה-Wio Terminal זקוק לחיישן טמפרטורה.

החיישן שבו תשתמש הוא [חיישן לחות וטמפרטורה מסוג DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), שמשלב שני חיישנים בחבילה אחת. זהו חיישן פופולרי למדי, וישנם חיישנים מסחריים רבים שמשלבים טמפרטורה, לחות ולעיתים גם לחץ אטמוספרי. רכיב חיישן הטמפרטורה הוא תרמיסטור בעל מקדם טמפרטורה שלילי (NTC), כלומר תרמיסטור שבו ההתנגדות יורדת ככל שהטמפרטורה עולה.

זהו חיישן דיגיטלי, ולכן יש לו ממיר ADC מובנה שיוצר אות דיגיטלי שמכיל את נתוני הטמפרטורה והלחות שהמיקרו-בקר יכול לקרוא.

### חיבור חיישן הטמפרטורה

ניתן לחבר את חיישן הטמפרטורה מסוג Grove ליציאת הדיגיטל של ה-Wio Terminal.

#### משימה - חיבור חיישן הטמפרטורה

חבר את חיישן הטמפרטורה.

![חיישן טמפרטורה מסוג Grove](../../../../../translated_images/he/grove-dht11.07f8eafceee17004.webp)

1. הכנס קצה אחד של כבל Grove לשקע בחיישן הלחות והטמפרטורה. הכבל ייכנס רק בכיוון אחד.

1. כאשר ה-Wio Terminal מנותק מהמחשב או ממקור כוח אחר, חבר את הקצה השני של כבל Grove לשקע הימני ביותר ב-Wio Terminal כשאתה מסתכל על המסך. זהו השקע הרחוק ביותר מכפתור ההפעלה.

![חיישן הטמפרטורה מחובר לשקע הימני](../../../../../translated_images/he/wio-temperature-sensor.2934928f38c7f79a.webp)

## תכנות חיישן הטמפרטורה

כעת ניתן לתכנת את ה-Wio Terminal לשימוש בחיישן הטמפרטורה המחובר.

### משימה - תכנות חיישן הטמפרטורה

תכנת את המכשיר.

1. צור פרויקט חדש ל-Wio Terminal באמצעות PlatformIO. קרא לפרויקט הזה `temperature-sensor`. הוסף קוד לפונקציית `setup` כדי להגדיר את יציאת הסריאל.

    > ⚠️ תוכל לעיין [בהוראות ליצירת פרויקט ב-PlatformIO בפרויקט 1, שיעור 1 אם יש צורך](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. הוסף תלות ספרייה עבור ספריית Seeed Grove Humidity and Temperature sensor לקובץ `platformio.ini` של הפרויקט:

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ תוכל לעיין [בהוראות להוספת ספריות לפרויקט ב-PlatformIO בפרויקט 1, שיעור 4 אם יש צורך](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries).

1. הוסף את הוראות `#include` הבאות לראש הקובץ, מתחת ל-`#include <Arduino.h>` הקיים:

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    הוראות אלו מייבאות קבצים הדרושים לאינטראקציה עם החיישן. קובץ הכותרת `DHT.h` מכיל את הקוד עבור החיישן עצמו, והוספת קובץ הכותרת `SPI.h` מבטיחה שהקוד הדרוש לתקשורת עם החיישן ייכלל כאשר האפליקציה תורכב.

1. לפני פונקציית `setup`, הכרז על חיישן ה-DHT:

    ```cpp
    DHT dht(D0, DHT11);
    ```

    הכרזה זו יוצרת מופע של מחלקת `DHT` שמנהלת את חיישן הלחות והטמפרטורה הדיגיטלי. החיישן מחובר ליציאת `D0`, השקע הימני ביותר ב-Wio Terminal. הפרמטר השני מציין לקוד שהחיישן שבו משתמשים הוא *DHT11* - הספרייה שבה אתה משתמש תומכת גם בגרסאות אחרות של החיישן.

1. בפונקציית `setup`, הוסף קוד להגדרת חיבור הסריאל:

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. בסוף פונקציית `setup`, לאחר ה-`delay` האחרון, הוסף קריאה להפעלת חיישן ה-DHT:

    ```cpp
    dht.begin();
    ```

1. בפונקציית `loop`, הוסף קוד לקריאה מהחיישן ולהדפסת הטמפרטורה ליציאת הסריאל:

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    קוד זה מכריז על מערך ריק של שני ערכים מסוג float, ומעביר אותו לקריאה ל-`readTempAndHumidity` במופע `DHT`. קריאה זו ממלאת את המערך בשני ערכים - הלחות נכנסת לפריט ה-0 במערך (זכור שב-C++ מערכים מתחילים מ-0, כך שהפריט ה-0 הוא 'הראשון' במערך), והטמפרטורה נכנסת לפריט ה-1.

    הטמפרטורה נקראת מהפריט ה-1 במערך ומודפסת ליציאת הסריאל.

    > 🇺🇸 הטמפרטורה נקראת במעלות צלזיוס. עבור אמריקאים, כדי להמיר את הערך למעלות פרנהייט, חלק את ערך הצלזיוס ב-5, לאחר מכן הכפל ב-9, ולבסוף הוסף 32. לדוגמה, קריאת טמפרטורה של 20°C הופכת ל-((20/5)*9) + 32 = 68°F.

1. הרכב והעלה את הקוד ל-Wio Terminal.

    > ⚠️ תוכל לעיין [בהוראות ליצירת פרויקט ב-PlatformIO בפרויקט 1, שיעור 1 אם יש צורך](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. לאחר העלאה, תוכל לעקוב אחר הטמפרטורה באמצעות צג הסריאל:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal).

😀 תוכנית חיישן הטמפרטורה שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.