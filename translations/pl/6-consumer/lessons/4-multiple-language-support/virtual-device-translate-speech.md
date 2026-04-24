# Tłumaczenie mowy - Wirtualne urządzenie IoT

W tej części lekcji napiszesz kod, który przetłumaczy mowę podczas konwersji na tekst za pomocą usługi rozpoznawania mowy, a następnie przetłumaczy tekst za pomocą usługi Translator, zanim wygeneruje odpowiedź głosową.

## Użycie usługi rozpoznawania mowy do tłumaczenia mowy

Usługa rozpoznawania mowy może nie tylko konwertować mowę na tekst w tym samym języku, ale także tłumaczyć wynik na inne języki.

### Zadanie - użycie usługi rozpoznawania mowy do tłumaczenia mowy

1. Otwórz projekt `smart-timer` w VS Code i upewnij się, że środowisko wirtualne jest załadowane w terminalu.

1. Dodaj poniższe instrukcje importu poniżej istniejących importów:

    ```python
    from azure.cognitiveservices import speech
    from azure.cognitiveservices.speech.translation import SpeechTranslationConfig, TranslationRecognizer
    import requests
    ```

    Importuje to klasy używane do tłumaczenia mowy oraz bibliotekę `requests`, która będzie używana do wywołania usługi Translator w dalszej części tej lekcji.

