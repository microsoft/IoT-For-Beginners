<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-27T20:51:41+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "he"
}
-->
# יצירת מכונה וירטואלית שמריצה IoT Edge

ב-Azure, ניתן ליצור מכונה וירטואלית - מחשב בענן שניתן להגדיר אותו בכל דרך שתרצו ולהריץ עליו את התוכנה שלכם.

> 💁 ניתן לקרוא עוד על מכונות וירטואליות בעמוד [המכונה הווירטואלית בויקיפדיה](https://wikipedia.org/wiki/Virtual_machine).

## משימה - הגדרת מכונה וירטואלית עם IoT Edge

1. הריצו את הפקודה הבאה כדי ליצור מכונה וירטואלית עם Azure IoT Edge שכבר מותקן מראש:

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    החליפו את `<vm_name>` בשם עבור המכונה הווירטואלית. השם צריך להיות ייחודי גלובלית, לכן השתמשו במשהו כמו `fruit-quality-detector-vm-` עם השם שלכם או ערך אחר בסוף.

    החליפו את `<username>` ו-`<password>` בשם משתמש וסיסמה לשימוש לצורך התחברות למכונה הווירטואלית. השם והסיסמה צריכים להיות יחסית מאובטחים, לכן לא ניתן להשתמש ב-admin/password.

    החליפו את `<connection_string>` במחרוזת החיבור של מכשיר ה-IoT Edge שלכם, `fruit-quality-detector-edge`.

    פעולה זו תיצור מכונה וירטואלית מוגדרת כ-`DS1 v2`. קטגוריות אלו מציינות את עוצמת המכונה, ולכן גם את העלות שלה. למכונה זו יש מעבד אחד ו-3.5GB של זיכרון RAM.

    > 💰 ניתן לראות את המחירים הנוכחיים של מכונות אלו במדריך [תמחור מכונות וירטואליות של Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn).

    לאחר יצירת המכונה הווירטואלית, ה-IoT Edge runtime יותקן באופן אוטומטי ויוגדר להתחבר ל-IoT Hub שלכם כמכשיר `fruit-quality-detector-edge`.

1. תצטרכו את כתובת ה-IP או את שם ה-DNS של המכונה הווירטואלית כדי לקרוא למסווג התמונות ממנה. הריצו את הפקודה הבאה כדי לקבל את המידע הזה:

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    העתיקו את הערך של השדה `PublicIps` או `Fqdns`.

1. מכונות וירטואליות עולות כסף. נכון לזמן כתיבת שורות אלו, מכונה מסוג DS1 עולה כ-$0.06 לשעה. כדי לצמצם עלויות, כדאי לכבות את המכונה הווירטואלית כשאינכם משתמשים בה ולמחוק אותה כשסיימתם את הפרויקט.

    ניתן להגדיר את המכונה הווירטואלית לכיבוי אוטומטי בשעה מסוימת בכל יום. כך, אם תשכחו לכבות אותה, לא תחויבו מעבר לזמן עד הכיבוי האוטומטי. השתמשו בפקודה הבאה כדי להגדיר זאת:

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    החליפו את `<vm_name>` בשם המכונה הווירטואלית שלכם.

    החליפו את `<shutdown_time_utc>` בזמן UTC שבו תרצו שהמכונה תכבה, באמצעות 4 ספרות בפורמט HHMM. לדוגמה, אם תרצו לכבות בחצות UTC, הגדירו זאת כ-`0000`. עבור 7:30 בערב בחוף המערבי של ארה"ב, השתמשו ב-`0230` (7:30 בערב בחוף המערבי של ארה"ב הוא 2:30 בבוקר UTC).

1. מסווג התמונות שלכם ירוץ על מכשיר ה-edge הזה, ויקשיב על פורט 80 (פורט HTTP סטנדרטי). כברירת מחדל, מכונות וירטואליות חוסמות פורטים נכנסים, לכן תצטרכו לאפשר את פורט 80. פורטים מופעלים בקבוצות אבטחת רשת, לכן קודם כל תצטרכו לדעת את שם קבוצת האבטחה של הרשת עבור המכונה הווירטואלית שלכם, אותו ניתן למצוא באמצעות הפקודה הבאה:

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    העתיקו את הערך של השדה `Name`.

1. הריצו את הפקודה הבאה כדי להוסיף חוק לפתיחת פורט 80 בקבוצת האבטחה של הרשת:

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    החליפו את `<nsg name>` בשם קבוצת האבטחה של הרשת מהשלב הקודם.

### משימה - ניהול המכונה הווירטואלית לצמצום עלויות

1. כשאינכם משתמשים במכונה הווירטואלית, כדאי לכבות אותה. כדי לכבות את המכונה, השתמשו בפקודה הבאה:

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    החליפו את `<vm_name>` בשם המכונה הווירטואלית שלכם.

    > 💁 קיימת פקודה `az vm stop` שתעצור את המכונה הווירטואלית, אך היא תשאיר את המחשב מוקצה לכם, כך שתמשיכו לשלם כאילו הוא עדיין פועל.

1. כדי להפעיל מחדש את המכונה הווירטואלית, השתמשו בפקודה הבאה:

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    החליפו את `<vm_name>` בשם המכונה הווירטואלית שלכם.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.