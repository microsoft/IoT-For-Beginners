<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c4320311c0f2c1884a6a21265d98a51",
  "translation_date": "2025-08-27T20:31:22+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/single-board-computer-count-stock.md",
  "language_code": "he"
}
-->
# ספירת מלאי ממכשיר IoT שלך - חומרה וירטואלית של IoT ו-Raspberry Pi

שילוב של התחזיות ותיבות הגבול שלהן יכול לשמש לספירת מלאי בתמונה.

## הצגת תיבות גבול

כשלב עזר לדיבוג, ניתן לא רק להדפיס את תיבות הגבול, אלא גם לצייר אותן על התמונה שנשמרה בדיסק כאשר התמונה צולמה.

### משימה - הדפסת תיבות הגבול

1. ודא שהפרויקט `stock-counter` פתוח ב-VS Code, והסביבה הווירטואלית מופעלת אם אתה משתמש במכשיר IoT וירטואלי.

1. שנה את פקודת `print` בלולאת ה-`for` לקוד הבא כדי להדפיס את תיבות הגבול לקונסול:

    ```python
    print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%\t{prediction.bounding_box}')
    ```

1. הרץ את האפליקציה כאשר המצלמה מכוונת למלאי על מדף. תיבות הגבול יודפסו לקונסול, עם ערכי left, top, width ו-height בין 0 ל-1.

    ```output
    pi@raspberrypi:~/stock-counter $ python3 app.py 
    tomato paste:   33.42%  {'additional_properties': {}, 'left': 0.3455171, 'top': 0.09916268, 'width': 0.14175442, 'height': 0.29405564}
    tomato paste:   34.41%  {'additional_properties': {}, 'left': 0.48283678, 'top': 0.10242918, 'width': 0.11782813, 'height': 0.27467814}
    tomato paste:   31.25%  {'additional_properties': {}, 'left': 0.4923783, 'top': 0.35007596, 'width': 0.13668466, 'height': 0.28304994}
    tomato paste:   31.05%  {'additional_properties': {}, 'left': 0.36416405, 'top': 0.37494493, 'width': 0.14024884, 'height': 0.26880276}
    ```

### משימה - ציור תיבות גבול על התמונה

