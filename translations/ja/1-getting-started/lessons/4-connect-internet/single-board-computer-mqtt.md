<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "90fb93446e03c38f3c0e4009c2471906",
  "translation_date": "2025-08-24T23:10:14+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md",
  "language_code": "ja"
}
-->
# インターネットでナイトライトを制御する - 仮想IoTハードウェアとRaspberry Pi

IoTデバイスは、MQTTを使用して*test.mosquitto.org*と通信し、光センサーの読み取り値を含むテレメトリ値を送信し、LEDを制御するコマンドを受信するようにコード化する必要があります。

このレッスンのこの部分では、Raspberry Piまたは仮想IoTデバイスをMQTTブローカーに接続します。

## MQTTクライアントパッケージをインストールする

MQTTブローカーと通信するために、Pi上または仮想デバイスを使用している場合は仮想環境内でMQTTライブラリのpipパッケージをインストールする必要があります。

### タスク

pipパッケージをインストールする

1. VS Codeでナイトライトプロジェクトを開きます。

1. 仮想IoTデバイスを使用している場合は、ターミナルが仮想環境を実行していることを確認してください。Raspberry Piを使用している場合は仮想環境を使用しません。

1. 次のコマンドを実行してMQTTのpipパッケージをインストールします:

    ```sh
    pip3 install paho-mqtt
    ```

## デバイスをコード化する

デバイスのコード化準備が整いました。

### タスク

デバイスコードを書く

1. `app.py`ファイルの先頭に次のインポートを追加します:

    ```python
    import paho.mqtt.client as mqtt
    ```

    `paho.mqtt.client`ライブラリは、アプリがMQTTを介して通信することを可能にします。

1. 光センサーとLEDの定義の後に次のコードを追加します:

    ```python
    id = '<ID>'

    client_name = id + 'nightlight_client'
    ```

    `<ID>`を、このデバイスクライアントの名前として使用されるユニークなIDに置き換えてください。このIDは後で、このデバイスが公開および購読するトピックにも使用されます。*test.mosquitto.org*ブローカーは公開されており、多くの人々、特にこの課題に取り組んでいる他の学生によって使用されています。ユニークなMQTTクライアント名とトピック名を持つことで、コードが他の人と衝突することを防ぎます。このIDは後でサーバーコードを作成する際にも必要になります。

    > 💁 [GUIDGen](https://www.guidgen.com)のようなウェブサイトを使用してユニークなIDを生成することができます。

    `client_name`は、このMQTTクライアントのブローカー上でのユニークな名前です。

1. 次のコードをこの新しいコードの下に追加して、MQTTクライアントオブジェクトを作成し、MQTTブローカーに接続します:

    ```python
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()

    print("MQTT connected!")
    ```

    このコードはクライアントオブジェクトを作成し、公開MQTTブローカーに接続し、バックグラウンドスレッドで実行される処理ループを開始して、購読しているトピックのメッセージをリスニングします。

1. 前の課題のコードを実行したのと同じ方法でコードを実行します。仮想IoTデバイスを使用している場合は、CounterFitアプリが実行されており、光センサーとLEDが正しいピンに作成されていることを確認してください。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Light level: 0
    Light level: 0
    ```

> 💁 このコードは[code-mqtt/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/virtual-device)フォルダーまたは[code-mqtt/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/pi)フォルダーにあります。

😀 デバイスをMQTTブローカーに正常に接続しました。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤訳について、当社は一切の責任を負いません。