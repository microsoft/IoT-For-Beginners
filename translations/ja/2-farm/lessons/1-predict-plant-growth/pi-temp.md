<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-24T22:08:47+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "ja"
}
-->
# 温度を測定する - Raspberry Pi

このレッスンのこの部分では、Raspberry Pi に温度センサーを追加します。

## ハードウェア

使用するセンサーは [DHT11 湿度・温度センサー](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html) です。このセンサーは 2 つのセンサーを 1 つのパッケージに組み合わせたものです。これは非常に一般的で、温度、湿度、時には気圧を組み合わせた市販のセンサーが数多く存在します。温度センサーのコンポーネントは負の温度係数（NTC）サーミスタで、温度が上昇すると抵抗が減少する特性を持っています。

このセンサーはデジタルセンサーであり、温度と湿度のデータを含むデジタル信号を生成するオンボード ADC を備えています。この信号をマイクロコントローラーが読み取ることができます。

### 温度センサーを接続する

Grove 温度センサーを Raspberry Pi に接続できます。

#### タスク

温度センサーを接続する

![Grove 温度センサー](../../../../../translated_images/ja/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Grove ケーブルの片方の端を湿度・温度センサーのソケットに差し込みます。ケーブルは一方向にしか差し込めません。

1. Raspberry Pi の電源を切った状態で、Grove ケーブルのもう一方の端を Pi に接続された Grove Base Hat のデジタルソケット **D5** に接続します。このソケットは GPIO ピンの隣のソケット列の左から 2 番目にあります。

![ソケット A0 に接続された Grove 温度センサー](../../../../../translated_images/ja/pi-temperature-sensor.3ff82fff672c8e565ef25a39d26d111de006b825a7e0867227ef4e7fbff8553c.png)

## 温度センサーをプログラムする

これで、接続された温度センサーを使用するようにデバイスをプログラムできます。

### タスク

デバイスをプログラムする

1. Pi の電源を入れ、起動を待ちます。

1. VS Code を起動します。Pi 上で直接起動するか、Remote SSH 拡張機能を使用して接続します。

    > ⚠️ 必要に応じて、[レッスン 1 の VS Code のセットアップと起動に関する手順](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md)を参照してください。

1. ターミナルから、`pi` ユーザーのホームディレクトリに `temperature-sensor` という新しいフォルダを作成します。このフォルダ内に `app.py` というファイルを作成します：

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. このフォルダを VS Code で開きます。

1. 温度・湿度センサーを使用するには、追加の Pip パッケージをインストールする必要があります。VS Code のターミナルから、以下のコマンドを実行して Pi に Pip パッケージをインストールします：

    ```sh
    pip3 install seeed-python-dht
    ```

1. 必要なライブラリをインポートするために、以下のコードを `app.py` ファイルに追加します：

    ```python
    import time
    from seeed_dht import DHT
    ```

    `from seeed_dht import DHT` ステートメントは、`seeed_dht` モジュールから Grove 温度センサーとやり取りするための `DHT` センサークラスをインポートします。

1. 上記のコードの後に、温度センサーを管理するクラスのインスタンスを作成するための以下のコードを追加します：

    ```python
    sensor = DHT("11", 5)
    ```

    これは、**D**igital **H**umidity and **T**emperature センサーを管理する `DHT` クラスのインスタンスを宣言します。最初のパラメータは、使用しているセンサーが *DHT11* センサーであることをコードに伝えます。使用しているライブラリは、このセンサーの他のバリエーションもサポートしています。2 番目のパラメータは、センサーが Grove Base Hat のデジタルポート `D5` に接続されていることをコードに伝えます。

    > ✅ すべてのソケットには固有のピン番号があります。ピン 0、2、4、6 はアナログピン、ピン 5、16、18、22、24、26 はデジタルピンです。

1. 上記のコードの後に無限ループを追加し、温度センサーの値をポーリングしてコンソールに出力します：

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    `sensor.read()` の呼び出しは、湿度と温度のタプルを返します。必要なのは温度値だけなので、湿度は無視します。その後、温度値をコンソールに出力します。

1. ループの最後に 10 秒間のスリープを追加します。温度レベルを継続的にチェックする必要はありません。スリープを追加することで、デバイスの消費電力を削減できます。

    ```python
    time.sleep(10)
    ```

1. VS Code のターミナルから、以下を実行して Python アプリを実行します：

    ```sh
    python3 app.py
    ```

    コンソールに温度値が出力されるのが確認できるはずです。センサーを温めるために、親指で押さえたり、ファンを使用したりして値が変化するのを確認してください：

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 このコードは [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi) フォルダにあります。

😀 温度センサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。