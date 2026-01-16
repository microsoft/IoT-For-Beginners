<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-27T20:43:08+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "el"
}
-->
# Μετάφραση ομιλίας - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα γράψετε κώδικα για τη μετάφραση κειμένου χρησιμοποιώντας την υπηρεσία μεταφραστή.

## Μετατροπή κειμένου σε ομιλία χρησιμοποιώντας την υπηρεσία μεταφραστή

Το REST API της υπηρεσίας ομιλίας δεν υποστηρίζει άμεσες μεταφράσεις. Αντίθετα, μπορείτε να χρησιμοποιήσετε την υπηρεσία Translator για να μεταφράσετε το κείμενο που παράγεται από την υπηρεσία μετατροπής ομιλίας σε κείμενο, καθώς και το κείμενο της απάντησης που εκφωνείται. Αυτή η υπηρεσία διαθέτει REST API που μπορείτε να χρησιμοποιήσετε για τη μετάφραση του κειμένου, αλλά για να διευκολυνθεί η χρήση της, θα ενσωματωθεί σε ένα άλλο HTTP trigger στην εφαρμογή functions σας.

### Εργασία - δημιουργία serverless function για τη μετάφραση κειμένου

1. Ανοίξτε το έργο `smart-timer-trigger` στο VS Code και ανοίξτε το τερματικό, διασφαλίζοντας ότι το εικονικό περιβάλλον είναι ενεργοποιημένο. Αν όχι, τερματίστε και δημιουργήστε ξανά το τερματικό.

1. Ανοίξτε το αρχείο `local.settings.json` και προσθέστε ρυθμίσεις για το κλειδί API και την τοποθεσία της υπηρεσίας μεταφραστή:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    Αντικαταστήστε το `<key>` με το API key για τον πόρο της υπηρεσίας μεταφραστή. Αντικαταστήστε το `<location>` με την τοποθεσία που χρησιμοποιήσατε κατά τη δημιουργία του πόρου της υπηρεσίας μεταφραστή.

1. Προσθέστε ένα νέο HTTP trigger σε αυτήν την εφαρμογή με το όνομα `translate-text` χρησιμοποιώντας την παρακάτω εντολή από το τερματικό του VS Code στον ριζικό φάκελο του έργου functions app:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    Αυτό θα δημιουργήσει ένα HTTP trigger με το όνομα `translate-text`.

1. Αντικαταστήστε το περιεχόμενο του αρχείου `__init__.py` στον φάκελο `translate-text` με το εξής:

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

    Αυτός ο κώδικας εξάγει το κείμενο και τις γλώσσες από το HTTP αίτημα. Στη συνέχεια, κάνει ένα αίτημα στο REST API του μεταφραστή, περνώντας τις γλώσσες ως παραμέτρους για το URL και το κείμενο προς μετάφραση ως σώμα. Τέλος, επιστρέφεται η μετάφραση.

1. Εκτελέστε την εφαρμογή functions τοπικά. Στη συνέχεια, μπορείτε να την καλέσετε χρησιμοποιώντας ένα εργαλείο όπως το curl με τον ίδιο τρόπο που δοκιμάσατε το HTTP trigger `text-to-timer`. Βεβαιωθείτε ότι περνάτε το κείμενο προς μετάφραση και τις γλώσσες ως JSON σώμα:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    Αυτό το παράδειγμα μεταφράζει το *Définir une minuterie de 30 secondes* από τα Γαλλικά στα Αγγλικά (ΗΠΑ). Θα επιστρέψει *Set a 30-second timer*.

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions).

### Εργασία - χρήση της λειτουργίας μεταφραστή για τη μετάφραση κειμένου

1. Ανοίξτε το έργο `smart-timer` στο VS Code αν δεν είναι ήδη ανοιχτό.

