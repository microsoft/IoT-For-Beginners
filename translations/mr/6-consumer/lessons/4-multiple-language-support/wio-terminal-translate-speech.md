# भाषण अनुवाद करा - Wio Terminal

या धड्याच्या भागात, तुम्ही अनुवादक सेवेसाठी कोड लिहून मजकूर अनुवादित कराल.

## अनुवादक सेवेसाठी मजकूर भाषणात रूपांतरित करा

स्पीच सेवा REST API थेट अनुवादांना समर्थन देत नाही, परंतु तुम्ही स्पीच टू टेक्स्ट सेवेद्वारे तयार केलेल्या मजकूराचा आणि बोलल्या प्रतिसादाचा मजकूर अनुवादित करण्यासाठी अनुवादक सेवा वापरू शकता. या सेवेसाठी REST API उपलब्ध आहे, परंतु वापरण्यास सुलभ करण्यासाठी हे तुमच्या फंक्शन्स अ‍ॅपमध्ये आणखी एका HTTP ट्रिगरमध्ये गुंडाळले जाईल.

### कार्य - मजकूर अनुवाद करण्यासाठी सर्व्हरलेस फंक्शन तयार करा

1. तुमचा `smart-timer-trigger` प्रकल्प VS Code मध्ये उघडा आणि टर्मिनल उघडा, याची खात्री करा की वर्च्युअल वातावरण सक्रिय आहे. नसल्यास, टर्मिनल बंद करा आणि पुन्हा तयार करा.

