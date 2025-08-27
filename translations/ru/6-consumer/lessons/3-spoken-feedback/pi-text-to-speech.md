<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T00:12:25+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ru"
}
-->
# Текст в речь - Raspberry Pi

В этой части урока вы напишете код для преобразования текста в речь с использованием службы распознавания речи.

## Преобразование текста в речь с использованием службы распознавания речи

Текст можно отправить в службу распознавания речи через REST API, чтобы получить речь в виде аудиофайла, который можно воспроизвести на вашем IoT-устройстве. При запросе речи необходимо указать голос, так как речь может быть сгенерирована с использованием различных голосов.

Каждый язык поддерживает множество различных голосов, и вы можете сделать REST-запрос к службе распознавания речи, чтобы получить список поддерживаемых голосов для каждого языка.

### Задача - получить голос

1. Откройте проект `smart-timer` в VS Code.

1. Добавьте следующий код выше функции `say`, чтобы запросить список голосов для языка:

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    Этот код определяет функцию `get_voice`, которая использует службу распознавания речи для получения списка голосов. Затем он находит первый голос, соответствующий используемому языку.

    Эта функция вызывается для сохранения первого голоса, а имя голоса выводится в консоль. Этот голос можно запросить один раз, а затем использовать его значение для каждого вызова преобразования текста в речь.

    > 💁 Вы можете получить полный список поддерживаемых голосов из [документации о поддержке языков и голосов на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Если вы хотите использовать конкретный голос, вы можете удалить эту функцию и жестко прописать имя голоса из этой документации. Например:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Задача - преобразовать текст в речь

1. Ниже этого определите константу для формата аудио, которое будет получено из службы распознавания речи. При запросе аудио вы можете выбрать один из множества форматов.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Формат, который вы можете использовать, зависит от вашего оборудования. Если вы получаете ошибки `Invalid sample rate` при воспроизведении аудио, измените это значение на другое. Список поддерживаемых значений можно найти в [документации REST API для преобразования текста в речь на Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Вам нужно использовать аудио в формате `riff`, а значения, которые стоит попробовать, это `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` и `riff-48khz-16bit-mono-pcm`.

1. Ниже этого объявите функцию `get_speech`, которая будет преобразовывать текст в речь с использованием REST API службы распознавания речи:

    ```python
    def get_speech(text):
    ```

1. В функции `get_speech` определите URL для вызова и заголовки для передачи:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    Здесь задаются заголовки для использования сгенерированного токена доступа, устанавливается контент в формате SSML и определяется необходимый аудиоформат.

1. Ниже этого определите SSML для отправки в REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Этот SSML задает язык и голос для использования, а также текст для преобразования.

1. Наконец, добавьте код в эту функцию для выполнения REST-запроса и возврата бинарных аудиоданных:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Задача - воспроизвести аудио

1. Ниже функции `get_speech` определите новую функцию для воспроизведения аудио, возвращенного REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech`, переданный в эту функцию, будет бинарными аудиоданными, возвращенными из REST API. Используйте следующий код, чтобы открыть это как wave-файл и передать его в PyAudio для воспроизведения:

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    Этот код использует поток PyAudio, аналогично захвату аудио. Разница в том, что поток здесь настроен как выходной, а данные читаются из аудиофайла и передаются в поток.

    Вместо жесткого кодирования деталей потока, таких как частота дискретизации, они считываются из аудиоданных.

1. Замените содержимое функции `say` следующим:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Этот код преобразует текст в речь в виде бинарных аудиоданных и воспроизводит аудио.

1. Запустите приложение и убедитесь, что функция приложения также работает. Установите несколько таймеров, и вы услышите голосовой ответ, сообщающий, что ваш таймер установлен, а затем другой голосовой ответ, когда таймер завершится.

    Если вы получаете ошибки `Invalid sample rate`, измените `playback_format`, как описано выше.

> 💁 Вы можете найти этот код в папке [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Ваше приложение таймера успешно работает!

---

**Отказ от ответственности**:  
Этот документ был переведен с помощью сервиса автоматического перевода [Co-op Translator](https://github.com/Azure/co-op-translator). Несмотря на наши усилия обеспечить точность, автоматические переводы могут содержать ошибки или неточности. Оригинальный документ на его исходном языке следует считать авторитетным источником. Для получения критически важной информации рекомендуется профессиональный перевод человеком. Мы не несем ответственности за любые недоразумения или неправильные интерпретации, возникшие в результате использования данного перевода.