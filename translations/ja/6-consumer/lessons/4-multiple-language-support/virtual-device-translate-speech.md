<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d620a470d9dd8614d99824832978360a",
  "translation_date": "2025-08-24T23:56:42+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/virtual-device-translate-speech.md",
  "language_code": "ja"
}
-->
# スピーチ翻訳 - 仮想IoTデバイス

このレッスンのこの部分では、スピーチサービスを使用して音声をテキストに変換し、その後、翻訳サービスを使用してテキストを翻訳し、音声応答を生成するコードを書きます。

## スピーチサービスを使用して音声を翻訳する

スピーチサービスは、音声を同じ言語でテキストに変換するだけでなく、出力を他の言語に翻訳することもできます。

### タスク - スピーチサービスを使用して音声を翻訳する

1. VS Codeで`smart-timer`プロジェクトを開き、ターミナルで仮想環境がロードされていることを確認してください。

1. 既存のインポート文の下に以下のインポート文を追加してください：

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    これにより、音声を翻訳するために使用されるクラスと、後でこのレッスンで翻訳サービスに呼び出しを行うために使用される`requests`ライブラリがインポートされます。

1. スマートタイマーには2つの言語が設定されます - LUISをトレーニングするために使用されたサーバーの言語（この言語はユーザーに話しかけるメッセージを構築するためにも使用されます）と、ユーザーが話す言語です。`language`変数をユーザーが話す言語に設定し、LUISをトレーニングするために使用された言語を指定する新しい変数`server_language`を追加してください：

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    `<user language>`を、話す予定の言語のロケール名に置き換えてください。例えば、フランス語の場合は`fr-FR`、広東語の場合は`zn-HK`です。

    `<server language>`を、LUISをトレーニングするために使用された言語のロケール名に置き換えてください。

    サポートされている言語とそのロケール名のリストは、[Microsoft Docsの言語と音声サポートドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)で確認できます。

    > 💁 複数の言語を話せない場合は、[Bing翻訳](https://www.bing.com/translator)や[Google翻訳](https://translate.google.com)などのサービスを使用して、好みの言語から選択した言語に翻訳することができます。これらのサービスは翻訳されたテキストの音声を再生することもできます。ただし、スピーチ認識機能はデバイスからの一部の音声出力を無視することがあるため、翻訳されたテキストを再生するために追加のデバイスが必要になる場合があります。
    >
    > 例えば、LUISを英語でトレーニングし、ユーザー言語としてフランス語を使用したい場合、"set a 2 minute and 27 second timer"のような文を英語からフランス語にBing翻訳を使用して翻訳し、**Listen translation**ボタンを使用して翻訳をマイクに話しかけることができます。
    >
    > ![Bing翻訳のListen translationボタン](../../../../../translated_images/ja/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `recognizer_config`と`recognizer`の宣言を以下のコードに置き換えてください：

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    これにより、ユーザー言語で音声を認識し、ユーザー言語とサーバー言語で翻訳を作成するための翻訳設定が作成されます。その後、この設定を使用して翻訳認識器を作成します - スピーチ認識の出力を複数の言語に翻訳できるスピーチ認識器です。

    > 💁 元の言語を`target_languages`に指定する必要があります。そうしないと翻訳が得られません。

1. `recognized`関数を更新し、関数の内容全体を以下のコードに置き換えてください：

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    このコードは、認識されたイベントが音声が翻訳されたために発生したかどうかを確認します（このイベントは、音声が認識されたが翻訳されなかった場合など、他のタイミングでも発生する可能性があります）。音声が翻訳された場合、`args.result.translations`辞書内でサーバー言語に一致する翻訳を見つけます。

    `args.result.translations`辞書は、ロケール設定の全体ではなく言語部分をキーとして使用します。例えば、フランス語の翻訳を`fr-FR`で要求した場合、辞書には`fr-FR`ではなく`fr`のエントリが含まれます。

    翻訳されたテキストはIoT Hubに送信されます。

1. このコードを実行して翻訳をテストしてください。関数アプリが実行中であることを確認し、ユーザー言語でタイマーを要求してください。自分でその言語を話すか、翻訳アプリを使用してください。

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## 翻訳サービスを使用してテキストを翻訳する

スピーチサービスはテキストを音声に戻す翻訳をサポートしていません。その代わりに、翻訳サービスを使用してテキストを翻訳することができます。このサービスにはテキストを翻訳するためのREST APIがあります。

### タスク - 翻訳リソースを使用してテキストを翻訳する

1. `speech_api_key`の下に翻訳APIキーを追加してください：

    ```python
    translator_api_key = '<key>'
    ```

    `<key>`を翻訳サービスリソースのAPIキーに置き換えてください。

1. `say`関数の上に、サーバー言語からユーザー言語にテキストを翻訳する`translate_text`関数を定義してください：

    ```python
    def translate_text(text):
    ```

1. この関数内で、REST API呼び出しのURLとヘッダーを定義してください：

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    このAPIのURLは場所に依存せず、場所はヘッダーとして渡されます。APIキーは直接使用されるため、スピーチサービスのようにトークン発行APIからアクセストークンを取得する必要はありません。

1. この下に、呼び出しのパラメータと本文を定義してください：

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params`はAPI呼び出しに渡すパラメータを定義し、元の言語と翻訳先の言語を渡します。この呼び出しは`from`言語のテキストを`to`言語に翻訳します。

    `body`は翻訳するテキストを含みます。これは配列であり、同じ呼び出しで複数のテキストブロックを翻訳することができます。

1. REST APIを呼び出し、レスポンスを取得してください：

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    戻ってくるレスポンスはJSON配列であり、翻訳を含む1つのアイテムが含まれています。このアイテムには、本文で渡されたすべてのアイテムの翻訳の配列があります。

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

1. 配列内の最初のアイテムから最初の翻訳の`test`プロパティを返してください：

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. SSMLが生成される前に、`say`関数を更新して話すテキストを翻訳してください：

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    このコードは、元のテキストと翻訳されたテキストをコンソールに出力することもします。

1. コードを実行してください。関数アプリが実行中であることを確認し、ユーザー言語でタイマーを要求してください。自分でその言語を話すか、翻訳アプリを使用してください。

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

    > 💁 言語によって表現方法が異なるため、LUISに与えた例とは少し異なる翻訳が得られる場合があります。この場合は、LUISにさらに多くの例を追加し、再トレーニングしてモデルを再公開してください。

> 💁 このコードは[code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device)フォルダーにあります。

😀 あなたの多言語タイマープログラムは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が信頼できる情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や解釈の誤りについて、当方は一切の責任を負いません。