1. חבילת Pip בשם [Pillow](https://pypi.org/project/Pillow/) יכולה לשמש לציור על תמונות. התקן אותה באמצעות הפקודה הבאה:

    ```sh
    pip3 install pillow
    ```

    אם אתה משתמש במכשיר IoT וירטואלי, ודא שאתה מריץ את הפקודה מתוך הסביבה הווירטואלית המופעלת.

1. הוסף את פקודת ה-import הבאה לראש קובץ `app.py`:

    ```python
    from PIL import Image, ImageDraw, ImageColor
    ```

    זה מייבא את הקוד הדרוש לעריכת התמונה.

1. הוסף את הקוד הבא לסוף קובץ `app.py`:

    ```python
    with Image.open('image.jpg') as im:
        draw = ImageDraw.Draw(im)
    
        for prediction in predictions:
            scale_left = prediction.bounding_box.left
            scale_top = prediction.bounding_box.top
            scale_right = prediction.bounding_box.left + prediction.bounding_box.width
            scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
            
            left = scale_left * im.width
            top = scale_top * im.height
            right = scale_right * im.width
            bottom = scale_bottom * im.height
    
            draw.rectangle([left, top, right, bottom], outline=ImageColor.getrgb('red'), width=2)
    
        im.save('image.jpg')
    ```

    הקוד פותח את התמונה שנשמרה קודם לעריכה. לאחר מכן הוא עובר דרך התחזיות, מקבל את תיבות הגבול ומחשב את הקואורדינטה הימנית התחתונה באמצעות ערכי תיבת הגבול בין 0 ל-1. הערכים הללו מומרות לקואורדינטות תמונה על ידי הכפלה בממד הרלוונטי של התמונה. לדוגמה, אם ערך left היה 0.5 בתמונה ברוחב 600 פיקסלים, זה יומר ל-300 (0.5 x 600 = 300).

    כל תיבת גבול מצוירת על התמונה באמצעות קו אדום. לבסוף, התמונה הערוכה נשמרת ומחליפה את התמונה המקורית.

1. הרץ את האפליקציה כאשר המצלמה מכוונת למלאי על מדף. תראה את קובץ `image.jpg` ב-VS Code explorer, ותוכל לבחור אותו כדי לראות את תיבות הגבול.

    ![4 קופסאות של רסק עגבניות עם תיבות גבול סביב כל קופסה](../../../../../translated_images/he/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

## ספירת מלאי

בתמונה שמוצגת למעלה, תיבות הגבול חופפות מעט. אם החפיפה הייתה גדולה יותר, תיבות הגבול עשויות להצביע על אותו אובייקט. כדי לספור את האובייקטים בצורה נכונה, יש להתעלם מתיבות עם חפיפה משמעותית.

### משימה - ספירת מלאי תוך התעלמות מחפיפה

1. חבילת Pip בשם [Shapely](https://pypi.org/project/Shapely/) יכולה לשמש לחישוב החפיפה. אם אתה משתמש ב-Raspberry Pi, תצטרך להתקין תלות ספרייה תחילה:

    ```sh
    sudo apt install libgeos-dev
    ```

1. התקן את חבילת Shapely באמצעות Pip:

    ```sh
    pip3 install shapely
    ```

    אם אתה משתמש במכשיר IoT וירטואלי, ודא שאתה מריץ את הפקודה מתוך הסביבה הווירטואלית המופעלת.

1. הוסף את פקודת ה-import הבאה לראש קובץ `app.py`:

    ```python
    from shapely.geometry import Polygon
    ```

    זה מייבא את הקוד הדרוש ליצירת פוליגונים לחישוב חפיפה.

1. מעל הקוד שמצייר את תיבות הגבול, הוסף את הקוד הבא:

    ```python
    overlap_threshold = 0.20
    ```

    זה מגדיר את אחוז החפיפה המותר לפני שתיבות הגבול נחשבות לאותו אובייקט. 0.20 מגדיר חפיפה של 20%.

1. כדי לחשב חפיפה באמצעות Shapely, תיבות הגבול צריכות להיות מומרות לפוליגונים של Shapely. הוסף את הפונקציה הבאה כדי לעשות זאת:

    ```python
    def create_polygon(prediction):
        scale_left = prediction.bounding_box.left
        scale_top = prediction.bounding_box.top
        scale_right = prediction.bounding_box.left + prediction.bounding_box.width
        scale_bottom = prediction.bounding_box.top + prediction.bounding_box.height
    
        return Polygon([(scale_left, scale_top), (scale_right, scale_top), (scale_right, scale_bottom), (scale_left, scale_bottom)])
    ```

    הפונקציה יוצרת פוליגון באמצעות תיבת הגבול של תחזית.

1. הלוגיקה להסרת אובייקטים חופפים כוללת השוואת כל תיבות הגבול, ואם זוג תחזיות כלשהו חופף יותר מהסף, אחת התחזיות נמחקת. כדי להשוות את כל התחזיות, משווים תחזית 1 עם 2, 3, 4 וכו', ואז 2 עם 3, 4 וכו'. הקוד הבא עושה זאת:

    ```python
    to_delete = []

    for i in range(0, len(predictions)):
        polygon_1 = create_polygon(predictions[i])
    
        for j in range(i+1, len(predictions)):
            polygon_2 = create_polygon(predictions[j])
            overlap = polygon_1.intersection(polygon_2).area

            smallest_area = min(polygon_1.area, polygon_2.area)
    
            if overlap > (overlap_threshold * smallest_area):
                to_delete.append(predictions[i])
                break
    
    for d in to_delete:
        predictions.remove(d)

    print(f'Counted {len(predictions)} stock items')
    ```

    החפיפה מחושבת באמצעות שיטת `Polygon.intersection` של Shapely שמחזירה פוליגון שמייצג את החפיפה. השטח מחושב מהפוליגון הזה. סף החפיפה אינו ערך מוחלט, אלא צריך להיות אחוז מתיבת הגבול, ולכן תיבת הגבול הקטנה ביותר נמצאת, וסף החפיפה משמש לחישוב איזה שטח החפיפה יכול להיות כדי לא לחרוג מאחוז החפיפה של תיבת הגבול הקטנה ביותר. אם החפיפה חורגת מזה, התחזית מסומנת למחיקה.

    ברגע שתחזית מסומנת למחיקה, אין צורך לבדוק אותה שוב, ולכן הלולאה הפנימית נשברת כדי לבדוק את התחזית הבאה. אי אפשר למחוק פריטים מרשימה בזמן שעוברים עליה, ולכן תיבות הגבול שחופפות יותר מהסף מתווספות לרשימת `to_delete`, ואז נמחקות בסוף.

    לבסוף, ספירת המלאי מודפסת לקונסול. ניתן לשלוח את המידע הזה לשירות IoT כדי להתריע אם רמות המלאי נמוכות. כל הקוד הזה נמצא לפני ציור תיבות הגבול, כך שתראה את תחזיות המלאי ללא חפיפות על התמונות שנוצרו.

    > 💁 זהו פתרון מאוד פשוט להסרת חפיפות, שמסיר רק את הראשון בזוג חופף. בקוד ייצור, תרצה להוסיף לוגיקה נוספת, כמו התחשבות בחפיפות בין אובייקטים מרובים, או אם תיבת גבול אחת מכילה אחרת.

1. הרץ את האפליקציה כאשר המצלמה מכוונת למלאי על מדף. הפלט יציין את מספר תיבות הגבול ללא חפיפות שחורגות מהסף. נסה לשנות את ערך `overlap_threshold` כדי לראות תחזיות שמתעלמים מהן.

> 💁 תוכל למצוא את הקוד הזה בתיקיות [code-count/pi](../../../../../5-retail/lessons/2-check-stock-device/code-count/pi) או [code-count/virtual-iot-device](../../../../../5-retail/lessons/2-check-stock-device/code-count/virtual-iot-device).

😀 תוכנית ספירת המלאי שלך הצליחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.