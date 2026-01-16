<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-26T22:09:14+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "mo"
}
-->
# 檢測接近 - Raspberry Pi

在本課程中，您將為 Raspberry Pi 添加一個接近感測器，並從中讀取距離。

## 硬體

Raspberry Pi 需要一個接近感測器。

您將使用的感測器是 [Grove 飛行時間距離感測器](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)。此感測器使用雷射測距模組來檢測距離。此感測器的範圍為 10mm 至 2000mm（1cm - 2m），並能相當準確地報告該範圍內的值，超過 1000mm 的距離將報告為 8109mm。

雷射測距儀位於感測器的背面，也就是 Grove 插座的相反側。

這是一個 I²C 感測器。

### 連接飛行時間感測器

Grove 飛行時間感測器可以連接到 Raspberry Pi。

#### 任務 - 連接飛行時間感測器

連接飛行時間感測器。

![Grove 飛行時間感測器](../../../../../translated_images/mo/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. 將 Grove 電纜的一端插入飛行時間感測器上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關閉電源的情況下，將 Grove 電纜的另一端連接到 Grove Base hat 上標有 **I²C** 的插座之一。這些插座位於底部排，靠近相機電纜插槽，與 GPIO 引腳的相反端。

![Grove 飛行時間感測器連接到 I²C 插座](../../../../../translated_images/mo/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## 程式設計飛行時間感測器

現在可以為 Raspberry Pi 編程以使用已連接的飛行時間感測器。

### 任務 - 程式設計飛行時間感測器

編程設備。

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 在 VS Code 中打開 `fruit-quality-detector` 程式碼，可以直接在 Raspberry Pi 上操作，也可以通過 Remote SSH 擴展連接。

1. 安裝 rpi-vl53l0x Pip 套件，這是一個與 VL53L0X 飛行時間距離感測器互動的 Python 套件。使用以下 pip 命令安裝：

    ```sh
    pip install rpi-vl53l0x
    ```

1. 在此專案中建立一個名為 `distance-sensor.py` 的新檔案。

    > 💁 模擬多個 IoT 設備的一個簡單方法是將每個設備放在不同的 Python 檔案中，然後同時運行它們。

1. 將以下程式碼添加到此檔案中：

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    此程式碼導入 Grove I²C 總線庫，以及 Grove 飛行時間感測器內建核心硬體的感測器庫。

1. 在此程式碼下方，添加以下程式碼以訪問感測器：

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    此程式碼使用 Grove I²C 總線宣告一個距離感測器，然後啟動感測器。

1. 最後，添加一個無限迴圈以讀取距離：

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    此程式碼等待感測器準備好讀取值，然後將其打印到控制台。

1. 運行此程式碼。

    > 💁 別忘了此檔案名為 `distance-sensor.py`！請確保通過 Python 運行它，而不是 `app.py`。

1. 您將在控制台中看到距離測量值。將物體放置在感測器附近，您將看到距離測量值：

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    測距儀位於感測器的背面，因此在測量距離時請確保使用正確的一側。

    ![飛行時間感測器背面的測距儀指向一根香蕉](../../../../../translated_images/mo/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 您可以在 [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) 資料夾中找到此程式碼。

😀 您的接近感測器程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。