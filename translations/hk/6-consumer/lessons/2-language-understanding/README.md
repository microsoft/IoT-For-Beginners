<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "6f4ba69d77f16c4a5110623a96a215c3",
  "translation_date": "2025-08-26T15:24:18+00:00",
  "source_file": "6-consumer/lessons/2-language-understanding/README.md",
  "language_code": "hk"
}
-->
# 理解語言

![本課程的手繪筆記概覽](../../../../../translated_images/lesson-22.6148ea28500d9e00c396aaa2649935fb6641362c8f03d8e5e90a676977ab01dd.hk.jpg)

> 手繪筆記由 [Nitya Narasimhan](https://github.com/nitya) 提供。點擊圖片查看更大版本。

## 課前測驗

[課前測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/43)

## 簡介

在上一課中，你已經將語音轉換為文字。若要將其用於編程一個智能計時器，你的程式需要理解所說的內容。你可以假設使用者會說固定的短語，例如「設置一個3分鐘的計時器」，並解析該表達式以獲取計時器的時間，但這樣的方式對使用者來說並不友好。如果使用者說「設置一個計時器為3分鐘」，你或我能理解其意思，但你的程式無法理解，因為它預期的是固定短語。

這就是語言理解的作用所在，利用人工智能模型來解釋文字並返回所需的細節。例如，它能夠理解「設置一個3分鐘的計時器」和「設置一個計時器為3分鐘」都表示需要一個3分鐘的計時器。

在本課中，你將學習語言理解模型，如何創建、訓練它們，並在程式中使用它們。

本課將涵蓋：

* [語言理解](../../../../../6-consumer/lessons/2-language-understanding)
* [創建語言理解模型](../../../../../6-consumer/lessons/2-language-understanding)
* [意圖和實體](../../../../../6-consumer/lessons/2-language-understanding)
* [使用語言理解模型](../../../../../6-consumer/lessons/2-language-understanding)

## 語言理解

人類已經使用語言進行溝通數十萬年。我們通過文字、聲音或行動來交流，並理解所說的內容，不僅是文字、聲音或行動的意思，還包括它們的上下文。我們能理解真誠與諷刺，讓相同的文字因語氣不同而表達不同的意思。

✅ 想一想你最近的一些對話。有多少內容對電腦來說會因為需要上下文而難以理解？

語言理解，也稱為自然語言理解，是人工智能的一個分支，屬於自然語言處理（NLP）的一部分，專注於閱讀理解，試圖理解文字或句子的細節。如果你使用過語音助手，例如 Alexa 或 Siri，那麼你已經使用過語言理解服務。這些服務是背後的人工智能技術，能將「Alexa，播放泰勒·斯威夫特的最新專輯」轉化為我女兒在客廳裡隨著她最喜歡的音樂跳舞。

> 💁 儘管電腦技術已經取得了很大的進步，但在真正理解文字方面仍有很長的路要走。當我們提到電腦的語言理解時，並不是指像人類交流那樣高級，而是指從一些文字中提取關鍵細節。

作為人類，我們幾乎不需要思考就能理解語言。如果我請另一個人「播放泰勒·斯威夫特的最新專輯」，他們會本能地知道我的意思。對於電腦來說，這就困難得多。它需要將文字（從語音轉換而來）分解並提取以下信息：

* 需要播放音樂
* 音樂的演唱者是泰勒·斯威夫特
* 具體的音樂是一整張專輯，包含多首按順序排列的曲目
* 泰勒·斯威夫特有很多專輯，因此需要按時間順序排序，並選擇最新發行的專輯

✅ 想一想你在提出請求時說過的一些句子，例如點咖啡或請家人遞東西。試著將這些句子分解為電腦需要提取的關鍵信息。

語言理解模型是訓練用來從語言中提取特定細節的人工智能模型，並通過遷移學習針對特定任務進行訓練，就像你使用少量圖片訓練自定義視覺模型一樣。你可以採用一個模型，然後用你希望它理解的文字進行訓練。

## 創建語言理解模型

![LUIS 標誌](../../../../../translated_images/luis-logo.5cb4f3e88c020ee6df4f614e8831f4a4b6809a7247bf52085fb48d629ef9be52.hk.png)

你可以使用 LUIS（Language Understanding Intelligent Service），一個來自 Microsoft 的語言理解服務，來創建語言理解模型。LUIS 是認知服務的一部分。

### 任務 - 創建一個編輯資源

要使用 LUIS，你需要創建一個編輯資源。

1. 使用以下命令在你的 `smart-timer` 資源組中創建一個編輯資源：

    ```python
    az cognitiveservices account create --name smart-timer-luis-authoring \
                                        --resource-group smart-timer \
                                        --kind LUIS.Authoring \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    將 `<location>` 替換為創建資源組時使用的位置。

    > ⚠️ LUIS 並非在所有地區都可用，如果你收到以下錯誤：
    >
    > ```output
    > InvalidApiSetId: The account type 'LUIS.Authoring' is either invalid or unavailable in given region.
    > ```
    >
    > 請選擇其他地區。

    這將創建一個免費層的 LUIS 編輯資源。

### 任務 - 創建一個語言理解應用

1. 在瀏覽器中打開 LUIS 入口網站 [luis.ai](https://luis.ai?WT.mc_id=academic-17441-jabenn)，並使用你在 Azure 中使用的相同帳戶登錄。

1. 按照對話框中的指示選擇你的 Azure 訂閱，然後選擇你剛剛創建的 `smart-timer-luis-authoring` 資源。

1. 從 *Conversation apps* 列表中，選擇 **New app** 按鈕來創建一個新應用。將新應用命名為 `smart-timer`，並將 *Culture* 設置為你的語言。

    > 💁 有一個預測資源的字段。你可以為預測單獨創建一個資源，但免費的編輯資源每月允許 1,000 次預測，對於開發來說應該足夠，因此可以留空。

1. 閱讀創建應用後出現的指南，了解訓練語言理解模型所需的步驟。完成後關閉該指南。

## 意圖和實體

語言理解基於 *意圖* 和 *實體*。意圖是文字的目的，例如播放音樂、設置計時器或點餐。實體是意圖所指的對象，例如專輯、計時器的時長或食物的種類。模型解釋的每個句子應至少有一個意圖，並可選擇性地包含一個或多個實體。

一些例子：

| 句子                                                | 意圖             | 實體                                       |
| --------------------------------------------------- | ---------------- | ------------------------------------------ |
| 「播放泰勒·斯威夫特的最新專輯」                     | *播放音樂*       | *泰勒·斯威夫特的最新專輯*                 |
| 「設置一個3分鐘的計時器」                           | *設置計時器*     | *3分鐘*                                   |
| 「取消我的計時器」                                  | *取消計時器*     | 無                                         |
| 「點3個大號菠蘿披薩和一份凱撒沙拉」                 | *點餐*           | *3個大號菠蘿披薩*，*凱撒沙拉*             |

✅ 將你之前想到的句子，試著找出其中的意圖和實體。

要訓練 LUIS，首先需要設置實體。這些實體可以是固定的術語列表，或者從文字中學習。例如，你可以提供菜單中可用食物的固定列表，並為每個詞提供變體（或同義詞），例如 *egg plant* 和 *aubergine* 作為 *aubergine* 的變體。LUIS 還提供了一些可用的預設實體，例如數字和地點。

對於設置計時器，你可以使用預設的數字實體來表示時間，並創建另一個實體來表示單位，例如分鐘和秒。每個單位應有多個變體以涵蓋單數和複數形式，例如 minute 和 minutes。

設置實體後，接下來創建意圖。這些意圖是基於你提供的示例句子（稱為語句）由模型學習的。例如，對於 *設置計時器* 的意圖，你可以提供以下句子：

* `設置一個1秒的計時器`
* `設置一個計時器為1分鐘12秒`
* `設置一個計時器為3分鐘`
* `設置一個9分鐘30秒的計時器`

然後，你需要告訴 LUIS 這些句子中的哪些部分對應於實體：

![句子「設置一個計時器為1分鐘12秒」分解為實體](../../../../../translated_images/sentence-as-intent-entities.301401696f992259.hk.png)

句子 `設置一個計時器為1分鐘12秒` 的意圖是 `設置計時器`。它還有兩個實體，每個實體有兩個值：

|            | 時間 | 單位   |
| ---------- | ---: | ------ |
| 1分鐘      | 1    | 分鐘   |
| 12秒       | 12   | 秒     |

要訓練一個好的模型，你需要提供多種不同的示例句子，以涵蓋人們可能用來表達相同意思的多種方式。

> 💁 與任何人工智能模型一樣，訓練所用的數據越多且越準確，模型的效果就越好。

✅ 想一想你可能用來表達相同意思的不同方式，並期望人類能理解。

### 任務 - 向語言理解模型添加實體

對於計時器，你需要添加兩個實體——一個表示時間單位（分鐘或秒），另一個表示分鐘或秒的數量。

你可以在 Microsoft Docs 的 [快速入門：在 LUIS 入口網站中構建應用](https://docs.microsoft.com/azure/cognitive-services/luis/luis-get-started-create-app?WT.mc_id=academic-17441-jabenn) 文檔中找到使用 LUIS 入口網站的指導。

1. 在 LUIS 入口網站中，選擇 *Entities* 標籤，然後通過選擇 **Add prebuilt entity** 按鈕添加 *number* 預設實體，從列表中選擇 *number*。

1. 使用 **Create** 按鈕創建一個新的實體來表示時間單位。將實體命名為 `time unit`，並將類型設置為 *List*。在 *Normalized values* 列表中添加 `minute` 和 `second` 的值，並在 *synonyms* 列表中添加單數和複數形式作為同義詞。每添加一個同義詞後按 `return` 鍵將其添加到列表中。

    | 標準化值       | 同義詞            |
    | -------------- | ----------------- |
    | minute         | minute, minutes  |
    | second         | second, seconds  |

### 任務 - 向語言理解模型添加意圖

1. 在 *Intents* 標籤中，選擇 **Create** 按鈕來創建一個新意圖。將此意圖命名為 `set timer`。

1. 在示例中，輸入設置計時器的不同方式，使用分鐘、秒以及分鐘和秒的組合。例如：

    * `設置一個1秒的計時器`
    * `設置一個4分鐘的計時器`
    * `設置一個四分鐘六秒的計時器`
    * `設置一個9分鐘30秒的計時器`
    * `設置一個計時器為1分鐘12秒`
    * `設置一個計時器為3分鐘`
    * `設置一個計時器為3分鐘1秒`
    * `設置一個計時器為三分鐘一秒`
    * `設置一個計時器為1分鐘1秒`
    * `設置一個計時器為30秒`
    * `設置一個計時器為1秒`

    混合使用數字的文字形式和數字形式，讓模型學會處理兩者。

1. 當你輸入每個示例時，LUIS 會開始檢測實體，並將檢測到的實體用下劃線標記並標籤。

    ![示例中數字和時間單位被 LUIS 用下劃線標記](../../../../../translated_images/luis-intent-examples.25716580b2d2723cf1bafdf277d015c7f046d8cfa20f27bddf3a0873ec45fab7.hk.png)

### 任務 - 訓練和測試模型

1. 配置好實體和意圖後，可以使用頂部菜單中的 **Train** 按鈕訓練模型。選擇此按鈕，模型應在幾秒鐘內完成訓練。訓練期間按鈕會變灰，完成後會重新啟用。

1. 從頂部菜單中選擇 **Test** 按鈕來測試語言理解模型。輸入例如 `設置一個計時器為5分鐘4秒` 的文字並按回車鍵。句子會出現在你輸入文字的文本框下方，並在其下方顯示 *top intent*，即檢測到的最高概率的意圖。這應該是 `set timer`。意圖名稱後會顯示檢測到該意圖的概率。

1. 選擇 **Inspect** 選項查看結果的詳細信息。你將看到最高分的意圖及其概率百分比，以及檢測到的實體列表。

1. 測試完成後，關閉 *Test* 面板。

### 任務 - 發佈模型

要從程式中使用此模型，你需要將其發佈。從 LUIS 發佈時，你可以選擇發佈到測試用的暫存環境或正式發佈的生產環境。在本課中，暫存環境即可。

1. 在 LUIS 入口網站中，從頂部菜單中選擇 **Publish** 按鈕。

1. 確保選擇了 *Staging slot*，然後選擇 **Done**。應用發佈後，你會看到通知。

1. 你可以使用 curl 測試此模型。要構建 curl 命令，你需要三個值——端點、應用程式 ID（App ID）和 API 金鑰。這些可以從頂部菜單中選擇 **MANAGE** 標籤後訪問。

    1. 在 *Settings* 部分，複製 App ID
1. 從 *Azure 資源* 部分選擇 *Authoring Resource*，然後複製 *Primary Key* 和 *Endpoint URL*

1. 在命令提示符或終端中運行以下 curl 命令：

    ```sh
    curl "<endpoint url>/luis/prediction/v3.0/apps/<app id>/slots/staging/predict" \
          --request GET \
          --get \
          --data "subscription-key=<primary key>" \
          --data "verbose=false" \
          --data "show-all-intents=true" \
          --data-urlencode "query=<sentence>"
    ```

    將 `<endpoint url>` 替換為 *Azure 資源* 部分中的 Endpoint URL。

    將 `<app id>` 替換為 *Settings* 部分中的 App ID。

    將 `<primary key>` 替換為 *Azure 資源* 部分中的 Primary Key。

    將 `<sentence>` 替換為您想測試的句子。

1. 此調用的輸出將是一個 JSON 文件，詳細說明查詢、最高意圖以及按類型劃分的實體列表。

    ```JSON
    {
        "query": "set a timer for 45 minutes and 12 seconds",
        "prediction": {
            "topIntent": "set timer",
            "intents": {
                "set timer": {
                    "score": 0.97031575
                },
                "None": {
                    "score": 0.02205793
                }
            },
            "entities": {
                "number": [
                    45,
                    12
                ],
                "time-unit": [
                    [
                        "minute"
                    ],
                    [
                        "second"
                    ]
                ]
            }
        }
    }
    ```

    上述 JSON 是通過查詢 `set a timer for 45 minutes and 12 seconds` 生成的：

    * `set timer` 是最高意圖，概率為 97%。
    * 檢測到兩個 *number* 實體，分別是 `45` 和 `12`。
    * 檢測到兩個 *time-unit* 實體，分別是 `minute` 和 `second`。

## 使用語言理解模型

一旦發佈，LUIS 模型可以從代碼中調用。在之前的課程中，您已經使用 IoT Hub 處理與雲服務的通信，發送遙測數據並接收命令。這種方式是非常異步的——一旦遙測數據發送出去，您的代碼不會等待響應，如果雲服務宕機，您也不會知道。

對於智能計時器，我們希望立即獲得響應，這樣我們可以告訴用戶計時器已設置，或者提醒他們雲服務不可用。為此，我們的 IoT 設備將直接調用一個 Web Endpoint，而不是依賴 IoT Hub。

與其從 IoT 設備直接調用 LUIS，您可以使用無伺服器代碼和一種不同類型的觸發器——HTTP 觸發器。這允許您的函數應用程序監聽 REST 請求並對其進行響應。此函數將成為您的設備可以調用的 REST Endpoint。

> 💁 雖然您可以直接從 IoT 設備調用 LUIS，但使用無伺服器代碼會更好。這樣，當您想更改調用的 LUIS 應用程序時，例如訓練了一個更好的模型或用不同語言訓練了一個模型，您只需更新雲端代碼，而不需要重新部署到可能成千上萬甚至數百萬的 IoT 設備。

### 任務 - 創建無伺服器函數應用程序

1. 創建一個名為 `smart-timer-trigger` 的 Azure Functions 應用程序，並在 VS Code 中打開它。

1. 使用以下命令在 VS Code 終端中為此應用程序添加一個名為 `speech-trigger` 的 HTTP 觸發器：

    ```sh
    func new --name text-to-timer --template "HTTP trigger"
    ```

    這將創建一個名為 `text-to-timer` 的 HTTP 觸發器。

1. 通過運行函數應用程序來測試 HTTP 觸發器。運行時，您將在輸出中看到列出的 Endpoint：

    ```output
    Functions:
    
            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    ```

    通過在瀏覽器中加載 [http://localhost:7071/api/text-to-timer](http://localhost:7071/api/text-to-timer) URL 進行測試。

    ```output
    This HTTP triggered function executed successfully. Pass a name in the query string or in the request body for a personalized response.
    ```

### 任務 - 使用語言理解模型

1. LUIS 的 SDK 可通過 Pip 包獲得。將以下行添加到 `requirements.txt` 文件中以添加對此包的依賴：

    ```sh
    azure-cognitiveservices-language-luis
    ```

1. 確保 VS Code 終端已激活虛擬環境，並運行以下命令來安裝 Pip 包：

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 如果出現錯誤，您可能需要使用以下命令升級 pip：
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. 在 `local.settings.json` 文件中為您的 LUIS API Key、Endpoint URL 和 App ID 添加新條目，這些信息可以從 LUIS 入口網站的 **MANAGE** 標籤中獲得：

    ```JSON
    "LUIS_KEY": "<primary key>",
    "LUIS_ENDPOINT_URL": "<endpoint url>",
    "LUIS_APP_ID": "<app id>"
    ```

    將 `<endpoint url>` 替換為 **MANAGE** 標籤中 *Azure 資源* 部分的 Endpoint URL。這將是 `https://<location>.api.cognitive.microsoft.com/`。

    將 `<app id>` 替換為 **MANAGE** 標籤中 *Settings* 部分的 App ID。

    將 `<primary key>` 替換為 **MANAGE** 標籤中 *Azure 資源* 部分的 Primary Key。

1. 將以下導入添加到 `__init__.py` 文件中：

    ```python
    import json
    import os
    from azure.cognitiveservices.language.luis.runtime import LUISRuntimeClient
    from msrest.authentication import CognitiveServicesCredentials
    ```

    這將導入一些系統庫以及與 LUIS 交互的庫。

1. 刪除 `main` 方法的內容，並添加以下代碼：

    ```python
    luis_key = os.environ['LUIS_KEY']
    endpoint_url = os.environ['LUIS_ENDPOINT_URL']
    app_id = os.environ['LUIS_APP_ID']
    
    credentials = CognitiveServicesCredentials(luis_key)
    client = LUISRuntimeClient(endpoint=endpoint_url, credentials=credentials)
    ```

    這將加載您在 `local.settings.json` 文件中為 LUIS 應用程序添加的值，創建一個帶有 API Key 的憑據對象，然後創建一個 LUIS 客戶端對象以與您的 LUIS 應用程序交互。

1. 此 HTTP 觸發器將通過 JSON 傳遞要理解的文本，文本位於名為 `text` 的屬性中。以下代碼從 HTTP 請求的主體中提取該值，並將其記錄到控制台。將此代碼添加到 `main` 函數中：

    ```python
    req_body = req.get_json()
    text = req_body['text']
    logging.info(f'Request - {text}')
    ```

1. 通過發送預測請求（包含要預測的文本的 JSON 文件）來向 LUIS 請求預測。使用以下代碼創建此請求：

    ```python
    prediction_request = { 'query' : text }
    ```

1. 然後可以使用應用程序發佈到的暫存槽將此請求發送到 LUIS：

    ```python
    prediction_response = client.prediction.get_slot_prediction(app_id, 'Staging', prediction_request)
    ```

1. 預測響應包含最高意圖（具有最高預測分數的意圖）以及實體。如果最高意圖是 `set timer`，則可以讀取實體以獲取計時器所需的時間：

    ```python
    if prediction_response.prediction.top_intent == 'set timer':
        numbers = prediction_response.prediction.entities['number']
        time_units = prediction_response.prediction.entities['time unit']
        total_seconds = 0
    ```

    `number` 實體將是一個數字數組。例如，如果您說 *"Set a four minute 17 second timer."*，則 `number` 數組將包含兩個整數 - 4 和 17。

    `time unit` 實體將是一個字符串數組的數組，每個時間單位作為數組中的一個字符串。例如，如果您說 *"Set a four minute 17 second timer."*，則 `time unit` 數組將包含兩個單值數組 - `['minute']` 和 `['second']`。

    這些實體的 JSON 版本為 *"Set a four minute 17 second timer."*：

    ```json
    {
        "number": [4, 17],
        "time unit": [
            ["minute"],
            ["second"]
        ]
    }
    ```

    此代碼還定義了一個計時器總時間（以秒為單位）的計數器。這將由實體中的值填充。

1. 實體之間沒有鏈接，但我們可以對它們做出一些假設。它們將按照說話的順序排列，因此可以使用數組中的位置來確定哪個數字與哪個時間單位匹配。例如：

    * *"Set a 30 second timer"* - 這將有一個數字 `30` 和一個時間單位 `second`，因此單個數字將匹配單個時間單位。
    * *"Set a 2 minute and 30 second timer"* - 這將有兩個數字 `2` 和 `30`，以及兩個時間單位 `minute` 和 `second`，因此第一個數字將對應第一個時間單位（2 分鐘），第二個數字對應第二個時間單位（30 秒）。

    以下代碼獲取 `number` 實體中的項目數，並使用該數量從每個數組中提取第一個項目，然後是第二個，依此類推。將此代碼添加到 `if` 塊內。

    ```python
    for i in range(0, len(numbers)):
        number = numbers[i]
        time_unit = time_units[i][0]
    ```

    對於 *"Set a four minute 17 second timer."*，這將循環兩次，給出以下值：

    | 循環次數 | `number` | `time_unit` |
    | -------: | -------: | ----------- |
    | 0        | 4        | minute      |
    | 1        | 17       | second      |

1. 在此循環內，使用數字和時間單位計算計時器的總時間，為每分鐘添加 60 秒，並為每秒添加相應的秒數。

    ```python
    if time_unit == 'minute':
        total_seconds += number * 60
    else:
        total_seconds += number
    ```

1. 在實體循環之外，記錄計時器的總時間：

    ```python
    logging.info(f'Timer required for {total_seconds} seconds')
    ```

1. 計時器的秒數需要作為 HTTP 響應從函數返回。在 `if` 塊的末尾添加以下代碼：

    ```python
    payload = {
        'seconds': total_seconds
    }
    return func.HttpResponse(json.dumps(payload), status_code=200)
    ```

    此代碼創建一個包含計時器總秒數的有效負載，將其轉換為 JSON 字符串，並以狀態碼 200（表示調用成功）作為 HTTP 結果返回。

1. 最後，在 `if` 塊之外，處理未識別意圖的情況，返回錯誤代碼：

    ```python
    return func.HttpResponse(status_code=404)
    ```

    404 是 *未找到* 的狀態碼。

1. 運行函數應用程序並使用 curl 測試。

    ```sh
    curl --request POST 'http://localhost:7071/api/text-to-timer' \
         --header 'Content-Type: application/json' \
         --include \
         --data '{"text":"<text>"}'
    ```

    將 `<text>` 替換為您的請求文本，例如 `set a 2 minutes 27 second timer`。

    您將在函數應用程序的輸出中看到以下內容：

    ```output
    Functions:

            text-to-timer: [GET,POST] http://localhost:7071/api/text-to-timer
    
    For detailed output, run func with --verbose flag.
    [2021-06-26T19:45:14.502Z] Worker process started and initialized.
    [2021-06-26T19:45:19.338Z] Host lock lease acquired by instance ID '000000000000000000000000951CAE4E'.
    [2021-06-26T19:45:52.059Z] Executing 'Functions.text-to-timer' (Reason='This function was programmatically called via the host APIs.', Id=f68bfb90-30e4-47a5-99da-126b66218e81)
    [2021-06-26T19:45:53.577Z] Timer required for 147 seconds
    [2021-06-26T19:45:53.746Z] Executed 'Functions.text-to-timer' (Succeeded, Id=f68bfb90-30e4-47a5-99da-126b66218e81, Duration=1750ms)
    ```

    curl 的調用將返回以下內容：

    ```output
    HTTP/1.1 200 OK
    Date: Tue, 29 Jun 2021 01:14:11 GMT
    Content-Type: text/plain; charset=utf-8
    Server: Kestrel
    Transfer-Encoding: chunked
    
    {"seconds": 147}
    ```

    計時器的秒數位於 `"seconds"` 值中。

> 💁 您可以在 [code/functions](../../../../../6-consumer/lessons/2-language-understanding/code/functions) 文件夾中找到此代碼。

### 任務 - 讓您的函數可供 IoT 設備使用

1. 為了讓您的 IoT 設備調用您的 REST Endpoint，它需要知道 URL。當您之前訪問它時，您使用了 `localhost`，這是一個訪問本地機器上 REST Endpoint 的快捷方式。要讓您的 IoT 設備訪問，您需要將其發佈到雲端，或者獲取您的 IP 地址以在本地訪問。

    > ⚠️ 如果您使用的是 Wio Terminal，運行函數應用程序在本地會更容易，因為會有依賴庫，這意味著您無法像之前那樣部署函數應用程序。在本地運行函數應用程序並通過計算機的 IP 地址訪問它。如果您確實想部署到雲端，後續課程中將提供相關信息。

    * 發佈函數應用程序 - 按照之前課程中的說明將函數應用程序發佈到雲端。發佈後，URL 將是 `https://<APP_NAME>.azurewebsites.net/api/text-to-timer`，其中 `<APP_NAME>` 是您的函數應用程序名稱。確保也發佈您的本地設置。

      當使用 HTTP 觸發器時，它們默認通過函數應用程序密鑰進行保護。要獲取此密鑰，運行以下命令：

      ```sh
      az functionapp keys list --resource-group smart-timer \
                               --name <APP_NAME>                               
      ```

      從 `functionKeys` 部分複製 `default` 條目的值。

      ```output
      {
        "functionKeys": {
          "default": "sQO1LQaeK9N1qYD6SXeb/TctCmwQEkToLJU6Dw8TthNeUH8VA45hlA=="
        },
        "masterKey": "RSKOAIlyvvQEQt9dfpabJT018scaLpQu9p1poHIMCxx5LYrIQZyQ/g==",
        "systemKeys": {}
      }
      ```

      此密鑰需要作為查詢參數添加到 URL 中，因此最終的 URL 將是 `https://<APP_NAME>.azurewebsites.net/api/text-to-timer?code=<FUNCTION_KEY>`，其中 `<APP_NAME>` 是您的函數應用程序名稱，`<FUNCTION_KEY>` 是您的默認函數密鑰。

      > 💁 您可以使用 `function.json` 文件中的 `authlevel` 設置更改 HTTP 觸發器的授權類型。您可以在 [Microsoft Docs 上的 Azure Functions HTTP 觸發器文檔配置部分](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python#configuration) 中閱讀更多相關信息。

    * 在本地運行函數應用程序並使用 IP 地址訪問 - 您可以獲取計算機在本地網絡上的 IP 地址，並使用該地址構建 URL。

      獲取您的 IP 地址：

      * 在 Windows 10 上，請參考 [查找您的 IP 地址指南](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn)。
      * 在 macOS 上，請參考 [如何在 Mac 上查找 IP 地址指南](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac)。
      * 在 Linux 上，請參考 [如何在 Linux 中查找 IP 地址指南](https://opensource.com/article/18/5/how-find-ip-address-linux) 中的查找私有 IP 地址部分。

      獲取 IP 地址後，您將能夠通過 `http://`

:7071/api/text-to-timer`，其中 `<IP_ADDRESS>` 是你的 IP 地址，例如 `http://192.168.1.10:7071/api/text-to-timer`。

      > 💁 請注意這裡使用了 7071 埠，因此在 IP 地址後需要加上 `:7071`。

      > 💁 這僅在你的 IoT 裝置與電腦位於同一網絡時才有效。

1. 使用 curl 測試該端點。

---

## 🚀 挑戰

設置計時器有很多不同的請求方式。想想不同的方法來完成這件事，並將它們作為範例添加到你的 LUIS 應用中。測試這些範例，看看你的模型能否處理多種設置計時器的請求方式。

## 課後測驗

[課後測驗](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/44)

## 回顧與自學

* 在 [Microsoft Docs 的語言理解 (LUIS) 文件頁面](https://docs.microsoft.com/azure/cognitive-services/luis/?WT.mc_id=academic-17441-jabenn)上閱讀更多關於 LUIS 及其功能的資訊
* 在 [維基百科的自然語言理解頁面](https://wikipedia.org/wiki/Natural-language_understanding)上閱讀更多關於語言理解的資訊
* 在 [Microsoft Docs 的 Azure Functions HTTP 觸發器文件頁面](https://docs.microsoft.com/azure/azure-functions/functions-bindings-http-webhook-trigger?WT.mc_id=academic-17441-jabenn&tabs=python)上閱讀更多關於 HTTP 觸發器的資訊

## 作業

[取消計時器](assignment.md)

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始語言的文件應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。