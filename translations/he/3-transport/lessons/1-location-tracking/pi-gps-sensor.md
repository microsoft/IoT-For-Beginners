<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3b2448c7ab4e9673e77e35a50c5e350d",
  "translation_date": "2025-08-27T22:55:46+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/pi-gps-sensor.md",
  "language_code": "he"
}
-->
# קריאת נתוני GPS - Raspberry Pi

בחלק זה של השיעור, תוסיף חיישן GPS ל-Raspberry Pi שלך ותקריא ממנו ערכים.

## חומרה

ה-Raspberry Pi זקוק לחיישן GPS.

החיישן שבו תשתמש הוא [חיישן Grove GPS Air530](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html). חיישן זה יכול להתחבר למערכות GPS מרובות כדי לספק מיקום מהיר ומדויק. החיישן מורכב משני חלקים - האלקטרוניקה המרכזית של החיישן ואנטנה חיצונית המחוברת באמצעות כבל דק לקליטת גלי רדיו מהלוויינים.

זהו חיישן UART, ולכן הוא שולח נתוני GPS דרך UART.

## חיבור חיישן ה-GPS

ניתן לחבר את חיישן ה-GPS ל-Raspberry Pi.

### משימה - חיבור חיישן ה-GPS

חבר את חיישן ה-GPS.

