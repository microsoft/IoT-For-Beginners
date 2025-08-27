<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T22:28:19+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "fi"
}
-->
# Teksti puheeksi - Wio Terminal

Tässä osassa oppituntia muutat tekstin puheeksi tarjotaksesi puhuttua palautetta.

## Teksti puheeksi

Puhepalveluiden SDK, jota käytit edellisessä oppitunnissa muuttaaksesi puheen tekstiksi, voidaan käyttää tekstin muuttamiseen takaisin puheeksi.

## Hanki lista äänistä

Kun pyydät puhetta, sinun täytyy määrittää käytettävä ääni, sillä puhetta voidaan tuottaa monilla eri äänillä. Jokainen kieli tukee useita eri ääniä, ja puhepalveluiden SDK:sta voit saada listan kunkin kielen tuetuista äänistä. Mikro-ohjainten rajoitukset tulevat tässä esiin - puhepalveluiden tukemien äänien lista on yli 77KB kokoinen JSON-dokumentti, joka on liian suuri käsiteltäväksi Wio Terminalilla. Kirjoitushetkellä täydellinen lista sisältää 215 ääntä, joista jokainen on määritelty JSON-dokumentilla, kuten seuraava:

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

Tämä JSON koskee **Aria**-ääntä, jolla on useita äänen tyylejä. Tekstin muuttamiseksi puheeksi tarvitaan vain lyhytnimi, `en-US-AriaNeural`.

Sen sijaan, että lataisit ja dekoodaisit koko listan mikro-ohjaimellasi, sinun täytyy kirjoittaa lisää serverittömiä koodeja hakeaksesi listan käytettävän kielen äänistä ja kutsua tätä Wio Terminalista. Koodisi voi sitten valita sopivan äänen listasta, esimerkiksi ensimmäisen löytämänsä.

### Tehtävä - luo serveritön funktio äänilistan hakemiseksi

1. Avaa `smart-timer-trigger`-projektisi VS Codessa ja avaa terminaali varmistaen, että virtuaaliympäristö on aktivoitu. Jos ei, lopeta ja luo terminaali uudelleen.

1. Avaa `local.settings.json`-tiedosto ja lisää asetukset puhepalvelun API-avaimelle ja sijainnille:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Korvaa `<key>` puhepalveluresurssisi API-avaimella. Korvaa `<location>` sijainnilla, jota käytit luodessasi puhepalveluresurssin.

1. Lisää uusi HTTP-triggeri tähän sovellukseen nimeltä `get-voices` käyttämällä seuraavaa komentoa VS Code -terminaalissa funktiosovelluksen projektin juurikansiossa:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Tämä luo HTTP-triggerin nimeltä `get-voices`.

1. Korvaa `get-voices`-kansion `__init__.py`-tiedoston sisältö seuraavalla:

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    Tämä koodi tekee HTTP-pyynnön endpointiin äänien hakemiseksi. Äänilista on suuri JSON-lohko, joka sisältää kaikkien kielten äänet, joten pyynnön rungossa välitetyn kielen äänet suodatetaan, ja lyhytnimi poimitaan ja palautetaan JSON-listana. Lyhytnimi on arvo, jota tarvitaan tekstin muuttamiseksi puheeksi, joten vain tämä arvo palautetaan.

    > 💁 Voit muuttaa suodatinta tarpeen mukaan valitaksesi vain haluamasi äänet.

    Tämä pienentää datan kokoa 77KB:sta (kirjoitushetkellä) paljon pienemmäksi JSON-dokumentiksi. Esimerkiksi Yhdysvaltain äänille tämä on 408 tavua.

1. Aja funktiosovelluksesi paikallisesti. Voit sitten kutsua tätä työkalulla, kuten curl, samalla tavalla kuin testasit `text-to-timer` HTTP-triggeriä. Muista välittää kielesi JSON-runkona:

    ```json
    {
        "language":"<language>"
    }
    ```

    Korvaa `<language>` kielelläsi, kuten `en-GB` tai `zh-CN`.

> 💁 Löydät tämän koodin [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)-kansiosta.

### Tehtävä - hae ääni Wio Terminalistasi

1. Avaa `smart-timer`-projektisi VS Codessa, jos se ei ole jo auki.

