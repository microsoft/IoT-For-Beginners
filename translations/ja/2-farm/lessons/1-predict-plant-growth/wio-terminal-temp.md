<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "59263d094f20b302053888cd236880c3",
  "translation_date": "2025-08-24T22:04:46+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp.md",
  "language_code": "ja"
}
-->
# 温度を測定する - Wio Terminal

このレッスンのこの部分では、Wio Terminalに温度センサーを追加し、そこから温度値を読み取ります。

## ハードウェア

Wio Terminalには温度センサーが必要です。

使用するセンサーは[DHT11湿度・温度センサー](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html)で、1つのパッケージに2つのセンサーが組み込まれています。このセンサーは非常に人気があり、温度、湿度、時には気圧を組み合わせた商用センサーが数多く存在します。温度センサーのコンポーネントは負の温度係数（NTC）サーミスタで、温度が上昇すると抵抗が減少する特性を持っています。

このセンサーはデジタルセンサーであり、オンボードADCを備えており、温度と湿度のデータを含むデジタル信号を生成し、マイクロコントローラーが読み取ることができます。

### 温度センサーを接続する

Grove温度センサーは、Wio Terminalのデジタルポートに接続できます。

#### タスク - 温度センサーを接続する

温度センサーを接続してください。

![Grove温度センサー](../../../../../translated_images/ja/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.png)

1. Groveケーブルの片方の端を湿度・温度センサーのソケットに差し込みます。このケーブルは一方向にしか差し込めません。

1. Wio Terminalをコンピューターや他の電源から切り離した状態で、Groveケーブルのもう片方の端をWio Terminalの画面右側のGroveソケットに接続します。このソケットは電源ボタンから最も遠い位置にあります。

![右側のソケットに接続されたGrove温度センサー](../../../../../translated_images/ja/wio-temperature-sensor.2934928f38c7f79a.webp)

## 温度センサーをプログラムする

Wio Terminalをプログラムして、接続された温度センサーを使用できるようにします。

### タスク - 温度センサーをプログラムする

デバイスをプログラムしてください。

1. PlatformIOを使用して新しいWio Terminalプロジェクトを作成します。このプロジェクトを`temperature-sensor`と名付け、`setup`関数内にシリアルポートを設定するコードを追加します。

    > ⚠️ 必要に応じて、[プロジェクト1、レッスン1のPlatformIOプロジェクト作成手順](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#create-a-platformio-project)を参照してください。

1. Seeed Grove湿度・温度センサーライブラリの依存関係をプロジェクトの`platformio.ini`ファイルに追加します：

    ```ini
    lib_deps =
        seeed-studio/Grove Temperature And Humidity Sensor @ 1.0.1
    ```

    > ⚠️ 必要に応じて、[プロジェクト1、レッスン4のPlatformIOプロジェクトへのライブラリ追加手順](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md#install-the-wifi-and-mqtt-arduino-libraries)を参照してください。

1. 既存の`#include <Arduino.h>`の下に、以下の`#include`ディレクティブをファイルの先頭に追加します：

    ```cpp
    #include <DHT.h>
    #include <SPI.h>
    ```

    これにより、センサーと対話するために必要なファイルがインポートされます。`DHT.h`ヘッダーファイルにはセンサー自体のコードが含まれており、`SPI.h`ヘッダーを追加することで、アプリがコンパイルされる際にセンサーと通信するためのコードがリンクされます。

1. `setup`関数の前に、DHTセンサーを宣言します：

    ```cpp
    DHT dht(D0, DHT11);
    ```

    これにより、**D**igital **H**umidity and **T**emperatureセンサーを管理する`DHT`クラスのインスタンスが宣言されます。このセンサーはポート`D0`、つまりWio Terminalの右側のGroveソケットに接続されています。2番目のパラメータは、使用しているセンサーが*DHT11*センサーであることをコードに伝えます。このライブラリは他のバリエーションのセンサーもサポートしています。

1. `setup`関数内に、シリアル接続を設定するコードを追加します：

    ```cpp
    void setup()
    {
        Serial.begin(9600);
    
        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    ```

1. 最後の`delay`の後、`setup`関数の末尾にDHTセンサーを開始する呼び出しを追加します：

    ```cpp
    dht.begin();
    ```

1. `loop`関数内に、センサーを呼び出して温度をシリアルポートに出力するコードを追加します：

    ```cpp
    void loop()
    {
        float temp_hum_val[2] = {0};
        dht.readTempAndHumidity(temp_hum_val);
        Serial.print("Temperature: ");
        Serial.print(temp_hum_val[1]);
        Serial.println ("°C");
    
        delay(10000);
    }
    ```

    このコードは2つのfloat型の空の配列を宣言し、これを`DHT`インスタンスの`readTempAndHumidity`呼び出しに渡します。この呼び出しにより、配列に2つの値が格納されます。湿度は配列の0番目の項目に（C++の配列は0ベースであるため、0番目の項目が配列の「最初」の項目になります）、温度は1番目の項目に格納されます。

    温度は配列の1番目の項目から読み取られ、シリアルポートに出力されます。

    > 🇺🇸 温度は摂氏で読み取られます。アメリカ人向けにこれを華氏に変換するには、読み取った摂氏値を5で割り、9を掛けてから32を足します。例えば、20°Cの温度は((20/5)*9) + 32 = 68°Fとなります。

1. コードをビルドしてWio Terminalにアップロードします。

    > ⚠️ 必要に応じて、[プロジェクト1、レッスン1のPlatformIOプロジェクト作成手順](../../../1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md#write-the-hello-world-app)を参照してください。

1. アップロードが完了したら、シリアルモニターを使用して温度を監視できます：

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 25.00°C
    Temperature: 24.00°C
    ```

> 💁 このコードは[code-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/wio-terminal)フォルダーにあります。

😀 温度センサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。