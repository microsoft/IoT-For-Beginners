<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T00:13:57+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "ja"
}
-->
# テキスト読み上げ - Wio Terminal

このレッスンでは、テキストを音声に変換して音声フィードバックを提供します。

## テキスト読み上げ

前回のレッスンで使用した音声サービスSDKは、音声をテキストに変換するだけでなく、テキストを音声に戻すこともできます。

## 音声のリストを取得する

音声をリクエストする際には、使用する音声を指定する必要があります。さまざまな音声を使用して音声を生成できるためです。各言語には複数の音声がサポートされており、音声サービスSDKから各言語でサポートされている音声のリストを取得できます。ただし、マイクロコントローラーの制約がここで問題になります。テキスト読み上げサービスでサポートされている音声のリストを取得するための呼び出しは、77KB以上のJSONドキュメントであり、Wio Terminalでは処理するには大きすぎます。執筆時点では、リスト全体には215の音声が含まれており、それぞれ以下のようなJSONドキュメントで定義されています。

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

このJSONは**Aria**音声用で、複数の音声スタイルがあります。テキストを音声に変換する際に必要なのは、`en-US-AriaNeural`のようなshortnameだけです。

マイクロコントローラーでこのリスト全体をダウンロードしてデコードする代わりに、使用する言語の音声リストを取得するためのサーバーレスコードを作成し、Wio Terminalからこれを呼び出す必要があります。その後、コードでリストから適切な音声を選択できます（例えば、最初に見つかったものを選ぶなど）。

### タスク - 音声リストを取得するサーバーレス関数を作成する

1. VS Codeで`smart-timer-trigger`プロジェクトを開き、仮想環境が有効になっていることを確認してターミナルを開きます。有効でない場合は、ターミナルを終了して再作成してください。

1. `local.settings.json`ファイルを開き、音声APIキーとロケーションの設定を追加します：

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    `<key>`を音声サービスリソースのAPIキーに置き換えます。`<location>`を音声サービスリソースを作成した際に使用したロケーションに置き換えます。

1. このアプリに`get-voices`という新しいHTTPトリガーを追加します。VS Codeターミナルで関数アプリプロジェクトのルートフォルダー内から以下のコマンドを使用します：

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    これにより、`get-voices`というHTTPトリガーが作成されます。

1. `get-voices`フォルダー内の`__init__.py`ファイルの内容を以下のコードに置き換えます：

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    このコードは、音声リストを取得するためのエンドポイントにHTTPリクエストを送信します。この音声リストは、すべての言語の音声を含む大きなJSONブロックであるため、リクエストボディで渡された言語の音声だけをフィルタリングし、shortnameを抽出してJSONリストとして返します。shortnameはテキストを音声に変換するために必要な値なので、この値だけが返されます。

    > 💁 必要に応じてフィルタを変更して、必要な音声だけを選択できます。

    これにより、データサイズは執筆時点で77KBから、はるかに小さいJSONドキュメントに削減されます。例えば、US音声の場合は408バイトです。

1. 関数アプリをローカルで実行します。その後、curlのようなツールを使用して、`text-to-timer` HTTPトリガーをテストしたのと同じ方法でこれを呼び出すことができます。リクエストボディとしてJSON形式で言語を渡すことを忘れないでください：

    ```json
    {
        "language":"<language>"
    }
    ```

    `<language>`を`en-GB`や`zh-CN`などの言語に置き換えます。

> 💁 このコードは[code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)フォルダーにあります。

### タスク - Wio Terminalから音声を取得する

1. `smart-timer`プロジェクトをVS Codeで開きます（まだ開いていない場合）。

1. `config.h`ヘッダーファイルを開き、関数アプリのURLを追加します：

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    `<URL>`を関数アプリの`get-voices` HTTPトリガーのURLに置き換えます。このURLは`TEXT_TO_TIMER_FUNCTION_URL`の値と同じですが、関数名が`text-to-timer`ではなく`get-voices`になります。

1. `src`フォルダーに`text_to_speech.h`という新しいファイルを作成します。このファイルは、テキストを音声に変換するクラスを定義するために使用されます。

1. 新しい`text_to_speech.h`ファイルの先頭に以下のインクルードディレクティブを追加します：

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. 以下のコードを追加して、`TextToSpeech`クラスを宣言し、アプリケーションの他の部分で使用できるインスタンスを作成します：

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. 関数アプリを呼び出すためにWiFiクライアントを宣言します。クラスの`private`セクションに以下を追加します：

    ```cpp
    WiFiClient _client;
    ```

1. `private`セクションに、選択された音声のフィールドを追加します：

    ```cpp
    String _voice;
    ```

