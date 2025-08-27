<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4bcc29fe2b65e56eada83d2476279227",
  "translation_date": "2025-08-26T23:17:54+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md",
  "language_code": "mo"
}
-->
# 通過互聯網控制夜燈 - Wio Terminal

在本課程的這部分，你將把來自 Wio Terminal 的光線強度數據作為遙測數據發送到 MQTT broker。

## 安裝 JSON Arduino 函式庫

使用 JSON 是通過 MQTT 發送消息的一種常見方式。有一個 Arduino 的 JSON 函式庫，可以讓讀取和寫入 JSON 文件變得更加簡單。

### 任務

安裝 Arduino JSON 函式庫。

1. 在 VS Code 中打開夜燈專案。

1. 在 `platformio.ini` 文件的 `lib_deps` 列表中新增以下一行：

    ```ini
    bblanchon/ArduinoJson @ 6.17.3
    ```

    這將匯入 [ArduinoJson](https://arduinojson.org)，一個 Arduino 的 JSON 函式庫。

## 發佈遙測數據

下一步是創建一個包含遙測數據的 JSON 文件，並將其發送到 MQTT broker。

### 任務 - 發佈遙測數據

將遙測數據發佈到 MQTT broker。

1. 在 `config.h` 文件的底部新增以下程式碼，定義 MQTT broker 的遙測主題名稱：

    ```cpp
    const string CLIENT_TELEMETRY_TOPIC = ID + "/telemetry";
    ```

    `CLIENT_TELEMETRY_TOPIC` 是設備將用來發佈光線強度數據的主題。

1. 打開 `main.cpp` 文件。

1. 在文件頂部新增以下 `#include` 指令：

    ```cpp
    #include <ArduinoJSON.h>
    ```

1. 在 `loop` 函數內，`delay` 之前新增以下程式碼：

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

    這段程式碼會讀取光線強度，並使用 ArduinoJson 創建一個包含該數據的 JSON 文件。接著，將其序列化為字串，並通過 MQTT 客戶端發佈到遙測 MQTT 主題。

1. 將程式碼上傳到你的 Wio Terminal，並使用序列監視器查看發送到 MQTT broker 的光線強度數據。

    ```output
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"light":652}
    Sending telemetry {"light":612}
    Sending telemetry {"light":583}
    ```

> 💁 你可以在 [code-telemetry/wio-terminal](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/wio-terminal) 資料夾中找到這段程式碼。

😀 恭喜！你已成功從設備發送遙測數據。

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。