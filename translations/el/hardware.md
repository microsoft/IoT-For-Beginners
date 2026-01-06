<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3dce18fab38adf93ff30b8c221b1eec5",
  "translation_date": "2025-08-27T19:52:29+00:00",
  "source_file": "hardware.md",
  "language_code": "el"
}
-->
# Υλικό

Το **T** στο IoT είναι **Πράγματα** και αναφέρεται σε συσκευές που αλληλεπιδρούν με τον κόσμο γύρω μας. Κάθε έργο βασίζεται σε πραγματικό υλικό που είναι διαθέσιμο σε μαθητές και χομπίστες. Έχουμε δύο επιλογές υλικού IoT ανάλογα με τις προσωπικές προτιμήσεις, τις γνώσεις ή τις προτιμήσεις στη γλώσσα προγραμματισμού, τους μαθησιακούς στόχους και τη διαθεσιμότητα. Έχουμε επίσης παρέχει μια έκδοση "εικονικού υλικού" για όσους δεν έχουν πρόσβαση σε υλικό ή θέλουν να μάθουν περισσότερα πριν δεσμευτούν σε μια αγορά.

> 💁 Δεν χρειάζεται να αγοράσετε κανένα υλικό IoT για να ολοκληρώσετε τις ασκήσεις. Μπορείτε να κάνετε τα πάντα χρησιμοποιώντας εικονικό υλικό IoT.

Οι επιλογές φυσικού υλικού είναι Arduino ή Raspberry Pi. Κάθε πλατφόρμα έχει τα πλεονεκτήματα και τα μειονεκτήματά της, και αυτά καλύπτονται σε ένα από τα αρχικά μαθήματα. Εάν δεν έχετε ήδη αποφασίσει για μια πλατφόρμα υλικού, μπορείτε να ανατρέξετε [στο δεύτερο μάθημα του πρώτου έργου](./1-getting-started/lessons/2-deeper-dive/README.md) για να αποφασίσετε ποια πλατφόρμα υλικού σας ενδιαφέρει περισσότερο να μάθετε.

Το συγκεκριμένο υλικό επιλέχθηκε για να μειώσει την πολυπλοκότητα των μαθημάτων και των ασκήσεων. Αν και άλλα υλικά μπορεί να λειτουργούν, δεν μπορούμε να εγγυηθούμε ότι όλες οι ασκήσεις θα υποστηρίζονται στη συσκευή σας χωρίς πρόσθετο υλικό. Για παράδειγμα, πολλές συσκευές Arduino δεν διαθέτουν WiFi, το οποίο είναι απαραίτητο για τη σύνδεση στο cloud - το Wio terminal επιλέχθηκε επειδή έχει ενσωματωμένο WiFi.

Θα χρειαστείτε επίσης μερικά μη τεχνικά αντικείμενα, όπως χώμα ή ένα γλαστράκι, και φρούτα ή λαχανικά.

## Αγοράστε τα κιτ

![Το λογότυπο των Seeed studios](../../translated_images/seeed-logo.74732b6b482b6e8e.el.png)

Τα Seeed Studios έχουν ευγενικά διαθέσει όλο το υλικό ως εύκολα προσβάσιμα κιτ:

### Arduino - Wio Terminal

**[IoT για αρχάριους με Seeed και Microsoft - Wio Terminal Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)**

