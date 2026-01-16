<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2026-01-07T03:39:51+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "te"
}
-->
# Translate speech - Wio Terminal

ఈ పాఠంలో, మీరు ట్రాన్స్లేటర్ సర్వీస్ ఉపయోగించి టెక్స్ట్‌ను అనువాదం చేసేందుకు కోడ్ రాస్తారు.

## ట్రాన్స్లేటర్ సర్వీస్ ఉపయోగించి టెక్స్ట్‌ని మాటలోకి మార్చడం

స్పీచ్ సర్వీస్ REST API ప్రత్యక్ష అనువాదాలను మద్దతు ఇవ్వదు, బదులుగా మీరు ట్రాన్స్లేటర్ సర్వీస్ ఉపయోగించి టెక్స్ట్‌ని అనువదించవచ్చు, ఇది స్పీచ్ టు టెక్స్ట్ సర్వీస్ ద్వారా ఉత్పత్తి చేసిన టెక్స్ట్ మరియు మాట్లాడు ప్రతిస్పందన టెక్స్ట్‌ను అనువదిస్తుంది. ఈ సర్వీస్‌కు REST API ఉంది, దీన్ని మీరు టెక్స్ట్‌ను అనువదించడానికి ఉపయోగించవచ్చు, కానీ ఈ కోడ్‌ను మరింత సులభంగా ఉపయోగించడానికి మీ ఫంక్షన్స్ యాప్‌లో మరో HTTP ట్రిగ్గర్‌లో ర్యాప్ చేస్తారు.

### టాస్క్ - టెక్స్ట్ అనువదించడానికి సర్వర్‌లెస్ ఫంక్షన్ సృష్టించడం

1. మీ `smart-timer-trigger` ప్రాజెక్టును VS కోడ్‌లో తెరిచి, టెర్మినల్‌ను ఓపెన్ చేసి వర్చువల్ ఎన్‌వైరన్మెంట్ యాక్టివేట్ అయిందో లేదో చూసుకోండి. లేకపోతే, టెర్మినల్‌ను డెడ్ చేసి పునఃసృష్టించండి.

