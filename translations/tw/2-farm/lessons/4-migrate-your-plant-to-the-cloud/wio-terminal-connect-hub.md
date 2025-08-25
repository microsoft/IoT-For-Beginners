<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "28320305a35ea3bc59c41fe146a2e6ed",
  "translation_date": "2025-08-24T22:49:57+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/wio-terminal-connect-hub.md",
  "language_code": "tw"
}
-->
# 將您的 IoT 裝置連接到雲端 - Wio Terminal

在本課程的這部分，您將把 Wio Terminal 連接到 IoT Hub，以傳送遙測數據並接收指令。

## 將裝置連接到 IoT Hub

下一步是將您的裝置連接到 IoT Hub。

### 任務 - 連接到 IoT Hub

1. 在 VS Code 中打開 `soil-moisture-sensor` 專案。

1. 打開 `platformio.ini` 檔案。移除 `knolleary/PubSubClient` 函式庫的依賴項。這個函式庫是用來連接到公共 MQTT broker 的，但連接到 IoT Hub 時不需要。

1. 添加以下函式庫依賴項：

    ```ini
    seeed-studio/Seeed Arduino RTC @ 2.0.0
    arduino-libraries/AzureIoTHub @ 1.6.0
    azure/AzureIoTUtility @ 1.6.1
    azure/AzureIoTProtocol_MQTT @ 1.6.0
    azure/AzureIoTProtocol_HTTP @ 1.6.0
    azure/AzureIoTSocket_WiFi @ 1.0.2
    ```

    `Seeed Arduino RTC` 函式庫提供與 Wio Terminal 的實時時鐘互動的程式碼，用於追蹤時間。其餘的函式庫則允許您的 IoT 裝置連接到 IoT Hub。

1. 在 `platformio.ini` 檔案的底部添加以下內容：

    ```ini
    build_flags =
        -DDONT_USE_UPLOADTOBLOB
    ```

    這會設置一個編譯器標誌，在編譯 Arduino IoT Hub 程式碼時需要用到。

1. 打開 `config.h` 標頭檔案。移除所有 MQTT 設定，並添加以下裝置連接字串的常數：

    ```cpp
    // IoT Hub settings
    const char *CONNECTION_STRING = "<connection string>";
    ```

    將 `<connection string>` 替換為您之前複製的裝置連接字串。

