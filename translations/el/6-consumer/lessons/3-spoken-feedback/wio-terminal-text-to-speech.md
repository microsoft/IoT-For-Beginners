<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-27T20:26:31+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "el"
}
-->
# Μετατροπή κειμένου σε ομιλία - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα μετατρέψετε κείμενο σε ομιλία για να παρέχετε ακουστική ανατροφοδότηση.

## Μετατροπή κειμένου σε ομιλία

Το SDK υπηρεσιών ομιλίας που χρησιμοποιήσατε στο προηγούμενο μάθημα για τη μετατροπή ομιλίας σε κείμενο μπορεί να χρησιμοποιηθεί για τη μετατροπή κειμένου πίσω σε ομιλία.

## Λήψη λίστας φωνών

Όταν ζητάτε ομιλία, πρέπει να καθορίσετε τη φωνή που θα χρησιμοποιηθεί, καθώς η ομιλία μπορεί να παραχθεί χρησιμοποιώντας μια ποικιλία διαφορετικών φωνών. Κάθε γλώσσα υποστηρίζει μια σειρά από διαφορετικές φωνές, και μπορείτε να λάβετε τη λίστα των υποστηριζόμενων φωνών για κάθε γλώσσα από το SDK υπηρεσιών ομιλίας. Εδώ έρχονται οι περιορισμοί των μικροελεγκτών - η κλήση για τη λήψη της λίστας φωνών που υποστηρίζονται από τις υπηρεσίες μετατροπής κειμένου σε ομιλία είναι ένα έγγραφο JSON μεγέθους άνω των 77KB, πολύ μεγάλο για να επεξεργαστεί από το Wio Terminal. Τη στιγμή της συγγραφής, η πλήρης λίστα περιέχει 215 φωνές, καθεμία από τις οποίες ορίζεται από ένα έγγραφο JSON όπως το παρακάτω:

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

Αυτό το JSON αφορά τη φωνή **Aria**, η οποία διαθέτει πολλαπλά στυλ φωνής. Το μόνο που χρειάζεται για τη μετατροπή κειμένου σε ομιλία είναι το σύντομο όνομα, `en-US-AriaNeural`.

Αντί να κατεβάσετε και να αποκωδικοποιήσετε ολόκληρη αυτή τη λίστα στον μικροελεγκτή σας, θα χρειαστεί να γράψετε λίγο περισσότερη serverless κώδικα για να ανακτήσετε τη λίστα φωνών για τη γλώσσα που χρησιμοποιείτε και να καλέσετε αυτόν τον κώδικα από το Wio Terminal σας. Ο κώδικάς σας μπορεί στη συνέχεια να επιλέξει μια κατάλληλη φωνή από τη λίστα, όπως η πρώτη που βρίσκει.

### Εργασία - Δημιουργία serverless λειτουργίας για λήψη λίστας φωνών

1. Ανοίξτε το έργο σας `smart-timer-trigger` στο VS Code και ανοίξτε το τερματικό, διασφαλίζοντας ότι το εικονικό περιβάλλον είναι ενεργοποιημένο. Αν όχι, τερματίστε και δημιουργήστε ξανά το τερματικό.

1. Ανοίξτε το αρχείο `local.settings.json` και προσθέστε ρυθμίσεις για το κλειδί API ομιλίας και την τοποθεσία:

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    Αντικαταστήστε το `<key>` με το κλειδί API για τον πόρο της υπηρεσίας ομιλίας σας. Αντικαταστήστε το `<location>` με την τοποθεσία που χρησιμοποιήσατε κατά τη δημιουργία του πόρου της υπηρεσίας ομιλίας.

1. Προσθέστε μια νέα HTTP trigger σε αυτήν την εφαρμογή που ονομάζεται `get-voices` χρησιμοποιώντας την παρακάτω εντολή από το τερματικό του VS Code στον ριζικό φάκελο του έργου της εφαρμογής λειτουργιών:

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    Αυτό θα δημιουργήσει ένα HTTP trigger που ονομάζεται `get-voices`.

