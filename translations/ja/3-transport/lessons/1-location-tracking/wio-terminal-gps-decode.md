<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "fbbcf96a9b63ccd661db98bbf854bb06",
  "translation_date": "2025-08-25T00:54:58+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/wio-terminal-gps-decode.md",
  "language_code": "ja"
}
-->
# GPSデータをデコードする - Wio Terminal

このレッスンでは、Wio TerminalのGPSセンサーから読み取ったNMEAメッセージをデコードし、緯度と経度を抽出します。

## GPSデータをデコードする

シリアルポートから生のNMEAデータを読み取った後、オープンソースのNMEAライブラリを使用してデコードすることができます。

### タスク - GPSデータをデコードする

デバイスをプログラムしてGPSデータをデコードしましょう。

1. `gps-sensor`アプリプロジェクトをまだ開いていない場合は開いてください。

1. プロジェクトの`platformio.ini`ファイルに[TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus)ライブラリの依存関係を追加します。このライブラリにはNMEAデータをデコードするためのコードが含まれています。

    ```ini
    lib_deps =
        mikalhart/TinyGPSPlus @ 1.0.2
    ```

1. `main.cpp`にTinyGPSPlusライブラリをインクルードするディレクティブを追加します：

    ```cpp
    #include <TinyGPS++.h>
    ```

1. `Serial3`の宣言の下に、NMEA文を処理するためのTinyGPSPlusオブジェクトを宣言します：

    ```cpp
    TinyGPSPlus gps;
    ```

1. `printGPSData`関数の内容を以下のように変更します：

    ```cpp
    if (gps.encode(Serial3.read()))
    {
        if (gps.location.isValid())
        {
            Serial.print(gps.location.lat(), 6);
            Serial.print(F(","));
            Serial.print(gps.location.lng(), 6);
            Serial.print(" - from ");
            Serial.print(gps.satellites.value());
            Serial.println(" satellites");
        }
    }
    ```

    このコードは、UARTシリアルポートから次の文字を`gps` NMEAデコーダーに読み込みます。各文字の後、デコーダーが有効な文を読み取ったかどうかを確認し、その後、有効な位置情報を読み取ったかどうかを確認します。位置情報が有効であれば、それをシリアルモニターに送信し、この位置情報の取得に寄与した衛星の数も表示します。

1. コードをビルドしてWio Terminalにアップロードします。

1. アップロードが完了したら、シリアルモニターを使用してGPS位置データを確認できます。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    47.6423109,-122.1390293 - from 3 satellites
    ```

> 💁 このコードは[code-gps-decode/wio-terminal](../../../../../3-transport/lessons/1-location-tracking/code-gps-decode/wio-terminal)フォルダにあります。

😀 GPSセンサーのデータデコードプログラムが成功しました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を期すよう努めておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があります。元の言語で記載された原文が公式な情報源と見なされるべきです。重要な情報については、専門の人間による翻訳を推奨します。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。