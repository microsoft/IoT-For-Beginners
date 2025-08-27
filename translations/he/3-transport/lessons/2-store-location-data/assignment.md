<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "b2e0a965723082b068f735aec0faf3f6",
  "translation_date": "2025-08-27T23:04:22+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/assignment.md",
  "language_code": "he"
}
-->
# חקור חיבורים של פונקציות

## הוראות

חיבורים של פונקציות מאפשרים לקוד שלך לשמור בלובים באחסון בלוב על ידי החזרתם מפונקציית `main`. חשבון אחסון Azure, האוסף ופרטים נוספים מוגדרים בקובץ `function.json`.

כאשר עובדים עם Azure או טכנולוגיות אחרות של Microsoft, המקור הטוב ביותר למידע הוא [התיעוד של Microsoft ב-docs.com](https://docs.microsoft.com/?WT.mc_id=academic-17441-jabenn). במשימה זו תצטרך לקרוא את התיעוד על חיבורים של Azure Functions כדי להבין כיצד להגדיר את חיבור הפלט.

כמה עמודים שכדאי להתחיל מהם:

* [מושגים של טריגרים וחיבורים ב-Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python)
* [סקירה כללית על חיבורי אחסון בלוב עבור Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob?WT.mc_id=academic-17441-jabenn)
* [חיבור פלט של אחסון בלוב עבור Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-bindings-storage-blob-output?WT.mc_id=academic-17441-jabenn&tabs=python)

## קריטריונים להערכה

| קריטריון | מצטיין | מספק | דורש שיפור |
| -------- | ------- | ----- | ---------- |
| הגדרת חיבור פלט לאחסון בלוב | הצליח להגדיר את חיבור הפלט, להחזיר את הבלוב ולשמור אותו בהצלחה באחסון בלוב | הצליח להגדיר את חיבור הפלט או להחזיר את הבלוב אך לא הצליח לשמור אותו בהצלחה באחסון בלוב | לא הצליח להגדיר את חיבור הפלט |

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.