1. 連接到 IoT Hub 使用的是基於時間的權杖。這意味著 IoT 裝置需要知道當前時間。與 Windows、macOS 或 Linux 等操作系統不同，微控制器不會自動通過網際網路同步當前時間。因此，您需要添加程式碼從 [NTP](https://wikipedia.org/wiki/Network_Time_Protocol) 伺服器獲取當前時間。一旦獲取時間，它可以存儲在 Wio Terminal 的實時時鐘中，允許在稍後請求正確時間，前提是裝置未斷電。新增一個名為 `ntp.h` 的檔案，並添加以下程式碼：

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

    這段程式碼的細節超出了本課程的範圍。它定義了一個名為 `initTime` 的函數，用於從 NTP 伺服器獲取當前時間，並用它來設置 Wio Terminal 的時鐘。

1. 打開 `main.cpp` 檔案，移除所有 MQTT 程式碼，包括 `PubSubClient.h` 標頭檔案、`PubSubClient` 變數的宣告、`reconnectMQTTClient` 和 `createMQTTClient` 方法，以及對這些變數和方法的任何調用。該檔案應僅包含連接 WiFi、獲取土壤濕度並用其創建 JSON 文件的程式碼。

1. 在 `main.cpp` 檔案的頂部添加以下 `#include` 指令，以包含 IoT Hub 函式庫和設置時間的標頭檔案：

    ```cpp
    #include <AzureIoTHub.h>
    #include <AzureIoTProtocol_MQTT.h>
    #include <iothubtransportmqtt.h>
    #include "ntp.h"
    ```

1. 在 `setup` 函數的末尾添加以下調用來設置當前時間：

    ```cpp
    initTime();
    ```

1. 在檔案頂部的 include 指令下方添加以下變數宣告：

    ```cpp
    IOTHUB_DEVICE_CLIENT_LL_HANDLE _device_ll_handle;
    ```

    這宣告了一個 `IOTHUB_DEVICE_CLIENT_LL_HANDLE`，即 IoT Hub 連接的句柄。

1. 在這之下添加以下程式碼：

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

    這定義了一個回調函數，當連接到 IoT Hub 的狀態發生變化（例如連接或斷開）時會被調用。狀態會被發送到序列埠。

1. 在這之下添加一個函數來連接到 IoT Hub：

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

    這段程式碼初始化 IoT Hub 函式庫程式碼，然後使用 `config.h` 標頭檔案中的連接字串創建連接。該連接基於 MQTT。如果連接失敗，錯誤會被發送到序列埠——如果您在輸出中看到這個錯誤，請檢查連接字串。最後，設置連接狀態回調。

1. 在 `setup` 函數中，將此函數調用添加到 `initTime` 調用的下方：

    ```cpp
    connectIoTHub();
    ```

1. 與 MQTT 客戶端一樣，這段程式碼在單一執行緒上運行，因此需要時間來處理由 Hub 發送和接收的消息。在 `loop` 函數的頂部添加以下內容來實現：

    ```cpp
    IoTHubDeviceClient_LL_DoWork(_device_ll_handle);
    ```

1. 編譯並上傳這段程式碼。您會在序列監視器中看到連接：

    ```output
    Connecting to WiFi..
    Connected!
    Fetched NTP epoch time is: 1619983687
    Sending telemetry {"soil_moisture":391}
    The device client is connected to iothub
    ```

    在輸出中，您可以看到 NTP 時間被獲取，隨後裝置客戶端連接。連接可能需要幾秒鐘，因此在裝置連接時，您可能會在輸出中看到土壤濕度。

    > 💁 您可以使用像 [unixtimestamp.com](https://www.unixtimestamp.com) 這樣的網站將 UNIX 時間轉換為更易讀的格式。

## 傳送遙測數據

現在您的裝置已連接，您可以將遙測數據發送到 IoT Hub，而不是 MQTT broker。

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

    這段程式碼從作為參數傳遞的字串創建一個 IoT Hub 消息，將其發送到 Hub，然後清理消息物件。

1. 在 `loop` 函數中，在將遙測數據發送到序列埠的那一行之後調用這段程式碼：

    ```cpp
    sendTelemetry(telemetry.c_str());
    ```

## 處理指令

您的裝置需要處理來自伺服器程式碼的指令，以控制繼電器。這是作為直接方法請求發送的。

## 任務 - 處理直接方法請求

1. 在 `connectIoTHub` 函數之前添加以下程式碼：

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

    這段程式碼定義了一個回調方法，當 IoT Hub 函式庫收到直接方法請求時會調用。請求的方法名稱會通過 `method_name` 參數傳遞。該函數會將調用的方法名稱打印到序列埠，然後根據方法名稱打開或關閉繼電器。

    > 💁 這也可以通過單一的直接方法請求來實現，將繼電器的期望狀態作為有效負載傳遞，該有效負載可以通過 `payload` 參數獲取。

1. 在 `directMethodCallback` 函數的末尾添加以下程式碼：

    ```cpp
    char resultBuff[16];
    sprintf(resultBuff, "{\"Result\":\"\"}");
    *response_size = strlen(resultBuff);
    *response = (unsigned char *)malloc(*response_size);
    memcpy(*response, resultBuff, *response_size);

    return IOTHUB_CLIENT_OK;
    ```

    直接方法請求需要一個回應，回應分為兩部分——作為文字的回應和返回碼。這段程式碼會創建以下 JSON 文件作為結果：

    ```JSON
    {
        "Result": ""
    }
    ```

    然後將其複製到 `response` 參數中，並在 `response_size` 參數中設置該回應的大小。最後，這段程式碼返回 `IOTHUB_CLIENT_OK`，表示方法已正確處理。

1. 在 `connectIoTHub` 函數的末尾添加以下程式碼來連接回調：

    ```cpp
    IoTHubClient_LL_SetDeviceMethodCallback(_device_ll_handle, directMethodCallback, NULL);
    ```

1. `loop` 函數會調用 `IoTHubDeviceClient_LL_DoWork` 函數來處理 IoT Hub 發送的事件。由於 `delay` 的原因，這僅每 10 秒調用一次，這意味著直接方法僅每 10 秒處理一次。為了提高效率，可以將 10 秒的延遲分解為多個較短的延遲，每次調用 `IoTHubDeviceClient_LL_DoWork`。為此，在 `loop` 函數之前添加以下程式碼：

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

    這段程式碼會重複循環，調用 `IoTHubDeviceClient_LL_DoWork` 並每次延遲 100 毫秒。它會根據 `delay_time` 參數的值執行多次，這意味著裝置最多等待 100 毫秒來處理直接方法請求。

1. 在 `loop` 函數中，移除對 `IoTHubDeviceClient_LL_DoWork` 的調用，並將 `delay(10000)` 替換為以下程式碼來調用新函數：

    ```cpp
    work_delay(10000);
    ```

> 💁 您可以在 [code/wio-terminal](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/code/wio-terminal) 資料夾中找到這段程式碼。

😀 您的土壤濕度感測器程式已成功連接到 IoT Hub！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對於因使用本翻譯而產生的任何誤解或錯誤解讀概不負責。