1. Ο έξυπνος χρονοδιακόπτης σας θα έχει 2 γλώσσες ορισμένες - τη γλώσσα του διακομιστή που χρησιμοποιήθηκε για την εκπαίδευση του LUIS (η ίδια γλώσσα χρησιμοποιείται επίσης για τη δημιουργία των μηνυμάτων που εκφωνούνται στον χρήστη) και τη γλώσσα που μιλά ο χρήστης. Ενημερώστε τη σταθερά `LANGUAGE` στο αρχείο κεφαλίδας `config.h` ώστε να είναι η γλώσσα που θα μιλά ο χρήστης και προσθέστε μια νέα σταθερά με το όνομα `SERVER_LANGUAGE` για τη γλώσσα που χρησιμοποιήθηκε για την εκπαίδευση του LUIS:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    Αντικαταστήστε το `<user language>` με το όνομα τοπικής ρύθμισης για τη γλώσσα που θα μιλάτε, για παράδειγμα `fr-FR` για τα Γαλλικά ή `zn-HK` για τα Καντονέζικα.

    Αντικαταστήστε το `<server language>` με το όνομα τοπικής ρύθμισης για τη γλώσσα που χρησιμοποιήθηκε για την εκπαίδευση του LUIS.

    Μπορείτε να βρείτε μια λίστα με τις υποστηριζόμενες γλώσσες και τα ονόματα τοπικών ρυθμίσεων στην [τεκμηρίωση υποστήριξης γλωσσών και φωνών στο Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Αν δεν μιλάτε πολλές γλώσσες, μπορείτε να χρησιμοποιήσετε μια υπηρεσία όπως το [Bing Translate](https://www.bing.com/translator) ή το [Google Translate](https://translate.google.com) για να μεταφράσετε από την προτιμώμενη γλώσσα σας σε μια γλώσσα της επιλογής σας. Αυτές οι υπηρεσίες μπορούν στη συνέχεια να αναπαράγουν ήχο του μεταφρασμένου κειμένου.
    >
    > Για παράδειγμα, αν εκπαιδεύσετε το LUIS στα Αγγλικά, αλλά θέλετε να χρησιμοποιήσετε τα Γαλλικά ως γλώσσα χρήστη, μπορείτε να μεταφράσετε προτάσεις όπως "set a 2 minute and 27 second timer" από τα Αγγλικά στα Γαλλικά χρησιμοποιώντας το Bing Translate και στη συνέχεια να χρησιμοποιήσετε το κουμπί **Listen translation** για να εκφωνήσετε τη μετάφραση στο μικρόφωνό σας.
    >
    > ![Το κουμπί listen translation στο Bing translate](../../../../../translated_images/el/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. Προσθέστε το API key και την τοποθεσία του μεταφραστή κάτω από το `SPEECH_LOCATION`:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    Αντικαταστήστε το `<KEY>` με το API key για τον πόρο της υπηρεσίας μεταφραστή. Αντικαταστήστε το `<LOCATION>` με την τοποθεσία που χρησιμοποιήσατε κατά τη δημιουργία του πόρου της υπηρεσίας μεταφραστή.

1. Προσθέστε το URL του trigger του μεταφραστή κάτω από το `VOICE_URL`:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    Αντικαταστήστε το `<URL>` με το URL για το HTTP trigger `translate-text` στην εφαρμογή functions σας. Αυτό θα είναι το ίδιο με την τιμή για το `TEXT_TO_TIMER_FUNCTION_URL`, εκτός από το ότι το όνομα της λειτουργίας θα είναι `translate-text` αντί για `text-to-timer`.

1. Προσθέστε ένα νέο αρχείο στον φάκελο `src` με το όνομα `text_translator.h`.

1. Αυτό το νέο αρχείο κεφαλίδας `text_translator.h` θα περιέχει μια κλάση για τη μετάφραση κειμένου. Προσθέστε τα παρακάτω σε αυτό το αρχείο για να δηλώσετε αυτήν την κλάση:

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

    Αυτό δηλώνει την κλάση `TextTranslator`, μαζί με ένα στιγμιότυπο αυτής της κλάσης. Η κλάση έχει ένα μόνο πεδίο για τον WiFi client.

1. Στην ενότητα `public` αυτής της κλάσης, προσθέστε μια μέθοδο για τη μετάφραση κειμένου:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    Αυτή η μέθοδος λαμβάνει τη γλώσσα από την οποία θα γίνει η μετάφραση και τη γλώσσα στην οποία θα γίνει η μετάφραση. Όταν γίνεται επεξεργασία ομιλίας, η ομιλία θα μεταφράζεται από τη γλώσσα του χρήστη στη γλώσσα του διακομιστή LUIS, και όταν δίνονται απαντήσεις, θα μεταφράζεται από τη γλώσσα του διακομιστή LUIS στη γλώσσα του χρήστη.

1. Σε αυτήν τη μέθοδο, προσθέστε κώδικα για τη δημιουργία ενός JSON σώματος που περιέχει το κείμενο προς μετάφραση και τις γλώσσες:

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

1. Παρακάτω, προσθέστε τον παρακάτω κώδικα για να στείλετε το σώμα στην εφαρμογή functions:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. Στη συνέχεια, προσθέστε κώδικα για να λάβετε την απάντηση:

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

1. Τέλος, προσθέστε κώδικα για να κλείσετε τη σύνδεση και να επιστρέψετε το μεταφρασμένο κείμενο:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### Εργασία - μετάφραση της αναγνωρισμένης ομιλίας και των απαντήσεων

1. Ανοίξτε το αρχείο `main.cpp`.

1. Προσθέστε μια οδηγία include στην κορυφή του αρχείου για το αρχείο κεφαλίδας της κλάσης `TextTranslator`:

    ```cpp
    #include "text_translator.h"
    ```

1. Το κείμενο που λέγεται όταν ρυθμίζεται ή λήγει ένας χρονοδιακόπτης πρέπει να μεταφραστεί. Για να το κάνετε αυτό, προσθέστε το παρακάτω ως την πρώτη γραμμή της συνάρτησης `say`:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Αυτό θα μεταφράσει το κείμενο στη γλώσσα του χρήστη.

1. Στη συνάρτηση `processAudio`, το κείμενο λαμβάνεται από τον καταγεγραμμένο ήχο με την κλήση `String text = speechToText.convertSpeechToText();`. Μετά από αυτήν την κλήση, μεταφράστε το κείμενο:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    Αυτό θα μεταφράσει το κείμενο από τη γλώσσα του χρήστη στη γλώσσα που χρησιμοποιείται στον διακομιστή.

1. Δημιουργήστε αυτόν τον κώδικα, ανεβάστε τον στο Wio Terminal σας και δοκιμάστε τον μέσω του σειριακού παρακολουθητή. Μόλις δείτε το `Ready` στον σειριακό παρακολουθητή, πατήστε το κουμπί C (το αριστερό κουμπί, πιο κοντά στον διακόπτη τροφοδοσίας) και μιλήστε. Βεβαιωθείτε ότι η εφαρμογή functions εκτελείται και ζητήστε έναν χρονοδιακόπτη στη γλώσσα του χρήστη, είτε μιλώντας αυτήν τη γλώσσα είτε χρησιμοποιώντας μια εφαρμογή μετάφρασης.

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

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal).

😀 Το πολυγλωσσικό πρόγραμμα χρονοδιακόπτη σας ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.