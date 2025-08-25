<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a202fa5889790a3777bfc33dd9f4b459",
  "translation_date": "2025-08-25T00:12:30+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/wio-terminal-text-to-speech.md",
  "language_code": "tw"
}
-->
# 文字轉語音 - Wio Terminal

在本課程中，您將把文字轉換為語音，以提供語音回饋。

## 文字轉語音

您在上一課中使用的語音服務 SDK，可以用來將語音轉換為文字，同樣也可以用來將文字轉換回語音。

## 獲取語音列表

在請求語音時，您需要提供要使用的語音，因為語音可以使用多種不同的聲音生成。每種語言都支持一系列不同的聲音，您可以從語音服務 SDK 獲取每種語言支持的語音列表。微控制器的限制在此處顯現——獲取文字轉語音服務支持的語音列表的調用是一個超過 77KB 的 JSON 文件，遠遠超出 Wio Terminal 的處理能力。在撰寫本文時，完整列表包含 215 種語音，每種語音由如下的 JSON 文件定義：

```json
{
    "Name": "Microsoft Server Speech Text to Speech Voice (en-US, AriaNeural)",
    "DisplayName": "Aria",
    "LocalName": "Aria",
    "ShortName": "en-US-AriaNeural",
    "Gender": "Female",
    "Locale": "en-US",
    "StyleList": [
        "chat",
        "customerservice",
        "narration-professional",
        "newscast-casual",
        "newscast-formal",
        "cheerful",
        "empathetic"
    ],
    "SampleRateHertz": "24000",
    "VoiceType": "Neural",
    "Status": "GA"
}
```

此 JSON 是 **Aria** 語音的定義，該語音具有多種語音風格。在進行文字轉語音時，只需要短名稱，例如 `en-US-AriaNeural`。

與其在微控制器上下載並解碼整個列表，您需要編寫一些無伺服器代碼來檢索您使用的語言的語音列表，並從 Wio Terminal 調用此代碼。您的代碼可以從列表中選擇合適的語音，例如找到的第一個語音。

### 任務 - 創建一個無伺服器函數以獲取語音列表

1. 在 VS Code 中打開您的 `smart-timer-trigger` 專案，並打開終端，確保虛擬環境已啟動。如果未啟動，請終止並重新創建終端。

1. 打開 `local.settings.json` 文件，並添加語音 API 金鑰和位置的設置：

    ```json
    "SPEECH_KEY": "<key>",
    "SPEECH_LOCATION": "<location>"
    ```

    將 `<key>` 替換為您的語音服務資源的 API 金鑰。將 `<location>` 替換為您創建語音服務資源時使用的位置。

1. 使用以下命令在 VS Code 終端中函數應用專案的根文件夾內添加一個名為 `get-voices` 的 HTTP 觸發器：

    ```sh
    func new --name get-voices --template "HTTP trigger"
    ```

    這將創建一個名為 `get-voices` 的 HTTP 觸發器。

1. 將 `get-voices` 文件夾中的 `__init__.py` 文件內容替換為以下內容：

    ```python
    import json
    import os
    import requests
    
    import azure.functions as func
    
    def main(req: func.HttpRequest) -> func.HttpResponse:
        location = os.environ['SPEECH_LOCATION']
        speech_key = os.environ['SPEECH_KEY']
    
        req_body = req.get_json()
        language = req_body['language']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        voices = filter(lambda x: x['Locale'].lower() == language.lower(), voices_json)
        voices = map(lambda x: x['ShortName'], voices)
    
        return func.HttpResponse(json.dumps(list(voices)), status_code=200)
    ```

    此代碼向端點發送 HTTP 請求以獲取語音列表。語音列表是一個包含所有語言語音的大型 JSON 文件，因此會篩選出請求正文中指定語言的語音，然後提取短名稱並以 JSON 列表形式返回。短名稱是進行文字轉語音所需的值，因此僅返回此值。

    > 💁 您可以根據需要更改篩選條件，以選擇您想要的語音。

    這將數據大小從 77KB（撰寫本文時）減少到更小的 JSON 文件。例如，對於美國語音，大小為 408 字節。

