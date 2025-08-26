<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "c0550b254b9ba2539baf1e6bb5fc05f8",
  "translation_date": "2025-08-26T07:24:04+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/virtual-device-speech-to-text.md",
  "language_code": "pl"
}
-->
# Przetwarzanie mowy na tekst - Wirtualne urządzenie IoT

W tej części lekcji napiszesz kod, który przekształci mowę przechwyconą z mikrofonu na tekst za pomocą usługi rozpoznawania mowy.

## Przekształcanie mowy na tekst

Na systemach Windows, Linux i macOS można użyć Python SDK dla usług rozpoznawania mowy, aby nasłuchiwać mikrofon i przekształcać wykrytą mowę na tekst. SDK będzie nasłuchiwać ciągle, wykrywając poziomy dźwięku i przesyłając mowę do konwersji na tekst, gdy poziom dźwięku spadnie, na przykład na końcu wypowiedzi.

### Zadanie - przekształć mowę na tekst

1. Utwórz nową aplikację w Pythonie na swoim komputerze w folderze `smart-timer` z jednym plikiem o nazwie `app.py` oraz wirtualnym środowiskiem Python.

1. Zainstaluj pakiet Pip dla usług rozpoznawania mowy. Upewnij się, że instalujesz go z terminala, w którym aktywowane jest wirtualne środowisko.

    ```sh
    pip install azure-cognitiveservices-speech
    ```

    > ⚠️ Jeśli pojawi się następujący błąd:
    >
    > ```output
    > ERROR: Could not find a version that satisfies the requirement azure-cognitiveservices-speech (from versions: none)
    > ERROR: No matching distribution found for azure-cognitiveservices-speech
    > ```
    >
    > Musisz zaktualizować Pip. Zrób to za pomocą poniższego polecenia, a następnie spróbuj ponownie zainstalować pakiet:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. Dodaj następujące importy do pliku `app.py`:

    ```python
    import requests
    import time
    from azure.cognitiveservices.speech import SpeechConfig, SpeechRecognizer
    ```

    Importuje to klasy używane do rozpoznawania mowy.

1. Dodaj poniższy kod, aby zadeklarować konfigurację:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'

    recognizer_config = SpeechConfig(subscription=speech_api_key,
                                     region=location,
                                     speech_recognition_language=language)
    ```

    Zamień `<key>` na klucz API dla swojej usługi rozpoznawania mowy. Zamień `<location>` na lokalizację, którą wybrałeś podczas tworzenia zasobu usługi rozpoznawania mowy.

    Zamień `<language>` na nazwę lokalizacji języka, w którym będziesz mówić, na przykład `en-GB` dla angielskiego lub `zn-HK` dla kantońskiego. Listę obsługiwanych języków i ich nazw lokalizacji znajdziesz w [dokumentacji wsparcia językowego i głosowego na stronie Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    Ta konfiguracja jest następnie używana do utworzenia obiektu `SpeechConfig`, który będzie służył do konfiguracji usług rozpoznawania mowy.

1. Dodaj poniższy kod, aby utworzyć rozpoznawacz mowy:

    ```python
    recognizer = SpeechRecognizer(speech_config=recognizer_config)
    ```

1. Rozpoznawacz mowy działa w tle, nasłuchując dźwięku i przekształcając wykrytą mowę na tekst. Możesz uzyskać tekst za pomocą funkcji zwrotnej (callback) - funkcji, którą definiujesz i przekazujesz do rozpoznawacza. Za każdym razem, gdy wykryta zostanie mowa, funkcja zwrotna zostanie wywołana. Dodaj poniższy kod, aby zdefiniować funkcję zwrotną, przekazać ją do rozpoznawacza oraz zdefiniować funkcję przetwarzającą tekst, która wypisze go na konsolę:

    ```python
    def process_text(text):
        print(text)

    def recognized(args):
        process_text(args.result.text)
    
    recognizer.recognized.connect(recognized)
    ```

1. Rozpoznawacz zaczyna nasłuchiwać dopiero wtedy, gdy wyraźnie go uruchomisz. Dodaj poniższy kod, aby rozpocząć rozpoznawanie. Działa to w tle, więc Twoja aplikacja będzie również potrzebować nieskończonej pętli, która będzie "usypiać", aby utrzymać aplikację w działaniu.

    ```python
    recognizer.start_continuous_recognition()

    while True:
        time.sleep(1)
    ```

1. Uruchom tę aplikację. Mów do mikrofonu, a dźwięk przekształcony na tekst zostanie wyświetlony na konsoli.

    ```output
    (.venv) ➜  smart-timer python3 app.py
    Hello world.
    Welcome to IoT for beginners.
    ```

    Wypróbuj różne typy zdań, w tym zdania, w których słowa brzmią podobnie, ale mają różne znaczenia. Na przykład, jeśli mówisz po angielsku, powiedz „I want to buy two bananas and an apple too” i zauważ, jak aplikacja użyje odpowiednich słów „to”, „two” i „too” na podstawie kontekstu, a nie tylko ich brzmienia.

> 💁 Ten kod znajdziesz w folderze [code-speech-to-text/virtual-iot-device](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/virtual-iot-device).

😀 Twój program przekształcający mowę na tekst zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.