1. `local.settings.json` फाइल उघडा आणि अनुवादक API की आणि स्थानासाठी सेटिंग्ज जोडा:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` ला तुमच्या अनुवादक सेवा संसाधनासाठी API कीने बदला. `<location>` ला तुम्ही अनुवादक सेवा संसाधन तयार करताना वापरलेल्या स्थानाने बदला.

1. या अ‍ॅपमध्ये `translate-text` नावाचा नवीन HTTP ट्रिगर खालील कमांड वापरून तयार करा, जो VS Code टर्मिनलमध्ये फंक्शन्स अ‍ॅप प्रकल्पाच्या मूळ फोल्डरमध्ये आहे:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    यामुळे `translate-text` नावाचा HTTP ट्रिगर तयार होईल.

1. `translate-text` फोल्डरमधील `__init__.py` फाइलची सामग्री खालीलप्रमाणे बदला:

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

    हा कोड HTTP विनंतीमधून मजकूर आणि भाषांचा अर्क काढतो. त्यानंतर, भाषांना URL साठी पॅरामीटर्स म्हणून आणि अनुवादित करण्यासाठी मजकूर शरीर म्हणून पास करत अनुवादक REST API ला विनंती करतो. शेवटी, अनुवाद परत केला जातो.

1. तुमचे फंक्शन अ‍ॅप स्थानिक स्तरावर चालवा. तुम्ही हे curl सारख्या टूलचा वापर करून कॉल करू शकता, जसे तुम्ही `text-to-timer` HTTP ट्रिगरची चाचणी केली होती. अनुवादित करण्यासाठी मजकूर आणि भाषांना JSON शरीर म्हणून पास करा:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    हा उदाहरण फ्रेंचमधील *Définir une minuterie de 30 secondes* ला यूएस इंग्रजीमध्ये अनुवादित करतो. यामुळे *Set a 30-second timer* परत मिळेल.

> 💁 तुम्ही हा कोड [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) फोल्डरमध्ये शोधू शकता.

### कार्य - अनुवादक फंक्शन वापरून मजकूर अनुवादित करा

1. `smart-timer` प्रकल्प VS Code मध्ये उघडा, जर तो आधीच उघडलेला नसेल.

1. तुमच्या स्मार्ट टाइमरमध्ये 2 भाषा सेट असतील - LUIS प्रशिक्षणासाठी वापरलेली सर्व्हरची भाषा (हीच भाषा वापरकर्त्याशी संवाद साधण्यासाठी संदेश तयार करण्यासाठी वापरली जाते), आणि वापरकर्त्याने बोललेली भाषा. `config.h` हेडर फाइलमधील `LANGUAGE` स्थिरांक वापरकर्त्याने बोलली जाणारी भाषा म्हणून अपडेट करा आणि LUIS प्रशिक्षणासाठी वापरलेल्या भाषेसाठी `SERVER_LANGUAGE` नावाचा नवीन स्थिरांक जोडा:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` ला तुम्ही बोलत असलेल्या भाषेसाठी स्थानिक नावाने बदला, उदाहरणार्थ फ्रेंचसाठी `fr-FR`, किंवा कॅंटोनीजसाठी `zn-HK`.

    `<server language>` ला LUIS प्रशिक्षणासाठी वापरलेल्या भाषेच्या स्थानिक नावाने बदला.

    तुम्ही समर्थित भाषांची यादी आणि त्यांची स्थानिक नावे [Microsoft docs वर भाषेचे आणि आवाजाचे समर्थन दस्तऐवज](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) मध्ये शोधू शकता.

    > 💁 जर तुम्ही अनेक भाषा बोलत नसाल तर तुम्ही [Bing Translate](https://www.bing.com/translator) किंवा [Google Translate](https://translate.google.com) सारख्या सेवांचा वापर करून तुमच्या पसंतीच्या भाषेतून दुसऱ्या भाषेत अनुवाद करू शकता. या सेवा अनुवादित मजकूराचे ऑडिओ प्ले करू शकतात.
    >
    > उदाहरणार्थ, जर तुम्ही LUIS इंग्रजीमध्ये प्रशिक्षित केले असेल, परंतु वापरकर्ता भाषा म्हणून फ्रेंच वापरायचे असेल, तर तुम्ही Bing Translate वापरून "set a 2 minute and 27 second timer" सारख्या वाक्यांचे इंग्रजीमधून फ्रेंचमध्ये अनुवाद करू शकता, आणि नंतर **Listen translation** बटण वापरून अनुवादित मजकूर तुमच्या मायक्रोफोनमध्ये बोलू शकता.
    >
    > ![Bing Translate वर Listen translation बटण](../../../../../translated_images/mr/bing-translate.348aa796d6efe2a9.webp)

1. `SPEECH_LOCATION` खाली अनुवादक API की आणि स्थान जोडा:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` ला तुमच्या अनुवादक सेवा संसाधनासाठी API कीने बदला. `<LOCATION>` ला तुम्ही अनुवादक सेवा संसाधन तयार करताना वापरलेल्या स्थानाने बदला.

1. `VOICE_URL` खाली अनुवादक ट्रिगर URL जोडा:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ला तुमच्या फंक्शन अ‍ॅपवरील `translate-text` HTTP ट्रिगरचा URL बदला. हे `TEXT_TO_TIMER_FUNCTION_URL` च्या मूल्यासारखेच असेल, फक्त फंक्शन नाव `text-to-timer` ऐवजी `translate-text` असेल.

1. `src` फोल्डरमध्ये `text_translator.h` नावाची नवीन फाइल जोडा.

1. ही नवीन `text_translator.h` हेडर फाइल मजकूर अनुवादित करण्यासाठी एक वर्ग समाविष्ट करेल. या फाइलमध्ये खालीलप्रमाणे हा वर्ग घोषित करा:

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

    हे `TextTranslator` वर्ग घोषित करते, तसेच या वर्गाची एक उदाहरण. वर्गामध्ये WiFi क्लायंटसाठी एक फील्ड आहे.

1. या वर्गाच्या `public` विभागात, मजकूर अनुवादित करण्यासाठी एक पद्धत जोडा:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    ही पद्धत अनुवादित करण्यासाठी भाषा घेते. भाषण हाताळताना, भाषण वापरकर्त्याच्या भाषेतून LUIS सर्व्हर भाषेत अनुवादित केले जाईल, आणि प्रतिसाद देताना LUIS सर्व्हर भाषेतून वापरकर्त्याच्या भाषेत अनुवादित केले जाईल.

1. या पद्धतीमध्ये, अनुवादित करण्यासाठी मजकूर आणि भाषांचा समावेश असलेले JSON शरीर तयार करण्यासाठी कोड जोडा:

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

1. याखाली, सर्व्हरलेस फंक्शन अ‍ॅपला शरीर पाठवण्यासाठी खालील कोड जोडा:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. पुढे, प्रतिसाद मिळवण्यासाठी कोड जोडा:

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

1. शेवटी, कनेक्शन बंद करण्यासाठी आणि अनुवादित मजकूर परत करण्यासाठी कोड जोडा:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### कार्य - ओळखलेले भाषण आणि प्रतिसाद अनुवादित करा

1. `main.cpp` फाइल उघडा.

1. `TextTranslator` वर्ग हेडर फाइलसाठी फाइलच्या शीर्षस्थानी एक समाविष्ट निर्देश जोडा:

    ```cpp
    #include "text_translator.h"
    ```

1. टाइमर सेट किंवा संपल्यावर म्हटले जाणारे मजकूर अनुवादित करणे आवश्यक आहे. हे करण्यासाठी, `say` फंक्शनच्या पहिल्या ओळीत खालीलप्रमाणे जोडा:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    हे मजकूर वापरकर्त्याच्या भाषेत अनुवादित करेल.

1. `processAudio` फंक्शनमध्ये, `String text = speechToText.convertSpeechToText();` कॉलसह कॅप्चर केलेल्या ऑडिओमधून मजकूर मिळवला जातो. या कॉलनंतर, मजकूर अनुवादित करा:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    हे मजकूर वापरकर्त्याच्या भाषेतून सर्व्हरवर वापरल्या जाणाऱ्या भाषेत अनुवादित करेल.

1. हा कोड तयार करा, Wio Terminal वर अपलोड करा आणि सीरियल मॉनिटरद्वारे चाचणी करा. एकदा तुम्हाला सीरियल मॉनिटरमध्ये `Ready` दिसल्यावर, C बटण (डाव्या बाजूला, पॉवर स्विचच्या जवळ) दाबा आणि बोला. तुमचे फंक्शन अ‍ॅप चालू असल्याची खात्री करा आणि वापरकर्त्याच्या भाषेत टाइमरची विनंती करा, स्वतः ती भाषा बोलून किंवा अनुवाद अ‍ॅप वापरून.

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

> 💁 तुम्ही हा कोड [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) फोल्डरमध्ये शोधू शकता.

😀 तुमचा बहुभाषिक टाइमर प्रोग्राम यशस्वी झाला!

---

**अस्वीकरण**:  
हा दस्तऐवज [Co-op Translator](https://github.com/Azure/co-op-translator) या एआय भाषांतर सेवेचा वापर करून भाषांतरित करण्यात आला आहे. आम्ही अचूकतेसाठी प्रयत्नशील असलो तरी, कृपया लक्षात घ्या की स्वयंचलित भाषांतरांमध्ये त्रुटी किंवा अचूकतेचा अभाव असू शकतो. मूळ भाषेतील दस्तऐवज हा अधिकृत स्रोत मानला जावा. महत्त्वाच्या माहितीसाठी व्यावसायिक मानवी भाषांतराची शिफारस केली जाते. या भाषांतराचा वापर केल्यामुळे उद्भवलेल्या कोणत्याही गैरसमज किंवा चुकीच्या अर्थासाठी आम्ही जबाबदार राहणार नाही.