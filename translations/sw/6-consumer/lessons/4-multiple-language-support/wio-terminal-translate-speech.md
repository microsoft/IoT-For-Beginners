<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T21:31:56+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "sw"
}
-->
# Tafsiri hotuba - Wio Terminal

Katika sehemu hii ya somo, utaandika msimbo wa kutafsiri maandishi ukitumia huduma ya mtafsiri.

## Badilisha maandishi kuwa hotuba ukitumia huduma ya mtafsiri

API ya REST ya huduma ya hotuba haiungi mkono tafsiri za moja kwa moja. Badala yake, unaweza kutumia huduma ya Translator kutafsiri maandishi yanayotokana na huduma ya hotuba hadi maandishi, pamoja na maandishi ya majibu yanayozungumzwa. Huduma hii ina API ya REST unayoweza kutumia kutafsiri maandishi, lakini ili iwe rahisi kutumia, itafungwa ndani ya trigger nyingine ya HTTP kwenye programu yako ya functions.

### Kazi - unda function isiyo na server ya kutafsiri maandishi

1. Fungua mradi wako wa `smart-timer-trigger` kwenye VS Code, na fungua terminal ukihakikisha mazingira ya virtual yamewashwa. Ikiwa hayajawashwa, zima na uunde upya terminal.

1. Fungua faili ya `local.settings.json` na ongeza mipangilio ya API key ya mtafsiri na eneo:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Badilisha `<key>` na API key ya rasilimali yako ya huduma ya mtafsiri. Badilisha `<location>` na eneo ulilotumia ulipounda rasilimali ya huduma ya mtafsiri.

1. Ongeza trigger mpya ya HTTP kwenye programu hii inayoitwa `translate-text` ukitumia amri ifuatayo kutoka ndani ya terminal ya VS Code kwenye folda kuu ya mradi wa programu ya functions:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Hii itaunda trigger ya HTTP inayoitwa `translate-text`.

1. Badilisha yaliyomo ya faili ya `__init__.py` kwenye folda ya `translate-text` na yafuatayo:

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

    Msimbo huu unatoa maandishi na lugha kutoka kwenye ombi la HTTP. Kisha unatuma ombi kwa API ya REST ya mtafsiri, ukipita lugha kama vigezo vya URL na maandishi ya kutafsiri kama mwili. Hatimaye, tafsiri inarudishwa.

1. Endesha programu yako ya functions kwa ndani. Unaweza kisha kuiita ukitumia zana kama curl kwa njia ile ile ulivyopima trigger ya HTTP ya `text-to-timer`. Hakikisha unapita maandishi ya kutafsiri na lugha kama mwili wa JSON:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Mfano huu unatafsiri *Définir une minuterie de 30 secondes* kutoka Kifaransa hadi Kiingereza cha Marekani. Itarudisha *Set a 30-second timer*.

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Kazi - tumia function ya mtafsiri kutafsiri maandishi

1. Fungua mradi wa `smart-timer` kwenye VS Code ikiwa haujafunguliwa tayari.

