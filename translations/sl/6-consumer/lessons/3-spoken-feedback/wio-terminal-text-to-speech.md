<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T12:44:33+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "sl"
}
-->
# Pretvorba besedila v govor - Wio Terminal

V tem delu lekcije boste pretvorili besedilo v govor, da zagotovite zvočne povratne informacije.

## Pretvorba besedila v govor

SDK za storitve govora, ki ste ga uporabili v prejšnji lekciji za pretvorbo govora v besedilo, lahko uporabite tudi za pretvorbo besedila nazaj v govor.

## Pridobitev seznama glasov

Pri zahtevi za govor morate določiti glas, ki ga želite uporabiti, saj je govor mogoče ustvariti z različnimi glasovi. Vsak jezik podpira različne glasove, seznam podprtih glasov za vsak jezik pa lahko pridobite iz SDK za storitve govora. Tukaj pridejo do izraza omejitve mikrokrmilnikov - klic za pridobitev seznama glasov, ki jih podpira storitev za pretvorbo besedila v govor, vrne JSON dokument, ki je velik več kot 77 KB, kar je preveliko za obdelavo na Wio Terminalu. V času pisanja ta seznam vsebuje 215 glasov, vsak definiran z JSON dokumentom, kot je naslednji:

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

Ta JSON je za glas **Aria**, ki ima več slogov govora. Za pretvorbo besedila v govor je potreben le kratko ime, `en-US-AriaNeural`.

Namesto da bi prenesli in dekodirali celoten seznam na mikrokrmilniku, boste morali napisati nekaj strežniške kode za pridobitev seznama glasov za jezik, ki ga uporabljate, in to poklicati iz Wio Terminala. Vaša koda lahko nato izbere ustrezen glas s seznama, na primer prvega, ki ga najde.

### Naloga - ustvarite strežniško funkcijo za pridobitev seznama glasov

1. Odprite svoj projekt `smart-timer-trigger` v VS Code in odprite terminal, pri čemer preverite, da je virtualno okolje aktivirano. Če ni, zaprite in ponovno ustvarite terminal.

1. Odprite datoteko `local.settings.json` in dodajte nastavitve za ključ API storitve govora in lokacijo:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Zamenjajte `<key>` s ključem API za vašo storitev govora. Zamenjajte `<location>` z lokacijo, ki ste jo uporabili pri ustvarjanju vira storitve govora.

1. Dodajte nov HTTP sprožilec tej aplikaciji z imenom `get-voices` z naslednjim ukazom v terminalu VS Code v korenski mapi projekta funkcij:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    To bo ustvarilo HTTP sprožilec z imenom `get-voices`.

1. Zamenjajte vsebino datoteke `__init__.py` v mapi `get-voices` z naslednjim:

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

    Ta koda pošlje HTTP zahtevo na končno točko za pridobitev glasov. Seznam glasov je velik JSON dokument z glasovi za vse jezike, zato se glasovi za jezik, poslan v telesu zahteve, filtrirajo, nato pa se izlušči kratko ime in vrne kot JSON seznam. Kratko ime je vrednost, potrebna za pretvorbo besedila v govor, zato se vrne le ta vrednost.

    > 💁 Filter lahko po potrebi spremenite, da izberete le glasove, ki jih želite.

    To zmanjša velikost podatkov s 77 KB (v času pisanja) na veliko manjši JSON dokument. Na primer, za glasove v ZDA je to 408 bajtov.

1. Lokalno zaženite svojo aplikacijo funkcij. Nato jo lahko pokličete z orodjem, kot je curl, na enak način, kot ste testirali HTTP sprožilec `text-to-timer`. Prepričajte se, da ste poslali svoj jezik kot JSON telo:

    ```json
    {
        "language":"<language>"
    }
    ```

    Zamenjajte `<language>` s svojim jezikom, na primer `en-GB` ali `zh-CN`.

