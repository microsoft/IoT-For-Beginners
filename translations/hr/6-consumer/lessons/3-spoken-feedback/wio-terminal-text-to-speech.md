<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T12:43:32+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "hr"
}
-->
# Pretvaranje teksta u govor - Wio Terminal

U ovom dijelu lekcije pretvorit ćete tekst u govor kako biste omogućili govornu povratnu informaciju.

## Pretvaranje teksta u govor

SDK za govorne usluge koji ste koristili u prethodnoj lekciji za pretvaranje govora u tekst može se koristiti za pretvaranje teksta natrag u govor.

## Dohvaćanje popisa glasova

Prilikom zahtjeva za govor, potrebno je odabrati glas koji će se koristiti, jer govor može biti generiran koristeći različite glasove. Svaki jezik podržava niz različitih glasova, a popis podržanih glasova za svaki jezik možete dobiti putem SDK-a za govorne usluge. Ovdje dolaze do izražaja ograničenja mikrokontrolera - poziv za dohvaćanje popisa glasova podržanih za pretvaranje teksta u govor vraća JSON dokument veličine preko 77KB, što je preveliko za obradu na Wio Terminalu. U trenutku pisanja, cijeli popis sadrži 215 glasova, svaki definiran JSON dokumentom poput sljedećeg:

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

Ovaj JSON dokument odnosi se na glas **Aria**, koji ima više stilova glasa. Sve što je potrebno za pretvaranje teksta u govor je kratko ime, `en-US-AriaNeural`.

Umjesto preuzimanja i dekodiranja cijelog popisa na vašem mikrokontroleru, potrebno je napisati dodatni serverless kod za dohvaćanje popisa glasova za jezik koji koristite i pozvati ga s vašeg Wio Terminala. Vaš kod tada može odabrati odgovarajući glas s popisa, poput prvog koji pronađe.

### Zadatak - kreiranje serverless funkcije za dohvaćanje popisa glasova

1. Otvorite svoj projekt `smart-timer-trigger` u VS Code-u i otvorite terminal, osiguravajući da je virtualno okruženje aktivirano. Ako nije, zatvorite i ponovno kreirajte terminal.

1. Otvorite datoteku `local.settings.json` i dodajte postavke za API ključ govorne usluge i lokaciju:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Zamijenite `<key>` API ključem za vaš resurs govorne usluge. Zamijenite `<location>` lokacijom koju ste koristili prilikom kreiranja resursa govorne usluge.

1. Dodajte novi HTTP trigger ovoj aplikaciji nazvan `get-voices` koristeći sljedeću naredbu unutar terminala u root direktoriju projekta funkcijske aplikacije:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Ovo će kreirati HTTP trigger nazvan `get-voices`.

1. Zamijenite sadržaj datoteke `__init__.py` u mapi `get-voices` sljedećim:

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

    Ovaj kod šalje HTTP zahtjev prema endpointu za dohvaćanje glasova. Popis glasova je veliki blok JSON-a s glasovima za sve jezike, pa se glasovi za jezik proslijeđen u tijelu zahtjeva filtriraju, zatim se kratko ime izvlači i vraća kao JSON popis. Kratko ime je vrijednost potrebna za pretvaranje teksta u govor, pa se samo ta vrijednost vraća.

    > 💁 Možete promijeniti filter prema potrebi kako biste odabrali samo glasove koje želite.

    Ovo smanjuje veličinu podataka s 77KB (u trenutku pisanja) na mnogo manji JSON dokument. Na primjer, za glasove iz SAD-a ovo je 408 bajtova.

1. Pokrenite svoju funkcijsku aplikaciju lokalno. Zatim je možete pozvati koristeći alat poput curl-a na isti način na koji ste testirali HTTP trigger `text-to-timer`. Obavezno proslijedite svoj jezik kao JSON tijelo:

    ```json
    {
        "language":"<language>"
    }
    ```

    Zamijenite `<language>` svojim jezikom, poput `en-GB` ili `zh-CN`.

