<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "da6ae0a795cf06be33d23ca5b8493fc8",
  "translation_date": "2025-08-25T00:44:50+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-sensor.md",
  "language_code": "ja"
}
-->
# GPSデータを読み取る - Wio Terminal

このレッスンでは、Wio TerminalにGPSセンサーを追加し、その値を読み取ります。

## ハードウェア

Wio TerminalにはGPSセンサーが必要です。

使用するセンサーは[Grove GPS Air530センサー](https://www.seeedstudio.com/Grove-GPS-Air530-p-4584.html)です。このセンサーは複数のGPSシステムに接続でき、迅速かつ正確な位置情報を取得できます。センサーは2つの部分で構成されており、センサーのコア電子部品と、衛星からの電波を受信するための薄いワイヤーで接続された外部アンテナがあります。

このセンサーはUARTセンサーであり、UARTを介してGPSデータを送信します。

### GPSセンサーを接続する

Grove GPSセンサーはWio Terminalに接続できます。

#### タスク - GPSセンサーを接続する

GPSセンサーを接続します。

![Grove GPSセンサー](../../../../../translated_images/ja/grove-gps-sensor.247943bf69b03f0d1820ef6ed10c587f9b650e8db55b936851c92412180bd3e2.png)

1. Groveケーブルの片方の端をGPSセンサーのソケットに差し込みます。ケーブルは一方向にしか差し込めません。

1. Wio Terminalをコンピュータやその他の電源から切断した状態で、Groveケーブルのもう片方の端をWio Terminalの画面左側のGroveソケットに接続します。このソケットは電源ボタンに最も近いソケットです。

    ![左側のソケットに接続されたGrove GPSセンサー](../../../../../translated_images/ja/wio-gps-sensor.19fd52b81ce58095.webp)

1. GPSセンサーを配置し、接続されたアンテナが空を見渡せるようにします。理想的には窓の近くや屋外に置くと良いです。アンテナに障害物がない方が信号を受信しやすくなります。

1. Wio Terminalをコンピュータに接続します。

1. GPSセンサーには2つのLEDがあります。青色のLEDはデータが送信されると点滅し、緑色のLEDは衛星からデータを受信すると毎秒点滅します。Wio Terminalの電源を入れた際に青色のLEDが点滅していることを確認してください。数分後に緑色のLEDが点滅します。点滅しない場合はアンテナの位置を調整する必要があるかもしれません。

## GPSセンサーをプログラムする

Wio Terminalをプログラムして接続されたGPSセンサーを使用できるようにします。

### タスク - GPSセンサーをプログラムする

デバイスをプログラムします。

1. PlatformIOを使用して新しいWio Terminalプロジェクトを作成します。このプロジェクトを`gps-sensor`と名付けます。`setup`関数内にシリアルポートを設定するコードを追加します。

1. `main.cpp`ファイルの冒頭に以下のインクルードディレクティブを追加します。これにより、左側のGroveポートをUART用に設定する関数が含まれます。

    ```cpp
    #include <wiring_private.h>
    ```

1. その下に以下のコードを追加して、UARTポートへのシリアルポート接続を宣言します。

    ```cpp
    static Uart Serial3(&sercom3, PIN_WIRE_SCL, PIN_WIRE_SDA, SERCOM_RX_PAD_1, UART_TX_PAD_0);
    ```

1. 内部のシグナルハンドラをこのシリアルポートにリダイレクトするコードを追加する必要があります。`Serial3`の宣言の下に以下のコードを追加します。

    ```cpp
    void SERCOM3_0_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_1_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_2_Handler()
    {
        Serial3.IrqHandler();
    }
    
    void SERCOM3_3_Handler()
    {
        Serial3.IrqHandler();
    }
    ```

1. `setup`関数内で`Serial`ポートを設定した後、以下のコードを使用してUARTシリアルポートを設定します。

    ```cpp
    Serial3.begin(9600);

    while (!Serial3)
        ; // Wait for Serial3 to be ready

    delay(1000);
    ```

1. `setup`関数内のこのコードの下に、以下のコードを追加してGroveピンをシリアルポートに接続します。

    ```cpp
    pinPeripheral(PIN_WIRE_SCL, PIO_SERCOM_ALT);
    ```

1. `loop`関数の前に以下の関数を追加して、GPSデータをシリアルモニターに送信します。

    ```cpp
    void printGPSData()
    {
        Serial.println(Serial3.readStringUntil('\n'));
    }
    ```

1. `loop`関数内に以下のコードを追加して、UARTシリアルポートからデータを読み取り、シリアルモニターに出力します。

    ```cpp
    while (Serial3.available() > 0)
    {
        printGPSData();
    }
    
    delay(1000);
    ```

    このコードはUARTシリアルポートからデータを読み取ります。`readStringUntil`関数は終端文字（この場合は改行）まで読み取ります。これにより、1つのNMEA文（NMEA文は改行文字で終端されます）を読み取ることができます。UARTシリアルポートからデータを読み取れる間は、データを読み取り、`printGPSData`関数を介してシリアルモニターに送信します。データが読み取れなくなると、`loop`関数は1秒（1,000ms）遅延します。

1. コードをビルドしてWio Terminalにアップロードします。

1. アップロードが完了したら、シリアルモニターを使用してGPSデータを確認できます。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GPGSA,A,1,,,,,,,,,,,,,,,*1E
    $BDGSA,A,1,,,,,,,,,,,,,,,*0F
    $GPGSV,1,1,00*79
    $BDGSV,1,1,00*68
    ```

> 💁 このコードは[code-gps/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps/wio-terminal)フォルダーにあります。

😀 GPSセンサーのプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。