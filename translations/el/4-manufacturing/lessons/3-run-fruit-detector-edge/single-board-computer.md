<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-27T20:10:40+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "el"
}
-->
# Ταξινόμηση εικόνας χρησιμοποιώντας έναν ταξινομητή εικόνων βασισμένο σε IoT Edge - Εικονικό IoT Υλικό και Raspberry Pi

Σε αυτό το μέρος του μαθήματος, θα χρησιμοποιήσετε τον Ταξινομητή Εικόνων που εκτελείται στη συσκευή IoT Edge.

## Χρήση του ταξινομητή IoT Edge

Η συσκευή IoT μπορεί να ανακατευθυνθεί ώστε να χρησιμοποιεί τον ταξινομητή εικόνων IoT Edge. Η διεύθυνση URL για τον Ταξινομητή Εικόνων είναι `http://<IP address or name>/image`, αντικαθιστώντας το `<IP address or name>` με τη διεύθυνση IP ή το όνομα του υπολογιστή που εκτελεί το IoT Edge.

Η βιβλιοθήκη Python για το Custom Vision λειτουργεί μόνο με μοντέλα που φιλοξενούνται στο cloud, όχι με μοντέλα που φιλοξενούνται στο IoT Edge. Αυτό σημαίνει ότι θα χρειαστεί να χρησιμοποιήσετε το REST API για να καλέσετε τον ταξινομητή.

### Εργασία - χρήση του ταξινομητή IoT Edge

1. Ανοίξτε το έργο `fruit-quality-detector` στο VS Code, αν δεν είναι ήδη ανοιχτό. Αν χρησιμοποιείτε εικονική συσκευή IoT, βεβαιωθείτε ότι το εικονικό περιβάλλον είναι ενεργοποιημένο.

1. Ανοίξτε το αρχείο `app.py` και αφαιρέστε τις δηλώσεις εισαγωγής από `azure.cognitiveservices.vision.customvision.prediction` και `msrest.authentication`.

1. Προσθέστε την παρακάτω εισαγωγή στην κορυφή του αρχείου:

    ```python
    import requests
    ```

1. Διαγράψτε όλο τον κώδικα μετά την αποθήκευση της εικόνας σε αρχείο, από `image_file.write(image.read())` μέχρι το τέλος του αρχείου.

1. Προσθέστε τον παρακάτω κώδικα στο τέλος του αρχείου:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Αντικαταστήστε το `<URL>` με τη διεύθυνση URL του ταξινομητή σας.

    Αυτός ο κώδικας κάνει ένα αίτημα REST POST στον ταξινομητή, στέλνοντας την εικόνα ως σώμα του αιτήματος. Τα αποτελέσματα επιστρέφουν ως JSON, και αυτό αποκωδικοποιείται για να εμφανιστούν οι πιθανότητες.

1. Εκτελέστε τον κώδικά σας, με την κάμερά σας να δείχνει κάποιο φρούτο, ή ένα κατάλληλο σύνολο εικόνων, ή φρούτα ορατά από την κάμερα web σας αν χρησιμοποιείτε εικονικό IoT υλικό. Θα δείτε την έξοδο στην κονσόλα:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στους φακέλους [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) ή [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Το πρόγραμμα ταξινόμησης ποιότητας φρούτων σας ήταν επιτυχές!

---

**Αποποίηση Ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτόματες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.