<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-27T22:02:51+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "he"
}
-->
# מחשב לוח וירטואלי

במקום לרכוש מכשיר IoT יחד עם חיישנים ומפעילים, ניתן להשתמש במחשב שלך כדי לדמות חומרת IoT. פרויקט [CounterFit](https://github.com/CounterFit-IoT/CounterFit) מאפשר לך להפעיל אפליקציה מקומית המדמה חומרת IoT כמו חיישנים ומפעילים, ולגשת אליהם באמצעות קוד Python מקומי שנכתב באותו אופן שבו היית כותב קוד עבור Raspberry Pi עם חומרה פיזית.

## הגדרות

כדי להשתמש ב-CounterFit, תצטרך להתקין תוכנה חינמית במחשב שלך.

### משימה

התקן את התוכנה הנדרשת.

1. התקן את Python. עיין ב-[דף ההורדות של Python](https://www.python.org/downloads/) להוראות כיצד להתקין את הגרסה העדכנית ביותר של Python.

1. התקן את Visual Studio Code (VS Code). זהו העורך שבו תשתמש לכתיבת קוד המכשיר הווירטואלי ב-Python. עיין ב-[תיעוד של VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) להוראות כיצד להתקין את VS Code.

    > 💁 אתה חופשי להשתמש בכל IDE או עורך Python אחר לשיעורים אלו אם יש לך כלי מועדף, אך ההוראות בשיעורים יתבססו על שימוש ב-VS Code.

1. התקן את התוסף Pylance עבור VS Code. זהו תוסף המספק תמיכה לשפת Python ב-VS Code. עיין ב-[תיעוד התוסף Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) להוראות כיצד להתקין את התוסף ב-VS Code.

ההוראות להתקנה והגדרה של אפליקציית CounterFit יינתנו בזמן הרלוונטי בהוראות המשימה, מכיוון שהיא מותקנת על בסיס פרויקט.

## שלום עולם

נהוג להתחיל עם שפה או טכנולוגיה חדשה על ידי יצירת אפליקציית 'שלום עולם' - אפליקציה קטנה שמדפיסה טקסט כמו `"Hello World"` כדי לוודא שכל הכלים מוגדרים כראוי.

אפליקציית 'שלום עולם' עבור חומרת IoT וירטואלית תוודא ש-Python ו-Visual Studio Code מותקנים כראוי. היא גם תתחבר ל-CounterFit עבור חיישני ומפעילי IoT וירטואליים. היא לא תשתמש בחומרה, אלא רק תתחבר כדי להוכיח שהכול פועל.

אפליקציה זו תהיה בתיקייה בשם `nightlight`, והיא תשמש שוב עם קוד שונה בחלקים מאוחרים יותר של המשימה לבניית אפליקציית תאורת לילה.

### הגדרת סביבה וירטואלית של Python

אחת התכונות החזקות של Python היא היכולת להתקין [חבילות Pip](https://pypi.org) - אלו חבילות קוד שנכתבו על ידי אחרים ופורסמו באינטרנט. ניתן להתקין חבילת Pip במחשב שלך עם פקודה אחת, ואז להשתמש בה בקוד שלך. תשתמש ב-Pip כדי להתקין חבילה שתאפשר לך לתקשר עם CounterFit.

כברירת מחדל, כאשר אתה מתקין חבילה, היא זמינה בכל המחשב שלך, וזה עלול לגרום לבעיות עם גרסאות חבילות - כמו אפליקציה אחת שתלויה בגרסה מסוימת של חבילה שעלולה להישבר כאשר תתקין גרסה חדשה עבור אפליקציה אחרת. כדי להתמודד עם בעיה זו, ניתן להשתמש ב-[סביבה וירטואלית של Python](https://docs.python.org/3/library/venv.html), שהיא למעשה עותק של Python בתיקייה ייעודית, וכאשר אתה מתקין חבילות Pip הן מותקנות רק בתיקייה זו.

> 💁 אם אתה משתמש ב-Raspberry Pi, לא הגדרת סביבה וירטואלית במכשיר זה לניהול חבילות Pip, אלא אתה משתמש בחבילות גלובליות, מכיוון שחבילות Grove מותקנות באופן גלובלי על ידי סקריפט ההתקנה.

#### משימה - הגדרת סביבה וירטואלית של Python

הגדר סביבה וירטואלית של Python והתקן את חבילות Pip עבור CounterFit.

1. מהטרמינל או שורת הפקודה שלך, הרץ את הפקודות הבאות במיקום לבחירתך כדי ליצור ולנווט לתיקייה חדשה:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. כעת הרץ את הפקודות הבאות כדי ליצור סביבה וירטואלית בתיקייה `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 עליך לקרוא במפורש ל-`python3` כדי ליצור את הסביבה הווירטואלית, למקרה שיש לך Python 2 מותקן בנוסף ל-Python 3 (הגרסה העדכנית ביותר). אם יש לך Python 2 מותקן, קריאה ל-`python` תשתמש ב-Python 2 במקום ב-Python 3.

1. הפעל את הסביבה הווירטואלית:

    * ב-Windows:
        * אם אתה משתמש ב-Command Prompt, או ב-Command Prompt דרך Windows Terminal, הרץ:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * אם אתה משתמש ב-PowerShell, הרץ:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > אם אתה מקבל שגיאה על כך שהרצת סקריפטים מושבתת במערכת זו, תצטרך לאפשר הרצת סקריפטים על ידי הגדרת מדיניות ביצוע מתאימה. תוכל לעשות זאת על ידי פתיחת PowerShell כמנהל מערכת, ואז הרצת הפקודה הבאה:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            הקלד `Y` כאשר תתבקש לאשר. לאחר מכן הפעל מחדש את PowerShell ונסה שוב.

            תוכל לאפס מדיניות ביצוע זו במועד מאוחר יותר אם תצטרך. תוכל לקרוא עוד על כך ב-[דף מדיניות ביצוע באתר Microsoft Docs](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * ב-macOS או Linux, הרץ:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 פקודות אלו צריכות להתבצע מהמיקום שבו יצרת את הסביבה הווירטואלית. לעולם לא תצטרך לנווט לתוך תיקיית `.venv`, עליך תמיד להריץ את פקודת ההפעלה וכל פקודות להתקנת חבילות או הרצת קוד מהמיקום שבו היית כשיצרת את הסביבה הווירטואלית.

1. לאחר שהסביבה הווירטואלית הופעלה, פקודת `python` כברירת מחדל תריץ את גרסת Python שבה השתמשת ליצירת הסביבה הווירטואלית. הרץ את הפקודה הבאה כדי לבדוק את הגרסה:

    ```sh
    python --version
    ```

    הפלט צריך לכלול את הדברים הבאים:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 ייתכן שגרסת Python שלך תהיה שונה - כל עוד היא גרסה 3.6 או גבוהה יותר, אתה במצב טוב. אם לא, מחק את התיקייה הזו, התקן גרסה חדשה יותר של Python ונסה שוב.

1. הרץ את הפקודות הבאות כדי להתקין את חבילות Pip עבור CounterFit. חבילות אלו כוללות את אפליקציית CounterFit הראשית וכן שימסים עבור חומרת Grove. שימסים אלו מאפשרים לך לכתוב קוד כאילו אתה מתכנת עם חיישנים ומפעילים פיזיים ממערכת Grove אך מחוברים למכשירי IoT וירטואליים.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    חבילות Pip אלו יותקנו רק בסביבה הווירטואלית, ולא יהיו זמינות מחוץ לה.

### כתיבת הקוד

לאחר שהסביבה הווירטואלית של Python מוכנה, תוכל לכתוב את הקוד עבור אפליקציית 'שלום עולם'.

#### משימה - כתיבת הקוד

צור אפליקציית Python שתדפיס `"Hello World"` לקונסול.

1. מהטרמינל או שורת הפקודה שלך, הרץ את הפקודות הבאות בתוך הסביבה הווירטואלית כדי ליצור קובץ Python בשם `app.py`:

    * ב-Windows הרץ:

        ```cmd
        type nul > app.py
        ```

    * ב-macOS או Linux הרץ:

        ```cmd
        touch app.py
        ```

1. פתח את התיקייה הנוכחית ב-VS Code:

    ```sh
    code .
    ```

    > 💁 אם הטרמינל שלך מחזיר `command not found` ב-macOS, זה אומר ש-VS Code לא נוסף ל-PATH שלך. תוכל להוסיף את VS Code ל-PATH על ידי ביצוע ההוראות ב-[החלק על הפעלה משורת הפקודה בתיעוד של VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) ולאחר מכן להריץ את הפקודה שוב. ב-Windows ו-Linux, VS Code נוסף ל-PATH כברירת מחדל.

1. כאשר VS Code יופעל, הוא יפעיל את הסביבה הווירטואלית של Python. הסביבה הווירטואלית שנבחרה תופיע בשורת המצב התחתונה:

    ![VS Code showing the selected virtual environment](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.he.png)

1. אם הטרמינל של VS Code כבר פועל כאשר VS Code מופעל, הוא לא יפעיל את הסביבה הווירטואלית בתוכו. הדרך הקלה ביותר היא לסגור את הטרמינל באמצעות כפתור **Kill the active terminal instance**:

    ![VS Code Kill the active terminal instance button](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.he.png)

    תוכל לדעת אם הטרמינל מפעיל את הסביבה הווירטואלית לפי שם הסביבה הווירטואלית שיופיע כקידומת בשורת הפקודה של הטרמינל. לדוגמה, זה עשוי להיות:

    ```sh
    (.venv) ➜  nightlight
    ```

    אם אין `.venv` כקידומת בשורת הפקודה, הסביבה הווירטואלית אינה פעילה בטרמינל.

1. הפעל טרמינל חדש ב-VS Code על ידי בחירה ב-*Terminal -> New Terminal*, או על ידי לחיצה על `` CTRL+` ``. הטרמינל החדש יטען את הסביבה הווירטואלית, והקריאה להפעלתה תופיע בטרמינל. שורת הפקודה תכלול גם את שם הסביבה הווירטואלית (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. פתח את הקובץ `app.py` מתוך סייר הקבצים של VS Code והוסף את הקוד הבא:

    ```python
    print('Hello World!')
    ```

    הפונקציה `print` מדפיסה לקונסול כל מה שמועבר אליה.

1. מהטרמינל של VS Code, הרץ את הפקודה הבאה כדי להריץ את אפליקציית Python שלך:

    ```sh
    python app.py
    ```

    הפלט יהיה:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 אפליקציית 'שלום עולם' שלך הצליחה!

### חיבור ה'חומרה'

כשלב שני של 'שלום עולם', תפעיל את אפליקציית CounterFit ותחבר את הקוד שלך אליה. זהו המקבילה הווירטואלית לחיבור חומרת IoT ללוח פיתוח.

#### משימה - חיבור ה'חומרה'

1. מהטרמינל של VS Code, הפעל את אפליקציית CounterFit עם הפקודה הבאה:

    ```sh
    counterfit
    ```

    האפליקציה תתחיל לפעול ותיפתח בדפדפן האינטרנט שלך:

    ![The Counter Fit app running in a browser](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.he.png)

    היא תסומן כ-*Disconnected*, עם הנורית בפינה הימנית העליונה כבויה.

1. הוסף את הקוד הבא לראש הקובץ `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    קוד זה מייבא את המחלקה `CounterFitConnection` ממודול `counterfit_connection`, שמגיע מחבילת ה-pip `counterfit-connection` שהתקנת קודם. לאחר מכן הוא מאתחל חיבור לאפליקציית CounterFit שרצה על `127.0.0.1`, שהוא כתובת IP שתמיד ניתן להשתמש בה כדי לגשת למחשב המקומי שלך (לעיתים קרובות נקרא *localhost*), על פורט 5000.

    > 💁 אם יש לך אפליקציות אחרות שרצות על פורט 5000, תוכל לשנות זאת על ידי עדכון הפורט בקוד, והרצת CounterFit באמצעות `CounterFit --port <port_number>`, כאשר `<port_number>` הוא הפורט שברצונך להשתמש בו.

1. תצטרך להפעיל טרמינל חדש ב-VS Code על ידי בחירה בכפתור **Create a new integrated terminal**. זאת מכיוון שאפליקציית CounterFit רצה בטרמינל הנוכחי.

    ![VS Code Create a new integrated terminal button](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.he.png)

1. בטרמינל החדש, הרץ את הקובץ `app.py` כפי שעשית קודם. הסטטוס של CounterFit ישתנה ל-**Connected** והנורית תידלק.

    ![Counter Fit showing as connected](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.he.png)

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 החיבור שלך לחומרה הצליח!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.