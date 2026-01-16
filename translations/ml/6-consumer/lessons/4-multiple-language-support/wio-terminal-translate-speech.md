<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2026-01-07T03:40:41+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "ml"
}
-->
# വാക്കുകളെ other भाषയിൽ വിവർത്തനം ചെയ്യുക - Wio Terminal

പാഠത്തിന്റെ ഈ ഭാഗത്തിൽ, നിങ്ങൾ വിവർത്തകൻ സേവനം ഉപയോഗിച്ച് എഴുത്ത് പരിഭാഷപ്പെടുത്താൻ കോഡ് എഴുതും.

## വിവർത്തകൻ സേവനം ഉപയോഗിച്ച് എഴുത്ത് വാക്കുകളാക്കി മാറ്റുക

വാക്കുകൾ സേവന REST API നേരിട്ട് വിവർത്തനം പിന്തുണയ്ക്കുന്നില്ല, പകരം നിങ്ങൾക്ക് വാക്കുകളിൽ നിന്നും എഴുത്തിലേക്ക് സേവനം ഉപയോഗിച്ച് സൃഷ്ടിച്ച വാചകത്തിന്റെ എഴുത്തും സംസാരിച്ച മറുപടിയുടെ എഴുത്തും വിവർത്തനം ചെയ്യാൻ വിവർത്തകൻ സേവനം ഉപയോഗിക്കാം. ഈ സേവനത്തിന് REST API ഉണ്ട്, നിങ്ങൾക്ക് എഴുത്ത് വിവർത്തനം ചെയ്യാനായി ഉപയോഗിക്കാം, പക്ഷേ ഇത് ഉപയോഗിക്കാൻ എളുപ്പമാക്കാനായി നിങ്ങൾ ഫങ്ഷൻ ആപ്പിൽ മറ്റൊരു HTTP ട്രിഗ്ഗറിൽ ഇത് ചുറ്റിപ്പിരിയുന്നു.

### പ്രവർത്തി - എഴുത്ത് വിവർത്തനം ചെയ്യാൻ സെർവർലെസ് ഫങ്ഷൻ സൃഷ്ടിക്കുക

1. നിങ്ങളുടെ `smart-timer-trigger` പ്രോജക്റ്റ് VS കോഡിൽ തുറക്കുക, ടെർമിനൽ തുറന്ന് വെർച്ച്വൽ എൻവയരൺമെന്റ് സജീവമാണെന്ന് ഉറപ്പാക്കുക. ഇല്ലെങ്കിൽ ടെർമിനൽ നിർത്തി വീണ്ടും സൃഷ്ടിക്കുക.

