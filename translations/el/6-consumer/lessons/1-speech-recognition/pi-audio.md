<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0ac0afcfb40cb5970ef4cb74f01c32e9",
  "translation_date": "2025-08-27T20:33:28+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-audio.md",
  "language_code": "el"
}
-->
# Καταγραφή ήχου - Raspberry Pi

Σε αυτό το μέρος του μαθήματος, θα γράψετε κώδικα για να καταγράψετε ήχο στο Raspberry Pi σας. Η καταγραφή ήχου θα ελέγχεται από ένα κουμπί.

## Υλικό

Το Raspberry Pi χρειάζεται ένα κουμπί για να ελέγχει την καταγραφή ήχου.

Το κουμπί που θα χρησιμοποιήσετε είναι ένα κουμπί Grove. Αυτός είναι ένας ψηφιακός αισθητήρας που ενεργοποιεί ή απενεργοποιεί ένα σήμα. Αυτά τα κουμπιά μπορούν να ρυθμιστούν ώστε να στέλνουν υψηλό σήμα όταν πατηθούν και χαμηλό όταν δεν πατηθούν, ή χαμηλό όταν πατηθούν και υψηλό όταν δεν πατηθούν.

Αν χρησιμοποιείτε το ReSpeaker 2-Mics Pi HAT ως μικρόφωνο, τότε δεν χρειάζεται να συνδέσετε κουμπί, καθώς αυτό το HAT έχει ήδη ένα ενσωματωμένο. Προχωρήστε στην επόμενη ενότητα.

### Σύνδεση του κουμπιού

Το κουμπί μπορεί να συνδεθεί στη βάση Grove.

#### Εργασία - σύνδεση του κουμπιού

![Ένα κουμπί Grove](../../../../../translated_images/el/grove-button.a70cfbb809a8563681003250cf5b06d68cdcc68624f9e2f493d5a534ae2da1e5.png)

1. Εισάγετε το ένα άκρο ενός καλωδίου Grove στην υποδοχή του κουμπιού. Θα μπει μόνο με έναν συγκεκριμένο τρόπο.

1. Με το Raspberry Pi απενεργοποιημένο, συνδέστε το άλλο άκρο του καλωδίου Grove στην ψηφιακή υποδοχή με την ένδειξη **D5** στη βάση Grove που είναι συνδεδεμένη στο Pi. Αυτή η υποδοχή είναι η δεύτερη από τα αριστερά, στη σειρά των υποδοχών δίπλα στα GPIO pins.

![Το κουμπί Grove συνδεδεμένο στην υποδοχή D5](../../../../../translated_images/el/pi-button.c7a1a4f55943341ce1baf1057658e9a205804d4131d258e820c93f951df0abf3.png)

## Καταγραφή ήχου

Μπορείτε να καταγράψετε ήχο από το μικρόφωνο χρησιμοποιώντας κώδικα Python.

### Εργασία - καταγραφή ήχου

1. Ενεργοποιήστε το Pi και περιμένετε να εκκινήσει.

1. Εκκινήστε το VS Code, είτε απευθείας στο Pi είτε συνδεθείτε μέσω της επέκτασης Remote SSH.

1. Το πακέτο PyAudio Pip έχει συναρτήσεις για εγγραφή και αναπαραγωγή ήχου. Αυτό το πακέτο εξαρτάται από κάποιες βιβλιοθήκες ήχου που πρέπει να εγκατασταθούν πρώτα. Εκτελέστε τις παρακάτω εντολές στο τερματικό για να τις εγκαταστήσετε:

    ```sh
    sudo apt update
    sudo apt install libportaudio0 libportaudio2 libportaudiocpp0 portaudio19-dev libasound2-plugins --yes 
    ```

1. Εγκαταστήστε το πακέτο PyAudio Pip.

    ```sh
    pip3 install pyaudio
    ```

1. Δημιουργήστε έναν νέο φάκελο με όνομα `smart-timer` και προσθέστε ένα αρχείο με όνομα `app.py` σε αυτόν τον φάκελο.

