<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "012b69d57d898d670adf61304f42a137",
  "translation_date": "2025-08-25T00:09:41+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-set-timer.md",
  "language_code": "ja"
}
-->
# タイマーを設定する - Wio Terminal

このレッスンのこの部分では、サーバーレスコードを呼び出して音声を理解し、その結果に基づいてWio Terminalにタイマーを設定します。

## タイマーを設定する

音声認識から返ってきたテキストは、LUISで処理するためにサーバーレスコードに送信する必要があります。そして、タイマーの秒数を取得します。この秒数を使用してタイマーを設定できます。

マイクロコントローラーはArduinoで複数スレッドをネイティブにサポートしていないため、Pythonや他の高レベル言語で見られるような標準的なタイマークラスはありません。その代わりに、`loop`関数内で経過時間を測定し、時間が経過したときに関数を呼び出すタイマーライブラリを使用できます。

### タスク - テキストをサーバーレス関数に送信する

1. VS Codeで`smart-timer`プロジェクトを開きます（まだ開いていない場合）。

1. `config.h`ヘッダーファイルを開き、関数アプリのURLを追加します：

    ```cpp
    const char *TEXT_TO_TIMER_FUNCTION_URL = "<URL>";
    ```

    `<URL>`を、前のレッスンの最後のステップで取得した関数アプリのURLに置き換えます。このURLは、関数アプリを実行しているローカルマシンのIPアドレスを指します。

1. `src`フォルダに新しいファイルを作成し、`language_understanding.h`と名付けます。このファイルは、認識された音声を関数アプリに送信し、LUISを使用して秒数に変換するクラスを定義するために使用します。

1. このファイルの先頭に以下を追加します：

    ```cpp
    #pragma once
    
    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <WiFiClient.h>
    
    #include "config.h"
    ```

    必要なヘッダーファイルを含めます。

1. `LanguageUnderstanding`というクラスを定義し、このクラスのインスタンスを宣言します：

    ```cpp
    class LanguageUnderstanding
    {
    public:
    private:
    };

    LanguageUnderstanding languageUnderstanding;
    ```

1. 関数アプリを呼び出すために、WiFiクライアントを宣言する必要があります。クラスの`private`セクションに以下を追加します：

    ```cpp
    WiFiClient _client;
    ```

1. クラスの`public`セクションに、関数アプリを呼び出すための`GetTimerDuration`というメソッドを宣言します：

    ```cpp
    int GetTimerDuration(String text)
    {
    }
    ```

1. `GetTimerDuration`メソッド内で、関数アプリに送信するJSONを構築するコードを以下に追加します：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    これにより、`GetTimerDuration`メソッドに渡されたテキストが以下のJSONに変換されます：

    ```json
    {
        "text" : "<text>"
    }
    ```

    `<text>`は関数に渡されたテキストです。

1. この下に、関数アプリを呼び出すコードを追加します：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_TIMER_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    これにより、JSONボディを渡してPOSTリクエストを送信し、レスポンスコードを取得します。

1. この下に以下のコードを追加します：

    ```cpp
    int seconds = 0;
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonObject obj = doc.as<JsonObject>();
        seconds = obj["seconds"].as<int>();
    }
    else
    {
        Serial.print("Failed to understand text - error ");
        Serial.println(httpResponseCode);
    }
    ```

    このコードはレスポンスコードをチェックします。コードが200（成功）の場合、レスポンスボディからタイマーの秒数を取得します。それ以外の場合は、シリアルモニターにエラーを送信し、秒数を0に設定します。

1. このメソッドの最後に以下のコードを追加してHTTP接続を閉じ、秒数を返します：

    ```cpp
    httpClient.end();

    return seconds;
    ```

1. `main.cpp`ファイルで、この新しいヘッダーをインクルードします：

    ```cpp
    #include "speech_to_text.h"
    ```

1. `processAudio`関数の最後で、`GetTimerDuration`メソッドを呼び出してタイマーの秒数を取得します：

    ```cpp
    int total_seconds = languageUnderstanding.GetTimerDuration(text);
    ```

    これにより、`SpeechToText`クラスからのテキストがタイマーの秒数に変換されます。

