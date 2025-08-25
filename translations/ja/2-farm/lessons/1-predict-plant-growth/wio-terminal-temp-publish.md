<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-24T22:05:56+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "ja"
}
-->
# 温度を公開する - Wio Terminal

このレッスンのこの部分では、Wio Terminalで検出された温度値をMQTTを通じて公開し、後でGDDを計算するために使用できるようにします。

## 温度を公開する

温度が読み取られると、それをMQTTを通じて公開し、値を読み取り、GDD計算の準備として保存する「サーバー」コードに送ることができます。マイクロコントローラーはインターネットから時間を読み取ったり、リアルタイムクロックで時間を追跡したりする機能を標準で備えていません。そのため、必要なハードウェアがある場合はデバイスをプログラムする必要があります。

このレッスンを簡略化するために、センサーのデータと一緒に時間を送信することはせず、メッセージを受信した後にサーバーコード側で時間を追加することにします。

### タスク

デバイスをプログラムして温度データを公開します。

1. `temperature-sensor` Wio Terminalプロジェクトを開きます。

1. レッスン4で行った手順を繰り返してMQTTに接続し、テレメトリを送信します。同じ公開Mosquittoブローカーを使用します。

    この手順は以下の通りです：

    - `.ini`ファイルにSeeed WiFiとMQTTライブラリを追加する
    - WiFiに接続するための設定ファイルとコードを追加する
    - MQTTブローカーに接続するコードを追加する
    - テレメトリを公開するコードを追加する

    > ⚠️ 必要に応じて、[MQTTに接続する手順](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md)や[テレメトリを送信する手順](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md)を参照してください。

1. `config.h`ヘッダーファイル内の`CLIENT_NAME`がこのプロジェクトを反映していることを確認してください：

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. テレメトリについては、光の値を送信する代わりに、DHTセンサーから読み取った温度値をJSONドキュメントの`temperature`というプロパティとして送信するように`main.cpp`の`loop`関数を変更してください：

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. 温度値は頻繁に読み取る必要はありません。短時間で大きく変化することはないため、`loop`関数内の`delay`を10分に設定してください：

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay`関数はミリ秒単位で時間を受け取るため、読みやすくするために計算結果として値を渡します。1秒は1,000ms、1分は60秒なので、10 x (1分の60秒) x (1秒の1000ms)で10分の遅延が得られます。

1. これをWio Terminalにアップロードし、シリアルモニターを使用してMQTTブローカーに送信される温度を確認してください。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 このコードは[code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal)フォルダーにあります。

😀 デバイスからテレメトリとして温度を正常に公開しました。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤った解釈について、当方は責任を負いません。