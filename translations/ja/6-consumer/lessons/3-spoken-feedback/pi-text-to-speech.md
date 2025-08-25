<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-25T00:11:19+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "ja"
}
-->
# テキスト読み上げ - Raspberry Pi

このレッスンのこの部分では、音声サービスを使用してテキストを音声に変換するコードを書きます。

## 音声サービスを使用してテキストを音声に変換する

テキストはREST APIを使用して音声サービスに送信され、IoTデバイスで再生可能な音声ファイルとして取得できます。音声をリクエストする際には、使用する声を指定する必要があります。音声はさまざまな声で生成することができます。

各言語にはさまざまな声がサポートされており、音声サービスに対してRESTリクエストを送信することで、各言語でサポートされている声のリストを取得できます。

### タスク - 声を取得する

1. VS Codeで`smart-timer`プロジェクトを開きます。

1. 言語の声のリストをリクエストするために、`say`関数の上に次のコードを追加します:

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

    このコードは、音声サービスを使用して声のリストを取得する`get_voice`という関数を定義します。そして、使用されている言語に一致する最初の声を見つけます。

    この関数は最初の声を保存するために呼び出され、声の名前がコンソールに出力されます。この声は一度リクエストして、その値をテキストを音声に変換するすべての呼び出しで使用できます。

    > 💁 サポートされている声の完全なリストは、[Microsoft Docsの言語と声のサポートドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech)で確認できます。特定の声を使用したい場合は、この関数を削除して、ドキュメントから声の名前をハードコードすることができます。例えば:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### タスク - テキストを音声に変換する

1. この下に、音声サービスから取得するオーディオ形式の定数を定義します。オーディオをリクエストする際には、さまざまな形式で取得できます。

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    使用する形式はハードウェアによって異なります。オーディオを再生する際に`Invalid sample rate`エラーが発生した場合は、これを別の値に変更してください。サポートされている値のリストは、[Microsoft Docsのテキスト読み上げREST APIドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs)で確認できます。`riff`形式のオーディオを使用する必要があり、試すべき値は`riff-16khz-16bit-mono-pcm`、`riff-24khz-16bit-mono-pcm`、`riff-48khz-16bit-mono-pcm`です。

1. この下に、音声サービスREST APIを使用してテキストを音声に変換する`get_speech`という関数を宣言します:

    ```python
    def get_speech(text):
    ```

1. `get_speech`関数内で、呼び出すURLと渡すヘッダーを定義します:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    これにより、生成されたアクセストークンを使用し、コンテンツをSSMLとして設定し、必要なオーディオ形式を定義します。

1. この下に、REST APIに送信するSSMLを定義します:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    このSSMLは、使用する言語と声を設定し、変換するテキストを指定します。

1. 最後に、この関数内でRESTリクエストを実行し、バイナリオーディオデータを返すコードを追加します:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### タスク - オーディオを再生する

1. `get_speech`関数の下に、REST API呼び出しで返されたオーディオを再生する新しい関数を定義します:

    ```python
    def play_speech(speech):
    ```

1. この関数に渡される`speech`は、REST APIから返されたバイナリオーディオデータです。次のコードを使用してこれを波形ファイルとして開き、PyAudioを使用してオーディオを再生します:

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

    このコードはPyAudioストリームを使用します。音声をキャプチャする場合と同様ですが、ここではストリームが出力ストリームとして設定され、オーディオデータから読み取られたデータがストリームに送られます。

    ストリームの詳細（サンプルレートなど）をハードコードする代わりに、オーディオデータから読み取ります。

1. `say`関数の内容を次のコードに置き換えます:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    このコードは、テキストをバイナリオーディオデータとして音声に変換し、そのオーディオを再生します。

1. アプリを実行し、関数アプリも実行されていることを確認します。いくつかのタイマーを設定すると、タイマーが設定されたことを知らせる音声応答が聞こえ、タイマーが完了すると別の音声応答が聞こえます。

    `Invalid sample rate`エラーが発生した場合は、上記の説明に従って`playback_format`を変更してください。

> 💁 このコードは[code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi)フォルダーにあります。

😀 タイマーアプリは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。