<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T22:56:37+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "tl"
}
-->
# Isalin ang pagsasalita - Wio Terminal

Sa bahaging ito ng aralin, magsusulat ka ng code upang isalin ang teksto gamit ang serbisyo ng tagasalin.

## I-convert ang teksto sa pagsasalita gamit ang serbisyo ng tagasalin

Ang REST API ng speech service ay hindi sumusuporta sa direktang pagsasalin. Sa halip, maaari mong gamitin ang Translator service upang isalin ang teksto na nabuo ng speech-to-text service, pati na rin ang teksto ng sinasalitang tugon. Ang serbisyong ito ay may REST API na maaari mong gamitin upang isalin ang teksto, ngunit upang gawing mas madali, ito ay ibabalot sa isa pang HTTP trigger sa iyong functions app.

### Gawain - gumawa ng serverless function upang isalin ang teksto

1. Buksan ang iyong proyekto na `smart-timer-trigger` sa VS Code, at buksan ang terminal na siguraduhing naka-activate ang virtual environment. Kung hindi, patayin at muling likhain ang terminal.

1. Buksan ang file na `local.settings.json` at magdagdag ng mga setting para sa translator API key at lokasyon:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Palitan ang `<key>` ng API key para sa iyong translator service resource. Palitan ang `<location>` ng lokasyon na ginamit mo nang likhain ang translator service resource.

1. Magdagdag ng bagong HTTP trigger sa app na ito na tinatawag na `translate-text` gamit ang sumusunod na command mula sa loob ng VS Code terminal sa root folder ng functions app project:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Ito ay lilikha ng isang HTTP trigger na tinatawag na `translate-text`.

1. Palitan ang nilalaman ng file na `__init__.py` sa folder na `translate-text` ng sumusunod:

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

    Ang code na ito ay kumukuha ng teksto at mga wika mula sa HTTP request. Pagkatapos, ito ay gumagawa ng request sa translator REST API, ipinapasa ang mga wika bilang mga parameter para sa URL at ang teksto na isasalin bilang body. Sa huli, ang pagsasalin ay ibinabalik.

1. Patakbuhin ang iyong function app nang lokal. Maaari mo itong tawagin gamit ang tool tulad ng curl sa parehong paraan na sinubukan mo ang `text-to-timer` HTTP trigger. Siguraduhing ipasa ang teksto na isasalin at ang mga wika bilang isang JSON body:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Ang halimbawang ito ay nagsasalin ng *Définir une minuterie de 30 secondes* mula sa Pranses patungong US English. Ibabalik nito ang *Set a 30-second timer*.

> 💁 Maaari mong makita ang code na ito sa [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions) folder.

### Gawain - gamitin ang translator function upang isalin ang teksto

1. Buksan ang proyekto na `smart-timer` sa VS Code kung hindi pa ito bukas.

