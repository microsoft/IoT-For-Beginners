<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T16:03:50+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "uk"
}
-->
# Класифікація зображення за допомогою класифікатора зображень на базі IoT Edge - Віртуальне IoT обладнання та Raspberry Pi

У цій частині уроку ви використовуватимете класифікатор зображень, який працює на пристрої IoT Edge.

## Використання класифікатора IoT Edge

Пристрій IoT можна перенаправити для використання класифікатора зображень IoT Edge. URL для класифікатора зображень — це `http://<IP address or name>/image`, де `<IP address or name>` потрібно замінити на IP-адресу або ім'я хоста комп'ютера, на якому працює IoT Edge.

Бібліотека Python для Custom Vision працює лише з моделями, розміщеними в хмарі, а не з моделями, розміщеними на IoT Edge. Це означає, що вам потрібно буде використовувати REST API для виклику класифікатора.

### Завдання - використання класифікатора IoT Edge

1. Відкрийте проєкт `fruit-quality-detector` у VS Code, якщо він ще не відкритий. Якщо ви використовуєте віртуальний IoT-пристрій, переконайтеся, що віртуальне середовище активоване.

1. Відкрийте файл `app.py` і видаліть імпорт із `azure.cognitiveservices.vision.customvision.prediction` та `msrest.authentication`.

1. Додайте наступний імпорт на початку файлу:

    ```python
    import requests
    ```

1. Видаліть увесь код після того, як зображення збережено у файл, починаючи з `image_file.write(image.read())` і до кінця файлу.

1. Додайте наступний код у кінець файлу:

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

    Замініть `<URL>` на URL вашого класифікатора.

    Цей код виконує REST POST-запит до класифікатора, надсилаючи зображення як тіло запиту. Результати повертаються у форматі JSON, який декодується для виведення ймовірностей.

1. Запустіть ваш код, направивши камеру на якийсь фрукт, відповідний набір зображень або фрукт, видимий на вашій вебкамері, якщо ви використовуєте віртуальне IoT обладнання. Ви побачите результат у консолі:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Ви можете знайти цей код у папці [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) або [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Ваше програмне забезпечення для класифікації якості фруктів працює успішно!

---

**Відмова від відповідальності**:  
Цей документ був перекладений за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критичної інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають внаслідок використання цього перекладу.