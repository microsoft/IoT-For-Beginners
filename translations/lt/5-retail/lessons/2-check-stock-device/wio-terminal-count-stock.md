<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T20:17:15+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "lt"
}
-->
# Skaičiuokite atsargas iš savo IoT įrenginio - Wio Terminal

Prognozių ir jų ribinių dėžių derinys gali būti naudojamas atsargoms skaičiuoti vaizde.

## Atsargų skaičiavimas

![4 pomidorų pastos skardinės su ribinėmis dėžėmis aplink kiekvieną skardinę](../../../../../translated_images/lt/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

Pateiktame paveikslėlyje ribinės dėžės šiek tiek persidengia. Jei šis persidengimas būtų daug didesnis, ribinės dėžės galėtų nurodyti tą patį objektą. Norint teisingai suskaičiuoti objektus, reikia ignoruoti dėžes su reikšmingu persidengimu.

### Užduotis - skaičiuoti atsargas ignoruojant persidengimą

1. Atidarykite savo `stock-counter` projektą, jei jis dar neatidarytas.

1. Virš `processPredictions` funkcijos pridėkite šį kodą:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Tai apibrėžia leistiną persidengimo procentą, po kurio ribinės dėžės laikomos tuo pačiu objektu. 0.20 apibrėžia 20% persidengimą.

1. Po to, virš `processPredictions` funkcijos, pridėkite šį kodą, kad apskaičiuotumėte persidengimą tarp dviejų stačiakampių:

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

    Šis kodas apibrėžia `Point` struktūrą, skirtą taškams vaizde saugoti, ir `Rect` struktūrą, skirtą stačiakampiui apibrėžti naudojant viršutinį kairįjį ir apatinį dešinįjį koordinatą. Tada jis apibrėžia `area` funkciją, kuri apskaičiuoja stačiakampio plotą pagal viršutinį kairįjį ir apatinį dešinįjį koordinatą.

    Toliau apibrėžiama `overlappingArea` funkcija, kuri apskaičiuoja persidengimo plotą tarp 2 stačiakampių. Jei jie nesusikerta, grąžinama 0.

1. Po `overlappingArea` funkcijos deklaruokite funkciją, kuri konvertuoja ribinę dėžę į `Rect`:

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

    Ši funkcija paima prognozę iš objektų detektoriaus, ištraukia ribinę dėžę ir naudoja jos reikšmes stačiakampiui apibrėžti. Dešinė pusė apskaičiuojama kaip kairė plius plotis. Apačia apskaičiuojama kaip viršus plius aukštis.

1. Prognozės turi būti lyginamos tarpusavyje, ir jei 2 prognozės turi persidengimą, viršijantį nustatytą ribą, viena iš jų turi būti pašalinta. Persidengimo riba yra procentas, todėl ji turi būti padauginta iš mažiausios ribinės dėžės dydžio, kad būtų patikrinta, ar persidengimas viršija nurodytą ribinės dėžės procentą, o ne viso vaizdo procentą. Pradėkite ištrindami `processPredictions` funkcijos turinį.

1. Pridėkite šį kodą į tuščią `processPredictions` funkciją:

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

    Šis kodas deklaruoja vektorių, skirtą saugoti prognozes, kurios nesusikerta. Tada jis pereina per visas prognozes, sukuriant `Rect` iš ribinės dėžės.

    Toliau šis kodas pereina per likusias prognozes, pradedant nuo tos, kuri yra po dabartinės prognozės. Tai sustabdo prognozių lyginimą daugiau nei vieną kartą - kai 1 ir 2 buvo palygintos, nereikia lyginti 2 su 1, tik su 3, 4 ir t.t.

    Kiekvienai prognozių porai apskaičiuojamas persidengimo plotas. Tada jis lyginamas su mažiausios ribinės dėžės plotu - jei persidengimas viršija nustatytą ribos procentą mažiausios ribinės dėžės, prognozė pažymima kaip nepriimta. Jei po visų persidengimų palyginimo prognozė praeina patikrinimus, ji pridedama prie `passed_predictions` kolekcijos.

    > 💁 Tai labai paprastas būdas pašalinti persidengimus, tiesiog pašalinant pirmąją iš persidengiančios poros. Produkcijos kode norėtumėte pridėti daugiau logikos, pavyzdžiui, atsižvelgti į persidengimus tarp kelių objektų arba jei viena ribinė dėžė yra kitos ribose.

1. Po to pridėkite šį kodą, kad išsiųstumėte priimtų prognozių detales į serijinį monitorių:

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

    Šis kodas pereina per priimtas prognozes ir spausdina jų detales į serijinį monitorių.

1. Po to pridėkite kodą, kad išspausdintumėte suskaičiuotų objektų skaičių į serijinį monitorių:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Tai galėtų būti siunčiama į IoT paslaugą, kad būtų pranešta, jei atsargų lygis yra žemas.

1. Įkelkite ir paleiskite savo kodą. Nukreipkite kamerą į objektus lentynoje ir paspauskite C mygtuką. Pabandykite koreguoti `overlap_threshold` reikšmę, kad pamatytumėte ignoruojamas prognozes.

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

> 💁 Šį kodą galite rasti [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal) aplanke.

😀 Jūsų atsargų skaičiavimo programa buvo sėkminga!

---

**Atsakomybės atsisakymas**:  
Šis dokumentas buvo išverstas naudojant AI vertimo paslaugą [Co-op Translator](https://github.com/Azure/co-op-translator). Nors siekiame tikslumo, prašome atkreipti dėmesį, kad automatiniai vertimai gali turėti klaidų ar netikslumų. Originalus dokumentas jo gimtąja kalba turėtų būti laikomas autoritetingu šaltiniu. Kritinei informacijai rekomenduojama naudoti profesionalų žmogaus vertimą. Mes neprisiimame atsakomybės už nesusipratimus ar klaidingus interpretavimus, atsiradusius dėl šio vertimo naudojimo.