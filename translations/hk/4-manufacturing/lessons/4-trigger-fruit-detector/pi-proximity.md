<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6145a1d791731c8a9d0afd0a1bae5108",
  "translation_date": "2025-08-26T14:23:32+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/pi-proximity.md",
  "language_code": "hk"
}
-->
# 檢測接近距離 - Raspberry Pi

在本課程中，您將為 Raspberry Pi 添加一個接近感應器，並從中讀取距離。

## 硬件

Raspberry Pi 需要一個接近感應器。

您將使用的感應器是 [Grove 飛行時間距離感應器](https://www.seeedstudio.com/Grove-Time-of-Flight-Distance-Sensor-VL53L0X.html)。此感應器使用激光測距模組來檢測距離。該感應器的範圍為 10mm 至 2000mm（1cm - 2m），並能相當準確地報告該範圍內的值，超過 1000mm 的距離將報告為 8109mm。

激光測距儀位於感應器的背面，即 Grove 插座的對面。

這是一個 I²C 感應器。

### 連接飛行時間感應器

Grove 飛行時間感應器可以連接到 Raspberry Pi。

#### 任務 - 連接飛行時間感應器

連接飛行時間感應器。

![Grove 飛行時間感應器](../../../../../translated_images/hk/grove-time-of-flight-sensor.d82ff2165bfded9f485de54d8d07195a6270a602696825fca19f629ddfe94e86.png)

1. 將 Grove 電纜的一端插入飛行時間感應器上的插座。它只能以一種方式插入。

1. 在 Raspberry Pi 關閉電源的情況下，將 Grove 電纜的另一端連接到 Grove Base Hat 上標記為 **I²C** 的插座之一。這些插座位於底部排，靠近攝像頭電纜插槽，與 GPIO 引腳的另一端相對。

![Grove 飛行時間感應器連接到 I²C 插座](../../../../../translated_images/hk/pi-time-of-flight-sensor.58c8dc04eb3bfb57.webp)

## 編程飛行時間感應器

現在可以編程 Raspberry Pi 以使用連接的飛行時間感應器。

### 任務 - 編程飛行時間感應器

編程設備。

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 在 VS Code 中打開 `fruit-quality-detector` 代碼，可以直接在 Raspberry Pi 上操作，也可以通過 Remote SSH 擴展連接。

1. 安裝 rpi-vl53l0x Pip 套件，這是一個與 VL53L0X 飛行時間距離感應器交互的 Python 套件。使用以下 pip 命令安裝：

    ```sh
    pip install rpi-vl53l0x
    ```

1. 在此項目中創建一個名為 `distance-sensor.py` 的新文件。

    > 💁 模擬多個 IoT 設備的一個簡單方法是將每個設備放在不同的 Python 文件中，然後同時運行它們。

1. 在此文件中添加以下代碼：

    ```python
    import time
    
    from grove.i2c import Bus
    from rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    這段代碼導入了 Grove I²C 總線庫，以及 Grove 飛行時間感應器內置核心硬件的感應器庫。

1. 在此代碼下方，添加以下代碼以訪問感應器：

    ```python
    distance_sensor = VL53L0X(bus = Bus().bus)
    distance_sensor.begin()    
    ```

    此代碼使用 Grove I²C 總線聲明了一個距離感應器，然後啟動感應器。

1. 最後，添加一個無限循環以讀取距離：

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    此代碼等待感應器準備好讀取值，然後將其打印到控制台。

1. 運行此代碼。

    > 💁 請記住此文件名為 `distance-sensor.py`！確保通過 Python 運行它，而不是 `app.py`。

1. 您將在控制台中看到距離測量值。將物體放置在感應器附近，您將看到距離測量值：

    ```output
    pi@raspberrypi:~/fruit-quality-detector $ python3 distance_sensor.py 
    Distance = 29 mm
    Distance = 28 mm
    Distance = 30 mm
    Distance = 151 mm
    ```

    測距儀位於感應器的背面，因此在測量距離時請確保使用正確的一側。

    ![飛行時間感應器背面的測距儀指向一根香蕉](../../../../../translated_images/hk/time-of-flight-banana.079921ad8b1496e4.webp)

> 💁 您可以在 [code-proximity/pi](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/pi) 文件夾中找到此代碼。

😀 您的接近感應器程序運行成功！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。