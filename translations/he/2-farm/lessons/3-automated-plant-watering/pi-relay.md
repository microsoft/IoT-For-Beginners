<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-27T21:14:06+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "he"
}
-->
# שליטה בריליי - Raspberry Pi

בחלק זה של השיעור, תוסיף ריליי ל-Raspberry Pi שלך בנוסף לחיישן לחות הקרקע, ותשלוט בו בהתאם לרמת הלחות בקרקע.

## חומרה

ה-Raspberry Pi זקוק לריליי.

הריליי שבו תשתמש הוא [Grove relay](https://www.seeedstudio.com/Grove-Relay.html), ריליי במצב פתוח (כלומר, מעגל היציאה פתוח או מנותק כאשר לא נשלח אות לריליי) שיכול להתמודד עם מעגלי יציאה עד 250V ו-10A.

זהו מפעיל דיגיטלי, ולכן הוא מתחבר לפין דיגיטלי על ה-Grove Base Hat.

### חיבור הריליי

ניתן לחבר את ריליי Grove ל-Raspberry Pi.

#### משימה

חבר את הריליי.

![ריליי Grove](../../../../../translated_images/he/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. הכנס קצה אחד של כבל Grove לשקע על הריליי. הוא ייכנס רק בכיוון אחד.

1. כאשר ה-Raspberry Pi כבוי, חבר את הקצה השני של כבל Grove לשקע הדיגיטלי המסומן **D5** על ה-Grove Base Hat המחובר ל-Pi. שקע זה הוא השני משמאל, בשורה של השקעים ליד פיני ה-GPIO. השאר את חיישן לחות הקרקע מחובר לשקע **A0**.

![הריליי Grove מחובר לשקע D5, וחיישן לחות הקרקע מחובר לשקע A0](../../../../../translated_images/he/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. הכנס את חיישן לחות הקרקע לאדמה, אם הוא לא כבר מחובר מהשיעור הקודם.

## תכנות הריליי

כעת ניתן לתכנת את ה-Raspberry Pi להשתמש בריליי המחובר.

### משימה

תכנת את המכשיר.

1. הפעל את ה-Pi והמתן עד שיסיים את תהליך האתחול.

1. פתח את הפרויקט `soil-moisture-sensor` מהשיעור הקודם ב-VS Code אם הוא לא כבר פתוח. תוסיף לפרויקט הזה.

1. הוסף את הקוד הבא לקובץ `app.py` מתחת לייבוא הקיים:

    ```python
    from grove.grove_relay import GroveRelay
    ```

    שורה זו מייבאת את `GroveRelay` מספריות ה-Python של Grove כדי לתקשר עם הריליי Grove.

1. הוסף את הקוד הבא מתחת להצהרה של מחלקת `ADC` כדי ליצור מופע של `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    פעולה זו יוצרת ריליי באמצעות פין **D5**, הפין הדיגיטלי שאליו חיברת את הריליי.

1. כדי לבדוק שהריליי עובד, הוסף את הקוד הבא ללולאת `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    הקוד מפעיל את הריליי, ממתין 0.5 שניות, ואז מכבה את הריליי.

1. הרץ את אפליקציית ה-Python. הריליי יידלק וייכבה כל 10 שניות, עם עיכוב של חצי שנייה בין הדלקה לכיבוי. תשמע את הריליי לוחץ כשהוא נדלק ואז כשהוא נכבה. נורית LED על לוח Grove תידלק כשהריליי פועל ותכבה כשהריליי כבוי.

    ![הריליי נדלק ונכבה](../../../../../images/relay-turn-on-off.gif)

## שליטה בריליי לפי לחות הקרקע

כעת כשהריליי עובד, ניתן לשלוט בו בתגובה לקריאות לחות הקרקע.

### משימה

שלוט בריליי.

1. מחק את שלוש שורות הקוד שהוספת כדי לבדוק את הריליי. החלף אותן בקוד הבא:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    קוד זה בודק את רמת הלחות בקרקע מחיישן לחות הקרקע. אם היא מעל 450, הוא מדליק את הריליי, ומכבה אותו כשהיא יורדת מתחת ל-450.

    > 💁 זכור שחיישן לחות הקרקע הקיבולי קורא שככל שרמת הלחות נמוכה יותר, יש יותר לחות בקרקע, ולהפך.

1. הרץ את אפליקציית ה-Python. תראה את הריליי נדלק או נכבה בהתאם לרמת הלחות בקרקע. נסה באדמה יבשה, ואז הוסף מים.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi).

😀 התוכנית שלך לשליטה בריליי באמצעות חיישן לחות הקרקע הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.