<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-27T21:04:16+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "he"
}
-->
# פרסום טמפרטורה - חומרה וירטואלית לאינטרנט של הדברים ו-Raspberry Pi

בחלק זה של השיעור, תפרסמו את ערכי הטמפרטורה שזוהו על ידי ה-Raspberry Pi או מכשיר IoT וירטואלי באמצעות MQTT, כך שניתן יהיה להשתמש בהם מאוחר יותר לחישוב GDD.

## פרסום הטמפרטורה

לאחר קריאת הטמפרטורה, ניתן לפרסם אותה באמצעות MQTT לקוד 'שרת' שיקרא את הערכים וישמור אותם לשימוש בחישוב GDD.

### משימה - פרסום הטמפרטורה

תכנתו את המכשיר לפרסם את נתוני הטמפרטורה.

1. פתחו את פרויקט האפליקציה `temperature-sensor` אם הוא עדיין לא פתוח.

1. חזרו על השלבים שביצעתם בשיעור 4 כדי להתחבר ל-MQTT ולשלוח טלמטריה. אתם תשתמשו באותו Mosquitto broker ציבורי.

    השלבים לכך הם:

    - הוסיפו את חבילת ה-pip של MQTT
    - הוסיפו את הקוד להתחברות ל-MQTT broker
    - הוסיפו את הקוד לפרסום טלמטריה

    > ⚠️ עיינו ב-[הוראות להתחברות ל-MQTT](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md) וב-[הוראות לשליחת טלמטריה](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md) מהשיעור הרביעי אם יש צורך.

1. ודאו ש-`client_name` משקף את שם הפרויקט הזה:

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. עבור הטלמטריה, במקום לשלוח ערך אור, שלחו את ערך הטמפרטורה שנקרא מהחיישן DHT בתכונה במסמך JSON שנקראת `temperature`:

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. אין צורך לקרוא את ערך הטמפרטורה לעיתים קרובות - הוא לא ישתנה הרבה בזמן קצר, לכן הגדירו את `time.sleep` ל-10 דקות:

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 הפונקציה `sleep` מקבלת את הזמן בשניות, ולכן כדי להקל על הקריאה הערך מועבר כתוצאה מחישוב. 60 שניות בדקה, כך ש-10 x (60 שניות בדקה) נותן עיכוב של 10 דקות.

1. הריצו את הקוד באותו אופן שבו הרצתם את הקוד מהחלק הקודם של המשימה. אם אתם משתמשים במכשיר IoT וירטואלי, ודאו שאפליקציית CounterFit פועלת ושחיישני הלחות והטמפרטורה נוצרו על הפינים הנכונים.

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 תוכלו למצוא את הקוד הזה בתיקיית [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) או בתיקיית [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi).

😀 הצלחתם לפרסם את הטמפרטורה כטלמטריה מהמכשיר שלכם.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.