<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3f92edf2975175577174910caca4a389",
  "translation_date": "2025-08-27T20:39:52+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/wio-terminal-speech-to-text.md",
  "language_code": "el"
}
-->
# Μετατροπή ομιλίας σε κείμενο - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα γράψετε κώδικα για να μετατρέψετε την ομιλία από τον καταγεγραμμένο ήχο σε κείμενο χρησιμοποιώντας την υπηρεσία ομιλίας.

## Αποστολή του ήχου στην υπηρεσία ομιλίας

Ο ήχος μπορεί να σταλεί στην υπηρεσία ομιλίας μέσω του REST API. Για να χρησιμοποιήσετε την υπηρεσία ομιλίας, πρώτα πρέπει να ζητήσετε ένα διακριτικό πρόσβασης (access token) και στη συνέχεια να χρησιμοποιήσετε αυτό το διακριτικό για πρόσβαση στο REST API. Αυτά τα διακριτικά λήγουν μετά από 10 λεπτά, οπότε ο κώδικάς σας θα πρέπει να τα ζητά τακτικά για να διασφαλίσει ότι είναι πάντα ενημερωμένα.

### Εργασία - λήψη διακριτικού πρόσβασης

1. Ανοίξτε το έργο `smart-timer` αν δεν είναι ήδη ανοιχτό.

1. Προσθέστε τις παρακάτω εξαρτήσεις βιβλιοθηκών στο αρχείο `platformio.ini` για πρόσβαση στο WiFi και διαχείριση JSON:

    ```ini
    seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
    seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
    seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    bblanchon/ArduinoJson @ 6.17.3
    ```

