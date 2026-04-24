# Wykrywanie bliskości - Wirtualny sprzęt IoT

W tej części lekcji dodasz czujnik bliskości do swojego wirtualnego urządzenia IoT i odczytasz z niego odległość.

## Sprzęt

Wirtualne urządzenie IoT będzie korzystać z symulowanego czujnika odległości.

W fizycznym urządzeniu IoT użyłbyś czujnika z modułem pomiaru odległości za pomocą lasera.

### Dodanie czujnika odległości do CounterFit

Aby użyć wirtualnego czujnika odległości, musisz dodać go do aplikacji CounterFit.

#### Zadanie - dodanie czujnika odległości do CounterFit

Dodaj czujnik odległości do aplikacji CounterFit.

1. Otwórz kod `fruit-quality-detector` w VS Code i upewnij się, że środowisko wirtualne jest aktywne.

1. Zainstaluj dodatkowy pakiet Pip, aby dodać CounterFit shim, który może symulować czujniki odległości, naśladując pakiet [rpi-vl53l0x Pip](https://pypi.org/project/rpi-vl53l0x/), czyli pakiet Pythona współpracujący z [czujnikiem odległości VL53L0X](https://wiki.seeedstudio.com/Grove-Time_of_Flight_Distance_Sensor-VL53L0X/). Upewnij się, że instalujesz to z terminala z aktywowanym środowiskiem wirtualnym.

    ```sh
    pip install counterfit-shims-rpi-vl53l0x
    ```

1. Upewnij się, że aplikacja webowa CounterFit działa.

1. Utwórz czujnik odległości:

    1. W polu *Create sensor* w panelu *Sensors* rozwiń pole *Sensor type* i wybierz *Distance*.

    1. Pozostaw jednostki jako `Millimeter`.

    1. Ten czujnik to czujnik I²C, więc ustaw adres na `0x29`. Jeśli używałbyś fizycznego czujnika VL53L0X, byłby on zakodowany na stałe na tym adresie.

    1. Wybierz przycisk **Add**, aby utworzyć czujnik odległości.

    ![Ustawienia czujnika odległości](../../../../../translated_images/pl/counterfit-create-distance-sensor.967c9fb98f27888d.webp)

    Czujnik odległości zostanie utworzony i pojawi się na liście czujników.

    ![Utworzony czujnik odległości](../../../../../translated_images/pl/counterfit-distance-sensor.079eefeeea0b68af.webp)

## Programowanie czujnika odległości

Wirtualne urządzenie IoT może teraz zostać zaprogramowane do korzystania z symulowanego czujnika odległości.

### Zadanie - programowanie czujnika czasu przelotu

1. Utwórz nowy plik w projekcie `fruit-quality-detector` o nazwie `distance-sensor.py`.

    > 💁 Łatwym sposobem na symulowanie wielu urządzeń IoT jest tworzenie każdego z nich w osobnym pliku Pythona, a następnie uruchamianie ich jednocześnie.

1. Rozpocznij połączenie z CounterFit za pomocą poniższego kodu:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Dodaj poniższy kod poniżej:

    ```python
    import time
    
    from counterfit_shims_rpi_vl53l0x.vl53l0x import VL53L0X
    ```

    Importuje to bibliotekę shim dla czujnika czasu przelotu VL53L0X.

1. Poniżej tego dodaj następujący kod, aby uzyskać dostęp do czujnika:

    ```python
    distance_sensor = VL53L0X()
    distance_sensor.begin()
    ```

    Kod ten deklaruje czujnik odległości, a następnie go uruchamia.

1. Na koniec dodaj nieskończoną pętlę do odczytu odległości:

    ```python
    while True:
        distance_sensor.wait_ready()
        print(f'Distance = {distance_sensor.get_distance()} mm')
        time.sleep(1)
    ```

    Kod ten czeka na wartość gotową do odczytu z czujnika, a następnie wypisuje ją w konsoli.

1. Uruchom ten kod.

    > 💁 Pamiętaj, że ten plik nazywa się `distance-sensor.py`! Upewnij się, że uruchamiasz go za pomocą Pythona, a nie `app.py`.

1. Zobaczysz pomiary odległości pojawiające się w konsoli. Zmień wartość w CounterFit, aby zobaczyć, jak zmienia się ta wartość, lub użyj losowych wartości.

    ```output
    (.venv) ➜  fruit-quality-detector python distance-sensor.py 
    Distance = 37 mm
    Distance = 42 mm
    Distance = 29 mm
    ```

> 💁 Kod ten znajdziesz w folderze [code-proximity/virtual-iot-device](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector/code-proximity/virtual-iot-device).

😀 Twój program czujnika bliskości działa poprawnie!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.