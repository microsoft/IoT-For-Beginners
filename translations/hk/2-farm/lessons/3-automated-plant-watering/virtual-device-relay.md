<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f8f541ee945545017a51aaf309aa37c3",
  "translation_date": "2025-08-26T14:36:32+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/virtual-device-relay.md",
  "language_code": "hk"
}
-->
# 控制繼電器 - 虛擬物聯網硬件

在這部分課程中，你將在虛擬物聯網設備中添加一個繼電器，除了土壤濕度傳感器外，還可以根據土壤濕度水平來控制它。

## 虛擬硬件

虛擬物聯網設備將使用模擬的 Grove 繼電器。這樣的設置與使用 Raspberry Pi 和實體 Grove 繼電器的操作方式相同。

在實體物聯網設備中，繼電器通常是常開型繼電器（即當沒有信號發送到繼電器時，輸出電路是斷開的）。這類繼電器可以處理高達 250V 和 10A 的輸出電路。

### 將繼電器添加到 CounterFit

要使用虛擬繼電器，你需要將它添加到 CounterFit 應用中。

#### 任務

將繼電器添加到 CounterFit 應用中。

1. 如果尚未打開，請在 VS Code 中打開上一課的 `soil-moisture-sensor` 項目。你將在此基礎上進行添加。

1. 確保 CounterFit 網頁應用正在運行。

1. 創建一個繼電器：

    1. 在 *Actuators* 面板的 *Create actuator* 框中，展開 *Actuator type* 下拉框，選擇 *Relay*。

    1. 將 *Pin* 設置為 *5*。

    1. 點擊 **Add** 按鈕，在 Pin 5 上創建繼電器。

    ![繼電器設置](../../../../../translated_images/hk/counterfit-create-relay.fa7c40fd0f2f6afc33b35ea94fcb235085be4861e14e3fe6b9b7bcfc82d1c888.png)

    繼電器將被創建並顯示在 Actuators 列表中。

    ![已創建的繼電器](../../../../../translated_images/hk/counterfit-relay.bbf74c1dbdc8b9acd983367fcbd06703a402aefef6af54ddb28e11307ba8a12c.png)

## 編程繼電器

現在可以編程土壤濕度傳感器應用以使用虛擬繼電器。

### 任務

編程虛擬設備。

1. 如果尚未打開，請在 VS Code 中打開上一課的 `soil-moisture-sensor` 項目。你將在此基礎上進行添加。

1. 在 `app.py` 文件的現有導入語句下方添加以下代碼：

    ```python
    from counterfit_shims_grove.grove_relay import GroveRelay
    ```

    這段語句從 Grove Python shim 庫中導入 `GroveRelay`，以便與虛擬 Grove 繼電器交互。

1. 在 `ADC` 類的聲明下方添加以下代碼，創建一個 `GroveRelay` 實例：

    ```python
    relay = GroveRelay(5)
    ```

    這段代碼使用 Pin **5** 創建了一個繼電器，這是你之前連接繼電器的引腳。

1. 為了測試繼電器是否正常工作，在 `while True:` 循環中添加以下代碼：

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    這段代碼會打開繼電器，等待 0.5 秒，然後關閉繼電器。

1. 運行 Python 應用。繼電器將每 10 秒打開和關閉一次，打開和關閉之間有 0.5 秒的延遲。你將看到 CounterFit 應用中的虛擬繼電器隨著打開和關閉而閉合和斷開。

    ![虛擬繼電器打開和關閉](../../../../../images/virtual-relay-turn-on-off.gif)

## 根據土壤濕度控制繼電器

現在繼電器已經可以正常工作，接下來可以根據土壤濕度讀數來控制它。

### 任務

控制繼電器。

1. 刪除你添加的測試繼電器的 3 行代碼，並用以下代碼替換：

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    這段代碼會檢查來自土壤濕度傳感器的濕度水平。如果濕度值高於 450，則打開繼電器；如果低於 450，則關閉繼電器。

    > 💁 請記住，電容式土壤濕度傳感器的讀數越低，表示土壤中的濕度越高，反之亦然。

1. 運行 Python 應用。你將看到繼電器根據土壤濕度水平打開或關閉。更改土壤濕度傳感器的 *Value* 或 *Random* 設置以查看值的變化。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 你可以在 [code-relay/virtual-device](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/virtual-device) 文件夾中找到這段代碼。

😀 你的虛擬土壤濕度傳感器控制繼電器程序成功完成！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。