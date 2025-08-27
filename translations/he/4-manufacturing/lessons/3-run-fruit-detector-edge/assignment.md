<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "cc7ad255517f5f618f9c8899e6ff6783",
  "translation_date": "2025-08-27T20:51:00+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/assignment.md",
  "language_code": "he"
}
-->
# הפעלת שירותים נוספים בקצה

## הוראות

לא רק מסווגי תמונות יכולים לפעול בקצה, כל דבר שניתן לארוז בתוך מכולה יכול להיות מופעל על מכשיר IoT Edge. קוד ללא שרת שמופעל כ-Azure Functions, כמו הטריגרים שיצרתם בשיעורים קודמים, יכול לפעול בתוך מכולות, ולכן גם על IoT Edge.

בחרו אחד מהשיעורים הקודמים ונסו להפעיל את אפליקציית Azure Functions בתוך מכולת IoT Edge. תוכלו למצוא מדריך שמראה כיצד לעשות זאת באמצעות פרויקט אפליקציית Functions שונה ב-[מדריך: פריסת Azure Functions כמודולים של IoT Edge במסמכי Microsoft](https://docs.microsoft.com/azure/iot-edge/tutorial-deploy-function?WT.mc_id=academic-17441-jabenn&view=iotedge-2020-11).

## קריטריונים להערכה

| קריטריון | מצטיין | מספק | דורש שיפור |
| -------- | ------- | ----- | ---------- |
| פריסת אפליקציית Azure Functions ל-IoT Edge | הצליח לפרוס אפליקציית Azure Functions ל-IoT Edge ולהשתמש בה עם מכשיר IoT כדי להפעיל טריגר מנתוני IoT | הצליח לפרוס אפליקציית Functions ל-IoT Edge, אך לא הצליח להפעיל את הטריגר | לא הצליח לפרוס אפליקציית Functions ל-IoT Edge |

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.