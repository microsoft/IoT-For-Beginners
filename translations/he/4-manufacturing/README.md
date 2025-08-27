<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3764e089adf2d5801272bc0895f8498b",
  "translation_date": "2025-08-27T20:35:22+00:00",
  "source_file": "4-manufacturing/README.md",
  "language_code": "he"
}
-->
# ייצור ועיבוד - שימוש ב-IoT לשיפור עיבוד מזון

כאשר מזון מגיע למרכז לוגיסטי או למפעל עיבוד, הוא לא תמיד נשלח ישירות לסופרמרקטים. לעיתים קרובות המזון עובר מספר שלבי עיבוד, כמו מיון לפי איכות. זהו תהליך שבעבר היה ידני - הוא היה מתחיל בשדה, כאשר הקוטפים היו בוחרים רק פירות בשלים, ואז במפעל הפירות היו נוסעים על מסוע ועובדים היו מסירים ידנית פירות חבולים או רקובים. בתור מי שקטף ומיין תותים בעצמי כעבודת קיץ בזמן הלימודים, אני יכול להעיד שזה לא עבודה מהנה.

מערכות מודרניות יותר מסתמכות על IoT למיון. חלק מהמכשירים הראשונים, כמו הממיינים של [Weco](https://wecotek.com), משתמשים בחיישנים אופטיים כדי לזהות את איכות התוצרת, למשל לדחות עגבניות ירוקות. ניתן להשתמש בהם בקוצרים בשדה עצמו או במפעלי עיבוד.

ככל שהטכנולוגיה מתקדמת בתחומי הבינה המלאכותית (AI) ולמידת המכונה (ML), מכשירים אלו יכולים להפוך למתקדמים יותר, תוך שימוש במודלים של ML שאומנו להבחין בין פירות לבין עצמים זרים כמו אבנים, לכלוך או חרקים. ניתן גם לאמן מודלים אלו לזהות את איכות הפירות, לא רק פירות חבולים אלא גם זיהוי מוקדם של מחלות או בעיות אחרות בגידולים.

> 🎓 המונח *מודל ML* מתייחס לתוצאה של אימון תוכנה ללמידת מכונה על סט נתונים. לדוגמה, ניתן לאמן מודל ML להבחין בין עגבניות בשלות ולא בשלות, ואז להשתמש במודל על תמונות חדשות כדי לבדוק אם העגבניות בשלות או לא.

בארבעה שיעורים אלו תלמדו כיצד לאמן מודלים מבוססי תמונה לזיהוי איכות פירות, כיצד להשתמש בהם ממכשיר IoT, וכיצד להפעיל אותם בקצה - כלומר על מכשיר IoT ולא בענן.

> 💁 שיעורים אלו ישתמשו בכמה משאבי ענן. אם לא תסיימו את כל השיעורים בפרויקט זה, ודאו שאתם [מנקים את הפרויקט שלכם](../clean-up.md).

## נושאים

1. [אימון גלאי איכות פירות](./lessons/1-train-fruit-detector/README.md)
1. [בדיקת איכות פירות ממכשיר IoT](./lessons/2-check-fruit-from-device/README.md)
1. [הפעלת גלאי הפירות בקצה](./lessons/3-run-fruit-detector-edge/README.md)
1. [הפעלת זיהוי איכות פירות מחיישן](./lessons/4-trigger-fruit-detector/README.md)

## קרדיטים

כל השיעורים נכתבו באהבה ♥️ על ידי [Jen Fox](https://github.com/jenfoxbot) ו-[Jim Bennett](https://GitHub.com/JimBobBennett)

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.