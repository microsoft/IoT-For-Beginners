<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-28T09:00:39+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ro"
}
-->
# Text to speech - Wio Terminal

În această parte a lecției, vei transforma textul în vorbire pentru a oferi feedback vocal.

## Text to speech

SDK-ul serviciilor de vorbire pe care l-ai folosit în lecția anterioară pentru a transforma vorbirea în text poate fi utilizat și pentru a transforma textul în vorbire.

## Obține o listă de voci

Când soliciți vorbire, trebuie să specifici vocea care va fi utilizată, deoarece vorbirea poate fi generată folosind o varietate de voci diferite. Fiecare limbă suportă o gamă de voci, iar lista vocilor disponibile pentru fiecare limbă poate fi obținută din SDK-ul serviciilor de vorbire. Limitările microcontrolerelor intervin aici - apelul pentru a obține lista vocilor suportate de serviciile text-to-speech este un document JSON de peste 77KB, mult prea mare pentru a fi procesat de Wio Terminal. La momentul redactării, lista completă conține 215 voci, fiecare definită printr-un document JSON precum următorul:

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

Acest JSON este pentru vocea **Aria**, care are mai multe stiluri vocale. Tot ce este necesar pentru a transforma textul în vorbire este numele scurt, `en-US-AriaNeural`.

În loc să descarci și să decodezi întreaga listă pe microcontroler, va trebui să scrii un cod serverless suplimentar pentru a prelua lista vocilor pentru limba pe care o folosești și să apelezi acest cod de pe Wio Terminal. Codul tău poate apoi să aleagă o voce potrivită din listă, cum ar fi prima pe care o găsește.

### Sarcină - creează o funcție serverless pentru a obține o listă de voci

1. Deschide proiectul `smart-timer-trigger` în VS Code și deschide terminalul, asigurându-te că mediul virtual este activat. Dacă nu, închide și recreează terminalul.

1. Deschide fișierul `local.settings.json` și adaugă setările pentru cheia API a serviciului de vorbire și locație:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Înlocuiește `<key>` cu cheia API pentru resursa serviciului de vorbire. Înlocuiește `<location>` cu locația pe care ai utilizat-o când ai creat resursa serviciului de vorbire.

1. Adaugă un nou trigger HTTP în această aplicație numit `get-voices` folosind următoarea comandă din terminalul VS Code, în folderul rădăcină al proiectului aplicației de funcții:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Aceasta va crea un trigger HTTP numit `get-voices`.

1. Înlocuiește conținutul fișierului `__init__.py` din folderul `get-voices` cu următorul cod:

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

    Acest cod face o cerere HTTP către endpoint pentru a obține vocile. Lista vocilor este un bloc mare de JSON cu voci pentru toate limbile, astfel încât vocile pentru limba transmisă în corpul cererii sunt filtrate, iar numele scurt este extras și returnat ca o listă JSON. Numele scurt este valoarea necesară pentru a transforma textul în vorbire, astfel încât doar această valoare este returnată.

    > 💁 Poți modifica filtrul după cum este necesar pentru a selecta doar vocile dorite.

    Aceasta reduce dimensiunea datelor de la 77KB (la momentul redactării) la un document JSON mult mai mic. De exemplu, pentru vocile din SUA, acesta are 408 bytes.

1. Rulează aplicația de funcții local. Poți apoi să o apelezi folosind un instrument precum curl, la fel cum ai testat trigger-ul HTTP `text-to-timer`. Asigură-te că transmiți limba ca un corp JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Înlocuiește `<language>` cu limba ta, cum ar fi `en-GB` sau `zh-CN`.

