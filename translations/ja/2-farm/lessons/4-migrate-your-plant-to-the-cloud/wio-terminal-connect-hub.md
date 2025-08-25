<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-24T22:50:46+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "ja"
}
-->
# IoTデバイスをクラウドに接続する - Wio Terminal

このレッスンでは、Wio TerminalをIoT Hubに接続し、テレメトリを送信したりコマンドを受信したりします。

## デバイスをIoT Hubに接続する

次のステップでは、デバイスをIoT Hubに接続します。

### タスク - IoT Hubに接続する

1. VS Codeで`soil-moisture-sensor`プロジェクトを開きます。

1. `platformio.ini`ファイルを開きます。`knolleary/PubSubClient`ライブラリ依存関係を削除してください。このライブラリは公開MQTTブローカーに接続するために使用されていましたが、IoT Hubに接続するためには必要ありません。

1. 以下のライブラリ依存関係を追加してください：

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC`ライブラリは、Wio Terminalのリアルタイムクロックと連携するコードを提供します。残りのライブラリは、IoTデバイスがIoT Hubに接続するために必要です。

1. `platformio.ini`ファイルの末尾に以下を追加してください：

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    これは、Arduino IoT Hubコードをコンパイルする際に必要なコンパイラフラグを設定します。

1. `config.h`ヘッダーファイルを開きます。すべてのMQTT設定を削除し、デバイス接続文字列のための以下の定数を追加してください：

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    `<connection string>`を、以前コピーしたデバイスの接続文字列に置き換えてください。

1. IoT Hubへの接続は時間ベースのトークンを使用します。そのため、IoTデバイスは現在の時刻を知る必要があります。Windows、macOS、Linuxのようなオペレーティングシステムとは異なり、マイクロコントローラーはインターネット経由で自動的に現在の時刻を同期しません。そのため、[NTP](https://wikipedia.org/wiki/Network_Time_Protocol)サーバーから現在の時刻を取得するコードを追加する必要があります。時刻が取得されると、Wio Terminalのリアルタイムクロックに保存され、デバイスが電源を失わない限り、後で正しい時刻を要求できます。以下のコードを含む新しいファイル`ntp.h`を作成してください：

    ```cpp
    #pragma once
    
    #include "DateTime.h"
    #include <time.h>
    #include "samd/NTPClientAz.h"
    #include <sys/time.h>

    static void initTime()
    {
        WiFiUDP _udp;
        time_t epochTime = (time_t)-1;
        NTPClientAz ntpClient;

        ntpClient.begin();

        while (true)
        {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (time_t)-1)
            {
                Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
                delay(2000);
            }
            else
            {
                Serial.print("Fetched NTP epoch time is: ");

                char buff[32];
                sprintf(buff, "%.f", difftime(epochTime, (time_t)0));
                Serial.println(buff);
                break;
            }
        }

        ntpClient.end();

        struct timeval tv;
        tv.tv_sec = epochTime;
        tv.tv_usec = 0;

        settimeofday(&tv, NULL);
    }
    ```

    このコードの詳細はこのレッスンの範囲外です。このコードは、NTPサーバーから現在の時刻を取得し、それを使用してWio Terminalの時計を設定する`initTime`という関数を定義します。

1. `main.cpp`ファイルを開き、すべてのMQTTコードを削除してください。これには、`PubSubClient.h`ヘッダーファイル、`PubSubClient`変数の宣言、`reconnectMQTTClient`および`createMQTTClient`メソッド、これらの変数やメソッドへの呼び出しが含まれます。このファイルには、WiFiに接続し、土壌湿度を取得し、それを含むJSONドキュメントを作成するコードのみが含まれるべきです。

1. `main.cpp`ファイルの冒頭に以下の`#include`ディレクティブを追加し、IoT Hubライブラリと時刻設定用のヘッダーファイルを含めます：

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. `setup`関数の末尾に以下の呼び出しを追加し、現在の時刻を設定します：

    ```cpp
    initTime();
    ```

1. ファイルの冒頭、`include`ディレクティブのすぐ下に以下の変数宣言を追加してください：

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    これは、IoT Hubへの接続を管理する`IOTHUB_DEVICE_CLIENT_LL_HANDLE`を宣言します。

1. その下に以下のコードを追加してください：

    ```cpp
    static void connectionStatusCallback(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void *user_context)
    {
        if (result == IOTHUB_CLIENT_CONNECTION_AUTHENTICATED)
        {
            Serial.println("The device client is connected to iothub");
        }
        else
        {
            Serial.println("The device client has been disconnected");
        }
    }
    ```

    これは、IoT Hubへの接続状態が変化したときに呼び出されるコールバック関数を宣言します。接続状態はシリアルポートに送信されます。

1. その下にIoT Hubに接続する関数を追加してください：

    ```cpp
    void connectIoTHub()
    {
        IoTHub_Init();
    
        _device_ll_handle = IoTHubDeviceClient_LL_CreateFromConnectionString(CONNECTION_STRING, MQTT_Protocol);
        
        if (_device_ll_handle == NULL)
        {
            Serial.println("Failure creating Iothub device. Hint: Check your connection string.");
            return;
        }
    
        IoTHubDeviceClient_LL_SetConnectionStatusCallback(_device_ll_handle, connectionStatusCallback, NULL);
    }
    ```

    このコードは、IoT Hubライブラリコードを初期化し、`config.h`ヘッダーファイル内の接続文字列を使用して接続を作成します。この接続はMQTTに基づいています。接続が失敗した場合、シリアルポートに通知されます。出力でこれが表示された場合は、接続文字列を確認してください。最後に、接続状態コールバックが設定されます。

