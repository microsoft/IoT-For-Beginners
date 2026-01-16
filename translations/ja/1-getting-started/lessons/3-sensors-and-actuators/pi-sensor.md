<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-24T23:13:57+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "ja"
}
-->
# ナイトライトを作る - Raspberry Pi

このレッスンでは、Raspberry Piに光センサーを追加します。

## ハードウェア

このレッスンで使用するセンサーは、光を電気信号に変換する[フォトダイオード](https://wikipedia.org/wiki/Photodiode)を使用した**光センサー**です。このセンサーはアナログセンサーで、0から1,000までの整数値を送信し、光の相対量を示しますが、[ルクス](https://wikipedia.org/wiki/Lux)のような標準的な単位には対応していません。

光センサーは外部のGroveセンサーであり、Raspberry PiのGrove Base hatに接続する必要があります。

### 光センサーを接続する

光レベルを検出するために使用するGrove光センサーをRaspberry Piに接続します。

#### タスク - 光センサーを接続する

光センサーを接続します。

![Grove光センサー](../../../../../translated_images/ja/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Groveケーブルの片方の端を光センサーモジュールのソケットに差し込みます。このケーブルは一方向にしか差し込めません。

1. Raspberry Piの電源を切った状態で、Groveケーブルのもう片方の端をPiに取り付けられたGrove Base hatの**A0**と記されたアナログソケットに接続します。このソケットはGPIOピンの隣のソケット列の右から2番目にあります。

![ソケットA0に接続されたGrove光センサー](../../../../../translated_images/ja/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## 光センサーをプログラムする

これで、Grove光センサーを使用してデバイスをプログラムできます。

### タスク - 光センサーをプログラムする

デバイスをプログラムします。

1. Piの電源を入れ、起動を待ちます。

1. VS Codeで、前の課題で作成したナイトライトプロジェクトを開きます。Pi上で直接実行するか、Remote SSH拡張機能を使用して接続します。

1. `app.py`ファイルを開き、すべてのコードを削除します。

1. 以下のコードを`app.py`ファイルに追加して、必要なライブラリをインポートします：

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time`ステートメントは、この課題で後ほど使用する`time`モジュールをインポートします。

    `from grove.grove_light_sensor_v1_2 import GroveLightSensor`ステートメントは、Grove Pythonライブラリから`GroveLightSensor`をインポートします。このライブラリにはGrove光センサーと対話するためのコードが含まれており、Piのセットアップ時にグローバルにインストールされています。

1. 上記のコードの後に以下のコードを追加して、光センサーを管理するクラスのインスタンスを作成します：

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)`という行は、光センサーが接続されているアナログGroveピン**A0**に接続する`GroveLightSensor`クラスのインスタンスを作成します。

1. 上記のコードの後に無限ループを追加して、光センサーの値をポーリングし、コンソールに出力します：

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    これにより、`GroveLightSensor`クラスの`light`プロパティを使用して0-1,023のスケールで現在の光レベルを読み取ります。このプロパティはピンからアナログ値を読み取ります。この値はコンソールに出力されます。

1. ループの最後に1秒間の短いスリープを追加します。光レベルを継続的にチェックする必要はありません。スリープを追加することでデバイスの消費電力を削減できます。

    ```python
    time.sleep(1)
    ```

1. VS Codeのターミナルから以下を実行してPythonアプリを実行します：

    ```sh
    python3 app.py
    ```

    光の値がコンソールに出力されます。光センサーを覆ったり外したりすると、値が変化します：

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 このコードは[code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi)フォルダーにあります。

😀 ナイトライトプログラムにセンサーを追加することに成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。