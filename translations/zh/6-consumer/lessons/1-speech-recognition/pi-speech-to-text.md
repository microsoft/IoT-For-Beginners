<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T00:33:08+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "zh"
}
-->
# 语音转文字 - 树莓派

在本课的这一部分，你将编写代码，将捕获的音频中的语音转换为文字，使用语音服务完成这一任务。

## 将音频发送到语音服务

可以通过 REST API 将音频发送到语音服务。要使用语音服务，首先需要请求一个访问令牌，然后使用该令牌访问 REST API。这些访问令牌的有效期为10分钟，因此你的代码需要定期请求新的令牌，以确保它们始终是最新的。

### 任务 - 获取访问令牌

1. 在你的树莓派上打开 `smart-timer` 项目。

1. 删除 `play_audio` 函数。这个函数已经不再需要，因为你不希望智能计时器重复你所说的话。

1. 在 `app.py` 文件的顶部添加以下导入：

    ```python
    import requests
    ```

1. 在 `while True` 循环的上方添加以下代码，以声明语音服务的一些设置：

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    将 `<key>` 替换为你的语音服务资源的 API 密钥。将 `<location>` 替换为你创建语音服务资源时使用的位置。

    将 `<language>` 替换为你将使用的语言的区域名称，例如 `en-GB` 表示英语，或者 `zn-HK` 表示粤语。你可以在 [Microsoft 文档上的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text) 中找到支持的语言及其区域名称的列表。

1. 在此代码的下方，添加以下函数以获取访问令牌：

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    该函数调用一个令牌发放端点，并将 API 密钥作为请求头传递。此调用返回一个访问令牌，可用于调用语音服务。

1. 在此代码的下方，声明一个函数，通过 REST API 将捕获的音频中的语音转换为文字：

    ```python
    def convert_speech_to_text(buffer):
    ```

1. 在此函数内部，设置 REST API 的 URL 和请求头：

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    这段代码使用语音服务资源的位置构建一个 URL。然后，它将 `get_access_token` 函数返回的访问令牌以及捕获音频时使用的采样率填充到请求头中。最后，它定义了一些参数，这些参数将与 URL 一起传递，包含音频中的语言信息。

1. 在此代码的下方，添加以下代码以调用 REST API 并获取返回的文字：

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    这段代码调用 URL，并解码响应中的 JSON 值。响应中的 `RecognitionStatus` 值指示是否成功将语音提取为文字。如果该值为 `Success`，则函数返回提取的文字，否则返回一个空字符串。

1. 在 `while True:` 循环的上方，定义一个函数来处理语音转文字服务返回的文字。这个函数目前只会将文字打印到控制台。

    ```python
    def process_text(text):
        print(text)
    ```

1. 最后，在 `while True` 循环中，将对 `play_audio` 的调用替换为对 `convert_speech_to_text` 函数的调用，并将返回的文字传递给 `process_text` 函数：

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. 运行代码。按下按钮并对着麦克风说话。完成后松开按钮，音频将被转换为文字并打印到控制台。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    尝试不同类型的句子，以及一些单词发音相同但含义不同的句子。例如，如果你使用英语，可以说“我想买两个香蕉和一个苹果”，注意它会根据单词的上下文正确使用 to、two 和 too，而不仅仅是根据发音。

> 💁 你可以在 [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi) 文件夹中找到这段代码。

😀 你的语音转文字程序运行成功了！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们概不负责。