> 💁 Poți găsi acest cod în folderul [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Sarcină - preia vocea de pe Wio Terminal

1. Deschide proiectul `smart-timer` în VS Code, dacă nu este deja deschis.

1. Deschide fișierul header `config.h` și adaugă URL-ul pentru aplicația ta de funcții:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Înlocuiește `<URL>` cu URL-ul pentru trigger-ul HTTP `get-voices` din aplicația ta de funcții. Acesta va fi același cu valoarea pentru `TEXT_TO_TIMER_FUNCTION_URL`, cu excepția faptului că numele funcției va fi `get-voices` în loc de `text-to-timer`.

1. Creează un fișier nou în folderul `src` numit `text_to_speech.h`. Acesta va fi utilizat pentru a defini o clasă care transformă textul în vorbire.

1. Adaugă următoarele directive include în partea de sus a noului fișier `text_to_speech.h`:

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

1. Adaugă următorul cod mai jos pentru a declara clasa `TextToSpeech`, împreună cu o instanță care poate fi utilizată în restul aplicației:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Pentru a apela aplicația de funcții, trebuie să declari un client WiFi. Adaugă următorul cod în secțiunea `private` a clasei:

    ```cpp
    WiFiClient _client;
    ```

1. În secțiunea `private`, adaugă un câmp pentru vocea selectată:

    ```cpp
    String _voice;
    ```

1. În secțiunea `public`, adaugă o funcție `init` care va obține prima voce:

    ```cpp
    void init()
    {
    }
    ```

1. Pentru a obține vocile, un document JSON trebuie trimis către aplicația de funcții cu limba. Adaugă următorul cod în funcția `init` pentru a crea acest document JSON:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Creează un `HTTPClient`, apoi folosește-l pentru a apela aplicația de funcții pentru a obține vocile, postând documentul JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Mai jos, adaugă cod pentru a verifica codul de răspuns, iar dacă este 200 (succes), extrage lista de voci, preluând prima din listă:

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

1. După aceasta, închide conexiunea clientului HTTP:

    ```cpp
    httpClient.end();
    ```

1. Deschide fișierul `main.cpp` și adaugă următoarea directivă include în partea de sus pentru a include acest nou fișier header:

    ```cpp
    #include "text_to_speech.h"
    ```

1. În funcția `setup`, sub apelul către `speechToText.init();`, adaugă următorul cod pentru a inițializa clasa `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Compilează acest cod, încarcă-l pe Wio Terminal și testează-l prin monitorul serial. Asigură-te că aplicația ta de funcții rulează.

    Vei vedea lista vocilor disponibile returnată de aplicația de funcții, împreună cu vocea selectată.

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

## Transformă textul în vorbire

Odată ce ai o voce de utilizat, aceasta poate fi folosită pentru a transforma textul în vorbire. Aceleași limitări de memorie cu vocile se aplică și atunci când transformi textul în vorbire, astfel încât va trebui să scrii vorbirea pe un card SD pentru a fi redată prin ReSpeaker.

> 💁 În lecțiile anterioare ale acestui proiect, ai folosit memoria flash pentru a stoca vorbirea captată de microfon. Această lecție folosește un card SD, deoarece este mai ușor să redai audio de pe acesta folosind bibliotecile audio Seeed.

Există și o altă limitare de luat în considerare: datele audio disponibile de la serviciul de vorbire și formatele pe care Wio Terminal le suportă. Spre deosebire de computerele complete, bibliotecile audio pentru microcontrolere pot fi foarte limitate în formatele audio pe care le suportă. De exemplu, biblioteca Seeed Arduino Audio care poate reda sunet prin ReSpeaker suportă doar audio la o rată de eșantionare de 44.1KHz. Serviciile de vorbire Azure pot furniza audio în mai multe formate, dar niciunul dintre ele nu folosește această rată de eșantionare; ele oferă doar 8KHz, 16KHz, 24KHz și 48KHz. Aceasta înseamnă că audio-ul trebuie re-eșantionat la 44.1KHz, ceva ce ar necesita mai multe resurse decât are Wio Terminal, în special memorie.

Când este nevoie să manipulezi astfel de date, este adesea mai bine să folosești cod serverless, mai ales dacă datele sunt obținute printr-un apel web. Wio Terminal poate apela o funcție serverless, transmițând textul de convertit, iar funcția serverless poate atât să apeleze serviciul de vorbire pentru a transforma textul în vorbire, cât și să re-eșantioneze audio-ul la rata de eșantionare necesară. Apoi poate returna audio-ul în forma de care Wio Terminal are nevoie pentru a fi stocat pe cardul SD și redat prin ReSpeaker.

### Sarcină - creează o funcție serverless pentru a transforma textul în vorbire

1. Deschide proiectul `smart-timer-trigger` în VS Code și deschide terminalul, asigurându-te că mediul virtual este activat. Dacă nu, închide și recreează terminalul.

1. Adaugă un nou trigger HTTP în această aplicație numit `text-to-speech` folosind următoarea comandă din terminalul VS Code, în folderul rădăcină al proiectului aplicației de funcții:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Aceasta va crea un trigger HTTP numit `text-to-speech`.

1. Pachetul Pip [librosa](https://librosa.org) are funcții pentru re-eșantionarea audio-ului, așa că adaugă-l în fișierul `requirements.txt`:

    ```sh
    librosa
    ```

    După ce l-ai adăugat, instalează pachetele Pip folosind următoarea comandă din terminalul VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Dacă folosești Linux, inclusiv Raspberry Pi OS, este posibil să fie nevoie să instalezi `libsndfile` cu următoarea comandă:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Pentru a transforma textul în vorbire, nu poți folosi direct cheia API a serviciului de vorbire; în schimb, trebuie să soliciți un token de acces, folosind cheia API pentru a autentifica cererea de token de acces. Deschide fișierul `__init__.py` din folderul `text-to-speech` și înlocuiește tot codul din el cu următorul:

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

    Acesta definește constante pentru locație și cheia serviciului de vorbire, care vor fi citite din setări. Apoi definește funcția `get_access_token` care va prelua un token de acces pentru serviciul de vorbire.

1. Mai jos de acest cod, adaugă următorul:

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

    Acesta definește trigger-ul HTTP care transformă textul în vorbire. Extrage textul de convertit, limba și vocea din corpul JSON transmis cererii, construiește un SSML pentru a solicita vorbirea, apoi apelează API-ul REST relevant, autentificându-se folosind token-ul de acces. Acest apel API REST returnează audio-ul codificat ca fișier WAV mono de 16 biți, 48KHz, definit de valoarea `playback_format`, care este transmisă apelului API REST.

    Acesta este apoi re-eșantionat de `librosa` de la o rată de eșantionare de 48KHz la o rată de eșantionare de 44.1KHz, apoi acest audio este salvat într-un buffer binar care este apoi returnat.

1. Rulează aplicația de funcții local sau distribuie-o în cloud. Poți apoi să o apelezi folosind un instrument precum curl, la fel cum ai testat trigger-ul HTTP `text-to-timer`. Asigură-te că transmiți limba, vocea și textul ca un corp JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Înlocuiește `<language>` cu limba ta, cum ar fi `en-GB` sau `zh-CN`. Înlocuiește `<voice>` cu vocea pe care vrei să o folosești. Înlocuiește `<text>` cu textul pe care vrei să-l transformi în vorbire. Poți salva rezultatul într-un fișier și să-l redai cu orice player audio care poate reda fișiere WAV.

    De exemplu, pentru a transforma "Hello" în vorbire folosind engleza americană cu vocea Jenny Neural, cu aplicația de funcții rulând local, poți folosi următoarea comandă curl:

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

    Aceasta va salva audio-ul în `hello.wav` în directorul curent.

> 💁 Poți găsi acest cod în folderul [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Sarcină - preia vorbirea de pe Wio Terminal

1. Deschide proiectul `smart-timer` în VS Code, dacă nu este deja deschis.

1. Deschide fișierul header `config.h` și adaugă URL-ul pentru aplicația ta de funcții:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Înlocuiește `<URL>` cu URL-ul pentru trigger-ul HTTP `text-to-speech` din aplicația ta de funcții. Acesta va fi același cu valoarea pentru `TEXT_TO_TIMER_FUNCTION_URL`, cu excepția faptului că numele funcției va fi `text-to-speech` în loc de `text-to-timer`.

1. Deschide fișierul header `text_to_speech.h` și adaugă următoarea metodă în secțiunea `public` a clasei `TextToSpeech`:

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. În metoda `convertTextToSpeech`, adaugă următorul cod pentru a crea JSON-ul care va fi trimis către aplicația de funcții:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Acesta scrie limba, vocea și textul în documentul JSON, apoi îl serializează într-un șir.

1. Mai jos, adaugă următorul cod pentru a apela aplicația de funcții:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Acesta creează un `HTTPClient`, apoi face o cerere POST folosind documentul JSON către trigger-ul HTTP text-to-speech.

1. Dacă apelul funcționează, datele binare brute returnate de apelul aplicației de funcții pot fi transmise către un fișier pe cardul SD. Adaugă următorul cod pentru a face acest lucru:

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

    Acest cod verifică răspunsul, iar dacă este 200 (succes), datele binare sunt transmise către un fișier în rădăcina cardului SD numit `SPEECH.WAV`.

1. La sfârșitul acestei metode, închide conexiunea HTTP:

    ```cpp
    httpClient.end();
    ```

1. Textul care trebuie rostit poate acum fi transformat în audio. În fișierul `main.cpp`, adaugă următoarea linie la sfârșitul funcției `say` pentru a transforma textul de rostit în audio:
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Sarcină - redă audio pe Wio Terminal

**În curând**

## Implementarea aplicației tale de funcții în cloud

Motivul pentru rularea aplicației de funcții local este că pachetul Pip `librosa` pe Linux are o dependență de o bibliotecă care nu este instalată în mod implicit și va trebui instalată înainte ca aplicația de funcții să poată rula. Aplicațiile de funcții sunt serverless - nu există servere pe care să le poți gestiona singur, așa că nu există nicio modalitate de a instala această bibliotecă în prealabil.

Modalitatea de a face acest lucru este, în schimb, să implementezi aplicația ta de funcții folosind un container Docker. Acest container este implementat de cloud ori de câte ori este necesar să se pornească o nouă instanță a aplicației tale de funcții (cum ar fi atunci când cererea depășește resursele disponibile sau dacă aplicația de funcții nu a fost utilizată de ceva timp și este închisă).

Poți găsi instrucțiunile pentru configurarea unei aplicații de funcții și implementarea prin Docker în [documentația pentru crearea unei funcții pe Linux folosind un container personalizat pe Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Odată ce aceasta a fost implementată, poți adapta codul pentru Wio Terminal pentru a accesa această funcție:

1. Adaugă certificatul Azure Functions în `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Schimbă toate includerile de `
<WiFiClient.h>` în `<WiFiClientSecure.h>`.

1. Schimbă toate câmpurile `WiFiClient` în `WiFiClientSecure`.

1. În fiecare clasă care are un câmp `WiFiClientSecure`, adaugă un constructor și setează certificatul în acel constructor:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.