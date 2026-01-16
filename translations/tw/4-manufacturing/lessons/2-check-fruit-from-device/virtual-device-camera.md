<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "3ba7150ffc4a6999f6c3cfb4906ec7df",
  "translation_date": "2025-08-24T21:33:47+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/virtual-device-camera.md",
  "language_code": "tw"
}
-->
# 捕捉影像 - 虛擬 IoT 硬體

在本課程中，您將為虛擬 IoT 裝置新增一個相機感測器，並從中讀取影像。

## 硬體

虛擬 IoT 裝置將使用模擬相機，該相機可以傳送來自檔案或您的網路攝影機的影像。

### 將相機新增到 CounterFit

要使用虛擬相機，您需要將其新增到 CounterFit 應用程式中。

#### 任務 - 將相機新增到 CounterFit

將相機新增到 CounterFit 應用程式中。

1. 在您的電腦上建立一個名為 `fruit-quality-detector` 的資料夾，並在其中建立一個名為 `app.py` 的單一檔案和一個 Python 虛擬環境，然後新增 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，您可以參考[第 1 課中建立和設定 CounterFit Python 專案的指導說明](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安裝一個額外的 Pip 套件，以安裝一個 CounterFit shim，該 shim 可以透過模擬部分 [Picamera Pip 套件](https://pypi.org/project/picamera/) 與相機感測器進行通訊。請確保您是在啟用虛擬環境的終端機中執行安裝。

    ```sh
    pip install counterfit-shims-picamera
    ```

1. 確保 CounterFit 網頁應用程式正在執行。

1. 建立一個相機：

    1. 在 *Sensors* 面板的 *Create sensor* 區塊中，展開 *Sensor type* 下拉選單並選擇 *Camera*。

    1. 將 *Name* 設定為 `Picamera`。

    1. 選擇 **Add** 按鈕以建立相機。

    ![相機設定](../../../../../translated_images/tw/counterfit-create-camera.a5de97f59c0bd3cbe0416d7e89a3cfe86d19fbae05c641c53a91286412af0a34.png)

    相機將被建立並顯示在感測器清單中。

    ![已建立的相機](../../../../../translated_images/tw/counterfit-camera.001ec52194c8ee5d3f617173da2c79e1df903d10882adc625cbfc493525125d4.png)

## 程式設計相機

現在可以為虛擬 IoT 裝置編寫程式以使用虛擬相機。

### 任務 - 程式設計相機

為裝置編寫程式。

1. 確保 `fruit-quality-detector` 應用程式已在 VS Code 中開啟。

1. 開啟 `app.py` 檔案。

1. 在 `app.py` 的頂部新增以下程式碼，以將應用程式連接到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在您的 `app.py` 檔案中新增以下程式碼：

    ```python
    import io
    from counterfit_shims_picamera import PiCamera
    ```

    此程式碼匯入了一些必要的函式庫，包括來自 counterfit_shims_picamera 函式庫的 `PiCamera` 類別。

1. 在此程式碼下方新增以下程式碼以初始化相機：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    ```

    此程式碼建立了一個 PiCamera 物件，並將解析度設定為 640x480。雖然支援更高的解析度，但影像分類器僅處理更小的影像（227x227），因此無需捕捉和傳送更大的影像。

    `camera.rotation = 0` 這一行設定了影像的旋轉角度（以度為單位）。如果需要旋轉來自網路攝影機或檔案的影像，請根據需要進行設定。例如，如果您想將橫向模式的網路攝影機中香蕉的影像改為直向模式，請設定 `camera.rotation = 90`。

1. 在此程式碼下方新增以下程式碼以將影像捕捉為二進位資料：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    此程式碼建立了一個 `BytesIO` 物件來儲存二進位資料。影像以 JPEG 檔案的形式從相機讀取並儲存在此物件中。此物件具有一個位置指標，用於指示目前在資料中的位置，以便在需要時可以將更多資料寫入結尾。因此，`image.seek(0)` 這一行將位置移回起始位置，以便稍後可以讀取所有資料。

1. 在此程式碼下方新增以下程式碼以將影像儲存到檔案中：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    此程式碼開啟一個名為 `image.jpg` 的檔案進行寫入，然後從 `BytesIO` 物件中讀取所有資料並將其寫入檔案中。

    > 💁 您可以直接將影像捕捉到檔案中，而不是使用 `BytesIO` 物件，只需將檔案名稱傳遞給 `camera.capture` 呼叫即可。使用 `BytesIO` 物件的原因是，在本課程稍後的部分，您可以將影像傳送到影像分類器。

1. 設定 CounterFit 中相機將捕捉的影像。您可以將 *Source* 設定為 *File*，然後上傳一個影像檔案；或者將 *Source* 設定為 *WebCam*，影像將從您的網路攝影機捕捉。確保在選擇圖片或網路攝影機後按下 **Set** 按鈕。

    ![CounterFit 設定為檔案作為影像來源，並顯示網路攝影機預覽中一個人拿著香蕉的畫面](../../../../../translated_images/tw/counterfit-camera-options.eb3bd5150a8e7dffbf24bc5bcaba0cf2cdef95fbe6bbe393695d173817d6b8df.png)

1. 一張影像將被捕捉並儲存為 `image.jpg`，位於目前的資料夾中。您將在 VS Code 的檔案總管中看到此檔案。選擇該檔案以檢視影像。如果需要旋轉，請根據需要更新 `camera.rotation = 0` 這一行，然後重新拍攝影像。

> 💁 您可以在 [code-camera/virtual-iot-device](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/virtual-iot-device) 資料夾中找到此程式碼。

😀 您的相機程式設計成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。