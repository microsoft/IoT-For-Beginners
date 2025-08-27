<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-27T21:33:17+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "he"
}
-->
# חבר את מכשיר ה-IoT שלך לענן - חומרת IoT וירטואלית ו-Raspberry Pi

בחלק זה של השיעור, תחבר את מכשיר ה-IoT הווירטואלי שלך או את ה-Raspberry Pi שלך ל-IoT Hub, כדי לשלוח טלמטריה ולקבל פקודות.

## חיבור המכשיר ל-IoT Hub

השלב הבא הוא לחבר את המכשיר שלך ל-IoT Hub.

### משימה - התחברות ל-IoT Hub

1. פתח את התיקייה `soil-moisture-sensor` ב-VS Code. ודא שהסביבה הווירטואלית פועלת בטרמינל אם אתה משתמש במכשיר IoT וירטואלי.

1. התקן כמה חבילות Pip נוספות:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` היא ספרייה לתקשורת עם ה-IoT Hub שלך.

1. הוסף את הייבוא הבא לראש קובץ `app.py`, מתחת לייבוא הקיים:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    קוד זה מייבא את ה-SDK לתקשורת עם ה-IoT Hub שלך.

1. הסר את השורה `import paho.mqtt.client as mqtt`, מכיוון שהספרייה הזו כבר אינה נחוצה. הסר את כל קוד ה-MQTT כולל שמות הנושאים, כל קוד שמשתמש ב-`mqtt_client` וב-`handle_command`. שמור את הלולאה `while True:`, פשוט מחק את השורה `mqtt_client.publish` מתוך הלולאה הזו.

1. הוסף את הקוד הבא מתחת להצהרות הייבוא:

    ```python
    connection_string = "<connection string>"
    ```

    החלף את `<connection string>` במחרוזת החיבור שהשגת עבור המכשיר מוקדם יותר בשיעור זה.

    > 💁 זה אינו נוהג מומלץ. אין לשמור מחרוזות חיבור בקוד המקור, מכיוון שהן יכולות להיכנס למערכת בקרת גרסאות ולהיות נגישות לכל אחד. אנו עושים זאת כאן לצורך פשטות. באופן אידיאלי, כדאי להשתמש במשתנה סביבה ובכלי כמו [`python-dotenv`](https://pypi.org/project/python-dotenv/). תלמד על כך יותר בשיעור הבא.

1. מתחת לקוד זה, הוסף את הקוד הבא ליצירת אובייקט לקוח מכשיר שיכול לתקשר עם ה-IoT Hub, וחבר אותו:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. הרץ את הקוד הזה. תראה שהמכשיר שלך מתחבר.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## שליחת טלמטריה

עכשיו כשהמכשיר שלך מחובר, תוכל לשלוח טלמטריה ל-IoT Hub במקום ל-MQTT broker.

### משימה - שליחת טלמטריה

1. הוסף את הקוד הבא בתוך הלולאה `while True`, ממש לפני השינה:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    קוד זה יוצר `Message` של IoT Hub שמכיל את קריאת לחות הקרקע כמחרוזת JSON, ואז שולח זאת ל-IoT Hub כהודעה ממכשיר לענן.

## טיפול בפקודות

המכשיר שלך צריך לטפל בפקודה מהקוד בשרת כדי לשלוט בממסר. זה נשלח כבקשת שיטה ישירה.

## משימה - טיפול בבקשת שיטה ישירה

1. הוסף את הקוד הבא לפני הלולאה `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    קוד זה מגדיר שיטה, `handle_method_request`, שתיקרא כאשר שיטה ישירה תופעל על ידי ה-IoT Hub. לכל שיטה יש שם, והקוד הזה מצפה לשיטה בשם `relay_on` כדי להפעיל את הממסר, ו-`relay_off` כדי לכבות אותו.

    > 💁 ניתן גם ליישם זאת בשיטה ישירה אחת, על ידי העברת המצב הרצוי של הממסר במטען שניתן להעביר עם בקשת השיטה וזמין מאובייקט `request`.

1. שיטות ישירות דורשות תגובה כדי להודיע לקוד הקורא שהן טופלו. הוסף את הקוד הבא בסוף פונקציית `handle_method_request` כדי ליצור תגובה לבקשה:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    קוד זה שולח תגובה לבקשת השיטה הישירה עם קוד סטטוס HTTP של 200, ושולח זאת חזרה ל-IoT Hub.

1. הוסף את הקוד הבא מתחת להגדרת הפונקציה הזו:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    קוד זה אומר ללקוח ה-IoT Hub לקרוא לפונקציה `handle_method_request` כאשר שיטה ישירה מופעלת.

> 💁 תוכל למצוא את הקוד הזה בתיקיות [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) או [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 תוכנית חיישן לחות הקרקע שלך מחוברת ל-IoT Hub שלך!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.