<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-27T21:28:07+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "he"
}
-->
# מדידת לחות קרקע - Raspberry Pi

בחלק זה של השיעור, תוסיף חיישן לחות קרקע קיבולי ל-Raspberry Pi שלך, ותקרא ממנו ערכים.

## חומרה

ה-Raspberry Pi זקוק לחיישן לחות קרקע קיבולי.

החיישן שבו תשתמש הוא [חיישן לחות קרקע קיבולי](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html), שמודד את לחות הקרקע על ידי זיהוי הקיבוליות של הקרקע, תכונה שמשתנה בהתאם לשינויי הלחות בקרקע. ככל שלחות הקרקע עולה, המתח יורד.

זהו חיישן אנלוגי, ולכן הוא משתמש בפין אנלוגי וב-ADC של 10 ביט בכובע הבסיס של Grove על ה-Pi כדי להמיר את המתח לאות דיגיטלי בטווח של 1-1,023. האות הזה נשלח לאחר מכן דרך GPIO ב-Pi.

### חיבור חיישן לחות הקרקע

ניתן לחבר את חיישן לחות הקרקע של Grove ל-Raspberry Pi.

#### משימה - חיבור חיישן לחות הקרקע

חבר את חיישן לחות הקרקע.

![חיישן לחות קרקע של Grove](../../../../../translated_images/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.he.png)

1. הכנס קצה אחד של כבל Grove לשקע על חיישן לחות הקרקע. הכבל ייכנס רק בכיוון אחד.

1. כשה-Raspberry Pi כבוי, חבר את הקצה השני של כבל Grove לשקע האנלוגי המסומן **A0** בכובע הבסיס של Grove המחובר ל-Pi. שקע זה הוא השני מימין, בשורה של השקעים ליד פיני ה-GPIO.

![חיישן לחות הקרקע של Grove מחובר לשקע A0](../../../../../translated_images/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.he.png)

1. הכנס את חיישן לחות הקרקע לתוך הקרקע. יש לו 'קו מיקום עליון' - קו לבן שחוצה את החיישן. הכנס את החיישן עד לקו זה אך לא מעבר לו.

![חיישן לחות הקרקע של Grove בתוך הקרקע](../../../../../translated_images/soil-moisture-sensor-in-soil.bfad91002bda5e96.he.png)

## תכנות חיישן לחות הקרקע

כעת ניתן לתכנת את ה-Raspberry Pi לשימוש בחיישן לחות הקרקע המחובר.

### משימה - תכנות חיישן לחות הקרקע

תכנת את המכשיר.

1. הפעל את ה-Pi והמתן עד שיסיים את תהליך האתחול.

1. פתח את VS Code, או ישירות על ה-Pi, או באמצעות חיבור דרך תוסף Remote SSH.

    > ⚠️ תוכל לעיין [בהוראות להגדרת VS Code והפעלתו בשיעור 1 של nightlight אם יש צורך](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. מהטרמינל, צור תיקייה חדשה בספריית הבית של המשתמש `pi` בשם `soil-moisture-sensor`. צור קובץ בתיקייה זו בשם `app.py`.

1. פתח את התיקייה הזו ב-VS Code.

1. הוסף את הקוד הבא לקובץ `app.py` כדי לייבא ספריות נדרשות:

    ```python
    import time
    from grove.adc import ADC
    ```

    הפקודה `import time` מייבאת את המודול `time` שישמש בהמשך המשימה.

    הפקודה `from grove.adc import ADC` מייבאת את ה-`ADC` מספריות ה-Python של Grove. ספרייה זו מכילה קוד לאינטראקציה עם ממיר האנלוגי לדיגיטלי בכובע הבסיס של ה-Pi ולקריאת מתחים מחיישנים אנלוגיים.

1. הוסף את הקוד הבא מתחת לזה כדי ליצור מופע של מחלקת `ADC`:

    ```python
    adc = ADC()
    ```

1. הוסף לולאה אינסופית שקוראת מה-ADC בפין A0, וכותבת את התוצאה לקונסול. הלולאה תישן למשך 10 שניות בין קריאות.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. הרץ את אפליקציית ה-Python. תראה את מדידות לחות הקרקע נכתבות לקונסול. הוסף מים לקרקע, או הוצא את החיישן מהקרקע, וצפה בשינוי הערך.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    בדוגמת הפלט למעלה, ניתן לראות את ירידת המתח כאשר מוסיפים מים.

> 💁 תוכל למצוא את הקוד הזה בתיקייה [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi).

😀 תוכנית חיישן לחות הקרקע שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.