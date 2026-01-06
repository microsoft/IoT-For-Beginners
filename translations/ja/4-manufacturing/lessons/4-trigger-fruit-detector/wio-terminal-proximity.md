<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "288aebb0c59f7be1d2719b8f9660a313",
  "translation_date": "2025-08-24T21:55:09+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/wio-terminal-proximity.md",
  "language_code": "ja"
}
-->
# 近接検知 - Wio Terminal

このレッスンでは、Wio Terminalに近接センサーを追加し、距離を読み取る方法を学びます。

## ハードウェア

Wio Terminalには近接センサーが必要です。

使用するセンサーは、[Grove Time of Flight距離センサー](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)です。このセンサーはレーザー測距モジュールを使用して距離を検知します。このセンサーの測定範囲は10mmから2000mm（1cm - 2m）で、この範囲内の値をかなり正確に報告します。1000mmを超える距離は8109mmとして報告されます。

レーザー測距モジュールはセンサーの背面にあり、Groveソケットの反対側に位置しています。

これはI²Cセンサーです。

### Time of Flightセンサーを接続する

Grove Time of FlightセンサーはWio Terminalに接続できます。

#### タスク - Time of Flightセンサーを接続する

Time of Flightセンサーを接続します。

![Grove Time of Flightセンサー](../../../../../translated_images/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.ja.png)

1. Groveケーブルの一端をTime of Flightセンサーのソケットに挿入します。ケーブルは一方向にしか挿入できません。

1. Wio Terminalをコンピュータや他の電源から切り離した状態で、Groveケーブルのもう一端をWio Terminalの左側のGroveソケットに接続します（画面を見たときの左側）。このソケットは電源ボタンに最も近いソケットで、デジタルとI²Cの両方に対応しています。

![左側のソケットに接続されたGrove Time of Flightセンサー](../../../../../translated_images/wio-time-of-flight-sensor.c4c182131d2ea73d.ja.png)

1. これでWio Terminalをコンピュータに接続できます。

## Time of Flightセンサーをプログラムする

これで、Wio Terminalに接続されたTime of Flightセンサーを使用するプログラムを作成できます。

### タスク - Time of Flightセンサーをプログラムする

1. PlatformIOを使用して新しいWio Terminalプロジェクトを作成します。このプロジェクトを`distance-sensor`と名付けます。`setup`関数内にシリアルポートを設定するコードを追加します。

1. プロジェクトの`platformio.ini`ファイルに、Seeed Grove Time of Flight距離センサーライブラリの依存関係を追加します：

    ```ini
    lib_deps =
        seeed-studio/Grove Ranging sensor - VL53L0X @ ^1.1.1
    ```

1. `main.cpp`で、既存のインクルードディレクティブの下に以下を追加し、Time of Flightセンサーとやり取りするための`Seeed_vl53l0x`クラスのインスタンスを宣言します：

    ```cpp
    #include "Seeed_vl53l0x.h"
    
    Seeed_vl53l0x VL53L0X;
    ```

1. `setup`関数の末尾に以下を追加し、センサーを初期化します：

    ```cpp
    VL53L0X.VL53L0X_common_init();
    VL53L0X.VL53L0X_high_accuracy_ranging_init();
    ```

1. `loop`関数内でセンサーから値を読み取ります：

    ```cpp
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));

    VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    ```

    このコードはデータを読み取るためのデータ構造を初期化し、それを`PerformSingleRangingMeasurement`メソッドに渡して距離測定値を取得します。

1. この下に、距離測定値を出力し、1秒間の遅延を追加します：

    ```cpp
    Serial.print("Distance = ");
    Serial.print(RangingMeasurementData.RangeMilliMeter);
    Serial.println(" mm");

    delay(1000);
    ```

1. このコードをビルド、アップロード、実行します。シリアルモニタで距離測定値を確認できます。センサーの近くに物体を置くと、距離測定値が変化するのがわかります：

    ```output
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    測距モジュールはセンサーの背面にあるため、距離を測定する際は正しい側を使用してください。

    ![バナナに向けられたTime of Flightセンサーの背面の測距モジュール](../../../../../translated_images/time-of-flight-banana.079921ad8b1496e4.ja.png)

> 💁 このコードは[code-proximity/wio-terminal](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/wio-terminal)フォルダにあります。

😀 近接センサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。