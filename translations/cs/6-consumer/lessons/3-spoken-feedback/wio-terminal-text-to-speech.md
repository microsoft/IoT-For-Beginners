<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T21:11:53+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "cs"
}
-->
# Převod textu na řeč - Wio Terminal

V této části lekce převedete text na řeč, abyste poskytli mluvenou zpětnou vazbu.

## Převod textu na řeč

SDK pro služby řeči, které jste použili v předchozí lekci k převodu řeči na text, lze také použít k převodu textu zpět na řeč.

## Získání seznamu hlasů

Při požadavku na řeč je nutné zadat hlas, který se má použít, protože řeč může být generována pomocí různých hlasů. Každý jazyk podporuje různé hlasy a seznam podporovaných hlasů pro každý jazyk můžete získat pomocí SDK služeb řeči. Zde se projevují omezení mikrokontrolérů – volání pro získání seznamu hlasů podporovaných službami převodu textu na řeč vrací JSON dokument o velikosti přes 77 KB, což je příliš velké na zpracování Wio Terminalem. V době psaní tohoto textu obsahuje celý seznam 215 hlasů, přičemž každý je definován JSON dokumentem, jako je následující:

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

Tento JSON je pro hlas **Aria**, který má několik stylů hlasu. Pro převod textu na řeč je potřeba pouze krátký název, `en-US-AriaNeural`.

Místo stahování a dekódování celého seznamu na mikrokontroléru budete muset napsat další serverless kód, který získá seznam hlasů pro jazyk, který používáte, a zavolat tento kód z Wio Terminalu. Vaše aplikace pak může vybrat vhodný hlas ze seznamu, například první nalezený.

### Úkol - vytvoření serverless funkce pro získání seznamu hlasů

1. Otevřete svůj projekt `smart-timer-trigger` ve VS Code a otevřete terminál, přičemž se ujistěte, že je aktivováno virtuální prostředí. Pokud ne, ukončete a znovu vytvořte terminál.

1. Otevřete soubor `local.settings.json` a přidejte nastavení pro klíč API služby řeči a umístění:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Nahraďte `<key>` klíčem API pro váš zdroj služby řeči. Nahraďte `<location>` umístěním, které jste použili při vytvoření zdroje služby řeči.

1. Přidejte nový HTTP trigger do této aplikace s názvem `get-voices` pomocí následujícího příkazu v terminálu VS Code v kořenové složce projektu funkcí:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Tím se vytvoří HTTP trigger s názvem `get-voices`.

1. Nahraďte obsah souboru `__init__.py` ve složce `get-voices` následujícím:

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

    Tento kód provádí HTTP požadavek na endpoint pro získání hlasů. Tento seznam hlasů je velký JSON dokument obsahující hlasy pro všechny jazyky, takže hlasy pro jazyk předaný v těle požadavku jsou filtrovány a poté je extrahován krátký název a vrácen jako JSON seznam. Krátký název je hodnota potřebná pro převod textu na řeč, takže je vrácena pouze tato hodnota.

    > 💁 Filtr můžete upravit podle potřeby, abyste vybrali pouze hlasy, které chcete.

    Tím se velikost dat zmenší z 77 KB (v době psaní) na mnohem menší JSON dokument. Například pro americké hlasy je to 408 bajtů.

1. Spusťte svou funkční aplikaci lokálně. Poté ji můžete volat pomocí nástroje jako curl stejným způsobem, jakým jste testovali HTTP trigger `text-to-timer`. Ujistěte se, že předáváte svůj jazyk jako JSON tělo:

    ```json
    {
        "language":"<language>"
    }
    ```

    Nahraďte `<language>` svým jazykem, například `en-GB` nebo `zh-CN`.

