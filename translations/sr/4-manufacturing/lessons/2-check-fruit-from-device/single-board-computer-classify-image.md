# Класификуј слику - Виртуелни IoT хардвер и Raspberry Pi

У овом делу лекције, послаћете слику снимљену камером на Custom Vision сервис ради класификације.

## Слање слика на Custom Vision

Custom Vision сервис има Python SDK који можете користити за класификацију слика.

### Задатак - слање слика на Custom Vision

1. Отворите фасциклу `fruit-quality-detector` у VS Code. Ако користите виртуелни IoT уређај, уверите се да је виртуелно окружење покренуто у терминалу.

1. Python SDK за слање слика на Custom Vision доступан је као Pip пакет. Инсталирајте га следећом командом:

    ```sh
    pip3 install azure-cognitiveservices-vision-customvision
    ```

1. Додајте следеће import изјаве на врх фајла `app.py`:

    ```python
    from msrest.authentication import ApiKeyCredentials
    from azure.cognitiveservices.vision.customvision.prediction import CustomVisionPredictionClient
    ```

    Ово укључује неке модуле из Custom Vision библиотека, један за аутентификацију са prediction key, и један за обезбеђивање prediction client класе која може позивати Custom Vision.

1. Додајте следећи код на крај фајла:

    ```python
    prediction_url = '<prediction_url>'
    prediction_key = '<prediction key>'
    ```

    Замените `<prediction_url>` са URL-ом који сте копирали из дијалога *Prediction URL* раније у овој лекцији. Замените `<prediction key>` са prediction key који сте копирали из истог дијалога.

1. Prediction URL који је обезбеђен у дијалогу *Prediction URL* дизајниран је за директно коришћење при позивању REST ендпоинта. Python SDK користи делове URL-а на различитим местима. Додајте следећи код да бисте раздвојили овај URL на потребне делове:

    ```python
    parts = prediction_url.split('/')
    endpoint = 'https://' + parts[2]
    project_id = parts[6]
    iteration_name = parts[9]
    ```

    Ово дели URL, извлачећи ендпоинт `https://<location>.api.cognitive.microsoft.com`, ID пројекта и име објављене итерације.

1. Направите predictor објекат за извршавање предвиђања помоћу следећег кода:

    ```python
    prediction_credentials = ApiKeyCredentials(in_headers={"Prediction-key": prediction_key})
    predictor = CustomVisionPredictionClient(endpoint, prediction_credentials)
    ```

    `prediction_credentials` обухватају prediction key. Они се затим користе за креирање prediction client објекта који показује на ендпоинт.

1. Пошаљите слику на Custom Vision користећи следећи код:

    ```python
    image.seek(0)
    results = predictor.classify_image(project_id, iteration_name, image)
    ```

    Ово враћа слику на почетак, а затим је шаље prediction client-у.

1. На крају, прикажите резултате помоћу следећег кода:

    ```python
    for prediction in results.predictions:
        print(f'{prediction.tag_name}:\t{prediction.probability * 100:.2f}%')
    ```

    Ово ће проћи кроз сва предвиђања која су враћена и приказати их у терминалу. Вероватноће које се враћају су бројеви са покретним зарезом од 0-1, где је 0 шанса од 0% да се подудара са ознаком, а 1 шанса од 100%.

    > 💁 Класификатори слика ће вратити проценат за све ознаке које су коришћене. Свака ознака ће имати вероватноћу да слика одговара тој ознаци.

1. Покрените свој код, са камером усмереном на неко воће, одговарајући сет слика, или воће видљиво на вашој веб камери ако користите виртуелни IoT хардвер. Видећете излаз у конзоли:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

    Моћи ћете да видите слику која је снимљена, као и ове вредности у картици **Predictions** у Custom Vision.

    ![Банана у Custom Vision предвиђена као зрела са 56.8% и незрела са 43.1%](../../../../../translated_images/sr/custom-vision-banana-prediction.30cdff4e1d72db5d.webp)

> 💁 Овај код можете пронаћи у фасцикли [code-classify/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/pi) или [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-classify/virtual-iot-device).

😀 Ваш програм за класификацију квалитета воћа је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати меродавним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.