<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f7bb24ba53fb627ddb38a8b24a05e594",
  "translation_date": "2025-08-24T22:10:26+00:00",
  "source_file": "2-farm/lessons/3-automated-plant-watering/README.md",
  "language_code": "tw"
}
-->
# 自動植物澆水

![本課程的手繪筆記概述](../../../../../translated_images/tw/lesson-7.30b5f577d3cb8e031238751475cb519c7d6dbaea261b5df4643d086ffb2a03bb.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

本課程是 [IoT 初學者項目 2 - 數字農業系列](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) 的一部分，由 [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn) 提供。

[![IoT 驅動的自動植物澆水](https://img.youtube.com/vi/g9FfZwv9R58/0.jpg)](https://youtu.be/g9FfZwv9R58)

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/13)

## 簡介

在上一課中，你學習了如何監測土壤濕度。在本課中，你將學習如何構建一個自動澆水系統的核心組件，該系統能根據土壤濕度進行響應。你還將了解時間的概念——傳感器可能需要一些時間來響應變化，而執行器可能需要時間來改變傳感器測量的屬性。

本課將涵蓋以下內容：

* [從低功率 IoT 設備控制高功率設備](../../../../../2-farm/lessons/3-automated-plant-watering)
* [控制繼電器](../../../../../2-farm/lessons/3-automated-plant-watering)
* [通過 MQTT 控制植物](../../../../../2-farm/lessons/3-automated-plant-watering)
* [傳感器和執行器的時間](../../../../../2-farm/lessons/3-automated-plant-watering)
* [為植物控制伺服器添加時間功能](../../../../../2-farm/lessons/3-automated-plant-watering)

## 從低功率 IoT 設備控制高功率設備

IoT 設備使用低電壓。雖然這足以驅動傳感器和像 LED 這樣的低功率執行器，但對於控制更大的硬件（例如用於灌溉的水泵）來說，電壓太低。即使是用於室內植物的小型水泵，其電流需求也超過了 IoT 開發板的承受範圍，可能會導致開發板燒毀。

> 🎓 電流（以安培 A 為單位）是指流經電路的電量。電壓提供推動力，而電流則是被推動的量。你可以在 [維基百科的電流頁面](https://wikipedia.org/wiki/Electric_current) 上了解更多。

解決方案是將水泵連接到外部電源，並使用執行器來開啟水泵，就像你用手指打開燈的開關一樣。手指翻動開關所需的能量非常小，這樣就能將燈連接到 110v/240v 的市電。

![燈開關打開燈的電源](../../../../../translated_images/tw/light-switch.760317ad6ab8bd6d611da5352dfe9c73a94a0822ccec7df3c8bae35da18e1658.png)

> 🎓 [市電](https://wikipedia.org/wiki/Mains_electricity) 是指通過國家基礎設施向家庭和企業提供的電力。

✅ IoT 設備通常能提供 3.3V 或 5V，電流小於 1 安培（1A）。相比之下，市電通常為 230V（北美為 120V，日本為 100V），能為需要 30A 電流的設備提供電力。

有許多執行器可以完成這項工作，包括可以附加到現有開關上的機械設備，模仿手指打開開關的動作。其中最常見的是繼電器。

### 繼電器

繼電器是一種電機機械開關，它將電信號轉換為機械運動以打開或關閉開關。繼電器的核心是一個電磁鐵。

> 🎓 [電磁鐵](https://wikipedia.org/wiki/Electromagnet) 是通過電流流過線圈而產生的磁鐵。當電流通過時，線圈被磁化；當電流停止時，線圈失去磁性。

![當電磁鐵通電時，產生磁場，打開輸出電路的開關](../../../../../translated_images/tw/relay-on.4db16a0fd6b66926.webp)

在繼電器中，控制電路為電磁鐵供電。當電磁鐵通電時，它拉動一個杠杆，移動開關，閉合一對觸點，完成輸出電路。

![當電磁鐵斷電時，磁場消失，關閉輸出電路的開關](../../../../../translated_images/tw/relay-off.c34a178a2960fecd.webp)

當控制電路斷電時，電磁鐵停止工作，釋放杠杆並打開觸點，關閉輸出電路。繼電器是一種數字執行器——高信號打開繼電器，低信號關閉繼電器。

輸出電路可以用來為額外的硬件供電，例如灌溉系統。IoT 設備可以打開繼電器，完成供電灌溉系統的輸出電路，植物就會被澆水。然後 IoT 設備可以關閉繼電器，切斷灌溉系統的電源，停止澆水。

![繼電器打開，啟動水泵向植物供水](../../../../../images/strawberry-pump.gif)

在上面的視頻中，繼電器被打開。繼電器上的 LED 亮起，指示繼電器已打開（某些繼電器板上有 LED 指示繼電器的開啟或關閉狀態），電力被送到水泵，啟動水泵向植物供水。

> 💁 繼電器也可以用來在兩個輸出電路之間切換，而不是僅僅打開或關閉一個電路。當杠杆移動時，它將開關從完成一個輸出電路移動到完成另一個輸出電路，通常共享一個公共電源或公共接地連接。

✅ 做一些研究：繼電器有多種類型，差異包括控制電路在通電時是打開還是關閉繼電器，或者是否有多個輸出電路。了解這些不同類型的繼電器。

當杠杆移動時，你通常可以聽到它與電磁鐵接觸時發出的清晰的“咔嗒”聲。

> 💁 繼電器可以被接線設計成在連接時實際上斷開繼電器的電源，關閉繼電器，然後重新向繼電器供電，打開繼電器，如此反覆。這樣繼電器會快速點擊，發出嗡嗡聲。這是一些早期電門鈴中的蜂鳴器的工作原理。

### 繼電器的功率

電磁鐵啟動並拉動杠杆所需的功率不大，可以使用 IoT 開發板的 3.3V 或 5V 輸出進行控制。輸出電路可以承載更多功率，取決於繼電器的規格，包括市電電壓甚至更高的工業用電功率。這樣 IoT 開發板就可以控制灌溉系統，從單個植物的小型水泵到整個商業農場的大型工業系統。

![一個 Grove 繼電器，標註了控制電路、輸出電路和繼電器](../../../../../translated_images/tw/grove-relay-labelled.293e068f5c3c2a199bd7892f2661fdc9e10c920b535cfed317fbd6d1d4ae1168.png)

上圖顯示了一個 Grove 繼電器。控制電路連接到 IoT 設備，使用 3.3V 或 5V 打開或關閉繼電器。輸出電路有兩個端子，任一端都可以是電源或接地。輸出電路可以處理高達 250V、10A 的電力，足以驅動一系列市電設備。你還可以找到能處理更高功率的繼電器。

![通過繼電器連接的水泵](../../../../../translated_images/tw/pump-wired-to-relay.66c5cfc0d8918990.webp)

在上圖中，通過繼電器向水泵供電。一根紅線將 USB 電源的 +5V 端子連接到繼電器的輸出電路的一個端子，另一根紅線將輸出電路的另一端子連接到水泵。一根黑線將水泵連接到 USB 電源的接地端子。當繼電器打開時，它完成電路，向水泵提供 5V 電壓，啟動水泵。

## 控制繼電器

你可以使用 IoT 開發板控制繼電器。

### 任務 - 控制繼電器

按照相關指南，使用你的 IoT 設備控制繼電器：

* [Arduino - Wio Terminal](wio-terminal-relay.md)
* [單板電腦 - Raspberry Pi](pi-relay.md)
* [單板電腦 - 虛擬設備](virtual-device-relay.md)

## 通過 MQTT 控制植物

目前你的繼電器是由 IoT 設備直接控制，基於單一的土壤濕度讀數。在商業灌溉系統中，控制邏輯通常是集中化的，這樣可以根據多個傳感器的數據進行澆水決策，並且可以在一個地方更改所有配置。為了模擬這一點，你可以通過 MQTT 控制繼電器。

### 任務 - 通過 MQTT 控制繼電器

1. 在你的 `soil-moisture-sensor` 項目中添加相關的 MQTT 庫/pip 包和代碼以連接到 MQTT。將客戶端 ID 命名為 `soilmoisturesensor_client`，並在前面加上你的 ID。

    > ⚠️ 如果需要，可以參考 [項目 1，第 4 課中連接到 MQTT 的說明](../../../1-getting-started/lessons/4-connect-internet/README.md#connect-your-iot-device-to-mqtt)。

1. 添加相關設備代碼以使用土壤濕度設置發送遙測數據。對於遙測消息，將屬性命名為 `soil_moisture`。

    > ⚠️ 如果需要，可以參考 [項目 1，第 4 課中發送遙測數據到 MQTT 的說明](../../../1-getting-started/lessons/4-connect-internet/README.md#send-telemetry-from-your-iot-device)。

1. 在名為 `soil-moisture-sensor-server` 的文件夾中創建一些本地伺服器代碼，用於訂閱遙測數據並發送命令以控制繼電器。將命令消息中的屬性命名為 `relay_on`，並將客戶端 ID 命名為 `soilmoisturesensor_server`，在前面加上你的 ID。保持與你在項目 1，第 4 課中編寫的伺服器代碼相同的結構，因為你稍後會在本課中添加到此代碼。

    > ⚠️ 如果需要，可以參考 [項目 1，第 4 課中發送遙測數據到 MQTT 的說明](../../../1-getting-started/lessons/4-connect-internet/README.md#write-the-server-code) 和 [通過 MQTT 發送命令的說明](../../../1-getting-started/lessons/4-connect-internet/README.md#send-commands-to-the-mqtt-broker)。

1. 添加相關設備代碼以根據接收到的命令控制繼電器，使用消息中的 `relay_on` 屬性。如果 `soil_moisture` 大於 450，則發送 true 給 `relay_on`，否則發送 false，與你之前為 IoT 設備添加的邏輯相同。

    > ⚠️ 如果需要，可以參考 [項目 1，第 4 課中響應 MQTT 命令的說明](../../../1-getting-started/lessons/4-connect-internet/README.md#handle-commands-on-the-iot-device)。

> 💁 你可以在 [code-mqtt](../../../../../2-farm/lessons/3-automated-plant-watering/code-mqtt) 文件夾中找到此代碼。

確保代碼在你的設備和本地伺服器上運行，並通過改變土壤濕度水平進行測試，可以通過更改虛擬傳感器發送的值，或者通過向土壤添加水或移除傳感器來改變土壤濕度。

## 傳感器和執行器的時間

在第 3 課中，你構建了一個夜燈——當光傳感器檢測到低光水平時，LED 立即亮起。光傳感器能夠即時檢測光線變化，設備能快速響應，僅受 `loop` 函數或 `while True:` 循環中的延遲時間限制。作為 IoT 開發者，你不能總是依賴如此快速的反饋循環。

### 土壤濕度的時間

如果你在上一課中使用了物理傳感器測量土壤濕度，你可能會注意到在澆水後，土壤濕度讀數需要幾秒鐘才會下降。這並不是因為傳感器速度慢，而是因為水需要時間滲透到土壤中。
💁 如果你在感測器附近澆水，可能會看到讀數迅速下降，然後又回升——這是因為感測器附近的水分擴散到土壤其他部分，導致感測器周圍的土壤濕度降低。
![土壤濕度測量值為 658，在澆水過程中沒有變化，只有當水滲透到土壤後才會降至 320](../../../../../translated_images/tw/soil-moisture-travel.a0e31af222cf1438.webp)

在上圖中，土壤濕度讀數顯示為 658。植物被澆水，但這個讀數不會立即改變，因為水尚未到達感測器。甚至在水到達感測器之前，澆水可能就已經結束，而讀數會在水滲透到土壤後下降，反映新的濕度水平。

如果你正在撰寫一段程式碼，基於土壤濕度水平通過繼電器來控制灌溉系統，你需要考慮這種延遲，並在你的 IoT 裝置中建立更智能的時間控制。

✅ 花點時間思考一下你會如何處理這個問題。

### 控制感測器與執行器的時間

假設你被指派為一個農場建造灌溉系統。根據土壤類型，已經發現植物的理想土壤濕度水平對應於 400-450 的類比電壓讀數。

你可以像夜燈一樣編寫裝置程式碼——只要感測器讀數高於 450，就打開繼電器啟動水泵。然而，問題在於水從水泵流到土壤再到感測器需要一段時間。當感測器檢測到 450 的濕度水平時會停止供水，但由於水持續滲透到土壤中，濕度水平會繼續下降。最終結果是浪費水資源，並可能損害植物根部。

✅ 記住——過多的水對植物的危害可能和過少一樣，並且浪費了寶貴的資源。

更好的解決方案是理解執行器啟動與感測器讀數改變之間存在延遲。這意味著感測器不僅需要等待一段時間再進行測量，執行器也需要在下一次感測器測量之前關閉一段時間。

每次繼電器應該開啟多久？最好謹慎行事，只讓繼電器開啟短時間，然後等待水滲透，再重新檢查濕度水平。畢竟，你可以隨時再次啟動繼電器添加更多水，但無法從土壤中移除多餘的水。

> 💁 這種時間控制非常依賴於你正在建造的 IoT 裝置、測量的屬性以及使用的感測器和執行器。

![一株草莓植物通過水泵連接到水源，水泵通過繼電器控制。繼電器和植物中的土壤濕度感測器都連接到 Raspberry Pi](../../../../../translated_images/tw/strawberry-with-pump.b410fc72ac6aabad.webp)

例如，我有一株草莓植物，配備了一個土壤濕度感測器和一個由繼電器控制的水泵。我觀察到當我加水時，土壤濕度讀數需要大約 20 秒才能穩定下來。這意味著我需要關閉繼電器並等待 20 秒再檢查濕度水平。我寧願水少一點也不願多——我可以隨時再次啟動水泵，但無法從植物中移除多餘的水。

![步驟 1，測量濕度。步驟 2，加水。步驟 3，等待水滲透到土壤中。步驟 4，重新測量濕度](../../../../../translated_images/tw/soil-moisture-delay.865f3fae206db01d.webp)

這意味著最佳的澆水流程應該是：

* 啟動水泵 5 秒
* 等待 20 秒
* 檢查土壤濕度
* 如果濕度水平仍高於需求，重複上述步驟

5 秒對於水泵來說可能太長，特別是當濕度水平僅略高於需求時。最佳的時間設定方式是先嘗試，然後根據感測器數據進行調整，形成一個持續的反饋循環。這甚至可以導致更精細的時間控制，例如每超過需求濕度 100 就啟動水泵 1 秒，而不是固定的 5 秒。

✅ 做些研究：是否還有其他時間考量？是否可以在任何時候只要土壤濕度過低就澆水，還是有特定的時間適合或不適合澆水？

> 💁 在控制戶外種植的自動灌溉系統時，天氣預測也可以納入考量。如果預計會下雨，那麼可以暫停澆水，等雨停後再檢查土壤是否已經足夠濕潤。這樣比在下雨前澆水更有效率，避免浪費水資源。

## 在植物控制伺服器中加入時間控制

伺服器程式碼可以修改以增加對澆水週期時間控制的功能，並等待土壤濕度水平的變化。控制繼電器時間的伺服器邏輯如下：

1. 接收到遙測訊息
1. 檢查土壤濕度水平
1. 如果濕度正常，則不執行任何操作。如果讀數過高（表示土壤濕度過低），則：
    1. 發送指令啟動繼電器
    1. 等待 5 秒
    1. 發送指令關閉繼電器
    1. 等待 20 秒讓土壤濕度穩定

澆水週期，即從接收到遙測訊息到準備再次處理土壤濕度水平的過程，大約需要 25 秒。我們每 10 秒發送一次土壤濕度數據，因此在伺服器等待土壤濕度穩定期間，可能會收到新的訊息，從而啟動另一個澆水週期。

有兩種解決方法：

* 修改 IoT 裝置程式碼，使其每分鐘只發送一次遙測數據，這樣澆水週期可以在下一次訊息發送前完成
* 在澆水週期期間取消訂閱遙測數據

第一種方法對於大型農場來說並不總是理想的解決方案。例如，農民可能希望在澆水過程中捕捉土壤濕度數據，以便日後分析，例如了解農場不同區域的水流情況，從而指導更有針對性的澆水。第二種方法更好——程式碼只是忽略無法使用的遙測數據，但數據仍然可以供其他訂閱的服務使用。

> 💁 IoT 數據並非僅從一個裝置發送到一個服務，而是許多裝置可以將數據發送到一個代理，許多服務可以從代理中接收數據。例如，一個服務可以監聽土壤濕度數據並將其存儲到資料庫中以供日後分析。另一個服務則可以監聽相同的遙測數據來控制灌溉系統。

### 任務 - 在植物控制伺服器中加入時間控制

更新你的伺服器程式碼，使繼電器運行 5 秒，然後等待 20 秒。

1. 如果尚未打開，請在 VS Code 中打開 `soil-moisture-sensor-server` 資料夾。確保虛擬環境已啟動。

1. 打開 `app.py` 檔案

1. 在現有的匯入語句下方，新增以下程式碼：

    ```python
    import threading
    ```

    這段程式碼從 Python 庫中匯入 `threading`，允許 Python 在等待時執行其他程式碼。

1. 在 `handle_telemetry` 函數之前新增以下程式碼：

    ```python
    water_time = 5
    wait_time = 20
    ```

    這段程式碼定義了繼電器運行的時間（`water_time`）以及之後檢查土壤濕度的等待時間（`wait_time`）。

1. 在這段程式碼下方新增以下內容：

    ```python
    def send_relay_command(client, state):
        command = { 'relay_on' : state }
        print("Sending message:", command)
        client.publish(server_command_topic, json.dumps(command))
    ```

    這段程式碼定義了一個名為 `send_relay_command` 的函數，用於通過 MQTT 發送指令來控制繼電器。遙測數據被創建為一個字典，然後轉換為 JSON 字串。傳遞給 `state` 的值決定繼電器應該開啟還是關閉。

1. 在 `send_relay_code` 函數之後新增以下程式碼：

    ```python
    def control_relay(client):
        print("Unsubscribing from telemetry")
        mqtt_client.unsubscribe(client_telemetry_topic)
    
        send_relay_command(client, True)
        time.sleep(water_time)
        send_relay_command(client, False)
    
        time.sleep(wait_time)
    
        print("Subscribing to telemetry")
        mqtt_client.subscribe(client_telemetry_topic)
    ```

    這段程式碼定義了一個函數，用於基於所需的時間控制繼電器。它首先取消訂閱遙測數據，這樣在澆水期間不會處理土壤濕度訊息。接著，它發送指令啟動繼電器，等待 `water_time`，然後發送指令關閉繼電器。最後，它等待 `wait_time` 秒讓土壤濕度穩定，然後重新訂閱遙測數據。

1. 將 `handle_telemetry` 函數更改為以下內容：

    ```python
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
        if payload['soil_moisture'] > 450:
            threading.Thread(target=control_relay, args=(client,)).start()
    ```

    這段程式碼檢查土壤濕度水平。如果大於 450，則土壤需要澆水，並調用 `control_relay` 函數。此函數在一個單獨的執行緒中運行，於背景執行。

1. 確保你的 IoT 裝置正在運行，然後執行此程式碼。改變土壤濕度水平，觀察繼電器的行為——它應該啟動 5 秒，然後至少關閉 20 秒，只有在土壤濕度不足時才會再次啟動。

    ```output
    (.venv) ➜  soil-moisture-sensor-server ✗ python app.py
    Message received: {'soil_moisture': 457}
    Unsubscribing from telemetry
    Sending message: {'relay_on': True}
    Sending message: {'relay_on': False}
    Subscribing to telemetry
    Message received: {'soil_moisture': 302}
    ```

    在模擬灌溉系統中測試此功能的一個好方法是使用乾燥的土壤，然後在繼電器啟動時手動倒水，並在繼電器關閉時停止倒水。

> 💁 你可以在 [code-timing](../../../../../2-farm/lessons/3-automated-plant-watering/code-timing) 資料夾中找到這段程式碼。

> 💁 如果你想使用水泵建造一個真實的灌溉系統，可以使用 [6V 水泵](https://www.seeedstudio.com/6V-Mini-Water-Pump-p-1945.html) 和 [USB 終端電源](https://www.adafruit.com/product/3628)。確保水泵的電源或輸出通過繼電器連接。

---

## 🚀 挑戰

你能想到其他 IoT 或電氣裝置也有類似的問題嗎？即執行器的效果需要一段時間才能反映到感測器上。你家裡或學校可能就有幾個這樣的例子。

* 它們測量什麼屬性？
* 執行器啟動後，屬性需要多長時間才能改變？
* 屬性超過所需值是否可以接受？
* 如果需要，如何將屬性恢復到所需值？

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/14)

## 複習與自學

* 閱讀更多關於繼電器的資訊，包括它們在電話交換機中的歷史用途：[繼電器維基百科頁面](https://wikipedia.org/wiki/Relay)。

## 作業

[建立更高效的澆水週期](assignment.md)

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。