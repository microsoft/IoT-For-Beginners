<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-26T07:20:01+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "pl"
}
-->
# Text na mowę - Wio Terminal

W tej części lekcji przekształcisz tekst na mowę, aby zapewnić mówioną informację zwrotną.

## Tekst na mowę

SDK usług mowy, które używałeś w poprzedniej lekcji do konwersji mowy na tekst, może być również używane do przekształcania tekstu z powrotem na mowę.

## Pobierz listę głosów

Podczas żądania mowy musisz określić głos, który ma być użyty, ponieważ mowę można generować za pomocą różnych głosów. Każdy język obsługuje różne głosy, a listę obsługiwanych głosów dla każdego języka można uzyskać z SDK usług mowy. Ograniczenia mikrokontrolerów odgrywają tutaj istotną rolę - wywołanie w celu uzyskania listy głosów obsługiwanych przez usługi tekst na mowę zwraca dokument JSON o rozmiarze ponad 77 KB, co jest zbyt dużym rozmiarem, aby mógł być przetworzony przez Wio Terminal. W momencie pisania pełna lista zawiera 215 głosów, z których każdy jest zdefiniowany przez dokument JSON, taki jak poniższy:

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

Ten JSON dotyczy głosu **Aria**, który ma wiele stylów głosu. Wszystko, co jest potrzebne do konwersji tekstu na mowę, to krótka nazwa, `en-US-AriaNeural`.

Zamiast pobierać i dekodować całą tę listę na mikrokontrolerze, musisz napisać trochę więcej kodu bezserwerowego, aby pobrać listę głosów dla języka, którego używasz, i wywołać to z Wio Terminal. Twój kod może wtedy wybrać odpowiedni głos z listy, na przykład pierwszy, który znajdzie.

### Zadanie - utwórz funkcję bezserwerową do pobrania listy głosów

1. Otwórz swój projekt `smart-timer-trigger` w VS Code i otwórz terminal, upewniając się, że wirtualne środowisko jest aktywowane. Jeśli nie, zakończ i ponownie utwórz terminal.

1. Otwórz plik `local.settings.json` i dodaj ustawienia dla klucza API usług mowy oraz lokalizacji:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Zamień `<key>` na klucz API dla zasobu usługi mowy. Zamień `<location>` na lokalizację, którą użyłeś podczas tworzenia zasobu usługi mowy.

1. Dodaj nowy wyzwalacz HTTP do tej aplikacji o nazwie `get-voices`, używając następującego polecenia w terminalu VS Code w folderze głównym projektu aplikacji funkcji:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    To utworzy wyzwalacz HTTP o nazwie `get-voices`.

1. Zamień zawartość pliku `__init__.py` w folderze `get-voices` na następującą:

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

    Ten kod wykonuje żądanie HTTP do punktu końcowego w celu uzyskania głosów. Lista głosów to duży blok JSON z głosami dla wszystkich języków, więc głosy dla języka przekazanego w treści żądania są filtrowane, a następnie wyodrębniana jest krótka nazwa i zwracana jako lista JSON. Krótka nazwa to wartość potrzebna do konwersji tekstu na mowę, więc zwracana jest tylko ta wartość.

    > 💁 Możesz zmienić filtr w razie potrzeby, aby wybrać tylko głosy, które chcesz.

    To zmniejsza rozmiar danych z 77 KB (w momencie pisania) do znacznie mniejszego dokumentu JSON. Na przykład dla głosów z USA jest to 408 bajtów.

1. Uruchom lokalnie swoją aplikację funkcji. Następnie możesz ją wywołać za pomocą narzędzia takiego jak curl w taki sam sposób, jak testowałeś wyzwalacz HTTP `text-to-timer`. Upewnij się, że przekazujesz swój język jako treść JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Zamień `<language>` na swój język, na przykład `en-GB` lub `zh-CN`.

