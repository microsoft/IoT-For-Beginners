<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "160be8c0f558687f6686dca64f10f739",
  "translation_date": "2025-08-27T20:14:28+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md",
  "language_code": "el"
}
-->
# Λήψη εικόνας - Wio Terminal

Σε αυτό το μέρος του μαθήματος, θα προσθέσετε μια κάμερα στο Wio Terminal σας και θα τραβήξετε εικόνες από αυτήν.

## Υλικό

Το Wio Terminal χρειάζεται μια κάμερα.

Η κάμερα που θα χρησιμοποιήσετε είναι η [ArduCam Mini 2MP Plus](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/). Πρόκειται για μια κάμερα 2 megapixel που βασίζεται στον αισθητήρα εικόνας OV2640. Επικοινωνεί μέσω διεπαφής SPI για τη λήψη εικόνων και χρησιμοποιεί I2C για τη ρύθμιση του αισθητήρα.

## Σύνδεση της κάμερας

Η ArduCam δεν διαθέτει υποδοχή Grove, αλλά συνδέεται τόσο με τα SPI όσο και με τα I2C bus μέσω των ακίδων GPIO στο Wio Terminal.

### Εργασία - σύνδεση της κάμερας

Συνδέστε την κάμερα.

![Ένας αισθητήρας ArduCam](../../../../../translated_images/el/arducam.20e4e4cbb268296570b5914e20d6c349fc42ddac9ed4e1b9deba2188204eebae.png)

1. Οι ακίδες στη βάση της ArduCam πρέπει να συνδεθούν στις ακίδες GPIO του Wio Terminal. Για να διευκολυνθεί η εύρεση των σωστών ακίδων, τοποθετήστε το αυτοκόλλητο ακίδων GPIO που συνοδεύει το Wio Terminal γύρω από τις ακίδες:

    ![Το Wio Terminal με το αυτοκόλλητο ακίδων GPIO](../../../../../translated_images/el/wio-terminal-pin-sticker.b90b1535937b84bd.webp)

1. Χρησιμοποιώντας καλώδια jumper, κάντε τις παρακάτω συνδέσεις:

    | Ακίδα ArduCAM | Ακίδα Wio Terminal | Περιγραφή                                |
    | ------------- | ------------------ | ---------------------------------------- |
    | CS            | 24 (SPI_CS)        | Επιλογή Chip SPI                         |
    | MOSI          | 19 (SPI_MOSI)      | Έξοδος Ελεγκτή SPI, Είσοδος Περιφερειακού |
    | MISO          | 21 (SPI_MISO)      | Είσοδος Ελεγκτή SPI, Έξοδος Περιφερειακού |
    | SCK           | 23 (SPI_SCLK)      | Ρολόι Σειριακού SPI                      |
    | GND           | 6 (GND)            | Γείωση - 0V                              |
    | VCC           | 4 (5V)             | Τροφοδοσία 5V                            |
    | SDA           | 3 (I2C1_SDA)       | Σειριακά Δεδομένα I2C                    |
    | SCL           | 5 (I2C1_SCL)       | Σειριακό Ρολόι I2C                       |

    ![Το Wio Terminal συνδεδεμένο με την ArduCam με καλώδια jumper](../../../../../translated_images/el/arducam-wio-terminal-connections.a4d5a4049bdb5ab800a2877389fc6ecf5e4ff307e6451ff56c517e6786467d0a.png)

    Οι συνδέσεις GND και VCC παρέχουν τροφοδοσία 5V στην ArduCam. Λειτουργεί στα 5V, σε αντίθεση με τους αισθητήρες Grove που λειτουργούν στα 3V. Αυτή η τροφοδοσία προέρχεται απευθείας από τη σύνδεση USB-C που τροφοδοτεί τη συσκευή.

    > 💁 Για τη σύνδεση SPI, οι ετικέτες ακίδων στην ArduCam και τα ονόματα ακίδων Wio Terminal που χρησιμοποιούνται στον κώδικα εξακολουθούν να χρησιμοποιούν την παλιά ονοματολογία. Οι οδηγίες σε αυτό το μάθημα θα χρησιμοποιούν τη νέα ονοματολογία, εκτός όταν τα ονόματα ακίδων χρησιμοποιούνται στον κώδικα.

