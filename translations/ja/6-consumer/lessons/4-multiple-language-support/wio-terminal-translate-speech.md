<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5f6c164e349f8989959e02a90f37908d",
  "translation_date": "2025-08-24T23:49:53+00:00",
  "source_file": "6-consumer/lessons/4-multiple-language-support/wio-terminal-translate-speech.md",
  "language_code": "ja"
}
-->
# 音声を翻訳する - Wio Terminal

このレッスンのこの部分では、翻訳サービスを使用してテキストを翻訳するコードを書きます。

## 翻訳サービスを使用してテキストを音声に変換する

音声サービスのREST APIは直接翻訳をサポートしていません。その代わりに、音声からテキストサービスで生成されたテキストや、話された応答のテキストを翻訳するためにTranslatorサービスを使用できます。このサービスにはテキストを翻訳するためのREST APIがありますが、使いやすくするために、関数アプリ内で別のHTTPトリガーとしてラップします。

### タスク - テキストを翻訳するサーバーレス関数を作成する

1. VS Codeで`smart-timer-trigger`プロジェクトを開き、仮想環境が有効になっていることを確認してターミナルを開きます。有効でない場合は、ターミナルを終了して再作成してください。

1. `local.settings.json`ファイルを開き、翻訳APIキーとロケーションの設定を追加します:

    ```json
    "TRANSLATOR_KEY": "<key>",
    "TRANSLATOR_LOCATION": "<location>"
    ```

    `<key>`を翻訳サービスリソースのAPIキーに置き換えます。`<location>`を翻訳サービスリソースを作成した際に使用したロケーションに置き換えます。

1. VS Codeターミナルの関数アプリプロジェクトのルートフォルダー内で以下のコマンドを使用して、このアプリに`translate-text`という新しいHTTPトリガーを追加します:

    ```sh
    func new --name translate-text --template "HTTP trigger"
    ```

    これにより、`translate-text`というHTTPトリガーが作成されます。

1. `translate-text`フォルダー内の`__init__.py`ファイルの内容を以下のコードに置き換えます:

    ```python
    import logging
    import os
    import requests
    
    import azure.functions as func
    
    location = os.environ['TRANSLATOR_LOCATION']
    translator_key = os.environ['TRANSLATOR_KEY']
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        from_language = req_body['from_language']
        to_language = req_body['to_language']
        text = req_body['text']
        
        logging.info(f'Translating {text} from {from_language} to {to_language}')
    
        url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'
    
        headers = {
            'Ocp-Apim-Subscription-Key': translator_key,
            'Ocp-Apim-Subscription-Region': location,
            'Content-type': 'application/json'
        }
    
        params = {
            'from': from_language,
            'to': to_language
        }
    
        body = [{
            'text' : text
        }]
        
        response = requests.post(url, headers=headers, params=params, json=body)
        return func.HttpResponse(response.json()[0]['translations'][0]['text'])
    ```

    このコードはHTTPリクエストからテキストと言語を抽出します。その後、翻訳REST APIにリクエストを送り、URLのパラメーターとして言語を渡し、翻訳するテキストを本文として送信します。最後に翻訳結果を返します。

1. 関数アプリをローカルで実行します。その後、curlのようなツールを使用して`text-to-timer` HTTPトリガーをテストしたのと同じ方法でこれを呼び出すことができます。翻訳するテキストと言語をJSON本文として渡してください:

    ```json
    {
        "text": "Définir une minuterie de 30 secondes",
        "from_language": "fr-FR",
        "to_language": "en-US"
    }
    ```

    この例では、フランス語の*Définir une minuterie de 30 secondes*を米国英語に翻訳します。結果は*Set a 30-second timer*となります。

> 💁 このコードは[code/functions](../../../../../6-consumer/lessons/4-multiple-language-support/code/functions)フォルダーにあります。

### タスク - 翻訳関数を使用してテキストを翻訳する

1. `smart-timer`プロジェクトをVS Codeで開きます（まだ開いていない場合）。

