<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4db8a3879a53490513571df2f6cf7641",
  "translation_date": "2025-08-24T23:21:03+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-actuator.md",
  "language_code": "ja"
}
-->
# ナイトライトを作る - Raspberry Pi

このレッスンでは、Raspberry PiにLEDを追加してナイトライトを作成します。

## ハードウェア

ナイトライトにはアクチュエータが必要です。

アクチュエータは**LED**、つまり[発光ダイオード](https://wikipedia.org/wiki/Light-emitting_diode)で、電流が流れると光を放ちます。これはデジタルアクチュエータで、オンとオフの2つの状態を持っています。値を1にするとLEDが点灯し、0にすると消灯します。LEDは外部のGroveアクチュエータであり、Raspberry PiのGrove Base hatに接続する必要があります。

ナイトライトのロジックを擬似コードで表すと以下のようになります：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### LEDを接続する

Grove LEDは複数のLEDがセットになったモジュールとして提供されており、色を選ぶことができます。

#### タスク - LEDを接続する

LEDを接続します。

![Grove LED](../../../../../translated_images/ja/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. 好きな色のLEDを選び、LEDモジュールの2つの穴に足を差し込みます。

    LEDは発光ダイオードであり、ダイオードは電流を一方向にしか流せない電子部品です。そのため、LEDは正しい向きで接続しないと動作しません。

    LEDの足の一方は正極ピン、もう一方は負極ピンです。LEDは完全な円形ではなく、一方が少し平らになっています。この平らな側が負極ピンです。LEDをモジュールに接続する際、丸い側のピンがモジュール外側の**+**と記されたソケットに接続され、平らな側がモジュール中央付近のソケットに接続されるようにしてください。

1. LEDモジュールには明るさを調整するための回転ボタンがあります。まずはこれを反時計回りに最大まで回して設定してください。小型のプラスドライバーを使用します。

1. Groveケーブルの片方の端をLEDモジュールのソケットに差し込みます。このケーブルは一方向にしか差し込めません。

1. Raspberry Piの電源を切った状態で、Groveケーブルのもう片方の端をPiに接続されたGrove Base hatのデジタルソケット**D5**に接続します。このソケットはGPIOピンの隣にあるソケット列の左から2番目です。

![D5ソケットに接続されたGrove LED](../../../../../translated_images/ja/pi-led.97f1d474981dc35d1c7996c7b17de355d3d0a6bc9606d79fa5f89df933415122.png)

## ナイトライトをプログラムする

Grove光センサーとGrove LEDを使用してナイトライトをプログラムします。

### タスク - ナイトライトをプログラムする

ナイトライトをプログラムします。

1. Piの電源を入れ、起動を待ちます。

1. VS Codeで前回の課題で作成したナイトライトプロジェクトを開きます。Pi上で直接実行するか、Remote SSH拡張機能を使用して接続します。

1. 必要なライブラリをインポートするコードを`app.py`ファイルの上部、他の`import`行の下に追加します。

    ```python
    from grove.grove_led import GroveLed
    ```

    `from grove.grove_led import GroveLed`ステートメントは、Grove Pythonライブラリから`GroveLed`をインポートします。このライブラリにはGrove LEDとやり取りするためのコードが含まれています。

1. `light_sensor`宣言の後に以下のコードを追加し、LEDを管理するクラスのインスタンスを作成します：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)`という行は、**D5**ピンに接続されたGrove LEDクラスのインスタンスを作成します。このピンはLEDが接続されているデジタルGroveピンです。

    > 💁 ソケットにはそれぞれ固有のピン番号があります。ピン0、2、4、6はアナログピンで、ピン5、16、18、22、24、26はデジタルピンです。

1. `while`ループ内で、`time.sleep`の前に光レベルをチェックし、LEDをオンまたはオフにするコードを追加します：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    このコードは`light`値をチェックします。値が300未満の場合、`GroveLed`クラスの`on`メソッドを呼び出し、LEDを点灯させるデジタル値1を送信します。光値が300以上の場合、`off`メソッドを呼び出し、LEDを消灯させるデジタル値0を送信します。

    > 💁 このコードは`print('Light level:', light)`行と同じインデントレベルにする必要があります。これにより、`while`ループ内に含まれます。

    > 💁 アクチュエータにデジタル値を送信する際、値0は0V、値1はデバイスの最大電圧を表します。Raspberry PiとGroveセンサーおよびアクチュエータの場合、値1の電圧は3.3Vです。

1. VS Codeのターミナルから以下を実行してPythonアプリを実行します：

    ```sh
    python3 app.py
    ```

    光値がコンソールに出力されます。

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. 光センサーを覆ったり外したりしてみてください。光レベルが300以下の場合、LEDが点灯し、光レベルが300以上の場合、LEDが消灯することを確認してください。

    > 💁 LEDが点灯しない場合、正しい向きで接続されているか、回転ボタンが最大に設定されているか確認してください。

![光レベルの変化に応じて点灯・消灯するPiに接続されたLED](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 このコードは[code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi)フォルダーにあります。

😀 ナイトライトプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が正式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤訳について、当社は一切の責任を負いません。