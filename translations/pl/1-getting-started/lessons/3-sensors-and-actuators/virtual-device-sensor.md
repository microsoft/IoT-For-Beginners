<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "11f10c6760fb8202cf368422702fdf70",
  "translation_date": "2025-08-26T07:04:56+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-sensor.md",
  "language_code": "pl"
}
-->
# Zbuduj lampkę nocną - Wirtualny sprzęt IoT

W tej części lekcji dodasz czujnik światła do swojego wirtualnego urządzenia IoT.

## Wirtualny sprzęt

Lampka nocna potrzebuje jednego czujnika, utworzonego w aplikacji CounterFit.

Czujnik to **czujnik światła**. W fizycznym urządzeniu IoT byłby to [fotodioda](https://wikipedia.org/wiki/Photodiode), która przekształca światło w sygnał elektryczny. Czujniki światła są analogowymi czujnikami, które wysyłają wartość całkowitą wskazującą względną ilość światła, która nie odpowiada żadnej standardowej jednostce miary, takiej jak [lux](https://wikipedia.org/wiki/Lux).

### Dodaj czujniki do CounterFit

Aby użyć wirtualnego czujnika światła, musisz dodać go do aplikacji CounterFit.

#### Zadanie - dodaj czujniki do CounterFit

Dodaj czujnik światła do aplikacji CounterFit.

1. Upewnij się, że aplikacja internetowa CounterFit działa z poprzedniej części tego zadania. Jeśli nie, uruchom ją.

1. Utwórz czujnik światła:

    1. W polu *Create sensor* w panelu *Sensors* rozwiń pole *Sensor type* i wybierz *Light*.

    1. Pozostaw *Units* ustawione na *NoUnits*.

    1. Upewnij się, że *Pin* jest ustawiony na *0*.

    1. Wybierz przycisk **Add**, aby utworzyć czujnik światła na Pinie 0.

    ![Ustawienia czujnika światła](../../../../../translated_images/pl/counterfit-create-light-sensor.9f36a5e0d4458d8d554d54b34d2c806d56093d6e49fddcda2d20f6fef7f5cce1.png)

    Czujnik światła zostanie utworzony i pojawi się na liście czujników.

    ![Utworzony czujnik światła](../../../../../translated_images/pl/counterfit-light-sensor.5d0f5584df56b90f6b2561910d9cb20dfbd73eeff2177c238d38f4de54aefae1.png)

## Programowanie czujnika światła

Urządzenie może teraz zostać zaprogramowane do korzystania z wbudowanego czujnika światła.

### Zadanie - zaprogramuj czujnik światła

Zaprogramuj urządzenie.

1. Otwórz projekt lampki nocnej w VS Code, który utworzyłeś w poprzedniej części tego zadania. Jeśli to konieczne, zamknij i ponownie utwórz terminal, aby upewnić się, że działa w wirtualnym środowisku.

1. Otwórz plik `app.py`.

1. Dodaj poniższy kod na początku pliku `app.py` wraz z pozostałymi instrukcjami `import`, aby zaimportować wymagane biblioteki:

    ```python
    import time
    from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor
    ```

    Instrukcja `import time` importuje moduł Python `time`, który będzie używany później w tym zadaniu.

    Instrukcja `from counterfit_shims_grove.grove_light_sensor_v1_2 import GroveLightSensor` importuje `GroveLightSensor` z bibliotek Python CounterFit Grove shim. Ta biblioteka zawiera kod do obsługi czujnika światła utworzonego w aplikacji CounterFit.

1. Dodaj poniższy kod na końcu pliku, aby utworzyć instancje klas zarządzających czujnikiem światła:

    ```python
    light_sensor = GroveLightSensor(0)
    ```

    Linia `light_sensor = GroveLightSensor(0)` tworzy instancję klasy `GroveLightSensor`, łącząc się z pinem **0** - pinem CounterFit Grove, do którego podłączony jest czujnik światła.

1. Dodaj nieskończoną pętlę po powyższym kodzie, aby odczytywać wartość czujnika światła i wyświetlać ją w konsoli:

    ```python
    while True:
        light = light_sensor.light
        print('Light level:', light)
    ```

    To odczyta aktualny poziom światła za pomocą właściwości `light` klasy `GroveLightSensor`. Ta właściwość odczytuje wartość analogową z pinu. Następnie wartość ta zostanie wyświetlona w konsoli.

1. Dodaj krótką pauzę trwającą jedną sekundę na końcu pętli `while`, ponieważ poziomy światła nie muszą być sprawdzane ciągle. Pauza zmniejsza zużycie energii przez urządzenie.

    ```python
    time.sleep(1)
    ```

1. W terminalu VS Code uruchom poniższe polecenie, aby uruchomić swoją aplikację w Pythonie:

    ```sh
    python3 app.py
    ```

    Wartości światła zostaną wyświetlone w konsoli. Początkowo wartość ta będzie wynosić 0.

1. W aplikacji CounterFit zmień wartość czujnika światła, która będzie odczytywana przez aplikację. Możesz to zrobić na dwa sposoby:

    * Wpisz liczbę w polu *Value* dla czujnika światła, a następnie wybierz przycisk **Set**. Liczba, którą wpiszesz, będzie wartością zwracaną przez czujnik.

    * Zaznacz pole *Random* i wpisz wartości *Min* oraz *Max*, a następnie wybierz przycisk **Set**. Za każdym razem, gdy czujnik odczytuje wartość, będzie odczytywał losową liczbę pomiędzy *Min* a *Max*.

    Wartości, które ustawisz, zostaną wyświetlone w konsoli. Zmień ustawienia *Value* lub *Random*, aby wartość się zmieniała.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

> 💁 Ten kod znajdziesz w folderze [code-sensor/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/virtual-device).

😀 Twój program lampki nocnej zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.