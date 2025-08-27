<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-27T21:38:54+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "he"
}
-->
# השתמשו בתעודת X.509 בקוד המכשיר שלכם - חומרה וירטואלית ל-IoT ו-Raspberry Pi

בחלק זה של השיעור, תחברו את מכשיר ה-IoT הווירטואלי שלכם או את ה-Raspberry Pi שלכם ל-IoT Hub באמצעות תעודת X.509.

## חיבור המכשיר שלכם ל-IoT Hub

השלב הבא הוא לחבר את המכשיר שלכם ל-IoT Hub באמצעות תעודות X.509.

### משימה - חיבור ל-IoT Hub

1. העתיקו את קבצי המפתח והתעודה לתיקייה שמכילה את קוד המכשיר שלכם. אם אתם משתמשים ב-Raspberry Pi דרך VS Code Remote SSH ויצרתם את המפתחות במחשב האישי או ה-Mac שלכם, תוכלו לגרור ולשחרר את הקבצים לתוך ה-explorer ב-VS Code כדי להעתיק אותם.

1. פתחו את הקובץ `app.py`

1. כדי להתחבר באמצעות תעודת X.509, תצטרכו את שם המארח של ה-IoT Hub ואת תעודת ה-X.509. התחילו ביצירת משתנה שמכיל את שם המארח על ידי הוספת הקוד הבא לפני יצירת ה-device client:

    ```python
    host_name = "<host_name>"
    ```

    החליפו את `<host_name>` בשם המארח של ה-IoT Hub שלכם. תוכלו למצוא אותו בחלק `HostName` בתוך ה-`connection_string`. זה יהיה שם ה-IoT Hub שלכם, שמסתיים ב-`.azure-devices.net`.

1. מתחת לזה, הכריזו על משתנה עם ה-device ID:

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. תצטרכו מופע של מחלקת `X509` שמכיל את קבצי ה-X.509. הוסיפו את `X509` לרשימת המחלקות המיובאות ממודול `azure.iot.device`:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. צרו מופע של מחלקת `X509` באמצעות קבצי התעודה והמפתח שלכם על ידי הוספת הקוד הזה מתחת להצהרת `host_name`:

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    זה ייצור את מחלקת `X509` באמצעות הקבצים `soil-moisture-sensor-x509-cert.pem` ו-`soil-moisture-sensor-x509-key.pem` שנוצרו קודם לכן.

1. החליפו את שורת הקוד שיוצרת את ה-`device_client` מתוך connection string, עם השורה הבאה:

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    זה יתחבר באמצעות תעודת X.509 במקום connection string.

1. מחקו את השורה עם משתנה ה-`connection_string`.

1. הריצו את הקוד שלכם. עקבו אחרי ההודעות שנשלחות ל-IoT Hub ושלחו בקשות direct method כמו קודם. תראו שהמכשיר מתחבר ושולח קריאות לחות קרקע, וגם מקבל בקשות direct method.

> 💁 תוכלו למצוא את הקוד הזה בתיקיות [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) או [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device).

😀 תוכנית חיישן לחות הקרקע שלכם מחוברת ל-IoT Hub באמצעות תעודת X.509!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור הסמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.