<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-27T21:14:51+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "he"
}
-->
# שליטה בממסר - חומרה וירטואלית לאינטרנט של הדברים

בחלק זה של השיעור, תוסיפו ממסר למכשיר האינטרנט של הדברים הווירטואלי שלכם בנוסף לחיישן לחות הקרקע, ותשלבו אותו בהתאם לרמת לחות הקרקע.

## חומרה וירטואלית

מכשיר האינטרנט של הדברים הווירטואלי ישתמש בממסר Grove מדומה. זה שומר על המעבדה זהה לשימוש ב-Raspberry Pi עם ממסר Grove פיזי.

במכשיר אינטרנט של הדברים פיזי, הממסר יהיה ממסר פתוח-בדרך כלל (כלומר מעגל היציאה פתוח או מנותק כאשר לא נשלח אות לממסר). ממסר כזה יכול להתמודד עם מעגלי יציאה עד 250V ו-10A.

### הוספת ממסר ל-CounterFit

כדי להשתמש בממסר וירטואלי, עליכם להוסיף אותו לאפליקציית CounterFit.

#### משימה

הוסיפו את הממסר לאפליקציית CounterFit.

1. פתחו את פרויקט `soil-moisture-sensor` מהשיעור הקודם ב-VS Code אם הוא לא פתוח כבר. תוסיפו לפרויקט הזה.

1. ודאו שאפליקציית הווב של CounterFit פועלת.

1. צרו ממסר:

    1. בתיבה *Create actuator* בלשונית *Actuators*, פתחו את תיבת *Actuator type* ובחרו *Relay*.

    1. הגדירו את *Pin* ל-*5*.

    1. לחצו על כפתור **Add** כדי ליצור את הממסר על Pin 5.

    ![הגדרות הממסר](../../../../../translated_images/he/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    הממסר ייווצר ויופיע ברשימת המפעילים.

    ![הממסר שנוצר](../../../../../translated_images/he/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## תכנות הממסר

אפליקציית חיישן לחות הקרקע יכולה עכשיו להיות מתוכנתת לשימוש בממסר הווירטואלי.

### משימה

תכנתו את המכשיר הווירטואלי.

1. פתחו את פרויקט `soil-moisture-sensor` מהשיעור הקודם ב-VS Code אם הוא לא פתוח כבר. תוסיפו לפרויקט הזה.

1. הוסיפו את הקוד הבא לקובץ `app.py` מתחת לייבוא הקיים:

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    שורה זו מייבאת את `GroveRelay` מספריות ה-Grove Python shim כדי לתקשר עם ממסר Grove הווירטואלי.

1. הוסיפו את הקוד הבא מתחת להצהרת מחלקת `ADC` כדי ליצור מופע של `GroveRelay`:

    ```python
    relay = GroveRelay(5)
    ```

    זה יוצר ממסר באמצעות Pin **5**, הפין שאליו חיברתם את הממסר.

1. כדי לבדוק שהממסר עובד, הוסיפו את הקוד הבא ללולאת `while True:`:

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    הקוד מדליק את הממסר, ממתין 0.5 שניות, ואז מכבה אותו.

1. הריצו את אפליקציית ה-Python. הממסר ידלק ויכבה כל 10 שניות, עם עיכוב של חצי שנייה בין הדלקה לכיבוי. תוכלו לראות את הממסר הווירטואלי באפליקציית CounterFit נסגר ונפתח כשהממסר נדלק ונכבה.

    ![הממסר הווירטואלי נדלק ונכבה](../../../../../images/virtual-relay-turn-on-off.gif)

## שליטה בממסר לפי לחות הקרקע

עכשיו כשהממסר עובד, ניתן לשלוט בו בתגובה לקריאות לחות הקרקע.

### משימה

שליטה בממסר.

1. מחקו את שלוש שורות הקוד שהוספתם כדי לבדוק את הממסר. החליפו אותן בקוד הבא במקום:

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    קוד זה בודק את רמת לחות הקרקע מחיישן לחות הקרקע. אם היא מעל 450, הוא מדליק את הממסר, ומכבה אותו אם היא יורדת מתחת ל-450.

    > 💁 זכרו שחיישן לחות הקרקע הקיבולי קורא שככל שרמת לחות הקרקע נמוכה יותר, יש יותר לחות בקרקע ולהפך.

1. הריצו את אפליקציית ה-Python. תוכלו לראות את הממסר נדלק או נכבה בהתאם לרמות לחות הקרקע. שנו את *Value* או את הגדרות *Random* של חיישן לחות הקרקע כדי לראות את הערך משתנה.

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device).

😀 התוכנית שלכם לשליטה בממסר באמצעות חיישן לחות הקרקע הווירטואלי הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.