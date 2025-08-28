<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T18:03:33+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "uk"
}
-->
# Підключіть ваш IoT-пристрій до хмари - Віртуальне IoT обладнання та Raspberry Pi

У цій частині уроку ви підключите ваш віртуальний IoT-пристрій або Raspberry Pi до IoT Hub, щоб надсилати телеметрію та отримувати команди.

## Підключіть ваш пристрій до IoT Hub

Наступний крок — підключити ваш пристрій до IoT Hub.

### Завдання - підключення до IoT Hub

1. Відкрийте папку `soil-moisture-sensor` у VS Code. Переконайтеся, що віртуальне середовище запущене в терміналі, якщо ви використовуєте віртуальний IoT-пристрій.

1. Встановіть кілька додаткових пакетів Pip:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` — це бібліотека для зв’язку з вашим IoT Hub.

1. Додайте наступні імпорти на початок файлу `app.py`, нижче існуючих імпортів:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Цей код імпортує SDK для зв’язку з вашим IoT Hub.

1. Видаліть рядок `import paho.mqtt.client as mqtt`, оскільки ця бібліотека більше не потрібна. Видаліть весь код MQTT, включаючи назви тем, весь код, який використовує `mqtt_client`, і `handle_command`. Залиште цикл `while True:`, просто видаліть рядок `mqtt_client.publish` з цього циклу.

1. Додайте наступний код нижче імпортів:

    ```python
    connection_string = "<connection string>"
    ```

    Замініть `<connection string>` на рядок підключення, який ви отримали для пристрою раніше в цьому уроці.

    > 💁 Це не найкраща практика. Рядки підключення ніколи не слід зберігати в вихідному коді, оскільки їх можна додати до системи контролю версій і знайти будь-хто. Ми робимо це тут для простоти. Ідеально було б використовувати щось на кшталт змінної середовища та інструмент, як [`python-dotenv`](https://pypi.org/project/python-dotenv/). Ви дізнаєтеся більше про це в наступному уроці.

1. Нижче цього коду додайте наступне, щоб створити об’єкт клієнта пристрою, який може спілкуватися з IoT Hub, і підключіть його:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Запустіть цей код. Ви побачите, як ваш пристрій підключається.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Надсилання телеметрії

Тепер, коли ваш пристрій підключений, ви можете надсилати телеметрію до IoT Hub замість брокера MQTT.

### Завдання - надсилання телеметрії

1. Додайте наступний код всередині циклу `while True`, прямо перед `sleep`:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Цей код створює IoT Hub `Message`, що містить показник вологості ґрунту у вигляді JSON-рядка, а потім надсилає його до IoT Hub як повідомлення від пристрою до хмари.

## Обробка команд

Ваш пристрій має обробляти команду від серверного коду для керування реле. Це надсилається як запит прямого методу.

## Завдання - обробка запиту прямого методу

1. Додайте наступний код перед циклом `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Це визначає метод `handle_method_request`, який буде викликаний, коли IoT Hub викликає прямий метод. Кожен прямий метод має назву, і цей код очікує методи з назвою `relay_on` для увімкнення реле та `relay_off` для вимкнення реле.

    > 💁 Це також можна реалізувати в одному запиті прямого методу, передаючи бажаний стан реле в корисному навантаженні, яке можна передати з запитом методу та отримати з об’єкта `request`.

1. Прямі методи вимагають відповіді, щоб повідомити викликаючий код, що вони були оброблені. Додайте наступний код в кінці функції `handle_method_request`, щоб створити відповідь на запит:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Цей код надсилає відповідь на запит прямого методу з HTTP-статусом 200 і повертає її до IoT Hub.

1. Додайте наступний код нижче визначення цієї функції:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Цей код повідомляє клієнту IoT Hub викликати функцію `handle_method_request`, коли викликається прямий метод.

> 💁 Ви можете знайти цей код у папці [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) або [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Ваша програма датчика вологості ґрунту підключена до вашого IoT Hub!

---

**Відмова від відповідальності**:  
Цей документ було перекладено за допомогою сервісу автоматичного перекладу [Co-op Translator](https://github.com/Azure/co-op-translator). Хоча ми прагнемо до точності, будь ласка, майте на увазі, що автоматичні переклади можуть містити помилки або неточності. Оригінальний документ на його рідній мові слід вважати авторитетним джерелом. Для критично важливої інформації рекомендується професійний людський переклад. Ми не несемо відповідальності за будь-які непорозуміння або неправильні тлумачення, що виникають у результаті використання цього перекладу.