1. Προσθέστε τις παρακάτω εισαγωγές στην κορυφή αυτού του αρχείου:

    ```python
    import io
    import pyaudio
    import time
    import wave
    
    from grove.factory import Factory
    ```

    Αυτές εισάγουν το module `pyaudio`, κάποια τυπικά modules της Python για τη διαχείριση αρχείων wave, και το module `grove.factory` για την εισαγωγή ενός `Factory` για τη δημιουργία μιας κλάσης κουμπιού.

1. Παρακάτω, προσθέστε κώδικα για να δημιουργήσετε ένα κουμπί Grove.

    Αν χρησιμοποιείτε το ReSpeaker 2-Mics Pi HAT, χρησιμοποιήστε τον παρακάτω κώδικα:

    ```python
    # The button on the ReSpeaker 2-Mics Pi HAT
    button = Factory.getButton("GPIO-LOW", 17)
    ```

    Αυτό δημιουργεί ένα κουμπί στην υποδοχή **D17**, την υποδοχή στην οποία είναι συνδεδεμένο το κουμπί του ReSpeaker 2-Mics Pi HAT. Αυτό το κουμπί έχει ρυθμιστεί να στέλνει χαμηλό σήμα όταν πατηθεί.

    Αν δεν χρησιμοποιείτε το ReSpeaker 2-Mics Pi HAT και χρησιμοποιείτε ένα κουμπί Grove συνδεδεμένο στη βάση, χρησιμοποιήστε αυτόν τον κώδικα:

    ```python
    button = Factory.getButton("GPIO-HIGH", 5)
    ```

    Αυτό δημιουργεί ένα κουμπί στην υποδοχή **D5**, το οποίο έχει ρυθμιστεί να στέλνει υψηλό σήμα όταν πατηθεί.

1. Παρακάτω, δημιουργήστε μια παρουσία της κλάσης PyAudio για τη διαχείριση του ήχου:

    ```python
    audio = pyaudio.PyAudio()
    ```

1. Δηλώστε τον αριθμό της κάρτας υλικού για το μικρόφωνο και το ηχείο. Αυτός θα είναι ο αριθμός της κάρτας που βρήκατε εκτελώντας `arecord -l` και `aplay -l` νωρίτερα στο μάθημα.

    ```python
    microphone_card_number = <microphone card number>
    speaker_card_number = <speaker card number>
    ```

    Αντικαταστήστε το `<microphone card number>` με τον αριθμό της κάρτας του μικροφώνου σας.

    Αντικαταστήστε το `<speaker card number>` με τον αριθμό της κάρτας του ηχείου σας, τον ίδιο αριθμό που ορίσατε στο αρχείο `alsa.conf`.

1. Παρακάτω, δηλώστε τον ρυθμό δειγματοληψίας που θα χρησιμοποιηθεί για την καταγραφή και την αναπαραγωγή ήχου. Ίσως χρειαστεί να αλλάξετε αυτήν την τιμή ανάλογα με το υλικό που χρησιμοποιείτε.

    ```python
    rate = 48000 #48KHz
    ```

    Αν λάβετε σφάλματα δειγματοληψίας όταν εκτελέσετε τον κώδικα αργότερα, αλλάξτε αυτήν την τιμή σε `44100` ή `16000`. Όσο μεγαλύτερη η τιμή, τόσο καλύτερη η ποιότητα του ήχου.

1. Παρακάτω, δημιουργήστε μια νέα συνάρτηση με όνομα `capture_audio`. Αυτή θα καλείται για να καταγράψει ήχο από το μικρόφωνο:

    ```python
    def capture_audio():
    ```

