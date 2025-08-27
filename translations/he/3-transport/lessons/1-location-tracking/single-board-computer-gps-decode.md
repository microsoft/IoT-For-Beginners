<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cbb8c285bc64c5192fae3368fb5077d2",
  "translation_date": "2025-08-27T22:54:55+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/single-board-computer-gps-decode.md",
  "language_code": "he"
}
-->
# פענוח נתוני GPS - חומרה וירטואלית לאינטרנט של הדברים ו-Raspberry Pi

בחלק זה של השיעור, תפענחו את הודעות NMEA שנקראות מחיישן ה-GPS על ידי ה-Raspberry Pi או מכשיר IoT וירטואלי, ותפיקו את קווי הרוחב והאורך.

## פענוח נתוני GPS

לאחר קריאת נתוני NMEA הגולמיים מהפורט הסדרתי, ניתן לפענח אותם באמצעות ספריית NMEA בקוד פתוח.

### משימה - פענוח נתוני GPS

תכנתו את המכשיר לפענח את נתוני ה-GPS.

1. פתחו את פרויקט האפליקציה `gps-sensor` אם הוא עדיין לא פתוח.

1. התקינו את חבילת Pip בשם `pynmea2`. חבילה זו מכילה קוד לפענוח הודעות NMEA.

    ```sh
    pip3 install pynmea2
    ```

1. הוסיפו את הקוד הבא לייבואים בקובץ `app.py` כדי לייבא את המודול `pynmea2`:

    ```python
    import pynmea2
    ```

1. החליפו את תוכן הפונקציה `print_gps_data` בקוד הבא:

    ```python
    msg = pynmea2.parse(line)
    if msg.sentence_type == 'GGA':
        lat = pynmea2.dm_to_sd(msg.lat)
        lon = pynmea2.dm_to_sd(msg.lon)

        if msg.lat_dir == 'S':
            lat = lat * -1

        if msg.lon_dir == 'W':
            lon = lon * -1

        print(f'{lat},{lon} - from {msg.num_sats} satellites')
    ```

    קוד זה ישתמש בספריית `pynmea2` כדי לנתח את השורה שנקראה מפורט ה-UART הסדרתי.

    אם סוג המשפט של ההודעה הוא `GGA`, אז מדובר בהודעת תיקון מיקום, והיא מעובדת. ערכי קווי הרוחב והאורך נקראים מההודעה ומומרים למעלות עשרוניות מפורמט NMEA `(d)ddmm.mmmm`. פונקציית `dm_to_sd` מבצעת את ההמרה הזו.

    לאחר מכן נבדקת כיווניות קו הרוחב, ואם קו הרוחב הוא דרומי, הערך מומר למספר שלילי. אותו הדבר לגבי קו האורך, אם הוא מערבי, הוא מומר למספר שלילי.

    לבסוף, הקואורדינטות מודפסות לקונסולה, יחד עם מספר הלוויינים ששימשו למציאת המיקום.

1. הריצו את הקוד. אם אתם משתמשים במכשיר IoT וירטואלי, ודאו שאפליקציית CounterFit פועלת ונתוני ה-GPS נשלחים.

    ```output
    pi@raspberrypi:~/gps-sensor $ python3 app.py 
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-gps-decode/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/virtual-device), או בתיקיית [code-gps-decode/pi](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/pi).

😀 תוכנית חיישן ה-GPS שלכם עם פענוח נתונים הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.