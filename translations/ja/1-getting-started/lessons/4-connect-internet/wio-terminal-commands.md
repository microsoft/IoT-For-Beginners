<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6754c915dae64ba70fcd5e52c37f3adf",
  "translation_date": "2025-08-24T23:12:59+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-commands.md",
  "language_code": "ja"
}
-->
# インターネットでナイトライトを操作する - Wio Terminal

このレッスンのこの部分では、MQTTブローカーから送信されるコマンドをWio Terminalで受信する方法を学びます。

## コマンドを受信する

次のステップでは、MQTTブローカーから送信されるコマンドを受信し、それに応答します。

### タスク

コマンドを受信する。

1. VS Codeでナイトライトプロジェクトを開きます。

1. `config.h`ファイルの末尾に以下のコードを追加して、コマンド用のトピック名を定義します。

    ```cpp
    const string SERVER_COMMAND_TOPIC = ID + "/commands";
    ```

    `SERVER_COMMAND_TOPIC`は、デバイスがLEDコマンドを受信するために購読するトピックです。

1. MQTTクライアントが再接続された際にコマンドトピックを購読するように、`reconnectMQTTClient`関数の末尾に以下の行を追加します。

    ```cpp
    client.subscribe(SERVER_COMMAND_TOPIC.c_str());
    ```

1. `reconnectMQTTClient`関数の下に以下のコードを追加します。

    ```cpp
    void clientCallback(char *topic, uint8_t *payload, unsigned int length)
    {
        char buff[length + 1];
        for (int i = 0; i < length; i++)
        {
            buff[i] = (char)payload[i];
        }
        buff[length] = '\0';
    
        Serial.print("Message received:");
        Serial.println(buff);
    
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, buff);
        JsonObject obj = doc.as<JsonObject>();
    
        bool led_on = obj["led_on"];
    
        if (led_on)
            digitalWrite(D0, HIGH);
        else
            digitalWrite(D0, LOW);
    }
    ```

    この関数は、MQTTクライアントがサーバーからメッセージを受信した際に呼び出されるコールバックです。

    メッセージは符号なし8ビット整数の配列として受信されるため、テキストとして扱うには文字配列に変換する必要があります。

    メッセージにはJSONドキュメントが含まれており、ArduinoJsonライブラリを使用してデコードされます。JSONドキュメントの`led_on`プロパティを読み取り、その値に応じてLEDをオンまたはオフにします。

1. `createMQTTClient`関数に以下のコードを追加します。

    ```cpp
    client.setCallback(clientCallback);
    ```

    このコードは、MQTTブローカーからメッセージを受信した際に呼び出されるコールバックとして`clientCallback`を設定します。

    > 💁 `clientCallback`ハンドラーは購読しているすべてのトピックに対して呼び出されます。後で複数のトピックをリッスンするコードを書く場合、コールバック関数に渡される`topic`パラメータからメッセージが送信されたトピックを取得できます。

1. コードをWio Terminalにアップロードし、シリアルモニターを使用してMQTTブローカーに送信される光レベルを確認します。

1. 実際のデバイスまたは仮想デバイスで検出される光レベルを調整します。ターミナルでメッセージが受信され、コマンドが送信される様子が確認できます。また、光レベルに応じてLEDがオンまたはオフになる様子も確認できます。

> 💁 このコードは[code-commands/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/wio-terminal)フォルダーにあります。

😀 MQTTブローカーからのコマンドに応答するようにデバイスをコーディングすることに成功しました。

**免責事項**:  
本書類は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があります。原文（元の言語で記載された文書）が信頼できる情報源として優先されるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。