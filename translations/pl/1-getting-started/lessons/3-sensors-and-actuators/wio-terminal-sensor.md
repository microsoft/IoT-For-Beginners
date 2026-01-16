<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "7f4ad0ef54f248b85b92187c94cf9dcb",
  "translation_date": "2025-08-26T07:05:17+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/wio-terminal-sensor.md",
  "language_code": "pl"
}
-->
# Dodaj czujnik - Wio Terminal

W tej części lekcji użyjesz czujnika światła w swoim Wio Terminal.

## Sprzęt

Czujnik używany w tej lekcji to **czujnik światła**, który wykorzystuje [fotodiodę](https://wikipedia.org/wiki/Fotodioda) do przekształcania światła w sygnał elektryczny. Jest to czujnik analogowy, który wysyła wartość całkowitą od 0 do 1 023, wskazując względną ilość światła, która nie jest powiązana z żadną standardową jednostką miary, taką jak [lux](https://wikipedia.org/wiki/Lux).

Czujnik światła jest wbudowany w Wio Terminal i widoczny przez przezroczyste plastikowe okienko z tyłu urządzenia.

![Czujnik światła z tyłu Wio Terminal](../../../../../translated_images/pl/wio-light-sensor.b1f529f3c95f5165.png)

## Programowanie czujnika światła

Urządzenie można teraz zaprogramować do korzystania z wbudowanego czujnika światła.

### Zadanie

Zaprogramuj urządzenie.

1. Otwórz projekt nightlight w VS Code, który utworzyłeś w poprzedniej części tego zadania.

1. Dodaj następującą linię na końcu funkcji `setup`:

    ```cpp
    pinMode(WIO_LIGHT, INPUT);
    ```

    Ta linia konfiguruje piny używane do komunikacji ze sprzętem czujnika.

    Pin `WIO_LIGHT` to numer pinu GPIO połączonego z wbudowanym czujnikiem światła. Ten pin jest ustawiony na `INPUT`, co oznacza, że łączy się z czujnikiem i dane będą odczytywane z tego pinu.

1. Usuń zawartość funkcji `loop`.

1. Dodaj następujący kod do teraz pustej funkcji `loop`.

    ```cpp
    int light = analogRead(WIO_LIGHT);
    Serial.print("Light value: ");
    Serial.println(light);
    ```

    Ten kod odczytuje wartość analogową z pinu `WIO_LIGHT`. Odczytuje wartość od 0 do 1 023 z wbudowanego czujnika światła. Ta wartość jest następnie wysyłana do portu szeregowego, dzięki czemu możesz ją odczytać w Serial Monitor, gdy ten kod działa. `Serial.print` zapisuje tekst bez nowej linii na końcu, więc każda linia zacznie się od `Light value:` i zakończy rzeczywistą wartością światła.

1. Dodaj małe opóźnienie jednej sekundy (1 000 ms) na końcu `loop`, ponieważ poziomy światła nie muszą być sprawdzane ciągle. Opóźnienie zmniejsza zużycie energii przez urządzenie.

    ```cpp
    delay(1000);
    ```

1. Podłącz ponownie Wio Terminal do komputera i wgraj nowy kod, tak jak wcześniej.

1. Połącz się z Serial Monitor. Wartości światła będą wyświetlane w terminalu. Zakrywaj i odkrywaj czujnik światła z tyłu Wio Terminal, a wartości będą się zmieniać.

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

> 💁 Ten kod znajdziesz w folderze [code-sensor/wio-terminal](../../../../../1-getting-started/lessons/3-sensors-and-actuators/code-sensor/wio-terminal).

😀 Dodanie czujnika do programu nightlight zakończyło się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić precyzję, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.