1. Αντικαταστήστε το περιεχόμενο του αρχείου `__init__.py` στον φάκελο `get-voices` με το παρακάτω:

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

    Αυτός ο κώδικας κάνει μια HTTP αίτηση στο endpoint για να λάβει τις φωνές. Αυτή η λίστα φωνών είναι ένα μεγάλο μπλοκ JSON με φωνές για όλες τις γλώσσες, οπότε οι φωνές για τη γλώσσα που περνά στο σώμα της αίτησης φιλτράρονται, και στη συνέχεια εξάγεται και επιστρέφεται το σύντομο όνομα ως λίστα JSON. Το σύντομο όνομα είναι η τιμή που χρειάζεται για τη μετατροπή κειμένου σε ομιλία, οπότε μόνο αυτή η τιμή επιστρέφεται.

    > 💁 Μπορείτε να αλλάξετε το φίλτρο όπως απαιτείται για να επιλέξετε μόνο τις φωνές που θέλετε.

    Αυτό μειώνει το μέγεθος των δεδομένων από 77KB (τη στιγμή της συγγραφής) σε ένα πολύ μικρότερο έγγραφο JSON. Για παράδειγμα, για φωνές των ΗΠΑ αυτό είναι 408 bytes.

1. Εκτελέστε την εφαρμογή λειτουργιών σας τοπικά. Στη συνέχεια, μπορείτε να την καλέσετε χρησιμοποιώντας ένα εργαλείο όπως το curl με τον ίδιο τρόπο που δοκιμάσατε το HTTP trigger `text-to-timer`. Βεβαιωθείτε ότι περνάτε τη γλώσσα ως σώμα JSON:

    ```json
    {
        "language":"<language>"
    }
    ```

    Αντικαταστήστε το `<language>` με τη γλώσσα σας, όπως `en-GB` ή `zh-CN`.

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Εργασία - Ανάκτηση της φωνής από το Wio Terminal σας

1. Ανοίξτε το έργο `smart-timer` στο VS Code αν δεν είναι ήδη ανοιχτό.

1. Ανοίξτε το αρχείο κεφαλίδας `config.h` και προσθέστε το URL για την εφαρμογή λειτουργιών σας:

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    Αντικαταστήστε το `<URL>` με το URL για το HTTP trigger `get-voices` στην εφαρμογή λειτουργιών σας. Αυτό θα είναι το ίδιο με την τιμή για το `TEXT_TO_TIMER_FUNCTION_URL`, εκτός από το ότι το όνομα της λειτουργίας θα είναι `get-voices` αντί για `text-to-timer`.

1. Δημιουργήστε ένα νέο αρχείο στον φάκελο `src` που ονομάζεται `text_to_speech.h`. Αυτό θα χρησιμοποιηθεί για να ορίσετε μια κλάση για τη μετατροπή από κείμενο σε ομιλία.

1. Προσθέστε τις παρακάτω οδηγίες include στην κορυφή του νέου αρχείου `text_to_speech.h`:

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

1. Προσθέστε τον παρακάτω κώδικα για να δηλώσετε την κλάση `TextToSpeech`, μαζί με ένα στιγμιότυπο που μπορεί να χρησιμοποιηθεί στο υπόλοιπο της εφαρμογής:

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. Για να καλέσετε την εφαρμογή λειτουργιών σας, πρέπει να δηλώσετε έναν WiFi client. Προσθέστε τα παρακάτω στην ενότητα `private` της κλάσης:

    ```cpp
    WiFiClient _client;
    ```

1. Στην ενότητα `private`, προσθέστε ένα πεδίο για την επιλεγμένη φωνή:

    ```cpp
    String _voice;
    ```

1. Στην ενότητα `public`, προσθέστε μια συνάρτηση `init` που θα λάβει την πρώτη φωνή:

    ```cpp
    void init()
    {
    }
    ```

1. Για να λάβετε τις φωνές, ένα έγγραφο JSON πρέπει να σταλεί στην εφαρμογή λειτουργιών με τη γλώσσα. Προσθέστε τον παρακάτω κώδικα στη συνάρτηση `init` για να δημιουργήσετε αυτό το έγγραφο JSON:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. Στη συνέχεια, δημιουργήστε έναν `HTTPClient` και χρησιμοποιήστε τον για να καλέσετε την εφαρμογή λειτουργιών για να λάβετε τις φωνές, δημοσιεύοντας το έγγραφο JSON:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Παρακάτω, προσθέστε κώδικα για να ελέγξετε τον κωδικό απόκρισης, και αν είναι 200 (επιτυχία), τότε εξάγετε τη λίστα φωνών, ανακτώντας την πρώτη από τη λίστα:

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

