<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T10:52:24+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "bg"
}
-->
# Броене на наличности от вашето IoT устройство - Wio Terminal

Комбинация от прогнозите и техните ограничителни рамки може да се използва за броене на наличности в изображение.

## Броене на наличности

![4 консерви доматено пюре с ограничителни рамки около всяка консервa](../../../../../translated_images/bg/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

На изображението по-горе ограничителните рамки имат малко припокриване. Ако това припокриване беше много по-голямо, тогава рамките може да показват един и същ обект. За да преброите обектите правилно, трябва да игнорирате рамки със значително припокриване.

### Задача - броене на наличности, игнорирайки припокриването

1. Отворете вашия проект `stock-counter`, ако вече не е отворен.

1. Над функцията `processPredictions` добавете следния код:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Това определя процента на припокриване, който е допустим, преди ограничителните рамки да се считат за един и същ обект. 0.20 определя 20% припокриване.

1. Под това, и над функцията `processPredictions`, добавете следния код за изчисляване на припокриването между два правоъгълника:

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

    Този код дефинира структура `Point` за съхраняване на точки върху изображението и структура `Rect` за дефиниране на правоъгълник чрез горен ляв и долен десен координат. След това дефинира функция `area`, която изчислява площта на правоъгълник от горен ляв и долен десен координат.

    След това дефинира функция `overlappingArea`, която изчислява припокриващата се площ на два правоъгълника. Ако те не се припокриват, връща 0.

1. Под функцията `overlappingArea` декларирайте функция за преобразуване на ограничителна рамка в `Rect`:

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

    Това взема прогноза от детектора на обекти, извлича ограничителната рамка и използва стойностите на рамката за дефиниране на правоъгълник. Дясната страна се изчислява като лявата плюс ширината. Долната страна се изчислява като горната плюс височината.

1. Прогнозите трябва да бъдат сравнени една с друга, и ако две прогнози имат припокриване, което надвишава прага, една от тях трябва да бъде изтрита. Прагът за припокриване е процент, така че трябва да бъде умножен по размера на най-малката ограничителна рамка, за да се провери дали припокриването надвишава дадения процент от рамката, а не дадения процент от цялото изображение. Започнете, като изтриете съдържанието на функцията `processPredictions`.

1. Добавете следното към празната функция `processPredictions`:

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

    Този код декларира вектор за съхраняване на прогнозите, които не се припокриват. След това преминава през всички прогнози, създавайки `Rect` от ограничителната рамка.

    След това този код преминава през останалите прогнози, започвайки от тази след текущата прогноза. Това предотвратява сравняването на прогнози повече от веднъж - след като 1 и 2 са сравнени, няма нужда да се сравнява 2 с 1, само с 3, 4 и т.н.

    За всяка двойка прогнози се изчислява припокриващата се площ. След това тя се сравнява с площта на най-малката ограничителна рамка - ако припокриването надвишава прага като процент от най-малката рамка, прогнозата се маркира като неуспешна. Ако след сравняване на всички припокривания прогнозата премине проверките, тя се добавя към колекцията `passed_predictions`.

    > 💁 Това е много опростен начин за премахване на припокривания, просто премахвайки първата в припокриваща се двойка. За производствен код бихте искали да добавите повече логика тук, като например разглеждане на припокриванията между множество обекти или ако една ограничителна рамка е съдържана в друга.

1. След това добавете следния код за изпращане на детайли за успешните прогнози към серийния монитор:

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

    Този код преминава през успешните прогнози и отпечатва техните детайли на серийния монитор.

1. Под това добавете код за отпечатване на броя на преброените обекти на серийния монитор:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Това може да бъде изпратено към IoT услуга, за да се сигнализира, ако нивата на наличностите са ниски.

1. Качете и стартирайте вашия код. Насочете камерата към обекти на рафт и натиснете бутон C. Опитайте да регулирате стойността на `overlap_threshold`, за да видите как прогнозите се игнорират.

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

> 💁 Можете да намерите този код в папката [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Вашата програма за броене на наличности беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.