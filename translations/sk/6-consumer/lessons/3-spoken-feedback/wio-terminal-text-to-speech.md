<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T08:59:25+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "sk"
}
-->
# Text na reč - Wio Terminal

V tejto časti lekcie prevediete text na reč, aby ste poskytli hovorenú spätnú väzbu.

## Text na reč

SDK pre služby reči, ktoré ste použili v predchádzajúcej lekcii na prevod reči na text, môžete použiť aj na prevod textu späť na reč.

## Získanie zoznamu hlasov

Pri požiadavke na reč musíte zadať hlas, ktorý sa má použiť, pretože reč môže byť generovaná pomocou rôznych hlasov. Každý jazyk podporuje rôzne hlasy a zoznam podporovaných hlasov pre každý jazyk môžete získať zo služby reči SDK. Tu sa prejavujú obmedzenia mikrokontrolérov - volanie na získanie zoznamu hlasov podporovaných službami text na reč je JSON dokument s veľkosťou viac ako 77 KB, čo je príliš veľké na spracovanie Wio Terminalom. V čase písania tento zoznam obsahuje 215 hlasov, pričom každý je definovaný JSON dokumentom, ako je tento:

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

Tento JSON je pre hlas **Aria**, ktorý má viacero štýlov hlasu. Na prevod textu na reč stačí krátky názov, `en-US-AriaNeural`.

Namiesto sťahovania a dekódovania celého tohto zoznamu na vašom mikrokontroléri budete musieť napísať ďalší serverless kód na získanie zoznamu hlasov pre jazyk, ktorý používate, a zavolať ho z vášho Wio Terminalu. Váš kód potom môže vybrať vhodný hlas zo zoznamu, napríklad prvý, ktorý nájde.

### Úloha - vytvorte serverless funkciu na získanie zoznamu hlasov

1. Otvorte svoj projekt `smart-timer-trigger` vo VS Code a otvorte terminál, pričom sa uistite, že virtuálne prostredie je aktivované. Ak nie, ukončite a znova vytvorte terminál.

1. Otvorte súbor `local.settings.json` a pridajte nastavenia pre kľúč API služby reči a umiestnenie:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Nahraďte `<key>` kľúčom API pre váš zdroj služby reči. Nahraďte `<location>` umiestnením, ktoré ste použili pri vytváraní zdroja služby reči.

1. Pridajte nový HTTP trigger do tejto aplikácie s názvom `get-voices` pomocou nasledujúceho príkazu z terminálu VS Code v koreňovom priečinku projektu aplikácie funkcií:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Tým sa vytvorí HTTP trigger s názvom `get-voices`.

1. Nahraďte obsah súboru `__init__.py` v priečinku `get-voices` nasledujúcim:

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

    Tento kód vykoná HTTP požiadavku na endpoint na získanie hlasov. Tento zoznam hlasov je veľký blok JSON s hlasmi pre všetky jazyky, takže hlasy pre jazyk odoslaný v tele požiadavky sú filtrované, potom sa extrahuje krátky názov a vráti sa ako JSON zoznam. Krátky názov je hodnota potrebná na prevod textu na reč, takže sa vráti iba táto hodnota.

    > 💁 Filter môžete podľa potreby zmeniť, aby ste vybrali iba hlasy, ktoré chcete.

    Tým sa veľkosť údajov zníži z 77 KB (v čase písania) na oveľa menší JSON dokument. Napríklad pre americké hlasy je to 408 bajtov.

1. Spustite svoju funkčnú aplikáciu lokálne. Potom ju môžete zavolať pomocou nástroja ako curl rovnakým spôsobom, ako ste testovali HTTP trigger `text-to-timer`. Uistite sa, že odosielate svoj jazyk ako JSON telo:

    ```json
    {
        "language":"<language>"
    }
    ```

    Nahraďte `<language>` svojím jazykom, napríklad `en-GB` alebo `zh-CN`.

