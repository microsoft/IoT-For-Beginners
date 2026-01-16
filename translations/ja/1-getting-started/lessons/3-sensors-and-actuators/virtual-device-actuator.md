<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-24T23:23:37+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "ja"
}
-->
# ナイトライトを作る - 仮想IoTハードウェア

このレッスンのこの部分では、仮想IoTデバイスにLEDを追加し、それを使ってナイトライトを作成します。

## 仮想ハードウェア

ナイトライトには、CounterFitアプリで作成された1つのアクチュエータが必要です。

アクチュエータは**LED**です。物理的なIoTデバイスでは、これは電流が流れると光を放つ[発光ダイオード](https://wikipedia.org/wiki/Light-emitting_diode)です。これはデジタルアクチュエータで、オンとオフの2つの状態を持ちます。値1を送信するとLEDが点灯し、値0を送信すると消灯します。

ナイトライトのロジックを擬似コードで表すと次のようになります：

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### CounterFitにアクチュエータを追加する

仮想LEDを使用するには、CounterFitアプリに追加する必要があります。

#### タスク - CounterFitにアクチュエータを追加する

CounterFitアプリにLEDを追加します。

1. この課題の前の部分でCounterFitウェブアプリが実行中であることを確認してください。実行されていない場合は、起動して光センサーを再追加してください。

1. LEDを作成します：

    1. *Actuator*ペインの*Create actuator*ボックスで、*Actuator type*ドロップダウンを開き、*LED*を選択します。

    1. *Pin*を*5*に設定します。

    1. **Add**ボタンを選択して、Pin 5にLEDを作成します。

    ![LEDの設定](../../../../../translated_images/ja/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    LEDが作成され、アクチュエータリストに表示されます。

    ![作成されたLED](../../../../../translated_images/ja/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    LEDが作成されたら、*Color*ピッカーを使用して色を変更できます。色を選択した後、**Set**ボタンを選択して色を変更します。

### ナイトライトをプログラムする

CounterFitの光センサーとLEDを使用してナイトライトをプログラムできます。

#### タスク - ナイトライトをプログラムする

ナイトライトをプログラムします。

1. この課題の前の部分で作成したVS Codeのナイトライトプロジェクトを開きます。必要に応じて、仮想環境を使用して実行されるようにターミナルを終了して再作成してください。

1. `app.py`ファイルを開きます。

1. 必要なライブラリをインポートするために、以下のコードを`app.py`ファイルの他の`import`行の下に追加します。

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    `from counterfit_shims_grove.grove_led import GroveLed`ステートメントは、CounterFit Grove shim Pythonライブラリから`GroveLed`をインポートします。このライブラリには、CounterFitアプリで作成されたLEDとやり取りするためのコードが含まれています。

1. `light_sensor`宣言の後に以下のコードを追加して、LEDを管理するクラスのインスタンスを作成します：

    ```python
    led = GroveLed(5)
    ```

    `led = GroveLed(5)`行は、Pin **5**に接続された`GroveLed`クラスのインスタンスを作成します。これは、LEDが接続されているCounterFit Groveのピンです。

1. `while`ループ内で、`time.sleep`の前にチェックを追加して、光レベルを確認し、LEDをオンまたはオフにします：

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    このコードは`light`値をチェックします。この値が300未満の場合、`GroveLed`クラスの`on`メソッドを呼び出し、LEDを点灯させるデジタル値1を送信します。光の値が300以上の場合、`off`メソッドを呼び出し、LEDを消灯させるデジタル値0を送信します。

    > 💁 このコードは、`print('Light level:', light)`行と同じレベルにインデントされ、whileループ内に含まれるようにしてください！

1. VS Codeのターミナルから、以下を実行してPythonアプリを実行します：

    ```sh
    python3 app.py
    ```

    光の値がコンソールに出力されます。

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. *Value*または*Random*設定を変更して、光レベルを300以上および以下に変化させます。LEDが点灯および消灯します。

![光レベルの変化に応じてCounterFitアプリ内で点灯および消灯するLED](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 このコードは[code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device)フォルダーにあります。

😀 ナイトライトプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確さが含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤訳について、当社は一切の責任を負いません。