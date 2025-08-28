<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "50151d9f9dce2801348a93880ef16d86",
  "translation_date": "2025-08-28T12:22:07+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/single-board-computer.md",
  "language_code": "sr"
}
-->
# Класификујте слику користећи класификатор слика заснован на IoT Edge - Виртуелни IoT хардвер и Raspberry Pi

У овом делу лекције, користићете класификатор слика који ради на IoT Edge уређају.

## Користите класификатор IoT Edge

IoT уређај може бити преусмерен да користи класификатор слика IoT Edge. URL за класификатор слика је `http://<IP адреса или име>/image`, где `<IP адреса или име>` треба заменити IP адресом или именом хоста рачунара на коме ради IoT Edge.

Python библиотека за Custom Vision ради само са моделима хостованим у облаку, а не са моделима хостованим на IoT Edge. То значи да ћете морати да користите REST API за позивање класификатора.

### Задатак - користите класификатор IoT Edge

1. Отворите пројекат `fruit-quality-detector` у VS Code ако већ није отворен. Ако користите виртуелни IoT уређај, уверите се да је виртуелно окружење активирано.

1. Отворите датотеку `app.py` и уклоните изјаве за увоз из `azure.cognitiveservices.vision.customvision.prediction` и `msrest.authentication`.

1. Додајте следећи увоз на врх датотеке:

    ```python
    import requests
    ```

1. Обришите сав код након што је слика сачувана у датотеку, од `image_file.write(image.read())` до краја датотеке.

1. Додајте следећи код на крај датотеке:

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

    Замените `<URL>` са URL-ом вашег класификатора.

    Овај код прави REST POST захтев класификатору, шаљући слику као тело захтева. Резултати се враћају као JSON, који се декодира да би се исписале вероватноће.

1. Покрените свој код, са камером усмереном на неко воће, или одговарајући сет слика, или воће видљиво на вашој веб камери ако користите виртуелни IoT хардвер. Видећете излаз у конзоли:

    ```output
    (.venv) ➜  fruit-quality-detector python app.py
    ripe:   56.84%
    unripe: 43.16%
    ```

> 💁 Овај код можете пронаћи у фасцикли [code-classify/pi](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/pi) или [code-classify/virtual-iot-device](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-classify/virtual-iot-device).

😀 Ваш програм за класификатор квалитета воћа је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.