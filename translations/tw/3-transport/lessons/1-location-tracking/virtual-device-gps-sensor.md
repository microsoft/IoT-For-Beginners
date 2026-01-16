<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64f18a8f8aaa1fef5e7320e0992d8b3a",
  "translation_date": "2025-08-25T00:45:43+00:00",
  "source_file": "3-transport/lessons/1-location-tracking/virtual-device-gps-sensor.md",
  "language_code": "tw"
}
-->
# 讀取 GPS 數據 - 虛擬物聯網硬件

在本課程中，您將為虛擬物聯網設備添加一個 GPS 傳感器，並從中讀取數據。

## 虛擬硬件

虛擬物聯網設備將使用一個模擬的 GPS 傳感器，該傳感器可以通過串口 UART 訪問。

實體 GPS 傳感器通常配備天線，用於接收來自 GPS 衛星的電波，並將 GPS 信號轉換為 GPS 數據。虛擬版本則模擬此過程，允許您設置緯度和經度、發送原始 NMEA 語句，或上傳包含多個位置的 GPX 文件，這些位置可以按順序返回。

> 🎓 NMEA 語句將在本課程後續部分進行講解

### 在 CounterFit 中添加傳感器

要使用虛擬 GPS 傳感器，您需要在 CounterFit 應用中添加一個。

#### 任務 - 在 CounterFit 中添加傳感器

將 GPS 傳感器添加到 CounterFit 應用中。

1. 在您的電腦上創建一個名為 `gps-sensor` 的新 Python 應用，並在其中創建一個名為 `app.py` 的文件以及一個 Python 虛擬環境，然後添加 CounterFit 的 pip 套件。

    > ⚠️ 如果需要，您可以參考[第 1 課中創建和設置 CounterFit Python 項目的指導](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md)。

1. 安裝額外的 Pip 套件，以便安裝一個 CounterFit shim，該 shim 可以通過串口與基於 UART 的傳感器通信。確保您在啟動虛擬環境的終端中進行安裝。

    ```sh
    pip install counterfit-shims-serial
    ```

1. 確保 CounterFit 網頁應用正在運行。

1. 創建一個 GPS 傳感器：

    1. 在 *Sensors* 面板的 *Create sensor* 框中，展開 *Sensor type* 下拉框並選擇 *UART GPS*。

    1. 保持 *Port* 設置為 */dev/ttyAMA0*。

    1. 點擊 **Add** 按鈕，在端口 `/dev/ttyAMA0` 上創建 GPS 傳感器。

    ![GPS 傳感器設置](../../../../../translated_images/tw/counterfit-create-gps-sensor.6385dc9357d85ad1d47b4abb2525e7651fd498917d25eefc5a72feab09eedc70.png)

    GPS 傳感器將被創建並顯示在傳感器列表中。

    ![已創建的 GPS 傳感器](../../../../../translated_images/tw/counterfit-gps-sensor.3fbb15af0a5367566f2f11324ef5a6f30861cdf2b497071a5e002b7aa473550e.png)

## 編程 GPS 傳感器

現在可以為虛擬物聯網設備編程以使用虛擬 GPS 傳感器。

### 任務 - 編程 GPS 傳感器

編程 GPS 傳感器應用。

1. 確保 `gps-sensor` 應用已在 VS Code 中打開。

1. 打開 `app.py` 文件。

1. 在 `app.py` 文件的頂部添加以下代碼，以連接應用到 CounterFit：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. 在此代碼下方添加以下代碼，以導入一些需要的庫，包括 CounterFit 串口庫：

    ```python
    import time
    import counterfit_shims_serial
    
    serial = counterfit_shims_serial.Serial('/dev/ttyAMA0')
    ```

    此代碼從 `counterfit_shims_serial` Pip 套件中導入 `serial` 模塊。然後連接到 `/dev/ttyAMA0` 串口——這是虛擬 GPS 傳感器用於其 UART 端口的地址。

1. 在此代碼下方添加以下代碼，以從串口讀取數據並將值打印到控制台：

    ```python
    def print_gps_data(line):
        print(line.rstrip())
    
    while True:
        line = serial.readline().decode('utf-8')
    
        while len(line) > 0:
            print_gps_data(line)
            line = serial.readline().decode('utf-8')
    
        time.sleep(1)
    ```

    定義了一個名為 `print_gps_data` 的函數，用於將傳入的行打印到控制台。

    接下來，代碼進行無限循環，每次循環從串口讀取多行文本。對每行文本調用 `print_gps_data` 函數。

    在所有數據讀取完成後，循環會休眠 1 秒，然後再次嘗試。

1. 運行此代碼，確保使用與 CounterFit 應用運行的終端不同的終端，以便 CounterFit 應用保持運行。

1. 從 CounterFit 應用中更改 GPS 傳感器的值。您可以通過以下方式之一進行更改：

    * 將 **Source** 設置為 `Lat/Lon`，並設置明確的緯度、經度以及用於獲得 GPS 定位的衛星數量。此值僅會發送一次，因此勾選 **Repeat** 框以使數據每秒重複發送。

      ![選擇緯度和經度的 GPS 傳感器](../../../../../translated_images/tw/counterfit-gps-sensor-latlon.008c867d75464fbe7f84107cc57040df565ac07cb57d2f21db37d087d470197d.png)

    * 將 **Source** 設置為 `NMEA`，並在文本框中添加一些 NMEA 語句。所有這些值將被發送，每個新的 GGA（位置修正）語句可以在 1 秒延遲後被讀取。

      ![設置 NMEA 語句的 GPS 傳感器](../../../../../translated_images/tw/counterfit-gps-sensor-nmea.c62eea442171e17e19528b051b104cfcecdc9cd18db7bc72920f29821ae63f73.png)

      您可以使用像 [nmeagen.org](https://www.nmeagen.org) 這樣的工具通過在地圖上繪製來生成這些語句。這些值僅會發送一次，因此勾選 **Repeat** 框以使數據在全部發送後每秒重複一次。

    * 將 **Source** 設置為 GPX 文件，並上傳包含軌跡位置的 GPX 文件。您可以從一些流行的地圖和徒步網站（如 [AllTrails](https://www.alltrails.com/)）下載 GPX 文件。這些文件包含作為軌跡的多個 GPS 位置，GPS 傳感器將以 1 秒間隔返回每個新位置。

      ![設置 GPX 文件的 GPS 傳感器](../../../../../translated_images/tw/counterfit-gps-sensor-gpxfile.8310b063ce8a425ccc8ebeec8306aeac5e8e55207f007d52c6e1194432a70cd9.png)

      這些值僅會發送一次，因此勾選 **Repeat** 框以使數據在全部發送後每秒重複一次。

    配置 GPS 設置後，選擇 **Set** 按鈕以將這些值提交到傳感器。

1. 您將看到來自 GPS 傳感器的原始輸出，類似以下內容：

    ```output
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    $GNGGA,020604.001,4738.538654,N,12208.341758,W,1,3,,164.7,M,-17.1,M,,*67
    ```

> 💁 您可以在 [code-gps/virtual-device](../../../../../3-transport/lessons/1-location-tracking/code-gps/virtual-device) 文件夾中找到此代碼。

😀 您的 GPS 傳感器程序成功了！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對於因使用此翻譯而引起的任何誤解或誤讀概不負責。