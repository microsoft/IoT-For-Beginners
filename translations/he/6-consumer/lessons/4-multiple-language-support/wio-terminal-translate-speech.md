# תרגום דיבור - Wio Terminal

בחלק זה של השיעור, תכתבו קוד לתרגום טקסט באמצעות שירות התרגום.

## המרת טקסט לדיבור באמצעות שירות התרגום

ממשק ה-REST API של שירות הדיבור אינו תומך בתרגומים ישירים. במקום זאת, ניתן להשתמש בשירות התרגום כדי לתרגם את הטקסט שנוצר על ידי שירות הדיבור לטקסט, ואת הטקסט של התגובה המדוברת. לשירות זה יש ממשק REST API שניתן להשתמש בו לתרגום הטקסט, אך כדי להקל על השימוש, נעטוף אותו בטריגר HTTP נוסף באפליקציית הפונקציות שלכם.

### משימה - יצירת פונקציה ללא שרת לתרגום טקסט

1. פתחו את הפרויקט `smart-timer-trigger` ב-VS Code, ופתחו את הטרמינל תוך וידוא שהסביבה הווירטואלית מופעלת. אם לא, סגרו וצרו מחדש את הטרמינל.

1. פתחו את הקובץ `local.settings.json` והוסיפו הגדרות עבור מפתח ה-API של שירות התרגום והמיקום:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    החליפו `<key>` במפתח ה-API של משאב שירות התרגום שלכם. החליפו `<location>` במיקום שבו יצרתם את משאב שירות התרגום.

1. הוסיפו טריגר HTTP חדש לאפליקציה זו בשם `translate-text` באמצעות הפקודה הבאה מתוך הטרמינל של VS Code בתיקיית השורש של פרויקט אפליקציית הפונקציות:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    פעולה זו תיצור טריגר HTTP בשם `translate-text`.

1. החליפו את תוכן הקובץ `__init__.py` בתיקיית `translate-text` בקוד הבא:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    קוד זה מוציא את הטקסט והשפות מבקשת ה-HTTP. לאחר מכן, הוא שולח בקשה ל-REST API של שירות התרגום, מעביר את השפות כפרמטרים ל-URL ואת הטקסט לתרגום כגוף הבקשה. לבסוף, התרגום מוחזר.

1. הריצו את אפליקציית הפונקציות שלכם באופן מקומי. לאחר מכן, תוכלו לקרוא לה באמצעות כלי כמו curl באותו אופן שבו בדקתם את טריגר ה-HTTP `text-to-timer`. ודאו שאתם מעבירים את הטקסט לתרגום והשפות כגוף JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    דוגמה זו מתרגמת את *Définir une minuterie de 30 secondes* מצרפתית לאנגלית אמריקאית. היא תחזיר את *Set a 30-second timer*.

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### משימה - שימוש בפונקציית התרגום לתרגום טקסט

1. פתחו את הפרויקט `smart-timer` ב-VS Code אם הוא עדיין לא פתוח.