1. Προσθέστε τον παρακάτω κώδικα στο αρχείο κεφαλίδας `config.h`:

    ```cpp
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    
    const char *SPEECH_API_KEY = "<API_KEY>";
    const char *SPEECH_LOCATION = "<LOCATION>";
    const char *LANGUAGE = "<LANGUAGE>";

    const char *TOKEN_URL = "https://%s.api.cognitive.microsoft.com/sts/v1.0/issuetoken";
    ```

    Αντικαταστήστε το `<SSID>` και το `<PASSWORD>` με τις σχετικές τιμές για το WiFi σας.

    Αντικαταστήστε το `<API_KEY>` με το κλειδί API για τον πόρο της υπηρεσίας ομιλίας σας. Αντικαταστήστε το `<LOCATION>` με την τοποθεσία που χρησιμοποιήσατε όταν δημιουργήσατε τον πόρο της υπηρεσίας ομιλίας.

    Αντικαταστήστε το `<LANGUAGE>` με το όνομα τοπικής ρύθμισης για τη γλώσσα στην οποία θα μιλήσετε, για παράδειγμα `en-GB` για Αγγλικά ή `zn-HK` για Καντονέζικα. Μπορείτε να βρείτε μια λίστα με τις υποστηριζόμενες γλώσσες και τα ονόματα τοπικών ρυθμίσεων στην [τεκμηρίωση υποστήριξης γλωσσών και φωνών στο Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Η σταθερά `TOKEN_URL` είναι η διεύθυνση URL του εκδότη διακριτικών χωρίς την τοποθεσία. Αυτή θα συνδυαστεί με την τοποθεσία αργότερα για να δημιουργηθεί η πλήρης διεύθυνση URL.

1. Όπως και με τη σύνδεση στο Custom Vision, θα χρειαστεί να χρησιμοποιήσετε μια σύνδεση HTTPS για να συνδεθείτε στην υπηρεσία έκδοσης διακριτικών. Στο τέλος του `config.h`, προσθέστε τον παρακάτω κώδικα:

    ```cpp
    const char *TOKEN_CERTIFICATE =
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

    Αυτό είναι το ίδιο πιστοποιητικό που χρησιμοποιήσατε όταν συνδεθήκατε στο Custom Vision.

1. Προσθέστε μια εντολή include για το αρχείο κεφαλίδας WiFi και το αρχείο κεφαλίδας config στην κορυφή του αρχείου `main.cpp`:

    ```cpp
    #include <rpcWiFi.h>

    #include "config.h"
    ```

1. Προσθέστε κώδικα για σύνδεση στο WiFi στο `main.cpp` πάνω από τη συνάρτηση `setup`:

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

1. Καλέστε αυτή τη συνάρτηση από τη συνάρτηση `setup` αφού έχει δημιουργηθεί η σύνδεση σειριακής επικοινωνίας:

    ```cpp
    connectWiFi();
    ```

1. Δημιουργήστε ένα νέο αρχείο κεφαλίδας στον φάκελο `src` με όνομα `speech_to_text.h`. Στο αρχείο κεφαλίδας, προσθέστε τον παρακάτω κώδικα:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "mic.h"
    
    class SpeechToText
    {
    public:

    private:

    };

    SpeechToText speechToText;
    ```

    Αυτό περιλαμβάνει κάποια απαραίτητα αρχεία κεφαλίδας για μια σύνδεση HTTP, τη διαμόρφωση και το αρχείο κεφαλίδας `mic.h`, και ορίζει μια κλάση με όνομα `SpeechToText`, πριν δηλώσει μια παρουσία αυτής της κλάσης που μπορεί να χρησιμοποιηθεί αργότερα.

1. Προσθέστε τα παρακάτω 2 πεδία στην ενότητα `private` αυτής της κλάσης:

    ```cpp
    WiFiClientSecure _token_client;
    String _access_token;
    ```

    Το `_token_client` είναι ένας WiFi Client που χρησιμοποιεί HTTPS και θα χρησιμοποιηθεί για να λάβει το διακριτικό πρόσβασης. Αυτό το διακριτικό θα αποθηκευτεί στη συνέχεια στο `_access_token`.

1. Προσθέστε την παρακάτω μέθοδο στην ενότητα `private`:

    ```cpp
    String getAccessToken()
    {
        char url[128];
        sprintf(url, TOKEN_URL, SPEECH_LOCATION);
    
        HTTPClient httpClient;
        httpClient.begin(_token_client, url);
    
        httpClient.addHeader("Ocp-Apim-Subscription-Key", SPEECH_API_KEY);
        int httpResultCode = httpClient.POST("{}");
    
        if (httpResultCode != 200)
        {
            Serial.println("Error getting access token, trying again...");
            delay(10000);
            return getAccessToken();
        }
    
        Serial.println("Got access token.");
        String result = httpClient.getString();
    
        httpClient.end();
    
        return result;
    }
    ```

    Αυτός ο κώδικας δημιουργεί τη διεύθυνση URL για το API του εκδότη διακριτικών χρησιμοποιώντας την τοποθεσία του πόρου ομιλίας. Στη συνέχεια, δημιουργεί έναν `HTTPClient` για να κάνει το αίτημα ιστού, ρυθμίζοντάς τον να χρησιμοποιεί τον WiFi client που έχει διαμορφωθεί με το πιστοποιητικό των τελικών σημείων του εκδότη διακριτικών. Ορίζει το κλειδί API ως κεφαλίδα για την κλήση. Στη συνέχεια, κάνει ένα αίτημα POST για να λάβει το πιστοποιητικό, επαναλαμβάνοντας αν λάβει σφάλματα. Τέλος, επιστρέφεται το διακριτικό πρόσβασης.

1. Στην ενότητα `public`, προσθέστε μια μέθοδο για να λάβετε το διακριτικό πρόσβασης. Αυτό θα χρειαστεί σε επόμενα μαθήματα για τη μετατροπή κειμένου σε ομιλία.

    ```cpp
    String AccessToken()
    {
        return _access_token;
    }
    ```

1. Στην ενότητα `public`, προσθέστε μια μέθοδο `init` που ρυθμίζει τον client διακριτικών:

    ```cpp
    void init()
    {
        _token_client.setCACert(TOKEN_CERTIFICATE);
        _access_token = getAccessToken();
    }
    ```

    Αυτό ορίζει το πιστοποιητικό στον WiFi client και στη συνέχεια λαμβάνει το διακριτικό πρόσβασης.

1. Στο `main.cpp`, προσθέστε αυτό το νέο αρχείο κεφαλίδας στις εντολές include:

    ```cpp
    #include "speech_to_text.h"
    ```

1. Αρχικοποιήστε την κλάση `SpeechToText` στο τέλος της συνάρτησης `setup`, μετά την κλήση `mic.init` αλλά πριν γραφτεί το `Ready` στον σειριακό παρακολουθητή:

    ```cpp
    speechToText.init();
    ```

### Εργασία - ανάγνωση ήχου από τη μνήμη flash

1. Σε ένα προηγούμενο μέρος αυτού του μαθήματος, ο ήχος καταγράφηκε στη μνήμη flash. Αυτός ο ήχος θα χρειαστεί να σταλεί στο REST API της Υπηρεσίας Ομιλίας, οπότε πρέπει να διαβαστεί από τη μνήμη flash. Δεν μπορεί να φορτωθεί σε έναν buffer στη μνήμη καθώς θα ήταν πολύ μεγάλος. Η κλάση `HTTPClient` που κάνει τις κλήσεις REST μπορεί να μεταδώσει δεδομένα χρησιμοποιώντας ένα Arduino Stream - μια κλάση που μπορεί να φορτώσει δεδομένα σε μικρά κομμάτια, στέλνοντας τα κομμάτια ένα κάθε φορά ως μέρος του αιτήματος. Κάθε φορά που καλείτε τη `read` σε ένα stream, επιστρέφει το επόμενο μπλοκ δεδομένων. Μπορεί να δημιουργηθεί ένα Arduino stream που μπορεί να διαβάσει από τη μνήμη flash. Δημιουργήστε ένα νέο αρχείο με όνομα `flash_stream.h` στον φάκελο `src` και προσθέστε τον παρακάτω κώδικα:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <HTTPClient.h>
    #include <sfud.h>

    #include "config.h"
    
    class FlashStream : public Stream
    {
    public:
        virtual size_t write(uint8_t val)
        {    
        }
    
        virtual int available()
        {
        }
    
        virtual int read()
        {
        }
    
        virtual int peek()
        {
        }
    private:
    
    };
    ```

    Αυτό δηλώνει την κλάση `FlashStream`, που προέρχεται από την κλάση `Stream` του Arduino. Αυτή είναι μια αφηρημένη κλάση - οι παράγωγες κλάσεις πρέπει να υλοποιήσουν μερικές μεθόδους πριν η κλάση μπορέσει να δημιουργηθεί.

    ✅ Διαβάστε περισσότερα για τα Arduino Streams στην [τεκμηρίωση Stream του Arduino](https://www.arduino.cc/reference/en/language/functions/communication/stream/)

1. Προσθέστε τα παρακάτω πεδία στην ενότητα `private`:

    ```cpp
    size_t _pos;
    size_t _flash_address;
    const sfud_flash *_flash;

    byte _buffer[HTTP_TCP_BUFFER_SIZE];
    ```

    Αυτό ορίζει έναν προσωρινό buffer για την αποθήκευση δεδομένων που διαβάζονται από τη μνήμη flash, μαζί με πεδία για την τρέχουσα θέση κατά την ανάγνωση από τον buffer, την τρέχουσα διεύθυνση για ανάγνωση από τη μνήμη flash και τη συσκευή μνήμης flash.

1. Στην ενότητα `private`, προσθέστε την παρακάτω μέθοδο:

    ```cpp
    void populateBuffer()
    {
        sfud_read(_flash, _flash_address, HTTP_TCP_BUFFER_SIZE, _buffer);
        _flash_address += HTTP_TCP_BUFFER_SIZE;
        _pos = 0;
    }
    ```

    Αυτός ο κώδικας διαβάζει από τη μνήμη flash στη τρέχουσα διεύθυνση και αποθηκεύει τα δεδομένα σε έναν buffer. Στη συνέχεια, αυξάνει τη διεύθυνση, ώστε η επόμενη κλήση να διαβάσει το επόμενο μπλοκ μνήμης. Ο buffer έχει μέγεθος βασισμένο στο μεγαλύτερο κομμάτι που θα στείλει ο `HTTPClient` στο REST API κάθε φορά.

    > 💁 Η διαγραφή της μνήμης flash πρέπει να γίνεται χρησιμοποιώντας το μέγεθος του grain, ενώ η ανάγνωση δεν έχει τέτοιο περιορισμό.

1. Στην ενότητα `public` αυτής της κλάσης, προσθέστε έναν constructor:

    ```cpp
    FlashStream()
    {
        _pos = 0;
        _flash_address = 0;
        _flash = sfud_get_device_table() + 0;
        
        populateBuffer();
    }
    ```

    Αυτός ο constructor ρυθμίζει όλα τα πεδία για να ξεκινήσει η ανάγνωση από την αρχή του μπλοκ μνήμης flash και φορτώνει το πρώτο κομμάτι δεδομένων στον buffer.

1. Υλοποιήστε τη μέθοδο `write`. Αυτό το stream θα διαβάζει μόνο δεδομένα, οπότε αυτή η μέθοδος μπορεί να μην κάνει τίποτα και να επιστρέφει 0:

    ```cpp
    virtual size_t write(uint8_t val)
    {
        return 0;
    }
    ```

1. Υλοποιήστε τη μέθοδο `peek`. Αυτή επιστρέφει τα δεδομένα στη τρέχουσα θέση χωρίς να μετακινεί το stream. Η κλήση της `peek` πολλές φορές θα επιστρέφει πάντα τα ίδια δεδομένα, εφόσον δεν διαβαστούν δεδομένα από το stream.

    ```cpp
    virtual int peek()
    {
        return _buffer[_pos];
    }
    ```

1. Υλοποιήστε τη συνάρτηση `available`. Αυτή επιστρέφει πόσα bytes μπορούν να διαβαστούν από το stream ή -1 αν το stream έχει ολοκληρωθεί. Για αυτή την κλάση, το μέγιστο διαθέσιμο δεν θα είναι ποτέ μεγαλύτερο από το μέγεθος chunk του HTTPClient. Όταν αυτό το stream χρησιμοποιείται στον HTTP client, καλεί αυτή τη συνάρτηση για να δει πόσα δεδομένα είναι διαθέσιμα και στη συνέχεια ζητά τόσα δεδομένα για να στείλει στο REST API. Δεν θέλουμε κάθε chunk να είναι μεγαλύτερο από το μέγεθος chunk του HTTP client, οπότε αν είναι διαθέσιμα περισσότερα, επιστρέφεται το μέγεθος chunk. Αν είναι λιγότερα, επιστρέφεται ό,τι είναι διαθέσιμο. Μόλις όλα τα δεδομένα έχουν μεταδοθεί, επιστρέφεται -1.

    ```cpp
    virtual int available()
    {
        int remaining = BUFFER_SIZE - ((_flash_address - HTTP_TCP_BUFFER_SIZE) + _pos);
        int bytes_available = min(HTTP_TCP_BUFFER_SIZE, remaining);

        if (bytes_available == 0)
        {
            bytes_available = -1;
        }

        return bytes_available;
    }
    ```

1. Υλοποιήστε τη μέθοδο `read` για να επιστρέφει το επόμενο byte από τον buffer, αυξάνοντας τη θέση. Αν η θέση υπερβεί το μέγεθος του buffer, γεμίζει τον buffer με το επόμενο μπλοκ από τη μνήμη flash και επαναφέρει τη θέση.

    ```cpp
    virtual int read()
    {
        int retVal = _buffer[_pos++];

        if (_pos == HTTP_TCP_BUFFER_SIZE)
        {
            populateBuffer();
        }

        return retVal;
    }
    ```

1. Στο αρχείο κεφαλίδας `speech_to_text.h`, προσθέστε μια εντολή include για αυτό το νέο αρχείο κεφαλίδας:

    ```cpp
    #include "flash_stream.h"
    ```

### Εργασία - μετατροπή της ομιλίας σε κείμενο

1. Η ομιλία μπορεί να μετατραπεί σε κείμενο στέλνοντας τον ήχο στην Υπηρεσία Ομιλίας μέσω ενός REST API. Αυτό το REST API έχει διαφορετικό πιστοποιητικό από τον εκδότη διακριτικών, οπότε προσθέστε τον παρακάτω κώδικα στο αρχείο κεφαλίδας `config.h` για να ορίσετε αυτό το πιστοποιητικό:

    ```cpp
    const char *SPEECH_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "MIIF8zCCBNugAwIBAgIQCq+mxcpjxFFB6jvh98dTFzANBgkqhkiG9w0BAQwFADBh\r\n"
        "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\r\n"
        "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBH\r\n"
        "MjAeFw0yMDA3MjkxMjMwMDBaFw0yNDA2MjcyMzU5NTlaMFkxCzAJBgNVBAYTAlVT\r\n"
        "MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKjAoBgNVBAMTIU1pY3Jv\r\n"
        "c29mdCBBenVyZSBUTFMgSXNzdWluZyBDQSAwMTCCAiIwDQYJKoZIhvcNAQEBBQAD\r\n"
        "ggIPADCCAgoCggIBAMedcDrkXufP7pxVm1FHLDNA9IjwHaMoaY8arqqZ4Gff4xyr\r\n"
        "RygnavXL7g12MPAx8Q6Dd9hfBzrfWxkF0Br2wIvlvkzW01naNVSkHp+OS3hL3W6n\r\n"
        "l/jYvZnVeJXjtsKYcXIf/6WtspcF5awlQ9LZJcjwaH7KoZuK+THpXCMtzD8XNVdm\r\n"
        "GW/JI0C/7U/E7evXn9XDio8SYkGSM63aLO5BtLCv092+1d4GGBSQYolRq+7Pd1kR\r\n"
        "EkWBPm0ywZ2Vb8GIS5DLrjelEkBnKCyy3B0yQud9dpVsiUeE7F5sY8Me96WVxQcb\r\n"
        "OyYdEY/j/9UpDlOG+vA+YgOvBhkKEjiqygVpP8EZoMMijephzg43b5Qi9r5UrvYo\r\n"
        "o19oR/8pf4HJNDPF0/FJwFVMW8PmCBLGstin3NE1+NeWTkGt0TzpHjgKyfaDP2tO\r\n"
        "4bCk1G7pP2kDFT7SYfc8xbgCkFQ2UCEXsaH/f5YmpLn4YPiNFCeeIida7xnfTvc4\r\n"
        "7IxyVccHHq1FzGygOqemrxEETKh8hvDR6eBdrBwmCHVgZrnAqnn93JtGyPLi6+cj\r\n"
        "WGVGtMZHwzVvX1HvSFG771sskcEjJxiQNQDQRWHEh3NxvNb7kFlAXnVdRkkvhjpR\r\n"
        "GchFhTAzqmwltdWhWDEyCMKC2x/mSZvZtlZGY+g37Y72qHzidwtyW7rBetZJAgMB\r\n"
        "AAGjggGtMIIBqTAdBgNVHQ4EFgQUDyBd16FXlduSzyvQx8J3BM5ygHYwHwYDVR0j\r\n"
        "BBgwFoAUTiJUIBiV5uNu5g/6+rkS7QYXjzkwDgYDVR0PAQH/BAQDAgGGMB0GA1Ud\r\n"
        "JQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAGAQH/AgEAMHYG\r\n"
        "CCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0cDovL29jc3AuZGlnaWNlcnQu\r\n"
        "Y29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0cy5kaWdpY2VydC5jb20vRGln\r\n"
        "aUNlcnRHbG9iYWxSb290RzIuY3J0MHsGA1UdHwR0MHIwN6A1oDOGMWh0dHA6Ly9j\r\n"
        "cmwzLmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5jcmwwN6A1oDOG\r\n"
        "MWh0dHA6Ly9jcmw0LmRpZ2ljZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RHMi5j\r\n"
        "cmwwHQYDVR0gBBYwFDAIBgZngQwBAgEwCAYGZ4EMAQICMBAGCSsGAQQBgjcVAQQD\r\n"
        "AgEAMA0GCSqGSIb3DQEBDAUAA4IBAQAlFvNh7QgXVLAZSsNR2XRmIn9iS8OHFCBA\r\n"
        "WxKJoi8YYQafpMTkMqeuzoL3HWb1pYEipsDkhiMnrpfeYZEA7Lz7yqEEtfgHcEBs\r\n"
        "K9KcStQGGZRfmWU07hPXHnFz+5gTXqzCE2PBMlRgVUYJiA25mJPXfB00gDvGhtYa\r\n"
        "+mENwM9Bq1B9YYLyLjRtUz8cyGsdyTIG/bBM/Q9jcV8JGqMU/UjAdh1pFyTnnHEl\r\n"
        "Y59Npi7F87ZqYYJEHJM2LGD+le8VsHjgeWX2CJQko7klXvcizuZvUEDTjHaQcs2J\r\n"
        "+kPgfyMIOY1DMJ21NxOJ2xPRC/wAh/hzSBRVtoAnyuxtkZ4VjIOh\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. Προσθέστε μια σταθερά σε αυτό το αρχείο για τη διεύθυνση URL της ομιλίας χωρίς την τοποθεσία. Αυτή θα συνδυαστεί με την τοποθεσία και τη γλώσσα αργότερα για να δημιουργηθεί η πλήρης διεύθυνση URL.

    ```cpp
    const char *SPEECH_URL = "https://%s.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=%s";
    ```

1. Στο αρχείο κεφαλίδας `speech_to_text.h`, στην ενότητα `private` της κλάσης `SpeechToText`, ορίστε ένα πεδίο για έναν WiFi Client που χρησιμοποιεί το πιστοποιητικό ομιλίας:

    ```cpp
    WiFiClientSecure _speech_client;
    ```

1. Στη μέθοδο `init`, ορίστε το πιστοποιητικό σε αυτόν τον WiFi Client:

    ```cpp
    _speech_client.setCACert(SPEECH_CERTIFICATE);
    ```

1. Προσθέστε τον παρακάτω κώδικα στην ενότητα `public` της κλάσης `SpeechToText` για να ορίσετε μια μέθοδο για τη μετατροπή ομιλίας σε κείμενο:

    ```cpp
    String convertSpeechToText()
    {
        
    }
    ```

1. Προσθέστε τον παρακάτω κώδικα σε αυτή τη μέθοδο για να δημιουργήσετε έναν HTTP client χρησιμοποιώντας τον WiFi client που έχει διαμορφωθεί με το πιστοποιητικό ομιλίας και χρησιμοποιώντας τη διεύθυνση URL ομιλίας που έχει οριστεί με την τοποθεσία και τη γλώσσα:

    ```cpp
    char url[128];
    sprintf(url, SPEECH_URL, SPEECH_LOCATION, LANGUAGE);

    HTTPClient httpClient;
    httpClient.begin(_speech_client, url);
    ```

1. Ορισμένες κεφαλίδες πρέπει να οριστούν στη σύνδεση:

    ```cpp
    httpClient.addHeader("Authorization", String("Bearer ") + _access_token);
    httpClient.addHeader("Content-Type", String("audio/wav; codecs=audio/pcm; samplerate=") + String(RATE));
    httpClient.addHeader("Accept", "application/json;text/xml");
    ```

    Αυτό ορίζει κεφαλίδες για την εξουσιοδότηση χρησιμοποιώντας το διακριτικό πρόσβασης, τη μορφή ήχου χρησιμοποιώντας τον ρυθμό δειγματοληψίας και ορίζει ότι ο client αναμένει το αποτέλεσμα ως JSON.

1. Μετά από αυτό, προσθέστε τον παρακάτω κώδικα για να κάνετε την κλήση REST API:

    ```cpp
    Serial.println("Sending speech...");

    FlashStream stream;
    int httpResponseCode = httpClient.sendRequest("POST", &stream, BUFFER_SIZE);

    Serial.println("Speech sent!");
    ```

    Αυτό δημιουργεί ένα `FlashStream` και το χρησιμοποιεί για να μεταδώσει δεδομένα στο REST API.

1. Παρακάτω, προσθέστε τον παρακάτω κώδικα:

    ```cpp
    String text = "";

    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        text = obj["DisplayText"].as<String>();
    }
    else if (httpResponseCode == 401)
    {
        Serial.println("Access token expired, trying again with a new token");
        _access_token = getAccessToken();
        return convertSpeechToText();
    }
    else
    {
        Serial.print("Failed to convert text to speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    Αυτός ο κώδικας ελέγχει τον κωδικό απόκρισης.

    Αν είναι 200, ο κωδικός για επιτυχία, τότε το αποτέλεσμα ανακτάται, αποκωδικοποιείται από JSON και η ιδιότητα `DisplayText` ορίζεται στη μεταβλητή `text`. Αυτή είναι η ιδιότητα στην οποία επιστρέφεται η κειμενική έκδοση της ομιλίας.

    Αν ο κωδικός απόκρισης είναι 401, τότε το διακριτικό πρόσβασης έχει λήξει (αυτά τα διακριτικά διαρκούν μόνο 10 λεπτά). Ζητείται ένα νέο διακριτικό πρόσβασης και η κλήση γίνεται ξανά.

    Διαφορετικά, ένα σφάλμα αποστέλλεται στον σειριακό παρακολουθητή και το `text` παραμένει κενό.

1. Προσθέστε τον παρακάτω κώδικα στο τέλος αυτής της μεθόδου για να κλείσετε τον HTTP client και να επιστρέψετε το κείμενο:

    ```cpp
    httpClient.end();

    return text;
    ```

1. Στο `main.cpp`, καλέστε αυτή τη νέα μέθοδο `convertSpeechToText` στη συνάρτηση `processAudio` και στη συνέχεια καταγράψτε την ομιλία στον σειριακό παρακολουθητή:

    ```cpp
    String text = speechToText.convertSpeechToText();
    Serial.println(text);
    ```

1. Δημιουργήστε αυτόν τον κώδικα, ανεβάστε τον στο Wio Terminal σας και δοκιμάστε τον μέσω του σειριακού παρακολουθητή. Μόλις δείτε το `Ready` στον σειριακό παρακολουθητή, πατήστε το κουμπί C (το κουμπί στην αριστερή πλευρά, πιο κοντά στον διακόπτη τροφοδοσίας) και μιλήστε. Θα καταγραφούν 4 δευτερόλεπτα ήχου και στη συνέχεια θα μετατραπούν σε κείμενο.

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    ```

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-speech-to-text/wio-terminal](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/wio-terminal).

😀 Το πρόγραμμα μετατροπής ομιλίας σε κείμενο ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.