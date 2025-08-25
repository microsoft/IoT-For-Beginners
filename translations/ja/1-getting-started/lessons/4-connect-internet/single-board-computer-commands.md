<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c527ce85d69b1a3875366ec61cbed8aa",
  "translation_date": "2025-08-24T23:00:22+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-commands.md",
  "language_code": "ja"
}
-->
# インターネット経由でナイトライトを制御する - 仮想IoTハードウェアとRaspberry Pi

このレッスンのこの部分では、MQTTブローカーから送信されるコマンドをRaspberry Piまたは仮想IoTデバイスで受信する方法を学びます。

## コマンドを購読する

次のステップは、MQTTブローカーから送信されるコマンドを購読し、それに応答することです。

### タスク

コマンドを購読します。

1. VS Codeでナイトライトプロジェクトを開きます。

1. 仮想IoTデバイスを使用している場合は、ターミナルで仮想環境が実行されていることを確認してください。Raspberry Piを使用している場合は、仮想環境を使用しません。

1. `client_telemetry_topic`の定義の後に、次のコードを追加します：

    ```python
    server_command_topic = id + '/commands'
    ```

    `server_command_topic`は、デバイスがLEDコマンドを受信するために購読するMQTTトピックです。

1. メインループの直前、`mqtt_client.loop_start()`行の後に、次のコードを追加します：

    ```python
    def handle_command(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['led_on']:
            led.on()
        else:
            led.off()
    
    mqtt_client.subscribe(server_command_topic)
    mqtt_client.on_message = handle_command
    ```

    このコードは、`handle_command`という関数を定義します。この関数は、メッセージをJSONドキュメントとして読み取り、`led_on`プロパティの値を確認します。この値が`True`に設定されている場合はLEDが点灯し、それ以外の場合は消灯します。

    MQTTクライアントは、サーバーがメッセージを送信するトピックを購読し、メッセージを受信したときに`handle_command`関数を呼び出すように設定します。

    > 💁 `on_message`ハンドラーは、購読しているすべてのトピックに対して呼び出されます。後で複数のトピックをリッスンするコードを書く場合、ハンドラー関数に渡される`message`オブジェクトからメッセージが送信されたトピックを取得できます。

1. 前の課題のコードを実行したのと同じ方法でコードを実行します。仮想IoTデバイスを使用している場合は、CounterFitアプリが実行されており、光センサーとLEDが正しいピンに作成されていることを確認してください。

1. 物理デバイスまたは仮想デバイスで検出される光レベルを調整します。受信したメッセージと送信されたコマンドがターミナルに表示されます。また、光レベルに応じてLEDが点灯および消灯します。

> 💁 このコードは、[code-commands/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/virtual-device)フォルダーまたは[code-commands/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/pi)フォルダーにあります。

😀 MQTTブローカーからのコマンドに応答するようにデバイスをコーディングすることに成功しました。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確さが含まれる可能性があることをご承知おきください。元の言語で記載された原文が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の利用に起因する誤解や誤認について、当方は一切の責任を負いません。