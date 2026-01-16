<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "70e5a428b607cd5a9a4f422c2a4df03d",
  "translation_date": "2025-08-24T22:07:17+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/virtual-device-temp.md",
  "language_code": "ja"
}
-->
# 温度を測定する - 仮想IoTハードウェア

このレッスンでは、仮想IoTデバイスに温度センサーを追加します。

## 仮想ハードウェア

仮想IoTデバイスでは、シミュレートされたGrove Digital Humidity and Temperatureセンサーを使用します。これにより、物理的なGrove DHT11センサーを使用する場合と同じようにこのラボを進めることができます。

このセンサーは**温度センサー**と**湿度センサー**を組み合わせたものですが、このラボでは温度センサーのコンポーネントにのみ注目します。物理的なIoTデバイスでは、温度センサーは[サーミスタ](https://wikipedia.org/wiki/Thermistor)であり、温度変化による抵抗の変化を感知して温度を測定します。温度センサーは通常デジタルセンサーであり、内部で測定された抵抗を摂氏（またはケルビン、華氏）の温度に変換します。

### CounterFitにセンサーを追加する

仮想湿度および温度センサーを使用するには、CounterFitアプリに2つのセンサーを追加する必要があります。

#### タスク - CounterFitにセンサーを追加する

CounterFitアプリに湿度センサーと温度センサーを追加します。

1. `temperature-sensor`というフォルダーに新しいPythonアプリを作成し、`app.py`という単一のファイルとPython仮想環境を作成します。そしてCounterFitのpipパッケージを追加します。

    > ⚠️ 必要に応じて[レッスン1でのCounterFit Pythonプロジェクトの作成と設定手順](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)を参照してください。

1. DHT11センサー用のCounterFitシムをインストールするための追加のPipパッケージをインストールします。この操作は仮想環境が有効化されたターミナルで行ってください。

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. CounterFitウェブアプリが実行中であることを確認します。

1. 湿度センサーを作成します：

    1. *Sensors*ペインの*Create sensor*ボックスで、*Sensor type*ドロップダウンを開き、*Humidity*を選択します。

    1. *Units*は*Percentage*のままにします。

    1. *Pin*が*5*に設定されていることを確認します。

    1. **Add**ボタンを選択して、Pin 5に湿度センサーを作成します。

    ![湿度センサーの設定](../../../../../translated_images/ja/counterfit-create-humidity-sensor.2750e27b6f30e09cf4e22101defd5252710717620816ab41ba688f91f757c49a.png)

    湿度センサーが作成され、センサーリストに表示されます。

    ![作成された湿度センサー](../../../../../translated_images/ja/counterfit-humidity-sensor.7b12f7f339e430cb26c8211d2dba4ef75261b353a01da0932698b5bebd693f27.png)

1. 温度センサーを作成します：

    1. *Sensors*ペインの*Create sensor*ボックスで、*Sensor type*ドロップダウンを開き、*Temperature*を選択します。

    1. *Units*は*Celsius*のままにします。

    1. *Pin*が*6*に設定されていることを確認します。

    1. **Add**ボタンを選択して、Pin 6に温度センサーを作成します。

    ![温度センサーの設定](../../../../../translated_images/ja/counterfit-create-temperature-sensor.199350ed34f7343d79dccbe95eaf6c11d2121f03d1c35ab9613b330c23f39b29.png)

    温度センサーが作成され、センサーリストに表示されます。

    ![作成された温度センサー](../../../../../translated_images/ja/counterfit-temperature-sensor.f0560236c96a9016bafce7f6f792476fe3367bc6941a1f7d5811d144d4bcbfff.png)

## 温度センサーアプリをプログラムする

CounterFitセンサーを使用して温度センサーアプリをプログラムします。

### タスク - 温度センサーアプリをプログラムする

温度センサーアプリをプログラムします。

1. `temperature-sensor`アプリがVS Codeで開かれていることを確認します。

1. `app.py`ファイルを開きます。

1. CounterFitにアプリを接続するために、以下のコードを`app.py`の先頭に追加します：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 必要なライブラリをインポートするために、以下のコードを`app.py`ファイルに追加します：

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    `from seeed_dht import DHT`ステートメントは、`counterfit_shims_seeed_python_dht`モジュールから`DHT`センサークラスをインポートし、仮想Grove温度センサーとやり取りするためのシムを提供します。

1. 仮想湿度および温度センサーを管理するクラスのインスタンスを作成するために、以下のコードを上記のコードの後に追加します：

    ```python
    sensor = DHT("11", 5)
    ```

    これは仮想**D**igital **H**umidity and **T**emperatureセンサーを管理する`DHT`クラスのインスタンスを宣言します。最初のパラメータは使用しているセンサーが仮想*DHT11*センサーであることをコードに伝えます。2番目のパラメータはセンサーがポート`5`に接続されていることをコードに伝えます。

    > 💁 CounterFitはこの湿度と温度センサーを2つのセンサーに接続することでシミュレートします。湿度センサーが指定されたピンに接続され、温度センサーは次のピンで動作します。湿度センサーがピン5にある場合、シムは温度センサーがピン6にあると仮定します。

1. 温度センサー値をポーリングしてコンソールに出力するために、以下のコードを上記のコードの後に追加します：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()`の呼び出しは湿度と温度のタプルを返します。必要なのは温度値だけなので、湿度は無視されます。その後、温度値がコンソールに出力されます。

1. 温度レベルを継続的にチェックする必要がないため、`loop`の最後に10秒間のスリープを追加します。スリープはデバイスの消費電力を削減します。

    ```python
    time.sleep(10)
    ```

1. VS Codeターミナルで仮想環境が有効化された状態で、以下を実行してPythonアプリを実行します：

    ```sh
    python app.py
    ```

1. CounterFitアプリから、アプリが読み取る温度センサーの値を変更します。以下の2つの方法で変更できます：

    * 温度センサーの*Value*ボックスに数値を入力し、**Set**ボタンを選択します。入力した数値がセンサーから返される値になります。

    * *Random*チェックボックスをオンにし、*Min*と*Max*値を入力して**Set**ボタンを選択します。センサーが値を読み取るたびに、*Min*と*Max*の間のランダムな数値が返されます。

    設定した値がコンソールに表示されるはずです。*Value*や*Random*設定を変更して値の変化を確認してください。

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 このコードは[code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device)フォルダーにあります。

😀 温度センサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があることをご承知おきください。原文（元の言語で記載された文書）が信頼できる情報源として優先されるべきです。重要な情報については、専門の人間による翻訳をお勧めします。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いかねます。