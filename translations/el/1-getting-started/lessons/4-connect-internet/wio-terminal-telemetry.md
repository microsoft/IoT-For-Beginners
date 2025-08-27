<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-27T21:15:22+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "el"
}
-->
# Ελέγξτε το νυχτερινό σας φως μέσω του Διαδικτύου - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα στείλετε τηλεμετρία με επίπεδα φωτός από το Wio Terminal σας στον MQTT broker.

## Εγκατάσταση των βιβλιοθηκών JSON για Arduino

Ένας δημοφιλής τρόπος για να στέλνετε μηνύματα μέσω MQTT είναι χρησιμοποιώντας JSON. Υπάρχει μια βιβλιοθήκη για Arduino που κάνει την ανάγνωση και τη συγγραφή εγγράφων JSON πιο εύκολη.

### Εργασία

Εγκαταστήστε τη βιβλιοθήκη Arduino JSON.

1. Ανοίξτε το έργο του νυχτερινού φωτός στο VS Code.

1. Προσθέστε την παρακάτω γραμμή στη λίστα `lib_deps` στο αρχείο `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Αυτό εισάγει το [ArduinoJson](https://arduinojson.org), μια βιβλιοθήκη JSON για Arduino.

## Δημοσίευση τηλεμετρίας

Το επόμενο βήμα είναι να δημιουργήσετε ένα έγγραφο JSON με τηλεμετρία και να το στείλετε στον MQTT broker.

### Εργασία - δημοσίευση τηλεμετρίας

Δημοσιεύστε τηλεμετρία στον MQTT broker.

1. Προσθέστε τον παρακάτω κώδικα στο τέλος του αρχείου `config.h` για να ορίσετε το όνομα του θέματος τηλεμετρίας για τον MQTT broker:

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    Το `CLIENT_TELEMETRY_TOPIC` είναι το θέμα στο οποίο η συσκευή θα δημοσιεύει τα επίπεδα φωτός.

1. Ανοίξτε το αρχείο `main.cpp`.

1. Προσθέστε την παρακάτω οδηγία `#include` στην κορυφή του αρχείου:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Προσθέστε τον παρακάτω κώδικα μέσα στη συνάρτηση `loop`, ακριβώς πριν από το `delay`:

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    Αυτός ο κώδικας διαβάζει το επίπεδο φωτός και δημιουργεί ένα έγγραφο JSON χρησιμοποιώντας το ArduinoJson που περιέχει αυτό το επίπεδο. Στη συνέχεια, αυτό μετατρέπεται σε συμβολοσειρά και δημοσιεύεται στο θέμα τηλεμετρίας MQTT από τον MQTT client.

1. Μεταφορτώστε τον κώδικα στο Wio Terminal σας και χρησιμοποιήστε το Serial Monitor για να δείτε τα επίπεδα φωτός που αποστέλλονται στον MQTT broker.

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal).

😀 Έχετε στείλει επιτυχώς τηλεμετρία από τη συσκευή σας.

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν σφάλματα ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.