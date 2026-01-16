<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e5896207b304ce1abaf065b8acc0cc79",
  "translation_date": "2025-08-27T20:16:17+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/single-board-computer-classify-image.md",
  "language_code": "el"
}
-->
# Ταξινόμηση εικόνας - Εικονικό IoT Hardware και Raspberry Pi

Σε αυτό το μέρος του μαθήματος, θα στείλετε την εικόνα που καταγράφηκε από την κάμερα στην υπηρεσία Custom Vision για να την ταξινομήσετε.

## Αποστολή εικόνων στο Custom Vision

Η υπηρεσία Custom Vision διαθέτει ένα Python SDK που μπορείτε να χρησιμοποιήσετε για την ταξινόμηση εικόνων.

### Εργασία - Αποστολή εικόνων στο Custom Vision

1. Ανοίξτε τον φάκελο `fruit-quality-detector` στο VS Code. Εάν χρησιμοποιείτε μια εικονική συσκευή IoT, βεβαιωθείτε ότι το εικονικό περιβάλλον λειτουργεί στο τερματικό.

1. Το Python SDK για την αποστολή εικόνων στο Custom Vision είναι διαθέσιμο ως πακέτο Pip. Εγκαταστήστε το με την ακόλουθη εντολή:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Προσθέστε τις ακόλουθες δηλώσεις εισαγωγής στην κορυφή του αρχείου `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Αυτό εισάγει ορισμένα modules από τις βιβλιοθήκες του Custom Vision, ένα για την αυθεντικοποίηση με το prediction key και ένα για την παροχή μιας κλάσης prediction client που μπορεί να καλεί το Custom Vision.

1. Προσθέστε τον ακόλουθο κώδικα στο τέλος του αρχείου:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Αντικαταστήστε το `<prediction_url>` με το URL που αντιγράψατε από το διάλογο *Prediction URL* νωρίτερα σε αυτό το μάθημα. Αντικαταστήστε το `<prediction key>` με το prediction key που αντιγράψατε από τον ίδιο διάλογο.

1. Το prediction URL που παρέχεται από το διάλογο *Prediction URL* έχει σχεδιαστεί για χρήση όταν καλείτε το REST endpoint απευθείας. Το Python SDK χρησιμοποιεί μέρη του URL σε διαφορετικά σημεία. Προσθέστε τον ακόλουθο κώδικα για να διαχωρίσετε αυτό το URL στα μέρη που χρειάζονται:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Αυτό διαχωρίζει το URL, εξάγοντας το endpoint `https://<location>.api.cognitive.microsoft.com`, το project ID και το όνομα της δημοσιευμένης επανάληψης.

1. Δημιουργήστε ένα αντικείμενο predictor για να εκτελέσετε την πρόβλεψη με τον ακόλουθο κώδικα:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    Τα `prediction_credentials` περιλαμβάνουν το prediction key. Αυτά χρησιμοποιούνται για τη δημιουργία ενός αντικειμένου prediction client που δείχνει στο endpoint.

1. Στείλτε την εικόνα στο Custom Vision χρησιμοποιώντας τον ακόλουθο κώδικα:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Αυτό επαναφέρει την εικόνα στην αρχή και στη συνέχεια την στέλνει στον prediction client.

1. Τέλος, εμφανίστε τα αποτελέσματα με τον ακόλουθο κώδικα:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Αυτό θα επαναλάβει όλες τις προβλέψεις που έχουν επιστραφεί και θα τις εμφανίσει στο τερματικό. Οι πιθανότητες που επιστρέφονται είναι δεκαδικοί αριθμοί από 0-1, με το 0 να αντιπροσωπεύει 0% πιθανότητα να ταιριάζει με την ετικέτα και το 1 να αντιπροσωπεύει 100% πιθανότητα.

    > 💁 Οι ταξινομητές εικόνων θα επιστρέψουν τα ποσοστά για όλες τις ετικέτες που έχουν χρησιμοποιηθεί. Κάθε ετικέτα θα έχει μια πιθανότητα ότι η εικόνα ταιριάζει με αυτήν την ετικέτα.

1. Εκτελέστε τον κώδικά σας, με την κάμερά σας να δείχνει σε κάποιο φρούτο, ή σε ένα κατάλληλο σύνολο εικόνων, ή φρούτα ορατά στην webcam σας εάν χρησιμοποιείτε εικονικό IoT hardware. Θα δείτε την έξοδο στην κονσόλα:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Θα μπορείτε να δείτε την εικόνα που τραβήχτηκε και αυτές τις τιμές στην καρτέλα **Predictions** στο Custom Vision.

    ![Μια μπανάνα στο Custom Vision προβλέφθηκε ώριμη με 56.8% και άγουρη με 43.1%](../../../../../translated_images/el/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) ή [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Το πρόγραμμα ταξινόμησης ποιότητας φρούτων σας ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.