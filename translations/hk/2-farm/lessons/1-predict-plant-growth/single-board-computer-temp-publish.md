<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4efc74299e19f5d08f2f3f34451a11ba",
  "translation_date": "2025-08-26T14:28:51+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/single-board-computer-temp-publish.md",
  "language_code": "hk"
}
-->
# 發佈溫度數據 - 虛擬物聯網硬件與樹莓派

在本課程的這部分，你將通過 MQTT 發佈由樹莓派或虛擬物聯網設備檢測到的溫度值，以便稍後用於計算 GDD。

## 發佈溫度數據

一旦讀取到溫度數據，就可以通過 MQTT 發佈到某些「伺服器」代碼，該代碼將讀取這些數據並存儲起來，準備用於 GDD 計算。

### 任務 - 發佈溫度數據

編程設備以發佈溫度數據。

1. 如果尚未打開 `temperature-sensor` 應用項目，請將其打開。

1. 重複你在第 4 課中完成的步驟，連接到 MQTT 並發送遙測數據。你將使用相同的公共 Mosquitto broker。

    具體步驟如下：

    - 添加 MQTT 的 pip 套件
    - 添加連接到 MQTT broker 的代碼
    - 添加發佈遙測數據的代碼

    > ⚠️ 如有需要，請參考[連接到 MQTT 的指引](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-mqtt.md)和[發送遙測數據的指引](../../../1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md)（第 4 課）。

1. 確保 `client_name` 反映此項目的名稱：

    ```python
    client_name = id + 'temperature_sensor_client'
    ```

1. 對於遙測數據，與其發送光線值，不如發送從 DHT 傳感器讀取的溫度值，並將其作為 JSON 文檔中的一個屬性，名為 `temperature`：

    ```python
    _, temp = sensor.read()
    telemetry = json.dumps({'temperature' : temp})
    ```

1. 溫度值不需要頻繁讀取——在短時間內它不會有太大變化，因此將 `time.sleep` 設置為 10 分鐘：

    ```cpp
    time.sleep(10 * 60);
    ```

    > 💁 `sleep` 函數以秒為單位，因此為了更易於閱讀，這裡的值是通過計算得出的。1 分鐘有 60 秒，因此 10 x（每分鐘 60 秒）得出 10 分鐘的延遲。

1. 以與完成上一部分作業相同的方式運行代碼。如果你使用的是虛擬物聯網設備，請確保 CounterFit 應用正在運行，並且已在正確的引腳上創建了濕度和溫度傳感器。

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py
    MQTT connected!
    Sending telemetry  {"temperature": 25}
    Sending telemetry  {"temperature": 25}
    ```

> 💁 你可以在 [code-publish-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/virtual-device) 文件夾或 [code-publish-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-publish-temperature/pi) 文件夾中找到此代碼。

😀 你已成功將設備的溫度數據作為遙測數據發佈出去。

---

**免責聲明**：  
此文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議使用專業的人工作翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解讀概不負責。