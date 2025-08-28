<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T08:37:27+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "bg"
}
-->
# Класифициране на изображение с помощта на IoT Edge базиран класификатор на изображения - Виртуален IoT хардуер и Raspberry Pi

В тази част на урока ще използвате класификатора на изображения, който работи на устройството IoT Edge.

## Използване на класификатора на IoT Edge

IoT устройството може да бъде пренасочено да използва класификатора на изображения на IoT Edge. URL адресът за класификатора на изображения е `http://<IP адрес или име>/image`, като замените `<IP адрес или име>` с IP адреса или хост името на компютъра, на който работи IoT Edge.

Python библиотеката за Custom Vision работи само с модели, хоствани в облака, а не с модели, хоствани на IoT Edge. Това означава, че ще трябва да използвате REST API, за да извикате класификатора.

### Задача - използване на класификатора на IoT Edge

1. Отворете проекта `fruit-quality-detector` в VS Code, ако вече не е отворен. Ако използвате виртуално IoT устройство, уверете се, че виртуалната среда е активирана.

1. Отворете файла `app.py` и премахнете импортите от `azure.cognitiveservices.vision.customvision.prediction` и `msrest.authentication`.

1. Добавете следния импорт в началото на файла:

    ```python
    import requests
    ```

1. Изтрийте целия код след запазването на изображението във файл, от `image_file.write(image.read())` до края на файла.

1. Добавете следния код в края на файла:

    ```python
    prediction_url = '<URL>'
    headers = {
        'Content-Type' : 'application/octet-stream'
    }
    image.seek(0)
    response = requests.post(prediction_url, headers=headers, data=image)
    results = response.json()
    
    for prediction in results['predictions']:
        print(f'{prediction["tagName"]}:\t{prediction["probability"] * 100:.2f}%')
    ```

    Заменете `<URL>` с URL адреса на вашия класификатор.

    Този код прави REST POST заявка към класификатора, като изпраща изображението като тяло на заявката. Резултатите се връщат като JSON, който се декодира, за да се отпечатат вероятностите.

1. Стартирайте кода си, като насочите камерата към някакъв плод, подходящ набор от изображения или плод, видим на вашата уеб камера, ако използвате виртуален IoT хардуер. Ще видите изхода в конзолата:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Можете да намерите този код в папката [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) или [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Вашата програма за класифициране на качеството на плодовете беше успешна!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.