<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-27T20:36:19+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "el"
}
-->
# Μετατροπή Ομιλίας σε Κείμενο - Raspberry Pi

Σε αυτό το μέρος του μαθήματος, θα γράψετε κώδικα για να μετατρέψετε την ομιλία στον καταγεγραμμένο ήχο σε κείμενο χρησιμοποιώντας την υπηρεσία ομιλίας.

## Αποστολή του ήχου στην υπηρεσία ομιλίας

Ο ήχος μπορεί να σταλεί στην υπηρεσία ομιλίας χρησιμοποιώντας το REST API. Για να χρησιμοποιήσετε την υπηρεσία ομιλίας, πρώτα πρέπει να ζητήσετε ένα access token και στη συνέχεια να χρησιμοποιήσετε αυτό το token για πρόσβαση στο REST API. Αυτά τα access tokens λήγουν μετά από 10 λεπτά, οπότε ο κώδικάς σας θα πρέπει να τα ζητά τακτικά για να διασφαλίσει ότι είναι πάντα ενημερωμένα.

### Εργασία - Απόκτηση ενός access token

1. Ανοίξτε το έργο `smart-timer` στο Raspberry Pi σας.

1. Αφαιρέστε τη συνάρτηση `play_audio`. Δεν χρειάζεται πλέον, καθώς δεν θέλετε ο έξυπνος χρονομετρητής να επαναλαμβάνει αυτά που λέτε.

1. Προσθέστε την παρακάτω εισαγωγή στην κορυφή του αρχείου `app.py`:

    ```python
    import requests
    ```

1. Προσθέστε τον παρακάτω κώδικα πάνω από τον βρόχο `while True` για να δηλώσετε κάποιες ρυθμίσεις για την υπηρεσία ομιλίας:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Αντικαταστήστε το `<key>` με το API key για τον πόρο της υπηρεσίας ομιλίας σας. Αντικαταστήστε το `<location>` με την τοποθεσία που χρησιμοποιήσατε όταν δημιουργήσατε τον πόρο της υπηρεσίας ομιλίας.

    Αντικαταστήστε το `<language>` με το όνομα της γλώσσας που θα μιλάτε, για παράδειγμα `en-GB` για Αγγλικά ή `zn-HK` για Καντονέζικα. Μπορείτε να βρείτε μια λίστα με τις υποστηριζόμενες γλώσσες και τα ονόματά τους στη [τεκμηρίωση υποστήριξης γλωσσών και φωνών στο Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Κάτω από αυτό, προσθέστε την παρακάτω συνάρτηση για να αποκτήσετε ένα access token:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Αυτή καλεί ένα endpoint έκδοσης token, περνώντας το API key ως header. Αυτή η κλήση επιστρέφει ένα access token που μπορεί να χρησιμοποιηθεί για την κλήση των υπηρεσιών ομιλίας.

1. Κάτω από αυτό, δηλώστε μια συνάρτηση για να μετατρέψετε την ομιλία στον καταγεγραμμένο ήχο σε κείμενο χρησιμοποιώντας το REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Μέσα σε αυτή τη συνάρτηση, ρυθμίστε το URL και τα headers του REST API:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Αυτό δημιουργεί ένα URL χρησιμοποιώντας την τοποθεσία του πόρου της υπηρεσίας ομιλίας. Στη συνέχεια, συμπληρώνει τα headers με το access token από τη συνάρτηση `get_access_token`, καθώς και με τον ρυθμό δειγματοληψίας που χρησιμοποιείται για την καταγραφή του ήχου. Τέλος, ορίζει κάποιες παραμέτρους που θα περαστούν με το URL και περιέχουν τη γλώσσα του ήχου.

1. Κάτω από αυτό, προσθέστε τον παρακάτω κώδικα για να καλέσετε το REST API και να επιστρέψετε το κείμενο:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Αυτό καλεί το URL και αποκωδικοποιεί την τιμή JSON που επιστρέφεται στην απόκριση. Η τιμή `RecognitionStatus` στην απόκριση δείχνει αν η κλήση κατάφερε να εξάγει την ομιλία σε κείμενο με επιτυχία, και αν είναι `Success`, τότε το κείμενο επιστρέφεται από τη συνάρτηση, διαφορετικά επιστρέφεται μια κενή συμβολοσειρά.

1. Πάνω από τον βρόχο `while True:`, ορίστε μια συνάρτηση για να επεξεργαστείτε το κείμενο που επιστρέφεται από την υπηρεσία μετατροπής ομιλίας σε κείμενο. Αυτή η συνάρτηση προς το παρόν θα εκτυπώνει το κείμενο στην κονσόλα.

    ```python
    def process_text(text):
        print(text)
    ```

1. Τέλος, αντικαταστήστε την κλήση στη `play_audio` μέσα στον βρόχο `while True` με μια κλήση στη συνάρτηση `convert_speech_to_text`, περνώντας το κείμενο στη συνάρτηση `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Εκτελέστε τον κώδικα. Πατήστε το κουμπί και μιλήστε στο μικρόφωνο. Αφήστε το κουμπί όταν τελειώσετε, και ο ήχος θα μετατραπεί σε κείμενο και θα εκτυπωθεί στην κονσόλα.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Δοκιμάστε διαφορετικούς τύπους προτάσεων, καθώς και προτάσεις όπου οι λέξεις ακούγονται ίδιες αλλά έχουν διαφορετικές σημασίες. Για παράδειγμα, αν μιλάτε Αγγλικά, πείτε "I want to buy two bananas and an apple too" και παρατηρήστε πώς χρησιμοποιεί το σωστό "to", "two" και "too" με βάση το πλαίσιο της λέξης, όχι μόνο τον ήχο της.

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Το πρόγραμμα μετατροπής ομιλίας σε κείμενο ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.