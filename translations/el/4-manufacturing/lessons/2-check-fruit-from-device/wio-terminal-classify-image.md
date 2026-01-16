<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "32a1f23e7834fbe7715da8c4ebb450b9",
  "translation_date": "2025-08-27T20:16:55+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-classify-image.md",
  "language_code": "el"
}
-->
# Ταξινόμηση μιας εικόνας - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα στείλετε την εικόνα που καταγράφηκε από την κάμερα στην υπηρεσία Custom Vision για να την ταξινομήσετε.

## Ταξινόμηση μιας εικόνας

Η υπηρεσία Custom Vision διαθέτει ένα REST API που μπορείτε να καλέσετε από το Wio Terminal για να ταξινομήσετε εικόνες. Αυτό το REST API είναι προσβάσιμο μέσω μιας σύνδεσης HTTPS - μιας ασφαλούς σύνδεσης HTTP.

Όταν αλληλεπιδράτε με τελικά σημεία HTTPS, ο κώδικας του πελάτη πρέπει να ζητήσει το πιστοποιητικό δημόσιου κλειδιού από τον διακομιστή που προσεγγίζεται και να το χρησιμοποιήσει για να κρυπτογραφήσει την κυκλοφορία που στέλνει. Ο περιηγητής σας το κάνει αυτό αυτόματα, αλλά οι μικροελεγκτές όχι. Θα χρειαστεί να ζητήσετε αυτό το πιστοποιητικό χειροκίνητα και να το χρησιμοποιήσετε για να δημιουργήσετε μια ασφαλή σύνδεση με το REST API. Αυτά τα πιστοποιητικά δεν αλλάζουν, οπότε μόλις αποκτήσετε ένα πιστοποιητικό, μπορεί να ενσωματωθεί στον κώδικά σας.

Αυτά τα πιστοποιητικά περιέχουν δημόσια κλειδιά και δεν χρειάζεται να διατηρούνται ασφαλή. Μπορείτε να τα χρησιμοποιήσετε στον πηγαίο κώδικά σας και να τα μοιραστείτε δημόσια σε μέρη όπως το GitHub.

### Εργασία - Ρύθμιση ενός SSL client

1. Ανοίξτε το έργο της εφαρμογής `fruit-quality-detector` αν δεν είναι ήδη ανοιχτό.

