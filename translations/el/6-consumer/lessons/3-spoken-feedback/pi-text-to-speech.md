<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T20:28:13+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "el"
}
-->
# Μετατροπή κειμένου σε ομιλία - Raspberry Pi

Σε αυτό το μέρος του μαθήματος, θα γράψετε κώδικα για να μετατρέψετε κείμενο σε ομιλία χρησιμοποιώντας την υπηρεσία ομιλίας.

## Μετατροπή κειμένου σε ομιλία χρησιμοποιώντας την υπηρεσία ομιλίας

Το κείμενο μπορεί να σταλεί στην υπηρεσία ομιλίας μέσω του REST API για να παραχθεί ως αρχείο ήχου που μπορεί να αναπαραχθεί στη συσκευή IoT σας. Κατά την αίτηση ομιλίας, πρέπει να καθορίσετε τη φωνή που θα χρησιμοποιηθεί, καθώς η ομιλία μπορεί να παραχθεί με διάφορες φωνές.

Κάθε γλώσσα υποστηρίζει μια σειρά από διαφορετικές φωνές, και μπορείτε να κάνετε μια αίτηση REST στην υπηρεσία ομιλίας για να λάβετε τη λίστα των υποστηριζόμενων φωνών για κάθε γλώσσα.

### Εργασία - λήψη φωνής

1. Ανοίξτε το έργο `smart-timer` στο VS Code.

1. Προσθέστε τον παρακάτω κώδικα πάνω από τη συνάρτηση `say` για να ζητήσετε τη λίστα φωνών για μια γλώσσα:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Αυτός ο κώδικας ορίζει μια συνάρτηση που ονομάζεται `get_voice`, η οποία χρησιμοποιεί την υπηρεσία ομιλίας για να λάβει μια λίστα φωνών. Στη συνέχεια, βρίσκει την πρώτη φωνή που ταιριάζει με τη γλώσσα που χρησιμοποιείται.

    Αυτή η συνάρτηση καλείται για να αποθηκεύσει την πρώτη φωνή, και το όνομα της φωνής εκτυπώνεται στην κονσόλα. Αυτή η φωνή μπορεί να ζητηθεί μία φορά και η τιμή να χρησιμοποιηθεί για κάθε κλήση μετατροπής κειμένου σε ομιλία.

    > 💁 Μπορείτε να βρείτε την πλήρη λίστα των υποστηριζόμενων φωνών από την [τεκμηρίωση υποστήριξης γλωσσών και φωνών στο Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Εάν θέλετε να χρησιμοποιήσετε μια συγκεκριμένη φωνή, μπορείτε να αφαιρέσετε αυτήν τη συνάρτηση και να καθορίσετε τη φωνή με το όνομα της φωνής από αυτήν την τεκμηρίωση. Για παράδειγμα:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Εργασία - μετατροπή κειμένου σε ομιλία

1. Κάτω από αυτό, ορίστε μια σταθερά για τη μορφή ήχου που θα ληφθεί από τις υπηρεσίες ομιλίας. Όταν ζητάτε ήχο, μπορείτε να το κάνετε σε μια σειρά από διαφορετικές μορφές.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Η μορφή που μπορείτε να χρησιμοποιήσετε εξαρτάται από το υλικό σας. Εάν λάβετε σφάλματα `Invalid sample rate` κατά την αναπαραγωγή του ήχου, αλλάξτε αυτό σε άλλη τιμή. Μπορείτε να βρείτε τη λίστα των υποστηριζόμενων τιμών στην [τεκμηρίωση REST API για μετατροπή κειμένου σε ομιλία στο Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Θα χρειαστεί να χρησιμοποιήσετε ήχο μορφής `riff`, και οι τιμές που μπορείτε να δοκιμάσετε είναι `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` και `riff-48khz-16bit-mono-pcm`.

1. Κάτω από αυτό, δηλώστε μια συνάρτηση που ονομάζεται `get_speech`, η οποία θα μετατρέπει το κείμενο σε ομιλία χρησιμοποιώντας το REST API της υπηρεσίας ομιλίας:

    ```python
    def get_speech(text):
    ```

1. Στη συνάρτηση `get_speech`, ορίστε το URL που θα καλέσετε και τις κεφαλίδες που θα περάσετε:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Αυτό ορίζει τις κεφαλίδες για τη χρήση ενός παραγόμενου access token, καθορίζει το περιεχόμενο ως SSML και ορίζει τη μορφή ήχου που χρειάζεται.

1. Κάτω από αυτό, ορίστε το SSML που θα σταλεί στο REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Αυτό το SSML καθορίζει τη γλώσσα και τη φωνή που θα χρησιμοποιηθεί, μαζί με το κείμενο που θα μετατραπεί.

1. Τέλος, προσθέστε κώδικα σε αυτήν τη συνάρτηση για να κάνετε την αίτηση REST και να επιστρέψετε τα δυαδικά δεδομένα ήχου:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Εργασία - αναπαραγωγή του ήχου

1. Κάτω από τη συνάρτηση `get_speech`, ορίστε μια νέα συνάρτηση για την αναπαραγωγή του ήχου που επιστρέφεται από την κλήση του REST API:

    ```python
    def play_speech(speech):
    ```

1. Ο `speech` που περνάει σε αυτήν τη συνάρτηση θα είναι τα δυαδικά δεδομένα ήχου που επιστρέφονται από το REST API. Χρησιμοποιήστε τον παρακάτω κώδικα για να ανοίξετε αυτό ως αρχείο wave και να το περάσετε στο PyAudio για την αναπαραγωγή του ήχου:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Αυτός ο κώδικας χρησιμοποιεί ένα stream του PyAudio, όπως και για την καταγραφή ήχου. Η διαφορά εδώ είναι ότι το stream ορίζεται ως stream εξόδου, και τα δεδομένα διαβάζονται από τα δεδομένα ήχου και προωθούνται στο stream.

    Αντί να καθορίσετε τις λεπτομέρειες του stream, όπως το sample rate, αυτές διαβάζονται από τα δεδομένα ήχου.

1. Αντικαταστήστε το περιεχόμενο της συνάρτησης `say` με το εξής:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Αυτός ο κώδικας μετατρέπει το κείμενο σε ομιλία ως δυαδικά δεδομένα ήχου και αναπαράγει τον ήχο.

1. Εκτελέστε την εφαρμογή και βεβαιωθείτε ότι η εφαρμογή λειτουργιών είναι επίσης ενεργοποιημένη. Ρυθμίστε μερικούς χρονομετρητές και θα ακούσετε μια φωνητική απάντηση που λέει ότι ο χρονομετρητής σας έχει ρυθμιστεί, και στη συνέχεια μια άλλη φωνητική απάντηση όταν ο χρονομετρητής ολοκληρωθεί.

    Εάν λάβετε σφάλματα `Invalid sample rate`, αλλάξτε το `playback_format` όπως περιγράφεται παραπάνω.

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Το πρόγραμμα χρονομέτρησης σας ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.