1. Kipima muda chako cha smart kitakuwa na lugha 2 zilizowekwa - lugha ya seva iliyotumika kufundisha LUIS (lugha hiyo hiyo pia hutumika kujenga ujumbe wa kuzungumza na mtumiaji), na lugha inayozungumzwa na mtumiaji. Sasisha thamani ya `LANGUAGE` kwenye faili ya kichwa ya `config.h` kuwa lugha itakayozungumzwa na mtumiaji, na ongeza thamani mpya inayoitwa `SERVER_LANGUAGE` kwa lugha iliyotumika kufundisha LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Badilisha `<user language>` na jina la locale kwa lugha utakayozungumza, kwa mfano `fr-FR` kwa Kifaransa, au `zn-HK` kwa Kantonese.

    Badilisha `<server language>` na jina la locale kwa lugha iliyotumika kufundisha LUIS.

    Unaweza kupata orodha ya lugha zinazoungwa mkono na majina yao ya locale kwenye [Nyaraka za msaada wa lugha na sauti kwenye Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ikiwa huzungumzi lugha nyingi, unaweza kutumia huduma kama [Bing Translate](https://www.bing.com/translator) au [Google Translate](https://translate.google.com) kutafsiri kutoka lugha unayopendelea hadi lugha unayochagua. Huduma hizi zinaweza pia kucheza sauti ya maandishi yaliyotafsiriwa.
    >
    > Kwa mfano, ikiwa unafundisha LUIS kwa Kiingereza, lakini unataka kutumia Kifaransa kama lugha ya mtumiaji, unaweza kutafsiri sentensi kama "set a 2 minute and 27 second timer" kutoka Kiingereza hadi Kifaransa ukitumia Bing Translate, kisha tumia kitufe cha **Listen translation** kuzungumza tafsiri hiyo kwenye kipaza sauti chako.
    >
    > ![Kitufe cha listen translation kwenye Bing translate](../../../../../translated_images/sw/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Ongeza API key ya mtafsiri na eneo chini ya `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Badilisha `<KEY>` na API key ya rasilimali yako ya huduma ya mtafsiri. Badilisha `<LOCATION>` na eneo ulilotumia ulipounda rasilimali ya huduma ya mtafsiri.

1. Ongeza URL ya trigger ya mtafsiri chini ya `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Badilisha `<URL>` na URL ya trigger ya HTTP ya `translate-text` kwenye programu yako ya functions. Hii itakuwa sawa na thamani ya `TEXT_TO_TIMER_FUNCTION_URL`, isipokuwa na jina la function la `translate-text` badala ya `text-to-timer`.

1. Ongeza faili mpya kwenye folda ya `src` inayoitwa `text_translator.h`.

1. Faili hii mpya ya kichwa ya `text_translator.h` itakuwa na darasa la kutafsiri maandishi. Ongeza yafuatayo kwenye faili hii kutangaza darasa hili:

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

    Hii inatangaza darasa la `TextTranslator`, pamoja na mfano wa darasa hili. Darasa lina uwanja mmoja kwa mteja wa WiFi.

1. Kwenye sehemu ya `public` ya darasa hili, ongeza mbinu ya kutafsiri maandishi:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Mbinu hii inachukua lugha ya kutafsiri kutoka, na lugha ya kutafsiri kwenda. Wakati wa kushughulikia hotuba, hotuba itatafsiriwa kutoka lugha ya mtumiaji hadi lugha ya seva ya LUIS, na wakati wa kutoa majibu itatafsiri kutoka lugha ya seva ya LUIS hadi lugha ya mtumiaji.

1. Kwenye mbinu hii, ongeza msimbo wa kuunda mwili wa JSON unaoelezea maandishi ya kutafsiri na lugha:

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

1. Chini ya hii, ongeza msimbo wa kutuma mwili kwa programu ya functions isiyo na server:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Kisha, ongeza msimbo wa kupata majibu:

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

1. Hatimaye, ongeza msimbo wa kufunga muunganisho na kurudisha maandishi yaliyotafsiriwa:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Kazi - tafsiri hotuba iliyotambuliwa na majibu

1. Fungua faili ya `main.cpp`.

1. Ongeza agizo la kujumuisha mwanzoni mwa faili kwa faili ya kichwa ya darasa la `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Maandishi yanayosemwa wakati kipima muda kimewekwa au kinapomalizika yanahitaji kutafsiriwa. Ili kufanya hivyo, ongeza yafuatayo kama mstari wa kwanza wa kazi ya `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Hii itatafsiri maandishi kwa lugha ya mtumiaji.

1. Kwenye kazi ya `processAudio`, maandishi yanapatikana kutoka kwa sauti iliyorekodiwa kwa wito wa `String text = speechToText.convertSpeechToText();`. Baada ya wito huu, tafsiri maandishi:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Hii itatafsiri maandishi kutoka lugha ya mtumiaji hadi lugha inayotumika kwenye seva.

1. Jenga msimbo huu, upakie kwenye Wio Terminal yako na ujaribu kupitia serial monitor. Mara tu unapoona `Ready` kwenye serial monitor, bonyeza kitufe cha C (kile kilicho upande wa kushoto, karibu na swichi ya nguvu), na uzungumze. Hakikisha programu yako ya functions inaendesha, na omba kipima muda kwa lugha ya mtumiaji, ama kwa kuzungumza lugha hiyo mwenyewe, au ukitumia programu ya kutafsiri.

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

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Programu yako ya kipima muda cha lugha nyingi imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya kutafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafadhali fahamu kuwa tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuzingatiwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.