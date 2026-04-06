# បកប្រែសូភាសា - Wio Terminal

ក្នុងផ្នែកនេះនៃមេរៀន អ្នកនឹងសរសេរកូដដើម្បីបកប្រែអត្ថបទដោយប្រើសេវាកម្មអ្នកបកប្រែ។

## បំលែងអត្ថបទទៅជាសូរ្យដោយប្រើសេវាកម្មអ្នកបកប្រែ

សេវាកម្មសូរ្យ REST API មិនគាំទ្រការបកប្រែដោយផ្ទាល់ទេ ទោះយ៉ាងណា អ្នកអាចប្រើសេវាកម្មអ្នកបកប្រែ ដើម្បីបកប្រែអត្ថបទដែលបានបង្កើតដោយសេវាកម្មសូរ្យទៅអត្ថបទ និងអត្ថបទនៃការឆ្លើយតបទៅជាសូរ្យ។ សេវាកម្មនេះមាន REST API ដែលអ្នកអាចប្រើដើម្បីបកប្រែអត្ថបទ ប៉ុន្តែដើម្បីឲ្យងាយស្រួលក្នុងការប្រើ នេះនឹងត្រូវបានរុំជុំក្នុងវីធីគ្រាប់ HTTP ផ្សេងទៀតនៅក្នុងកម្មវិធី function របស់អ្នក។

### ភារកិច្ច - បង្កើត function ដែលមិនមានម៉ាស៊ីនបម្រើសម្រាប់បកប្រែអត្ថបទ

1. បើកគម្រោង `smart-timer-trigger` របស់អ្នកនៅក្នុង VS Code ហើយបើក terminal ដើម្បីធានាថាបរិយាកាសសំណុំបែបបទបានដំណើរការ។ ប្រសិនបើមិនដំណើរការ សូមបិទ ហើយបង្កើត terminal ថ្មីម្តងទៀត។

1. បើកក្រុមហ៊ុន `local.settings.json` ហើយបន្ថែមការកំណត់សម្រាប់កូនសោ API និងទីតាំងសម្រាប់សេវាកម្មអ្នកបកប្រែ៖

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    ជំនួស `<key>` ជាមួយកូនសោ API សម្រាប់ធនធានសេវាកម្មអ្នកបកប្រែរបស់អ្នក។ ជំនួស `<location>` ជាមួយទីតាំងដែលអ្នកប្រើពេលបង្កើតធនធានសេវាកម្មអ្នកបកប្រែ។

1. បន្ថែម HTTP trigger ថ្មីឈ្មោះ `translate-text` ទៅកម្មវិធីនេះដោយប្រើពាក្យបញ្ជាតាមដំណាក់កាលក្នុង terminal VS Code នៅថត root របស់គម្រោង function app៖

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    វានឹងបង្កើត HTTP trigger ឈ្មោះ `translate-text`។

1. ជំនួសមាតិកានៃឯកសារ `__init__.py` នៅក្នុងថត `translate-text` ជាមួយអ្វីដូចខាងក្រោម៖

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

    កូដនេះដកអត្ថបទ និងភាសាពីសំណើ HTTP។ បន្ទាប់មកវាចេញសំណើទៅកាន់ REST API នៃអ្នកបកប្រែ ដោយផ្ញើភាសាជាពារព័ន្ធសម្រាប់ URL និងអត្ថបទដែលត្រូវបកប្រែជារូបភាពសម្រាប់ body។ ហើយចុងក្រោយ បកប្រែត្រូវបានត្រឡប់មកវិញ។

1. ដំណើរការកម្មវិធី function app របស់អ្នកក្នុងបរិយាកាសក្នុងមូលដ្ឋាន។ បន្ទាប់មក អ្នកអាចហៅវាតាមរបៀបប្រើឧបករណ៍ដូចជា curl ដូច្នេះអ្នកបានសាកល្បង HTTP trigger `text-to-timer` របស់អ្នក។ សូមប្រាកដថាបញ្ជូនអត្ថបទដែលត្រូវបកប្រែ និងភាសាជាលំហូរជា JSON body៖

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    ឧទាហរណ៍នេះបកប្រែ *Définir une minuterie de 30 secondes* ពីភាសាបារាំងទៅភាសាអង់គ្លេសអាមេរិក។ វានឹងត្រឡប់បាន *Set a 30-second timer*។

> 💁 អ្នកអាចរកឃើញកូដនេះនៅក្នុងថត [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions)។

### ភារកិច្ច - ប្រើ function អ្នកបកប្រែដើម្បីបកប្រែអត្ថបទ

1. បើកគម្រោង `smart-timer` ក្នុង VS Code ប្រសិនបើវាមិនត្រូវបានបើករួចទេ។

