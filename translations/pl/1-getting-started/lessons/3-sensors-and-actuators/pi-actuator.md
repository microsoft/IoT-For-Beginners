# Zbuduj lampkę nocną - Raspberry Pi

W tej części lekcji dodasz diodę LED do swojego Raspberry Pi i użyjesz jej do stworzenia lampki nocnej.

## Sprzęt

Lampka nocna potrzebuje teraz aktuatora.

Aktuatorem jest **LED**, czyli [dioda emitująca światło](https://wikipedia.org/wiki/Light-emitting_diode), która świeci, gdy przepływa przez nią prąd. Jest to cyfrowy aktuator, który ma dwa stany: włączony i wyłączony. Wysłanie wartości 1 włącza diodę LED, a 0 ją wyłącza. LED jest zewnętrznym aktuatoriem Grove i musi być podłączony do Grove Base hat na Raspberry Pi.

Logika lampki nocnej w pseudokodzie wygląda następująco:

```output
Check the light level.
If the light is less than 300
    Turn the LED on
Otherwise
    Turn the LED off
```

### Podłącz diodę LED

Dioda Grove LED jest dostępna jako moduł z wyborem diod LED, co pozwala wybrać kolor.

#### Zadanie - podłącz diodę LED

Podłącz diodę LED.

![Dioda Grove LED](../../../../../translated_images/pl/grove-led.6c853be93f473cf2.webp)

1. Wybierz swoją ulubioną diodę LED i włóż jej nóżki do dwóch otworów w module LED.

    Diody LED to diody emitujące światło, a diody to urządzenia elektroniczne, które mogą przewodzić prąd tylko w jednym kierunku. Oznacza to, że dioda LED musi być podłączona w odpowiedni sposób, inaczej nie będzie działać.

    Jedna z nóżek diody LED to pin dodatni, a druga to pin ujemny. Dioda LED nie jest idealnie okrągła i jest nieco bardziej płaska z jednej strony. Ta bardziej płaska strona to pin ujemny. Podłączając diodę LED do modułu, upewnij się, że nóżka po stronie zaokrąglonej jest podłączona do gniazda oznaczonego **+** na zewnątrz modułu, a płaska strona jest podłączona do gniazda bliżej środka modułu.

1. Moduł LED ma pokrętło, które pozwala kontrolować jasność. Na początek ustaw je na maksymalną jasność, obracając je w kierunku przeciwnym do ruchu wskazówek zegara, aż do oporu, używając małego śrubokręta krzyżakowego.

1. Włóż jeden koniec kabla Grove do gniazda w module LED. Kabel wejdzie tylko w jednym kierunku.

1. Przy wyłączonym Raspberry Pi podłącz drugi koniec kabla Grove do gniazda cyfrowego oznaczonego **D5** na Grove Base hat podłączonym do Pi. To gniazdo znajduje się jako drugie od lewej, w rzędzie gniazd obok pinów GPIO.

![Dioda Grove LED podłączona do gniazda D5](../../../../../translated_images/pl/pi-led.97f1d474981dc35d.webp)

## Zaprogramuj lampkę nocną

Lampka nocna może teraz zostać zaprogramowana przy użyciu czujnika światła Grove i diody LED Grove.

### Zadanie - zaprogramuj lampkę nocną

Zaprogramuj lampkę nocną.

1. Włącz Raspberry Pi i poczekaj, aż się uruchomi.

1. Otwórz projekt lampki nocnej w VS Code, który utworzyłeś w poprzedniej części zadania, uruchamiając go bezpośrednio na Pi lub łącząc się za pomocą rozszerzenia Remote SSH.

1. Dodaj poniższy kod do pliku `app.py`, aby zaimportować wymaganą bibliotekę. Kod ten powinien być dodany na górze, poniżej innych linii `import`.

    ```python
    from grove.grove_led import GroveLed
    ```

    Instrukcja `from grove.grove_led import GroveLed` importuje `GroveLed` z bibliotek Python Grove. Ta biblioteka zawiera kod do interakcji z diodą LED Grove.

1. Dodaj poniższy kod po deklaracji `light_sensor`, aby utworzyć instancję klasy zarządzającej diodą LED:

    ```python
    led = GroveLed(5)
    ```

    Linia `led = GroveLed(5)` tworzy instancję klasy `GroveLed`, łącząc się z pinem **D5** - cyfrowym pinem Grove, do którego podłączona jest dioda LED.

    > 💁 Wszystkie gniazda mają unikalne numery pinów. Piny 0, 2, 4 i 6 to piny analogowe, a piny 5, 16, 18, 22, 24 i 26 to piny cyfrowe.

1. Dodaj sprawdzenie wewnątrz pętli `while`, przed `time.sleep`, aby sprawdzić poziomy światła i włączyć lub wyłączyć diodę LED:

    ```python
    if light < 300:
        led.on()
    else:
        led.off()
    ```

    Ten kod sprawdza wartość `light`. Jeśli jest ona mniejsza niż 300, wywołuje metodę `on` klasy `GroveLed`, która wysyła wartość cyfrową 1 do diody LED, włączając ją. Jeśli wartość światła jest większa lub równa 300, wywołuje metodę `off`, wysyłając wartość cyfrową 0 do diody LED, wyłączając ją.

    > 💁 Ten kod powinien być wcięty na tym samym poziomie co linia `print('Light level:', light)`, aby znajdował się wewnątrz pętli while!

    > 💁 Podczas wysyłania wartości cyfrowych do aktuatorów wartość 0 oznacza 0V, a wartość 1 oznacza maksymalne napięcie dla urządzenia. Dla Raspberry Pi z czujnikami i aktuatorami Grove napięcie 1 wynosi 3.3V.

1. W terminalu VS Code uruchom poniższe polecenie, aby uruchomić swoją aplikację w Pythonie:

    ```sh
    python3 app.py
    ```

    Wartości światła będą wyświetlane w konsoli.

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py 
    Light level: 634
    Light level: 634
    Light level: 634
    Light level: 230
    Light level: 104
    Light level: 290
    ```

1. Zakryj i odkryj czujnik światła. Zauważ, że dioda LED zapali się, jeśli poziom światła wynosi 300 lub mniej, a wyłączy się, gdy poziom światła będzie większy niż 300.

    > 💁 Jeśli dioda LED się nie zapala, upewnij się, że jest podłączona w odpowiedni sposób, a pokrętło jest ustawione na maksymalną jasność.

![Dioda LED podłączona do Pi zapala się i gaśnie w zależności od poziomu światła](../../../../../images/pi-running-assignment-1-1.gif)

> 💁 Ten kod znajdziesz w folderze [code-actuator/pi](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/pi).

😀 Twój program lampki nocnej zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.