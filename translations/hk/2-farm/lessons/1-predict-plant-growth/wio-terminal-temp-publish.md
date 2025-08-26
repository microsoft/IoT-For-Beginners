<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "df28cd649cd892bcce034e064913b2f3",
  "translation_date": "2025-08-26T14:30:14+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/wio-terminal-temp-publish.md",
  "language_code": "hk"
}
-->
# 發佈溫度 - Wio Terminal

在這部分課程中，你將透過 MQTT 發佈由 Wio Terminal 偵測到的溫度值，以便稍後用於計算 GDD。

## 發佈溫度

當溫度被讀取後，可以透過 MQTT 發佈到某些「伺服器」代碼，該代碼將讀取這些值並存儲起來，準備用於 GDD 計算。微控制器無法直接從互聯網讀取時間，也無法自帶實時時鐘來追蹤時間，設備需要被編程以執行此操作，前提是它具備必要的硬件。

為了簡化本課程，時間不會與感測器數據一起發送，而是可以在伺服器代碼接收到消息後再添加。

### 任務

編程設備以發佈溫度數據。

1. 打開 `temperature-sensor` Wio Terminal 專案

1. 重複你在第 4 課中所做的步驟，連接到 MQTT 並發送遙測數據，你將使用相同的公共 Mosquitto broker。

    這些步驟包括：

    - 在 `.ini` 文件中添加 Seeed WiFi 和 MQTT 庫
    - 添加配置文件和連接 WiFi 的代碼
    - 添加連接到 MQTT broker 的代碼
    - 添加發佈遙測數據的代碼

    > ⚠️ 如有需要，請參考 [連接到 MQTT 的指引](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-mqtt.md) 和 [發送遙測數據的指引](../../../1-getting-started/lessons/4-connect-internet/wio-terminal-telemetry.md)（第 4 課）。

1. 確保 `config.h` 標頭文件中的 `CLIENT_NAME` 反映此專案：

    ```cpp
    const string CLIENT_NAME = ID + "temperature_sensor_client";
    ```

1. 對於遙測數據，將讀取自 DHT 感測器的溫度值作為 JSON 文件中的 `temperature` 屬性發送，而不是發送光線值，通過修改 `main.cpp` 中的 `loop` 函數：

    ```cpp
    float temp_hum_val[2] = {0};
    dht.readTempAndHumidity(temp_hum_val);

    DynamicJsonDocument doc(1024);
    doc["temperature"] = temp_hum_val[1];
    ```

1. 溫度值不需要頻繁讀取——在短時間內它不會有太大變化，因此將 `loop` 函數中的 `delay` 設置為 10 分鐘：

    ```cpp
    delay(10 * 60 * 1000);
    ```

    > 💁 `delay` 函數以毫秒為單位，因此為了更容易閱讀，該值是通過計算得出的。1,000 毫秒等於 1 秒，60 秒等於 1 分鐘，因此 10 x (60 秒/分鐘) x (1000 毫秒/秒) 得出 10 分鐘的延遲。

1. 將此代碼上傳到你的 Wio Terminal，並使用串口監視器查看溫度是否已成功發送到 MQTT broker。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1201  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Attempting MQTT connection...connected
    Sending telemetry {"temperature":25}
    Sending telemetry {"temperature":25}
    ```

> 💁 你可以在 [code-publish-temperature/wio-terminal](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/wio-terminal) 文件夾中找到此代碼。

😀 恭喜你成功將溫度作為遙測數據從你的設備發佈出去！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為具權威性的來源。對於重要資訊，建議使用專業的人類翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。