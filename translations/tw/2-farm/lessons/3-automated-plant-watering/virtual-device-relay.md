<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-24T22:19:03+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "tw"
}
-->
# 控制繼電器 - 虛擬物聯網硬體

在本課程的這部分，您將在虛擬物聯網設備中新增一個繼電器，除了土壤濕度感測器之外，還可以根據土壤濕度水平來控制它。

## 虛擬硬體

虛擬物聯網設備將使用模擬的 Grove 繼電器。這使得本實驗與使用實體 Grove 繼電器的 Raspberry Pi 保持一致。

在實體物聯網設備中，繼電器通常是常開型繼電器（這意味著當沒有信號發送到繼電器時，輸出電路是開路或斷開的）。這類繼電器可以處理高達 250V 和 10A 的輸出電路。

### 將繼電器新增到 CounterFit

要使用虛擬繼電器，您需要將其新增到 CounterFit 應用程式中。

#### 任務

將繼電器新增到 CounterFit 應用程式中。

1. 如果尚未打開，請在 VS Code 中打開上一課的 `soil-moisture-sensor` 專案。您將在此專案中進行新增。

1. 確保 CounterFit 網頁應用程式正在運行。

1. 創建一個繼電器：

    1. 在 *Actuators* 面板的 *Create actuator* 框中，展開 *Actuator type* 下拉框並選擇 *Relay*。

    1. 將 *Pin* 設置為 *5*。

    1. 選擇 **Add** 按鈕，在 Pin 5 上創建繼電器。

    ![繼電器設置](../../../../../translated_images/tw/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    繼電器將被創建並顯示在 Actuators 列表中。

    ![已創建的繼電器](../../../../../translated_images/tw/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## 編程繼電器

現在可以編程土壤濕度感測器應用程式以使用虛擬繼電器。

### 任務

編程虛擬設備。

1. 如果尚未打開，請在 VS Code 中打開上一課的 `soil-moisture-sensor` 專案。您將在此專案中進行新增。

1. 在 `app.py` 文件的現有匯入語句下方新增以下程式碼：

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    此語句從 Grove Python shim 庫中匯入 `GroveRelay`，以與虛擬 Grove 繼電器互動。

1. 在 `ADC` 類的聲明下方新增以下程式碼，以創建一個 `GroveRelay` 實例：

    ```python
    relay = GroveRelay(5)
    ```

    這會使用 Pin **5** 創建一個繼電器，該 Pin 是您連接繼電器的位置。

1. 為了測試繼電器是否正常工作，請在 `while True:` 迴圈中新增以下程式碼：

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    此程式碼會打開繼電器，等待 0.5 秒，然後關閉繼電器。

1. 運行 Python 應用程式。繼電器將每 10 秒打開和關閉一次，打開和關閉之間有 0.5 秒的延遲。您將看到 CounterFit 應用程式中的虛擬繼電器隨著繼電器的打開和關閉而閉合和斷開。

    ![虛擬繼電器打開和關閉](../../../../../images/virtual-relay-turn-on-off.gif)

## 根據土壤濕度控制繼電器

現在繼電器已正常工作，可以根據土壤濕度讀數進行控制。

### 任務

控制繼電器。

1. 刪除您新增的用於測試繼電器的 3 行程式碼。用以下程式碼替換它們：

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    此程式碼檢查來自土壤濕度感測器的土壤濕度水平。如果濕度值高於 450，則打開繼電器；如果低於 450，則關閉繼電器。

    > 💁 請記住，電容式土壤濕度感測器的讀數越低，土壤中的濕度越高，反之亦然。

1. 運行 Python 應用程式。您將看到繼電器根據土壤濕度水平打開或關閉。更改土壤濕度感測器的 *Value* 或 *Random* 設置以查看值的變化。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 您可以在 [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) 資料夾中找到此程式碼。

😀 您的虛擬土壤濕度感測器控制繼電器程式成功完成！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。