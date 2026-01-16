<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2026-01-07T03:41:31+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "kn"
}
-->
# ಭಾಷಾಂತರಿಸಿ ಭಾಷಣ - ವಿಯೋ ಟರ್ಮಿನಲ್

ಈ ಪಾಠದ ಭಾಗದಲ್ಲಿ ನೀವು ಭಾಷಾಂತರಕ ಸೇವೆಯನ್ನು ಬಳಸಿ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ಕೋಡ್ ಬರೆಯುತ್ತೀರಿ.

## ಭಾಷಾಂತರಕ ಸೇವೆಯನ್ನು ಬಳಸಿ ಪಠ್ಯವನ್ನು ಮಾತನಾಡಿ ಬದಲಿಸಿ

ಭಾಷಣ ಸೇವೆಯ REST API ನೇರ ಭಾಷಾಂತರಗಳನ್ನು ಬೆಂಬಲಿಸುವುದಿಲ್ಲ, ಬದಲಿಗೆ ನೀವು ಭಾಷಣದಿಂದ ಪಠ್ಯದ ಸೇವೆಯಿಂದ ಉತ್ಪನ್ನವಾದ ಪಠ್ಯವನ್ನು ಮತ್ತು ಉಚ್ಚರಿಸಲಾದ ಪ್ರತಿಕ್ರಿಯೆಯ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ಭಾಷಾಂತರಕ ಸೇವೆಯನ್ನು ಬಳಸಬಹುದು. ಈ ಸೇವೆಗೆ REST API ಇರುತ್ತದೆ, ಅದನ್ನು ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ಬಳಸಬಹುದು, ಆದರೆ ಇದನ್ನು ಬಳಸಲು ಸುಲಭವಾಗಿಸಲು ನಿಮ್ಮ ಫಂಕ್ಷನ್‌ಗಳ ಅಪ್ಲಿಕೇಶನ್‌ನಲ್ಲಿ ಮತ್ತೊಂದು HTTP ಟ್ರಿಗರ್‌ನಲ್ಲಿ ಮൂടಲಾಗುತ್ತದೆ.

### ಕಾರ್ಯ - ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ಒಂದು ಸರ್ವರ್‌ಲೆಸ್ ಫಂಕ್ಷನ್ ರಚಿಸಿ

1. ನಿಮ್ಮ `smart-timer-trigger` ಯೋಜನೆಯನ್ನು VS ಕೋಡ್‌ನಲ್ಲಿ ತೆರೆಯಿರಿ ಮತ್ತು ಟರ್ಮಿನಲ್ ತೆರೆಯಿರಿ, ವರ್ಚ್ಯುಯಲ್ ಪರಿಸರ (virtual environment) ಸಕ್ರಿಯಗೊಂಡಿರುವುದಾಗಿ ಖಚಿತಪಡಿಸಿಕೊಳ್ಳಿ. ಇಲ್ಲದಿದ್ದರೆ, ಟರ್ಮಿನಲ್ ಅನ್ನು ನಿಲ್ಲಿಸಿ ಮತ್ತು ಮರುಸೃಷ್ಟಿಸಿ.

1. `local.settings.json` ಫೈಲನ್ನು ತೆರೆಯಿರಿ ಮತ್ತು ಭಾಷಾಂತರಕ API ಕೀ ಮತ್ತು ಸ್ಥಳಕ್ಕಾಗಿ ಸೆಟ್ಟಿಂಗ್ಸ್ ಅನ್ನು ಸೇರಿಸಿ:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    ನಿಮ್ಮ ಭಾಷಾಂತರಕ ಸೇವಾ ಸಂಪನ್ಮೂಲಕ್ಕಾಗಿ API ಕೀ `<key>` ಅನ್ನು ಬದಲಾಯಿಸಿ. ನೀವು ಭಾಷಾಂತರಕ ಸೇವಾ ಸಂಪನ್ಮೂಲವನ್ನು ರಚಿಸಿದಾಗ ಬಳಸಿದ ಸ್ಥಳ `<location>` ಅನ್ನು ಬದಲಾಯಿಸಿ.