1. Μέσα σε αυτήν τη συνάρτηση, προσθέστε τα παρακάτω για να καταγράψετε τον ήχο:

    ```python
    stream = audio.open(format = pyaudio.paInt16,
                        rate = rate,
                        channels = 1, 
                        input_device_index = microphone_card_number,
                        input = True,
                        frames_per_buffer = 4096)

    frames = []

    while button.is_pressed():
        frames.append(stream.read(4096))

    stream.stop_stream()
    stream.close()
    ```

    Αυτός ο κώδικας ανοίγει ένα stream εισόδου ήχου χρησιμοποιώντας το αντικείμενο PyAudio. Αυτό το stream θα καταγράφει ήχο από το μικρόφωνο στα 16KHz, καταγράφοντάς τον σε buffers μεγέθους 4096 bytes.

    Ο κώδικας στη συνέχεια επαναλαμβάνεται όσο το κουμπί Grove είναι πατημένο, διαβάζοντας αυτά τα buffers των 4096 bytes σε έναν πίνακα κάθε φορά.

    > 💁 Μπορείτε να διαβάσετε περισσότερα για τις επιλογές που περνιούνται στη μέθοδο `open` στην [τεκμηρίωση του PyAudio](https://people.csail.mit.edu/hubert/pyaudio/docs/).

    Μόλις το κουμπί απελευθερωθεί, το stream σταματά και κλείνει.

1. Προσθέστε τα παρακάτω στο τέλος αυτής της συνάρτησης:

    ```python
    wav_buffer = io.BytesIO()
    with wave.open(wav_buffer, 'wb') as wavefile:
        wavefile.setnchannels(1)
        wavefile.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wavefile.setframerate(rate)
        wavefile.writeframes(b''.join(frames))
        wav_buffer.seek(0)

    return wav_buffer
    ```

    Αυτός ο κώδικας δημιουργεί έναν δυαδικό buffer και γράφει όλο τον καταγεγραμμένο ήχο σε αυτόν ως [αρχείο WAV](https://wikipedia.org/wiki/WAV). Αυτός είναι ένας τυπικός τρόπος για να γράψετε μη συμπιεσμένο ήχο σε ένα αρχείο. Αυτός ο buffer στη συνέχεια επιστρέφεται.

1. Προσθέστε τη συνάρτηση `play_audio` για την αναπαραγωγή του buffer ήχου:

    ```python
    def play_audio(buffer):
        stream = audio.open(format = pyaudio.paInt16,
                            rate = rate,
                            channels = 1,
                            output_device_index = speaker_card_number,
                            output = True)
    
        with wave.open(buffer, 'rb') as wf:
            data = wf.readframes(4096)
    
            while len(data) > 0:
                stream.write(data)
                data = wf.readframes(4096)
    
            stream.close()
    ```

    Αυτή η συνάρτηση ανοίγει ένα άλλο stream ήχου, αυτή τη φορά για έξοδο - για την αναπαραγωγή του ήχου. Χρησιμοποιεί τις ίδιες ρυθμίσεις με το stream εισόδου. Ο buffer στη συνέχεια ανοίγεται ως αρχείο wave και γράφεται στο stream εξόδου σε chunks των 4096 bytes, αναπαράγοντας τον ήχο. Το stream στη συνέχεια κλείνει.

1. Προσθέστε τον παρακάτω κώδικα κάτω από τη συνάρτηση `capture_audio` για να επαναλαμβάνεται μέχρι να πατηθεί το κουμπί. Μόλις πατηθεί το κουμπί, ο ήχος καταγράφεται και στη συνέχεια αναπαράγεται.

    ```python
    while True:
        while not button.is_pressed():
            time.sleep(.1)
        
        buffer = capture_audio()
        play_audio(buffer)
    ```

1. Εκτελέστε τον κώδικα. Πατήστε το κουμπί και μιλήστε στο μικρόφωνο. Απελευθερώστε το κουμπί όταν τελειώσετε και θα ακούσετε την εγγραφή.

    Ίσως λάβετε κάποια σφάλματα ALSA όταν δημιουργηθεί η παρουσία του PyAudio. Αυτό οφείλεται στη διαμόρφωση του Pi για συσκευές ήχου που δεν έχετε. Μπορείτε να αγνοήσετε αυτά τα σφάλματα.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.front
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.rear
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.center_lfe
    ALSA lib pcm.c:2565:(snd_pcm_open_noupdate) Unknown PCM cards.pcm.side
    ```

    Αν λάβετε το παρακάτω σφάλμα:

    ```output
    OSError: [Errno -9997] Invalid sample rate
    ```

    τότε αλλάξτε το `rate` σε `44100` ή `16000`.

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-record/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-record/pi).

😀 Το πρόγραμμα εγγραφής ήχου σας ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν σφάλματα ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.