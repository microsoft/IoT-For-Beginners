<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "0b2ae20b0fc8e73c9598dea937cac038",
  "translation_date": "2025-08-28T17:38:11+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-count-stock.md",
  "language_code": "uk"
}
-->
# Підрахунок запасів за допомогою вашого IoT-пристрою - Wio Terminal

Поєднання прогнозів і їхніх обмежувальних рамок можна використовувати для підрахунку запасів на зображенні.

## Підрахунок запасів

![4 банки томатної пасти з обмежувальними рамками навколо кожної банки](../../../../../translated_images/uk/rpi-stock-with-bounding-boxes.b5540e2ecb7cd49f.jpg)

На зображенні, показаному вище, обмежувальні рамки мають невелике перекриття. Якщо це перекриття було б значно більшим, то рамки могли б вказувати на той самий об'єкт. Щоб правильно підрахувати об'єкти, потрібно ігнорувати рамки з суттєвим перекриттям.

### Завдання - підрахунок запасів з ігноруванням перекриття

1. Відкрийте ваш проєкт `stock-counter`, якщо він ще не відкритий.

1. Над функцією `processPredictions` додайте наступний код:

    ```cpp
    const float overlap_threshold = 0.20f;
    ```

    Це визначає відсоток перекриття, який дозволяється, перш ніж обмежувальні рамки вважаються одним і тим самим об'єктом. 0.20 визначає 20% перекриття.

1. Нижче цього, і над функцією `processPredictions`, додайте наступний код для обчислення перекриття між двома прямокутниками:

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

    Цей код визначає структуру `Point` для зберігання точок на зображенні та структуру `Rect` для визначення прямокутника за допомогою верхньої лівої та нижньої правої координат. Потім визначається функція `area`, яка обчислює площу прямокутника за верхньою лівою та нижньою правою координатами.

    Далі визначається функція `overlappingArea`, яка обчислює площу перекриття двох прямокутників. Якщо вони не перекриваються, вона повертає 0.

1. Нижче функції `overlappingArea` оголосіть функцію для перетворення обмежувальної рамки в `Rect`:

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

    Ця функція бере прогноз з детектора об'єктів, витягує обмежувальну рамку і використовує значення рамки для визначення прямокутника. Права сторона обчислюється як ліва плюс ширина. Нижня сторона обчислюється як верхня плюс висота.

1. Прогнози потрібно порівняти між собою, і якщо два прогнози мають перекриття більше за порогове значення, один із них потрібно видалити. Порогове значення перекриття є відсотком, тому його потрібно помножити на розмір найменшої обмежувальної рамки, щоб перевірити, чи перевищує перекриття заданий відсоток рамки, а не відсоток усього зображення. Почніть із видалення вмісту функції `processPredictions`.

1. Додайте наступне до порожньої функції `processPredictions`:

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

    Цей код оголошує вектор для зберігання прогнозів, які не перекриваються. Потім він перебирає всі прогнози, створюючи `Rect` з обмежувальної рамки.

    Далі цей код перебирає решту прогнозів, починаючи з наступного після поточного. Це запобігає повторному порівнянню прогнозів - після порівняння 1 і 2 немає потреби порівнювати 2 з 1, лише з 3, 4 тощо.

    Для кожної пари прогнозів обчислюється площа перекриття. Потім це значення порівнюється з площею найменшої обмежувальної рамки - якщо перекриття перевищує пороговий відсоток найменшої рамки, прогноз позначається як такий, що не пройшов. Якщо після перевірки всіх перекриттів прогноз проходить перевірки, він додається до колекції `passed_predictions`.

    > 💁 Це дуже простий спосіб видалення перекриттів, просто видаляючи перший у парі, що перекривається. Для виробничого коду ви б хотіли додати більше логіки, наприклад, враховувати перекриття між кількома об'єктами або якщо одна обмежувальна рамка міститься в іншій.

1. Після цього додайте наступний код для відправки деталей прогнозів, що пройшли, до серійного монітора:

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

    Цей код перебирає прогнози, що пройшли, і виводить їхні деталі на серійний монітор.

1. Нижче цього додайте код для виведення кількості підрахованих об'єктів на серійний монітор:

    ```cpp
    Serial.print("Counted ");
    Serial.print(passed_predictions.size());
    Serial.println(" stock items.");
    ```

    Це потім можна відправити до IoT-сервісу для сповіщення про низький рівень запасів.

1. Завантажте та запустіть ваш код. Наведіть камеру на об'єкти на полиці та натисніть кнопку C. Спробуйте змінити значення `overlap_threshold`, щоб побачити, як прогнози ігноруються.

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

> 💁 Ви можете знайти цей код у папці [code-count/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-count/wio-terminal).

😀 Ваш проєкт підрахунку запасів був успішним!

---

**Відмова від відповідальності**:  
Цей документ було перекладено за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, зверніть увагу, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ мовою оригіналу слід вважати авторитетним джерелом. Для критично важливої інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникли внаслідок використання цього перекладу.