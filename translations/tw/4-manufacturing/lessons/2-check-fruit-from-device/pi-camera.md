<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c677667095f6133eee418c7e53615d05",
  "translation_date": "2025-08-24T21:29:21+00:00",
  "source_file": "4-manufacturing/lessons/2-check-fruit-from-device/pi-camera.md",
  "language_code": "tw"
}
-->
# 捕捉影像 - Raspberry Pi

在本課程中，您將為 Raspberry Pi 添加一個相機感測器，並從中讀取影像。

## 硬體

Raspberry Pi 需要一個相機。

您將使用的相機是 [Raspberry Pi Camera Module](https://www.raspberrypi.org/products/camera-module-v2/)。這款相機專為 Raspberry Pi 設計，通過 Pi 上的專用連接器連接。

> 💁 這款相機使用 [Camera Serial Interface，一種由移動產業處理器接口聯盟制定的協議](https://wikipedia.org/wiki/Camera_Serial_Interface)，簡稱 MIPI-CSI。這是一種專用的影像傳輸協議。

## 連接相機

相機可以通過一條扁平排線連接到 Raspberry Pi。

### 任務 - 連接相機

![Raspberry Pi 相機](../../../../../translated_images/tw/pi-camera-module.4278753c31bd6e757aa2b858be97d72049f71616278cefe4fb5abb485b40a078.png)

1. 關閉 Raspberry Pi 的電源。

1. 將隨相機附帶的扁平排線連接到相機上。為此，輕輕拉動插座上的黑色塑料夾，使其稍微彈出，然後將排線滑入插座，藍色面朝遠離鏡頭的一側，金屬針腳條朝向鏡頭的一側。插到底後，將黑色塑料夾推回原位。

   您可以在 [Raspberry Pi 相機模組入門文檔](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/2) 中找到一個動畫，展示如何打開夾子並插入排線。

   ![扁平排線插入相機模組](../../../../../translated_images/tw/pi-camera-ribbon-cable.0bf82acd251611c21ac616f082849413e2b322a261d0e4f8fec344248083b07e.png)

1. 從 Raspberry Pi 上取下 Grove Base Hat。

1. 將扁平排線穿過 Grove Base Hat 上的相機槽。確保排線的藍色面朝向標有 **A0**、**A1** 等的類比端口。

   ![扁平排線穿過 Grove Base Hat](../../../../../translated_images/tw/grove-base-hat-ribbon-cable.501fed202fcf73b11b2b68f6d246189f7d15d3e4423c572ddee79d77b4632b47.png)

1. 將扁平排線插入 Raspberry Pi 上的相機端口。同樣，拉起黑色塑料夾，插入排線，然後將夾子推回原位。排線的藍色面應朝向 USB 和以太網端口。

   ![扁平排線連接到 Raspberry Pi 的相機插座](../../../../../translated_images/tw/pi-camera-socket-ribbon-cable.a18309920b11800911082ed7aa6fb28e6d9be3a022e4079ff990016cae3fca10.png)

1. 重新安裝 Grove Base Hat。

## 編程相機

現在可以使用 [PiCamera](https://pypi.org/project/picamera/) Python 庫來編程 Raspberry Pi 以使用相機。

### 任務 - 啟用舊版相機模式

不幸的是，隨著 Raspberry Pi OS Bullseye 的發布，操作系統中相機軟體發生了變化，導致 PiCamera 默認無法使用。目前正在開發一個替代方案，名為 PiCamera2，但尚未準備好使用。

目前，您可以將 Raspberry Pi 設置為舊版相機模式，以使 PiCamera 正常工作。相機插座默認也是禁用的，但啟用舊版相機軟體會自動啟用插座。

1. 啟動 Raspberry Pi，並等待其完成啟動。

1. 啟動 VS Code，可以直接在 Raspberry Pi 上操作，或者通過 Remote SSH 擴展連接。

1. 在終端中執行以下命令：

    ```sh
    sudo raspi-config nonint do_legacy 0
    sudo reboot
    ```

    這將切換設置以啟用舊版相機軟體，然後重新啟動 Raspberry Pi 以使設置生效。

1. 等待 Raspberry Pi 重新啟動，然後重新啟動 VS Code。

### 任務 - 編程相機

編程設備。

1. 在終端中，於 `pi` 用戶的主目錄中創建一個名為 `fruit-quality-detector` 的新資料夾。在此資料夾中創建一個名為 `app.py` 的檔案。

1. 在 VS Code 中打開此資料夾。

1. 要與相機互動，可以使用 PiCamera Python 庫。使用以下命令安裝 Pip 套件：

    ```sh
    pip3 install picamera
    ```

1. 將以下代碼添加到您的 `app.py` 檔案中：

    ```python
    import io
    import time
    from picamera import PiCamera
    ```

    此代碼導入了一些所需的庫，包括 `PiCamera` 庫。

1. 在此代碼下方添加以下代碼以初始化相機：

    ```python
    camera = PiCamera()
    camera.resolution = (640, 480)
    camera.rotation = 0
    
    time.sleep(2)
    ```

    此代碼創建了一個 PiCamera 對象，並將解析度設置為 640x480。雖然支持更高的解析度（最高可達 3280x2464），但影像分類器處理的影像尺寸要小得多（227x227），因此無需捕捉和傳輸更大的影像。

    `camera.rotation = 0` 行設置了影像的旋轉角度。扁平排線從相機底部進入，但如果您的相機為了更方便地對準要分類的物品而旋轉了，則可以將此行更改為相應的旋轉角度。

    ![相機懸掛在飲料罐上方](../../../../../translated_images/tw/pi-camera-upside-down.5376961ba31459883362124152ad6b823d5ac5fc14e85f317e22903bd681c2b6.png)

    例如，如果您將扁平排線懸掛在某物上，使其位於相機的頂部，則將旋轉角度設置為 180：

    ```python
    camera.rotation = 180
    ```

    相機啟動需要幾秒鐘，因此需要 `time.sleep(2)`。

1. 在此代碼下方添加以下代碼以將影像捕捉為二進位數據：

    ```python
    image = io.BytesIO()
    camera.capture(image, 'jpeg')
    image.seek(0)
    ```

    此代碼創建了一個 `BytesIO` 對象來存儲二進位數據。影像以 JPEG 文件的形式從相機讀取並存儲在此對象中。此對象有一個位置指示器，用於指示當前數據的位置，以便需要時可以在末尾寫入更多數據，因此 `image.seek(0)` 行將此位置移回起始位置，以便稍後可以讀取所有數據。

1. 在此代碼下方添加以下代碼以將影像保存到文件：

    ```python
    with open('image.jpg', 'wb') as image_file:
        image_file.write(image.read())
    ```

    此代碼打開一個名為 `image.jpg` 的文件進行寫入，然後從 `BytesIO` 對象中讀取所有數據並寫入該文件。

    > 💁 您可以直接將影像捕捉到文件，而不是使用 `BytesIO` 對象，只需將文件名傳遞給 `camera.capture` 調用即可。使用 `BytesIO` 對象的原因是，在本課程的後續部分，您可以將影像發送到影像分類器。

1. 將相機對準某物並運行此代碼。

1. 一張影像將被捕捉並保存為當前資料夾中的 `image.jpg`。您可以在 VS Code 的檔案瀏覽器中看到此文件。選擇該文件以查看影像。如果需要旋轉，請更新 `camera.rotation = 0` 行，然後重新拍攝。

> 💁 您可以在 [code-camera/pi](../../../../../4-manufacturing/lessons/2-check-fruit-from-device/code-camera/pi) 資料夾中找到此代碼。

😀 您的相機程式成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤讀概不負責。