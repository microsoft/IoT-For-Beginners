<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "606f3af1c78e3741e48ce77c31cea626",
  "translation_date": "2025-08-26T07:19:40+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/pi-text-to-speech.md",
  "language_code": "pl"
}
-->
# Konwersja tekstu na mowę - Raspberry Pi

W tej części lekcji napiszesz kod, który przekształci tekst na mowę za pomocą usługi mowy.

## Konwersja tekstu na mowę za pomocą usługi mowy

Tekst można przesłać do usługi mowy za pomocą REST API, aby uzyskać mowę w formie pliku audio, który można odtworzyć na urządzeniu IoT. Podczas żądania mowy należy określić głos, który ma być użyty, ponieważ mowę można generować za pomocą różnych głosów.

Każdy język obsługuje różne głosy, a za pomocą żądania REST do usługi mowy można uzyskać listę obsługiwanych głosów dla każdego języka.

### Zadanie - uzyskaj głos

1. Otwórz projekt `smart-timer` w VS Code.

1. Dodaj poniższy kod powyżej funkcji `say`, aby zażądać listy głosów dla danego języka:

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

    Ten kod definiuje funkcję o nazwie `get_voice`, która korzysta z usługi mowy, aby uzyskać listę głosów. Następnie znajduje pierwszy głos, który pasuje do używanego języka.

    Funkcja ta jest następnie wywoływana, aby zapisać pierwszy głos, a nazwa głosu jest drukowana w konsoli. Ten głos można zażądać raz, a wartość używać przy każdym wywołaniu konwersji tekstu na mowę.

    > 💁 Pełną listę obsługiwanych głosów można znaleźć w [dokumentacji obsługi języków i głosów na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn#text-to-speech). Jeśli chcesz użyć konkretnego głosu, możesz usunąć tę funkcję i na stałe wpisać nazwę głosu z tej dokumentacji. Na przykład:
    >
    > ```python
    > voice = 'hi-IN-SwaraNeural'
    > ```

### Zadanie - konwersja tekstu na mowę

1. Poniżej tego, zdefiniuj stałą dla formatu audio, który ma być pobrany z usług mowy. Podczas żądania audio można to zrobić w różnych formatach.

    ```python
    playback_format = 'riff-48khz-16bit-mono-pcm'
    ```

    Format, którego możesz użyć, zależy od Twojego sprzętu. Jeśli pojawią się błędy `Invalid sample rate` podczas odtwarzania audio, zmień to na inną wartość. Listę obsługiwanych wartości znajdziesz w [dokumentacji REST API tekstu na mowę na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/rest-text-to-speech?WT.mc_id=academic-17441-jabenn#audio-outputs). Musisz użyć audio w formacie `riff`, a wartości do wypróbowania to `riff-16khz-16bit-mono-pcm`, `riff-24khz-16bit-mono-pcm` i `riff-48khz-16bit-mono-pcm`.

1. Poniżej tego, zadeklaruj funkcję o nazwie `get_speech`, która przekształci tekst na mowę za pomocą REST API usługi mowy:

    ```python
    def get_speech(text):
    ```

1. W funkcji `get_speech` zdefiniuj URL do wywołania oraz nagłówki do przekazania:

    ```python
        url = f'https://{location}.tts.speech.microsoft.com/cognitiveservices/v1'
    
        headers = {
            'Authorization': 'Bearer ' + get_access_token(),
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': playback_format
        }
    ```

    To ustawia nagłówki, aby użyć wygenerowanego tokenu dostępu, ustawia zawartość na SSML i definiuje potrzebny format audio.

1. Poniżej tego, zdefiniuj SSML do wysłania do REST API:

    ```python
    ssml =  f'<speak version=\'1.0\' xml:lang=\'{language}\'>'
    ssml += f'<voice xml:lang=\'{language}\' name=\'{voice}\'>'
    ssml += text
    ssml += '</voice>'
    ssml += '</speak>'
    ```

    Ten SSML ustawia język i głos do użycia, wraz z tekstem do konwersji.

1. Na koniec dodaj kod w tej funkcji, aby wykonać żądanie REST i zwrócić binarne dane audio:

    ```python
    response = requests.post(url, headers=headers, data=ssml.encode('utf-8'))
    return io.BytesIO(response.content)
    ```

### Zadanie - odtwórz audio

1. Poniżej funkcji `get_speech`, zdefiniuj nową funkcję do odtwarzania audio zwróconego przez wywołanie REST API:

    ```python
    def play_speech(speech):
    ```

1. `speech` przekazane do tej funkcji będzie binarnymi danymi audio zwróconymi przez REST API. Użyj poniższego kodu, aby otworzyć to jako plik wave i przekazać do PyAudio w celu odtworzenia audio:

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

    Ten kod używa strumienia PyAudio, podobnie jak przy przechwytywaniu audio. Różnica polega na tym, że strumień jest ustawiony jako strumień wyjściowy, a dane są odczytywane z danych audio i przesyłane do strumienia.

    Zamiast na stałe ustawiać szczegóły strumienia, takie jak częstotliwość próbkowania, są one odczytywane z danych audio.

1. Zastąp zawartość funkcji `say` następującym kodem:

    ```python
    speech = get_speech(text)
    play_speech(speech)
    ```

    Ten kod przekształca tekst na mowę jako binarne dane audio i odtwarza audio.

1. Uruchom aplikację i upewnij się, że aplikacja funkcji również działa. Ustaw kilka timerów, a usłyszysz odpowiedź głosową informującą, że Twój timer został ustawiony, a następnie kolejną odpowiedź głosową, gdy timer się zakończy.

    Jeśli pojawią się błędy `Invalid sample rate`, zmień `playback_format`, jak opisano powyżej.

> 💁 Ten kod znajdziesz w folderze [code-spoken-response/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-spoken-response/pi).

😀 Twój program timerów zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.