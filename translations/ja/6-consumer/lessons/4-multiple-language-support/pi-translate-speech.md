<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "bbb5aa34221fe129dd3ce4d9ec33831a",
  "translation_date": "2025-08-24T23:55:12+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/pi-translate-speech.md",
  "language_code": "ja"
}
-->
# スピーチを翻訳する - Raspberry Pi

このレッスンのこの部分では、翻訳サービスを使用してテキストを翻訳するコードを書きます。

## 翻訳サービスを使用してテキストを音声に変換する

スピーチサービスのREST APIは直接の翻訳をサポートしていません。その代わりに、スピーチからテキストへのサービスで生成されたテキストや、話された応答のテキストを翻訳するためにTranslatorサービスを使用できます。このサービスには、テキストを翻訳するために使用できるREST APIがあります。

### タスク - Translatorリソースを使用してテキストを翻訳する

1. スマートタイマーには2つの言語が設定されます。1つはLUISをトレーニングするために使用されたサーバーの言語（この言語はユーザーに話しかけるメッセージを作成するためにも使用されます）、もう1つはユーザーが話す言語です。`language`変数をユーザーが話す言語に更新し、LUISをトレーニングするために使用された言語用に`server_language`という新しい変数を追加してください：

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>`を、話す予定の言語のロケール名に置き換えてください。例えば、フランス語の場合は`fr-FR`、広東語の場合は`zn-HK`です。

    `<server language>`を、LUISをトレーニングするために使用された言語のロケール名に置き換えてください。

    サポートされている言語とそのロケール名のリストは、[Microsoft Docsの言語と音声のサポートドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)で確認できます。

    > 💁 複数の言語を話せない場合は、[Bing Translate](https://www.bing.com/translator)や[Google Translate](https://translate.google.com)のようなサービスを使用して、好みの言語から選択した言語に翻訳することができます。これらのサービスは翻訳されたテキストの音声を再生することもできます。
    >
    > 例えば、LUISを英語でトレーニングし、ユーザー言語としてフランス語を使用したい場合、Bing Translateを使用して「2分27秒のタイマーを設定して」という文を英語からフランス語に翻訳し、その後**Listen translation**ボタンを使用して翻訳をマイクに話すことができます。
    >
    > ![Bing TranslateのListen translationボタン](../../../../../translated_images/ja/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `speech_api_key`の下にTranslator APIキーを追加してください：

    ```python
    translator_api_key = '<key>'
    ```

    `<key>`をTranslatorサービスリソースのAPIキーに置き換えてください。

1. `say`関数の上に、サーバー言語からユーザー言語へテキストを翻訳する`translate_text`関数を定義してください：

    ```python
    def translate_text(text, from_language, to_language):
    ```

    この関数には、翻訳元と翻訳先の言語が渡されます。アプリは、スピーチを認識する際にユーザー言語からサーバー言語へ変換し、話されたフィードバックを提供する際にサーバー言語からユーザー言語へ変換する必要があります。

1. この関数内で、REST API呼び出しのURLとヘッダーを定義してください：

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    このAPIのURLは場所に依存せず、代わりに場所はヘッダーとして渡されます。APIキーは直接使用されるため、スピーチサービスのようにトークン発行APIからアクセストークンを取得する必要はありません。

1. 次に、呼び出しのパラメータと本文を定義してください：

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params`はAPI呼び出しに渡すパラメータを定義し、翻訳元と翻訳先の言語を渡します。この呼び出しは、`from`言語のテキストを`to`言語に翻訳します。

    `body`は翻訳するテキストを含みます。これは配列であり、同じ呼び出しで複数のテキストブロックを翻訳できます。

1. REST APIを呼び出し、レスポンスを取得してください：

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    戻ってくるレスポンスはJSON配列であり、翻訳を含む1つのアイテムがあります。このアイテムには、本文で渡されたすべてのアイテムの翻訳の配列があります。

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. 配列内の最初のアイテムから最初の翻訳の`test`プロパティを返してください：

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. `while True`ループを更新して、ユーザー言語からサーバー言語へ`convert_speech_to_text`呼び出しのテキストを翻訳してください：

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    このコードは、元のテキストと翻訳されたテキストをコンソールに出力します。

1. `say`関数を更新して、サーバー言語からユーザー言語へ話すテキストを翻訳してください：

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    このコードは、元のテキストと翻訳されたテキストをコンソールに出力します。

1. コードを実行してください。関数アプリが実行されていることを確認し、ユーザー言語でタイマーをリクエストしてください。自分でその言語を話すか、翻訳アプリを使用してください。

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 言語によって表現方法が異なるため、LUISに与えた例とは少し異なる翻訳が得られる場合があります。その場合は、LUISにさらに例を追加し、再トレーニングしてモデルを再公開してください。

> 💁 このコードは[code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi)フォルダーにあります。

😀 あなたの多言語タイマーアプリは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。