1. `public`セクションに、最初の音声を取得する`init`関数を追加します：

    ```cpp
    void init()
    {
    }
    ```

1. 音声を取得するために、リクエストボディとして言語を含むJSONドキュメントを作成します。`init`関数に以下のコードを追加します：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. 次に、`HTTPClient`を作成し、これを使用して関数アプリを呼び出し、JSONドキュメントをポストします：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. この下に、レスポンスコードを確認し、200（成功）であれば音声リストを抽出し、リストから最初の音声を取得するコードを追加します：

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. この後、HTTPクライアント接続を終了します：

    ```cpp
    httpClient.end();
    ```

1. `main.cpp`ファイルを開き、この新しいヘッダーファイルをインクルードするためのディレクティブを追加します：

    ```cpp
    #include "text_to_speech.h"
    ```

1. `setup`関数内で、`speechToText.init();`の呼び出しの下に以下を追加して、`TextToSpeech`クラスを初期化します：

    ```cpp
    textToSpeech.init();
    ```

1. このコードをビルドし、Wio Terminalにアップロードして、シリアルモニターを通じてテストします。関数アプリが実行中であることを確認してください。

    関数アプリから返された利用可能な音声のリストと、選択された音声が表示されます。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## テキストを音声に変換する

使用する音声が決まったら、それを使用してテキストを音声に変換できます。音声をテキストに変換する場合と同様に、音声を変換する際にもメモリの制約があります。そのため、音声をSDカードに書き込み、ReSpeakerを介して再生する準備をする必要があります。

> 💁 このプロジェクトの以前のレッスンでは、マイクからキャプチャした音声をフラッシュメモリに保存しました。このレッスンでは、Seeedオーディオライブラリを使用してSDカードから音声を再生する方が簡単であるため、SDカードを使用します。

また、考慮すべきもう1つの制約として、音声サービスから提供されるオーディオデータと、Wio Terminalがサポートするフォーマットがあります。通常のコンピューターとは異なり、マイクロコントローラー用のオーディオライブラリはサポートするオーディオフォーマットが非常に限られています。例えば、ReSpeakerを介して音声を再生できるSeeed Arduino Audioライブラリは、44.1KHzのサンプルレートの音声しかサポートしていません。Azure音声サービスは複数のフォーマットで音声を提供できますが、44.1KHzのサンプルレートを使用するものはありません。提供されるのは8KHz、16KHz、24KHz、48KHzのみです。このため、音声を44.1KHzに再サンプリングする必要がありますが、これはWio Terminalのリソース、特にメモリでは対応できません。

このようなデータ操作が必要な場合、特にデータがWeb呼び出しを介して取得される場合は、サーバーレスコードを使用する方が適しています。Wio Terminalはサーバーレス関数を呼び出し、変換するテキストを渡し、サーバーレス関数がテキストを音声に変換するだけでなく、必要なサンプルレートに再サンプリングすることができます。その後、Wio TerminalがSDカードに保存し、ReSpeakerを介して再生するために必要な形式で音声を返すことができます。

### タスク - テキストを音声に変換するサーバーレス関数を作成する

1. VS Codeで`smart-timer-trigger`プロジェクトを開き、仮想環境が有効になっていることを確認してターミナルを開きます。有効でない場合は、ターミナルを終了して再作成してください。

1. このアプリに`text-to-speech`という新しいHTTPトリガーを追加します。VS Codeターミナルで関数アプリプロジェクトのルートフォルダー内から以下のコマンドを使用します：

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    これにより、`text-to-speech`というHTTPトリガーが作成されます。