1. ಈ ಅಪ್ಲಿಕೇಶನ್‌ಗೆ `translate-text` ಎಂಬ HTTP ಟ್ರಿಗರ್ ಅನ್ನು ಕೆಳಗಿನ ಆಜ್ಞೆಯನ್ನು ಬಳಸಿ VS ಕೋಡ್ ಟರ್ಮಿನಲ್‌ನಲ್ಲಿ ಫಂಕ್ಷನ್ ಆಪ್ ಯೋಜನೆಯ ಮೂಲ ಫೋಲ್ಡರ್‌ನಿಂದ ಸೇರಿಸಿ:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    ಇದು `translate-text` ಎಂಬ HTTP ಟ್ರಿಗರ್ ಅನ್ನು ರಚಿಸುತ್ತದೆ.

1. `translate-text` ಫೋಲ್ಡರ್‌ನ `__init__.py` ಫೈಲಿನ ಒಳзарು ವಿಷಯವನ್ನು ಕೆಳಗಿನಂತಿರಲಿ:

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

    ಈ ಕೋಡ್ HTTP ವಿನಂತಿಯಿಂದ ಪಠ್ಯ ಮತ್ತು ಭಾಷೆಗಳನ್ನ ತೆಗೆದುಕೊಳ್ಳುತ್ತದೆ. ನಂತರ ಭಾಷಾಂತರಕ REST API ಗೆ ವಿನಂತಿ ಮಾಡುತ್ತದೆ, ಭಾಷೆಗಳನ್ನು URL ಪ್ಯಾರಾಮೀಟರ್ಗಳಾಗಿ ಮತ್ತು ಭಾಷಾಂತರಿಸಬೇಕಾದ ಪಠ್ಯವನ್ನು ಬಾಡಿಯಾಗಿ ಕಳುಹಿಸುತ್ತದೆ. ಕೊನೆಗೆ, ಭಾಷಾಂತರಿತ ಪಠ್ಯವನ್ನು ಕೈಗೆತ್ತಿಕೊಳ್ಳುತ್ತದೆ.

1. ನಿಮ್ಮ ಫಂಕ್ಷನ್ ಆಪ್ ಅನ್ನು ಸ್ಥಳೀಯವಾಗಿ ಚಾಲನೆ ಮಾಡಿ. ನಂತರ, ನೀವು `text-to-timer` HTTP ಟ್ರಿಗರ್ ಅನ್ನು ಪರೀಕ್ಷಿಸಿದ ಹಾಗೆ ಈ ಫಂಕ್ಷನ್ನನ್ನು curl ಅಥವಾ ಇತರೆ ಸಾಧನಗಳಿಂದ ಕರೆ ಮಾಡಬಹುದು. JSON ಬಾಡಿಯಾಗಿ ಭಾಷಾಂತರಿಸಲು ಆಗಬೇಕಾದ ಪಠ್ಯ ಮತ್ತು ಭಾಷೆಗಳನ್ನು ಕಳುಹಿಸಿ:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    ಈ ಉದಾಹರಣೆ ಫ್ರೆಂಚ್ ನಿಂದ ಅಮೇರಿಕನ್ ಇಂಗ್ಲಿಷ್‌ಗೆ *Définir une minuterie de 30 secondes* ಅನ್ನು ಭಾಷಾಂತರಿಸುತ್ತದೆ. ಇದು *Set a 30-second timer* ಅನ್ನು ಮರಳಿಸುತ್ತದೆ.

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

### ಕಾರ್ಯ - ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಲು ಭಾಷಾಂತರಕ ಫಂಕ್ಷನ್ನನ್ನು ಬಳಸಿ