1. 在本地運行您的函數應用。然後，您可以使用 curl 等工具調用此函數，就像測試 `text-to-timer` HTTP 觸發器一樣。確保以 JSON 正文的形式傳遞您的語言：

    ```json
    {
        "language":"<language>"
    }
    ```

    將 `<language>` 替換為您的語言，例如 `en-GB` 或 `zh-CN`。

> 💁 您可以在 [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) 文件夾中找到此代碼。

### 任務 - 從 Wio Terminal 獲取語音

1. 如果尚未打開，請在 VS Code 中打開 `smart-timer` 專案。

1. 打開 `config.h` 標頭文件，並添加您的函數應用的 URL：

    ```cpp
    const char *GET_VOICES_FUNCTION_URL = "<URL>";
    ```

    將 `<URL>` 替換為函數應用中 `get-voices` HTTP 觸發器的 URL。此 URL 與 `TEXT_TO_TIMER_FUNCTION_URL` 的值相同，只是函數名稱從 `text-to-timer` 改為 `get-voices`。

1. 在 `src` 文件夾中創建一個名為 `text_to_speech.h` 的新文件。此文件將用於定義一個將文字轉換為語音的類。

1. 在新的 `text_to_speech.h` 文件頂部添加以下 include 指令：

    ```cpp
    #pragma once

    #include <Arduino.h>
    #include <ArduinoJson.h>
    #include <HTTPClient.h>
    #include <Seeed_FS.h>
    #include <SD/Seeed_SD.h>
    #include <WiFiClient.h>
    #include <WiFiClientSecure.h>
    
    #include "config.h"
    #include "speech_to_text.h"
    ```

1. 在此之下添加以下代碼，聲明 `TextToSpeech` 類以及可以在應用程序的其他部分使用的實例：

    ```cpp
    class TextToSpeech
    {
    public:
    private:
    };
    
    TextToSpeech textToSpeech;
    ```

1. 為了調用函數應用，您需要聲明一個 WiFi 客戶端。在類的 `private` 部分添加以下內容：

    ```cpp
    WiFiClient _client;
    ```

1. 在 `private` 部分添加一個字段，用於存儲選擇的語音：

    ```cpp
    String _voice;
    ```

1. 在 `public` 部分添加一個 `init` 函數，用於獲取第一個語音：

    ```cpp
    void init()
    {
    }
    ```

