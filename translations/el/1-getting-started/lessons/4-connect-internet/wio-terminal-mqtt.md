<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-27T21:13:41+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "el"
}
-->
# Ελέγξτε το νυχτερινό σας φως μέσω του Διαδικτύου - Wio Terminal

Η συσκευή IoT πρέπει να προγραμματιστεί ώστε να επικοινωνεί με το *test.mosquitto.org* χρησιμοποιώντας το MQTT για να στέλνει τιμές τηλεμετρίας με την ανάγνωση του αισθητήρα φωτός και να λαμβάνει εντολές για τον έλεγχο του LED.

Σε αυτό το μέρος του μαθήματος, θα συνδέσετε το Wio Terminal σας με έναν MQTT broker.

## Εγκατάσταση των βιβλιοθηκών WiFi και MQTT για Arduino

Για να επικοινωνήσετε με τον MQTT broker, πρέπει να εγκαταστήσετε κάποιες βιβλιοθήκες Arduino για να χρησιμοποιήσετε το τσιπ WiFi στο Wio Terminal και να επικοινωνήσετε με το MQTT. Κατά την ανάπτυξη για συσκευές Arduino, μπορείτε να χρησιμοποιήσετε μια μεγάλη ποικιλία βιβλιοθηκών που περιέχουν κώδικα ανοιχτού κώδικα και υλοποιούν ένα ευρύ φάσμα δυνατοτήτων. Η Seeed δημοσιεύει βιβλιοθήκες για το Wio Terminal που του επιτρέπουν να επικοινωνεί μέσω WiFi. Άλλοι προγραμματιστές έχουν δημοσιεύσει βιβλιοθήκες για την επικοινωνία με MQTT brokers, και θα χρησιμοποιήσετε αυτές τις βιβλιοθήκες με τη συσκευή σας.

Αυτές οι βιβλιοθήκες παρέχονται ως πηγαίος κώδικας που μπορεί να εισαχθεί αυτόματα στο PlatformIO και να μεταγλωττιστεί για τη συσκευή σας. Με αυτόν τον τρόπο, οι βιβλιοθήκες Arduino θα λειτουργούν σε οποιαδήποτε συσκευή υποστηρίζει το πλαίσιο Arduino, υπό την προϋπόθεση ότι η συσκευή διαθέτει οποιοδήποτε συγκεκριμένο υλικό που απαιτείται από τη βιβλιοθήκη. Ορισμένες βιβλιοθήκες, όπως οι βιβλιοθήκες WiFi της Seeed, είναι συγκεκριμένες για ορισμένο υλικό.

Οι βιβλιοθήκες μπορούν να εγκατασταθούν παγκοσμίως και να μεταγλωττιστούν αν χρειαστεί ή σε ένα συγκεκριμένο έργο. Για αυτήν την εργασία, οι βιβλιοθήκες θα εγκατασταθούν στο έργο.

