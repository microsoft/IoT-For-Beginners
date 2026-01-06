<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7678f7c67b97ee52d5727496dcd7d346",
  "translation_date": "2025-08-26T06:43:51+00:00",
  "source_file": "2-farm/lessons/1-predict-plant-growth/pi-temp.md",
  "language_code": "pl"
}
-->
# Mierzenie temperatury - Raspberry Pi

W tej części lekcji dodasz czujnik temperatury do swojego Raspberry Pi.

## Sprzęt

Czujnik, którego użyjesz, to [czujnik wilgotności i temperatury DHT11](https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DHT11.html), łączący dwa czujniki w jednym urządzeniu. Jest to dość popularne rozwiązanie, a wiele dostępnych na rynku czujników łączy pomiar temperatury, wilgotności, a czasem także ciśnienia atmosferycznego. Komponent czujnika temperatury to termistor o ujemnym współczynniku temperaturowym (NTC), czyli termistor, którego opór maleje wraz ze wzrostem temperatury.

Jest to czujnik cyfrowy, co oznacza, że posiada wbudowany przetwornik ADC, który generuje sygnał cyfrowy zawierający dane o temperaturze i wilgotności, które mikroprocesor może odczytać.

### Podłączanie czujnika temperatury

Czujnik temperatury Grove można podłączyć do Raspberry Pi.

#### Zadanie

Podłącz czujnik temperatury.

![Czujnik temperatury Grove](../../../../../translated_images/grove-dht11.07f8eafceee170043efbb53e1d15722bd4e00fbaa9ff74290b57e9f66eb82c17.pl.png)

1. Włóż jeden koniec kabla Grove do gniazda na czujniku wilgotności i temperatury. Kabel wejdzie tylko w jednym kierunku.

1. Przy wyłączonym zasilaniu Raspberry Pi, podłącz drugi koniec kabla Grove do gniazda cyfrowego oznaczonego jako **D5** na nakładce Grove Base zamontowanej na Raspberry Pi. To gniazdo znajduje się jako drugie od lewej w rzędzie gniazd obok pinów GPIO.

![Czujnik temperatury Grove podłączony do gniazda A0](../../../../../translated_images/pi-temperature-sensor.3ff82fff672c8e56.pl.png)

## Programowanie czujnika temperatury

Teraz można zaprogramować urządzenie do korzystania z podłączonego czujnika temperatury.

### Zadanie

Zaprogramuj urządzenie.

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Uruchom VS Code, bezpośrednio na Raspberry Pi lub łącząc się za pomocą rozszerzenia Remote SSH.

    > ⚠️ Możesz odwołać się do [instrukcji konfiguracji i uruchamiania VS Code w lekcji 1, jeśli to konieczne](../../../1-getting-started/lessons/1-introduction-to-iot/pi.md).

1. W terminalu utwórz nowy folder w katalogu domowym użytkownika `pi` o nazwie `temperature-sensor`. W tym folderze utwórz plik o nazwie `app.py`:

    ```sh
    mkdir temperature-sensor
    cd temperature-sensor
    touch app.py
    ```

1. Otwórz ten folder w VS Code.

1. Aby użyć czujnika temperatury i wilgotności, należy zainstalować dodatkowy pakiet Pip. W terminalu w VS Code uruchom następujące polecenie, aby zainstalować ten pakiet na Raspberry Pi:

    ```sh
    pip3 install seeed-python-dht
    ```

1. Dodaj poniższy kod do pliku `app.py`, aby zaimportować wymagane biblioteki:

    ```python
    import time
    from seeed_dht import DHT
    ```

    Instrukcja `from seeed_dht import DHT` importuje klasę `DHT`, która umożliwia interakcję z czujnikiem temperatury Grove z modułu `seeed_dht`.

1. Dodaj poniższy kod po wcześniejszym, aby utworzyć instancję klasy zarządzającej czujnikiem temperatury:

    ```python
    sensor = DHT("11", 5)
    ```

    To deklaruje instancję klasy `DHT`, która zarządza **D**igitalnym czujnikiem **H**umidity i **T**emperature. Pierwszy parametr informuje kod, że używany jest czujnik *DHT11* - biblioteka, której używasz, obsługuje inne warianty tego czujnika. Drugi parametr informuje kod, że czujnik jest podłączony do portu cyfrowego `D5` na nakładce Grove Base.

    > ✅ Pamiętaj, że wszystkie gniazda mają unikalne numery pinów. Piny 0, 2, 4 i 6 to piny analogowe, a piny 5, 16, 18, 22, 24 i 26 to piny cyfrowe.

1. Dodaj nieskończoną pętlę po wcześniejszym kodzie, aby odczytywać wartość z czujnika temperatury i wyświetlać ją w konsoli:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Wywołanie `sensor.read()` zwraca krotkę zawierającą wilgotność i temperaturę. Potrzebujesz tylko wartości temperatury, więc wilgotność jest pomijana. Wartość temperatury jest następnie wyświetlana w konsoli.

1. Dodaj krótką pauzę trwającą dziesięć sekund na końcu pętli, ponieważ poziomy temperatury nie muszą być sprawdzane ciągle. Pauza zmniejsza zużycie energii przez urządzenie.

    ```python
    time.sleep(10)
    ```

1. W terminalu VS Code uruchom następujące polecenie, aby uruchomić swoją aplikację w Pythonie:

    ```sh
    python3 app.py
    ```

    Powinieneś zobaczyć wartości temperatury wyświetlane w konsoli. Użyj czegoś, aby ogrzać czujnik, na przykład przyciśnij go kciukiem lub użyj wentylatora, aby zobaczyć zmieniające się wartości:

    ```output
    pi@raspberrypi:~/temperature-sensor $ python3 app.py 
    Temperature 26°C
    Temperature 26°C
    Temperature 28°C
    Temperature 30°C
    Temperature 32°C
    ```

> 💁 Kod ten znajdziesz w folderze [code-temperature/pi](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/pi).

😀 Twój program do obsługi czujnika temperatury zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.