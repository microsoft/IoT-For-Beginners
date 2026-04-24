# Käännä puhe - Wio Terminal

Tässä osassa oppituntia kirjoitat koodia tekstin kääntämiseen käyttäen käännöspalvelua.

## Muunna teksti puheeksi käännöspalvelun avulla

Puhepalvelun REST API ei tue suoria käännöksiä, mutta voit käyttää Translator-palvelua kääntämään tekstin, joka on luotu puheesta tekstiksi -palvelulla, sekä puhutun vastauksen tekstiä. Tämä palvelu tarjoaa REST API:n tekstin kääntämiseen, mutta sen käytön helpottamiseksi se kääritään toiseen HTTP-triggeriin funktiosovelluksessasi.

### Tehtävä - luo palveluton funktio tekstin kääntämiseen

1. Avaa `smart-timer-trigger`-projektisi VS Codessa ja avaa terminaali varmistaen, että virtuaaliympäristö on aktivoitu. Jos ei, sulje ja luo terminaali uudelleen.

1. Avaa `local.settings.json`-tiedosto ja lisää asetukset käännöspalvelun API-avaimelle ja sijainnille:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Korvaa `<key>` käännöspalveluresurssisi API-avaimella. Korvaa `<location>` sijainnilla, jota käytit luodessasi käännöspalveluresurssin.

1. Lisää uusi HTTP-triggeri tähän sovellukseen nimeltä `translate-text` käyttämällä seuraavaa komentoa VS Code -terminaalissa funktiosovelluksen projektin juurikansiossa:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Tämä luo HTTP-triggerin nimeltä `translate-text`.

1. Korvaa `translate-text`-kansion `__init__.py`-tiedoston sisältö seuraavalla:

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

    Tämä koodi poimii tekstin ja kielet HTTP-pyynnöstä. Se tekee sitten pyynnön käännöspalvelun REST API:lle, välittäen kielet URL-parametreina ja käännettävän tekstin pyynnön runkona. Lopuksi käännös palautetaan.

1. Aja funktiosovelluksesi paikallisesti. Voit sitten kutsua sitä työkalulla kuten curl samalla tavalla kuin testasit `text-to-timer` HTTP-triggeriä. Muista välittää käännettävä teksti ja kielet JSON-runkoina:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Tämä esimerkki kääntää *Définir une minuterie de 30 secondes* ranskasta Yhdysvaltain englantiin. Se palauttaa *Set a 30-second timer*.

> 💁 Löydät tämän koodin [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions)-kansiosta.

### Tehtävä - käytä käännösfunktiota tekstin kääntämiseen

1. Avaa `smart-timer`-projekti VS Codessa, jos se ei ole jo auki.

