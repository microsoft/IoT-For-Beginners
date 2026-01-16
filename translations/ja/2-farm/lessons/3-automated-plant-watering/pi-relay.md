<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-24T22:18:16+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "ja"
}
-->
# リレーを制御する - Raspberry Pi

このレッスンでは、土壌湿度センサーに加えてリレーをRaspberry Piに追加し、土壌湿度レベルに基づいてリレーを制御します。

## ハードウェア

Raspberry Piにはリレーが必要です。

使用するリレーは、[Groveリレー](https://www.seeedstudio.com/Grove-Relay.html)です。これは通常開（NO: Normally Open）のリレーで、信号が送られていない場合は出力回路が開いている（接続されていない）状態です。このリレーは最大250V、10Aの出力回路を扱うことができます。

このリレーはデジタルアクチュエータであり、Grove Base Hatのデジタルピンに接続します。

### リレーを接続する

GroveリレーをRaspberry Piに接続します。

#### タスク

リレーを接続します。

![Groveリレー](../../../../../translated_images/ja/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Groveケーブルの片方の端をリレーのソケットに差し込みます。ケーブルは一方向にしか差し込めません。

1. Raspberry Piの電源を切った状態で、Groveケーブルのもう一方の端をPiに接続されたGrove Base Hatのデジタルソケット**D5**に接続します。このソケットは、GPIOピンの隣のソケット列の左から2番目にあります。土壌湿度センサーは**A0**ソケットに接続したままにしておきます。

![D5ソケットに接続されたGroveリレーと、A0ソケットに接続された土壌湿度センサー](../../../../../translated_images/ja/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. 前のレッスンで既に土壌湿度センサーを土に挿していない場合は、土壌湿度センサーを土に挿します。

## リレーをプログラムする

Raspberry Piをプログラムして、接続されたリレーを使用できるようにします。

### タスク

デバイスをプログラムします。

1. Piの電源を入れ、起動を待ちます。

1. 前回のレッスンで作成した`soil-moisture-sensor`プロジェクトをVS Codeで開きます（まだ開いていない場合）。このプロジェクトにコードを追加します。

1. 既存のインポート文の下に、以下のコードを`app.py`ファイルに追加します：

    ```python
    from grove.grove_relay import GroveRelay
    ```

    この文は、Grove Pythonライブラリから`GroveRelay`をインポートし、Groveリレーとやり取りするために使用します。

1. `ADC`クラスの宣言の下に、以下のコードを追加して`GroveRelay`インスタンスを作成します：

    ```python
    relay = GroveRelay(5)
    ```

    これにより、リレーが**D5**ピン（リレーを接続したデジタルピン）を使用して作成されます。

1. リレーが動作しているかテストするために、以下のコードを`while True:`ループ内に追加します：

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    このコードはリレーをオンにし、0.5秒待機してからリレーをオフにします。

1. Pythonアプリを実行します。リレーは10秒ごとにオンとオフを繰り返し、オンとオフの間に0.5秒の遅延があります。リレーがオンになると「カチッ」という音がし、オフになると再び「カチッ」という音がします。リレーがオンのとき、Groveボード上のLEDが点灯し、オフのときに消灯します。

    ![リレーのオン・オフ](../../../../../images/relay-turn-on-off.gif)

## 土壌湿度に基づいてリレーを制御する

リレーが動作するようになったので、土壌湿度センサーの読み取り値に応じてリレーを制御します。

### タスク

リレーを制御します。

1. リレーをテストするために追加した3行のコードを削除します。それを以下のコードに置き換えます：

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    このコードは、土壌湿度センサーから土壌湿度レベルをチェックします。湿度レベルが450を超えるとリレーをオンにし、450を下回るとリレーをオフにします。

    > 💁 静電容量式土壌湿度センサーは、土壌の湿度レベルが低いほど土壌に水分が多く、高いほど水分が少ないことを示します。

1. Pythonアプリを実行します。土壌湿度レベルに応じてリレーがオンまたはオフになるのを確認できます。乾燥した土壌で試し、その後水を加えてみてください。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 このコードは[code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi)フォルダーにあります。

😀 土壌湿度センサーでリレーを制御するプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は一切の責任を負いません。