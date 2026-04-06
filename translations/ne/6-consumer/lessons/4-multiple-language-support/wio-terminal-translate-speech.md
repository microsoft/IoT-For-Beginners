# भाषण अनुवाद गर्नुहोस् - Wio Terminal

यस पाठको यस भागमा, तपाईं अनुवादक सेवाको प्रयोग गरेर पाठ अनुवाद गर्न कोड लेख्नुहुनेछ।

## अनुवादक सेवाको प्रयोग गरेर पाठलाई भाषणमा रूपान्तरण गर्नुहोस्

स्पीच सेवा REST API ले प्रत्यक्ष अनुवादलाई समर्थन गर्दैन। यसको सट्टा, तपाईं स्पीच टु टेक्स्ट सेवाले उत्पन्न गरेको पाठ र बोलेको प्रतिक्रियाको पाठ अनुवाद गर्न अनुवादक सेवाको प्रयोग गर्न सक्नुहुन्छ। यो सेवाले पाठ अनुवाद गर्न REST API प्रदान गर्दछ, तर यसलाई प्रयोग गर्न सजिलो बनाउन, यो तपाईंको फङ्क्सन एपमा अर्को HTTP ट्रिगरमा समेटिनेछ।

### कार्य - पाठ अनुवाद गर्न एक सर्भरलेस फङ्क्सन बनाउनुहोस्

1. आफ्नो `smart-timer-trigger` प्रोजेक्टलाई VS Code मा खोल्नुहोस्, र टर्मिनल खोल्नुहोस् सुनिश्चित गर्दै कि भर्चुअल वातावरण सक्रिय छ। यदि छैन भने, टर्मिनल बन्द गरेर पुनः सिर्जना गर्नुहोस्।