> 💁 Tento kód nájdete v priečinku [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Úloha - získajte hlas z vášho Wio Terminalu

1. Otvorte projekt `smart-timer` vo VS Code, ak ešte nie je otvorený.

1. Otvorte hlavičkový súbor `config.h` a pridajte URL pre vašu funkčnú aplikáciu:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL adresou pre HTTP trigger `get-voices` vo vašej funkčnej aplikácii. Táto bude rovnaká ako hodnota pre `TEXT_TO_TIMER_FUNCTION_URL`, okrem názvu funkcie `get-voices` namiesto `text-to-timer`.

1. Vytvorte nový súbor v priečinku `src` s názvom `text_to_speech.h`. Tento súbor sa použije na definovanie triedy na prevod textu na reč.

1. Pridajte nasledujúce direktívy `include` na začiatok nového súboru `text_to_speech.h`:

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

1. Pod týmto deklarujte triedu `TextToSpeech` spolu s inštanciou, ktorá sa môže použiť v zvyšku aplikácie:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Na volanie vašej funkčnej aplikácie musíte deklarovať WiFi klienta. Pridajte nasledujúce do sekcie `private` triedy:

    ```cpp
    WiFiClient _client;
    ```

1. V sekcii `private` pridajte pole pre vybraný hlas:

    ```cpp
    String _voice;
    ```

1. Do sekcie `public` pridajte funkciu `init`, ktorá získa prvý hlas:

    ```cpp
    void init()
    {
    }
    ```

1. Na získanie hlasov je potrebné odoslať JSON dokument do funkčnej aplikácie s jazykom. Pridajte nasledujúci kód do funkcie `init` na vytvorenie tohto JSON dokumentu:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Následne vytvorte `HTTPClient` a použite ho na volanie funkčnej aplikácie na získanie hlasov, odoslaním JSON dokumentu:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Pod týmto pridajte kód na kontrolu kódu odpovede a ak je 200 (úspech), extrahujte zoznam hlasov a získajte prvý zo zoznamu:

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

1. Po tomto ukončite pripojenie HTTP klienta:

    ```cpp
    httpClient.end();
    ```

1. Otvorte súbor `main.cpp` a pridajte nasledujúcu direktívu `include` na začiatok, aby ste zahrnuli tento nový hlavičkový súbor:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Vo funkcii `setup`, pod volaním `speechToText.init();`, pridajte nasledujúce na inicializáciu triedy `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Skontrolujte kód, nahrajte ho do vášho Wio Terminalu a otestujte ho cez sériový monitor. Uistite sa, že vaša funkčná aplikácia beží.

    Uvidíte zoznam dostupných hlasov vrátených z funkčnej aplikácie spolu s vybraným hlasom.

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

## Prevod textu na reč

Keď máte hlas, ktorý chcete použiť, môžete ho použiť na prevod textu na reč. Rovnaké obmedzenia pamäte pre hlasy platia aj pri prevode reči na text, takže reč budete musieť uložiť na SD kartu, aby sa mohla prehrať cez ReSpeaker.

> 💁 V predchádzajúcich lekciách tohto projektu ste používali flash pamäť na ukladanie reči zachytenej z mikrofónu. Táto lekcia používa SD kartu, pretože je jednoduchšie prehrávať zvuk z nej pomocou knižníc Seeed audio.

Existuje aj ďalšie obmedzenie, ktoré treba zvážiť, a to dostupné zvukové dáta zo služby reči a formáty, ktoré Wio Terminal podporuje. Na rozdiel od plnohodnotných počítačov môžu byť zvukové knižnice pre mikrokontroléry veľmi obmedzené v podporovaných zvukových formátoch. Napríklad knižnica Seeed Arduino Audio, ktorá dokáže prehrávať zvuk cez ReSpeaker, podporuje iba zvuk so vzorkovacou frekvenciou 44,1 kHz. Služby Azure reči môžu poskytovať zvuk v niekoľkých formátoch, ale žiadny z nich nepoužíva túto vzorkovaciu frekvenciu, poskytujú iba 8 kHz, 16 kHz, 24 kHz a 48 kHz. To znamená, že zvuk musí byť pre-vzorkovaný na 44,1 kHz, čo by vyžadovalo viac zdrojov, než má Wio Terminal, najmä pamäte.

Keď je potrebné manipulovať s údajmi, ako sú tieto, je často lepšie použiť serverless kód, najmä ak sú údaje získavané prostredníctvom webového volania. Wio Terminal môže zavolať serverless funkciu, odovzdať text na prevod a serverless funkcia môže zavolať službu reči na prevod textu na reč, ako aj pre-vzorkovať zvuk na požadovanú vzorkovaciu frekvenciu. Potom môže vrátiť zvuk vo formáte, ktorý Wio Terminal potrebuje, aby sa mohol uložiť na SD kartu a prehrať cez ReSpeaker.

### Úloha - vytvorte serverless funkciu na prevod textu na reč

1. Otvorte svoj projekt `smart-timer-trigger` vo VS Code a otvorte terminál, pričom sa uistite, že virtuálne prostredie je aktivované. Ak nie, ukončite a znova vytvorte terminál.

1. Pridajte nový HTTP trigger do tejto aplikácie s názvom `text-to-speech` pomocou nasledujúceho príkazu z terminálu VS Code v koreňovom priečinku projektu aplikácie funkcií:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Tým sa vytvorí HTTP trigger s názvom `text-to-speech`.

1. Balík Pip [librosa](https://librosa.org) obsahuje funkcie na pre-vzorkovanie zvuku, takže ho pridajte do súboru `requirements.txt`:

    ```sh
    librosa
    ```

    Po pridaní nainštalujte balíky Pip pomocou nasledujúceho príkazu z terminálu VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Ak používate Linux, vrátane Raspberry Pi OS, možno budete musieť nainštalovať `libsndfile` pomocou nasledujúceho príkazu:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Na prevod textu na reč nemôžete použiť priamo kľúč API služby reči, namiesto toho musíte požiadať o prístupový token, pričom na autentifikáciu požiadavky na prístupový token použijete kľúč API. Otvorte súbor `__init__.py` z priečinka `text-to-speech` a nahraďte všetok kód v ňom nasledujúcim:

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

    Tým sa definujú konštanty pre umiestnenie a kľúč služby reči, ktoré sa načítajú z nastavení. Potom sa definuje funkcia `get_access_token`, ktorá získa prístupový token pre službu reči.

1. Pod tento kód pridajte nasledujúce:

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

    Tým sa definuje HTTP trigger, ktorý prevádza text na reč. Extrahuje text na prevod, jazyk a hlas z JSON tela odoslaného v požiadavke, vytvorí SSML na požiadavku reči a potom zavolá príslušné REST API, pričom autentifikuje pomocou prístupového tokenu. Toto volanie REST API vráti zvuk kódovaný ako 16-bitový, 48 kHz mono WAV súbor, definovaný hodnotou `playback_format`, ktorá sa odosiela do volania REST API.

    Tento zvuk sa potom pre-vzorkuje pomocou `librosa` z vzorkovacej frekvencie 48 kHz na vzorkovaciu frekvenciu 44,1 kHz, potom sa tento zvuk uloží do binárneho bufferu, ktorý sa následne vráti.

1. Spustite svoju funkčnú aplikáciu lokálne alebo ju nasadte do cloudu. Potom ju môžete zavolať pomocou nástroja ako curl rovnakým spôsobom, ako ste testovali HTTP trigger `text-to-timer`. Uistite sa, že odosielate jazyk, hlas a text ako JSON telo:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Nahraďte `<language>` svojím jazykom, napríklad `en-GB` alebo `zh-CN`. Nahraďte `<voice>` hlasom, ktorý chcete použiť. Nahraďte `<text>` textom, ktorý chcete previesť na reč. Výstup môžete uložiť do súboru a prehrať ho pomocou akéhokoľvek prehrávača, ktorý dokáže prehrávať WAV súbory.

    Napríklad na prevod "Hello" na reč pomocou americkej angličtiny s hlasom Jenny Neural, s funkčnou aplikáciou bežiacou lokálne, môžete použiť nasledujúci príkaz curl:

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

    Tým sa uloží zvuk do `hello.wav` v aktuálnom adresári.

> 💁 Tento kód nájdete v priečinku [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Úloha - získajte reč z vášho Wio Terminalu

1. Otvorte projekt `smart-timer` vo VS Code, ak ešte nie je otvorený.

1. Otvorte hlavičkový súbor `config.h` a pridajte URL pre vašu funkčnú aplikáciu:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL adresou pre HTTP trigger `text-to-speech` vo vašej funkčnej aplikácii. Táto bude rovnaká ako hodnota pre `TEXT_TO_TIMER_FUNCTION_URL`, okrem názvu funkcie `text-to-speech` namiesto `text-to-timer`.

1. Otvorte hlavičkový súbor `text_to_speech.h` a pridajte nasledujúcu metódu do sekcie `public` triedy `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Do metódy `convertTextToSpeech` pridajte nasledujúci kód na vytvorenie JSON na odoslanie do funkčnej aplikácie:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tento kód zapisuje jazyk, hlas a text do JSON dokumentu a potom ho serializuje na reťazec.

1. Pod týmto pridajte nasledujúci kód na volanie funkčnej aplikácie:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tento kód vytvorí `HTTPClient` a potom vykoná POST požiadavku pomocou JSON dokumentu na HTTP trigger `text-to-speech`.

1. Ak volanie funguje, surové binárne dáta vrátené z volania funkčnej aplikácie môžu byť streamované do súboru na SD karte. Pridajte nasledujúci kód na vykonanie tohto:

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

    Tento kód skontroluje odpoveď a ak je 200 (úspech), binárne dáta sa streamujú do súboru v koreňovom adresári SD karty s názvom `SPEECH.WAV`.

1. Na konci tejto metódy ukončite HTTP pripojenie:

    ```cpp
    httpClient.end();
    ```

1. Text, ktorý sa má prehovoriť, teraz môžete previesť na zvuk. V súbore `main.cpp` pridajte nasledujúci riadok na koniec funkcie `say`, aby ste previedli text na reč:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Úloha - prehrávanie zvuku z vášho Wio Terminalu

**Čoskoro dostupné**

## Nasadenie vašej funkčnej aplikácie do cloudu

Dôvodom, prečo spúšťať funkčnú aplikáciu lokálne, je to, že balík `librosa` pre Pip na Linuxe má závislosť na knižnici, ktorá nie je predvolene nainštalovaná, a bude ju potrebné nainštalovať predtým, než bude funkčná aplikácia schopná bežať. Funkčné aplikácie sú bezserverové - neexistujú servery, ktoré by ste mohli spravovať sami, takže nie je možné túto knižnicu nainštalovať vopred.

Riešením je namiesto toho nasadiť vašu funkčnú aplikáciu pomocou Docker kontajnera. Tento kontajner je nasadený cloudom vždy, keď je potrebné spustiť novú inštanciu vašej funkčnej aplikácie (napríklad keď dopyt presiahne dostupné zdroje alebo ak aplikácia nebola nejaký čas používaná a bola ukončená).

Pokyny na nastavenie funkčnej aplikácie a nasadenie cez Docker nájdete v [dokumentácii na Microsoft Docs o vytvorení funkcie na Linuxe pomocou vlastného kontajnera](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Keď je aplikácia nasadená, môžete preniesť kód pre Wio Terminal na prístup k tejto funkcii:

1. Pridajte certifikát Azure Functions do `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Zmeňte všetky zahrnutia `
<WiFiClient.h>` na `<WiFiClientSecure.h>`.

1. Zmeňte všetky polia `WiFiClient` na `WiFiClientSecure`.

1. V každej triede, ktorá má pole `WiFiClientSecure`, pridajte konštruktor a nastavte certifikát v tomto konštruktore:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Upozornenie**:  
Tento dokument bol preložený pomocou služby AI prekladu [Co-op Translator](https://github.com/Azure/co-op-translator). Hoci sa snažíme o presnosť, prosím, berte na vedomie, že automatizované preklady môžu obsahovať chyby alebo nepresnosti. Pôvodný dokument v jeho rodnom jazyku by mal byť považovaný za autoritatívny zdroj. Pre kritické informácie sa odporúča profesionálny ľudský preklad. Nie sme zodpovední za akékoľvek nedorozumenia alebo nesprávne interpretácie vyplývajúce z použitia tohto prekladu.