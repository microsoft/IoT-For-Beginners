<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7e9f05bdc50a40fd924b1d66934471bf",
  "translation_date": "2025-08-24T21:56:18+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/virtual-device-proximity.md",
  "language_code": "ja"
}
-->
# 近接検知 - 仮想IoTハードウェア

このレッスンでは、仮想IoTデバイスに近接センサーを追加し、距離を読み取る方法を学びます。

## ハードウェア

仮想IoTデバイスでは、シミュレーションされた距離センサーを使用します。

物理的なIoTデバイスでは、レーザー測距モジュールを備えたセンサーを使用して距離を検知します。

### CounterFitに距離センサーを追加する

仮想距離センサーを使用するには、CounterFitアプリにセンサーを追加する必要があります。

#### タスク - CounterFitに距離センサーを追加する

CounterFitアプリに距離センサーを追加します。

1. VS Codeで`fruit-quality-detector`コードを開き、仮想環境が有効になっていることを確認します。

1. 追加のPipパッケージをインストールして、距離センサーと通信するCounterFit shimをインストールします。このshimは、[rpi-vl53l0x Pipパッケージ](https://pypi.org/project/rpi-vl53l0x/)をシミュレートします。このPythonパッケージは、[VL53L0X飛行時間距離センサー](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/)と連携します。仮想環境が有効になっているターミナルからインストールしてください。

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. CounterFitウェブアプリが実行中であることを確認します。

1. 距離センサーを作成します：

    1. *Sensors*ペインの*Create sensor*ボックスで、*Sensor type*ドロップダウンを開き、*Distance*を選択します。

    1. *Units*は`Millimeter`のままにします。

    1. このセンサーはI²Cセンサーなので、アドレスを`0x29`に設定します。物理的なVL53L0Xセンサーを使用する場合、このアドレスはハードコードされています。

    1. **Add**ボタンを選択して距離センサーを作成します。

    ![距離センサーの設定](../../../../../translated_images/ja/counterfit-create-distance-sensor.967c9fb98f27888d95920c9784d004c972490eb71f70397fe13bd70a79a879a3.png)

    距離センサーが作成され、センサーリストに表示されます。

    ![作成された距離センサー](../../../../../translated_images/ja/counterfit-distance-sensor.079eefeeea0b68afc36431ce8fcbe2f09a7e4916ed1cd5cb30e696db53bc18fa.png)

## 距離センサーをプログラムする

仮想IoTデバイスは、シミュレーションされた距離センサーを使用するようにプログラムできます。

### タスク - 飛行時間センサーをプログラムする

1. `fruit-quality-detector`プロジェクトに新しいファイル`distance-sensor.py`を作成します。

    > 💁 複数のIoTデバイスをシミュレーションする簡単な方法は、それぞれを別々のPythonファイルで作成し、同時に実行することです。

1. 次のコードを使用してCounterFitへの接続を開始します：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. この下に次のコードを追加します：

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    これはVL53L0X飛行時間センサー用のセンサーライブラリshimをインポートします。

1. さらにその下に、センサーにアクセスするための次のコードを追加します：

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    このコードは距離センサーを宣言し、センサーを開始します。

1. 最後に、距離を読み取る無限ループを追加します：

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    このコードはセンサーから値を読み取る準備ができるのを待ち、コンソールに値を表示します。

1. このコードを実行します。

    > 💁 このファイルは`distance-sensor.py`という名前です！`app.py`ではなく、Pythonで実行してください。

1. コンソールに距離測定値が表示されます。CounterFitで値を変更すると、この値が変化するのがわかります。またはランダムな値を使用してください。

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 このコードは[code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device)フォルダーにあります。

😀 近接センサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は一切の責任を負いません。