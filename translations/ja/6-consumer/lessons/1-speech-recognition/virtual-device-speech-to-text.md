<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-25T00:23:56+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "ja"
}
-->
# 音声からテキストへの変換 - 仮想IoTデバイス

このレッスンのこの部分では、マイクから取得した音声を音声サービスを使用してテキストに変換するコードを書きます。

## 音声をテキストに変換する

Windows、Linux、macOSでは、音声サービスのPython SDKを使用してマイクを聞き取り、検出された音声をテキストに変換することができます。このSDKは継続的に音声を聞き取り、音声レベルが下がったとき（例えば、音声のブロックが終了したとき）に音声を検出してテキストに変換します。

### タスク - 音声をテキストに変換する

1. `smart-timer`というフォルダーに新しいPythonアプリを作成し、その中に`app.py`という単一のファイルとPython仮想環境を作成します。

1. 音声サービス用のPipパッケージをインストールします。仮想環境が有効化されたターミナルからインストールすることを確認してください。

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ 以下のエラーが発生した場合:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Pipを更新する必要があります。以下のコマンドを使用して更新し、再度パッケージをインストールしてください。
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. `app.py`ファイルに以下のインポートを追加します:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    これにより、音声認識に使用されるクラスがインポートされます。

1. 以下のコードを追加して、いくつかの設定を宣言します:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    `<key>`を音声サービスのAPIキーに置き換えてください。`<location>`を音声サービスリソースを作成した場所に置き換えてください。

    `<language>`を使用する言語のロケール名に置き換えてください。例えば、英語の場合は`en-GB`、広東語の場合は`zn-HK`です。サポートされている言語とそのロケール名のリストは、[Microsoft Docsの言語と音声サポートのドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)で確認できます。

    この設定は、音声サービスを設定するために使用される`SpeechConfig`オブジェクトを作成するために使用されます。

1. 以下のコードを追加して、音声認識器を作成します:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. 音声認識器はバックグラウンドスレッドで動作し、音声を聞き取り、それをテキストに変換します。テキストを取得するにはコールバック関数を使用します。コールバック関数は認識器に渡され、音声が検出されるたびに呼び出されます。以下のコードを追加してコールバックを定義し、このコールバックを認識器に渡します。また、テキストを処理してコンソールに出力する関数を定義します:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. 認識器は明示的に開始されるまで音声を聞き取りません。以下のコードを追加して認識を開始します。この処理はバックグラウンドで実行されるため、アプリケーションを実行し続けるために無限ループでスリープする必要があります。

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. このアプリを実行します。マイクに向かって話しかけると、音声がテキストに変換されてコンソールに出力されます。

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    様々な種類の文章を試してみてください。また、同じ音を持つが異なる意味を持つ単語を含む文章も試してみてください。例えば、英語で話す場合、「I want to buy two bananas and an apple too」と言ってみてください。音だけでなく文脈に基づいて正しい「to」「two」「too」を使用することに気づくでしょう。

> 💁 このコードは[code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device)フォルダーで確認できます。

😀 音声からテキストへの変換プログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。