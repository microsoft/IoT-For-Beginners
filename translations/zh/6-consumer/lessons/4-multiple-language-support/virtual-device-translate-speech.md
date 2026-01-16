<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-24T23:55:44+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "zh"
}
-->
# 翻译语音 - 虚拟物联网设备

在本课的这一部分中，您将编写代码，在使用语音服务将语音转换为文本时进行翻译，然后使用翻译服务将文本翻译为目标语言，最后生成语音响应。

## 使用语音服务翻译语音

语音服务不仅可以将语音转换为同一语言的文本，还可以将输出翻译为其他语言。

### 任务 - 使用语音服务翻译语音

1. 在 VS Code 中打开 `smart-timer` 项目，并确保虚拟环境已在终端中加载。

1. 在现有的导入语句下添加以下导入语句：

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    这将导入用于翻译语音的类，以及稍后在本课中调用翻译服务时需要用到的 `requests` 库。

1. 您的智能计时器将设置两种语言：用于训练 LUIS 的服务器语言（同样用于构建与用户交流的消息）和用户使用的语言。将 `language` 变量更新为用户将使用的语言，并添加一个名为 `server_language` 的新变量，用于表示训练 LUIS 时使用的语言：

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    将 `<user language>` 替换为您将使用的语言的区域设置名称，例如法语为 `fr-FR`，粤语为 `zh-HK`。

    将 `<server language>` 替换为训练 LUIS 时使用的语言的区域设置名称。

    您可以在 [Microsoft 文档上的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的语言及其区域设置名称的列表。

    > 💁 如果您不会多种语言，可以使用 [必应翻译](https://www.bing.com/translator) 或 [谷歌翻译](https://translate.google.com) 等服务将您的首选语言翻译为其他语言。这些服务还可以播放翻译文本的音频。请注意，语音识别器会忽略设备的一些音频输出，因此您可能需要使用额外的设备播放翻译文本。
    >
    > 例如，如果您用英语训练 LUIS，但希望用户语言为法语，您可以使用必应翻译将诸如“设置一个2分27秒的计时器”这样的句子从英语翻译为法语，然后使用**收听翻译**按钮将翻译内容通过麦克风输入。
    >
    > ![必应翻译上的收听翻译按钮](../../../../../translated_images/zh/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. 替换 `recognizer_config` 和 `recognizer` 的声明，使用以下内容：

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    这将创建一个翻译配置，用于识别用户语言中的语音，并生成用户语言和服务器语言的翻译。然后，它使用此配置创建一个翻译识别器——一个可以将语音识别输出翻译为多种语言的语音识别器。

    > 💁 必须在 `target_languages` 中指定原始语言，否则您将无法获得任何翻译。

1. 更新 `recognized` 函数，用以下内容替换函数的全部内容：

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    此代码检查触发的识别事件是否是由于语音被翻译（此事件也可能在其他情况下触发，例如语音被识别但未翻译）。如果语音被翻译，它会在 `args.result.translations` 字典中找到与服务器语言匹配的翻译。

    `args.result.translations` 字典的键是区域设置的语言部分，而不是整个设置。例如，如果您请求将法语 `fr-FR` 的翻译，字典中将包含 `fr` 的条目，而不是 `fr-FR`。

    翻译后的文本将被发送到 IoT Hub。

1. 运行代码测试翻译功能。确保您的函数应用正在运行，并用用户语言请求一个计时器，可以自己用该语言说话，也可以使用翻译应用。

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## 使用翻译服务翻译文本

语音服务不支持将翻译后的文本转换回语音，因此您可以使用翻译服务来翻译文本。该服务提供了一个 REST API，您可以用来翻译文本。

### 任务 - 使用翻译资源翻译文本

1. 在 `speech_api_key` 下添加翻译 API 密钥：

    ```python
    translator_api_key = '<key>'
    ```

    将 `<key>` 替换为您的翻译服务资源的 API 密钥。

1. 在 `say` 函数上方定义一个 `translate_text` 函数，用于将文本从服务器语言翻译为用户语言：

    ```python
    def translate_text(text):
    ```

1. 在此函数中定义 REST API 调用的 URL 和头信息：

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    此 API 的 URL 并非特定于位置，而是通过头信息传递位置。API 密钥直接使用，因此与语音服务不同，无需从令牌颁发 API 获取访问令牌。

1. 在此之下定义调用的参数和请求体：

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` 定义了传递给 API 调用的参数，指定源语言和目标语言。此调用将把 `from` 语言的文本翻译为 `to` 语言。

    `body` 包含要翻译的文本。这是一个数组，因为在一次调用中可以翻译多个文本块。

1. 调用 REST API 并获取响应：

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    返回的响应是一个 JSON 数组，其中包含一个项目，该项目包含所有传入文本块的翻译结果。

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. 返回数组中第一个项目的第一个翻译的 `text` 属性：

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. 更新 `say` 函数，在生成 SSML 之前翻译要说的文本：

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    此代码还会将原始文本和翻译文本打印到控制台。

1. 运行代码。确保您的函数应用正在运行，并用用户语言请求一个计时器，可以自己用该语言说话，也可以使用翻译应用。

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 由于不同语言表达方式的差异，您可能会得到与您提供给 LUIS 的示例略有不同的翻译。如果是这种情况，请向 LUIS 添加更多示例，重新训练并重新发布模型。

> 💁 您可以在 [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device) 文件夹中找到此代码。

😀 您的多语言计时器程序大获成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保翻译的准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。我们对于因使用此翻译而引起的任何误解或误读不承担责任。