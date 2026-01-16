<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-26T23:41:17+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "mo"
}
-->
# 樹莓派

[樹莓派](https://raspberrypi.org) 是一款單板電腦。你可以使用各種設備和生態系統添加感測器和致動器，這些課程中將使用一種名為 [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html) 的硬體生態系統。你將使用 Python 為樹莓派編寫程式並存取 Grove 感測器。

![樹莓派 4](../../../../../translated_images/mo/raspberry-pi-4.fd4590d308c3d456.webp)

## 設置

如果你使用樹莓派作為物聯網硬體，有兩種選擇——你可以直接在樹莓派上完成所有課程並編寫程式碼，或者遠端連接到一個「無頭」的樹莓派，從你的電腦上進行編碼。

在開始之前，你還需要將 Grove Base Hat 連接到樹莓派。

### 任務 - 設置

安裝 Grove Base Hat 並配置樹莓派。

1. 將 Grove Base Hat 連接到樹莓派。帽子上的插槽與樹莓派的所有 GPIO 引腳對應，將其完全滑入引腳，穩固地安裝在基座上。它會覆蓋樹莓派。

    ![安裝 Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. 決定你想如何編程樹莓派，然後前往以下相關部分：

    * [直接在樹莓派上工作](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [遠端訪問樹莓派進行編碼](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### 直接在樹莓派上工作

如果你想直接在樹莓派上工作，可以使用樹莓派 OS 的桌面版本並安裝所有需要的工具。

#### 任務 - 直接在樹莓派上工作

為開發設置樹莓派。

1. 按照 [樹莓派設置指南](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up) 的說明設置樹莓派，連接鍵盤/滑鼠/顯示器，連接到 WiFi 或乙太網路，並更新軟體。

為了使用 Grove 感測器和致動器編寫程式碼，你需要安裝一個編輯器來撰寫設備程式碼，以及與 Grove 硬體互動的各種庫和工具。

1. 當樹莓派重新啟動後，點擊頂部菜單欄的 **Terminal** 圖示啟動終端，或者選擇 *Menu -> Accessories -> Terminal*。

1. 執行以下命令以確保操作系統和已安裝的軟體是最新的：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. 執行以下命令以安裝 Grove 硬體所需的所有庫：

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    這些命令首先安裝 Git 和 Pip，用於安裝 Python 套件。

    Python 的一個強大功能是能夠安裝 [Pip 套件](https://pypi.org)——這些是其他人編寫並發布到網路上的程式碼包。你可以用一條命令將 Pip 套件安裝到電腦上，然後在程式碼中使用該套件。

    Seeed Grove 的 Python 套件需要從原始碼安裝。這些命令會克隆包含該套件原始碼的倉庫，然後在本地安裝。

    > 💁 默認情況下，當你安裝一個套件時，它會在電腦的所有地方可用，這可能會導致套件版本的問題——例如，一個應用程式依賴於某個版本的套件，而安裝新版本可能會破壞另一個應用程式。為了解決這個問題，你可以使用 [Python 虛擬環境](https://docs.python.org/3/library/venv.html)，它本質上是 Python 的一個副本，位於一個專用資料夾中，當你安裝 Pip 套件時，它們只會安裝到該資料夾中。在使用樹莓派時，你不會使用虛擬環境。Grove 安裝腳本會全域安裝 Grove 的 Python 套件，因此如果你想使用虛擬環境，需要先設置虛擬環境，然後手動重新安裝 Grove 套件到該環境中。使用全域套件更簡單，特別是許多樹莓派開發者會為每個專案重新刷新乾淨的 SD 卡。

    最後，這些命令會啟用 I<sup>2</sup>C 介面。

1. 使用菜單或在終端中執行以下命令重新啟動樹莓派：

    ```sh
    sudo reboot
    ```

1. 當樹莓派重新啟動後，重新打開終端並執行以下命令安裝 [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn)——這是你將用來用 Python 編寫設備程式碼的編輯器。

    ```sh
    sudo apt install code
    ```

    安裝完成後，VS Code 將可從頂部菜單中訪問。

    > 💁 如果你有偏好的工具，可以自由選擇任何 Python IDE 或編輯器來完成這些課程，但課程中的指導將基於 VS Code。

1. 安裝 Pylance。這是 VS Code 的一個擴展，提供 Python 語言支持。請參考 [Pylance 擴展文檔](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 了解如何在 VS Code 中安裝該擴展。

### 遠端訪問樹莓派進行編碼

與其直接在樹莓派上編碼，你可以讓它以「無頭」模式運行，也就是不連接鍵盤/滑鼠/顯示器，並從你的電腦上使用 Visual Studio Code 進行配置和編碼。

#### 設置樹莓派 OS

要遠端編碼，需要將樹莓派 OS 安裝到 SD 卡上。

##### 任務 - 設置樹莓派 OS

設置無頭模式的樹莓派 OS。

1. 從 [樹莓派 OS 軟體頁面](https://www.raspberrypi.org/software/) 下載 **Raspberry Pi Imager** 並安裝。

1. 將 SD 卡插入電腦，必要時使用轉接器。

1. 啟動 Raspberry Pi Imager。

1. 在 Raspberry Pi Imager 中，選擇 **CHOOSE OS** 按鈕，然後選擇 *Raspberry Pi OS (Other)*，接著選擇 *Raspberry Pi OS Lite (32-bit)*。

    ![Raspberry Pi Imager 中選擇 Raspberry Pi OS Lite](../../../../../translated_images/mo/raspberry-pi-imager.24aedeab9e233d84.webp)

    > 💁 Raspberry Pi OS Lite 是樹莓派 OS 的一個版本，沒有桌面 UI 或基於 UI 的工具。這些對無頭模式的樹莓派來說並不需要，並且使安裝更小，啟動時間更快。

1. 選擇 **CHOOSE STORAGE** 按鈕，然後選擇你的 SD 卡。

1. 按下 `Ctrl+Shift+X` 啟動 **Advanced Options**。這些選項允許在將樹莓派 OS 寫入 SD 卡之前進行一些預配置。

    1. 勾選 **Enable SSH**，並為 `pi` 使用者設置密碼。這是你稍後登錄樹莓派時使用的密碼。

    1. 如果你計劃通過 WiFi 連接樹莓派，勾選 **Configure WiFi**，並輸入你的 WiFi SSID 和密碼，還有選擇你的 WiFi 國家。如果你將使用乙太網線，則不需要這樣做。確保你連接的網路與電腦在同一網路中。

    1. 勾選 **Set locale settings**，並設置你的國家和時區。

    1. 選擇 **SAVE** 按鈕。

1. 選擇 **WRITE** 按鈕將 OS 寫入 SD 卡。如果你使用 macOS，系統會要求你輸入密碼，因為寫入磁碟映像的底層工具需要特權訪問。

OS 會被寫入 SD 卡，完成後系統會彈出該卡，並通知你。從電腦中取出 SD 卡，插入樹莓派，啟動樹莓派並等待約 2 分鐘讓其正常啟動。

#### 連接到樹莓派

下一步是遠端訪問樹莓派。你可以使用 `ssh`，該工具在 macOS、Linux 和最近版本的 Windows 上可用。

##### 任務 - 連接到樹莓派

遠端訪問樹莓派。

1. 啟動終端或命令提示符，輸入以下命令連接到樹莓派：

    ```sh
    ssh pi@raspberrypi.local
    ```

    如果你使用的是舊版 Windows，且未安裝 `ssh`，可以使用 OpenSSH。安裝說明請參考 [OpenSSH 安裝文檔](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn)。

1. 這應該會連接到樹莓派並要求輸入密碼。

    能夠通過 `<hostname>.local` 在網路上找到電腦是 Linux 和 Windows 最近新增的一個功能。如果你使用的是 Linux 或 Windows，並且收到有關找不到主機名的錯誤，則需要安裝額外的軟體來啟用 ZeroConf 網路（Apple 稱之為 Bonjour）：

    1. 如果你使用的是 Linux，使用以下命令安裝 Avahi：

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. 如果你使用的是 Windows，啟用 ZeroConf 最簡單的方法是安裝 [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999)。你也可以安裝 [iTunes for Windows](https://www.apple.com/itunes/download/) 以獲得該工具的更新版本（該版本無法單獨下載）。

    > 💁 如果你無法使用 `raspberrypi.local` 連接，則可以使用樹莓派的 IP 地址。請參考 [樹莓派 IP 地址文檔](https://www.raspberrypi.org/documentation/remote-access/ip-address.md) 獲取多種方法來獲取 IP 地址的說明。

1. 輸入你在 Raspberry Pi Imager 高級選項中設置的密碼。

#### 配置樹莓派上的軟體

連接到樹莓派後，你需要確保操作系統是最新的，並安裝與 Grove 硬體互動的各種庫和工具。

##### 任務 - 配置樹莓派上的軟體

配置已安裝的樹莓派軟體並安裝 Grove 庫。

1. 在你的 `ssh` 會話中，執行以下命令以更新並重新啟動樹莓派：

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    樹莓派將被更新並重新啟動。當樹莓派重新啟動時，`ssh` 會話將結束，因此等待約 30 秒後重新連接。

1. 在重新連接的 `ssh` 會話中，執行以下命令以安裝 Grove 硬體所需的所有庫：

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    這些命令首先安裝 Git 和 Pip，用於安裝 Python 套件。

    Python 的一個強大功能是能夠安裝 [Pip 套件](https://pypi.org)——這些是其他人編寫並發布到網路上的程式碼包。你可以用一條命令將 Pip 套件安裝到電腦上，然後在程式碼中使用該套件。

    Seeed Grove 的 Python 套件需要從原始碼安裝。這些命令會克隆包含該套件原始碼的倉庫，然後在本地安裝。

    > 💁 默認情況下，當你安裝一個套件時，它會在電腦的所有地方可用，這可能會導致套件版本的問題——例如，一個應用程式依賴於某個版本的套件，而安裝新版本可能會破壞另一個應用程式。為了解決這個問題，你可以使用 [Python 虛擬環境](https://docs.python.org/3/library/venv.html)，它本質上是 Python 的一個副本，位於一個專用資料夾中，當你安裝 Pip 套件時，它們只會安裝到該資料夾中。在使用樹莓派時，你不會使用虛擬環境。Grove 安裝腳本會全域安裝 Grove 的 Python 套件，因此如果你想使用虛擬環境，需要先設置虛擬環境，然後手動重新安裝 Grove 套件到該環境中。使用全域套件更簡單，特別是許多樹莓派開發者會為每個專案重新刷新乾淨的 SD 卡。

    最後，這些命令會啟用 I<sup>2</sup>C 介面。

1. 執行以下命令重新啟動樹莓派：

    ```sh
    sudo reboot
    ```

    當樹莓派重新啟動時，`ssh` 會話將結束。無需重新連接。

#### 配置 VS Code 進行遠端訪問

樹莓派配置完成後，你可以使用 Visual Studio Code (VS Code) 從電腦連接到它——這是一款免費的開發者文本編輯器，你將用它來用 Python 編寫設備程式碼。

##### 任務 - 配置 VS Code 進行遠端訪問

安裝所需軟體並遠端連接到樹莓派。

1. 按照 [VS Code 文檔](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) 的說明在電腦上安裝 VS Code。

1. 按照 [VS Code 遠端開發使用 SSH 文檔](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn) 的說明安裝所需組件。

1. 按照相同的說明，將 VS Code 連接到樹莓派。

1. 連接後，按照 [管理擴展](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn) 的說明，將 [Pylance 擴展](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance) 遠端安裝到樹莓派上。

## Hello world
通常在學習一種新的程式語言或技術時，會先建立一個「Hello World」應用程式——一個小型應用程式，輸出類似於 `"Hello World"` 的文字，以確認所有工具已正確配置。

針對樹莓派的 Hello World 應用程式將確保您已正確安裝 Python 和 Visual Studio Code。

此應用程式將存放在名為 `nightlight` 的資料夾中，稍後在此作業的其他部分中，將使用不同的程式碼來建立夜燈應用程式。

### 任務 - Hello World

建立 Hello World 應用程式。

1. 啟動 VS Code，可以直接在樹莓派上啟動，或者在您的電腦上啟動並使用 Remote SSH 擴展連接到樹莓派。

1. 透過選擇 *Terminal -> New Terminal* 或按下 `` CTRL+` `` 開啟 VS Code 終端機。終端機將開啟至 `pi` 使用者的主目錄。

1. 執行以下指令以建立程式碼的資料夾，並在該資料夾中建立一個名為 `app.py` 的 Python 檔案：

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. 在 VS Code 中開啟此資料夾，選擇 *File -> Open...*，然後選擇 *nightlight* 資料夾，接著選擇 **OK**。

    ![VS Code 開啟對話框顯示 nightlight 資料夾](../../../../../translated_images/mo/vscode-open-nightlight-remote.d3d2a4011e30d535.webp)

1. 從 VS Code 的檔案瀏覽器中開啟 `app.py` 檔案，並加入以下程式碼：

    ```python
    print('Hello World!')
    ```

    `print` 函數會將傳遞給它的內容輸出到終端機。

1. 從 VS Code 終端機執行以下指令以運行您的 Python 應用程式：

    ```sh
    python app.py
    ```

    > 💁 如果您的系統同時安裝了 Python 2 和 Python 3（最新版本），可能需要明確使用 `python3` 來執行此程式碼。若系統安裝了 Python 2，則執行 `python` 時會使用 Python 2 而非 Python 3。預設情況下，最新版本的 Raspberry Pi OS 只安裝了 Python 3。

    終端機中將出現以下輸出：

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 您可以在 [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi) 資料夾中找到此程式碼。

😀 您的「Hello World」程式成功了！

---

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。