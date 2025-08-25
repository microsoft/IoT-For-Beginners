<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T00:10:24+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "zh"
}
-->
# 文本转语音 - 树莓派

在本课的这一部分，你将编写代码，通过语音服务将文本转换为语音。

## 使用语音服务将文本转换为语音

可以通过 REST API 将文本发送到语音服务，以获取可以在你的 IoT 设备上播放的音频文件。在请求语音时，你需要指定使用的语音，因为语音可以通过多种不同的声音生成。

每种语言都支持一系列不同的声音，你可以通过向语音服务发送 REST 请求来获取每种语言支持的声音列表。

### 任务 - 获取语音

1. 在 VS Code 中打开 `smart-timer` 项目。

1. 在 `say` 函数上方添加以下代码，以请求某种语言的声音列表：

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

    此代码定义了一个名为 `get_voice` 的函数，该函数使用语音服务获取声音列表。然后，它找到与正在使用的语言匹配的第一个声音。

    该函数随后被调用以存储第一个声音，并将声音名称打印到控制台。此声音可以请求一次，并在每次调用文本转语音时使用该值。

    > 💁 你可以从 [Microsoft Docs 上的语言和语音支持文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) 获取支持的声音的完整列表。如果你想使用特定的声音，可以删除此函数并将声音名称硬编码为文档中的声音名称。例如：
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### 任务 - 将文本转换为语音

1. 在此代码下方，定义一个常量，用于从语音服务中检索音频格式。当你请求音频时，可以选择多种不同的格式。

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    你可以使用的格式取决于你的硬件。如果在播放音频时遇到 `Invalid sample rate` 错误，请将其更改为其他值。你可以在 [Microsoft Docs 上的文本转语音 REST API 文档](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) 中找到支持的值列表。你需要使用 `riff` 格式音频，可以尝试的值包括 `riff-16khz-16bit-mono-pcm`、`riff-24khz-16bit-mono-pcm` 和 `riff-48khz-16bit-mono-pcm`。

1. 在此代码下方，声明一个名为 `get_speech` 的函数，该函数将使用语音服务 REST API 将文本转换为语音：

    ```python
    def get_speech(text):
    ```

1. 在 `get_speech` 函数中，定义要调用的 URL 和需要传递的请求头：

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    这设置了请求头以使用生成的访问令牌，将内容设置为 SSML，并定义所需的音频格式。

1. 在此代码下方，定义要发送到 REST API 的 SSML：

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    此 SSML 设置了要使用的语言和声音，以及要转换的文本。

1. 最后，在此函数中添加代码以发出 REST 请求并返回二进制音频数据：

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### 任务 - 播放音频

1. 在 `get_speech` 函数下方，定义一个新函数，用于播放 REST API 调用返回的音频：

    ```python
    def play_speech(speech):
    ```

1. 传递给此函数的 `speech` 是 REST API 返回的二进制音频数据。使用以下代码将其作为波形文件打开，并传递给 PyAudio 以播放音频：

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

    此代码使用 PyAudio 流，与捕获音频的方式相同。不同之处在于，此流设置为输出流，并从音频数据中读取数据并推送到流中。

    流的详细信息（如采样率）不是硬编码的，而是从音频数据中读取的。

1. 将 `say` 函数的内容替换为以下代码：

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    此代码将文本转换为二进制音频数据，并播放音频。

1. 运行应用程序，并确保函数应用程序也在运行。设置一些计时器，你会听到语音响应，告诉你计时器已设置，然后在计时器完成时听到另一个语音响应。

    如果遇到 `Invalid sample rate` 错误，请按照上述说明更改 `playback_format`。

> 💁 你可以在 [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) 文件夹中找到此代码。

😀 你的计时器程序运行成功！

**免责声明**：  
本文档使用AI翻译服务[Co-op Translator](https://github.com/Azure/co-op-translator)进行翻译。尽管我们努力确保准确性，但请注意，自动翻译可能包含错误或不准确之处。应以原始语言的文档作为权威来源。对于关键信息，建议使用专业人工翻译。对于因使用本翻译而引起的任何误解或误读，我们不承担责任。