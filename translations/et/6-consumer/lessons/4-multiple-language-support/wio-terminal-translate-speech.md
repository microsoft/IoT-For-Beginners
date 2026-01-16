<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-10-11T12:13:56+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "et"
}
-->
# Tõlgi kõne - Wio Terminal

Selles õppetunni osas kirjutad koodi, et tõlkida teksti kasutades tõlketeenust.

## Teksti teisendamine kõneks tõlketeenuse abil

Kõneteenuse REST API ei toeta otseseid tõlkeid, kuid saad kasutada Translator teenust, et tõlkida kõneteksti teenuse poolt genereeritud teksti ja räägitud vastuse teksti. Sellel teenusel on REST API, mida saab kasutada teksti tõlkimiseks, kuid lihtsuse huvides pakitakse see funktsioonirakendusesse teise HTTP-triggeri abil.

### Ülesanne - loo serverivaba funktsioon teksti tõlkimiseks

1. Ava oma `smart-timer-trigger` projekt VS Code'is ja ava terminal, veendudes, et virtuaalne keskkond on aktiveeritud. Kui ei ole, sulge ja loo terminal uuesti.

1. Ava fail `local.settings.json` ja lisa tõlketeenuse API võtme ja asukoha seaded:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Asenda `<key>` oma tõlketeenuse ressursi API võtmega. Asenda `<location>` asukohaga, mida kasutasid tõlketeenuse ressursi loomisel.

1. Lisa sellele rakendusele uus HTTP-trigger nimega `translate-text`, kasutades järgmist käsku VS Code terminalis funktsioonirakenduse projekti juurkataloogis:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    See loob HTTP-triggeri nimega `translate-text`.

1. Asenda `translate-text` kausta `__init__.py` faili sisu järgmisega:

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

    See kood eraldab teksti ja keeled HTTP-päringust. Seejärel tehakse päring tõlketeenuse REST API-le, edastades keeled URL-i parameetritena ja tõlgitava teksti päringu kehas. Lõpuks tagastatakse tõlge.

1. Käivita oma funktsioonirakendus lokaalselt. Saad seda testida tööriistaga nagu curl samamoodi, nagu testisid `text-to-timer` HTTP-triggerit. Veendu, et edastad tõlgitava teksti ja keeled JSON-kehas:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    See näide tõlgib *Définir une minuterie de 30 secondes* prantsuse keelest USA inglise keelde. Tagastatakse *Set a 30-second timer*.

> 💁 Selle koodi leiad kaustast [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Ülesanne - kasuta tõlkefunktsiooni teksti tõlkimiseks

1. Ava `smart-timer` projekt VS Code'is, kui see pole juba avatud.

1. Sinu nutikas taimeril on määratud 2 keelt - serveri keel, mida kasutati LUIS-i treenimiseks (sama keelt kasutatakse ka kasutajale räägitavate sõnumite koostamiseks), ja kasutaja räägitav keel. Uuenda `LANGUAGE` konstant `config.h` päisefailis, et see vastaks keelele, mida kasutaja räägib, ja lisa uus konstant nimega `SERVER_LANGUAGE` LUIS-i treenimiseks kasutatud keele jaoks:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Asenda `<user language>` keele lokaadi nimega, milles räägid, näiteks `fr-FR` prantsuse keele jaoks või `zn-HK` kantoni keele jaoks.

    Asenda `<server language>` LUIS-i treenimiseks kasutatud keele lokaadi nimega.

    Saad toetatud keelte ja nende lokaadi nimede loendi [Microsofti dokumentatsioonist keele ja hääle toe kohta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Kui sa ei räägi mitut keelt, saad kasutada teenuseid nagu [Bing Translate](https://www.bing.com/translator) või [Google Translate](https://translate.google.com), et tõlkida oma eelistatud keelest valitud keelde. Need teenused saavad mängida ka tõlgitud teksti heli.
    >
    > Näiteks, kui treenid LUIS-i inglise keeles, kuid soovid kasutada prantsuse keelt kasutaja keeleks, saad tõlkida lauseid nagu "set a 2 minute and 27 second timer" inglise keelest prantsuse keelde Bing Translate'i abil ja seejärel kasutada **Kuula tõlget** nuppu, et rääkida tõlge mikrofoni.
    >
    > ![Kuula tõlget nupp Bing Translate'is](../../../../../translated_images/et/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Lisa tõlketeenuse API võti ja asukoht `SPEECH_LOCATION` alla:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Asenda `<KEY>` oma tõlketeenuse ressursi API võtmega. Asenda `<LOCATION>` asukohaga, mida kasutasid tõlketeenuse ressursi loomisel.

1. Lisa tõlketeenuse triggeri URL `VOICE_URL` alla:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Asenda `<URL>` `translate-text` HTTP-triggeri URL-iga oma funktsioonirakenduses. See on sama, mis `TEXT_TO_TIMER_FUNCTION_URL` väärtus, välja arvatud funktsiooni nimi, mis on `translate-text` asemel `text-to-timer`.

1. Lisa uus fail `src` kausta nimega `text_translator.h`.

1. See uus `text_translator.h` päisefail sisaldab klassi teksti tõlkimiseks. Lisa sellele failile järgmine, et klassi deklareerida:

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

    See deklareerib `TextTranslator` klassi koos selle klassi instantsiga. Klassil on üks väli WiFi kliendi jaoks.

1. Lisa selle klassi `public` sektsiooni meetod teksti tõlkimiseks:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    See meetod võtab keele, millest tõlkida, ja keele, millesse tõlkida. Kõne käsitlemisel tõlgitakse kõne kasutaja keelest LUIS-i serveri keelde ja vastuste andmisel tõlgitakse LUIS-i serveri keelest kasutaja keelde.

1. Lisa sellele meetodile kood JSON-keha koostamiseks, mis sisaldab tõlgitavat teksti ja keeli:

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

1. Selle alla lisa järgmine kood keha serverivaba funktsioonirakendusse saatmiseks:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Järgmiseks lisa kood vastuse saamiseks:

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

1. Lõpuks lisa kood ühenduse sulgemiseks ja tõlgitud teksti tagastamiseks:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Ülesanne - tõlgi tuvastatud kõne ja vastused

1. Ava `main.cpp` fail.

1. Lisa faili algusesse include direktiiv `TextTranslator` klassi päisefaili jaoks:

    ```cpp
    #include "text_translator.h"
    ```

1. Tekst, mida öeldakse, kui taimer on seadistatud või aegub, tuleb tõlkida. Selleks lisa järgmine `say` funktsiooni esimese reana:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    See tõlgib teksti kasutaja keelde.

1. `processAudio` funktsioonis saadakse tekst salvestatud helist `String text = speechToText.convertSpeechToText();` käsuga. Pärast seda käsku tõlgi tekst:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    See tõlgib teksti kasutaja keelest serveri kasutatavasse keelde.

1. Koosta see kood, laadi see oma Wio Terminali ja testi seda läbi seeriamonitori. Kui näed seeriamonitoris `Ready`, vajuta C nuppu (vasakpoolne nupp, mis on kõige lähemal toitelülitile) ja räägi. Veendu, et sinu funktsioonirakendus töötab, ja küsi taimerit kasutaja keeles, kas rääkides ise selles keeles või kasutades tõlketeenuse rakendust.

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

> 💁 Selle koodi leiad kaustast [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Sinu mitmekeelne taimeriprogramm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta selle tõlke kasutamisest tulenevate arusaamatuste või valesti tõlgenduste eest.