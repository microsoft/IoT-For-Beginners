<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-24T23:08:43+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "ja"
}
-->
# インターネットでナイトライトを操作する - Wio Terminal

このレッスンでは、Wio TerminalからMQTTブローカーに光レベルのテレメトリを送信します。

## JSON Arduinoライブラリをインストールする

MQTTでメッセージを送信する一般的な方法はJSONを使用することです。Arduinoには、JSONドキュメントの読み書きを簡単にするためのライブラリがあります。

### タスク

Arduino JSONライブラリをインストールします。

1. VS Codeでナイトライトプロジェクトを開きます。

1. `platformio.ini`ファイルの`lib_deps`リストに以下の行を追加します：

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    これにより、Arduino JSONライブラリ[ArduinoJson](https://arduinojson.org)がインポートされます。

## テレメトリを送信する

次のステップは、テレメトリを含むJSONドキュメントを作成し、それをMQTTブローカーに送信することです。

### タスク - テレメトリを送信する

MQTTブローカーにテレメトリを送信します。

1. MQTTブローカーのテレメトリトピック名を定義するために、以下のコードを`config.h`ファイルの末尾に追加します：

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC`は、デバイスが光レベルを送信するトピックです。

1. `main.cpp`ファイルを開きます。

1. ファイルの先頭に以下の`#include`ディレクティブを追加します：

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. `loop`関数内の`delay`の直前に以下のコードを追加します：

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    このコードは光レベルを読み取り、ArduinoJsonを使用してこのレベルを含むJSONドキュメントを作成します。その後、これを文字列にシリアライズし、MQTTクライアントによってテレメトリMQTTトピックに公開されます。

1. コードをWio Terminalにアップロードし、シリアルモニターを使用して光レベルがMQTTブローカーに送信されていることを確認します。

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 このコードは[code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal)フォルダーにあります。

😀 デバイスからテレメトリを正常に送信しました。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確さが含まれる可能性があることをご承知おきください。原文（元の言語で記載された文書）が信頼できる情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。