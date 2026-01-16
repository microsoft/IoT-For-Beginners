<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-27T22:50:43+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "he"
}
-->
# קריאת נתוני GPS - חומרה וירטואלית לאינטרנט של הדברים

בחלק זה של השיעור, תוסיפו חיישן GPS למכשיר האינטרנט של הדברים הווירטואלי שלכם, ותקראו ממנו ערכים.

## חומרה וירטואלית

מכשיר האינטרנט של הדברים הווירטואלי ישתמש בחיישן GPS מדומה שניתן לגשת אליו דרך UART באמצעות חיבור סריאלי.

חיישן GPS פיזי יכלול אנטנה לקליטת גלי רדיו מלווייני GPS, ויהפוך את אותות ה-GPS לנתוני GPS. הגרסה הווירטואלית מדמה זאת על ידי מתן אפשרות להגדיר קו רוחב וקו אורך, לשלוח משפטי NMEA גולמיים, או להעלות קובץ GPX עם מיקומים מרובים שניתן להחזירם באופן רציף.

> 🎓 משפטי NMEA יכוסו בהמשך השיעור

### הוספת החיישן ל-CounterFit

כדי להשתמש בחיישן GPS וירטואלי, עליכם להוסיף אותו לאפליקציית CounterFit.

#### משימה - הוספת החיישן ל-CounterFit

הוסיפו את חיישן ה-GPS לאפליקציית CounterFit.

1. צרו אפליקציית Python חדשה במחשב שלכם בתיקייה בשם `gps-sensor` עם קובץ יחיד בשם `app.py` וסביבת עבודה וירטואלית של Python, והוסיפו את חבילות ה-Pip של CounterFit.

    > ⚠️ תוכלו לעיין [בהוראות ליצירת והגדרת פרויקט Python של CounterFit בשיעור 1 אם יש צורך](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. התקינו חבילת Pip נוספת כדי להתקין שכבת CounterFit שיכולה לתקשר עם חיישנים מבוססי UART דרך חיבור סריאלי. ודאו שאתם מתקינים זאת מתוך טרמינל שבו סביבת העבודה הווירטואלית מופעלת.

    ```sh
    pip install counterfit-shims-serial
    ```

1. ודאו שאפליקציית ה-Web של CounterFit פועלת.

1. צרו חיישן GPS:

    1. בתיבה *Create sensor* בלשונית *Sensors*, פתחו את תיבת *Sensor type* ובחרו *UART GPS*.

    1. השאירו את *Port* מוגדר ל-*/dev/ttyAMA0*

    1. בחרו בכפתור **Add** כדי ליצור את חיישן ה-GPS על פורט `/dev/ttyAMA0`.

    ![הגדרות חיישן ה-GPS](../../../../../translated_images/he/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    חיישן ה-GPS ייווצר ויופיע ברשימת החיישנים.

    ![חיישן ה-GPS נוצר](../../../../../translated_images/he/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## תכנות חיישן ה-GPS

כעת ניתן לתכנת את מכשיר האינטרנט של הדברים הווירטואלי להשתמש בחיישן ה-GPS הווירטואלי.

### משימה - תכנות חיישן ה-GPS

תכנתו את אפליקציית חיישן ה-GPS.

1. ודאו שאפליקציית `gps-sensor` פתוחה ב-VS Code.

1. פתחו את קובץ `app.py`.

1. הוסיפו את הקוד הבא לראש הקובץ `app.py` כדי לחבר את האפליקציה ל-CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. הוסיפו את הקוד הבא מתחת לזה כדי לייבא כמה ספריות נדרשות, כולל הספרייה עבור הפורט הסריאלי של CounterFit:

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    קוד זה מייבא את המודול `serial` מחבילת ה-Pip `counterfit_shims_serial`. לאחר מכן הוא מתחבר לפורט הסריאלי `/dev/ttyAMA0` - זהו הכתובת של הפורט הסריאלי שבו חיישן ה-GPS הווירטואלי משתמש עבור פורט ה-UART שלו.

1. הוסיפו את הקוד הבא מתחת לזה כדי לקרוא מהפורט הסריאלי ולהדפיס את הערכים לקונסולה:

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    פונקציה בשם `print_gps_data` מוגדרת שמדפיסה את השורה שהועברה אליה לקונסולה.

    לאחר מכן הקוד מבצע לולאה אינסופית, קורא כמה שורות טקסט שהוא יכול מהפורט הסריאלי בכל לולאה. הוא קורא לפונקציה `print_gps_data` עבור כל שורה.

    לאחר שכל הנתונים נקראו, הלולאה ישנה למשך שנייה אחת, ואז תנסה שוב.

1. הריצו את הקוד הזה, ודאו שאתם משתמשים בטרמינל שונה מזה שבו אפליקציית CounterFit פועלת, כך שאפליקציית CounterFit תישאר פעילה.

1. מתוך אפליקציית CounterFit, שנו את הערך של חיישן ה-GPS. תוכלו לעשות זאת באחת מהדרכים הבאות:

    * הגדירו את **Source** ל-`Lat/Lon`, והגדירו קו רוחב, קו אורך ומספר לוויינים ששימשו לקבלת תיקון GPS. ערך זה יישלח רק פעם אחת, לכן סמנו את תיבת **Repeat** כדי שהנתונים יחזרו כל שנייה.

      ![חיישן ה-GPS עם lat lon נבחר](../../../../../translated_images/he/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * הגדירו את **Source** ל-`NMEA` והוסיפו כמה משפטי NMEA לתיבת הטקסט. כל הערכים הללו יישלחו, עם עיכוב של שנייה אחת לפני כל משפט GGA (תיקון מיקום) חדש שניתן לקרוא.

      ![חיישן ה-GPS עם משפטי NMEA מוגדרים](../../../../../translated_images/he/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      תוכלו להשתמש בכלי כמו [nmeagen.org](https://www.nmeagen.org) כדי ליצור את המשפטים הללו על ידי ציור על מפה. ערכים אלו יישלחו רק פעם אחת, לכן סמנו את תיבת **Repeat** כדי שהנתונים יחזרו שנייה אחת לאחר שכל הנתונים נשלחו.

    * הגדירו את **Source** לקובץ GPX, והעלו קובץ GPX עם מיקומי מסלול. תוכלו להוריד קבצי GPX ממספר אתרי מפות וטיולים פופולריים, כמו [AllTrails](https://www.alltrails.com/). קבצים אלו מכילים מיקומי GPS מרובים כנתיב, וחיישן ה-GPS יחזיר כל מיקום חדש במרווחים של שנייה אחת.

      ![חיישן ה-GPS עם קובץ GPX מוגדר](../../../../../translated_images/he/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      ערכים אלו יישלחו רק פעם אחת, לכן סמנו את תיבת **Repeat** כדי שהנתונים יחזרו שנייה אחת לאחר שכל הנתונים נשלחו.

    לאחר שהגדרתם את הגדרות ה-GPS, בחרו בכפתור **Set** כדי לשמור את הערכים הללו לחיישן.

1. תראו את הפלט הגולמי מחיישן ה-GPS, משהו כמו הבא:

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device).

😀 תוכנית חיישן ה-GPS שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.