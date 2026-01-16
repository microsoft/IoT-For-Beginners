<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-26T14:12:58+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "hk"
}
-->
# 捕捉影像 - 虛擬物聯網硬件

在本課程中，你將為虛擬物聯網設備添加一個相機感應器，並從中讀取影像。

## 硬件

虛擬物聯網設備將使用模擬相機，該相機可以傳送文件中的影像或來自你的網絡攝像頭的影像。

### 在 CounterFit 中添加相機

要使用虛擬相機，你需要在 CounterFit 應用中添加一個相機。

#### 任務 - 在 CounterFit 中添加相機

在 CounterFit 應用中添加相機。

1. 在你的電腦上創建一個名為 `fruit-quality-detector` 的文件夾，並在其中創建一個名為 `app.py` 的單一文件和一個 Python 虛擬環境，然後添加 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，你可以參考[課程 1 中創建和設置 CounterFit Python 項目的指導](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安裝額外的 Pip 套件，以安裝一個 CounterFit shim，它可以通過模擬部分 [Picamera Pip 套件](https://pypi.org/project/picamera/) 與相機感應器通信。確保你是在啟動了虛擬環境的終端中進行安裝。

    ```sh
    pip install counterfit-shims-picamera
    ```

1. 確保 CounterFit 網頁應用正在運行。

1. 創建一個相機：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，打開 *Sensor type* 下拉框並選擇 *Camera*。

    1. 將 *Name* 設置為 `Picamera`。

    1. 選擇 **Add** 按鈕以創建相機。

    ![相機設置](../../../../../translated_images/hk/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    相機將被創建並顯示在感應器列表中。

    ![創建的相機](../../../../../translated_images/hk/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## 編程相機

現在可以為虛擬物聯網設備編程以使用虛擬相機。

### 任務 - 編程相機

為設備編程。

1. 確保 `fruit-quality-detector` 應用已在 VS Code 中打開。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部添加以下代碼，以連接應用到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在你的 `app.py` 文件中添加以下代碼：

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    此代碼導入了一些需要的庫，包括來自 counterfit_shims_picamera 庫的 `PiCamera` 類。

1. 在此代碼下方添加以下代碼以初始化相機：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    此代碼創建了一個 PiCamera 對象，並將分辨率設置為 640x480。雖然支持更高的分辨率，但影像分類器僅處理更小的影像（227x227），因此無需捕捉和傳送更大的影像。

    `camera.rotation = 0` 行設置影像的旋轉角度（以度為單位）。如果需要旋轉來自網絡攝像頭或文件的影像，請根據需要設置。例如，如果你想將網絡攝像頭中橫向模式的香蕉影像更改為縱向模式，請設置 `camera.rotation = 90`。

1. 在此代碼下方添加以下代碼以捕捉影像為二進制數據：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    此代碼創建了一個 `BytesIO` 對象來存儲二進制數據。影像以 JPEG 文件的形式從相機中讀取並存儲在此對象中。此對象有一個位置指示器，用於指示當前數據的位置，以便後續可以在末尾寫入更多數據，因此 `image.seek(0)` 行將位置移回起始位置，以便稍後可以讀取所有數據。

1. 在此代碼下方添加以下代碼以將影像保存到文件：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    此代碼打開一個名為 `image.jpg` 的文件進行寫入，然後從 `BytesIO` 對象中讀取所有數據並寫入該文件。

    > 💁 你可以直接將影像捕捉到文件，而不是使用 `BytesIO` 對象，只需將文件名傳遞給 `camera.capture` 調用即可。使用 `BytesIO` 對象的原因是稍後在本課程中，你可以將影像發送到你的影像分類器。

1. 配置 CounterFit 中相機將捕捉的影像。你可以將 *Source* 設置為 *File*，然後上傳一個影像文件，或者將 *Source* 設置為 *WebCam*，影像將從你的網絡攝像頭捕捉。確保在選擇圖片或網絡攝像頭後選擇 **Set** 按鈕。

    ![CounterFit 中設置文件為影像來源，以及網絡攝像頭顯示一個人拿著香蕉的預覽](../../../../../translated_images/hk/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. 一個影像將被捕捉並保存為 `image.jpg`，位於當前文件夾中。你將在 VS Code 的資源管理器中看到此文件。選擇該文件以查看影像。如果需要旋轉，根據需要更新 `camera.rotation = 0` 行並重新拍攝影像。

> 💁 你可以在 [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) 文件夾中找到此代碼。

😀 你的相機程序成功了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業的人類翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。