1. Ang iyong smart timer ay magkakaroon ng 2 wika na nakatakda - ang wika ng server na ginamit upang sanayin ang LUIS (ang parehong wika ay ginagamit din upang bumuo ng mga mensahe na sasabihin sa user), at ang wika na sinasalita ng user. I-update ang `LANGUAGE` constant sa `config.h` header file upang maging wika na sasabihin ng user, at magdagdag ng bagong constant na tinatawag na `SERVER_LANGUAGE` para sa wika na ginamit upang sanayin ang LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Palitan ang `<user language>` ng pangalan ng locale para sa wika na iyong gagamitin, halimbawa `fr-FR` para sa Pranses, o `zn-HK` para sa Cantonese.

    Palitan ang `<server language>` ng pangalan ng locale para sa wika na ginamit upang sanayin ang LUIS.

    Maaari mong makita ang listahan ng mga suportadong wika at ang kanilang mga pangalan ng locale sa [Language and voice support documentation on Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Kung hindi ka nagsasalita ng maraming wika, maaari kang gumamit ng serbisyo tulad ng [Bing Translate](https://www.bing.com/translator) o [Google Translate](https://translate.google.com) upang isalin mula sa iyong gustong wika patungo sa wika ng iyong pinili. Ang mga serbisyong ito ay maaari ring magpatugtog ng audio ng isinaling teksto.
    >
    > Halimbawa, kung sinanay mo ang LUIS sa Ingles, ngunit nais mong gamitin ang Pranses bilang wika ng user, maaari mong isalin ang mga pangungusap tulad ng "set a 2 minute and 27 second timer" mula sa Ingles patungo sa Pranses gamit ang Bing Translate, pagkatapos ay gamitin ang **Listen translation** button upang sabihin ang pagsasalin sa iyong mikropono.
    >
    > ![Ang listen translation button sa Bing translate](../../../../../translated_images/tl/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Idagdag ang translator API key at lokasyon sa ibaba ng `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Palitan ang `<KEY>` ng API key para sa iyong translator service resource. Palitan ang `<LOCATION>` ng lokasyon na ginamit mo nang likhain ang translator service resource.

1. Idagdag ang translator trigger URL sa ibaba ng `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Palitan ang `<URL>` ng URL para sa `translate-text` HTTP trigger sa iyong function app. Ito ay magiging pareho sa halaga para sa `TEXT_TO_TIMER_FUNCTION_URL`, maliban sa pangalan ng function na `translate-text` sa halip na `text-to-timer`.

1. Magdagdag ng bagong file sa folder na `src` na tinatawag na `text_translator.h`.

1. Ang bagong `text_translator.h` header file na ito ay maglalaman ng isang klase upang isalin ang teksto. Idagdag ang sumusunod sa file na ito upang ideklara ang klase:

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

    Ito ay nagdedeklara ng `TextTranslator` class, kasama ang isang instance ng klase na ito. Ang klase ay may isang field para sa WiFi client.

1. Sa seksyong `public` ng klase na ito, magdagdag ng isang method upang isalin ang teksto:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Ang method na ito ay tumatanggap ng wika na isasalin mula, at ang wika na isasalin patungo. Kapag humahawak ng pagsasalita, ang pagsasalita ay isasalin mula sa wika ng user patungo sa wika ng LUIS server, at kapag nagbibigay ng mga tugon, ito ay isasalin mula sa wika ng LUIS server patungo sa wika ng user.

1. Sa method na ito, magdagdag ng code upang bumuo ng isang JSON body na naglalaman ng teksto na isasalin at ang mga wika:

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

1. Sa ibaba nito, magdagdag ng sumusunod na code upang ipadala ang body sa serverless function app:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Susunod, magdagdag ng code upang makuha ang tugon:

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

1. Sa wakas, magdagdag ng code upang isara ang koneksyon at ibalik ang isinaling teksto:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Gawain - isalin ang nakilalang pagsasalita at ang mga tugon

1. Buksan ang file na `main.cpp`.

1. Magdagdag ng include directive sa itaas ng file para sa `TextTranslator` class header file:

    ```cpp
    #include "text_translator.h"
    ```

1. Ang teksto na sinasabi kapag ang timer ay na-set o nag-expire ay kailangang isalin. Upang gawin ito, idagdag ang sumusunod bilang unang linya ng `say` function:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Isasalin nito ang teksto sa wika ng user.

1. Sa `processAudio` function, ang teksto ay kinukuha mula sa na-capture na audio gamit ang tawag na `String text = speechToText.convertSpeechToText();`. Pagkatapos ng tawag na ito, isalin ang teksto:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Isasalin nito ang teksto mula sa wika ng user patungo sa wika na ginamit sa server.

1. I-build ang code na ito, i-upload ito sa iyong Wio Terminal at subukan ito sa pamamagitan ng serial monitor. Kapag nakita mo ang `Ready` sa serial monitor, pindutin ang C button (ang nasa kaliwang bahagi, pinakamalapit sa power switch), at magsalita. Siguraduhing tumatakbo ang iyong function app, at humiling ng timer sa wika ng user, alinman sa pamamagitan ng pagsasalita ng wika na iyon, o gamit ang isang translation app.

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

> 💁 Maaari mong makita ang code na ito sa [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal) folder.

😀 Tagumpay ang iyong multilingual timer program!

---

**Paunawa**:  
Ang dokumentong ito ay isinalin gamit ang AI translation service na [Co-op Translator](https://github.com/Azure/co-op-translator). Bagama't sinisikap naming maging tumpak, tandaan na ang mga awtomatikong pagsasalin ay maaaring maglaman ng mga pagkakamali o hindi pagkakatugma. Ang orihinal na dokumento sa kanyang katutubong wika ang dapat ituring na opisyal na sanggunian. Para sa mahalagang impormasyon, inirerekomenda ang propesyonal na pagsasalin ng tao. Hindi kami mananagot sa anumang hindi pagkakaunawaan o maling interpretasyon na maaaring magmula sa paggamit ng pagsasaling ito.