✅ Μπορείτε να μάθετε περισσότερα για τη διαχείριση βιβλιοθηκών και πώς να βρείτε και να εγκαταστήσετε βιβλιοθήκες στην [τεκμηρίωση βιβλιοθηκών του PlatformIO](https://docs.platformio.org/en/latest/librarymanager/index.html).

### Εργασία - εγκατάσταση των βιβλιοθηκών WiFi και MQTT για Arduino

Εγκαταστήστε τις βιβλιοθήκες Arduino.

1. Ανοίξτε το έργο nightlight στο VS Code.

1. Προσθέστε τα παρακάτω στο τέλος του αρχείου `platformio.ini`:

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    Αυτό εισάγει τις βιβλιοθήκες WiFi της Seeed. Η σύνταξη `@ <number>` αναφέρεται σε έναν συγκεκριμένο αριθμό έκδοσης της βιβλιοθήκης.

    > 💁 Μπορείτε να αφαιρέσετε το `@ <number>` για να χρησιμοποιείτε πάντα την πιο πρόσφατη έκδοση των βιβλιοθηκών, αλλά δεν υπάρχουν εγγυήσεις ότι οι νεότερες εκδόσεις θα λειτουργούν με τον παρακάτω κώδικα. Ο κώδικας εδώ έχει δοκιμαστεί με αυτήν την έκδοση των βιβλιοθηκών.

    Αυτό είναι όλο που χρειάζεται να κάνετε για να προσθέσετε τις βιβλιοθήκες. Την επόμενη φορά που το PlatformIO θα κατασκευάσει το έργο, θα κατεβάσει τον πηγαίο κώδικα αυτών των βιβλιοθηκών και θα τον μεταγλωττίσει στο έργο σας.

1. Προσθέστε τα παρακάτω στο `lib_deps`:

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    Αυτό εισάγει το [PubSubClient](https://github.com/knolleary/pubsubclient), έναν MQTT client για Arduino.

## Σύνδεση στο WiFi

Το Wio Terminal μπορεί τώρα να συνδεθεί στο WiFi.

### Εργασία - σύνδεση στο WiFi

Συνδέστε το Wio Terminal στο WiFi.

1. Δημιουργήστε ένα νέο αρχείο στον φάκελο `src` με όνομα `config.h`. Μπορείτε να το κάνετε αυτό επιλέγοντας τον φάκελο `src` ή το αρχείο `main.cpp` μέσα και επιλέγοντας το κουμπί **New file** από τον εξερευνητή. Αυτό το κουμπί εμφανίζεται μόνο όταν ο δείκτης σας είναι πάνω από τον εξερευνητή.

    ![Το κουμπί νέου αρχείου](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.el.png)

1. Προσθέστε τον παρακάτω κώδικα σε αυτό το αρχείο για να ορίσετε σταθερές για τα διαπιστευτήρια του WiFi σας:

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    Αντικαταστήστε το `<SSID>` με το SSID του WiFi σας. Αντικαταστήστε το `<PASSWORD>` με τον κωδικό πρόσβασης του WiFi σας.

1. Ανοίξτε το αρχείο `main.cpp`.

1. Προσθέστε τις παρακάτω οδηγίες `#include` στην κορυφή του αρχείου:

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    Αυτό περιλαμβάνει αρχεία κεφαλίδας για τις βιβλιοθήκες που προσθέσατε νωρίτερα, καθώς και το αρχείο κεφαλίδας config. Αυτά τα αρχεία κεφαλίδας είναι απαραίτητα για να πείτε στο PlatformIO να φέρει τον κώδικα από τις βιβλιοθήκες. Χωρίς να συμπεριλάβετε ρητά αυτά τα αρχεία κεφαλίδας, ορισμένος κώδικας δεν θα μεταγλωττιστεί και θα λάβετε σφάλματα μεταγλώττισης.

1. Προσθέστε τον παρακάτω κώδικα πάνω από τη συνάρτηση `setup`:

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    Αυτός ο κώδικας επαναλαμβάνεται όσο η συσκευή δεν είναι συνδεδεμένη στο WiFi και προσπαθεί να συνδεθεί χρησιμοποιώντας το SSID και τον κωδικό πρόσβασης από το αρχείο κεφαλίδας config.

1. Προσθέστε μια κλήση σε αυτήν τη συνάρτηση στο κάτω μέρος της συνάρτησης `setup`, αφού έχουν διαμορφωθεί οι ακροδέκτες.

    ```cpp
    connectWiFi();
    ```

1. Μεταφορτώστε αυτόν τον κώδικα στη συσκευή σας για να ελέγξετε ότι η σύνδεση WiFi λειτουργεί. Θα πρέπει να δείτε αυτό στην οθόνη σειριακής παρακολούθησης.

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## Σύνδεση στο MQTT

Μόλις το Wio Terminal συνδεθεί στο WiFi, μπορεί να συνδεθεί στον MQTT broker.

### Εργασία - σύνδεση στο MQTT

Συνδεθείτε στον MQTT broker.

1. Προσθέστε τον παρακάτω κώδικα στο κάτω μέρος του αρχείου `config.h` για να ορίσετε τις λεπτομέρειες σύνδεσης για τον MQTT broker:

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    Αντικαταστήστε το `<ID>` με ένα μοναδικό ID που θα χρησιμοποιηθεί ως όνομα του client της συσκευής αυτής και αργότερα για τα θέματα που αυτή η συσκευή δημοσιεύει και εγγράφεται. Ο broker *test.mosquitto.org* είναι δημόσιος και χρησιμοποιείται από πολλούς ανθρώπους, συμπεριλαμβανομένων άλλων μαθητών που εργάζονται σε αυτήν την εργασία. Έχοντας ένα μοναδικό όνομα client MQTT και ονόματα θεμάτων διασφαλίζει ότι ο κώδικάς σας δεν θα συγκρουστεί με κανενός άλλου. Θα χρειαστείτε επίσης αυτό το ID όταν δημιουργείτε τον κώδικα του server αργότερα σε αυτήν την εργασία.

    > 💁 Μπορείτε να χρησιμοποιήσετε έναν ιστότοπο όπως το [GUIDGen](https://www.guidgen.com) για να δημιουργήσετε ένα μοναδικό ID.

    Το `BROKER` είναι το URL του MQTT broker.

    Το `CLIENT_NAME` είναι ένα μοναδικό όνομα για αυτόν τον MQTT client στον broker.

1. Ανοίξτε το αρχείο `main.cpp` και προσθέστε τον παρακάτω κώδικα κάτω από τη συνάρτηση `connectWiFi` και πάνω από τη συνάρτηση `setup`:

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    Αυτός ο κώδικας δημιουργεί έναν WiFi client χρησιμοποιώντας τις βιβλιοθήκες WiFi του Wio Terminal και τον χρησιμοποιεί για να δημιουργήσει έναν MQTT client.

1. Κάτω από αυτόν τον κώδικα, προσθέστε τα εξής:

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    Αυτή η συνάρτηση δοκιμάζει τη σύνδεση με τον MQTT broker και επανασυνδέεται αν δεν είναι συνδεδεμένη. Επαναλαμβάνεται συνεχώς όσο δεν είναι συνδεδεμένη και προσπαθεί να συνδεθεί χρησιμοποιώντας το μοναδικό όνομα client που ορίζεται στο αρχείο κεφαλίδας config.

    Αν η σύνδεση αποτύχει, επαναπροσπαθεί μετά από 5 δευτερόλεπτα.

1. Προσθέστε τον παρακάτω κώδικα κάτω από τη συνάρτηση `reconnectMQTTClient`:

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    Αυτός ο κώδικας ορίζει τον MQTT broker για τον client, καθώς και τη ρύθμιση της επιστροφής κλήσης όταν λαμβάνεται ένα μήνυμα. Στη συνέχεια, προσπαθεί να συνδεθεί στον broker.

1. Καλέστε τη συνάρτηση `createMQTTClient` στη συνάρτηση `setup` αφού συνδεθεί το WiFi.

1. Αντικαταστήστε ολόκληρη τη συνάρτηση `loop` με τα εξής:

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    Αυτός ο κώδικας ξεκινά με την επανασύνδεση στον MQTT broker. Αυτές οι συνδέσεις μπορεί να διακοπούν εύκολα, οπότε αξίζει να ελέγχετε τακτικά και να επανασυνδέεστε αν χρειάζεται. Στη συνέχεια, καλεί τη μέθοδο `loop` στον MQTT client για να επεξεργαστεί τυχόν μηνύματα που έρχονται στο θέμα στο οποίο έχει εγγραφεί. Αυτή η εφαρμογή είναι μονονηματική, οπότε τα μηνύματα δεν μπορούν να ληφθούν σε ένα νήμα παρασκηνίου, επομένως πρέπει να διατεθεί χρόνος στο κύριο νήμα για την επεξεργασία τυχόν μηνυμάτων που περιμένουν στη σύνδεση δικτύου.

    Τέλος, μια καθυστέρηση 2 δευτερολέπτων διασφαλίζει ότι τα επίπεδα φωτός δεν αποστέλλονται πολύ συχνά και μειώνει την κατανάλωση ενέργειας της συσκευής.

1. Μεταφορτώστε τον κώδικα στο Wio Terminal σας και χρησιμοποιήστε τη Σειριακή Παρακολούθηση για να δείτε τη συσκευή να συνδέεται στο WiFi και το MQTT.

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal).

😀 Έχετε συνδέσει με επιτυχία τη συσκευή σας σε έναν MQTT broker.

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.