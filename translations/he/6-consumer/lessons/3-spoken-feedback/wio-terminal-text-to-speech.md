<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T22:30:35+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "he"
}
-->
# טקסט לדיבור - Wio Terminal

בחלק זה של השיעור, תבצעו המרה של טקסט לדיבור כדי לספק משוב קולי.

## טקסט לדיבור

ערכת ה-SDK של שירותי הדיבור שבה השתמשתם בשיעור הקודם להמרת דיבור לטקסט יכולה לשמש גם להמרת טקסט לדיבור.

## קבלת רשימת קולות

כאשר מבקשים דיבור, יש לספק את הקול שבו יש להשתמש, שכן ניתן לייצר דיבור באמצעות מגוון קולות שונים. כל שפה תומכת במגוון קולות, וניתן לקבל את רשימת הקולות הנתמכים לכל שפה באמצעות ערכת ה-SDK של שירותי הדיבור. כאן נכנסות מגבלות המיקרו-בקרים - הקריאה לקבלת רשימת הקולות הנתמכים על ידי שירותי הטקסט לדיבור היא מסמך JSON בגודל של מעל 77KB, גדול מדי לעיבוד על ידי Wio Terminal. נכון לזמן הכתיבה, הרשימה המלאה מכילה 215 קולות, שכל אחד מהם מוגדר על ידי מסמך JSON כמו הבא:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

JSON זה מתאר את קול **Aria**, שיש לו סגנונות קוליים מרובים. כל מה שנדרש להמרת טקסט לדיבור הוא ה-shortname, `en-US-AriaNeural`.

במקום להוריד ולפענח את הרשימה המלאה על המיקרו-בקר, תצטרכו לכתוב קוד serverless נוסף כדי לאחזר את רשימת הקולות עבור השפה שבה אתם משתמשים, ולקרוא לזה מ-Wio Terminal שלכם. הקוד שלכם יוכל אז לבחור קול מתאים מהרשימה, כמו הראשון שהוא מוצא.

### משימה - יצירת פונקציה serverless לקבלת רשימת קולות

1. פתחו את פרויקט `smart-timer-trigger` ב-VS Code, ופתחו את הטרמינל תוך וידוא שהסביבה הווירטואלית מופעלת. אם לא, סגרו וצרו מחדש את הטרמינל.

1. פתחו את קובץ `local.settings.json` והוסיפו הגדרות עבור מפתח ה-API של שירותי הדיבור והמיקום:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    החליפו `<key>` במפתח ה-API של משאב שירותי הדיבור שלכם. החליפו `<location>` במיקום שבו יצרתם את משאב שירותי הדיבור.

1. הוסיפו טריגר HTTP חדש לאפליקציה זו בשם `get-voices` באמצעות הפקודה הבאה מתוך הטרמינל של VS Code בתיקיית השורש של פרויקט אפליקציית הפונקציות:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    פעולה זו תיצור טריגר HTTP בשם `get-voices`.

1. החליפו את תוכן הקובץ `__init__.py` בתיקיית `get-voices` בתוכן הבא:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    קוד זה מבצע בקשת HTTP לנקודת הקצה כדי לקבל את הקולות. רשימת הקולות היא בלוק JSON גדול עם קולות לכל השפות, כך שהקולות עבור השפה שנשלחה בגוף הבקשה מסוננים, ואז ה-shortname נשלף ומוחזר כרשימת JSON. ה-shortname הוא הערך הדרוש להמרת טקסט לדיבור, ולכן רק ערך זה מוחזר.

    > 💁 ניתן לשנות את המסנן לפי הצורך כדי לבחור רק את הקולות הרצויים.

    פעולה זו מצמצמת את גודל הנתונים מ-77KB (נכון לזמן הכתיבה) למסמך JSON קטן בהרבה. לדוגמה, עבור קולות אמריקאים זה 408 בתים.

1. הריצו את אפליקציית הפונקציות שלכם מקומית. תוכלו לקרוא לה באמצעות כלי כמו curl באותו אופן שבו בדקתם את טריגר ה-HTTP `text-to-timer`. ודאו שאתם מעבירים את השפה כגוף JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    החליפו `<language>` בשפה שלכם, כמו `en-GB` או `zh-CN`.

