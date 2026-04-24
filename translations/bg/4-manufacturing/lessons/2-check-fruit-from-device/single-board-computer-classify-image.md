# Класифициране на изображение - Виртуален IoT хардуер и Raspberry Pi

В тази част от урока ще изпратите изображението, заснето от камерата, към услугата Custom Vision, за да го класифицирате.

## Изпращане на изображения към Custom Vision

Услугата Custom Vision разполага с Python SDK, който можете да използвате за класифициране на изображения.

### Задача - изпращане на изображения към Custom Vision

1. Отворете папката `fruit-quality-detector` в VS Code. Ако използвате виртуално IoT устройство, уверете се, че виртуалната среда е стартирана в терминала.

1. Python SDK за изпращане на изображения към Custom Vision е наличен като пакет за Pip. Инсталирайте го със следната команда:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Добавете следните import изявления в началото на файла `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Това включва някои модули от библиотеките на Custom Vision – един за удостоверяване с prediction ключа и един за предоставяне на клас клиент за предсказания, който може да извиква Custom Vision.

1. Добавете следния код в края на файла:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Заменете `<prediction_url>` с URL адреса, който копирахте от диалога *Prediction URL* по-рано в този урок. Заменете `<prediction key>` с prediction ключа, който също копирахте от същия диалог.

1. Prediction URL адресът, предоставен от диалога *Prediction URL*, е предназначен за директно извикване на REST endpoint. Python SDK използва части от URL адреса на различни места. Добавете следния код, за да разделите този URL на необходимите части:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Това разделя URL адреса, извличайки endpoint-а `https://<location>.api.cognitive.microsoft.com`, ID на проекта и името на публикуваната итерация.

1. Създайте predictor обект, за да извършите предсказанието със следния код:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` обгръща prediction ключа. Те след това се използват за създаване на обект клиент за предсказания, насочен към endpoint-а.

1. Изпратете изображението към Custom Vision със следния код:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Това връща изображението в началото, след което го изпраща към prediction клиента.

1. Накрая, покажете резултатите със следния код:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Това ще премине през всички предсказания, които са върнати, и ще ги покаже в терминала. Върнатите вероятности са числа с плаваща запетая от 0 до 1, където 0 е 0% вероятност за съвпадение с етикета, а 1 е 100% вероятност.

    > 💁 Класификаторите на изображения ще върнат процентите за всички етикети, които са били използвани. Всеки етикет ще има вероятност, че изображението съвпада с този етикет.

1. Стартирайте кода си, като насочите камерата към някакъв плод, подходящ набор от изображения или плод, видим на вашата уеб камера, ако използвате виртуален IoT хардуер. Ще видите изхода в конзолата:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Ще можете да видите заснетото изображение, както и тези стойности в таба **Predictions** в Custom Vision.

    ![Банан в Custom Vision, предсказан като узрял с 56.8% и неузрял с 43.1%](../../../../../translated_images/bg/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Можете да намерите този код в папката [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) или [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Вашата програма за класифициране на качеството на плодовете беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.