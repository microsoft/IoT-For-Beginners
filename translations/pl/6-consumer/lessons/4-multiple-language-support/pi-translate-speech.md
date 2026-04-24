# Tłumaczenie mowy - Raspberry Pi

W tej części lekcji napiszesz kod do tłumaczenia tekstu za pomocą usługi tłumacza.

## Konwersja tekstu na mowę za pomocą usługi tłumacza

REST API usługi mowy nie obsługuje bezpośrednich tłumaczeń, zamiast tego możesz użyć usługi Translator do tłumaczenia tekstu wygenerowanego przez usługę zamiany mowy na tekst oraz tekstu odpowiedzi mówionej. Ta usługa posiada REST API, które możesz wykorzystać do tłumaczenia tekstu.

### Zadanie - użyj zasobu tłumacza do tłumaczenia tekstu

1. Twój inteligentny timer będzie miał ustawione 2 języki - język serwera, który został użyty do trenowania LUIS (ten sam język jest również używany do budowania wiadomości przekazywanych użytkownikowi), oraz język używany przez użytkownika. Zaktualizuj zmienną `language`, aby odpowiadała językowi, którym będzie mówił użytkownik, i dodaj nową zmienną o nazwie `server_language` dla języka użytego do trenowania LUIS:

    ```python
    language = '<user language>'
    server_language = '<server language>'
    ```

    Zamień `<user language>` na nazwę lokalizacji dla języka, którym będziesz mówić, na przykład `fr-FR` dla francuskiego lub `zn-HK` dla kantońskiego.

    Zamień `<server language>` na nazwę lokalizacji dla języka użytego do trenowania LUIS.

    Listę obsługiwanych języków i ich nazw lokalizacji znajdziesz w [dokumentacji wsparcia językowego i głosowego na stronie Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

    > 💁 Jeśli nie mówisz w wielu językach, możesz skorzystać z usługi takiej jak [Bing Translate](https://www.bing.com/translator) lub [Google Translate](https://translate.google.com), aby przetłumaczyć z preferowanego języka na wybrany język. Te usługi mogą również odtwarzać audio przetłumaczonego tekstu.
    >
    > Na przykład, jeśli trenujesz LUIS w języku angielskim, ale chcesz używać francuskiego jako języka użytkownika, możesz przetłumaczyć zdania takie jak "ustaw timer na 2 minuty i 27 sekund" z angielskiego na francuski za pomocą Bing Translate, a następnie użyć przycisku **Listen translation**, aby wypowiedzieć tłumaczenie do mikrofonu.
    >
    > ![Przycisk Listen translation w Bing Translate](../../../../../translated_images/pl/bing-translate.348aa796d6efe2a9.webp)

1. Dodaj klucz API tłumacza poniżej `speech_api_key`:

    ```python
    translator_api_key = '<key>'
    ```

    Zamień `<key>` na klucz API dla zasobu usługi tłumacza.

1. Powyżej funkcji `say` zdefiniuj funkcję `translate_text`, która będzie tłumaczyć tekst z języka serwera na język użytkownika:

    ```python
    def translate_text(text, from_language, to_language):
    ```

    Języki źródłowy i docelowy są przekazywane do tej funkcji - Twoja aplikacja musi konwertować z języka użytkownika na język serwera podczas rozpoznawania mowy oraz z języka serwera na język użytkownika podczas udzielania odpowiedzi mówionej.

1. Wewnątrz tej funkcji zdefiniuj URL i nagłówki dla wywołania REST API:

    ```python
    url = f'https://api.cognitive.microsofttranslator.com/translate?api-version=3.0'

    headers = {
        'Ocp-Apim-Subscription-Key': translator_api_key,
        'Ocp-Apim-Subscription-Region': location,
        'Content-type': 'application/json'
    }
    ```

    URL dla tego API nie jest specyficzny dla lokalizacji, zamiast tego lokalizacja jest przekazywana jako nagłówek. Klucz API jest używany bezpośrednio, więc w przeciwieństwie do usługi mowy nie ma potrzeby uzyskiwania tokenu dostępu z API wydającego tokeny.

1. Poniżej zdefiniuj parametry i treść dla wywołania:

    ```python
    params = {
        'from': from_language,
        'to': to_language
    }

    body = [{
        'text' : text
    }]
    ```

    `params` definiuje parametry przekazywane do wywołania API, przekazując języki źródłowy i docelowy. To wywołanie przetłumaczy tekst w języku `from` na język `to`.

    `body` zawiera tekst do przetłumaczenia. Jest to tablica, ponieważ w jednym wywołaniu można przetłumaczyć wiele bloków tekstu.

1. Wykonaj wywołanie REST API i pobierz odpowiedź:

    ```python
    response = requests.post(url, headers=headers, params=params, json=body)
    ```

    Odpowiedź, która wraca, to tablica JSON, z jednym elementem zawierającym tłumaczenia. Ten element ma tablicę tłumaczeń dla wszystkich elementów przekazanych w treści.

    ```json
    [
        {
            "translations": [
                {
                    "text": "Set a 2 minute 27 second timer.",
                    "to": "en"
                }
            ]
        }
    ]
    ```

1. Zwróć właściwość `text` z pierwszego tłumaczenia z pierwszego elementu w tablicy:

    ```python
    return response.json()[0]['translations'][0]['text']
    ```

1. Zaktualizuj pętlę `while True`, aby tłumaczyć tekst z wywołania `convert_speech_to_text` z języka użytkownika na język serwera:

    ```python
    if len(text) > 0:
        print('Original:', text)
        text = translate_text(text, language, server_language)
        print('Translated:', text)

        message = Message(json.dumps({ 'speech': text }))
        device_client.send_message(message)
    ```

    Ten kod również drukuje oryginalną i przetłumaczoną wersję tekstu w konsoli.

1. Zaktualizuj funkcję `say`, aby tłumaczyć tekst do wypowiedzenia z języka serwera na język użytkownika:

    ```python
    def say(text):
        print('Original:', text)
        text = translate_text(text, server_language, language)
        print('Translated:', text)
        speech = get_speech(text)
        play_speech(speech)
    ```

    Ten kod również drukuje oryginalną i przetłumaczoną wersję tekstu w konsoli.

1. Uruchom swój kod. Upewnij się, że Twoja aplikacja funkcji działa, i poproś o timer w języku użytkownika, mówiąc w tym języku samodzielnie lub korzystając z aplikacji tłumaczącej.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py
    Connecting
    Connected
    Using voice fr-FR-DeniseNeural
    Original: Définir une minuterie de 2 minutes et 27 secondes.
    Translated: Set a timer of 2 minutes and 27 seconds.
    Original: 2 minute 27 second timer started.
    Translated: 2 minute 27 seconde minute a commencé.
    Original: Times up on your 2 minute 27 second timer.
    Translated: Chronométrant votre minuterie de 2 minutes 27 secondes.
    ```

    > 💁 Ze względu na różne sposoby wyrażania się w różnych językach, możesz otrzymać tłumaczenia, które nieco różnią się od przykładów, które podałeś LUIS. Jeśli tak się stanie, dodaj więcej przykładów do LUIS, ponownie wytrenuj, a następnie opublikuj model.

> 💁 Ten kod znajdziesz w folderze [code/pi](../../../../../6-consumer/lessons/4-multiple-language-support/code/pi).

😀 Twój wielojęzyczny program timerowy odniósł sukces!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.