### タスク - タイマーを設定する

取得した秒数を使用してタイマーを設定します。

1. タイマーを設定するライブラリを追加するために、`platformio.ini`ファイルに以下のライブラリ依存関係を追加します：

    ```ini
    contrem/arduino-timer @ 2.3.0
    ```

1. このライブラリをインクルードする指示を`main.cpp`ファイルに追加します：

    ```cpp
    #include <arduino-timer.h>
    ```

1. `processAudio`関数の上に以下のコードを追加します：

    ```cpp
    auto timer = timer_create_default();
    ```

    このコードは`timer`というタイマーを宣言します。

1. この下に以下のコードを追加します：

    ```cpp
    void say(String text)
    {
        Serial.print("Saying ");
        Serial.println(text);
    }
    ```

    この`say`関数は最終的にテキストを音声に変換しますが、現時点では渡されたテキストをシリアルモニターに書き込むだけです。

1. `say`関数の下に以下のコードを追加します：

    ```cpp
    bool timerExpired(void *announcement)
    {
        say((char *)announcement);
        return false;
    }
    ```

    これはタイマーが終了したときに呼び出されるコールバック関数です。タイマーが終了したときに表示するメッセージが渡されます。タイマーは繰り返し実行することができますが、このコールバックの戻り値で制御します。この場合、`false`を返してタイマーを再実行しないようにします。

1. `processAudio`関数の最後に以下のコードを追加します：

    ```cpp
    if (total_seconds == 0)
    {
        return;
    }

    int minutes = total_seconds / 60;
    int seconds = total_seconds % 60;
    ```

    このコードは合計秒数をチェックし、0の場合は関数呼び出しから戻ります。タイマーが設定されないようにします。その後、合計秒数を分と秒に変換します。

1. このコードの下に、タイマーが開始されたときに表示するメッセージを作成する以下のコードを追加します：

    ```cpp
    String begin_message;
    if (minutes > 0)
    {
        begin_message += minutes;
        begin_message += " minute ";
    }
    if (seconds > 0)
    {
        begin_message += seconds;
        begin_message += " second ";
    }

    begin_message += "timer started.";
    ```

1. この下に、タイマーが終了したときに表示するメッセージを作成する同様のコードを追加します：

    ```cpp
    String end_message("Times up on your ");
    if (minutes > 0)
    {
        end_message += minutes;
        end_message += " minute ";
    }
    if (seconds > 0)
    {
        end_message += seconds;
        end_message += " second ";
    }

    end_message += "timer.";
    ```

1. この後、タイマー開始メッセージを表示します：

    ```cpp
    say(begin_message);
    ```

1. この関数の最後にタイマーを開始します：

    ```cpp
    timer.in(total_seconds * 1000, timerExpired, (void *)(end_message.c_str()));
    ```

    これによりタイマーがトリガーされます。タイマーはミリ秒単位で設定されるため、合計秒数を1,000倍してミリ秒に変換します。`timerExpired`関数がコールバックとして渡され、`end_message`がコールバックに渡される引数として渡されます。このコールバックは`void *`型の引数しか受け取れないため、文字列を適切に変換します。

1. 最後に、タイマーを「動作」させる必要があります。これは`loop`関数内で行います。`loop`関数の最後に以下のコードを追加します：

    ```cpp
    timer.tick();
    ```

1. このコードをビルドし、Wio Terminalにアップロードしてシリアルモニターでテストします。シリアルモニターに`Ready`と表示されたら、Cボタン（左側で電源スイッチに最も近いボタン）を押して話します。4秒間の音声がキャプチャされ、テキストに変換され、関数アプリに送信され、タイマーが設定されます。関数アプリがローカルで実行されていることを確認してください。

    タイマーが開始されたときと終了したときが表示されます。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    Ready.
    Starting recording...
    Finished recording
    Sending speech...
    Speech sent!
    {"RecognitionStatus":"Success","DisplayText":"Set a 2 minute and 27 second timer.","Offset":4700000,"Duration":35300000}
    Set a 2 minute and 27 second timer.
    {"seconds": 147}
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 このコードは[code-timer/wio-terminal](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/wio-terminal)フォルダにあります。

😀 タイマープログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。