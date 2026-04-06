# Překlad řeči - Wio Terminal

V této části lekce napíšete kód pro překlad textu pomocí služby překladače.

## Převod textu na řeč pomocí služby překladače

REST API služby pro řeč nepodporuje přímé překlady, místo toho můžete použít službu Translator k překladu textu generovaného službou pro převod řeči na text a textu mluvené odpovědi. Tato služba má REST API, které můžete použít k překladu textu, ale pro zjednodušení bude zabalena do dalšího HTTP triggeru ve vaší aplikaci funkcí.

### Úkol - vytvoření serverless funkce pro překlad textu

1. Otevřete svůj projekt `smart-timer-trigger` v VS Code a otevřete terminál, ujistěte se, že je aktivováno virtuální prostředí. Pokud ne, ukončete a znovu vytvořte terminál.

1. Otevřete soubor `local.settings.json` a přidejte nastavení pro API klíč a umístění služby překladače:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Nahraďte `<key>` API klíčem pro váš zdroj služby překladače. Nahraďte `<location>` umístěním, které jste použili při vytvoření zdroje služby překladače.

1. Přidejte nový HTTP trigger do této aplikace nazvaný `translate-text` pomocí následujícího příkazu z terminálu VS Code v kořenové složce projektu aplikace funkcí:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Tím se vytvoří HTTP trigger nazvaný `translate-text`.

1. Nahraďte obsah souboru `__init__.py` ve složce `translate-text` následujícím:

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

    Tento kód extrahuje text a jazyky z HTTP požadavku. Poté provede požadavek na REST API překladače, přičemž jazyky předá jako parametry URL a text k překladu jako tělo. Nakonec se vrátí překlad.

1. Spusťte svou aplikaci funkcí lokálně. Poté ji můžete volat pomocí nástroje jako curl stejným způsobem, jakým jste testovali HTTP trigger `text-to-timer`. Ujistěte se, že předáváte text k překladu a jazyky jako JSON tělo:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Tento příklad překládá *Définir une minuterie de 30 secondes* z francouzštiny do americké angličtiny. Vrátí *Set a 30-second timer*.

> 💁 Tento kód najdete ve složce [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Úkol - použití funkce překladače k překladu textu

1. Otevřete projekt `smart-timer` v VS Code, pokud již není otevřený.

1. Váš chytrý časovač bude mít nastaveny 2 jazyky - jazyk serveru, který byl použit k trénování LUIS (stejný jazyk je také použit k sestavení zpráv pro uživatele), a jazyk, kterým mluví uživatel. Aktualizujte konstantu `LANGUAGE` v hlavičkovém souboru `config.h` na jazyk, kterým bude mluvit uživatel, a přidejte novou konstantu nazvanou `SERVER_LANGUAGE` pro jazyk použitý k trénování LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Nahraďte `<user language>` názvem místního nastavení jazyka, kterým budete mluvit, například `fr-FR` pro francouzštinu nebo `zn-HK` pro kantonštinu.

    Nahraďte `<server language>` názvem místního nastavení jazyka použitého k trénování LUIS.

    Seznam podporovaných jazyků a jejich názvů místního nastavení najdete v [dokumentaci o podpoře jazyků a hlasů na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Pokud nemluvíte více jazyky, můžete použít službu jako [Bing Translate](https://www.bing.com/translator) nebo [Google Translate](https://translate.google.com) k překladu z vašeho preferovaného jazyka do jazyka dle vašeho výběru. Tyto služby pak mohou přehrát audio přeloženého textu.
    >
    > Například pokud trénujete LUIS v angličtině, ale chcete použít francouzštinu jako jazyk uživatele, můžete přeložit věty jako "set a 2 minute and 27 second timer" z angličtiny do francouzštiny pomocí Bing Translate, poté použít tlačítko **Listen translation** k přehrání překladu do mikrofonu.
    >
    > ![Tlačítko pro poslech překladu na Bing Translate](../../../../../translated_images/cs/bing-translate.348aa796d6efe2a9.webp)

1. Přidejte API klíč a umístění překladače pod `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Nahraďte `<KEY>` API klíčem pro váš zdroj služby překladače. Nahraďte `<LOCATION>` umístěním, které jste použili při vytvoření zdroje služby překladače.

1. Přidejte URL triggeru překladače pod `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL pro HTTP trigger `translate-text` ve vaší aplikaci funkcí. Toto bude stejné jako hodnota `TEXT_TO_TIMER_FUNCTION_URL`, kromě názvu funkce `translate-text` místo `text-to-timer`.

1. Přidejte nový soubor do složky `src` nazvaný `text_translator.h`.

1. Tento nový hlavičkový soubor `text_translator.h` bude obsahovat třídu pro překlad textu. Přidejte následující do tohoto souboru pro deklaraci této třídy:

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

    Tím se deklaruje třída `TextTranslator` spolu s instancí této třídy. Třída má jedno pole pro WiFi klienta.

1. Do sekce `public` této třídy přidejte metodu pro překlad textu:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Tato metoda bere jazyk, ze kterého se překládá, a jazyk, do kterého se překládá. Při zpracování řeči bude řeč přeložena z jazyka uživatele do jazyka serveru LUIS, a při poskytování odpovědí bude přeložena z jazyka serveru LUIS do jazyka uživatele.

1. V této metodě přidejte kód pro sestavení JSON těla obsahujícího text k překladu a jazyky:

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

1. Pod tímto přidejte následující kód pro odeslání těla do serverless funkce:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Dále přidejte kód pro získání odpovědi:

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

1. Nakonec přidejte kód pro uzavření spojení a vrácení přeloženého textu:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Úkol - překlad rozpoznané řeči a odpovědí

1. Otevřete soubor `main.cpp`.

1. Přidejte direktivu include na začátek souboru pro hlavičkový soubor třídy `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Text, který je vysloven při nastavení nebo vypršení časovače, je třeba přeložit. K tomu přidejte následující jako první řádek funkce `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Tím se text přeloží do jazyka uživatele.

1. Ve funkci `processAudio` je text získán z zachyceného audia pomocí volání `String text = speechToText.convertSpeechToText();`. Po tomto volání přeložte text:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Tím se text přeloží z jazyka uživatele do jazyka použitého na serveru.

1. Sestavte tento kód, nahrajte jej do svého Wio Terminalu a otestujte jej přes sériový monitor. Jakmile uvidíte `Ready` v sériovém monitoru, stiskněte tlačítko C (to na levé straně, nejblíže k vypínači) a mluvte. Ujistěte se, že vaše aplikace funkcí běží, a požádejte o časovač v jazyce uživatele, buď mluvením tímto jazykem, nebo použitím aplikace pro překlad.

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

> 💁 Tento kód najdete ve složce [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Váš vícejazyčný program časovače byl úspěšný!

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). I když se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace se doporučuje profesionální lidský překlad. Nenese odpovědnost za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.