<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-24T21:54:07+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "ja"
}
-->
# 近接検知 - Raspberry Pi

このレッスンでは、Raspberry Piに近接センサーを追加し、距離を読み取る方法を学びます。

## ハードウェア

Raspberry Piには近接センサーが必要です。

使用するセンサーは[Grove Time of Flight距離センサー](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)です。このセンサーはレーザー測距モジュールを使用して距離を検知します。このセンサーの測定範囲は10mmから2000mm（1cm - 2m）で、この範囲内の値をかなり正確に報告します。1000mmを超える距離は8109mmとして報告されます。

レーザー測距モジュールはセンサーの背面にあり、Groveソケットの反対側に位置しています。

これはI²Cセンサーです。

### Time of Flightセンサーを接続する

Grove Time of FlightセンサーはRaspberry Piに接続できます。

#### タスク - Time of Flightセンサーを接続する

Time of Flightセンサーを接続します。

![Grove Time of Flightセンサー](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.ja.png)

1. Groveケーブルの片方の端をTime of Flightセンサーのソケットに差し込みます。このケーブルは一方向にしか差し込めません。

1. Raspberry Piの電源をオフにした状態で、Groveケーブルのもう片方の端を、Piに取り付けられたGrove Base Hatの**I²C**と記されたソケットの1つに接続します。このソケットは下段にあり、GPIOピンの反対側で、カメラケーブルスロットの隣にあります。

![I²Cソケットに接続されたGrove Time of Flightセンサー](../../../../../translated_images/pi-time-of-flight-sensor.58c8dc04eb3bfb57.ja.png)

## Time of Flightセンサーをプログラムする

Raspberry Piをプログラムして、接続されたTime of Flightセンサーを使用できるようにします。

### タスク - Time of Flightセンサーをプログラムする

デバイスをプログラムします。

1. Piの電源を入れ、起動を待ちます。

1. `fruit-quality-detector`コードをVS Codeで開きます。Pi上で直接開くか、Remote SSH拡張機能を使用して接続します。

1. VL53L0X Time of Flight距離センサーとやり取りするPythonパッケージであるrpi-vl53l0x Pipパッケージをインストールします。以下のpipコマンドを使用してインストールします。

    ```sh
    pip install rpi-vl53l0x
    ```

1. このプロジェクトに新しいファイル`distance-sensor.py`を作成します。

    > 💁 複数のIoTデバイスをシミュレーションする簡単な方法は、それぞれを別々のPythonファイルで作成し、それらを同時に実行することです。

1. このファイルに以下のコードを追加します：

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    これにより、Grove I²Cバスライブラリと、Grove Time of Flightセンサーに組み込まれたコアセンサーのハードウェア用ライブラリがインポートされます。

1. 次に、センサーにアクセスするための以下のコードを追加します：

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    このコードは、Grove I²Cバスを使用して距離センサーを宣言し、センサーを開始します。

1. 最後に、距離を読み取るための無限ループを追加します：

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    このコードは、センサーから値を読み取る準備ができるのを待ち、コンソールに値を表示します。

1. このコードを実行します。

    > 💁 このファイルは`distance-sensor.py`という名前です！`app.py`ではなく、Pythonで実行することを忘れないでください。

1. コンソールに距離測定値が表示されます。センサーの近くに物体を置くと、距離測定値が表示されます：

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    測距モジュールはセンサーの背面にあるため、距離を測定する際には正しい側を使用してください。

    ![バナナに向けられたTime of Flightセンサーの背面の測距モジュール](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.ja.png)

> 💁 このコードは[code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi)フォルダーにあります。

😀 近接センサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。