1. Μετά από αυτό, τερματίστε τη σύνδεση του HTTP client:

    ```cpp
    httpClient.end();
    ```

1. Ανοίξτε το αρχείο `main.cpp` και προσθέστε την παρακάτω οδηγία include στην κορυφή για να συμπεριλάβετε αυτό το νέο αρχείο κεφαλίδας:

    ```cpp
    #include "text_to_speech.h"
    ```

1. Στη συνάρτηση `setup`, κάτω από την κλήση `speechToText.init();`, προσθέστε το παρακάτω για να αρχικοποιήσετε την κλάση `TextToSpeech`:

    ```cpp
    textToSpeech.init();
    ```

1. Δημιουργήστε τον κώδικα, ανεβάστε τον στο Wio Terminal σας και δοκιμάστε τον μέσω του σειριακού παρακολουθητή. Βεβαιωθείτε ότι η εφαρμογή λειτουργιών σας εκτελείται.

    Θα δείτε τη λίστα των διαθέσιμων φωνών που επιστρέφονται από την εφαρμογή λειτουργιών, μαζί με την επιλεγμένη φωνή.

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

## Μετατροπή κειμένου σε ομιλία

Μόλις έχετε μια φωνή για χρήση, μπορεί να χρησιμοποιηθεί για τη μετατροπή κειμένου σε ομιλία. Οι ίδιοι περιορισμοί μνήμης με τις φωνές ισχύουν και για τη μετατροπή ομιλίας σε κείμενο, οπότε θα χρειαστεί να γράψετε την ομιλία σε μια κάρτα SD για να αναπαραχθεί μέσω του ReSpeaker.

> 💁 Σε προηγούμενα μαθήματα αυτού του έργου χρησιμοποιήσατε μνήμη flash για να αποθηκεύσετε την ομιλία που καταγράφηκε από το μικρόφωνο. Αυτό το μάθημα χρησιμοποιεί κάρτα SD καθώς είναι ευκολότερο να αναπαραχθεί ήχος από αυτήν χρησιμοποιώντας τις βιβλιοθήκες ήχου Seeed.

Υπάρχει επίσης ένας άλλος περιορισμός που πρέπει να ληφθεί υπόψη, τα διαθέσιμα δεδομένα ήχου από την υπηρεσία ομιλίας και οι μορφές που υποστηρίζει το Wio Terminal. Σε αντίθεση με πλήρεις υπολογιστές, οι βιβλιοθήκες ήχου για μικροελεγκτές μπορεί να είναι πολύ περιορισμένες στις μορφές ήχου που υποστηρίζουν. Για παράδειγμα, η βιβλιοθήκη Seeed Arduino Audio που μπορεί να αναπαράγει ήχο μέσω του ReSpeaker υποστηρίζει μόνο ήχο με ρυθμό δειγματοληψίας 44.1KHz. Οι υπηρεσίες ομιλίας Azure μπορούν να παρέχουν ήχο σε διάφορες μορφές, αλλά καμία από αυτές δεν χρησιμοποιεί αυτόν τον ρυθμό δειγματοληψίας, παρέχουν μόνο 8KHz, 16KHz, 24KHz και 48KHz. Αυτό σημαίνει ότι ο ήχος πρέπει να επαναδειγματοληφθεί σε 44.1KHz, κάτι που θα απαιτούσε περισσότερους πόρους από αυτούς που διαθέτει το Wio Terminal, ειδικά μνήμη.

Όταν χρειάζεται να χειριστείτε δεδομένα όπως αυτά, είναι συχνά καλύτερο να χρησιμοποιείτε serverless κώδικα, ειδικά αν τα δεδομένα προέρχονται μέσω μιας διαδικτυακής κλήσης. Το Wio Terminal μπορεί να καλέσει μια serverless λειτουργία, περνώντας το κείμενο για μετατροπή, και η serverless λειτουργία μπορεί να καλέσει την υπηρεσία ομιλίας για να μετατρέψει το κείμενο σε ομιλία, καθώς και να επαναδειγματοληπτήσει τον ήχο στον απαιτούμενο ρυθμό δειγματοληψίας. Στη συνέχεια, μπορεί να επιστρέψει τον ήχο στη μορφή που χρειάζεται το Wio Terminal για να αποθηκευτεί στην κάρτα SD και να αναπαραχθεί μέσω του ReSpeaker.

