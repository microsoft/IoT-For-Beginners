<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-25T00:15:49+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "tw"
}
-->
# 文字轉語音 - 虛擬物聯網設備

在本課程的這部分，你將撰寫程式碼，使用語音服務將文字轉換為語音。

## 將文字轉換為語音

在上一課中你使用的語音服務 SDK 可以用來將語音轉換為文字，同樣也可以用來將文字轉換回語音。在請求語音時，你需要提供要使用的語音，因為語音可以使用多種不同的聲音來生成。

每種語言都支持多種不同的聲音，你可以從語音服務 SDK 獲取每種語言支持的聲音列表。

### 任務 - 將文字轉換為語音

1. 在 VS Code 中打開 `smart-timer` 專案，並確保虛擬環境已在終端中載入。

1. 從 `azure.cognitiveservices.speech` 套件中匯入 `SpeechSynthesizer`，將其添加到現有的匯入中：

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. 在 `say` 函數上方，建立一個語音配置，用於語音合成器：

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    這使用了與辨識器相同的 API 金鑰、位置和語言。

1. 在此之下，添加以下程式碼以獲取語音並將其設置到語音配置中：

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    這會檢索所有可用聲音的列表，然後找到第一個與正在使用的語言匹配的聲音。

    > 💁 你可以從 [Microsoft Docs 的語言和聲音支持文檔](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) 獲取支持的聲音的完整列表。如果你想使用特定的聲音，可以移除此函數並直接硬編碼聲音名稱。例如：
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. 更新 `say` 函數的內容以生成回應的 SSML：

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. 在此之下，停止語音辨識，播放 SSML，然後重新啟動辨識：

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    在播放文字時停止辨識，以避免計時器啟動的公告被檢測到，發送到 LUIS 並可能被解釋為設置新計時器的請求。

    > 💁 你可以通過註解掉停止和重新啟動辨識的程式碼來測試這一點。設置一個計時器，你可能會發現公告設置了一個新計時器，這導致新的公告，進而設置新的計時器，如此循環不斷！

1. 運行應用程式，並確保函數應用程式也在運行。設置一些計時器，你會聽到語音回應，告訴你計時器已設置，然後在計時器完成時聽到另一個語音回應。

> 💁 你可以在 [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) 資料夾中找到這段程式碼。

😀 你的計時器程式大功告成！

**免責聲明**：  
本文件使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。應以原始語言的文件作為權威來源。對於關鍵資訊，建議尋求專業人工翻譯。我們對於因使用此翻譯而引起的任何誤解或錯誤解釋概不負責。