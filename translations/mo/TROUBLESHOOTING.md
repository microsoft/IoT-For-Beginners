<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9713e21a309662f6fcb271b573d47848",
  "translation_date": "2026-01-05T17:37:31+00:00",
  "source_file": "TROUBLESHOOTING.md",
  "language_code": "mo"
}
-->
# 疑難排解指南

本指南幫助您解決在使用 IoT for Beginners 課程時常見的問題。問題按類別組織，方便瀏覽。

## 目錄

- [安裝問題](../..)
  - [Python 安裝](../..)
  - [VS Code 與擴充套件](../..)
  - [PlatformIO（Wio Terminal）](../..)
  - [Grove 函式庫](../..)
- [硬體問題](../..)
  - [Raspberry Pi](../..)
  - [Wio Terminal](../..)
  - [虛擬裝置（CounterFit）](../..)
- [連線問題](../..)
  - [WiFi 連線](../..)
  - [雲端服務](../..)
  - [MQTT](../..)
- [感測器與執行器問題](../..)
  - [Grove 感測器](../..)
  - [相機](../..)
  - [麥克風與喇叭](../..)
- [開發環境問題](../..)
  - [VS Code](../..)
  - [Python 虛擬環境](../..)
  - [相依性](../..)
- [效能問題](../..)
- [常見錯誤訊息](../..)
- [求助](../..)

---

## 安裝問題

### Python 安裝

#### 問題：Python 版本太舊
**錯誤：** `需要 Python 3.6 或更高版本`

