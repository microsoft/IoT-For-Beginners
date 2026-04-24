# பேச்சை மொழிபெயர்க்கவும் - Wio Terminal

இந்த பாடத்தின் இந்த பகுதியில், மொழிபெயர்ப்பாளர் சேவையைப் பயன்படுத்தி உரையை மொழிபெயர்க்க குறியீட்டை எழுதுவீர்கள்.

## மொழிபெயர்ப்பாளர் சேவையைப் பயன்படுத்தி உரையை பேச்சாக மாற்றவும்

Speech service REST API நேரடி மொழிபெயர்ப்புகளை ஆதரிக்காது, அதற்கு பதிலாக Speech to Text சேவையால் உருவாக்கப்பட்ட உரை மற்றும் பேசப்பட்ட பதிலின் உரையை மொழிபெயர்க்க Translator சேவையைப் பயன்படுத்தலாம். இந்த சேவைக்கு REST API உள்ளது, ஆனால் இதைப் பயன்படுத்த எளிதாக்க, functions app-இல் HTTP trigger மூலம் இதைச் சுற்றி ஒரு அடுக்கு உருவாக்கப்படும்.

### பணிகள் - உரையை மொழிபெயர்க்க ஒரு serverless function உருவாக்கவும்

1. உங்கள் `smart-timer-trigger` திட்டத்தை VS Code-இல் திறக்கவும், மற்றும் terminal-ஐ திறக்கவும், virtual environment செயல்படுத்தப்பட்டுள்ளதா என்பதை உறுதிப்படுத்தவும். இல்லையெனில், terminal-ஐ முடித்து மீண்டும் உருவாக்கவும்.