1. `local.settings.json` ഫയൽ തുറന്ന് വിവർത്തകൻ API കീയും ലൊക്കേഷനും ചേർക്കുക:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>` ന്റെ പകരം നിങ്ങളുടെ വിവർത്തകൻ സേവന റിസോഴ്സിനുള്ള API കീ നൽകുക. `<location>` ന്റെ പകരം നിങ്ങൾ സൃഷ്ടിച്ച വിവർത്തകൻ സേവന റിസോഴ്സ് ലൊക്കേഷൻ നൽകുക.

1. ഈ ആപ്പിൽ `translate-text` എന്ന പുതിയ HTTP ട്രിഗ്ഗർ ചേർക്കുക താഴെ കൊടുത്ത കമാൻഡ് ഉപയോഗിച്ച് VS കോഡ് ടെർമിനലിൽ ഫങ്ഷൻ ആപ്പ് പ്രോജക്റ്റ് റൂട്ട് ഫോൾഡറിൽ നിന്നു:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    ഇത് `translate-text` എന്ന HTTP ട്രിഗ്ഗർ സൃഷ്ടിക്കും.

1. `translate-text` ഫോൾഡറിൽ ഉള്ള `__init__.py` ഫയലിന്റെ ഉള്ളടക്കം താഴെ കൊടുത്തതുമായി മടങ്ങിയിരുത്തുക:

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

    ഈ കോഡ് HTTP അഭ്യർത്ഥനയിൽ നിന്ന് ടെക്സ്റ്റും ഭാഷകളും തിരിച്ചു പറയും. പിന്നീട് ട്വെക്സ്റ്റ് വിവർത്തനം ചെയ്യാൻ വിവർത്തകൻ REST API കൾ പറയും, ഭാഷകൾ URL പാരാമീറ്ററുകളായി പാസ്സും തിരുത്താനുള്ള എഴുത്ത് ബോഡി ആയി നൽകും. അവസാനത്ത, വിവർത്തനം തിരിച്ചേ നൽകും.

1. നിങ്ങളുടെ ഫങ്ഷൻ ആപ്പ് ലോക്കലായി റൺ ചെയ്യുക. പിന്നീട് curl പോലുള്ള ടൂളിൽ നിന്ന് ഇത് കോൾ ചെയ്തു പരീക്ഷിക്കാം. വിവർത്തനം ചെയ്യാനുള്ള എഴുത്തും ഭാഷകളും JSON ബോഡിയായി പാസാക്കുക:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    ഈ ഉദാഹരണം *Définir une minuterie de 30 secondes* എന്ന ഫ്രഞ്ച് വാചകത്തെ യു.എസ് ഇംഗ്ലീഷിലേക്ക് വിവർത്തനം ചെയ്യും. *Set a 30-second timer* തിരികെ നൽകും.

> 💁 നിങ്ങൾക്ക് ഈ കോഡ് [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) ഫോൾഡറിലാണ് കാണാൻ കഴിയുന്നത്.

### പ്രവർത്തി - വിവർത്തകനുള്ള ഫങ്ഷൻ ഉപയോഗിച്ച് എഴുത്ത് വിവർത്തനം ചെയ്യുക

1. `smart-timer` പ്രോജക്റ്റ് VS കോഡിൽ തുറക്കുക, ഇത് തുറന്നിരിക്കുന്നില്ലെങ്കിൽ.

1. നിങ്ങളുടെ സ്മാർട്ട് ടൈമറിൽ 2 ഭാഷകൾ സജ്ജമാകുന്നുണ്ടാകും - LUIS പരിശീലിപ്പിക്കാൻ ഉപയോഗിച്ച സർവറിന്റെ ഭാഷ (ഗുണം, അതേ ഭാഷ സന്ദേശങ്ങൾ പറയുന്നതിനും ഉപയോഗിക്കുന്നു), കൂടാതെ ഉപയോക്താവിന്റെ സംസാരിക്കുന്ന ഭാഷ. `config.h` ഹെഡർ ഫയലിൽ `LANGUAGE` കോൺസ്റ്റന്റ് ഉപയോക്താവിന്റെ സംസാരിക്കുന്ന ഭാഷ ആക്കുക, കൂടാതെ LUIS പരിശീലനത്തിനുള്ള ഭാഷ `SERVER_LANGUAGE` എന്ന പുതിയ കോൺസ്റ്റന്റ് ചേർക്കുക:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>` എന്നിടത്ത് നിങ്ങൾ സംസാരിക്കുന്ന ഭാഷയുടെ ലോക്കൽ നാമം നൽകുക, ഉദാഹരണത്തിന് ഫ്രഞ്ച് `fr-FR` അല്ലെങ്കിൽ കാന്റോണീസ് `zn-HK`.

    `<server language>` എന്നിടത്ത് LUIS പരിശീലിപ്പിക്കാൻ ഉപയോഗിച്ച ഭാഷയുടെ ലോക്കൽ നാമം നൽകുക.

    [ലാംഗ്വേജ് ആൻഡ് വോയ്സ് സപ്പോർട്ട്](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) പേജിൽ പിന്തുണയുള്ള ഭാഷകളും അവയുടെ ലോക്കൽ നാമങ്ങളും കാണാം.

    > 💁 നിങ്ങൾക്ക് പലഭാഷകളും സംസാരിക്കാത്ത പക്ഷം [Bing Translate](https://www.bing.com/translator) അല്ലെങ്കിൽ [Google Translate](https://translate.google.com) പോലുള്ള സേവനം ഉപയോഗിച്ച് ആഗ്രഹിക്കുന്ന ഭാഷയിൽ നിന്ന് വേറെ ഒരാശയം ഭാഷയിൽ വിവർത്തനം ചെയ്യാൻ കഴിയും. ഈ സേവനങ്ങൾ പിന്നീട് വിവർത്തിത എഴുത്തിന്റെ ഓഡിയോ പ്ലേ ചെയ്യാനും കഴിയും.
    >
    > ഉദാഹരണത്തിന്, നിങ്ങൾ LUIS ഇംഗ്ലീഷിൽ പരിശീലിപ്പിച്ചാലും, ഉപയോക്താവിന്റെ ഭാഷ ഫ്രഞ്ചായിരിക്കണമെങ്കിൽ, Bing Translate ഉപയോഗിച്ച് "set a 2 minute and 27 second timer" എന്ന വാചകം ഇംഗ്ലീഷിൽ നിന്ന് ഫ്രഞ്ചിലേക്ക് വിവർത്തനം ചെയ്ത് **Listen translation** ബട്ടൺ ഉപയോഗിച്ച് മൈക്രോഫോണിലേക്ക് സംസാരിപ്പിക്കാം.
    >
    > ![Bing Translate ലിസ്റ്റൻ വിവർത്തനം ബട്ടണിൻ്റെ ചിത്രം](../../../../../translated_images/ml/bing-translate.348aa796d6efe2a9.png)

1. `SPEECH_LOCATION` ന്റെ താഴെ വിവർത്തകൻ API കീയും ലൊക്കേഷനും ചേർക്കുക:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>` ന്റെ പകരം നിങ്ങൾ സൃഷ്ടിച്ച വിവർത്തകൻ സേവന റിസോഴ്സിന്റെ API കീ നൽകുക. `<LOCATION>` ന്റെ പകരം അനുയോജ്യമായ ലൊക്കേഷൻ നൽകുക.

1. `VOICE_URL` ന്റെ താഴെ വിവർത്തകൻ ട്രിഗ്ഗർ URL ചേർക്കുക:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>` ന്റെ പകരം നിങ്ങളുടെ ഫങ്ഷൻ ആപ്പിലെ `translate-text` HTTP ട്രിഗ്ഗറിന്റെ URL നൽകുക. ഇത് `TEXT_TO_TIMER_FUNCTION_URL` ന്റെ സമാനമായിരിക്കും, മാത്രം ഫങ്ഷൻ പേര് `text-to-timer` ഇനഹത് `translate-text` ആയും മാറിയിരിക്കും.

1. `src` ഫോൾഡറിൽ `text_translator.h` എന്ന് പുതിയ ഫയൽ ചേർക്കുക.

1. ഈ പുതിയ `text_translator.h` ഹെഡർ ഫയലിൽ എഴുത്ത് വിവർത്തനം ചെയ്യാനുള്ള ക്ലാസ് സൃഷ്ടിക്കും. താഴെ കൊടുത്തത് കോഡ് ഈ ക്ലാസ് പ്രഖ്യാപിക്കാൻ ചേർക്കുക:

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

    ഇതിൽ `TextTranslator` ക്ലാസ് പ്രഖ്യാപനവും ഈ ക്ലാസ്സിന്റെ ഒരു ഇൻസ്റ്റൻസ് സൃഷ്ടിച്ചതുമുണ്ട്. ക്ലാസ് ഒരു വെൽ ഫോർക്ക WiFi ക്ലയന്റ് ഫീൽഡും ഉൾക്കൊള്ളുന്നു.

1. ഈ ക്ലാസിന്റെ `public` സെക്ഷനിൽ, എഴുത്ത് വിവർത്തനം ചെയ്യാനുള്ള മെത്തോഡ് ചേർക്കുക:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    ഈ മെഥഡ് നിന്ന് ഭാരത്തും ലക്ഷ്യം ഭാരത്തും ഭാഷ എടുക്കുന്നു. വാക്കുകൾ കൈകാര്യം ചെയ്യുമ്പോൾ, ഉപയോക്തൃ ഭാഷയിൽ നിന്നു LUIS സർവർ ഭാഷയിലേക്ക് വിവർത്തനം ചെയ്യും, മറുപടികൾക്കായി LUIS സർവർ ഭാഷയിൽ നിന്ന് ഉപയോക്തൃ ഭാഷയിലേക്ക് വിവർത്തനം ചെയ്യും.

1. ഈ മെത്തോഡിൽ, വിവർത്തനം ചെയ്യാനുള്ള എഴുത്തും ഭാഷകളും ഉൾക്കൊള്ളുന്ന JSON ബോഡി നിർമ്മിക്കാൻ കോഡ് ചേർക്കുക:

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

1. ഇതിനു താഴെ, JSON ബോഡി സെർവർലെസ് ഫങ്ഷൻ ആപ്പിന് അയയ്ക്കാനുള്ള കോഡ് ചേർക്കുക:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. തുടർന്ന്, മറുപടി ലഭിക്കാൻ കോഡ് ചേർക്കുക:

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

1. അവസാനം, കണക്ഷൻ അടയ്ക്കും, വിവർത്തനം ചെയ്‌ത എഴുത്ത് തിരികെ നൽകും കോഡ് ചേർക്കുക:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### പ്രവർത്തി - തിരിച്ചറിയപ്പെട്ട വാക്കുകളും മറുപടികളും വിവർത്തനം ചെയ്യുക

1. `main.cpp` ഫയൽ തുറക്കുക.

1. ഫയലിന്റെ മുകളിൽ `TextTranslator` ക്ലാസിന്റെ ഹെഡർ ഫയൽ ഉൾപ്പെടുത്തുന്നതിനുള്ള ഇൻക്ലൂഡ് നിർദ്ദേശം ചേർക്കുക:

    ```cpp
    #include "text_translator.h"
    ```

1. ടൈമർ സജ്ജമാക്കുമ്പോഴോ കാലഹരണപ്പെടുമ്പോഴോ പറയുന്ന എഴുത്ത് വിവർത്തനം ചെയ്യേണ്ടതുണ്ട്. ഇതിന്, `say` ഫങ്ഷന്റെ ആദ്യ വരിയായി താഴെ കൊടുത്തത് ചേർക്കുക:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ഇത് എഴുത്ത് ഉപയോക്തൃ ഭാഷയിലേക്ക് വിവർത്തനം ചെയ്യും.

1. `processAudio` ഫങ്ഷനിൽ, വാചകം പിടിച്ചെടുത്ത് `String text = speechToText.convertSpeechToText();` വിളിച്ച് എടുക്കുന്നു. ഈ വിളിക്കയത്തിലെ ശേഷം, എഴുത്ത് വിവർത്തനം ചെയ്യുക:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ഇത് ഉപയോക്തൃ ഭാഷയിൽ നിന്നു സർവർ ഭാഷയിലേക്ക് വാചകത്തെ വിവർത്തനം ചെയ്യും.

1. ഈ കോഡ് ബിൽഡ് ചെയ്ത് നിങ്ങളുടെ Wio ടെർമിനലിലേക്ക് അപ്‌ലോഡ് ചെയ്ത് സീരിയൽ മോണിറ്ററും വഴി പരീക്ഷിക്കാം. സീരിയൽ മോണിറ്ററിൽ `Ready` കാണുമ്പോൾ, C ബട്ടൺ (ഇടത് വശം, പവർ സ്വിച്ച് അടുത്തുള്ളത്) അമർത്തി സംസാരിക്കുക. നിങ്ങളുടെ ഫങ്ഷൻ ആപ്പ് പ്രവർത്തിക്കുന്നുവെന്ന് ഉറപ്പാക്കുക, ഉപയോക്തൃ ഭാഷയിൽ ടൈമർ ആവശ്യപ്പെടുക; നിവേദനങ്ങൾ സ്വയം സംസാരിക്കുകയോ, വിവർത്തന ആപ്പ് ഉപയോഗിക്കുകയോ ചെയ്യാം.

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

> 💁 ഈ കോഡ് [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) ഫോൾഡറിൽ കാണാൻ കഴിയും.

😀 നിങ്ങൾ്റെ ബഹുഭാഷ ആദ്യകാല ടൈമർ പ്രോഗ്രാം വിജയകരമായി ഒരുക്കി!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ടിസ്ലെയിമർ**:  
ഈ ഡോക്യുമെന്റ് എഐ തർജ്മാ സേവനം [Co-op Translator](https://github.com/Azure/co-op-translator) ഉപയോഗിച്ച് തർജ്ജമ ചെയ്തതാണ്. നാം കൃത്യതയ്ക്ക് പരിശ്രമിക്കുന്നത് ഒട്ടും എങ്കിലും, താന്റെ യന്ത്ര തർജ്മകളിൽ പിശകുകളും തെറ്റുകളും ഉണ്ടാകാവുന്നതാണ് എന്ന് ദയവായി ശ്രദ്ധിക്കുക. പ്രാചീന ഭാഷയിൽ ഉള്ള അച്ചടിച്ച ഡോക്യുമെന്റ് പുരോഗമനമായ ഉറവിടമായി കണക്കാക്കണം. നിർണായക വിവരങ്ങൾക്കായി പ്രൊഫഷണൽ മനുഷ്യ തർജ്മ നിർദ്ദേശിക്കപ്പെടുന്നു. ഈ തർജുമാനം ഉപയോഗിച്ചതിന്റെ ഫലമായുണ്ടാകുന്ന ഏതെങ്കിലും തെറ്റായ മനസ്സിലാക്കലുകൾക്കും വ്യാഖ്യാനങ്ങൾക്കും ഞങ്ങൾ ഉത്തരവാദികളല്ല.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->