![חיישן Grove GPS](../../../../../translated_images/he/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. הכנס קצה אחד של כבל Grove לשקע בחיישן ה-GPS. הכבל ייכנס רק בכיוון אחד.

1. כאשר ה-Raspberry Pi כבוי, חבר את הקצה השני של כבל Grove לשקע UART המסומן **UART** על כובע הבסיס של Grove המחובר ל-Pi. שקע זה נמצא בשורה האמצעית, בצד הקרוב לחריץ כרטיס ה-SD, בצד השני מהשקעים של ה-USB והאת'רנט.

    ![חיישן Grove GPS מחובר לשקע UART](../../../../../translated_images/he/pi-gps-sensor.1f99ee2b2f6528915047ec78967bd362e0e4ee0ed594368a3837b9cf9cdaca64.png)

1. מקם את חיישן ה-GPS כך שהאנטנה המחוברת תהיה עם ראות לשמיים - רצוי ליד חלון פתוח או בחוץ. קל יותר לקבל אות ברור כאשר אין מכשולים בדרך של האנטנה.

## תכנות חיישן ה-GPS

כעת ניתן לתכנת את ה-Raspberry Pi לשימוש בחיישן ה-GPS המחובר.

### משימה - תכנות חיישן ה-GPS

תכנת את המכשיר.

1. הפעל את ה-Pi והמתן עד שיסיים את תהליך האתחול.

1. לחיישן ה-GPS יש שני נורות LED - נורה כחולה שמבזיקה כאשר נתונים מועברים, ונורה ירוקה שמבזיקה כל שנייה כאשר מתקבלים נתונים מלוויינים. ודא שהנורה הכחולה מבזיקה כאשר אתה מפעיל את ה-Pi. לאחר מספר דקות הנורה הירוקה תתחיל להבהב - אם לא, ייתכן שתצטרך למקם מחדש את האנטנה.

1. הפעל את VS Code, או ישירות על ה-Pi, או באמצעות הרחבת Remote SSH.

    > ⚠️ תוכל לעיין [בהוראות להגדרת והפעלת VS Code בשיעור 1 אם יש צורך](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. בגרסאות החדשות יותר של Raspberry Pi שתומכות ב-Bluetooth, ישנו קונפליקט בין יציאת הסריאל המשמשת ל-Bluetooth לבין זו המשמשת ליציאת UART של Grove. כדי לפתור זאת, בצע את הפעולות הבאות:

    1. מתוך הטרמינל של VS Code, ערוך את הקובץ `/boot/config.txt` באמצעות `nano`, עורך טקסט מובנה בטרמינל, עם הפקודה הבאה:

        ```sh
        sudo nano /boot/config.txt
        ```

        > לא ניתן לערוך קובץ זה באמצעות VS Code מכיוון שיש צורך בהרשאות `sudo`, הרשאות מוגבהות. VS Code אינו פועל עם הרשאות אלו.

    1. השתמש במקשי החצים כדי לנווט לסוף הקובץ, ואז העתק את הקוד הבא והדבק אותו בסוף הקובץ:

        ```ini
        dtoverlay=pi3-miniuart-bt
        dtoverlay=pi3-disable-bt
        enable_uart=1
        ```

        ניתן להדביק באמצעות קיצורי המקלדת הרגילים של המכשיר שלך (`Ctrl+v` ב-Windows, Linux או Raspberry Pi OS, `Cmd+v` ב-macOS).

    1. שמור את הקובץ וצא מ-nano על ידי לחיצה על `Ctrl+x`. לחץ `y` כאשר תתבקש לשמור את השינויים, ואז לחץ `enter` כדי לאשר שברצונך להחליף את `/boot/config.txt`.

        > אם עשית טעות, תוכל לצאת מבלי לשמור, ואז לחזור על השלבים הללו.

    1. ערוך את הקובץ `/boot/cmdline.txt` ב-nano עם הפקודה הבאה:

        ```sh
        sudo nano /boot/cmdline.txt
        ```

    1. קובץ זה מכיל מספר זוגות מפתח/ערך המופרדים ברווחים. הסר כל זוגות מפתח/ערך עבור המפתח `console`. הם כנראה ייראו כך:

        ```output
        console=serial0,115200 console=tty1 
        ```

        תוכל לנווט לערכים אלו באמצעות מקשי החצים, ואז למחוק באמצעות מקשי `del` או `backspace` הרגילים.

        לדוגמה, אם הקובץ המקורי שלך נראה כך:

        ```output
        console=serial0,115200 console=tty1 root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

        הגרסה החדשה תיראה כך:

        ```output
        root=PARTUUID=058e2867-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait
        ```

    1. עקוב אחר השלבים לעיל כדי לשמור את הקובץ ולצאת מ-nano.

    1. אתחל מחדש את ה-Pi שלך, ואז התחבר מחדש ב-VS Code לאחר שה-Pi אתחל.

1. מתוך הטרמינל, צור תיקייה חדשה בספריית הבית של המשתמש `pi` בשם `gps-sensor`. צור קובץ בתיקייה זו בשם `app.py`.

1. פתח את התיקייה הזו ב-VS Code.

1. מודול ה-GPS שולח נתוני UART דרך יציאת סריאל. התקן את חבילת Pip בשם `pyserial` כדי לתקשר עם יציאת הסריאל מתוך קוד ה-Python שלך:

    ```sh
    pip3 install pyserial
    ```

1. הוסף את הקוד הבא לקובץ `app.py` שלך:

    ```python
    import time
    import serial
    
    serial = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
    serial.reset_input_buffer()
    serial.flush()
    
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    קוד זה מייבא את המודול `serial` מתוך חבילת Pip `pyserial`. לאחר מכן הוא מתחבר ליציאת הסריאל `/dev/ttyAMA0` - זו הכתובת של יציאת הסריאל שבה משתמש כובע הבסיס של Grove עבור יציאת UART שלו. לאחר מכן הוא מנקה כל נתונים קיימים מחיבור הסריאל הזה.

    לאחר מכן מוגדרת פונקציה בשם `print_gps_data` שמדפיסה את השורה שהועברה אליה לקונסול.

    לאחר מכן הקוד מבצע לולאה אינסופית, קורא כמה שורות טקסט שהוא יכול מיציאת הסריאל בכל לולאה. הוא קורא לפונקציה `print_gps_data` עבור כל שורה.

    לאחר שכל הנתונים נקראו, הלולאה ישנה למשך שנייה אחת, ואז תנסה שוב.

1. הרץ את הקוד הזה. תראה את הפלט הגולמי מחיישן ה-GPS, משהו כמו:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

    > אם אתה מקבל אחת מהשגיאות הבאות כאשר אתה עוצר ומפעיל מחדש את הקוד שלך, הוסף בלוק `try - except` ללולאה שלך.

      ```output
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0x93 in position 0: invalid start byte
      UnicodeDecodeError: 'utf-8' codec can't decode byte 0xf1 in position 0: invalid continuation byte
      ```

    ```python
    while True:
        try:
            line = serial.readline().decode('utf-8')
              
            while len(line) > 0:
                print_gps_data()
                line = serial.readline().decode('utf-8')
      
        # There's a random chance the first byte being read is part way through a character.
        # Read another full line and continue.

        except UnicodeDecodeError:
            line = serial.readline().decode('utf-8')

    time.sleep(1)
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code-gps/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps/pi).

😀 תוכנית חיישן ה-GPS שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.