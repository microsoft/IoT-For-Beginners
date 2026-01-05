<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-05T17:44:02+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "tw"
}
-->
# 疑難排解指南

本指南幫助您解決使用 IoT for Beginners 課程時常見的問題。問題依類別組織，方便快速瀏覽。

## 目錄

- [安裝問題](../..)
  - [Python 安裝](../..)
  - [VS Code 與擴充套件](../..)
  - [PlatformIO（Wio Terminal）](../..)
  - [Grove 程式庫](../..)
- [硬體問題](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [虛擬裝置（CounterFit）](../..)
- [連線問題](../..)
  - [WiFi 連線](../..)
  - [雲端服務](../..)
  - [MQTT](../..)
- [感測器與致動器問題](../..)
  - [Grove 感測器](../..)
  - [相機](../..)
  - [麥克風與喇叭](../..)
- [開發環境問題](../..)
  - [VS Code](../..)
  - [Python 虛擬環境](../..)
  - [相依套件](../..)
- [效能問題](../..)
- [常見錯誤訊息](../..)
- [尋求幫助](../..)

---

## 安裝問題

### Python 安裝

#### 問題：Python 版本過舊
**錯誤：** `Python 3.6 或以上版本為必須`

**解決方案：**
1. 從 [python.org](https://www.python.org/downloads/) 下載最新的 Python 3
2. Windows 安裝時，勾選「Add Python to PATH」
3. 驗證安裝：
   ```bash
   python3 --version
   ```

#### 問題：多個 Python 版本造成衝突
**症狀：** 執行錯誤的 Python 版本，套件安裝到錯誤位置

**解決方案：**
- **Windows：** 使用 `py -3` 取代 `python` 明確呼叫 Python 3
- **macOS/Linux：** 使用 `python3` 代替 `python`
- 專案務必建立並使用虛擬環境

#### 問題：找不到 pip 指令
**錯誤：** `'pip' 不是內部或外部命令，也不是可執行的程式或批次檔`

**解決方案：**
1. 嘗試使用 `pip3` 代替 `pip`
2. 或使用 `python -m pip` 或 `python3 -m pip`
3. 確認 Python 已加入 PATH（重新安裝 Python 並勾選此選項）

### VS Code 與擴充套件

#### 問題：Pylance 擴充套件不工作
**症狀：** 沒有 Python 的 IntelliSense、程式碼完成或型別檢查

**解決方案：**
1. 開啟 VS Code 指令面板（`Ctrl+Shift+P` 或 `Cmd+Shift+P`）
2. 執行 "Python: Select Interpreter"
3. 選擇正確的 Python 直譯器（若使用虛擬環境，選擇該環境）
4. 重新載入 VS Code 視窗

#### 問題：VS Code 無法偵測虛擬環境
**症狀：** 選擇錯誤的 Python 直譯器

**解決方案：**
1. 確認已在終端機啟用虛擬環境
2. 開啟指令面板並執行 "Python: Select Interpreter"
3. 選擇 `.venv` 資料夾內的直譯器
4. 檢查狀態列（左下角）顯示正確的 Python 版本

### PlatformIO（Wio Terminal）

#### 問題：PlatformIO 安裝失敗
**錯誤：** PlatformIO 安裝時出現多種錯誤

**解決方案：**
1. 確認 VS Code 已更新至最新版
2. 先安裝 C/C++ 擴充套件
3. 安裝 PlatformIO 後重新啟動 VS Code
4. 確認網路連線（PlatformIO 需下載大型檔案）

#### 問題：PlatformIO 找不到開發板
**症狀：** 無法將程式上傳至 Wio Terminal

**解決方案：**
1. 嘗試更換 USB 線（有些線僅支援充電）
2. 檢查裝置管理員（Windows）或用 `ls /dev/tty*`（macOS/Linux）
3. 安裝或更新 USB 驅動程式
4. 嘗試不同的 USB 連接埠
5. 將 Wio Terminal 電源開關滑動兩次快速進入 bootloader 模式

#### 問題：PlatformIO 編譯錯誤
**錯誤：** `fatal error: Arduino.h: No such file or directory`

**解決方案：**
1. 刪除專案中的 `.pio` 資料夾
2. 從指令面板執行 "PlatformIO: Rebuild"
3. 確認 `platformio.ini` 中板子設定正確：
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove 程式庫

#### 問題：Raspberry Pi 上 Grove 程式庫匯入失敗
**錯誤：** `ModuleNotFoundError: No module named 'grove'`

**解決方案：**
1. 重新安裝 Grove 程式庫：
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. 若使用虛擬環境，可能需要全球安裝或複製程式庫
3. 確認已啟用 I2C：`sudo raspi-config nonint do_i2c 0`

#### 問題：Grove 感測器無法偵測
**錯誤：** `IOError: [Errno 121] Remote I/O error`

**解決方案：**
1. 檢查實體連接（確認 Grove 線纜完全插入）
2. 確認感測器連接到正確的連接埠（類比、數位、I2C、UART）
3. 執行 `i2cdetect -y 1` 看是否能在 I2C 匯流排上看到裝置
4. 嘗試更換 Grove 線纜
5. 確保 Grove Base Hat 正確插在 Raspberry Pi GPIO 頂針上

---

## 硬體問題

### Raspberry Pi

#### 問題：Raspberry Pi 無法開機
**症狀：** 沒有顯示、LED 不亮或出現彩虹畫面

**解決方案：**
1. **檢查電源供應器：** Pi 4 建議使用官方 5V 3A USB-C 電源
2. **SD 卡問題：** 
   - 重新格式化 SD 卡並重新安裝 Raspberry Pi OS
   - 嘗試其他 SD 卡（建議使用知名品牌）
   - 確保 SD 卡正確插入
3. **檢查 HDMI 連接：** 嘗試 Pi 4 上的兩個 HDMI 埠，用接近電源的 HDMI 埠

#### 問題：無法 SSH 連線至 Raspberry Pi
**症狀：** 連線被拒或逾時

**解決方案：**
1. 啟用 SSH：
   - 使用 Raspberry Pi Imager 寫入 SD 卡時，在進階選項開啟 SSH
   - 或在啟動磁區建立一個名為 `ssh`（無副檔名）的空檔案
2. 找到 Pi 的 IP 位址：
   - 檢查路由器的連線裝置列表
   - 使用 `ping raspberrypi.local`（若 mDNS 有效）
   - 使用網路掃描工具如 `nmap` 或 Angry IP Scanner
3. 檢查網路：
   - 確認 Pi 與電腦同網段
   - 改用乙太網路連線取代 WiFi
4. 確認帳號密碼（預設使用者為 `pi`，密碼為 `raspberry`）

#### 問題：Grove Base Hat 無法被辨識
**症狀：** 感測器不正常、I2C 發生錯誤

**解決方案：**
1. 確保 Base Hat 完全接合所有 GPIO 頂針
2. 檢查 Pi 和 Base Hat 是否有彎曲的頂針
3. 啟用 I2C 介面：
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. 確認 I2C 是否正常運作：`i2cdetect -y 1`

#### 問題：Raspberry Pi 執行緩慢
**症狀：** 介面卡頓、反應遲鈍

**解決方案：**
1. 檢查 SD 卡速度（建議使用 Class 10 或以上，或 USB 外接 SSD）
2. 釋放磁碟空間：用 `df -h` 檢查，刪除不必要的檔案
3. 在 `raspi-config` 減少 GPU 記憶體配置（若不大量使用相機或顯示器）
4. 關閉不必要的程式
5. 若使用 Pi 3 或更舊版本，可考慮升級至擁有更多 RAM 的 Pi 4

### Wio Terminal

#### 問題：Wio Terminal 螢幕一直黑屏
**症狀：** 上傳程式後沒有顯示輸出

**解決方案：**
1. 確認程式有初始化顯示器（使用 TFT_eSPI 程式庫）
2. 從 [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/) 更新 Wio Terminal 韌體
3. 加入顯示初始化程式碼：
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. 嘗試由 PlatformIO 上傳範例程式測試硬體

#### 問題：Wio Terminal 無法連接 WiFi
**症狀：** 無法連接 WiFi，發生網路錯誤

**解決方案：**
1. **更新 WiFi 韌體：** 參考 [Wio Terminal WiFi 韌體更新指南](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **檢查 WiFi 帳密：** 確認 SSID 與密碼正確
3. **WiFi 頻段：** Wio Terminal 只支援 2.4GHz WiFi（不支援 5GHz）
4. **訊號強度：** 靠近路由器
5. **路由器設定：** 部分企業/ WPA-Enterprise 網路可能不相容

#### 問題：電腦無法辨識 Wio Terminal
**症狀：** USB 裝置未被偵測

**解決方案：**
1. **嘗試不同 USB 線：** 使用具備資料傳輸功能的線材，非充電線
2. **進入 bootloader 模式：** 快速滑動電源開關兩次
   - 藍色 LED 應該會閃爍，裝置在裝置管理員顯示為「Arduino」
3. **安裝驅動程式（Windows）：**
   - 下載並安裝 [Seeed USB 驅動程式](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **嘗試不同 USB 埠：** 避免使用集線器，改用主機板直連
5. **更新系統 USB 驅動程式**

#### 問題：Wio Terminal 上感測器無法運作
**症狀：** Grove 感測器無法讀取資料

**解決方案：**
1. 檢查 Grove 線纜連接
2. 確認使用正確的 Grove 連接埠（左側或右側）
3. 引入正確的感測器程式庫
4. 檢查感測器電源需求
5. 用程式庫中的範例程式測試感測器

### 虛擬裝置（CounterFit）

#### 問題：CounterFit 應用程式無法啟動
**錯誤：** 啟動 CounterFit 時出現各種 Python 錯誤

**解決方案：**
1. 確認虛擬環境已啟用
2. 安裝或重新安裝 CounterFit：
   ```bash
   pip install CounterFit
   ```
3. 檢查埠號 5000 是否已被使用：
   - Windows: `netstat -ano | findstr :5000`
   - macOS/Linux: `lsof -i :5000`
4. 終止佔用埠號 5000 的進程或使用其他埠號：
   ```bash
   counterfit --port 5001
   ```

#### 問題：程式無法連接 CounterFit
**錯誤：** 連線被拒或逾時

**解決方案：**
1. 確認 CounterFit 正在執行：於瀏覽器開啟 `http://127.0.0.1:5000`
2. 檢查程式中連線 URL 是否與 CounterFit 地址相符
3. 確認防火牆沒有封鎖連線
4. 重啟 CounterFit 應用程式與您的程式碼

#### 問題：感測器沒有顯示在 CounterFit
**症狀：** 建立的感測器未在 CounterFit UI 出現

**解決方案：**
1. 先在 CounterFit UI 創建感測器，再執行程式
2. 重新整理瀏覽器頁面
3. 確認感測器類型與程式預期相符
4. 清除瀏覽器快取

---

## 連線問題

### WiFi 連線

#### 問題：裝置無法連接 WiFi
**症狀：** 連線逾時，認證失敗

**解決方案：**
1. **檢查 SSID 與密碼：** 確認憑證正確無誤
2. **WiFi 頻段：** 多數 IoT 裝置僅支援 2.4GHz（不支援 5GHz）
3. **路由器設定：**
   - 若有啟用 AP 隔離請關閉
   - 使用 WPA2-PSK 安全性（避免 WPA3、WEP 或開放網路）
   - 確認 DHCP 啟用中
4. **隱藏網路：** 若 SSID 被隱藏，可能需在設定中明確輸入
5. **訊號強度：** 將裝置靠近路由器
6. **訊號干擾：** 其他裝置、微波爐或牆壁可能干擾訊號

#### 問題：WiFi 連線頻繁中斷
**症狀：** 斷斷續續連線

**解決方案：**
1. 檢查路由器穩定度，考慮重啟
2. 更新裝置韌體
3. 改用靜態 IP 代替 DHCP
4. 減少裝置與路由器距離或加裝 WiFi 延伸器
5. 檢查附近的干擾來源
6. 確認電源供應充足（尤其 Raspberry Pi）

### 雲端服務

#### 問題：無法連接 Azure IoT Hub
**錯誤：** 認證失敗、連線被拒

**解決方案：**
1. **驗證憑證：**
   - 確認連線字串正確無誤
   - 確保連線字串沒有額外空白或換行
2. **檢查裝置註冊：** 裝置必須已註冊於 IoT Hub
3. **防火牆/代理：** 確認允許出站 MQTT（埠號 8883）或 HTTPS（埠號 443）
4. **IoT Hub 地區：** 確認 IoT Hub 運作正常，且非不同地區造成延遲
5. **配額限制：** 檢查免費層數量是否已超過
6. **測試連線：**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### 問題：Azure Functions 未觸發
**症狀：** 訊息已傳送但函式未執行

**解決方案：**
1. 確認 Function App 正在運行（非停止狀態）
2. 驗證 Function App 設定中的連線字串
3. 檢查 Azure 入口網站上的函式日誌
4. 確認 Event Hub 相容端點設定正確
5. 驗證訊息格式符合函式期望
6. 檢查 Function App 的服務方案（消耗模式或專用）

### MQTT
#### 問題：MQTT 連線失敗  
**錯誤：** 連線被拒絕，驗證失敗  

**解決方案：**  
1. **Broker 地址：** 驗證 Broker 的 URL/IP 是否正確  
2. **連接埠：** 檢查連接埠號（非加密為 1883，TLS 為 8883）  
3. **驗證：** 若需要，確認使用者名稱/密碼  
4. **TLS/SSL：** 確保憑證有效且被信任  
5. **防火牆：** 確認連接埠未被封鎖  
6. **使用 MQTT 客戶端測試：** 使用 MQTT Explorer 或 mosquitto_pub/sub 進行測試  

#### 問題：未收到 MQTT 訊息  
**症狀：** 已發佈訊息但訂閱者未收到  

**解決方案：**  
1. **主題名稱：** 確認訂閱主題與發佈主題完全相符  
2. **QoS 等級：** 嘗試使用 QoS 1 或 2 代替 0  
3. **萬用字元：** 檢查主題萬用字元使用是否正確（`+` 表示單一層級，`#` 表示多層級）  
4. **保留訊息：** 發佈者可設置保留旗標以保留最後訊息  
5. **連線時機：** 確保訂閱者在訊息發佈前已連線  

---

## 感測器與執行元件問題  

### Grove 感測器  

#### 問題：感測器回傳錯誤值  
**症狀：** 讀值為 0、-1 或不合理值  

**解決方案：**  
1. **檢查接線：** 確保感測器連接正確  
2. **正確插槽：** 確認感測器接在正確的插槽類型：  
   - 類比感測器 → 類比插槽（A0、A2、A4）  
   - 數位感測器 → 數位插槽（D5、D16、D18 等）  
   - I2C 感測器 → I2C 插槽  
3. **校正：** 某些感測器需要校正（土壤濕度、光線等）  
4. **重新上電：** 斷開再重新連接感測器  
5. **感測器規格書：** 查閱感測器規格和需求  

#### 問題：電容式土壤濕度感測器總是顯示潮濕  
**症狀：** 感測器即使乾燥也顯示高濕度  

**解決方案：**  
1. **需要校正：** 土壤感測器需要校正：  
   - 在空氣（乾燥基線）測量數值  
   - 在水中（潮濕基線）測量數值  
   - 將讀數映射於該區間  
2. **檢查感測器塗層：** 若塗層破損，濕度感測器易劣化  
3. **安放位置：** 確保感測器完全插入土壤中  

#### 問題：溫濕度感測器讀值錯誤  
**症狀：** DHT11/DHT22 顯示錯誤溫度或濕度  

**解決方案：**  
1. **感測器放置：** 避免直射陽光、熱源或氣流  
2. **暖機時間：** 上電後等待約 2 秒再讀取  
3. **讀取頻率：** DHT 感測器間隔讀取時間需至少 2 秒  
4. **注意結露：** 可能影響讀取值  
5. **感測器品質：** DHT11 精度較 DHT22 低  

### 攝影機  

#### 問題：Raspberry Pi 無法偵測攝影機  
**錯誤：** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`  

**解決方案：**  
1. **啟用攝影機介面：**  
   ```bash
   sudo raspi-config
   ```
   前往介面選項 → 攝影機 → 啟用  
2. **檢查排線：** 確保攝影機排線正確插入  
   - Pi Zero 藍色面朝 USB 插槽  
   - Pi 4 藍色面背離 USB 插槽  
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
  
#### 問題：攝影機拍攝畫質差  
**症狀：** 影像模糊、過暗或過曝  

**解決方案：**  
1. **對焦：** 移除鏡頭保護膜，若可調焦則調整對焦  
2. **光線：** 確保光線充足  
3. **攝影機設定：** 在程式中調整曝光、ISO、白平衡  
4. **穩定性：** 保持攝影機穩定，必要時使用腳架  
5. **解析度：** 不要超過攝影機最大解析度  

### 麥克風與喇叭  

#### 問題：無音訊輸入/輸出  
**症狀：** 麥克風無法錄音，喇叭無聲音  

**解決方案：**  
1. **檢查接線：** 確認音訊設備連接正常  
2. **測試硬體：**  
   - 喇叭：`speaker-test -t wav -c 2`  
   - 麥克風：使用 `arecord -l` 列出裝置，`arecord test.wav` 錄音  
3. **音量設定：** 檢查並調整音量：  
   ```bash
   alsamixer
   ```
4. **選擇音訊裝置：** 程式中指定正確音訊裝置  
5. **驅動問題：** 更新 ALSA 或重新安裝音訊驅動  

#### 問題：ReSpeaker 擴充板無法運作  
**症狀：** 沒有偵測到音訊設備  

**解決方案：**  
1. **安裝驅動：**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **確認安裝狀況：** `arecord -l` 應列出 ReSpeaker  
3. **更新韌體：** 部分 Pi OS 版本需更新驅動  
4. **檢查安裝：** 確保擴充板正確插在 GPIO 腳位上  

---

## 開發環境問題  

### VS Code  

#### 問題：終端機未自動啟動虛擬環境  
**症狀：** 終端機開啟但未啟用 venv  

**解決方案：**  
1. **設置 Python 直譯器：** 命令面板 → "Python: Select Interpreter" → 選擇 venv  
2. 選擇後重新啟動 VS Code  
3. 檢查 `settings.json`，新增：  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### 問題：程式碼在裝置上無執行反應  
**症狀：** 程式執行，但裝置無任何反應  

**解決方案：**  
1. **確認程式碼已儲存**（檔案標籤是否有點示意未儲存）  
2. **檢查執行的 Python 版本：** `which python` 或 `where python`  
3. **針對 Wio Terminal:** 確保透過 PlatformIO 上傳程式（點擊上傳按鈕）  
4. **針對 Raspberry Pi:** SSH 連線 Pi 後執行程式  
5. 查看輸出視窗是否有錯誤訊息  

#### 問題：IntelliSense 不顯示函式自動完成  
**症狀：** 匯入模組後無自動補全  

**解決方案：**  
1. 確認函式庫已安裝於當前環境  
2. 重新載入 VS Code 視窗  
3. 檢查 Python 直譯器是否正確  
4. 若有，安裝型別定義：`pip install types-<library-name>`  

### Python 虛擬環境  

#### 問題：無法建立虛擬環境  
**錯誤：** `The virtual environment was not created successfully`  

**解決方案：**  
1. **安裝 venv 模組：**  
   - Ubuntu/Debian: `sudo apt install python3-venv`  
   - macOS: Python 通常已包含  
   - Windows: 重新安裝 Python 並包含所有元件  
2. **檢查 Python 安裝：** 確認 Python 安裝正確  
3. **使用完整路徑執行：** 嘗試 `python3 -m venv .venv`  

#### 問題：套件安裝到錯誤位置  
**症狀：** 安裝套件後匯入出錯  

**解決方案：**  
1. **確認 venv 已啟用：** 命令提示字元應顯示 `(.venv)`  
2. **檢查 pip 位置：** `which pip` 指向 `.venv/bin/pip`  
3. **在 venv 中重新安裝：** 啟用 venv 後 `pip install <package>`  
4. **勿在虛擬環境中用 sudo 執行 pip**  

#### 問題：虛擬環境不可攜帶移動  
**症狀：** 移動或在不同電腦使用後 venv 無法運作  

**解決方案：**  
1. **勿移動 venv：** 刪除後在新位置重新建立  
2. **使用 requirements.txt：**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **重新建立 venv：**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # 或在 Windows 上執行 activate.bat
   pip install -r requirements.txt
   ```
  

### 相依性問題  

#### 問題：套件安裝失敗  
**錯誤：** 安裝時出現各種 pip 錯誤  

**解決方案：**  
1. **更新 pip：**  
   ```bash
   pip install --upgrade pip
   ```
2. **安裝編譯工具：**  
   - Ubuntu/Debian: `sudo apt install build-essential python3-dev`  
   - macOS: `xcode-select --install`  
   - Windows: 安裝 Visual Studio Build Tools  
3. **檢查網路連線**  
4. **嘗試不同套件索引：** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **指定版本安裝：** `pip install <package>==<version>`  

#### 問題：相依衝突  
**錯誤：** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`  

**解決方案：**  
1. **為每個專案使用全新虛擬環境**  
2. **更新套件：** `pip install --upgrade <package>`  
3. **檢查套件相依：** 使用 `pip check` 找出衝突  
4. **安裝相容版本：** 在 requirements.txt 指定版本範圍  

---

## 效能問題  

### 問題：程式碼執行緩慢  
**症狀：** 延遲、逾時、無回應  

**解決方案：**  
1. **減少感測器讀取頻率：** 不要過度頻繁讀取  
2. **優化迴圈：** 避免忙等待，使用 sleep() 或延遲  
3. **記憶體問題：**  
   - 關閉不必要的應用程式  
   - 釋放儲存空間  
   - 在 Pi 用 `top` 或 `htop` 監控  
4. **SD 卡速度：** 使用更快的 SD 卡或 SSD 作為儲存  
5. **網路延遲：** 網路呼叫使用非同步作業  

### 問題：記憶體不足錯誤  
**錯誤：** `MemoryError` 或系統當機  

**解決方案：**  
1. **針對 Raspberry Pi：**  
   - 關閉不需要的應用程式  
   - 增加交換區  
   - 使用精簡版作業系統（Lite 版）  
   - 升級 RAM（Pi 4 有 2/4/8GB 選項）  
2. **針對 Wio Terminal：**  
   - 減小緩衝區大小  
   - 使用較小的影像  
   - 優化字串使用  
   - 檢查記憶體洩漏（未釋放的記憶體）  

### 問題：資料遺失或損壞  
**症狀：** 訊息遺失、檔案損毀  

**解決方案：**  
1. **SD 卡問題：**  
   - 使用品質良好的 SD 卡（避免便宜或仿冒品）  
   - 定期備份資料  
   - 正確關機（避免直接拔電）  
2. **緩衝區溢位：** 增加程式內的緩衝區大小  
3. **網路可靠度：** 實作重試邏輯和錯誤處理  
4. **服務品質：** 對重要訊息使用 MQTT QoS 1 或 2  

---

## 常見錯誤訊息  

### `ModuleNotFoundError: No module named 'X'`  
**原因：** 套件未安裝或虛擬環境未啟用  

**解決方案：**  
```bash
pip install X
```
請先確保虛擬環境已啟用。  

### Linux/macOS 顯示 `Permission denied`  
**原因：** 需要管理員權限或檔案權限問題  

**解決方案：**  
- 系統操作使用 `sudo`  
- pip 不要在虛擬環境使用 sudo，請先啟用 venv  
- 串列埠權限：將使用者加入 dialout 群組：`sudo usermod -a -G dialout $USER`，然後登出再登入  

### `OSError: [Errno 98] Address already in use`  
**原因：** 連接埠已被其他程序使用  

**解決方案：**  
1. 查找使用該埠的程序：`lsof -i :<port>` 或 `netstat -ano | findstr :<port>`  
2. 結束該程序或在程式中使用不同連接埠  

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**原因：** SSL 憑證驗證失敗  

**解決方案：**  
1. 更新憑證：`pip install --upgrade certifi`  
2. 確認系統時間正確：`date`  
3. 僅於開發環境（非正式環境）可在程式中關閉驗證  

### `IndentationError: unexpected indent`  
**原因：** Python 縮排問題（混用 Tab 與空白）  

**解決方案：**  
1. 使用一致縮排（Python 標準為 4 個空白）  
2. 編輯器設定使用空白取代 Tab  
3. VS Code 設定 `"editor.insertSpaces": true` 及 `"editor.tabSize": 4`  

### `UnicodeDecodeError` 或 `UnicodeEncodeError`  
**原因：** 字元編碼問題  

**解決方案：**  
```python
# 讀取檔案時
with open('file.txt', 'r', encoding='utf-8') as f:
    content = f.read()

# 寫入檔案時
with open('file.txt', 'w', encoding='utf-8') as f:
    f.write(content)
```
  
---

## 尋求協助  

若您已嘗試上述排除方式仍有問題：  

### 1. 檢閱現有資源  
- **文件：** 閱讀 [README](README.md) 和課程指示  
- **硬體指南：** 查看 [hardware.md](hardware.md) 的硬體相關資訊  
- **Seeed Studio Wiki：** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) 查找 Grove 元件資訊  

### 2. 搜尋類似問題  
- **GitHub Issues：** 搜尋 [現有問題](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow：** 搜尋錯誤訊息  
- **裝置論壇：** 查詢 Raspberry Pi 論壇或 Arduino 論壇  

### 3. 建立 GitHub Issue  
若找不到解決方案：  
1. 前往 [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. 點擊「New Issue」  
3. 提供：  
   - 清楚問題描述  
   - 重現步驟  
   - 錯誤訊息（完整）  
   - 硬體/軟體版本  
   - 已嘗試過的方案  
   - 相關截圖（若有）  

### 4. 加入社群  
- **Discord:** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn:** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)  

### 5. 提供完整的 Bug 回報  
一份好的 Bug 回報應包含：
- **環境:** 作業系統、Python 版本、硬體環境
- **重現步驟:** 導致問題的準確步驟
- **預期行為:** 應該發生的狀況
- **實際行為:** 實際發生的狀況
- **錯誤訊息:** 完整的錯誤文字，非截圖
- **程式碼:** 最小化能重現問題的範例程式碼

---

## 預防小貼士

### 一般最佳實踐
1. **保持備份:** 定期備份可用的 SD 卡/程式碼
2. **記錄變更:** 在註解中記錄有效的方法
3. **版本控制:** 使用 git 追蹤程式碼變更
4. **逐步測試:** 先測試小的變更再合併
5. **閱讀錯誤訊息:** 錯誤訊息常告訴你問題所在
6. **定期更新:** 保持軟體/韌體最新
7. **使用優質元件:** 避免使用低價線材/電源供應器
8. **穩定電源:** 使用適當電源供應器（尤其是 Pi）

### 開發工作流程
1. **從簡開始:** 從可用的範例程式碼開始
2. **一次變更一件事:** 更容易找出問題所在
3. **經常測試:** 早期發現問題
4. **保持整潔:** 合理組織檔案與程式碼
5. **註解程式碼:** 未來的你會感謝這些註解

---

*此疑難排解指南由社群維護。如果你找到此處未列出的解決方案，請考慮[貢獻](CONTRIBUTING.md)幫助其他人！*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**免責聲明**：  
本文件係使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們力求準確，但請注意自動翻譯可能包含錯誤或不準確之處。原文文件的母語版本應視為權威依據。對於重要資訊，建議尋求專業人工翻譯。我們不對因使用本翻譯而造成的任何誤解或誤譯負責。
<!-- CO-OP TRANSLATOR DISCLAIMER END -->