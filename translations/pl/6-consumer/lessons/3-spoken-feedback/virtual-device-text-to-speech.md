<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7966848a1f870e4c42edb4db67b13c57",
  "translation_date": "2025-08-26T07:21:29+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/virtual-device-text-to-speech.md",
  "language_code": "pl"
}
-->
# Przetwarzanie tekstu na mowę - Wirtualne urządzenie IoT

W tej części lekcji napiszesz kod, który przekształca tekst na mowę za pomocą usługi mowy.

## Przekształcanie tekstu na mowę

SDK usług mowy, którego używałeś w poprzedniej lekcji do przekształcania mowy na tekst, może być również używane do przekształcania tekstu z powrotem na mowę. Podczas generowania mowy musisz określić głos, który ma być użyty, ponieważ mowę można generować za pomocą różnych głosów.

Każdy język obsługuje różne głosy, a listę obsługiwanych głosów dla każdego języka można uzyskać z SDK usług mowy.

### Zadanie - przekształć tekst na mowę

1. Otwórz projekt `smart-timer` w VS Code i upewnij się, że w terminalu załadowane jest wirtualne środowisko.

1. Zaimportuj `SpeechSynthesizer` z pakietu `azure.cognitiveservices.speech`, dodając go do istniejących importów:

    ```python
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer, SpeechSynthesizer
    ```

1. Nad funkcją `say` utwórz konfigurację mowy do użycia z syntezatorem mowy:

    ```python
    speech_config = SpeechConfig(subscription=speech_api_key,
                                 region=location)
    speech_config.speech_synthesis_language = language
    speech_synthesizer = SpeechSynthesizer(speech_config=speech_config)
    ```

    Wykorzystuje to ten sam klucz API, lokalizację i język, które były używane przez rozpoznawanie mowy.

1. Poniżej dodaj następujący kod, aby pobrać głos i ustawić go w konfiguracji mowy:

    ```python
    voices = speech_synthesizer.get_voices_async().get().voices
    first_voice = next(x for x in voices if x.locale.lower() == language.lower())
    speech_config.speech_synthesis_voice_name = first_voice.short_name
    ```

    Kod ten pobiera listę wszystkich dostępnych głosów, a następnie znajduje pierwszy głos, który pasuje do używanego języka.

    > 💁 Pełną listę obsługiwanych głosów możesz znaleźć w [dokumentacji wsparcia językowego i głosowego na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jeśli chcesz użyć konkretnego głosu, możesz usunąć tę funkcję i na stałe wpisać nazwę głosu z tej dokumentacji. Na przykład:
    >
    > ```python
    > speech_config.speech_synthesis_voice_name = 'hi-IN-SwaraNeural'
    > ```

1. Zaktualizuj zawartość funkcji `say`, aby wygenerować SSML dla odpowiedzi:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{first_voice.short_name}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

1. Poniżej zatrzymaj rozpoznawanie mowy, wygeneruj mowę z SSML, a następnie ponownie uruchom rozpoznawanie:

    ```python
    recognizer.stop_continuous_recognition()
    speech_synthesizer.speak_ssml(ssml)
    recognizer.start_continuous_recognition()
    ```

    Rozpoznawanie jest zatrzymywane na czas odtwarzania mowy, aby uniknąć sytuacji, w której ogłoszenie rozpoczęcia timera zostanie wykryte, wysłane do LUIS i potencjalnie zinterpretowane jako prośba o ustawienie nowego timera.

    > 💁 Możesz to przetestować, komentując linie zatrzymujące i ponownie uruchamiające rozpoznawanie. Ustaw jeden timer, a możesz zauważyć, że ogłoszenie ustawia nowy timer, co powoduje kolejne ogłoszenie, prowadzące do ustawienia nowego timera, i tak dalej w nieskończoność!

1. Uruchom aplikację i upewnij się, że aplikacja funkcji również działa. Ustaw kilka timerów, a usłyszysz odpowiedź głosową informującą, że timer został ustawiony, a następnie kolejną odpowiedź głosową, gdy timer się zakończy.

> 💁 Kod ten znajdziesz w folderze [code-spoken-response/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/virtual-iot-device).

😀 Twój program do obsługi timerów zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.