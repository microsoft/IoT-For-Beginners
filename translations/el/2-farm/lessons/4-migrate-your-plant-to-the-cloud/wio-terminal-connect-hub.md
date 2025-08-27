<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-27T22:01:51+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "el"
}
-->
# Συνδέστε τη συσκευή IoT σας στο cloud - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα συνδέσετε το Wio Terminal σας με το IoT Hub, για να στείλετε τηλεμετρία και να λαμβάνετε εντολές.

## Συνδέστε τη συσκευή σας στο IoT Hub

Το επόμενο βήμα είναι να συνδέσετε τη συσκευή σας στο IoT Hub.

### Εργασία - σύνδεση με το IoT Hub

1. Ανοίξτε το έργο `soil-moisture-sensor` στο VS Code.

1. Ανοίξτε το αρχείο `platformio.ini`. Αφαιρέστε την εξάρτηση της βιβλιοθήκης `knolleary/PubSubClient`. Αυτή χρησιμοποιήθηκε για τη σύνδεση με τον δημόσιο MQTT broker και δεν είναι απαραίτητη για τη σύνδεση με το IoT Hub.

1. Προσθέστε τις παρακάτω εξαρτήσεις βιβλιοθηκών:

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    Η βιβλιοθήκη `Seeed Arduino RTC` παρέχει κώδικα για την αλληλεπίδραση με ένα ρολόι πραγματικού χρόνου στο Wio Terminal, που χρησιμοποιείται για την παρακολούθηση του χρόνου. Οι υπόλοιπες βιβλιοθήκες επιτρέπουν στη συσκευή IoT σας να συνδεθεί με το IoT Hub.

1. Προσθέστε το παρακάτω στο τέλος του αρχείου `platformio.ini`:

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    Αυτό ορίζει μια σημαία του μεταγλωττιστή που είναι απαραίτητη κατά τη μεταγλώττιση του κώδικα Arduino IoT Hub.

1. Ανοίξτε το αρχείο κεφαλίδας `config.h`. Αφαιρέστε όλες τις ρυθμίσεις MQTT και προσθέστε την παρακάτω σταθερά για τη συμβολοσειρά σύνδεσης της συσκευής:

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    Αντικαταστήστε το `<connection string>` με τη συμβολοσειρά σύνδεσης για τη συσκευή σας που αντιγράψατε νωρίτερα.

1. Η σύνδεση με το IoT Hub χρησιμοποιεί ένα διακριτικό που βασίζεται στον χρόνο. Αυτό σημαίνει ότι η συσκευή IoT πρέπει να γνωρίζει την τρέχουσα ώρα. Σε αντίθεση με λειτουργικά συστήματα όπως τα Windows, macOS ή Linux, οι μικροελεγκτές δεν συγχρονίζουν αυτόματα την τρέχουσα ώρα μέσω του Διαδικτύου. Αυτό σημαίνει ότι θα χρειαστεί να προσθέσετε κώδικα για να λάβετε την τρέχουσα ώρα από έναν [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) server. Μόλις ληφθεί η ώρα, μπορεί να αποθηκευτεί σε ένα ρολόι πραγματικού χρόνου στο Wio Terminal, επιτρέποντας την ανάκτηση της σωστής ώρας αργότερα, εφόσον η συσκευή δεν χάσει την τροφοδοσία. Προσθέστε ένα νέο αρχείο που ονομάζεται `ntp.h` με τον παρακάτω κώδικα:

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    Οι λεπτομέρειες αυτού του κώδικα είναι εκτός του πεδίου αυτού του μαθήματος. Ορίζει μια συνάρτηση που ονομάζεται `initTime` που λαμβάνει την τρέχουσα ώρα από έναν NTP server και τη χρησιμοποιεί για να ρυθμίσει το ρολόι στο Wio Terminal.

1. Ανοίξτε το αρχείο `main.cpp` και αφαιρέστε όλο τον κώδικα MQTT, συμπεριλαμβανομένου του αρχείου κεφαλίδας `PubSubClient.h`, της δήλωσης της μεταβλητής `PubSubClient`, των μεθόδων `reconnectMQTTClient` και `createMQTTClient`, και οποιωνδήποτε κλήσεων σε αυτές τις μεταβλητές και μεθόδους. Αυτό το αρχείο θα πρέπει να περιέχει μόνο κώδικα για τη σύνδεση στο WiFi, τη λήψη της υγρασίας του εδάφους και τη δημιουργία ενός JSON εγγράφου με αυτήν.