1. 為了獲取語音，需要向函數應用發送一個包含語言的 JSON 文件。向 `init` 函數添加以下代碼以創建此 JSON 文件：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;

    String body;
    serializeJson(doc, body);
    ```

1. 接下來創建一個 `HTTPClient`，然後使用它調用函數應用以獲取語音，並發送 JSON 文件：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, GET_VOICES_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

1. 在此之下添加代碼以檢查響應代碼，如果是 200（成功），則提取語音列表，並從列表中檢索第一個語音：

    ```cpp
    if (httpResponseCode == 200)
    {
        String result = httpClient.getString();
        Serial.println(result);

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, result.c_str());

        JsonArray obj = doc.as<JsonArray>();
        _voice = obj[0].as<String>();

        Serial.print("Using voice ");
        Serial.println(_voice);
    }
    else
    {
        Serial.print("Failed to get voices - error ");
        Serial.println(httpResponseCode);
    }
    ```

1. 在此之後，結束 HTTP 客戶端連接：

    ```cpp
    httpClient.end();
    ```

1. 打開 `main.cpp` 文件，並在頂部添加以下 include 指令以包含此新標頭文件：

    ```cpp
    #include "text_to_speech.h"
    ```

1. 在 `setup` 函數中，`speechToText.init();` 調用之下添加以下內容以初始化 `TextToSpeech` 類：

    ```cpp
    textToSpeech.init();
    ```

1. 編譯此代碼，將其上傳到您的 Wio Terminal，並通過串行監視器進行測試。確保您的函數應用正在運行。

    您將看到函數應用返回的可用語音列表以及選擇的語音。

    ```output
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem1101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Connecting to WiFi..
    Connected!
    Got access token.
    ["en-US-JennyNeural", "en-US-JennyMultilingualNeural", "en-US-GuyNeural", "en-US-AriaNeural", "en-US-AmberNeural", "en-US-AnaNeural", "en-US-AshleyNeural", "en-US-BrandonNeural", "en-US-ChristopherNeural", "en-US-CoraNeural", "en-US-ElizabethNeural", "en-US-EricNeural", "en-US-JacobNeural", "en-US-MichelleNeural", "en-US-MonicaNeural", "en-US-AriaRUS", "en-US-BenjaminRUS", "en-US-GuyRUS", "en-US-ZiraRUS"]
    Using voice en-US-JennyNeural
    Ready.
    ```

## 將文字轉換為語音

一旦有了要使用的語音，就可以用它將文字轉換為語音。與語音列表相同的內存限制也適用於將文字轉換為語音，因此您需要將語音寫入 SD 卡，以便通過 ReSpeaker 播放。

> 💁 在本專案的早期課程中，您使用了閃存來存儲從麥克風捕獲的語音。本課程使用 SD 卡，因為使用 Seeed 音頻庫從 SD 卡播放音頻更為簡單。

還有另一個需要考慮的限制，即語音服務提供的音頻數據以及 Wio Terminal 支持的格式。與完整的計算機不同，微控制器的音頻庫對支持的音頻格式可能非常有限。例如，Seeed Arduino Audio 庫僅支持 44.1KHz 的音頻。Azure 語音服務可以提供多種格式的音頻，但它們都不使用此採樣率，只提供 8KHz、16KHz、24KHz 和 48KHz。這意味著音頻需要重新採樣為 44.1KHz，而這需要比 Wio Terminal 擁有的資源更多，尤其是內存。

當需要操作此類數據時，通常使用無伺服器代碼更好，尤其是當數據通過網絡調用獲取時。Wio Terminal 可以調用無伺服器函數，傳遞要轉換的文字，無伺服器函數可以調用語音服務將文字轉換為語音，並將音頻重新採樣為所需的採樣率。然後它可以以 Wio Terminal 需要的形式返回音頻，存儲在 SD 卡上並通過 ReSpeaker 播放。

### 任務 - 創建一個無伺服器函數以將文字轉換為語音

1. 在 VS Code 中打開您的 `smart-timer-trigger` 專案，並打開終端，確保虛擬環境已啟動。如果未啟動，請終止並重新創建終端。

1. 使用以下命令在 VS Code 終端中函數應用專案的根文件夾內添加一個名為 `text-to-speech` 的 HTTP 觸發器：

    ```sh
    func new --name text-to-speech --template "HTTP trigger"
    ```

    這將創建一個名為 `text-to-speech` 的 HTTP 觸發器。

1. [librosa](https://librosa.org) Pip 套件具有重新採樣音頻的功能，因此將其添加到 `requirements.txt` 文件：

    ```sh
    librosa
    ```

    添加後，使用以下命令從 VS Code 終端安裝 Pip 套件：

    ```sh
    pip install -r requirements.txt
    ```

    > ⚠️ 如果您使用的是 Linux，包括 Raspberry Pi OS，可能需要使用以下命令安裝 `libsndfile`：
    >
    > ```sh
    > sudo apt update
    > sudo apt install libsndfile1-dev
    > ```

1. 為了將文字轉換為語音，您不能直接使用語音 API 金鑰，而需要請求訪問令牌，使用 API 金鑰來驗證訪問令牌請求。打開 `text-to-speech` 文件夾中的 `__init__.py` 文件，並將其中的所有代碼替換為以下內容：

    ```python
    import io
    import os
    import requests
    
    import librosa
    import soundfile as sf
    import azure.functions as func
    
    location = os.environ['SPEECH_LOCATION']
    speech_key = os.environ['SPEECH_KEY']
    
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    此代碼定義了從設置中讀取的位置和語音金鑰常量。然後定義了 `get_access_token` 函數，用於檢索語音服務的訪問令牌。

