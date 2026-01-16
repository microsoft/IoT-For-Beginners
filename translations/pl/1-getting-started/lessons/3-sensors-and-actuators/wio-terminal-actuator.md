<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "db44083b4dc6fb06eac83c4f16448940",
  "translation_date": "2025-08-26T07:04:10+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-actuator.md",
  "language_code": "pl"
}
-->
# Zbuduj lampkę nocną - Wio Terminal

W tej części lekcji dodasz diodę LED do swojego Wio Terminal i użyjesz jej do stworzenia lampki nocnej.

## Sprzęt

Lampka nocna potrzebuje teraz aktuatora.

Aktuatorem jest **LED**, czyli [dioda emitująca światło](https://wikipedia.org/wiki/Light-emitting_diode), która świeci, gdy przepływa przez nią prąd. Jest to cyfrowy aktuator, który ma dwa stany: włączony i wyłączony. Wysłanie wartości 1 włącza diodę LED, a 0 ją wyłącza. Jest to zewnętrzny aktuator Grove, który należy podłączyć do Wio Terminal.

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

![Dioda Grove LED](../../../../../translated_images/pl/grove-led.6c853be93f473cf2c439cfc74bb1064732b22251a83cedf66e62f783f9cc1a79.png)

1. Wybierz swoją ulubioną diodę LED i włóż jej nóżki do dwóch otworów w module LED.

    Diody LED to diody emitujące światło, a diody to urządzenia elektroniczne, które mogą przewodzić prąd tylko w jednym kierunku. Oznacza to, że dioda LED musi być podłączona w odpowiedni sposób, inaczej nie będzie działać.

    Jedna z nóżek diody LED to pin dodatni, a druga to pin ujemny. Dioda LED nie jest idealnie okrągła i jest lekko spłaszczona z jednej strony. Lekko spłaszczona strona to pin ujemny. Podłączając diodę LED do modułu, upewnij się, że nóżka po stronie zaokrąglonej jest podłączona do gniazda oznaczonego **+** na zewnątrz modułu, a spłaszczona strona jest podłączona do gniazda bliżej środka modułu.

1. Moduł LED ma pokrętło, które pozwala kontrolować jasność. Na początek ustaw je na maksymalną jasność, obracając je w kierunku przeciwnym do ruchu wskazówek zegara, aż do oporu, używając małego śrubokręta krzyżakowego.

1. Włóż jeden koniec kabla Grove do gniazda w module LED. Kabel wejdzie tylko w jednym kierunku.

1. Gdy Wio Terminal jest odłączony od komputera lub innego źródła zasilania, podłącz drugi koniec kabla Grove do gniazda Grove po prawej stronie Wio Terminal, patrząc na ekran. Jest to gniazdo najbardziej oddalone od przycisku zasilania.

    > 💁 Prawe gniazdo Grove może być używane z analogowymi lub cyfrowymi czujnikami i aktuatorami. Lewe gniazdo jest przeznaczone tylko dla czujników i aktuatorów cyfrowych. C zostanie omówione w późniejszej lekcji.

![Dioda Grove LED podłączona do prawego gniazda](../../../../../translated_images/pl/wio-led.265a1897e72d7f21.webp)

## Zaprogramuj lampkę nocną

Lampka nocna może teraz zostać zaprogramowana przy użyciu wbudowanego czujnika światła i diody Grove LED.

### Zadanie - zaprogramuj lampkę nocną

Zaprogramuj lampkę nocną.

1. Otwórz projekt lampki nocnej w VS Code, który utworzyłeś w poprzedniej części tego zadania.

1. Dodaj następującą linię na końcu funkcji `setup`:

    ```cpp
    pinMode(D0, OUTPUT);
    ```

    Ta linia konfiguruje pin używany do komunikacji z diodą LED przez port Grove.

    Pin `D0` to cyfrowy pin dla prawego gniazda Grove. Ten pin jest ustawiony na `OUTPUT`, co oznacza, że łączy się z aktuatorami, a dane będą zapisywane na pinie.

1. Dodaj następujący kod bezpośrednio przed `delay` w funkcji `loop`:

    ```cpp
    if (light < 300)
    {
        digitalWrite(D0, HIGH);
    }
    else
    {
        digitalWrite(D0, LOW);
    }
    ```

    Ten kod sprawdza wartość `light`. Jeśli jest ona mniejsza niż 300, wysyła wartość `HIGH` do cyfrowego pinu `D0`. Wartość `HIGH` to wartość 1, która włącza diodę LED. Jeśli wartość światła jest większa lub równa 300, wysyłana jest wartość `LOW` wynosząca 0, która wyłącza diodę LED.

    > 💁 Podczas wysyłania wartości cyfrowych do aktuatorów wartość LOW to 0V, a wartość HIGH to maksymalne napięcie dla urządzenia. Dla Wio Terminal napięcie HIGH wynosi 3,3V.

1. Podłącz ponownie Wio Terminal do komputera i wgraj nowy kod tak jak wcześniej.

1. Podłącz Serial Monitor. Wartości światła będą wyświetlane w terminalu.

    ```output
    > Executing task: platformio device monitor <

    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Light value: 4
    Light value: 5
    Light value: 4
    Light value: 158
    Light value: 343
    Light value: 348
    Light value: 344
    ```

1. Zakryj i odkryj czujnik światła. Zauważ, jak dioda LED zapala się, gdy poziom światła wynosi 300 lub mniej, i gaśnie, gdy poziom światła jest większy niż 300.

![Dioda LED podłączona do WIO zapala się i gaśnie w zależności od poziomu światła](../../../../../images/wio-running-assignment-1-1.gif)

> 💁 Ten kod znajdziesz w folderze [code-actuator/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-actuator/wio-terminal).

😀 Twój program lampki nocnej zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.