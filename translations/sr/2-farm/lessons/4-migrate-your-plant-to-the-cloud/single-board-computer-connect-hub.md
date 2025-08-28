<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-28T15:03:09+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "sr"
}
-->
# Повежите ваш IoT уређај са облаком - Виртуелни IoT хардвер и Raspberry Pi

У овом делу лекције, повезаћете ваш виртуелни IoT уређај или Raspberry Pi са вашим IoT Hub-ом, како бисте слали телеметрију и примали команде.

## Повежите ваш уређај са IoT Hub-ом

Следећи корак је да повежете ваш уређај са IoT Hub-ом.

### Задатак - повезивање са IoT Hub-ом

1. Отворите фасциклу `soil-moisture-sensor` у VS Code-у. Уверите се да је виртуелно окружење покренуто у терминалу ако користите виртуелни IoT уређај.

1. Инсталирајте додатне Pip пакете:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device` је библиотека за комуникацију са вашим IoT Hub-ом.

1. Додајте следеће увозе на врх датотеке `app.py`, испод постојећих увоза:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    Овај код увози SDK за комуникацију са вашим IoT Hub-ом.

1. Уклоните линију `import paho.mqtt.client as mqtt`, јер ова библиотека више није потребна. Уклоните сав MQTT код, укључујући називе тема, сав код који користи `mqtt_client` и `handle_command`. Задржите `while True:` петљу, само избришите линију `mqtt_client.publish` из ове петље.

1. Додајте следећи код испод увозних изјава:

    ```python
    connection_string = "<connection string>"
    ```

    Замените `<connection string>` са низом за повезивање који сте преузели за уређај раније у овој лекцији.

    > 💁 Ово није најбоља пракса. Низови за повезивање никада не би требало да се чувају у изворном коду, јер могу бити проверени у систем за контролу верзија и пронађени од стране било кога. Овде то радимо ради једноставности. Идеално би било да користите нешто попут променљиве окружења и алат као што је [`python-dotenv`](https://pypi.org/project/python-dotenv/). О овоме ћете више научити у наредној лекцији.

1. Испод овог кода, додајте следеће како бисте креирали објекат клијента уређаја који може комуницирати са IoT Hub-ом и повезати га:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. Покрените овај код. Видећете да се ваш уређај повезао.

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## Слање телеметрије

Сада када је ваш уређај повезан, можете слати телеметрију IoT Hub-у уместо MQTT брокеру.

### Задатак - слање телеметрије

1. Додајте следећи код унутар `while True` петље, непосредно пре паузе:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    Овај код креира IoT Hub `Message` који садржи очитавање влажности земљишта као JSON стринг, а затим га шаље IoT Hub-у као поруку од уређаја ка облаку.

## Обрада команди

Ваш уређај треба да обради команду са серверског кода за контролу релеја. Ово се шаље као захтев за директни метод.

## Задатак - обрада захтева за директни метод

1. Додајте следећи код пре `while True` петље:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    Ово дефинише метод, `handle_method_request`, који ће бити позван када IoT Hub позове директни метод. Сваки директни метод има назив, а овај код очекује метод назван `relay_on` за укључивање релеја и `relay_off` за искључивање релеја.

    > 💁 Ово би такође могло бити имплементирано у једном захтеву за директни метод, прослеђујући жељено стање релеја у payload-у који може бити прослеђен са захтевом за метод и доступан из објекта `request`.

1. Директни методи захтевају одговор како би обавестили позивајући код да су обрађени. Додајте следећи код на крај функције `handle_method_request` како бисте креирали одговор на захтев:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    Овај код шаље одговор на захтев за директни метод са HTTP статус кодом 200 и враћа га IoT Hub-у.

1. Додајте следећи код испод дефиниције ове функције:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    Овај код говори IoT Hub клијенту да позове функцију `handle_method_request` када се позове директни метод.

> 💁 Овај код можете пронаћи у фасцикли [code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi) или [code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device).

😀 Ваш програм за сензор влажности земљишта је повезан са вашим IoT Hub-ом!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.