1. 在此代碼下方添加以下內容：

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'

    def main(req: func.HttpRequest) -> func.HttpResponse:
        req_body = req.get_json()
        language = req_body['language']
        voice = req_body['voice']
        text = req_body['text']
    
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    
        ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
        ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
        ssml += text
        ssml += '</voice>'
        ssml += '</speak>'
    
        response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    
        raw_audio, sample_rate = librosa.load(io.BytesIO(response.content), sr=48000)
        resampled = librosa.resample(raw_audio, sample_rate, 44100)
        
        output_buffer = io.BytesIO()
        sf.write(output_buffer, resampled, 44100, 'PCM_16', format='wav')
        output_buffer.seek(0)
    
        return func.HttpResponse(output_buffer.read(), status_code=200)
    ```

    此代碼定義了將文字轉換為語音的 HTTP 觸發器。它從發送到請求的 JSON 正文中提取要轉換的文字、語言和語音，構建一些 SSML 以請求語音，然後調用相關的 REST API，使用訪問令牌進行身份驗證。此 REST API 調用返回音頻，編碼為 16 位、48KHz 單聲道 WAV 文件，由 `playback_format` 的值定義，該值發送到 REST API 調用。

    然後使用 `librosa` 將音頻從 48KHz 的採樣率重新採樣為 44.1KHz，然後將此音頻保存到二進制緩衝區，最後返回。

1. 在本地運行您的函數應用，或將其部署到雲端。然後，您可以使用 curl 等工具調用此函數，就像測試 `text-to-timer` HTTP 觸發器一樣。確保以 JSON 正文的形式傳遞語言、語音和文字：

    ```json
    {
        "language": "<language>",
        "voice": "<voice>",
        "text": "<text>"
    }
    ```

    將 `<language>` 替換為您的語言，例如 `en-GB` 或 `zh-CN`。將 `<voice>` 替換為您想要使用的語音。將 `<text>` 替換為您想要轉換為語音的文字。您可以將輸出保存到文件，並使用任何可以播放 WAV 文件的音頻播放器播放。

    例如，要使用美式英語的 Jenny Neural 語音將 "Hello" 轉換為語音，並且函數應用在本地運行，您可以使用以下 curl 命令：

    ```sh
    curl -X GET 'http://localhost:7071/api/text-to-speech' \
         -H 'Content-Type: application/json' \
         -o hello.wav \
         -d '{
           "language":"en-US",
           "voice": "en-US-JennyNeural",
           "text": "Hello"
         }'
    ```

    這將音頻保存到當前目錄中的 `hello.wav` 文件。

> 💁 您可以在 [code-spoken-response/functions](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/functions) 文件夾中找到此代碼。

### 任務 - 從 Wio Terminal 獲取語音

1. 如果尚未打開，請在 VS Code 中打開 `smart-timer` 專案。

1. 打開 `config.h` 標頭文件，並添加您的函數應用的 URL：

    ```cpp
    const char *TEXT_TO_SPEECH_FUNCTION_URL = "<URL>";
    ```

    將 `<URL>` 替換為函數應用中 `text-to-speech` HTTP 觸發器的 URL。此 URL 與 `TEXT_TO_TIMER_FUNCTION_URL` 的值相同，只是函數名稱從 `text-to-timer` 改為 `text-to-speech`。

1. 打開 `text_to_speech.h` 標頭文件，並在 `TextToSpeech` 類的 `public` 部分添加以下方法：

    ```cpp
    void convertTextToSpeech(String text)
    {
    }
    ```

1. 在 `convertTextToSpeech` 方法中，添加以下代碼以創建要發送到函數應用的 JSON：

    ```cpp
    DynamicJsonDocument doc(1024);
    doc["language"] = LANGUAGE;
    doc["voice"] = _voice;
    doc["text"] = text;

    String body;
    serializeJson(doc, body);
    ```

    此代碼將語言、語音和文字寫入 JSON 文件，然後將其序列化為字符串。

1. 在此之下，添加以下代碼以調用函數應用：

    ```cpp
    HTTPClient httpClient;
    httpClient.begin(_client, TEXT_TO_SPEECH_FUNCTION_URL);

    int httpResponseCode = httpClient.POST(body);
    ```

    此代碼創建一個 HTTPClient，然後使用 JSON 文件向文字轉語音 HTTP 觸發器發送 POST 請求。

1. 如果調用成功，函數應用返回的原始二進制數據可以流式傳輸到 SD 卡上的文件。添加以下代碼以完成此操作：

    ```cpp
    if (httpResponseCode == 200)
    {            
        File wav_file = SD.open("SPEECH.WAV", FILE_WRITE);
        httpClient.writeToStream(&wav_file);
        wav_file.close();
    }
    else
    {
        Serial.print("Failed to get speech - error ");
        Serial.println(httpResponseCode);
    }
    ```

    此代碼檢查響應，如果是 200（成功），則將二進制數據流式傳輸到 SD 卡根目錄中的 `SPEECH.WAV` 文件。

1. 在此方法的末尾，關閉 HTTP 連接：

    ```cpp
    httpClient.end();
    ```

1. 現在可以將要說的文字轉換為音頻。在 `main.cpp` 文件中，將以下行添加到 `say` 函數的末尾，以將要說的文字轉換為音頻：
```cpp
    textToSpeech.convertTextToSpeech(text);
    ```

### 任務 - 從你的 Wio Terminal 播放音頻

**即將推出**

## 將你的 Functions App 部署到雲端

在本地運行 Functions App 的原因是因為 Linux 上的 `librosa` Pip 套件依賴於一個預設未安裝的庫，必須先安裝該庫才能讓 Functions App 正常運行。Functions App 是無伺服器的——你無法自行管理伺服器，因此無法事先安裝該庫。

解決方法是使用 Docker 容器來部署你的 Functions App。每當需要啟動新的 Functions App 實例時（例如需求超過可用資源，或者 Functions App 長時間未使用而被關閉），雲端會部署該容器。

你可以在 [Microsoft Docs 上的使用自定義容器在 Linux 上創建 Function 的文檔](https://docs.microsoft.com/azure/azure-functions/functions-create-function-linux-custom-image?WT.mc_id=academic-17441-jabenn&tabs=bash%2Cazurecli&pivots=programming-language-python) 中找到設置 Functions App 並通過 Docker 部署的指導。

部署完成後，你可以移植你的 Wio Terminal 代碼以訪問該功能：

1. 將 Azure Functions 證書添加到 `config.h`：

    ```cpp
    const char *FUNCTIONS_CERTIFICATE =
        "-----BEGIN CERTIFICATE-----\r\n"
        "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\r\n"
        "-----END CERTIFICATE-----\r\n";
    ```

1. 將所有包含 `<WiFiClient.h>` 的地方更改為 `<WiFiClientSecure.h>`。

1. 將所有 `WiFiClient` 字段更改為 `WiFiClientSecure`。

1. 在每個包含 `WiFiClientSecure` 字段的類中，添加一個構造函數，並在該構造函數中設置證書：

    ```cpp
    _client.setCACert(FUNCTIONS_CERTIFICATE);
    ```

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原文文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。