**解決方案：**
1. 從 [python.org](https://www.python.org/downloads/) 下載最新 Python 3
2. 在 Windows 安裝時，勾選「將 Python 加入 PATH」
3. 驗證安裝：
   ```bash
   python3 --version
   ```

#### 問題：多個 Python 版本衝突
**症狀：** 執行錯誤的 Python 版本，套件安裝到錯誤位置

**解決方案：**
- **Windows：** 使用 `py -3` 替代 `python` 明確呼叫 Python 3
- **macOS/Linux：** 使用 `python3` 替代 `python`
- 專案中務必建立並使用虛擬環境

#### 問題：找不到 pip 指令
**錯誤：** `'pip' 不是內部或外部命令，也不是可執行的程式或批次檔`

**解決方案：**
1. 嘗試使用 `pip3` 替代 `pip`
2. 或使用 `python -m pip` 或 `python3 -m pip`
3. 確認 Python 已加入 PATH（重新安裝 Python 並勾選相關選項）

### VS Code 與擴充套件

#### 問題：Pylance 擴充套件無法運作
**症狀：** 沒有 Python 智慧感知、程式碼補完或型別檢查

**解決方案：**
1. 打開 VS Code 命令面板（`Ctrl+Shift+P` 或 `Cmd+Shift+P`）
2. 執行「Python: Select Interpreter」
3. 選擇正確的 Python 直譯器（如使用虛擬環境選擇虛擬環境）
4. 重新載入 VS Code 視窗

#### 問題：VS Code 無法偵測虛擬環境
**症狀：** 選錯 Python 直譯器

**解決方案：**
1. 確認已在終端機啟動虛擬環境
2. 開啟命令面板並執行「Python: Select Interpreter」
3. 選擇 `.venv` 資料夾中的直譯器
4. 查看狀態列（左下）顯示正確 Python 版本

### PlatformIO（Wio Terminal）

#### 問題：PlatformIO 安裝失敗
**錯誤：** PlatformIO 安裝過程中出現各種錯誤

**解決方案：**
1. 確認 VS Code 為最新版
2. 先安裝 C/C++ 擴充套件
3. 安裝 PlatformIO 後重啟 VS Code
4. 檢查網路連線（PlatformIO 需下載大型檔案）

#### 問題：PlatformIO 無法偵測開發板
**症狀：** 無法上傳程式碼至 Wio Terminal

**解決方案：**
1. 換用不同 USB 線（有些線只支援充電）
2. 檢查裝置管理員（Windows）或使用 `ls /dev/tty*`（macOS/Linux）
3. 安裝或更新 USB 驅動程式
4. 換用不同 USB 埠
5. 快速滑動 Wio Terminal 電源開關兩次進入 bootloader 模式

#### 問題：PlatformIO 編譯錯誤
**錯誤：** `fatal error: Arduino.h: No such file or directory`

**解決方案：**
1. 刪除專案中的 `.pio` 資料夾
2. 使用命令面板執行「PlatformIO: Rebuild」
3. 確認 `platformio.ini` 內使用正確開發板設定：
   ```ini
   [env:seeed_wio_terminal]
   platform = atmelsam
   board = seeed_wio_terminal
   framework = arduino
   ```

### Grove 函式庫

#### 問題：Raspberry Pi 上的 Grove 函式庫導入失敗
**錯誤：** `ModuleNotFoundError: No module named 'grove'`

**解決方案：**
1. 重新安裝 Grove 函式庫：
   ```bash
   cd ~
   git clone https://github.com/Seeed-Studio/grove.py
   cd grove.py
   sudo pip3 install .
   ```
2. 若使用虛擬環境，可能需在全域安裝或複製函式庫
3. 確認已啟用 I2C：`sudo raspi-config nonint do_i2c 0`

#### 問題：Grove 感測器無法偵測
**錯誤：** `IOError: [Errno 121] Remote I/O error`

**解決方案：**
1. 檢查物理連接（確保 Grove 線材完全插入）
2. 確認感測器接到正確埠位（類比、數位、I2C、UART）
3. 執行 `i2cdetect -y 1` 查看裝置是否出現在 I2C 匯流排
4. 換用另一條 Grove 線材
5. 確認 Grove Base Hat 是否正確插於 Raspberry Pi GPIO 腳位

---

## 硬體問題

### Raspberry Pi

#### 問題：Raspberry Pi 無法開機
**症狀：** 無顯示、無 LED 動作或出現彩虹螢幕

**解決方案：**
1. **檢查電源供應：** Pi 4 使用官方 5V 3A USB-C 電源供應器
2. **SD 卡問題：** 
   - 重新格式化 SD 卡並重新安裝 Raspberry Pi OS
   - 換用不同 SD 卡（推薦的品牌）
   - 確認 SD 卡插入正確
3. **檢查 HDMI 連接：** 嘗試 Pi 4 上兩個 HDMI 埠，使用靠近電源的 HDMI 埠

#### 問題：無法 SSH 連線至 Raspberry Pi
**症狀：** 連線被拒或逾時

**解決方案：**
1. 啟用 SSH：
   - 使用 Raspberry Pi Imager 燒錄 SD 卡時在進階選項設定 SSH
   - 或在啟動分割區建立名為 `ssh`（無副檔名）的空文件
2. 找出 Pi 的 IP 位址：
   - 查看路由器的已連接裝置
   - 使用 `ping raspberrypi.local`（若 mDNS 有效）
   - 使用網路掃描工具如 `nmap` 或 Angry IP Scanner
3. 網路檢查：
   - 確認 Pi 與電腦在同一網路
   - 嘗試使用有線乙太網路代替 WiFi
4. 驗證帳號/密碼（預設：使用者名稱 `pi`，密碼 `raspberry`）

#### 問題：Grove Base Hat 未被識別
**症狀：** 感測器無法運作，I2C 錯誤

**解決方案：**
1. 確保 Base Hat 牢固插入全部 GPIO 腳位
2. 檢查 Pi 或 Base Hat 的腳位是否彎曲
3. 啟用 I2C 介面：
   ```bash
   sudo raspi-config nonint do_i2c 0
   sudo reboot
   ```
4. 驗證 I2C 運作：`i2cdetect -y 1`

#### 問題：Raspberry Pi 執行速度緩慢
**症狀：** 介面卡頓，反應遲鈍

**解決方案：**
1. 檢查 SD 卡速度（使用 Class 10 或以上，或透過 USB 外接 SSD）
2. 釋放磁碟空間：使用 `df -h` 檢查，刪除不必要檔案
3. 若未頻繁使用相機或顯示器，可在 `raspi-config` 減少 GPU 記憶體分配
4. 關閉不必要的應用程式
5. 若用 Pi 3 或更舊機型，考慮升級到具更多 RAM 的 Pi 4

### Wio Terminal

#### 問題：Wio Terminal 螢幕維持空白
**症狀：** 上傳程式後無顯示輸出

**解決方案：**
1. 確認程式碼有初始化螢幕顯示（使用 TFT_eSPI 函式庫）
2. 從 [Seeed Wiki](https://wiki.seeedstudio.com/Wio-Terminal-Getting-Started/) 更新 Wio Terminal 韌體
3. 新增螢幕初始化程式碼：
   ```cpp
   #include <TFT_eSPI.h>
   TFT_eSPI tft;
   tft.begin();
   tft.fillScreen(TFT_BLACK);
   ```
4. 透過 PlatformIO 上傳範例程式碼測試硬體

#### 問題：Wio Terminal WiFi 無法使用
**症狀：** 無法連線 WiFi，出現網路錯誤

**解決方案：**
1. **更新 WiFi 韌體：** 參考 [Wio Terminal WiFi 韌體更新指南](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/)
2. **檢查 WiFi 資訊：** 確認 SSID 與密碼正確
3. **WiFi 頻段：** Wio Terminal 僅支援 2.4GHz WiFi（不支援 5GHz）
4. **訊號強度：** 讓裝置靠近路由器
5. **路由器設定：** 部份企業網路/WPA-Enterprise 可能無法使用

#### 問題：Wio Terminal 未被電腦識別
**症狀：** USB 裝置未被偵測

**解決方案：**
1. **換用不同 USB 線：** 使用資料線，非僅充電線
2. **進入 bootloader 模式：** 快速向下滑動電源開關兩次  
   - 藍燈會閃爍，裝置在裝置管理員顯示為「Arduino」
3. **安裝驅動程式（Windows）：**  
   - 下載並安裝 [Seeed USB 驅動程式](https://wiki.seeedstudio.com/Driver_for_Seeeduino/)
4. **換用不同 USB 埠：** 避免使用 USB 集線器，使用直接連接
5. **更新系統 USB 驅動程式**

#### 問題：Wio Terminal 感測器無法運作
**症狀：** Grove 感測器無法讀取資料

**解決方案：**
1. 檢查 Grove 線材連接
2. 確認使用正確 Grove 埠（左邊或右邊）
3. 包含感測器所需的函式庫
4. 檢查感測器的電源要求
5. 使用函式庫範例程式測試感測器

### 虛擬裝置（CounterFit）

#### 問題：CounterFit 應用程式無法啟動
**錯誤：** 啟動 CounterFit 時出現各種 Python 錯誤

**解決方案：**
1. 確認虛擬環境已啟動
2. 安裝或重新安裝 CounterFit：
   ```bash
   pip install CounterFit
   ```
3. 檢查 5000 埠是否已被占用：  
   - Windows：`netstat -ano | findstr :5000`  
   - macOS/Linux：`lsof -i :5000`  
4. 結束使用 5000 埠的程序或使用其他埠位：
   ```bash
   counterfit --port 5001
   ```

#### 問題：無法從程式碼連接到 CounterFit
**錯誤：** 連線被拒絕或逾時

**解決方案：**
1. 確認 CounterFit 正在執行：用瀏覽器開啟 `http://127.0.0.1:5000`
2. 檢查程式碼中的連線 URL 是否與 CounterFit 位址一致
3. 確認防火牆未阻擋連線
4. 嘗試重新啟動 CounterFit 應用程式與您的程式碼

#### 問題：CounterFit 中感測器不顯示
**症狀：** 已建立的感測器無法在 CounterFit UI 中顯示

**解決方案：**
1. 在執行程式前，先在 CounterFit UI 中建立感測器
2. 手動重新整理瀏覽器頁面
3. 確認感測器類型符合程式碼使用
4. 清除瀏覽器快取

---

## 連線問題

### WiFi 連線

#### 問題：裝置無法連接 WiFi
**症狀：** 連線逾時，認證失敗

**解決方案：**
1. **檢查 SSID 與密碼：** 確認資料正確
2. **WiFi 頻段：** 大部分物聯網裝置只支援 2.4GHz（不支援 5GHz）
3. **路由器設定：**
   - 如果啟用，請關閉 AP 隔離
   - 使用 WPA2-PSK 安全性（避免 WPA3、WEP 或開放網路）
   - 確認啟用 DHCP
4. **隱藏網路：** 隱藏 SSID 時可能需手動設定
5. **訊號強度：** 讓裝置靠近路由器
6. **干擾：** 其他裝置、微波爐或牆壁可能造成干擾

#### 問題：WiFi 連線常掉線
**症狀：** 連線不穩定斷斷續續

**解決方案：**
1. 檢查路由器穩定性並考慮重啟
2. 更新裝置韌體
3. 使用固定 IP 代替 DHCP
4. 減少裝置與路由器間距離或使用 WiFi 延伸器
5. 檢查其他裝置的干擾狀況
6. 確認電源供應充足（特別是 Raspberry Pi）

### 雲端服務

#### 問題：無法連接 Azure IoT Hub
**錯誤：** 認證失敗，連線被拒

**解決方案：**
1. **確認認證：**
   - 檢查連線字串正確無誤
   - 確認連線字串無額外空白或換行
2. **檢查裝置註冊：** 裝置必須已註冊於 IoT Hub
3. **防火牆/代理伺服器：** 確保允許外送 MQTT（埠號 8883）或 HTTPS（埠號 443）
4. **IoT Hub 所屬區域：** 確保 IoT Hub 在運作中且不在不同區域以避免延遲
5. **配額限制：** 檢查是否超過免費層限制
6. **測試連線：**
   ```bash
   az iot hub device-identity show-connection-string --hub-name YourIoTHub --device-id YourDevice
   ```

#### 問題：Azure Functions 無法觸發
**症狀：** 訊息送出，但函式不執行

**解決方案：**
1. 確認 Function App 正在執行（未停止）
2. 驗證 Function App 設定中的連線字串
3. 檢查 Azure 入口網站中的函式日誌
4. 確保 Event Hub 相容端點設定正確
5. 驗證訊息格式符合函式需求
6. 檢查 Function App 服務方案（消耗方案 vs. 專用方案）

### MQTT
#### 問題：MQTT 連線失敗  
**錯誤：** 連線被拒，驗證失敗

**解決方案：**  
1. **Broker 位址：** 確認 Broker URL/IP 是否正確  
2. **埠號：** 檢查埠號（1883 為未加密，8883 為 TLS）  
3. **認證：** 確認是否需要使用者名稱與密碼  
4. **TLS/SSL：** 確保憑證有效且被信任  
5. **防火牆：** 檢查埠號是否被阻擋  
6. **使用 MQTT 用戶端測試：** 使用 MQTT Explorer 或 mosquitto_pub/sub 測試

#### 問題：MQTT 訊息無法接收  
**症狀：** 訊息已發布但訂閱者未收到

**解決方案：**  
1. **主題名稱：** 確認訂閱主題與發布主題完全一致  
2. **QoS 等級：** 嘗試 QoS 1 或 2 代替 0  
3. **萬用字元：** 檢查主題萬用字元使用是否正確（`+` 單層，`#` 多層）  
4. **保留訊息：** 發布者可設定保留旗標以保存最後一則訊息  
5. **連線時間：** 確保訂閱者在訊息發布前已連接

---

## 感測器與執行器問題

### Grove 感測器

#### 問題：感測器回傳錯誤數值  
**症狀：** 讀值為 0、-1 或無意義值

**解決方案：**  
1. **檢查連線：** 確保感測器接線正確  
2. **正確埠口：** 確認感測器連接到正確類型埠口：  
   - 類比感測器 → 類比埠（A0、A2、A4）  
   - 數位感測器 → 數位埠（D5、D16、D18 等）  
   - I2C 感測器 → I2C 埠口  
3. **校正：** 某些感測器需校正（土壤濕度、光感測器）  
4. **重新開機：** 斷開後重連感測器  
5. **感測器規格表：** 檢查感測器規格與需求

#### 問題：電容式土壤濕度感測器總是讀取為濕  
**症狀：** 感測器即使乾燥也讀取高濕度

**解決方案：**  
1. **需校正：** 土壤感測器需校正：  
   - 在空氣中讀取值（乾燥基準）  
   - 在水中讀取值（濕潤基準）  
   - 將讀取值映射在這些基準中間  
2. **檢查感測器塗層：** 濕度感測器塗層損壞會影響讀值  
3. **放置位置：** 確保感測器完全插入土壤中

#### 問題：溫濕度感測器讀值錯誤  
**症狀：** DHT11/DHT22 顯示的溫度或濕度錯誤

**解決方案：**  
1. **感測器放置：** 避免直射日光、熱源或空氣流通強烈的地方  
2. **暖機時間：** 電源開啟後給感測器 2 秒暖機時間再讀取  
3. **讀取頻率：** DHT 感測器需間隔時間（至少 2 秒）  
4. **檢查結露：** 濕氣結露會影響讀值  
5. **感測器品質：** DHT11 精準度低於 DHT22

### 攝影機

#### 問題：樹莓派無法偵測攝影機  
**錯誤：** `mmal: mmal_vc_component_create: failed to create component 'vc.ril.camera'`

**解決方案：**  
1. **啟用攝影機介面：**  
   ```bash
   sudo raspi-config
   ```
 進入介面選項 → 攝影機 → 啟用  
2. **檢查排線：** 確認攝影機排線正確插入  
   - Pi Zero 藍色一面朝 USB 埠方向  
   - Pi 4 藍色一面背離 USB 埠方向  
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
**症狀：** 影像模糊、昏暗或過曝

**解決方案：**  
1. **對焦：** 移除鏡頭保護膜，如可調整則調整焦距  
2. **光線：** 確保足夠的照明  
3. **攝影機設定：** 調整程式中的曝光、ISO、白平衡  
4. **穩定性：** 保持攝影機固定，必要時使用三腳架  
5. **解像度：** 不要超過攝影機最大解像度

### 麥克風與喇叭

#### 問題：無法錄音或播放音訊  
**症狀：** 麥克風無錄音，喇叭無播放

**解決方案：**  
1. **檢查連線：** 確認音訊裝置已正確接線  
2. **測試硬體：**  
   - 喇叭：`speaker-test -t wav -c 2`  
   - 麥克風：`arecord -l` 列出裝置，`arecord test.wav` 錄音  
3. **音量設定：** 調整與檢查音量：  
   ```bash
   alsamixer
   ```
4. **選擇音訊裝置：** 代碼中指定正確音訊裝置  
5. **驅動程式問題：** 更新 ALSA 或重裝音訊驅動

#### 問題：ReSpeaker HAT 無法運作  
**症狀：** 無法偵測音訊裝置

**解決方案：**  
1. **安裝驅動程式：**  
   ```bash
   git clone https://github.com/HinTak/seeed-voicecard
   cd seeed-voicecard
   sudo ./install.sh
   sudo reboot
   ```
2. **檢查安裝：** `arecord -l` 應有 ReSpeaker 裝置  
3. **韌體更新：** 部分 Pi OS 版本需更新驅動  
4. **確認安裝位置：** 確保 HAT 正確插入 GPIO 腳位

---

## 開發環境問題

### VS Code

#### 問題：終端機未自動啟動虛擬環境  
**症狀：** 終端顯示但 venv 未啟動

**解決方案：**  
1. **設定 Python 直譯器：** 指令面板 → "Python: Select Interpreter" → 選擇 venv  
2. **重新啟動 VS Code** 選擇直譯器後  
3. **設定檔檢查：** 在 `settings.json` 加入：  
   ```json
   "python.terminal.activateEnvironment": true
   ```
  
#### 問題：代碼執行不出結果  
**症狀：** 代碼執行但裝置沒有反應

**解決方案：**  
1. **確定代碼已保存**（檔案標籤上有點）  
2. **檢查使用的 Python：** `which python` 或 `where python`  
3. **Wio Terminal：** 確保經由 PlatformIO 上傳（點按上傳鈕）  
4. **Raspberry Pi：** SSH 登入 Pi 並在那裏執行代碼  
5. **檢查輸出視窗** 是否有錯誤訊息

#### 問題：IntelliSense 不顯示函數  
**症狀：** 匯入模組沒有自動補全

**解決方案：**  
1. 確保函式庫安裝於目前環境  
2. 重新載入 VS Code 視窗  
3. 檢查 Python 直譯器是否正確  
4. 安裝型別提示：`pip install types-<library-name>`

### Python 虛擬環境

#### 問題：無法建立虛擬環境  
**錯誤：** `The virtual environment was not created successfully`

**解決方案：**  
1. **安裝 venv 模組：**  
   - Ubuntu/Debian：`sudo apt install python3-venv`  
   - macOS：Python 內建  
   - Windows：重新安裝 Python 並安裝所有組件  
2. **檢查 Python 安裝：** 確認 Python 已正確安裝  
3. **使用完整路徑：** 嘗試使用 `python3 -m venv .venv`

#### 問題：套件安裝位置錯誤  
**症狀：** 安裝套件後匯入失敗

**解決方案：**  
1. **確認 venv 已啟動：** 命令提示符應該顯示 `(.venv)`  
2. **檢查 pip 位置：** `which pip` 應指向 `.venv/bin/pip`  
3. **重新安裝於 venv：** 啟動 venv 後執行 `pip install <package>`  
4. **虛擬環境中不要使用 sudo**

#### 問題：虛擬環境無法攜帶移動  
**症狀：** 移動或在不同電腦上無法使用 venv

**解決方案：**  
1. **不要移動 venv：** 刪除並在新位置重新建立  
2. **使用 requirements.txt：**  
   ```bash
   pip freeze > requirements.txt
   pip install -r requirements.txt
   ```
3. **重新建立 venv：**  
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate  # 或 Windows 上的 activate.bat
   pip install -r requirements.txt
   ```
  
### 相依性問題

#### 問題：套件安裝失敗  
**錯誤：** 不同 pip 錯誤訊息

**解決方案：**  
1. **更新 pip：**  
   ```bash
   pip install --upgrade pip
   ```
2. **安裝建置工具：**  
   - Ubuntu/Debian：`sudo apt install build-essential python3-dev`  
   - macOS：`xcode-select --install`  
   - Windows：安裝 Visual Studio Build Tools  
3. **檢查網路連線**  
4. **切換套件源：** `pip install --index-url https://pypi.org/simple/ <package>`  
5. **安裝特定版本：** `pip install <package>==<version>`

#### 問題：相依性衝突  
**錯誤：** `ERROR: pip's dependency resolver does not currently take into account all the packages that are installed`

**解決方案：**  
1. **每專案使用新的虛擬環境**  
2. **更新套件：** `pip install --upgrade <package>`  
3. **檢查需求衝突：** 使用 `pip check`  
4. **安裝相容版本：** 在 requirements.txt 指定版本範圍

---

## 效能問題

### 問題：代碼運行緩慢  
**症狀：** 延遲、逾時、無回應

**解決方案：**  
1. **減少感測器讀取頻率**，不要過頻繁讀取  
2. **優化迴圈：** 避免忙等，使用 sleep() 或延遲  
3. **記憶體問題：**  
   - 關閉不必要的應用程式  
   - 釋放儲存空間  
   - 使用 Pi 上的 `top` 或 `htop` 監控  
4. **SD 卡速度：** 使用較快的 SD 卡或 SSD  
5. **網路延遲：** 網路呼叫使用非同步

### 問題：記憶體不足錯誤  
**錯誤：** `MemoryError` 或系統凍結

**解決方案：**  
1. **Raspberry Pi：**  
   - 關閉不必要的程式  
   - 增加交換空間  
   - 使用輕量版本的作業系統（Lite）  
   - 升級 RAM（Pi 4 有 2/4/8GB 選項）  
2. **Wio Terminal：**  
   - 減少快取大小  
   - 使用較小的圖片  
   - 優化字串使用  
   - 檢查記憶體洩漏

### 問題：資料遺失或損毀  
**症狀：** 訊息丟失、檔案毀損

**解決方案：**  
1. **SD 卡問題：**  
   - 使用品質良好的 SD 卡（避免廉價/仿冒）  
   - 定期備份  
   - 正確關機（勿強制斷電）  
2. **快取溢位：** 增加程式內快取大小  
3. **網絡可靠性：** 實作重試與錯誤處理  
4. **服務品質：** 重要訊息使用 MQTT QoS 1 或 2

---

## 常見錯誤訊息

### `ModuleNotFoundError: No module named 'X'`  
**原因：** 套件未安裝或虛擬環境未啟動

**解決方案：**  
```bash
pip install X
```
請先確認虛擬環境已啟動。

### Linux/macOS `Permission denied`  
**原因：** 權限不足或檔案權限問題

**解決方案：**  
- 系統操作使用 `sudo`  
- pip 不要在虛擬環境內使用 sudo，先啟動 venv  
- 串口權限：將使用者加入 dialout 群組：`sudo usermod -a -G dialout $USER`，然後重新登入

### `OSError: [Errno 98] Address already in use`  
**原因：** 埠號已被其他程序使用

**解決方案：**  
1. 查找占用程序：`lsof -i :<port>` 或 `netstat -ano | findstr :<port>`  
2. 終止程序或在代碼中使用不同埠號

### `SSL: CERTIFICATE_VERIFY_FAILED`  
**原因：** SSL 憑證驗證失敗

**解決方案：**  
1. 更新憑證：`pip install --upgrade certifi`  
2. 檢查系統時間是否正確：`date`  
3. 僅開發時（非正式環境）可在代碼中禁用驗證

### `IndentationError: unexpected indent`  
**原因：** Python 縮排錯誤（混用 tab 與空格）

**解決方案：**  
1. 統一縮排風格（Python 標準為 4 個空格）  
2. 編輯器設定使用空格取代 tab  
3. VS Code 設定 `"editor.insertSpaces": true` 和 `"editor.tabSize": 4`

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

如果已嘗試上述排除方法仍有問題：

### 1. 查閱現有資源  
- **文件：** 查看 [README](README.md) 及課程說明  
- **硬體指南：** 參考 [hardware.md](hardware.md) 硬體相關資訊  
- **Seeed Studio Wiki:** [Seeed Studio Wiki](https://wiki.seeedstudio.com/) 了解 Grove 元件

### 2. 搜尋類似問題  
- **GitHub Issues：** 搜尋 [現有問題](https://github.com/microsoft/IoT-For-Beginners/issues)  
- **Stack Overflow：** 搜尋錯誤訊息  
- **裝置論壇：** 查詢 Raspberry Pi 論壇或 Arduino 論壇

### 3. 建立 GitHub 問題單  
若找不到解決方案：  
1. 前往 [GitHub Issues](https://github.com/microsoft/IoT-For-Beginners/issues)  
2. 點選「New Issue」  
3. 提供：  
   - 清楚描述問題  
   - 重現步驟  
   - 錯誤訊息（完整文字）  
   - 硬體／軟體版本  
   - 已嘗試的方式  
   - 如有相關，附上截圖

### 4. 加入社群  
- **Discord：** [Microsoft Foundry Discord](https://discord.gg/nTYy5BXMWG)  
- **Microsoft Learn：** [Microsoft Learn IoT](https://docs.microsoft.com/learn/browse/?products=azure-iot)

### 5. 提供良好錯誤回報  
良好的錯誤回報包含：
- **環境：** 作業系統、Python 版本、使用的硬件
- **重現步驟：** 引起問題的確切步驟
- **預期行為：** 應該發生的情況
- **實際行為：** 實際發生的情況
- **錯誤訊息：** 完整錯誤文字，非截圖
- **程式碼：** 能重現問題的最小範例程式碼

---

## 預防小貼士

### 一般最佳做法
1. **保持備份：** 定期備份正常運作的 SD 卡／程式碼
2. **記錄變更：** 在註解中記下有效的方法
3. **版本控制：** 使用 git 追蹤程式碼更動
4. **逐步測試：** 小幅度改動先測試，再合併
5. **閱讀錯誤訊息：** 常會明確說明問題所在
6. **定期更新：** 保持軟件／韌體最新
7. **使用優質零件：** 避免廉價線材／電源供應器
8. **電力穩定：** 使用適當電源（特別是 Pi）

### 開發工作流程
1. **從簡入手：** 從可用示例程式開始
2. **一次一改：** 容易找出問題所在
3. **經常測試：** 及早發現問題
4. **保持整潔：** 合理整理檔案和程式碼
5. **註解程式碼：** 未來的你會感激

---

*這份故障排除指南由社群維護。如果你找到此處未列出問題的解決方案，請考慮[貢獻](CONTRIBUTING.md)幫助他人！*

---

<!-- CO-OP TRANSLATOR DISCLAIMER START -->
**免責聲明**：
本文件由人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們力求準確，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要資訊，建議採用專業人工翻譯。我們不對因使用本翻譯而產生的任何誤解或錯誤詮釋承擔責任。
<!-- CO-OP TRANSLATOR DISCLAIMER END -->