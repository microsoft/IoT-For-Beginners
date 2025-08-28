<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-28T12:39:28+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "sr"
}
-->
# Претварање текста у говор - Виртуелни IoT уређај

У овом делу лекције, написаћете код за претварање текста у говор користећи услугу за говор.

## Претварање текста у говор

SDK за услуге говора који сте користили у претходној лекцији за претварање говора у текст може се користити за претварање текста назад у говор. Приликом захтева за говор, потребно је да наведете глас који ће се користити, јер се говор може генерисати користећи различите гласове.

Сваки језик подржава низ различитих гласова, а листу подржаних гласова за сваки језик можете добити из SDK-а за услуге говора.

### Задатак - претварање текста у говор

1. Отворите пројекат `smart-timer` у VS Code-у и уверите се да је виртуелно окружење учитано у терминалу.

1. Увезите `SpeechSynthesizer` из пакета `azure.cognitiveservices.speech` додавањем у постојеће увозе:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Изнад функције `say`, направите конфигурацију за говор коју ћете користити са синтетизатором говора:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Ово користи исти API кључ, локацију и језик који је користио препознавач.

1. Испод овога, додајте следећи код за добијање гласа и постављање на конфигурацију за говор:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Ово преузима листу свих доступних гласова, а затим проналази први глас који одговара језику који се користи.

    > 💁 Комплетну листу подржаних гласова можете добити из [документације о подршци за језик и глас на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Ако желите да користите одређени глас, можете уклонити ову функцију и ручно унети име гласа из документације. На пример:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Ажурирајте садржај функције `say` да генерише SSML за одговор:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Испод овога, зауставите препознавање говора, изговорите SSML, а затим поново покрените препознавање:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Препознавање се зауставља док се текст изговара како би се избегло да се најављивање покретања тајмера детектује, пошаље LUIS-у и евентуално протумачи као захтев за постављање новог тајмера.

    > 💁 Ово можете тестирати тако што ћете закоментарисати линије за заустављање и поновно покретање препознавања. Поставите један тајмер, и можда ћете приметити да најављивање поставља нови тајмер, што узрокује нову најаву, која води до новог тајмера, и тако у недоглед!

1. Покрените апликацију и уверите се да функцијска апликација такође ради. Поставите неке тајмере, и чућете говорни одговор који каже да је ваш тајмер постављен, а затим други говорни одговор када тајмер истекне.

> 💁 Овај код можете пронаћи у [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) фасцикли.

😀 Ваш програм за тајмер је био успешан!

---

**Одрицање од одговорности**:  
Овај документ је преведен коришћењем услуге за превођење помоћу вештачке интелигенције [Co-op Translator](https://github.com/Azure/co-op-translator). Иако се трудимо да обезбедимо тачност, молимо вас да имате у виду да аутоматски преводи могу садржати грешке или нетачности. Оригинални документ на његовом изворном језику треба сматрати ауторитативним извором. За критичне информације препоручује се професионални превод од стране људи. Не преузимамо одговорност за било каква погрешна тумачења или неспоразуме који могу настати услед коришћења овог превода.