> 💁 Ten kod znajdziesz w folderze [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Zadanie - pobierz głos z Wio Terminal

1. Otwórz projekt `smart-timer` w VS Code, jeśli nie jest już otwarty.

1. Otwórz plik nagłówkowy `config.h` i dodaj URL dla swojej aplikacji funkcji:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Zamień `<URL>` na URL dla wyzwalacza HTTP `get-voices` w swojej aplikacji funkcji. Będzie to takie samo jak wartość `TEXT_TO_TIMER_FUNCTION_URL`, z wyjątkiem nazwy funkcji `get-voices` zamiast `text-to-timer`.

1. Utwórz nowy plik w folderze `src` o nazwie `text_to_speech.h`. Będzie on używany do zdefiniowania klasy do konwersji tekstu na mowę.

1. Dodaj następujące dyrektywy include na początku nowego pliku `text_to_speech.h`:

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

1. Dodaj poniższy kod poniżej, aby zadeklarować klasę `TextToSpeech`, wraz z instancją, która może być używana w reszcie aplikacji:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Aby wywołać aplikację funkcji, musisz zadeklarować klienta WiFi. Dodaj następujące do sekcji `private` klasy:

    ```cpp
    WiFiClient _client;
    ```

1. W sekcji `private` dodaj pole dla wybranego głosu:

    ```cpp
    String _voice;
    ```

1. W sekcji `public` dodaj funkcję `init`, która pobierze pierwszy głos:

    ```cpp
    void init()
    {
    }
    ```

1. Aby pobrać głosy, dokument JSON musi zostać wysłany do aplikacji funkcji z językiem. Dodaj następujący kod do funkcji `init`, aby utworzyć ten dokument JSON:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Następnie utwórz `HTTPClient`, a następnie użyj go do wywołania aplikacji funkcji w celu uzyskania głosów, przesyłając dokument JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Poniżej tego dodaj kod, aby sprawdzić kod odpowiedzi, a jeśli jest to 200 (sukces), wyodrębnij listę głosów, pobierając pierwszy z listy:

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

1. Po tym zakończ połączenie klienta HTTP:

    ```cpp
    httpClient.end();
    ```

1. Otwórz plik `main.cpp` i dodaj następującą dyrektywę include na początku, aby uwzględnić ten nowy plik nagłówkowy:

    ```cpp
    #include "text_to_speech.h"
    ```

1. W funkcji `setup`, pod wywołaniem `speechToText.init();`, dodaj następujące, aby zainicjalizować klasę `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Zbuduj ten kod, wgraj go na Wio Terminal i przetestuj przez monitor szeregowy. Upewnij się, że aplikacja funkcji działa.

    Zobaczysz listę dostępnych głosów zwróconą przez aplikację funkcji, wraz z wybranym głosem.

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

## Konwersja tekstu na mowę

Gdy masz głos do użycia, można go użyć do konwersji tekstu na mowę. Te same ograniczenia pamięci dotyczące głosów mają zastosowanie również podczas konwersji mowy na tekst, więc musisz zapisać mowę na karcie SD, aby można ją było odtworzyć przez ReSpeaker.

> 💁 W wcześniejszych lekcjach tego projektu używałeś pamięci flash do przechowywania mowy przechwyconej z mikrofonu. Ta lekcja używa karty SD, ponieważ łatwiej jest odtwarzać z niej dźwięk za pomocą bibliotek audio Seeed.

Istnieje również inne ograniczenie, które należy wziąć pod uwagę: dostępne dane audio z usługi mowy oraz formaty obsługiwane przez Wio Terminal. W przeciwieństwie do pełnych komputerów, biblioteki audio dla mikrokontrolerów mogą być bardzo ograniczone w obsługiwanych formatach audio. Na przykład biblioteka Seeed Arduino Audio, która może odtwarzać dźwięk przez ReSpeaker, obsługuje tylko dźwięk o częstotliwości próbkowania 44,1 kHz. Usługi mowy Azure mogą dostarczać dźwięk w różnych formatach, ale żaden z nich nie używa tej częstotliwości próbkowania, oferując jedynie 8 kHz, 16 kHz, 24 kHz i 48 kHz. Oznacza to, że dźwięk musi zostać przeskalowany do 44,1 kHz, co wymagałoby więcej zasobów niż ma Wio Terminal, szczególnie pamięci.

Kiedy trzeba manipulować danymi w ten sposób, często lepiej jest użyć kodu bezserwerowego, zwłaszcza jeśli dane są pozyskiwane za pomocą wywołania sieciowego. Wio Terminal może wywołać funkcję bezserwerową, przekazując tekst do konwersji, a funkcja bezserwerowa może zarówno wywołać usługę mowy w celu konwersji tekstu na mowę, jak i przeskalować dźwięk do wymaganej częstotliwości próbkowania. Następnie może zwrócić dźwięk w formie, której potrzebuje Wio Terminal, aby zapisać go na karcie SD i odtworzyć przez ReSpeaker.

### Zadanie - utwórz funkcję bezserwerową do konwersji tekstu na mowę

1. Otwórz swój projekt `smart-timer-trigger` w VS Code i otwórz terminal, upewniając się, że wirtualne środowisko jest aktywowane. Jeśli nie, zakończ i ponownie utwórz terminal.

1. Dodaj nowy wyzwalacz HTTP do tej aplikacji o nazwie `text-to-speech`, używając następującego polecenia w terminalu VS Code w folderze głównym projektu aplikacji funkcji:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    To utworzy wyzwalacz HTTP o nazwie `text-to-speech`.

1. Pakiet Pip [librosa](https://librosa.org) ma funkcje do przeskalowania dźwięku, więc dodaj go do pliku `requirements.txt`:

    ```sh
    librosa
    ```

    Po dodaniu tego, zainstaluj pakiety Pip za pomocą następującego polecenia w terminalu VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Jeśli używasz Linuxa, w tym Raspberry Pi OS, może być konieczne zainstalowanie `libsndfile` za pomocą następującego polecenia:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Aby przekształcić tekst na mowę, nie możesz używać bezpośrednio klucza API usługi mowy, zamiast tego musisz zażądać tokenu dostępu, używając klucza API do uwierzytelnienia żądania tokenu dostępu. Otwórz plik `__init__.py` z folderu `text-to-speech` i zamień cały kod w nim na następujący:

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

    To definiuje stałe dla lokalizacji i klucza mowy, które będą odczytywane z ustawień. Następnie definiuje funkcję `get_access_token`, która pobierze token dostępu dla usługi mowy.

1. Poniżej tego kodu dodaj następujące:

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

    To definiuje wyzwalacz HTTP, który konwertuje tekst na mowę. Wyodrębnia tekst do konwersji, język i głos z treści JSON ustawionej w żądaniu, buduje SSML do żądania mowy, a następnie wywołuje odpowiednie REST API, uwierzytelniając za pomocą tokenu dostępu. To wywołanie REST API zwraca dźwięk zakodowany jako 16-bitowy, 48 kHz mono plik WAV, zdefiniowany przez wartość `playback_format`, która jest wysyłana do wywołania REST API.

    Następnie jest on przeskalowany przez `librosa` z częstotliwości próbkowania 48 kHz do częstotliwości próbkowania 44,1 kHz, a następnie ten dźwięk jest zapisywany w buforze binarnym, który jest następnie zwracany.

1. Uruchom lokalnie swoją aplikację funkcji lub wdroż ją w chmurze. Następnie możesz ją wywołać za pomocą narzędzia takiego jak curl w taki sam sposób, jak testowałeś wyzwalacz HTTP `text-to-timer`. Upewnij się, że przekazujesz język, głos i tekst jako treść JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Zamień `<language>` na swój język, na przykład `en-GB` lub `zh-CN`. Zamień `<voice>` na głos, którego chcesz użyć. Zamień `<text>` na tekst, który chcesz przekształcić na mowę. Możesz zapisać wynik w pliku i odtworzyć go za pomocą dowolnego odtwarzacza audio, który obsługuje pliki WAV.

    Na przykład, aby przekształcić "Hello" na mowę w języku angielskim (USA) z głosem Jenny Neural, z aplikacją funkcji działającą lokalnie, możesz użyć następującego polecenia curl:

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

    To zapisze dźwięk w pliku `hello.wav` w bieżącym katalogu.

> 💁 Ten kod znajdziesz w folderze [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Zadanie - pobierz mowę z Wio Terminal

1. Otwórz projekt `smart-timer` w VS Code, jeśli nie jest już otwarty.

1. Otwórz plik nagłówkowy `config.h` i dodaj URL dla swojej aplikacji funkcji:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Zamień `<URL>` na URL dla wyzwalacza HTTP `text-to-speech` w swojej aplikacji funkcji. Będzie to takie samo jak wartość `TEXT_TO_TIMER_FUNCTION_URL`, z wyjątkiem nazwy funkcji `text-to-speech` zamiast `text-to-timer`.

1. Otwórz plik nagłówkowy `text_to_speech.h` i dodaj następującą metodę do sekcji `public` klasy `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Do metody `convertTextToSpeech` dodaj następujący kod, aby utworzyć JSON do wysłania do aplikacji funkcji:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    To zapisuje język, głos i tekst w dokumencie JSON, a następnie serializuje go do ciągu znaków.

1. Poniżej tego dodaj następujący kod, aby wywołać aplikację funkcji:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    To tworzy `HTTPClient`, a następnie wykonuje żądanie POST za pomocą dokumentu JSON do wyzwalacza HTTP `text-to-speech`.

1. Jeśli wywołanie działa, surowe dane binarne zwrócone z wywołania aplikacji funkcji mogą być przesyłane strumieniowo do pliku na karcie SD. Dodaj następujący kod, aby to zrobić:

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

    Ten kod sprawdza odpowiedź, a jeśli jest to 200 (sukces), dane binarne są przesyłane strumieniowo do pliku w katalogu głównym karty SD o nazwie `SPEECH.WAV`.

1. Na końcu tej metody zamknij połączenie HTTP:

    ```cpp
    httpClient.end();
    ```

1. Tekst do wypowiedzenia może teraz zostać przekształcony na dźwięk. W pliku `main.cpp` dodaj następującą linię na końcu funkcji `say`, aby przekształcić tekst do wypowiedzenia na dźwięk:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Zadanie - odtwarzanie dźwięku z Wio Terminal

**Wkrótce dostępne**

## Wdrażanie aplikacji funkcji w chmurze

Powodem uruchamiania aplikacji funkcji lokalnie jest to, że pakiet Pip `librosa` na systemie Linux ma zależność od biblioteki, która nie jest domyślnie zainstalowana i będzie musiała zostać zainstalowana, zanim aplikacja funkcji będzie mogła działać. Aplikacje funkcji są bezserwerowe - nie ma serwerów, którymi można zarządzać samodzielnie, więc nie ma możliwości wcześniejszego zainstalowania tej biblioteki.

Sposobem na rozwiązanie tego problemu jest wdrożenie aplikacji funkcji za pomocą kontenera Docker. Ten kontener jest wdrażany przez chmurę za każdym razem, gdy konieczne jest uruchomienie nowej instancji aplikacji funkcji (na przykład, gdy zapotrzebowanie przekracza dostępne zasoby lub gdy aplikacja funkcji nie była używana przez jakiś czas i została zamknięta).

Instrukcje dotyczące konfiguracji aplikacji funkcji i wdrożenia za pomocą Dockera można znaleźć w [dokumentacji tworzenia funkcji na Linuxie przy użyciu niestandardowego kontenera na Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Po wdrożeniu możesz przenieść kod Wio Terminal, aby uzyskać dostęp do tej funkcji:

1. Dodaj certyfikat Azure Functions do `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Zmień wszystkie odwołania do `<WiFiClient.h>` na `<WiFiClientSecure.h>`.

1. Zmień wszystkie pola `WiFiClient` na `WiFiClientSecure`.

1. W każdej klasie, która ma pole `WiFiClientSecure`, dodaj konstruktor i ustaw certyfikat w tym konstruktorze:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.