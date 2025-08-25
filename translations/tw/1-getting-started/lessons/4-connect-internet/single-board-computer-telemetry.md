<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1226517aae5f5b6f904434670394c688",
  "translation_date": "2025-08-24T23:00:52+00:00",
  "source_file": "1-getting-started/lessons/4-connect-internet/single-board-computer-telemetry.md",
  "language_code": "tw"
}
-->
# 通過網路控制夜燈 - 虛擬物聯網硬體與樹莓派

在本課程的這部分，你將從樹莓派或虛擬物聯網設備向 MQTT broker 發送光線強度的遙測數據。

## 發佈遙測數據

下一步是建立一個包含遙測數據的 JSON 文件並將其發送到 MQTT broker。

### 任務

將遙測數據發佈到 MQTT broker。

1. 在 VS Code 中打開夜燈專案。

1. 如果你使用的是虛擬物聯網設備，請確保終端正在運行虛擬環境。如果你使用的是樹莓派，則不需要使用虛擬環境。

1. 在 `app.py` 文件的頂部添加以下導入：

    ```python
    import json
    ```

    `json` 庫用於將遙測數據編碼為 JSON 文件。

1. 在 `client_name` 宣告之後添加以下內容：

    ```python
    client_telemetry_topic = id + '/telemetry'
    ```

    `client_telemetry_topic` 是設備將光線強度發佈到的 MQTT 主題。

1. 用以下內容替換文件末尾的 `while True:` 迴圈：

    ```python
    while True:
        light = light_sensor.light
        telemetry = json.dumps({'light' : light})

        print("Sending telemetry ", telemetry)
    
        mqtt_client.publish(client_telemetry_topic, telemetry)
    
        time.sleep(5)
    ```

    此程式碼將光線強度打包成 JSON 文件並發佈到 MQTT broker。然後它會休眠以減少訊息發送的頻率。

1. 以與作業上一部分相同的方式運行程式碼。如果你使用的是虛擬物聯網設備，請確保 CounterFit 應用正在運行，並且光線感測器和 LED 已在正確的引腳上建立。

    ```output
    (.venv) ➜  nightlight python app.py 
    MQTT connected!
    Sending telemetry  {"light": 0}
    Sending telemetry  {"light": 0}
    ```

> 💁 你可以在 [code-telemetry/virtual-device](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/virtual-device) 資料夾或 [code-telemetry/pi](../../../../../1-getting-started/lessons/4-connect-internet/code-telemetry/pi) 資料夾中找到此程式碼。

😀 你已成功從設備發送遙測數據。

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。