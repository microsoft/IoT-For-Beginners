# Mierz temperaturę - Wirtualny sprzęt IoT

W tej części lekcji dodasz czujnik temperatury do swojego wirtualnego urządzenia IoT.

## Wirtualny sprzęt

Wirtualne urządzenie IoT będzie korzystać z symulowanego czujnika Grove Digital Humidity and Temperature. Dzięki temu laboratorium pozostaje takie samo, jak przy użyciu Raspberry Pi z fizycznym czujnikiem Grove DHT11.

Czujnik łączy **czujnik temperatury** z **czujnikiem wilgotności**, ale w tym laboratorium interesuje Cię tylko komponent czujnika temperatury. W fizycznym urządzeniu IoT czujnik temperatury byłby [termistorem](https://wikipedia.org/wiki/Thermistor), który mierzy temperaturę, wykrywając zmiany oporu w zależności od zmian temperatury. Czujniki temperatury są zazwyczaj cyfrowe i wewnętrznie przekształcają zmierzony opór na temperaturę w stopniach Celsjusza (lub Kelwina, lub Fahrenheita).

### Dodaj czujniki do CounterFit

Aby użyć wirtualnego czujnika wilgotności i temperatury, musisz dodać oba czujniki do aplikacji CounterFit.

#### Zadanie - dodaj czujniki do CounterFit

Dodaj czujniki wilgotności i temperatury do aplikacji CounterFit.

1. Utwórz nową aplikację Python na swoim komputerze w folderze `temperature-sensor` z jednym plikiem o nazwie `app.py` oraz wirtualnym środowiskiem Python, a następnie dodaj pakiety pip CounterFit.

    > ⚠️ Możesz odwołać się do [instrukcji dotyczących tworzenia i konfiguracji projektu Python dla CounterFit w lekcji 1, jeśli zajdzie taka potrzeba](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Zainstaluj dodatkowy pakiet Pip, aby zainstalować CounterFit shim dla czujnika DHT11. Upewnij się, że instalujesz go z terminala z aktywowanym wirtualnym środowiskiem.

    ```sh
    pip install counterfit-shims-seeed-python-dht
    ```

1. Upewnij się, że aplikacja webowa CounterFit działa.

1. Utwórz czujnik wilgotności:

    1. W polu *Create sensor* w panelu *Sensors* rozwiń pole *Sensor type* i wybierz *Humidity*.

    1. Pozostaw *Units* ustawione na *Percentage*.

    1. Upewnij się, że *Pin* jest ustawiony na *5*.

    1. Wybierz przycisk **Add**, aby utworzyć czujnik wilgotności na pinie 5.

    ![Ustawienia czujnika wilgotności](../../../../../translated_images/pl/counterfit-create-humidity-sensor.2750e27b6f30e09c.webp)

    Czujnik wilgotności zostanie utworzony i pojawi się na liście czujników.

    ![Utworzony czujnik wilgotności](../../../../../translated_images/pl/counterfit-humidity-sensor.7b12f7f339e430cb.webp)

1. Utwórz czujnik temperatury:

    1. W polu *Create sensor* w panelu *Sensors* rozwiń pole *Sensor type* i wybierz *Temperature*.

    1. Pozostaw *Units* ustawione na *Celsius*.

    1. Upewnij się, że *Pin* jest ustawiony na *6*.

    1. Wybierz przycisk **Add**, aby utworzyć czujnik temperatury na pinie 6.

    ![Ustawienia czujnika temperatury](../../../../../translated_images/pl/counterfit-create-temperature-sensor.199350ed34f7343d.webp)

    Czujnik temperatury zostanie utworzony i pojawi się na liście czujników.

    ![Utworzony czujnik temperatury](../../../../../translated_images/pl/counterfit-temperature-sensor.f0560236c96a9016.webp)

## Programowanie aplikacji czujnika temperatury

Teraz możesz zaprogramować aplikację czujnika temperatury, korzystając z czujników CounterFit.

### Zadanie - zaprogramuj aplikację czujnika temperatury

Zaprogramuj aplikację czujnika temperatury.

1. Upewnij się, że aplikacja `temperature-sensor` jest otwarta w VS Code.

1. Otwórz plik `app.py`.

1. Dodaj następujący kod na początku pliku `app.py`, aby połączyć aplikację z CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Dodaj następujący kod do pliku `app.py`, aby zaimportować wymagane biblioteki:

    ```python
    import time
    from counterfit_shims_seeed_python_dht import DHT
    ```

    Instrukcja `from seeed_dht import DHT` importuje klasę `DHT`, która umożliwia interakcję z wirtualnym czujnikiem Grove temperatury za pomocą shima z modułu `counterfit_shims_seeed_python_dht`.

1. Dodaj następujący kod po powyższym, aby utworzyć instancję klasy zarządzającej wirtualnym czujnikiem wilgotności i temperatury:

    ```python
    sensor = DHT("11", 5)
    ```

    To deklaruje instancję klasy `DHT`, która zarządza wirtualnym **D**igital **H**umidity and **T**emperature sensor. Pierwszy parametr informuje kod, że używany czujnik to wirtualny *DHT11*. Drugi parametr informuje kod, że czujnik jest podłączony do portu `5`.

    > 💁 CounterFit symuluje ten połączony czujnik wilgotności i temperatury, łącząc się z dwoma czujnikami: czujnikiem wilgotności na pinie podanym podczas tworzenia klasy `DHT` oraz czujnikiem temperatury działającym na następnym pinie. Jeśli czujnik wilgotności jest na pinie 5, shim oczekuje, że czujnik temperatury będzie na pinie 6.

1. Dodaj nieskończoną pętlę po powyższym kodzie, aby odczytywać wartość czujnika temperatury i wyświetlać ją w konsoli:

    ```python
    while True:
        _, temp = sensor.read()
        print(f'Temperature {temp}°C')
    ```

    Wywołanie `sensor.read()` zwraca krotkę zawierającą wilgotność i temperaturę. Potrzebujesz tylko wartości temperatury, więc wilgotność jest ignorowana. Wartość temperatury jest następnie wyświetlana w konsoli.

1. Dodaj krótką pauzę trwającą dziesięć sekund na końcu pętli, ponieważ poziomy temperatury nie muszą być sprawdzane ciągle. Pauza zmniejsza zużycie energii przez urządzenie.

    ```python
    time.sleep(10)
    ```

1. Z terminala VS Code z aktywowanym wirtualnym środowiskiem uruchom następujące polecenie, aby uruchomić swoją aplikację Python:

    ```sh
    python app.py
    ```

1. W aplikacji CounterFit zmień wartość czujnika temperatury, która będzie odczytywana przez aplikację. Możesz to zrobić na dwa sposoby:

    * Wpisz liczbę w polu *Value* dla czujnika temperatury, a następnie wybierz przycisk **Set**. Liczba, którą wpiszesz, będzie wartością zwracaną przez czujnik.

    * Zaznacz pole *Random*, wpisz wartości *Min* i *Max*, a następnie wybierz przycisk **Set**. Za każdym razem, gdy czujnik odczytuje wartość, będzie to losowa liczba pomiędzy *Min* a *Max*.

    Powinieneś zobaczyć wartości, które ustawiłeś, pojawiające się w konsoli. Zmień *Value* lub ustawienia *Random*, aby zobaczyć zmieniające się wartości.

    ```output
    (.venv) ➜  temperature-sensor python app.py
    Temperature 28.25°C
    Temperature 30.71°C
    Temperature 25.17°C
    ```

> 💁 Ten kod znajdziesz w folderze [code-temperature/virtual-device](../../../../../2-farm/lessons/1-predict-plant-growth/code-temperature/virtual-device).

😀 Twoja aplikacja czujnika temperatury zakończyła się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.