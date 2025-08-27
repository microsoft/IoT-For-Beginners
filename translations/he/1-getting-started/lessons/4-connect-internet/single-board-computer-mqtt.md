<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-27T21:46:46+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "he"
}
-->
# שלוט בתאורת הלילה שלך דרך האינטרנט - חומרת IoT וירטואלית ו-Raspberry Pi

מכשיר ה-IoT צריך להיות מתוכנת לתקשר עם *test.mosquitto.org* באמצעות MQTT כדי לשלוח ערכי טלמטריה עם קריאת חיישן האור, ולקבל פקודות לשליטה בנורת ה-LED.

בחלק זה של השיעור, תחבר את ה-Raspberry Pi או את מכשיר ה-IoT הווירטואלי שלך ל-MQTT broker.

## התקנת חבילת לקוח MQTT

כדי לתקשר עם ה-MQTT broker, עליך להתקין חבילת ספריית MQTT באמצעות pip, בין אם על ה-Pi שלך או בסביבה הווירטואלית אם אתה משתמש במכשיר וירטואלי.

### משימה

התקן את חבילת ה-pip

1. פתח את פרויקט תאורת הלילה ב-VS Code.

1. אם אתה משתמש במכשיר IoT וירטואלי, ודא שהטרמינל פועל בסביבה הווירטואלית. אם אתה משתמש ב-Raspberry Pi, לא תשתמש בסביבה וירטואלית.

1. הרץ את הפקודה הבאה כדי להתקין את חבילת ה-pip של MQTT:

    ```sh
    pip3 install paho-mqtt
    ```

## כתיבת קוד למכשיר

המכשיר מוכן לקידוד.

### משימה

כתוב את קוד המכשיר.

1. הוסף את הייבוא הבא לראש קובץ `app.py`:

    ```python
    import paho.mqtt.client as mqtt
    ```

    ספריית `paho.mqtt.client` מאפשרת לאפליקציה שלך לתקשר באמצעות MQTT.

1. הוסף את הקוד הבא לאחר ההגדרות של חיישן האור וה-LED:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    החלף את `<ID>` ב-ID ייחודי שישמש כשם של לקוח המכשיר הזה, ובהמשך לנושאים שהמכשיר הזה יפרסם וירשם אליהם. ה-broker *test.mosquitto.org* הוא ציבורי ומשמש אנשים רבים, כולל תלמידים אחרים שעובדים על משימה זו. שימוש בשם לקוח MQTT ייחודי ושמות נושאים ייחודיים מבטיח שהקוד שלך לא יתנגש עם קוד של אחרים. תצטרך גם את ה-ID הזה כאשר תיצור את קוד השרת בהמשך המשימה.

    > 💁 תוכל להשתמש באתר כמו [GUIDGen](https://www.guidgen.com) כדי ליצור ID ייחודי.

    ה-`client_name` הוא שם ייחודי עבור לקוח ה-MQTT הזה ב-broker.

1. הוסף את הקוד הבא מתחת לקוד החדש הזה כדי ליצור אובייקט לקוח MQTT ולהתחבר ל-MQTT broker:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    קוד זה יוצר את אובייקט הלקוח, מתחבר ל-MQTT broker הציבורי, ומתחיל לולאת עיבוד שרצה ברקע ומאזינה להודעות בכל נושא שהמכשיר רשום אליו.

1. הרץ את הקוד באותו אופן שבו הרצת את הקוד מהחלק הקודם של המשימה. אם אתה משתמש במכשיר IoT וירטואלי, ודא שאפליקציית CounterFit פועלת ושחיישן האור וה-LED נוצרו על הפינים הנכונים.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device) או בתיקייה [code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi).

😀 הצלחת לחבר את המכשיר שלך ל-MQTT broker.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.