1. Avaa `config.h`-otsikkotiedosto ja lisää URL funktiosovelluksellesi:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Korvaa `<URL>` URL:lla `get-voices` HTTP-triggerille funktiosovelluksessasi. Tämä on sama kuin `TEXT_TO_TIMER_FUNCTION_URL`-arvo, paitsi että funktiolla on nimi `get-voices` eikä `text-to-timer`.

1. Luo uusi tiedosto `src`-kansioon nimeltä `text_to_speech.h`. Tätä käytetään luokan määrittämiseen tekstin muuttamiseksi puheeksi.

1. Lisää seuraavat include-direktiivit uuden `text_to_speech.h`-tiedoston alkuun:

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. Lisää tämän alle seuraava koodi `TextToSpeech`-luokan julistamiseksi, sekä instanssi, jota voidaan käyttää sovelluksen muissa osissa:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Kutsua varten funktiosovellusta, sinun täytyy julistaa WiFi-asiakas. Lisää seuraava luokan `private`-osioon:

    ```cpp
    WiFiClient _client;
    ```

1. Lisää `private`-osioon kenttä valitulle äänelle:

    ```cpp
    String _voice;
    ```

1. Lisää `public`-osioon `init`-funktio, joka hakee ensimmäisen äänen:

    ```cpp
    void init()
    {
    }
    ```

1. Äänien hakemiseksi JSON-dokumentti täytyy lähettää funktiosovellukseen kielen kanssa. Lisää seuraava koodi `init`-funktioon luodaksesi tämän JSON-dokumentin:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Luo seuraavaksi `HTTPClient` ja käytä sitä kutsuaksesi funktiosovellusta äänien hakemiseksi, lähettäen JSON-dokumentin:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Lisää tämän alle koodi tarkistaaksesi vastauskoodin, ja jos se on 200 (onnistuminen), poimi äänilista ja hae ensimmäinen ääni listasta:

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. Tämän jälkeen lopeta HTTP-asiakasliittymän yhteys:

    ```cpp
    httpClient.end();
    ```

