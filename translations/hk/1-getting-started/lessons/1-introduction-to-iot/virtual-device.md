<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "52b4de6144b2efdced7797a5339d6035",
  "translation_date": "2025-08-26T15:11:24+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/virtual-device.md",
  "language_code": "hk"
}
-->
# 虛擬單板電腦

與其購買物聯網設備以及感應器和執行器，你可以使用你的電腦來模擬物聯網硬件。[CounterFit 專案](https://github.com/CounterFit-IoT/CounterFit) 允許你在本地運行一個應用程式，模擬像感應器和執行器這樣的物聯網硬件，並通過本地的 Python 程式碼訪問這些感應器和執行器。這些程式碼的編寫方式與你在 Raspberry Pi 上使用實體硬件時的編寫方式相同。

## 設置

要使用 CounterFit，你需要在電腦上安裝一些免費的軟件。

### 任務

安裝所需的軟件。

1. 安裝 Python。請參考 [Python 下載頁面](https://www.python.org/downloads/) 以獲取安裝最新版本 Python 的指引。

1. 安裝 Visual Studio Code (VS Code)。這是你將用來編寫虛擬設備 Python 程式碼的編輯器。請參考 [VS Code 文件](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) 以獲取安裝 VS Code 的指引。

    > 💁 如果你有偏好的工具，可以自由選擇任何 Python IDE 或編輯器來完成這些課程，但課程中的指引將基於使用 VS Code。

1. 安裝 VS Code 的 Pylance 擴展。這是一個為 VS Code 提供 Python 語言支持的擴展。請參考 [Pylance 擴展文件](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 以獲取在 VS Code 中安裝此擴展的指引。

CounterFit 應用程式的安裝和配置指引將在相關的作業指令中提供，因為它是按專案安裝的。

## Hello World

在學習一種新的程式語言或技術時，通常會先建立一個 "Hello World" 應用程式——一個小型應用程式，輸出類似 `"Hello World"` 的文字，以確認所有工具已正確配置。

虛擬物聯網硬件的 Hello World 應用程式將確保你已正確安裝 Python 和 Visual Studio Code。它還會連接到 CounterFit 以模擬物聯網感應器和執行器。這個應用程式不會使用任何硬件，只是進行連接以確認一切正常。

此應用程式將位於名為 `nightlight` 的資料夾中，並在作業的後續部分中重複使用不同的程式碼來建立夜燈應用程式。

### 配置 Python 虛擬環境

Python 的一個強大功能是能夠安裝 [Pip 套件](https://pypi.org)——這些是由其他人編寫並發布到互聯網上的程式碼套件。你可以通過一條指令在電腦上安裝 Pip 套件，然後在程式碼中使用該套件。你將使用 Pip 安裝一個套件來與 CounterFit 通訊。

默認情況下，當你安裝一個套件時，它在電腦的所有地方都可用，這可能會導致套件版本的問題——例如，一個應用程式依賴於某個版本的套件，而安裝新版本可能會導致另一個應用程式出現問題。為了解決這個問題，你可以使用 [Python 虛擬環境](https://docs.python.org/3/library/venv.html)，它本質上是 Python 的一個副本，存放在一個專用資料夾中，當你安裝 Pip 套件時，它們只會安裝到該資料夾中。

> 💁 如果你使用的是 Raspberry Pi，那麼你不需要在該設備上設置虛擬環境來管理 Pip 套件，而是使用全局套件，因為 Grove 套件是通過安裝腳本全局安裝的。

#### 任務 - 配置 Python 虛擬環境

配置 Python 虛擬環境並安裝 CounterFit 的 Pip 套件。

1. 在終端或命令行中，運行以下指令以在你選擇的位置建立並進入一個新目錄：

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. 現在運行以下指令以在 `.venv` 資料夾中建立虛擬環境：

    ```sh
    python3 -m venv .venv
    ```

    > 💁 你需要明確調用 `python3` 來建立虛擬環境，以防你的系統同時安裝了 Python 2 和 Python 3（最新版本）。如果安裝了 Python 2，調用 `python` 會使用 Python 2 而不是 Python 3。

1. 啟動虛擬環境：

    * 在 Windows 上：
        * 如果你使用的是命令提示符或 Windows Terminal 中的命令提示符，運行：

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * 如果你使用的是 PowerShell，運行：

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > 如果你收到關於系統禁用腳本運行的錯誤，你需要通過設置適當的執行策略來啟用腳本運行。你可以以管理員身份啟動 PowerShell，然後運行以下指令：

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            當被要求確認時輸入 `Y`。然後重新啟動 PowerShell 並再次嘗試。

            如果需要，你可以稍後重置此執行策略。你可以在 [Microsoft Docs 的執行策略頁面](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn) 上了解更多。

    * 在 macOS 或 Linux 上，運行：

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 這些指令應在你運行建立虛擬環境指令的同一位置執行。你永遠不需要進入 `.venv` 資料夾，應始終在建立虛擬環境的資料夾中運行啟動指令以及任何安裝套件或運行程式的指令。

1. 啟動虛擬環境後，默認的 `python` 指令將運行用於建立虛擬環境的 Python 版本。運行以下指令以檢查版本：

    ```sh
    python --version
    ```

    輸出應包含以下內容：

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 你的 Python 版本可能不同——只要是 3.6 或更高版本即可。如果不是，刪除該資料夾，安裝更新版本的 Python 並重試。

1. 運行以下指令以安裝 CounterFit 的 Pip 套件。這些套件包括主要的 CounterFit 應用程式以及 Grove 硬件的 shims。這些 shims 允許你像編寫 Grove 生態系統的實體感應器和執行器程式碼一樣編寫程式碼，但連接的是虛擬物聯網設備。

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    這些 Pip 套件只會安裝在虛擬環境中，無法在虛擬環境外部使用。

### 編寫程式碼

當 Python 虛擬環境準備好後，你可以編寫 "Hello World" 應用程式的程式碼。

#### 任務 - 編寫程式碼

建立一個 Python 應用程式，將 `"Hello World"` 輸出到控制台。

1. 在虛擬環境中，通過終端或命令行運行以下指令以建立名為 `app.py` 的 Python 文件：

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

    > 💁 如果你的終端在 macOS 上返回 `command not found`，這意味著 VS Code 尚未添加到 PATH。你可以按照 [VS Code 文件中從命令行啟動部分](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) 的指引將 VS Code 添加到 PATH，然後再次運行指令。VS Code 在 Windows 和 Linux 上默認添加到 PATH。

1. 當 VS Code 啟動時，它將激活 Python 虛擬環境。選定的虛擬環境將顯示在底部狀態欄中：

    ![VS Code 顯示選定的虛擬環境](../../../../../translated_images/vscode-virtual-env.8ba42e04c3d533cf.hk.png)

1. 如果 VS Code Terminal 在啟動時已運行，它將不會激活虛擬環境。最簡單的方法是使用 **Kill the active terminal instance** 按鈕關閉終端：

    ![VS Code Kill the active terminal instance 按鈕](../../../../../translated_images/vscode-kill-terminal.1cc4de7c6f25ee08.hk.png)

    你可以通過終端提示的前綴來判斷終端是否激活了虛擬環境。例如，它可能是：

    ```sh
    (.venv) ➜  nightlight
    ```

    如果提示中沒有 `.venv` 作為前綴，則虛擬環境未在終端中激活。

1. 通過選擇 *Terminal -> New Terminal* 或按 `` CTRL+` `` 啟動新的 VS Code 終端。新終端將加載虛擬環境，並在終端中顯示激活指令。提示也會包含虛擬環境的名稱（`.venv`）：

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. 從 VS Code 的資源管理器中打開 `app.py` 文件，並添加以下程式碼：

    ```python
    print('Hello World!')
    ```

    `print` 函數將其接收的內容輸出到控制台。

1. 從 VS Code 終端運行以下指令以運行你的 Python 應用程式：

    ```sh
    python app.py
    ```

    輸出將包含以下內容：

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 你的 "Hello World" 程式成功了！

### 連接 "硬件"

作為第二步的 "Hello World"，你將運行 CounterFit 應用程式並將程式碼連接到它。這是虛擬等效於將一些物聯網硬件插入開發套件。

#### 任務 - 連接 "硬件"

1. 從 VS Code 終端運行以下指令啟動 CounterFit 應用程式：

    ```sh
    counterfit
    ```

    應用程式將開始運行並在你的網頁瀏覽器中打開：

    ![Counter Fit 應用程式在瀏覽器中運行](../../../../../translated_images/counterfit-first-run.433326358b669b31d0e99c3513cb01bfbb13724d162c99cdcc8f51ecf5f9c779.hk.png)

    它將顯示為 *Disconnected*，右上角的 LED 是熄滅的。

1. 在 `app.py` 文件的頂部添加以下程式碼：

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    此程式碼從 `counterfit_connection` 模組中導入 `CounterFitConnection` 類，該模組來自你之前安裝的 `counterfit-connection` Pip 套件。然後它初始化了一個連接到運行在 `127.0.0.1` 的 CounterFit 應用程式，該 IP 地址始終可用於訪問你的本地電腦（通常稱為 *localhost*），端口為 5000。

    > 💁 如果你有其他應用程式在端口 5000 上運行，你可以通過更新程式碼中的端口來更改此設置，並使用 `CounterFit --port <port_number>` 運行 CounterFit，將 `<port_number>` 替換為你想使用的端口。

1. 你需要通過選擇 **Create a new integrated terminal** 按鈕啟動新的 VS Code 終端。這是因為 CounterFit 應用程式正在當前終端中運行。

    ![VS Code Create a new integrated terminal 按鈕](../../../../../translated_images/vscode-new-terminal.77db8fc0f9cd3182.hk.png)

1. 在這個新終端中，像之前一樣運行 `app.py` 文件。CounterFit 的狀態將變為 **Connected**，LED 會亮起。

    ![Counter Fit 顯示為已連接](../../../../../translated_images/counterfit-connected.ed30b46d8f79b0921f3fc70be10366e596a89dca3f80c2224a9d9fc98fccf884.hk.png)

> 💁 你可以在 [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device) 資料夾中找到這段程式碼。

😀 你成功連接到硬件了！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。