1. `smart-timer` ಯೋಜನೆಯನ್ನು VS ಕೋಡ್‌ನಲ್ಲಿ ತೆರೆಯಿರಿ (ಇನ್ನೂ ತೆರೆಯದಿದ್ದರೆ).

1. ನಿಮ್ಮ ಸ್ಮಾರ್ಟ್ ಟೈಮರ್‌ನಲ್ಲಿ 2 ಭಾಷೆಗಳು ಹೊಂದಿಕೊಂಡಿರುತ್ತವೆ - LUIS ಅನ್ನು ತರಬೇತು ಮಾಡಲಾದ ಸರ್ವರ್ ಭಾಷೆ (ಈ ಭಾಷೆಯು ಬಳಕೆದಾರರಿಗೆ ಮಾತನಾಡಲು ಸಂದೇಶಗಳನ್ನು ನಿರ್ಮಿಸಲು ಸಹ ಬಳಸಲಾಗುತ್ತದೆ), ಹಾಗೂ ಬಳಕೆದಾರರ ಮಾತಿನ ಭಾಷೆ. `config.h` ಹೆಡರ್ ಫೈಲಿನ `LANGUAGE` ಸ್ಥಿರಾಂಕವನ್ನು ಬಳಕೆದಾರ बोलेಸುವ ಭಾಷೆಯಾಗಿ ನವೀಕರಿಸಿ ಹಾಗೂ LUIS ತರಬೇತಿಗೆ ಬಳಸುವ ಭಾಷೆಯಿಗಾಗಿ `SERVER_LANGUAGE` ಎಂಬ ಹೊಸ ಸ್ಥಿರಾಂಕ ಸೇರಿಸಿ:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    ನೀವು ಮಾತನಾಡುವ ಭಾಷೆಯ ಸ್ಥಳೀಯ ನಾಮವನ್ನು `<user language>` ನಲ್ಲಿ ಬದಲಾಯಿಸಿ, ಉದಾಹರಣೆಗೆ ಫ್ರೆಂಚ್‌ಗಾಗಿ `fr-FR`, ಕ್ಯಾಂಟೋನೀಸ್‌ಗಾಗಿ `zn-HK`.

    LUIS ತರಬೇತಿಗಾಗಿ ಉಪಯೋಗಿಸಿದ ಭಾಷೆಯ ಸ್ಥಳೀಯ ನಾಮವನ್ನು `<server language>` ನಲ್ಲಿ ಬದಲಾಯಿಸಿ.

    [Microsoft ಡಾಕ್ಸ್‌ನಲ್ಲಿ ಭಾಷಾ ಹಾಗೂ ಧ್ವನಿ ಬೆಂಬಲ ದಾಖಲೆ](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)ಯಲ್ಲಿ ಬೆಂಬಲಿತ ಭಾಷೆಗಳ ಹಾಗೂ ಅವುಗಳ ಸ್ಥಳೀಯ ನಾಮಗಳ ಪಟ್ಟಿಯನ್ನು ಕಾಣಬಹುದು.

    > 💁 ನೀವು ಬಹುಭಾಷೆಯ ವಿಷಯದಲ್ಲಿ ಪರಿಣಿತರಾಗದಿದ್ದರೆ, ನಿಮ್ಮ ಇಚ್ಛಿತ ಭಾಷೆಯಿಂದ ಬೇರೆ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸಲು [Bing Translate](https://www.bing.com/translator) ಅಥವಾ [Google Translate](https://translate.google.com) ಸೇವೆಗಳನ್ನು ಬಳಸಬಹುದು. ಈ ಸೇವೆಗಳು ನಂತರ ಭಾಷಾಂತರಿತ ಪಠ್ಯದ ಧ್ವನಿಯನ್ನು ಪ್ಲೇ ಮಾಡಲು ಸಹ ಸಾಧ್ಯವಾಗುತ್ತವೆ.
    >
    > ಉದಾಹರಣೆಗೆ, ನೀವು LUIS ಅನ್ನು ಇಂಗ್ಲಿಷಿನಲ್ಲಿ ತರಬೇತುಗೊಳಿಸಿದರೂ, ಬಳಕೆದಾರ ಭಾಷೆಾಗಿ ಫ್ರೆಂಚ್ ಬಳಸಲು ಬಯಸಿದರೆ, ಬಿಂಗ್ ಟ್ರಾನ್ಸ್‌ಲೇಟ್ ಬಳಸಿ "set a 2 minute and 27 second timer" ಇಂಗ್ಲಿಷಿನಿಂದ ಫ್ರೆಂಚ್‌ಗೆ ಭಾಷಾಂತರಿಸಿ, ನಂತರ **Listen translation** ಬಟನ್ ಮೂಲಕ ಆ ಭಾಷಾಂತರವನ್ನು ನಿಮ್ಮ ಮೈಕ್ರೋಫೋನಿಗೆ ಮಾತನಾಡಿಸಬಹುದು.
    >
    > ![Bing Translate上的“听翻译”按钮](../../../../../translated_images/kn/bing-translate.348aa796d6efe2a9.png)

1. `SPEECH_LOCATION` ಕೆಳಗೆ ಭಾಷಾಂತರಕ API ಕೀ ಮತ್ತು ಸ್ಥಳ ಸೇರಿಸಿ:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    ನಿಮ್ಮ ಭಾಷಾಂತರಕ ಸೇವಾ ಸಂಪನ್ಮೂಲ API ಕೀ `<KEY>` ಮತ್ತು ಸ್ಥಳ `<LOCATION>` ಬದಲಾಯಿಸಿ.

1. `VOICE_URL` ಕೆಳಗೆ ಭಾಷಾಂತರಕ ಟ್ರಿಗರ್ URL ಸೇರಿಸಿ:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    ನಿಮ್ಮ ಫಂಕ್ಷನ್ ಆಪ್‌ನ `translate-text` HTTP ಟ್ರಿಗರ್ URL `<URL>` ಬದಲಾಯಿಸಿ. ಇದು `TEXT_TO_TIMER_FUNCTION_URL` ನಂತೆ ಇರಬೇಕು, ಆದರೆ ಫಂಕ್ಷನ್ ಹೆಸರು `translate-text` ಆಗಿರಬೇಕು, `text-to-timer` ಬದಲಿಗೆ.

1. `src` ಫೋಲ್ಡರ್‌ಗೆ `text_translator.h` ಎಂಬ ಹೊಸ ಫೈಲ್ ಸೇರಿಸಿ.

1. ಈ ಹೊಸ `text_translator.h` ಹೆಡರ್ ಫೈಲ್ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸುವ ಕ್ಲಾಸ್ ಹೊಂದಿರುತ್ತದೆ. ಈ ಕೆಳಗಿನದು ಈ ಕ್ಲಾಸ್ ಘೋಷಿಸಲು ಬೇಕು:

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

    ಇದು `TextTranslator` ಕ್ಲಾಸ್ ಮತ್ತು ಒಂದು ಉದಾಹರಣೆ ಘೋಷಿಸುತ್ತದೆ. ಈ ಕ್ಲಾಸಿನಲ್ಲಿ WiFi ಕ್ಲಯಂಟ್‌ಗೆ ಒಂದು ಕ್ಷೇತ್ರವಿದೆ.

1. ಈ ಕ್ಲಾಸ್‌ನ `public` ವಿಭಾಗದಲ್ಲಿ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸುವ ಮೆತೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    ಈ ಮೆತೋಡ್ ಭಾಷೆ FROM ಮತ್ತು ಭಾಷೆ TO ರೀಸ್ವಿಗೆ ಕರೆ ಮಾಡುತ್ತದೆ. ಭಾಷಣ ನಿರ್ವಹಿಸುವಾಗ, ಭಾಷಣವನ್ನು ಬಳಕೆದಾರ ಭಾಷೆಯಿಂದ LUIS ಸರ್ವರ್ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸಲಾಗುತ್ತದೆ; ಪ್ರತಿಕ್ರಿಯೆಗಳನ್ನು ಕೊಡುವಾಗ LUIS ಸರ್ವರ್ ಭಾಷೆಯಿಂದ ಬಳಕೆದಾರ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸಲಾಗುತ್ತದೆ.

1. ಈ ಮೆತೋಡ್‌ನಲ್ಲಿ, ಭಾಷಾಂತರಿಸಬೇಕಾದ ಪಠ್ಯ ಮತ್ತು ಭಾಷೆಗಳನ್ನು ಒಳಗೊಂಡ JSON ಬಾಡಿ ಸಂಕಲಿಸಲು ಕೋಡ್ ಸೇರಿಸಿ:

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

1. ಇದರ ಕೆಳಗೆ, ಬಾಡಿಯನ್ನು ಸರ್ವರ್‌ಲೆಸ್ ಫಂಕ್ಷನ್ ಆಪಿಗೆ ಕಳುಹಿಸಲು ಕೆಳಗಿನ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. ನಂತರ, ಪ್ರತಿಕ್ರಿಯೆಯನ್ನು ಪಡೆಯುವ ಕೋಡ್ ಸೇರಿಸಿ:

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

1. ಕೊನೆಗೆ, ಸಂಪರ್ಕವನ್ನು ಮುಚ್ಚಿ ಭಾಷಾಂತರಿತ ಪಠ್ಯವನ್ನು ಮರಳಿಸುವ ಕೋಡ್ ಸೇರಿಸಿ:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### ಕಾರ್ಯ - ಗುರುತಿಸಿದ ಭಾಷಣ ಮತ್ತು ಪ್ರತಿಕ್ರಿಯೆಗಳನ್ನು ಭಾಷಾಂತರಿಸಿ

1. `main.cpp` ಫೈಲನ್ನು ತೆರೆಯಿರಿ.

1. ಫೈಲ್ ಮٿೆಯಲ್ಲಿ `TextTranslator` ಕ್ಲಾಸ್ ಹೆಡರ್ ಫೈಲ್ನ ಇನ್ಕ್ಲೂಡ್ ನಿರ್ದೇಶನ ಸೇರಿಸಿ:

    ```cpp
    #include "text_translator.h"
    ```

1. ಟೈಮರ್ ಸೆಟ್ ಅಥವಾ ಅವಧಿ ಮುಗಿದಾಗ ಹೇಳಲಾಗುವ ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಬೇಕಾಗುತ್ತದೆ. ಇದಕ್ಕಾಗಿ, `say` ಫಂಕ್ಷನ್‌ನ ಮೊದಲ ಸಾಲಾಗಿ ಕೆಳಗಿನ ಸಾಲು ಸೇರಿಸಿ:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ಇದು ಪಠ್ಯವನ್ನು ಬಳಕೆದಾರರ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸುತ್ತದೆ.

1. `processAudio` ಫಂಕ್ಷನ್‌ನಲ್ಲಿ, ಅಂಗೀಕೃತ ಧ್ವನಿಯಿಂದ ಪಠ್ಯ `String text = speechToText.convertSpeechToText();` ಕರೆಮೂಲಕ ಪಡೆಯಲ್ಪಡುತ್ತದೆ. ಈ ಕರೆ ನಂತರ, ಪಠ್ಯವನ್ನು ಭಾಷಾಂತರಿಸಿ:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    ಇದು ಪಠ್ಯವನ್ನು ಬಳಕೆದಾರ ಭಾಷೆಯಿಂದ ಸರ್ವರ್ ಬಳಸಿದ ಭಾಷೆಗೆ ಭಾಷಾಂತರಿಸುತ್ತದೆ.

1. ಈ ಕೋಡ್ ಅನ್ನು ನಿರ್ಮಿಸಿ, ನಿಮ್ಮ Wio ಟರ್ಮಿನಲ್ ಗೆ ಅಪ್‌ಲೋಡ್ ಮಾಡಿ ಮತ್ತು ಸೀರಿಯಲ್ ಮಾನಿಟರ್ ಮೂಲಕ ಪರೀಕ್ಷಿಸಿ. ಸೀರಿಯಲ್ ಮಾನಿಟರ್‌ನಲ್ಲಿ `Ready` ತೋರುವುದಾದರೆ, ಎಡ ಬದರೆಯಲ್ಲಿರುವ “C” ಬಟನ್ ಒತ್ತಿ ಮತ್ತು ಮಾತನಾಡಿ. ನಿಮ್ಮ ಫಂಕ್ಷನ್ ಆಪ್ ಚಾಲನೆಯಲ್ಲಿರುವುದನ್ನು ಖಚಿತಪಡಿಸಿ ಮತ್ತು ಬಳಕೆದಾರ ಭಾಷೆಯಲ್ಲಿ ಟೈಮರ್ ವಿನಂತಿಸಿರಿ, ನೀವು ತಾವು ಆ ಭಾಷೆಯಲ್ಲಿ ಮಾತನಾಡಲಿ ಅಥವಾ ಭಾಷಾಂತರ ಆಪ್ ಬಳಸಲಿ.

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

> 💁 ನೀವು ಈ ಕೋಡ್ ಅನ್ನು [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) ಫೋಲ್ಡರ್‌ನಲ್ಲಿ ಕಾಣಬಹುದು.

😀 ನಿಮ್ಮ ಬಹುಭಾಷಾ ಟೈಮರ್ ಪ್ರೋಗ್ರಾಂ ಯಶಸ್ವಿಯಾಯಿತು!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ತ್ಯಾಜ್ಯ ಪ್ರಕಟಣೆ**:
ಈ ಡಾಕ್ಯುಮೆಂಟ್ ಅನ್ನು AI ಅನುವಾದ ಸೇವೆ [Co-op Translator](https://github.com/Azure/co-op-translator) ಉಪಯೋಗಿಸಿ ಅನುವಾದಿಸಲಾಗಿದೆ. ನಾವು ನಿಖರತೆಯಕ್ಕಾಗಿ ಪ್ರಯತ್ನಿಸುತ್ತಿದ್ದರೂ, ಸ್ವಯಂಚಾಲಿತ ಅನುವಾದಗಳಲ್ಲಿ ದೋಷಗಳು ಅಥವಾ ಅಸತ್ಯತೆಗಳಿರಬಹುದೆಂದು ದಯವಿಟ್ಟು ಗಮನಿಸಿ. ಮೂಲ ಭಾಷೆಯಲ್ಲಿನ ಮೂಲ ಡಾಕ್ಯುಮೆಂಟ್ ಅನ್ನು ಪ್ರಮಾಣಿಕ ಮೂಲವೆಂದು ಪರಿಗಣಿಸಬೇಕು. ಪ್ರಮುಖ ಮಾಹಿತಿಗಾಗಿ ವೃತ್ತಿಪರ ಮಾನವ ಅನುವಾದವನ್ನು ಶಿಫಾರಸು ಮಾಡಲಾಗುತ್ತದೆ. ಈ ಅನುವಾದವನ್ನು ಬಳಸಿದ ಪರಿಣಾಮದಲ್ಲಿ ಸಂಭವಿಸುವ ಯಾವದಾದರೂ ತಪ್ಪು ಅర్థಕಮನಗಳು ಅಥವಾ ತರ್ಜೀಮೆಯಲ್ಲಿ ನಾವು ಹೊಣೆಗಾರರಾಗಿರುವುದಿಲ್ಲ.
<!-- CO-OP TRANSLATOR DISCLAIMER END -->