<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-27T21:27:24+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "he"
}
-->
# מדידת לחות קרקע - חומרה וירטואלית ל-IoT

בחלק זה של השיעור, תוסיפו חיישן לחות קרקע קיבולי למכשיר ה-IoT הווירטואלי שלכם, ותקראו ממנו ערכים.

## חומרה וירטואלית

מכשיר ה-IoT הווירטואלי ישתמש בחיישן לחות קרקע קיבולי מדומה מסוג Grove. זה שומר על המעבדה זהה לשימוש ב-Raspberry Pi עם חיישן לחות קרקע קיבולי פיזי.

במכשיר IoT פיזי, חיישן לחות הקרקע יהיה חיישן קיבולי שמודד את לחות הקרקע על ידי זיהוי הקיבוליות של הקרקע, תכונה שמשתנה בהתאם לשינויי הלחות בקרקע. ככל שלחות הקרקע עולה, המתח יורד.

זהו חיישן אנלוגי, ולכן הוא משתמש בממיר ADC מדומה של 10 ביט כדי לדווח על ערך בטווח של 1-1,023.

### הוספת חיישן לחות הקרקע ל-CounterFit

כדי להשתמש בחיישן לחות קרקע וירטואלי, יש להוסיף אותו לאפליקציית CounterFit.

#### משימה - הוספת חיישן לחות הקרקע ל-CounterFit

הוסיפו את חיישן לחות הקרקע לאפליקציית CounterFit.

1. צרו אפליקציית Python חדשה במחשב שלכם בתיקייה בשם `soil-moisture-sensor` עם קובץ יחיד בשם `app.py` וסביבת עבודה וירטואלית של Python, והוסיפו את חבילות ה-pip של CounterFit.

    > ⚠️ ניתן לעיין [בהוראות ליצירת והגדרת פרויקט Python של CounterFit בשיעור 1 במידת הצורך](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. ודאו שאפליקציית הווב של CounterFit פועלת.

1. צרו חיישן לחות קרקע:

    1. בתיבה *Create sensor* בלשונית *Sensors*, פתחו את התפריט הנפתח של *Sensor type* ובחרו *Soil Moisture*.

    1. השאירו את *Units* על *NoUnits*.

    1. ודאו שה-*Pin* מוגדר ל-*0*.

    1. לחצו על כפתור **Add** כדי ליצור את חיישן ה-*Soil Moisture* על Pin 0.

    ![הגדרות חיישן לחות הקרקע](../../../../../translated_images/he/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    חיישן לחות הקרקע ייווצר ויופיע ברשימת החיישנים.

    ![חיישן לחות הקרקע שנוצר](../../../../../translated_images/he/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## תכנות אפליקציית חיישן לחות הקרקע

כעת ניתן לתכנת את אפליקציית חיישן לחות הקרקע באמצעות החיישנים של CounterFit.

### משימה - תכנות אפליקציית חיישן לחות הקרקע

תכנתו את אפליקציית חיישן לחות הקרקע.

1. ודאו שאפליקציית `soil-moisture-sensor` פתוחה ב-VS Code.

1. פתחו את הקובץ `app.py`.

1. הוסיפו את הקוד הבא לראש הקובץ `app.py` כדי לחבר את האפליקציה ל-CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. הוסיפו את הקוד הבא לקובץ `app.py` כדי לייבא ספריות נדרשות:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    הפקודה `import time` מייבאת את המודול `time`, שישמש בהמשך המשימה.

    הפקודה `from counterfit_shims_grove.adc import ADC` מייבאת את המחלקה `ADC` כדי לתקשר עם ממיר אנלוגי לדיגיטלי וירטואלי שיכול להתחבר לחיישן של CounterFit.

1. הוסיפו את הקוד הבא מתחת לזה כדי ליצור מופע של המחלקה `ADC`:

    ```python
    adc = ADC()
    ```

1. הוסיפו לולאה אינסופית שקוראת מהממיר ADC על Pin 0 וכותבת את התוצאה לקונסולה. הלולאה תישן למשך 10 שניות בין קריאות.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. מתוך אפליקציית CounterFit, שנו את הערך של חיישן לחות הקרקע שייקרא על ידי האפליקציה. ניתן לעשות זאת באחת משתי דרכים:

    * הזינו מספר בתיבה *Value* של חיישן לחות הקרקע, ואז לחצו על כפתור **Set**. המספר שתזינו יהיה הערך שיוחזר על ידי החיישן.

    * סמנו את תיבת הסימון *Random*, הזינו ערכי *Min* ו-*Max*, ואז לחצו על כפתור **Set**. בכל פעם שהחיישן יקרא ערך, הוא יקרא מספר אקראי בין *Min* ל-*Max*.

1. הריצו את אפליקציית ה-Python. תראו את מדידות לחות הקרקע נכתבות לקונסולה. שנו את *Value* או את הגדרות ה-*Random* כדי לראות את הערך משתנה.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקייה [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 תוכנית חיישן לחות הקרקע שלכם הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.