1. `local.settings.json` கோப்பைத் திறந்து, translator API key மற்றும் location-க்கு அமைப்புகளைச் சேர்க்கவும்:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` ஐ உங்கள் translator service resource-க்கு API key-ஆக மாற்றவும். `<location>` ஐ translator service resource உருவாக்கிய போது நீங்கள் பயன்படுத்திய இடத்துடன் மாற்றவும்.

1. இந்த app-க்கு `translate-text` என்ற புதிய HTTP trigger-ஐ கீழே உள்ள கட்டளையை functions app திட்டத்தின் root folder-இல் உள்ள VS Code terminal-இல் இருந்து பயன்படுத்தி சேர்க்கவும்:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    இது `translate-text` என்ற HTTP trigger-ஐ உருவாக்கும்.

1. `translate-text` கோப்பகத்தில் உள்ள `__init__.py` கோப்பின் உள்ளடக்கத்தை கீழே உள்ளவற்றால் மாற்றவும்:

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

    இந்த குறியீடு HTTP கோரிக்கையிலிருந்து உரை மற்றும் மொழிகளை எடுக்கிறது. பின்னர், translator REST API-க்கு கோரிக்கையைச் செய்கிறது, URL-க்கு மொழிகளை அளவுருக்களாகவும், மொழிபெயர்க்க உரையை body-ஆகவும் அனுப்புகிறது. இறுதியாக, மொழிபெயர்ப்பு திருப்பி அனுப்பப்படுகிறது.

1. உங்கள் function app-ஐ உள்ளூரில் இயக்கவும். பின்னர், curl போன்ற ஒரு கருவியைப் பயன்படுத்தி உங்கள் `text-to-timer` HTTP trigger-ஐ சோதித்தது போல இதை அழைக்கலாம். JSON body-யாக மொழிபெயர்க்க உரை மற்றும் மொழிகளை அனுப்புவதை உறுதிப்படுத்தவும்:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    இந்த எடுத்துக்காட்டு *Définir une minuterie de 30 secondes* என்பதைக் பிரெஞ்சில் இருந்து US ஆங்கிலத்திற்கு மொழிபெயர்க்கிறது. இது *Set a 30-second timer* என்பதை திருப்பி அனுப்பும்.

> 💁 இந்த குறியீட்டை [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) கோப்பகத்தில் காணலாம்.

### பணிகள் - உரையை மொழிபெயர்க்க translator function-ஐ பயன்படுத்தவும்

1. `smart-timer` திட்டத்தை VS Code-இல் திறக்கவும், இது ஏற்கனவே திறக்கப்படவில்லை என்றால்.

1. உங்கள் smart timer-க்கு 2 மொழிகள் அமைக்கப்படும் - LUIS-ஐ பயிற்றுவிக்க பயன்படுத்தப்பட்ட server மொழி (பயனாளருடன் பேசுவதற்கான செய்திகளை உருவாக்கவும் இதே மொழி பயன்படுத்தப்படும்), மற்றும் பயனர் பேசும் மொழி. `config.h` header கோப்பில் உள்ள `LANGUAGE` நிலையானத்தைப் பயனர் பேசும் மொழியாக மாற்றவும், மேலும் LUIS-ஐ பயிற்றுவிக்க பயன்படுத்தப்பட்ட மொழிக்கான `SERVER_LANGUAGE` என்ற புதிய நிலையானத்தைச் சேர்க்கவும்:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` ஐ நீங்கள் பேசும் மொழிக்கான locale பெயருடன் மாற்றவும், உதாரணமாக பிரெஞ்சுக்கான `fr-FR`, அல்லது கான்டோனீஸுக்கான `zn-HK`.

    `<server language>` ஐ LUIS-ஐ பயிற்றுவிக்க பயன்படுத்தப்பட்ட மொழிக்கான locale பெயருடன் மாற்றவும்.

    Microsoft docs-இல் உள்ள [Language and voice support documentation](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) இல் ஆதரிக்கப்படும் மொழிகள் மற்றும் அவற்றின் locale பெயர்களின் பட்டியலைக் காணலாம்.

    > 💁 நீங்கள் பல மொழிகளைப் பேசவில்லை என்றால், [Bing Translate](https://www.bing.com/translator) அல்லது [Google Translate](https://translate.google.com) போன்ற சேவையைப் பயன்படுத்தி உங்கள் விருப்பமான மொழியிலிருந்து மற்றொரு மொழிக்கு மொழிபெயர்க்கலாம். இந்த சேவைகள் பின்னர் மொழிபெயர்க்கப்பட்ட உரையின் ஆடியோவை இயக்கலாம்.
    >
    > உதாரணமாக, நீங்கள் LUIS-ஐ ஆங்கிலத்தில் பயிற்றுவிக்கிறீர்கள், ஆனால் பயனர் மொழியாக பிரெஞ்சை பயன்படுத்த விரும்புகிறீர்கள் என்றால், "set a 2 minute and 27 second timer" போன்ற வாக்கியங்களை Bing Translate-ஐப் பயன்படுத்தி ஆங்கிலத்திலிருந்து பிரெஞ்சுக்கு மொழிபெயர்க்கலாம், பின்னர் **Listen translation** பொத்தானை பயன்படுத்தி மொழிபெயர்ப்பை உங்கள் மைக்ரோஃபோனில் பேசலாம்.
    >
    > ![Bing Translate-இல் Listen translation பொத்தான்](../../../../../translated_images/ta/bing-translate.348aa796d6efe2a9.webp)

1. `SPEECH_LOCATION` கீழே translator API key மற்றும் location-ஐச் சேர்க்கவும்:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` ஐ உங்கள் translator service resource-க்கு API key-ஆக மாற்றவும். `<LOCATION>` ஐ translator service resource உருவாக்கிய போது நீங்கள் பயன்படுத்திய இடத்துடன் மாற்றவும்.

1. `VOICE_URL` கீழே translator trigger URL-ஐச் சேர்க்கவும்:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ஐ உங்கள் function app-இல் `translate-text` HTTP trigger-க்கு URL-ஆக மாற்றவும். இது `TEXT_TO_TIMER_FUNCTION_URL`-க்கு மதிப்பாக இருக்கும், ஆனால் `text-to-timer` என்பதற்குப் பதிலாக `translate-text` என்ற function பெயருடன் இருக்கும்.

1. `src` கோப்பகத்தில் புதிய கோப்பைச் சேர்க்கவும், இதற்கு `text_translator.h` என்று பெயரிடவும்.

1. இந்த புதிய `text_translator.h` header கோப்பில் உரையை மொழிபெயர்க்க ஒரு class-ஐ உருவாக்கவும். இந்த class-ஐ அறிவிக்க கீழே உள்ளவற்றைச் சேர்க்கவும்:

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

    இது `TextTranslator` class-ஐ அறிவிக்கிறது, மற்றும் இந்த class-இன் ஒரு instance-ஐ உருவாக்குகிறது. class-க்கு WiFi client-க்கு ஒரு single field உள்ளது.

1. இந்த class-இன் `public` பிரிவில், உரையை மொழிபெயர்க்க ஒரு முறைசெயலியைச் சேர்க்கவும்:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    இந்த முறைசெயலி எந்த மொழியில் இருந்து மொழிபெயர்க்க வேண்டும், மற்றும் எந்த மொழிக்கு மொழிபெயர்க்க வேண்டும் என்பதை எடுத்துக்கொள்கிறது. பேச்சைச் செயல்படுத்தும்போது, பேச்சு பயனர் மொழியில் இருந்து LUIS server மொழிக்கு மொழிபெயர்க்கப்படும், மற்றும் பதில்களை வழங்கும்போது, LUIS server மொழியில் இருந்து பயனர் மொழிக்கு மொழிபெயர்க்கப்படும்.

1. இந்த முறைசெயலியில், மொழிபெயர்க்க உரை மற்றும் மொழிகளை உள்ளடக்கிய JSON body-ஐ உருவாக்க குறியீட்டைச் சேர்க்கவும்:

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

1. இதற்கு கீழே, serverless function app-க்கு body-ஐ அனுப்ப குறியீட்டைச் சேர்க்கவும்:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. அடுத்ததாக, பதிலைப் பெற குறியீட்டைச் சேர்க்கவும்:

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

1. இறுதியாக, இணைப்பை மூடவும் மற்றும் மொழிபெயர்க்கப்பட்ட உரையை திருப்பி அனுப்பவும்:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### பணிகள் - அடையாளம் காணப்பட்ட பேச்சு மற்றும் பதில்களை மொழிபெயர்க்கவும்

1. `main.cpp` கோப்பைத் திறக்கவும்.

1. `TextTranslator` class header கோப்புக்கான include directive-ஐ கோப்பின் மேல் சேர்க்கவும்:

    ```cpp
    #include "text_translator.h"
    ```

1. ஒரு timer அமைக்கப்பட்டால் அல்லது காலாவதியாக இருந்தால் கூறப்படும் உரை மொழிபெயர்க்கப்பட வேண்டும். இதைச் செய்ய, `say` function-இன் முதல் வரியாக கீழே உள்ளவற்றைச் சேர்க்கவும்:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    இது உரையை பயனர் மொழிக்கு மொழிபெயர்க்கும்.

1. `processAudio` function-இல், `String text = speechToText.convertSpeechToText();` அழைப்புடன் captured audio-இலிருந்து உரை பெறப்படுகிறது. இந்த அழைப்புக்குப் பிறகு, உரையை மொழிபெயர்க்கவும்:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    இது உரையை பயனர் மொழியில் இருந்து server-ல் பயன்படுத்தப்படும் மொழிக்கு மொழிபெயர்க்கும்.

1. இந்த குறியீட்டை உருவாக்கவும், அதை உங்கள் Wio Terminal-க்கு பதிவேற்றவும், மற்றும் serial monitor மூலம் சோதிக்கவும். serial monitor-இல் `Ready` என்பதைப் பார்க்கும் போது, C பொத்தானை அழுத்தவும் (power switch-க்கு அருகிலுள்ள இடது பக்கம்), மற்றும் பேசவும். உங்கள் function app இயங்குகிறதா என்பதை உறுதிப்படுத்தவும், மற்றும் பயனர் மொழியில் timer-ஐ கோரவும், நீங்கள் அந்த மொழியைப் பேசுவதன் மூலம் அல்லது மொழிபெயர்ப்பு app-ஐப் பயன்படுத்துவதன் மூலம்.

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

> 💁 இந்த குறியீட்டை [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) கோப்பகத்தில் காணலாம்.

😀 உங்கள் பல மொழி timer திட்டம் வெற்றிகரமாக முடிந்தது!

---

**குறிப்பு**:  
இந்த ஆவணம் [Co-op Translator](https://github.com/Azure/co-op-translator) என்ற AI மொழிபெயர்ப்பு சேவையை பயன்படுத்தி மொழிபெயர்க்கப்பட்டுள்ளது. நாங்கள் துல்லியத்திற்காக முயற்சிக்கின்றோம், ஆனால் தானியங்கி மொழிபெயர்ப்புகளில் பிழைகள் அல்லது தவறான தகவல்கள் இருக்கக்கூடும் என்பதை கவனத்தில் கொள்ளவும். அதன் தாய்மொழியில் உள்ள மூல ஆவணம் அதிகாரப்பூர்வ ஆதாரமாக கருதப்பட வேண்டும். முக்கியமான தகவல்களுக்கு, தொழில்முறை மனித மொழிபெயர்ப்பு பரிந்துரைக்கப்படுகிறது. இந்த மொழிபெயர்ப்பைப் பயன்படுத்துவதால் ஏற்படும் எந்த தவறான புரிதல்கள் அல்லது தவறான விளக்கங்களுக்கு நாங்கள் பொறுப்பல்ல.