### Εργασία - Δημιουργία serverless λειτουργίας για μετατροπή κειμένου σε ομιλία

1. Ανοίξτε το έργο σας `smart-timer-trigger` στο VS Code και ανοίξτε το τερματικό, διασφαλίζοντας ότι το εικονικό περιβάλλον είναι ενεργοποιημένο. Αν όχι, τερματίστε και δημιουργήστε ξανά το τερματικό.

1. Προσθέστε μια νέα HTTP trigger σε αυτήν την εφαρμογή που ονομάζεται `text-to-speech` χρησιμοποιώντας την παρακάτω εντολή από το τερματικό του VS Code στον ριζικό φάκελο του έργου της εφαρμογής λειτουργιών:

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    Αυτό θα δημιουργήσει ένα HTTP trigger που ονομάζεται `text-to-speech`.

1. Το πακέτο Pip [librosa](https://librosa.org) έχει συναρτήσεις για επαναδειγματοληψία ήχου, οπότε προσθέστε το στο αρχείο `requirements.txt`:

    ```sh
    librosa
    ```

    Μόλις προστεθεί, εγκαταστήστε τα πακέτα Pip χρησιμοποιώντας την παρακάτω εντολή από το τερματικό του VS Code:

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Αν χρησιμοποιείτε Linux, συμπεριλαμβανομένου του Raspberry Pi OS, ίσως χρειαστεί να εγκαταστήσετε το `libsndfile` με την παρακάτω εντολή:
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. Για να μετατρέψετε κείμενο σε ομιλία, δεν μπορείτε να χρησιμοποιήσετε απευθείας το κλειδί API ομιλίας, αντίθετα πρέπει να ζητήσετε ένα access token, χρησιμοποιώντας το κλειδί API για να πιστοποιήσετε το αίτημα του access token. Ανοίξτε το αρχείο `__init__.py` από το φάκελο `text-to-speech` και αντικαταστήστε όλο τον κώδικα σε αυτό με το παρακάτω:

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

    Αυτό ορίζει σταθερές για την τοποθεσία και το κλειδί ομιλίας που θα διαβαστούν από τις ρυθμίσεις. Στη συνέχεια, ορίζει τη συνάρτηση `get_access_token` που θα ανακτήσει ένα access token για την υπηρεσία ομιλίας.

1. Παρακάτω από αυτόν τον κώδικα, προσθέστε το παρακάτω:

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

    Αυτό ορίζει το HTTP trigger που μετατρέπει το κείμενο σε ομιλία. Εξάγει το κείμενο για μετατροπή, τη γλώσσα και τη φωνή από το σώμα JSON που ορίζεται στο αίτημα, δημιουργεί κάποιο SSML για να ζητήσει την ομιλία, και στη συνέχεια καλεί το σχετικό REST API πιστοποιώντας χρησιμοποιώντας το access token. Αυτή η κλήση REST API επιστρέφει τον ήχο κωδικοποιημένο ως 16-bit, 48KHz mono WAV αρχείο, όπως ορίζεται από την τιμή του `playback_format`, η οποία αποστέλλεται στην κλήση REST API.

    Στη συνέχεια, αυτός ο ήχος επαναδειγματοληπτείται από το `librosa` από ρυθμό δειγματοληψίας 48KHz σε ρυθμό δειγματοληψίας 44.1KHz, και στη συνέχεια αυτός ο ήχος αποθηκεύεται σε έναν δυαδικό buffer που στη συνέχεια επιστρέφεται.

1. Εκτελέστε την εφαρμογή λειτουργιών σας τοπικά ή αναπτύξτε την στο cloud. Στη συνέχεια, μπορείτε να την καλέσετε χρησιμοποιώντας ένα εργαλείο όπως το curl με τον ίδιο τρόπο που δοκιμάσατε το HTTP trigger `text-to-timer`. Βεβαιωθείτε ότι περνάτε τη γλώσσα, τη φωνή και το κείμενο ως σώμα JSON:

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    Αντικαταστήστε το `<language>` με τη γλώσσα σας, όπως `en-GB` ή `zh-CN`. Αντικαταστήστε το `<voice>` με τη φωνή που θέλετε να χρησιμοποιήσετε. Αντικαταστήστε το `<text>` με το κείμενο που θέλετε να μετατρέψετε σε ομιλία. Μπορείτε να αποθηκεύσετε την έξοδο σε ένα αρχείο και να την αναπαραγάγετε με οποιοδήποτε πρόγραμμα αναπαραγωγής ήχου που μπορεί να αναπαράγει αρχεία WAV.

    Για παράδειγμα, για να μετατρέψετε το "Hello" σε ομιλία χρησιμοποιώντας τα Αγγλικά ΗΠΑ με τη φωνή Jenny Neural, με την εφαρμογή λειτουργιών να εκτελείται τοπικά, μπορείτε να χρησιμοποιήσετε την παρακάτω εντολή curl:

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

    Αυτό θα αποθηκεύσει τον ήχο στο `hello.wav` στον τρέχοντα κατάλογο.

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions).

