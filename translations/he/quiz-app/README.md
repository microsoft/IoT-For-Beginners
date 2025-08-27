<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2a459ea9177fb0508ca96068ae1009d2",
  "translation_date": "2025-08-27T23:05:31+00:00",
  "source_file": "quiz-app/README.md",
  "language_code": "he"
}
-->
# חידונים

החידונים האלו הם החידונים שלפני ואחרי ההרצאות בתוכנית הלימודים "IoT למתחילים" בכתובת https://aka.ms/iot-beginners

## הגדרת הפרויקט

```
npm install
```

### קומפילציה וטעינה מחדש בזמן פיתוח

```
npm run serve
```

### קומפילציה ומזעור עבור ייצור

```
npm run build
```

### בדיקת קוד ותיקון קבצים

```
npm run lint
```

### התאמה אישית של ההגדרות

ראו [הפניה להגדרות](https://cli.vuejs.org/config/).

קרדיטים: תודה לגרסה המקורית של אפליקציית החידונים הזו: https://github.com/arpan45/simple-quiz-vue

## פריסה ל-Azure

להלן מדריך שלב-אחר-שלב שיעזור לכם להתחיל:

1. שיבוט מאגר GitHub  
ודאו שקוד האפליקציה הסטטית שלכם נמצא במאגר ה-GitHub שלכם. שיבטו את המאגר הזה.

2. יצירת אפליקציה סטטית ב-Azure  
- צרו [חשבון Azure](http://azure.microsoft.com)  
- היכנסו ל-[פורטל Azure](https://portal.azure.com)  
- לחצו על "Create a resource" וחפשו "Static Web App".  
- לחצו על "Create".  

3. הגדרת האפליקציה הסטטית  
- #### פרטים בסיסיים:  
  - Subscription: בחרו את המנוי שלכם ב-Azure.  
  - Resource Group: צרו קבוצת משאבים חדשה או השתמשו בקיימת.  
  - Name: תנו שם לאפליקציה הסטטית שלכם.  
  - Region: בחרו את האזור הקרוב ביותר למשתמשים שלכם.  

- #### פרטי פריסה:  
  - Source: בחרו "GitHub".  
  - GitHub Account: אשרו ל-Azure גישה לחשבון ה-GitHub שלכם.  
  - Organization: בחרו את הארגון שלכם ב-GitHub.  
  - Repository: בחרו את המאגר שמכיל את קוד האפליקציה הסטטית שלכם.  
  - Branch: בחרו את הענף שממנו תרצו לפרוס.  

- #### פרטי בנייה:  
  - Build Presets: בחרו את המסגרת שבה האפליקציה שלכם נבנתה (לדוגמה, React, Angular, Vue וכו').  
  - App Location: ציינו את התיקייה שמכילה את קוד האפליקציה שלכם (לדוגמה, / אם היא נמצאת בשורש).  
  - API Location: אם יש לכם API, ציינו את מיקומו (אופציונלי).  
  - Output Location: ציינו את התיקייה שבה נוצר פלט הבנייה (לדוגמה, build או dist).  

4. סקירה ויצירה  
עברו על ההגדרות ולחצו "Create". Azure יגדיר את המשאבים הנדרשים וייצור קובץ GitHub Actions במאגר שלכם.

5. קובץ GitHub Actions  
Azure ייצור אוטומטית קובץ GitHub Actions במאגר שלכם (.github/workflows/azure-static-web-apps-<name>.yml). קובץ זה יטפל בתהליך הבנייה והפריסה.

6. מעקב אחר הפריסה  
עברו ללשונית "Actions" במאגר ה-GitHub שלכם.  
תוכלו לראות תהליך עבודה רץ. תהליך זה יבנה ויפרס את האפליקציה הסטטית שלכם ל-Azure.  
לאחר סיום התהליך, האפליקציה שלכם תהיה זמינה בכתובת ה-URL שסופקה על ידי Azure.

### דוגמה לקובץ תהליך עבודה

להלן דוגמה לאיך קובץ GitHub Actions עשוי להיראות:  
name: Azure Static Web Apps CI/CD  
```
on:
  push:
    branches:
      - main
  pull_request:
    types: [opened, synchronize, reopened, closed]
    branches:
      - main

jobs:
  build_and_deploy_job:
    runs-on: ubuntu-latest
    name: Build and Deploy Job
    steps:
      - uses: actions/checkout@v2
      - name: Build And Deploy
        id: builddeploy
        uses: Azure/static-web-apps-deploy@v1
        with:
          azure_static_web_apps_api_token: ${{ secrets.AZURE_STATIC_WEB_APPS_API_TOKEN }}
          repo_token: ${{ secrets.GITHUB_TOKEN }}
          action: "upload"
          app_location: "quiz-app" #App source code path
          api_location: ""API source code path optional
          output_location: "dist" #Built app content directory - optional
```

### משאבים נוספים  
- [תיעוד אפליקציות סטטיות ב-Azure](https://learn.microsoft.com/azure/static-web-apps/getting-started)  
- [תיעוד GitHub Actions](https://docs.github.com/actions/use-cases-and-examples/deploying/deploying-to-azure-static-web-app)  

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.