1. Twój inteligentny timer będzie miał ustawione 2 języki - język serwera, który został użyty do trenowania LUIS (ten sam język jest również używany do budowania komunikatów dla użytkownika), oraz język, którym posługuje się użytkownik. Zaktualizuj zmienną `language`, aby odpowiadała językowi, którym będzie mówił użytkownik, i dodaj nową zmienną o nazwie `server_language` dla języka używanego do trenowania LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Zamień `<user language>` na nazwę lokalizacji języka, którym będziesz mówić, na przykład `fr-FR` dla francuskiego lub `zn-HK` dla kantońskiego.

    Zamień `<server language>` na nazwę lokalizacji języka używanego do trenowania LUIS.

    Listę obsługiwanych języków i ich nazw lokalizacji znajdziesz w [dokumentacji wsparcia językowego i głosowego na stronie Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jeśli nie mówisz w wielu językach, możesz użyć usługi takiej jak [Bing Translate](https://www.bing.com/translator) lub [Google Translate](https://translate.google.com), aby przetłumaczyć z preferowanego języka na wybrany język. Te usługi mogą również odtwarzać dźwięk przetłumaczonego tekstu. Pamiętaj, że rozpoznawanie mowy może ignorować niektóre dźwięki odtwarzane z Twojego urządzenia, więc może być konieczne użycie dodatkowego urządzenia do odtwarzania przetłumaczonego tekstu.
    >
    > Na przykład, jeśli trenujesz LUIS w języku angielskim, ale chcesz używać francuskiego jako języka użytkownika, możesz przetłumaczyć zdania takie jak "set a 2 minute and 27 second timer" z angielskiego na francuski za pomocą Bing Translate, a następnie użyć przycisku **Listen translation**, aby wypowiedzieć tłumaczenie do mikrofonu.
    >
    > ![Przycisk Listen translation w Bing Translate](../../../../../translated_images/pl/bing-translate.348aa796d6efe2a9.webp)

1. Zamień deklaracje `recognizer_config` i `recognizer` na następujące:

    ```python
    translation_config = SpeechTranslationConfig(subscription=speech_api_key,
                                                 region=location,
                                                 speech_recognition_language=language,
                                                 target_languages=(language, server_language))
    
    recognizer = TranslationRecognizer(translation_config=translation_config)
    ```

    Tworzy to konfigurację tłumaczenia, aby rozpoznawać mowę w języku użytkownika i tworzyć tłumaczenia w języku użytkownika oraz języku serwera. Następnie używa tej konfiguracji do stworzenia tłumacza mowy - rozpoznawacza mowy, który może tłumaczyć wynik rozpoznawania mowy na wiele języków.

    > 💁 Oryginalny język musi być określony w `target_languages`, w przeciwnym razie nie otrzymasz żadnych tłumaczeń.

1. Zaktualizuj funkcję `recognized`, zastępując całą jej zawartość następującym kodem:

    ```python
    if args.result.reason == speech.ResultReason.TranslatedSpeech:
        language_match = next(l for l in args.result.translations if server_language.lower().startswith(l.lower()))
        text = args.result.translations[language_match]
        if (len(text) > 0):
            print(f'Translated text: {text}')
    
            message = Message(json.dumps({ 'speech': text }))
            device_client.send_message(message)
    ```

    Kod ten sprawdza, czy zdarzenie rozpoznania zostało wywołane, ponieważ mowa została przetłumaczona (to zdarzenie może być wywołane w innych sytuacjach, na przykład gdy mowa została rozpoznana, ale nie przetłumaczona). Jeśli mowa została przetłumaczona, znajduje tłumaczenie w słowniku `args.result.translations`, które odpowiada językowi serwera.

    Słownik `args.result.translations` jest indeksowany na podstawie części językowej ustawienia lokalizacji, a nie całego ustawienia. Na przykład, jeśli zażądasz tłumaczenia na `fr-FR` dla francuskiego, słownik będzie zawierał wpis dla `fr`, a nie `fr-FR`.

    Przetłumaczony tekst jest następnie wysyłany do IoT Hub.

1. Uruchom ten kod, aby przetestować tłumaczenia. Upewnij się, że Twoja aplikacja funkcji działa, i poproś o timer w języku użytkownika, mówiąc w tym języku samodzielnie lub używając aplikacji tłumaczącej.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    ```

## Tłumaczenie tekstu za pomocą usługi Translator

Usługa rozpoznawania mowy nie obsługuje tłumaczenia tekstu z powrotem na mowę, zamiast tego możesz użyć usługi Translator do tłumaczenia tekstu. Ta usługa ma interfejs REST API, którego możesz użyć do tłumaczenia tekstu.

### Zadanie - użycie zasobu Translator do tłumaczenia tekstu

1. Dodaj klucz API Translator poniżej `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Zamień `<key>` na klucz API dla swojego zasobu usługi Translator.

1. Powyżej funkcji `say` zdefiniuj funkcję `translate_text`, która będzie tłumaczyć tekst z języka serwera na język użytkownika:

    ```python
    def translate_text(text):
    ```

1. Wewnątrz tej funkcji zdefiniuj URL i nagłówki dla wywołania REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL dla tego API nie jest specyficzny dla lokalizacji, zamiast tego lokalizacja jest przekazywana jako nagłówek. Klucz API jest używany bezpośrednio, więc w przeciwieństwie do usługi rozpoznawania mowy, nie ma potrzeby uzyskiwania tokena dostępu z API wydawcy tokenów.

1. Poniżej zdefiniuj parametry i treść wywołania:

    ```python
    params = {
        'from': server_language,
        'to': language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definiuje parametry przekazywane do wywołania API, określając języki źródłowy i docelowy. To wywołanie przetłumaczy tekst z języka `from` na język `to`.

    `body` zawiera tekst do przetłumaczenia. Jest to tablica, ponieważ w jednym wywołaniu można przetłumaczyć wiele bloków tekstu.

1. Wykonaj wywołanie REST API i pobierz odpowiedź:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odpowiedź, która wraca, to tablica JSON, z jednym elementem zawierającym tłumaczenia. Ten element ma tablicę tłumaczeń wszystkich elementów przekazanych w treści.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Chronométrant votre minuterie de 2 minutes 27 secondes.",
                    "to": "fr"
                }
            ]
        }
    ]
    ```

1. Zwróć właściwość `text` z pierwszego tłumaczenia z pierwszego elementu w tablicy:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Zaktualizuj funkcję `say`, aby przetłumaczyć tekst przed wygenerowaniem SSML:

    ```python
    print('Original:', text)
    text = translate_text(text)
    print('Translated:', text)
    ```

    Kod ten również drukuje oryginalną i przetłumaczoną wersję tekstu w konsoli.

1. Uruchom swój kod. Upewnij się, że Twoja aplikacja funkcji działa, i poproś o timer w języku użytkownika, mówiąc w tym języku samodzielnie lub używając aplikacji tłumaczącej.

    ```output
    (.venv) ➜  smart-timer python app.py
    Connecting
    Connected
    Translated text: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Ze względu na różne sposoby wyrażania się w różnych językach, możesz otrzymać tłumaczenia, które nieco różnią się od przykładów, które podałeś LUIS. W takim przypadku dodaj więcej przykładów do LUIS, przetrenuj model, a następnie opublikuj go ponownie.

> 💁 Kod ten znajdziesz w folderze [code/virtual-iot-device](../../../../../6-consumer/lessons/4-multiple-language-support/code/virtual-iot-device).

😀 Twój wielojęzyczny program timera odniósł sukces!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.