1. Älykäs ajastimesi käyttää kahta kieltä - palvelimen kieltä, jota käytettiin LUIS:n kouluttamiseen (sama kieli käytetään myös käyttäjälle puhuttavien viestien rakentamiseen), ja käyttäjän puhumaa kieltä. Päivitä `LANGUAGE`-vakio `config.h`-otsikkotiedostossa käyttäjän puhumaksi kieleksi ja lisää uusi vakio nimeltä `SERVER_LANGUAGE` LUIS:n koulutuksessa käytetylle kielelle:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Korvaa `<user language>` kielen paikallisnimi, jolla aiot puhua, esimerkiksi `fr-FR` ranskalle tai `zn-HK` kantonille.

    Korvaa `<server language>` LUIS:n koulutuksessa käytetyn kielen paikallisnimi.

    Löydät tuettujen kielten ja niiden paikallisnimien listan [Microsoftin dokumentaatiosta](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jos et puhu useita kieliä, voit käyttää palvelua kuten [Bing Translate](https://www.bing.com/translator) tai [Google Translate](https://translate.google.com) kääntääksesi suosikkikielestäsi valitsemaasi kieleen. Nämä palvelut voivat myös toistaa käännetyn tekstin äänenä.
    >
    > Esimerkiksi, jos koulutat LUIS:n englanniksi, mutta haluat käyttää ranskaa käyttäjän kielenä, voit kääntää lauseita kuten "set a 2 minute and 27 second timer" englannista ranskaksi Bing Translaten avulla ja käyttää **Kuuntele käännös**-painiketta puhuaksesi käännöksen mikrofoniin.
    >
    > ![Kuuntele käännös -painike Bing Translatessa](../../../../../translated_images/fi/bing-translate.348aa796d6efe2a9.webp)

1. Lisää käännöspalvelun API-avain ja sijainti `SPEECH_LOCATION`-kohdan alle:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Korvaa `<KEY>` käännöspalveluresurssisi API-avaimella. Korvaa `<LOCATION>` sijainnilla, jota käytit luodessasi käännöspalveluresurssin.

1. Lisää käännöspalvelun triggerin URL `VOICE_URL`-kohdan alle:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Korvaa `<URL>` `translate-text` HTTP-triggerin URL:lla funktiosovelluksessasi. Tämä on sama kuin `TEXT_TO_TIMER_FUNCTION_URL`-arvo, paitsi että funktiolla on nimi `translate-text` eikä `text-to-timer`.

1. Lisää uusi tiedosto `src`-kansioon nimeltä `text_translator.h`.

1. Tämä uusi `text_translator.h`-otsikkotiedosto sisältää luokan tekstin kääntämiseen. Lisää tiedostoon seuraava luokan määrittämiseksi:

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

    Tämä määrittää `TextTranslator`-luokan sekä sen instanssin. Luokalla on yksi kenttä WiFi-asiakkaalle.

1. Lisää tämän luokan `public`-osioon metodi tekstin kääntämiseen:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Tämä metodi ottaa kielen, josta käännetään, ja kielen, johon käännetään. Kun käsitellään puhetta, puhe käännetään käyttäjän kielestä LUIS-palvelimen kieleen, ja vastauksia annettaessa se käännetään LUIS-palvelimen kielestä käyttäjän kieleen.

1. Lisää tähän metodiin koodi JSON-runkojen rakentamiseksi, jotka sisältävät käännettävän tekstin ja kielet:

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

1. Tämän alle lisää seuraava koodi rungon lähettämiseksi palveluttomaan funktiosovellukseen:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Lisää seuraavaksi koodi vastauksen hakemiseksi:

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

1. Lopuksi lisää koodi yhteyden sulkemiseksi ja käännetyn tekstin palauttamiseksi:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Tehtävä - käännä tunnistettu puhe ja vastaukset

1. Avaa `main.cpp`-tiedosto.

1. Lisää tiedoston alkuun include-direktiivi `TextTranslator`-luokan otsikkotiedostolle:

    ```cpp
    #include "text_translator.h"
    ```

1. Teksti, joka sanotaan, kun ajastin asetetaan tai päättyy, täytyy kääntää. Tee tämä lisäämällä seuraava `say`-funktion ensimmäiseksi riviksi:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Tämä kääntää tekstin käyttäjän kielelle.

1. `processAudio`-funktiossa teksti haetaan tallennetusta äänestä `String text = speechToText.convertSpeechToText();`-kutsulla. Tämän kutsun jälkeen käännä teksti:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Tämä kääntää tekstin käyttäjän kielestä palvelimella käytettyyn kieleen.

1. Rakenna tämä koodi, lataa se Wio Terminaliin ja testaa se sarjamonitorin kautta. Kun näet `Ready` sarjamonitorissa, paina C-painiketta (vasemmanpuoleinen painike, lähimpänä virtakytkintä) ja puhu. Varmista, että funktiosovelluksesi on käynnissä, ja pyydä ajastinta käyttäjän kielellä joko puhumalla itse tai käyttämällä käännössovellusta.

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

> 💁 Löydät tämän koodin [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal)-kansiosta.

😀 Monikielinen ajastinohjelmasi onnistui!

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.