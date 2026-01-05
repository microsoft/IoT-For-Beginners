<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "d6faf0e8d3c2d6d20c0aef2a305dab18",
  "translation_date": "2025-08-26T23:20:27+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md",
  "language_code": "mo"
}
-->
# 通過互聯網控制你的夜燈 - Wio Terminal

物聯網設備需要編寫程式碼，使用 MQTT 與 *test.mosquitto.org* 通訊，發送光感測器讀取的遙測值，並接收控制 LED 的指令。

在本課程的這部分，你將把 Wio Terminal 連接到 MQTT broker。

## 安裝 WiFi 和 MQTT Arduino 函式庫

為了與 MQTT broker 通訊，你需要安裝一些 Arduino 函式庫，使用 Wio Terminal 的 WiFi 晶片並與 MQTT 通訊。在開發 Arduino 設備時，你可以使用大量的函式庫，這些函式庫包含開源程式碼並實現了多種功能。Seeed 提供了 Wio Terminal 的函式庫，允許其通過 WiFi 通訊。其他開發者也發布了與 MQTT broker 通訊的函式庫，你將使用這些函式庫與你的設備進行互動。

這些函式庫以原始碼形式提供，可以自動導入到 PlatformIO 並編譯到你的設備中。這樣，Arduino 函式庫可以在任何支援 Arduino 框架的設備上運行，前提是該設備具有函式庫所需的特定硬體。一些函式庫，例如 Seeed WiFi 函式庫，是針對特定硬體的。

函式庫可以全域安裝並在需要時編譯，也可以安裝到特定專案中。在這次作業中，函式庫將安裝到專案中。

