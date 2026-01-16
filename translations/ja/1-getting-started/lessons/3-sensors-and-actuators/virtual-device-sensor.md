<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-24T23:24:54+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "ja"
}
-->
# ナイトライトを作る - 仮想IoTハードウェア

このレッスンでは、仮想IoTデバイスに光センサーを追加します。

## 仮想ハードウェア

ナイトライトには、CounterFitアプリで作成された1つのセンサーが必要です。

センサーは**光センサー**です。物理的なIoTデバイスでは、光を電気信号に変換する[フォトダイオード](https://wikipedia.org/wiki/Photodiode)が使用されます。光センサーはアナログセンサーで、標準的な単位（例えば[lux](https://wikipedia.org/wiki/Lux)）に対応しない相対的な光量を示す整数値を送信します。

### CounterFitにセンサーを追加する

仮想光センサーを使用するには、CounterFitアプリに追加する必要があります。

#### タスク - CounterFitにセンサーを追加する

CounterFitアプリに光センサーを追加します。

1. 前の課題で使用したCounterFitウェブアプリが実行中であることを確認してください。実行していない場合は、起動してください。

1. 光センサーを作成します：

    1. *Sensors*ペインの*Create sensor*ボックスで、*Sensor type*ドロップダウンを開き、*Light*を選択します。

    1. *Units*は*NoUnits*のままにします。

    1. *Pin*が*0*に設定されていることを確認します。

    1. **Add**ボタンを選択して、Pin 0に光センサーを作成します。

    ![光センサーの設定](../../../../../translated_images/ja/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    光センサーが作成され、センサーリストに表示されます。

    ![作成された光センサー](../../../../../translated_images/ja/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## 光センサーをプログラムする

デバイスは、内蔵の光センサーを使用するようにプログラムできます。

### タスク - 光センサーをプログラムする

デバイスをプログラムします。

1. 前の課題で作成したVS Codeのナイトライトプロジェクトを開きます。必要に応じて、仮想環境を使用していることを確認するためにターミナルを終了して再作成してください。

1. `app.py`ファイルを開きます。

1. 必要なライブラリをインポートするために、以下のコードを`app.py`ファイルの上部にある`import`文の部分に追加します：

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    `import time`文は、後で使用するPythonの`time`モジュールをインポートします。

    `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor`文は、CounterFit Grove shim Pythonライブラリから`GroveLightSensor`をインポートします。このライブラリには、CounterFitアプリで作成された光センサーとやり取りするコードが含まれています。

1. 光センサーを管理するクラスのインスタンスを作成するために、以下のコードをファイルの下部に追加します：

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    `light_sensor = GroveLightSensor(0)`行は、Pin **0**に接続された`GroveLightSensor`クラスのインスタンスを作成します。このPinは、CounterFit Groveで光センサーが接続されているPinです。

1. 上記のコードの後に無限ループを追加し、光センサーの値をポーリングしてコンソールに出力します：

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    これにより、`GroveLightSensor`クラスの`light`プロパティを使用して現在の光レベルを読み取ります。このプロパティはPinからアナログ値を読み取り、その値をコンソールに出力します。

1. `while`ループの最後に1秒間の短いスリープを追加します。光レベルを継続的にチェックする必要はありません。スリープを追加することでデバイスの消費電力を削減できます。

    ```python
    time.sleep(1)
    ```

1. VS Codeターミナルから以下を実行してPythonアプリを実行します：

    ```sh
    python3 app.py
    ```

    光の値がコンソールに出力されます。最初はこの値が0になります。

1. CounterFitアプリから、アプリが読み取る光センサーの値を変更します。以下の2つの方法のいずれかで変更できます：

    * 光センサーの*Value*ボックスに数値を入力し、**Set**ボタンを選択します。入力した数値がセンサーから返される値になります。

    * *Random*チェックボックスをオンにし、*Min*と*Max*値を入力して**Set**ボタンを選択します。センサーが値を読み取るたびに、*Min*と*Max*の間のランダムな数値が読み取られます。

    設定した値がコンソールに出力されます。*Value*や*Random*設定を変更して値を変化させてください。

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 このコードは[code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device)フォルダーにあります。

😀 ナイトライトプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。