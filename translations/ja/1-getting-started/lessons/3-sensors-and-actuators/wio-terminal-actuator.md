<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-24T23:22:24+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "ja"
}
-->
# ナイトライトを作る - Wio Terminal

このレッスンでは、Wio TerminalにLEDを追加してナイトライトを作成します。

## ハードウェア

ナイトライトにはアクチュエータが必要です。

アクチュエータは**LED**、つまり[発光ダイオード](https://wikipedia.org/wiki/Light-emitting_diode)で、電流が流れると光を放ちます。このデジタルアクチュエータにはオンとオフの2つの状態があります。値を1にするとLEDが点灯し、0にすると消灯します。このLEDは外部のGroveアクチュエータであり、Wio Terminalに接続する必要があります。

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

![Grove LED](../../../../../translated_images/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.ja.png)

1. 好きな色のLEDを選び、LEDモジュールの2つの穴に足を差し込みます。

    LEDは発光ダイオードであり、ダイオードは電流を一方向にしか流せない電子部品です。つまり、LEDは正しい向きで接続しないと動作しません。

    LEDの足の一方は正極ピンで、もう一方は負極ピンです。LEDは完全な円形ではなく、一方が少し平らになっています。この平らな側が負極ピンです。LEDをモジュールに接続する際、丸い側のピンがモジュールの外側にある**+**と記されたソケットに接続され、平らな側がモジュールの中央に近いソケットに接続されるようにしてください。

1. LEDモジュールには明るさを調整するための回転ボタンがあります。まずは小さなプラスドライバーを使って反時計回りに回し、最大まで明るさを上げてください。

1. Groveケーブルの片方の端をLEDモジュールのソケットに差し込みます。このケーブルは一方向にしか差し込めません。

1. Wio Terminalをコンピュータやその他の電源から切り離した状態で、Groveケーブルのもう一方の端をWio Terminalの画面右側のGroveソケットに接続します。このソケットは電源ボタンから最も遠い位置にあります。

    > 💁 右側のGroveソケットはアナログまたはデジタルセンサーやアクチュエータに使用できます。左側のソケットはI2Cとデジタルセンサーやアクチュエータ専用です。

![右側のソケットに接続されたGrove LED](../../../../../translated_images/wio-led.265a1897e72d7f21.ja.png)

## ナイトライトをプログラムする

内蔵の光センサーとGrove LEDを使用してナイトライトをプログラムします。

### タスク - ナイトライトをプログラムする

ナイトライトをプログラムします。

1. 前の課題で作成したナイトライトプロジェクトをVS Codeで開きます。

1. `setup`関数の最後に以下の行を追加します：

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    この行は、Groveポートを介してLEDと通信するために使用されるピンを設定します。

    `D0`ピンは右側のGroveソケットのデジタルピンです。このピンは`OUTPUT`に設定され、アクチュエータに接続され、データがピンに書き込まれます。

1. `loop`関数内の`delay`の直前に以下のコードを追加します：

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    このコードは`light`値をチェックします。この値が300未満の場合、`D0`デジタルピンに`HIGH`値を送信します。この`HIGH`値は1で、LEDを点灯させます。光が300以上の場合、`LOW`値の0をピンに送信し、LEDを消灯します。

    > 💁 デジタル値をアクチュエータに送信する場合、LOW値は0V、HIGH値はデバイスの最大電圧です。Wio Terminalの場合、HIGH電圧は3.3Vです。

1. Wio Terminalをコンピュータに再接続し、前と同じ方法で新しいコードをアップロードします。

1. シリアルモニターを接続します。光の値がターミナルに出力されます。

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. 光センサーを覆ったり外したりしてみてください。光レベルが300以下の場合、LEDが点灯し、光レベルが300以上の場合、LEDが消灯することに気づくでしょう。

![光レベルの変化に応じて点灯・消灯するWioに接続されたLED](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 このコードは[code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal)フォルダーにあります。

😀 ナイトライトプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。