1. Προσθέστε τις παρακάτω οδηγίες `#include` στην κορυφή του αρχείου `main.cpp` για να συμπεριλάβετε αρχεία κεφαλίδας για τις βιβλιοθήκες IoT Hub και για τη ρύθμιση της ώρας:

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. Προσθέστε την παρακάτω κλήση στο τέλος της συνάρτησης `setup` για να ρυθμίσετε την τρέχουσα ώρα:

    ```cpp
    initTime();
    ```

1. Προσθέστε την παρακάτω δήλωση μεταβλητής στην κορυφή του αρχείου, ακριβώς κάτω από τις οδηγίες `include`:

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    Αυτό δηλώνει ένα `IOTHUB_DEVICE_CLIENT_LL_HANDLE`, μια λαβή για τη σύνδεση με το IoT Hub.

1. Κάτω από αυτό, προσθέστε τον παρακάτω κώδικα:

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    Αυτό δηλώνει μια συνάρτηση επιστροφής που θα καλείται όταν η σύνδεση με το IoT Hub αλλάζει κατάσταση, όπως σύνδεση ή αποσύνδεση. Η κατάσταση αποστέλλεται στη σειριακή θύρα.

1. Κάτω από αυτό, προσθέστε μια συνάρτηση για τη σύνδεση με το IoT Hub:

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    Αυτός ο κώδικας αρχικοποιεί τον κώδικα της βιβλιοθήκης IoT Hub και στη συνέχεια δημιουργεί μια σύνδεση χρησιμοποιώντας τη συμβολοσειρά σύνδεσης στο αρχείο κεφαλίδας `config.h`. Αυτή η σύνδεση βασίζεται στο MQTT. Εάν η σύνδεση αποτύχει, αυτό αποστέλλεται στη σειριακή θύρα - αν το δείτε στην έξοδο, ελέγξτε τη συμβολοσειρά σύνδεσης. Τέλος, η συνάρτηση επιστροφής κατάστασης σύνδεσης ρυθμίζεται.

1. Καλέστε αυτήν τη συνάρτηση στη συνάρτηση `setup` κάτω από την κλήση στη `initTime`:

    ```cpp
    connectIoTHub();
    ```

