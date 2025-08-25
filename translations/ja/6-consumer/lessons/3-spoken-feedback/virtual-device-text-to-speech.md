<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T00:16:12+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "ja"
}
-->
# テキストから音声へ - 仮想IoTデバイス

このレッスンのこの部分では、音声サービスを使用してテキストを音声に変換するコードを書きます。

## テキストを音声に変換する

前のレッスンで使用した音声サービスSDKは、テキストを音声に変換するためにも使用できます。音声をリクエストする際には、使用する声を指定する必要があります。音声はさまざまな声で生成することができます。

各言語には複数の声がサポートされており、音声サービスSDKから各言語でサポートされている声のリストを取得できます。

### タスク - テキストを音声に変換する

1. VS Codeで`smart-timer`プロジェクトを開き、ターミナルで仮想環境が読み込まれていることを確認してください。

1. 既存のインポートに以下を追加して、`azure.cognitiveservices.speech`パッケージから`SpeechSynthesizer`をインポートします：

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. `say`関数の上に、音声合成器で使用する音声設定を作成します：

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    これは、認識器で使用したのと同じAPIキー、場所、言語を使用します。

1. この下に、以下のコードを追加して声を取得し、音声設定に設定します：

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    これは利用可能な声のリストを取得し、使用している言語に一致する最初の声を見つけます。

    > 💁 Microsoft Docsの[言語と音声のサポートドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech)からサポートされている声の完全なリストを取得できます。特定の声を使用したい場合は、この関数を削除して、ドキュメントに記載されている声の名前をハードコードすることができます。例えば：
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. `say`関数の内容を更新して、応答のためのSSMLを生成します：

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. この下に、音声認識を停止し、SSMLを話し、再び認識を開始するコードを追加します：

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    テキストが話されている間、タイマー開始のアナウンスが検出され、LUISに送信され、新しいタイマーを設定するリクエストとして解釈される可能性があるため、認識は停止されます。

    > 💁 認識を停止および再開する行をコメントアウトしてこれをテストすることができます。一つのタイマーを設定すると、アナウンスが新しいタイマーを設定し、それが新しいアナウンスを引き起こし、永遠に続く可能性があります！

1. アプリを実行し、関数アプリも実行されていることを確認してください。いくつかのタイマーを設定すると、タイマーが設定されたことを知らせる音声応答が聞こえ、タイマーが完了した際にも別の音声応答が聞こえます。

> 💁 このコードは[code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device)フォルダーにあります。

😀 あなたのタイマーアプリは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当社は責任を負いません。