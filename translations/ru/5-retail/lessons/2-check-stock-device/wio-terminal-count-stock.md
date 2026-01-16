<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-26T21:33:11+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "ru"
}
-->
# Подсчет запасов с вашего IoT-устройства - Wio Terminal

Сочетание предсказаний и их ограничивающих рамок можно использовать для подсчета запасов на изображении.

## Подсчет запасов

![4 банки томатной пасты с ограничивающими рамками вокруг каждой банки](../../../../../translated_images/ru/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

На изображении выше ограничивающие рамки немного перекрываются. Если бы это перекрытие было значительно больше, рамки могли бы указывать на один и тот же объект. Чтобы правильно подсчитать объекты, необходимо игнорировать рамки с существенным перекрытием.

### Задача - подсчет запасов с игнорированием перекрытий

1. Откройте ваш проект `stock-counter`, если он еще не открыт.

1. Над функцией `processPredictions` добавьте следующий код:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Это определяет процент перекрытия, допустимый до того, как ограничивающие рамки будут считаться одним и тем же объектом. Значение 0.20 задает 20% перекрытия.

1. Ниже этого, но все еще над функцией `processPredictions`, добавьте следующий код для вычисления перекрытия между двумя прямоугольниками:

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

    Этот код определяет структуру `Point` для хранения точек на изображении и структуру `Rect` для определения прямоугольника с использованием координат верхнего левого и нижнего правого углов. Затем он определяет функцию `area`, которая вычисляет площадь прямоугольника на основе этих координат.

    Далее определяется функция `overlappingArea`, которая вычисляет площадь перекрытия двух прямоугольников. Если они не перекрываются, возвращается 0.

1. Под функцией `overlappingArea` объявите функцию для преобразования ограничивающей рамки в `Rect`:

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

    Эта функция берет предсказание от детектора объектов, извлекает ограничивающую рамку и использует ее значения для определения прямоугольника. Правая сторона рассчитывается как сумма левой стороны и ширины. Нижняя сторона рассчитывается как сумма верхней стороны и высоты.

1. Предсказания нужно сравнить друг с другом, и если два предсказания имеют перекрытие больше порогового значения, одно из них нужно удалить. Порог перекрытия задается в процентах, поэтому его нужно умножить на размер меньшей ограничивающей рамки, чтобы проверить, превышает ли перекрытие заданный процент от рамки, а не от всего изображения. Начните с удаления содержимого функции `processPredictions`.

1. Добавьте следующее в пустую функцию `processPredictions`:

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

    Этот код объявляет вектор для хранения предсказаний, которые не перекрываются. Затем он проходит по всем предсказаниям, создавая `Rect` из ограничивающей рамки.

    Далее код проходит по оставшимся предсказаниям, начиная с того, что идет после текущего. Это предотвращает повторное сравнение предсказаний — после того как 1 и 2 были сравнены, нет необходимости сравнивать 2 с 1, только с 3, 4 и так далее.

    Для каждой пары предсказаний вычисляется площадь перекрытия. Затем она сравнивается с площадью меньшей ограничивающей рамки — если перекрытие превышает пороговый процент от меньшей рамки, предсказание помечается как не прошедшее. Если после всех проверок предсказание проходит, оно добавляется в коллекцию `passed_predictions`.

    > 💁 Это очень упрощенный способ удаления перекрытий, просто удаляющий первое из двух перекрывающихся предсказаний. Для производственного кода вы могли бы добавить больше логики, например, учитывать перекрытия между несколькими объектами или случаи, когда одна рамка полностью содержится в другой.

1. После этого добавьте следующий код для отправки деталей прошедших предсказаний в монитор последовательного порта:

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

    Этот код проходит по прошедшим предсказаниям и выводит их детали в монитор последовательного порта.

1. Ниже этого добавьте код для вывода количества подсчитанных объектов в монитор последовательного порта:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Это значение затем можно отправить в IoT-сервис для оповещения о низком уровне запасов.

1. Загрузите и запустите ваш код. Направьте камеру на объекты на полке и нажмите кнопку C. Попробуйте изменить значение `overlap_threshold`, чтобы увидеть, как предсказания игнорируются.

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

> 💁 Вы можете найти этот код в папке [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Ваше приложение для подсчета запасов успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникающие в результате использования данного перевода.