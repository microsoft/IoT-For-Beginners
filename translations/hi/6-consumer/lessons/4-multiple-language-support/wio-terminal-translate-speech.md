# भाषण का अनुवाद करें - Wio Terminal

इस पाठ के इस भाग में, आप अनुवादक सेवा का उपयोग करके टेक्स्ट का अनुवाद करने के लिए कोड लिखेंगे।

## अनुवादक सेवा का उपयोग करके टेक्स्ट को भाषण में बदलें

स्पीच सर्विस REST API सीधे अनुवाद का समर्थन नहीं करता है। इसके बजाय, आप स्पीच टू टेक्स्ट सेवा द्वारा उत्पन्न टेक्स्ट और बोले गए उत्तर के टेक्स्ट का अनुवाद करने के लिए अनुवादक सेवा का उपयोग कर सकते हैं। इस सेवा में एक REST API है जिसे आप टेक्स्ट का अनुवाद करने के लिए उपयोग कर सकते हैं, लेकिन इसे उपयोग में आसान बनाने के लिए इसे आपके फ़ंक्शन ऐप में एक अन्य HTTP ट्रिगर में लपेटा जाएगा।

### कार्य - टेक्स्ट का अनुवाद करने के लिए एक सर्वरलेस फ़ंक्शन बनाएं

1. अपने `smart-timer-trigger` प्रोजेक्ट को VS Code में खोलें और सुनिश्चित करें कि टर्मिनल में वर्चुअल एनवायरनमेंट सक्रिय है। यदि नहीं, तो टर्मिनल को बंद करें और पुनः बनाएँ।