> 💁 Tento kód najdete ve složce [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Úkol - získání hlasu z Wio Terminalu

1. Otevřete projekt `smart-timer` ve VS Code, pokud již není otevřen.

1. Otevřete hlavičkový soubor `config.h` a přidejte URL pro vaši funkční aplikaci:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL pro HTTP trigger `get-voices` ve vaší funkční aplikaci. Toto bude stejné jako hodnota `TEXT_TO_TIMER_FUNCTION_URL`, kromě názvu funkce `get-voices` místo `text-to-timer`.

1. Vytvořte nový soubor ve složce `src` s názvem `text_to_speech.h`. Tento soubor bude použit k definování třídy pro převod textu na řeč.

1. Přidejte následující direktivy include na začátek nového souboru `text_to_speech.h`:

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

1. Přidejte následující kód pod tyto direktivy pro deklaraci třídy `TextToSpeech` spolu s instancí, která může být použita ve zbytku aplikace:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Pro volání vaší funkční aplikace musíte deklarovat WiFi klienta. Přidejte následující do sekce `private` třídy:

    ```cpp
    WiFiClient _client;
    ```

1. V sekci `private` přidejte pole pro vybraný hlas:

    ```cpp
    String _voice;
    ```

1. Do sekce `public` přidejte funkci `init`, která získá první hlas:

    ```cpp
    void init()
    {
    }
    ```

1. Pro získání hlasů je potřeba vytvořit JSON dokument, který bude odeslán do funkční aplikace s jazykem. Přidejte následující kód do funkce `init` pro vytvoření tohoto JSON dokumentu:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Dále vytvořte `HTTPClient` a použijte jej k volání funkční aplikace pro získání hlasů, odesláním JSON dokumentu:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Pod tímto přidejte kód pro kontrolu kódu odpovědi a pokud je 200 (úspěch), extrahujte seznam hlasů a získejte první z nich:

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

1. Poté ukončete připojení HTTP klienta:

    ```cpp
    httpClient.end();
    ```

1. Otevřete soubor `main.cpp` a přidejte následující direktivu include na začátek pro zahrnutí tohoto nového hlavičkového souboru:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Ve funkci `setup` pod voláním `speechToText.init();` přidejte následující pro inicializaci třídy `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Sestavte tento kód, nahrajte jej do svého Wio Terminalu a otestujte jej přes sériový monitor. Ujistěte se, že vaše funkční aplikace běží.

    Uvidíte seznam dostupných hlasů vrácený z funkční aplikace spolu s vybraným hlasem.

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

## Převod textu na řeč

Jakmile máte hlas, který chcete použít, můžete jej použít k převodu textu na řeč. Stejná omezení paměti, která platí pro hlasy, platí také při převodu řeči na text, takže budete muset uložit řeč na SD kartu, aby mohla být přehrána přes ReSpeaker.

> 💁 V dřívějších lekcích tohoto projektu jste používali flash paměť pro ukládání řeči zachycené z mikrofonu. Tato lekce používá SD kartu, protože je jednodušší přehrávat zvuk z ní pomocí knihoven Seeed audio.

Existuje také další omezení, které je třeba zvážit, a to dostupné zvukové formáty ze služby řeči a formáty, které Wio Terminal podporuje. Na rozdíl od plnohodnotných počítačů mohou být zvukové knihovny pro mikrokontroléry velmi omezené v podporovaných zvukových formátech. Například knihovna Seeed Arduino Audio, která umožňuje přehrávání zvuku přes ReSpeaker, podporuje pouze zvuk s vzorkovací frekvencí 44,1 kHz. Služby řeči Azure mohou poskytovat zvuk v několika formátech, ale žádný z nich nepoužívá tuto vzorkovací frekvenci, poskytují pouze 8 kHz, 16 kHz, 24 kHz a 48 kHz. To znamená, že zvuk musí být pře-vzorkován na 44,1 kHz, což by vyžadovalo více prostředků, než má Wio Terminal, zejména paměti.

Když je potřeba manipulovat s daty tímto způsobem, je často lepší použít serverless kód, zejména pokud jsou data získávána prostřednictvím webového volání. Wio Terminal může zavolat serverless funkci, předat text k převodu a serverless funkce může jak zavolat službu řeči pro převod textu na řeč, tak pře-vzorkovat zvuk na požadovanou vzorkovací frekvenci. Poté může vrátit zvuk ve formátu, který Wio Terminal potřebuje, aby mohl být uložen na SD kartu a přehrán přes ReSpeaker.

### Úkol - vytvoření serverless funkce pro převod textu na řeč

1. Otevřete svůj projekt `smart-timer-trigger` ve VS Code a otevřete terminál, přičemž se ujistěte, že je aktivováno virtuální prostředí. Pokud ne, ukončete a znovu vytvořte terminál.

1. Přidejte nový HTTP trigger do této aplikace s názvem `text-to-speech` pomocí následujícího příkazu v terminálu VS Code v kořenové složce projektu funkcí:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Tím se vytvoří HTTP trigger s názvem `text-to-speech`.

1. Balíček Pip [librosa](https://librosa.org) obsahuje funkce pro pře-vzorkování zvuku, takže jej přidejte do souboru `requirements.txt`:

    ```sh
    librosa
    ```

    Jakmile to přidáte, nainstalujte balíčky Pip pomocí následujícího příkazu v terminálu VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Pokud používáte Linux, včetně Raspberry Pi OS, možná budete muset nainstalovat `libsndfile` pomocí následujícího příkazu:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Pro převod textu na řeč nemůžete přímo použít klíč API služby řeči, místo toho musíte požádat o přístupový token, přičemž klíč API použijete k autentizaci požadavku na přístupový token. Otevřete soubor `__init__.py` ze složky `text-to-speech` a nahraďte veškerý kód v něm následujícím:

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

    Tento kód definuje konstanty pro umístění a klíč služby řeči, které budou čteny z nastavení. Poté definuje funkci `get_access_token`, která získá přístupový token pro službu řeči.

1. Pod tento kód přidejte následující:

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

    Tento kód definuje HTTP trigger, který převádí text na řeč. Extrahuje text k převodu, jazyk a hlas z JSON těla požadavku, vytvoří SSML pro požadavek na řeč a poté zavolá příslušné REST API, přičemž autentizuje pomocí přístupového tokenu. Toto volání REST API vrací zvuk kódovaný jako 16bitový, 48kHz mono WAV soubor, definovaný hodnotou `playback_format`, která je odeslána do volání REST API.

    Zvuk je poté pře-vzorkován pomocí `librosa` z vzorkovací frekvence 48 kHz na vzorkovací frekvenci 44,1 kHz a poté je tento zvuk uložen do binárního bufferu, který je následně vrácen.

1. Spusťte svou funkční aplikaci lokálně nebo ji nasazte do cloudu. Poté ji můžete volat pomocí nástroje jako curl stejným způsobem, jakým jste testovali HTTP trigger `text-to-timer`. Ujistěte se, že předáváte jazyk, hlas a text jako JSON tělo:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Nahraďte `<language>` svým jazykem, například `en-GB` nebo `zh-CN`. Nahraďte `<voice>` hlasem, který chcete použít. Nahraďte `<text>` textem, který chcete převést na řeč. Výstup můžete uložit do souboru a přehrát jej pomocí libovolného přehrávače zvuku, který podporuje WAV soubory.

    Například pro převod "Hello" na řeč pomocí americké angličtiny s hlasem Jenny Neural, při spuštění funkční aplikace lokálně, můžete použít následující příkaz curl:

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

    Tím se uloží zvuk do souboru `hello.wav` v aktuálním adresáři.

> 💁 Tento kód najdete ve složce [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Úkol - získání řeči z Wio Terminalu

1. Otevřete projekt `smart-timer` ve VS Code, pokud již není otevřen.

1. Otevřete hlavičkový soubor `config.h` a přidejte URL pro vaši funkční aplikaci:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Nahraďte `<URL>` URL pro HTTP trigger `text-to-speech` ve vaší funkční aplikaci. Toto bude stejné jako hodnota `TEXT_TO_TIMER_FUNCTION_URL`, kromě názvu funkce `text-to-speech` místo `text-to-timer`.

1. Otevřete hlavičkový soubor `text_to_speech.h` a přidejte následující metodu do sekce `public` třídy `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Do metody `convertTextToSpeech` přidejte následující kód pro vytvoření JSON dokumentu, který bude odeslán do funkční aplikace:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Tento kód zapisuje jazyk, hlas a text do JSON dokumentu a poté jej serializuje do řetězce.

1. Pod tento kód přidejte následující kód pro volání funkční aplikace:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Tento kód vytvoří `HTTPClient` a poté provede POST požadavek pomocí JSON dokumentu na HTTP trigger `text-to-speech`.

1. Pokud volání funguje, surová binární data vrácená z volání funkční aplikace mohou být streamována do souboru na SD kartě. Přidejte následující kód pro provedení tohoto úkolu:

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

    Tento kód zkontroluje odpověď a pokud je 200 (úspěch), binární data jsou streamována do souboru v kořenovém adresáři SD karty s názvem `SPEECH.WAV`.

1. Na konci této metody uzavřete HTTP připojení:

    ```cpp
    httpClient.end();
    ```

1. Text, který má být vysloven, nyní může být převeden na zvuk. V souboru `main.cpp` přidejte následující řádek na konec funkce `say`, aby se text k vyslovení převedl na zvuk:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Úkol - přehrávání zvuku na vašem Wio Terminalu

**Již brzy**

## Nasazení vaší funkční aplikace do cloudu

Důvodem pro spuštění funkční aplikace lokálně je to, že balíček `librosa` pro Python na Linuxu má závislost na knihovně, která není standardně nainstalována, a bude ji třeba nainstalovat, než bude funkční aplikace schopna běžet. Funkční aplikace jsou bezserverové - neexistují žádné servery, které byste mohli spravovat sami, takže není možné tuto knihovnu předem nainstalovat.

Řešením je místo toho nasadit vaši funkční aplikaci pomocí Docker kontejneru. Tento kontejner je nasazen cloudem vždy, když je potřeba spustit novou instanci vaší funkční aplikace (například když poptávka překročí dostupné zdroje, nebo pokud funkční aplikace nebyla nějakou dobu používána a byla ukončena).

Pokyny k nastavení funkční aplikace a nasazení pomocí Dockeru najdete v [dokumentaci k vytvoření funkce na Linuxu pomocí vlastního kontejneru na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Jakmile je aplikace nasazena, můžete přenést svůj kód pro Wio Terminal, aby přistupoval k této funkci:

1. Přidejte certifikát Azure Functions do `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIFWjCCBEKgAwIBAgIQDxSWXyAgaZlP1ceseIlB4jANBgkqhkiG9w0BAQsFADBa\r\n"
        "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\r\n"
        "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\r\n"
        "MDcyMTIzMDAwMFoXDTI0MTAwODA3MDAwMFowTzELMAkGA1UEBhMCVVMxHjAcBgNV\r\n"
        "BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEgMB4GA1UEAxMXTWljcm9zb2Z0IFJT\r\n"
        "QSBUTFMgQ0EgMDEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCqYnfP\r\n"
        "mmOyBoTzkDb0mfMUUavqlQo7Rgb9EUEf/lsGWMk4bgj8T0RIzTqk970eouKVuL5R\r\n"
        "IMW/snBjXXgMQ8ApzWRJCZbar879BV8rKpHoAW4uGJssnNABf2n17j9TiFy6BWy+\r\n"
        "IhVnFILyLNK+W2M3zK9gheiWa2uACKhuvgCca5Vw/OQYErEdG7LBEzFnMzTmJcli\r\n"
        "W1iCdXby/vI/OxbfqkKD4zJtm45DJvC9Dh+hpzqvLMiK5uo/+aXSJY+SqhoIEpz+\r\n"
        "rErHw+uAlKuHFtEjSeeku8eR3+Z5ND9BSqc6JtLqb0bjOHPm5dSRrgt4nnil75bj\r\n"
        "c9j3lWXpBb9PXP9Sp/nPCK+nTQmZwHGjUnqlO9ebAVQD47ZisFonnDAmjrZNVqEX\r\n"
        "F3p7laEHrFMxttYuD81BdOzxAbL9Rb/8MeFGQjE2Qx65qgVfhH+RsYuuD9dUw/3w\r\n"
        "ZAhq05yO6nk07AM9c+AbNtRoEcdZcLCHfMDcbkXKNs5DJncCqXAN6LhXVERCw/us\r\n"
        "G2MmCMLSIx9/kwt8bwhUmitOXc6fpT7SmFvRAtvxg84wUkg4Y/Gx++0j0z6StSeN\r\n"
        "0EJz150jaHG6WV4HUqaWTb98Tm90IgXAU4AW2GBOlzFPiU5IY9jt+eXC2Q6yC/Zp\r\n"
        "TL1LAcnL3Qa/OgLrHN0wiw1KFGD51WRPQ0Sh7QIDAQABo4IBJTCCASEwHQYDVR0O\r\n"
        "BBYEFLV2DDARzseSQk1Mx1wsyKkM6AtkMB8GA1UdIwQYMBaAFOWdWTCCR1jMrPoI\r\n"
        "VDaGezq1BE3wMA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYI\r\n"
        "KwYBBQUHAwIwEgYDVR0TAQH/BAgwBgEB/wIBADA0BggrBgEFBQcBAQQoMCYwJAYI\r\n"
        "KwYBBQUHMAGGGGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTA6BgNVHR8EMzAxMC+g\r\n"
        "LaArhilodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vT21uaXJvb3QyMDI1LmNybDAq\r\n"
        "BgNVHSAEIzAhMAgGBmeBDAECATAIBgZngQwBAgIwCwYJKwYBBAGCNyoBMA0GCSqG\r\n"
        "SIb3DQEBCwUAA4IBAQCfK76SZ1vae4qt6P+dTQUO7bYNFUHR5hXcA2D59CJWnEj5\r\n"
        "na7aKzyowKvQupW4yMH9fGNxtsh6iJswRqOOfZYC4/giBO/gNsBvwr8uDW7t1nYo\r\n"
        "DYGHPpvnpxCM2mYfQFHq576/TmeYu1RZY29C4w8xYBlkAA8mDJfRhMCmehk7cN5F\r\n"
        "JtyWRj2cZj/hOoI45TYDBChXpOlLZKIYiG1giY16vhCRi6zmPzEwv+tk156N6cGS\r\n"
        "Vm44jTQ/rs1sa0JSYjzUaYngoFdZC4OfxnIkQvUIA4TOFmPzNPEFdjcZsgbeEz4T\r\n"
        "cGHTBPK4R28F44qIMCtHRV55VMX53ev6P3hRddJb\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Změňte všechny zahrnutí `WiFiClient.h` na `<WiFiClientSecure.h>`.

1. Změňte všechna pole `WiFiClient` na `WiFiClientSecure`.

1. V každé třídě, která má pole `WiFiClientSecure`, přidejte konstruktor a nastavte certifikát v tomto konstruktoru:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Prohlášení**:  
Tento dokument byl přeložen pomocí služby pro automatický překlad [Co-op Translator](https://github.com/Azure/co-op-translator). Přestože se snažíme o přesnost, mějte na paměti, že automatické překlady mohou obsahovat chyby nebo nepřesnosti. Původní dokument v jeho původním jazyce by měl být považován za autoritativní zdroj. Pro důležité informace doporučujeme profesionální lidský překlad. Neodpovídáme za žádné nedorozumění nebo nesprávné interpretace vyplývající z použití tohoto překladu.