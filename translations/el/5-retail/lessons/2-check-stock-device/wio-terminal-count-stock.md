<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T21:39:16+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "el"
}
-->
# Μετρήστε το απόθεμα από τη συσκευή IoT σας - Wio Terminal

Ένας συνδυασμός των προβλέψεων και των ορίων τους μπορεί να χρησιμοποιηθεί για να μετρήσετε το απόθεμα σε μια εικόνα.

## Μετρήστε το απόθεμα

![4 κονσέρβες πάστας ντομάτας με οριοθετημένα πλαίσια γύρω από κάθε κονσέρβα](../../../../../translated_images/el/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

Στην εικόνα που φαίνεται παραπάνω, τα οριοθετημένα πλαίσια έχουν μια μικρή επικάλυψη. Αν αυτή η επικάλυψη ήταν πολύ μεγαλύτερη, τότε τα οριοθετημένα πλαίσια μπορεί να υποδείκνυαν το ίδιο αντικείμενο. Για να μετρήσετε σωστά τα αντικείμενα, πρέπει να αγνοήσετε πλαίσια με σημαντική επικάλυψη.

### Εργασία - μετρήστε το απόθεμα αγνοώντας την επικάλυψη

1. Ανοίξτε το έργο σας `stock-counter` αν δεν είναι ήδη ανοιχτό.

1. Πάνω από τη συνάρτηση `processPredictions`, προσθέστε τον ακόλουθο κώδικα:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Αυτό ορίζει το ποσοστό επικάλυψης που επιτρέπεται πριν τα οριοθετημένα πλαίσια θεωρηθούν το ίδιο αντικείμενο. Το 0.20 ορίζει μια επικάλυψη 20%.

1. Κάτω από αυτό, και πάνω από τη συνάρτηση `processPredictions`, προσθέστε τον ακόλουθο κώδικα για να υπολογίσετε την επικάλυψη μεταξύ δύο ορθογωνίων:

    ```cpp
    struct Point {
        float x, y;
    };

    struct Rect {
        Point topLeft, bottomRight;
    };

    float area(Rect rect)
    {
        return abs(rect.bottomRight.x - rect.topLeft.x) * abs(rect.bottomRight.y - rect.topLeft.y);
    }
     
    float overlappingArea(Rect rect1, Rect rect2)
    {
        float left = max(rect1.topLeft.x, rect2.topLeft.x);
        float right = min(rect1.bottomRight.x, rect2.bottomRight.x);
        float top = max(rect1.topLeft.y, rect2.topLeft.y);
        float bottom = min(rect1.bottomRight.y, rect2.bottomRight.y);
    
    
        if ( right > left && bottom > top )
        {
            return (right-left)*(bottom-top);
        }
        
        return 0.0f;
    }
    ```

    Αυτός ο κώδικας ορίζει μια δομή `Point` για να αποθηκεύει σημεία στην εικόνα, και μια δομή `Rect` για να ορίζει ένα ορθογώνιο χρησιμοποιώντας μια πάνω αριστερή και κάτω δεξιά συντεταγμένη. Στη συνέχεια, ορίζει μια συνάρτηση `area` που υπολογίζει την περιοχή ενός ορθογωνίου από μια πάνω αριστερή και κάτω δεξιά συντεταγμένη.

    Έπειτα, ορίζει μια συνάρτηση `overlappingArea` που υπολογίζει την περιοχή επικάλυψης δύο ορθογωνίων. Αν δεν επικαλύπτονται, επιστρέφει 0.

1. Κάτω από τη συνάρτηση `overlappingArea`, δηλώστε μια συνάρτηση για να μετατρέψετε ένα οριοθετημένο πλαίσιο σε `Rect`:

    ```cpp
    Rect rectFromBoundingBox(JsonVariant prediction)
    {
        JsonObject bounding_box = prediction["boundingBox"].as<JsonObject>();
    
        float left = bounding_box["left"].as<float>();
        float top = bounding_box["top"].as<float>();
        float width = bounding_box["width"].as<float>();
        float height = bounding_box["height"].as<float>();
    
        Point topLeft = {left, top};
        Point bottomRight = {left + width, top + height};
    
        return {topLeft, bottomRight};
    }
    ```

    Αυτό παίρνει μια πρόβλεψη από τον ανιχνευτή αντικειμένων, εξάγει το οριοθετημένο πλαίσιο και χρησιμοποιεί τις τιμές του οριοθετημένου πλαισίου για να ορίσει ένα ορθογώνιο. Η δεξιά πλευρά υπολογίζεται από την αριστερή συν το πλάτος. Το κάτω μέρος υπολογίζεται ως το πάνω συν το ύψος.

1. Οι προβλέψεις πρέπει να συγκριθούν μεταξύ τους, και αν δύο προβλέψεις έχουν επικάλυψη μεγαλύτερη από το όριο, μία από αυτές πρέπει να διαγραφεί. Το όριο επικάλυψης είναι ένα ποσοστό, οπότε πρέπει να πολλαπλασιαστεί με το μέγεθος του μικρότερου οριοθετημένου πλαισίου για να ελεγχθεί αν η επικάλυψη υπερβαίνει το δεδομένο ποσοστό του οριοθετημένου πλαισίου, όχι το δεδομένο ποσοστό ολόκληρης της εικόνας. Ξεκινήστε διαγράφοντας το περιεχόμενο της συνάρτησης `processPredictions`.

1. Προσθέστε τα ακόλουθα στην κενή συνάρτηση `processPredictions`:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for (int i = 0; i < predictions.size(); ++i)
    {
        Rect prediction_1_rect = rectFromBoundingBox(predictions[i]);
        float prediction_1_area = area(prediction_1_rect);
        bool passed = true;

        for (int j = i + 1; j < predictions.size(); ++j)
        {
            Rect prediction_2_rect = rectFromBoundingBox(predictions[j]);
            float prediction_2_area = area(prediction_2_rect);

            float overlap = overlappingArea(prediction_1_rect, prediction_2_rect);
            float smallest_area = min(prediction_1_area, prediction_2_area);

            if (overlap > (overlap_threshold * smallest_area))
            {
                passed = false;
                break;
            }
        }

        if (passed)
        {
            passed_predictions.push_back(predictions[i]);
        }
    }
    ```

    Αυτός ο κώδικας δηλώνει έναν πίνακα για να αποθηκεύει τις προβλέψεις που δεν επικαλύπτονται. Στη συνέχεια, επαναλαμβάνει όλες τις προβλέψεις, δημιουργώντας ένα `Rect` από το οριοθετημένο πλαίσιο.

    Έπειτα, αυτός ο κώδικας επαναλαμβάνει τις υπόλοιπες προβλέψεις, ξεκινώντας από την επόμενη μετά την τρέχουσα πρόβλεψη. Αυτό σταματά τις προβλέψεις να συγκρίνονται περισσότερες από μία φορές - μόλις συγκριθούν οι 1 και 2, δεν υπάρχει ανάγκη να συγκριθεί η 2 με την 1, μόνο με την 3, 4, κ.λπ.

    Για κάθε ζεύγος προβλέψεων, υπολογίζεται η περιοχή επικάλυψης. Στη συνέχεια, συγκρίνεται με την περιοχή του μικρότερου οριοθετημένου πλαισίου - αν η επικάλυψη υπερβαίνει το ποσοστό ορίου του μικρότερου οριοθετημένου πλαισίου, η πρόβλεψη σημειώνεται ως μη αποδεκτή. Αν μετά τη σύγκριση όλων των επικαλύψεων, η πρόβλεψη περάσει τους ελέγχους, προστίθεται στη συλλογή `passed_predictions`.

    > 💁 Αυτός είναι ένας πολύ απλοϊκός τρόπος για να αφαιρέσετε επικαλύψεις, απλώς αφαιρώντας την πρώτη σε ένα ζεύγος επικαλυπτόμενων. Για κώδικα παραγωγής, θα θέλατε να προσθέσετε περισσότερη λογική εδώ, όπως να εξετάσετε τις επικαλύψεις μεταξύ πολλαπλών αντικειμένων ή αν ένα οριοθετημένο πλαίσιο περιέχεται από άλλο.

1. Μετά από αυτό, προσθέστε τον ακόλουθο κώδικα για να στείλετε λεπτομέρειες των αποδεκτών προβλέψεων στον σειριακό παρακολούθηση:

    ```cpp
    for(JsonVariant prediction : passed_predictions)
    {
        String boundingBox = prediction["boundingBox"].as<String>();
        String tag = prediction["tagName"].as<String>();
        float probability = prediction["probability"].as<float>();

        char buff[32];
        sprintf(buff, "%s:\t%.2f%%\t%s", tag.c_str(), probability * 100.0, boundingBox.c_str());
        Serial.println(buff);
    }
    ```

    Αυτός ο κώδικας επαναλαμβάνει τις αποδεκτές προβλέψεις και εκτυπώνει τις λεπτομέρειές τους στον σειριακό παρακολούθηση.

1. Κάτω από αυτό, προσθέστε κώδικα για να εκτυπώσετε τον αριθμό των μετρημένων αντικειμένων στον σειριακό παρακολούθηση:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Αυτό θα μπορούσε στη συνέχεια να σταλεί σε μια υπηρεσία IoT για να ειδοποιήσει αν τα επίπεδα αποθέματος είναι χαμηλά.

1. Ανεβάστε και εκτελέστε τον κώδικά σας. Στρέψτε την κάμερα σε αντικείμενα σε ένα ράφι και πατήστε το κουμπί C. Δοκιμάστε να προσαρμόσετε την τιμή `overlap_threshold` για να δείτε προβλέψεις να αγνοούνται.

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%  {"left":0.395631,"top":0.215897,"width":0.180768,"height":0.359364}
    tomato paste:   35.87%  {"left":0.378554,"top":0.583012,"width":0.14824,"height":0.359382}
    tomato paste:   34.11%  {"left":0.699024,"top":0.592617,"width":0.124411,"height":0.350456}
    tomato paste:   35.16%  {"left":0.513006,"top":0.647853,"width":0.187472,"height":0.325817}
    Counted 4 stock items.
    ```

> 💁 Μπορείτε να βρείτε αυτόν τον κώδικα στον φάκελο [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Το πρόγραμμα μέτρησης αποθέματος σας ήταν επιτυχές!

---

**Αποποίηση ευθύνης**:  
Αυτό το έγγραφο έχει μεταφραστεί χρησιμοποιώντας την υπηρεσία αυτόματης μετάφρασης [Co-op Translator](https://github.com/Azure/co-op-translator). Παρόλο που καταβάλλουμε προσπάθειες για ακρίβεια, παρακαλούμε να έχετε υπόψη ότι οι αυτοματοποιημένες μεταφράσεις ενδέχεται να περιέχουν σφάλματα ή ανακρίβειες. Το πρωτότυπο έγγραφο στη μητρική του γλώσσα θα πρέπει να θεωρείται η αυθεντική πηγή. Για κρίσιμες πληροφορίες, συνιστάται επαγγελματική ανθρώπινη μετάφραση. Δεν φέρουμε ευθύνη για τυχόν παρεξηγήσεις ή εσφαλμένες ερμηνείες που προκύπτουν από τη χρήση αυτής της μετάφρασης.