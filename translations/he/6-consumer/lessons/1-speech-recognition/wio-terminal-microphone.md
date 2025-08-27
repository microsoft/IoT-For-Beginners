<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "93d352de36526b8990e41dd538100324",
  "translation_date": "2025-08-27T22:42:47+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-microphone.md",
  "language_code": "he"
}
-->
# הגדר את המיקרופון והרמקולים שלך - Wio Terminal

בחלק זה של השיעור, תוסיף רמקולים ל-Wio Terminal שלך. ל-Wio Terminal כבר יש מיקרופון מובנה, שניתן להשתמש בו כדי להקליט דיבור.

## חומרה

ל-Wio Terminal כבר יש מיקרופון מובנה, שניתן להשתמש בו כדי להקליט שמע לצורך זיהוי דיבור.

![המיקרופון ב-Wio Terminal](../../../../../translated_images/wio-mic.3f8c843dbe8ad917424037a93e3d25c62634add00a04dd8e091317b5a7a90088.he.png)

כדי להוסיף רמקול, ניתן להשתמש ב-[ReSpeaker 2-Mics Pi Hat](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html). מדובר בלוח חיצוני שמכיל שני מיקרופונים MEMS, כמו גם חיבור לרמקול ושקע לאוזניות.

![ReSpeaker 2-Mics Pi Hat](../../../../../translated_images/respeaker.f5d19d1c6b14ab1676d24ac2764e64fac5339046ae07be8b45ce07633d61b79b.he.png)

תצטרך להוסיף אוזניות, רמקול עם חיבור 3.5 מ"מ, או רמקול עם חיבור JST כמו [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html).

כדי לחבר את ה-ReSpeaker 2-Mics Pi Hat תצטרך כבלי ג'אמפר 40 פינים (המכונים גם זכר-לזכר).

> 💁 אם אתה מיומן בהלחמה, תוכל להשתמש ב-[40 Pin Raspberry Pi Hat Adapter Board For Wio Terminal](https://www.seeedstudio.com/40-Pin-Raspberry-Pi-Hat-Adapter-Board-For-Wio-Terminal-p-4730.html) כדי לחבר את ה-ReSpeaker.

תצטרך גם כרטיס SD כדי להוריד ולהשמיע שמע. ה-Wio Terminal תומך רק בכרטיסי SD עד גודל של 16GB, ויש לעצב אותם כ-FAT32 או exFAT.

### משימה - חיבור ה-ReSpeaker Pi Hat

1. כשה-Wio Terminal כבוי, חבר את ה-ReSpeaker 2-Mics Pi Hat ל-Wio Terminal באמצעות כבלי הג'אמפר ושקעי ה-GPIO בגב ה-Wio Terminal:

    יש לחבר את הפינים בצורה הבאה:

    ![תרשים פינים](../../../../../translated_images/wio-respeaker-wiring-0.767f80aa6508103880d256cdf99ee7219e190db257c7261e4aec219759dc67b9.he.png)

1. מקם את ה-ReSpeaker ואת ה-Wio Terminal כך ששקעי ה-GPIO פונים כלפי מעלה, ובצד השמאלי.

1. התחל מהשקע בפינה השמאלית העליונה של שקע ה-GPIO ב-ReSpeaker. חבר כבל ג'אמפר מהשקע השמאלי העליון של ה-ReSpeaker לשקע השמאלי העליון של ה-Wio Terminal.

1. חזור על הפעולה לאורך כל שקעי ה-GPIO בצד השמאלי. ודא שהפינים מחוברים היטב.

    ![ReSpeaker עם הפינים השמאליים מחוברים לפינים השמאליים של ה-Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-1.8d894727f2ba24004824ee5e06b83b6d10952550003a3efb603182121521b0ef.he.png)

    ![ReSpeaker עם הפינים השמאליים מחוברים לפינים השמאליים של ה-Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-2.329e1cbd306e754f8ffe56f9294794f4a8fa123860d76067a79e9ea385d1bf56.he.png)

    > 💁 אם כבלי הג'אמפר שלך מחוברים ברצועות, שמור אותם יחד - זה מקל על הבטחת חיבור כל הכבלים בסדר הנכון.

1. חזור על התהליך באמצעות שקעי ה-GPIO בצד הימני של ה-ReSpeaker וה-Wio Terminal. הכבלים הללו צריכים לעבור מסביב לכבלים שכבר מחוברים.

    ![ReSpeaker עם הפינים הימניים מחוברים לפינים הימניים של ה-Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-3.75b0be447e2fa9307a6a954f9ae8a71b77e39ada6a5ef1a059d341dc850fd90c.he.png)

    ![ReSpeaker עם הפינים הימניים מחוברים לפינים הימניים של ה-Wio Terminal](../../../../../translated_images/wio-respeaker-wiring-4.aa9cd434d8779437de720cba2719d83992413caed1b620b6148f6c8924889afb.he.png)

    > 💁 אם כבלי הג'אמפר שלך מחוברים ברצועות, חלק אותם לשתי רצועות. העבר אחת מכל צד של הכבלים הקיימים.

    > 💁 ניתן להשתמש בנייר דבק כדי להחזיק את הפינים כבלוק ולמנוע יציאה שלהם בזמן החיבור.
    >
    > ![הפינים מקובעים עם נייר דבק](../../../../../translated_images/wio-respeaker-wiring-5.af117c20acf622f3cd656ccd8f4053f8845d6aaa3af164d24cb7dbd54a4bb470.he.png)

1. תצטרך להוסיף רמקול.

    * אם אתה משתמש ברמקול עם כבל JST, חבר אותו ליציאת ה-JST ב-ReSpeaker.

      ![רמקול מחובר ל-ReSpeaker עם כבל JST](../../../../../translated_images/respeaker-jst-speaker.a441d177809df9458041a2012dd336dbb22c00a5c9642647109d2940a50d6fcc.he.png)

    * אם אתה משתמש ברמקול עם חיבור 3.5 מ"מ או אוזניות, הכנס אותם לשקע 3.5 מ"מ.

      ![רמקול מחובר ל-ReSpeaker דרך שקע 3.5 מ"מ](../../../../../translated_images/respeaker-35mm-speaker.ad79ef4f128c7751f0abf854869b6b779c90c12ae3e48909944a7e48aeee3c7e.he.png)

### משימה - הגדרת כרטיס ה-SD

1. חבר את כרטיס ה-SD למחשב שלך, באמצעות קורא חיצוני אם אין לך חריץ לכרטיס SD.

1. עצב את כרטיס ה-SD באמצעות הכלי המתאים במחשב שלך, וודא שאתה משתמש במערכת קבצים FAT32 או exFAT.

1. הכנס את כרטיס ה-SD לחריץ ה-SD בצד השמאלי של ה-Wio Terminal, ממש מתחת לכפתור ההפעלה. ודא שהכרטיס נכנס עד הסוף ונלחץ פנימה - ייתכן שתצטרך כלי דק או כרטיס SD נוסף כדי לדחוף אותו עד הסוף.

    ![הכנסת כרטיס ה-SD לחריץ ה-SD מתחת למתג ההפעלה](../../../../../translated_images/wio-sd-card.acdcbe322fa4ee7f8f9c8cc015b3263964bb26ab5c7e25b41747988cc5280d64.he.png)

    > 💁 כדי להוציא את כרטיס ה-SD, יש ללחוץ עליו מעט והוא ייצא. תצטרך כלי דק כמו מברג שטוח או כרטיס SD נוסף כדי לעשות זאת.

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.