1. [librosa](https://librosa.org) Pipパッケージには音声を再サンプリングする関数が含まれているため、これを`requirements.txt`ファイルに追加します：

    ```sh
    librosa
    ```

    追加後、VS Codeターミナルで以下のコマンドを使用してPipパッケージをインストールします：

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ Linux（Raspberry Pi OSを含む）を使用している場合、以下のコマンドで`libsndfile`をインストールする必要がある場合があります：
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. テキストを音声に変換するには、音声APIキーを直接使用するのではなく、アクセスキーをリクエストする必要があります。このリクエストにはAPIキーを使用して認証します。`text-to-speech`フォルダー内の`__init__.py`ファイルを開き、すべてのコードを以下のコードに置き換えます：

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    これにより、設定から読み取られるロケーションと音声キーの定数が定義されます。その後、音声サービスのアクセスキーを取得する`get_access_token`関数が定義されます。

1. このコードの下に以下を追加します：

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    これにより、テキストを音声に変換するHTTPトリガーが定義されます。リクエストで送信されたJSONボディから変換するテキスト、言語、音声を抽出し、音声をリクエストするためのSSMLを構築して、アクセスキーを使用してREST APIを呼び出します。このREST API呼び出しは、16ビット、48KHzモノラルWAVファイルとしてエンコードされた音声を返します。この形式は`playback_format`の値で定義され、REST API呼び出しに送信されます。

    その後、`librosa`によって48KHzのサンプルレートから44.1KHzに再サンプリングされ、この音声がバイナリバッファに保存されて返されます。

1. 関数アプリをローカルで実行するか、クラウドにデプロイします。その後、curlのようなツールを使用して、`text-to-timer` HTTPトリガーをテストしたのと同じ方法でこれを呼び出すことができます。JSONボディとして言語、音声、テキストを渡すことを忘れないでください：

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    `<language>`を`en-GB`や`zh-CN`などの言語に置き換えます。`<voice>`を使用したい音声に置き換えます。`<text>`を音声に変換したいテキストに置き換えます。出力をファイルに保存し、WAVファイルを再生できる任意のオーディオプレーヤーで再生できます。

    例えば、"Hello"をUS英語のJenny Neural音声で音声に変換する場合、関数アプリがローカルで実行されているときに以下のcurlコマンドを使用します：

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    これにより、現在のディレクトリに`hello.wav`という名前で音声が保存されます。

> 💁 このコードは[code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions)フォルダーにあります。

### タスク - Wio Terminalから音声を取得する

1. `smart-timer`プロジェクトをVS Codeで開きます（まだ開いていない場合）。

1. `config.h`ヘッダーファイルを開き、関数アプリのURLを追加します：

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    `<URL>`を関数アプリの`text-to-speech` HTTPトリガーのURLに置き換えます。このURLは`TEXT_TO_TIMER_FUNCTION_URL`の値と同じですが、関数名が`text-to-timer`ではなく`text-to-speech`になります。

1. `text_to_speech.h`ヘッダーファイルを開き、`TextToSpeech`クラスの`public`セクションに以下のメソッドを追加します：

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. `convertTextToSpeech`メソッドに、関数アプリに送信するJSONを作成する以下のコードを追加します：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    これにより、言語、音声、テキストがJSONドキュメントに書き込まれ、文字列としてシリアライズされます。

1. この下に、関数アプリを呼び出す以下のコードを追加します：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    これにより、HTTPClientが作成され、JSONドキュメントを使用してテキスト読み上げHTTPトリガーにPOSTリクエストが行われます。

1. 呼び出しが成功した場合、関数アプリ呼び出しから返された生のバイナリデータをSDカード上のファイルにストリームできます。これを行う以下のコードを追加します：

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    このコードはレスポンスを確認し、200（成功）であれば、バイナリデータをSDカードのルートにある`SPEECH.WAV`という名前のファイルにストリームします。

1. このメソッドの最後に、HTTP接続を閉じます：

    ```cpp
    httpClient.end();
    ```

1. 話すべきテキストを音声に変換できるようになりました。`main.cpp`ファイルの`say`関数の最後に以下の行を追加して、話すテキストを音声に変換します：
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### タスク - Wio Terminalでオーディオを再生する

**近日公開**

## 関数アプリをクラウドにデプロイする

関数アプリをローカルで実行する理由は、Linux上の`librosa` Pipパッケージがデフォルトでインストールされていないライブラリに依存しているためです。このライブラリをインストールしないと関数アプリは実行できません。関数アプリはサーバーレスであり、自分で管理できるサーバーが存在しないため、事前にこのライブラリをインストールする方法はありません。

これを解決する方法は、Dockerコンテナを使用して関数アプリをデプロイすることです。このコンテナは、クラウドが関数アプリの新しいインスタンスを起動する必要がある場合（例えば、需要が利用可能なリソースを超えた場合や、関数アプリがしばらく使用されておらずシャットダウンされた場合）にデプロイされます。

Linux上でカスタムコンテナを使用して関数を作成し、Dockerを介してデプロイする手順については、[Microsoft Docsのドキュメント](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python)をご覧ください。

デプロイが完了したら、Wio Terminalのコードを移植してこの関数にアクセスできるようにします：

1. Azure Functionsの証明書を`config.h`に追加します：

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. `<WiFiClient.h>`のすべてのインクルードを`<WiFiClientSecure.h>`に変更します。

1. すべての`WiFiClient`フィールドを`WiFiClientSecure`に変更します。

1. `WiFiClientSecure`フィールドを持つすべてのクラスにコンストラクタを追加し、そのコンストラクタ内で証明書を設定します：

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤訳について、当社は一切の責任を負いません。