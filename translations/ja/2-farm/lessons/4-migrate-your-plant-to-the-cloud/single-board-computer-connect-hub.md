<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ac42e284a7222c0e83d2d43231a364f",
  "translation_date": "2025-08-24T22:49:11+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/single-board-computer-connect-hub.md",
  "language_code": "ja"
}
-->
# IoTデバイスをクラウドに接続する - 仮想IoTハードウェアとRaspberry Pi

このレッスンのこの部分では、仮想IoTデバイスまたはRaspberry PiをIoT Hubに接続し、テレメトリを送信し、コマンドを受信します。

## デバイスをIoT Hubに接続する

次のステップは、デバイスをIoT Hubに接続することです。

### タスク - IoT Hubに接続する

1. VS Codeで`soil-moisture-sensor`フォルダーを開きます。仮想IoTデバイスを使用している場合は、ターミナルで仮想環境が実行されていることを確認してください。

1. いくつかの追加のPipパッケージをインストールします:

    ```sh
    pip3 install azure-iot-device
    ```

    `azure-iot-device`は、IoT Hubと通信するためのライブラリです。

1. 以下のインポートを既存のインポートの下にある`app.py`ファイルの冒頭に追加します:

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse
    ```

    このコードは、IoT Hubと通信するためのSDKをインポートします。

1. `import paho.mqtt.client as mqtt`の行を削除します。このライブラリはもう必要ありません。MQTTコード全体を削除し、トピック名、`mqtt_client`を使用するコード、および`handle_command`を含むすべてを削除します。ただし、`while True:`ループは保持し、このループ内の`mqtt_client.publish`行だけを削除してください。

1. インポート文の下に以下のコードを追加します:

    ```python
    connection_string = "<connection string>"
    ```

    `<connection string>`を、このレッスンの前半で取得したデバイスの接続文字列に置き換えてください。

    > 💁 これは最善の方法ではありません。接続文字列はソースコードに保存すべきではありません。ソースコード管理にチェックインされ、誰でも見つけることができる可能性があります。ここでは簡単さを優先してこの方法を使用しています。理想的には、環境変数や[`python-dotenv`](https://pypi.org/project/python-dotenv/)のようなツールを使用するべきです。これについては次のレッスンで詳しく学びます。

1. このコードの下に、IoT Hubと通信できるデバイスクライアントオブジェクトを作成し、接続するための以下のコードを追加します:

    ```python
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)

    print('Connecting')
    device_client.connect()
    print('Connected')
    ```

1. このコードを実行します。デバイスが接続されるのが確認できます。

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Connecting
    Connected
    Soil moisture: 379
    ```

## テレメトリを送信する

デバイスが接続されたので、MQTTブローカーではなくIoT Hubにテレメトリを送信できます。

### タスク - テレメトリを送信する

1. `while True`ループ内のスリープの直前に以下のコードを追加します:

    ```python
    message = Message(json.dumps({ 'soil_moisture': soil_moisture }))
    device_client.send_message(message)
    ```

    このコードは、土壌湿度の読み取り値をJSON文字列として含むIoT Hubの`Message`を作成し、デバイスからクラウドへのメッセージとしてIoT Hubに送信します。

## コマンドを処理する

デバイスは、リレーを制御するためにサーバーコードから送信されるコマンドを処理する必要があります。これは直接メソッドリクエストとして送信されます。

## タスク - 直接メソッドリクエストを処理する

1. `while True`ループの前に以下のコードを追加します:

    ```python
    def handle_method_request(request):
        print("Direct method received - ", request.name)
    
        if request.name == "relay_on":
            relay.on()
        elif request.name == "relay_off":
            relay.off()    
    ```

    このコードは、IoT Hubから直接メソッドが呼び出されたときに呼び出される`handle_method_request`メソッドを定義します。各直接メソッドには名前があり、このコードはリレーをオンにする`relay_on`メソッドとリレーをオフにする`relay_off`メソッドを期待します。

    > 💁 これを単一の直接メソッドリクエストとして実装し、リクエストオブジェクトから利用可能なペイロードでリレーの希望する状態を渡すこともできます。

1. 直接メソッドには、呼び出し元のコードに処理されたことを伝える応答が必要です。`handle_method_request`関数の最後に以下のコードを追加して、リクエストへの応答を作成します:

    ```python
    method_response = MethodResponse.create_from_method_request(request, 200)
    device_client.send_method_response(method_response)
    ```

    このコードは、HTTPステータスコード200を持つ直接メソッドリクエストへの応答を送信し、これをIoT Hubに返します。

1. この関数定義の下に以下のコードを追加します:

    ```python
    device_client.on_method_request_received = handle_method_request
    ```

    このコードは、直接メソッドが呼び出されたときにIoT Hubクライアントが`handle_method_request`関数を呼び出すように指示します。

> 💁 このコードは[code/pi](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/pi)または[code/virtual-device](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/virtual-device)フォルダーにあります。

😀 土壌湿度センサーのプログラムがIoT Hubに接続されました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。