1. この関数を`setup`関数内の`initTime`呼び出しの下に追加してください：

    ```cpp
    connectIoTHub();
    ```

1. MQTTクライアントと同様に、このコードは単一のスレッドで動作するため、ハブから送信されるメッセージやハブに送信されるメッセージを処理する時間が必要です。以下を`loop`関数の冒頭に追加してください：

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. このコードをビルドしてアップロードしてください。シリアルモニターに接続が表示されます：

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    出力には、NTP時刻の取得後にデバイスクライアントが接続する様子が表示されます。接続には数秒かかる場合があるため、デバイスが接続している間に土壌湿度が出力に表示されることがあります。

    > 💁 NTPのUNIX時刻をより読みやすい形式に変換するには、[unixtimestamp.com](https://www.unixtimestamp.com)のようなウェブサイトを使用できます。

## テレメトリを送信する

デバイスが接続されたので、MQTTブローカーではなくIoT Hubにテレメトリを送信できます。

### タスク - テレメトリを送信する

1. `setup`関数の上に以下の関数を追加してください：

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    このコードは、渡された文字列からIoT Hubメッセージを作成し、それをハブに送信し、メッセージオブジェクトをクリーンアップします。

1. このコードを`loop`関数内で、テレメトリがシリアルポートに送信される行の直後に呼び出してください：

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## コマンドを処理する

デバイスは、リレーを制御するためにサーバーコードから送信されるコマンドを処理する必要があります。これは直接メソッドリクエストとして送信されます。

### タスク - 直接メソッドリクエストを処理する

1. `connectIoTHub`関数の前に以下のコードを追加してください：

    ```cpp
    int directMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
    {
        Serial.printf("Direct method received %s\r\n", method_name);
    
        if (strcmp(method_name, "relay_on") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, HIGH);
        }
        else if (strcmp(method_name, "relay_off") == 0)
        {
            digitalWrite(PIN_WIRE_SCL, LOW);
        }
    }
    ```

    このコードは、IoT Hubライブラリが直接メソッドリクエストを受信したときに呼び出すコールバックメソッドを定義します。リクエストされたメソッドは`method_name`パラメータで送信されます。この関数は、呼び出されたメソッドをシリアルポートに出力し、メソッド名に応じてリレーをオンまたはオフにします。

    > 💁 この機能は、リレーの希望する状態をペイロードとして渡し、メソッドリクエストとともに送信される単一の直接メソッドリクエストとしても実装できます。

1. `directMethodCallback`関数の末尾に以下のコードを追加してください：

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    直接メソッドリクエストには応答が必要であり、応答はテキストとしての応答と戻りコードの2つの部分で構成されます。このコードは以下のJSONドキュメントとして結果を作成します：

    ```JSON
    {
        "Result": ""
    }
    ```

    これが`response`パラメータにコピーされ、`response_size`パラメータでこの応答のサイズが設定されます。このコードは、メソッドが正しく処理されたことを示すために`IOTHUB_CLIENT_OK`を返します。

1. 以下のコードを`connectIoTHub`関数の末尾に追加し、コールバックを設定してください：

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop`関数は、IoT Hubから送信されるイベントを処理するために`IoTHubDeviceClient_LL_DoWork`関数を呼び出します。この関数は`delay`によって10秒ごとにしか呼び出されないため、直接メソッドは10秒ごとにしか処理されません。これをより効率的にするために、10秒の遅延を複数の短い遅延として実装し、その間に`IoTHubDeviceClient_LL_DoWork`を毎回呼び出すことができます。以下のコードを`loop`関数の上に追加してください：

    ```cpp
    void work_delay(int delay_time)
    {
        int current = 0;
        do
        {
            IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
            delay(100);
            current += 100;
        } while (current < delay_time);
    }
    ```

    このコードは繰り返しループし、`IoTHubDeviceClient_LL_DoWork`を呼び出し、毎回100ms遅延します。これを必要な回数だけ繰り返し、`delay_time`パラメータで指定された時間だけ遅延します。これにより、デバイスは最大100msで直接メソッドリクエストを処理します。

1. `loop`関数内で`IoTHubDeviceClient_LL_DoWork`の呼び出しを削除し、`delay(10000)`の呼び出しを以下のコードに置き換えて新しい関数を呼び出してください：

    ```cpp
    work_delay(10000);
    ```

> 💁 このコードは[code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal)フォルダーにあります。

😀 土壌湿度センサーのプログラムがIoT Hubに接続されました！

**免責事項**:  
この文書は、AI翻訳サービス [Co-op Translator](https://github.com/Azure/co-op-translator) を使用して翻訳されています。正確性を追求しておりますが、自動翻訳には誤りや不正確な部分が含まれる可能性があることをご承知おきください。元の言語で記載された文書が公式な情報源とみなされるべきです。重要な情報については、専門の人間による翻訳をお勧めします。本翻訳の使用に起因する誤解や誤認について、当方は一切の責任を負いません。