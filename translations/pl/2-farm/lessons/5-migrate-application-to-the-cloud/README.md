# Przenieś logikę swojej aplikacji do chmury

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-9.dfe99c8e891f48e1.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ta lekcja była częścią [Projektu IoT dla początkujących 2 - Cykl o cyfrowym rolnictwie](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) organizowanego przez [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Steruj swoim urządzeniem IoT za pomocą kodu bezserwerowego](https://img.youtube.com/vi/VVZDcs5u1_I/0.jpg)](https://youtu.be/VVZDcs5u1_I)

## Quiz przed lekcją

[Quiz przed lekcją](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/17)

## Wprowadzenie

W poprzedniej lekcji nauczyłeś się, jak połączyć monitorowanie wilgotności gleby i sterowanie przekaźnikiem z usługą IoT w chmurze. Kolejnym krokiem jest przeniesienie kodu serwera, który kontroluje czas działania przekaźnika, do chmury. W tej lekcji dowiesz się, jak to zrobić za pomocą funkcji bezserwerowych.

W tej lekcji omówimy:

* [Czym jest bezserwerowość?](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Tworzenie aplikacji bezserwerowej](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Tworzenie wyzwalacza zdarzeń IoT Hub](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Wysyłanie żądań metod bezpośrednich z kodu bezserwerowego](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)
* [Wdrażanie kodu bezserwerowego w chmurze](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud)

## Czym jest bezserwerowość?

Bezserwerowość, czyli przetwarzanie bezserwerowe, polega na tworzeniu małych bloków kodu, które są uruchamiane w chmurze w odpowiedzi na różne zdarzenia. Gdy zdarzenie wystąpi, Twój kod jest uruchamiany i otrzymuje dane dotyczące tego zdarzenia. Zdarzenia te mogą pochodzić z różnych źródeł, takich jak żądania sieciowe, wiadomości umieszczone w kolejce, zmiany danych w bazie danych czy wiadomości wysyłane do usługi IoT przez urządzenia IoT.

![Zdarzenia wysyłane z usługi IoT do usługi bezserwerowej, przetwarzane jednocześnie przez wiele funkcji](../../../../../translated_images/pl/iot-messages-to-serverless.0194da1cc0732bb7.webp)

> 💁 Jeśli wcześniej korzystałeś z wyzwalaczy w bazach danych, możesz to porównać do tego samego mechanizmu — kod jest uruchamiany w odpowiedzi na zdarzenie, takie jak wstawienie wiersza.

![Gdy wiele zdarzeń występuje jednocześnie, usługa bezserwerowa skaluje się, aby obsłużyć je wszystkie w tym samym czasie](../../../../../translated_images/pl/serverless-scaling.f8c769adf0413fd1.webp)

Twój kod jest uruchamiany tylko wtedy, gdy wystąpi zdarzenie, a w innych momentach nie jest aktywny. Zdarzenie występuje, Twój kod jest ładowany i uruchamiany. Dzięki temu bezserwerowość jest bardzo skalowalna — jeśli wiele zdarzeń wystąpi jednocześnie, dostawca chmury może uruchomić Twoją funkcję tyle razy, ile potrzeba, na dostępnych serwerach. Wadą tego podejścia jest to, że jeśli musisz udostępniać informacje między zdarzeniami, musisz je zapisać w miejscu takim jak baza danych, zamiast przechowywać je w pamięci.

Twój kod jest pisany jako funkcja, która przyjmuje szczegóły dotyczące zdarzenia jako parametr. Możesz używać szerokiej gamy języków programowania do pisania tych funkcji bezserwerowych.

> 🎓 Bezserwerowość jest również nazywana Funkcjami jako Usługa (FaaS), ponieważ każdy wyzwalacz zdarzenia jest implementowany jako funkcja w kodzie.

Pomimo nazwy, bezserwerowość faktycznie korzysta z serwerów. Nazwa pochodzi stąd, że jako programista nie musisz martwić się o serwery potrzebne do uruchomienia Twojego kodu — interesuje Cię tylko to, że Twój kod jest uruchamiany w odpowiedzi na zdarzenie. Dostawca chmury posiada środowisko uruchomieniowe bezserwerowe, które zarządza przydzielaniem serwerów, siecią, pamięcią masową, procesorem, pamięcią RAM i wszystkim innym potrzebnym do uruchomienia Twojego kodu. W tym modelu nie płacisz za serwer, ponieważ nie ma serwera. Zamiast tego płacisz za czas, w którym Twój kod jest uruchamiany, oraz za ilość użytej pamięci.

> 💰 Bezserwerowość to jeden z najtańszych sposobów uruchamiania kodu w chmurze. Na przykład, w momencie pisania tego tekstu, jeden z dostawców chmury pozwala na wykonanie wszystkich Twoich funkcji bezserwerowych łącznie 1 000 000 razy miesięcznie, zanim zacznie naliczać opłaty, a po tym nalicza 0,20 USD za każde 1 000 000 wykonanych funkcji. Gdy Twój kod nie działa, nie płacisz.

Jako programista IoT, model bezserwerowy jest idealny. Możesz napisać funkcję, która jest wywoływana w odpowiedzi na wiadomości wysyłane przez dowolne urządzenie IoT podłączone do Twojej usługi IoT hostowanej w chmurze. Twój kod obsłuży wszystkie wysłane wiadomości, ale będzie działał tylko wtedy, gdy będzie to potrzebne.

✅ Spójrz na kod, który napisałeś jako kod serwera nasłuchujący wiadomości przez MQTT. Jak mógłby on działać w chmurze, korzystając z bezserwerowości? Jak myślisz, jakie zmiany byłyby potrzebne, aby dostosować kod do przetwarzania bezserwerowego?

> 💁 Model bezserwerowy jest również wdrażany w innych usługach chmurowych, oprócz uruchamiania kodu. Na przykład, w chmurze dostępne są bazy danych bezserwerowe, które korzystają z modelu cenowego bezserwerowego, gdzie płacisz za każde żądanie wykonane wobec bazy danych, takie jak zapytanie czy wstawienie danych. Koszty są zwykle oparte na ilości pracy potrzebnej do obsługi żądania. Na przykład, pojedyncze zapytanie o jeden wiersz na podstawie klucza głównego będzie kosztować mniej niż skomplikowana operacja łącząca wiele tabel i zwracająca tysiące wierszy.

## Tworzenie aplikacji bezserwerowej

Usługa przetwarzania bezserwerowego od Microsoftu nazywa się Azure Functions.

![Logo Azure Functions](../../../../../translated_images/pl/azure-functions-logo.1cfc8e3204c9c44a.webp)

Krótki film poniżej przedstawia przegląd Azure Functions.

[![Film o Azure Functions](https://img.youtube.com/vi/8-jz5f_JyEQ/0.jpg)](https://www.youtube.com/watch?v=8-jz5f_JyEQ)

> 🎥 Kliknij obraz powyżej, aby obejrzeć film.

✅ Poświęć chwilę na zbadanie i przeczytanie przeglądu Azure Functions w [dokumentacji Microsoft Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-overview?WT.mc_id=academic-17441-jabenn).

Aby napisać Azure Functions, zaczynasz od aplikacji Azure Functions w wybranym przez siebie języku. Domyślnie Azure Functions obsługuje Python, JavaScript, TypeScript, C#, F#, Java i Powershell. W tej lekcji nauczysz się, jak napisać aplikację Azure Functions w Pythonie.

> 💁 Azure Functions obsługuje również niestandardowe obsługiwacze, dzięki czemu możesz pisać swoje funkcje w dowolnym języku, który obsługuje żądania HTTP, w tym w starszych językach, takich jak COBOL.

Aplikacje funkcji składają się z jednego lub więcej *wyzwalaczy* — funkcji, które reagują na zdarzenia. Możesz mieć wiele wyzwalaczy w jednej aplikacji funkcji, które współdzielą wspólną konfigurację. Na przykład w pliku konfiguracyjnym Twojej aplikacji funkcji możesz mieć szczegóły połączenia z IoT Hub, a wszystkie funkcje w aplikacji mogą z tego korzystać, aby się połączyć i nasłuchiwać zdarzeń.

### Zadanie - zainstaluj narzędzia Azure Functions

> W momencie pisania tego tekstu narzędzia do kodowania Azure Functions nie działają w pełni na komputerach Apple Silicon z projektami w Pythonie. Będziesz musiał użyć komputera Mac z procesorem Intel, komputera z systemem Windows lub komputera z systemem Linux.

Jedną z wielkich zalet Azure Functions jest to, że możesz je uruchamiać lokalnie. To samo środowisko uruchomieniowe, które jest używane w chmurze, może być uruchamiane na Twoim komputerze, co pozwala na pisanie kodu reagującego na wiadomości IoT i jego lokalne uruchamianie. Możesz nawet debugować swój kod podczas obsługi zdarzeń. Gdy będziesz zadowolony z kodu, możesz go wdrożyć w chmurze.

Narzędzia Azure Functions są dostępne jako interfejs wiersza poleceń, znany jako Azure Functions Core Tools.

1. Zainstaluj narzędzia Azure Functions Core Tools, postępując zgodnie z instrukcjami w [dokumentacji Azure Functions Core Tools](https://docs.microsoft.com/azure/azure-functions/functions-run-local?WT.mc_id=academic-17441-jabenn).

1. Zainstaluj rozszerzenie Azure Functions dla VS Code. To rozszerzenie zapewnia wsparcie dla tworzenia, debugowania i wdrażania funkcji Azure. Zapoznaj się z [dokumentacją rozszerzenia Azure Functions](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-azuretools.vscode-azurefunctions), aby uzyskać instrukcje dotyczące instalacji tego rozszerzenia w VS Code.

Podczas wdrażania aplikacji Azure Functions w chmurze potrzebuje ona niewielkiej ilości pamięci w chmurze do przechowywania takich rzeczy jak pliki aplikacji i pliki dziennika. Podczas lokalnego uruchamiania aplikacji Functions nadal musisz połączyć się z pamięcią w chmurze, ale zamiast korzystać z rzeczywistej pamięci w chmurze, możesz użyć emulatora pamięci o nazwie [Azurite](https://github.com/Azure/Azurite). Działa on lokalnie, ale zachowuje się jak pamięć w chmurze.

> 🎓 W Azure pamięć używana przez Azure Functions to konto magazynu Azure. Konta te mogą przechowywać pliki, bloby, dane w tabelach lub dane w kolejkach. Możesz współdzielić jedno konto magazynu między wieloma aplikacjami, takimi jak aplikacja Functions i aplikacja internetowa.

1. Azurite to aplikacja Node.js, więc musisz zainstalować Node.js. Możesz znaleźć instrukcje dotyczące pobierania i instalacji na [stronie Node.js](https://nodejs.org/). Jeśli używasz Maca, możesz również zainstalować go za pomocą [Homebrew](https://formulae.brew.sh/formula/node).

1. Zainstaluj Azurite za pomocą następującego polecenia (`npm` to narzędzie instalowane razem z Node.js):

    ```sh
    npm install -g azurite
    ```

1. Utwórz folder o nazwie `azurite`, który Azurite będzie używać do przechowywania danych:

    ```sh
    mkdir azurite
    ```

1. Uruchom Azurite, przekazując mu ten nowy folder:

    ```sh
    azurite --location azurite
    ```

    Emulator pamięci Azurite zostanie uruchomiony i będzie gotowy do połączenia z lokalnym środowiskiem uruchomieniowym Functions.

    ```output
    ➜  ~ azurite --location azurite  
    Azurite Blob service is starting at http://127.0.0.1:10000
    Azurite Blob service is successfully listening at http://127.0.0.1:10000
    Azurite Queue service is starting at http://127.0.0.1:10001
    Azurite Queue service is successfully listening at http://127.0.0.1:10001
    Azurite Table service is starting at http://127.0.0.1:10002
    Azurite Table service is successfully listening at http://127.0.0.1:10002
    ```

### Zadanie - utwórz projekt Azure Functions

Interfejs wiersza poleceń Azure Functions może być używany do tworzenia nowej aplikacji funkcji.

1. Utwórz folder dla swojej aplikacji funkcji i przejdź do niego. Nazwij go `soil-moisture-trigger`.

    ```sh
    mkdir soil-moisture-trigger
    cd soil-moisture-trigger
    ```

1. Utwórz wirtualne środowisko Pythona w tym folderze:

    ```sh
    python3 -m venv .venv
    ```

1. Aktywuj wirtualne środowisko:

    * W systemie Windows:
        * Jeśli używasz Wiersza Poleceń lub Wiersza Poleceń przez Windows Terminal, uruchom:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jeśli używasz PowerShell, uruchom:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * W systemie macOS lub Linux uruchom:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Te polecenia powinny być uruchamiane z tej samej lokalizacji, w której uruchomiłeś polecenie tworzenia wirtualnego środowiska. Nigdy nie musisz przechodzić do folderu `.venv`, zawsze uruchamiaj polecenie aktywacji i inne polecenia instalacji pakietów lub uruchamiania kodu z folderu, w którym utworzyłeś wirtualne środowisko.

1. Uruchom następujące polecenie, aby utworzyć aplikację funkcji w tym folderze:

    ```sh
    func init --worker-runtime python soil-moisture-trigger
    ```

    To polecenie utworzy trzy pliki w bieżącym folderze:

    * `host.json` - ten dokument JSON zawiera ustawienia Twojej aplikacji funkcji. Nie będziesz musiał modyfikować tych ustawień.
    * `local.settings.json` - ten dokument JSON zawiera ustawienia, których Twoja aplikacja używa podczas lokalnego uruchamiania, takie jak ciągi połączeń do Twojego IoT Hub. Te ustawienia są tylko lokalne i nie powinny być dodawane do systemu kontroli wersji. Podczas wdrażania aplikacji w chmurze te ustawienia nie są wdrażane, zamiast tego Twoje ustawienia są ładowane z ustawień aplikacji. To zostanie omówione później w tej lekcji.
    * `requirements.txt` - to [plik wymagań Pip](https://pip.pypa.io/en/stable/user_guide/#requirements-files), który zawiera pakiety Pip potrzebne do uruchomienia Twojej aplikacji funkcji.

1. Plik `local.settings.json` zawiera ustawienie dla konta magazynu, które aplikacja funkcji będzie używać. Domyślnie jest ono puste, więc musi zostać ustawione. Aby połączyć się z lokalnym emulatorem pamięci Azurite, ustaw tę wartość na następującą:

    ```json
    "AzureWebJobsStorage": "UseDevelopmentStorage=true",
    ```

1. Zainstaluj niezbędne pakiety Pip za pomocą pliku wymagań:

    ```sh
    pip install -r requirements.txt
    ```

    > 💁 Wymagane pakiety Pip muszą znajdować się w tym pliku, aby podczas wdrażania aplikacji funkcji w chmurze środowisko uruchomieniowe mogło upewnić się, że zainstalowano odpowiednie pakiety.

1. Aby sprawdzić, czy wszystko działa poprawnie, możesz uruchomić środowisko uruchomieniowe funkcji. Uruchom następujące polecenie:

    ```sh
    func start
    ```

    Zobaczysz, jak środowisko uruchomieniowe się uruchamia i zgłasza, że nie znalazło żadnych funkcji zadaniowych (wyzwalaczy).

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    [2021-05-05T01:24:46.795Z] No job functions found.
    ```
> ⚠️ Jeśli pojawi się powiadomienie o zaporze, udziel dostępu, ponieważ aplikacja `func` musi mieć możliwość odczytu i zapisu w Twojej sieci.
> ⚠️ Jeśli używasz macOS, w wynikach mogą pojawić się ostrzeżenia:
>
> ```output
    > (.venv) ➜  soil-moisture-trigger func start
    > Found Python version 3.9.1 (python3).
    >
    > Azure Functions Core Tools
    > Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    > Function Runtime Version: 3.0.15417.0
    >
    > [2021-06-16T08:18:28.315Z] Cannot create directory for shared memory usage: /dev/shm/AzureFunctions
    > [2021-06-16T08:18:28.316Z] System.IO.FileSystem: Access to the path '/dev/shm/AzureFunctions' is denied. Operation not permitted.
    > [2021-06-16T08:18:30.361Z] No job functions found.
    > ```
>
> Możesz je zignorować, o ile aplikacja Functions uruchamia się poprawnie i wyświetla działające funkcje. Jak wspomniano w [tym pytaniu na Microsoft Docs Q&A](https://docs.microsoft.com/answers/questions/396617/azure-functions-core-tools-error-osx-devshmazurefu.html?WT.mc_id=academic-17441-jabenn), można je zignorować.

1. Zatrzymaj aplikację Functions, naciskając `ctrl+c`.

1. Otwórz bieżący folder w VS Code, albo uruchamiając VS Code i otwierając ten folder, albo uruchamiając następujące polecenie:

    ```sh
    code .
    ```

    VS Code wykryje Twój projekt Functions i wyświetli powiadomienie:

    ```output
    Detected an Azure Functions Project in folder "soil-moisture-trigger" that may have been created outside of
    VS Code. Initialize for optimal use with VS Code?
    ```

    ![Powiadomienie](../../../../../translated_images/pl/vscode-azure-functions-init-notification.bd19b49229963edb.webp)

    Wybierz **Yes** w tym powiadomieniu.

1. Upewnij się, że w terminalu VS Code działa wirtualne środowisko Python. Jeśli to konieczne, zakończ je i uruchom ponownie.

## Utwórz wyzwalacz zdarzeń IoT Hub

Aplikacja Functions jest powłoką dla Twojego kodu serwerless. Aby reagować na zdarzenia IoT Hub, możesz dodać wyzwalacz IoT Hub do tej aplikacji. Wyzwalacz musi połączyć się ze strumieniem wiadomości wysyłanych do IoT Hub i na nie reagować. Aby uzyskać ten strumień wiadomości, Twój wyzwalacz musi połączyć się z *kompatybilnym punktem końcowym Event Hub* IoT Hub.

IoT Hub opiera się na innej usłudze Azure zwanej Azure Event Hubs. Event Hubs to usługa umożliwiająca wysyłanie i odbieranie wiadomości, a IoT Hub rozszerza ją o funkcje dla urządzeń IoT. Sposób, w jaki łączysz się, aby odczytać wiadomości z IoT Hub, jest taki sam, jak w przypadku korzystania z Event Hubs.

✅ Zrób trochę badań: Przeczytaj przegląd Event Hubs w [dokumentacji Azure Event Hubs](https://docs.microsoft.com/azure/event-hubs/event-hubs-about?WT.mc_id=academic-17441-jabenn). Jak podstawowe funkcje porównują się z IoT Hub?

Aby urządzenie IoT mogło połączyć się z IoT Hub, musi używać klucza tajnego, który zapewnia, że tylko dozwolone urządzenia mogą się połączyć. To samo dotyczy połączenia w celu odczytu wiadomości – Twój kod będzie potrzebował ciągu połączenia zawierającego klucz tajny oraz szczegóły IoT Hub.

> 💁 Domyślny ciąg połączenia, który otrzymujesz, ma uprawnienia **iothubowner**, co daje każdemu kodowi, który go używa, pełne uprawnienia do IoT Hub. Idealnie powinieneś łączyć się z najniższym poziomem wymaganych uprawnień. Zostanie to omówione w następnej lekcji.

Po nawiązaniu połączenia przez wyzwalacz, kod wewnątrz funkcji będzie wywoływany dla każdej wiadomości wysłanej do IoT Hub, niezależnie od tego, które urządzenie ją wysłało. Wyzwalacz przekaże wiadomość jako parametr.

### Zadanie - uzyskaj ciąg połączenia kompatybilnego punktu końcowego Event Hub

1. W terminalu VS Code uruchom następujące polecenie, aby uzyskać ciąg połączenia dla kompatybilnego punktu końcowego Event Hub IoT Hub:

    ```sh
    az iot hub connection-string show --default-eventhub \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

1. W VS Code otwórz plik `local.settings.json`. Dodaj następującą wartość w sekcji `Values`:

    ```json
    "IOT_HUB_CONNECTION_STRING": "<connection string>"
    ```

    Zamień `<connection string>` na wartość z poprzedniego kroku. Musisz dodać przecinek po poprzedniej linii, aby plik był poprawnym JSON-em.

### Zadanie - utwórz wyzwalacz zdarzeń

Teraz możesz utworzyć wyzwalacz zdarzeń.

1. W terminalu VS Code uruchom następujące polecenie z folderu `soil-moisture-trigger`:

    ```sh
    func new --name iot-hub-trigger --template "Azure Event Hub trigger"
    ```

    To polecenie tworzy nową funkcję o nazwie `iot-hub-trigger`. Wyzwalacz połączy się z kompatybilnym punktem końcowym Event Hub w IoT Hub, więc możesz użyć wyzwalacza Event Hub. Nie ma specyficznego wyzwalacza IoT Hub.

To utworzy folder w folderze `soil-moisture-trigger` o nazwie `iot-hub-trigger`, który zawiera tę funkcję. W tym folderze znajdą się następujące pliki:

* `__init__.py` - plik kodu Python zawierający wyzwalacz, używający standardowej konwencji nazewnictwa plików Python, aby przekształcić ten folder w moduł Python.

    Ten plik będzie zawierał następujący kod:

    ```python
    import logging

    import azure.functions as func


    def main(event: func.EventHubEvent):
        logging.info('Python EventHub trigger processed an event: %s',
                    event.get_body().decode('utf-8'))
    ```

    Główna część wyzwalacza to funkcja `main`. To właśnie ta funkcja jest wywoływana z wydarzeniami z IoT Hub. Funkcja ma parametr `event`, który zawiera `EventHubEvent`. Za każdym razem, gdy wiadomość jest wysyłana do IoT Hub, funkcja jest wywoływana, przekazując tę wiadomość jako `event`, wraz z właściwościami, które są takie same jak adnotacje, które widziałeś w poprzedniej lekcji.

    Główna część tej funkcji loguje zdarzenie.

* `function.json` - zawiera konfigurację dla wyzwalacza. Główna konfiguracja znajduje się w sekcji `bindings`. Binding to termin określający połączenie między Azure Functions a innymi usługami Azure. Ta funkcja ma binding wejściowy do Event Hub - łączy się z Event Hub i odbiera dane.

    > 💁 Możesz także mieć bindingi wyjściowe, dzięki którym dane wyjściowe funkcji są wysyłane do innej usługi. Na przykład możesz dodać binding wyjściowy do bazy danych i zwrócić zdarzenie IoT Hub z funkcji, a zostanie ono automatycznie wstawione do bazy danych.

    ✅ Zrób trochę badań: Przeczytaj o bindingach w [dokumentacji koncepcji wyzwalaczy i bindingów Azure Functions](https://docs.microsoft.com/azure/azure-functions/functions-triggers-bindings?WT.mc_id=academic-17441-jabenn&tabs=python).

    Sekcja `bindings` zawiera konfigurację dla bindingu. Interesujące wartości to:

  * `"type": "eventHubTrigger"` - informuje funkcję, że musi nasłuchiwać zdarzeń z Event Hub
  * `"name": "events"` - to nazwa parametru używanego dla zdarzeń Event Hub. Odpowiada nazwie parametru w funkcji `main` w kodzie Python.
  * `"direction": "in"` - to binding wejściowy, dane z Event Hub trafiają do funkcji
  * `"connection": ""` - definiuje nazwę ustawienia, z którego odczytywany jest ciąg połączenia. Podczas uruchamiania lokalnie, ustawienie to zostanie odczytane z pliku `local.settings.json`.

    > 💁 Ciąg połączenia nie może być przechowywany w pliku `function.json`, musi być odczytywany z ustawień. Ma to na celu zapobieżenie przypadkowemu ujawnieniu ciągu połączenia.

1. Z powodu [błędu w szablonie Azure Functions](https://github.com/Azure/azure-functions-templates/issues/1250), pole `cardinality` w pliku `function.json` ma nieprawidłową wartość. Zaktualizuj tę wartość z `many` na `one`:

    ```json
    "cardinality": "one",
    ```

1. Zaktualizuj wartość `"connection"` w pliku `function.json`, aby wskazywała na nową wartość dodaną do pliku `local.settings.json`:

    ```json
    "connection": "IOT_HUB_CONNECTION_STRING",
    ```

    > 💁 Pamiętaj - musi to wskazywać na ustawienie, a nie zawierać rzeczywisty ciąg połączenia.

1. Ciąg połączenia zawiera wartość `eventHubName`, więc wartość dla tego pola w pliku `function.json` musi być wyczyszczona. Zaktualizuj tę wartość do pustego ciągu:

    ```json
    "eventHubName": "",
    ```

### Zadanie - uruchom wyzwalacz zdarzeń

1. Upewnij się, że nie uruchamiasz monitora zdarzeń IoT Hub. Jeśli działa on jednocześnie z aplikacją Functions, aplikacja Functions nie będzie mogła się połączyć i konsumować zdarzeń.

    > 💁 Wiele aplikacji może łączyć się z punktami końcowymi IoT Hub, używając różnych *grup konsumentów*. Zostanie to omówione w późniejszej lekcji.

1. Aby uruchomić aplikację Functions, uruchom następujące polecenie w terminalu VS Code:

    ```sh
    func start
    ```

    Aplikacja Functions uruchomi się, wykryje funkcję `iot-hub-trigger` i przetworzy wszystkie zdarzenia, które zostały już wysłane do IoT Hub w ciągu ostatniego dnia.

    ```output
    (.venv) ➜  soil-moisture-trigger func start
    Found Python version 3.9.1 (python3).
    
    Azure Functions Core Tools
    Core Tools Version:       3.0.3442 Commit hash: 6bfab24b2743f8421475d996402c398d2fe4a9e0  (64-bit)
    Function Runtime Version: 3.0.15417.0
    
    Functions:
    
            iot-hub-trigger: eventHubTrigger
    
    For detailed output, run func with --verbose flag.
    [2021-05-05T02:44:07.517Z] Worker process started and initialized.
    [2021-05-05T02:44:09.202Z] Executing 'Functions.iot-hub-trigger' (Reason='(null)', Id=802803a5-eae9-4401-a1f4-176631456ce4)
    [2021-05-05T02:44:09.205Z] Trigger Details: PartitionId: 0, Offset: 1011240-1011632, EnqueueTimeUtc: 2021-05-04T19:04:04.2030000Z-2021-05-04T19:04:04.3900000Z, SequenceNumber: 2546-2547, Count: 2
    [2021-05-05T02:44:09.352Z] Python EventHub trigger processed an event: {"soil_moisture":628}
    [2021-05-05T02:44:09.354Z] Python EventHub trigger processed an event: {"soil_moisture":624}
    [2021-05-05T02:44:09.395Z] Executed 'Functions.iot-hub-trigger' (Succeeded, Id=802803a5-eae9-4401-a1f4-176631456ce4, Duration=245ms)
    ```

    Każde wywołanie funkcji będzie otoczone blokiem `Executing 'Functions.iot-hub-trigger'`/`Executed 'Functions.iot-hub-trigger'` w wynikach, dzięki czemu zobaczysz, ile wiadomości zostało przetworzonych w każdym wywołaniu funkcji.

1. Upewnij się, że Twoje urządzenie IoT działa. Zobaczysz nowe wiadomości o wilgotności gleby pojawiające się w aplikacji Functions.

1. Zatrzymaj i ponownie uruchom aplikację Functions. Zobaczysz, że nie przetworzy ponownie poprzednich wiadomości, przetworzy tylko nowe wiadomości.

> 💁 VS Code obsługuje również debugowanie Twoich funkcji. Możesz ustawić punkty przerwania, klikając na marginesie przy początku każdej linii kodu, lub umieszczając kursor na linii kodu i wybierając *Run -> Toggle breakpoint*, lub naciskając `F9`. Możesz uruchomić debuger, wybierając *Run -> Start debugging*, naciskając `F5`, lub wybierając panel *Run and debug* i klikając przycisk **Start debugging**. Dzięki temu możesz zobaczyć szczegóły przetwarzanych zdarzeń.

#### Rozwiązywanie problemów

* Jeśli otrzymasz następujący błąd:

    ```output
    The listener for function 'Functions.iot-hub-trigger' was unable to start. Microsoft.WindowsAzure.Storage: Connection refused. System.Net.Http: Connection refused. System.Private.CoreLib: Connection refused.
    ```

    Sprawdź, czy Azurite działa i czy ustawiłeś `AzureWebJobsStorage` w pliku `local.settings.json` na `UseDevelopmentStorage=true`.

* Jeśli otrzymasz następujący błąd:

    ```output
    System.Private.CoreLib: Exception while executing function: Functions.iot-hub-trigger. System.Private.CoreLib: Result: Failure Exception: AttributeError: 'list' object has no attribute 'get_body'
    ```

    Sprawdź, czy ustawiłeś `cardinality` w pliku `function.json` na `one`.

* Jeśli otrzymasz następujący błąd:

    ```output
    Azure.Messaging.EventHubs: The path to an Event Hub may be specified as part of the connection string or as a separate value, but not both.  Please verify that your connection string does not have the `EntityPath` token if you are passing an explicit Event Hub name. (Parameter 'connectionString').
    ```

    Sprawdź, czy ustawiłeś `eventHubName` w pliku `function.json` na pusty ciąg.

## Wysyłanie żądań metod bezpośrednich z kodu serwerless

Do tej pory Twoja aplikacja Functions nasłuchuje wiadomości z IoT Hub, używając kompatybilnego punktu końcowego Event Hub. Teraz musisz wysyłać polecenia do urządzenia IoT. Odbywa się to za pomocą innego połączenia z IoT Hub przez *Registry Manager*. Registry Manager to narzędzie, które pozwala zobaczyć, jakie urządzenia są zarejestrowane w IoT Hub, i komunikować się z tymi urządzeniami, wysyłając wiadomości z chmury do urządzenia, żądania metod bezpośrednich lub aktualizując bliźniaka urządzenia. Możesz również używać go do rejestrowania, aktualizowania lub usuwania urządzeń IoT z IoT Hub.

Aby połączyć się z Registry Manager, potrzebujesz ciągu połączenia.

### Zadanie - uzyskaj ciąg połączenia Registry Manager

1. Aby uzyskać ciąg połączenia, uruchom następujące polecenie:

    ```sh
    az iot hub connection-string show --policy-name service \
                                      --output table \
                                      --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

    Ciąg połączenia jest żądany dla polityki *ServiceConnect* za pomocą parametru `--policy-name service`. Podczas żądania ciągu połączenia możesz określić, jakie uprawnienia ten ciąg połączenia będzie umożliwiał. Polityka ServiceConnect pozwala Twojemu kodowi na połączenie i wysyłanie wiadomości do urządzeń IoT.

    ✅ Zrób trochę badań: Przeczytaj o różnych politykach w [dokumentacji uprawnień IoT Hub](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-security#iot-hub-permissions?WT.mc_id=academic-17441-jabenn)

1. W VS Code otwórz plik `local.settings.json`. Dodaj następującą wartość w sekcji `Values`:

    ```json
    "REGISTRY_MANAGER_CONNECTION_STRING": "<connection string>"
    ```

    Zamień `<connection string>` na wartość z poprzedniego kroku. Musisz dodać przecinek po poprzedniej linii, aby plik był poprawnym JSON-em.

### Zadanie - wyślij żądanie metody bezpośredniej do urządzenia

1. SDK dla Registry Manager jest dostępne jako pakiet Pip. Dodaj następującą linię do pliku `requirements.txt`, aby dodać zależność od tego pakietu:

    ```sh
    azure-iot-hub
    ```

1. Upewnij się, że terminal VS Code ma aktywowane wirtualne środowisko, i uruchom następujące polecenie, aby zainstalować pakiety Pip:

    ```sh
    pip install -r requirements.txt
    ```

1. Dodaj następujące importy do pliku `__init__.py`:

    ```python
    import json
    import os
    from azure.iot.hub import IoTHubRegistryManager
    from azure.iot.hub.models import CloudToDeviceMethod
    ```

    To importuje niektóre biblioteki systemowe, a także biblioteki do interakcji z Registry Manager i wysyłania żądań metod bezpośrednich.

1. Usuń kod z wnętrza metody `main`, ale zachowaj samą metodę.

1. W metodzie `main` dodaj następujący kod:

    ```python
    body = json.loads(event.get_body().decode('utf-8'))
    device_id = event.iothub_metadata['connection-device-id']

    logging.info(f'Received message: {body} from {device_id}')
    ```

    Ten kod wyodrębnia treść zdarzenia, która zawiera wiadomość JSON wysłaną przez urządzenie IoT.

    Następnie pobiera identyfikator urządzenia z adnotacji przekazanych z wiadomością. Treść zdarzenia zawiera wiadomość wysłaną jako telemetria, a słownik `iothub_metadata` zawiera właściwości ustawione przez IoT Hub, takie jak identyfikator urządzenia nadawcy i czas wysłania wiadomości.

    Te informacje są następnie logowane. Zobaczysz to logowanie w terminalu podczas lokalnego uruchamiania aplikacji Functions.

1. Poniżej tego dodaj następujący kod:

    ```python
    soil_moisture = body['soil_moisture']

    if soil_moisture > 450:
        direct_method = CloudToDeviceMethod(method_name='relay_on', payload='{}')
    else:
        direct_method = CloudToDeviceMethod(method_name='relay_off', payload='{}')
    ```

    Ten kod pobiera wilgotność gleby z wiadomości. Następnie sprawdza wilgotność gleby i w zależności od wartości tworzy klasę pomocniczą dla żądania metody bezpośredniej dla metody `relay_on` lub `relay_off`. Żądanie metody nie wymaga ładunku, więc wysyłany jest pusty dokument JSON.

1. Poniżej tego dodaj następujący kod:

    ```python
    logging.info(f'Sending direct method request for {direct_method.method_name} for device {device_id}')

    registry_manager_connection_string = os.environ['REGISTRY_MANAGER_CONNECTION_STRING']
    registry_manager = IoTHubRegistryManager(registry_manager_connection_string)
    ```
Ten kod ładuje `REGISTRY_MANAGER_CONNECTION_STRING` z pliku `local.settings.json`. Wartości w tym pliku są udostępniane jako zmienne środowiskowe i można je odczytać za pomocą funkcji `os.environ`, która zwraca słownik wszystkich zmiennych środowiskowych.

> 💁 Gdy ten kod zostanie wdrożony w chmurze, wartości z pliku `local.settings.json` zostaną ustawione jako *Application Settings* i można je odczytać ze zmiennych środowiskowych.

Kod następnie tworzy instancję pomocniczej klasy Registry Manager, używając ciągu połączenia.

1. Poniżej dodaj następujący kod:

    ```python
    registry_manager.invoke_device_method(device_id, direct_method)

    logging.info('Direct method request sent!')
    ```

    Ten kod instruuje menedżera rejestru, aby wysłał żądanie metody bezpośredniej do urządzenia, które wysłało telemetrię.

    > 💁 W wersjach aplikacji, które stworzyłeś w poprzednich lekcjach, używając MQTT, polecenia sterowania przekaźnikiem były wysyłane do wszystkich urządzeń. Kod zakładał, że będziesz mieć tylko jedno urządzenie. Ta wersja kodu wysyła żądanie metody do pojedynczego urządzenia, dzięki czemu działa, jeśli masz wiele zestawów czujników wilgotności i przekaźników, wysyłając odpowiednie żądanie metody do właściwego urządzenia.

1. Uruchom aplikację Functions i upewnij się, że Twoje urządzenie IoT wysyła dane. Zobaczysz przetwarzane wiadomości i wysyłane żądania metod bezpośrednich. Przesuwaj czujnik wilgotności gleby w i poza glebę, aby zobaczyć zmieniające się wartości i włączanie/wyłączanie przekaźnika.

> 💁 Ten kod znajdziesz w folderze [code/functions](../../../../../2-farm/lessons/5-migrate-application-to-the-cloud/code/functions).

## Wdróż swój kod bezserwerowy w chmurze

Twój kod działa teraz lokalnie, więc następnym krokiem jest wdrożenie aplikacji Functions w chmurze.

### Zadanie - utwórz zasoby w chmurze

Twoja aplikacja Functions musi zostać wdrożona w zasobie Functions App w Azure, znajdującym się w grupie zasobów, którą utworzyłeś dla swojego IoT Hub. Będziesz także potrzebować konta magazynu utworzonego w Azure, aby zastąpić emulowane konto działające lokalnie.

1. Uruchom następujące polecenie, aby utworzyć konto magazynu:

    ```sh
    az storage account create --resource-group soil-moisture-sensor \
                              --sku Standard_LRS \
                              --name <storage_name> 
    ```

    Zamień `<storage_name>` na nazwę swojego konta magazynu. Musi być ona globalnie unikalna, ponieważ stanowi część adresu URL używanego do uzyskania dostępu do konta magazynu. Możesz używać tylko małych liter i cyfr, bez innych znaków, a nazwa jest ograniczona do 24 znaków. Użyj czegoś w rodzaju `sms` i dodaj unikalny identyfikator na końcu, na przykład losowe słowa lub swoje imię.

    Opcja `--sku Standard_LRS` wybiera poziom cenowy, wybierając najtańsze konto ogólnego przeznaczenia. Nie ma darmowego poziomu magazynu, a płacisz za to, co wykorzystasz. Koszty są stosunkowo niskie, a najdroższy magazyn kosztuje mniej niż 0,05 USD miesięcznie za gigabajt przechowywanych danych.

    ✅ Przeczytaj więcej o cenach na stronie [Azure Storage Account pricing page](https://azure.microsoft.com/pricing/details/storage/?WT.mc_id=academic-17441-jabenn)

1. Uruchom następujące polecenie, aby utworzyć aplikację Functions:

    ```sh
    az functionapp create --resource-group soil-moisture-sensor \
                          --runtime python \
                          --functions-version 3 \
                          --os-type Linux \
                          --consumption-plan-location <location> \
                          --storage-account <storage_name> \
                          --name <functions_app_name>
    ```

    Zamień `<location>` na lokalizację, której użyłeś podczas tworzenia grupy zasobów w poprzedniej lekcji.

    Zamień `<storage_name>` na nazwę konta magazynu, które utworzyłeś w poprzednim kroku.

    Zamień `<functions_app_name>` na unikalną nazwę dla swojej aplikacji Functions. Musi być ona globalnie unikalna, ponieważ stanowi część adresu URL, który może być używany do uzyskania dostępu do aplikacji Functions. Użyj czegoś w rodzaju `soil-moisture-sensor-` i dodaj unikalny identyfikator na końcu, na przykład losowe słowa lub swoje imię.

    Opcja `--functions-version 3` ustawia wersję Azure Functions do użycia. Wersja 3 to najnowsza wersja.

    Opcja `--os-type Linux` informuje środowisko uruchomieniowe Functions, aby używało systemu Linux jako systemu operacyjnego do hostowania tych funkcji. Funkcje mogą być hostowane na systemach Linux lub Windows, w zależności od używanego języka programowania. Aplikacje Python są obsługiwane tylko na systemie Linux.

### Zadanie - prześlij ustawienia aplikacji

Podczas tworzenia aplikacji Functions przechowywałeś pewne ustawienia w pliku `local.settings.json` dla ciągów połączeń do swojego IoT Hub. Te ustawienia muszą zostać zapisane jako Application Settings w Twojej aplikacji Functions w Azure, aby mogły być używane przez Twój kod.

> 🎓 Plik `local.settings.json` jest przeznaczony wyłącznie do ustawień lokalnych i nie powinien być dodawany do systemu kontroli wersji, takiego jak GitHub. Po wdrożeniu w chmurze używane są Application Settings. Application Settings to pary klucz/wartość hostowane w chmurze i odczytywane ze zmiennych środowiskowych w kodzie lub przez środowisko uruchomieniowe podczas łączenia kodu z IoT Hub.

1. Uruchom następujące polecenie, aby ustawić ustawienie `IOT_HUB_CONNECTION_STRING` w Application Settings aplikacji Functions:

    ```sh
    az functionapp config appsettings set --resource-group soil-moisture-sensor \
                                          --name <functions_app_name> \
                                          --settings "IOT_HUB_CONNECTION_STRING=<connection string>"
    ```

    Zamień `<functions_app_name>` na nazwę, której użyłeś dla swojej aplikacji Functions.

    Zamień `<connection string>` na wartość `IOT_HUB_CONNECTION_STRING` z pliku `local.settings.json`.

1. Powtórz powyższy krok, ale ustaw wartość `REGISTRY_MANAGER_CONNECTION_STRING` na odpowiednią wartość z pliku `local.settings.json`.

Po uruchomieniu tych poleceń zostanie również wyświetlona lista wszystkich Application Settings dla aplikacji Functions. Możesz użyć tej listy, aby sprawdzić, czy wartości zostały ustawione poprawnie.

> 💁 Zobaczysz wartość już ustawioną dla `AzureWebJobsStorage`. W pliku `local.settings.json` była ona ustawiona na wartość używającą lokalnego emulatora magazynu. Podczas tworzenia aplikacji Functions przekazujesz konto magazynu jako parametr, a wartość ta jest ustawiana automatycznie w tym ustawieniu.

### Zadanie - wdroż swoją aplikację Functions w chmurze

Teraz, gdy aplikacja Functions jest gotowa, Twój kod może zostać wdrożony.

1. Uruchom następujące polecenie z terminala VS Code, aby opublikować swoją aplikację Functions:

    ```sh
    func azure functionapp publish <functions_app_name>
    ```

    Zamień `<functions_app_name>` na nazwę, której użyłeś dla swojej aplikacji Functions.

Kod zostanie spakowany i wysłany do aplikacji Functions, gdzie zostanie wdrożony i uruchomiony. Na konsoli pojawi się wiele komunikatów, kończących się potwierdzeniem wdrożenia i listą wdrożonych funkcji. W tym przypadku lista będzie zawierać tylko wyzwalacz.

```output
Deployment successful.
Remote build succeeded!
Syncing triggers...
Functions in soil-moisture-sensor:
    iot-hub-trigger - [eventHubTrigger]
```

Upewnij się, że Twoje urządzenie IoT działa. Zmieniaj poziomy wilgotności, dostosowując wilgotność gleby lub przesuwając czujnik w i poza glebę. Zobaczysz, jak przekaźnik włącza się i wyłącza w zależności od zmian wilgotności gleby.

---

## 🚀 Wyzwanie

W poprzedniej lekcji zarządzałeś czasem działania przekaźnika, rezygnując z subskrypcji wiadomości MQTT, gdy przekaźnik był włączony, i przez krótki czas po jego wyłączeniu. Nie możesz użyć tej metody tutaj - nie możesz zrezygnować z subskrypcji wyzwalacza IoT Hub.

Zastanów się nad różnymi sposobami, w jakie możesz to obsłużyć w swojej aplikacji Functions.

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/18)

## Przegląd i samodzielna nauka

* Przeczytaj o obliczeniach bezserwerowych na stronie [Serverless Computing na Wikipedii](https://wikipedia.org/wiki/Serverless_computing)
* Przeczytaj o używaniu rozwiązań bezserwerowych w Azure, w tym więcej przykładów, na blogu [Go serverless for your IoT needs Azure](https://azure.microsoft.com/blog/go-serverless-for-your-iot-needs/?WT.mc_id=academic-17441-jabenn)
* Dowiedz się więcej o Azure Functions na [kanale YouTube Azure Functions](https://www.youtube.com/c/AzureFunctions)

## Zadanie

[Dodaj ręczne sterowanie przekaźnikiem](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić precyzję, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.