1. スマートタイマーには2つの言語が設定されます - LUISをトレーニングするために使用されたサーバーの言語（ユーザーに話しかけるメッセージを構築するためにも使用される）と、ユーザーが話す言語です。`config.h`ヘッダーファイルの`LANGUAGE`定数をユーザーが話す言語に更新し、LUISをトレーニングするために使用された言語用に`SERVER_LANGUAGE`という新しい定数を追加します:

    ```cpp
    const char *LANGUAGE = "<user language>";
    const char *SERVER_LANGUAGE = "<server language>";
    ```

    `<user language>`を話す予定の言語のロケール名に置き換えます。例えば、フランス語の場合は`fr-FR`、広東語の場合は`zn-HK`です。

    `<server language>`をLUISをトレーニングするために使用された言語のロケール名に置き換えます。

    サポートされている言語とそのロケール名のリストは、[Microsoft Docsの言語と音声サポートドキュメント](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text)で確認できます。

    > 💁 複数の言語を話せない場合は、[Bing Translate](https://www.bing.com/translator)や[Google Translate](https://translate.google.com)のようなサービスを使用して、好みの言語から選択した言語に翻訳できます。これらのサービスは翻訳されたテキストの音声を再生することもできます。
    >
    > 例えば、LUISを英語でトレーニングし、ユーザー言語としてフランス語を使用したい場合、Bing Translateを使用して英語の文「set a 2 minute and 27 second timer」をフランス語に翻訳し、**Listen translation**ボタンを使用して翻訳された音声をマイクに話すことができます。
    >
    > ![Bing TranslateのListen translationボタン](../../../../../translated_images/ja/bing-translate.348aa796d6efe2a92f41ea74a5cf42bb4c63d6faaa08e7f46924e072a35daa48.png)

1. `SPEECH_LOCATION`の下に翻訳APIキーとロケーションを追加します:

    ```cpp
    const char *TRANSLATOR_API_KEY = "<KEY>";
    const char *TRANSLATOR_LOCATION = "<LOCATION>";
    ```

    `<KEY>`を翻訳サービスリソースのAPIキーに置き換えます。`<LOCATION>`を翻訳サービスリソースを作成した際に使用したロケーションに置き換えます。

1. `VOICE_URL`の下に翻訳トリガーURLを追加します:

    ```cpp
    const char *TRANSLATE_FUNCTION_URL = "<URL>";
    ```

    `<URL>`を関数アプリの`translate-text` HTTPトリガーのURLに置き換えます。この値は`TEXT_TO_TIMER_FUNCTION_URL`の値と同じですが、関数名が`text-to-timer`ではなく`translate-text`になります。

1. `src`フォルダーに`text_translator.h`という新しいファイルを追加します。

1. この新しい`text_translator.h`ヘッダーファイルにはテキストを翻訳するクラスが含まれます。このファイルに以下を追加してクラスを宣言します:

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    
    class TextTranslator
    {
    public:   
    private:
        WiFiClient _client;
    };
    
    TextTranslator textTranslator;
    ```

    これにより`TextTranslator`クラスが宣言され、このクラスのインスタンスが作成されます。このクラスにはWiFiクライアント用のフィールドが1つあります。

1. このクラスの`public`セクションにテキストを翻訳するメソッドを追加します:

    ```cpp
    String translateText(String text, String from_language, String to_language)
    {
    }
    ```

    このメソッドは翻訳元の言語と翻訳先の言語を受け取ります。音声を処理する際には、ユーザー言語からLUISサーバー言語に翻訳し、応答を提供する際にはLUISサーバー言語からユーザー言語に翻訳します。

1. このメソッド内に、翻訳するテキストと言語を含むJSON本文を構築するコードを追加します:

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;
    doc["from_language"] = from_language;
    doc["to_language"] = to_language;

    String body;
    serializeJson(doc, body);

    Serial.print("Translating ");
    Serial.print(text);
    Serial.print(" from ");
    Serial.print(from_language);
    Serial.print(" to ");
    Serial.print(to_language);
    ```

1. その下に、本文をサーバーレス関数アプリに送信するコードを追加します:

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TRANSLATE_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. 次に、応答を取得するコードを追加します:

    ```cpp
    String translated_text = "";

    if (httpResponseCode == 200)
    {
        translated_text = httpClient.getString();
        Serial.print("Translated: ");
        Serial.println(translated_text);
    }
    else
    {
        Serial.print("Failed to translate text - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. 最後に、接続を閉じて翻訳されたテキストを返すコードを追加します:

    ```cpp
    httpClient.end();

    return translated_text;
    ```

### タスク - 認識された音声と応答を翻訳する

1. `main.cpp`ファイルを開きます。

1. ファイルの先頭に`TextTranslator`クラスヘッダーファイルのインクルード指令を追加します:

    ```cpp
    #include "text_translator.h"
    ```

1. タイマーが設定されたり期限切れになったりした際に話されるテキストを翻訳する必要があります。これを行うために、`say`関数の最初の行として以下を追加します:

    ```cpp
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    これにより、テキストがユーザー言語に翻訳されます。

1. `processAudio`関数では、`String text = speechToText.convertSpeechToText();`呼び出しでキャプチャされた音声からテキストが取得されます。この呼び出しの後にテキストを翻訳します:

    ```cpp
    String text = speechToText.convertSpeechToText();
    text = textTranslator.translateText(text, LANGUAGE, SERVER_LANGUAGE);
    ```

    これにより、テキストがユーザー言語からサーバーで使用される言語に翻訳されます。

1. このコードをビルドし、Wio Terminalにアップロードしてシリアルモニターでテストします。シリアルモニターに`Ready`と表示されたら、Cボタン（左側で電源スイッチに最も近いボタン）を押して話します。関数アプリが実行されていることを確認し、ユーザー言語でタイマーをリクエストします。自分でその言語を話すか、翻訳アプリを使用してください。

    ```output
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Définir une minuterie de 2 minutes 27 secondes.","Offset":9600000,"Duration":40400000}
    Translating Définir une minuterie de 2 minutes 27 secondes. from fr-FR to en-US
    Translated: Set a timer of 2 minutes 27 seconds.
    Set a timer of 2 minutes 27 seconds.
    {"seconds": 147}
    Translating 2 minute 27 second timer started. from en-US to fr-FR
    Translated: 2 minute 27 seconde minute a commencé.
    2 minute 27 seconde minute a commencé.
    Translating Times up on your 2 minute 27 second timer. from en-US to fr-FR
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

> 💁 このコードは[code/wio-terminal](../../../../../6-consumer/lessons/4-multiple-language-support/code/wio-terminal)フォルダーにあります。

😀 あなたの多言語タイマーアプリは成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があります。元の言語で記載された文書が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。