1. `local.settings.json` फ़ाइल खोलें और अनुवादक API कुंजी और स्थान के लिए सेटिंग्स जोड़ें:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` को अपने अनुवादक सेवा संसाधन के API कुंजी से बदलें। `<location>` को उस स्थान से बदलें जिसे आपने अनुवादक सेवा संसाधन बनाते समय उपयोग किया था।

1. इस ऐप में एक नया HTTP ट्रिगर जोड़ें जिसे `translate-text` कहा जाता है। इसे VS Code टर्मिनल में फ़ंक्शन ऐप प्रोजेक्ट के रूट फ़ोल्डर के अंदर निम्नलिखित कमांड का उपयोग करके करें:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    यह एक HTTP ट्रिगर बनाएगा जिसे `translate-text` कहा जाता है।

1. `translate-text` फ़ोल्डर में `__init__.py` फ़ाइल की सामग्री को निम्नलिखित से बदलें:

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

    यह कोड HTTP अनुरोध से टेक्स्ट और भाषाओं को निकालता है। फिर यह अनुवादक REST API को अनुरोध करता है, URL के लिए पैरामीटर के रूप में भाषाओं को पास करता है और अनुवाद करने के लिए टेक्स्ट को बॉडी के रूप में पास करता है। अंत में, अनुवाद लौटाया जाता है।

1. अपने फ़ंक्शन ऐप को लोकल रूप से चलाएँ। आप इसे उसी तरह से कॉल कर सकते हैं जैसे आपने `text-to-timer` HTTP ट्रिगर का परीक्षण किया था। सुनिश्चित करें कि JSON बॉडी के रूप में अनुवाद करने के लिए टेक्स्ट और भाषाओं को पास करें:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    यह उदाहरण *Définir une minuterie de 30 secondes* को फ्रेंच से यूएस इंग्लिश में अनुवाद करता है। यह *Set a 30-second timer* लौटाएगा।

> 💁 आप इस कोड को [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) फ़ोल्डर में पा सकते हैं।

### कार्य - अनुवादक फ़ंक्शन का उपयोग करके टेक्स्ट का अनुवाद करें

1. यदि `smart-timer` प्रोजेक्ट पहले से खुला नहीं है, तो इसे VS Code में खोलें।

1. आपका स्मार्ट टाइमर 2 भाषाओं के साथ सेट होगा - वह भाषा जो LUIS को प्रशिक्षित करने के लिए सर्वर पर उपयोग की गई थी (वही भाषा उपयोगकर्ता से बात करने के लिए संदेश बनाने के लिए भी उपयोग की जाती है), और वह भाषा जो उपयोगकर्ता द्वारा बोली जाती है। `config.h` हेडर फ़ाइल में `LANGUAGE` कॉन्स्टेंट को उपयोगकर्ता द्वारा बोली जाने वाली भाषा के लिए अपडेट करें, और LUIS को प्रशिक्षित करने के लिए उपयोग की गई भाषा के लिए `SERVER_LANGUAGE` नामक एक नया कॉन्स्टेंट जोड़ें:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` को उस भाषा के लोकेल नाम से बदलें जिसमें आप बोलेंगे, उदाहरण के लिए फ्रेंच के लिए `fr-FR`, या कैंटोनीज़ के लिए `zn-HK`।

    `<server language>` को उस भाषा के लोकेल नाम से बदलें जिसे LUIS को प्रशिक्षित करने के लिए उपयोग किया गया था।

    आप समर्थित भाषाओं और उनके लोकेल नामों की सूची [Microsoft Docs पर भाषा और आवाज़ समर्थन दस्तावेज़](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) में पा सकते हैं।

    > 💁 यदि आप कई भाषाएँ नहीं बोलते हैं, तो आप [Bing Translate](https://www.bing.com/translator) या [Google Translate](https://translate.google.com) जैसी सेवा का उपयोग अपनी पसंदीदा भाषा से किसी अन्य भाषा में अनुवाद करने के लिए कर सकते हैं। ये सेवाएँ अनुवादित टेक्स्ट का ऑडियो भी चला सकती हैं।
    >
    > उदाहरण के लिए, यदि आप LUIS को अंग्रेजी में प्रशिक्षित करते हैं, लेकिन उपयोगकर्ता भाषा के रूप में फ्रेंच का उपयोग करना चाहते हैं, तो आप Bing Translate का उपयोग करके "set a 2 minute and 27 second timer" जैसे वाक्यों को अंग्रेजी से फ्रेंच में अनुवाद कर सकते हैं, फिर **Listen translation** बटन का उपयोग करके अनुवाद को अपने माइक्रोफोन में बोल सकते हैं।
    >
    > ![Bing Translate पर Listen translation बटन](../../../../../translated_images/hi/bing-translate.348aa796d6efe2a9.webp)

1. `SPEECH_LOCATION` के नीचे अनुवादक API कुंजी और स्थान जोड़ें:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` को अपने अनुवादक सेवा संसाधन के API कुंजी से बदलें। `<LOCATION>` को उस स्थान से बदलें जिसे आपने अनुवादक सेवा संसाधन बनाते समय उपयोग किया था।

1. `VOICE_URL` के नीचे अनुवादक ट्रिगर URL जोड़ें:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` को आपके फ़ंक्शन ऐप पर `translate-text` HTTP ट्रिगर के URL से बदलें। यह `TEXT_TO_TIMER_FUNCTION_URL` के मान के समान होगा, सिवाय इसके कि फ़ंक्शन का नाम `text-to-timer` के बजाय `translate-text` होगा।

1. `src` फ़ोल्डर में एक नई फ़ाइल जोड़ें जिसे `text_translator.h` कहा जाता है।

1. यह नया `text_translator.h` हेडर फ़ाइल टेक्स्ट का अनुवाद करने के लिए एक क्लास को शामिल करेगा। इस क्लास को घोषित करने के लिए इस फ़ाइल में निम्नलिखित जोड़ें:

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

    यह `TextTranslator` क्लास को घोषित करता है, साथ ही इस क्लास का एक इंस्टेंस भी। क्लास में WiFi क्लाइंट के लिए एक सिंगल फ़ील्ड है।

1. इस क्लास के `public` सेक्शन में, टेक्स्ट का अनुवाद करने के लिए एक मेथड जोड़ें:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    यह मेथड उस भाषा से अनुवाद करता है जिसमें से अनुवाद करना है, और उस भाषा में अनुवाद करता है जिसमें अनुवाद करना है। जब भाषण को संभाला जाता है, तो भाषण उपयोगकर्ता की भाषा से LUIS सर्वर भाषा में अनुवादित होगा, और जब उत्तर दिए जाते हैं तो यह LUIS सर्वर भाषा से उपयोगकर्ता की भाषा में अनुवादित होगा।

1. इस मेथड में, JSON बॉडी बनाने के लिए कोड जोड़ें जिसमें अनुवाद करने के लिए टेक्स्ट और भाषाएँ शामिल हों:

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

1. इसके नीचे, सर्वरलेस फ़ंक्शन ऐप को बॉडी भेजने के लिए निम्नलिखित कोड जोड़ें:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. अगला, प्रतिक्रिया प्राप्त करने के लिए कोड जोड़ें:

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

1. अंत में, कनेक्शन बंद करने और अनुवादित टेक्स्ट लौटाने के लिए कोड जोड़ें:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### कार्य - पहचाने गए भाषण और उत्तरों का अनुवाद करें

1. `main.cpp` फ़ाइल खोलें।

1. फ़ाइल के शीर्ष पर `TextTranslator` क्लास हेडर फ़ाइल के लिए एक include निर्देश जोड़ें:

    ```cpp
    #include "text_translator.h"
    ```

1. जब टाइमर सेट होता है या समाप्त होता है, तो कहा गया टेक्स्ट का अनुवाद करने की आवश्यकता होती है। ऐसा करने के लिए, `say` फ़ंक्शन की पहली पंक्ति के रूप में निम्नलिखित जोड़ें:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    यह टेक्स्ट को उपयोगकर्ता की भाषा में अनुवाद करेगा।

1. `processAudio` फ़ंक्शन में, टेक्स्ट को कैप्चर किए गए ऑडियो से `String text = speechToText.convertSpeechToText();` कॉल के साथ प्राप्त किया जाता है। इस कॉल के बाद, टेक्स्ट का अनुवाद करें:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    यह टेक्स्ट को उपयोगकर्ता की भाषा से सर्वर पर उपयोग की गई भाषा में अनुवाद करेगा।

1. इस कोड को बनाएं, इसे अपने Wio Terminal पर अपलोड करें और इसे सीरियल मॉनिटर के माध्यम से परीक्षण करें। एक बार जब आप सीरियल मॉनिटर में `Ready` देखें, तो C बटन दबाएँ (जो बाईं ओर है, पावर स्विच के सबसे करीब), और बोलें। सुनिश्चित करें कि आपका फ़ंक्शन ऐप चल रहा है, और उपयोगकर्ता की भाषा में टाइमर का अनुरोध करें, चाहे वह भाषा स्वयं बोलकर हो, या अनुवाद ऐप का उपयोग करके।

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

> 💁 आप इस कोड को [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) फ़ोल्डर में पा सकते हैं।

😀 आपका बहुभाषी टाइमर प्रोग्राम सफल रहा!

**अस्वीकरण**:  
यह दस्तावेज़ AI अनुवाद सेवा [Co-op Translator](https://github.com/Azure/co-op-translator) का उपयोग करके अनुवादित किया गया है। जबकि हम सटीकता सुनिश्चित करने का प्रयास करते हैं, कृपया ध्यान दें कि स्वचालित अनुवाद में त्रुटियां या अशुद्धियां हो सकती हैं। मूल भाषा में उपलब्ध मूल दस्तावेज़ को आधिकारिक स्रोत माना जाना चाहिए। महत्वपूर्ण जानकारी के लिए, पेशेवर मानव अनुवाद की सिफारिश की जाती है। इस अनुवाद के उपयोग से उत्पन्न किसी भी गलतफहमी या गलत व्याख्या के लिए हम जिम्मेदार नहीं हैं।