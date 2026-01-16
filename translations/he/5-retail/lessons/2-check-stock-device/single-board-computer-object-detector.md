<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a3fdfec1d1e2cb645ea11c2930b51299",
  "translation_date": "2025-08-27T20:27:11+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-object-detector.md",
  "language_code": "he"
}
-->
# קרא למזהה האובייקטים שלך ממכשיר ה-IoT שלך - חומרה וירטואלית של IoT ו-Raspberry Pi

לאחר שמזהה האובייקטים שלך פורסם, ניתן להשתמש בו ממכשיר ה-IoT שלך.

## העתק את פרויקט מסווג התמונות

רוב הקוד של מזהה המלאי שלך זהה למסווג התמונות שיצרת בשיעור קודם.

### משימה - העתק את פרויקט מסווג התמונות

1. צור תיקייה בשם `stock-counter` במחשב שלך אם אתה משתמש במכשיר IoT וירטואלי, או ב-Raspberry Pi שלך. אם אתה משתמש במכשיר IoT וירטואלי, ודא שהגדרת סביבה וירטואלית.

1. הגדר את חומרת המצלמה.

    * אם אתה משתמש ב-Raspberry Pi, תצטרך לחבר את ה-PiCamera. ייתכן שתרצה גם לקבע את המצלמה במיקום קבוע, לדוגמה, על ידי תליית הכבל מעל קופסה או פחית, או קיבוע המצלמה לקופסה עם דבק דו-צדדי.
    * אם אתה משתמש במכשיר IoT וירטואלי, תצטרך להתקין את CounterFit ואת ה-CounterFit PyCamera shim. אם אתה מתכוון להשתמש בתמונות סטטיות, צלם כמה תמונות שמזהה האובייקטים שלך עדיין לא ראה. אם אתה מתכוון להשתמש במצלמת הרשת שלך, ודא שהיא ממוקמת כך שתוכל לראות את המלאי שאתה מזהה.

1. שחזר את השלבים מ-[שיעור 2 של פרויקט הייצור](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) כדי לצלם תמונות מהמצלמה.

1. שחזר את השלבים מ-[שיעור 2 של פרויקט הייצור](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) כדי לקרוא למסווג התמונות. רוב הקוד הזה ישמש שוב לזיהוי אובייקטים.

## שנה את הקוד ממסווג למזהה תמונות

הקוד שבו השתמשת לסיווג תמונות דומה מאוד לקוד לזיהוי אובייקטים. ההבדל העיקרי הוא השיטה שנקראת ב-SDK של Custom Vision, ותוצאות הקריאה.

### משימה - שנה את הקוד ממסווג למזהה תמונות

1. מחק את שלוש שורות הקוד שמסווגות את התמונה ומעבדות את התחזיות:

    ```python
    results = predictor.classify_image(project_id, iteration_name, image)
    
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    מחק את שלוש השורות הללו.

1. הוסף את הקוד הבא כדי לזהות אובייקטים בתמונה:

    ```python
    results = predictor.detect_image(project_id, iteration_name, image)

    threshold = 0.3
    
    predictions = list(prediction for prediction in results.predictions if prediction.probability > threshold)
    
    for prediction in predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    קוד זה קורא לשיטה `detect_image` על ה-predictor כדי להפעיל את מזהה האובייקטים. לאחר מכן הוא אוסף את כל התחזיות עם הסתברות מעל סף מסוים ומדפיס אותן לקונסולה.

    בניגוד למסווג תמונות שמחזיר רק תוצאה אחת לכל תג, מזהה האובייקטים יחזיר תוצאות מרובות, ולכן יש לסנן כל תוצאה עם הסתברות נמוכה.

1. הרץ את הקוד הזה והוא יצלם תמונה, ישלח אותה למזהה האובייקטים, וידפיס את האובייקטים שזוהו. אם אתה משתמש במכשיר IoT וירטואלי, ודא שיש לך תמונה מתאימה מוגדרת ב-CounterFit, או שמצלמת הרשת שלך נבחרה. אם אתה משתמש ב-Raspberry Pi, ודא שהמצלמה שלך מכוונת לאובייקטים על מדף.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   34.13%
    tomato paste:   33.95%
    tomato paste:   35.05%
    tomato paste:   32.80%
    ```

    > 💁 ייתכן שתצטרך להתאים את ה-`threshold` לערך מתאים לתמונות שלך.

    תוכל לראות את התמונה שצולמה ואת הערכים הללו בלשונית **Predictions** ב-Custom Vision.

    ![4 קופסאות של רסק עגבניות על מדף עם תחזיות של 35.8%, 33.5%, 25.7% ו-16.6%](../../../../../translated_images/he/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 תוכל למצוא את הקוד הזה בתיקיות [code-detect/pi](../../../../../5-retail/lessons/2-check-stock-device/code-detect/pi) או [code-detect/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-detect/virtual-iot-device).

😀 תוכנית מונה המלאי שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.