[![Το κιτ υλικού Wio Terminal](../../translated_images/wio-hardware-kit.4c70c48b85e4283a.el.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Wio-Terminal-Starter-Kit-p-5006.html)

### Raspberry Pi

**[IoT για αρχάριους με Seeed και Microsoft - Raspberry Pi 4 Starter Kit](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)**

[![Το κιτ υλικού Raspberry Pi Terminal](../../translated_images/pi-hardware-kit.26dbadaedb7dd44c73b0131d5d68ea29472ed0a9744f90d5866c6d82f2d16380.el.png)](https://www.seeedstudio.com/IoT-for-beginners-with-Seeed-and-Microsoft-Raspberry-Pi-Starter-Kit-p-5004.html)

## Arduino

Όλος ο κώδικας για το Arduino είναι γραμμένος σε C++. Για να ολοκληρώσετε όλες τις ασκήσεις θα χρειαστείτε τα εξής:

### Υλικό Arduino

* [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html)
* *Προαιρετικό* - Καλώδιο USB-C ή αντάπτορα USB-A σε USB-C. Το Wio terminal διαθέτει θύρα USB-C και συνοδεύεται από καλώδιο USB-C σε USB-A. Εάν ο υπολογιστής ή το Mac σας διαθέτει μόνο θύρες USB-C, θα χρειαστείτε ένα καλώδιο USB-C ή έναν αντάπτορα USB-A σε USB-C.

### Ειδικοί αισθητήρες και ενεργοποιητές για Arduino

Αυτά είναι ειδικά για τη συσκευή Arduino Wio terminal και δεν σχετίζονται με τη χρήση του Raspberry Pi.

* [ArduCam Mini 2MP Plus - OV2640](https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/)
* [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html)
* [Breadboard Jumper Wires](https://www.seeedstudio.com/Breadboard-Jumper-Wire-Pack-241mm-200mm-160mm-117m-p-234.html)
* Ακουστικά ή άλλο ηχείο με βύσμα 3.5mm, ή ηχείο JST όπως:
  * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
* Κάρτα microSD 16GB ή λιγότερο, μαζί με έναν συνδετήρα για χρήση της κάρτας SD με τον υπολογιστή σας εάν δεν διαθέτετε ενσωματωμένο. **ΣΗΜΕΙΩΣΗ** - το Wio Terminal υποστηρίζει μόνο κάρτες SD έως 16GB, δεν υποστηρίζει μεγαλύτερες χωρητικότητες.

## Raspberry Pi

Όλος ο κώδικας για το Raspberry Pi είναι γραμμένος σε Python. Για να ολοκληρώσετε όλες τις ασκήσεις θα χρειαστείτε τα εξής:

### Υλικό Raspberry Pi

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/)
  > 💁 Οι εκδόσεις από το Pi 2B και πάνω θα πρέπει να λειτουργούν με τις ασκήσεις αυτών των μαθημάτων. Εάν σκοπεύετε να εκτελέσετε το VS Code απευθείας στο Pi, τότε χρειάζεστε ένα Pi 4 με 2GB ή περισσότερη RAM. Εάν πρόκειται να αποκτήσετε πρόσβαση στο Pi εξ αποστάσεως, τότε οποιοδήποτε Pi 2B και πάνω θα λειτουργήσει.
* Κάρτα microSD (Μπορείτε να βρείτε κιτ Raspberry Pi που περιλαμβάνουν κάρτα microSD), μαζί με έναν συνδετήρα για χρήση της κάρτας SD με τον υπολογιστή σας εάν δεν διαθέτετε ενσωματωμένο.
* Τροφοδοτικό USB (Μπορείτε να βρείτε κιτ Raspberry Pi 4 που περιλαμβάνουν τροφοδοτικό). Εάν χρησιμοποιείτε Raspberry Pi 4 χρειάζεστε τροφοδοτικό USB-C, ενώ οι προηγούμενες συσκευές χρειάζονται τροφοδοτικό micro-USB.

### Ειδικοί αισθητήρες και ενεργοποιητές για Raspberry Pi

Αυτά είναι ειδικά για τη χρήση του Raspberry Pi και δεν σχετίζονται με τη συσκευή Arduino.

* [Grove Pi base hat](https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html)
* [Raspberry Pi Camera module](https://www.raspberrypi.org/products/camera-module-v2/)
* Μικρόφωνο και ηχείο:

  Χρησιμοποιήστε ένα από τα παρακάτω (ή αντίστοιχο):
  * Οποιοδήποτε USB μικρόφωνο με οποιοδήποτε USB ηχείο, ή ηχείο με καλώδιο βύσματος 3.5mm, ή χρησιμοποιώντας έξοδο ήχου HDMI εάν το Raspberry Pi σας είναι συνδεδεμένο σε οθόνη ή τηλεόραση με ηχεία
  * Οποιοδήποτε USB ακουστικό με ενσωματωμένο μικρόφωνο
  * [ReSpeaker 2-Mics Pi HAT](https://www.seeedstudio.com/ReSpeaker-2-Mics-Pi-HAT.html) με
    * Ακουστικά ή άλλο ηχείο με βύσμα 3.5mm, ή ηχείο JST όπως:
    * [Mono Enclosed Speaker - 2W 6 Ohm](https://www.seeedstudio.com/Mono-Enclosed-Speaker-2W-6-Ohm-p-2832.html)
  * [USB Speakerphone](https://www.amazon.com/USB-Speakerphone-Conference-Business-Microphones/dp/B07Q3D7F8S/ref=sr_1_1?dchild=1&keywords=m0&qid=1614647389&sr=8-1)
* [Grove Light sensor](https://www.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html)
* [Grove button](https://www.seeedstudio.com/Grove-Button.html)

## Αισθητήρες και ενεργοποιητές

Οι περισσότεροι από τους αισθητήρες και τους ενεργοποιητές που χρειάζονται χρησιμοποιούνται και στις δύο διαδρομές μάθησης Arduino και Raspberry Pi:

* [Grove LED](https://www.seeedstudio.com/Grove-LED-Pack-p-4364.html) x 2
* [Grove humidity and temperature sensor](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)
* [Grove capacitive soil moisture sensor](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html)
* [Grove relay](https://www.seeedstudio.com/Grove-Relay.html)
* [Grove GPS (Air530)](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)
* [Grove Time of flight Distance Sensor](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)

## Προαιρετικό υλικό

Τα μαθήματα για την αυτοματοποιημένη άρδευση λειτουργούν χρησιμοποιώντας ένα ρελέ. Ως επιλογή, μπορείτε να συνδέσετε αυτό το ρελέ σε μια αντλία νερού που τροφοδοτείται μέσω USB χρησιμοποιώντας το παρακάτω υλικό.

* [6V water pump](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html)
* [USB terminal](https://www.adafruit.com/product/3628)
* Σωλήνες σιλικόνης
* Κόκκινα και μαύρα καλώδια
* Μικρό κατσαβίδι επίπεδης κεφαλής

## Εικονικό υλικό

Η διαδρομή εικονικού υλικού θα παρέχει προσομοιωτές για τους αισθητήρες και τους ενεργοποιητές, υλοποιημένους σε Python. Ανάλογα με τη διαθεσιμότητα του υλικού σας, μπορείτε να το εκτελέσετε στη συσκευή ανάπτυξής σας, όπως Mac, PC, ή να το εκτελέσετε σε ένα Raspberry Pi και να προσομοιώσετε μόνο το υλικό που δεν έχετε. Για παράδειγμα, εάν έχετε την κάμερα Raspberry Pi αλλά όχι τους αισθητήρες Grove, θα μπορείτε να εκτελέσετε τον εικονικό κώδικα συσκευής στο Pi σας και να προσομοιώσετε τους αισθητήρες Grove, αλλά να χρησιμοποιήσετε μια φυσική κάμερα.

Το εικονικό υλικό θα χρησιμοποιήσει το [CounterFit project](https://github.com/CounterFit-IoT/CounterFit).

Για να ολοκληρώσετε αυτά τα μαθήματα θα χρειαστείτε μια κάμερα web, μικρόφωνο και έξοδο ήχου όπως ηχεία ή ακουστικά. Αυτά μπορεί να είναι ενσωματωμένα ή εξωτερικά και πρέπει να είναι διαμορφωμένα ώστε να λειτουργούν με το λειτουργικό σας σύστημα και να είναι διαθέσιμα για χρήση από όλες τις εφαρμογές.

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτόματες μεταφράσεις ενδέχεται να περιέχουν λάθη ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.