1. `local.settings.json` फाइल खोल्नुहोस् र अनुवादक API कुञ्जी र स्थानको लागि सेटिङहरू थप्नुहोस्:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` लाई तपाईंको अनुवादक सेवा स्रोतको लागि API कुञ्जीले प्रतिस्थापन गर्नुहोस्। `<location>` लाई तपाईंले अनुवादक सेवा स्रोत सिर्जना गर्दा प्रयोग गरेको स्थानले प्रतिस्थापन गर्नुहोस्।

1. यस एपमा `translate-text` नामको नयाँ HTTP ट्रिगर थप्नुहोस्। यसका लागि, VS Code टर्मिनलमा फङ्क्सन एप प्रोजेक्टको मूल फोल्डरभित्र निम्न आदेश चलाउनुहोस्:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    यसले `translate-text` नामको HTTP ट्रिगर सिर्जना गर्नेछ।

1. `translate-text` फोल्डरको `__init__.py` फाइलको सामग्रीलाई निम्नसँग प्रतिस्थापन गर्नुहोस्:

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

    यो कोडले HTTP अनुरोधबाट पाठ र भाषाहरू निकाल्छ। त्यसपछि यो अनुवादक REST API मा अनुरोध गर्छ, URL को लागि भाषाहरूलाई प्यारामिटरको रूपमा र अनुवाद गर्न पाठलाई बडीको रूपमा पास गर्दै। अन्ततः, अनुवाद फर्काइन्छ।

1. आफ्नो फङ्क्सन एपलाई स्थानीय रूपमा चलाउनुहोस्। त्यसपछि तपाईं यसलाई curl जस्तो उपकरण प्रयोग गरेर परीक्षण गर्न सक्नुहुन्छ, ठीक त्यस्तै जसरी तपाईंले `text-to-timer` HTTP ट्रिगर परीक्षण गर्नुभयो। अनुवाद गर्न पाठ र भाषाहरू JSON बडीको रूपमा पास गर्न सुनिश्चित गर्नुहोस्:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    यो उदाहरणले *Définir une minuterie de 30 secondes* लाई फ्रेन्चबाट अमेरिकी अंग्रेजीमा अनुवाद गर्दछ। यसले *Set a 30-second timer* फर्काउनेछ।

> 💁 तपाईं यो कोड [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) फोल्डरमा पाउन सक्नुहुन्छ।

### कार्य - अनुवादक फङ्क्सन प्रयोग गरेर पाठ अनुवाद गर्नुहोस्

1. यदि `smart-timer` प्रोजेक्ट VS Code मा खुला छैन भने यसलाई खोल्नुहोस्।

1. तपाईंको स्मार्ट टाइमरमा 2 भाषा सेट हुनेछ - LUIS प्रशिक्षण गर्न प्रयोग गरिएको सर्भरको भाषा (उही भाषा प्रयोगकर्तासँग बोल्न सन्देश निर्माण गर्न प्रयोग गरिन्छ), र प्रयोगकर्ताले बोलेको भाषा। `config.h` हेडर फाइलमा `LANGUAGE` स्थिरांकलाई प्रयोगकर्ताले बोल्ने भाषामा अपडेट गर्नुहोस्, र `SERVER_LANGUAGE` नामको नयाँ स्थिरांक थप्नुहोस् जुन LUIS प्रशिक्षण गर्न प्रयोग गरिएको भाषाको लागि हो:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` लाई तपाईं बोल्ने भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्, उदाहरणका लागि फ्रेन्चको लागि `fr-FR`, वा क्यान्टोनिजको लागि `zn-HK`।

    `<server language>` लाई LUIS प्रशिक्षण गर्न प्रयोग गरिएको भाषाको लोकेल नामले प्रतिस्थापन गर्नुहोस्।

    तपाईं समर्थित भाषाहरू र तिनका लोकेल नामहरूको सूची [Microsoft docs मा भाषाको समर्थन](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मा पाउन सक्नुहुन्छ।

    > 💁 यदि तपाईं धेरै भाषाहरू बोल्न सक्नुहुन्न भने, तपाईं [Bing Translate](https://www.bing.com/translator) वा [Google Translate](https://translate.google.com) जस्ता सेवाहरू प्रयोग गर्न सक्नुहुन्छ। यी सेवाहरूले अनुवादित पाठको अडियो पनि बजाउन सक्छ।
    >
    > उदाहरणका लागि, यदि तपाईंले LUIS लाई अंग्रेजीमा प्रशिक्षण गर्नुभयो, तर प्रयोगकर्ता भाषा फ्रेन्च प्रयोग गर्न चाहनुहुन्छ भने, तपाईं Bing Translate प्रयोग गरेर "set a 2 minute and 27 second timer" लाई अंग्रेजीबाट फ्रेन्चमा अनुवाद गर्न सक्नुहुन्छ। त्यसपछि **Listen translation** बटन प्रयोग गरेर अनुवादलाई आफ्नो माइक्रोफोनमा बोल्न सक्नुहुन्छ।
    >
    > ![Bing Translate मा Listen translation बटन](../../../../../translated_images/ne/bing-translate.348aa796d6efe2a9.webp)

1. `SPEECH_LOCATION` तल अनुवादक API कुञ्जी र स्थान थप्नुहोस्:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` लाई तपाईंको अनुवादक सेवा स्रोतको लागि API कुञ्जीले प्रतिस्थापन गर्नुहोस्। `<LOCATION>` लाई तपाईंले अनुवादक सेवा स्रोत सिर्जना गर्दा प्रयोग गरेको स्थानले प्रतिस्थापन गर्नुहोस्।

1. `VOICE_URL` तल अनुवादक ट्रिगर URL थप्नुहोस्:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` लाई तपाईंको फङ्क्सन एपमा `translate-text` HTTP ट्रिगरको URL ले प्रतिस्थापन गर्नुहोस्। यो `TEXT_TO_TIMER_FUNCTION_URL` को मानसँग समान हुनेछ, तर `text-to-timer` को सट्टा `translate-text` फङ्क्सन नाम हुनेछ।

1. `src` फोल्डरमा `text_translator.h` नामको नयाँ फाइल थप्नुहोस्।

1. यो नयाँ `text_translator.h` हेडर फाइलमा पाठ अनुवाद गर्न कक्षा समावेश हुनेछ। यो कक्षा घोषणा गर्न निम्न थप्नुहोस्:

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

    यसले `TextTranslator` कक्षा घोषणा गर्दछ, साथै यस कक्षाको एक उदाहरण। कक्षामा WiFi क्लाइन्टको लागि एक मात्र फिल्ड छ।

1. कक्षाको `public` भागमा पाठ अनुवाद गर्न विधि थप्नुहोस्:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    यो विधिले अनुवाद गर्न भाषा र अनुवाद गर्न भाषा लिन्छ। जब भाषण ह्यान्डल गरिन्छ, भाषण प्रयोगकर्ता भाषाबाट LUIS सर्भर भाषामा अनुवाद गरिन्छ, र प्रतिक्रिया दिने बेला यो LUIS सर्भर भाषाबाट प्रयोगकर्ता भाषामा अनुवाद गरिन्छ।

1. यस विधिमा, अनुवाद गर्न पाठ र भाषाहरू समावेश गर्ने JSON बडी निर्माण गर्न कोड थप्नुहोस्:

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

1. यसको तल, सर्भरलेस फङ्क्सन एपमा बडी पठाउन निम्न कोड थप्नुहोस्:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. त्यसपछि, प्रतिक्रिया प्राप्त गर्न कोड थप्नुहोस्:

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

1. अन्ततः, कनेक्शन बन्द गर्न र अनुवादित पाठ फर्काउन कोड थप्नुहोस्:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### कार्य - पहिचान गरिएको भाषण र प्रतिक्रियाहरू अनुवाद गर्नुहोस्

1. `main.cpp` फाइल खोल्नुहोस्।

1. फाइलको शीर्षमा `TextTranslator` कक्षा हेडर फाइलको लागि समावेश निर्देशन थप्नुहोस्:

    ```cpp
    #include "text_translator.h"
    ```

1. टाइमर सेट गर्दा वा समाप्त हुँदा भनिएको पाठ अनुवाद गर्न आवश्यक छ। यसका लागि, `say` फङ्क्सनको पहिलो लाइनको रूपमा निम्न थप्नुहोस्:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    यसले पाठलाई प्रयोगकर्ता भाषामा अनुवाद गर्नेछ।

1. `processAudio` फङ्क्सनमा, `String text = speechToText.convertSpeechToText();` कलको साथ अडियोबाट पाठ प्राप्त गरिन्छ। यस कलपछि, पाठ अनुवाद गर्नुहोस्:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    यसले पाठलाई प्रयोगकर्ता भाषाबाट सर्भरमा प्रयोग गरिएको भाषामा अनुवाद गर्नेछ।

1. यो कोड निर्माण गर्नुहोस्, यसलाई आफ्नो Wio Terminal मा अपलोड गर्नुहोस् र सिरियल मोनिटर मार्फत परीक्षण गर्नुहोस्। जब सिरियल मोनिटरमा `Ready` देख्नुहुन्छ, C बटन थिच्नुहोस् (बायाँतिरको, पावर स्विचको नजिक), र बोल्नुहोस्। सुनिश्चित गर्नुहोस् कि तपाईंको फङ्क्सन एप चलिरहेको छ, र प्रयोगकर्ता भाषामा टाइमर अनुरोध गर्नुहोस्, चाहे आफैंले त्यो भाषा बोल्दै, वा अनुवाद एप प्रयोग गरेर।

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

> 💁 तपाईं यो कोड [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) फोल्डरमा पाउन सक्नुहुन्छ।

😀 तपाईंको बहुभाषी टाइमर कार्यक्रम सफल भयो!

---

**अस्वीकरण**:  
यो दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) प्रयोग गरेर अनुवाद गरिएको छ। हामी शुद्धताको लागि प्रयास गर्छौं, तर कृपया ध्यान दिनुहोस् कि स्वचालित अनुवादहरूमा त्रुटि वा अशुद्धता हुन सक्छ। यसको मूल भाषा मा रहेको मूल दस्तावेज़लाई आधिकारिक स्रोत मानिनुपर्छ। महत्वपूर्ण जानकारीको लागि, व्यावसायिक मानव अनुवाद सिफारिस गरिन्छ। यस अनुवादको प्रयोगबाट उत्पन्न हुने कुनै पनि गलतफहमी वा गलत व्याख्याको लागि हामी जिम्मेवार हुने छैनौं।