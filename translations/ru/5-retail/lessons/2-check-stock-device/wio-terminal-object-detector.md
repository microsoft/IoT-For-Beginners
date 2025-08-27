<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4cf1421420a6fab9ab4f2c391bd523b7",
  "translation_date": "2025-08-26T21:35:51+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/wio-terminal-object-detector.md",
  "language_code": "ru"
}
-->
# Вызов детектора объектов с вашего IoT-устройства - Wio Terminal

После публикации вашего детектора объектов его можно использовать с вашего IoT-устройства.

## Скопируйте проект классификатора изображений

Большая часть вашего детектора объектов аналогична классификатору изображений, который вы создали в предыдущем уроке.

### Задача - скопируйте проект классификатора изображений

1. Подключите вашу ArduCam к Wio Terminal, следуя шагам из [урока 2 проекта по производству](../../../4-manufacturing/lessons/2-check-fruit-from-device/wio-terminal-camera.md#task---connect-the-camera).

    Вы также можете зафиксировать камеру в одном положении, например, подвесив кабель над коробкой или банкой, либо прикрепив камеру к коробке с помощью двустороннего скотча.

1. Создайте новый проект для Wio Terminal с использованием PlatformIO. Назовите этот проект `stock-counter`.

1. Повторите шаги из [урока 2 проекта по производству](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---capture-an-image-using-an-iot-device) для захвата изображений с камеры.

1. Повторите шаги из [урока 2 проекта по производству](../../../4-manufacturing/lessons/2-check-fruit-from-device/README.md#task---classify-images-from-your-iot-device) для вызова классификатора изображений. Большая часть этого кода будет использована для обнаружения объектов.

## Измените код с классификатора на детектор изображений

Код, который вы использовали для классификации изображений, очень похож на код для обнаружения объектов. Основное отличие заключается в URL, который вы получили из Custom Vision, и результатах вызова.

### Задача - измените код с классификатора на детектор изображений

1. Добавьте следующий директиву include в начало файла `main.cpp`:

    ```cpp
    #include <vector>
    ```

1. Переименуйте функцию `classifyImage` в `detectStock`, изменив как название функции, так и вызов в функции `buttonPressed`.

1. Над функцией `detectStock` объявите пороговое значение для фильтрации любых обнаружений с низкой вероятностью:

    ```cpp
    const float threshold = 0.3f;
    ```

    В отличие от классификатора изображений, который возвращает только один результат на тег, детектор объектов возвращает несколько результатов, поэтому те, у которых низкая вероятность, нужно отфильтровать.

1. Над функцией `detectStock` объявите функцию для обработки предсказаний:

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

    Эта функция принимает список предсказаний и выводит их в монитор последовательного порта.

1. В функции `detectStock` замените содержимое цикла `for`, который проходит по предсказаниям, следующим кодом:

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

    Этот код проходит по предсказаниям, сравнивая вероятность с пороговым значением. Все предсказания с вероятностью выше порога добавляются в `list` и передаются в функцию `processPredictions`.

1. Загрузите и запустите ваш код. Направьте камеру на объекты на полке и нажмите кнопку C. Вы увидите вывод в мониторе последовательного порта:

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

    > 💁 Возможно, вам потребуется настроить значение `threshold` для ваших изображений.

    Вы сможете увидеть изображение, которое было сделано, а также эти значения на вкладке **Predictions** в Custom Vision.

    ![4 банки томатной пасты на полке с предсказаниями для 4 обнаружений: 35.8%, 33.5%, 25.7% и 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.ru.png)

> 💁 Вы можете найти этот код в папке [code-detect/wio-terminal](../../../../../5-retail/lessons/2-check-stock-device/code-detect/wio-terminal).

😀 Ваше приложение для подсчета запасов успешно завершено!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Хотя мы стремимся к точности, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникающие в результате использования данного перевода.