✅ 你可以在 [PlatformIO 函式庫文檔](https://docs.platformio.org/en/latest/librarymanager/index.html) 中了解更多有關函式庫管理以及如何查找和安裝函式庫的資訊。

### 任務 - 安裝 WiFi 和 MQTT Arduino 函式庫

安裝 Arduino 函式庫。

1. 在 VS Code 中打開夜燈專案。

1. 在 `platformio.ini` 文件的末尾添加以下內容：

    ```ini
    lib_deps =
        seeed-studio/Seeed Arduino rpcWiFi @ 1.0.5
        seeed-studio/Seeed Arduino FS @ 2.1.1
        seeed-studio/Seeed Arduino SFUD @ 2.0.2
        seeed-studio/Seeed Arduino rpcUnified @ 2.1.3
        seeed-studio/Seeed_Arduino_mbedtls @ 3.0.1
    ```

    這將導入 Seeed WiFi 函式庫。`@ <number>` 語法指的是函式庫的特定版本號。

    > 💁 你可以移除 `@ <number>` 以始終使用最新版本的函式庫，但不能保證後續版本能與下面的程式碼正常運行。此處的程式碼已使用該版本的函式庫進行測試。

    這就是添加函式庫所需的全部操作。下次 PlatformIO 編譯專案時，它將下載這些函式庫的原始碼並編譯到你的專案中。

1. 在 `lib_deps` 中添加以下內容：

    ```ini
    knolleary/PubSubClient @ 2.8
    ```

    這將導入 [PubSubClient](https://github.com/knolleary/pubsubclient)，一個 Arduino MQTT 客戶端。

## 連接到 WiFi

現在可以將 Wio Terminal 連接到 WiFi。

### 任務 - 連接到 WiFi

將 Wio Terminal 連接到 WiFi。

1. 在 `src` 資料夾中建立一個名為 `config.h` 的新文件。你可以通過選擇 `src` 資料夾或其中的 `main.cpp` 文件，然後在資源管理器中選擇 **新文件** 按鈕來完成。當你的游標位於資源管理器上時，該按鈕才會出現。

    ![新文件按鈕](../../../../../translated_images/vscode-new-file-button.182702340fe6723c.mo.png)

1. 在此文件中添加以下程式碼以定義 WiFi 憑據的常數：

    ```cpp
    #pragma once

    #include <string>
    
    using namespace std;
    
    // WiFi credentials
    const char *SSID = "<SSID>";
    const char *PASSWORD = "<PASSWORD>";
    ```

    將 `<SSID>` 替換為你的 WiFi SSID。將 `<PASSWORD>` 替換為你的 WiFi 密碼。

1. 打開 `main.cpp` 文件。

1. 在文件頂部添加以下 `#include` 指令：

    ```cpp
    #include <PubSubClient.h>
    #include <rpcWiFi.h>
    #include <SPI.h>
    
    #include "config.h"
    ```

    這將包含你之前添加的函式庫的標頭文件以及配置標頭文件。這些標頭文件是必需的，用於告訴 PlatformIO 導入函式庫中的程式碼。如果未顯式包含這些標頭文件，某些程式碼將不會被編譯，並且你會遇到編譯器錯誤。

1. 在 `setup` 函數上方添加以下程式碼：

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

    此程式碼在設備未連接到 WiFi 時進行迴圈，並嘗試使用配置標頭文件中的 SSID 和密碼進行連接。

1. 在 `setup` 函數底部，配置引腳後，調用此函數。

    ```cpp
    connectWiFi();
    ```

1. 將此程式碼上傳到你的設備以檢查 WiFi 連接是否正常。你應該能在序列監視器中看到以下內容。

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    ```

## 連接到 MQTT

Wio Terminal 連接到 WiFi 後，可以連接到 MQTT broker。

### 任務 - 連接到 MQTT

連接到 MQTT broker。

1. 在 `config.h` 文件底部添加以下程式碼，以定義 MQTT broker 的連接詳細資訊：

    ```cpp
    // MQTT settings
    const string ID = "<ID>";
    
    const string BROKER = "test.mosquitto.org";
    const string CLIENT_NAME = ID + "nightlight_client";
    ```

    將 `<ID>` 替換為用作此設備客戶端名稱的唯一 ID，稍後用於此設備發布和訂閱的主題。*test.mosquitto.org* broker 是公共的，許多人都在使用，包括其他完成此作業的學生。擁有唯一的 MQTT 客戶端名稱和主題名稱可以確保你的程式碼不會與其他人的程式碼衝突。稍後在此作業中建立伺服器程式碼時，你也需要此 ID。

    > 💁 你可以使用像 [GUIDGen](https://www.guidgen.com) 這樣的網站生成唯一 ID。

    `BROKER` 是 MQTT broker 的 URL。

    `CLIENT_NAME` 是此 MQTT 客戶端在 broker 上的唯一名稱。

1. 打開 `main.cpp` 文件，並在 `connectWiFi` 函數下方、`setup` 函數上方添加以下程式碼：

    ```cpp
    WiFiClient wioClient;
    PubSubClient client(wioClient);
    ```

    此程式碼使用 Wio Terminal WiFi 函式庫建立 WiFi 客戶端，並使用它建立 MQTT 客戶端。

1. 在此程式碼下方添加以下內容：

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

    此函數測試與 MQTT broker 的連接，並在未連接時重新連接。它會在未連接時進行迴圈，並嘗試使用配置標頭文件中定義的唯一客戶端名稱進行連接。

    如果連接失敗，5 秒後重試。

1. 在 `reconnectMQTTClient` 函數下方添加以下程式碼：

    ```cpp
    void createMQTTClient()
    {
        client.setServer(BROKER.c_str(), 1883);
        reconnectMQTTClient();
    }
    ```

    此程式碼為客戶端設置 MQTT broker，並設置接收到訊息時的回調函數。然後嘗試連接到 broker。

1. 在 WiFi 連接後，在 `setup` 函數中調用 `createMQTTClient` 函數。

1. 用以下程式碼替換整個 `loop` 函數：

    ```cpp
    void loop()
    {
        reconnectMQTTClient();
        client.loop();
    
        delay(2000);
    }
    ```

    此程式碼首先重新連接到 MQTT broker。這些連接很容易中斷，因此定期檢查並在必要時重新連接是值得的。然後調用 MQTT 客戶端的 `loop` 方法，處理任何在訂閱主題上接收到的訊息。此應用程式是單執行緒的，因此訊息無法在背景執行緒上接收，因此需要在主執行緒上分配時間來處理任何等待的網路連接訊息。

    最後，2 秒的延遲確保光線水平不會發送得太頻繁，並減少設備的功耗。

1. 將程式碼上傳到你的 Wio Terminal，並使用序列監視器查看設備連接到 WiFi 和 MQTT。

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

> 💁 你可以在 [code-mqtt/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-mqtt/wio-terminal) 資料夾中找到此程式碼。

😀 你已成功將設備連接到 MQTT broker。

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。