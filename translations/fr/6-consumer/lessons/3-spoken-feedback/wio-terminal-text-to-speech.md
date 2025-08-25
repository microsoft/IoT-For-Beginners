<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T00:13:11+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "fr"
}
-->
# Conversion de texte en parole - Wio Terminal

Dans cette partie de la leçon, vous allez convertir du texte en parole pour fournir un retour vocal.

## Texte en parole

Le SDK des services vocaux que vous avez utilisé dans la leçon précédente pour convertir la parole en texte peut également être utilisé pour convertir du texte en parole.

## Obtenir une liste de voix

Lors de la demande de synthèse vocale, vous devez spécifier la voix à utiliser, car la parole peut être générée avec une variété de voix différentes. Chaque langue prend en charge plusieurs voix, et vous pouvez obtenir la liste des voix disponibles pour chaque langue à partir du SDK des services vocaux. Cependant, les limitations des microcontrôleurs entrent en jeu ici : l'appel pour obtenir la liste des voix disponibles génère un document JSON de plus de 77 Ko, bien trop volumineux pour être traité par le Wio Terminal. Au moment de la rédaction, la liste complète contient 215 voix, chacune définie par un document JSON comme celui-ci :

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

Ce JSON correspond à la voix **Aria**, qui propose plusieurs styles de voix. Pour convertir du texte en parole, seule l'information `shortname`, `en-US-AriaNeural`, est nécessaire.

Au lieu de télécharger et de décoder cette liste complète sur votre microcontrôleur, vous devrez écrire un peu de code sans serveur pour récupérer la liste des voix pour la langue que vous utilisez, et appeler ce code depuis votre Wio Terminal. Votre code pourra ensuite choisir une voix appropriée dans la liste, comme la première qu'il trouve.

### Tâche - Créer une fonction sans serveur pour obtenir une liste de voix

1. Ouvrez votre projet `smart-timer-trigger` dans VS Code, et ouvrez le terminal en vous assurant que l'environnement virtuel est activé. Sinon, terminez et recréez le terminal.

1. Ouvrez le fichier `local.settings.json` et ajoutez les paramètres pour la clé API des services vocaux et la localisation :

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Remplacez `<key>` par la clé API de votre ressource de service vocal. Remplacez `<location>` par la localisation utilisée lors de la création de la ressource de service vocal.

1. Ajoutez un nouveau déclencheur HTTP à cette application appelé `get-voices` en utilisant la commande suivante dans le terminal de VS Code, à la racine du projet de l'application de fonctions :

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Cela créera un déclencheur HTTP appelé `get-voices`.

1. Remplacez le contenu du fichier `__init__.py` dans le dossier `get-voices` par ce qui suit :

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

    Ce code effectue une requête HTTP à l'endpoint pour obtenir les voix. La liste des voix est un grand bloc JSON contenant les voix pour toutes les langues. Les voix correspondant à la langue spécifiée dans le corps de la requête sont filtrées, puis le `shortname` est extrait et renvoyé sous forme de liste JSON. Le `shortname` est la valeur nécessaire pour convertir du texte en parole, donc seule cette valeur est renvoyée.

    > 💁 Vous pouvez modifier le filtre si nécessaire pour sélectionner uniquement les voix souhaitées.

    Cela réduit la taille des données de 77 Ko (au moment de la rédaction) à un document JSON beaucoup plus petit. Par exemple, pour les voix américaines, cela représente 408 octets.

1. Exécutez votre application de fonctions localement. Vous pouvez ensuite l'appeler à l'aide d'un outil comme curl, de la même manière que vous avez testé votre déclencheur HTTP `text-to-timer`. Assurez-vous de passer votre langue dans le corps JSON :

    ```json
    {
        "language":"<language>"
    }
    ```

    Remplacez `<language>` par votre langue, comme `en-GB` ou `zh-CN`.

