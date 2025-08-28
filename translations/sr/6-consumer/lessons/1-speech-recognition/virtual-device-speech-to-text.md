<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-28T12:54:30+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "sr"
}
-->
# Претварање говора у текст - Виртуелни IoT уређај

У овом делу лекције, написаћете код за претварање говора снимљеног са вашег микрофона у текст користећи услугу за обраду говора.

## Претварање говора у текст

На Windows, Linux и macOS оперативним системима, Python SDK за услуге обраде говора може се користити за слушање вашег микрофона и претварање сваког детектованог говора у текст. SDK ће континуирано слушати, детектовати нивое звука и слати говор на претварање у текст када ниво звука опадне, на пример на крају блока говора.

### Задатак - претварање говора у текст

1. Направите нову Python апликацију на вашем рачунару у фасцикли названој `smart-timer` са једним фајлом названим `app.py` и Python виртуелним окружењем.

1. Инсталирајте Pip пакет за услуге обраде говора. Уверите се да ово радите из терминала са активираним виртуелним окружењем.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Ако добијете следећу грешку:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Мораћете да ажурирате Pip. Урадите то помоћу следеће команде, а затим покушајте поново да инсталирате пакет.
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Додајте следеће увозе у `app.py` фајл:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Ово увози неке класе које се користе за препознавање говора.

1. Додајте следећи код за декларацију конфигурације:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Замените `<key>` са API кључем за вашу услугу обраде говора. Замените `<location>` са локацијом коју сте користили приликом креирања ресурса за услугу обраде говора.

    Замените `<language>` са именом локала за језик на којем ћете говорити, на пример `en-GB` за енглески или `zn-HK` за кантонски. Листу подржаних језика и њихових локала можете пронаћи у [документацији о подршци за језике и гласове на Microsoft docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ова конфигурација се затим користи за креирање `SpeechConfig` објекта који ће се користити за конфигурисање услуга обраде говора.

1. Додајте следећи код за креирање препознавача говора:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Препознавач говора ради на позадинском thread-у, слушајући аудио и претварајући сваки говор у текст. Текст можете добити помоћу callback функције - функције коју дефинишете и прослеђујете препознавачу. Сваки пут када се детектује говор, позива се callback. Додајте следећи код за дефинисање callback функције и прослеђивање ове функције препознавачу, као и дефинисање функције за обраду текста, која ће га исписивати на конзолу:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Препознавач почиње да слуша само када га експлицитно покренете. Додајте следећи код за покретање препознавања. Ово се извршава у позадини, па ће ваша апликација такође захтевати бесконачну петљу која спава како би апликација остала активна.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Покрените ову апликацију. Говорите у ваш микрофон и аудио претворен у текст ће бити исписан на конзолу.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Испробајте различите типове реченица, као и реченице где речи звуче исто, али имају различита значења. На пример, ако говорите на енглеском, реците 'I want to buy two bananas and an apple too', и приметите како ће користити исправне to, two и too на основу контекста речи, а не само њиховог звука.

> 💁 Овај код можете пронаћи у [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device) фасцикли.

😀 Ваш програм за претварање говора у текст је успешно завршен!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да превод буде тачан, молимо вас да имате у виду да аутоматизовани преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.