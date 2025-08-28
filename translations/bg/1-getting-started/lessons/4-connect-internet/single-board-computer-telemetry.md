<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T10:13:12+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "bg"
}
-->
# Контролирайте нощната си лампа през Интернет - Виртуален IoT хардуер и Raspberry Pi

В тази част на урока ще изпратите телеметрия със стойности на светлината от вашия Raspberry Pi или виртуално IoT устройство към MQTT брокер.

## Изпращане на телеметрия

Следващата стъпка е да създадете JSON документ с телеметрия и да го изпратите към MQTT брокера.

### Задача

Изпратете телеметрия към MQTT брокера.

1. Отворете проекта за нощната лампа в VS Code.

1. Ако използвате виртуално IoT устройство, уверете се, че терминалът работи във виртуалната среда. Ако използвате Raspberry Pi, няма да използвате виртуална среда.

1. Добавете следния импорт в началото на файла `app.py`:

    ```python
    import json
    ```

    Библиотеката `json` се използва за кодиране на телеметрията като JSON документ.

1. Добавете следното след декларацията на `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` е MQTT темата, към която устройството ще изпраща стойностите на светлината.

1. Заменете съдържанието на цикъла `while True:` в края на файла със следното:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Този код пакетира стойността на светлината в JSON документ и я изпраща към MQTT брокера. След това прави пауза, за да намали честотата на изпращане на съобщения.

1. Стартирайте кода по същия начин, както стартирахте кода от предишната част на задачата. Ако използвате виртуално IoT устройство, уверете се, че приложението CounterFit работи и че светлинният сензор и LED са създадени на правилните пинове.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Можете да намерите този код в папката [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) или в папката [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi).

😀 Успешно изпратихте телеметрия от вашето устройство.

---

**Отказ от отговорност**:  
Този документ е преведен с помощта на AI услуга за превод [Co-op Translator](https://github.com/Azure/co-op-translator). Въпреки че се стремим към точност, моля, имайте предвид, че автоматичните преводи може да съдържат грешки или неточности. Оригиналният документ на неговия изходен език трябва да се счита за авторитетен източник. За критична информация се препоръчва професионален превод от човек. Ние не носим отговорност за каквито и да е недоразумения или погрешни интерпретации, произтичащи от използването на този превод.