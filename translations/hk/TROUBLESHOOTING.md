<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-05T17:40:44+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "hk"
}
-->
# 故障排除指南

本指南協助您解決在使用 IoT for Beginners 課程時常見的問題。問題依類別組織，便於瀏覽。

## 目錄

- [安裝問題](../..)
  - [Python 安裝](../..)
  - [VS Code 與擴充功能](../..)
  - [PlatformIO（Wio Terminal）](../..)
  - [Grove 函式庫](../..)
- [硬件問題](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [虛擬設備（CounterFit）](../..)
- [連線問題](../..)
  - [WiFi 連線](../..)
  - [雲端服務](../..)
  - [MQTT](../..)
- [感測器與致動器問題](../..)
  - [Grove 感測器](../..)
  - [相機](../..)
  - [麥克風與揚聲器](../..)
- [開發環境問題](../..)
  - [VS Code](../..)
  - [Python 虛擬環境](../..)
  - [相依性](../..)
- [效能問題](../..)
- [常見錯誤訊息](../..)
- [取得協助](../..)

---

## 安裝問題

### Python 安裝

#### 問題：Python 版本太舊
**錯誤：** `需要 Python 3.6 或以上版本`

**解決方法：**
1. 從 [python.org](https://www.python.org/downloads/) 下載最新 Python 3
2. 在 Windows 安裝時，勾選「Add Python to PATH」
3. 驗證安裝：
   ```bash
   python3 --version
   ```

#### 問題：多個 Python 版本衝突
**症狀：** 執行錯誤版本的 Python，套件安裝到錯誤的位置

**解決方法：**
- **Windows：** 使用 `py -3` 明確呼叫 Python 3，而非 `python`
- **macOS/Linux：** 使用 `python3` 替代 `python`
- 專案始終建立並使用虛擬環境

#### 問題：找不到 pip 指令
**錯誤：** `'pip' 不是內部或外部命令，也不是可執行的程式或批次檔`

**解決方法：**
1. 嘗試使用 `pip3` 替代 `pip`
2. 或使用 `python -m pip` 或 `python3 -m pip`
3. 確保 Python 已加入 PATH（重新安裝 Python 並勾選選項）

### VS Code 與擴充功能

#### 問題：Pylance 擴充功能無法使用
**症狀：** 無 Python IntelliSense、程式碼補全或型別檢查

**解決方法：**
1. 開啟 VS Code 命令面板（`Ctrl+Shift+P` 或 `Cmd+Shift+P`）
2. 執行「Python: Select Interpreter」
3. 選擇正確的 Python 解譯器（若使用虛擬環境，選擇該環境）
4. 重新載入 VS Code 視窗

#### 問題：VS Code 無法偵測虛擬環境
**症狀：** 選擇了錯誤的 Python 解譯器

**解決方法：**
1. 確保在終端機已啟動虛擬環境
2. 開啟命令面板，執行「Python: Select Interpreter」
3. 選擇 `.venv` 資料夾中的解譯器
4. 查看狀態列（左下角）顯示正確的 Python 版本

### PlatformIO（Wio Terminal）

#### 問題：PlatformIO 安裝失敗
**錯誤：** PlatformIO 安裝過程中出現各種錯誤

**解決方法：**
1. 確保 VS Code 更新至最新版本
2. 先安裝 C/C++ 擴充功能
3. 安裝 PlatformIO 後重啟 VS Code
4. 檢查網路連線（PlatformIO 需下載大型檔案）

#### 問題：PlatformIO 無法偵測開發板
**症狀：** 無法上傳程式碼至 Wio Terminal

**解決方法：**
1. 嘗試更換 USB 線（部分線材僅能充電）
2. 在 Windows 檢查裝置管理員，macOS/Linux 執行 `ls /dev/tty*`
3. 安裝或更新 USB 驅動程式
4. 更換 USB 埠
5. 快速滑動 Wio Terminal 電源開關兩次以進入 bootloader 模式

#### 問題：PlatformIO 編譯錯誤
**錯誤：** `fatal error: Arduino.h: No such file or directory`

**解決方法：**
1. 刪除專案中的 `.pio` 資料夾
2. 從命令面板執行「PlatformIO: Rebuild」
3. 確認 `platformio.ini` 有正確的開發板設定：
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove 函式庫

#### 問題：Grove 函式庫在 Raspberry Pi 上導入失敗
**錯誤：** `ModuleNotFoundError: No module named 'grove'`

**解決方法：**
1. 重新安裝 Grove 函式庫：
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. 若使用虛擬環境，可能需全域安裝或複製函式庫
3. 確認 I2C 已啟用：`sudo raspi-config nonint do_i2c 0`

#### 問題：Grove 感測器無法偵測
**錯誤：** `IOError: [Errno 121] Remote I/O error`

**解決方法：**
1. 檢查實體連接（確保 Grove 線纜完全插入）
2. 確認感測器接至正確埠口（類比、數位、I2C、UART）
3. 執行 `i2cdetect -y 1`，確認 I2C 匯流排上有裝置
4. 換用另一條 Grove 線纜嘗試
5. 確保 Grove Base Hat 與 Raspberry Pi GPIO 腳位良好連接

---

## 硬件問題

### Raspberry Pi

#### 問題：Raspberry Pi 無法開機
**症狀：** 無畫面、LED 無反應，或出現彩虹畫面

**解決方法：**
1. **檢查電源供應器：** Pi 4 使用官方 5V 3A USB-C 電源供應器
2. **SD 卡問題：**
   - 重新格式化 SD 卡並重灌 Raspberry Pi OS
   - 更換不同 SD 卡（使用推薦品牌）
   - 確認 SD 卡已正確插入
3. **檢查 HDMI 連接：** 試用 Pi 4 兩個 HDMI 埠，建議使用靠近電源的 HDMI 埠

#### 問題：無法 SSH 連線至 Raspberry Pi
**症狀：** 連線被拒或逾時

**解決方法：**
1. 啟用 SSH：
   - 使用 Raspberry Pi Imager 寫入 SD 卡時，在進階選項中設定 SSH
   - 或在開機分割區建立名為 `ssh`（無副檔名）的空檔案
2. 找出 Pi 的 IP 位址：
   - 檢查路由器連線裝置列表
   - 使用 `ping raspberrypi.local`（若 mDNS 有作用）
   - 使用 `nmap` 或 Angry IP Scanner 等網路掃描工具
3. 檢查網路：
   - 確認 Pi 與電腦在同一網路中
   - 優先嘗試有線以太網，避免使用 WiFi
4. 確認使用者名稱與密碼（預設：使用者名稱 `pi`，密碼 `raspberry`）

#### 問題：Grove Base Hat 無法被辨識
**症狀：** 感測器無法運作，出現 I2C 錯誤

**解決方法：**
1. 確保 Base Hat 平穩安裝在所有 GPIO 腳位上
2. 檢查 Pi 或 Base Hat 腳位是否彎曲
3. 啟用 I2C 介面：
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. 驗證 I2C 功能：執行 `i2cdetect -y 1`

#### 問題：Raspberry Pi 運行緩慢
**症狀：** 使用者介面卡頓、反應遲鈍

**解決方法：**
1. 檢查 SD 卡速度（使用 Class 10 或更新，或利用 USB 外接 SSD）
2. 釋放磁碟空間：執行 `df -h` 檢查，刪除不必要檔案
3. 若不頻繁使用相機或顯示器，降低 `raspi-config` 中的 GPU 記憶體
4. 關閉不必要的應用程式
5. 若使用 Pi 3 或更舊版本，可考慮升級至記憶體更多的 Pi 4

### Wio Terminal

#### 問題：Wio Terminal 螢幕保持空白
**症狀：** 上傳程式後無畫面輸出

**解決方法：**
1. 確認程式有初始化螢幕（使用 TFT_eSPI 函式庫）
2. 從 [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/) 更新 Wio Terminal 韌體
3. 加入螢幕初始化程式碼：
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. 嘗試從 PlatformIO 上傳範例程式測試硬體是否正常

#### 問題：Wio Terminal WiFi 無法連線
**症狀：** 無法連接 WiFi，出現網路錯誤

**解決方法：**
1. **更新 WiFi 韌體：** 參考 [Wio Terminal WiFi 韌體更新指南](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **檢查 WiFi 帳密：** 確認 SSID 與密碼正確
3. **WiFi 頻段：** Wio Terminal 僅支援 2.4GHz WiFi（不支援 5GHz）
4. **訊號強度：** 移動裝置靠近路由器
5. **路由器設定：** 部分企業/WPA-Enterprise 網路可能無法連接

#### 問題：電腦無法辨識 Wio Terminal
**症狀：** USB 裝置未偵測到

**解決方法：**
1. **嘗試不同 USB 線材：** 使用支援資料傳輸的線材，非僅充電線
2. **進入 bootloader 模式：** 快速向下滑動電源開關兩次
   - 藍燈閃爍，裝置在裝置管理員顯示為「Arduino」
3. **安裝驅動程式（Windows）：**
   - 下載並安裝 [Seeed USB 驅動程式](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **更換 USB 埠：** 避免使用 USB 集線器，使用直連
5. 更新系統 USB 驅動程式

#### 問題：Wio Terminal 感測器無法讀取資料
**症狀：** Grove 感測器無回應

**解決方法：**
1. 檢查 Grove 線纜連接
2. 確認使用正確的 Grove 埠（左邊或右邊）
3. 載入相應感測器函式庫
4. 檢查感測器電源需求
5. 使用函式庫範例程式測試感測器

### 虛擬設備（CounterFit）

#### 問題：CounterFit 應用程式無法啟動
**錯誤：** 啟動 CounterFit 時出現各種 Python 錯誤

**解決方法：**
1. 確保虛擬環境已啟動
2. 安裝或重新安裝 CounterFit：
   ```bash
   pip install CounterFit
   ```
3. 檢查埠號 5000 是否已被佔用：
   - Windows：`netstat -ano | findstr :5000`
   - macOS/Linux：`lsof -i :5000`
4. 停止佔用 5000 埠的程序，或使用不同埠號：
   ```bash
   counterfit --port 5001
   ```

#### 問題：無法從程式連接至 CounterFit
**錯誤：** 連線被拒或逾時

**解決方法：**
1. 確認 CounterFit 正在執行：瀏覽器開啟 `http://127.0.0.1:5000`
2. 檢查程式中連接的 URL 是否與 CounterFit 位址相符
3. 確認防火牆未阻擋連線
4. 嘗試重新啟動 CounterFit 和您的程式

#### 問題：CounterFit 中感測器未出現
**症狀：** 創建的感測器未出現在 CounterFit UI

**解決方法：**
1. 先在 CounterFit UI 創建感測器再執行程式
2. 刷新瀏覽器頁面
3. 確認感測器類型與程式預期相符
4. 清除瀏覽器快取

---

## 連線問題

### WiFi 連線

#### 問題：裝置無法連接 WiFi
**症狀：** 連線逾時、驗證失敗

**解決方法：**
1. **檢查 SSID 與密碼：** 確認憑證正確
2. **WiFi 頻段：** 多數 IoT 裝置僅支援 2.4GHz（不支援 5GHz）
3. **路由器設定：**
   - 若啟用 AP 隔離，請關閉
   - 使用 WPA2-PSK 安全性（避免 WPA3、WEP 或開放網路）
   - 確保 DHCP 啟用
4. **隱藏網路：** 若 SSID 隱藏，可能須明確設定連線
5. **訊號強度：** 將裝置移近路由器
6. **干擾：** 其他裝置、微波爐或牆壁可能產生干擾

#### 問題：WiFi 連線頻繁中斷
**症狀：** 連線斷斷續續

**解決方法：**
1. 檢查路由器穩定性，考慮重啟
2. 更新裝置韌體
3. 使用靜態 IP 取代 DHCP
4. 縮短距離至路由器或增加 WiFi 延伸器
5. 檢查其他裝置的干擾情況
6. 確認電源供應足夠（尤其是 Raspberry Pi）

### 雲端服務

#### 問題：無法連接 Azure IoT Hub
**錯誤：** 驗證失敗，連線被拒

**解決方法：**
1. **核對憑證：**
   - 確認連線字串正確無誤
   - 確認連線字串中無多餘空格或換行
2. **檢查裝置註冊：** 裝置必須已在 IoT Hub 中註冊
3. **防火牆/代理：** 確保允許出站 MQTT 埠（8883）或 HTTPS 埠（443）
4. **IoT Hub 地區：** 確認 IoT Hub 正常運作，且非因區域不同導致延遲
5. **配額限制：** 檢查是否超過免費方案限制
6. **測試連線：**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### 問題：Azure Functions 未啟動
**症狀：** 訊息已送達但函數未執行

**解決方法：**
1. 檢查函數應用程式是否運行（非停止狀態）
2. 確認函數應用程式設定中的連線字串
3. 查看 Azure Portal 中函數日誌
4. 確保已正確設定 Event Hub 相容端點
5. 驗證訊息格式符合函數預期
6. 檢查函數應用服務方案（消耗計算或專用）

### MQTT
#### 問題：MQTT 連線失敗  
**錯誤：** 連線被拒絕，驗證失敗

**解決方案：**  
1. **Broker 地址：** 驗證 broker URL/IP 是否正確  
2. **埠號：** 檢查埠號（未加密用 1883，TLS 用 8883）  
3. **驗證：** 如有需要，確認使用者名稱/密碼  
4. **TLS/SSL：** 確保憑證有效並受信任  
5. **防火牆：** 檢查埠號是否被封鎖  
6. **使用 MQTT 用戶端測試：** 使用 MQTT Explorer 或 mosquitto_pub/sub 進行測試

#### 問題：MQTT 訊息未接收  
**症狀：** 已發布訊息但訂閱者未收到

**解決方案：**  
1. **主題名稱：** 確認訂閱者主題與發布者主題完全相符  
2. **QoS 等級：** 嘗試 QoS 1 或 2 替代 0  
3. **萬用字元：** 檢查主題萬用字元使用是否正確（`+` 表單層，`#` 表多層）  
4. **保留訊息：** 發布者可設定 retain 標記保留最後訊息  
5. **連線時機：** 確保訂閱者在訊息發布前已連線

---

## 感測器與執行器問題

### Grove 感測器

#### 問題：感測器回傳錯誤數值  
**症狀：** 讀值為 0、-1，或不合理數值

**解決方案：**  
1. **檢查連線：** 確保感測器正確連接  
2. **正確埠口：** 確認感測器接到正確埠口類型：  
   - 類比感測器 → 類比埠（A0, A2, A4）  
   - 數位感測器 → 數位埠（D5, D16, D18 等）  
   - I2C 感測器 → I2C 埠  
3. **校正：** 某些感測器需校正（土壤濕度、光感）  
4. **電源重啟：** 將感測器斷電再重新接上  
5. **感測器規格表：** 查閱感測器規格與需求

#### 問題：電容式土壤濕度感測器永遠顯示濕潤  
**症狀：** 感測器即使乾燥也顯示高濕度

**解決方案：**  
1. **需校正：** 土壤感測器校正步驟：  
   - 讀取空氣中值（乾燥基準）  
   - 讀取水中值（濕潤基準）  
   - 將讀值對應於這兩值之間  
2. **檢查感測器塗層：** 濕度感測器若塗層受損會退化  
3. **放置方式：** 確保感測器完全插入土中

#### 問題：溫濕度感測器讀數不正確  
**症狀：** DHT11/DHT22 顯示錯誤溫度或濕度

**解決方案：**  
1. **感測器放置：** 避免直射陽光、熱源或氣流  
2. **暖機時間：** 電源開啟後等待 2 秒再讀取  
3. **讀取頻率：** DHT 感測器讀取間隔需至少 2 秒  
4. **檢查冷凝水：** 冷凝水會影響讀取  
5. **感測器品質：** DHT11 精度不及 DHT22

### 攝影機

#### 問題：Raspberry Pi 無法辨識攝影機  
**錯誤：** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**解決方案：**  
1. **啟用攝影機介面：**  
   ```bash
   sudo raspi-config
   ```
   前往 Interface Options → Camera → Enable  
2. **檢查排線：** 確保攝影機排線正確插入  
   - Pi Zero 藍色面朝 USB 埠  
   - Pi 4 藍色面背向 USB 埠  
3. **更新韌體：**  
   ```bash
   sudo apt update
   sudo apt full-upgrade
   sudo reboot
   ```
4. **測試攝影機：**  
   ```bash
   raspistill -o test.jpg
   ```


#### 問題：攝影機影像品質差  
**症狀：** 模糊、過暗或曝光不足的影像

**解決方案：**  
1. **對焦：** 移除鏡頭保護膜，若可調整則調整焦距  
2. **照明：** 確保光源充足  
3. **攝影機設定：** 調整曝光、ISO、白平衡參數  
4. **穩定性：** 攝影機要穩固，必要時用三腳架  
5. **解析度：** 不要超出攝影機最高解析度

### 麥克風與喇叭

#### 問題：無音訊輸入/輸出  
**症狀：** 麥克風無聲音錄製，喇叭無播放聲

**解決方案：**  
1. **檢查連接：** 確認音訊裝置正確接好  
2. **硬體測試：**  
   - 喇叭：`speaker-test -t wav -c 2`  
   - 麥克風：`arecord -l` 列出裝置，`arecord test.wav` 錄音  
3. **音量設定：** 調整及檢查音量：  
   ```bash
   alsamixer
   ```
4. **選擇音訊裝置：** 程式中指定正確音訊裝置  
5. **驅動程式問題：** 更新 ALSA 或重新安裝音訊驅動

#### 問題：ReSpeaker 擴充板無反應  
**症狀：** 音訊裝置無法偵測

**解決方案：**  
1. **安裝驅動：**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **檢查安裝：** `arecord -l` 應列出 ReSpeaker 裝置  
3. **更新韌體：** 有些 Pi OS 版本需更新驅動  
4. **檢查接合：** 確保擴充板正確接上 GPIO 腳位

---

## 開發環境問題

### VS Code

#### 問題：終端機未自動啟動虛擬環境  
**症狀：** 終端機開啟但未啟用 venv

**解決方案：**  
1. **設定 Python 解譯器：** 命令面板 → "Python: Select Interpreter" → 選擇 venv  
2. 選擇解譯器後重新啟動 VS Code  
3. 確認設定檔 `settings.json` 加入：  
   ```json
   "python.terminal.activateEnvironment": true
   ```


#### 問題：程式碼執行無反應於設備上  
**症狀：** 程式碼有執行但設備無任何反應

**解決方案：**  
1. 確認程式已儲存（檔案頁籤有點標示）  
2. 檢查執行的 Python 版本：`which python` 或 `where python`  
3. Wio Terminal 確保使用 PlatformIO 上傳程式（點擊上傳鍵）  
4. Raspberry Pi 請 SSH 登入 Pi 後執行程式碼  
5. 檢查輸出視窗是否有錯誤訊息

#### 問題：IntelliSense 無法顯示函式庫功能  
**症狀：** 匯入模組無自動補全

**解決方案：**  
1. 確保函式庫已安裝於當前環境  
2. 重新載入 VS Code 視窗  
3. 確認 Python 解譯器正確  
4. 若有，安裝類型定義檔（type stubs）：`pip install types-<library-name>`

### Python 虛擬環境

#### 問題：無法建立虛擬環境  
**錯誤：** `The virtual environment was not created successfully`

**解決方案：**  
1. **安裝 venv 模組：**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Python 內建包含  
   - Windows: 重新安裝包含所有元件的 Python  
2. **檢查 Python 安裝：** 確認 Python 安裝完整  
3. **使用完整路徑建立：** `python3 -m venv .venv`

#### 問題：套件安裝在錯誤位置  
**症狀：** 安裝套件後匯入錯誤

**解決方案：**  
1. 確認 venv 已啟用，命令提示字元顯示 `(.venv)`  
2. 檢查 pip 路徑：`which pip` 顯示 `.venv/bin/pip`  
3. 啟用 venv 後重新安裝套件：`pip install <package>`  
4. 不要在虛擬環境內使用 sudo

#### 問題：虛擬環境無法攜帶  
**症狀：** 移動或在不同電腦使用 venv 異常

**解決方案：**  
1. 不要移動已有的 venv，刪除後重新建立  
2. 使用 requirements.txt：  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. 重新建立 venv：  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # 或在 Windows 上執行 activate.bat
   pip install -r requirements.txt
   ```


### 相依套件問題

#### 問題：套件安裝失敗  
**錯誤：** 安裝時出現多種 pip 錯誤

**解決方案：**  
1. 更新 pip：  
   ```bash
   pip install --upgrade pip
   ```
2. 安裝建置工具：  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: 安裝 Visual Studio Build Tools  
3. 確認網路連線正常  
4. 嘗試使用不同套件索引：`pip install --index-url https://pypi.org/simple/ <package>`  
5. 安裝特定版本：`pip install <package>==<version>`

#### 問題：相依套件衝突  
**錯誤：** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**解決方案：**  
1. 每個專案使用新的虛擬環境  
2. 更新套件：`pip install --upgrade <package>`  
3. 檢查相依衝突：使用 `pip check`  
4. 指定相容版本範圍於 requirements.txt

---

## 效能問題

### 問題：程式執行緩慢  
**症狀：** 延遲、逾時、無反應

**解決方案：**  
1. 降低感測器讀取頻率，不要讀太頻繁  
2. 優化迴圈，避免忙等，使用 sleep() 或延遲  
3. 記憶體問題：  
   - 關閉不必要的應用程式  
   - 釋放儲存空間  
   - 用 `top` 或 `htop` 監控 Raspberry Pi  
4. SD 卡速度：使用較快的 SD 卡或 SSD  
5. 網路延遲：使用非同步操作處理網路呼叫

### 問題：記憶體不足錯誤  
**錯誤：** `MemoryError` 或系統凍結

**解決方案：**  
1. Raspberry Pi：  
   - 關閉不必要應用程式  
   - 增加 swap 空間  
   - 使用精簡版作業系統（Lite 版）  
   - 升級記憶體（Pi 4 可選 2/4/8GB）  
2. Wio Terminal：  
   - 減少緩衝區大小  
   - 使用較小圖片  
   - 優化字串使用  
   - 檢查是否有記憶體洩漏（未釋放記憶體）

### 問題：資料遺失或損壞  
**症狀：** 訊息遺失，檔案損壞

**解決方案：**  
1. SD 卡問題：  
   - 使用品質良好的 SD 卡（避免廉價/仿冒品）  
   - 定期備份  
   - 正確關機（勿直接斷電）  
2. 緩衝區溢位：增加程式緩衝區大小  
3. 網路穩定性：實作重試邏輯與錯誤處理  
4. 服務品質：重要訊息使用 MQTT QoS 1 或 2

---

## 常見錯誤訊息

### `ModuleNotFoundError: No module named 'X'`  
**原因：** 套件未安裝或虛擬環境未啟用

**解決方案：**  
```bash
pip install X
```
  
請先啟用虛擬環境。

### Linux/macOS 出現 `Permission denied`  
**原因：** 權限不足或檔案權限設定問題

**解決方案：**  
- 做系統操作使用 `sudo`  
- pip 安裝時不要用 sudo，在 venv 啟用後執行  
- 針對序列埠加使用者至 dialout 群組：`sudo usermod -a -G dialout $USER`，然後登出再登入

### `OSError: [Errno 98] Address already in use`  
**原因：** 埠口已被其他程序佔用

**解決方案：**  
1. 找出使用該埠的程序：`lsof -i :<port>` 或 `netstat -ano | findstr :<port>`  
2. 終止該程序或程式中使用不同埠號

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**原因：** SSL 憑證驗證失敗

**解決方案：**  
1. 更新憑證：`pip install --upgrade certifi`  
2. 檢查系統時間是否正確：`date`  
3. 只限開發用途（非正式環境）：可在程式碼中關閉驗證

### `IndentationError: unexpected indent`  
**原因：** Python 縮排錯誤（混用 tab 與空白）

**解決方案：**  
1. 使用一致縮排（Python 標準為 4 個空白）  
2. 編輯器設定改用空白代替 Tab  
3. VS Code 設定 `"editor.insertSpaces": true` 及 `"editor.tabSize": 4`

### `UnicodeDecodeError` 或 `UnicodeEncodeError`  
**原因：** 字元編碼問題

**解決方案：**  
```python
# 當讀取檔案時
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# 當寫入檔案時
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```


---

## 尋求協助

若嘗試以上排除步驟後仍有問題：

### 1. 檢查現有資源  
- **文件說明：** 閱讀 [README](README.md) 與課程指示  
- **硬體指南：** 查看 [hardware.md](hardware.md) 中硬體相關訊息  
- **Seeed Studio Wiki：** 查閱 [Seeed Studio Wiki](https://wiki.seeedstudio.com/) 相關 Grove 產品資訊

### 2. 搜尋相似問題  
- **GitHub Issues：** 搜尋已有 [issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow：** 尋找錯誤訊息相關內容  
- **裝置論壇：** 查詢 Raspberry Pi 論壇或 Arduino 論壇

### 3. 建立 GitHub Issue  
若找不到解法：  
1. 前往 [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. 點選「New Issue」  
3. 提供：  
   - 清楚問題描述  
   - 重現步驟  
   - 錯誤訊息（完整文字）  
   - 硬體/軟體版本  
   - 已嘗試過的排除方式  
   - 相關截圖（如有）

### 4. 加入社群  
- **Discord：** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn：** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. 提供完善的錯誤回報  
完善的錯誤回報包括：
- **環境：** 作業系統、Python 版本、使用的硬件  
- **重現步驟：** 造成問題的確切步驟  
- **預期行為：** 應該發生的情況  
- **實際行為：** 實際發生的情況  
- **錯誤訊息：** 完整的錯誤文字，不要截圖  
- **程式碼：** 能重現問題的最簡程式範例

---

## 預防建議

### 一般最佳實務
1. **保持備份：** 定期備份可正常運作的 SD 卡/程式碼  
2. **紀錄變更：** 在註解中標明哪些有效  
3. **版本控制：** 使用 git 追蹤程式碼變動  
4. **逐步測試：** 先測試小變更再合併  
5. **閱讀錯誤訊息：** 它們通常會告訴你問題所在  
6. **定期更新：** 保持軟體／韌體最新  
7. **使用優質零件：** 避免使用便宜線材／電源供應器  
8. **電力穩定：** 使用合適的電源供應（尤其是 Pi）

### 開發工作流程
1. **從簡單開始：** 從可用的範例程式開始  
2. **一次只改一件事：** 較容易找到出問題的地方  
3. **頻繁測試：** 及早發現問題  
4. **保持整潔：** 有條理組織檔案與程式碼  
5. **註解程式碼：** 未來的你會感激

---

*此故障排除指南由社群維護。如果您找到此處未列出問題的解決方案，請考慮[貢獻](CONTRIBUTING.md)幫助更多人！*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**免責聲明**：
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於確保翻譯的準確性，但請注意自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要資訊，建議使用專業人工翻譯。我們不對因使用本翻譯而產生的任何誤解或曲解承擔責任。
<!-- CO-OP TRANSLATOR DISCLAIMER END -->