1. `local.settings.json` ఫైల్‌ను ఓపెన్ చేసి ట్రాన్స్లేటర్ API కీ మరియు ప్రాంతం కోసం సెట్టింగ్స్ జోడించండి:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` స్థానంలో మీ ట్రాన్స్లేటర్ సర్వీస్ రిసోర్సు API కీని, `<location>` స్థానంలో మీరు సృష్టించిన ప్రాంతాన్ని భర్తీ చేయండి.

1. VS కోడ్ టెర్మినల్‌లో ఫంక్షన్స్ యాప్ రూట్ ఫోల్డర్‌లో నుండి కింది ఆదేశంతో `translate-text` అనే కొత్త HTTP ట్రిగ్గర్ జోడించండి:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    ఇది `translate-text` అనే HTTP ట్రిగ్గర్ ను సృష్టిస్తుంది.

1. `translate-text` ఫోల్డర్‌లోని `__init__.py` ఫైల్ లోని కంటెంట్స్ ఈ క్రింది కోడ్‌తో మార్చండి:

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

    ఈ కోడ్ HTTP రిక్వెస్ట్ నుండి టెక్స్ట్ మరియు భాషలను తీసుకుంటుంది. తరువాత, ట్రాన్స్లేటర్ REST API కి భాషలను URL పారా మీటర్లుగా పంపి, అనువదించవలసిన టెక్స్ట్‌ను బాడీగా పంపుతుంది. చివరగా, అనువాదం తిరిగి ఇస్తుంది.

1. మీ ఫంక్షన్ యాప్‌ను లోకల్‌గా రన్ చేయండి. మీరు `text-to-timer` HTTP ట్రిగ్గర్‌ను పరీక్షించానెల్లా, ఇక్కడ కూడా curl వంటి టూల్‌తో ఈ ఫంక్షన్ కి కాల్ చేయొచ్చు. టెక్స్ట్ మరియు భాషలను JSON బాడీగా పంపించండి:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    ఈ ఉదాహరణ ఫ్రెంచ్ నుండి US ఇంగ్లీష్‌లో *Définir une minuterie de 30 secondes* అని అనువదిస్తుంది. ఫలితంగా *Set a 30-second timer* వస్తుంది.

> 💁 మీరు ఈ కోడ్‌ను [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) ఫోల్డర్‌లో చూడవచ్చు.

### టాస్క్ - ట్రాన్స్లేటర్ ఫంక్షన్ ఉపయోగించి టెక్స్ట్ అనువదించడం

1. `smart-timer` ప్రాజెక్టును VS కోడ్‌లో ఓపెన్ చేయండి, ఇంకా ఓపెన్ చేయకపోతే.

1. మీ స్మార్ట్ టైమర్‌లో రెండు భాషలు సెట్ ఉంటాయి - LUIS నేర్చుకున్న సర్వర్ భాష (అదేప్రకారం యూజర్‌తో మాట్లాడే భాషకు సందేశాలు నిర్మించబడతాయి), మరియు యూజర్ మాట్లాడే భాష. `config.h` హెడర్ ఫైల్లో `LANGUAGE` కానిస్టెంట్‌ను యూజర్ మాట్లాడే భాషగా అప్‌డేట్ చేసి, LUIS సర్వర్ భాష కోసం `SERVER_LANGUAGE` కానిస్టెంట్‌ను జోడించండి:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` స్థానంలో మీరు మాట్లాడబోయే భాష యొక్క లోకల్ నేమ్ ఇవ్వండి, ఉదాహరణకు ఫ్రెంచ్‌కు `fr-FR` లేదా కాంటోనిస్‌కు `zn-HK`.

    `<server language>` స్థానంలో LUIS శిక్షణకు ఉపయోగించిన భాష యొక్క లోకల్ నేమ్ ఇవ్వండి.

    మద్దతు ఉన్న భాషల జాబితా మరియు వారి లోకల్ నేమ్‌లు [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)లో చూడవచ్చు.

    > 💁 మీరు బహుభాషలు మాట్లాడకపోతే, [Bing Translate](https://www.bing.com/translator) లేదా [Google Translate](https://translate.google.com) వంటి సర్వీసులను ఉపయోగించి మీరు ఇష్టపడే భాష నుండి మీకు కావల్సిన భాషకు ట్రాన్స్లేట్ చేయవచ్చు. ఈ సర్వీసులు అనువాద టెక్స్ట్ ఆడియోగా ప్లే చేయగలవు.
    >
    > ఉదాహరణకి, మీరు ఇంగ్లీష్‌లో LUIS నిలిపినట్లయితే కానీ యూజర్ భాష ఫ్రెంచ్ అయితే, "set a 2 minute and 27 second timer" వాక్యాన్ని Bing Translate ఉపయోగించి ఇంగ్లీష్ నుండి ఫ్రెంచ్‌కు అనువదించండి, తరువాత **Listen translation** బటన్ పైన క్లిక్ చేసి మీ మైక్రోఫోన్‌కి అనువాదాన్ని పలకరించండి.
    >
    > ![The listen translation button on Bing translate](../../../../../translated_images/te/bing-translate.348aa796d6efe2a9.png)

1. `SPEECH_LOCATION` కింద ట్రాన్స్లేటర్ API కీ మరియు ప్రాంతం జోడించండి:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` స్థానంలో మీ ట్రాన్స్లేటర్ సర్వీస్ రిసోర్సు API కీని, `<LOCATION>` స్థానంలో మీరు సృష్టించిన ప్రాంతాన్ని భర్తీ చేయండి.

1. `VOICE_URL` కింద ట్రాన్స్లేటర్ ట్రిగ్గర్ URL జోడించండి:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` స్థానంలో మీ ఫంక్షన్ యాప్‌లోని `translate-text` HTTP ట్రిగ్గర్ URL ని ఇవ్వండి. ఇది `TEXT_TO_TIMER_FUNCTION_URL` విలువతో అదే ఉంటుంది, కాని `text-to-timer` బదులు `translate-text` ఫంక్షన్ పేరు ఉంటుంది.

1. `src` ఫోల్డర్‌లో `text_translator.h` అనే కొత్త ఫైల్ జోడించండి.

1. ఈ కొత్త `text_translator.h` హెడర్ ఫైల్‌లో టెక్స్ట్‌ని అనువదించే క్లాస్ ఉంటుంది. ఈ ఫైల్‌లో ఈ క్రింది కోడ్ జోడించి క్లాస్ ప్రకటించండి:

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

    ఇది `TextTranslator` క్లాస్‌ను మరియు క్లాస్ యొక్క ఒక ఇన్‌స్టన్స్ను ప్రకటిస్తుంది. క్లాస్‌లో ఒకే ఒక్క WiFi క్లయింట్ ఫీల్డ్ ఉంటుంది.

1. ఈ క్లాస్ `public` సెక్షన్‌లో టెక్స్ట్ అనువదించే ఒక మెథడ్ జోడించండి:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    ఈ మెథడ్ అనువదించవలసిన భాష మరియు అనూవదానికి గల భాషను తీసుకుంటుంది. స్పీచ్ హ్యాండ్లింగ్ లో, స్పీచ్ యూజర్ భాష నుండి LUIS సర్వర్ భాషకు అనువదించబడుతుంది, మరియు స్పందనలప్పుడు LUIS సర్వర్ భాష నుండి యూజర్ భాషకు అనువదిస్తుంది.

1. ఈ మెథడ్‌లో JSON బాడీని నిర్మించడానికిపట్టిన కోడ్ జోడించండి, ఇది అనువదించవలసిన టెక్స్ట్ మరియు భాషలను కలిగి ఉంటుంది:

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

1. దీని కింద సర్వర్‌లెస్ ఫంక్షన్ యాప్‌కి బాడీ పంపడానికి ఈ క్రింది కోడ్ జోడించండి:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. తరువాత, స్పందన పొందడానికి కోడ్ జోడించండి:

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

1. చివరగా కనెక్షన్ మూసివేసి అనువాద టెక్స్ట్ తిరిగి ఇచ్చే కోడ్ జోడించండి:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### టాస్క్ - గుర్తించిన స్పీచ్ మరియు ప్రతిస్పందనలు అనువదించడం

1. `main.cpp` ఫైల్ తెరవండి.

1. ఫైల్ ప్రారంభంలో `TextTranslator` క్లాస్ హెడర్ ఫైల్‌కు include డైరెక్టివ్ జోడించండి:

    ```cpp
    #include "text_translator.h"
    ```

1. టైమర్ సెట్ అవుతూనే లేదా కాలమైనప్పుడు చెప్పే టెక్స్ట్ అనువదించవలసి ఉంటుంది. దీని కోసం `say` ఫంక్షన్ మొదటి లైనుగా ఈ క్రింది కోడ్ జోడించండి:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ఇది టెక్స్ట్‌ను యూజర్ భాషకి అనువదిస్తుంది.

1. `processAudio` ఫంక్షన్‌లో, క్యాప్చర్ చేసిన ఆడియో నుండి టెక్స్ట్‌ను ఈ పాఠంతో `String text = speechToText.convertSpeechToText();` కాల్ ద్వారా పొందుతారు. ఆ కాల్ అనంతరం, ఈ క్రింది విధంగా టెక్స్ట్ అనువదించండి:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ఇది టెక్స్ట్‌ను యూజర్ భాష నుండి సర్వర్ భాషకు అనువదిస్తుంది.

1. కోడ్ కంపైల్ చేసి, Wio Terminalకి అప్లోడ్ చేసి, సీరియల్ మానిటర్ ద్వారా పరీక్షించండి. సీరియల్ మానిటర్‌లో `Ready` కనిపించిన తర్వాత, C బటన్ ( ఎడమ వైపు, పవర్ స్విచ్ కంటే దగ్గరగా ఉన్నది) నొక్కి, మాట్లాడండి. మీ ఫంక్షన్ యాప్ పని చేస్తున్నదో లేదో ధృవపరచుకోండి, యూజర్ భాషలో టైమర్ కోరండి, మీరు ఆ భాషలో మాట్లాడవచ్చు లేదా అనువాద యాప్ ఉపయోగించవచ్చు.

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

> 💁 మీరు ఈ కోడ్‌ను [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) ఫోల్డర్‌లో చూడవచ్చు.

😀 మీ బహుభాషా టైమర్ ప్రోగ్రామ్ విజయం!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**అస్పష్టీకరణ**:
ఈ పత్రికను AI అనువాద సేవ [Co-op Translator](https://github.com/Azure/co-op-translator) ఉపయోగించి అనువదించడం జరిగింది. మేము సత్వరత కోసం ప్రయత్నిస్తూనే ఉంటాము, అయినప్పటికీ ఆటోమేటిక్ అనువాదాలలో తప్పులు లేదా పొరపాట్లు ఉండవచ్చు. అటువంటి సందర్భాల్లో, మాతృభాషలో ఉన్న మౌలిక పత్రికను అధికారిక మూలంగా పరిగణించాలి. కీలక సమాచారం కోసం, ప్రొఫెషనల్ మానవ అనువాదం సూచించబడుతుంది. ఈ అనువాదం వలన కలిగే ఏవైనా అభిప్రాయ భిన్నతల కోసం మేము బాధ్యులు కాదు.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->