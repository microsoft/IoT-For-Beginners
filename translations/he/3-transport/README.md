<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e978534a245b000725ed2a048f943213",
  "translation_date": "2025-08-27T22:44:36+00:00",
  "source_file": "3-transport/README.md",
  "language_code": "he"
}
-->
# הובלת מזון מהחווה למפעל - שימוש ב-IoT למעקב אחר משלוחים

חקלאים רבים מגדלים מזון למכירה - בין אם הם חקלאים מסחריים שמוכרים את כל מה שהם מגדלים, או חקלאים לצריכה עצמית שמוכרים את התוצרת העודפת שלהם כדי לקנות מוצרים חיוניים. איכשהו, המזון צריך להגיע מהחווה לצרכן, וזה בדרך כלל מתבצע באמצעות הובלה בכמויות גדולות מהחוות, למרכזים או מפעלי עיבוד, ומשם לחנויות. לדוגמה, חקלאי עגבניות יקטוף עגבניות, יארוז אותן בקופסאות, יעמיס את הקופסאות על משאית ואז יספק אותן למפעל עיבוד. העגבניות ימוינו, ומשם יועברו לצרכנים בצורת מזון מעובד, מכירה קמעונאית, או יוגשו במסעדות.

IoT יכול לעזור בשרשרת האספקה הזו על ידי מעקב אחר המזון בזמן ההובלה - לוודא שהנהגים נוסעים למקומות הנכונים, לעקוב אחר מיקום הרכבים, ולקבל התראות כשהרכבים מגיעים כדי שהמזון יוכל להיפרק ולהיות מוכן לעיבוד בהקדם האפשרי.

> 🎓 *שרשרת אספקה* היא רצף הפעילויות לייצור והובלת מוצר. לדוגמה, בחקלאות עגבניות זה כולל זרעים, אדמה, דשן ואספקת מים, גידול עגבניות, הובלתן למרכז מרכזי, העברתן למרכז מקומי של סופרמרקט, הובלתן לסופרמרקט עצמו, הצגתן למכירה, מכירתן לצרכן והבאתן הביתה לאכילה. כל שלב הוא כמו חוליה בשרשרת.

> 🎓 החלק של ההובלה בשרשרת האספקה נקרא *לוגיסטיקה*.

בארבע השיעורים הללו, תלמדו כיצד ליישם את האינטרנט של הדברים כדי לשפר את שרשרת האספקה על ידי מעקב אחר מזון בזמן שהוא מועמס על משאית (וירטואלית), אשר נעקבת בזמן שהיא נעה ליעדה. תלמדו על מעקב GPS, כיצד לאחסן ולחזות נתוני GPS, וכיצד לקבל התראות כשהמשאית מגיעה ליעדה.

> 💁 השיעורים הללו ישתמשו בכמה משאבי ענן. אם לא תסיימו את כל השיעורים בפרויקט הזה, ודאו שאתם [מנקים את הפרויקט שלכם](../clean-up.md).

## נושאים

1. [מעקב מיקום](lessons/1-location-tracking/README.md)
1. [אחסון נתוני מיקום](lessons/2-store-location-data/README.md)
1. [הצגת נתוני מיקום](lessons/3-visualize-location-data/README.md)
1. [גדרות גיאוגרפיות](lessons/4-geofences/README.md)

## קרדיטים

כל השיעורים נכתבו באהבה על ידי [Jen Looper](https://github.com/jlooper) ו-[Jim Bennett](https://GitHub.com/JimBobBennett)

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.