1. Τώρα μπορείτε να συνδέσετε το Wio Terminal στον υπολογιστή σας.

## Προγραμματισμός της συσκευής για σύνδεση με την κάμερα

Το Wio Terminal μπορεί τώρα να προγραμματιστεί για να χρησιμοποιεί την συνδεδεμένη κάμερα ArduCAM.

### Εργασία - προγραμματισμός της συσκευής για σύνδεση με την κάμερα

1. Δημιουργήστε ένα νέο έργο Wio Terminal χρησιμοποιώντας το PlatformIO. Ονομάστε αυτό το έργο `fruit-quality-detector`. Προσθέστε κώδικα στη συνάρτηση `setup` για να ρυθμίσετε τη σειριακή θύρα.

1. Προσθέστε κώδικα για σύνδεση στο WiFi, με τα διαπιστευτήρια WiFi σας σε ένα αρχείο που ονομάζεται `config.h`. Μην ξεχάσετε να προσθέσετε τις απαιτούμενες βιβλιοθήκες στο αρχείο `platformio.ini`.

1. Η βιβλιοθήκη ArduCam δεν είναι διαθέσιμη ως βιβλιοθήκη Arduino που μπορεί να εγκατασταθεί από το αρχείο `platformio.ini`. Αντίθετα, θα χρειαστεί να εγκατασταθεί από τον πηγαίο κώδικα από τη σελίδα τους στο GitHub. Μπορείτε να το αποκτήσετε είτε:

    * Κλωνοποιώντας το αποθετήριο από [https://github.com/ArduCAM/Arduino.git](https://github.com/ArduCAM/Arduino.git)
    * Μεταβαίνοντας στο αποθετήριο στο GitHub στη διεύθυνση [github.com/ArduCAM/Arduino](https://github.com/ArduCAM/Arduino) και κατεβάζοντας τον κώδικα ως zip από το κουμπί **Code**

1. Χρειάζεστε μόνο τον φάκελο `ArduCAM` από αυτόν τον κώδικα. Αντιγράψτε ολόκληρο τον φάκελο στον φάκελο `lib` στο έργο σας.

    > ⚠️ Ολόκληρος ο φάκελος πρέπει να αντιγραφεί, ώστε ο κώδικας να βρίσκεται στον φάκελο `lib/ArduCam`. Μην αντιγράψετε μόνο τα περιεχόμενα του φακέλου `ArduCam` στον φάκελο `lib`, αντιγράψτε ολόκληρο τον φάκελο.

1. Ο κώδικας της βιβλιοθήκης ArduCam λειτουργεί για πολλούς τύπους κάμερας. Ο τύπος της κάμερας που θέλετε να χρησιμοποιήσετε ρυθμίζεται χρησιμοποιώντας σημαίες μεταγλωττιστή - αυτό διατηρεί τη βιβλιοθήκη όσο το δυνατόν μικρότερη αφαιρώντας τον κώδικα για κάμερες που δεν χρησιμοποιείτε. Για να ρυθμίσετε τη βιβλιοθήκη για την κάμερα OV2640, προσθέστε τα παρακάτω στο τέλος του αρχείου `platformio.ini`:

    ```ini
    build_flags =
        -DARDUCAM_SHIELD_V2
        -DOV2640_CAM
    ```

    Αυτό ορίζει 2 σημαίες μεταγλωττιστή:

      * `ARDUCAM_SHIELD_V2` για να ενημερώσει τη βιβλιοθήκη ότι η κάμερα βρίσκεται σε μια πλακέτα Arduino, γνωστή ως shield.
      * `OV2640_CAM` για να ενημερώσει τη βιβλιοθήκη να περιλαμβάνει μόνο κώδικα για την κάμερα OV2640.

1. Προσθέστε ένα αρχείο κεφαλίδας στον φάκελο `src` που ονομάζεται `camera.h`. Αυτό θα περιέχει κώδικα για την επικοινωνία με την κάμερα. Προσθέστε τον παρακάτω κώδικα σε αυτό το αρχείο:

    ```cpp
    #pragma once
    
    #include <ArduCAM.h>
    #include <Wire.h>
    
    class Camera
    {
    public:
        Camera(int format, int image_size) : _arducam(OV2640, PIN_SPI_SS)
        {
            _format = format;
            _image_size = image_size;
        }
    
        bool init()
        {
            // Reset the CPLD
            _arducam.write_reg(0x07, 0x80);
            delay(100);
    
            _arducam.write_reg(0x07, 0x00);
            delay(100);
    
            // Check if the ArduCAM SPI bus is OK
            _arducam.write_reg(ARDUCHIP_TEST1, 0x55);
            if (_arducam.read_reg(ARDUCHIP_TEST1) != 0x55)
            {
                return false;
            }
                
            // Change MCU mode
            _arducam.set_mode(MCU2LCD_MODE);
    
            uint8_t vid, pid;
    
            // Check if the camera module type is OV2640
            _arducam.wrSensorReg8_8(0xff, 0x01);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
            _arducam.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
            if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42)))
            {
                return false;
            }
            
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
            _arducam.OV2640_set_Light_Mode(Auto);
            _arducam.OV2640_set_Special_effects(Normal);
            delay(1000);
    
            return true;
        }
    
        void startCapture()
        {
            _arducam.flush_fifo();
            _arducam.clear_fifo_flag();
            _arducam.start_capture();
        }
    
        bool captureReady()
        {
            return _arducam.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK);
        }
    
        bool readImageToBuffer(byte **buffer, uint32_t &buffer_length)
        {
            if (!captureReady()) return false;
    
            // Get the image file length
            uint32_t length = _arducam.read_fifo_length();
            buffer_length = length;
    
            if (length >= MAX_FIFO_SIZE)
            {
                return false;
            }
            if (length == 0)
            {
                return false;
            }
    
            // create the buffer
            byte *buf = new byte[length];
    
            uint8_t temp = 0, temp_last = 0;
            int i = 0;
            uint32_t buffer_pos = 0;
            bool is_header = false;
    
            _arducam.CS_LOW();
            _arducam.set_fifo_burst();
            
            while (length--)
            {
                temp_last = temp;
                temp = SPI.transfer(0x00);
                //Read JPEG data from FIFO
                if ((temp == 0xD9) && (temp_last == 0xFF)) //If find the end ,break while,
                {
                    buf[buffer_pos] = temp;
    
                    buffer_pos++;
                    i++;
                    
                    _arducam.CS_HIGH();
                }
                if (is_header == true)
                {
                    //Write image data to buffer if not full
                    if (i < 256)
                    {
                        buf[buffer_pos] = temp;
                        buffer_pos++;
                        i++;
                    }
                    else
                    {
                        _arducam.CS_HIGH();
    
                        i = 0;
                        buf[buffer_pos] = temp;
    
                        buffer_pos++;
                        i++;
    
                        _arducam.CS_LOW();
                        _arducam.set_fifo_burst();
                    }
                }
                else if ((temp == 0xD8) & (temp_last == 0xFF))
                {
                    is_header = true;
    
                    buf[buffer_pos] = temp_last;
                    buffer_pos++;
                    i++;
    
                    buf[buffer_pos] = temp;
                    buffer_pos++;
                    i++;
                }
            }
            
            _arducam.clear_fifo_flag();
    
            _arducam.set_format(_format);
            _arducam.InitCAM();
            _arducam.OV2640_set_JPEG_size(_image_size);
    
            // return the buffer
            *buffer = buf;
        }
    
    private:
        ArduCAM _arducam;
        int _format;
        int _image_size;
    };
    ```

    Αυτός είναι χαμηλού επιπέδου κώδικας που ρυθμίζει την κάμερα χρησιμοποιώντας τις βιβλιοθήκες ArduCam και εξάγει τις εικόνες όταν απαιτείται μέσω του bus SPI. Αυτός ο κώδικας είναι πολύ συγκεκριμένος για την ArduCam, οπότε δεν χρειάζεται να ανησυχείτε για το πώς λειτουργεί σε αυτό το σημείο.

1. Στο `main.cpp`, προσθέστε τον παρακάτω κώδικα κάτω από τις άλλες δηλώσεις `include` για να συμπεριλάβετε αυτό το νέο αρχείο και να δημιουργήσετε μια παρουσία της κλάσης κάμερας:

    ```cpp
    #include "camera.h"

    Camera camera = Camera(JPEG, OV2640_640x480);
    ```

    Αυτό δημιουργεί μια `Camera` που αποθηκεύει τις εικόνες ως JPEG σε ανάλυση 640x480. Αν και υποστηρίζονται υψηλότερες αναλύσεις (έως 3280x2464), ο ταξινομητής εικόνων λειτουργεί με πολύ μικρότερες εικόνες (227x227), οπότε δεν υπάρχει λόγος να τραβήξετε και να στείλετε μεγαλύτερες εικόνες.

1. Προσθέστε τον παρακάτω κώδικα κάτω από αυτό για να ορίσετε μια συνάρτηση για τη ρύθμιση της κάμερας:

    ```cpp
    void setupCamera()
    {
        pinMode(PIN_SPI_SS, OUTPUT);
        digitalWrite(PIN_SPI_SS, HIGH);
    
        Wire.begin();
        SPI.begin();
    
        if (!camera.init())
        {
            Serial.println("Error setting up the camera!");
        }
    }
    ```

    Αυτή η συνάρτηση `setupCamera` ξεκινά ρυθμίζοντας την ακίδα επιλογής chip SPI (`PIN_SPI_SS`) ως υψηλή, καθιστώντας το Wio Terminal τον ελεγκτή SPI. Στη συνέχεια, ξεκινά τα bus I2C και SPI. Τέλος, αρχικοποιεί την κλάση κάμερας, η οποία ρυθμίζει τις ρυθμίσεις του αισθητήρα της κάμερας και διασφαλίζει ότι όλα είναι σωστά συνδεδεμένα.

1. Καλέστε αυτή τη συνάρτηση στο τέλος της συνάρτησης `setup`:

    ```cpp
    setupCamera();
    ```

1. Δημιουργήστε και ανεβάστε αυτόν τον κώδικα και ελέγξτε την έξοδο από τον σειριακό παρακολουθητή. Αν δείτε το μήνυμα `Error setting up the camera!`, ελέγξτε τη συνδεσμολογία για να βεβαιωθείτε ότι όλα τα καλώδια συνδέουν τις σωστές ακίδες στην ArduCam με τις σωστές ακίδες GPIO στο Wio Terminal και ότι όλα τα καλώδια jumper είναι σωστά τοποθετημένα.

## Λήψη εικόνας

Το Wio Terminal μπορεί τώρα να προγραμματιστεί για να τραβάει μια εικόνα όταν πατηθεί ένα κουμπί.

### Εργασία - λήψη εικόνας

1. Οι μικροελεγκτές εκτελούν τον κώδικά σας συνεχώς, οπότε δεν είναι εύκολο να ενεργοποιηθεί κάτι όπως η λήψη μιας φωτογραφίας χωρίς να αντιδράσει σε έναν αισθητήρα. Το Wio Terminal διαθέτει κουμπιά, οπότε η κάμερα μπορεί να ρυθμιστεί ώστε να ενεργοποιείται από ένα από τα κουμπιά. Προσθέστε τον παρακάτω κώδικα στο τέλος της συνάρτησης `setup` για να ρυθμίσετε το κουμπί C (ένα από τα τρία κουμπιά στην κορυφή, το πιο κοντινό στον διακόπτη τροφοδοσίας).

    ![Το κουμπί C στην κορυφή, κοντά στον διακόπτη τροφοδοσίας](../../../../../translated_images/el/wio-terminal-c-button.73df3cb1c1445ea0.webp)

    ```cpp
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    ```

    Η λειτουργία `INPUT_PULLUP` ουσιαστικά αντιστρέφει μια είσοδο. Για παράδειγμα, κανονικά ένα κουμπί θα έστελνε χαμηλό σήμα όταν δεν πατιέται και υψηλό σήμα όταν πατιέται. Όταν ρυθμιστεί σε `INPUT_PULLUP`, στέλνει υψηλό σήμα όταν δεν πατιέται και χαμηλό σήμα όταν πατιέται.

1. Προσθέστε μια κενή συνάρτηση για να ανταποκριθεί στο πάτημα του κουμπιού πριν από τη συνάρτηση `loop`:

    ```cpp
    void buttonPressed()
    {
        
    }
    ```

1. Καλέστε αυτή τη συνάρτηση στη μέθοδο `loop` όταν πατηθεί το κουμπί:

    ```cpp
    void loop()
    {
        if (digitalRead(WIO_KEY_C) == LOW)
        {
            buttonPressed();
            delay(2000);
        }
    
        delay(200);
    }
    ```

    Αυτός ο κώδικας ελέγχει αν το κουμπί πατιέται. Αν πατιέται, καλείται η συνάρτηση `buttonPressed` και η επανάληψη καθυστερεί για 2 δευτερόλεπτα. Αυτό γίνεται για να δοθεί χρόνος να απελευθερωθεί το κουμπί ώστε να μην καταγραφεί δύο φορές ένα παρατεταμένο πάτημα.

    > 💁 Το κουμπί στο Wio Terminal έχει ρυθμιστεί σε `INPUT_PULLUP`, οπότε στέλνει υψηλό σήμα όταν δεν πατιέται και χαμηλό σήμα όταν πατιέται.

1. Προσθέστε τον παρακάτω κώδικα στη συνάρτηση `buttonPressed`:

    ```cpp
    camera.startCapture();
 
    while (!camera.captureReady())
        delay(100);

    Serial.println("Image captured");

    byte *buffer;
    uint32_t length;

    if (camera.readImageToBuffer(&buffer, length))
    {
        Serial.print("Image read to buffer with length ");
        Serial.println(length);

        delete(buffer);
    }
    ```

    Αυτός ο κώδικας ξεκινά τη λήψη της εικόνας καλώντας τη `startCapture`. Το υλικό της κάμερας δεν λειτουργεί επιστρέφοντας τα δεδομένα όταν τα ζητάτε, αντίθετα στέλνετε μια εντολή για να ξεκινήσει η λήψη και η κάμερα θα λειτουργήσει στο παρασκήνιο για να τραβήξει την εικόνα, να τη μετατρέψει σε JPEG και να την αποθηκεύσει σε έναν τοπικό buffer στην ίδια την κάμερα. Η κλήση `captureReady` ελέγχει στη συνέχεια αν η λήψη της εικόνας έχει ολοκληρωθεί.

    Μόλις ολοκληρωθεί η λήψη, τα δεδομένα της εικόνας αντιγράφονται από τον buffer της κάμερας σε έναν τοπικό buffer (πίνακας byte) με την κλήση `readImageToBuffer`. Το μήκος του buffer στη συνέχεια αποστέλλεται στον σειριακό παρακολουθητή.

1. Δημιουργήστε και ανεβάστε αυτόν τον κώδικα και ελέγξτε την έξοδο στον σειριακό παρακολουθητή. Κάθε φορά που πατάτε το κουμπί C, θα τραβιέται μια εικόνα και θα βλέπετε το μέγεθος της εικόνας να αποστέλλεται στον σειριακό παρακολουθητή.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 9224
    Image captured
    Image read to buffer with length 11272
    ```

    Διαφορετικές εικόνες θα έχουν διαφορετικά μεγέθη. Συμπιέζονται ως JPEG και το μέγεθος ενός αρχείου JPEG για μια δεδομένη ανάλυση εξαρτάται από το περιεχόμενο της εικόνας.

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-camera/wio-terminal](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/wio-terminal).

😀 Έχετε τραβήξει επιτυχώς εικόνες με το Wio Terminal σας.

## Προαιρετικό - επαλήθευση των εικόνων της κάμερας χρησιμοποιώντας μια κάρτα SD

Ο ευκολότερος τρόπος για να δείτε τις εικόνες που τραβήχτηκαν από την κάμερα είναι να τις γράψετε σε μια κάρτα SD στο Wio Terminal και στη συνέχεια να τις δείτε στον υπολογιστή σας. Κάντε αυτό το βήμα αν έχετε μια εφεδρική κάρτα microSD και μια υποδοχή microSD στον υπολογιστή σας ή έναν προσαρμογέα.

Το Wio Terminal υποστηρίζει μόνο κάρτες microSD έως 16GB. Αν έχετε μεγαλύτερη κάρτα SD, δεν θα λειτουργήσει.

### Εργασία - επαλήθευση των εικόνων της κάμερας χρησιμοποιώντας μια κάρτα SD

1. Διαμορφώστε μια κάρτα microSD ως FAT32 ή exFAT χρησιμοποιώντας τις σχετικές εφαρμογές στον υπολογιστή σας (Disk Utility σε macOS, File Explorer σε Windows ή χρησιμοποιώντας εργαλεία γραμμής εντολών σε Linux).

1. Εισάγετε την κάρτα microSD στην υποδοχή ακριβώς κάτω από τον διακόπτη τροφοδοσίας. Βεβαιωθείτε ότι έχει εισαχθεί πλήρως μέχρι να κάνει κλικ και να παραμείνει στη θέση της. Ίσως χρειαστεί να την πιέσετε χρησιμοποιώντας ένα νύχι ή ένα λεπτό εργαλείο.

1. Προσθέστε τις παρακάτω δηλώσεις `include` στην κορυφή του αρχείου `main.cpp`:

    ```cpp
    #include "SD/Seeed_SD.h"
    #include <Seeed_FS.h>
    ```

1. Προσθέστε την παρακάτω συνάρτηση πριν από τη συνάρτηση `setup`:

    ```cpp
    void setupSDCard()
    {
        while (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI))
        {
            Serial.println("SD Card Error");
        }
    }
    ```

    Αυτή ρυθμίζει την κάρτα SD χρησιμοποιώντας το bus SPI.

1. Καλέστε αυτή τη συνάρτηση από τη συνάρτηση `setup`:

    ```cpp
    setupSDCard();
    ```

1. Προσθέστε τον παρακάτω κώδικα πάνω από τη συνάρτηση `buttonPressed`:

    ```cpp
    int fileNum = 1;

    void saveToSDCard(byte *buffer, uint32_t length)
    {
        char buff[16];
        sprintf(buff, "%d.jpg", fileNum);
        fileNum++;
    
        File outFile = SD.open(buff, FILE_WRITE );
        outFile.write(buffer, length);
        outFile.close();

        Serial.print("Image written to file ");
        Serial.println(buff);
    }
    ```

    Αυτό ορίζει μια καθολική μεταβλητή για τον αριθμό αρχείων. Αυτή χρησιμοποιείται για τα ονόματα αρχείων εικόνων, ώστε να μπορούν να τραβηχτούν πολλές εικόνες με αυξανόμενα ονόματα αρχείων - `1.jpg`, `2.jpg` κ.ο.κ.

    Στη συνέχεια, ορίζει τη συνάρτηση `saveToSDCard` που λαμβάνει έναν buffer δεδομένων byte και το μήκος του buffer. Δημιουργείται ένα όνομα αρχείου χρησιμοποιώντας τον αριθμό αρχείων και ο αριθμός αρχείων αυξάνεται έτοιμος για το επόμενο αρχείο. Τα δυαδικά δεδομένα από τον buffer γράφονται στο αρχείο.

1. Καλέστε τη συνάρτηση `saveToSDCard` από τη συνάρτηση `buttonPressed`. Η κλήση πρέπει να είναι **πριν** διαγραφεί ο buffer:

    ```cpp
    Serial.print("Image read to buffer with length ");
    Serial.println(length);

    saveToSDCard(buffer, length);
    
    delete(buffer);
    ```

1. Δημιουργήστε και ανεβάστε αυτόν τον κώδικα και ελέγξτε την έξοδο στον σειριακό παρακολουθητή. Κάθε φορά που πατάτε το κουμπί C, θα τραβιέται μια εικόνα και θα αποθηκεύεται στην κάρτα SD.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 16392
    Image written to file 1.jpg
    Image captured
    Image read to buffer with length 14344
    Image written to file 2.jpg
    ```

1. Απενεργοποιήστε την κάρτα microSD και εξαγάγετέ την πιέζοντάς την ελαφρώς
💁 Μπορεί να χρειαστούν μερικές εικόνες για να προσαρμοστεί η ισορροπία λευκού της κάμερας. Θα το παρατηρήσετε αυτό βάσει του χρώματος των εικόνων που καταγράφονται, οι πρώτες μπορεί να φαίνονται εκτός χρώματος. Μπορείτε πάντα να το παρακάμψετε αυτό αλλάζοντας τον κώδικα ώστε να καταγράψει μερικές εικόνες που αγνοούνται στη λειτουργία `setup`.


---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.