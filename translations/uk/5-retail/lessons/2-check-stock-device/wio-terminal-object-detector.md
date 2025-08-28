<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-28T17:36:35+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "uk"
}
-->
# Виклик детектора об'єктів з вашого IoT-пристрою - Wio Terminal

Після того як ваш детектор об'єктів опубліковано, його можна використовувати з вашого IoT-пристрою.

## Скопіюйте проект класифікатора зображень

Більшість вашого детектора запасів схожа на класифікатор зображень, який ви створили в попередньому уроці.

### Завдання - скопіюйте проект класифікатора зображень

1. Підключіть вашу ArduCam до Wio Terminal, дотримуючись інструкцій з [уроку 2 виробничого проекту](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Ви також можете зафіксувати камеру в одному положенні, наприклад, перекинувши кабель через коробку або банку, або прикріпивши камеру до коробки за допомогою двостороннього скотчу.

1. Створіть абсолютно новий проект для Wio Terminal за допомогою PlatformIO. Назвіть цей проект `stock-counter`.

1. Повторіть кроки з [уроку 2 виробничого проекту](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) для захоплення зображень з камери.

1. Повторіть кроки з [уроку 2 виробничого проекту](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) для виклику класифікатора зображень. Більшість цього коду буде повторно використано для виявлення об'єктів.

## Змініть код з класифікатора на детектор зображень

Код, який ви використовували для класифікації зображень, дуже схожий на код для виявлення об'єктів. Основна відмінність полягає в URL, який ви отримали з Custom Vision, і результатах виклику.

### Завдання - змініть код з класифікатора на детектор зображень

1. Додайте наступну директиву включення на початку файлу `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Перейменуйте функцію `classifyImage` на `detectStock`, як назву функції, так і виклик у функції `buttonPressed`.

1. Над функцією `detectStock` оголосіть поріг для фільтрації будь-яких виявлень з низькою ймовірністю:

    ```cpp
    const float threshold = 0.3f;
    ```

    На відміну від класифікатора зображень, який повертає лише один результат для кожного тегу, детектор об'єктів повертає кілька результатів, тому будь-які з низькою ймовірністю потрібно відфільтрувати.

1. Над функцією `detectStock` оголосіть функцію для обробки прогнозів:

    ```cpp
    void processPredictions(std::vector<JsonVariant> &predictions)
    {
        for(JsonVariant prediction : predictions)
        {
            String tag = prediction["tagName"].as<String>();
            float probability = prediction["probability"].as<float>();
    
            char buff[32];
            sprintf(buff, "%s:\t%.2f%%", tag.c_str(), probability * 100.0);
            Serial.println(buff);
        }
    }
    ```

    Ця функція приймає список прогнозів і виводить їх на серійний монітор.

1. У функції `detectStock` замініть вміст циклу `for`, який перебирає прогнози, наступним:

    ```cpp
    std::vector<JsonVariant> passed_predictions;

    for(JsonVariant prediction : predictions) 
    {
        float probability = prediction["probability"].as<float>();
        if (probability > threshold)
        {
            passed_predictions.push_back(prediction);
        }
    }

    processPredictions(passed_predictions);
    ```

    Цей код перебирає прогнози, порівнюючи ймовірність з порогом. Усі прогнози з ймовірністю, вищою за поріг, додаються до `list` і передаються у функцію `processPredictions`.

1. Завантажте та запустіть ваш код. Наведіть камеру на об'єкти на полиці та натисніть кнопку C. Ви побачите результат на серійному моніторі:

    ```output
    Connecting to WiFi..
    Connected!
    Image captured
    Image read to buffer with length 17416
    tomato paste:   35.84%
    tomato paste:   35.87%
    tomato paste:   34.11%
    tomato paste:   35.16%
    ```

    > 💁 Можливо, вам доведеться налаштувати `threshold` на відповідне значення для ваших зображень.

    Ви зможете побачити зображення, яке було зроблено, а також ці значення у вкладці **Predictions** в Custom Vision.

    ![4 банки томатної пасти на полиці з прогнозами для 4 виявлень: 35.8%, 33.5%, 25.7% і 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.uk.png)

> 💁 Ви можете знайти цей код у папці [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Ваш програмний лічильник запасів успішно працює!

---

**Відмова від відповідальності**:  
Цей документ було перекладено за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, зверніть увагу, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ мовою оригіналу слід вважати авторитетним джерелом. Для критично важливої інформації рекомендується професійний переклад людиною. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникли внаслідок використання цього перекладу.