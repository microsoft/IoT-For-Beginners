<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-26T15:00:03+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "hk"
}
-->
# 通過互聯網控制你的夜燈 - Wio Terminal

在這部分課程中，你將把 Wio Terminal 的光線水平數據作為遙測信息發送到 MQTT broker。

## 安裝 JSON Arduino 庫

使用 JSON 是通過 MQTT 發送消息的一種流行方式。有一個 Arduino 的 JSON 庫，可以讓讀取和寫入 JSON 文檔變得更簡單。

### 任務

安裝 Arduino JSON 庫。

1. 在 VS Code 中打開夜燈項目。

1. 在 `platformio.ini` 文件的 `lib_deps` 列表中添加以下額外的一行：

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    這將導入 [ArduinoJson](https://arduinojson.org)，一個 Arduino 的 JSON 庫。

## 發佈遙測信息

下一步是創建一個包含遙測信息的 JSON 文檔，並將其發送到 MQTT broker。

### 任務 - 發佈遙測信息

將遙測信息發佈到 MQTT broker。

1. 在 `config.h` 文件底部添加以下代碼，以定義 MQTT broker 的遙測主題名稱：

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` 是設備將用來發佈光線水平的主題。

1. 打開 `main.cpp` 文件

1. 在文件頂部添加以下 `#include` 指令：

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. 在 `loop` 函數內，`delay` 之前添加以下代碼：

    ```cpp
    int light = analogRead(WIO_LIGHT);

    DynamicJsonDocument doc(1024);
    doc["light"] = light;

    string telemetry;
    serializeJson(doc, telemetry);

    Serial.print("Sending telemetry ");
    Serial.println(telemetry.c_str());

    client.publish(CLIENT_TELEMETRY_TOPIC.c_str(), telemetry.c_str());
    ```

    此代碼會讀取光線水平，並使用 ArduinoJson 創建一個包含該水平的 JSON 文檔。然後將其序列化為字符串，並通過 MQTT 客戶端發佈到遙測 MQTT 主題。

1. 將代碼上傳到你的 Wio Terminal，並使用串口監視器查看光線水平被發送到 MQTT broker 的情況。

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 你可以在 [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) 文件夾中找到這段代碼。

😀 你已成功從設備發送遙測信息。

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。