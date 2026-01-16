<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-24T23:25:55+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "ja"
}
-->
# センサーを追加する - Wio Terminal

このレッスンでは、Wio Terminalの光センサーを使用します。

## ハードウェア

このレッスンで使用するセンサーは、**光センサー**です。このセンサーは[フォトダイオード](https://wikipedia.org/wiki/Photodiode)を使用して光を電気信号に変換します。これはアナログセンサーで、0から1,023までの整数値を送信し、光の相対量を示しますが、[ルクス](https://wikipedia.org/wiki/Lux)のような標準的な単位には対応していません。

光センサーはWio Terminalに内蔵されており、背面の透明なプラスチック窓を通して見ることができます。

![Wio Terminalの背面にある光センサー](../../../../../translated_images/ja/wio-light-sensor.b1f529f3c95f5165.webp)

## 光センサーをプログラムする

デバイスを内蔵光センサーを使用するようにプログラムできます。

### タスク

デバイスをプログラムします。

1. 前の課題で作成したVS Codeのナイトライトプロジェクトを開きます。

1. `setup`関数の最後に次の行を追加します：

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    この行は、センサーのハードウェアと通信するために使用されるピンを設定します。

    `WIO_LIGHT`ピンは、オンボード光センサーに接続されたGPIOピンの番号です。このピンは`INPUT`に設定されており、センサーに接続され、ピンからデータを読み取ることを意味します。

1. `loop`関数の内容を削除します。

1. 空になった`loop`関数に次のコードを追加します。

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    このコードは、`WIO_LIGHT`ピンからアナログ値を読み取ります。これにより、オンボード光センサーから0～1,023の値が読み取られます。この値はシリアルポートに送信され、コードが実行されている間、シリアルモニターで確認できます。`Serial.print`は改行なしでテキストを書き込むため、各行は`Light value:`で始まり、実際の光の値で終わります。

1. `loop`の最後に1秒（1,000ms）の短い遅延を追加します。光レベルを継続的にチェックする必要はないため、遅延を追加することでデバイスの消費電力を削減できます。

    ```cpp
    delay(1000);
    ```

1. Wio Terminalをコンピュータに再接続し、前と同じように新しいコードをアップロードします。

1. シリアルモニターを接続します。光の値がターミナルに出力されます。Wio Terminalの背面にある光センサーを覆ったり外したりすると、値が変化します。

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

> 💁 このコードは[code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal)フォルダーにあります。

😀 ナイトライトプログラムにセンサーを追加することに成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。