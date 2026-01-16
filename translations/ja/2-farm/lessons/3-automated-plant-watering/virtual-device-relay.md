<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-24T22:19:37+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "ja"
}
-->
# リレーを制御する - 仮想IoTハードウェア

このレッスンのこの部分では、土壌湿度センサーに加えて仮想IoTデバイスにリレーを追加し、土壌湿度レベルに基づいてそれを制御します。

## 仮想ハードウェア

仮想IoTデバイスでは、シミュレートされたGroveリレーを使用します。これにより、Raspberry Piと物理的なGroveリレーを使用する場合と同じようにこのラボを進めることができます。

物理的なIoTデバイスでは、リレーは通常オープン型リレー（信号が送られていない場合、出力回路が開いている、つまり接続されていない）になります。このようなリレーは、最大250Vおよび10Aの出力回路を処理できます。

### CounterFitにリレーを追加する

仮想リレーを使用するには、CounterFitアプリにリレーを追加する必要があります。

#### タスク

CounterFitアプリにリレーを追加します。

1. 前回のレッスンで作成した`soil-moisture-sensor`プロジェクトをVS Codeで開きます（まだ開いていない場合）。このプロジェクトに追加を行います。

1. CounterFitウェブアプリが実行中であることを確認します。

1. リレーを作成します：

    1. *Actuators*ペインの*Create actuator*ボックスで、*Actuator type*ドロップダウンを開き、*Relay*を選択します。

    1. *Pin*を*5*に設定します。

    1. **Add**ボタンを選択して、Pin 5にリレーを作成します。

    ![リレーの設定](../../../../../translated_images/ja/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    リレーが作成され、アクチュエータリストに表示されます。

    ![作成されたリレー](../../../../../translated_images/ja/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## リレーをプログラムする

土壌湿度センサーアプリを仮想リレーで使用するようにプログラムできます。

### タスク

仮想デバイスをプログラムします。

1. 前回のレッスンで作成した`soil-moisture-sensor`プロジェクトをVS Codeで開きます（まだ開いていない場合）。このプロジェクトに追加を行います。

1. 以下のコードを既存のインポートの下に`app.py`ファイルに追加します：

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    このステートメントは、仮想Groveリレーとやり取りするためにGrove Pythonシムライブラリから`GroveRelay`をインポートします。

1. `ADC`クラスの宣言の下に以下のコードを追加して、`GroveRelay`インスタンスを作成します：

    ```python
    relay = GroveRelay(5)
    ```

    これにより、Pin **5**を使用してリレーが作成されます。このピンはリレーを接続したピンです。

1. リレーが動作しているかテストするために、以下のコードを`while True:`ループ内に追加します：

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    このコードはリレーをオンにし、0.5秒待機してからリレーをオフにします。

1. Pythonアプリを実行します。リレーは10秒ごとにオンとオフを繰り返し、オンとオフの間に0.5秒の遅延があります。CounterFitアプリ内で仮想リレーがオンとオフになる様子が確認できます。

    ![オンとオフを繰り返す仮想リレー](../../../../../images/virtual-relay-turn-on-off.gif)

## 土壌湿度に基づいてリレーを制御する

リレーが動作するようになったので、土壌湿度の読み取り値に応じて制御できるようにします。

### タスク

リレーを制御します。

1. リレーをテストするために追加した3行のコードを削除します。その代わりに、以下のコードを追加します：

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    このコードは土壌湿度センサーからの土壌湿度レベルをチェックします。450を超える場合はリレーをオンにし、450を下回る場合はリレーをオフにします。

    > 💁 静電容量式土壌湿度センサーは、土壌湿度レベルが低いほど土壌に水分が多く、高いほど水分が少ないことを示します。

1. Pythonアプリを実行します。土壌湿度レベルに応じてリレーがオンまたはオフになります。土壌湿度センサーの*Value*または*Random*設定を変更して値の変化を確認してください。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 このコードは[code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device)フォルダーにあります。

😀 仮想土壌湿度センサーでリレーを制御するプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があることをご承知おきください。元の言語で記載された原文が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。