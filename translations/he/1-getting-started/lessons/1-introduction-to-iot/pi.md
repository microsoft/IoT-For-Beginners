<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-27T22:05:10+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "he"
}
-->
# רספברי פאי

ה-[Raspberry Pi](https://raspberrypi.org) הוא מחשב חד-לוח. ניתן להוסיף חיישנים ומפעילים באמצעות מגוון רחב של מכשירים ואקוסיסטמות, ובשיעורים אלו נעשה שימוש באקוסיסטמה חומרתית בשם [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). תכתבו קוד עבור ה-Pi ותיגשו לחיישני Grove באמצעות Python.

![רספברי פאי 4](../../../../../translated_images/he/raspberry-pi-4.fd4590d308c3d456.webp)

## הגדרות

אם אתם משתמשים ברספברי פאי כחומרת IoT שלכם, יש לכם שתי אפשרויות - תוכלו לעבוד על כל השיעורים הללו ולכתוב קוד ישירות על ה-Pi, או להתחבר מרחוק ל-Pi 'ללא ראש' ולכתוב קוד מהמחשב שלכם.

לפני שתתחילו, עליכם גם לחבר את Grove Base Hat ל-Pi שלכם.

### משימה - הגדרות

התקינו את Grove Base Hat על ה-Pi שלכם והגדירו את ה-Pi.

1. חברו את Grove Base Hat ל-Pi שלכם. השקע על ה-Hat מתאים לכל פיני ה-GPIO על ה-Pi, מחליק עד הסוף על הפינים כדי לשבת בצורה יציבה על הבסיס. הוא יושב מעל ה-Pi ומכסה אותו.

    ![חיבור Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. החליטו כיצד תרצו לתכנת את ה-Pi שלכם, ופנו לסעיף הרלוונטי למטה:

    * [עבודה ישירה על ה-Pi שלכם](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [גישה מרחוק לכתיבת קוד על ה-Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### עבודה ישירה על ה-Pi שלכם

אם אתם רוצים לעבוד ישירות על ה-Pi שלכם, תוכלו להשתמש בגרסת הדסקטופ של Raspberry Pi OS ולהתקין את כל הכלים הדרושים.

#### משימה - עבודה ישירה על ה-Pi שלכם

הגדירו את ה-Pi שלכם לפיתוח.

1. עקבו אחר ההוראות במדריך [הגדרת Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) כדי להגדיר את ה-Pi שלכם, לחבר אותו למקלדת/עכבר/מסך, לחבר אותו לרשת WiFi או Ethernet ולעדכן את התוכנה.

כדי לתכנת את ה-Pi באמצעות חיישני ומפעילי Grove, תצטרכו להתקין עורך שיאפשר לכם לכתוב את קוד המכשיר, וספריות וכלים שונים שמתקשרים עם חומרת Grove.

1. לאחר שה-Pi שלכם יופעל מחדש, פתחו את הטרמינל על ידי לחיצה על אייקון **Terminal** בסרגל התפריט העליון, או בחרו *Menu -> Accessories -> Terminal*

1. הריצו את הפקודה הבאה כדי לוודא שהמערכת והתוכנה המותקנת מעודכנות:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. הריצו את הפקודות הבאות כדי להתקין את כל הספריות הדרושות לחומרת Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    זה מתחיל בהתקנת Git, יחד עם Pip להתקנת חבילות Python.

    אחת התכונות החזקות של Python היא היכולת להתקין [חבילות Pip](https://pypi.org) - אלו חבילות קוד שנכתבו על ידי אנשים אחרים ופורסמו באינטרנט. ניתן להתקין חבילת Pip על המחשב שלכם עם פקודה אחת, ואז להשתמש בחבילה הזו בקוד שלכם.

    חבילות Python של Seeed Grove צריכות להיות מותקנות ממקור. הפקודות הללו ישכפלו את הריפו שמכיל את קוד המקור של החבילה הזו, ואז יתקינו אותו באופן מקומי.

    > 💁 כברירת מחדל, כאשר אתם מתקינים חבילה היא זמינה בכל מקום במחשב שלכם, וזה יכול להוביל לבעיות עם גרסאות חבילות - כמו אפליקציה אחת שתלויה בגרסה אחת של חבילה שנשברת כאשר אתם מתקינים גרסה חדשה עבור אפליקציה אחרת. כדי להתמודד עם הבעיה הזו, ניתן להשתמש ב-[סביבת עבודה וירטואלית של Python](https://docs.python.org/3/library/venv.html), שהיא למעשה עותק של Python בתיקייה ייעודית, וכאשר אתם מתקינים חבילות Pip הן מותקנות רק לתיקייה הזו. לא תשתמשו בסביבות עבודה וירטואליות כאשר אתם משתמשים ב-Pi שלכם. סקריפט ההתקנה של Grove מתקין את חבילות Python של Grove באופן גלובלי, כך שאם תרצו להשתמש בסביבת עבודה וירטואלית תצטרכו להגדיר אותה ואז להתקין מחדש את חבילות Grove בתוך הסביבה הזו. קל יותר פשוט להשתמש בחבילות גלובליות, במיוחד מכיוון שרבים ממפתחי ה-Pi יפרמטו כרטיס SD נקי עבור כל פרויקט.

    לבסוף, זה מפעיל את ממשק I<sup>2</sup>C.

1. הפעילו מחדש את ה-Pi באמצעות התפריט או הרצת הפקודה הבאה בטרמינל:

    ```sh
    sudo reboot
    ```

1. לאחר שה-Pi יופעל מחדש, פתחו שוב את הטרמינל והריצו את הפקודה הבאה כדי להתקין את [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) - זהו העורך שבו תשתמשו לכתיבת קוד המכשיר שלכם ב-Python.

    ```sh
    sudo apt install code
    ```

    לאחר שזה יותקן, VS Code יהיה זמין מהתפריט העליון.

    > 💁 אתם חופשיים להשתמש בכל IDE או עורך Python עבור השיעורים הללו אם יש לכם כלי מועדף, אך ההוראות בשיעורים יתבססו על שימוש ב-VS Code.

1. התקינו את Pylance. זהו הרחבה עבור VS Code שמספקת תמיכה בשפת Python. עיינו בתיעוד [הרחבת Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) להוראות התקנה של הרחבה זו ב-VS Code.

### גישה מרחוק לכתיבת קוד על ה-Pi

במקום לכתוב קוד ישירות על ה-Pi, ניתן להפעיל אותו 'ללא ראש', כלומר לא מחובר למקלדת/עכבר/מסך, ולהגדיר ולכתוב עליו מהמחשב שלכם, באמצעות Visual Studio Code.

#### הגדרת מערכת ההפעלה של ה-Pi

כדי לכתוב קוד מרחוק, מערכת ההפעלה של ה-Pi צריכה להיות מותקנת על כרטיס SD.

##### משימה - הגדרת מערכת ההפעלה של ה-Pi

הגדירו את מערכת ההפעלה של ה-Pi ללא ראש.

1. הורידו את **Raspberry Pi Imager** מדף [תוכנת Raspberry Pi OS](https://www.raspberrypi.org/software/) והתקינו אותו

1. הכניסו כרטיס SD למחשב שלכם, באמצעות מתאם אם יש צורך

1. הפעילו את Raspberry Pi Imager

1. מתוך Raspberry Pi Imager, בחרו בכפתור **CHOOSE OS**, ואז בחרו *Raspberry Pi OS (Other)*, ואחריו *Raspberry Pi OS Lite (32-bit)*

    ![Raspberry Pi Imager עם Raspberry Pi OS Lite נבחר](../../../../../translated_images/he/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite היא גרסה של Raspberry Pi OS שאין לה ממשק משתמש גרפי או כלים מבוססי ממשק משתמש. אלו אינם נחוצים עבור Pi ללא ראש והופכים את ההתקנה לקטנה יותר ואת זמן האתחול למהיר יותר.

1. בחרו בכפתור **CHOOSE STORAGE**, ואז בחרו את כרטיס ה-SD שלכם

1. הפעילו את **Advanced Options** על ידי לחיצה על `Ctrl+Shift+X`. אפשרויות אלו מאפשרות תצורה מוקדמת של Raspberry Pi OS לפני שהיא נכתבת לכרטיס ה-SD.

    1. סמנו את תיבת הסימון **Enable SSH**, והגדירו סיסמה עבור המשתמש `pi`. זו תהיה הסיסמה שבה תשתמשו כדי להתחבר ל-Pi מאוחר יותר.

    1. אם אתם מתכננים להתחבר ל-Pi דרך WiFi, סמנו את תיבת הסימון **Configure WiFi**, והכניסו את ה-SSID והסיסמה של ה-WiFi שלכם, כמו גם בחירת המדינה של ה-WiFi שלכם. אין צורך לעשות זאת אם תשתמשו בכבל Ethernet. ודאו שהרשת שאליה אתם מתחברים היא אותה רשת שבה נמצא המחשב שלכם.

    1. סמנו את תיבת הסימון **Set locale settings**, והגדירו את המדינה ואזור הזמן שלכם

    1. בחרו בכפתור **SAVE**

1. בחרו בכפתור **WRITE** כדי לכתוב את מערכת ההפעלה לכרטיס ה-SD. אם אתם משתמשים ב-macOS, תתבקשו להזין את הסיסמה שלכם מכיוון שהכלי הבסיסי שכותב תמונות דיסק דורש גישה מורשית.

מערכת ההפעלה תיכתב לכרטיס ה-SD, וכאשר תושלם הכרטיס ייפלט על ידי מערכת ההפעלה, ותקבלו הודעה. הסירו את כרטיס ה-SD מהמחשב שלכם, הכניסו אותו ל-Pi, הפעילו את ה-Pi והמתינו כ-2 דקות כדי שיבצע אתחול כראוי.

#### התחברות ל-Pi

השלב הבא הוא גישה מרחוק ל-Pi. ניתן לעשות זאת באמצעות `ssh`, שזמין ב-macOS, Linux וגרסאות עדכניות של Windows.

##### משימה - התחברות ל-Pi

גשו ל-Pi מרחוק.

1. הפעילו טרמינל או Command Prompt, והכניסו את הפקודה הבאה כדי להתחבר ל-Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    אם אתם משתמשים ב-Windows בגרסה ישנה שאין בה `ssh` מותקן, תוכלו להשתמש ב-OpenSSH. תוכלו למצוא את הוראות ההתקנה בתיעוד [התקנת OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. זה אמור להתחבר ל-Pi שלכם ולבקש את הסיסמה.

    היכולת למצוא מחשבים ברשת שלכם באמצעות `<hostname>.local` היא תוספת די חדשה ל-Linux ו-Windows. אם אתם משתמשים ב-Linux או Windows ומקבלים שגיאות כלשהן על כך שלא נמצא שם המארח, תצטרכו להתקין תוכנה נוספת כדי לאפשר רשת ZeroConf (המכונה גם על ידי Apple בשם Bonjour):

    1. אם אתם משתמשים ב-Linux, התקינו את Avahi באמצעות הפקודה הבאה:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. אם אתם משתמשים ב-Windows, הדרך הקלה ביותר לאפשר ZeroConf היא להתקין [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). תוכלו גם להתקין [iTunes for Windows](https://www.apple.com/itunes/download/) כדי לקבל גרסה חדשה יותר של הכלי (שאינה זמינה כעצמאית).

    > 💁 אם אינכם יכולים להתחבר באמצעות `raspberrypi.local`, תוכלו להשתמש בכתובת ה-IP של ה-Pi שלכם. עיינו בתיעוד [כתובת ה-IP של Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) להוראות על מספר דרכים להשיג את כתובת ה-IP.

1. הכניסו את הסיסמה שהגדרתם באפשרויות המתקדמות של Raspberry Pi Imager.

#### הגדרת תוכנה על ה-Pi

לאחר שהתחברתם ל-Pi, עליכם לוודא שמערכת ההפעלה מעודכנת, ולהתקין ספריות וכלים שונים שמתקשרים עם חומרת Grove.

##### משימה - הגדרת תוכנה על ה-Pi

הגדירו את התוכנה המותקנת על ה-Pi והתקינו את ספריות Grove.

1. מתוך סשן ה-`ssh` שלכם, הריצו את הפקודה הבאה כדי לעדכן ואז להפעיל מחדש את ה-Pi:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    ה-Pi יעודכן ויופעל מחדש. סשן ה-`ssh` יסתיים כאשר ה-Pi יופעל מחדש, אז המתינו כ-30 שניות ואז התחברו מחדש.

1. מתוך סשן ה-`ssh` המחודש, הריצו את הפקודות הבאות כדי להתקין את כל הספריות הדרושות לחומרת Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    זה מתחיל בהתקנת Git, יחד עם Pip להתקנת חבילות Python.

    אחת התכונות החזקות של Python היא היכולת להתקין [חבילות Pip](https://pypi.org) - אלו חבילות קוד שנכתבו על ידי אנשים אחרים ופורסמו באינטרנט. ניתן להתקין חבילת Pip על המחשב שלכם עם פקודה אחת, ואז להשתמש בחבילה הזו בקוד שלכם.

    חבילות Python של Seeed Grove צריכות להיות מותקנות ממקור. הפקודות הללו ישכפלו את הריפו שמכיל את קוד המקור של החבילה הזו, ואז יתקינו אותו באופן מקומי.

    > 💁 כברירת מחדל, כאשר אתם מתקינים חבילה היא זמינה בכל מקום במחשב שלכם, וזה יכול להוביל לבעיות עם גרסאות חבילות - כמו אפליקציה אחת שתלויה בגרסה אחת של חבילה שנשברת כאשר אתם מתקינים גרסה חדשה עבור אפליקציה אחרת. כדי להתמודד עם הבעיה הזו, ניתן להשתמש ב-[סביבת עבודה וירטואלית של Python](https://docs.python.org/3/library/venv.html), שהיא למעשה עותק של Python בתיקייה ייעודית, וכאשר אתם מתקינים חבילות Pip הן מותקנות רק לתיקייה הזו. לא תשתמשו בסביבות עבודה וירטואליות כאשר אתם משתמשים ב-Pi שלכם. סקריפט ההתקנה של Grove מתקין את חבילות Python של Grove באופן גלובלי, כך שאם תרצו להשתמש בסביבת עבודה וירטואלית תצטרכו להגדיר אותה ואז להתקין מחדש את חבילות Grove בתוך הסביבה הזו. קל יותר פשוט להשתמש בחבילות גלובליות, במיוחד מכיוון שרבים ממפתחי ה-Pi יפרמטו כרטיס SD נקי עבור כל פרויקט.

    לבסוף, זה מפעיל את ממשק I<sup>2</sup>C.

1. הפעילו מחדש את ה-Pi על ידי הרצת הפקודה הבאה:

    ```sh
    sudo reboot
    ```

    סשן ה-`ssh` יסתיים כאשר ה-Pi יופעל מחדש. אין צורך להתחבר מחדש.

#### הגדרת VS Code לגישה מרחוק

לאחר שה-Pi מוגדר, תוכלו להתחבר אליו באמצעות Visual Studio Code (VS Code) מהמחשב שלכם - זהו עורך טקסט חינמי למפתחים שבו תשתמשו לכתיבת קוד המכשיר שלכם ב-Python.

##### משימה - הגדרת VS Code לגישה מרחוק

התקינו את התוכנה הנדרשת והתחברו מרחוק ל-Pi שלכם.

1. התקינו את VS Code על המחשב שלכם על ידי מעקב אחר [תיעוד VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)

1. עקבו אחר ההוראות בתיעוד [פיתוח מרחוק באמצעות SSH ב-VS Code](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) כדי להתקין את הרכיבים הדרושים

1. עקבו אחר אותן הוראות כדי להתחבר ל-VS Code ל-Pi

1. לאחר ההתחברות, עקבו אחר הוראות [ניהול הרחבות](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) כדי להתקין את [הרחבת Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) מרחוק על ה-Pi

## שלום עולם
נהוג, כשמתחילים לעבוד עם שפת תכנות או טכנולוגיה חדשה, ליצור אפליקציה בשם 'Hello World' - אפליקציה קטנה שמדפיסה טקסט כמו `"Hello World"` כדי לוודא שכל הכלים הוגדרו כראוי.

אפליקציית Hello World עבור ה-Pi תוודא שיש לך התקנה תקינה של Python ושל Visual Studio Code.

האפליקציה הזו תהיה בתיקייה בשם `nightlight`, והיא תשמש שוב עם קוד שונה בחלקים הבאים של המשימה כדי לבנות את אפליקציית ה-nightlight.

### משימה - hello world

צור את אפליקציית Hello World.

1. הפעל את VS Code, או ישירות על ה-Pi, או על המחשב שלך כשהוא מחובר ל-Pi באמצעות תוסף Remote SSH.

1. הפעל את הטרמינל של VS Code על ידי בחירה ב-*Terminal -> New Terminal*, או על ידי לחיצה על `` CTRL+` ``. הטרמינל ייפתח בתיקיית הבית של המשתמש `pi`.

1. הרץ את הפקודות הבאות כדי ליצור תיקייה עבור הקוד שלך, וליצור קובץ Python בשם `app.py` בתוך התיקייה:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. פתח את התיקייה הזו ב-VS Code על ידי בחירה ב-*File -> Open...* ובחירה בתיקיית *nightlight*, ואז לחץ על **OK**.

    ![תיבת הדו-שיח של פתיחת קובץ ב-VS Code שמציגה את תיקיית nightlight](../../../../../translated_images/he/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. פתח את הקובץ `app.py` מתוך סייר הקבצים של VS Code והוסף את הקוד הבא:

    ```python
    print('Hello World!')
    ```

    הפונקציה `print` מדפיסה לקונסול כל מה שמועבר אליה.

1. מתוך הטרמינל של VS Code, הרץ את הפקודה הבאה כדי להפעיל את אפליקציית ה-Python שלך:

    ```sh
    python app.py
    ```

    > 💁 ייתכן שתצטרך לקרוא במפורש ל-`python3` כדי להריץ את הקוד הזה אם מותקנת אצלך גרסה 2 של Python בנוסף לגרסה 3 (הגרסה העדכנית ביותר). אם מותקנת גרסה 2, קריאה ל-`python` תשתמש בגרסה 2 במקום בגרסה 3. כברירת מחדל, הגרסאות האחרונות של Raspberry Pi OS כוללות רק את Python 3.

    הפלט הבא יופיע בטרמינל:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 אפליקציית 'Hello World' שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור הסמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.