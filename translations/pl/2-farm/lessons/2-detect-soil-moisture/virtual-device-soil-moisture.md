<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "2bf65f162bcebd35fbcba5fd245afac4",
  "translation_date": "2025-08-26T06:52:04+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/virtual-device-soil-moisture.md",
  "language_code": "pl"
}
-->
# Pomiar wilgotności gleby - Wirtualny sprzęt IoT

W tej części lekcji dodasz pojemnościowy czujnik wilgotności gleby do swojego wirtualnego urządzenia IoT i odczytasz z niego wartości.

## Wirtualny sprzęt

Wirtualne urządzenie IoT będzie korzystać z symulowanego pojemnościowego czujnika wilgotności gleby Grove. Dzięki temu laboratorium pozostaje takie samo, jak w przypadku użycia Raspberry Pi z fizycznym pojemnościowym czujnikiem wilgotności gleby Grove.

W fizycznym urządzeniu IoT czujnik wilgotności gleby byłby pojemnościowym czujnikiem, który mierzy wilgotność gleby poprzez wykrywanie jej pojemności, właściwości zmieniającej się wraz ze zmianą wilgotności gleby. Wraz ze wzrostem wilgotności gleby napięcie maleje.

Jest to czujnik analogowy, który wykorzystuje symulowany 10-bitowy przetwornik ADC do raportowania wartości w zakresie od 1 do 1 023.

### Dodanie czujnika wilgotności gleby do CounterFit

Aby użyć wirtualnego czujnika wilgotności gleby, musisz dodać go do aplikacji CounterFit.

#### Zadanie - Dodanie czujnika wilgotności gleby do CounterFit

Dodaj czujnik wilgotności gleby do aplikacji CounterFit.

1. Utwórz nową aplikację Python na swoim komputerze w folderze o nazwie `soil-moisture-sensor` z jednym plikiem o nazwie `app.py` oraz wirtualnym środowiskiem Python, a następnie dodaj pakiety pip CounterFit.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia i konfigurowania projektu Python w CounterFit w lekcji 1, jeśli to konieczne](../../../1-getting-started/lessons/1-introduction-to-iot/virtual-device.md).

1. Upewnij się, że aplikacja internetowa CounterFit jest uruchomiona.

1. Utwórz czujnik wilgotności gleby:

    1. W polu *Create sensor* w panelu *Sensors* rozwiń pole *Sensor type* i wybierz *Soil Moisture*.

    1. Pozostaw *Units* ustawione na *NoUnits*.

    1. Upewnij się, że *Pin* jest ustawiony na *0*.

    1. Wybierz przycisk **Add**, aby utworzyć czujnik *Soil Moisture* na pinie 0.

    ![Ustawienia czujnika wilgotności gleby](../../../../../translated_images/pl/counterfit-create-soil-moisture-sensor.35266135a5e0ae68b29a684d7db0d2933a8098b2307d197f7c71577b724603aa.png)

    Czujnik wilgotności gleby zostanie utworzony i pojawi się na liście czujników.

    ![Utworzony czujnik wilgotności gleby](../../../../../translated_images/pl/counterfit-soil-moisture-sensor.81742b2de0e9de60a3b3b9a2ff8ecc686d428eb6d71820f27a693be26e5aceee.png)

## Programowanie aplikacji czujnika wilgotności gleby

Teraz możesz zaprogramować aplikację czujnika wilgotności gleby, korzystając z czujników CounterFit.

### Zadanie - Programowanie aplikacji czujnika wilgotności gleby

Zaprogramuj aplikację czujnika wilgotności gleby.

1. Upewnij się, że aplikacja `soil-moisture-sensor` jest otwarta w VS Code.

1. Otwórz plik `app.py`.

1. Dodaj następujący kod na początku pliku `app.py`, aby połączyć aplikację z CounterFit:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

1. Dodaj następujący kod do pliku `app.py`, aby zaimportować wymagane biblioteki:

    ```python
    import time
    from counterfit_shims_grove.adc import ADC
    ```

    Instrukcja `import time` importuje moduł `time`, który będzie używany później w tym zadaniu.

    Instrukcja `from counterfit_shims_grove.adc import ADC` importuje klasę `ADC`, aby umożliwić interakcję z wirtualnym przetwornikiem analogowo-cyfrowym, który może być połączony z czujnikiem CounterFit.

1. Dodaj poniżej następujący kod, aby utworzyć instancję klasy `ADC`:

    ```python
    adc = ADC()
    ```

1. Dodaj nieskończoną pętlę, która odczytuje dane z tego przetwornika ADC na pinie 0 i zapisuje wynik w konsoli. Pętla ta może następnie usypiać na 10 sekund między odczytami.

    ```python
    while True:
        soil_moisture = adc.read(0)
        print("Soil moisture:", soil_moisture)
    
        time.sleep(10)
    ```

1. W aplikacji CounterFit zmień wartość czujnika wilgotności gleby, która będzie odczytywana przez aplikację. Możesz to zrobić na dwa sposoby:

    * Wpisz liczbę w polu *Value* dla czujnika wilgotności gleby, a następnie wybierz przycisk **Set**. Liczba, którą wpiszesz, będzie wartością zwracaną przez czujnik.

    * Zaznacz pole *Random* i wpisz wartości *Min* oraz *Max*, a następnie wybierz przycisk **Set**. Za każdym razem, gdy czujnik odczyta wartość, będzie to losowa liczba z zakresu *Min* i *Max*.

1. Uruchom aplikację Python. Zobaczysz pomiary wilgotności gleby wypisywane w konsoli. Zmień wartość w polu *Value* lub ustawienia *Random*, aby zobaczyć zmieniające się wartości.

    ```output
    (.venv) ➜ soil-moisture-sensor $ python app.py 
    Soil moisture: 615
    Soil moisture: 612
    Soil moisture: 498
    Soil moisture: 493
    Soil moisture: 490
    Soil Moisture: 388
    ```

> 💁 Kod ten znajdziesz w folderze [code/virtual-device](../../../../../2-farm/lessons/2-detect-soil-moisture/code/virtual-device).

😀 Twój program czujnika wilgotności gleby zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.