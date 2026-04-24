# Класифікація зображення - Віртуальне IoT обладнання та Raspberry Pi

У цій частині уроку ви відправите зображення, зроблене камерою, до служби Custom Vision для його класифікації.

## Відправка зображень до Custom Vision

Сервіс Custom Vision має Python SDK, який можна використовувати для класифікації зображень.

### Завдання - відправка зображень до Custom Vision

1. Відкрийте папку `fruit-quality-detector` у VS Code. Якщо ви використовуєте віртуальний IoT пристрій, переконайтеся, що віртуальне середовище запущене в терміналі.

1. Python SDK для відправки зображень до Custom Vision доступний як пакет Pip. Встановіть його за допомогою наступної команди:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Додайте наступні імпорт-заяви на початку файлу `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Це додає деякі модулі з бібліотек Custom Vision: один для автентифікації за допомогою prediction key, а інший для надання класу клієнта прогнозування, який може викликати Custom Vision.

1. Додайте наступний код у кінець файлу:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Замініть `<prediction_url>` на URL, який ви скопіювали з діалогу *Prediction URL* раніше в цьому уроці. Замініть `<prediction key>` на prediction key, який ви скопіювали з того ж діалогу.

1. URL прогнозування, наданий у діалозі *Prediction URL*, призначений для використання при прямому виклику REST-ендпоінту. Python SDK використовує частини цього URL у різних місцях. Додайте наступний код, щоб розділити цей URL на необхідні частини:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Це розділяє URL, витягуючи ендпоінт `https://<location>.api.cognitive.microsoft.com`, ID проєкту та ім'я опублікованої ітерації.

1. Створіть об'єкт прогнозування для виконання прогнозу за допомогою наступного коду:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` обгортає prediction key. Вони використовуються для створення об'єкта клієнта прогнозування, який вказує на ендпоінт.

1. Відправте зображення до Custom Vision за допомогою наступного коду:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Це повертає зображення на початок, а потім відправляє його клієнту прогнозування.

1. Нарешті, відобразіть результати за допомогою наступного коду:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Це пройде через усі прогнози, які були повернуті, і відобразить їх у терміналі. Ймовірності, що повертаються, є числами з плаваючою комою від 0 до 1, де 0 означає 0% ймовірності відповідності тегу, а 1 — 100% ймовірності.

    > 💁 Класифікатори зображень повертають відсотки для всіх тегів, які були використані. Кожен тег матиме ймовірність того, що зображення відповідає цьому тегу.

1. Запустіть свій код, направивши камеру на якийсь фрукт, або використовуючи відповідний набір зображень, або фрукт, видимий на вашій веб-камері, якщо ви використовуєте віртуальне IoT обладнання. Ви побачите результат у консолі:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Ви зможете побачити зображення, яке було зроблено, а також ці значення на вкладці **Predictions** у Custom Vision.

    ![Банан у Custom Vision, передбачено стиглий на 56.8% і нестиглий на 43.1%](../../../../../translated_images/uk/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Ви можете знайти цей код у папці [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) або [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Ваша програма для класифікації якості фруктів була успішною!

---

**Відмова від відповідальності**:  
Цей документ було перекладено за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, зверніть увагу, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ мовою оригіналу слід вважати авторитетним джерелом. Для критично важливої інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникли внаслідок використання цього перекладу.