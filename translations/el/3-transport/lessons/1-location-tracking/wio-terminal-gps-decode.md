<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-27T20:49:44+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "el"
}
-->
# Αποκωδικοποίηση δεδομένων GPS - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα αποκωδικοποιήσετε τα μηνύματα NMEA που διαβάζονται από τον αισθητήρα GPS μέσω του Wio Terminal και θα εξάγετε το γεωγραφικό πλάτος και μήκος.

## Αποκωδικοποίηση δεδομένων GPS

Αφού διαβαστούν τα ακατέργαστα δεδομένα NMEA από τη σειριακή θύρα, μπορούν να αποκωδικοποιηθούν χρησιμοποιώντας μια βιβλιοθήκη ανοιχτού κώδικα για NMEA.

### Εργασία - αποκωδικοποίηση δεδομένων GPS

Προγραμματίστε τη συσκευή ώστε να αποκωδικοποιεί τα δεδομένα GPS.

1. Ανοίξτε το έργο της εφαρμογής `gps-sensor` αν δεν είναι ήδη ανοιχτό.

1. Προσθέστε μια εξάρτηση βιβλιοθήκης για τη βιβλιοθήκη [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) στο αρχείο `platformio.ini` του έργου. Αυτή η βιβλιοθήκη περιέχει κώδικα για την αποκωδικοποίηση δεδομένων NMEA.

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. Στο `main.cpp`, προσθέστε μια οδηγία include για τη βιβλιοθήκη TinyGPSPlus:

    ```cpp
    #include <TinyGPS++.h>
    ```

1. Κάτω από τη δήλωση του `Serial3`, δηλώστε ένα αντικείμενο TinyGPSPlus για την επεξεργασία των προτάσεων NMEA:

    ```cpp
    TinyGPSPlus gps;
    ```

1. Αλλάξτε το περιεχόμενο της συνάρτησης `printGPSData` στο εξής:

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    Αυτός ο κώδικας διαβάζει τον επόμενο χαρακτήρα από τη σειριακή θύρα UART στον αποκωδικοποιητή NMEA `gps`. Μετά από κάθε χαρακτήρα, ελέγχει αν ο αποκωδικοποιητής έχει διαβάσει μια έγκυρη πρόταση και στη συνέχεια αν έχει διαβάσει μια έγκυρη τοποθεσία. Αν η τοποθεσία είναι έγκυρη, την αποστέλλει στον σειριακό παρακολουθητή, μαζί με τον αριθμό των δορυφόρων που συνέβαλαν σε αυτήν την τοποθέτηση.

1. Δημιουργήστε και ανεβάστε τον κώδικα στο Wio Terminal.

1. Μόλις ολοκληρωθεί η μεταφόρτωση, μπορείτε να παρακολουθήσετε τα δεδομένα τοποθεσίας GPS χρησιμοποιώντας τον σειριακό παρακολουθητή.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal).

😀 Το πρόγραμμα του αισθητήρα GPS με αποκωδικοποίηση δεδομένων ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.