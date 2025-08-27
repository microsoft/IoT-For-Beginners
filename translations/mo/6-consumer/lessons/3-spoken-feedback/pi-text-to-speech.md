<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-27T00:13:15+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "mo"
}
-->
# 將文字轉換為語音 - Raspberry Pi

在本課程的這部分，您將撰寫程式碼，使用語音服務將文字轉換為語音。

## 使用語音服務將文字轉換為語音

可以使用 REST API 將文字發送到語音服務，獲取語音作為音訊檔案，並在您的 IoT 裝置上播放。請求語音時，您需要提供使用的語音，因為語音可以使用多種不同的聲音生成。

每種語言都支援一系列不同的聲音，您可以對語音服務發送 REST 請求，以獲取每種語言支援的聲音列表。

### 任務 - 獲取聲音

1. 在 VS Code 中打開 `smart-timer` 專案。

1. 在 `say` 函數上方新增以下程式碼，以請求語言的聲音列表：

    ```python
    def get_voice():
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/voices/list'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token()
        }
    
        response = requests.get(url, headers=headers)
        voices_json = json.loads(response.text)
    
        first_voice = next(x for x in voices_json if x['Locale'].lower() == language.lower() and x['VoiceType'] == 'Neural')
        return first_voice['ShortName']
    
    voice = get_voice()
    print(f'Using voice {voice}')
    ```

    此程式碼定義了一個名為 `get_voice` 的函數，該函數使用語音服務獲取聲音列表。然後找到與正在使用的語言匹配的第一個聲音。

    接著呼叫此函數以儲存第一個聲音，並將聲音名稱列印到控制台。此聲音可以請求一次，並在每次將文字轉換為語音時使用該值。

    > 💁 您可以從 [Microsoft Docs 的語言和聲音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) 獲取支援的聲音完整列表。如果您想使用特定的聲音，可以移除此函數並直接將聲音名稱硬編碼到文件中的聲音名稱。例如：
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### 任務 - 將文字轉換為語音

1. 在此程式碼下方，定義一個常數，用於從語音服務檢索音訊格式。當您請求音訊時，可以使用多種不同的格式。

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    您可以使用的格式取決於您的硬體。如果在播放音訊時出現 `Invalid sample rate` 錯誤，請將其更改為其他值。您可以在 [Microsoft Docs 的文字轉語音 REST API 文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs) 中找到支援的值列表。您需要使用 `riff` 格式音訊，可嘗試的值包括 `riff-16khz-16bit-mono-pcm`、`riff-24khz-16bit-mono-pcm` 和 `riff-48khz-16bit-mono-pcm`。

1. 在此程式碼下方，宣告一個名為 `get_speech` 的函數，該函數將使用語音服務 REST API 將文字轉換為語音：

    ```python
    def get_speech(text):
    ```

1. 在 `get_speech` 函數中，定義要呼叫的 URL 和要傳遞的標頭：

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    此程式碼設定標頭以使用生成的存取權杖，將內容設定為 SSML，並定義所需的音訊格式。

1. 在此程式碼下方，定義要發送到 REST API 的 SSML：

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    此 SSML 設定要使用的語言和聲音，以及要轉換的文字。

1. 最後，在此函數中新增程式碼以進行 REST 請求並返回二進位音訊資料：

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### 任務 - 播放音訊

1. 在 `get_speech` 函數下方，定義一個新函數以播放 REST API 呼叫返回的音訊：

    ```python
    def play_speech(speech):
    ```

1. 傳遞給此函數的 `speech` 將是 REST API 返回的二進位音訊資料。使用以下程式碼將其作為波形檔案打開，並傳遞給 PyAudio 播放音訊：

    ```python
    def play_speech(speech):
        with wave.open(speech, 'rb') as wave_file:
            stream = audio.open(format=audio.get_format_from_width(wave_file.getsampwidth()),
                                channels=wave_file.getnchannels(),
                                rate=wave_file.getframerate(),
                                output_device_index=speaker_card_number,
                                output=True)

            data = wave_file.readframes(4096)

            while len(data) > 0:
                stream.write(data)
                data = wave_file.readframes(4096)

            stream.stop_stream()
            stream.close()
    ```

    此程式碼使用 PyAudio 流，與捕捉音訊相同。不同之處在於此流被設定為輸出流，並從音訊資料中讀取資料並推送到流中。

    與硬編碼流的詳細資訊（例如取樣率）不同，此處是從音訊資料中讀取。

1. 將 `say` 函數的內容替換為以下程式碼：

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    此程式碼將文字轉換為二進位音訊資料，並播放音訊。

1. 執行應用程式，並確保函數應用程式也在執行。設定一些計時器，您將聽到語音回應，告訴您計時器已設定，然後在計時器完成時聽到另一個語音回應。

    如果出現 `Invalid sample rate` 錯誤，請按照上述說明更改 `playback_format`。

> 💁 您可以在 [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi) 資料夾中找到此程式碼。

😀 您的計時器程式成功了！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。