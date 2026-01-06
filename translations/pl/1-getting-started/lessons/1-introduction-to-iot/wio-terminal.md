<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "a4f0c166010e31fd7b6ca20bc88dec6d",
  "translation_date": "2025-08-26T07:09:06+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/wio-terminal.md",
  "language_code": "pl"
}
-->
# Wio Terminal

[Wio Terminal od Seeed Studios](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) to mikrokontroler kompatybilny z Arduino, wyposażony w WiFi, kilka wbudowanych czujników i elementów wykonawczych, a także porty umożliwiające dodanie kolejnych czujników i elementów wykonawczych za pomocą ekosystemu sprzętowego o nazwie [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html).

![Wio Terminal od Seeed Studios](../../../../../translated_images/wio-terminal.b8299ee16587db9a.pl.png)

## Konfiguracja

Aby korzystać z Wio Terminal, musisz zainstalować na swoim komputerze darmowe oprogramowanie. Przed połączeniem urządzenia z WiFi konieczna będzie również aktualizacja oprogramowania układowego Wio Terminal.

### Zadanie - konfiguracja

Zainstaluj wymagane oprogramowanie i zaktualizuj firmware.

1. Zainstaluj Visual Studio Code (VS Code). To edytor, którego będziesz używać do pisania kodu urządzenia w językach C/C++. Zapoznaj się z [dokumentacją VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn), aby uzyskać instrukcje dotyczące instalacji.

    > 💁 Innym popularnym środowiskiem IDE do programowania Arduino jest [Arduino IDE](https://www.arduino.cc/en/software). Jeśli już znasz to narzędzie, możesz go używać zamiast VS Code i PlatformIO, ale lekcje będą oparte na instrukcjach dla VS Code.

1. Zainstaluj rozszerzenie PlatformIO dla VS Code. To rozszerzenie wspiera programowanie mikrokontrolerów w językach C/C++. Zapoznaj się z [dokumentacją rozszerzenia PlatformIO](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=platformio.platformio-ide), aby dowiedzieć się, jak je zainstalować w VS Code. Rozszerzenie to wymaga rozszerzenia Microsoft C/C++, które zostanie automatycznie zainstalowane wraz z PlatformIO.

1. Podłącz Wio Terminal do komputera. Wio Terminal posiada port USB-C na spodzie, który należy podłączyć do portu USB w komputerze. W zestawie znajduje się kabel USB-C do USB-A, ale jeśli Twój komputer ma tylko porty USB-C, będziesz potrzebować kabla USB-C lub adaptera USB-A do USB-C.

1. Postępuj zgodnie z instrukcjami w [dokumentacji Wio Terminal Wiki WiFi Overview](https://wiki.seeedstudio.com/Wio-Terminal-Network-Overview/), aby skonfigurować Wio Terminal i zaktualizować firmware.

## Hello World

Tradycyjnie, zaczynając pracę z nowym językiem programowania lub technologią, tworzy się aplikację 'Hello World' – mały program, który wyświetla tekst, np. `"Hello World"`, aby upewnić się, że wszystkie narzędzia są poprawnie skonfigurowane.

Aplikacja Hello World dla Wio Terminal pozwoli upewnić się, że Visual Studio Code zostało poprawnie zainstalowane z PlatformIO i skonfigurowane do pracy z mikrokontrolerami.

### Utwórz projekt PlatformIO

Pierwszym krokiem jest utworzenie nowego projektu w PlatformIO skonfigurowanego dla Wio Terminal.

#### Zadanie - utwórz projekt PlatformIO

Utwórz projekt PlatformIO.

1. Podłącz Wio Terminal do komputera.

1. Uruchom VS Code.

1. Ikona PlatformIO będzie widoczna na pasku menu bocznego:

    ![Opcja menu PlatformIO](../../../../../translated_images/vscode-platformio-menu.297be26b9733e5c4.pl.png)

    Wybierz tę opcję, a następnie wybierz *PIO Home -> Open*.

    ![Opcja otwarcia PlatformIO](../../../../../translated_images/vscode-platformio-home-open.3f9a41bfd3f4da1c.pl.png)

1. Na ekranie powitalnym wybierz przycisk **+ New Project**.

    ![Przycisk nowego projektu](../../../../../translated_images/vscode-platformio-welcome-new-button.ba6fc8a4c7b78cc8.pl.png)

1. Skonfiguruj projekt w *Project Wizard*:

    1. Nazwij swój projekt `nightlight`.

    1. W polu *Board* wpisz `WIO`, aby przefiltrować listę, i wybierz *Seeeduino Wio Terminal*.

    1. Pozostaw *Framework* jako *Arduino*.

    1. Zaznacz pole *Use default location* lub odznacz je i wybierz lokalizację dla swojego projektu.

    1. Kliknij przycisk **Finish**.

    ![Ukończony kreator projektu](../../../../../translated_images/vscode-platformio-nightlight-project-wizard.5c64db4da6037420.pl.png)

    PlatformIO pobierze potrzebne komponenty do kompilacji kodu dla Wio Terminal i utworzy Twój projekt. Może to potrwać kilka minut.

### Zbadaj projekt PlatformIO

Eksplorator VS Code pokaże kilka plików i folderów utworzonych przez kreator PlatformIO.

#### Foldery

* `.pio` - ten folder zawiera dane tymczasowe potrzebne PlatformIO, takie jak biblioteki czy skompilowany kod. Jest automatycznie odtwarzany po usunięciu i nie musisz go dodawać do systemu kontroli wersji, jeśli udostępniasz projekt np. na GitHubie.
* `.vscode` - ten folder zawiera konfigurację używaną przez PlatformIO i VS Code. Jest automatycznie odtwarzany po usunięciu i nie musisz go dodawać do systemu kontroli wersji, jeśli udostępniasz projekt np. na GitHubie.
* `include` - ten folder jest przeznaczony na zewnętrzne pliki nagłówkowe potrzebne przy dodawaniu dodatkowych bibliotek do kodu. Nie będziesz używać tego folderu w tych lekcjach.
* `lib` - ten folder jest przeznaczony na zewnętrzne biblioteki, które chcesz wywoływać w swoim kodzie. Nie będziesz używać tego folderu w tych lekcjach.
* `src` - ten folder zawiera główny kod źródłowy Twojej aplikacji. Na początku będzie zawierał tylko jeden plik - `main.cpp`.
* `test` - ten folder jest przeznaczony na testy jednostkowe Twojego kodu.

#### Pliki

* `main.cpp` - ten plik w folderze `src` zawiera punkt wejścia Twojej aplikacji. Otwórz ten plik, a znajdziesz w nim następujący kod:

    ```cpp
    #include <Arduino.h>
    
    void setup() {
      // put your setup code here, to run once:
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    }
    ```

    Po uruchomieniu urządzenia framework Arduino uruchomi funkcję `setup` raz, a następnie będzie wielokrotnie wykonywać funkcję `loop`, dopóki urządzenie nie zostanie wyłączone.

* `.gitignore` - ten plik zawiera listę plików i katalogów, które mają być ignorowane podczas dodawania kodu do systemu kontroli wersji git, np. podczas przesyłania na repozytorium GitHub.

* `platformio.ini` - ten plik zawiera konfigurację dla Twojego urządzenia i aplikacji. Otwórz ten plik, a znajdziesz w nim następujący kod:

    ```ini
    [env:seeed_wio_terminal]
    platform = atmelsam
    board = seeed_wio_terminal
    framework = arduino
    ```

    Sekcja `[env:seeed_wio_terminal]` zawiera konfigurację dla Wio Terminal. Możesz mieć wiele sekcji `env`, aby Twój kod mógł być kompilowany dla różnych płytek.

    Pozostałe wartości odpowiadają konfiguracji z kreatora projektu:

  * `platform = atmelsam` definiuje sprzęt używany przez Wio Terminal (mikrokontroler oparty na ATSAMD51).
  * `board = seeed_wio_terminal` definiuje typ płytki mikrokontrolera (Wio Terminal).
  * `framework = arduino` definiuje, że projekt korzysta z frameworka Arduino.

### Napisz aplikację Hello World

Teraz jesteś gotowy, aby napisać aplikację Hello World.

#### Zadanie - napisz aplikację Hello World

Napisz aplikację Hello World.

1. Otwórz plik `main.cpp` w VS Code.

1. Zmień kod na następujący:

    ```cpp
    #include <Arduino.h>

    void setup()
    {
        Serial.begin(9600);

        while (!Serial)
            ; // Wait for Serial to be ready
    
        delay(1000);
    }
    
    void loop()
    {
        Serial.println("Hello World");
        delay(5000);
    }
    ```

    Funkcja `setup` inicjalizuje połączenie z portem szeregowym – w tym przypadku portem USB, który łączy Wio Terminal z komputerem. Parametr `9600` to [prędkość transmisji](https://wikipedia.org/wiki/Symbol_rate) (znana również jako Symbol rate), czyli szybkość przesyłania danych przez port szeregowy w bitach na sekundę. Ustawienie to oznacza, że przesyłane jest 9 600 bitów (0 i 1) danych na sekundę. Następnie funkcja czeka, aż port szeregowy będzie gotowy.

    Funkcja `loop` wysyła linię `Hello World!` do portu szeregowego, czyli znaki `Hello World!` wraz ze znakiem nowej linii. Następnie usypia na 5 000 milisekund, czyli 5 sekund. Po zakończeniu funkcji `loop` jest ona uruchamiana ponownie, i tak w kółko, dopóki mikrokontroler jest włączony.

1. Wprowadź Wio Terminal w tryb przesyłania. Będziesz musiał to robić za każdym razem, gdy przesyłasz nowy kod na urządzenie:

    1. Dwukrotnie szybko przesuń przełącznik zasilania w dół – za każdym razem wróci on do pozycji włączonej.

    1. Sprawdź niebieską diodę LED statusu po prawej stronie portu USB. Powinna pulsować.
    
    [![Film pokazujący, jak wprowadzić Wio Terminal w tryb przesyłania](https://img.youtube.com/vi/LeKU_7zLRrQ/0.jpg)](https://youtu.be/LeKU_7zLRrQ)
    
    Kliknij obrazek powyżej, aby obejrzeć film pokazujący, jak to zrobić.

1. Skompiluj i prześlij kod na Wio Terminal.

    1. Otwórz paletę poleceń VS Code.

    1. Wpisz `PlatformIO Upload`, aby wyszukać opcję przesyłania, i wybierz *PlatformIO: Upload*.

        ![Opcja przesyłania PlatformIO w palecie poleceń](../../../../../translated_images/vscode-platformio-upload-command-palette.9e0f49cf80d1f1c3.pl.png)

        PlatformIO automatycznie skompiluje kod, jeśli będzie to konieczne, przed przesłaniem.

    1. Kod zostanie skompilowany i przesłany na Wio Terminal.

        > 💁 Jeśli korzystasz z macOS, pojawi się powiadomienie o *DISK NOT EJECTED PROPERLY*. Dzieje się tak, ponieważ Wio Terminal jest montowany jako dysk w procesie flashowania, a następnie odłączany, gdy skompilowany kod jest zapisywany na urządzeniu. Możesz zignorować to powiadomienie.

    ⚠️ Jeśli pojawią się błędy dotyczące niedostępności portu przesyłania, upewnij się, że Wio Terminal jest podłączony do komputera, włączony za pomocą przełącznika po lewej stronie ekranu i ustawiony w tryb przesyłania. Zielona dioda na spodzie powinna być włączona, a niebieska dioda powinna pulsować. Jeśli nadal występuje błąd, ponownie dwukrotnie szybko przesuń przełącznik zasilania w dół, aby wymusić tryb przesyłania, i spróbuj ponownie.

PlatformIO posiada Monitor Szeregowy, który pozwala monitorować dane przesyłane przez kabel USB z Wio Terminal. Dzięki temu możesz obserwować dane wysyłane przez polecenie `Serial.println("Hello World");`.

1. Otwórz paletę poleceń VS Code.

1. Wpisz `PlatformIO Serial`, aby wyszukać opcję Monitora Szeregowego, i wybierz *PlatformIO: Serial Monitor*.

    ![Opcja Monitora Szeregowego PlatformIO w palecie poleceń](../../../../../translated_images/vscode-platformio-serial-monitor-command-palette.b348ec841b8a1c14.pl.png)

    Otworzy się nowe okno terminala, a dane przesyłane przez port szeregowy będą wyświetlane w tym terminalu:

    ```output
    > Executing task: platformio device monitor <
    
    --- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
    --- More details at http://bit.ly/pio-monitor-filters
    --- Miniterm on /dev/cu.usbmodem101  9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
    Hello World
    Hello World
    ```

    `Hello World` będzie wyświetlane w monitorze szeregowym co 5 sekund.

> 💁 Kod ten znajdziesz w folderze [code/wio-terminal](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/wio-terminal).

😀 Twój program 'Hello World' zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.