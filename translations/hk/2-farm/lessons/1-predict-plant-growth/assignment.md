<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1e21b012c6685f8bf73e0e76cdca3347",
  "translation_date": "2025-08-26T14:29:14+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/assignment.md",
  "language_code": "hk"
}
-->
# 使用 Jupyter Notebook 視覺化 GDD 數據

## 指引

在本課程中，你使用 IoT 感測器收集了 GDD 數據。要獲得良好的 GDD 數據，你需要收集多天的數據。為了幫助視覺化溫度數據並計算 GDD，你可以使用像 [Jupyter Notebooks](https://jupyter.org) 這樣的工具來分析數據。

首先，收集幾天的數據。你需要確保你的伺服器程式在 IoT 裝置運行期間一直運行，可以通過調整電源管理設定或運行類似 [這個保持系統活躍的 Python 腳本](https://github.com/jaqsparow/keep-system-active) 來實現。

一旦你有了溫度數據，你可以使用此 repo 中的 Jupyter Notebook 來視覺化數據並計算 GDD。Jupyter Notebook 將程式碼和指引混合在稱為 *cells* 的區塊中，通常是 Python 程式碼。你可以閱讀指引，然後逐塊執行每段程式碼。你也可以編輯程式碼。例如，在這個 Notebook 中，你可以編輯用於計算植物 GDD 的基準溫度。

1. 建立一個名為 `gdd-calculation` 的資料夾

1. 下載 [gdd.ipynb](./code-notebook/gdd.ipynb) 檔案並將其複製到 `gdd-calculation` 資料夾中。

1. 複製由 MQTT 伺服器建立的 `temperature.csv` 檔案

1. 在 `gdd-calculation` 資料夾中建立一個新的 Python 虛擬環境。

1. 安裝一些 Jupyter Notebook 所需的 pip 套件，以及管理和繪製數據所需的庫：

    ```sh
    pip install --upgrade pip
    pip install pandas
    pip install matplotlib
    pip install jupyter
    ```

1. 在 Jupyter 中運行 Notebook：

    ```sh
    jupyter notebook gdd.ipynb
    ```

    Jupyter 會啟動並在你的瀏覽器中打開 Notebook。按照 Notebook 中的指引逐步操作，視覺化測量的溫度並計算生長度日。

    ![Jupyter Notebook](../../../../../translated_images/hk/gdd-jupyter-notebook.c5b52cf21094f158a61f47f455490fd95f1729777ff90861a4521820bf354cdc.png)

## 評分標準

| 評分項目 | 優秀 | 合格 | 需要改進 |
| -------- | ---- | ---- | -------- |
| 數據收集 | 收集至少 2 天完整的數據 | 收集至少 1 天完整的數據 | 收集部分數據 |
| 計算 GDD | 成功運行 Notebook 並計算 GDD | 成功運行 Notebook | 無法運行 Notebook |

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。