<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "af249a24d4fe4f4de4806adbc3bc9d86",
  "translation_date": "2025-08-26T07:27:00+00:00",
  "source_file": "6-consumer/lessons/1-speech-recognition/pi-speech-to-text.md",
  "language_code": "pl"
}
-->
# Przekształcanie mowy na tekst - Raspberry Pi

W tej części lekcji napiszesz kod, który przekształci mowę z nagranego dźwięku na tekst, korzystając z usługi rozpoznawania mowy.

## Wysyłanie dźwięku do usługi rozpoznawania mowy

Dźwięk można wysłać do usługi rozpoznawania mowy za pomocą interfejsu REST API. Aby korzystać z tej usługi, najpierw musisz uzyskać token dostępu, a następnie użyć go do korzystania z REST API. Tokeny dostępu wygasają po 10 minutach, więc Twój kod powinien regularnie je odświeżać, aby zawsze były aktualne.

### Zadanie - uzyskanie tokenu dostępu

1. Otwórz projekt `smart-timer` na swoim Raspberry Pi.

1. Usuń funkcję `play_audio`. Nie jest już potrzebna, ponieważ nie chcesz, aby inteligentny timer powtarzał to, co powiedziałeś.

1. Dodaj następujący import na początku pliku `app.py`:

    ```python
    import requests
    ```

1. Dodaj poniższy kod powyżej pętli `while True`, aby zadeklarować ustawienia dla usługi rozpoznawania mowy:

    ```python
    speech_api_key = '<key>'
    location = '<location>'
    language = '<language>'
    ```

    Zamień `<key>` na klucz API dla Twojego zasobu usługi rozpoznawania mowy. Zamień `<location>` na lokalizację, którą wybrałeś podczas tworzenia zasobu usługi rozpoznawania mowy.

    Zamień `<language>` na nazwę lokalizacji języka, w którym będziesz mówić, na przykład `en-GB` dla angielskiego lub `zn-HK` dla kantońskiego. Listę obsługiwanych języków i ich nazw lokalizacji znajdziesz w [dokumentacji wsparcia językowego i głosowego na stronie Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#speech-to-text).

1. Poniżej tego kodu dodaj następującą funkcję, aby uzyskać token dostępu:

    ```python
    def get_access_token():
        headers = {
            'Ocp-Apim-Subscription-Key': speech_api_key
        }
    
        token_endpoint = f'https://{location}.api.cognitive.microsoft.com/sts/v1.0/issuetoken'
        response = requests.post(token_endpoint, headers=headers)
        return str(response.text)
    ```

    Funkcja ta wywołuje punkt końcowy wydawania tokenów, przekazując klucz API jako nagłówek. Wywołanie to zwraca token dostępu, który można wykorzystać do wywoływania usług rozpoznawania mowy.

1. Poniżej tego kodu zadeklaruj funkcję, która przekształci mowę z nagranego dźwięku na tekst za pomocą REST API:

    ```python
    def convert_speech_to_text(buffer):
    ```

1. Wewnątrz tej funkcji skonfiguruj URL REST API i nagłówki:

    ```python
    url = f'https://{location}.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1'

    headers = {
        'Authorization': 'Bearer ' + get_access_token(),
        'Content-Type': f'audio/wav; codecs=audio/pcm; samplerate={rate}',
        'Accept': 'application/json;text/xml'
    }

    params = {
        'language': language
    }
    ```

    Funkcja ta tworzy URL, używając lokalizacji zasobu usługi rozpoznawania mowy. Następnie wypełnia nagłówki tokenem dostępu z funkcji `get_access_token`, a także częstotliwością próbkowania używaną do nagrywania dźwięku. Na końcu definiuje parametry przekazywane w URL, zawierające język nagranego dźwięku.

1. Poniżej tego kodu dodaj następujący kod, aby wywołać REST API i uzyskać tekst:

    ```python
    response = requests.post(url, headers=headers, params=params, data=buffer)
    response_json = response.json()

    if response_json['RecognitionStatus'] == 'Success':
        return response_json['DisplayText']
    else:
        return ''
    ```

    Funkcja ta wywołuje URL i dekoduje wartość JSON, która jest zwracana w odpowiedzi. Wartość `RecognitionStatus` w odpowiedzi wskazuje, czy udało się poprawnie przekształcić mowę na tekst. Jeśli wartość ta to `Success`, funkcja zwraca tekst, w przeciwnym razie zwraca pusty ciąg znaków.

1. Powyżej pętli `while True:` zdefiniuj funkcję, która przetworzy tekst zwrócony przez usługę rozpoznawania mowy. Na razie funkcja ta po prostu wypisze tekst w konsoli.

    ```python
    def process_text(text):
        print(text)
    ```

1. Na koniec zamień wywołanie `play_audio` w pętli `while True` na wywołanie funkcji `convert_speech_to_text`, przekazując tekst do funkcji `process_text`:

    ```python
    text = convert_speech_to_text(buffer)
    process_text(text)
    ```

1. Uruchom kod. Naciśnij przycisk i mów do mikrofonu. Zwolnij przycisk, gdy skończysz, a dźwięk zostanie przekształcony na tekst i wypisany w konsoli.

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Hello world.
    Welcome to IoT for beginners.
    ```

    Wypróbuj różne rodzaje zdań, w tym zdania, w których słowa brzmią podobnie, ale mają różne znaczenia. Na przykład, jeśli mówisz po angielsku, powiedz „I want to buy two bananas and an apple too” i zauważ, jak usługa użyje odpowiednich form „to”, „two” i „too” na podstawie kontekstu, a nie tylko ich brzmienia.

> 💁 Kod ten znajdziesz w folderze [code-speech-to-text/pi](../../../../../6-consumer/lessons/1-speech-recognition/code-speech-to-text/pi).

😀 Twój program przekształcający mowę na tekst zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.