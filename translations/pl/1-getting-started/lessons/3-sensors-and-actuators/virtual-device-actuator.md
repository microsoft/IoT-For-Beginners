<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9c640f93263fd9adbfda920739e09feb",
  "translation_date": "2025-08-26T07:04:36+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/virtual-device-actuator.md",
  "language_code": "pl"
}
-->
# Zbuduj lampkę nocną - Wirtualny sprzęt IoT

W tej części lekcji dodasz diodę LED do swojego wirtualnego urządzenia IoT i użyjesz jej do stworzenia lampki nocnej.

## Wirtualny sprzęt

Lampka nocna wymaga jednego aktuatora, który zostanie utworzony w aplikacji CounterFit.

Aktuatorem jest **LED**. W fizycznym urządzeniu IoT byłaby to [dioda elektroluminescencyjna](https://wikipedia.org/wiki/Dioda_elektroluminescencyjna), która emituje światło, gdy przepływa przez nią prąd. Jest to cyfrowy aktuator, który ma dwa stany: włączony i wyłączony. Wysłanie wartości 1 włącza diodę LED, a 0 ją wyłącza.

Logika lampki nocnej w pseudokodzie wygląda następująco:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Dodaj aktuator do CounterFit

Aby użyć wirtualnej diody LED, musisz dodać ją do aplikacji CounterFit.

#### Zadanie - dodaj aktuator do CounterFit

Dodaj diodę LED do aplikacji CounterFit.

1. Upewnij się, że aplikacja webowa CounterFit działa z poprzedniej części tego zadania. Jeśli nie, uruchom ją ponownie i dodaj czujnik światła.

1. Utwórz diodę LED:

    1. W polu *Create actuator* w panelu *Actuator* rozwiń listę *Actuator type* i wybierz *LED*.

    1. Ustaw *Pin* na *5*.

    1. Wybierz przycisk **Add**, aby utworzyć diodę LED na pinie 5.

    ![Ustawienia diody LED](../../../../../translated_images/pl/counterfit-create-led.ba9db1c9b8c622a635d6dfae5cdc4e70c2b250635bd4f0601c6cf0bd22b7ba46.png)

    Dioda LED zostanie utworzona i pojawi się na liście aktuatorów.

    ![Utworzona dioda LED](../../../../../translated_images/pl/counterfit-led.c0ab02de6d256ad84d9bad4d67a7faa709f0ea83e410cfe9b5561ef0cef30b1c.png)

    Po utworzeniu diody LED możesz zmienić jej kolor za pomocą selektora *Color*. Wybierz przycisk **Set**, aby zmienić kolor po jego wybraniu.

### Zaprogramuj lampkę nocną

Teraz możesz zaprogramować lampkę nocną, używając czujnika światła i diody LED w CounterFit.

#### Zadanie - zaprogramuj lampkę nocną

Zaprogramuj lampkę nocną.

1. Otwórz projekt lampki nocnej w VS Code, który utworzyłeś w poprzedniej części tego zadania. Jeśli to konieczne, zamknij i ponownie utwórz terminal, aby upewnić się, że działa w wirtualnym środowisku.

1. Otwórz plik `app.py`.

1. Dodaj poniższy kod do pliku `app.py`, aby zaimportować wymaganą bibliotekę. Kod ten powinien zostać dodany na górze, poniżej innych linii `import`.

    ```python
    from counterfit_shims_grove.grove_led import GroveLed
    ```

    Linia `from counterfit_shims_grove.grove_led import GroveLed` importuje `GroveLed` z bibliotek Python CounterFit Grove shim. Ta biblioteka zawiera kod do obsługi diody LED utworzonej w aplikacji CounterFit.

1. Dodaj poniższy kod po deklaracji `light_sensor`, aby utworzyć instancję klasy zarządzającej diodą LED:

    ```python
    led = GroveLed(5)
    ```

    Linia `led = GroveLed(5)` tworzy instancję klasy `GroveLed`, łącząc się z pinem **5** - pinem CounterFit Grove, do którego podłączona jest dioda LED.

1. Dodaj sprawdzenie wewnątrz pętli `while`, przed `time.sleep`, aby sprawdzić poziomy światła i włączyć lub wyłączyć diodę LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ten kod sprawdza wartość `light`. Jeśli jest mniejsza niż 300, wywołuje metodę `on` klasy `GroveLed`, która wysyła wartość cyfrową 1 do diody LED, włączając ją. Jeśli wartość światła jest większa lub równa 300, wywołuje metodę `off`, wysyłając wartość cyfrową 0 do diody LED, wyłączając ją.

    > 💁 Ten kod powinien być wcięty na tym samym poziomie co linia `print('Light level:', light)`, aby znajdował się wewnątrz pętli `while`!

1. W terminalu VS Code uruchom poniższe polecenie, aby uruchomić swoją aplikację w Pythonie:

    ```sh
    python3 app.py
    ```

    Wartości światła będą wyświetlane w konsoli.

    ```output
    (.venv) ➜  GroveTest python3 app.py 
    Light level: 143
    Light level: 244
    Light level: 246
    Light level: 253
    ```

1. Zmień ustawienia *Value* lub *Random*, aby zmieniać poziom światła powyżej i poniżej 300. Dioda LED będzie się włączać i wyłączać.

![Dioda LED w aplikacji CounterFit włączająca się i wyłączająca w zależności od poziomu światła](../../../../../images/virtual-device-running-assignment-1-1.gif)

> 💁 Ten kod znajdziesz w folderze [code-actuator/virtual-device](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/virtual-device).

😀 Twój program lampki nocnej działa poprawnie!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.