<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5de7dc1e2ddc402d415473bb795568d4",
  "translation_date": "2025-08-27T22:12:46+00:00",
  "source_file": "6-consumer/README.md",
  "language_code": "he"
}
-->
# צרכנות IoT - בניית עוזר קולי חכם

האוכל גודל, הועבר למפעל עיבוד, מוין לפי איכות, נמכר בחנות ועכשיו הגיע הזמן לבשל! אחד הכלים המרכזיים בכל מטבח הוא טיימר. בתחילה, הטיימרים היו שעוני חול - האוכל היה מוכן כאשר כל החול זרם לתחתית. לאחר מכן הם הפכו למכניים, ואז לחשמליים.

הגרסאות האחרונות הם חלק מהמכשירים החכמים שלנו. במטבחים בבתים בכל רחבי העולם תשמעו טבחים צועקים "היי סירי - הגדר טיימר ל-10 דקות", או "אלכסה - בטל את הטיימר של הלחם שלי". כבר אין צורך לחזור למטבח כדי לבדוק את הטיימר, אפשר לעשות זאת מהטלפון או בקריאה ברחבי החדר.

בארבעת השיעורים הללו תלמדו כיצד לבנות טיימר חכם, תוך שימוש בבינה מלאכותית לזיהוי הקול שלכם, הבנת הבקשה שלכם, ומתן תשובה עם מידע על הטיימר. בנוסף, תוסיפו תמיכה בשפות מרובות.

> ⚠️ עבודה עם נתוני דיבור ומיקרופון דורשת הרבה זיכרון, מה שאומר שקל להגיע למגבלות על מיקרו-בקרים. הפרויקט כאן מתמודד עם הבעיות הללו, אך שימו לב שהמעבדות של Wio Terminal מורכבות ועשויות לקחת יותר זמן ממעבדות אחרות בתוכנית הלימודים הזו.

> 💁 השיעורים הללו ישתמשו בכמה משאבי ענן. אם לא תסיימו את כל השיעורים בפרויקט הזה, ודאו שאתם [מנקים את הפרויקט שלכם](../clean-up.md).

## נושאים

1. [זיהוי דיבור עם מכשיר IoT](./lessons/1-speech-recognition/README.md)
1. [הבנת שפה](./lessons/2-language-understanding/README.md)
1. [הגדרת טיימר ומתן משוב קולי](./lessons/3-spoken-feedback/README.md)
1. [תמיכה בשפות מרובות](./lessons/4-multiple-language-support/README.md)

## קרדיטים

כל השיעורים נכתבו באהבה על ידי [Jim Bennett](https://GitHub.com/JimBobBennett)

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.