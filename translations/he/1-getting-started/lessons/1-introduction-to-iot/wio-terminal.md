<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-27T22:07:04+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "he"
}
-->
# Wio Terminal

ה-[Wio Terminal מבית Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) הוא מיקרו-בקר תואם Arduino, עם WiFi וחיישנים ומפעילים מובנים, וכן יציאות להוספת חיישנים ומפעילים נוספים, באמצעות מערכת חומרה הנקראת [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Wio Terminal מבית Seeed Studios](../../../../../translated_images/he/wio-terminal.b8299ee16587db9a.png)

## הגדרה

כדי להשתמש ב-Wio Terminal, תצטרכו להתקין תוכנה חינמית במחשב שלכם. בנוסף, תצטרכו לעדכן את הקושחה של ה-Wio Terminal לפני שתוכלו לחבר אותו ל-WiFi.

### משימה - הגדרה

התקינו את התוכנה הנדרשת ועדכנו את הקושחה.

1. התקינו את Visual Studio Code (VS Code). זהו העורך שבו תשתמשו לכתיבת קוד המכשיר שלכם ב-C/C++. עיינו ב-[תיעוד של VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) להוראות התקנה.

    > 💁 סביבת פיתוח פופולרית נוספת לפיתוח Arduino היא [Arduino IDE](https://www.arduino.cc/en/software). אם אתם כבר מכירים את הכלי הזה, תוכלו להשתמש בו במקום VS Code ו-PlatformIO, אך השיעורים יספקו הוראות בהתבסס על שימוש ב-VS Code.

1. התקינו את הרחבת PlatformIO עבור VS Code. זו הרחבה ל-VS Code שתומכת בתכנות מיקרו-בקרים ב-C/C++. עיינו ב-[תיעוד הרחבת PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide) להוראות התקנה. הרחבה זו תלויה בהרחבת Microsoft C/C++ כדי לעבוד עם קוד C ו-C++, והיא מותקנת אוטומטית עם התקנת PlatformIO.

1. חברו את ה-Wio Terminal למחשב שלכם. ל-Wio Terminal יש יציאת USB-C בתחתית, ויש לחבר אותה ליציאת USB במחשב שלכם. ה-Wio Terminal מגיע עם כבל USB-C ל-USB-A, אך אם במחשב שלכם יש רק יציאות USB-C, תצטרכו כבל USB-C או מתאם USB-A ל-USB-C.

1. עקבו אחר ההוראות בתיעוד [Wio Terminal Wiki WiFi Overview](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/) כדי להגדיר את ה-Wio Terminal ולעדכן את הקושחה.

## שלום עולם

נהוג להתחיל עם שפה או טכנולוגיה חדשה על ידי יצירת אפליקציית 'שלום עולם' - אפליקציה קטנה שמציגה טקסט כמו `"Hello World"` כדי לוודא שכל הכלים מוגדרים כראוי.

אפליקציית שלום עולם עבור ה-Wio Terminal תוודא ש-VS Code מותקן כראוי עם PlatformIO ומוכן לפיתוח מיקרו-בקרים.

### יצירת פרויקט PlatformIO

השלב הראשון הוא יצירת פרויקט חדש באמצעות PlatformIO המוגדר עבור ה-Wio Terminal.

#### משימה - יצירת פרויקט PlatformIO

צרו את פרויקט ה-PlatformIO.

1. חברו את ה-Wio Terminal למחשב שלכם

1. הפעילו את VS Code

1. סמל PlatformIO יופיע בסרגל התפריט הצדדי:

    ![אפשרות התפריט של PlatformIO](../../../../../translated_images/he/vscode-platformio-menu.297be26b9733e5c4.png)

    בחרו באפשרות זו, ואז בחרו *PIO Home -> Open*

    ![אפשרות הפתיחה של PlatformIO](../../../../../translated_images/he/vscode-platformio-home-open.3f9a41bfd3f4da1c.png)

1. במסך הפתיחה, בחרו בכפתור **+ New Project**

    ![כפתור הפרויקט החדש](../../../../../translated_images/he/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.png)

1. הגדירו את הפרויקט ב-*Project Wizard*:

    1. תנו שם לפרויקט שלכם `nightlight`

    1. בתפריט הנפתח *Board*, הקלידו `WIO` כדי לסנן את הלוחות, ובחרו *Seeeduino Wio Terminal*

    1. השאירו את *Framework* כ-*Arduino*

    1. השאירו את תיבת הסימון *Use default location* מסומנת, או בטלו אותה ובחרו מיקום לפרויקט שלכם

    1. לחצו על כפתור **Finish**

    ![אשף הפרויקט המושלם](../../../../../translated_images/he/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.png)

    PlatformIO יוריד את הרכיבים הדרושים לו כדי לקמפל קוד עבור ה-Wio Terminal ויצור את הפרויקט שלכם. זה עשוי לקחת כמה דקות.

### חקר פרויקט PlatformIO

סייר VS Code יציג מספר קבצים ותיקיות שנוצרו על ידי אשף PlatformIO.

#### תיקיות

* `.pio` - תיקייה זו מכילה נתונים זמניים ש-PlatformIO זקוק להם, כמו ספריות או קוד מקומפל. היא נוצרת מחדש אוטומטית אם נמחקת, ואין צורך להוסיף אותה לשליטה בקוד מקור אם אתם משתפים את הפרויקט שלכם באתרים כמו GitHub.
* `.vscode` - תיקייה זו מכילה את התצורה שבה משתמשים PlatformIO ו-VS Code. היא נוצרת מחדש אוטומטית אם נמחקת, ואין צורך להוסיף אותה לשליטה בקוד מקור אם אתם משתפים את הפרויקט שלכם באתרים כמו GitHub.
* `include` - תיקייה זו מיועדת לקבצי כותרת חיצוניים הנדרשים בעת הוספת ספריות נוספות לקוד שלכם. לא תשתמשו בתיקייה זו באף אחד מהשיעורים הללו.
* `lib` - תיקייה זו מיועדת לספריות חיצוניות שתרצו לקרוא להן מתוך הקוד שלכם. לא תשתמשו בתיקייה זו באף אחד מהשיעורים הללו.
* `src` - תיקייה זו מכילה את קוד המקור הראשי של האפליקציה שלכם. בתחילה, היא תכיל קובץ יחיד - `main.cpp`.
* `test` - תיקייה זו מיועדת למבחני יחידה עבור הקוד שלכם.

#### קבצים

* `main.cpp` - קובץ זה בתיקיית `src` מכיל את נקודת הכניסה לאפליקציה שלכם. פתחו את הקובץ, והוא יכיל את הקוד הבא:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    כאשר המכשיר מופעל, מסגרת Arduino תריץ את הפונקציה `setup` פעם אחת, ואז תריץ את הפונקציה `loop` שוב ושוב עד שהמכשיר יכבה.

* `.gitignore` - קובץ זה מפרט את הקבצים והתיקיות שיש להתעלם מהם בעת הוספת הקוד שלכם לשליטה בקוד מקור, כמו העלאה למאגר ב-GitHub.

* `platformio.ini` - קובץ זה מכיל תצורה עבור המכשיר והאפליקציה שלכם. פתחו את הקובץ, והוא יכיל את הקוד הבא:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    הסעיף `[env:seeed_wio_terminal]` מכיל תצורה עבור ה-Wio Terminal. ניתן להגדיר מספר סעיפי `env` כך שהקוד שלכם יוכל להיות מקומפל עבור מספר לוחות.

    הערכים האחרים תואמים את התצורה מאשף הפרויקט:

  * `platform = atmelsam` מגדיר את החומרה שבה משתמש ה-Wio Terminal (מיקרו-בקר מבוסס ATSAMD51)
  * `board = seeed_wio_terminal` מגדיר את סוג לוח המיקרו-בקר (ה-Wio Terminal)
  * `framework = arduino` מגדיר שהפרויקט הזה משתמש במסגרת Arduino.

### כתיבת אפליקציית שלום עולם

כעת אתם מוכנים לכתוב את אפליקציית שלום עולם.

#### משימה - כתיבת אפליקציית שלום עולם

כתבו את אפליקציית שלום עולם.

1. פתחו את הקובץ `main.cpp` ב-VS Code

1. שנו את הקוד כך שיתאים לקוד הבא:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    הפונקציה `setup` מאתחלת חיבור ליציאת הסריאל - במקרה זה, יציאת ה-USB שמשמשת לחיבור ה-Wio Terminal למחשב שלכם. הפרמטר `9600` הוא [קצב הסמל](https://wikipedia.org/wiki/Symbol_rate), או מהירות שבה נתונים יישלחו דרך יציאת הסריאל בביטים לשנייה. הגדרה זו אומרת ש-9,600 ביטים (0s ו-1s) של נתונים נשלחים בכל שנייה. לאחר מכן היא ממתינה שהיציאה הסריאלית תהיה מוכנה.

    הפונקציה `loop` שולחת את השורה `Hello World!` ליציאה הסריאלית, כך שהדמויות של `Hello World!` יחד עם תו שורה חדשה יישלחו. לאחר מכן היא ישנה למשך 5,000 מילישניות או 5 שניות. לאחר סיום הפונקציה `loop`, היא מופעלת שוב, ושוב, וכן הלאה כל עוד המיקרו-בקר מופעל.

1. הכניסו את ה-Wio Terminal למצב העלאה. תצטרכו לעשות זאת בכל פעם שתעלו קוד חדש למכשיר:

    1. משכו את מתג ההפעלה מטה פעמיים במהירות - הוא יחזור למצב הפעלה בכל פעם.

    1. בדקו את נורית הסטטוס הכחולה בצד ימין של יציאת ה-USB. היא אמורה להבהב.

    [![סרטון שמראה כיצד להכניס את ה-Wio Terminal למצב העלאה](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)

    לחצו על התמונה למעלה לצפייה בסרטון שמראה כיצד לעשות זאת.

1. קומפלו והעלו את הקוד ל-Wio Terminal

    1. פתחו את תפריט הפקודות של VS Code

    1. הקלידו `PlatformIO Upload` כדי לחפש את אפשרות ההעלאה, ובחרו *PlatformIO: Upload*

        ![אפשרות ההעלאה של PlatformIO בתפריט הפקודות](../../../../../translated_images/he/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.png)

        PlatformIO יקומפל את הקוד באופן אוטומטי אם יש צורך לפני ההעלאה.

    1. הקוד יקומפל ויועלה ל-Wio Terminal

        > 💁 אם אתם משתמשים ב-macOS, תופיע התראה על *DISK NOT EJECTED PROPERLY*. זה קורה מכיוון שה-Wio Terminal מותקן ככונן כחלק מתהליך ההעלאה, והוא מנותק כאשר הקוד המקומפל נכתב למכשיר. ניתן להתעלם מההתראה הזו.

    ⚠️ אם אתם מקבלים שגיאות על כך שיציאת ההעלאה אינה זמינה, קודם כל ודאו שה-Wio Terminal מחובר למחשב שלכם, מופעל באמצעות המתג בצד שמאל של המסך, ומוגדר למצב העלאה. הנורית הירוקה בתחתית צריכה להיות דולקת, והנורית הכחולה צריכה להבהב. אם עדיין יש שגיאה, משכו את מתג ההפעלה מטה פעמיים במהירות שוב כדי להכניס את ה-Wio Terminal למצב העלאה ונסו להעלות שוב.

ל-PlatformIO יש מוניטור סריאלי שיכול לעקוב אחר נתונים שנשלחים דרך כבל ה-USB מה-Wio Terminal. זה מאפשר לכם לעקוב אחר הנתונים שנשלחים על ידי הפקודה `Serial.println("Hello World");`.

1. פתחו את תפריט הפקודות של VS Code

1. הקלידו `PlatformIO Serial` כדי לחפש את אפשרות המוניטור הסריאלי, ובחרו *PlatformIO: Serial Monitor*

    ![אפשרות המוניטור הסריאלי של PlatformIO בתפריט הפקודות](../../../../../translated_images/he/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.png)

    ייפתח טרמינל חדש, והנתונים שנשלחים דרך יציאת הסריאל יוזרמו לטרמינל הזה:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` יודפס למוניטור הסריאלי כל 5 שניות.

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 אפליקציית 'שלום עולם' שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו אחראים לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.