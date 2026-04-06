# Классификация изображения - Виртуальное IoT-устройство и Raspberry Pi

В этой части урока вы отправите изображение, снятое камерой, в службу Custom Vision для его классификации.

## Отправка изображений в Custom Vision

Служба Custom Vision имеет Python SDK, который можно использовать для классификации изображений.

### Задание - отправка изображений в Custom Vision

1. Откройте папку `fruit-quality-detector` в VS Code. Если вы используете виртуальное IoT-устройство, убедитесь, что виртуальная среда запущена в терминале.

1. Python SDK для отправки изображений в Custom Vision доступен как пакет Pip. Установите его с помощью следующей команды:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Добавьте следующие инструкции импорта в начало файла `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Это подключает некоторые модули из библиотек Custom Vision: один для аутентификации с использованием ключа предсказания, а другой для предоставления класса клиента предсказаний, который может вызывать Custom Vision.

1. Добавьте следующий код в конец файла:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Замените `<prediction_url>` на URL, который вы скопировали из диалогового окна *Prediction URL* ранее в этом уроке. Замените `<prediction key>` на ключ предсказания, который вы скопировали из того же диалогового окна.

1. URL предсказания, предоставленный в диалоговом окне *Prediction URL*, предназначен для использования при прямом вызове REST-эндпоинта. Python SDK использует части этого URL в разных местах. Добавьте следующий код, чтобы разделить этот URL на необходимые части:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Это разделяет URL, извлекая конечную точку `https://<location>.api.cognitive.microsoft.com`, идентификатор проекта и имя опубликованной итерации.

1. Создайте объект предсказателя для выполнения предсказания с помощью следующего кода:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` оборачивает ключ предсказания. Эти данные затем используются для создания объекта клиента предсказаний, указывающего на конечную точку.

1. Отправьте изображение в Custom Vision с помощью следующего кода:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Этот код перематывает изображение обратно к началу, а затем отправляет его клиенту предсказаний.

1. Наконец, отобразите результаты с помощью следующего кода:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Этот код перебирает все возвращенные предсказания и отображает их в терминале. Вероятности возвращаются в виде чисел с плавающей точкой от 0 до 1, где 0 означает 0% вероятность соответствия тегу, а 1 — 100% вероятность.

    > 💁 Классификаторы изображений возвращают проценты для всех использованных тегов. Каждый тег будет иметь вероятность того, что изображение соответствует этому тегу.

1. Запустите ваш код, направив камеру на какой-либо фрукт, подходящий набор изображений или фрукт, видимый на вашей веб-камере, если вы используете виртуальное IoT-устройство. Вы увидите вывод в консоли:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Вы сможете увидеть сделанное изображение, а также эти значения на вкладке **Predictions** в Custom Vision.

    ![Банан в Custom Vision, предсказано: спелый - 56.8%, неспелый - 43.1%](../../../../../translated_images/ru/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Этот код можно найти в папке [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) или [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Ваше приложение для классификации качества фруктов успешно завершено!

---

**Отказ от ответственности**:  
Этот документ был переведен с использованием сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, пожалуйста, учитывайте, что автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.