### Εργασία - Ανάκτηση της ομιλίας από το Wio Terminal σας

1. Ανοίξτε το έργο `smart-timer` στο VS Code αν δεν είναι ήδη ανοιχτό.

1. Ανοίξτε το αρχείο κεφαλίδας `config.h` και προσθέστε το URL για την εφαρμογή λειτουργιών σας:

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    Αντικαταστήστε το `<URL>` με το URL για το HTTP trigger `text-to-speech` στην εφαρμογή λειτουργιών σας. Αυτό θα είναι το ίδιο
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### Εργασία - αναπαραγωγή ήχου από το Wio Terminal σας

**Σύντομα διαθέσιμο**

## Ανάπτυξη της εφαρμογής λειτουργιών σας στο cloud

Ο λόγος για την εκτέλεση της εφαρμογής λειτουργιών τοπικά είναι ότι το πακέτο Pip `librosa` στο Linux έχει μια εξάρτηση από μια βιβλιοθήκη που δεν είναι εγκατεστημένη από προεπιλογή και θα χρειαστεί να εγκατασταθεί πριν η εφαρμογή λειτουργιών μπορέσει να εκτελεστεί. Οι εφαρμογές λειτουργιών είναι χωρίς διακομιστές - δεν υπάρχουν διακομιστές που μπορείτε να διαχειριστείτε μόνοι σας, επομένως δεν υπάρχει τρόπος να εγκαταστήσετε αυτήν τη βιβλιοθήκη εκ των προτέρων.

Ο τρόπος για να το κάνετε αυτό είναι να αναπτύξετε την εφαρμογή λειτουργιών σας χρησιμοποιώντας ένα Docker container. Αυτό το container αναπτύσσεται από το cloud κάθε φορά που χρειάζεται να δημιουργηθεί μια νέα περίπτωση της εφαρμογής λειτουργιών σας (όπως όταν η ζήτηση υπερβαίνει τους διαθέσιμους πόρους ή αν η εφαρμογή λειτουργιών δεν έχει χρησιμοποιηθεί για κάποιο διάστημα και έχει κλείσει).

Μπορείτε να βρείτε τις οδηγίες για τη δημιουργία μιας εφαρμογής λειτουργιών και την ανάπτυξη μέσω Docker στην [τεκμηρίωση για τη δημιουργία λειτουργίας στο Linux χρησιμοποιώντας προσαρμοσμένη εικόνα στο Microsoft Docs](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python).

Αφού αναπτυχθεί, μπορείτε να μεταφέρετε τον κώδικα του Wio Terminal σας για να αποκτήσετε πρόσβαση σε αυτήν τη λειτουργία:

1. Προσθέστε το πιστοποιητικό Azure Functions στο `config.h`:

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Αλλάξτε όλες τις περιλήψεις του `
<WiFiClient.h>` σε `<WiFiClientSecure.h>`.

1. Αλλάξτε όλα τα πεδία `WiFiClient` σε `WiFiClientSecure`.

1. Σε κάθε κλάση που έχει πεδίο `WiFiClientSecure`, προσθέστε έναν κατασκευαστή και ορίστε το πιστοποιητικό σε αυτόν τον κατασκευαστή:

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.