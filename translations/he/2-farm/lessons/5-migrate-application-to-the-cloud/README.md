<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f2d2f4a5a023c93ab34a0cc5b47c0c4",
  "translation_date": "2025-08-27T21:18:08+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/README.md",
  "language_code": "he"
}
-->
# העבר את לוגיקת האפליקציה שלך לענן

![סקיצה של סקירה כללית של השיעור הזה](../../../../../translated_images/he/lesson-9.dfe99c8e891f48e179724520da9f5794392cf9a625079281ccdcbf09bd85e1b6.jpg)

> סקיצה מאת [ניטיה נאראסימן](https://github.com/nitya). לחץ על התמונה לגרסה גדולה יותר.

השיעור הזה נלמד כחלק מסדרת [IoT למתחילים - חקלאות דיגיטלית, פרויקט 2](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) מתוך [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![שלוט במכשיר ה-IoT שלך עם קוד ללא שרת](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## שאלון לפני השיעור

[שאלון לפני השיעור](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## מבוא

בשיעור הקודם, למדת כיצד לחבר את ניטור לחות הקרקע של הצמח שלך ואת בקרת הממסר לשירות IoT מבוסס ענן. השלב הבא הוא להעביר את קוד השרת שמנהל את תזמון הממסר לענן. בשיעור הזה תלמד כיצד לעשות זאת באמצעות פונקציות ללא שרת.

בשיעור הזה נעסוק ב:

* [מה זה ללא שרת?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [יצירת אפליקציה ללא שרת](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [יצירת טריגר אירוע IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [שליחת בקשות שיטה ישירה מקוד ללא שרת](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [פריסת הקוד ללא שרת לענן](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## מה זה ללא שרת?

ללא שרת, או מחשוב ללא שרת, כולל יצירת בלוקים קטנים של קוד שמופעלים בענן בתגובה לסוגים שונים של אירועים. כאשר האירוע מתרחש, הקוד שלך מופעל ומועבר אליו מידע על האירוע. אירועים אלו יכולים להגיע ממגוון מקורות, כולל בקשות אינטרנט, הודעות בתור, שינויים בנתונים בבסיס נתונים, או הודעות שנשלחות לשירות IoT על ידי מכשירי IoT.

![אירועים שנשלחים משירות IoT לשירות ללא שרת, כולם מעובדים בו זמנית על ידי פונקציות מרובות](../../../../../translated_images/he/iot-messages-to-serverless.0194da1cc0732bb7d0f823aed3fce54735c6b1ad3bf36089804d8aaefc0a774f.png)

> 💁 אם השתמשת בעבר בטריגרים של בסיס נתונים, תוכל לחשוב על זה כמשהו דומה - קוד שמופעל על ידי אירוע כמו הכנסת שורה.

![כאשר אירועים רבים נשלחים בו זמנית, שירות ללא שרת מתרחב כדי להפעיל את כולם בו זמנית](../../../../../translated_images/he/serverless-scaling.f8c769adf0413fd1.webp)

הקוד שלך מופעל רק כאשר האירוע מתרחש, ואין שום דבר שמחזיק את הקוד שלך פעיל בזמנים אחרים. האירוע מתרחש, הקוד שלך נטען ומופעל. זה הופך את המודל ללא שרת למאוד ניתן להרחבה - אם אירועים רבים מתרחשים בו זמנית, ספק הענן יכול להפעיל את הפונקציה שלך כמה פעמים שצריך בו זמנית על פני כל השרתים הזמינים. החיסרון הוא שאם אתה צריך לשתף מידע בין אירועים, תצטרך לשמור אותו במקום כלשהו כמו בסיס נתונים במקום בזיכרון.

הקוד שלך נכתב כפונקציה שמקבלת פרטים על האירוע כפרמטר. ניתן להשתמש במגוון רחב של שפות תכנות לכתיבת פונקציות ללא שרת.

> 🎓 ללא שרת נקרא גם פונקציות כשירות (FaaS), מכיוון שכל טריגר אירוע מיושם כפונקציה בקוד.

למרות השם, ללא שרת כן משתמש בשרתים. השם נובע מכך שאתה כמפתח לא צריך לדאוג לשרתים הנדרשים להפעלת הקוד שלך, כל מה שחשוב לך הוא שהקוד שלך יופעל בתגובה לאירוע. ספק הענן מחזיק *סביבת עבודה ללא שרת* שמנהלת את הקצאת השרתים, הרשת, האחסון, המעבד, הזיכרון וכל מה שצריך כדי להפעיל את הקוד שלך. מודל זה אומר שאתה לא משלם לפי שרת, אלא לפי הזמן שבו הקוד שלך פועל וכמות הזיכרון שנעשה בו שימוש.

> 💰 ללא שרת הוא אחד הדרכים הזולות ביותר להפעיל קוד בענן. לדוגמה, בזמן כתיבת שורות אלו, ספק ענן אחד מאפשר לכל הפונקציות שלך לפעול יחד 1,000,000 פעמים בחודש לפני שהם מתחילים לחייב אותך, ולאחר מכן הם גובים 0.20 דולר אמריקאי עבור כל 1,000,000 הפעלות. כאשר הקוד שלך לא פועל, אתה לא משלם.

כמפתח IoT, המודל ללא שרת הוא אידיאלי. תוכל לכתוב פונקציה שמופעלת בתגובה להודעות שנשלחות מכל מכשיר IoT שמחובר לשירות IoT שלך בענן. הקוד שלך יטפל בכל ההודעות שנשלחות, אך יפעל רק כשצריך.

✅ חזור לקוד שכתבת כקוד שרת שמאזין להודעות דרך MQTT. איך לדעתך זה יכול לפעול בענן באמצעות ללא שרת? איך לדעתך הקוד עשוי להשתנות כדי לתמוך במחשוב ללא שרת?

> 💁 המודל ללא שרת מתרחב לשירותי ענן נוספים בנוסף להפעלת קוד. לדוגמה, קיימים בסיסי נתונים ללא שרת בענן שמשתמשים במודל תמחור ללא שרת שבו אתה משלם לפי בקשה שנעשית נגד בסיס הנתונים, כמו שאילתה או הכנסת נתונים, בדרך כלל בהתבסס על כמות העבודה שנעשית כדי לשרת את הבקשה. לדוגמה, שאילתה אחת של שורה אחת נגד מפתח ראשי תעלה פחות מאשר פעולה מורכבת שמצטרפת לטבלאות רבות ומחזירה אלפי שורות.

## יצירת אפליקציה ללא שרת

שירות המחשוב ללא שרת של מיקרוסופט נקרא Azure Functions.

![לוגו של Azure Functions](../../../../../translated_images/he/azure-functions-logo.1cfc8e3204c9c44aaf80fcf406fc8544d80d7f00f8d3e8ed6fed764563e17564.png)

הסרטון הקצר למטה מציג סקירה כללית של Azure Functions.

[![סרטון סקירה של Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 לחץ על התמונה למעלה לצפייה בסרטון

✅ הקדש רגע למחקר וקרא את הסקירה של Azure Functions בתיעוד [Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

כדי לכתוב פונקציות Azure, מתחילים עם אפליקציית פונקציות בשפה לבחירתך. Azure Functions תומך באופן מובנה ב-Python, JavaScript, TypeScript, C#, F#, Java ו-Powershell. בשיעור הזה תלמד כיצד לכתוב אפליקציית פונקציות Azure ב-Python.

> 💁 Azure Functions תומך גם במטפלים מותאמים אישית, כך שתוכל לכתוב את הפונקציות שלך בכל שפה שתומכת בבקשות HTTP, כולל שפות ישנות כמו COBOL.

אפליקציות פונקציות מורכבות מטריגרים אחד או יותר - פונקציות שמגיבות לאירועים. ניתן לכלול מספר טריגרים בתוך אפליקציית פונקציות אחת, שכולן חולקות תצורה משותפת. לדוגמה, בקובץ התצורה של אפליקציית הפונקציות שלך תוכל לכלול את פרטי החיבור של ה-IoT Hub שלך, וכל הפונקציות באפליקציה יוכלו להשתמש בזה כדי להתחבר ולהאזין לאירועים.

### משימה - התקנת כלי Azure Functions

> בזמן כתיבת שורות אלו, כלי הקוד של Azure Functions לא פועלים באופן מלא על מחשבי Apple Silicon עם פרויקטים של Python. תצטרך להשתמש במחשב Mac מבוסס Intel, מחשב Windows או מחשב Linux במקום.

אחת התכונות הנהדרות של Azure Functions היא שניתן להפעיל אותן באופן מקומי. אותה סביבת עבודה שמשמשת בענן יכולה לפעול על המחשב שלך, מה שמאפשר לך לכתוב קוד שמגיב להודעות IoT ולהפעיל אותו באופן מקומי. תוכל אפילו לנפות שגיאות בקוד שלך בזמן שהאירועים מטופלים. לאחר שתהיה מרוצה מהקוד שלך, תוכל לפרוס אותו לענן.

כלי Azure Functions זמינים כ-CLI, הידוע בשם Azure Functions Core Tools.

1. התקן את כלי Azure Functions Core Tools על ידי ביצוע ההוראות בתיעוד [Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. התקן את התוסף Azure Functions עבור VS Code. תוסף זה מספק תמיכה ביצירה, ניפוי שגיאות ופריסת פונקציות Azure. עיין בתיעוד [Azure Functions extension](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions) להוראות התקנה של תוסף זה ב-VS Code.

כאשר אתה מפרסם את אפליקציית הפונקציות שלך לענן, היא צריכה להשתמש בכמות קטנה של אחסון ענן כדי לאחסן דברים כמו קבצי האפליקציה וקבצי יומן. כאשר אתה מפעיל את אפליקציית הפונקציות שלך באופן מקומי, עדיין תצטרך להתחבר לאחסון ענן, אך במקום להשתמש באחסון ענן אמיתי, תוכל להשתמש באמולטור אחסון בשם [Azurite](https://github.com/Azure/Azurite). זה פועל באופן מקומי אך מתנהג כמו אחסון ענן.

> 🎓 ב-Azure, האחסון שבו Azure Functions משתמש הוא חשבון אחסון Azure. חשבונות אלו יכולים לאחסן קבצים, בלובים, נתונים בטבלאות או נתונים בתורים. ניתן לשתף חשבון אחסון אחד בין אפליקציות רבות, כמו אפליקציית פונקציות ואפליקציית אינטרנט.

1. Azurite הוא אפליקציית Node.js, ולכן תצטרך להתקין את Node.js. תוכל למצוא את הוראות ההורדה וההתקנה באתר [Node.js](https://nodejs.org/). אם אתה משתמש ב-Mac, תוכל גם להתקין אותו מ-[Homebrew](https://formulae.brew.sh/formula/node).

1. התקן את Azurite באמצעות הפקודה הבאה (`npm` הוא כלי שמותקן כאשר אתה מתקין את Node.js):

    ```sh
    npm install -g azurite
    ```

1. צור תיקייה בשם `azurite` עבור Azurite לשימוש לאחסון נתונים:

    ```sh
    mkdir azurite
    ```

1. הפעל את Azurite, תוך העברת התיקייה החדשה הזו:

    ```sh
    azurite --location azurite
    ```

    אמולטור האחסון Azurite יופעל ויהיה מוכן להתחברות של סביבת העבודה המקומית של פונקציות.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### משימה - יצירת פרויקט פונקציות Azure

ניתן להשתמש ב-CLI של Azure Functions כדי ליצור אפליקציית פונקציות חדשה.

1. צור תיקייה עבור אפליקציית הפונקציות שלך ועבור אליה. קרא לה `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. צור סביבה וירטואלית של Python בתוך תיקייה זו:

    ```sh
    python3 -m venv .venv
    ```

1. הפעל את הסביבה הווירטואלית:

    * ב-Windows:
        * אם אתה משתמש ב-Command Prompt או ב-Command Prompt דרך Windows Terminal, הפעל:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * אם אתה משתמש ב-PowerShell, הפעל:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * ב-macOS או Linux, הפעל:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 פקודות אלו צריכות להיות מופעלות מהמיקום שבו הפעלת את הפקודה ליצירת הסביבה הווירטואלית. לעולם לא תצטרך לנווט לתוך תיקיית `.venv`, תמיד עליך להפעיל את הפקודה להפעלה וכל פקודה להתקנת חבילות או הפעלת קוד מהמיקום שבו היית כשיצרת את הסביבה הווירטואלית.

1. הפעל את הפקודה הבאה כדי ליצור אפליקציית פונקציות בתיקייה זו:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    פעולה זו תיצור שלושה קבצים בתוך התיקייה הנוכחית:

    * `host.json` - מסמך JSON זה מכיל הגדרות עבור אפליקציית הפונקציות שלך. לא תצטרך לשנות הגדרות אלו.
    * `local.settings.json` - מסמך JSON זה מכיל הגדרות שהאפליקציה שלך תשתמש בהן כאשר היא פועלת באופן מקומי, כמו מחרוזות חיבור ל-IoT Hub שלך. הגדרות אלו הן מקומיות בלבד ולא צריכות להיכלל בבקרת קוד מקור. כאשר אתה מפרסם את האפליקציה לענן, הגדרות אלו לא יפורסמו, במקום זאת ההגדרות שלך ייטענו מהגדרות האפליקציה. זה יכוסה מאוחר יותר בשיעור הזה.
    * `requirements.txt` - זהו [קובץ דרישות Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files) שמכיל את חבילות ה-Pip הדרושות להפעלת אפליקציית הפונקציות שלך.

1. קובץ `local.settings.json` מכיל הגדרה עבור חשבון האחסון שבו אפליקציית הפונקציות תשתמש. ברירת המחדל היא הגדרה ריקה, ולכן יש להגדיר אותה. כדי להתחבר לאמולטור האחסון המקומי Azurite, הגדר ערך זה ל:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. התקן את חבילות ה-Pip הדרושות באמצעות קובץ הדרישות:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 חבילות ה-Pip הדרושות צריכות להיות בקובץ זה, כך שכאשר אפליקציית הפונקציות תפורסם לענן, סביבת העבודה תוכל לוודא שהיא מתקינה את החבילות הנכונות.

1. כדי לבדוק שהכל עובד כראוי, תוכל להפעיל את סביבת העבודה של הפונקציות. הפעל את הפקודה הבאה כדי לעשות זאת:

    ```sh
    func start
    ```

    תראה את סביבת העבודה מתחילה ומדווחת שהיא לא מצאה פונקציות עבודה (טריגרים).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ אם אתה מקבל התראה על חומת אש, הענק גישה מכיוון שהיישום `func` צריך להיות מסוגל לקרוא ולכתוב ברשת שלך.
> ⚠️ אם אתה משתמש ב-macOS, ייתכן שיופיעו אזהרות בתוצאה:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> ניתן להתעלם מהן כל עוד אפליקציית הפונקציות מתחילה כראוי ומציגה את הפונקציות הפעילות. כפי שמוזכר [בשאלה זו ב-Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), ניתן להתעלם מכך.

1. עצור את אפליקציית הפונקציות על ידי לחיצה על `ctrl+c`.

1. פתח את התיקייה הנוכחית ב-VS Code, או על ידי פתיחת VS Code ואז פתיחת התיקייה הזו, או על ידי הרצת הפקודה הבאה:

    ```sh
    code .
    ```

    VS Code יזהה את פרויקט הפונקציות שלך ויציג הודעה שאומרת:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![ההודעה](../../../../../translated_images/he/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    בחר **כן** מההודעה הזו.

1. ודא שסביבת העבודה הווירטואלית של Python פועלת בטרמינל של VS Code. סיים אותה והפעל מחדש אם יש צורך.

## יצירת טריגר לאירועי IoT Hub

אפליקציית הפונקציות היא מעטפת לקוד חסר השרת שלך. כדי להגיב לאירועים מ-IoT Hub, ניתן להוסיף טריגר IoT Hub לאפליקציה זו. הטריגר צריך להתחבר לזרם ההודעות שנשלחות ל-IoT Hub ולהגיב להן. כדי לקבל את זרם ההודעות הזה, הטריגר שלך צריך להתחבר ל-*נקודת הקצה התואמת של Event Hub*.

IoT Hub מבוסס על שירות Azure אחר שנקרא Azure Event Hubs. Event Hubs הוא שירות שמאפשר לשלוח ולקבל הודעות, ו-IoT Hub מרחיב אותו כדי להוסיף תכונות למכשירי IoT. הדרך שבה מתחברים לקרוא הודעות מ-IoT Hub זהה לזו שבה היית משתמש ב-Event Hubs.

✅ בצע מחקר: קרא את סקירת Event Hubs ב-[תיעוד Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). כיצד התכונות הבסיסיות משוות ל-IoT Hub?

כדי שמכשיר IoT יתחבר ל-IoT Hub, עליו להשתמש במפתח סודי שמבטיח שרק מכשירים מורשים יוכלו להתחבר. אותו עיקרון חל גם כאשר מתחברים לקרוא הודעות; הקוד שלך יצטרך מחרוזת חיבור שמכילה מפתח סודי יחד עם פרטי ה-IoT Hub.

> 💁 מחרוזת החיבור המוגדרת כברירת מחדל כוללת הרשאות **iothubowner**, שמעניקות לקוד שמשתמש בה הרשאות מלאות על ה-IoT Hub. באופן אידיאלי, כדאי להתחבר עם רמת ההרשאות הנמוכה ביותר הנדרשת. זה יכוסה בשיעור הבא.

לאחר שהטריגר התחבר, הקוד בתוך הפונקציה ייקרא עבור כל הודעה שנשלחת ל-IoT Hub, ללא קשר לאיזה מכשיר שלח אותה. הטריגר יקבל את ההודעה כפרמטר.

### משימה - קבלת מחרוזת החיבור לנקודת הקצה התואמת של Event Hub

1. מהטרמינל של VS Code, הרץ את הפקודה הבאה כדי לקבל את מחרוזת החיבור לנקודת הקצה התואמת של Event Hub ב-IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    החלף `<hub_name>` בשם שבו השתמשת עבור ה-IoT Hub שלך.

1. ב-VS Code, פתח את הקובץ `local.settings.json`. הוסף את הערך הבא בתוך הסעיף `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    החלף `<connection string>` בערך מהשלב הקודם. תצטרך להוסיף פסיק אחרי השורה הקודמת כדי להפוך את זה ל-JSON תקין.

### משימה - יצירת טריגר לאירוע

כעת אתה מוכן ליצור את הטריגר לאירוע.

1. מהטרמינל של VS Code, הרץ את הפקודה הבאה מתוך התיקייה `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    פעולה זו יוצרת פונקציה חדשה בשם `iot-hub-trigger`. הטריגר יתחבר לנקודת הקצה התואמת של Event Hub ב-IoT Hub, כך שתוכל להשתמש בטריגר של Event Hub. אין טריגר ספציפי ל-IoT Hub.

פעולה זו תיצור תיקייה בתוך התיקייה `soil-moisture-trigger` בשם `iot-hub-trigger` שמכילה את הפונקציה הזו. בתיקייה זו יהיו הקבצים הבאים:

* `__init__.py` - זהו קובץ הקוד של Python שמכיל את הטריגר, תוך שימוש בשם הקובץ הסטנדרטי של Python כדי להפוך את התיקייה הזו למודול Python.

    קובץ זה יכיל את הקוד הבא:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    הליבה של הטריגר היא הפונקציה `main`. פונקציה זו נקראת עם האירועים מ-IoT Hub. לפונקציה יש פרמטר בשם `event` שמכיל `EventHubEvent`. בכל פעם שנשלחת הודעה ל-IoT Hub, פונקציה זו נקראת ומעבירה את ההודעה כ-`event`, יחד עם מאפיינים שהם זהים להערות שראית בשיעור הקודם.

    הליבה של פונקציה זו רושמת את האירוע.

* `function.json` - זהו קובץ שמכיל תצורה עבור הטריגר. התצורה העיקרית נמצאת בסעיף שנקרא `bindings`. Binding הוא המונח לחיבור בין פונקציות Azure לשירותי Azure אחרים. פונקציה זו כוללת binding קלט ל-Event Hub - היא מתחברת ל-Event Hub ומקבלת נתונים.

    > 💁 ניתן גם להגדיר binding פלט כך שפלט הפונקציה יישלח לשירות אחר. לדוגמה, ניתן להוסיף binding פלט למסד נתונים ולהחזיר את אירוע ה-IoT Hub מהפונקציה, והוא יוכנס אוטומטית למסד הנתונים.

    ✅ בצע מחקר: קרא על bindings ב-[תיעוד הקונספטים של טריגרים ו-bindings של פונקציות Azure](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    הסעיף `bindings` כולל תצורה עבור ה-binding. הערכים המעניינים הם:

  * `"type": "eventHubTrigger"` - זה אומר לפונקציה שהיא צריכה להאזין לאירועים מ-Event Hub
  * `"name": "events"` - זהו שם הפרמטר לשימוש עבור אירועי Event Hub. זה תואם לשם הפרמטר בפונקציה `main` בקוד Python.
  * `"direction": "in"` - זהו binding קלט, הנתונים מ-Event Hub נכנסים לפונקציה
  * `"connection": ""` - זה מגדיר את שם ההגדרה לקרוא את מחרוזת החיבור. כאשר מריצים מקומית, זה יקרא את ההגדרה הזו מהקובץ `local.settings.json`.

    > 💁 מחרוזת החיבור לא יכולה להיות מאוחסנת בקובץ `function.json`, היא חייבת להיקרא מההגדרות. זאת כדי למנוע חשיפה מקרית של מחרוזת החיבור שלך.

1. עקב [באג בתבנית פונקציות Azure](https://github.com/Azure/azure-functions-templates/issues/1250), הערך `cardinality` בקובץ `function.json` שגוי. עדכן ערך זה מ-`many` ל-`one`:

    ```json
    "cardinality": "one",
    ```

1. עדכן את הערך של `"connection"` בקובץ `function.json` כך שיצביע על הערך החדש שהוספת לקובץ `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 זכור - זה צריך להצביע על ההגדרה, ולא להכיל את מחרוזת החיבור בפועל.

1. מחרוזת החיבור מכילה את הערך `eventHubName`, ולכן הערך עבור זה בקובץ `function.json` צריך להיות ריק. עדכן ערך זה למחרוזת ריקה:

    ```json
    "eventHubName": "",
    ```

### משימה - הרצת הטריגר לאירוע

1. ודא שאינך מריץ את המוניטור לאירועי IoT Hub. אם זה פועל בו זמנית עם אפליקציית הפונקציות, אפליקציית הפונקציות לא תוכל להתחבר ולצרוך אירועים.

    > 💁 אפליקציות מרובות יכולות להתחבר לנקודות הקצה של IoT Hub באמצעות *קבוצות צרכנים* שונות. אלו יכוסו בשיעור מאוחר יותר.

1. כדי להריץ את אפליקציית הפונקציות, הרץ את הפקודה הבאה מהטרמינל של VS Code:

    ```sh
    func start
    ```

    אפליקציית הפונקציות תתחיל ותזהה את הפונקציה `iot-hub-trigger`. היא תעבד כל אירועים שכבר נשלחו ל-IoT Hub במהלך היום האחרון.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    כל קריאה לפונקציה תוקף על ידי בלוק `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` בתוצאה, כך שתוכל לראות כמה הודעות עובדו בכל קריאה לפונקציה.

1. ודא שמכשיר ה-IoT שלך פועל. תראה הודעות חדשות על לחות הקרקע מופיעות באפליקציית הפונקציות.

1. עצור והפעל מחדש את אפליקציית הפונקציות. תראה שהיא לא תעבד הודעות קודמות שוב, אלא רק הודעות חדשות.

> 💁 VS Code תומך גם בניפוי שגיאות של הפונקציות שלך. ניתן להגדיר נקודות עצירה על ידי לחיצה על הגבול בתחילת כל שורת קוד, או על ידי הצבת הסמן על שורת קוד ובחירה ב-*Run -> Toggle breakpoint*, או לחיצה על `F9`. ניתן להפעיל את מנפה השגיאות על ידי בחירה ב-*Run -> Start debugging*, לחיצה על `F5`, או בחירה בלשונית *Run and debug* ובחירה בכפתור **Start debugging**. על ידי כך תוכל לראות את פרטי האירועים המעובדים.

#### פתרון בעיות

* אם אתה מקבל את השגיאה הבאה:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    בדוק ש-Azurite פועל ושקבעת את `AzureWebJobsStorage` בקובץ `local.settings.json` ל-`UseDevelopmentStorage=true`.

* אם אתה מקבל את השגיאה הבאה:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    בדוק שקבעת את `cardinality` בקובץ `function.json` ל-`one`.

* אם אתה מקבל את השגיאה הבאה:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    בדוק שקבעת את `eventHubName` בקובץ `function.json` למחרוזת ריקה.

## שליחת בקשות שיטה ישירה מקוד חסר שרת

עד כה אפליקציית הפונקציות שלך מאזינה להודעות מ-IoT Hub באמצעות נקודת הקצה התואמת של Event Hub. כעת עליך לשלוח פקודות למכשיר IoT. פעולה זו מתבצעת באמצעות חיבור שונה ל-IoT Hub דרך *Registry Manager*. ה-Registry Manager הוא כלי שמאפשר לך לראות אילו מכשירים רשומים ב-IoT Hub, ולתקשר עם אותם מכשירים על ידי שליחת הודעות ענן למכשיר, בקשות שיטה ישירה או עדכון ה-Device Twin. ניתן גם להשתמש בו כדי לרשום, לעדכן או למחוק מכשירי IoT מ-IoT Hub.

כדי להתחבר ל-Registry Manager, תצטרך מחרוזת חיבור.

### משימה - קבלת מחרוזת החיבור ל-Registry Manager

1. כדי לקבל את מחרוזת החיבור, הרץ את הפקודה הבאה:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    החלף `<hub_name>` בשם שבו השתמשת עבור ה-IoT Hub שלך.

    מחרוזת החיבור מתבקשת עבור מדיניות *ServiceConnect* באמצעות הפרמטר `--policy-name service`. כאשר אתה מבקש מחרוזת חיבור, תוכל לציין אילו הרשאות מחרוזת החיבור תאפשר. מדיניות ServiceConnect מאפשרת לקוד שלך להתחבר ולשלוח הודעות למכשירי IoT.

    ✅ בצע מחקר: קרא על המדיניות השונות ב-[תיעוד ההרשאות של IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. ב-VS Code, פתח את הקובץ `local.settings.json`. הוסף את הערך הבא בתוך הסעיף `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    החלף `<connection string>` בערך מהשלב הקודם. תצטרך להוסיף פסיק אחרי השורה הקודמת כדי להפוך את זה ל-JSON תקין.

### משימה - שליחת בקשת שיטה ישירה למכשיר

1. ה-SDK עבור ה-Registry Manager זמין דרך חבילת Pip. הוסף את השורה הבאה לקובץ `requirements.txt` כדי להוסיף תלות בחבילה זו:

    ```sh
    azure-iot-hub
    ```

1. ודא שהטרמינל של VS Code מפעיל את סביבת העבודה הווירטואלית, והרץ את הפקודה הבאה כדי להתקין את חבילות ה-Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. הוסף את הייבואים הבאים לקובץ `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    זה מייבא כמה ספריות מערכת, כמו גם את הספריות לתקשורת עם ה-Registry Manager ושליחת בקשות שיטה ישירה.

1. הסר את הקוד מתוך הפונקציה `main`, אך שמור את הפונקציה עצמה.

1. בתוך הפונקציה `main`, הוסף את הקוד הבא:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    קוד זה מוציא את גוף האירוע שמכיל את הודעת ה-JSON שנשלחה על ידי מכשיר ה-IoT.

    לאחר מכן הוא מקבל את מזהה המכשיר מההערות שהועברו עם ההודעה. גוף האירוע מכיל את ההודעה שנשלחה כטֶלֶמֶטרִיָה, המילון `iothub_metadata` מכיל מאפיינים שהוגדרו על ידי IoT Hub כמו מזהה המכשיר של השולח וזמן שליחת ההודעה.

    מידע זה נרשם ביומן. תוכל לראות את הרישום הזה בטרמינל כאשר אתה מריץ את אפליקציית הפונקציות באופן מקומי.

1. מתחת לזה, הוסף את הקוד הבא:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    קוד זה מקבל את לחות הקרקע מההודעה. לאחר מכן הוא בודק את לחות הקרקע, ותלוי בערך, יוצר מחלקת עזר לבקשת שיטה ישירה עבור השיטה `relay_on` או `relay_off`. בקשת השיטה אינה זקוקה למטען, ולכן נשלח מסמך JSON ריק.

1. מתחת לזה הוסף את הקוד הבא:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
קוד זה טוען את `REGISTRY_MANAGER_CONNECTION_STRING` מתוך קובץ `local.settings.json`. הערכים בקובץ זה זמינים כמשתני סביבה, וניתן לקרוא אותם באמצעות הפונקציה `os.environ`, פונקציה שמחזירה מילון של כל משתני הסביבה.

💁 כאשר קוד זה נפרס לענן, הערכים בקובץ `local.settings.json` יוגדרו כ-*Application Settings*, וניתן יהיה לקרוא אותם ממשתני סביבה.

הקוד יוצר לאחר מכן מופע של מחלקת העזר Registry Manager באמצעות מחרוזת החיבור.

1. הוסף את הקוד הבא מתחת:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    קוד זה אומר ל-Registry Manager לשלוח בקשת שיטה ישירה למכשיר ששלח את הטלמטריה.

    💁 בגרסאות של האפליקציה שיצרת בשיעורים קודמים באמצעות MQTT, פקודות השליטה בממסר נשלחו לכל המכשירים. הקוד הניח שיש לך רק מכשיר אחד. גרסה זו של הקוד שולחת את בקשת השיטה למכשיר יחיד, כך שהיא תעבוד אם יש לך מספר מערכות של חיישני לחות וממסרים, ותשלח את בקשת השיטה הישירה למכשיר הנכון.

1. הרץ את אפליקציית הפונקציות, וודא שמכשיר ה-IoT שלך שולח נתונים. תראה את ההודעות מעובדות ואת בקשות השיטה הישירה נשלחות. הזז את חיישן לחות הקרקע פנימה והחוצה מהקרקע כדי לראות את הערכים משתנים ואת הממסר נדלק ונכבה.

💁 תוכל למצוא את הקוד הזה בתיקיית [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## פרוס את הקוד חסר השרת שלך לענן

הקוד שלך עובד כעת באופן מקומי, ולכן השלב הבא הוא לפרוס את אפליקציית הפונקציות לענן.

### משימה - צור את משאבי הענן

אפליקציית הפונקציות שלך צריכה להיות פרוסה למשאב אפליקציית פונקציות ב-Azure, שנמצא בתוך קבוצת המשאבים שיצרת עבור IoT Hub שלך. תצטרך גם חשבון אחסון שנוצר ב-Azure כדי להחליף את האחסון המדומה שפועל באופן מקומי.

1. הרץ את הפקודה הבאה כדי ליצור חשבון אחסון:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    החלף `<storage_name>` בשם עבור חשבון האחסון שלך. שם זה צריך להיות ייחודי גלובלית מכיוון שהוא מהווה חלק מכתובת ה-URL המשמשת לגישה לחשבון האחסון. ניתן להשתמש רק באותיות קטנות ומספרים עבור שם זה, ללא תווים אחרים, והוא מוגבל ל-24 תווים. השתמש במשהו כמו `sms` והוסף מזהה ייחודי בסוף, כמו מילים אקראיות או שמך.

    האפשרות `--sku Standard_LRS` בוחרת את שכבת התמחור, ובוחרת את חשבון המטרה הכללי בעלות הנמוכה ביותר. אין שכבת אחסון חינמית, ואתה משלם עבור מה שאתה משתמש. העלויות יחסית נמוכות, עם האחסון היקר ביותר בפחות מ-0.05 דולר לחודש לכל ג'יגה-בייט מאוחסן.

    ✅ קרא על תמחור בעמוד [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. הרץ את הפקודה הבאה כדי ליצור אפליקציית פונקציות:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    החלף `<location>` במיקום שבו השתמשת בעת יצירת קבוצת המשאבים בשיעור הקודם.

    החלף `<storage_name>` בשם חשבון האחסון שיצרת בשלב הקודם.

    החלף `<functions_app_name>` בשם ייחודי עבור אפליקציית הפונקציות שלך. שם זה צריך להיות ייחודי גלובלית מכיוון שהוא מהווה חלק מכתובת URL שניתן להשתמש בה לגישה לאפליקציית הפונקציות. השתמש במשהו כמו `soil-moisture-sensor-` והוסף מזהה ייחודי בסוף, כמו מילים אקראיות או שמך.

    האפשרות `--functions-version 3` מגדירה את גרסת Azure Functions לשימוש. גרסה 3 היא הגרסה האחרונה.

    האפשרות `--os-type Linux` אומרת ל-runtime של הפונקציות להשתמש בלינוקס כמערכת ההפעלה לאירוח הפונקציות הללו. פונקציות יכולות להיות מאוחסנות בלינוקס או ב-Windows, תלוי בשפת התכנות שבה נעשה שימוש. אפליקציות Python נתמכות רק בלינוקס.

### משימה - העלה את הגדרות האפליקציה שלך

כאשר פיתחת את אפליקציית הפונקציות שלך, שמרת כמה הגדרות בקובץ `local.settings.json` עבור מחרוזות החיבור ל-IoT Hub שלך. יש לכתוב אותן ל-Application Settings באפליקציית הפונקציות שלך ב-Azure כדי שניתן יהיה להשתמש בהן בקוד שלך.

🎓 קובץ `local.settings.json` מיועד רק להגדרות פיתוח מקומיות, ואין לבדוק אותו לתוך בקרת קוד מקור, כמו GitHub. כאשר נפרס לענן, נעשה שימוש ב-Application Settings. Application Settings הם זוגות מפתח/ערך שמתארחים בענן ונקראים ממשתני סביבה בקוד שלך או על ידי ה-runtime כאשר הוא מחבר את הקוד שלך ל-IoT Hub.

1. הרץ את הפקודה הבאה כדי להגדיר את הגדרת `IOT_HUB_CONNECTION_STRING` ב-Application Settings של אפליקציית הפונקציות:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    החלף `<functions_app_name>` בשם שבו השתמשת עבור אפליקציית הפונקציות שלך.

    החלף `<connection string>` בערך של `IOT_HUB_CONNECTION_STRING` מתוך קובץ `local.settings.json` שלך.

1. חזור על השלב לעיל, אך הגדר את הערך של `REGISTRY_MANAGER_CONNECTION_STRING` לערך המתאים מתוך קובץ `local.settings.json` שלך.

כאשר אתה מריץ את הפקודות הללו, הן גם יפיקו רשימה של כל ה-Application Settings עבור אפליקציית הפונקציות. תוכל להשתמש בזה כדי לבדוק שהערכים שלך מוגדרים נכון.

💁 תראה ערך שכבר מוגדר עבור `AzureWebJobsStorage`. בקובץ `local.settings.json` שלך, זה הוגדר לערך לשימוש באחסון המדומה המקומי. כאשר יצרת את אפליקציית הפונקציות, העברת את חשבון האחסון כפרמטר, וזה מוגדר אוטומטית בהגדרה זו.

### משימה - פרוס את אפליקציית הפונקציות שלך לענן

כעת, כאשר אפליקציית הפונקציות מוכנה, ניתן לפרוס את הקוד שלך.

1. הרץ את הפקודה הבאה מתוך מסוף VS Code כדי לפרסם את אפליקציית הפונקציות שלך:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    החלף `<functions_app_name>` בשם שבו השתמשת עבור אפליקציית הפונקציות שלך.

הקוד ייארז וישלח לאפליקציית הפונקציות, שם הוא ייפרס ויופעל. תהיה הרבה פלט במסוף, שיסתיים באישור הפריסה ורשימה של הפונקציות שפורסו. במקרה זה הרשימה תכיל רק את ה-trigger.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

וודא שמכשיר ה-IoT שלך פועל. שנה את רמות הלחות על ידי התאמת לחות הקרקע או הזזת החיישן פנימה והחוצה מהקרקע. תראה את הממסר נדלק ונכבה כאשר לחות הקרקע משתנה.

---

## 🚀 אתגר

בשיעור הקודם, ניהלת את התזמון עבור הממסר על ידי ביטול ההרשמה להודעות MQTT בזמן שהממסר היה דולק, ולמשך זמן קצר לאחר שהוא נכבה. אינך יכול להשתמש בשיטה זו כאן - אינך יכול לבטל את ההרשמה ל-trigger של IoT Hub שלך.

חשוב על דרכים שונות שבהן תוכל להתמודד עם זה באפליקציית הפונקציות שלך.

## שאלון לאחר השיעור

[שאלון לאחר השיעור](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## סקירה ולימוד עצמי

* קרא על מחשוב חסר שרת בעמוד [Serverless Computing page on Wikipedia](https://wikipedia.org/wiki/Serverless_computing)
* קרא על שימוש ב-serverless ב-Azure כולל כמה דוגמאות נוספות בפוסט [Go serverless for your IoT needs Azure blog post](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* למד עוד על Azure Functions בערוץ [Azure Functions YouTube channel](https://www.youtube.com/c/AzureFunctions)

## משימה

[הוסף שליטה ידנית בממסר](assignment.md)

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור הסמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.