1. ម៉ោងរាប់អ៊ីវ៉ែនឌង់របស់អ្នកនឹងមានភាសា 2 ភាសាត្រូវបានកំណត់ - ភាសានៃម៉ាស៊ីនបម្រើដែលបានប្រើសម្រាប់បណ្តុះបណ្តាល LUIS (ភាសាដដែលក៏បានប្រើសម្រាប់បង្កើតសារដែលនឹងនិយាយទៅឲ្យអ្នកប្រើ) និងភាសាដែលអ្នកប្រើនិយាយ។ អាប់ដេតថេរ `LANGUAGE` នៅក្នុងឯកសារ header `config.h` ដើម្បីជា ភាសាដែលនឹងនិយាយដោយអ្នកប្រើ ហើយបន្ថែមថេរ ថ្មីមួយរបស់ឈ្មោះ `SERVER_LANGUAGE` សម្រាប់ភាសាដែលប្រើសម្រាប់បណ្តុះបណ្តាល LUIS៖

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    ជំនួស `<user language>` ជាជាឈ្មោះ locale សម្រាប់ភាសាដែលអ្នកនឹងនិយាយ ឧទាហរណ៍ `fr-FR` សម្រាប់ភាសាបារាំង ឬ `zn-HK` សម្រាប់ភាសាកាន់តូន៉េស។

    ជំនួស `<server language>` ជាឈ្មោះ locale សម្រាប់ភាសាដែលបានប្រើសម្រាប់បណ្តុះបណ្តាល LUIS។

    អ្នកអាចរកបញ្ជីភាសាដែលគាំទ្រនិងឈ្មោះ locale របស់ពួកវានៅក្នុង [ឯកសារគាំទ្រភាសា និងសូរ្យនៅលើឯកសារ Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)។

    > 💁 ប្រសិនបើអ្នកមិននិយាយភាសាច្រើន អ្នកអាចប្រើសេវាកម្មដូចជា [Bing Translate](https://www.bing.com/translator) ឬ [Google Translate](https://translate.google.com) ដើម្បីបកប្រែពីភាសាដែលអ្នកចូលចិត្តទៅភាសាដែលអ្នកចង់បាន។ សេវាកម្មទាំងនេះអាចលេងសម្លេងសំឡេងអត្ថបទដែលបានបកប្រែ។

    > ឧទាហរណ៍ ប្រសិនបើអ្នកបណ្តុះបណ្តាល LUIS ជាភាសាអង់គ្លេស ប៉ុន្តាចង់ប្រើភាសាបារាំងជាភាសាអ្នកប្រើ អ្នកអាចបកប្រែប្រយោគដូចជា "set a 2 minute and 27 second timer" ពីភាសាអង់គ្លេស ទៅភាសាបារាំង ដោយប្រើ Bing Translate បន្ទាប់មកប្រើប៊ូតុង **Listen translation** ដើម្បីនិយាយការបកប្រែតាមមីក្រូហ្វូនរបស់អ្នក។

    > ![ប៊ូតុងនិយាយការបកប្រែលើ Bing translate](../../../../../translated_images/km/bing-translate.348aa796d6efe2a9.webp)

1. បន្ថែមកូនសោ API នៃអ្នកបកប្រែ និងទីតាំងខាងក្រោម `SPEECH_LOCATION`៖

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    ជំនួស `<KEY>` ជាមួយកូនសោ API ផ្នែកធនធានសេវាកម្មអ្នកបកប្រែរបស់អ្នក។ ជំនួស `<LOCATION>` ជាមួយទីតាំងដែលអ្នកប្រើពេលបង្កើតធនធានសេវាកម្មអ្នកបកប្រែ។

1. បន្ថែម URL នៃអ្នកបកប្រែ trigger ខាងក្រោម `VOICE_URL`៖

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    ជំនួស `<URL>` ជា URL សម្រាប់ HTTP trigger `translate-text` លើកម្មវិធី function app របស់អ្នក។ វានឹងដូចនឹងតម្លៃសម្រាប់ `TEXT_TO_TIMER_FUNCTION_URL` ប៉ុន្តែម្នាក់ឯងមានឈ្មោះ function ជា `translate-text` មិនមែន `text-to-timer` ទេ។

1. បន្ថែមឯកសារថ្មីមួយទៅថត `src` ឈ្មោះ `text_translator.h`។

1. ឯកសារ header ថ្មីនេះ `text_translator.h` នឹងមានថ្នាក់សម្រាប់បកប្រែអត្ថបទ។ បន្ថែមអ្វីខាងក្រោមទៅឯកសារនេះដើម្បីប្រកាសថ្នាក់នេះ៖

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

    នេះប្រកាសថ្នាក់ `TextTranslator` ជាមួយនឹងឧទាហរណ៍មួយនៃថ្នាក់នេះ។ ថ្នាក់មានព_field_តែមួយសម្រាប់ client WiFi។

1. នៅផ្នែក `public` នៃថ្នាក់នេះ បន្ថែមវិធីសាស្ត្រមួយសម្រាប់បកប្រែអត្ថបទ៖

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    វិធីសាស្ត្រនេះទទួលភាសាដែលត្រូវបកប្រែពី និងភាសាដែលត្រូវបកប្រែទៅ។ នៅពេលដំណើរការសូរ្យ សូរ្យនឹងត្រូវបកប្រែពីភាសាអ្នកប្រើទៅភាសាម៉ាស៊ីនបម្រើ LUIS ហើយនៅពេលផ្តល់ចម្លើយ វានឹងបកប្រែពីភាសា LUIS ម៉ាស៊ីនបម្រើ ទៅភាសា អ្នកប្រើ។

1. ក្នុងវិធីសាស្ត្រនេះ បន្ថែមកូដដើម្បីបង្កើត JSON body ដែលមានអត្ថបទដែលត្រូវបកប្រែ និងភាសា៖

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

1. ខាងក្រោមនេះ បន្ថែមកូដដើម្បីផ្ញើ body ទៅកម្មវិធី function app ដែលមិនមានម៉ាស៊ីនបម្រើ៖

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. បន្ទាប់មក បន្ថែមកូដដើម្បីទទួលបានការឆ្លើយតប៖

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

1. ចុងក្រោយ បន្ថែមកូដដើម្បីបិទការតភ្ជាប់ និងត្រឡប់អត្ថបទដែលបានបកប្រែ៖

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### ភារកិច្ច - បកប្រែសូរ្យដែលត្រូវបានទទួលស្គាល់ និងចម្លើយ

1. បើកឯកសារ `main.cpp`។

1. បន្ថែមបញ្ជា include នៅខាងលើឯកសារ សម្រាប់ឯកសារ header នៃថ្នាក់ `TextTranslator`៖

    ```cpp
    #include "text_translator.h"
    ```

1. អត្ថបទដែលនិយាយពេលម៉ោងធ្វើការកំណត់ ឬផុតកំណត់ត្រូវបានបកប្រែ។ ដើម្បីធ្វើបាន នេះ បន្ថែមអត្ថបទដូចខាងក្រោមជាថ្មីជួរដាក់ជួរដំបូងរបស់មុខងារ `say`៖

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    វានឹងបកប្រែអត្ថបទទៅភាសាអ្នកប្រើ។

1. ក្នុងមុខងារ `processAudio` អត្ថបទត្រូវបានទាញយកពីសម្លេងដែលបានចាប់យកជាមួយកាល `String text = speechToText.convertSpeechToText();`។ បន្ទាប់ពីការហៅនេះ បកប្រែអត្ថបទ៖

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    វានឹងបកប្រែអត្ថបទពីភាសាអ្នកប្រើទៅភាសាដែលប្រើនៅលើម៉ាស៊ីនបម្រើ។

1. បង្កើតកូដនេះ​, បញ្ចូនវាទៅ Wio Terminal របស់អ្នក ហើយសាកល្បងវាតាមរយៈម៉ូនីទ័រ serial។ បន្ទាប់ពីអ្នកឃើញ `Ready` នៅក្នុងម៉ូនីទ័រ serial សូមចុចប៊ូតុង C (ប៊ូតុងនៅខាងឆ្វេងសំរាប់ជិតប៊ូតុងថាមពល) ហើយនិយាយ។ សូមប្រាកដថាកម្មវិធី function app របស់អ្នកកំពុងដំណើរការ ហើយស្នើសុំម៉ោងរាប់ជាភាសាអ្នកប្រើ ម្តងទៀត អាចនិយាយភាសានេះដោយខ្លួនឯង ឬប្រើកម្មវិធីបកប្រែ។

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

> 💁 អ្នកអាចរកឃើញកូដនេះនៅក្នុងថត [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal)។

😀 ប្រ​កា​ស​លទ្ធិ​កម្ម​កម្មវិធីម៉ោងរាប់ភាសាច្រើន​របស់​អ្នកបាន​ជោគជ័យ!

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**ការបញ្ចាក់**៖  
ឯកសារនេះត្រូវបានបម្លែងភាសាដោយប្រើសេវាកម្មបកប្រែ AI [Co-op Translator](https://github.com/Azure/co-op-translator)។ ខណៈពេលដែលយើងខិតខំធ្វើឱ្យបានត្រឹមត្រូវ សូមប្រយ័ត្នថាការបកប្រែដោយស្វ័យប្រវត្តិនេះអាចមានកំហុសឬមិនត្រឹមត្រូវខ្លះ។ ឯកសារដើមក្នុងភាសាតំណើរការមានតម្លៃជារបស់ដើមដែលអាចជាការយោងដ៏ត្រឹមត្រូវ។ សម្រាប់ព័ត៌មានសំខាន់សូមណែនាំឱ្យបកប្រែដោយអ្នកជំនាញមនុស្សជាផ្លូវការជំនួយ។ យើងមិនទទួលខុសត្រូវចំពោះការយល់ច្រឡំ ឬការបកប្រែខុសៗនាដែលកើតមានពីការប្រើប្រាស់ការបកប្រែនេះនោះទេ។
<!-- CO-OP TRANSLATOR DISCLAIMER END -->