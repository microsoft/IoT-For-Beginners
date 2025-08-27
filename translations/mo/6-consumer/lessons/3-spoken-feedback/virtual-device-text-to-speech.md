<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-27T00:17:46+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "mo"
}
-->
# 將文字轉換為語音 - 虛擬物聯網設備

在本課程的這部分，你將撰寫程式碼，使用語音服務將文字轉換為語音。

## 將文字轉換為語音

在上一課中你使用的語音服務 SDK，不僅可以將語音轉換為文字，還可以將文字轉換回語音。當請求語音時，你需要提供要使用的語音，因為語音可以由多種不同的聲音生成。

每種語言都支援多種不同的聲音，你可以從語音服務 SDK 獲取每種語言支援的聲音列表。

### 任務 - 將文字轉換為語音

1. 在 VS Code 中打開 `smart-timer` 專案，並確保虛擬環境已在終端中加載。

1. 從 `azure.cognitiveservices.speech` 套件中匯入 `SpeechSynthesizer`，將其添加到現有的匯入部分：

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

    這使用了與語音識別器相同的 API 金鑰、位置和語言。

1. 在此之下，添加以下程式碼以獲取語音並將其設置到語音配置中：

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    這段程式碼會檢索所有可用語音的列表，然後找到第一個與正在使用的語言匹配的語音。

    > 💁 你可以從 [Microsoft Docs 上的語言和語音支援文件](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech) 獲取完整的支援語音列表。如果你想使用特定的語音，可以移除這個函數，並將語音名稱直接硬編碼到程式碼中。例如：
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. 更新 `say` 函數的內容，為回應生成 SSML：

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. 在此之下，停止語音識別，播放 SSML，然後重新啟動語音識別：

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    在播放語音時，語音識別會暫停，以避免計時器啟動的語音回應被檢測到，然後發送到 LUIS 並可能被解釋為設置新計時器的請求。

    > 💁 你可以通過註解掉停止和重新啟動語音識別的程式碼來測試這一點。設置一個計時器，你可能會發現語音回應設置了一個新計時器，這又導致新的語音回應，進而設置新的計時器，如此循環不斷！

1. 運行應用程式，並確保函數應用程式也在運行。設置一些計時器，你會聽到語音回應，告訴你計時器已設置，然後在計時器完成時聽到另一個語音回應。

> 💁 你可以在 [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device) 資料夾中找到這段程式碼。

😀 你的計時器程式大功告成！

---

**免責聲明**：  
本文件已使用 AI 翻譯服務 [Co-op Translator](https://github.com/Azure/co-op-translator) 進行翻譯。雖然我們致力於提供準確的翻譯，但請注意，自動翻譯可能包含錯誤或不準確之處。原始文件的母語版本應被視為權威來源。對於關鍵資訊，建議使用專業人工翻譯。我們對因使用此翻譯而引起的任何誤解或誤釋不承擔責任。