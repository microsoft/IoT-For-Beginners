<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "66b81165e60f8f169bd52a401b6a0f8b",
  "translation_date": "2025-08-26T14:36:00+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/pi-relay.md",
  "language_code": "hk"
}
-->
# 控制繼電器 - Raspberry Pi

在本課程中，您將在 Raspberry Pi 上添加一個繼電器，除了土壤濕度感測器外，還可以根據土壤濕度水平來控制它。

## 硬件

Raspberry Pi 需要一個繼電器。

您將使用的繼電器是 [Grove 繼電器](https://www.seeedstudio.com/Grove-Relay.html)，這是一個常開型繼電器（意味著當沒有信號傳送到繼電器時，輸出電路是開路或斷開的），它可以處理最高 250V 和 10A 的輸出電路。

這是一個數字執行器，因此需要連接到 Grove Base Hat 的數字插腳。

### 連接繼電器

Grove 繼電器可以連接到 Raspberry Pi。

#### 任務

連接繼電器。

![Grove 繼電器](../../../../../translated_images/hk/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.png)

1. 將 Grove 電纜的一端插入繼電器上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關機的情況下，將 Grove 電纜的另一端連接到 Pi 上 Grove Base Hat 的數字插座 **D5**。此插座位於 GPIO 插腳旁邊插座行的第二個位置。保持土壤濕度感測器連接到 **A0** 插座。

![Grove 繼電器連接到 D5 插座，土壤濕度感測器連接到 A0 插座](../../../../../translated_images/hk/pi-relay-and-soil-moisture-sensor.02f3198975b8c53e69ec716cd2719ce117700bd1fc933eaf93476c103c57939b.png)

1. 如果土壤濕度感測器尚未插入土壤，請將其插入土壤中（從上一課程中）。

## 編程繼電器

現在可以編程 Raspberry Pi 以使用連接的繼電器。

### 任務

編程設備。

1. 啟動 Raspberry Pi，並等待其啟動。

1. 在 VS Code 中打開上一課程的 `soil-moisture-sensor` 專案（如果尚未打開）。您將在此專案中進行添加。

1. 在現有的導入語句下，將以下代碼添加到 `app.py` 文件中：

    ```python
    from grove.grove_relay import GroveRelay
    ```

    此語句從 Grove Python 庫中導入 `GroveRelay`，以與 Grove 繼電器進行互動。

1. 在 `ADC` 類的聲明下方添加以下代碼，以創建一個 `GroveRelay` 實例：

    ```python
    relay = GroveRelay(5)
    ```

    這會使用插腳 **D5** 創建一個繼電器，該插腳是您連接繼電器的數字插腳。

1. 為了測試繼電器是否正常工作，將以下代碼添加到 `while True:` 循環中：

    ```python
    relay.on()
    time.sleep(.5)
    relay.off()
    ```

    此代碼會打開繼電器，等待 0.5 秒，然後關閉繼電器。

1. 運行 Python 應用程式。繼電器將每 10 秒打開和關閉一次，打開和關閉之間有半秒的延遲。您會聽到繼電器點擊聲，然後熄滅。當繼電器打開時，Grove 板上的 LED 會亮起，關閉時則熄滅。

    ![繼電器打開和關閉](../../../../../images/relay-turn-on-off.gif)

## 根據土壤濕度控制繼電器

現在繼電器已正常工作，可以根據土壤濕度讀數進行控制。

### 任務

控制繼電器。

1. 刪除您添加的用於測試繼電器的 3 行代碼。用以下代碼替換它們：

    ```python
    if soil_moisture > 450:
        print("Soil Moisture is too low, turning relay on.")
        relay.on()
    else:
        print("Soil Moisture is ok, turning relay off.")
        relay.off()
    ```

    此代碼會檢查土壤濕度感測器的土壤濕度水平。如果濕度高於 450，則打開繼電器；如果低於 450，則關閉繼電器。

    > 💁 請記住，電容式土壤濕度感測器的讀數越低，土壤中的濕度越高，反之亦然。

1. 運行 Python 應用程式。您會看到繼電器根據土壤濕度水平打開或關閉。嘗試在乾燥的土壤中測試，然後添加水。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 您可以在 [code-relay/pi](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/pi) 文件夾中找到此代碼。

😀 恭喜！您的土壤濕度感測器成功控制了繼電器！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業的人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。