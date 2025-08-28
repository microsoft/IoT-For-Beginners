<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-28T13:51:47+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "sr"
}
-->
# Контролишите своје ноћно светло преко интернета - Виртуелни IoT хардвер и Raspberry Pi

У овом делу лекције, послаћете телеметрију са нивоима светлости са вашег Raspberry Pi уређаја или виртуелног IoT уређаја на MQTT брокер.

## Објављивање телеметрије

Следећи корак је креирање JSON документа са телеметријом и његово слање на MQTT брокер.

### Задатак

Објавите телеметрију на MQTT брокеру.

1. Отворите пројекат ноћног светла у VS Code-у.

1. Ако користите виртуелни IoT уређај, уверите се да је терминал покренут у виртуелном окружењу. Ако користите Raspberry Pi, нећете користити виртуелно окружење.

1. Додајте следећи импорт на врх `app.py` датотеке:

    ```python
    import json
    ```

    Библиотека `json` се користи за кодирање телеметрије као JSON документа.

1. Додајте следеће након декларације `client_name`:

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` је MQTT тема на коју ће уређај објављивати нивое светлости.

1. Замените садржај `while True:` петље на крају датотеке следећим:

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    Овај код пакује ниво светлости у JSON документ и објављује га на MQTT брокеру. Затим прави паузу како би смањио учесталост слања порука.

1. Покрените код на исти начин као што сте покренули код из претходног дела задатка. Ако користите виртуелни IoT уређај, уверите се да је CounterFit апликација покренута и да су сензор светлости и LED креирани на одговарајућим пиновима.

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 Овај код можете пронаћи у [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) фасцикли или у [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) фасцикли.

😀 Успешно сте послали телеметрију са свог уређаја.

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматизовани преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.