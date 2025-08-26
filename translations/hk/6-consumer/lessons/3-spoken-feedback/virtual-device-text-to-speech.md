<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-26T15:32:49+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "hk"
}
-->
# 將文字轉換為語音 - 虛擬 IoT 裝置

在這部分課程中，你將撰寫程式碼，使用語音服務將文字轉換為語音。

## 將文字轉換為語音

在上一課中，你使用語音服務 SDK 將語音轉換為文字，現在可以使用相同的 SDK 將文字轉換回語音。在請求語音時，你需要指定使用的語音，因為語音可以由多種不同的聲音生成。

每種語言都支援多種不同的聲音，你可以透過語音服務 SDK 獲取每種語言支援的聲音清單。

### 任務 - 將文字轉換為語音

1. 在 VS Code 中打開 `smart-timer` 專案，並確保終端機中已載入虛擬環境。

1. 從 `azure.cognitiveservices.speech` 套件中匯入 `SpeechSynthesizer`，將其加入現有的匯入部分：

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. 在 `say` 函式上方，建立一個語音配置，用於語音合成器：

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    這裡使用了與語音辨識器相同的 API 金鑰、位置和語言。

1. 在這段程式碼下方，新增以下程式碼以獲取語音並將其設置到語音配置中：

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    這段程式碼會檢索所有可用的語音清單，然後找到第一個與正在使用的語言匹配的語音。

    > 💁 你可以從 [Microsoft Docs 的語言與語音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) 獲取完整的支援語音清單。如果你想使用特定的語音，可以移除這個函式，並將語音名稱直接硬編碼到程式中。例如：
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. 更新 `say` 函式的內容，生成回應的 SSML：

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. 在這段程式碼下方，停止語音辨識，播放 SSML，然後重新啟動語音辨識：

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    在播放語音時停止語音辨識，這樣可以避免計時器啟動的語音被辨識為新的請求，發送到 LUIS，並可能被解讀為設定新計時器的指令。

    > 💁 你可以透過註解掉停止和重新啟動辨識的程式碼來測試這個功能。設定一個計時器，你可能會發現語音回應會觸發新的計時器，導致新的語音回應，進而觸發新的計時器，如此循環不止！

1. 執行應用程式，並確保函式應用程式也在運行。設定一些計時器，你會聽到語音回應告訴你計時器已設定，當計時器完成時，還會有另一個語音回應。

> 💁 你可以在 [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) 資料夾中找到這段程式碼。

😀 你的計時器程式大功告成！

---

**免責聲明**：  
本文件已使用人工智能翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。儘管我們致力於提供準確的翻譯，請注意自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於重要信息，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。