> 💁 Ovaj kod možete pronaći u mapi [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Zadatak - dohvaćanje glasa s vašeg Wio Terminala

1. Otvorite projekt `smart-timer` u VS Code-u ako već nije otvoren.

1. Otvorite datoteku zaglavlja `config.h` i dodajte URL za vašu funkcijsku aplikaciju:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Zamijenite `<URL>` URL-om za HTTP trigger `get-voices` u vašoj funkcijskoj aplikaciji. Ovo će biti isto kao vrijednost za `TEXT_TO_TIMER_FUNCTION_URL`, osim što će ime funkcije biti `get-voices` umjesto `text-to-timer`.

1. Kreirajte novu datoteku u mapi `src` nazvanu `text_to_speech.h`. Ova datoteka će se koristiti za definiranje klase za pretvaranje teksta u govor.

1. Dodajte sljedeće direktive za uključivanje na vrh nove datoteke `text_to_speech.h`:

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

1. Dodajte sljedeći kod ispod ovoga za deklaraciju klase `TextToSpeech`, zajedno s instancom koja se može koristiti u ostatku aplikacije:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Za pozivanje funkcijske aplikacije, potrebno je deklarirati WiFi klijent. Dodajte sljedeće u privatni dio klase:

    ```cpp
    WiFiClient _client;
    ```

1. U privatni dio dodajte polje za odabrani glas:

    ```cpp
    String _voice;
    ```

1. U javni dio dodajte funkciju `init` koja će dohvatiti prvi glas:

    ```cpp
    void init()
    {
    }
    ```

1. Za dohvaćanje glasova, JSON dokument treba biti poslan funkcijskoj aplikaciji s jezikom. Dodajte sljedeći kod u funkciju `init` za kreiranje ovog JSON dokumenta:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Zatim kreirajte `HTTPClient`, a zatim ga koristite za pozivanje funkcijske aplikacije kako biste dobili glasove, šaljući JSON dokument:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ispod ovoga dodajte kod za provjeru odgovora, i ako je 200 (uspjeh), tada izvucite popis glasova, dohvaćajući prvi s popisa:

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

1. Nakon ovoga, završite HTTP klijentsku vezu:

    ```cpp
    httpClient.end();
    ```

1. Otvorite datoteku `main.cpp` i dodajte sljedeću direktivu za uključivanje na vrh kako biste uključili ovu novu datoteku zaglavlja:

    ```cpp
    #include "text_to_speech.h"
    ```

1. U funkciji `setup`, ispod poziva `speechToText.init();`, dodajte sljedeće za inicijalizaciju klase `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Izgradite ovaj kod, učitajte ga na vaš Wio Terminal i testirajte ga putem serijskog monitora. Osigurajte da vaša funkcijska aplikacija radi.

    Vidjet ćete popis dostupnih glasova vraćenih iz funkcijske aplikacije, zajedno s odabranim glasom.

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

## Pretvaranje teksta u govor

Kada imate glas koji ćete koristiti, on se može koristiti za pretvaranje teksta u govor. Ista ograničenja memorije s glasovima primjenjuju se i prilikom pretvaranja govora u tekst, pa ćete govor morati zapisati na SD karticu kako bi se mogao reproducirati preko ReSpeakera.

> 💁 U ranijim lekcijama ovog projekta koristili ste flash memoriju za pohranu govora snimljenog s mikrofona. Ova lekcija koristi SD karticu jer je lakše reproducirati audio s nje koristeći Seeed audio biblioteke.

Postoji još jedno ograničenje koje treba uzeti u obzir, dostupni audio podaci iz govorne usluge i formati koje Wio Terminal podržava. Za razliku od računala, audio biblioteke za mikrokontrolere mogu biti vrlo ograničene u formatima koje podržavaju. Na primjer, Seeed Arduino Audio biblioteka koja može reproducirati zvuk preko ReSpeakera podržava samo audio sa sample rate-om od 44.1KHz. Azure govorne usluge mogu pružiti audio u nekoliko formata, ali nijedan od njih ne koristi ovaj sample rate, oni pružaju samo 8KHz, 16KHz, 24KHz i 48KHz. To znači da audio treba biti ponovno uzorkovan na 44.1KHz, što bi zahtijevalo više resursa nego što Wio Terminal ima, posebno memorije.

Kada je potrebno manipulirati podacima poput ovih, često je bolje koristiti serverless kod, posebno ako se podaci dobivaju putem web poziva. Wio Terminal može pozvati serverless funkciju, proslijediti tekst za pretvaranje, a serverless funkcija može pozvati govornu uslugu za pretvaranje teksta u govor, kao i ponovno uzorkovati audio na potrebni sample rate. Zatim može vratiti audio u obliku koji Wio Terminal treba za pohranu na SD kartici i reprodukciju preko ReSpeakera.

### Zadatak - kreiranje serverless funkcije za pretvaranje teksta u govor

1. Otvorite svoj projekt `smart-timer-trigger` u VS Code-u i otvorite terminal, osiguravajući da je virtualno okruženje aktivirano. Ako nije, zatvorite i ponovno kreirajte terminal.

1. Dodajte novi HTTP trigger ovoj aplikaciji nazvan `text-to-speech` koristeći sljedeću naredbu unutar terminala u root direktoriju projekta funkcijske aplikacije:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Ovo će kreirati HTTP trigger nazvan `text-to-speech`.

1. Pip paket [librosa](https://librosa.org) ima funkcije za ponovno uzorkovanje audio zapisa, pa ga dodajte u datoteku `requirements.txt`:

    ```sh
    librosa
    ```

    Nakon što je ovo dodano, instalirajte Pip pakete koristeći sljedeću naredbu iz terminala u VS Code-u:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Ako koristite Linux, uključujući Raspberry Pi OS, možda ćete morati instalirati `libsndfile` koristeći sljedeću naredbu:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Za pretvaranje teksta u govor, ne možete koristiti API ključ govorne usluge direktno, već trebate zatražiti pristupni token koristeći API ključ za autentifikaciju zahtjeva za pristupni token. Otvorite datoteku `__init__.py` iz mape `text-to-speech` i zamijenite sav kod u njoj sljedećim:

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

    Ovo definira konstante za lokaciju i govorni ključ koji će se čitati iz postavki. Zatim definira funkciju `get_access_token` koja će dohvatiti pristupni token za govornu uslugu.

1. Ispod ovog koda dodajte sljedeće:

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

    Ovo definira HTTP trigger koji pretvara tekst u govor. Izvlači tekst za pretvaranje, jezik i glas iz JSON tijela poslanog u zahtjev, gradi SSML za zahtjev govora, zatim poziva odgovarajući REST API autentificirajući se koristeći pristupni token. Ovaj REST API poziv vraća audio kodiran kao 16-bitni, 48KHz mono WAV datoteku, definiranu vrijednošću `playback_format`, koja se šalje REST API pozivu.

    Ovo se zatim ponovno uzorkuje pomoću `librosa` sa sample rate-a od 48KHz na sample rate od 44.1KHz, zatim se ovaj audio zapis sprema u binarni buffer koji se zatim vraća.

1. Pokrenite svoju funkcijsku aplikaciju lokalno ili je implementirajte u oblak. Zatim je možete pozvati koristeći alat poput curl-a na isti način na koji ste testirali HTTP trigger `text-to-timer`. Obavezno proslijedite jezik, glas i tekst kao JSON tijelo:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Zamijenite `<language>` svojim jezikom, poput `en-GB` ili `zh-CN`. Zamijenite `<voice>` glasom koji želite koristiti. Zamijenite `<text>` tekstom koji želite pretvoriti u govor. Možete spremiti izlaz u datoteku i reproducirati ga s bilo kojim audio playerom koji može reproducirati WAV datoteke.

    Na primjer, za pretvaranje "Hello" u govor koristeći američki engleski s glasom Jenny Neural, s funkcijskom aplikacijom koja radi lokalno, možete koristiti sljedeću curl naredbu:

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

    Ovo će spremiti audio u `hello.wav` u trenutnom direktoriju.

> 💁 Ovaj kod možete pronaći u mapi [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Zadatak - dohvaćanje govora s vašeg Wio Terminala

1. Otvorite projekt `smart-timer` u VS Code-u ako već nije otvoren.

1. Otvorite datoteku zaglavlja `config.h` i dodajte URL za vašu funkcijsku aplikaciju:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Zamijenite `<URL>` URL-om za HTTP trigger `text-to-speech` u vašoj funkcijskoj aplikaciji. Ovo će biti isto kao vrijednost za `TEXT_TO_TIMER_FUNCTION_URL`, osim što će ime funkcije biti `text-to-speech` umjesto `text-to-timer`.

1. Otvorite datoteku zaglavlja `text_to_speech.h` i dodajte sljedeću metodu u javni dio klase `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. U metodu `convertTextToSpeech` dodajte sljedeći kod za kreiranje JSON-a koji će se poslati funkcijskoj aplikaciji:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Ovo zapisuje jezik, glas i tekst u JSON dokument, zatim ga serijalizira u string.

1. Ispod ovoga dodajte sljedeći kod za pozivanje funkcijske aplikacije:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Ovo kreira `HTTPClient`, zatim izvršava POST zahtjev koristeći JSON dokument prema HTTP triggeru za pretvaranje teksta u govor.

1. Ako poziv uspije, sirovi binarni podaci vraćeni iz poziva funkcijske aplikacije mogu se streamati u datoteku na SD kartici. Dodajte sljedeći kod za to:

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

    Ovaj kod provjerava odgovor, i ako je 200 (uspjeh), binarni podaci se streamaju u datoteku u root direktoriju SD kartice nazvanu `SPEECH.WAV`.

1. Na kraju ove metode zatvorite HTTP vezu:

    ```cpp
    httpClient.end();
    ```

1. Tekst koji treba izgovoriti sada se može pretvoriti u audio. U datoteci `main.cpp` dodajte sljedeći redak na kraj funkcije `say` kako biste pretvorili tekst za izgovor u audio:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Zadatak - reproducirajte zvuk na svom Wio Terminalu

**Uskoro dostupno**

## Postavljanje vaše funkcijske aplikacije u oblak

Razlog za pokretanje funkcijske aplikacije lokalno je taj što `librosa` Pip paket na Linuxu ima ovisnost o biblioteci koja nije instalirana prema zadanim postavkama i mora se instalirati prije nego što funkcijska aplikacija može raditi. Funkcijske aplikacije su bez poslužitelja - nema poslužitelja koje možete sami upravljati, pa nema načina da unaprijed instalirate ovu biblioteku.

Umjesto toga, način za to je postavljanje vaše funkcijske aplikacije pomoću Docker kontejnera. Ovaj kontejner oblak postavlja kad god treba pokrenuti novu instancu vaše funkcijske aplikacije (na primjer, kada potražnja premaši dostupne resurse ili ako funkcijska aplikacija nije korištena neko vrijeme i zatvorena je).

Upute za postavljanje funkcijske aplikacije i implementaciju putem Dockera možete pronaći u [dokumentaciji za stvaranje funkcije na Linuxu koristeći prilagođeni kontejner na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Nakon što je aplikacija postavljena, možete prenijeti svoj Wio Terminal kod kako biste pristupili ovoj funkciji:

1. Dodajte Azure Functions certifikat u `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Promijenite sve uključivanja `
<WiFiClient.h>` u `<WiFiClientSecure.h>`.

1. Promijenite sva polja `WiFiClient` u `WiFiClientSecure`.

1. U svakoj klasi koja ima polje `WiFiClientSecure`, dodajte konstruktor i postavite certifikat u tom konstruktoru:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Odricanje od odgovornosti**:  
Ovaj dokument je preveden pomoću AI usluge za prevođenje [Co-op Translator](https://github.com/Azure/co-op-translator). Iako nastojimo osigurati točnost, imajte na umu da automatski prijevodi mogu sadržavati pogreške ili netočnosti. Izvorni dokument na izvornom jeziku treba smatrati autoritativnim izvorom. Za ključne informacije preporučuje se profesionalni prijevod od strane ljudskog prevoditelja. Ne preuzimamo odgovornost za nesporazume ili pogrešna tumačenja koja mogu proizaći iz korištenja ovog prijevoda.