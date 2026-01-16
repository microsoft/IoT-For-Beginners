<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9d4d00a47d5d0f3e6ce42c0d1020064a",
  "translation_date": "2025-08-24T22:41:13+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/pi-soil-moisture.md",
  "language_code": "ja"
}
-->
# 土壌水分を測定する - Raspberry Pi

このレッスンでは、Raspberry Pi に容量式土壌水分センサーを追加し、その値を読み取ります。

## ハードウェア

Raspberry Pi には容量式土壌水分センサーが必要です。

使用するセンサーは [容量式土壌水分センサー](https://www.seeedstudio.com/Grove-Capacitive-Moisture-Sensor-Corrosion-Resistant.html) です。このセンサーは、土壌の水分量が変化することで変わる土壌の静電容量を検出して水分量を測定します。土壌の水分量が増えると、電圧は低下します。

このセンサーはアナログセンサーであり、アナログピンを使用します。Raspberry Pi 上の Grove Base Hat にある 10 ビット ADC を使用して電圧をデジタル信号（1～1,023）に変換します。この信号は GPIO ピンを介して Pi に送信されます。

### 土壌水分センサーを接続する

Grove 土壌水分センサーを Raspberry Pi に接続できます。

#### タスク - 土壌水分センサーを接続する

土壌水分センサーを接続します。

![Grove 土壌水分センサー](../../../../../translated_images/ja/grove-capacitive-soil-moisture-sensor.e7f0776cce30e78be5cc5a07839385fd6718857f31b5bf5ad3d0c73c83b2f0ef.png)

1. Grove ケーブルの片方の端を土壌水分センサーのソケットに差し込みます。このケーブルは一方向にしか差し込めません。

1. Raspberry Pi の電源を切った状態で、Grove ケーブルのもう一方の端を Pi に取り付けられた Grove Base Hat のアナログソケット **A0** に接続します。このソケットは、GPIO ピンの隣のソケット列の右から2番目にあります。

![A0 ソケットに接続された Grove 土壌水分センサー](../../../../../translated_images/ja/pi-soil-moisture-sensor.fdd7eb2393792cf6739cacf1985d9f55beda16d372f30d0b5a51d586f978a870.png)

1. 土壌水分センサーを土に挿します。センサーには「最高挿入ライン」があり、白い線で示されています。このラインまで（ラインを超えないように）センサーを挿入します。

![土に挿された Grove 土壌水分センサー](../../../../../translated_images/ja/soil-moisture-sensor-in-soil.bfad91002bda5e96.webp)

## 土壌水分センサーをプログラムする

Raspberry Pi をプログラムして、接続された土壌水分センサーを使用できるようにします。

### タスク - 土壌水分センサーをプログラムする

デバイスをプログラムします。

1. Pi の電源を入れ、起動を待ちます。

1. VS Code を起動します。Pi 上で直接起動するか、Remote SSH 拡張機能を使用して接続します。

    > ⚠️ 必要に応じて、[ナイトライト - レッスン1での VS Code のセットアップと起動に関する手順](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)を参照してください。

1. ターミナルから、`pi` ユーザーのホームディレクトリに `soil-moisture-sensor` という新しいフォルダを作成します。このフォルダ内に `app.py` というファイルを作成します。

1. このフォルダを VS Code で開きます。

1. 必要なライブラリをインポートするために、以下のコードを `app.py` ファイルに追加します。

    ```python
    import time
    from grove.adc import ADC
    ```

    `import time` ステートメントは、この課題で後ほど使用する `time` モジュールをインポートします。

    `from grove.adc import ADC` ステートメントは、Grove Python ライブラリから `ADC` をインポートします。このライブラリには、Pi Base Hat 上のアナログ-デジタルコンバータとやり取りし、アナログセンサーから電圧を読み取るためのコードが含まれています。

1. 次に、`ADC` クラスのインスタンスを作成するための以下のコードを追加します。

    ```python
    adc = ADC()
    ```

1. A0 ピンの ADC から値を読み取り、その結果をコンソールに出力する無限ループを追加します。このループは、読み取りの間に10秒間スリープします。

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)

        time.sleep(10)
    ```

1. Python アプリを実行します。土壌水分の測定値がコンソールに表示されます。土に水を加えたり、センサーを土から取り外したりして、値の変化を確認してください。

    ```output
    pi@raspberrypi:~/soil-moisture-sensor $ python3 app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

    上記の例では、水を加えると電圧が低下する様子が確認できます。

> 💁 このコードは [code/pi](../../../../../2-farm/lessons/2-detect-soil-moisture/code/pi) フォルダにあります。

😀 土壌水分センサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な表現が含まれる可能性があります。原文（元の言語で記載された文書）が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤解釈について、当方は一切の責任を負いません。