> 💁 To kodo najdete v mapi [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Naloga - pridobite glas iz svojega Wio Terminala

1. Odprite projekt `smart-timer` v VS Code, če še ni odprt.

1. Odprite glavno datoteko `config.h` in dodajte URL za svojo aplikacijo funkcij:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Zamenjajte `<URL>` z URL-jem za HTTP sprožilec `get-voices` v vaši aplikaciji funkcij. To bo enako kot vrednost za `TEXT_TO_TIMER_FUNCTION_URL`, razen z imenom funkcije `get-voices` namesto `text-to-timer`.

1. Ustvarite novo datoteko v mapi `src` z imenom `text_to_speech.h`. Ta bo uporabljena za definiranje razreda za pretvorbo besedila v govor.

1. Na vrh nove datoteke `text_to_speech.h` dodajte naslednje direktive za vključitev:

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

1. Pod tem dodajte naslednjo kodo za deklaracijo razreda `TextToSpeech` skupaj z instanco, ki jo lahko uporabite v preostalem delu aplikacije:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Za klic aplikacije funkcij morate deklarirati WiFi odjemalca. Dodajte naslednje v zasebni del razreda:

    ```cpp
    WiFiClient _client;
    ```

1. V zasebni del dodajte polje za izbrani glas:

    ```cpp
    String _voice;
    ```

1. V javni del dodajte funkcijo `init`, ki bo pridobila prvi glas:

    ```cpp
    void init()
    {
    }
    ```

1. Za pridobitev glasov je treba funkciji poslati JSON dokument z jezikom. Dodajte naslednjo kodo v funkcijo `init`, da ustvarite ta JSON dokument:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Nato ustvarite `HTTPClient` in ga uporabite za klic aplikacije funkcij za pridobitev glasov, pri čemer pošljete JSON dokument:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Pod tem dodajte kodo za preverjanje odzivne kode in, če je 200 (uspeh), izluščite seznam glasov ter pridobite prvega s seznama:

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

1. Po tem zaključite povezavo HTTP odjemalca:

    ```cpp
    httpClient.end();
    ```

1. Odprite datoteko `main.cpp` in na vrh dodajte naslednjo direktivo za vključitev te nove glave:

    ```cpp
    #include "text_to_speech.h"
    ```

1. V funkciji `setup`, pod klicem `speechToText.init();`, dodajte naslednje za inicializacijo razreda `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Sestavite to kodo, naložite jo na svoj Wio Terminal in jo preizkusite prek serijskega monitorja. Prepričajte se, da vaša aplikacija funkcij deluje.

    Videli boste seznam razpoložljivih glasov, ki jih vrne aplikacija funkcij, skupaj z izbranim glasom.

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

## Pretvorba besedila v govor

Ko imate glas, ga lahko uporabite za pretvorbo besedila v govor. Iste omejitve pomnilnika, ki veljajo za glasove, veljajo tudi pri pretvorbi govora v besedilo, zato boste morali govor zapisati na SD kartico, da ga predvajate prek ReSpeaker.

> 💁 V prejšnjih lekcijah tega projekta ste za shranjevanje govora, zajetega z mikrofonom, uporabljali flash pomnilnik. Ta lekcija uporablja SD kartico, saj je lažje predvajati zvok z nje z uporabo knjižnic Seeed Audio.

Obstaja tudi druga omejitev, ki jo je treba upoštevati, in sicer razpoložljivi zvočni podatki iz storitve govora ter formati, ki jih podpira Wio Terminal. Za razliko od polnih računalnikov so zvočne knjižnice za mikrokrmilnike lahko zelo omejene glede formatov zvoka, ki jih podpirajo. Na primer, knjižnica Seeed Arduino Audio, ki lahko predvaja zvok prek ReSpeaker, podpira le zvok s frekvenco vzorčenja 44,1 kHz. Storitve Azure Speech lahko zagotovijo zvok v več formatih, vendar nobeden od njih ne uporablja te frekvence vzorčenja; na voljo so le 8 kHz, 16 kHz, 24 kHz in 48 kHz. To pomeni, da je treba zvok ponovno vzorčiti na 44,1 kHz, kar zahteva več virov, kot jih ima Wio Terminal, zlasti pomnilnika.

Ko je treba manipulirati s podatki, kot je ta, je pogosto bolje uporabiti strežniško kodo, še posebej, če so podatki pridobljeni prek spletnega klica. Wio Terminal lahko pokliče strežniško funkcijo, posreduje besedilo za pretvorbo, strežniška funkcija pa lahko pokliče storitev govora za pretvorbo besedila v govor in ponovno vzorči zvok na zahtevano frekvenco vzorčenja. Nato lahko vrne zvok v obliki, ki jo Wio Terminal potrebuje za shranjevanje na SD kartico in predvajanje prek ReSpeaker.

### Naloga - ustvarite strežniško funkcijo za pretvorbo besedila v govor

1. Odprite svoj projekt `smart-timer-trigger` v VS Code in odprite terminal, pri čemer preverite, da je virtualno okolje aktivirano. Če ni, zaprite in ponovno ustvarite terminal.

1. Dodajte nov HTTP sprožilec tej aplikaciji z imenom `text-to-speech` z naslednjim ukazom v terminalu VS Code v korenski mapi projekta funkcij:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    To bo ustvarilo HTTP sprožilec z imenom `text-to-speech`.

1. Paket Pip [librosa](https://librosa.org) ima funkcije za ponovno vzorčenje zvoka, zato ga dodajte v datoteko `requirements.txt`:

    ```sh
    librosa
    ```

    Ko to dodate, namestite pakete Pip z naslednjim ukazom v terminalu VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Če uporabljate Linux, vključno z Raspberry Pi OS, boste morda morali namestiti `libsndfile` z naslednjim ukazom:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Za pretvorbo besedila v govor ne morete neposredno uporabiti ključa API za govor, temveč morate zahtevati dostopni žeton, pri čemer uporabite ključ API za overitev zahteve za dostopni žeton. Odprite datoteko `__init__.py` iz mape `text-to-speech` in zamenjajte vso kodo v njej z naslednjo:

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

    To definira konstante za lokacijo in ključ govora, ki bodo prebrani iz nastavitev. Nato definira funkcijo `get_access_token`, ki bo pridobila dostopni žeton za storitev govora.

1. Pod to kodo dodajte naslednje:

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

    To definira HTTP sprožilec, ki pretvori besedilo v govor. Izlušči besedilo za pretvorbo, jezik in glas iz JSON telesa, poslanega v zahtevo, ustvari nekaj SSML za zahtevo govora, nato pa pokliče ustrezni REST API, pri čemer se overi z dostopnim žetonom. Ta klic REST API vrne zvok, kodiran kot 16-bitni, 48 kHz mono WAV datoteka, določena z vrednostjo `playback_format`, ki je poslana v klic REST API.

    Nato `librosa` ponovno vzorči ta zvok s frekvence vzorčenja 48 kHz na frekvenco vzorčenja 44,1 kHz, nato pa se ta zvok shrani v binarni medpomnilnik, ki se nato vrne.

1. Lokalno zaženite svojo aplikacijo funkcij ali jo namestite v oblak. Nato jo lahko pokličete z orodjem, kot je curl, na enak način, kot ste testirali HTTP sprožilec `text-to-timer`. Prepričajte se, da ste poslali jezik, glas in besedilo kot JSON telo:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Zamenjajte `<language>` s svojim jezikom, na primer `en-GB` ali `zh-CN`. Zamenjajte `<voice>` z glasom, ki ga želite uporabiti. Zamenjajte `<text>` z besedilom, ki ga želite pretvoriti v govor. Izhod lahko shranite v datoteko in ga predvajate s katerim koli predvajalnikom zvoka, ki podpira WAV datoteke.

    Na primer, za pretvorbo "Hello" v govor z uporabo ameriške angleščine in glasu Jenny Neural, z aplikacijo funkcij, ki deluje lokalno, lahko uporabite naslednji ukaz curl:

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

    To bo shranilo zvok v datoteko `hello.wav` v trenutni imenik.

> 💁 To kodo najdete v mapi [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Naloga - pridobite govor iz svojega Wio Terminala

1. Odprite projekt `smart-timer` v VS Code, če še ni odprt.

1. Odprite glavno datoteko `config.h` in dodajte URL za svojo aplikacijo funkcij:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Zamenjajte `<URL>` z URL-jem za HTTP sprožilec `text-to-speech` v vaši aplikaciji funkcij. To bo enako kot vrednost za `TEXT_TO_TIMER_FUNCTION_URL`, razen z imenom funkcije `text-to-speech` namesto `text-to-timer`.

1. Odprite glavno datoteko `text_to_speech.h` in v javni del razreda `TextToSpeech` dodajte naslednjo metodo:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. V metodi `convertTextToSpeech` dodajte naslednjo kodo za ustvarjanje JSON, ki ga pošljete aplikaciji funkcij:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    To zapiše jezik, glas in besedilo v JSON dokument, nato pa ga serializira v niz.

1. Pod tem dodajte naslednjo kodo za klic aplikacije funkcij:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    To ustvari `HTTPClient`, nato pa izvede POST zahtevo z JSON dokumentom na HTTP sprožilec za pretvorbo besedila v govor.

1. Če klic uspe, se surovi binarni podatki, vrnjeni iz klica aplikacije funkcij, lahko pretakajo v datoteko na SD kartici. Dodajte naslednjo kodo za to:

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

    Ta koda preveri odziv in, če je 200 (uspeh), binarne podatke pretaka v datoteko v korenu SD kartice z imenom `SPEECH.WAV`.

1. Na koncu te metode zaprite HTTP povezavo:

    ```cpp
    httpClient.end();
    ```

1. Besedilo, ki ga je treba izgovoriti, je zdaj mogoče pretvoriti v zvok. V datoteki `main.cpp` na koncu funkcije `say` dodajte naslednjo vrstico za pretvorbo besedila v zvok:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Naloga - predvajanje zvoka na vašem Wio Terminalu

**Kmalu na voljo**

## Nameščanje vaše funkcijske aplikacije v oblak

Razlog za zagon funkcijske aplikacije lokalno je, da ima paket `librosa` za Pip na Linuxu odvisnost od knjižnice, ki ni privzeto nameščena, in jo bo treba namestiti, preden lahko funkcijska aplikacija deluje. Funkcijske aplikacije so brez strežnikov - ni strežnikov, ki bi jih lahko sami upravljali, zato ni načina, da bi to knjižnico vnaprej namestili.

Namesto tega je način za to, da funkcijsko aplikacijo namestite z uporabo Docker kontejnerja. Ta kontejner se namesti v oblaku, kadar koli je treba zagnati novo instanco vaše funkcijske aplikacije (na primer, ko povpraševanje preseže razpoložljive vire ali če funkcijska aplikacija ni bila uporabljena nekaj časa in je zaprta).

Navodila za nastavitev funkcijske aplikacije in namestitev prek Dockerja najdete v [dokumentaciji za ustvarjanje funkcije na Linuxu z uporabo prilagojene slike na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Ko je to nameščeno, lahko prenesete svojo kodo za Wio Terminal, da dostopa do te funkcije:

1. Dodajte certifikat za Azure Functions v `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Spremenite vse vključitve `
<WiFiClient.h>` v `<WiFiClientSecure.h>`.

1. Spremenite vsa polja `WiFiClient` v `WiFiClientSecure`.

1. V vsakem razredu, ki ima polje `WiFiClientSecure`, dodajte konstruktor in nastavite certifikat v tem konstruktorju:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Omejitev odgovornosti**:  
Ta dokument je bil preveden z uporabo storitve za prevajanje z umetno inteligenco [Co-op Translator](https://github.com/Azure/co-op-translator). Čeprav si prizadevamo za natančnost, vas prosimo, da upoštevate, da lahko avtomatizirani prevodi vsebujejo napake ali netočnosti. Izvirni dokument v njegovem izvirnem jeziku je treba obravnavati kot avtoritativni vir. Za ključne informacije priporočamo profesionalni človeški prevod. Ne prevzemamo odgovornosti za morebitna nesporazumevanja ali napačne razlage, ki bi nastale zaradi uporabe tega prevoda.