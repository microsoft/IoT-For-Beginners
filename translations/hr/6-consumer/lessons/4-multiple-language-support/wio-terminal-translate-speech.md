# Prevedi govor - Wio Terminal

U ovom dijelu lekcije napisat ćete kod za prevođenje teksta koristeći uslugu prevoditelja.

## Pretvorite tekst u govor koristeći uslugu prevoditelja

REST API usluge govora ne podržava izravna prevođenja, no možete koristiti uslugu Prevoditelja za prevođenje teksta generiranog uslugom govora u tekst, kao i teksta izgovorenog odgovora. Ova usluga ima REST API koji možete koristiti za prevođenje teksta, ali kako bi korištenje bilo jednostavnije, ovo će biti omotano u drugi HTTP okidač u vašoj aplikaciji funkcija.

### Zadatak - kreirajte serverless funkciju za prevođenje teksta

1. Otvorite svoj projekt `smart-timer-trigger` u VS Code-u i otvorite terminal osiguravajući da je virtualno okruženje aktivirano. Ako nije, zatvorite i ponovno kreirajte terminal.

1. Otvorite datoteku `local.settings.json` i dodajte postavke za API ključ i lokaciju usluge prevoditelja:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Zamijenite `<key>` API ključem za vaš resurs usluge prevoditelja. Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja resursa usluge prevoditelja.

1. Dodajte novi HTTP okidač ovoj aplikaciji nazvan `translate-text` koristeći sljedeću naredbu iz terminala u korijenskoj mapi projekta aplikacije funkcija:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Ovo će kreirati HTTP okidač nazvan `translate-text`.

1. Zamijenite sadržaj datoteke `__init__.py` u mapi `translate-text` sljedećim:

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

    Ovaj kod izvlači tekst i jezike iz HTTP zahtjeva. Zatim šalje zahtjev REST API-ju prevoditelja, prosljeđujući jezike kao parametre za URL i tekst za prevođenje kao tijelo. Na kraju, vraća se prijevod.

1. Pokrenite svoju aplikaciju funkcija lokalno. Zatim je možete pozvati koristeći alat poput curl-a na isti način na koji ste testirali HTTP okidač `text-to-timer`. Obavezno proslijedite tekst za prevođenje i jezike kao JSON tijelo:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Ovaj primjer prevodi *Définir une minuterie de 30 secondes* s francuskog na američki engleski. Vratit će *Set a 30-second timer*.

> 💁 Ovaj kod možete pronaći u mapi [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Zadatak - koristite funkciju prevoditelja za prevođenje teksta

1. Otvorite projekt `smart-timer` u VS Code-u ako već nije otvoren.

1. Vaš pametni timer imat će postavljena 2 jezika - jezik servera koji je korišten za treniranje LUIS-a (isti jezik se također koristi za kreiranje poruka koje se izgovaraju korisniku) i jezik koji govori korisnik. Ažurirajte konstantu `LANGUAGE` u zaglavnoj datoteci `config.h` na jezik koji će govoriti korisnik i dodajte novu konstantu nazvanu `SERVER_LANGUAGE` za jezik korišten za treniranje LUIS-a:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Zamijenite `<user language>` nazivom lokaliteta za jezik kojim ćete govoriti, na primjer `fr-FR` za francuski ili `zn-HK` za kantonski.

    Zamijenite `<server language>` nazivom lokaliteta za jezik korišten za treniranje LUIS-a.

    Popis podržanih jezika i njihovih naziva lokaliteta možete pronaći u [dokumentaciji o podršci za jezik i glas na Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Ako ne govorite više jezika, možete koristiti uslugu poput [Bing Translate](https://www.bing.com/translator) ili [Google Translate](https://translate.google.com) za prevođenje s vašeg preferiranog jezika na jezik po izboru. Ove usluge mogu reproducirati audio prevedenog teksta.
    >
    > Na primjer, ako trenirate LUIS na engleskom, ali želite koristiti francuski kao jezik korisnika, možete prevesti rečenice poput "set a 2 minute and 27 second timer" s engleskog na francuski koristeći Bing Translate, a zatim koristiti gumb **Listen translation** za izgovaranje prijevoda u mikrofon.
    >
    > ![Gumb za slušanje prijevoda na Bing Translate](../../../../../translated_images/hr/bing-translate.348aa796d6efe2a9.webp)

1. Dodajte API ključ i lokaciju prevoditelja ispod `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Zamijenite `<KEY>` API ključem za vaš resurs usluge prevoditelja. Zamijenite `<LOCATION>` lokacijom koju ste koristili prilikom kreiranja resursa usluge prevoditelja.

1. Dodajte URL okidača prevoditelja ispod `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Zamijenite `<URL>` URL-om za HTTP okidač `translate-text` u vašoj aplikaciji funkcija. Ovo će biti isto kao vrijednost za `TEXT_TO_TIMER_FUNCTION_URL`, osim što će ime funkcije biti `translate-text` umjesto `text-to-timer`.

1. Dodajte novu datoteku u mapu `src` nazvanu `text_translator.h`.

1. Ova nova zaglavna datoteka `text_translator.h` sadržavat će klasu za prevođenje teksta. Dodajte sljedeće u ovu datoteku kako biste deklarirali ovu klasu:

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

    Ovo deklarira klasu `TextTranslator`, zajedno s instancom ove klase. Klasa ima jedno polje za WiFi klijent.

1. U odjeljak `public` ove klase dodajte metodu za prevođenje teksta:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Ova metoda uzima jezik s kojeg se prevodi i jezik na koji se prevodi. Kada se obrađuje govor, govor će se prevoditi s jezika korisnika na jezik servera LUIS-a, a prilikom davanja odgovora prevodit će se s jezika servera LUIS-a na jezik korisnika.

1. U ovoj metodi dodajte kod za konstrukciju JSON tijela koje sadrži tekst za prevođenje i jezike:

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

1. Ispod ovoga dodajte sljedeći kod za slanje tijela aplikaciji funkcija:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Zatim dodajte kod za dobivanje odgovora:

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

1. Na kraju, dodajte kod za zatvaranje veze i vraćanje prevedenog teksta:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Zadatak - prevedite prepoznati govor i odgovore

1. Otvorite datoteku `main.cpp`.

1. Dodajte direktivu za uključivanje na vrh datoteke za zaglavnu datoteku klase `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Tekst koji se izgovara kada se postavi ili istekne timer treba prevesti. Da biste to učinili, dodajte sljedeće kao prvi redak funkcije `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ovo će prevesti tekst na jezik korisnika.

1. U funkciji `processAudio`, tekst se dohvaća iz snimljenog zvuka pozivom `String text = speechToText.convertSpeechToText();`. Nakon ovog poziva, prevedite tekst:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Ovo će prevesti tekst s jezika korisnika na jezik korišten na serveru.

1. Izgradite ovaj kod, učitajte ga na svoj Wio Terminal i testirajte ga putem serijskog monitora. Kada vidite `Ready` na serijskom monitoru, pritisnite gumb C (onaj na lijevoj strani, najbliži prekidaču za napajanje) i govorite. Osigurajte da vaša aplikacija funkcija radi i zatražite timer na jeziku korisnika, bilo govoreći tim jezikom sami ili koristeći aplikaciju za prevođenje.

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

> 💁 Ovaj kod možete pronaći u mapi [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Vaš program za višejezični timer bio je uspješan!

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden korištenjem AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati mjerodavnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane stručnjaka. Ne preuzimamo odgovornost za bilo kakve nesporazume ili pogrešne interpretacije proizašle iz korištenja ovog prijevoda.