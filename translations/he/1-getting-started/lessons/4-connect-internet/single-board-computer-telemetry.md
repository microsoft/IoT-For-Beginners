<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-27T21:41:06+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "he"
}
-->
# שלוט בתאורת הלילה שלך דרך האינטרנט - חומרה וירטואלית של IoT ו-Raspberry Pi

בחלק זה של השיעור, תשלח נתוני טלמטריה עם רמות אור מ-Raspberry Pi או ממכשיר IoT וירטואלי ל-MQTT broker.

## פרסום טלמטריה

השלב הבא הוא ליצור מסמך JSON עם נתוני טלמטריה ולשלוח אותו ל-MQTT broker.

### משימה

פרסם טלמטריה ל-MQTT broker.

1. פתח את פרויקט תאורת הלילה ב-VS Code.

1. אם אתה משתמש במכשיר IoT וירטואלי, ודא שהטרמינל פועל בסביבה הווירטואלית. אם אתה משתמש ב-Raspberry Pi, לא תשתמש בסביבה וירטואלית.

1. הוסף את הייבוא הבא לראש קובץ `app.py`:

    ```python
    import json
    ```

    ספריית `json` משמשת לקידוד הטלמטריה כמסמך JSON.

1. הוסף את הקוד הבא לאחר ההצהרה של `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` הוא נושא ה-MQTT שהמכשיר יפרסם אליו את רמות האור.

1. החלף את התוכן של הלולאה `while True:` בסוף הקובץ בקוד הבא:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    קוד זה אורז את רמת האור למסמך JSON ומפרסם אותו ל-MQTT broker. לאחר מכן הוא מבצע השהיה כדי להפחית את תדירות שליחת ההודעות.

1. הרץ את הקוד באותו אופן שבו הרצת את הקוד מהחלק הקודם של המשימה. אם אתה משתמש במכשיר IoT וירטואלי, ודא שהאפליקציה CounterFit פועלת וחיישן האור וה-LED נוצרו על הפינים הנכונים.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) או בתיקיית [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 הצלחת לשלוח טלמטריה מהמכשיר שלך.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.