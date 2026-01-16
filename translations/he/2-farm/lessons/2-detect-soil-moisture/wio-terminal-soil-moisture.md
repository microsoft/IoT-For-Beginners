<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0d55caa8c23d73635b7559102cd17b8a",
  "translation_date": "2025-08-27T21:25:32+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/wio-terminal-soil-moisture.md",
  "language_code": "he"
}
-->
# מדידת לחות קרקע - Wio Terminal

בחלק זה של השיעור, תוסיפו חיישן לחות קרקע קיבולי ל-Wio Terminal שלכם, ותקראו ממנו ערכים.

## חומרה

ה-Wio Terminal זקוק לחיישן לחות קרקע קיבולי.

החיישן שבו תשתמשו הוא [חיישן לחות קרקע קיבולי](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), שמודד את לחות הקרקע על ידי זיהוי הקיבוליות של הקרקע, תכונה שמשתנה בהתאם לשינויי הלחות בקרקע. ככל שלחות הקרקע עולה, המתח יורד.

זהו חיישן אנלוגי, ולכן הוא מתחבר לפינים אנלוגיים ב-Wio Terminal, תוך שימוש בממיר ADC מובנה ליצירת ערך בטווח של 0-1,023.

### חיבור חיישן לחות הקרקע

ניתן לחבר את חיישן לחות הקרקע של Grove ליציאת האנלוג/דיגיטל הניתנת להגדרה ב-Wio Terminal.

#### משימה - חיבור חיישן לחות הקרקע

חברו את חיישן לחות הקרקע.

![חיישן לחות קרקע מסוג Grove](../../../../../translated_images/he/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. הכניסו קצה אחד של כבל Grove לשקע שבחיישן לחות הקרקע. הכבל ייכנס רק בכיוון אחד.

1. כאשר ה-Wio Terminal מנותק מהמחשב או ממקור כוח אחר, חברו את הקצה השני של כבל ה-Grove לשקע הימני ביותר ב-Wio Terminal כאשר אתם מביטים במסך. זהו השקע הרחוק ביותר מכפתור ההפעלה.

![חיישן לחות הקרקע מחובר לשקע הימני](../../../../../translated_images/he/wio-soil-moisture-sensor.46919b61c3f6cb74.webp)

1. הכניסו את חיישן לחות הקרקע לתוך האדמה. יש לו "קו מיקום מקסימלי" - קו לבן שחוצה את החיישן. הכניסו את החיישן עד לקו זה אך לא מעבר לו.

![חיישן לחות הקרקע בתוך האדמה](../../../../../translated_images/he/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

1. כעת תוכלו לחבר את ה-Wio Terminal למחשב שלכם.

## תכנות חיישן לחות הקרקע

כעת ניתן לתכנת את ה-Wio Terminal לשימוש בחיישן לחות הקרקע המחובר.

### משימה - תכנות חיישן לחות הקרקע

תכנתו את המכשיר.

1. צרו פרויקט חדש עבור Wio Terminal באמצעות PlatformIO. קראו לפרויקט `soil-moisture-sensor`. הוסיפו קוד לפונקציית `setup` כדי להגדיר את יציאת הסריאל.

    > ⚠️ תוכלו לעיין [בהוראות ליצירת פרויקט PlatformIO בפרויקט 1, שיעור 1 במידת הצורך](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project).

1. אין ספרייה ייעודית לחיישן זה, אך ניתן לקרוא מהפין האנלוגי באמצעות פונקציית [`analogRead`](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/) המובנית של Arduino. התחילו בהגדרת הפין האנלוגי כקלט כך שניתן יהיה לקרוא ממנו ערכים על ידי הוספת הקוד הבא לפונקציית `setup`.

    ```cpp
    pinMode(A0, INPUT);
    ```

    קוד זה מגדיר את הפין `A0`, שהוא פין אנלוגי/דיגיטלי משולב, כפין קלט שממנו ניתן לקרוא מתח.

1. הוסיפו את הקוד הבא לפונקציית `loop` כדי לקרוא את המתח מהפין:

    ```cpp
    int soil_moisture = analogRead(A0);
    ```

1. מתחת לקוד זה, הוסיפו את הקוד הבא כדי להדפיס את הערך ליציאת הסריאל:

    ```cpp
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
    ```

1. לבסוף, הוסיפו השהיה של 10 שניות בסוף:

    ```cpp
    delay(10000);
    ```

1. בנו והעלו את הקוד ל-Wio Terminal.

    > ⚠️ תוכלו לעיין [בהוראות ליצירת פרויקט PlatformIO בפרויקט 1, שיעור 1 במידת הצורך](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app).

1. לאחר ההעלאה, תוכלו לעקוב אחר לחות הקרקע באמצעות צג הסריאל. הוסיפו מים לקרקע או הוציאו את החיישן מהקרקע, וצפו בערך משתנה.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Soil Moisture: 526
    Soil Moisture: 529
    Soil Moisture: 521
    Soil Moisture: 494
    Soil Moisture: 454
    Soil Moisture: 456
    Soil Moisture: 395
    Soil Moisture: 388
    Soil Moisture: 394
    Soil Moisture: 391
    ```

    בדוגמת הפלט למעלה, ניתן לראות את ירידת המתח כאשר מוסיפים מים.

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code/wio-terminal](../../../../../2-farm/lessons/2-detect-soil-moisture/code/wio-terminal).

😀 תוכנית חיישן לחות הקרקע שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.