<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-25T00:33:47+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "ja"
}
-->
# 音声からテキストへ - Raspberry Pi

このレッスンのこの部分では、キャプチャした音声を音声サービスを使ってテキストに変換するコードを書きます。

## 音声を音声サービスに送信する

音声はREST APIを使用して音声サービスに送信できます。音声サービスを使用するには、まずアクセス トークンをリクエストし、そのトークンを使用してREST APIにアクセスします。これらのアクセス トークンは10分で期限切れになるため、コードは定期的にトークンをリクエストして、常に最新の状態を保つ必要があります。

### タスク - アクセストークンを取得する

1. Pi上で`smart-timer`プロジェクトを開きます。

1. `play_audio`関数を削除します。スマートタイマーがあなたの発言を繰り返す必要がないため、これはもう必要ありません。

1. 次のインポートを`app.py`ファイルの先頭に追加します：

    ```python
    import requests
    ```

1. 次のコードを`while True`ループの上に追加して、音声サービスの設定を宣言します：

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    `<key>`を音声サービスリソースのAPIキーに置き換えます。`<location>`を音声サービスリソースを作成したときに使用した場所に置き換えます。

    `<language>`を、話す言語のロケール名に置き換えます。例えば、英語の場合は`en-GB`、広東語の場合は`zn-HK`です。サポートされている言語とそのロケール名のリストは、[Microsoft Docsの言語と音声サポートのドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)で確認できます。

1. この下に、アクセストークンを取得するための次の関数を追加します：

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    これはトークン発行エンドポイントを呼び出し、APIキーをヘッダーとして渡します。この呼び出しは、音声サービスを呼び出すために使用できるアクセストークンを返します。

1. この下に、キャプチャした音声をREST APIを使用してテキストに変換する関数を宣言します：

    ```python
    def convert_speech_to_text(buffer):
    ```

1. この関数内で、REST APIのURLとヘッダーを設定します：

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

    これは、音声サービスリソースの場所を使用してURLを構築します。その後、`get_access_token`関数から取得したアクセストークン、音声をキャプチャする際に使用したサンプルレートをヘッダーに設定します。最後に、音声の言語を含むURLに渡すパラメータを定義します。

1. この下に、REST APIを呼び出してテキストを取得する次のコードを追加します：

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    これはURLを呼び出し、レスポンスで返されるJSON値をデコードします。レスポンス内の`RecognitionStatus`値は、音声をテキストに正常に変換できたかどうかを示します。この値が`Success`の場合、関数からテキストが返されます。それ以外の場合は空の文字列が返されます。

1. `while True:`ループの上に、音声からテキストサービスで返されたテキストを処理する関数を定義します。この関数は、現在のところテキストをコンソールに出力するだけです。

    ```python
    def process_text(text):
        print(text)
    ```

1. 最後に、`while True`ループ内の`play_audio`の呼び出しを、`convert_speech_to_text`関数の呼び出しに置き換え、テキストを`process_text`関数に渡します：

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. コードを実行します。ボタンを押してマイクに向かって話します。話し終わったらボタンを離すと、音声がテキストに変換され、コンソールに出力されます。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    さまざまな種類の文や、同じ音でも異なる意味を持つ単語を含む文を試してみてください。例えば、英語で話している場合、「I want to buy two bananas and an apple too」と言ってみてください。文脈に基づいて「to」「two」「too」を正しく使い分ける様子を確認できます。

> 💁 このコードは[code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi)フォルダーにあります。

😀 音声からテキストへのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。