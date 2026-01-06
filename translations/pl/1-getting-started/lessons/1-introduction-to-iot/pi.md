<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "8ff0d0a1d29832bb896b9c103b69a452",
  "translation_date": "2025-08-26T07:08:01+00:00",
  "source_file": "1-getting-started/lessons/1-introduction-to-iot/pi.md",
  "language_code": "pl"
}
-->
# Raspberry Pi

[Raspberry Pi](https://raspberrypi.org) to komputer jednopłytkowy. Możesz dodawać czujniki i siłowniki, korzystając z szerokiej gamy urządzeń i ekosystemów. W tych lekcjach będziesz używać ekosystemu sprzętowego o nazwie [Grove](https://www.seeedstudio.com/category/Grove-c-1003.html). Kodowanie na Raspberry Pi oraz dostęp do czujników Grove odbywa się za pomocą języka Python.

![Raspberry Pi 4](../../../../../translated_images/raspberry-pi-4.fd4590d308c3d456.pl.jpg)

## Konfiguracja

Jeśli używasz Raspberry Pi jako swojego sprzętu IoT, masz dwie opcje – możesz przejść przez wszystkie lekcje i pisać kod bezpośrednio na Pi, lub możesz połączyć się zdalnie z Pi w trybie "headless" i pisać kod na swoim komputerze.

Przed rozpoczęciem musisz również podłączyć Grove Base Hat do swojego Pi.

### Zadanie - konfiguracja

Zainstaluj Grove Base Hat na swoim Pi i skonfiguruj Pi.

1. Podłącz Grove Base Hat do swojego Pi. Gniazdo na hat pasuje do wszystkich pinów GPIO na Pi, wsuwając się na nie aż do podstawy. Hat zakrywa Pi.

    ![Zakładanie Grove Hat](../../../../../images/pi-grove-hat-fitting.gif)

1. Zdecyduj, w jaki sposób chcesz programować swoje Pi, i przejdź do odpowiedniej sekcji poniżej:

    * [Praca bezpośrednio na Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)
    * [Zdalny dostęp do kodowania na Pi](../../../../../1-getting-started/lessons/1-introduction-to-iot)

### Praca bezpośrednio na Pi

Jeśli chcesz pracować bezpośrednio na swoim Pi, możesz użyć wersji desktopowej Raspberry Pi OS i zainstalować wszystkie potrzebne narzędzia.

#### Zadanie - praca bezpośrednio na Pi

Skonfiguruj swoje Pi do programowania.

1. Postępuj zgodnie z instrukcjami w [przewodniku konfiguracji Raspberry Pi](https://projects.raspberrypi.org/en/projects/raspberry-pi-setting-up), aby skonfigurować swoje Pi, podłączyć je do klawiatury/myszy/monitora, połączyć z siecią WiFi lub Ethernet i zaktualizować oprogramowanie.

Aby programować Pi za pomocą czujników i siłowników Grove, musisz zainstalować edytor do pisania kodu urządzenia oraz różne biblioteki i narzędzia do interakcji ze sprzętem Grove.

1. Po ponownym uruchomieniu Pi uruchom Terminal, klikając ikonę **Terminal** na górnym pasku menu lub wybierz *Menu -> Accessories -> Terminal*.

1. Wykonaj następujące polecenie, aby upewnić się, że system operacyjny i zainstalowane oprogramowanie są aktualne:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes
    ```

1. Wykonaj następujące polecenia, aby zainstalować wszystkie potrzebne biblioteki dla sprzętu Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    To rozpoczyna instalację Git oraz Pip do instalacji pakietów Pythona.

    Jedną z potężnych funkcji Pythona jest możliwość instalacji [pakietów Pip](https://pypi.org) – są to pakiety kodu napisane przez innych ludzi i opublikowane w Internecie. Możesz zainstalować pakiet Pip na swoim komputerze jednym poleceniem, a następnie używać go w swoim kodzie.

    Pakiety Python Grove od Seeed muszą być zainstalowane ze źródła. Te polecenia sklonują repozytorium zawierające kod źródłowy tego pakietu, a następnie zainstalują go lokalnie.

    > 💁 Domyślnie, gdy instalujesz pakiet, jest on dostępny wszędzie na twoim komputerze, co może prowadzić do problemów z wersjami pakietów – na przykład jedna aplikacja może zależeć od jednej wersji pakietu, która przestaje działać po zainstalowaniu nowej wersji dla innej aplikacji. Aby rozwiązać ten problem, możesz użyć [wirtualnego środowiska Pythona](https://docs.python.org/3/library/venv.html), czyli kopii Pythona w dedykowanym folderze, a instalowane pakiety Pip są dostępne tylko w tym folderze. Nie będziesz używać wirtualnych środowisk na swoim Pi. Skrypt instalacyjny Grove instaluje pakiety Python Grove globalnie, więc aby użyć wirtualnego środowiska, musiałbyś je skonfigurować, a następnie ręcznie ponownie zainstalować pakiety Grove w tym środowisku. Łatwiej jest po prostu używać pakietów globalnych, zwłaszcza że wielu deweloperów Pi ponownie flashuje czystą kartę SD dla każdego projektu.

    Na koniec to polecenie włącza interfejs I<sup>2</sup>C.

1. Uruchom ponownie Pi, używając menu lub wykonując następujące polecenie w Terminalu:

    ```sh
    sudo reboot
    ```

1. Po ponownym uruchomieniu Pi, ponownie uruchom Terminal i wykonaj następujące polecenie, aby zainstalować [Visual Studio Code (VS Code)](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn) – to edytor, którego będziesz używać do pisania kodu urządzenia w Pythonie.

    ```sh
    sudo apt install code
    ```

    Po zainstalowaniu VS Code będzie dostępny z górnego menu.

    > 💁 Możesz używać dowolnego IDE lub edytora Pythona, jeśli masz preferowane narzędzie, ale lekcje będą zawierały instrukcje oparte na używaniu VS Code.

1. Zainstaluj Pylance. Jest to rozszerzenie dla VS Code, które zapewnia wsparcie dla języka Python. Zapoznaj się z [dokumentacją rozszerzenia Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance), aby uzyskać instrukcje dotyczące instalacji tego rozszerzenia w VS Code.

### Zdalny dostęp do kodowania na Pi

Zamiast kodować bezpośrednio na Pi, możesz uruchomić je w trybie "headless", czyli bez podłączonej klawiatury/myszy/monitora, i konfigurować oraz pisać kod na nim z poziomu swojego komputera, używając Visual Studio Code.

#### Konfiguracja systemu Pi OS

Aby kodować zdalnie, system Pi OS musi być zainstalowany na karcie SD.

##### Zadanie - konfiguracja systemu Pi OS

Skonfiguruj system Pi OS w trybie headless.

1. Pobierz **Raspberry Pi Imager** ze [strony oprogramowania Raspberry Pi OS](https://www.raspberrypi.org/software/) i zainstaluj go.

1. Włóż kartę SD do swojego komputera, używając adaptera, jeśli to konieczne.

1. Uruchom Raspberry Pi Imager.

1. W Raspberry Pi Imager wybierz przycisk **CHOOSE OS**, a następnie wybierz *Raspberry Pi OS (Other)*, a potem *Raspberry Pi OS Lite (32-bit)*.

    ![Raspberry Pi Imager z wybranym Raspberry Pi OS Lite](../../../../../translated_images/raspberry-pi-imager.24aedeab9e233d84.pl.png)

    > 💁 Raspberry Pi OS Lite to wersja Raspberry Pi OS bez interfejsu graficznego i narzędzi opartych na UI. Nie są one potrzebne dla Pi w trybie headless, co sprawia, że instalacja jest mniejsza, a czas uruchamiania szybszy.

1. Wybierz przycisk **CHOOSE STORAGE**, a następnie wybierz swoją kartę SD.

1. Uruchom **Advanced Options**, naciskając `Ctrl+Shift+X`. Te opcje pozwalają na wstępną konfigurację Raspberry Pi OS przed zapisaniem go na karcie SD.

    1. Zaznacz pole **Enable SSH** i ustaw hasło dla użytkownika `pi`. To hasło będzie używane do logowania się na Pi później.

    1. Jeśli planujesz połączyć się z Pi przez WiFi, zaznacz pole **Configure WiFi** i wprowadź swoją nazwę sieci WiFi (SSID) oraz hasło, a także wybierz swój kraj WiFi. Nie musisz tego robić, jeśli będziesz używać kabla Ethernet. Upewnij się, że sieć, do której się łączysz, jest tą samą, na której znajduje się twój komputer.

    1. Zaznacz pole **Set locale settings** i ustaw swój kraj oraz strefę czasową.

    1. Wybierz przycisk **SAVE**.

1. Wybierz przycisk **WRITE**, aby zapisać system operacyjny na karcie SD. Jeśli używasz macOS, zostaniesz poproszony o podanie hasła, ponieważ narzędzie zapisujące obrazy dysków wymaga uprawnień administratora.

System operacyjny zostanie zapisany na karcie SD, a po zakończeniu karta zostanie wysunięta przez system operacyjny, a ty zostaniesz o tym powiadomiony. Wyjmij kartę SD z komputera, włóż ją do Pi, włącz Pi i poczekaj około 2 minut, aż się poprawnie uruchomi.

#### Połączenie z Pi

Następnym krokiem jest zdalny dostęp do Pi. Możesz to zrobić za pomocą `ssh`, które jest dostępne na macOS, Linux i nowszych wersjach Windows.

##### Zadanie - połączenie z Pi

Uzyskaj zdalny dostęp do Pi.

1. Uruchom Terminal lub Wiersz Poleceń i wprowadź następujące polecenie, aby połączyć się z Pi:

    ```sh
    ssh pi@raspberrypi.local
    ```

    Jeśli używasz starszej wersji Windows, która nie ma zainstalowanego `ssh`, możesz użyć OpenSSH. Instrukcje instalacji znajdziesz w [dokumentacji instalacji OpenSSH](https://docs.microsoft.com//windows-server/administration/openssh/openssh_install_firstuse?WT.mc_id=academic-17441-jabenn).

1. Powinno to połączyć cię z Pi i poprosić o hasło.

    Możliwość znajdowania komputerów w sieci za pomocą `<hostname>.local` to stosunkowo nowa funkcja w Linux i Windows. Jeśli używasz Linux lub Windows i pojawią się błędy dotyczące nieznalezienia nazwy hosta, będziesz musiał zainstalować dodatkowe oprogramowanie, aby włączyć sieć ZeroConf (określaną przez Apple jako Bonjour):

    1. Jeśli używasz Linux, zainstaluj Avahi, wykonując następujące polecenie:

        ```sh
        sudo apt-get install avahi-daemon
        ```

    1. Jeśli używasz Windows, najprostszym sposobem na włączenie ZeroConf jest zainstalowanie [Bonjour Print Services for Windows](http://support.apple.com/kb/DL999). Możesz również zainstalować [iTunes dla Windows](https://www.apple.com/itunes/download/), aby uzyskać nowszą wersję narzędzia (które nie jest dostępne samodzielnie).

    > 💁 Jeśli nie możesz połączyć się za pomocą `raspberrypi.local`, możesz użyć adresu IP swojego Pi. Zapoznaj się z [dokumentacją adresu IP Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ip-address.md), aby uzyskać instrukcje dotyczące różnych sposobów uzyskania adresu IP.

1. Wprowadź hasło, które ustawiłeś w zaawansowanych opcjach Raspberry Pi Imager.

#### Konfiguracja oprogramowania na Pi

Po połączeniu z Pi musisz upewnić się, że system operacyjny jest aktualny, oraz zainstalować różne biblioteki i narzędzia do interakcji ze sprzętem Grove.

##### Zadanie - konfiguracja oprogramowania na Pi

Skonfiguruj zainstalowane oprogramowanie Pi i zainstaluj biblioteki Grove.

1. W swojej sesji `ssh` wykonaj następujące polecenie, aby zaktualizować system, a następnie uruchomić Pi ponownie:

    ```sh
    sudo apt update && sudo apt full-upgrade --yes && sudo reboot
    ```

    Pi zostanie zaktualizowane i uruchomione ponownie. Sesja `ssh` zakończy się, gdy Pi zostanie uruchomione ponownie, więc odczekaj około 30 sekund, a następnie połącz się ponownie.

1. W ponownie połączonej sesji `ssh` wykonaj następujące polecenia, aby zainstalować wszystkie potrzebne biblioteki dla sprzętu Grove:

    ```sh
    sudo apt install git python3-dev python3-pip --yes

    git clone https://github.com/Seeed-Studio/grove.py
    cd grove.py
    sudo pip3 install .

    sudo raspi-config nonint do_i2c 0
    ```

    To rozpoczyna instalację Git oraz Pip do instalacji pakietów Pythona.

    Jedną z potężnych funkcji Pythona jest możliwość instalacji [pakietów Pip](https://pypi.org) – są to pakiety kodu napisane przez innych ludzi i opublikowane w Internecie. Możesz zainstalować pakiet Pip na swoim komputerze jednym poleceniem, a następnie używać go w swoim kodzie.

    Pakiety Python Grove od Seeed muszą być zainstalowane ze źródła. Te polecenia sklonują repozytorium zawierające kod źródłowy tego pakietu, a następnie zainstalują go lokalnie.

    > 💁 Domyślnie, gdy instalujesz pakiet, jest on dostępny wszędzie na twoim komputerze, co może prowadzić do problemów z wersjami pakietów – na przykład jedna aplikacja może zależeć od jednej wersji pakietu, która przestaje działać po zainstalowaniu nowej wersji dla innej aplikacji. Aby rozwiązać ten problem, możesz użyć [wirtualnego środowiska Pythona](https://docs.python.org/3/library/venv.html), czyli kopii Pythona w dedykowanym folderze, a instalowane pakiety Pip są dostępne tylko w tym folderze. Nie będziesz używać wirtualnych środowisk na swoim Pi. Skrypt instalacyjny Grove instaluje pakiety Python Grove globalnie, więc aby użyć wirtualnego środowiska, musiałbyś je skonfigurować, a następnie ręcznie ponownie zainstalować pakiety Grove w tym środowisku. Łatwiej jest po prostu używać pakietów globalnych, zwłaszcza że wielu deweloperów Pi ponownie flashuje czystą kartę SD dla każdego projektu.

    Na koniec to polecenie włącza interfejs I<sup>2</sup>C.

1. Uruchom ponownie Pi, wykonując następujące polecenie:

    ```sh
    sudo reboot
    ```

    Sesja `ssh` zakończy się, gdy Pi zostanie uruchomione ponownie. Nie ma potrzeby ponownego łączenia się.

#### Konfiguracja VS Code do zdalnego dostępu

Po skonfigurowaniu Pi możesz połączyć się z nim za pomocą Visual Studio Code (VS Code) z poziomu swojego komputera – jest to darmowy edytor tekstu dla programistów, którego będziesz używać do pisania kodu urządzenia w Pythonie.

##### Zadanie - konfiguracja VS Code do zdalnego dostępu

Zainstaluj wymagane oprogramowanie i połącz się zdalnie z Pi.

1. Zainstaluj VS Code na swoim komputerze, postępując zgodnie z [dokumentacją VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

1. Postępuj zgodnie z instrukcjami w [dokumentacji zdalnego programowania w VS Code za pomocą SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), aby zainstalować potrzebne komponenty.

1. Postępując zgodnie z tymi samymi instrukcjami, połącz VS Code z Pi.

1. Po połączeniu postępuj zgodnie z instrukcjami dotyczącymi [zarządzania rozszerzeniami](https://code.visualstudio.com/docs/remote/ssh#_managing-extensions?WT.mc_id=academic-17441-jabenn), aby zainstalować zdalnie na Pi rozszerzenie [Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance).

## Hello world
Tradycyjnie, gdy zaczynamy pracę z nowym językiem programowania lub technologią, tworzymy aplikację 'Hello World' – małą aplikację, która wyświetla tekst, np. `"Hello World"`, aby upewnić się, że wszystkie narzędzia są poprawnie skonfigurowane.

Aplikacja Hello World dla Raspberry Pi pozwoli Ci upewnić się, że Python i Visual Studio Code są poprawnie zainstalowane.

Ta aplikacja znajdzie się w folderze o nazwie `nightlight` i będzie ponownie wykorzystywana z różnym kodem w dalszych częściach tego zadania, aby stworzyć aplikację nightlight.

### Zadanie - hello world

Stwórz aplikację Hello World.

1. Uruchom VS Code, bezpośrednio na Raspberry Pi lub na swoim komputerze, łącząc się z Pi za pomocą rozszerzenia Remote SSH.

1. Otwórz terminal w VS Code, wybierając *Terminal -> New Terminal* lub naciskając `` CTRL+` ``. Terminal otworzy się w katalogu domowym użytkownika `pi`.

1. Wykonaj poniższe polecenia, aby utworzyć katalog na swój kod i plik Python o nazwie `app.py` w tym katalogu:

    ```sh
    mkdir nightlight
    cd nightlight
    touch app.py
    ```

1. Otwórz ten folder w VS Code, wybierając *File -> Open...* i wskazując folder *nightlight*, a następnie wybierz **OK**.

    ![Okno dialogowe otwierania w VS Code pokazujące folder nightlight](../../../../../translated_images/vscode-open-nightlight-remote.d3d2a4011e30d535.pl.png)

1. Otwórz plik `app.py` w eksploratorze VS Code i dodaj poniższy kod:

    ```python
    print('Hello World!')
    ```

    Funkcja `print` wypisuje na konsolę wszystko, co zostanie do niej przekazane.

1. W terminalu VS Code uruchom poniższe polecenie, aby uruchomić swoją aplikację w Pythonie:

    ```sh
    python app.py
    ```

    > 💁 Może być konieczne wyraźne użycie `python3`, aby uruchomić ten kod, jeśli masz zainstalowanego Pythona 2 obok Pythona 3 (najnowszej wersji). Jeśli Python 2 jest zainstalowany, wywołanie `python` uruchomi Pythona 2 zamiast Pythona 3. Domyślnie najnowsze wersje Raspberry Pi OS mają zainstalowanego tylko Pythona 3.

    W terminalu pojawi się następujący wynik:

    ```output
    pi@raspberrypi:~/nightlight $ python3 app.py
    Hello World!
    ```

> 💁 Ten kod znajdziesz w folderze [code/pi](../../../../../1-getting-started/lessons/1-introduction-to-iot/code/pi).

😀 Twój program 'Hello World' zakończył się sukcesem!

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.