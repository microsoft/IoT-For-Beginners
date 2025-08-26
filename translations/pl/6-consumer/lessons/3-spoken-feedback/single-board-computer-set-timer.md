<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "64ad4ddb4de81a18b7252e968f10b404",
  "translation_date": "2025-08-26T07:18:03+00:00",
  "source_file": "6-consumer/lessons/3-spoken-feedback/single-board-computer-set-timer.md",
  "language_code": "pl"
}
-->
# Ustawianie timera - Wirtualny sprzęt IoT i Raspberry Pi

W tej części lekcji wywołasz swój kod serverless, aby zrozumieć mowę i ustawić timer na swoim wirtualnym urządzeniu IoT lub Raspberry Pi na podstawie wyników.

## Ustawianie timera

Tekst zwrócony z wywołania funkcji rozpoznawania mowy musi zostać przesłany do twojego kodu serverless, aby został przetworzony przez LUIS, który zwróci liczbę sekund dla timera. Ta liczba sekund może być użyta do ustawienia timera.

Timery można ustawiać za pomocą klasy `threading.Timer` w Pythonie. Klasa ta przyjmuje czas opóźnienia i funkcję, która zostanie wykonana po upływie tego czasu.

### Zadanie - wyślij tekst do funkcji serverless

1. Otwórz projekt `smart-timer` w VS Code i upewnij się, że środowisko wirtualne jest załadowane w terminalu, jeśli korzystasz z wirtualnego urządzenia IoT.

1. Nad funkcją `process_text` zadeklaruj funkcję o nazwie `get_timer_time`, aby wywołać REST endpoint, który utworzyłeś:

    ```python
    def get_timer_time(text):
    ```

1. Dodaj poniższy kod do tej funkcji, aby zdefiniować URL do wywołania:

    ```python
    url = '<URL>'
    ```

    Zamień `<URL>` na URL swojego REST endpointu, który utworzyłeś w poprzedniej lekcji, czy to na swoim komputerze, czy w chmurze.

1. Dodaj poniższy kod, aby ustawić tekst jako właściwość przekazywaną w formacie JSON do wywołania:

    ```python
    body = {
        'text': text
    }
    
    response = requests.post(url, json=body)
    ```

1. Poniżej tego kodu pobierz `seconds` z odpowiedzi, zwracając 0, jeśli wywołanie się nie powiodło:

    ```python
    if response.status_code != 200:
        return 0
    
    payload = response.json()
    return payload['seconds']
    ```

    Udane wywołania HTTP zwracają kod statusu w zakresie 200, a twój kod serverless zwraca 200, jeśli tekst został przetworzony i rozpoznany jako intencja ustawienia timera.

### Zadanie - ustaw timer w wątku w tle

1. Dodaj poniższe polecenie importu na początku pliku, aby zaimportować bibliotekę threading w Pythonie:

    ```python
    import threading
    ```

1. Nad funkcją `process_text` dodaj funkcję, która będzie odpowiadać za wypowiadanie odpowiedzi. Na razie będzie ona tylko wypisywać tekst na konsolę, ale później w tej lekcji będzie odtwarzać mowę.

    ```python
    def say(text):
        print(text)
    ```

1. Poniżej dodaj funkcję, która zostanie wywołana przez timer, aby ogłosić, że timer się zakończył:

    ```python
    def announce_timer(minutes, seconds):
        announcement = 'Times up on your '
        if minutes > 0:
            announcement += f'{minutes} minute '
        if seconds > 0:
            announcement += f'{seconds} second '
        announcement += 'timer.'
        say(announcement)
    ```

    Funkcja ta przyjmuje liczbę minut i sekund dla timera i tworzy zdanie informujące, że timer się zakończył. Sprawdza liczbę minut i sekund, uwzględniając tylko te jednostki czasu, które mają wartość. Na przykład, jeśli liczba minut wynosi 0, w komunikacie uwzględniane są tylko sekundy. To zdanie jest następnie przesyłane do funkcji `say`.

1. Poniżej dodaj funkcję `create_timer`, która utworzy timer:

    ```python
    def create_timer(total_seconds):
        minutes, seconds = divmod(total_seconds, 60)
        threading.Timer(total_seconds, announce_timer, args=[minutes, seconds]).start()
    ```

    Funkcja ta przyjmuje całkowitą liczbę sekund dla timera, która zostanie przesłana w poleceniu, i konwertuje ją na minuty i sekundy. Następnie tworzy i uruchamia obiekt timera, używając całkowitej liczby sekund, przekazując funkcję `announce_timer` oraz listę zawierającą minuty i sekundy. Gdy timer się zakończy, wywoła funkcję `announce_timer` i przekaże zawartość tej listy jako parametry - pierwszy element listy zostanie przekazany jako parametr `minutes`, a drugi jako `seconds`.

1. Na końcu funkcji `create_timer` dodaj kod, który utworzy komunikat dla użytkownika, informujący o rozpoczęciu timera:

    ```python
    announcement = ''
    if minutes > 0:
        announcement += f'{minutes} minute '
    if seconds > 0:
        announcement += f'{seconds} second '    
    announcement += 'timer started.'
    say(announcement)
    ```

    Ponownie, uwzględniane są tylko te jednostki czasu, które mają wartość. To zdanie jest następnie przesyłane do funkcji `say`.

1. Dodaj poniższy kod na końcu funkcji `process_text`, aby pobrać czas dla timera z tekstu, a następnie utworzyć timer:

    ```python
    seconds = get_timer_time(text)
    if seconds > 0:
        create_timer(seconds)
    ```

    Timer jest tworzony tylko wtedy, gdy liczba sekund jest większa niż 0.

1. Uruchom aplikację i upewnij się, że aplikacja funkcji również działa. Ustaw kilka timerów, a w wynikach zobaczysz, jak timer jest ustawiany, a następnie informację, gdy się zakończy:

    ```output
    pi@raspberrypi:~/smart-timer $ python3 app.py 
    Set a two minute 27 second timer.
    2 minute 27 second timer started.
    Times up on your 2 minute 27 second timer.
    ```

> 💁 Kod ten znajdziesz w folderze [code-timer/pi](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/pi) lub [code-timer/virtual-iot-device](../../../../../6-consumer/lessons/3-spoken-feedback/code-timer/virtual-iot-device).

😀 Twój program do ustawiania timera zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.