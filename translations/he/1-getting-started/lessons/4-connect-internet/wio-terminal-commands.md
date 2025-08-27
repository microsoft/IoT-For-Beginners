<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-27T21:48:40+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "he"
}
-->
# שלוט באור הלילה שלך דרך האינטרנט - Wio Terminal

בחלק זה של השיעור, תתחבר לפקודות שנשלחות ממתווך MQTT אל ה-Wio Terminal שלך.

## התחברות לפקודות

השלב הבא הוא להתחבר לפקודות שנשלחות ממתווך MQTT, ולהגיב אליהן.

### משימה

התחבר לפקודות.

1. פתח את פרויקט אור הלילה ב-VS Code.

1. הוסף את הקוד הבא לתחתית קובץ `config.h` כדי להגדיר את שם הנושא עבור הפקודות:

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC` הוא הנושא שהמכשיר יתחבר אליו כדי לקבל פקודות להפעלת ה-LED.

1. הוסף את השורה הבאה לסוף הפונקציה `reconnectMQTTClient` כדי להתחבר לנושא הפקודות כאשר לקוח ה-MQTT מתחבר מחדש:

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. הוסף את הקוד הבא מתחת לפונקציה `reconnectMQTTClient`.

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    פונקציה זו תהיה פונקציית callback שהלקוח MQTT יקרא לה כאשר הוא מקבל הודעה מהשרת.

    ההודעה מתקבלת כמערך של מספרים שלמים בגודל 8 ביט, ולכן יש להמיר אותה למערך תווים כדי להתייחס אליה כטקסט.

    ההודעה מכילה מסמך JSON, והיא מפוענחת באמצעות ספריית ArduinoJson. תכונת `led_on` של מסמך ה-JSON נקראת, ובהתאם לערך שלה ה-LED נדלק או נכבה.

1. הוסף את הקוד הבא לפונקציה `createMQTTClient`:

    ```cpp
    client.setCallback(clientCallback);
    ```

    קוד זה מגדיר את `clientCallback` כ-callback שיקרא כאשר מתקבלת הודעה ממתווך ה-MQTT.

    > 💁 פונקציית `clientCallback` נקראת עבור כל הנושאים שהתחברת אליהם. אם תכתוב בהמשך קוד שמאזין למספר נושאים, תוכל לקבל את הנושא שההודעה נשלחה אליו מהפרמטר `topic` שמועבר לפונקציית ה-callback.

1. העלה את הקוד ל-Wio Terminal שלך, והשתמש ב-Serial Monitor כדי לראות את רמות האור שנשלחות למתווך ה-MQTT.

1. התאם את רמות האור שמזוהות על ידי המכשיר הפיזי או הווירטואלי שלך. תראה הודעות שמתקבלות ופקודות שנשלחות בטרמינל. כמו כן, תראה את ה-LED נדלק ונכבה בהתאם לרמת האור.

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal).

😀 הצלחת לקודד את המכשיר שלך כך שיגיב לפקודות ממתווך MQTT.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.