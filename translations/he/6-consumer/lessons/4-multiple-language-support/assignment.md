<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "701f4a4466f9309b6e1d863077df0c06",
  "translation_date": "2025-08-27T22:16:38+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/assignment.md",
  "language_code": "he"
}
-->
# בנה מתרגם אוניברסלי

## הוראות

מתרגם אוניברסלי הוא מכשיר שיכול לתרגם בין שפות שונות, ומאפשר לאנשים שמדברים שפות שונות לתקשר זה עם זה. השתמש במה שלמדת בשיעורים האחרונים כדי לבנות מתרגם אוניברסלי באמצעות שני מכשירי IoT.

> אם אין לך שני מכשירים, עקוב אחר השלבים בשיעורים הקודמים כדי להגדיר מכשיר IoT וירטואלי כאחד מהמכשירים.

עליך להגדיר מכשיר אחד לשפה אחת, ומכשיר נוסף לשפה אחרת. כל מכשיר צריך לקבל דיבור, להמיר אותו לטקסט, לשלוח אותו למכשיר השני דרך IoT Hub ואפליקציית Functions, ואז לתרגם אותו ולהשמיע את הדיבור המתורגם.

> 💁 טיפ: כשאתה שולח את הדיבור ממכשיר אחד למכשיר אחר, שלח גם את השפה שבה הוא נאמר, כדי להקל על התרגום. תוכל אפילו לגרום לכל מכשיר להירשם תחילה באמצעות IoT Hub ואפליקציית Functions, תוך העברת השפה שהוא תומך בה לאחסון ב-Azure Storage. לאחר מכן תוכל להשתמש באפליקציית Functions כדי לבצע את התרגומים ולשלוח את הטקסט המתורגם למכשיר ה-IoT.

## קריטריונים להערכה

| קריטריון | מצטיין | מספק | דורש שיפור |
| -------- | ------- | ----- | ----------- |
| יצירת מתרגם אוניברסלי | הצליח לבנות מתרגם אוניברסלי, הממיר דיבור שזוהה על ידי מכשיר אחד לדיבור שמושמע על ידי מכשיר אחר בשפה שונה | הצליח לגרום לחלק מהרכיבים לעבוד, כמו זיהוי דיבור או תרגום, אך לא הצליח לבנות פתרון מקצה לקצה | לא הצליח לבנות אף חלק ממתרגם אוניברסלי עובד |

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.