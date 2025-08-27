<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T22:31:56+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "he"
}
-->
# טקסט לדיבור - מכשיר IoT וירטואלי

בחלק זה של השיעור, תכתבו קוד להמרת טקסט לדיבור באמצעות שירות הדיבור.

## המרת טקסט לדיבור

ערכת ה-SDK של שירותי הדיבור שבה השתמשתם בשיעור הקודם להמרת דיבור לטקסט, יכולה לשמש גם להמרת טקסט חזרה לדיבור. כאשר מבקשים דיבור, יש לספק את הקול שבו יש להשתמש, מכיוון שניתן לייצר דיבור באמצעות מגוון קולות שונים.

כל שפה תומכת במגוון קולות שונים, וניתן לקבל את רשימת הקולות הנתמכים לכל שפה מתוך ערכת ה-SDK של שירותי הדיבור.

### משימה - המרת טקסט לדיבור

1. פתחו את פרויקט `smart-timer` ב-VS Code, וודאו שהסביבה הווירטואלית נטענת במסוף.

1. ייבאו את `SpeechSynthesizer` מתוך החבילה `azure.cognitiveservices.speech` על ידי הוספתו לייבוא הקיים:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. מעל הפונקציה `say`, צרו תצורת דיבור לשימוש עם ה-speech synthesizer:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    תצורה זו משתמשת באותו מפתח API, מיקום ושפה שבהם השתמש ה-recognizer.

1. מתחת לכך, הוסיפו את הקוד הבא כדי לקבל קול ולהגדיר אותו בתצורת הדיבור:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    קוד זה מאחזר רשימה של כל הקולות הזמינים, ואז מוצא את הקול הראשון שתואם לשפה שבה משתמשים.

    > 💁 ניתן לקבל את הרשימה המלאה של הקולות הנתמכים מתוך [התיעוד על תמיכה בשפות וקולות ב-Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). אם ברצונכם להשתמש בקול מסוים, תוכלו להסיר את הפונקציה הזו ולהגדיר את הקול ישירות לשם הקול מתוך התיעוד. לדוגמה:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. עדכנו את התוכן של הפונקציה `say` כדי לייצר SSML לתגובה:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. מתחת לכך, עצרו את זיהוי הדיבור, השמיעו את ה-SSML, ואז הפעילו מחדש את הזיהוי:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    הזיהוי נעצר בזמן שהטקסט מושמע כדי למנוע מצב שבו ההכרזה על תחילת הטיימר תזוהה, תישלח ל-LUIS ותתפרש בטעות כבקשה להגדיר טיימר חדש.

    > 💁 תוכלו לבדוק זאת על ידי הוספת הערות לשורות שעוצרות ומפעילות מחדש את הזיהוי. הגדירו טיימר אחד, וייתכן שתגלו שההכרזה מגדירה טיימר חדש, מה שגורם להכרזה חדשה, שמובילה לטיימר חדש, וכך הלאה לנצח!

1. הפעילו את האפליקציה, וודאו שאפליקציית הפונקציות פועלת גם היא. הגדירו כמה טיימרים, ותשמעו תגובה קולית שאומרת שהטיימר שלכם הוגדר, ואז תגובה קולית נוספת כשהטיימר מסתיים.

> 💁 תוכלו למצוא את הקוד הזה בתיקייה [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 תוכנית הטיימר שלכם הייתה הצלחה!

---

**כתב ויתור**:  
מסמך זה תורגם באמצעות שירות תרגום מבוסס בינה מלאכותית [Co-op Translator](https://github.com/Azure/co-op-translator). בעוד שאנו שואפים לדיוק, יש להיות מודעים לכך שתרגומים אוטומטיים עשויים להכיל שגיאות או אי-דיוקים. המסמך המקורי בשפתו המקורית צריך להיחשב כמקור הסמכותי. למידע קריטי, מומלץ להשתמש בתרגום מקצועי על ידי בני אדם. איננו נושאים באחריות לכל אי-הבנה או פרשנות שגויה הנובעת משימוש בתרגום זה.