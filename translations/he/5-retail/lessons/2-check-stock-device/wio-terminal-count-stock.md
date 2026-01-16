<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T20:30:17+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "he"
}
-->
# ספירת מלאי ממכשיר ה-IoT שלך - Wio Terminal

שילוב של התחזיות ותיבות הגבול שלהן יכול לשמש לספירת מלאי בתמונה.

## ספירת מלאי

![4 קופסאות של רסק עגבניות עם תיבות גבול סביב כל קופסה](../../../../../translated_images/he/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

בתמונה שמוצגת למעלה, תיבות הגבול חופפות מעט. אם החפיפה הייתה גדולה יותר, תיבות הגבול עשויות להצביע על אותו אובייקט. כדי לספור את האובייקטים בצורה נכונה, יש להתעלם מתיבות עם חפיפה משמעותית.

### משימה - ספירת מלאי תוך התעלמות מחפיפה

1. פתח את פרויקט `stock-counter` שלך אם הוא לא פתוח כבר.

1. מעל הפונקציה `processPredictions`, הוסף את הקוד הבא:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    זה מגדיר את אחוז החפיפה המותר לפני שתיבות הגבול נחשבות לאותו אובייקט. 0.20 מגדיר חפיפה של 20%.

1. מתחת לזה, ומעל הפונקציה `processPredictions`, הוסף את הקוד הבא כדי לחשב את החפיפה בין שני מלבנים:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    הקוד הזה מגדיר מבנה `Point` לאחסון נקודות בתמונה, ומבנה `Rect` להגדרת מלבן באמצעות נקודת פינה עליונה שמאלית ונקודת פינה תחתונה ימנית. לאחר מכן הוא מגדיר פונקציה `area` שמחשבת את שטח המלבן מנקודות הפינה העליונה והתחתונה.

    לאחר מכן הוא מגדיר פונקציה `overlappingArea` שמחשבת את שטח החפיפה של שני מלבנים. אם הם לא חופפים, היא מחזירה 0.

1. מתחת לפונקציה `overlappingArea`, הכרז על פונקציה להמרת תיבת גבול ל-`Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    הפונקציה הזו לוקחת תחזית ממזהה האובייקטים, מוציאה את תיבת הגבול ומשתמשת בערכים שבתיבת הגבול כדי להגדיר מלבן. הצד הימני מחושב מהצד השמאלי בתוספת הרוחב. התחתון מחושב מהחלק העליון בתוספת הגובה.

1. התחזיות צריכות להיות מושוות זו לזו, ואם לשתי תחזיות יש חפיפה שעולה על הסף, אחת מהן צריכה להימחק. סף החפיפה הוא אחוז, ולכן יש להכפיל אותו בגודל תיבת הגבול הקטנה ביותר כדי לבדוק אם החפיפה עולה על האחוז הנתון של תיבת הגבול, ולא על האחוז הנתון של כל התמונה. התחל על ידי מחיקת התוכן של הפונקציה `processPredictions`.

1. הוסף את הקוד הבא לפונקציה הריקה `processPredictions`:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    הקוד הזה מכריז על וקטור לאחסון התחזיות שלא חופפות. לאחר מכן הוא עובר על כל התחזיות, ויוצר `Rect` מתיבת הגבול.

    לאחר מכן הקוד הזה עובר על התחזיות הנותרות, החל מהתחזית שאחרי התחזית הנוכחית. זה מונע השוואת תחזיות יותר מפעם אחת - לאחר ש-1 ו-2 הושוו, אין צורך להשוות את 2 עם 1, רק עם 3, 4 וכו'.

    עבור כל זוג תחזיות, שטח החפיפה מחושב. לאחר מכן הוא מושווה לשטח תיבת הגבול הקטנה ביותר - אם החפיפה עולה על אחוז הסף של תיבת הגבול הקטנה ביותר, התחזית מסומנת כלא עברה. אם לאחר השוואת כל החפיפות התחזית עוברת את הבדיקות, היא מתווספת לאוסף `passed_predictions`.

    > 💁 זו דרך מאוד פשוטה להסיר חפיפות, פשוט להסיר את הראשונה בזוג חופף. עבור קוד ייצור, כדאי להוסיף כאן יותר לוגיקה, כמו התחשבות בחפיפות בין מספר אובייקטים, או אם תיבת גבול אחת מכילה אחרת.

1. לאחר מכן, הוסף את הקוד הבא כדי לשלוח פרטים על התחזיות שעברו למוניטור הסדרתי:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    הקוד הזה עובר על התחזיות שעברו ומדפיס את פרטיהן למוניטור הסדרתי.

1. מתחת לזה, הוסף קוד להדפסת מספר הפריטים שנמנו למוניטור הסדרתי:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    זה יכול להישלח לשירות IoT כדי להתריע אם רמות המלאי נמוכות.

1. העלה והרץ את הקוד שלך. כוון את המצלמה לאובייקטים על מדף ולחץ על כפתור C. נסה לשנות את ערך `overlap_threshold` כדי לראות תחזיות שמתעלמים מהן.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 תוכנית ספירת המלאי שלך הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.