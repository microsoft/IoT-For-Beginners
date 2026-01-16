<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-28T13:07:20+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "sl"
}
-->
# Prevedi govor - Wio Terminal

V tem delu lekcije boste napisali kodo za prevajanje besedila z uporabo storitve za prevajanje.

## Pretvorba besedila v govor z uporabo storitve za prevajanje

REST API storitve za govor ne podpira neposrednih prevodov, namesto tega lahko uporabite storitev Translator za prevajanje besedila, ki ga ustvari storitev za pretvorbo govora v besedilo, ter besedila izgovorjenega odziva. Ta storitev ima REST API, ki ga lahko uporabite za prevajanje besedila, vendar bo za lažjo uporabo ovita v drug HTTP sprožilec v vaši aplikaciji funkcij.

### Naloga - ustvarite strežniško funkcijo za prevajanje besedila

1. Odprite svoj projekt `smart-timer-trigger` v VS Code in odprite terminal, pri čemer se prepričajte, da je virtualno okolje aktivirano. Če ni, zaprite in ponovno ustvarite terminal.

1. Odprite datoteko `local.settings.json` in dodajte nastavitve za ključ API storitve Translator in lokacijo:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Zamenjajte `<key>` s ključem API za vaš vir storitve Translator. Zamenjajte `<location>` z lokacijo, ki ste jo uporabili ob ustvarjanju vira storitve Translator.

1. Dodajte nov HTTP sprožilec v to aplikacijo, imenovan `translate-text`, z uporabo naslednjega ukaza znotraj terminala VS Code v korenski mapi projekta aplikacije funkcij:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    To bo ustvarilo HTTP sprožilec, imenovan `translate-text`.

1. Zamenjajte vsebino datoteke `__init__.py` v mapi `translate-text` z naslednjim:

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

    Ta koda izlušči besedilo in jezike iz HTTP zahteve. Nato pošlje zahtevo REST API storitve Translator, pri čemer jezike posreduje kot parametre za URL, besedilo za prevajanje pa kot telo zahteve. Na koncu vrne prevod.

1. Lokalno zaženite svojo aplikacijo funkcij. Nato jo lahko pokličete z orodjem, kot je curl, na enak način, kot ste testirali svoj HTTP sprožilec `text-to-timer`. Prepričajte se, da besedilo za prevajanje in jezike posredujete kot JSON telo:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Ta primer prevaja *Définir une minuterie de 30 secondes* iz francoščine v ameriško angleščino. Vrne *Set a 30-second timer*.

> 💁 To kodo lahko najdete v mapi [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Naloga - uporabite funkcijo Translator za prevajanje besedila

1. Odprite projekt `smart-timer` v VS Code, če še ni odprt.

1. Vaš pametni časovnik bo imel nastavljena 2 jezika - jezik strežnika, ki je bil uporabljen za treniranje LUIS (isti jezik se uporablja tudi za gradnjo sporočil za uporabnika), in jezik, ki ga govori uporabnik. Posodobite konstanto `LANGUAGE` v glavni datoteki `config.h` na jezik, ki ga bo govoril uporabnik, ter dodajte novo konstanto, imenovano `SERVER_LANGUAGE`, za jezik, uporabljen za treniranje LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Zamenjajte `<user language>` z imenom lokalizacije jezika, v katerem boste govorili, na primer `fr-FR` za francoščino ali `zn-HK` za kantonščino.

    Zamenjajte `<server language>` z imenom lokalizacije jezika, uporabljenega za treniranje LUIS.

    Seznam podprtih jezikov in njihovih lokalizacijskih imen najdete v [dokumentaciji o podpori za jezike in glasove na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Če ne govorite več jezikov, lahko uporabite storitev, kot sta [Bing Translate](https://www.bing.com/translator) ali [Google Translate](https://translate.google.com), za prevajanje iz vašega najljubšega jezika v jezik po vaši izbiri. Te storitve lahko nato predvajajo zvok prevedenega besedila.
    >
    > Na primer, če trenirate LUIS v angleščini, vendar želite uporabiti francoščino kot uporabniški jezik, lahko prevedete stavke, kot je "set a 2 minute and 27 second timer", iz angleščine v francoščino z Bing Translate, nato pa uporabite gumb **Listen translation**, da izgovorite prevod v mikrofon.
    >
    > ![Gumb za poslušanje prevoda na Bing Translate](../../../../../translated_images/sl/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Dodajte ključ API storitve Translator in lokacijo pod `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Zamenjajte `<KEY>` s ključem API za vaš vir storitve Translator. Zamenjajte `<LOCATION>` z lokacijo, ki ste jo uporabili ob ustvarjanju vira storitve Translator.

1. Dodajte URL sprožilca Translator pod `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Zamenjajte `<URL>` z URL za HTTP sprožilec `translate-text` v vaši aplikaciji funkcij. To bo enako kot vrednost za `TEXT_TO_TIMER_FUNCTION_URL`, razen z imenom funkcije `translate-text` namesto `text-to-timer`.

1. Dodajte novo datoteko v mapo `src`, imenovano `text_translator.h`.

1. Ta nova glava `text_translator.h` bo vsebovala razred za prevajanje besedila. Dodajte naslednje v to datoteko, da deklarirate ta razred:

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

    To deklarira razred `TextTranslator` skupaj z instanco tega razreda. Razred ima eno polje za WiFi odjemalca.

1. V razdelek `public` tega razreda dodajte metodo za prevajanje besedila:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Ta metoda sprejme jezik, iz katerega prevaja, in jezik, v katerega prevaja. Pri obdelavi govora bo govor preveden iz uporabniškega jezika v jezik strežnika LUIS, pri podajanju odgovorov pa bo preveden iz jezika strežnika LUIS v uporabniški jezik.

1. V tej metodi dodajte kodo za sestavo JSON telesa, ki vsebuje besedilo za prevajanje in jezike:

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

1. Pod tem dodajte naslednjo kodo za pošiljanje telesa v aplikacijo strežniških funkcij:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Nato dodajte kodo za pridobitev odziva:

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

1. Na koncu dodajte kodo za zapiranje povezave in vrnitev prevedenega besedila:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Naloga - prevedite prepoznan govor in odgovore

1. Odprite datoteko `main.cpp`.

1. Na vrhu datoteke dodajte direktivo za vključitev glave razreda `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Besedilo, ki se izgovori, ko je časovnik nastavljen ali poteče, je treba prevesti. Za to dodajte naslednje kot prvo vrstico funkcije `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    To bo prevedlo besedilo v uporabniški jezik.

1. V funkciji `processAudio` se besedilo pridobi iz zajetega zvoka z ukazom `String text = speechToText.convertSpeechToText();`. Po tem klicu prevedite besedilo:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    To bo prevedlo besedilo iz uporabniškega jezika v jezik, uporabljen na strežniku.

1. Sestavite to kodo, naložite jo na svoj Wio Terminal in jo preizkusite prek serijskega monitorja. Ko vidite `Ready` na serijskem monitorju, pritisnite gumb C (tisti na levi strani, najbližje stikalu za vklop) in govorite. Prepričajte se, da vaša aplikacija funkcij deluje, in zahtevajte časovnik v uporabniškem jeziku, bodisi tako, da sami govorite ta jezik, bodisi z uporabo aplikacije za prevajanje.

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

> 💁 To kodo lahko najdete v mapi [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Vaš večjezični program za časovnik je bil uspešen!

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem maternem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazume ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.