# Wirtualny komputer jednopłytkowy

Zamiast kupować urządzenie IoT wraz z czujnikami i elementami wykonawczymi, możesz użyć swojego komputera do symulacji sprzętu IoT. Projekt [CounterFit](https://github.com/CounterFit-IoT/CounterFit) pozwala uruchomić aplikację lokalnie, która symuluje sprzęt IoT, taki jak czujniki i elementy wykonawcze, oraz uzyskać do nich dostęp za pomocą lokalnego kodu Python, napisanego w taki sam sposób, jak kod, który napisałbyś na Raspberry Pi, używając fizycznego sprzętu.

## Konfiguracja

Aby korzystać z CounterFit, musisz zainstalować na swoim komputerze kilka darmowych programów.

### Zadanie

Zainstaluj wymagane oprogramowanie.

1. Zainstaluj Pythona. Odwiedź [stronę pobierania Pythona](https://www.python.org/downloads/), aby uzyskać instrukcje dotyczące instalacji najnowszej wersji Pythona.

1. Zainstaluj Visual Studio Code (VS Code). To edytor, którego będziesz używać do pisania kodu dla wirtualnego urządzenia w Pythonie. Odwiedź [dokumentację VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn), aby uzyskać instrukcje dotyczące instalacji VS Code.

    > 💁 Możesz używać dowolnego IDE lub edytora dla Pythona, jeśli masz preferowane narzędzie, ale instrukcje w lekcjach będą oparte na używaniu VS Code.

1. Zainstaluj rozszerzenie Pylance dla VS Code. Jest to rozszerzenie, które zapewnia wsparcie dla języka Python. Odwiedź [dokumentację rozszerzenia Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance), aby uzyskać instrukcje dotyczące instalacji tego rozszerzenia w VS Code.

Instrukcje dotyczące instalacji i konfiguracji aplikacji CounterFit zostaną podane w odpowiednim momencie w ramach instrukcji zadania, ponieważ aplikacja jest instalowana indywidualnie dla każdego projektu.

## Hello World

Tradycyjnie, zaczynając pracę z nowym językiem programowania lub technologią, tworzy się aplikację 'Hello World' – małą aplikację, która wyświetla tekst, np. `"Hello World"`, aby upewnić się, że wszystkie narzędzia są poprawnie skonfigurowane.

Aplikacja Hello World dla wirtualnego sprzętu IoT pozwoli upewnić się, że Python i Visual Studio Code są poprawnie zainstalowane. Połączy się również z CounterFit, aby obsługiwać wirtualne czujniki i elementy wykonawcze IoT. Nie będzie używać żadnego sprzętu – po prostu połączy się, aby potwierdzić, że wszystko działa.

Ta aplikacja znajdzie się w folderze o nazwie `nightlight` i będzie ponownie używana z różnym kodem w późniejszych częściach tego zadania, aby zbudować aplikację lampki nocnej.

### Konfiguracja wirtualnego środowiska Pythona

Jedną z potężnych funkcji Pythona jest możliwość instalowania [pakietów Pip](https://pypi.org) – są to pakiety kodu napisane przez innych i opublikowane w Internecie. Możesz zainstalować pakiet Pip na swoim komputerze za pomocą jednego polecenia, a następnie używać go w swoim kodzie. W tym zadaniu użyjesz Pip do zainstalowania pakietu umożliwiającego komunikację z CounterFit.

Domyślnie, gdy instalujesz pakiet, jest on dostępny wszędzie na twoim komputerze, co może prowadzić do problemów z wersjami pakietów – na przykład jedna aplikacja może wymagać jednej wersji pakietu, która przestaje działać po zainstalowaniu nowej wersji dla innej aplikacji. Aby rozwiązać ten problem, możesz użyć [wirtualnego środowiska Pythona](https://docs.python.org/3/library/venv.html), czyli kopii Pythona w dedykowanym folderze. W takim środowisku pakiety Pip są instalowane tylko w tym folderze.

> 💁 Jeśli używasz Raspberry Pi, nie konfigurowałeś wirtualnego środowiska na tym urządzeniu do zarządzania pakietami Pip. Zamiast tego używasz pakietów globalnych, ponieważ pakiety Grove są instalowane globalnie przez skrypt instalacyjny.

#### Zadanie – konfiguracja wirtualnego środowiska Pythona

Skonfiguruj wirtualne środowisko Pythona i zainstaluj pakiety Pip dla CounterFit.

1. W terminalu lub wierszu poleceń uruchom następujące polecenia w wybranej lokalizacji, aby utworzyć i przejść do nowego katalogu:

    ```sh
    mkdir nightlight
    cd nightlight
    ```

1. Następnie uruchom następujące polecenie, aby utworzyć wirtualne środowisko w folderze `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Musisz wyraźnie wywołać `python3`, aby utworzyć wirtualne środowisko, na wypadek gdybyś miał zainstalowanego Pythona 2 obok Pythona 3 (najnowszej wersji). Jeśli masz zainstalowanego Pythona 2, wywołanie `python` użyje Pythona 2 zamiast Pythona 3.

1. Aktywuj wirtualne środowisko:

    * Na Windowsie:
        * Jeśli używasz Wiersza Poleceń lub Wiersza Poleceń w Windows Terminal, uruchom:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jeśli używasz PowerShell, uruchom:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

            > Jeśli pojawi się błąd dotyczący wyłączonego uruchamiania skryptów w tym systemie, musisz włączyć uruchamianie skryptów, ustawiając odpowiednią politykę wykonywania. Możesz to zrobić, uruchamiając PowerShell jako administrator, a następnie wykonując następujące polecenie:

            ```powershell
            Set-ExecutionPolicy -ExecutionPolicy Unrestricted
            ```

            Wpisz `Y`, aby potwierdzić. Następnie ponownie uruchom PowerShell i spróbuj ponownie.

            Możesz później przywrócić tę politykę wykonywania, jeśli zajdzie taka potrzeba. Więcej informacji znajdziesz na stronie [Execution Policies w dokumentacji Microsoft](https://docs.microsoft.com/powershell/module/microsoft.powershell.core/about/about_execution_policies?WT.mc_id=academic-17441-jabenn).

    * Na macOS lub Linux uruchom:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Te polecenia powinny być uruchamiane z tej samej lokalizacji, w której uruchomiłeś polecenie tworzące wirtualne środowisko. Nigdy nie musisz wchodzić do folderu `.venv`, zawsze uruchamiaj polecenie aktywacji i inne polecenia instalacji pakietów lub uruchamiania kodu z folderu, w którym utworzyłeś wirtualne środowisko.

1. Po aktywacji wirtualnego środowiska domyślne polecenie `python` uruchomi wersję Pythona, która została użyta do utworzenia środowiska. Uruchom następujące polecenie, aby sprawdzić wersję:

    ```sh
    python --version
    ```

    Wynik powinien zawierać:

    ```output
    (.venv) ➜  nightlight python --version
    Python 3.9.1
    ```

    > 💁 Twoja wersja Pythona może być inna – o ile jest to wersja 3.6 lub nowsza, wszystko jest w porządku. Jeśli nie, usuń ten folder, zainstaluj nowszą wersję Pythona i spróbuj ponownie.

1. Uruchom następujące polecenia, aby zainstalować pakiety Pip dla CounterFit. Pakiety te obejmują główną aplikację CounterFit oraz shimy dla sprzętu Grove. Shimy te pozwalają pisać kod tak, jakbyś programował z użyciem fizycznych czujników i elementów wykonawczych z ekosystemu Grove, ale podłączonych do wirtualnych urządzeń IoT.

    ```sh
    pip install CounterFit
    pip install counterfit-connection
    pip install counterfit-shims-grove
    ```

    Te pakiety Pip zostaną zainstalowane tylko w wirtualnym środowisku i nie będą dostępne poza nim.

### Napisz kod

Gdy wirtualne środowisko Pythona jest gotowe, możesz napisać kod dla aplikacji 'Hello World'.

#### Zadanie – napisz kod

Utwórz aplikację w Pythonie, która wypisze `"Hello World"` w konsoli.

1. W terminalu lub wierszu poleceń, będąc w wirtualnym środowisku, uruchom następujące polecenie, aby utworzyć plik Pythona o nazwie `app.py`:

    * Na Windowsie uruchom:

        ```cmd
        type nul > app.py
        ```

    * Na macOS lub Linux uruchom:

        ```cmd
        touch app.py
        ```

1. Otwórz bieżący folder w VS Code:

    ```sh
    code .
    ```

    > 💁 Jeśli twój terminal zwraca `command not found` na macOS, oznacza to, że VS Code nie został dodany do PATH. Możesz dodać VS Code do PATH, postępując zgodnie z instrukcjami w sekcji [Launching from the command line w dokumentacji VS Code](https://code.visualstudio.com/docs/setup/mac?WT.mc_id=academic-17441-jabenn#_launching-from-the-command-line) i uruchomić polecenie ponownie. VS Code jest domyślnie dodawany do PATH na Windowsie i Linuxie.

1. Po uruchomieniu VS Code aktywuje ono wirtualne środowisko Pythona. Wybrane środowisko pojawi się na dolnym pasku stanu:

    ![VS Code pokazujący wybrane wirtualne środowisko](../../../../../translated_images/pl/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Jeśli terminal VS Code jest już uruchomiony podczas startu VS Code, wirtualne środowisko nie będzie w nim aktywne. Najłatwiej jest zamknąć terminal, używając przycisku **Kill the active terminal instance**:

    ![VS Code przycisk Kill the active terminal instance](../../../../../translated_images/pl/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

    Możesz sprawdzić, czy terminal ma aktywne wirtualne środowisko, ponieważ nazwa środowiska będzie prefiksem w terminalu. Na przykład może to być:

    ```sh
    (.venv) ➜  nightlight
    ```

    Jeśli nie widzisz `.venv` jako prefiksu w terminalu, wirtualne środowisko nie jest aktywne.

1. Uruchom nowy terminal w VS Code, wybierając *Terminal -> New Terminal* lub naciskając `` CTRL+` ``. Nowy terminal załaduje wirtualne środowisko, a wywołanie aktywacji pojawi się w terminalu. W terminalu pojawi się również prefiks z nazwą środowiska (`.venv`):

    ```output
    ➜  nightlight source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Otwórz plik `app.py` w eksploratorze VS Code i dodaj następujący kod:

    ```python
    print('Hello World!')
    ```

    Funkcja `print` wypisuje w konsoli to, co zostanie do niej przekazane.

1. W terminalu VS Code uruchom następujące polecenie, aby uruchomić aplikację w Pythonie:

    ```sh
    python app.py
    ```

    W konsoli pojawi się:

    ```output
    (.venv) ➜  nightlight python app.py 
    Hello World!
    ```

😀 Twój program 'Hello World' działa poprawnie!

### Podłącz 'sprzęt'

Jako drugi krok 'Hello World', uruchomisz aplikację CounterFit i połączysz z nią swój kod. Jest to wirtualny odpowiednik podłączenia sprzętu IoT do zestawu deweloperskiego.

#### Zadanie – podłącz 'sprzęt'

1. W terminalu VS Code uruchom aplikację CounterFit za pomocą następującego polecenia:

    ```sh
    counterfit
    ```

    Aplikacja zacznie działać i otworzy się w przeglądarce internetowej:

    ![Aplikacja CounterFit uruchomiona w przeglądarce](../../../../../translated_images/pl/counterfit-first-run.433326358b669b31.webp)

    Będzie oznaczona jako *Disconnected*, a dioda LED w prawym górnym rogu będzie wyłączona.

1. Dodaj następujący kod na początku pliku `app.py`:

    ```python
    from counterfit_connection import CounterFitConnection
    CounterFitConnection.init('127.0.0.1', 5000)
    ```

    Kod ten importuje klasę `CounterFitConnection` z modułu `counterfit_connection`, który pochodzi z pakietu Pip `counterfit-connection`, zainstalowanego wcześniej. Następnie inicjalizuje połączenie z aplikacją CounterFit działającą na `127.0.0.1`, co jest adresem IP używanym do dostępu do lokalnego komputera (często nazywanego *localhost*), na porcie 5000.

    > 💁 Jeśli inne aplikacje działają na porcie 5000, możesz to zmienić, aktualizując port w kodzie i uruchamiając CounterFit za pomocą `CounterFit --port <port_number>`, zastępując `<port_number>` wybranym portem.

1. Będziesz musiał uruchomić nowy terminal w VS Code, wybierając przycisk **Create a new integrated terminal**. Jest to konieczne, ponieważ aplikacja CounterFit działa w bieżącym terminalu.

    ![VS Code przycisk Create a new integrated terminal](../../../../../translated_images/pl/vscode-new-terminal.77db8fc0f9cd3182.webp)

1. W nowym terminalu uruchom plik `app.py` tak jak wcześniej. Status CounterFit zmieni się na **Connected**, a dioda LED zaświeci się.

    ![CounterFit pokazujący status Connected](../../../../../translated_images/pl/counterfit-connected.ed30b46d8f79b092.webp)

> 💁 Kod ten znajdziesz w folderze [code/virtual-device](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/virtual-device).

😀 Połączenie ze sprzętem zakończyło się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.