1. Ανοίξτε το αρχείο κεφαλίδας `config.h` και προσθέστε το εξής:

    ```cpp
    const char *CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQAueRcfuAIek/4tmDg0xQwDANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwNjCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBALVGARl56bx3KBUSGuPc4H5uoNFkFH4e7pvTCxRi4j/+z+Xb\r\n"
        "wjEz+5CipDOqjx9/jWjskL5dk7PaQkzItidsAAnDCW1leZBOIi68Lff1bjTeZgMY\r\n"
        "iwdRd3Y39b/lcGpiuP2d23W95YHkMMT8IlWosYIX0f4kYb62rphyfnAjYb/4Od99\r\n"
        "ThnhlAxGtfvSbXcBVIKCYfZgqRvV+5lReUnd1aNjRYVzPOoifgSx2fRyy1+pO1Uz\r\n"
        "aMMNnIOE71bVYW0A1hr19w7kOb0KkJXoALTDDj1ukUEDqQuBfBxReL5mXiu1O7WG\r\n"
        "0vltg0VZ/SZzctBsdBlx1BkmWYBW261KZgBivrql5ELTKKd8qgtHcLQA5fl6JB0Q\r\n"
        "gs5XDaWehN86Gps5JW8ArjGtjcWAIP+X8CQaWfaCnuRm6Bk/03PQWhgdi84qwA0s\r\n"
        "sRfFJwHUPTNSnE8EiGVk2frt0u8PG1pwSQsFuNJfcYIHEv1vOzP7uEOuDydsmCjh\r\n"
        "lxuoK2n5/2aVR3BMTu+p4+gl8alXoBycyLmj3J/PUgqD8SL5fTCUegGsdia/Sa60\r\n"
        "N2oV7vQ17wjMN+LXa2rjj/b4ZlZgXVojDmAjDwIRdDUujQu0RVsJqFLMzSIHpp2C\r\n"
        "Zp7mIoLrySay2YYBu7SiNwL95X6He2kS8eefBBHjzwW/9FxGqry57i71c2cDAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQU1cFnOsKjnfR3UltZEjgp5lVou6UwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQB2oWc93fB8esci/8esixj++N22meiGDjgF\r\n"
        "+rA2LUK5IOQOgcUSTGKSqF9lYfAxPjrqPjDCUPHCURv+26ad5P/BYtXtbmtxJWu+\r\n"
        "cS5BhMDPPeG3oPZwXRHBJFAkY4O4AF7RIAAUW6EzDflUoDHKv83zOiPfYGcpHc9s\r\n"
        "kxAInCedk7QSgXvMARjjOqdakor21DTmNIUotxo8kHv5hwRlGhBJwps6fEVi1Bt0\r\n"
        "trpM/3wYxlr473WSPUFZPgP1j519kLpWOJ8z09wxay+Br29irPcBYv0GMXlHqThy\r\n"
        "8y4m/HyTQeI2IMvMrQnwqPpY+rLIXyviI2vLoI+4xKE4Rn38ZZ8m\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

    Αυτό είναι το *Microsoft Azure DigiCert Global Root G2 certificate* - ένα από τα πιστοποιητικά που χρησιμοποιούνται από πολλές υπηρεσίες Azure παγκοσμίως.

    > 💁 Για να δείτε ότι αυτό είναι το πιστοποιητικό που πρέπει να χρησιμοποιήσετε, εκτελέστε την παρακάτω εντολή σε macOS ή Linux. Αν χρησιμοποιείτε Windows, μπορείτε να εκτελέσετε αυτή την εντολή χρησιμοποιώντας το [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/windows/wsl/?WT.mc_id=academic-17441-jabenn):
    >
    > ```sh
    > openssl s_client -showcerts -verify 5 -connect api.cognitive.microsoft.com:443
    > ```
    >
    > Η έξοδος θα εμφανίσει το πιστοποιητικό DigiCert Global Root G2.

1. Ανοίξτε το `main.cpp` και προσθέστε την παρακάτω οδηγία include:

    ```cpp
    #include <WiFiClientSecure.h>
    ```

1. Κάτω από τις οδηγίες include, δηλώστε μια παρουσία του `WifiClientSecure`:

    ```cpp
    WiFiClientSecure client;
    ```

    Αυτή η κλάση περιέχει κώδικα για επικοινωνία με τελικά σημεία ιστού μέσω HTTPS.

1. Στη μέθοδο `connectWiFi`, ρυθμίστε το WiFiClientSecure να χρησιμοποιεί το πιστοποιητικό DigiCert Global Root G2:

    ```cpp
    client.setCACert(CERTIFICATE);
    ```

### Εργασία - Ταξινόμηση μιας εικόνας

1. Προσθέστε την παρακάτω γραμμή στη λίστα `lib_deps` στο αρχείο `platformio.ini`:

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    Αυτό εισάγει το [ArduinoJson](https://arduinojson.org), μια βιβλιοθήκη JSON για Arduino, που θα χρησιμοποιηθεί για την αποκωδικοποίηση της απόκρισης JSON από το REST API.

1. Στο `config.h`, προσθέστε σταθερές για το URL πρόβλεψης και το Key από την υπηρεσία Custom Vision:

    ```cpp
    const char *PREDICTION_URL = "<PREDICTION_URL>";
    const char *PREDICTION_KEY = "<PREDICTION_KEY>";
    ```

    Αντικαταστήστε το `<PREDICTION_URL>` με το URL πρόβλεψης από το Custom Vision. Αντικαταστήστε το `<PREDICTION_KEY>` με το κλειδί πρόβλεψης.

1. Στο `main.cpp`, προσθέστε μια οδηγία include για τη βιβλιοθήκη ArduinoJson:

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. Προσθέστε την παρακάτω συνάρτηση στο `main.cpp`, πάνω από τη συνάρτηση `buttonPressed`.

    ```cpp
    void classifyImage(byte *buffer, uint32_t length)
    {
        HTTPClient httpClient;
        httpClient.begin(client, PREDICTION_URL);
        httpClient.addHeader("Content-Type", "application/octet-stream");
        httpClient.addHeader("Prediction-Key", PREDICTION_KEY);
    
        int httpResponseCode = httpClient.POST(buffer, length);
    
        if (httpResponseCode == 200)
        {
            String result = httpClient.getString();
    
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, result.c_str());
    
            JsonObject obj = doc.as<JsonObject>();
            JsonArray predictions = obj["predictions"].as<JsonArray>();
    
            for(JsonVariant prediction : predictions) 
            {
                String tag = prediction["tagName"].as<String>();
                float probability = prediction["probability"].as<float>();
    
                char buff[32];
                sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
                Serial.println(buff);
            }
        }
    
        httpClient.end();
    }
    ```

    Αυτός ο κώδικας ξεκινά δηλώνοντας έναν `HTTPClient` - μια κλάση που περιέχει μεθόδους για αλληλεπίδραση με REST APIs. Στη συνέχεια, συνδέει τον client με το URL πρόβλεψης χρησιμοποιώντας την παρουσία `WiFiClientSecure` που ρυθμίστηκε με το δημόσιο κλειδί του Azure.

    Μόλις συνδεθεί, στέλνει headers - πληροφορίες για το επερχόμενο αίτημα που θα γίνει στο REST API. Το header `Content-Type` υποδεικνύει ότι η κλήση API θα στείλει ακατέργαστα δυαδικά δεδομένα, ενώ το header `Prediction-Key` περνά το κλειδί πρόβλεψης του Custom Vision.

    Στη συνέχεια, γίνεται ένα αίτημα POST στον HTTP client, ανεβάζοντας έναν πίνακα byte. Αυτός θα περιέχει την εικόνα JPEG που καταγράφηκε από την κάμερα όταν καλείται αυτή η συνάρτηση.

    > 💁 Τα αιτήματα POST προορίζονται για αποστολή δεδομένων και λήψη απόκρισης. Υπάρχουν και άλλοι τύποι αιτημάτων, όπως τα αιτήματα GET, που ανακτούν δεδομένα. Τα αιτήματα GET χρησιμοποιούνται από τον περιηγητή σας για τη φόρτωση ιστοσελίδων.

    Το αίτημα POST επιστρέφει έναν κωδικό κατάστασης απόκρισης. Αυτοί είναι καλά καθορισμένες τιμές, με το 200 να σημαίνει **OK** - το αίτημα POST ήταν επιτυχές.

    > 💁 Μπορείτε να δείτε όλους τους κωδικούς κατάστασης απόκρισης στη [λίστα κωδικών κατάστασης HTTP στη Wikipedia](https://wikipedia.org/wiki/List_of_HTTP_status_codes)

    Αν επιστραφεί 200, το αποτέλεσμα διαβάζεται από τον HTTP client. Αυτή είναι μια απόκριση κειμένου από το REST API με τα αποτελέσματα της πρόβλεψης ως έγγραφο JSON. Το JSON έχει την εξής μορφή:

    ```jSON
    {
        "id":"45d614d3-7d6f-47e9-8fa2-04f237366a16",
        "project":"135607e5-efac-4855-8afb-c93af3380531",
        "iteration":"04f1c1fa-11ec-4e59-bb23-4c7aca353665",
        "created":"2021-06-10T17:58:58.959Z",
        "predictions":[
            {
                "probability":0.5582016,
                "tagId":"05a432ea-9718-4098-b14f-5f0688149d64",
                "tagName":"ripe"
            },
            {
                "probability":0.44179836,
                "tagId":"bb091037-16e5-418e-a9ea-31c6a2920f17",
                "tagName":"unripe"
            }
        ]
    }
    ```

    Το σημαντικό μέρος εδώ είναι ο πίνακας `predictions`. Αυτός περιέχει τις προβλέψεις, με μία καταχώρηση για κάθε ετικέτα που περιέχει το όνομα της ετικέτας και την πιθανότητα. Οι πιθανότητες που επιστρέφονται είναι δεκαδικοί αριθμοί από 0-1, με το 0 να σημαίνει 0% πιθανότητα αντιστοίχισης της ετικέτας και το 1 να σημαίνει 100% πιθανότητα.

    > 💁 Οι ταξινομητές εικόνων επιστρέφουν τα ποσοστά για όλες τις ετικέτες που έχουν χρησιμοποιηθεί. Κάθε ετικέτα θα έχει μια πιθανότητα ότι η εικόνα αντιστοιχεί σε αυτή την ετικέτα.

    Αυτό το JSON αποκωδικοποιείται και οι πιθανότητες για κάθε ετικέτα αποστέλλονται στον σειριακό παρακολουθητή.

1. Στη συνάρτηση `buttonPressed`, είτε αντικαταστήστε τον κώδικα που αποθηκεύει στην κάρτα SD με μια κλήση στη `classifyImage`, είτε προσθέστε την μετά την εγγραφή της εικόνας, αλλά **πριν** διαγραφεί ο buffer:

    ```cpp
    classifyImage(buffer, length);
    ```

    > 💁 Αν αντικαταστήσετε τον κώδικα που αποθηκεύει στην κάρτα SD, μπορείτε να καθαρίσετε τον κώδικά σας αφαιρώντας τις συναρτήσεις `setupSDCard` και `saveToSDCard`.

1. Μεταφορτώστε και εκτελέστε τον κώδικά σας. Στρέψτε την κάμερα σε κάποιο φρούτο και πατήστε το κουμπί C. Θα δείτε την έξοδο στον σειριακό παρακολουθητή:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 8200
    ripe:   56.84%
    unripe: 43.16%
    ```

    Θα μπορείτε να δείτε την εικόνα που τραβήχτηκε και αυτές τις τιμές στην καρτέλα **Predictions** στο Custom Vision.

    ![Μια μπανάνα στο Custom Vision προβλέπεται ώριμη με 56.8% και άγουρη με 43.1%](../../../../../translated_images/el/custom-vision-banana-prediction.30cdff4e1d72db5d9a0be0193790a47c2b387da034e12dc1314dd57ca2131b59.png)

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-classify/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/wio-terminal).

😀 Το πρόγραμμα ταξινόμησης ποιότητας φρούτων σας ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν σφάλματα ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.