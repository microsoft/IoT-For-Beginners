<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T11:24:50+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "bg"
}
-->
# Свържете вашето IoT устройство с облака - Виртуален IoT хардуер и Raspberry Pi

В тази част от урока ще свържете вашето виртуално IoT устройство или Raspberry Pi към вашия IoT Hub, за да изпращате телеметрия и да получавате команди.

## Свържете устройството си към IoT Hub

Следващата стъпка е да свържете устройството си към IoT Hub.

### Задача - свързване към IoT Hub

1. Отворете папката `soil-moisture-sensor` в VS Code. Уверете се, че виртуалната среда работи в терминала, ако използвате виртуално IoT устройство.

1. Инсталирайте някои допълнителни Pip пакети:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` е библиотека за комуникация с вашия IoT Hub.

1. Добавете следните импорти в началото на файла `app.py`, под съществуващите импорти:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Този код импортира SDK за комуникация с вашия IoT Hub.

1. Премахнете реда `import paho.mqtt.client as mqtt`, тъй като тази библиотека вече не е необходима. Премахнете целия MQTT код, включително имената на темите, целия код, който използва `mqtt_client`, и `handle_command`. Запазете цикъла `while True:`, просто изтрийте реда `mqtt_client.publish` от този цикъл.

1. Добавете следния код под изявленията за импортиране:

    ```python
    connection_string = "<connection string>"
    ```

    Заменете `<connection string>` със стринга за връзка, който извлякохте за устройството по-рано в този урок.

    > 💁 Това не е най-добрата практика. Стринговете за връзка никога не трябва да се съхраняват в изходния код, тъй като могат да бъдат качени в система за контрол на версиите и намерени от всеки. Правим това тук заради простотата. Идеално би било да използвате нещо като променлива на средата и инструмент като [`python-dotenv`](https://pypi.org/project/python-dotenv/). Ще научите повече за това в предстоящ урок.

1. Под този код добавете следното, за да създадете обект за клиент на устройството, който може да комуникира с IoT Hub, и го свържете:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Стартирайте този код. Ще видите как устройството ви се свързва.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Изпращане на телеметрия

Сега, когато устройството ви е свързано, можете да изпращате телеметрия към IoT Hub вместо към MQTT брокера.

### Задача - изпращане на телеметрия

1. Добавете следния код вътре в цикъла `while True`, точно преди командата за пауза:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Този код създава IoT Hub `Message`, съдържащ показанията за влажност на почвата като JSON низ, след което го изпраща към IoT Hub като съобщение от устройство към облак.

## Обработка на команди

Вашето устройство трябва да обработва команда от сървърния код за управление на релето. Това се изпраща като заявка за директен метод.

## Задача - обработка на заявка за директен метод

1. Добавете следния код преди цикъла `while True`:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Това дефинира метод, `handle_method_request`, който ще бъде извикан, когато директен метод бъде извикан от IoT Hub. Всеки директен метод има име, и този код очаква метод, наречен `relay_on`, за да включи релето, и `relay_off`, за да го изключи.

    > 💁 Това може да бъде реализирано и в един директен метод, като се предаде желаното състояние на релето в полезен товар, който може да бъде предаден със заявката за метод и достъпен от обекта `request`.

1. Директните методи изискват отговор, за да информират извикващия код, че са били обработени. Добавете следния код в края на функцията `handle_method_request`, за да създадете отговор на заявката:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Този код изпраща отговор на заявката за директен метод с HTTP статус код 200 и го връща към IoT Hub.

1. Добавете следния код под дефиницията на тази функция:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Този код казва на клиента на IoT Hub да извика функцията `handle_method_request`, когато бъде извикан директен метод.

> 💁 Можете да намерите този код в папката [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) или [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Вашата програма за сензор за влажност на почвата е свързана с вашия IoT Hub!

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматизираните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия роден език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален човешки превод. Ние не носим отговорност за недоразумения или погрешни интерпретации, произтичащи от използването на този превод.