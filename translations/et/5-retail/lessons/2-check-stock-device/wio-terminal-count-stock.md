<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-10-11T12:48:31+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "et"
}
-->
# Loenda varusid oma IoT-seadmest - Wio Terminal

Ennustuste ja nende piirdekastide kombinatsiooni saab kasutada varude loendamiseks pildil.

## Varude loendamine

![4 tomatipasta purki, mille ümber on piirdekastid](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.et.jpg)

Ülaltoodud pildil on piirdekastid veidi kattuvad. Kui see kattumine oleks palju suurem, siis võivad piirdekastid viidata samale objektile. Objektide korrektseks loendamiseks tuleb ignoreerida kaste, mille kattumine on märkimisväärne.

### Ülesanne - loenda varusid ignoreerides kattumist

1. Ava oma `stock-counter` projekt, kui see pole juba avatud.

1. Lisa `processPredictions` funktsiooni kohale järgmine kood:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    See määratleb protsentuaalse kattumise, mille korral piirdekastid loetakse samaks objektiks. 0.20 määratleb 20% kattumise.

1. Selle alla ja `processPredictions` funktsiooni kohale lisa järgmine kood, et arvutada kahe ristküliku kattuvus:

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

    See kood määratleb `Point` struktuuri, et salvestada punkte pildil, ja `Rect` struktuuri, et määratleda ristkülik, kasutades ülemist vasakut ja alumist paremat koordinaati. Seejärel määratleb see `area` funktsiooni, mis arvutab ristküliku pindala ülemise vasaku ja alumise parema koordinaadi põhjal.

    Järgmisena määratleb see `overlappingArea` funktsiooni, mis arvutab kahe ristküliku kattuva ala. Kui need ei kattu, tagastab see 0.

1. Lisa `overlappingArea` funktsiooni alla funktsioon, mis teisendab piirdekasti `Rect`-iks:

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

    See võtab objekti detektori ennustuse, eraldab piirdekasti ja kasutab piirdekasti väärtusi ristküliku määratlemiseks. Parempoolne külg arvutatakse vasakust küljest pluss laius. Alumine külg arvutatakse ülemisest küljest pluss kõrgus.

1. Ennustusi tuleb omavahel võrrelda, ja kui kahel ennustusel on kattumine, mis ületab läve, tuleb üks neist kustutada. Kattumise lävi on protsent, seega tuleb see korrutada väikseima piirdekasti suurusega, et kontrollida, kas kattumine ületab antud protsendi piirdekastist, mitte kogu pildist. Alusta `processPredictions` funktsiooni sisu kustutamisega.

1. Lisa tühja `processPredictions` funktsiooni järgmine kood:

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

    See kood määratleb vektori, kuhu salvestatakse ennustused, mis ei kattu. Seejärel tsüklitakse läbi kõik ennustused, luues piirdekastist `Rect`.

    Järgmisena tsüklitakse läbi ülejäänud ennustused, alustades praeguse ennustuse järgmisest. See väldib ennustuste korduvat võrdlemist - kui 1 ja 2 on võrreldud, pole vaja võrrelda 2 ja 1, ainult 3, 4 jne.

    Iga ennustuste paari puhul arvutatakse kattuv ala. Seda võrreldakse väikseima piirdekasti pindalaga - kui kattumine ületab väikseima piirdekasti antud protsendi, märgitakse ennustus mitte läbituks. Kui pärast kõigi kattumiste võrdlemist ennustus läbib kontrollid, lisatakse see `passed_predictions` kogusse.

    > 💁 See on väga lihtsustatud viis kattumiste eemaldamiseks, lihtsalt eemaldades esimese kattuva paari. Tootmiskoodis tuleks siia lisada rohkem loogikat, näiteks arvestada mitme objekti kattumisi või kui üks piirdekast sisaldub teises.

1. Pärast seda lisa järgmine kood, et saata läbitud ennustuste üksikasjad seeriamonitorile:

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

    See kood tsüklitab läbi läbitud ennustused ja prindib nende üksikasjad seeriamonitorile.

1. Selle alla lisa kood, et prindida loendatud esemete arv seeriamonitorile:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    See võiks seejärel saata IoT-teenusele teate, kui varude tase on madal.

1. Laadi üles ja käivita oma kood. Suuna kaamera riiulil olevatele objektidele ja vajuta C-nuppu. Proovi muuta `overlap_threshold` väärtust, et näha, kuidas ennustusi ignoreeritakse.

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

> 💁 Selle koodi leiad kaustast [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Sinu varude loendamise programm oli edukas!

---

**Lahtiütlus**:  
See dokument on tõlgitud AI tõlketeenuse [Co-op Translator](https://github.com/Azure/co-op-translator) abil. Kuigi püüame tagada täpsust, palume arvestada, et automaatsed tõlked võivad sisaldada vigu või ebatäpsusi. Algne dokument selle algses keeles tuleks pidada autoriteetseks allikaks. Olulise teabe puhul soovitame kasutada professionaalset inimtõlget. Me ei vastuta arusaamatuste või valesti tõlgenduste eest, mis võivad tekkida selle tõlke kasutamise tõttu.