1. הטיימר החכם שלכם יוגדר עם 2 שפות - השפה של השרת ששימשה לאימון LUIS (אותה שפה משמשת גם לבניית ההודעות שמדברות עם המשתמש), והשפה שבה מדבר המשתמש. עדכנו את הקבוע `LANGUAGE` בקובץ הכותרת `config.h` לשפה שבה ידבר המשתמש, והוסיפו קבוע חדש בשם `SERVER_LANGUAGE` עבור השפה ששימשה לאימון LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    החליפו `<user language>` בשם האזור של השפה שבה תדברו, לדוגמה `fr-FR` עבור צרפתית, או `zn-HK` עבור קנטונזית.

    החליפו `<server language>` בשם האזור של השפה ששימשה לאימון LUIS.

    ניתן למצוא רשימה של השפות הנתמכות ושמות האזורים שלהן בתיעוד [Language and voice support במיקרוסופט](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 אם אינכם דוברים מספר שפות, תוכלו להשתמש בשירות כמו [Bing Translate](https://www.bing.com/translator) או [Google Translate](https://translate.google.com) כדי לתרגם מהשפה המועדפת עליכם לשפה אחרת. שירותים אלו יכולים גם להשמיע את הטקסט המתורגם.
    >
    > לדוגמה, אם אימנתם את LUIS באנגלית, אך רוצים להשתמש בצרפתית כשפת המשתמש, תוכלו לתרגם משפטים כמו "set a 2 minute and 27 second timer" מאנגלית לצרפתית באמצעות Bing Translate, ואז להשתמש בכפתור **Listen translation** כדי להשמיע את התרגום למיקרופון שלכם.
    >
    > ![כפתור השמעת התרגום ב-Bing Translate](../../../../../translated_images/he/bing-translate.348aa796d6efe2a9.webp)

1. הוסיפו את מפתח ה-API של שירות התרגום והמיקום מתחת ל-`SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    החליפו `<KEY>` במפתח ה-API של משאב שירות התרגום שלכם. החליפו `<LOCATION>` במיקום שבו יצרתם את משאב שירות התרגום.

1. הוסיפו את כתובת ה-URL של טריגר התרגום מתחת ל-`VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    החליפו `<URL>` בכתובת ה-URL של טריגר ה-HTTP `translate-text` באפליקציית הפונקציות שלכם. זה יהיה זהה לערך של `TEXT_TO_TIMER_FUNCTION_URL`, למעט שם הפונקציה `translate-text` במקום `text-to-timer`.

1. הוסיפו קובץ חדש לתיקיית `src` בשם `text_translator.h`.

1. קובץ הכותרת החדש `text_translator.h` יכיל מחלקה לתרגום טקסט. הוסיפו את הקוד הבא לקובץ זה כדי להכריז על המחלקה:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    זה מכריז על המחלקה `TextTranslator`, יחד עם מופע של מחלקה זו. למחלקה יש שדה יחיד עבור לקוח ה-WiFi.

1. לחלק ה-`public` של מחלקה זו, הוסיפו שיטה לתרגום טקסט:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    שיטה זו מקבלת את השפה שממנה מתרגמים ואת השפה שאליה מתרגמים. בעת טיפול בדיבור, הדיבור יתורגם משפת המשתמש לשפת שרת LUIS, ובעת מתן תגובות הוא יתורגם משפת שרת LUIS לשפת המשתמש.

1. בשיטה זו, הוסיפו קוד לבניית גוף JSON המכיל את הטקסט לתרגום והשפות:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. מתחת לזה, הוסיפו את הקוד הבא לשליחת הגוף לאפליקציית הפונקציות ללא שרת:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. לאחר מכן, הוסיפו קוד לקבלת התגובה:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. לבסוף, הוסיפו קוד לסגירת החיבור והחזרת הטקסט המתורגם:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### משימה - תרגום הדיבור המוכר והתגובות

1. פתחו את הקובץ `main.cpp`.

1. הוסיפו הנחיית include בראש הקובץ עבור קובץ הכותרת של מחלקת `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. הטקסט שנאמר כאשר טיימר מוגדר או פג תוקפו צריך להיות מתורגם. לשם כך, הוסיפו את השורה הבאה כקו הראשון של הפונקציה `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    זה יתרגם את הטקסט לשפת המשתמש.

1. בפונקציה `processAudio`, הטקסט נשלף מהאודיו שנלכד עם הקריאה `String text = speechToText.convertSpeechToText();`. לאחר קריאה זו, תרגמו את הטקסט:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    זה יתרגם את הטקסט משפת המשתמש לשפה שבה נעשה שימוש בשרת.

1. בנו את הקוד הזה, העלו אותו ל-Wio Terminal שלכם ובדקו אותו דרך המוניטור הסדרתי. ברגע שתראו `Ready` במוניטור הסדרתי, לחצו על כפתור C (הכפתור בצד שמאל, הקרוב ביותר למתג ההפעלה), ודברו. ודאו שאפליקציית הפונקציות שלכם פועלת, ובקשו טיימר בשפת המשתמש, או על ידי דיבור בשפה זו בעצמכם, או באמצעות אפליקציית תרגום.

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 ניתן למצוא את הקוד הזה בתיקיית [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 תוכנית הטיימר הרב-לשונית שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. אנו לא נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.