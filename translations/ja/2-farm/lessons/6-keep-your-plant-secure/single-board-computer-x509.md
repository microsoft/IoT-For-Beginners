<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9aea84bcc7520222b0e1c50469d62d6a",
  "translation_date": "2025-08-24T22:57:40+00:00",
  "source_file": "2-farm/lessons/6-keep-your-plant-secure/single-board-computer-x509.md",
  "language_code": "ja"
}
-->
# デバイスコードで X.509 証明書を使用する - 仮想 IoT ハードウェアと Raspberry Pi

このレッスンのこの部分では、仮想 IoT デバイスまたは Raspberry Pi を X.509 証明書を使用して IoT Hub に接続します。

## デバイスを IoT Hub に接続する

次のステップは、X.509 証明書を使用してデバイスを IoT Hub に接続することです。

### タスク - IoT Hub に接続する

1. キーと証明書ファイルを IoT デバイスコードが含まれるフォルダーにコピーします。VS Code Remote SSH を使用して Raspberry Pi を操作している場合で、PC または Mac 上でキーを作成した場合は、VS Code のエクスプローラーにファイルをドラッグ＆ドロップしてコピーできます。

1. `app.py` ファイルを開きます。

1. X.509 証明書を使用して接続するには、IoT Hub のホスト名と X.509 証明書が必要です。デバイスクライアントを作成する前に、次のコードを追加してホスト名を含む変数を作成します：

    ```python
    host_name = "<host_name>"
    ```

    `<host_name>` を IoT Hub のホスト名に置き換えます。この情報は `connection_string` の `HostName` セクションから取得できます。ホスト名は IoT Hub の名前で、`.azure-devices.net` で終わります。

1. この下に、デバイス ID を含む変数を宣言します：

    ```python
    device_id = "soil-moisture-sensor-x509"
    ```

1. X.509 ファイルを含む `X509` クラスのインスタンスが必要です。`azure.iot.device` モジュールからインポートするクラスのリストに `X509` を追加します：

    ```python
    from azure.iot.device import IoTHubDeviceClient, Message, MethodResponse, X509
    ```

1. 証明書とキーのファイルを使用して `X509` クラスのインスタンスを作成します。これを `host_name` 宣言の下に追加します：

    ```python
    x509 = X509("./soil-moisture-sensor-x509-cert.pem", "./soil-moisture-sensor-x509-key.pem")
    ```

    これにより、以前作成した `soil-moisture-sensor-x509-cert.pem` と `soil-moisture-sensor-x509-key.pem` ファイルを使用して `X509` クラスが作成されます。

1. 接続文字列から `device_client` を作成するコード行を、次のコードに置き換えます：

    ```python
    device_client = IoTHubDeviceClient.create_from_x509_certificate(x509, host_name, device_id)
    ```

    これにより、接続文字列の代わりに X.509 証明書を使用して接続します。

1. `connection_string` 変数を含む行を削除します。

1. コードを実行します。IoT Hub に送信されるメッセージを監視し、これまでと同様にダイレクトメソッドリクエストを送信します。デバイスが接続し、土壌湿度の測定値を送信し、ダイレクトメソッドリクエストを受信する様子が確認できます。

> 💁 このコードは [code/pi](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/pi) または [code/virtual-device](../../../../../2-farm/lessons/6-keep-your-plant-secure/code/virtual-device) フォルダーにあります。

😀 土壌湿度センサーのプログラムが X.509 証明書を使用して IoT Hub に接続されました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。