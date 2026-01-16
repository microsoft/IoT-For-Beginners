<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T10:52:05+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ro"
}
-->
# Numără stocul cu dispozitivul tău IoT - Wio Terminal

O combinație între predicții și casetele de delimitare poate fi utilizată pentru a număra stocul dintr-o imagine.

## Numără stocul

![4 cutii de pastă de roșii cu casete de delimitare în jurul fiecărei cutii](../../../../../translated_images/ro/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.webp)

În imaginea de mai sus, casetele de delimitare au o mică suprapunere. Dacă această suprapunere ar fi fost mult mai mare, casetele de delimitare ar putea indica același obiect. Pentru a număra corect obiectele, trebuie să ignori casetele cu o suprapunere semnificativă.

### Sarcină - numără stocul ignorând suprapunerile

1. Deschide proiectul tău `stock-counter` dacă nu este deja deschis.

1. Deasupra funcției `processPredictions`, adaugă următorul cod:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Acesta definește procentul de suprapunere permis înainte ca casetele de delimitare să fie considerate același obiect. 0.20 definește o suprapunere de 20%.

1. Sub acest cod, și deasupra funcției `processPredictions`, adaugă următorul cod pentru a calcula suprapunerea dintre două dreptunghiuri:

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

    Acest cod definește o structură `Point` pentru a stoca punctele din imagine și o structură `Rect` pentru a defini un dreptunghi folosind coordonatele colțului stânga sus și colțului dreapta jos. Apoi definește o funcție `area` care calculează aria unui dreptunghi pe baza coordonatelor colțului stânga sus și colțului dreapta jos.

    În continuare, definește o funcție `overlappingArea` care calculează aria de suprapunere a 2 dreptunghiuri. Dacă acestea nu se suprapun, returnează 0.

1. Sub funcția `overlappingArea`, declară o funcție pentru a converti o casetă de delimitare într-un `Rect`:

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

    Aceasta preia o predicție de la detectorul de obiecte, extrage caseta de delimitare și folosește valorile acesteia pentru a defini un dreptunghi. Latura dreaptă este calculată din stânga plus lățimea. Partea de jos este calculată ca partea de sus plus înălțimea.

1. Predicțiile trebuie comparate între ele, iar dacă 2 predicții au o suprapunere mai mare decât pragul, una dintre ele trebuie eliminată. Pragul de suprapunere este un procent, așa că trebuie înmulțit cu dimensiunea celei mai mici casete de delimitare pentru a verifica dacă suprapunerea depășește procentul dat din caseta de delimitare, nu procentul dat din întreaga imagine. Începe prin a șterge conținutul funcției `processPredictions`.

1. Adaugă următorul cod în funcția goală `processPredictions`:

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

    Acest cod declară un vector pentru a stoca predicțiile care nu se suprapun. Apoi parcurge toate predicțiile, creând un `Rect` din caseta de delimitare.

    În continuare, acest cod parcurge predicțiile rămase, începând cu cea de după predicția curentă. Acest lucru împiedică predicțiile să fie comparate de mai multe ori - odată ce 1 și 2 au fost comparate, nu mai este nevoie să compari 2 cu 1, ci doar cu 3, 4 etc.

    Pentru fiecare pereche de predicții, se calculează aria de suprapunere. Aceasta este apoi comparată cu aria celei mai mici casete de delimitare - dacă suprapunerea depășește procentul pragului din cea mai mică casetă de delimitare, predicția este marcată ca nevalidă. Dacă, după compararea tuturor suprapunerilor, predicția trece verificările, aceasta este adăugată în colecția `passed_predictions`.

    > 💁 Acesta este un mod foarte simplist de a elimina suprapunerile, eliminând doar prima dintr-o pereche suprapusă. Pentru codul de producție, ar trebui să adaugi mai multă logică aici, cum ar fi luarea în considerare a suprapunerilor între mai multe obiecte sau dacă o casetă de delimitare este conținută de alta.

1. După aceasta, adaugă următorul cod pentru a trimite detalii despre predicțiile validate către monitorul serial:

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

    Acest cod parcurge predicțiile validate și le afișează detaliile pe monitorul serial.

1. Sub acest cod, adaugă cod pentru a afișa numărul de articole numărate pe monitorul serial:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Acest număr ar putea fi apoi trimis către un serviciu IoT pentru a alerta dacă nivelurile de stoc sunt scăzute.

1. Încarcă și rulează codul tău. Îndreaptă camera către obiectele de pe un raft și apasă butonul C. Încearcă să ajustezi valoarea `overlap_threshold` pentru a vedea cum predicțiile sunt ignorate.

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

> 💁 Poți găsi acest cod în folderul [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Programul tău de numărare a stocului a fost un succes!

---

**Declinare de responsabilitate**:  
Acest document a fost tradus folosind serviciul de traducere AI [Co-op Translator](https://github.com/Azure/co-op-translator). Deși ne străduim să asigurăm acuratețea, vă rugăm să rețineți că traducerile automate pot conține erori sau inexactități. Documentul original în limba sa natală ar trebui considerat sursa autoritară. Pentru informații critice, se recomandă traducerea profesională realizată de un specialist uman. Nu ne asumăm responsabilitatea pentru eventualele neînțelegeri sau interpretări greșite care pot apărea din utilizarea acestei traduceri.