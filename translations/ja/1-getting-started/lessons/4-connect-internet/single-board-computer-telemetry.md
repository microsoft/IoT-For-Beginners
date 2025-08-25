<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-24T23:01:09+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "ja"
}
-->
# インターネットでナイトライトを操作する - 仮想IoTハードウェアとRaspberry Pi

このレッスンのこの部分では、Raspberry Piまたは仮想IoTデバイスからMQTTブローカーに光レベルのテレメトリを送信します。

## テレメトリを送信する

次のステップは、テレメトリを含むJSONドキュメントを作成し、それをMQTTブローカーに送信することです。

### タスク

MQTTブローカーにテレメトリを送信します。

1. VS Codeでナイトライトプロジェクトを開きます。

1. 仮想IoTデバイスを使用している場合は、ターミナルが仮想環境を実行していることを確認してください。Raspberry Piを使用している場合は、仮想環境を使用しません。

1. `app.py`ファイルの先頭に次のインポートを追加します：

    ```python
    import json
    ```

    `json`ライブラリは、テレメトリをJSONドキュメントとしてエンコードするために使用されます。

1. `client_name`の宣言の後に次のコードを追加します：

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic`は、デバイスが光レベルを公開するMQTTトピックです。

1. ファイルの最後にある`while True:`ループの内容を次のコードに置き換えます：

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    このコードは、光レベルをJSONドキュメントにパッケージ化し、それをMQTTブローカーに公開します。その後、メッセージ送信頻度を減らすためにスリープします。

1. 前の課題のコードを実行したのと同じ方法でコードを実行します。仮想IoTデバイスを使用している場合は、CounterFitアプリが実行されており、光センサーとLEDが正しいピンに作成されていることを確認してください。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 このコードは [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) フォルダーまたは [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) フォルダーにあります。

😀 デバイスからテレメトリを正常に送信しました。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤訳について、当社は一切の責任を負いません。