> 💁 ניתן למצוא קוד זה בתיקיית [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### משימה - אחזור הקול מ-Wio Terminal שלכם

1. פתחו את פרויקט `smart-timer` ב-VS Code אם הוא לא פתוח כבר.

1. פתחו את קובץ הכותרת `config.h` והוסיפו את ה-URL של אפליקציית הפונקציות שלכם:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    החליפו `<URL>` ב-URL של טריגר ה-HTTP `get-voices` באפליקציית הפונקציות שלכם. זה יהיה זהה לערך של `TEXT_TO_TIMER_FUNCTION_URL`, למעט שם הפונקציה `get-voices` במקום `text-to-timer`.

1. צרו קובץ חדש בתיקיית `src` בשם `text_to_speech.h`. קובץ זה ישמש להגדרת מחלקה להמרת טקסט לדיבור.

1. הוסיפו את הוראות ה-include הבאות לראש הקובץ החדש `text_to_speech.h`:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. הוסיפו את הקוד הבא מתחת לזה כדי להכריז על מחלקת `TextToSpeech`, יחד עם מופע שניתן להשתמש בו בשאר האפליקציה:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. כדי לקרוא לאפליקציית הפונקציות שלכם, עליכם להכריז על WiFi client. הוסיפו את הקוד הבא לחלק ה-private של המחלקה:

    ```cpp
    WiFiClient _client;
    ```

1. בחלק ה-private, הוסיפו שדה עבור הקול שנבחר:

    ```cpp
    String _voice;
    ```

1. לחלק ה-public, הוסיפו פונקציית `init` שתשיג את הקול הראשון:

    ```cpp
    void init()
    {
    }
    ```

1. כדי להשיג את הקולות, יש לשלוח מסמך JSON לאפליקציית הפונקציות עם השפה. הוסיפו את הקוד הבא לפונקציית `init` כדי ליצור מסמך JSON זה:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. לאחר מכן, צרו `HTTPClient`, ואז השתמשו בו כדי לקרוא לאפליקציית הפונקציות כדי להשיג את הקולות, תוך שליחת מסמך ה-JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. מתחת לזה, הוסיפו קוד לבדוק את קוד התגובה, ואם הוא 200 (הצלחה), אז שלפו את רשימת הקולות, ואחזרו את הראשון מהרשימה:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. לאחר מכן, סיימו את חיבור ה-HTTP client:

    ```cpp
    httpClient.end();
    ```

1. פתחו את הקובץ `main.cpp`, והוסיפו את הוראת ה-include הבאה בראש כדי לכלול את קובץ הכותרת החדש:

    ```cpp
    #include "text_to_speech.h"
    ```

1. בפונקציית `setup`, מתחת לקריאה ל-`speechToText.init();`, הוסיפו את השורה הבאה כדי לאתחל את מחלקת `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. בנו את הקוד הזה, העלו אותו ל-Wio Terminal שלכם ובדקו אותו דרך ה-serial monitor. ודאו שאפליקציית הפונקציות שלכם פועלת.

    תראו את רשימת הקולות הזמינים שהוחזרה מאפליקציית הפונקציות, יחד עם הקול שנבחר.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## המרת טקסט לדיבור

לאחר שיש לכם קול לשימוש, ניתן להשתמש בו להמרת טקסט לדיבור. אותן מגבלות זיכרון עם קולות חלות גם כאשר ממירים דיבור לטקסט, ולכן תצטרכו לכתוב את הדיבור לכרטיס SD כדי שיושמע דרך ה-ReSpeaker.

> 💁 בשיעורים קודמים בפרויקט זה השתמשתם בזיכרון פלאש לאחסון דיבור שנקלט מהמיקרופון. שיעור זה משתמש בכרטיס SD מכיוון שקל יותר להשמיע ממנו אודיו באמצעות ספריות האודיו של Seeed.

יש גם מגבלה נוספת שיש לקחת בחשבון, נתוני האודיו הזמינים משירות הדיבור והפורמטים שה-Wio Terminal תומך בהם. בניגוד למחשבים מלאים, ספריות האודיו למיקרו-בקרים יכולות להיות מוגבלות מאוד בפורמטים שהן תומכות בהם. לדוגמה, ספריית Seeed Arduino Audio שיכולה להשמיע צליל דרך ה-ReSpeaker תומכת רק באודיו בקצב דגימה של 44.1KHz. שירותי הדיבור של Azure יכולים לספק אודיו במספר פורמטים, אך אף אחד מהם לא משתמש בקצב דגימה זה, הם מספקים רק 8KHz, 16KHz, 24KHz ו-48KHz. משמעות הדבר היא שיש לבצע דגימה מחדש ל-44.1KHz, דבר שידרוש יותר משאבים ממה שיש ל-Wio Terminal, במיוחד זיכרון.

כאשר יש צורך לטפל בנתונים כאלה, לעיתים קרובות עדיף להשתמש בקוד serverless, במיוחד אם הנתונים מתקבלים דרך קריאה אינטרנטית. Wio Terminal יכול לקרוא לפונקציה serverless, להעביר את הטקסט להמרה, והפונקציה serverless יכולה גם לקרוא לשירות הדיבור להמרת טקסט לדיבור, וגם לבצע דגימה מחדש של האודיו לקצב הדגימה הנדרש. לאחר מכן היא יכולה להחזיר את האודיו בצורה שה-Wio Terminal צריך כדי לאחסן אותו על כרטיס SD ולהשמיע אותו דרך ה-ReSpeaker.

### משימה - יצירת פונקציה serverless להמרת טקסט לדיבור

1. פתחו את פרויקט `smart-timer-trigger` ב-VS Code, ופתחו את הטרמינל תוך וידוא שהסביבה הווירטואלית מופעלת. אם לא, סגרו וצרו מחדש את הטרמינל.

1. הוסיפו טריגר HTTP חדש לאפליקציה זו בשם `text-to-speech` באמצעות הפקודה הבאה מתוך הטרמינל של VS Code בתיקיית השורש של פרויקט אפליקציית הפונקציות:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    פעולה זו תיצור טריגר HTTP בשם `text-to-speech`.

1. חבילת ה-Pip [librosa](https://librosa.org) כוללת פונקציות לדגימה מחדש של אודיו, לכן הוסיפו אותה לקובץ `requirements.txt`:

    ```sh
    librosa
    ```

    לאחר שהוספתם זאת, התקינו את חבילות ה-Pip באמצעות הפקודה הבאה מתוך הטרמינל של VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ אם אתם משתמשים ב-Linux, כולל Raspberry Pi OS, ייתכן שתצטרכו להתקין `libsndfile` באמצעות הפקודה הבאה:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. כדי להמיר טקסט לדיבור, אינכם יכולים להשתמש ישירות במפתח ה-API של שירותי הדיבור, אלא עליכם לבקש אסימון גישה, תוך שימוש במפתח ה-API לאימות בקשת האסימון. פתחו את הקובץ `__init__.py` מתיקיית `text-to-speech` והחליפו את כל הקוד שבו בקוד הבא:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    קוד זה מגדיר קבועים עבור המיקום ומפתח הדיבור שייקראו מההגדרות. לאחר מכן הוא מגדיר את הפונקציה `get_access_token` שתשיג אסימון גישה לשירות הדיבור.

1. מתחת לקוד זה, הוסיפו את הקוד הבא:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    קוד זה מגדיר את טריגר ה-HTTP שממיר את הטקסט לדיבור. הוא שולף את הטקסט להמרה, השפה והקול מגוף ה-JSON שנשלח בבקשה, בונה SSML לבקשת הדיבור, ואז קורא ל-REST API הרלוונטי תוך אימות באמצעות אסימון הגישה. קריאת REST API זו מחזירה את האודיו מקודד כקובץ WAV מונו 16-ביט, 48KHz, כפי שמוגדר על ידי הערך של `playback_format`, שנשלח לקריאת REST API.

    לאחר מכן, האודיו עובר דגימה מחדש על ידי `librosa` מקצב דגימה של 48KHz לקצב דגימה של 44.1KHz, ואז האודיו הזה נשמר למאגר בינארי שמוחזר.

1. הריצו את אפליקציית הפונקציות שלכם מקומית, או פרסמו אותה לענן. תוכלו לקרוא לה באמצעות כלי כמו curl באותו אופן שבו בדקתם את טריגר ה-HTTP `text-to-timer`. ודאו שאתם מעבירים את השפה, הקול והטקסט כגוף JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    החליפו `<language>` בשפה שלכם, כמו `en-GB` או `zh-CN`. החליפו `<voice>` בקול שבו אתם רוצים להשתמש. החליפו `<text>` בטקסט שאתם רוצים להמיר לדיבור. תוכלו לשמור את הפלט לקובץ ולהשמיע אותו עם כל נגן אודיו שתומך בקבצי WAV.

    לדוגמה, כדי להמיר "Hello" לדיבור באמצעות אנגלית אמריקאית עם קול Jenny Neural, כאשר אפליקציית הפונקציות פועלת מקומית, תוכלו להשתמש בפקודת curl הבאה:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    פעולה זו תשמור את האודיו בקובץ `hello.wav` בתיקייה הנוכחית.

> 💁 ניתן למצוא קוד זה בתיקיית [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### משימה - אחזור הדיבור מ-Wio Terminal שלכם

1. פתחו את פרויקט `smart-timer` ב-VS Code אם הוא לא פתוח כבר.

1. פתחו את קובץ הכותרת `config.h` והוסיפו את ה-URL של אפליקציית הפונקציות שלכם:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    החליפו `<URL>` ב-URL של טריגר ה-HTTP `text-to-speech` באפליקציית הפונקציות שלכם. זה יהיה זהה לערך של `TEXT_TO_TIMER_FUNCTION_URL`, למעט שם הפונקציה `text-to-speech` במקום `text-to-timer`.

1. פתחו את קובץ הכותרת `text_to_speech.h`, והוסיפו את השיטה הבאה לחלק ה-public של מחלקת `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. לשיטת `convertTextToSpeech`, הוסיפו את הקוד הבא ליצירת ה-JSON לשליחה לאפליקציית הפונקציות:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    פעולה זו כותבת את השפה, הקול והטקסט למסמך JSON, ואז ממירה אותו למחרוזת.

1. מתחת לזה, הוסיפו את הקוד הבא לקריאה לאפליקציית הפונקציות:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    פעולה זו יוצרת HTTPClient, ואז מבצעת בקשת POST באמצעות מסמך ה-JSON לטריגר ה-HTTP של טקסט לדיבור.

1. אם הקריאה מצליחה, הנתונים הבינאריים הגולמיים שהוחזרו מקריאת אפליקציית הפונקציות יכולים להיות מוזרמים לקובץ בכרטיס ה-SD. הוסיפו את הקוד הבא כדי לעשות זאת:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    קוד זה בודק את התגובה, ואם היא 200 (הצלחה), הנתונים הבינאריים מוזרמים לקובץ בשורש כרטיס ה-SD בשם `SPEECH.WAV`.

1. בסוף שיטה זו, סגרו את חיבור ה-HTTP:

    ```cpp
    httpClient.end();
    ```

1. כעת ניתן להמיר את הטקסט לדיבור. בקובץ `main.cpp`, הוסיפו את השורה הבאה לסוף פונקציית `say` כדי להמיר את הטקסט לדיבור לאודיו:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### משימה - נגן אודיו מה-Wio Terminal שלך

**בקרוב**

## פריסת אפליקציית הפונקציות שלך לענן

הסיבה להרצת אפליקציית הפונקציות באופן מקומי היא שהחבילה `librosa` של Pip בלינוקס תלויה בספרייה שאינה מותקנת כברירת מחדל, ויש להתקין אותה לפני שאפליקציית הפונקציות תוכל לפעול. אפליקציות פונקציות הן ללא שרתים - אין שרתים שניתן לנהל בעצמך, ולכן אין דרך להתקין את הספרייה הזו מראש.

הדרך לעשות זאת היא במקום זאת לפרוס את אפליקציית הפונקציות שלך באמצעות מיכל Docker. מיכל זה נפרס על ידי הענן בכל פעם שיש צורך להפעיל מופע חדש של אפליקציית הפונקציות שלך (כגון כאשר הביקוש עולה על המשאבים הזמינים, או אם אפליקציית הפונקציות לא הייתה בשימוש זמן מה ונסגרה).

תוכל למצוא את ההוראות להקמת אפליקציית פונקציות ולפריסה באמצעות Docker בתיעוד [יצירת פונקציה בלינוקס באמצעות מיכל מותאם אישית ב-Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

לאחר שהפריסה הושלמה, תוכל להעביר את קוד ה-Wio Terminal שלך כדי לגשת לפונקציה זו:

1. הוסף את תעודת Azure Functions ל-`config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. שנה את כל ההכללות של `<WiFiClient.h>` ל-`<WiFiClientSecure.h>`.

1. שנה את כל השדות של `WiFiClient` ל-`WiFiClientSecure`.

1. בכל מחלקה שיש לה שדה `WiFiClientSecure`, הוסף בנאי והגדר את התעודה בתוך הבנאי:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). למרות שאנו שואפים לדיוק, יש לקחת בחשבון שתרגומים אוטומטיים עשויים להכיל שגיאות או אי דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור סמכותי. עבור מידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי אדם. איננו נושאים באחריות לאי הבנות או לפרשנויות שגויות הנובעות משימוש בתרגום זה.