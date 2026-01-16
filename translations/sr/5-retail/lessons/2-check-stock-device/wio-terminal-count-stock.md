<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T14:30:15+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "sr"
}
-->
# Бројање залиха са вашег IoT уређаја - Wio Terminal

Комбинација предвиђања и њихових оквира може се користити за бројање залиха на слици.

## Бројање залиха

![4 конзерве парадајз пасте са оквирима око сваке конзерве](../../../../../translated_images/sr/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

На слици изнад, оквири се благо преклапају. Ако би то преклапање било много веће, оквири би могли указивати на исти објекат. Да бисте исправно избројали објекте, потребно је игнорисати оквире са значајним преклапањем.

### Задатак - бројање залиха игноришући преклапање

1. Отворите свој пројекат `stock-counter` ако већ није отворен.

1. Изнад функције `processPredictions`, додајте следећи код:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Ово дефинише дозвољени проценат преклапања пре него што се оквири сматрају истим објектом. 0.20 дефинише 20% преклапања.

1. Испод овога, а изнад функције `processPredictions`, додајте следећи код за израчунавање преклапања између два правоугаоника:

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

    Овај код дефинише структуру `Point` за чување тачака на слици и структуру `Rect` за дефинисање правоугаоника користећи горњу леву и доњу десну координату. Затим дефинише функцију `area` која израчунава површину правоугаоника на основу горње леве и доње десне координате.

    Након тога дефинише функцију `overlappingArea` која израчунава површину преклапања два правоугаоника. Ако се не преклапају, враћа 0.

1. Испод функције `overlappingArea`, декларишите функцију за конвертовање оквира у `Rect`:

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

    Ова функција узима предвиђање из детектора објеката, извлачи оквир и користи вредности из оквира за дефинисање правоугаоника. Десна страна се израчунава као лева плус ширина. Доња страна се израчунава као горња плус висина.

1. Потребно је упоредити предвиђања међусобно, и ако два предвиђања имају преклапање веће од прага, једно од њих треба избрисати. Праг преклапања је проценат, па га треба помножити са величином најмањег оквира да би се проверило да ли преклапање премашује дати проценат оквира, а не проценат целе слике. Почните брисањем садржаја функције `processPredictions`.

1. Додајте следеће у празну функцију `processPredictions`:

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

    Овај код декларише вектор за чување предвиђања која се не преклапају. Затим пролази кроз сва предвиђања, креирајући `Rect` из оквира.

    Након тога, овај код пролази кроз преостала предвиђања, почевши од оног након тренутног предвиђања. Ово спречава да се предвиђања упоређују више пута - када су 1 и 2 упоређени, нема потребе упоређивати 2 са 1, већ само са 3, 4 итд.

    За сваки пар предвиђања израчунава се површина преклапања. Ово се затим пореди са површином најмањег оквира - ако преклапање премашује праг процента најмањег оквира, предвиђање се означава као неуспешно. Ако након свих поређења предвиђање прође провере, додаје се у колекцију `passed_predictions`.

    > 💁 Ово је веома једноставан начин уклањања преклапања, само уклањањем првог у пару који се преклапа. За продукцијски код, било би пожељно додати више логике, као што је разматрање преклапања између више објеката или ако је један оквир садржан у другом.

1. Након овога, додајте следећи код за слање детаља о успешним предвиђањима на серијски монитор:

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

    Овај код пролази кроз успешна предвиђања и штампа њихове детаље на серијски монитор.

1. Испод овога, додајте код за штампање броја избројаних ставки на серијски монитор:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Ово би се затим могло послати IoT услузи како би се упозорило ако је ниво залиха низак.

1. Отпремите и покрените свој код. Уперите камеру ка објектима на полици и притисните дугме C. Пробајте да подесите вредност `overlap_threshold` да видите како се предвиђања игноришу.

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

> 💁 Овај код можете пронаћи у фасцикли [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Ваш програм за бројање залиха је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматизовани преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.