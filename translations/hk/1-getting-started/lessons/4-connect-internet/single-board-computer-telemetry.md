<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-26T14:56:45+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "hk"
}
-->
# 通過互聯網控制你的夜燈 - 虛擬物聯網硬件和樹莓派

在本課程的這部分，你將從樹莓派或虛擬物聯網設備向 MQTT broker 發送光照水平的遙測數據。

## 發佈遙測數據

下一步是創建一個包含遙測數據的 JSON 文檔並將其發送到 MQTT broker。

### 任務

向 MQTT broker 發佈遙測數據。

1. 在 VS Code 中打開夜燈項目。

1. 如果你使用的是虛擬物聯網設備，請確保終端正在運行虛擬環境。如果你使用的是樹莓派，則不需要使用虛擬環境。

1. 在 `app.py` 文件的頂部添加以下導入：

    ```python
    import json
    ```

    `json` 庫用於將遙測數據編碼為 JSON 文檔。

1. 在 `client_name` 聲明之後添加以下內容：

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` 是設備將光照水平發佈到的 MQTT 主題。

1. 用以下內容替換文件末尾的 `while True:` 循環：

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    此代碼將光照水平打包成 JSON 文檔並發佈到 MQTT broker。然後它會休眠以減少消息發送的頻率。

1. 以與完成上一部分作業相同的方式運行代碼。如果你使用的是虛擬物聯網設備，請確保 CounterFit 應用正在運行，並且光傳感器和 LED 已在正確的引腳上創建。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 你可以在 [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) 文件夾或 [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) 文件夾中找到此代碼。

😀 你已成功從設備發送遙測數據。

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業的人類翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。