1. Όπως και με τον πελάτη MQTT, αυτός ο κώδικας εκτελείται σε ένα μόνο νήμα, οπότε χρειάζεται χρόνο για να επεξεργαστεί μηνύματα που αποστέλλονται από το hub και προς το hub. Προσθέστε το παρακάτω στην κορυφή της συνάρτησης `loop` για να το κάνετε αυτό:

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. Δημιουργήστε και ανεβάστε αυτόν τον κώδικα. Θα δείτε τη σύνδεση στη σειριακή οθόνη:

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    Στην έξοδο μπορείτε να δείτε την ώρα NTP να λαμβάνεται, ακολουθούμενη από τη σύνδεση του πελάτη της συσκευής. Μπορεί να χρειαστούν μερικά δευτερόλεπτα για να συνδεθεί, οπότε μπορεί να δείτε την υγρασία του εδάφους στην έξοδο ενώ η συσκευή συνδέεται.

    > 💁 Μπορείτε να μετατρέψετε την ώρα UNIX για το NTP σε μια πιο ευανάγνωστη μορφή χρησιμοποιώντας έναν ιστότοπο όπως το [unixtimestamp.com](https://www.unixtimestamp.com).

## Αποστολή τηλεμετρίας

Τώρα που η συσκευή σας είναι συνδεδεμένη, μπορείτε να στείλετε τηλεμετρία στο IoT Hub αντί για τον MQTT broker.

### Εργασία - αποστολή τηλεμετρίας

1. Προσθέστε την παρακάτω συνάρτηση πάνω από τη συνάρτηση `setup`:

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    Αυτός ο κώδικας δημιουργεί ένα μήνυμα IoT Hub από μια συμβολοσειρά που περνά ως παράμετρος, το στέλνει στο hub και στη συνέχεια καθαρίζει το αντικείμενο μηνύματος.

1. Καλέστε αυτόν τον κώδικα στη συνάρτηση `loop`, ακριβώς μετά τη γραμμή όπου η τηλεμετρία αποστέλλεται στη σειριακή θύρα:

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## Διαχείριση εντολών

Η συσκευή σας πρέπει να διαχειρίζεται μια εντολή από τον κώδικα του server για τον έλεγχο του ρελέ. Αυτό αποστέλλεται ως αίτημα άμεσης μεθόδου.

## Εργασία - διαχείριση αιτήματος άμεσης μεθόδου

1. Προσθέστε τον παρακάτω κώδικα πριν από τη συνάρτηση `connectIoTHub`:

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    Αυτός ο κώδικας ορίζει μια μέθοδο επιστροφής που η βιβλιοθήκη IoT Hub μπορεί να καλέσει όταν λαμβάνει ένα αίτημα άμεσης μεθόδου. Η μέθοδος που ζητείται αποστέλλεται στην παράμετρο `method_name`. Αυτή η συνάρτηση εκτυπώνει τη μέθοδο που καλείται στη σειριακή θύρα και στη συνέχεια ενεργοποιεί ή απενεργοποιεί το ρελέ ανάλογα με το όνομα της μεθόδου.

    > 💁 Αυτό θα μπορούσε επίσης να υλοποιηθεί σε ένα μόνο αίτημα άμεσης μεθόδου, περνώντας την επιθυμητή κατάσταση του ρελέ σε ένα payload που μπορεί να περάσει με το αίτημα μεθόδου και να είναι διαθέσιμο από την παράμετρο `payload`.

1. Προσθέστε τον παρακάτω κώδικα στο τέλος της συνάρτησης `directMethodCallback`:

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    Τα αιτήματα άμεσης μεθόδου χρειάζονται μια απάντηση, και η απάντηση είναι σε δύο μέρη - μια απάντηση ως κείμενο και ένας κωδικός επιστροφής. Αυτός ο κώδικας θα δημιουργήσει ένα αποτέλεσμα ως το παρακάτω JSON έγγραφο:

    ```JSON
    {
        "Result": ""
    }
    ```

    Αυτό στη συνέχεια αντιγράφεται στην παράμετρο `response` και το μέγεθος αυτής της απάντησης ορίζεται στην παράμετρο `response_size`. Αυτός ο κώδικας στη συνέχεια επιστρέφει `IOTHUB_CLIENT_OK` για να δείξει ότι η μέθοδος χειρίστηκε σωστά.

1. Συνδέστε τη συνάρτηση επιστροφής προσθέτοντας το παρακάτω στο τέλος της συνάρτησης `connectIoTHub`:

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. Η συνάρτηση `loop` θα καλεί τη συνάρτηση `IoTHubDeviceClient_LL_DoWork` για να επεξεργαστεί γεγονότα που αποστέλλονται από το IoT Hub. Αυτό καλείται μόνο κάθε 10 δευτερόλεπτα λόγω της `delay`, που σημαίνει ότι οι άμεσες μέθοδοι επεξεργάζονται μόνο κάθε 10 δευτερόλεπτα. Για να γίνει αυτό πιο αποτελεσματικό, η καθυστέρηση των 10 δευτερολέπτων μπορεί να υλοποιηθεί ως πολλές μικρότερες καθυστερήσεις, καλώντας τη `IoTHubDeviceClient_LL_DoWork` κάθε φορά. Για να το κάνετε αυτό, προσθέστε τον παρακάτω κώδικα πάνω από τη συνάρτηση `loop`:

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    Αυτός ο κώδικας θα επαναλαμβάνεται συνεχώς, καλώντας τη `IoTHubDeviceClient_LL_DoWork` και καθυστερώντας για 100ms κάθε φορά. Θα το κάνει αυτό όσες φορές χρειάζεται για να καθυστερήσει για το χρονικό διάστημα που δίνεται στην παράμετρο `delay_time`. Αυτό σημαίνει ότι η συσκευή περιμένει το πολύ 100ms για να επεξεργαστεί αιτήματα άμεσης μεθόδου.

1. Στη συνάρτηση `loop`, αφαιρέστε την κλήση στη `IoTHubDeviceClient_LL_DoWork` και αντικαταστήστε την κλήση `delay(10000)` με το παρακάτω για να καλέσετε αυτήν τη νέα συνάρτηση:

    ```cpp
    work_delay(10000);
    ```

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal).

😀 Το πρόγραμμα του αισθητήρα υγρασίας του εδάφους σας είναι συνδεδεμένο με το IoT Hub σας!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.