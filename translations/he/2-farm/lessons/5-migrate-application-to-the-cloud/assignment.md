<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c24b6e4d90501c9199f2ceb6a648a337",
  "translation_date": "2025-08-27T21:20:08+00:00",
  "source_file": "2-farm/lessons/5-migrate-application-to-the-cloud/assignment.md",
  "language_code": "he"
}
-->
# הוספת שליטה ידנית בממסר

## הוראות

קוד ללא שרת יכול להיות מופעל על ידי מגוון דברים, כולל בקשות HTTP. ניתן להשתמש בטריגרים של HTTP כדי להוסיף שליטה ידנית לממסר שלך, ולאפשר למישהו להפעיל או לכבות את הממסר באמצעות בקשת אינטרנט.

במשימה זו, עליך להוסיף שני טריגרים של HTTP לאפליקציית הפונקציות שלך כדי להפעיל ולכבות את הממסר, תוך שימוש במה שלמדת בשיעור זה כדי לשלוח פקודות למכשיר.

כמה רמזים:

* ניתן להוסיף טריגר HTTP לאפליקציית הפונקציות הקיימת שלך באמצעות הפקודה הבאה:

    ```sh
    func new --name <trigger name> --template "HTTP trigger"
    ```

    החלף את `<trigger name>` בשם עבור טריגר ה-HTTP שלך. השתמש במשהו כמו `relay_on` ו-`relay_off`.

* לטריגרים של HTTP יכולה להיות בקרת גישה. כברירת מחדל הם דורשים מפתח API ספציפי לפונקציה שיש להעביר עם ה-URL כדי לפעול. עבור משימה זו, ניתן להסיר את ההגבלה הזו כך שכל אחד יוכל להפעיל את הפונקציה. כדי לעשות זאת, עדכן את הגדרת `authLevel` בקובץ `function.json` עבור טריגרי ה-HTTP לערך הבא:

    ```json
    "authLevel": "anonymous"
    ```

    > 💁 ניתן לקרוא עוד על בקרת גישה זו בתיעוד [מפתחות גישה לפונקציות](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn#authorization-keys).

* טריגרים של HTTP תומכים כברירת מחדל בבקשות GET ו-POST. משמעות הדבר היא שניתן לקרוא להם באמצעות דפדפן אינטרנט - דפדפנים מבצעים בקשות GET.

    כאשר אתה מפעיל את אפליקציית הפונקציות שלך באופן מקומי, תראה את ה-URL של הטריגר:

    ```output
    Functions:

        relay_off: [GET,POST] http://localhost:7071/api/relay_off

        relay_on: [GET,POST] http://localhost:7071/api/relay_on

        iot-hub-trigger: eventHubTrigger
    ```

    הדבק את ה-URL בדפדפן שלך ולחץ על `return`, או `Ctrl+click` (`Cmd+click` ב-macOS) על הקישור בחלון הטרמינל ב-VS Code כדי לפתוח אותו בדפדפן ברירת המחדל שלך. פעולה זו תפעיל את הטריגר.

    > 💁 שים לב שה-URL מכיל `/api` - טריגרי HTTP נמצאים כברירת מחדל בתת-דומיין `api`.

* כאשר אתה מפרסם את אפליקציית הפונקציות, ה-URL של טריגר ה-HTTP יהיה:

    `https://<functions app name>.azurewebsites.net/api/<trigger name>`

    כאשר `<functions app name>` הוא שם אפליקציית הפונקציות שלך, ו-`<trigger name>` הוא שם הטריגר שלך.

## קריטריונים להערכה

| קריטריון | מצטיין | מספק | דורש שיפור |
| -------- | ------- | ----- | ---------- |
| יצירת טריגרי HTTP | נוצרו 2 טריגרים להפעלת וכיבוי הממסר, עם שמות מתאימים | נוצר טריגר אחד עם שם מתאים | לא הצליח ליצור טריגרים |
| שליטה בממסר דרך טריגרי HTTP | הצליח לחבר את שני הטריגרים ל-IoT Hub ולשלוט בממסר בצורה מתאימה | הצליח לחבר טריגר אחד ל-IoT Hub ולשלוט בממסר בצורה מתאימה | לא הצליח לחבר את הטריגרים ל-IoT Hub |

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.