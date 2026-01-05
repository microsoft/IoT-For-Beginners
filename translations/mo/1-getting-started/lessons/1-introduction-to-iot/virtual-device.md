<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-26T23:38:13+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "mo"
}
-->
# 虛擬單板電腦

與其購買物聯網設備以及感測器和致動器，你可以使用自己的電腦來模擬物聯網硬體。[CounterFit 專案](https://github.com/CounterFit-IoT/CounterFit) 允許你在本地運行一個應用程式，模擬感測器和致動器等物聯網硬體，並通過本地 Python 程式碼訪問這些感測器和致動器。這些程式碼的編寫方式與在 Raspberry Pi 上使用實體硬體時相同。

## 設置

要使用 CounterFit，你需要在電腦上安裝一些免費的軟體。

### 任務

安裝所需的軟體。

1. 安裝 Python。請參考 [Python 下載頁面](https://www.python.org/downloads/) 以獲取安裝最新版本 Python 的說明。

1. 安裝 Visual Studio Code (VS Code)。這是你將用來編寫虛擬設備 Python 程式碼的編輯器。請參考 [VS Code 文件](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) 以獲取安裝 VS Code 的說明。

    > 💁 如果你有偏好的工具，可以自由選擇任何 Python IDE 或編輯器來完成這些課程，但課程中的說明將基於使用 VS Code。

1. 安裝 VS Code 的 Pylance 擴展。這是為 VS Code 提供 Python 語言支持的擴展。請參考 [Pylance 擴展文件](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 以獲取在 VS Code 中安裝此擴展的說明。

安裝和配置 CounterFit 應用的說明將在作業指導的相關部分給出，因為它是按每個專案安裝的。

## Hello World

在學習一種新的程式語言或技術時，通常會從創建一個 "Hello World" 應用開始——這是一個小型應用，輸出類似於 `"Hello World"` 的文字，以確認所有工具已正確配置。

虛擬物聯網硬體的 Hello World 應用將確保你已正確安裝 Python 和 Visual Studio Code。它還會連接到 CounterFit，用於虛擬物聯網感測器和致動器。這個應用不會使用任何硬體，它只是連接以證明一切正常運行。

這個應用將位於一個名為 `nightlight` 的資料夾中，並在作業的後續部分中使用不同的程式碼來構建夜燈應用。

### 配置 Python 虛擬環境

Python 的一個強大功能是能夠安裝 [Pip 套件](https://pypi.org)——這些是由其他人編寫並發布到網路上的程式碼套件。你可以通過一條命令將 Pip 套件安裝到電腦上，然後在程式碼中使用該套件。你將使用 Pip 安裝一個與 CounterFit 通信的套件。

默認情況下，當你安裝一個套件時，它在電腦上的任何地方都可用，這可能會導致套件版本的問題——例如，一個應用依賴於某個版本的套件，而當你為另一個應用安裝新版本時，可能會導致問題。為了解決這個問題，你可以使用 [Python 虛擬環境](https://docs.python.org/3/library/venv.html)，它本質上是在一個專用資料夾中的 Python 副本，當你安裝 Pip 套件時，它們只會安裝到該資料夾中。

> 💁 如果你使用的是 Raspberry Pi，那麼你並未在該設備上設置虛擬環境來管理 Pip 套件，而是使用全域套件，因為 Grove 套件是通過安裝腳本全域安裝的。

#### 任務 - 配置 Python 虛擬環境

配置 Python 虛擬環境並安裝 CounterFit 的 Pip 套件。

1. 在終端或命令行中，運行以下命令，在你選擇的位置創建並導航到一個新目錄：

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. 現在運行以下命令，在 `.venv` 資料夾中創建一個虛擬環境：

    ```sh
    python3 -m venv .venv
    ```

    > 💁 你需要顯式調用 `python3` 來創建虛擬環境，以防你同時安裝了 Python 2 和 Python 3（最新版本）。如果安裝了 Python 2，則調用 `python` 將使用 Python 2 而不是 Python 3。

1. 啟動虛擬環境：

    * 在 Windows 上：
        * 如果使用命令提示符或 Windows Terminal 中的命令提示符，運行：

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * 如果使用 PowerShell，運行：

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > 如果出現關於系統禁用腳本運行的錯誤，你需要通過設置適當的執行策略來啟用腳本運行。你可以以管理員身份啟動 PowerShell，然後運行以下命令：

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            當被要求確認時輸入 `Y`。然後重新啟動 PowerShell 並重試。

            如果需要，你可以稍後重置此執行策略。你可以在 [Microsoft Docs 的執行策略頁面](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn) 上閱讀更多相關內容。

    * 在 macOS 或 Linux 上，運行：

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 這些命令應在你運行創建虛擬環境命令的相同位置運行。你永遠不需要導航到 `.venv` 資料夾中，應始終從創建虛擬環境時所在的資料夾運行啟動命令以及任何安裝套件或運行程式的命令。

1. 啟動虛擬環境後，默認的 `python` 命令將運行用於創建虛擬環境的 Python 版本。運行以下命令以獲取版本：

    ```sh
    python --version
    ```

    輸出應包含以下內容：

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 你的 Python 版本可能不同——只要是 3.6 或更高版本即可。如果不是，刪除此資料夾，安裝更新版本的 Python 並重試。

1. 運行以下命令以安裝 CounterFit 的 Pip 套件。這些套件包括主要的 CounterFit 應用以及 Grove 硬體的 shims。這些 shims 允許你像使用 Grove 生態系統中的實體感測器和致動器一樣編寫程式碼，但它們連接到虛擬物聯網設備。

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    這些 Pip 套件將僅安裝在虛擬環境中，無法在其外部使用。

### 編寫程式碼

當 Python 虛擬環境準備就緒後，你可以編寫 "Hello World" 應用的程式碼。

#### 任務 - 編寫程式碼

創建一個 Python 應用，將 `"Hello World"` 輸出到控制台。

1. 在虛擬環境中，從終端或命令行運行以下命令以創建一個名為 `app.py` 的 Python 文件：

    * 在 Windows 上運行：

        ```cmd
        type nul > app.py
        ```

    * 在 macOS 或 Linux 上運行：

        ```cmd
        touch app.py
        ```

1. 在 VS Code 中打開當前資料夾：

    ```sh
    code .
    ```

    > 💁 如果你的終端在 macOS 上返回 `command not found`，這意味著 VS Code 尚未添加到你的 PATH。你可以按照 [VS Code 文件中從命令行啟動部分](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) 的說明將 VS Code 添加到 PATH，然後再次運行該命令。在 Windows 和 Linux 上，VS Code 默認會添加到 PATH。

1. 當 VS Code 啟動時，它將啟動 Python 虛擬環境。選定的虛擬環境將顯示在底部狀態欄中：

    ![VS Code 顯示選定的虛擬環境](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.mo.png)

1. 如果 VS Code Terminal 在啟動時已運行，則它不會啟動虛擬環境。最簡單的方法是使用 **Kill the active terminal instance** 按鈕關閉終端：

    ![VS Code Kill the active terminal instance 按鈕](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.mo.png)

    你可以通過終端提示符上的虛擬環境名稱來判斷終端是否啟動了虛擬環境。例如，它可能是：

    ```sh
    (.venv) ➜  nightlight
    ```

    如果提示符中沒有 `.venv` 作為前綴，則終端未啟動虛擬環境。

1. 通過選擇 *Terminal -> New Terminal* 或按下 `` CTRL+` `` 啟動新的 VS Code Terminal。新終端將加載虛擬環境，並在終端中顯示啟動此環境的命令。提示符也將包含虛擬環境的名稱（`.venv`）：

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. 從 VS Code 資源管理器中打開 `app.py` 文件，並添加以下程式碼：

    ```python
    print('Hello World!')
    ```

    `print` 函數會將傳遞給它的內容輸出到控制台。

1. 從 VS Code 終端運行以下命令以運行你的 Python 應用：

    ```sh
    python app.py
    ```

    輸出將顯示以下內容：

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 你的 "Hello World" 程式成功了！

### 連接 "硬體"

作為第二個 "Hello World" 步驟，你將運行 CounterFit 應用並將程式碼連接到它。這相當於虛擬地將一些物聯網硬體插入開發套件。

#### 任務 - 連接 "硬體"

1. 從 VS Code 終端運行以下命令啟動 CounterFit 應用：

    ```sh
    counterfit
    ```

    該應用將開始運行並在瀏覽器中打開：

    ![在瀏覽器中運行的 Counter Fit 應用](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.mo.png)

    它將顯示為 *Disconnected*，右上角的 LED 為關閉狀態。

1. 在 `app.py` 文件的頂部添加以下程式碼：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    此程式碼從你之前安裝的 `counterfit-connection` pip 套件中導入 `CounterFitConnection` 類，然後初始化與運行在 `127.0.0.1`（一個始終可用於訪問本地電腦的 IP 地址，通常稱為 *localhost*）上的 CounterFit 應用的連接，端口為 5000。

    > 💁 如果你有其他應用運行在 5000 端口，你可以通過更新程式碼中的端口來更改此設置，並使用 `CounterFit --port <port_number>` 運行 CounterFit，將 `<port_number>` 替換為你想使用的端口。

1. 你需要通過選擇 **Create a new integrated terminal** 按鈕啟動新的 VS Code 終端。這是因為 CounterFit 應用正在當前終端中運行。

    ![VS Code Create a new integrated terminal 按鈕](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.mo.png)

1. 在這個新終端中，像之前一樣運行 `app.py` 文件。CounterFit 的狀態將變為 **Connected**，LED 會亮起。

    ![Counter Fit 顯示為已連接](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.mo.png)

> 💁 你可以在 [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) 資料夾中找到這段程式碼。

😀 你成功連接到硬體了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們努力確保翻譯的準確性，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋不承擔責任。