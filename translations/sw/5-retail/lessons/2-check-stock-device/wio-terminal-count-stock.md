<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-27T22:45:32+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "sw"
}
-->
# Hesabu Hisa Kutoka Kifaa chako cha IoT - Wio Terminal

Mchanganyiko wa utabiri na masanduku yao ya mipaka unaweza kutumika kuhesabu hisa kwenye picha.

## Hesabu Hisa

![Mikebe 4 ya tomato paste ikiwa na masanduku ya mipaka kuzunguka kila kebe](../../../../../translated_images/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.sw.jpg)

Kwenye picha iliyoonyeshwa hapo juu, masanduku ya mipaka yana mgongano mdogo. Ikiwa mgongano huu ungekuwa mkubwa zaidi, basi masanduku ya mipaka yanaweza kuonyesha kitu kimoja. Ili kuhesabu vitu kwa usahihi, unahitaji kupuuza masanduku yenye mgongano mkubwa.

### Kazi - hesabu hisa ukipuuza mgongano

1. Fungua mradi wako wa `stock-counter` ikiwa haujafunguliwa tayari.

1. Juu ya kazi ya `processPredictions`, ongeza msimbo ufuatao:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Hii inafafanua asilimia ya mgongano inayoruhusiwa kabla ya masanduku ya mipaka kuchukuliwa kama kitu kimoja. 0.20 inafafanua mgongano wa asilimia 20.

1. Chini ya hii, na juu ya kazi ya `processPredictions`, ongeza msimbo ufuatao ili kuhesabu mgongano kati ya miraba miwili:

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

    Msimbo huu unafafanua `Point` struct kuhifadhi pointi kwenye picha, na `Rect` struct kufafanua mstatili kwa kutumia kona ya juu kushoto na kona ya chini kulia. Kisha inafafanua kazi ya `area` inayohesabu eneo la mstatili kutoka kona ya juu kushoto na kona ya chini kulia.

    Kisha inafafanua kazi ya `overlappingArea` inayohesabu eneo la mgongano wa miraba miwili. Ikiwa hazigongani, inarudisha 0.

1. Chini ya kazi ya `overlappingArea`, tangaza kazi ya kubadilisha sanduku la mipaka kuwa `Rect`:

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

    Hii inachukua utabiri kutoka kwa kigunduzi cha vitu, inatoa sanduku la mipaka na kutumia thamani kwenye sanduku la mipaka kufafanua mstatili. Upande wa kulia unahesabiwa kutoka kushoto pamoja na upana. Chini inahesabiwa kama juu pamoja na urefu.

1. Utabiri unahitaji kulinganishwa kati yao, na ikiwa utabiri 2 una mgongano zaidi ya kizingiti, moja kati yao inapaswa kufutwa. Kizingiti cha mgongano ni asilimia, kwa hivyo kinahitaji kuzidishwa na ukubwa wa sanduku la mipaka dogo zaidi ili kuhakikisha kuwa mgongano unazidi asilimia iliyotolewa ya sanduku la mipaka, si asilimia iliyotolewa ya picha nzima. Anza kwa kufuta yaliyomo kwenye kazi ya `processPredictions`.

1. Ongeza yafuatayo kwenye kazi tupu ya `processPredictions`:

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

    Msimbo huu unatangaza vector kuhifadhi utabiri ambao haugongani. Kisha inazunguka kupitia utabiri wote, ikitengeneza `Rect` kutoka kwa sanduku la mipaka.

    Kisha msimbo huu unazunguka kupitia utabiri uliobaki, kuanzia ule baada ya utabiri wa sasa. Hii inazuia utabiri kulinganishwa zaidi ya mara moja - mara baada ya 1 na 2 kulinganishwa, hakuna haja ya kulinganisha 2 na 1, bali na 3, 4, nk.

    Kwa kila jozi la utabiri, eneo la mgongano linahesabiwa. Hii kisha inalinganishwa na eneo la sanduku la mipaka dogo zaidi - ikiwa mgongano unazidi asilimia ya kizingiti cha sanduku la mipaka dogo zaidi, utabiri unawekwa alama kama haujapita. Ikiwa baada ya kulinganisha mgongano wote, utabiri unapita ukaguzi, unaongezwa kwenye mkusanyiko wa `passed_predictions`.

    > 💁 Hii ni njia rahisi sana ya kuondoa migongano, kwa kufuta tu ya kwanza kwenye jozi inayogongana. Kwa msimbo wa uzalishaji, ungetaka kuweka mantiki zaidi hapa, kama kuzingatia migongano kati ya vitu vingi, au ikiwa sanduku moja la mipaka limejumuishwa na jingine.

1. Baada ya hii, ongeza msimbo ufuatao kutuma maelezo ya utabiri uliopitishwa kwenye serial monitor:

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

    Msimbo huu unazunguka kupitia utabiri uliopitishwa na kuchapisha maelezo yao kwenye serial monitor.

1. Chini ya hii, ongeza msimbo wa kuchapisha idadi ya vitu vilivyohesabiwa kwenye serial monitor:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Hii inaweza kisha kutumwa kwa huduma ya IoT ili kutoa tahadhari ikiwa viwango vya hisa viko chini.

1. Pakia na endesha msimbo wako. Elekeza kamera kwenye vitu kwenye rafu na bonyeza kitufe cha C. Jaribu kurekebisha thamani ya `overlap_threshold` ili kuona utabiri ukipuuzwa.

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

> 💁 Unaweza kupata msimbo huu kwenye folda ya [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Programu yako ya kuhesabu hisa imefanikiwa!

---

**Kanusho**:  
Hati hii imetafsiriwa kwa kutumia huduma ya tafsiri ya AI [Co-op Translator](https://github.com/Azure/co-op-translator). Ingawa tunajitahidi kuhakikisha usahihi, tafsiri za kiotomatiki zinaweza kuwa na makosa au kutokuwa sahihi. Hati ya asili katika lugha yake ya awali inapaswa kuchukuliwa kama chanzo cha mamlaka. Kwa taarifa muhimu, tafsiri ya kitaalamu ya binadamu inapendekezwa. Hatutawajibika kwa kutoelewana au tafsiri zisizo sahihi zinazotokana na matumizi ya tafsiri hii.