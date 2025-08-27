<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-26T22:03:52+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "ru"
}
-->
# Классификация изображения с использованием классификатора изображений на базе IoT Edge - Виртуальное IoT оборудование и Raspberry Pi

В этой части урока вы будете использовать классификатор изображений, работающий на устройстве IoT Edge.

## Использование классификатора IoT Edge

Устройство IoT можно перенаправить на использование классификатора изображений IoT Edge. URL для классификатора изображений: `http://<IP address or name>/image`, заменив `<IP address or name>` на IP-адрес или имя хоста компьютера, на котором работает IoT Edge.

Библиотека Python для Custom Vision работает только с моделями, размещенными в облаке, а не с моделями, размещенными на IoT Edge. Это означает, что вам нужно будет использовать REST API для вызова классификатора.

### Задача - использование классификатора IoT Edge

1. Откройте проект `fruit-quality-detector` в VS Code, если он еще не открыт. Если вы используете виртуальное устройство IoT, убедитесь, что виртуальная среда активирована.

1. Откройте файл `app.py` и удалите инструкции импорта из `azure.cognitiveservices.vision.customvision.prediction` и `msrest.authentication`.

1. Добавьте следующий импорт в начало файла:

    ```python
    import requests
    ```

1. Удалите весь код после сохранения изображения в файл, начиная с `image_file.write(image.read())` и до конца файла.

1. Добавьте следующий код в конец файла:

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

    Замените `<URL>` на URL вашего классификатора.

    Этот код выполняет REST POST запрос к классификатору, отправляя изображение в теле запроса. Результаты возвращаются в формате JSON, который декодируется для вывода вероятностей.

1. Запустите ваш код, направив камеру на какой-либо фрукт, подходящий набор изображений или фрукт, видимый на вашей веб-камере, если вы используете виртуальное IoT оборудование. Вы увидите вывод в консоли:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Этот код можно найти в папке [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) или [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Программа классификатора качества фруктов успешно выполнена!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его родном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникающие в результате использования данного перевода.