<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "ea733bd0cdf2479e082373f765a08678",
  "translation_date": "2025-08-26T07:01:44+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/pi-sensor.md",
  "language_code": "pl"
}
-->
# Zbuduj lampkę nocną - Raspberry Pi

W tej części lekcji dodasz czujnik światła do swojego Raspberry Pi.

## Sprzęt

Czujnikiem używanym w tej lekcji jest **czujnik światła**, który wykorzystuje [fotodiodę](https://wikipedia.org/wiki/Fotodioda) do przekształcania światła w sygnał elektryczny. Jest to czujnik analogowy, który wysyła wartość całkowitą od 0 do 1 000, wskazującą względną ilość światła, która nie odpowiada żadnej standardowej jednostce miary, takiej jak [lux](https://wikipedia.org/wiki/Lux).

Czujnik światła to zewnętrzny czujnik Grove, który należy podłączyć do nakładki Grove Base na Raspberry Pi.

### Podłącz czujnik światła

Czujnik światła Grove, który służy do wykrywania poziomów światła, musi zostać podłączony do Raspberry Pi.

#### Zadanie - podłącz czujnik światła

Podłącz czujnik światła.

![Czujnik światła Grove](../../../../../translated_images/pl/grove-light-sensor.b8127b7c434e632d6bcdb57587a14e9ef69a268a22df95d08628f62b8fa5505c.png)

1. Włóż jeden koniec kabla Grove do gniazda na module czujnika światła. Kabel wejdzie tylko w jedną stronę.

1. Przy wyłączonym Raspberry Pi podłącz drugi koniec kabla Grove do analogowego gniazda oznaczonego **A0** na nakładce Grove Base przymocowanej do Pi. To gniazdo znajduje się drugie od prawej strony, w rzędzie gniazd obok pinów GPIO.

![Czujnik światła Grove podłączony do gniazda A0](../../../../../translated_images/pl/pi-light-sensor.66cc1e31fa48cd7d5f23400d4b2119aa41508275cb7c778053a7923b4e972d7e.png)

## Zaprogramuj czujnik światła

Urządzenie można teraz zaprogramować przy użyciu czujnika światła Grove.

### Zadanie - zaprogramuj czujnik światła

Zaprogramuj urządzenie.

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Otwórz projekt lampki nocnej w VS Code, który utworzyłeś w poprzedniej części tego zadania, działając bezpośrednio na Pi lub łącząc się za pomocą rozszerzenia Remote SSH.

1. Otwórz plik `app.py` i usuń z niego cały kod.

1. Dodaj poniższy kod do pliku `app.py`, aby zaimportować wymagane biblioteki:

    ```python
    import time
    from grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Instrukcja `import time` importuje moduł `time`, który będzie używany później w tym zadaniu.

    Instrukcja `from grove.grove_light_sensor_v1_2 import GroveLightSensor` importuje `GroveLightSensor` z bibliotek Python Grove. Ta biblioteka zawiera kod do obsługi czujnika światła Grove i została zainstalowana globalnie podczas konfiguracji Pi.

1. Dodaj poniższy kod po kodzie powyżej, aby utworzyć instancję klasy zarządzającej czujnikiem światła:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linia `light_sensor = GroveLightSensor(0)` tworzy instancję klasy `GroveLightSensor`, łącząc się z pinem **A0** - analogowym pinem Grove, do którego podłączony jest czujnik światła.

1. Dodaj nieskończoną pętlę po kodzie powyżej, aby odczytywać wartość czujnika światła i wyświetlać ją w konsoli:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    To odczyta aktualny poziom światła w skali od 0 do 1 023, używając właściwości `light` klasy `GroveLightSensor`. Ta właściwość odczytuje wartość analogową z pinu. Wartość ta jest następnie wyświetlana w konsoli.

1. Dodaj krótką pauzę trwającą jedną sekundę na końcu pętli, ponieważ poziomy światła nie muszą być sprawdzane ciągle. Pauza zmniejsza zużycie energii przez urządzenie.

    ```python
    time.sleep(1)
    ```

1. W terminalu VS Code uruchom poniższe polecenie, aby uruchomić swoją aplikację w Pythonie:

    ```sh
    python3 app.py
    ```

    Wartości światła będą wyświetlane w konsoli. Zakryj i odkryj czujnik światła, a wartości będą się zmieniać:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

> 💁 Ten kod znajdziesz w folderze [code-sensor/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/pi).

😀 Dodanie czujnika do programu lampki nocnej zakończyło się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.