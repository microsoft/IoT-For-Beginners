<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f3c5d8afa2ef6a0b425ef8ff20615cb4",
  "translation_date": "2025-08-24T22:16:23+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/wio-terminal-relay.md",
  "language_code": "tw"
}
-->
# 控制繼電器 - Wio Terminal

在本課程中，除了土壤濕度傳感器外，您還將為 Wio Terminal 添加一個繼電器，並根據土壤濕度水平來控制它。

## 硬體

Wio Terminal 需要一個繼電器。

您將使用的是 [Grove 繼電器](https://www.seeedstudio.com/Grove-Relay.html)，這是一個常開型繼電器（意味著當沒有信號發送到繼電器時，輸出電路是開路或斷開的），它可以處理最高 250V 和 10A 的輸出電路。

這是一個數字執行器，因此需要連接到 Wio Terminal 的數字引腳。模擬/數字組合端口已經被土壤濕度傳感器使用，因此繼電器需要插入另一個端口，該端口是一個組合 I²C 和數字端口。

### 連接繼電器

Grove 繼電器可以連接到 Wio Terminal 的數字端口。

#### 任務

連接繼電器。

![Grove 繼電器](../../../../../translated_images/grove-relay.d426958ca210fbd0fb7983d7edc069d46c73a8b0a099d94797bd756f7b6bb6be.tw.png)

1. 將 Grove 電纜的一端插入繼電器上的插座。它只能以一種方式插入。

1. 在 Wio Terminal 與電腦或其他電源斷開連接的情況下，將 Grove 電纜的另一端連接到 Wio Terminal 屏幕左側的 Grove 插座。保持土壤濕度傳感器連接到右側插座。

![Grove 繼電器連接到左側插座，土壤濕度傳感器連接到右側插座](../../../../../translated_images/wio-relay-and-soil-moisture-sensor.ed722202d42babe0.tw.png)

1. 如果土壤濕度傳感器尚未插入土壤，請將其插入。

## 編程繼電器

現在可以編程 Wio Terminal 以使用連接的繼電器。

### 任務

編程設備。

1. 在 VS Code 中打開上一課的 `soil-moisture-sensor` 專案（如果尚未打開）。您將在此專案中進行添加。

2. 這個執行器沒有專用的庫——它是一個通過高或低信號控制的數字執行器。要打開它，您需要向引腳發送高信號（3.3V）；要關閉它，則發送低信號（0V）。您可以使用內建的 Arduino [`digitalWrite`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/) 函數來完成。首先，在 `setup` 函數的底部添加以下代碼，以將組合 I²C/數字端口設置為輸出引腳，用於向繼電器發送電壓：

    ```cpp
    pinMode(PIN_WIRE_SCL, OUTPUT);
    ```

    `PIN_WIRE_SCL` 是組合 I²C/數字端口的端口號。

1. 為了測試繼電器是否正常工作，將以下代碼添加到 `loop` 函數中，放在最後的 `delay` 之下：

    ```cpp
    digitalWrite(PIN_WIRE_SCL, HIGH);
    delay(500);
    digitalWrite(PIN_WIRE_SCL, LOW);
    ```

    此代碼向連接繼電器的引腳寫入高信號以打開繼電器，等待 500 毫秒（半秒），然後寫入低信號以關閉繼電器。

1. 編譯並上傳代碼到 Wio Terminal。

1. 上傳完成後，繼電器將每 10 秒打開和關閉一次，並在打開和關閉之間有半秒的延遲。您會聽到繼電器點擊聲，LED 在繼電器打開時亮起，關閉時熄滅。

    ![繼電器打開和關閉](../../../../../images/relay-turn-on-off.gif)

## 根據土壤濕度控制繼電器

現在繼電器已正常工作，可以根據土壤濕度讀數進行控制。

### 任務

控制繼電器。

1. 刪除您添加的用於測試繼電器的 3 行代碼。用以下代碼替換它們：

    ```cpp
    if (soil_moisture > 450)
    {
        Serial.println("Soil Moisture is too low, turning relay on.");
        digitalWrite(PIN_WIRE_SCL, HIGH);
    }
    else
    {
        Serial.println("Soil Moisture is ok, turning relay off.");
        digitalWrite(PIN_WIRE_SCL, LOW);
    }
    ```

    此代碼檢查土壤濕度傳感器的濕度水平。如果濕度值高於 450，則打開繼電器；如果低於 450，則關閉繼電器。

    > 💁 請記住，電容式土壤濕度傳感器的讀數越低，土壤中的水分越多，反之亦然。

1. 編譯並上傳代碼到 Wio Terminal。

1. 通過串列監視器監控設備。您將看到繼電器根據土壤濕度水平打開或關閉。嘗試在乾燥的土壤中測試，然後添加水。

    ```output
    Soil Moisture: 638
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 452
    Soil Moisture is too low, turning relay on.
    Soil Moisture: 347
    Soil Moisture is ok, turning relay off.
    ```

> 💁 您可以在 [code-relay/wio-terminal](../../../../../2-farm/lessons/3-automated-plant-watering/code-relay/wio-terminal) 文件夾中找到此代碼。

😀 恭喜！您的土壤濕度傳感器成功控制了繼電器！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。