> 💁 Vous pouvez trouver ce code dans le dossier [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tâche - Récupérer la voix depuis votre Wio Terminal

1. Ouvrez le projet `smart-timer` dans VS Code s'il n'est pas déjà ouvert.

1. Ouvrez le fichier d'en-tête `config.h` et ajoutez l'URL de votre application de fonctions :

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Remplacez `<URL>` par l'URL du déclencheur HTTP `get-voices` de votre application de fonctions. Cela sera identique à la valeur de `TEXT_TO_TIMER_FUNCTION_URL`, sauf que le nom de la fonction sera `get-voices` au lieu de `text-to-timer`.

1. Créez un nouveau fichier dans le dossier `src` appelé `text_to_speech.h`. Ce fichier sera utilisé pour définir une classe permettant de convertir du texte en parole.

1. Ajoutez les directives d'inclusion suivantes en haut du nouveau fichier `text_to_speech.h` :

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

1. Ajoutez ensuite le code suivant pour déclarer la classe `TextToSpeech`, ainsi qu'une instance qui pourra être utilisée dans le reste de l'application :

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Pour appeler votre application de fonctions, vous devez déclarer un client WiFi. Ajoutez ce qui suit à la section `private` de la classe :

    ```cpp
    WiFiClient _client;
    ```

1. Dans la section `private`, ajoutez un champ pour la voix sélectionnée :

    ```cpp
    String _voice;
    ```

1. Dans la section `public`, ajoutez une fonction `init` qui récupérera la première voix :

    ```cpp
    void init()
    {
    }
    ```

1. Pour obtenir les voix, un document JSON doit être envoyé à l'application de fonctions avec la langue. Ajoutez le code suivant à la fonction `init` pour créer ce document JSON :

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Ensuite, créez un `HTTPClient`, puis utilisez-le pour appeler l'application de fonctions afin d'obtenir les voix, en postant le document JSON :

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Ajoutez ensuite du code pour vérifier le code de réponse, et si c'est 200 (succès), extrayez la liste des voix et récupérez la première de la liste :

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

1. Après cela, terminez la connexion du client HTTP :

    ```cpp
    httpClient.end();
    ```

1. Ouvrez le fichier `main.cpp` et ajoutez la directive d'inclusion suivante en haut pour inclure ce nouveau fichier d'en-tête :

    ```cpp
    #include "text_to_speech.h"
    ```

1. Dans la fonction `setup`, sous l'appel à `speechToText.init();`, ajoutez ce qui suit pour initialiser la classe `TextToSpeech` :

    ```cpp
    textToSpeech.init();
    ```

1. Compilez ce code, téléversez-le sur votre Wio Terminal et testez-le via le moniteur série. Assurez-vous que votre application de fonctions est en cours d'exécution.

    Vous verrez la liste des voix disponibles renvoyée par l'application de fonctions, ainsi que la voix sélectionnée.

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

## Convertir du texte en parole

Une fois que vous avez une voix à utiliser, elle peut être utilisée pour convertir du texte en parole. Les mêmes limitations de mémoire pour les voix s'appliquent également lors de la conversion de texte en parole, donc vous devrez écrire le fichier audio sur une carte SD pour qu'il puisse être lu via le ReSpeaker.

> 💁 Dans les leçons précédentes de ce projet, vous avez utilisé la mémoire flash pour stocker la parole capturée par le microphone. Cette leçon utilise une carte SD car il est plus facile de lire de l'audio à partir de celle-ci en utilisant les bibliothèques audio de Seeed.

Il existe également une autre limitation à prendre en compte : les données audio disponibles à partir du service vocal et les formats pris en charge par le Wio Terminal. Contrairement aux ordinateurs complets, les bibliothèques audio pour microcontrôleurs peuvent être très limitées en termes de formats audio pris en charge. Par exemple, la bibliothèque Seeed Arduino Audio qui permet de lire du son via le ReSpeaker ne prend en charge que l'audio avec un taux d'échantillonnage de 44,1 kHz. Les services vocaux Azure peuvent fournir de l'audio dans plusieurs formats, mais aucun d'entre eux n'utilise ce taux d'échantillonnage. Ils fournissent uniquement 8 kHz, 16 kHz, 24 kHz et 48 kHz. Cela signifie que l'audio doit être ré-échantillonné à 44,1 kHz, ce qui nécessiterait plus de ressources que celles disponibles sur le Wio Terminal, en particulier en termes de mémoire.

Lorsque vous devez manipuler des données de cette manière, il est souvent préférable d'utiliser du code sans serveur, surtout si les données sont obtenues via un appel web. Le Wio Terminal peut appeler une fonction sans serveur, en passant le texte à convertir, et la fonction sans serveur peut à la fois appeler le service vocal pour convertir le texte en parole, ainsi que ré-échantillonner l'audio au taux d'échantillonnage requis. Elle peut ensuite renvoyer l'audio dans un format que le Wio Terminal peut stocker sur la carte SD et lire via le ReSpeaker.

### Tâche - Créer une fonction sans serveur pour convertir du texte en parole

1. Ouvrez votre projet `smart-timer-trigger` dans VS Code, et ouvrez le terminal en vous assurant que l'environnement virtuel est activé. Sinon, terminez et recréez le terminal.

1. Ajoutez un nouveau déclencheur HTTP à cette application appelé `text-to-speech` en utilisant la commande suivante dans le terminal de VS Code, à la racine du projet de l'application de fonctions :

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Cela créera un déclencheur HTTP appelé `text-to-speech`.

1. Le package Pip [librosa](https://librosa.org) contient des fonctions pour ré-échantillonner l'audio, ajoutez-le donc au fichier `requirements.txt` :

    ```sh
    librosa
    ```

    Une fois ajouté, installez les packages Pip en utilisant la commande suivante dans le terminal de VS Code :

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Si vous utilisez Linux, y compris Raspberry Pi OS, vous devrez peut-être installer `libsndfile` avec la commande suivante :
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Pour convertir du texte en parole, vous ne pouvez pas utiliser directement la clé API des services vocaux. Vous devez demander un jeton d'accès, en utilisant la clé API pour authentifier la demande de jeton d'accès. Ouvrez le fichier `__init__.py` du dossier `text-to-speech` et remplacez tout le code par ce qui suit :

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

    Cela définit des constantes pour la localisation et la clé des services vocaux, qui seront lues à partir des paramètres. Ensuite, la fonction `get_access_token` est définie pour récupérer un jeton d'accès pour le service vocal.

1. Ajoutez ensuite le code suivant :

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

    Cela définit le déclencheur HTTP qui convertit le texte en parole. Il extrait le texte à convertir, la langue et la voix du corps JSON envoyé avec la requête, construit un SSML pour demander la synthèse vocale, puis appelle l'API REST correspondante en s'authentifiant avec le jeton d'accès. Cet appel API REST renvoie l'audio encodé en fichier WAV mono 16 bits, 48 kHz, défini par la valeur de `playback_format`, qui est envoyée à l'appel API REST.

    Cet audio est ensuite ré-échantillonné par `librosa` d'un taux d'échantillonnage de 48 kHz à un taux d'échantillonnage de 44,1 kHz, puis cet audio est enregistré dans un tampon binaire qui est ensuite renvoyé.

1. Exécutez votre application de fonctions localement ou déployez-la dans le cloud. Vous pouvez ensuite l'appeler à l'aide d'un outil comme curl, de la même manière que vous avez testé votre déclencheur HTTP `text-to-timer`. Assurez-vous de passer la langue, la voix et le texte dans le corps JSON :

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Remplacez `<language>` par votre langue, comme `en-GB` ou `zh-CN`. Remplacez `<voice>` par la voix que vous souhaitez utiliser. Remplacez `<text>` par le texte que vous souhaitez convertir en parole. Vous pouvez enregistrer la sortie dans un fichier et la lire avec n'importe quel lecteur audio capable de lire des fichiers WAV.

    Par exemple, pour convertir "Hello" en parole en utilisant l'anglais américain avec la voix Jenny Neural, avec l'application de fonctions exécutée localement, vous pouvez utiliser la commande curl suivante :

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

    Cela enregistrera l'audio dans `hello.wav` dans le répertoire actuel.

> 💁 Vous pouvez trouver ce code dans le dossier [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Tâche - Récupérer la parole depuis votre Wio Terminal

1. Ouvrez le projet `smart-timer` dans VS Code s'il n'est pas déjà ouvert.

1. Ouvrez le fichier d'en-tête `config.h` et ajoutez l'URL de votre application de fonctions :

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Remplacez `<URL>` par l'URL du déclencheur HTTP `text-to-speech` de votre application de fonctions. Cela sera identique à la valeur de `TEXT_TO_TIMER_FUNCTION_URL`, sauf que le nom de la fonction sera `text-to-speech` au lieu de `text-to-timer`.

1. Ouvrez le fichier d'en-tête `text_to_speech.h` et ajoutez la méthode suivante à la section `public` de la classe `TextToSpeech` :

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. Dans la méthode `convertTextToSpeech`, ajoutez le code suivant pour créer le JSON à envoyer à l'application de fonctions :

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    Cela écrit la langue, la voix et le texte dans le document JSON, puis le sérialise en une chaîne.

1. Ajoutez ensuite le code suivant pour appeler l'application de fonctions :

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    Cela crée un `HTTPClient`, puis effectue une requête POST en utilisant le document JSON vers le déclencheur HTTP `text-to-speech`.

1. Si l'appel réussit, les données binaires brutes renvoyées par l'appel de l'application de fonctions peuvent être diffusées dans un fichier sur la carte SD. Ajoutez le code suivant pour le faire :

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

    Ce code vérifie la réponse, et si c'est 200 (succès), les données binaires sont diffusées dans un fichier à la racine de la carte SD appelé `SPEECH.WAV`.

1. À la fin de cette méthode, fermez la connexion HTTP :

    ```cpp
    httpClient.end();
    ```

1. Le texte à prononcer peut maintenant être converti en audio. Dans le fichier `main.cpp`, ajoutez la ligne suivante à la fin de la fonction `say` pour convertir le texte à dire en audio :
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Tâche - lire de l'audio depuis votre Wio Terminal

**Bientôt disponible**

## Déployer votre application de fonctions dans le cloud

La raison pour laquelle on exécute l'application de fonctions localement est que le package Pip `librosa` sur Linux a une dépendance à une bibliothèque qui n'est pas installée par défaut et devra être installée avant que l'application de fonctions puisse fonctionner. Les applications de fonctions sont sans serveur - il n'y a pas de serveurs que vous pouvez gérer vous-même, donc aucun moyen d'installer cette bibliothèque à l'avance.

La solution consiste à déployer votre application de fonctions en utilisant un conteneur Docker. Ce conteneur est déployé par le cloud chaque fois qu'il doit lancer une nouvelle instance de votre application de fonctions (par exemple, lorsque la demande dépasse les ressources disponibles, ou si l'application de fonctions n'a pas été utilisée depuis un moment et a été arrêtée).

Vous pouvez trouver les instructions pour configurer une application de fonctions et la déployer via Docker dans la [documentation sur la création d'une fonction sur Linux en utilisant une image personnalisée sur Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Une fois que cela a été déployé, vous pouvez adapter votre code Wio Terminal pour accéder à cette fonction :

1. Ajoutez le certificat Azure Functions à `config.h` :

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

1. Remplacez toutes les inclusions de `<WiFiClient.h>` par `<WiFiClientSecure.h>`.

1. Remplacez tous les champs `WiFiClient` par `WiFiClientSecure`.

1. Dans chaque classe qui contient un champ `WiFiClientSecure`, ajoutez un constructeur et définissez le certificat dans ce constructeur :

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.