1. Avaa `main.cpp`-tiedosto ja lisää seuraava include-direktiivi alkuun sisällyttääksesi tämän uuden otsikkotiedoston:

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup`-funktiossa, `speechToText.init();`-kutsun alapuolelle, lisää seuraava `TextToSpeech`-luokan alustamiseksi:

    ```cpp
    textToSpeech.init();
    ```

1. Rakenna tämä koodi, lataa se Wio Terminaliin ja testaa se sarjamonitorin kautta. Varmista, että funktiosovelluksesi on käynnissä.

    Näet funktiosovelluksesta palautetun saatavilla olevien äänien listan sekä valitun äänen.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## Muunna teksti puheeksi

Kun sinulla on ääni käytettäväksi, sitä voidaan käyttää tekstin muuttamiseen puheeksi. Samat muistirajoitukset, jotka koskevat ääniä, pätevät myös puheen muuttamiseen tekstiksi, joten sinun täytyy kirjoittaa puhe SD-kortille, jotta se voidaan toistaa ReSpeakerin kautta.

> 💁 Aiemmissa oppitunneissa tässä projektissa käytit flash-muistia mikrofonista tallennetun puheen säilyttämiseen. Tämä oppitunti käyttää SD-korttia, koska sen kautta on helpompi toistaa ääntä Seeed-audiokirjastojen avulla.

On myös toinen rajoitus, joka täytyy ottaa huomioon: saatavilla oleva puhepalvelun tuottama audiodata ja Wio Terminalin tukemat formaatit. Toisin kuin täysimittaiset tietokoneet, mikro-ohjainten audiokirjastot voivat olla hyvin rajallisia tukemiensa audioformaattien suhteen. Esimerkiksi Seeed Arduino Audio -kirjasto, joka voi toistaa ääntä ReSpeakerin kautta, tukee vain ääniformaatteja, joiden näytteenottotaajuus on 44.1KHz. Azure-puhepalvelut voivat tarjota ääntä useissa formaateissa, mutta mikään niistä ei käytä tätä näytteenottotaajuutta; ne tarjoavat vain 8KHz, 16KHz, 24KHz ja 48KHz. Tämä tarkoittaa, että ääni täytyy uudelleennäytteistää 44.1KHz:iin, mikä vaatisi enemmän resursseja kuin Wio Terminalilla on, erityisesti muistia.

Kun dataa täytyy käsitellä tällä tavalla, on usein parempi käyttää serveritöntä koodia, erityisesti jos data on peräisin verkkopyynnöstä. Wio Terminal voi kutsua serveritöntä funktiota, välittää tekstin muutettavaksi, ja serveritön funktio voi sekä kutsua puhepalvelua tekstin muuttamiseksi puheeksi että uudelleennäytteistää äänen tarvittavaan näytteenottotaajuuteen. Se voi sitten palauttaa äänen Wio Terminalin tarvitsemassa muodossa, jotta se voidaan tallentaa SD-kortille ja toistaa ReSpeakerin kautta.

### Tehtävä - luo serveritön funktio tekstin muuttamiseksi puheeksi

1. Avaa `smart-timer-trigger`-projektisi VS Codessa ja avaa terminaali varmistaen, että virtuaaliympäristö on aktivoitu. Jos ei, lopeta ja luo terminaali uudelleen.

1. Lisää uusi HTTP-triggeri tähän sovellukseen nimeltä `text-to-speech` käyttämällä seuraavaa komentoa VS Code -terminaalissa funktiosovelluksen projektin juurikansiossa:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Tämä luo HTTP-triggerin nimeltä `text-to-speech`.

1. [librosa](https://librosa.org)-Pip-paketilla on funktioita äänen uudelleennäytteistämiseen, joten lisää tämä `requirements.txt`-tiedostoon:

    ```sh
    librosa
    ```

    Kun tämä on lisätty, asenna Pip-paketit seuraavalla komennolla VS Code -terminaalista:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Jos käytät Linuxia, mukaan lukien Raspberry Pi OS:ää, sinun täytyy ehkä asentaa `libsndfile` seuraavalla komennolla:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Tekstin muuttamiseksi puheeksi et voi käyttää puhepalvelun API-avainta suoraan, vaan sinun täytyy pyytää käyttöoikeustunnus, käyttäen API-avainta autentikoimaan käyttöoikeustunnuspyynnön. Avaa `__init__.py`-tiedosto `text-to-speech`-kansiosta ja korvaa kaikki sen koodi seuraavalla:

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Tämä määrittää vakioita sijainnille ja puheavaimelle, jotka luetaan asetuksista. Se määrittää myös `get_access_token`-funktion, joka hakee käyttöoikeustunnuksen puhepalvelulle.

1. Lisää tämän koodin alle seuraava:

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    Tämä määrittää HTTP-triggerin, joka muuntaa tekstin puheeksi. Se poimii tekstin, kielen ja äänen JSON-rungosta, joka on lähetetty pyyntöön, rakentaa SSML:n puhepyyntöä varten, ja kutsuu asiaankuuluvaa REST-API:a autentikoiden käyttöoikeustunnuksella. Tämä REST-API-kutsu palauttaa äänen koodattuna 16-bittiseksi, 48KHz mono WAV-tiedostoksi, joka on määritelty `playback_format`-arvolla, joka lähetetään REST-API-kutsuun.

    Tämä uudelleennäytteistetään `librosa`-kirjastolla näytteenottotaajuudesta 48KHz näytteenottotaajuuteen 44.1KHz, ja tämä ääni tallennetaan binaariseen puskuriin, joka sitten palautetaan.

1. Aja funktiosovelluksesi paikallisesti tai julkaise se pilveen. Voit sitten kutsua tätä työkalulla, kuten curl, samalla tavalla kuin testasit `text-to-timer` HTTP-triggeriä. Muista välittää kieli, ääni ja teksti JSON-runkona:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Korvaa `<language>` kielelläsi, kuten `en-GB` tai `zh-CN`. Korvaa `<voice>` haluamallasi äänellä. Korvaa `<text>` tekstillä, jonka haluat muuttaa puheeksi. Voit tallentaa tuloksen tiedostoon ja toistaa sen millä tahansa WAV-tiedostoja toistavalla audioplayerilla.

    Esimerkiksi muuntaaksesi "Hello" puheeksi käyttäen Yhdysvaltain englantia ja Jenny Neural -ääntä, kun funktiosovellus on käynnissä paikallisesti, voit käyttää seuraavaa curl-komentoa:

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    Tämä tallentaa äänen `hello.wav`-tiedostoon nykyisessä hakemistossa.

> 💁 Löydät tämän koodin [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)-kansiosta.

### Tehtävä - hae puhe Wio Terminalistasi

1. Avaa `smart-timer`-projektisi VS Codessa, jos se ei ole jo auki.

1. Avaa `config.h`-otsikkotiedosto ja lisää URL funktiosovelluksellesi:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Korvaa `<URL>` URL:lla `text-to-speech` HTTP-triggerille funktiosovelluksessasi. Tämä on sama kuin `TEXT_TO_TIMER_FUNCTION_URL`-arvo, paitsi että funktiolla on nimi `text-to-speech` eikä `text-to-timer`.

1. Avaa `text_to_speech.h`-otsikkotiedosto ja lisää seuraava metodi `TextToSpeech`-luokan `public`-osioon:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Lisää `convertTextToSpeech`-metodiin seuraava koodi JSON:n luomiseksi, joka lähetetään funktiosovellukseen:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tämä kirjoittaa kielen, äänen ja tekstin JSON-dokumenttiin ja sarjoittaa sen merkkijonoksi.

1. Lisää tämän alle seuraava koodi funktiosovelluksen kutsumiseksi:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tämä luo HTTPClientin ja tekee POST-pyynnön JSON-dokumentilla tekstistä puheeksi HTTP-triggerille.

1. Jos kutsu onnistuu, funktiosovelluksen palauttama raaka binaaridata voidaan streamata tiedostoon SD-kortilla. Lisää seuraava koodi tämän tekemiseksi:

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Tämä koodi tarkistaa vastauksen, ja jos se on 200 (onnistuminen), binaaridata streamataan tiedostoon SD-kortin juureen nimeltä `SPEECH.WAV`.

1. Tämän metodin lopussa sulje HTTP-yhteys:

    ```cpp
    httpClient.end();
    ```

1. Nyt teksti, joka halutaan lausua, voidaan muuntaa ääneksi. `main.cpp`-tiedostossa lisää seuraava rivi `say`-funktion loppuun muuntaaksesi lausuttavan tekstin ääneksi:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Tehtävä - toista ääntä Wio Terminalilla

**Tulossa pian**

## Funktiosovelluksen julkaiseminen pilveen

Funktiosovelluksen suorittaminen paikallisesti johtuu siitä, että `librosa`-Pip-paketilla Linuxissa on riippuvuus kirjastoon, joka ei ole oletuksena asennettu ja joka täytyy asentaa ennen kuin funktiosovellus voi toimia. Funktiosovellukset ovat palvelimettomia - ei ole palvelimia, joita voisit hallita itse, joten tätä kirjastoa ei voi asentaa etukäteen.

Ratkaisu tähän on sen sijaan julkaista funktiosovellus Docker-kontin avulla. Tämä kontti otetaan pilvessä käyttöön aina, kun tarvitaan uusi instanssi funktiosovelluksestasi (esimerkiksi silloin, kun kysyntä ylittää käytettävissä olevat resurssit tai jos funktiosovellusta ei ole käytetty pitkään aikaan ja se on suljettu).

Ohjeet funktiosovelluksen luomiseen ja Dockerin kautta julkaisemiseen löydät [Microsoft Docsin Linuxilla mukautetun kontin avulla funktioiden luomisen dokumentaatiosta](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Kun tämä on julkaistu, voit siirtää Wio Terminal -koodisi käyttämään tätä funktiota:

1. Lisää Azure Functions -sertifikaatti tiedostoon `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Vaihda kaikki `
<WiFiClient.h>`-sisällytykset `<WiFiClientSecure.h>`-sisällytyksiin.

1. Vaihda kaikki `WiFiClient`-kentät `WiFiClientSecure`-kentiksi.

1. Lisää jokaiseen luokkaan, jossa on `WiFiClientSecure`-kenttä, konstruktori ja aseta sertifikaatti siinä konstruktorissa:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Vastuuvapauslauseke**:  
Tämä asiakirja on käännetty käyttämällä tekoälypohjaista käännöspalvelua [Co-op Translator](https://github.com/Azure/co-op-translator). Vaikka pyrimme tarkkuuteen, huomioithan, että automaattiset käännökset voivat sisältää virheitä tai epätarkkuuksia. Alkuperäistä asiakirjaa sen alkuperäisellä kielellä tulisi pitää ensisijaisena lähteenä. Kriittisen tiedon osalta suositellaan ammattimaista ihmiskäännöstä. Emme ole vastuussa väärinkäsityksistä tai virhetulkinnoista, jotka johtuvat tämän käännöksen käytöstä.