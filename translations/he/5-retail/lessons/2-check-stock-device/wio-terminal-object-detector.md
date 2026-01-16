<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-27T20:32:13+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "he"
}
-->
# קרא למזהה האובייקטים שלך ממכשיר ה-IoT שלך - Wio Terminal

לאחר שמזהה האובייקטים שלך פורסם, ניתן להשתמש בו ממכשיר ה-IoT שלך.

## העתק את פרויקט מסווג התמונות

רוב מזהה המלאי שלך דומה למסווג התמונות שיצרת בשיעור קודם.

### משימה - העתק את פרויקט מסווג התמונות

1. חבר את ה-ArduCam שלך ל-Wio Terminal, בהתאם לשלבים מ-[שיעור 2 של פרויקט הייצור](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    ייתכן שתרצה גם לקבע את המצלמה במיקום קבוע, למשל, על ידי תליית הכבל מעל קופסה או פחית, או קיבוע המצלמה לקופסה עם דבק דו-צדדי.

1. צור פרויקט חדש לחלוטין עבור Wio Terminal באמצעות PlatformIO. קרא לפרויקט הזה `stock-counter`.

1. שחזר את השלבים מ-[שיעור 2 של פרויקט הייצור](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) כדי לצלם תמונות מהמצלמה.

1. שחזר את השלבים מ-[שיעור 2 של פרויקט הייצור](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) כדי לקרוא למסווג התמונות. רוב הקוד הזה ישמש מחדש לזיהוי אובייקטים.

## שנה את הקוד ממסווג למזהה תמונות

הקוד שבו השתמשת לסיווג תמונות דומה מאוד לקוד לזיהוי אובייקטים. ההבדל העיקרי הוא ה-URL שנקרא, אותו קיבלת מ-Custom Vision, ותוצאות הקריאה.

### משימה - שנה את הקוד ממסווג למזהה תמונות

1. הוסף את הוראת ה-include הבאה לראש קובץ `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. שנה את שם הפונקציה `classifyImage` ל-`detectStock`, גם את שם הפונקציה וגם את הקריאה בפונקציה `buttonPressed`.

1. מעל הפונקציה `detectStock`, הכרז על סף לסינון כל זיהוי עם הסתברות נמוכה:

    ```cpp
    const float threshold = 0.3f;
    ```

    בניגוד למסווג תמונות שמחזיר רק תוצאה אחת לכל תג, מזהה האובייקטים יחזיר מספר תוצאות, ולכן יש לסנן כל תוצאה עם הסתברות נמוכה.

1. מעל הפונקציה `detectStock`, הכרז על פונקציה לעיבוד התחזיות:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    פונקציה זו מקבלת רשימת תחזיות ומדפיסה אותן לצג הסדרתי.

1. בפונקציה `detectStock`, החלף את תוכן הלולאה `for` שמסתובבת דרך התחזיות עם הבאה:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    הלולאה עוברת דרך התחזיות, משווה את ההסתברות לסף. כל התחזיות עם הסתברות גבוהה מהסף מתווספות ל-`list` ומועברות לפונקציה `processPredictions`.

1. העלה והרץ את הקוד שלך. כוון את המצלמה לאובייקטים על מדף ולחץ על כפתור C. תראה את הפלט בצג הסדרתי:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 ייתכן שתצטרך להתאים את ה-`threshold` לערך מתאים לתמונות שלך.

    תוכל לראות את התמונה שצולמה, ואת הערכים הללו בלשונית **Predictions** ב-Custom Vision.

    ![4 קופסאות של רסק עגבניות על מדף עם תחזיות ל-4 זיהויים של 35.8%, 33.5%, 25.7% ו-16.6%](../../../../../translated_images/he/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.png)

> 💁 תוכל למצוא את הקוד הזה בתיקיית [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 תוכנית ספירת המלאי שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.