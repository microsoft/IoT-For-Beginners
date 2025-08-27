<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-26T23:01:39+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "mo"
}
-->
# 將您的 IoT 裝置連接到雲端 - Wio Terminal

在本課程的這部分，您將把 Wio Terminal 連接到 IoT Hub，以傳送遙測數據並接收指令。

## 將您的裝置連接到 IoT Hub

下一步是將您的裝置連接到 IoT Hub。

### 任務 - 連接到 IoT Hub

1. 在 VS Code 中打開 `soil-moisture-sensor` 專案。

1. 打開 `platformio.ini` 文件。移除 `knolleary/PubSubClient` 庫的依賴項。這個庫是用來連接到公共 MQTT broker 的，但連接到 IoT Hub 不需要它。

1. 添加以下庫依賴項：

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` 庫提供了與 Wio Terminal 的實時時鐘交互的代碼，用於追蹤時間。其餘的庫則允許您的 IoT 裝置連接到 IoT Hub。

1. 在 `platformio.ini` 文件的底部添加以下內容：

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    這設置了一個編譯器標誌，在編譯 Arduino IoT Hub 代碼時需要。

1. 打開 `config.h` 標頭文件。移除所有 MQTT 設定，並添加以下裝置連接字串的常量：

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    將 `<connection string>` 替換為您之前複製的裝置連接字串。

1. 連接到 IoT Hub 使用基於時間的令牌。這意味著 IoT 裝置需要知道當前時間。與 Windows、macOS 或 Linux 等操作系統不同，微控制器不會自動通過網路同步當前時間。因此，您需要添加代碼以從 [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) 伺服器獲取當前時間。一旦獲取了時間，它可以存儲在 Wio Terminal 的實時時鐘中，允許在稍後日期請求正確的時間，假設裝置未斷電。新增一個名為 `ntp.h` 的文件，並添加以下代碼：

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

    此代碼的細節超出了本課程的範圍。它定義了一個名為 `initTime` 的函數，用於從 NTP 伺服器獲取當前時間並用它設置 Wio Terminal 的時鐘。

1. 打開 `main.cpp` 文件，移除所有 MQTT 代碼，包括 `PubSubClient.h` 標頭文件、`PubSubClient` 變數的聲明、`reconnectMQTTClient` 和 `createMQTTClient` 方法，以及對這些變數和方法的任何調用。此文件應僅包含連接 WiFi、獲取土壤濕度並創建 JSON 文檔的代碼。

1. 在 `main.cpp` 文件的頂部添加以下 `#include` 指令，以包含 IoT Hub 庫和設置時間的標頭文件：

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. 在 `setup` 函數的末尾添加以下調用以設置當前時間：

    ```cpp
    initTime();
    ```

1. 在文件的頂部，包含指令下方添加以下變數聲明：

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    這聲明了一個 `IOTHUB_DEVICE_CLIENT_LL_HANDLE`，用於連接到 IoT Hub 的句柄。

1. 在此下方添加以下代碼：

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

    這聲明了一個回調函數，當連接到 IoT Hub 的狀態改變（例如連接或斷開）時會被調用。狀態會被發送到串口。

1. 在此下方添加一個函數以連接到 IoT Hub：

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

    此代碼初始化 IoT Hub 庫代碼，然後使用 `config.h` 標頭文件中的連接字串創建連接。此連接基於 MQTT。如果連接失敗，會將此信息發送到串口——如果您在輸出中看到此信息，請檢查連接字串。最後，設置了連接狀態回調。

1. 在 `setup` 函數中，將此函數調用添加到 `initTime` 調用的下方：

    ```cpp
    connectIoTHub();
    ```

1. 與 MQTT 客戶端一樣，此代碼在單一線程上運行，因此需要時間來處理由 Hub 發送和發送到 Hub 的消息。在 `loop` 函數的頂部添加以下內容以完成此操作：

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. 編譯並上傳此代碼。您將在串口監視器中看到連接：

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    在輸出中，您可以看到 NTP 時間被獲取，接著是裝置客戶端連接。連接可能需要幾秒鐘，因此在裝置連接時，您可能會在輸出中看到土壤濕度。

    > 💁 您可以使用像 [unixtimestamp.com](https://www.unixtimestamp.com) 這樣的網站將 NTP 的 UNIX 時間轉換為更易讀的版本。

## 傳送遙測數據

現在您的裝置已連接，您可以將遙測數據傳送到 IoT Hub，而不是 MQTT broker。

### 任務 - 傳送遙測數據

1. 在 `setup` 函數上方添加以下函數：

    ```cpp
    void sendTelemetry(const char *telemetry)
    {
        IOTHUB_MESSAGE_HANDLE message_handle = IoTHubMessage_CreateFromString(telemetry);
        IoTHubDeviceClient_LL_SendEventAsync(_device_ll_handle, message_handle, NULL, NULL);
        IoTHubMessage_Destroy(message_handle);
    }
    ```

    此代碼從作為參數傳遞的字串創建 IoT Hub 消息，將其發送到 Hub，然後清理消息對象。

1. 在 `loop` 函數中，將此代碼調用添加到遙測數據發送到串口的行之後：

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## 處理指令

您的裝置需要處理來自伺服器代碼的指令，以控制繼電器。這是通過直接方法請求發送的。

## 任務 - 處理直接方法請求

1. 在 `connectIoTHub` 函數之前添加以下代碼：

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

    此代碼定義了一個回調方法，當 IoT Hub 庫接收到直接方法請求時可以調用。請求的方法通過 `method_name` 參數傳遞。此函數將調用的方法打印到串口，然後根據方法名稱打開或關閉繼電器。

    > 💁 這也可以通過單一直接方法請求實現，將繼電器的期望狀態作為有效負載傳遞，該有效負載可以通過 `payload` 參數獲得。

1. 在 `directMethodCallback` 函數的末尾添加以下代碼：

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    直接方法請求需要響應，響應分為兩部分——作為文本的響應和返回代碼。此代碼將創建以下 JSON 文檔作為結果：

    ```JSON
    {
        "Result": ""
    }
    ```

    然後將其複製到 `response` 參數中，並在 `response_size` 參數中設置此響應的大小。此代碼然後返回 `IOTHUB_CLIENT_OK`，表示方法已正確處理。

1. 在 `connectIoTHub` 函數的末尾添加以下代碼以連接回調：

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` 函數將調用 `IoTHubDeviceClient_LL_DoWork` 函數以處理 IoT Hub 發送的事件。由於 `delay` 的原因，此函數僅每 10 秒調用一次，這意味著直接方法僅每 10 秒處理一次。為了提高效率，10 秒的延遲可以分為多個較短的延遲，每次都調用 `IoTHubDeviceClient_LL_DoWork`。為此，在 `loop` 函數上方添加以下代碼：

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

    此代碼將重複循環，調用 `IoTHubDeviceClient_LL_DoWork` 並每次延遲 100 毫秒。它將根據 `delay_time` 參數的值執行多次，這意味著裝置最多等待 100 毫秒來處理直接方法請求。

1. 在 `loop` 函數中，移除對 `IoTHubDeviceClient_LL_DoWork` 的調用，並將 `delay(10000)` 替換為以下代碼以調用此新函數：

    ```cpp
    work_delay(10000);
    ```

> 💁 您可以在 [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) 文件夾中找到此代碼。

😀 您的土壤濕度感測器程式已成功連接到 IoT Hub！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。