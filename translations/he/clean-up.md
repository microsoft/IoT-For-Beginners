<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-27T20:23:20+00:00",
  "source_file": "clean-up.md",
  "language_code": "he"
}
-->
# נקה את הפרויקט שלך

לאחר שתסיים כל פרויקט, מומלץ למחוק את משאבי הענן שלך.

בשיעורים של כל פרויקט, ייתכן שיצרת חלק מהמשאבים הבאים:

* קבוצת משאבים (Resource Group)  
* IoT Hub  
* רישומי מכשירי IoT  
* חשבון אחסון (Storage Account)  
* אפליקציית Functions  
* חשבון Azure Maps  
* פרויקט Custom Vision  
* רישום מכולות Azure (Azure Container Registry)  
* משאב שירותי בינה מלאכותית (Cognitive Services)  

רוב המשאבים הללו לא יגרמו לעלויות - או שהם חינמיים לחלוטין, או שאתה משתמש ברמת שימוש חינמית. עבור שירותים שדורשים רמת שימוש בתשלום, סביר להניח שהשתמשת בהם ברמה הכלולה במכסה החינמית, או בעלות של כמה סנטים בלבד.

גם עם העלויות הנמוכות יחסית, כדאי למחוק את המשאבים הללו כשאתה מסיים. לדוגמה, ניתן להחזיק רק IoT Hub אחד ברמת השימוש החינמית, ולכן אם תרצה ליצור אחד נוסף תצטרך להשתמש ברמת שימוש בתשלום.

כל השירותים שלך נוצרו בתוך קבוצות משאבים, וזה מקל על הניהול. תוכל למחוק את קבוצת המשאבים, וכל השירותים באותה קבוצת משאבים יימחקו יחד איתה.

כדי למחוק את קבוצת המשאבים, הרץ את הפקודה הבאה בטרמינל או בשורת הפקודה:

```sh
az group delete --name <resource-group-name>
```

החלף את `<resource-group-name>` בשם קבוצת המשאבים שאתה מעוניין למחוק.

יופיע אישור:

```output
Are you sure you want to perform this operation? (y/n): 
```

הזן `y` כדי לאשר ולמחוק את קבוצת המשאבים.

ייקח זמן מה למחוק את כל השירותים.

> 💁 תוכל לקרוא עוד על מחיקת קבוצות משאבים בתיעוד [Azure Resource Manager resource group and resource deletion documentation on Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.