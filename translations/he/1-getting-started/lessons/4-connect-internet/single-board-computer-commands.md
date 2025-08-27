<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-27T21:40:38+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "he"
}
-->
# שלוט בתאורת הלילה שלך דרך האינטרנט - חומרה וירטואלית של IoT ו-Raspberry Pi

בחלק זה של השיעור, תתחבר לפקודות שנשלחות ממתווך MQTT אל ה-Raspberry Pi או אל מכשיר IoT וירטואלי שלך.

## התחברות לפקודות

השלב הבא הוא להתחבר לפקודות שנשלחות ממתווך MQTT ולהגיב אליהן.

### משימה

התחבר לפקודות.

1. פתח את פרויקט תאורת הלילה ב-VS Code.

1. אם אתה משתמש במכשיר IoT וירטואלי, ודא שהטרמינל פועל בסביבה הווירטואלית. אם אתה משתמש ב-Raspberry Pi, לא תשתמש בסביבה וירטואלית.

1. הוסף את הקוד הבא לאחר ההגדרות של `client_telemetry_topic`:

    ```python
    server_command_topic = id + '/commands'
    ```

    ה-`server_command_topic` הוא נושא ה-MQTT שהמכשיר יתחבר אליו כדי לקבל פקודות להפעלת ה-LED.

1. הוסף את הקוד הבא ממש מעל הלולאה הראשית, לאחר השורה `mqtt_client.loop_start()`:

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    קוד זה מגדיר פונקציה בשם `handle_command`, שקוראת הודעה כמסמך JSON ומחפשת את הערך של המאפיין `led_on`. אם הערך מוגדר כ-`True`, ה-LED נדלק, אחרת הוא נכבה.

    לקוח ה-MQTT מתחבר לנושא שהשרת ישלח אליו הודעות ומגדיר את הפונקציה `handle_command` שתיקרא כאשר מתקבלת הודעה.

    > 💁 המטפל `on_message` נקרא עבור כל הנושאים שאליהם התחברת. אם בהמשך תכתוב קוד שמאזין למספר נושאים, תוכל לקבל את הנושא שאליו נשלחה ההודעה מתוך אובייקט `message` שמועבר לפונקציית המטפל.

1. הרץ את הקוד באותו אופן שבו הרצת את הקוד מהחלק הקודם של המשימה. אם אתה משתמש במכשיר IoT וירטואלי, ודא שהאפליקציה CounterFit פועלת וחיישן האור וה-LED נוצרו על הפינים הנכונים.

1. התאם את רמות האור שמזוהות על ידי המכשיר הפיזי או הווירטואלי שלך. הודעות שמתקבלות ופקודות שנשלחות ייכתבו לטרמינל. ה-LED גם יידלק וייכבה בהתאם לרמת האור.

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device) או בתיקייה [code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi).

😀 הצלחת לקודד את המכשיר שלך כך שיגיב לפקודות ממתווך MQTT.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.