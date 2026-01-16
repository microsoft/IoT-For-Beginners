<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-26T21:53:19+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "mo"
}
-->
# 捕捉影像 - 虛擬物聯網硬體

在本課程中，您將為虛擬物聯網設備添加一個相機感測器，並從中讀取影像。

## 硬體

虛擬物聯網設備將使用模擬相機，該相機可以傳送檔案中的影像或來自您的網路攝影機的影像。

### 在 CounterFit 中添加相機

要使用虛擬相機，您需要在 CounterFit 應用程式中添加一個。

#### 任務 - 在 CounterFit 中添加相機

在 CounterFit 應用程式中添加相機。

1. 在您的電腦上建立一個名為 `fruit-quality-detector` 的資料夾，並在其中建立一個名為 `app.py` 的 Python 應用程式，設置 Python 虛擬環境，並添加 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，您可以參考[第 1 課中建立和設置 CounterFit Python 專案的指導](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安裝額外的 Pip 套件，以安裝一個 CounterFit shim，該 shim 可以通過模擬部分 [Picamera Pip 套件](https://pypi.org/project/picamera/) 與相機感測器進行通信。請確保您是在啟動虛擬環境的終端中進行安裝。

    ```sh
    pip install counterfit-shims-picamera
    ```

1. 確保 CounterFit 網頁應用程式正在運行。

1. 創建相機：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *Camera*。

    1. 將 *Name* 設置為 `Picamera`。

    1. 選擇 **Add** 按鈕以創建相機。

    ![相機設置](../../../../../translated_images/mo/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    相機將被創建並顯示在感測器列表中。

    ![創建的相機](../../../../../translated_images/mo/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## 編程相機

現在可以編程虛擬物聯網設備以使用虛擬相機。

### 任務 - 編程相機

編程設備。

1. 確保 `fruit-quality-detector` 應用程式已在 VS Code 中打開。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部添加以下程式碼，以連接應用程式到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在您的 `app.py` 文件中添加以下程式碼：

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    此程式碼導入了一些需要的庫，包括來自 counterfit_shims_picamera 庫的 `PiCamera` 類。

1. 在此程式碼下方添加以下程式碼以初始化相機：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    此程式碼創建了一個 PiCamera 對象，並將解析度設置為 640x480。雖然支持更高的解析度，但影像分類器僅處理更小的影像（227x227），因此無需捕捉和傳送更大的影像。

    `camera.rotation = 0` 行設置影像的旋轉角度（以度為單位）。如果需要旋轉來自網路攝影機或檔案的影像，請根據需要設置。例如，如果您希望將網路攝影機中橫向模式的香蕉影像更改為縱向模式，請設置 `camera.rotation = 90`。

1. 在此程式碼下方添加以下程式碼以捕捉影像為二進制數據：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    此程式碼創建了一個 `BytesIO` 對象來存儲二進制數據。影像以 JPEG 文件的形式從相機讀取並存儲在此對象中。該對象有一個位置指示器，用於指示數據中的位置，以便需要時可以將更多數據寫入末尾，因此 `image.seek(0)` 行將此位置移回起始位置，以便稍後可以讀取所有數據。

1. 在此程式碼下方添加以下程式碼以將影像保存到文件：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    此程式碼打開一個名為 `image.jpg` 的文件進行寫入，然後從 `BytesIO` 對象中讀取所有數據並將其寫入文件。

    > 💁 您可以直接將影像捕捉到文件，而不是使用 `BytesIO` 對象，只需將文件名傳遞給 `camera.capture` 調用即可。使用 `BytesIO` 對象的原因是稍後在本課程中，您可以將影像傳送到您的影像分類器。

1. 配置 CounterFit 中相機將捕捉的影像。您可以將 *Source* 設置為 *File*，然後上傳影像文件，或者將 *Source* 設置為 *WebCam*，影像將從您的網路攝影機捕捉。選擇影像或網路攝影機後，請確保選擇 **Set** 按鈕。

    ![CounterFit 中設置檔案為影像來源，以及網路攝影機顯示一個人手持香蕉的預覽](../../../../../translated_images/mo/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. 影像將被捕捉並保存為 `image.jpg`，位於當前資料夾中。您將在 VS Code 的檔案瀏覽器中看到此文件。選擇該文件以查看影像。如果需要旋轉，請根據需要更新 `camera.rotation = 0` 行並重新拍攝影像。

> 💁 您可以在 [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) 資料夾中找到此程式碼。

😀 您的相機程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。