<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-24T22:02:34+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "ja"
}
-->
# 温度を公開する - 仮想IoTハードウェアとRaspberry Pi

このレッスンのこの部分では、Raspberry Piまたは仮想IoTデバイスで検出された温度値をMQTTを介して公開し、後でGDDを計算するために使用できるようにします。

## 温度を公開する

温度が読み取られたら、それをMQTTを介して「サーバー」コードに公開できます。このコードは値を読み取り、GDD計算に使用するために保存します。

### タスク - 温度を公開する

デバイスをプログラムして温度データを公開します。

1. `temperature-sensor`アプリプロジェクトがまだ開いていない場合は開きます。

1. レッスン4で行った手順を繰り返して、MQTTに接続し、テレメトリを送信します。同じ公開Mosquittoブローカーを使用します。

    この手順は以下の通りです：

    - MQTTのpipパッケージを追加する
    - MQTTブローカーに接続するコードを追加する
    - テレメトリを公開するコードを追加する

    > ⚠️ 必要に応じて、[MQTTに接続する手順](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md)および[テレメトリを送信する手順](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md)を参照してください（レッスン4）。

1. `client_name`がこのプロジェクトの名前を反映していることを確認してください：

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. テレメトリについては、光の値を送信する代わりに、DHTセンサーから読み取った温度値をJSONドキュメントの`temperature`というプロパティに送信します：

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. 温度値は頻繁に読み取る必要はありません。短時間で大きく変化することはないため、`time.sleep`を10分に設定します：

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 `sleep`関数は秒単位で時間を取るため、読みやすくするために値は計算結果として渡されます。1分は60秒なので、10 x (1分あたり60秒)で10分の遅延となります。

1. 前の課題のコードを実行したのと同じ方法でコードを実行します。仮想IoTデバイスを使用している場合は、CounterFitアプリが実行中であり、湿度センサーと温度センサーが正しいピンに作成されていることを確認してください。

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 このコードは[code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device)フォルダーまたは[code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi)フォルダーにあります。

😀 デバイスからテレメトリとして温度を正常に公開しました。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された文書を正式な情報源としてお考えください。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当社は責任を負いません。