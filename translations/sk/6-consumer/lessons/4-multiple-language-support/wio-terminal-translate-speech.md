<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-28T09:26:13+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "sk"
}
-->
# Preložiť reč - Wio Terminal

V tejto časti lekcie napíšete kód na preklad textu pomocou prekladateľskej služby.

## Prevod textu na reč pomocou prekladateľskej služby

REST API služby reči nepodporuje priame preklady, namiesto toho môžete použiť prekladateľskú službu na preklad textu generovaného službou prevodu reči na text a textu hovorených odpovedí. Táto služba má REST API, ktoré môžete použiť na preklad textu, ale aby bolo jej použitie jednoduchšie, zabalíme ju do ďalšieho HTTP triggera vo vašej aplikácii funkcií.

### Úloha - vytvorte serverless funkciu na preklad textu

1. Otvorte svoj projekt `smart-timer-trigger` vo VS Code a otvorte terminál, pričom sa uistite, že virtuálne prostredie je aktivované. Ak nie, ukončite a znova vytvorte terminál.

1. Otvorte súbor `local.settings.json` a pridajte nastavenia pre API kľúč prekladateľskej služby a jej umiestnenie:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Nahraďte `<key>` API kľúčom pre váš zdroj prekladateľskej služby. Nahraďte `<location>` umiestnením, ktoré ste použili pri vytváraní zdroja prekladateľskej služby.

1. Pridajte nový HTTP trigger do tejto aplikácie s názvom `translate-text` pomocou nasledujúceho príkazu z terminálu VS Code v koreňovom priečinku projektu aplikácie funkcií:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Týmto sa vytvorí HTTP trigger s názvom `translate-text`.

1. Nahraďte obsah súboru `__init__.py` v priečinku `translate-text` nasledujúcim:

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

    Tento kód extrahuje text a jazyky z HTTP požiadavky. Potom odošle požiadavku na REST API prekladateľa, pričom jazyky odovzdá ako parametre URL a text na preklad ako telo požiadavky. Nakoniec sa vráti preložený text.

1. Spustite svoju aplikáciu funkcií lokálne. Potom ju môžete zavolať pomocou nástroja ako curl rovnakým spôsobom, ako ste testovali HTTP trigger `text-to-timer`. Uistite sa, že text na preklad a jazyky odovzdávate ako JSON telo:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Tento príklad prekladá *Définir une minuterie de 30 secondes* z francúzštiny do americkej angličtiny. Vráti *Set a 30-second timer*.

> 💁 Tento kód nájdete v priečinku [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Úloha - použite prekladateľskú funkciu na preklad textu

1. Otvorte projekt `smart-timer` vo VS Code, ak ešte nie je otvorený.

1. Váš inteligentný časovač bude mať nastavené 2 jazyky - jazyk servera, ktorý bol použitý na trénovanie LUIS (rovnaký jazyk sa používa aj na vytváranie správ pre používateľa), a jazyk, ktorým hovorí používateľ. Aktualizujte konštantu `LANGUAGE` v hlavičkovom súbore `config.h` na jazyk, ktorým bude hovoriť používateľ, a pridajte novú konštantu s názvom `SERVER_LANGUAGE` pre jazyk použitý na trénovanie LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Nahraďte `<user language>` názvom lokality pre jazyk, ktorým budete hovoriť, napríklad `fr-FR` pre francúzštinu alebo `zn-HK` pre kantončinu.

    Nahraďte `<server language>` názvom lokality pre jazyk použitý na trénovanie LUIS.

    Zoznam podporovaných jazykov a ich názvov lokalít nájdete v [dokumentácii o podpore jazykov a hlasov na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ak nehovoríte viacerými jazykmi, môžete použiť službu ako [Bing Translate](https://www.bing.com/translator) alebo [Google Translate](https://translate.google.com) na preklad z vášho preferovaného jazyka do iného jazyka podľa vášho výberu. Tieto služby môžu následne prehrávať zvuk preloženého textu.
    >
    > Napríklad, ak trénujete LUIS v angličtine, ale chcete používať francúzštinu ako jazyk používateľa, môžete preložiť vety ako "set a 2 minute and 27 second timer" z angličtiny do francúzštiny pomocou Bing Translate, a potom použiť tlačidlo **Listen translation** na prehranie prekladu do vášho mikrofónu.
    >
    > ![Tlačidlo Listen translation na Bing Translate](../../../../../translated_images/sk/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Pridajte API kľúč prekladateľa a jeho umiestnenie pod `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Nahraďte `<KEY>` API kľúčom pre váš zdroj prekladateľskej služby. Nahraďte `<LOCATION>` umiestnením, ktoré ste použili pri vytváraní zdroja prekladateľskej služby.

1. Pridajte URL triggera prekladateľa pod `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL adresou pre HTTP trigger `translate-text` vo vašej aplikácii funkcií. Táto bude rovnaká ako hodnota `TEXT_TO_TIMER_FUNCTION_URL`, okrem názvu funkcie, ktorý bude `translate-text` namiesto `text-to-timer`.

1. Pridajte nový súbor do priečinka `src` s názvom `text_translator.h`.

1. Tento nový hlavičkový súbor `text_translator.h` bude obsahovať triedu na preklad textu. Pridajte do tohto súboru nasledujúce na deklaráciu tejto triedy:

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

    Toto deklaruje triedu `TextTranslator`, spolu s jej inštanciou. Trieda má jedno pole pre WiFi klienta.

1. Do sekcie `public` tejto triedy pridajte metódu na preklad textu:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Táto metóda prijíma jazyk, z ktorého sa prekladá, a jazyk, do ktorého sa prekladá. Pri práci s rečou sa reč preloží z jazyka používateľa do jazyka servera LUIS a pri odpovediach sa preloží z jazyka servera LUIS do jazyka používateľa.

1. V tejto metóde pridajte kód na zostavenie JSON tela obsahujúceho text na preklad a jazyky:

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

1. Pod týmto pridajte nasledujúci kód na odoslanie tela do serverless funkcie:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ďalej pridajte kód na získanie odpovede:

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

1. Nakoniec pridajte kód na uzavretie spojenia a vrátenie preloženého textu:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Úloha - preložte rozpoznanú reč a odpovede

1. Otvorte súbor `main.cpp`.

1. Pridajte direktívu `include` na začiatku súboru pre hlavičkový súbor triedy `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Text, ktorý sa hovorí, keď je časovač nastavený alebo vyprší, je potrebné preložiť. Na tento účel pridajte nasledujúce ako prvý riadok funkcie `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Týmto sa text preloží do jazyka používateľa.

1. Vo funkcii `processAudio` sa text získava z nahraného zvuku pomocou volania `String text = speechToText.convertSpeechToText();`. Po tomto volaní preložte text:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Týmto sa text preloží z jazyka používateľa do jazyka používaného na serveri.

1. Zostavte tento kód, nahrajte ho do vášho Wio Terminal a otestujte ho cez sériový monitor. Keď uvidíte `Ready` v sériovom monitore, stlačte tlačidlo C (to na ľavej strane, najbližšie k vypínaču) a hovorte. Uistite sa, že vaša aplikácia funkcií beží, a požiadajte o časovač v jazyku používateľa, buď hovorením týmto jazykom, alebo použitím prekladovej aplikácie.

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

> 💁 Tento kód nájdete v priečinku [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Váš viacjazyčný program časovača bol úspešný!

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby na automatický preklad [Co-op Translator](https://github.com/Azure/co-op-translator). Aj keď sa snažíme o presnosť, upozorňujeme, že automatické preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho pôvodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nezodpovedáme za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.