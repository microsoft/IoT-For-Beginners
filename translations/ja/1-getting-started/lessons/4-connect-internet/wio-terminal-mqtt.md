<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-24T23:11:43+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "ja"
}
-->
# インターネット経由でナイトライトを制御する - Wio Terminal

IoTデバイスは、MQTTを使用して*test.mosquitto.org*と通信するようにコード化する必要があります。これにより、光センサーの読み取り値を含むテレメトリーデータを送信し、LEDを制御するコマンドを受信します。

このレッスンのこの部分では、Wio TerminalをMQTTブローカーに接続します。

## WiFiおよびMQTT Arduinoライブラリのインストール

MQTTブローカーと通信するには、Wio TerminalのWiFiチップを使用するためのArduinoライブラリをインストールし、MQTTと通信できるようにする必要があります。Arduinoデバイスの開発では、オープンソースコードを含む多くのライブラリを利用でき、さまざまな機能を実装できます。Seeedは、Wio TerminalがWiFiを介して通信できるようにするライブラリを公開しています。他の開発者は、MQTTブローカーと通信するためのライブラリを公開しており、これらをデバイスで使用します。

これらのライブラリはソースコードとして提供され、PlatformIOに自動的にインポートしてデバイス用にコンパイルできます。この方法により、Arduinoフレームワークをサポートするデバイスであれば、特定のハードウェアが必要な場合を除き、どのデバイスでもArduinoライブラリを使用できます。たとえば、Seeed WiFiライブラリのように、特定のハードウェアに特化したライブラリもあります。

ライブラリはグローバルにインストールして必要に応じてコンパイルすることも、特定のプロジェクトにインストールすることもできます。この課題では、ライブラリをプロジェクトにインストールします。

