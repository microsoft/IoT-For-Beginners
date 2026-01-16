<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-24T22:16:52+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "ja"
}
-->
# リレーを制御する - Wio Terminal

このレッスンでは、土壌湿度センサーに加えてリレーをWio Terminalに追加し、土壌湿度レベルに基づいてリレーを制御します。

## ハードウェア

Wio Terminalにはリレーが必要です。

使用するリレーは [Groveリレー](https://www.seeedstudio.com/Grove-Relay.html) です。これは通常開（信号が送られていないときに出力回路が開いている、つまり接続されていない）リレーで、最大250V、10Aの出力回路を扱うことができます。

このリレーはデジタルアクチュエータであり、Wio Terminalのデジタルピンに接続します。アナログ/デジタル複合ポートはすでに土壌湿度センサーで使用されているため、リレーはもう一方の複合I²C/デジタルポートに接続します。

### リレーを接続する

GroveリレーはWio Terminalのデジタルポートに接続できます。

#### タスク

リレーを接続してください。

![Groveリレー](../../../../../translated_images/ja/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. Groveケーブルの一端をリレーのソケットに差し込みます。ケーブルは一方向にしか差し込めません。

1. Wio Terminalをコンピュータや他の電源から切断した状態で、Groveケーブルのもう一端をWio Terminalの画面を見たときの左側のGroveソケットに接続します。右側のソケットには土壌湿度センサーを接続したままにしてください。

![左側のソケットに接続されたGroveリレーと、右側のソケットに接続された土壌湿度センサー](../../../../../translated_images/ja/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.webp)

1. 前のレッスンで土壌湿度センサーを土に挿していない場合は、土に挿してください。

## リレーをプログラムする

これで、Wio Terminalに接続されたリレーをプログラムで制御できるようになります。

### タスク

デバイスをプログラムしてください。

1. 前回のレッスンで作成した `soil-moisture-sensor` プロジェクトをVS Codeで開きます（まだ開いていない場合）。このプロジェクトにコードを追加します。

2. このアクチュエータには専用のライブラリはありません。デジタルアクチュエータは高信号または低信号で制御します。リレーをオンにするにはピンに高信号（3.3V）を送り、オフにするには低信号（0V）を送ります。これを組み込みのArduino [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) 関数を使って行います。まず、`setup` 関数の最後に以下を追加して、複合I²C/デジタルポートをリレーに電圧を送るための出力ピンとして設定します：

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` は複合I²C/デジタルポートのポート番号です。

1. リレーが動作するかテストするために、`loop` 関数の最後の `delay` の下に以下を追加します：

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    このコードは、リレーが接続されているピンに高信号を送りリレーをオンにし、500ms（0.5秒）待機した後、低信号を送ってリレーをオフにします。

1. コードをビルドしてWio Terminalにアップロードします。

1. アップロードが完了すると、リレーは10秒ごとにオンとオフを繰り返します。オンとオフの間には0.5秒の遅延があります。リレーがオンになると「カチッ」という音がし、オフになると再び「カチッ」という音がします。リレーがオンのときはGroveボード上のLEDが点灯し、オフのときは消灯します。

    ![リレーがオンとオフを繰り返す](../../../../../images/relay-turn-on-off.gif)

## 土壌湿度に基づいてリレーを制御する

リレーが動作するようになったので、土壌湿度センサーの読み取り値に応じてリレーを制御します。

### タスク

リレーを制御してください。

1. リレーをテストするために追加した3行のコードを削除します。その代わりに以下のコードを追加してください：

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    このコードは土壌湿度センサーから土壌湿度レベルをチェックします。450を超えるとリレーをオンにし、450を下回るとリレーをオフにします。

    > 💁 静電容量式土壌湿度センサーは、土壌湿度レベルが低いほど土壌に水分が多く、逆に高いほど水分が少ないことを示します。

1. コードをビルドしてWio Terminalにアップロードします。

1. シリアルモニターを使ってデバイスを監視します。土壌湿度レベルに応じてリレーがオンまたはオフになるのが確認できます。乾燥した土壌で試し、その後水を加えてみてください。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 このコードは [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal) フォルダーにあります。

😀 土壌湿度センサーでリレーを制御するプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知ください。元の言語で記載された文書が正式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当社は責任を負いません。