✅ ライブラリ管理やライブラリの検索・インストール方法については、[PlatformIOライブラリドキュメント](https://docs.platformio.org/en/latest/librarymanager/index.html)で詳しく学べます。

### タスク - WiFiおよびMQTT Arduinoライブラリのインストール

Arduinoライブラリをインストールします。

1. VS Codeでナイトライトプロジェクトを開きます。

1. `platformio.ini`ファイルの末尾に以下を追加します：

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    これにより、Seeed WiFiライブラリがインポートされます。`@ <number>`の構文は、ライブラリの特定のバージョン番号を指します。

    > 💁 `@ <number>`を削除すると、常に最新バージョンのライブラリを使用するようになりますが、後述のコードが後のバージョンで動作する保証はありません。ここでのコードは、このバージョンのライブラリでテストされています。

    これでライブラリを追加する準備は完了です。次回PlatformIOがプロジェクトをビルドする際に、これらのライブラリのソースコードをダウンロードし、プロジェクトにコンパイルします。

1. `lib_deps`に以下を追加します：

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    これは、[PubSubClient](https://github.com/knolleary/pubsubclient)というArduino MQTTクライアントをインポートします。

## WiFiに接続する

これでWio TerminalをWiFiに接続できるようになりました。

### タスク - WiFiに接続する

Wio TerminalをWiFiに接続します。

1. `src`フォルダに`config.h`という新しいファイルを作成します。これは、`src`フォルダまたはその中の`main.cpp`ファイルを選択し、エクスプローラーの**新しいファイル**ボタンをクリックすることで行えます。このボタンは、カーソルがエクスプローラー上にあるときにのみ表示されます。

    ![新しいファイルボタン](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.ja.png)

1. このファイルに以下のコードを追加し、WiFiの認証情報を定義します：

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    `<SSID>`をWiFiのSSIDに置き換えます。`<PASSWORD>`をWiFiのパスワードに置き換えます。

1. `main.cpp`ファイルを開きます。

1. ファイルの先頭に以下の`#include`ディレクティブを追加します：

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    これは、先ほど追加したライブラリやconfigヘッダーファイルのヘッダーファイルを含めます。これらのヘッダーファイルを明示的に含めないと、一部のコードがコンパイルされず、コンパイラエラーが発生します。

1. `setup`関数の上に以下のコードを追加します：

    ```cpp
    void connectWiFi()
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi..");
            WiFi.begin(SSID, PASSWORD);
            delay(500);
        }
    
        Serial.println("Connected!");
    }
    ```

    このコードは、デバイスがWiFiに接続されていない間ループし、configヘッダーファイルから取得したSSIDとパスワードを使用して接続を試みます。

1. この関数を`setup`関数のピン設定後に呼び出します。

    ```cpp
    connectWiFi();
    ```

1. このコードをデバイスにアップロードして、WiFi接続が機能しているか確認します。シリアルモニターに以下が表示されるはずです。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## MQTTに接続する

Wio TerminalがWiFiに接続されたら、MQTTブローカーに接続できます。

### タスク - MQTTに接続する

MQTTブローカーに接続します。

1. `config.h`ファイルの末尾に以下のコードを追加し、MQTTブローカーの接続情報を定義します：

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    `<ID>`を、このデバイスクライアントの名前として使用する一意のIDに置き換えます。このIDは、後でこのデバイスが発行および購読するトピックにも使用されます。*test.mosquitto.org*ブローカーは公開されており、多くの人が使用しています。この課題に取り組む他の学生も含まれます。一意のMQTTクライアント名とトピック名を持つことで、コードが他の人のコードと競合しないようにします。このIDは、後でサーバーコードを作成する際にも必要です。

    > 💁 [GUIDGen](https://www.guidgen.com)のようなウェブサイトを使用して、一意のIDを生成できます。

    `BROKER`はMQTTブローカーのURLです。

    `CLIENT_NAME`は、このブローカー上でのMQTTクライアントの一意の名前です。

1. `main.cpp`ファイルを開き、`connectWiFi`関数の下、`setup`関数の上に以下のコードを追加します：

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    このコードは、Wio Terminal WiFiライブラリを使用してWiFiクライアントを作成し、それを使用してMQTTクライアントを作成します。

1. このコードの下に以下を追加します：

    ```cpp
    void reconnectMQTTClient()
    {
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
    
            if (client.connect(CLIENT_NAME.c_str()))
            {
                Serial.println("connected");
            }
            else
            {
                Serial.print("Retying in 5 seconds - failed, rc=");
                Serial.println(client.state());
                
                delay(5000);
            }
        }
    }
    ```

    この関数は、MQTTブローカーへの接続をテストし、接続されていない場合は再接続します。接続されていない間はループし、configヘッダーファイルで定義された一意のクライアント名を使用して接続を試みます。

    接続に失敗した場合、5秒後に再試行します。

1. `reconnectMQTTClient`関数の下に以下のコードを追加します：

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    このコードは、クライアントのMQTTブローカーを設定し、メッセージを受信したときのコールバックを設定します。その後、ブローカーへの接続を試みます。

1. WiFi接続後に`setup`関数内で`createMQTTClient`関数を呼び出します。

1. `loop`関数全体を以下のコードに置き換えます：

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    このコードは、まずMQTTブローカーへの再接続を行います。これらの接続は簡単に切断される可能性があるため、定期的に確認し、必要に応じて再接続する価値があります。その後、MQTTクライアントの`loop`メソッドを呼び出して、購読しているトピックで受信しているメッセージを処理します。このアプリはシングルスレッドで動作するため、バックグラウンドスレッドでメッセージを受信することはできません。そのため、ネットワーク接続で待機しているメッセージを処理するためにメインスレッドの時間を割り当てる必要があります。

    最後に、2秒の遅延を設けることで、光レベルが頻繁に送信されるのを防ぎ、デバイスの消費電力を削減します。

1. このコードをWio Terminalにアップロードし、シリアルモニターを使用してデバイスがWiFiおよびMQTTに接続されているのを確認します。

    ```output
    > Executing task: platformio device monitor <
    
    source /Users/jimbennett/GitHub/IoT-For-Beginners/1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal/nightlight/.venv/bin/activate
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    ```

> 💁 このコードは[code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal)フォルダにあります。

😀 デバイスをMQTTブローカーに正常に接続しました。

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳を推奨します。この翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。