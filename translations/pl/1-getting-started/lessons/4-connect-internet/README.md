# Podłącz swoje urządzenie do Internetu

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-4.7344e074ea68fa54.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obrazek, aby zobaczyć większą wersję.

Ta lekcja była częścią serii [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) organizowanej przez [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcja została podzielona na dwa filmy: godzinny wykład oraz godzinne konsultacje, podczas których szczegółowo omówiono wybrane części lekcji i odpowiadano na pytania.

[![Lekcja 4: Podłącz swoje urządzenie do Internetu](https://img.youtube.com/vi/O4dd172mZhs/0.jpg)](https://youtu.be/O4dd172mZhs)

[![Lekcja 4: Podłącz swoje urządzenie do Internetu - Konsultacje](https://img.youtube.com/vi/j-cVCzRDE2Q/0.jpg)](https://youtu.be/j-cVCzRDE2Q)

> 🎥 Kliknij powyższe obrazy, aby obejrzeć filmy

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/7)

## Wprowadzenie

Litera **I** w IoT oznacza **Internet** – połączenie z chmurą i usługi, które umożliwiają wiele funkcji urządzeń IoT, od zbierania pomiarów z czujników podłączonych do urządzenia, po wysyłanie wiadomości sterujących do elementów wykonawczych. Urządzenia IoT zazwyczaj łączą się z jedną usługą IoT w chmurze za pomocą standardowego protokołu komunikacyjnego, a ta usługa jest połączona z resztą aplikacji IoT, od usług AI podejmujących inteligentne decyzje na podstawie danych, po aplikacje webowe do sterowania lub raportowania.

> 🎓 Dane zbierane z czujników i wysyłane do chmury nazywane są telemetrią.

Urządzenia IoT mogą odbierać wiadomości z chmury. Często są to polecenia – instrukcje wykonania jakiejś akcji, zarówno wewnętrznej (np. restart lub aktualizacja oprogramowania), jak i z użyciem elementu wykonawczego (np. włączenie światła).

Ta lekcja wprowadza niektóre protokoły komunikacyjne, które urządzenia IoT mogą używać do łączenia się z chmurą, oraz typy danych, które mogą wysyłać lub odbierać. Będziesz także mieć okazję praktycznie z nimi pracować, dodając kontrolę przez Internet do swojej lampki nocnej, przenosząc logikę sterowania diodą LED do kodu 'serwera' uruchamianego lokalnie.

W tej lekcji omówimy:

* [Protokoły komunikacyjne](../../../../../1-getting-started/lessons/4-connect-internet)
* [Message Queueing Telemetry Transport (MQTT)](../../../../../1-getting-started/lessons/4-connect-internet)
* [Telemetria](../../../../../1-getting-started/lessons/4-connect-internet)
* [Polecenia](../../../../../1-getting-started/lessons/4-connect-internet)

## Protokoły komunikacyjne

Istnieje wiele popularnych protokołów komunikacyjnych używanych przez urządzenia IoT do komunikacji z Internetem. Najpopularniejsze opierają się na modelu publikowania/subskrypcji za pośrednictwem jakiegoś rodzaju brokera. Urządzenia IoT łączą się z brokerem, publikują telemetrię i subskrybują polecenia. Usługi w chmurze również łączą się z brokerem, subskrybują wszystkie wiadomości telemetrii i publikują polecenia skierowane do konkretnych urządzeń lub grup urządzeń.

![Urządzenia IoT łączą się z brokerem, publikują telemetrię i subskrybują polecenia. Usługi w chmurze łączą się z brokerem, subskrybują wszystkie wiadomości telemetrii i wysyłają polecenia do konkretnych urządzeń.](../../../../../translated_images/pl/pub-sub.7c7ed43fe9fd15d4.webp)

MQTT jest najpopularniejszym protokołem komunikacyjnym dla urządzeń IoT i jest omówiony w tej lekcji. Inne protokoły to AMQP oraz HTTP/HTTPS.

## Message Queueing Telemetry Transport (MQTT)

[MQTT](http://mqtt.org) to lekki, otwarty standard protokołu komunikacyjnego, który umożliwia przesyłanie wiadomości między urządzeniami. Został zaprojektowany w 1999 roku do monitorowania rurociągów naftowych, a 15 lat później udostępniony jako otwarty standard przez IBM.

MQTT działa na zasadzie jednego brokera i wielu klientów. Wszystkie klienty łączą się z brokerem, a broker przekazuje wiadomości do odpowiednich klientów. Wiadomości są przekazywane za pomocą nazwanych tematów, zamiast być wysyłane bezpośrednio do konkretnego klienta. Klient może publikować wiadomości w temacie, a każdy klient subskrybujący ten temat otrzyma wiadomość.

![Urządzenie IoT publikujące telemetrię w temacie /telemetry, a usługa w chmurze subskrybująca ten temat](../../../../../translated_images/pl/mqtt.cbf7f21d9adc3e17.webp)

✅ Zrób badania. Jeśli masz wiele urządzeń IoT, jak możesz zapewnić, że Twój broker MQTT poradzi sobie z wszystkimi wiadomościami?

### Podłącz swoje urządzenie IoT do MQTT

Pierwszym krokiem w dodaniu kontroli przez Internet do lampki nocnej jest podłączenie jej do brokera MQTT.

#### Zadanie

Podłącz swoje urządzenie do brokera MQTT.

W tej części lekcji podłączysz swoją lampkę nocną IoT do Internetu, aby można było nią sterować zdalnie. Później w tej lekcji Twoje urządzenie IoT wyśle wiadomość telemetrii przez MQTT do publicznego brokera MQTT z poziomem światła, gdzie zostanie ona odebrana przez kod serwera, który napiszesz. Ten kod sprawdzi poziom światła i wyśle wiadomość polecenia z powrotem do urządzenia, informując je, czy włączyć, czy wyłączyć diodę LED.

Przykładem zastosowania takiego rozwiązania w rzeczywistości mogłoby być zbieranie danych z wielu czujników światła przed podjęciem decyzji o włączeniu świateł w miejscu, gdzie jest ich dużo, na przykład na stadionie. Dzięki temu światła nie zostaną włączone, jeśli tylko jeden czujnik zostanie zasłonięty przez chmury lub ptaka, ale pozostałe czujniki wykryją wystarczającą ilość światła.

✅ Jakie inne sytuacje wymagałyby oceny danych z wielu czujników przed wysłaniem poleceń?

Zamiast zajmować się złożonością konfiguracji brokera MQTT w ramach tego zadania, możesz skorzystać z publicznego serwera testowego, który działa na [Eclipse Mosquitto](https://www.mosquitto.org), otwartoźródłowym brokerze MQTT. Ten serwer testowy jest publicznie dostępny pod adresem [test.mosquitto.org](https://test.mosquitto.org) i nie wymaga zakładania konta, co czyni go świetnym narzędziem do testowania klientów i serwerów MQTT.

> 💁 Ten serwer testowy jest publiczny i nie jest zabezpieczony. Każdy może słuchać tego, co publikujesz, więc nie powinien być używany do przesyłania danych, które muszą pozostać prywatne.

![Schemat przepływu zadania pokazujący odczyty poziomów światła, ich sprawdzanie i kontrolę diody LED](../../../../../translated_images/pl/assignment-1-internet-flow.3256feab5f052fd2.webp)

Wykonaj odpowiedni krok poniżej, aby podłączyć swoje urządzenie do brokera MQTT:

* [Arduino - Wio Terminal](wio-terminal-mqtt.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie IoT](single-board-computer-mqtt.md)

### Głębsze spojrzenie na MQTT

Tematy mogą mieć hierarchię, a klienty mogą subskrybować różne poziomy hierarchii za pomocą symboli wieloznacznych. Na przykład możesz wysyłać wiadomości telemetrii temperatury do tematu `/telemetry/temperature` i wiadomości telemetrii wilgotności do tematu `/telemetry/humidity`, a następnie w swojej aplikacji w chmurze subskrybować temat `/telemetry/*`, aby odbierać zarówno wiadomości telemetrii temperatury, jak i wilgotności.

Wiadomości mogą być wysyłane z różnym poziomem jakości usług (QoS), który określa gwarancję ich odbioru.

* Najwyżej raz – wiadomość jest wysyłana tylko raz, a klient i broker nie podejmują dodatkowych kroków w celu potwierdzenia dostarczenia (wyślij i zapomnij).
* Co najmniej raz – wiadomość jest ponawiana przez nadawcę wielokrotnie, aż do otrzymania potwierdzenia (dostarczenie potwierdzone).
* Dokładnie raz – nadawca i odbiorca angażują się w dwupoziomowy proces potwierdzenia, aby zapewnić, że tylko jedna kopia wiadomości zostanie odebrana (dostarczenie gwarantowane).

✅ Jakie sytuacje mogą wymagać wiadomości z gwarantowanym dostarczeniem zamiast wiadomości typu wyślij i zapomnij?

Pomimo nazwy Message Queueing (inicjały w MQTT), protokół ten nie obsługuje kolejek wiadomości. Oznacza to, że jeśli klient się rozłączy, a następnie połączy ponownie, nie otrzyma wiadomości wysłanych podczas rozłączenia, z wyjątkiem tych, które już zaczął przetwarzać za pomocą procesu QoS. Wiadomości mogą mieć ustawioną flagę "retained". Jeśli jest ona ustawiona, broker MQTT przechowa ostatnią wiadomość wysłaną w temacie z tą flagą i wyśle ją do każdego klienta, który później zasubskrybuje ten temat. W ten sposób klienty zawsze otrzymają najnowszą wiadomość.

MQTT obsługuje również funkcję "keep alive", która sprawdza, czy połączenie jest nadal aktywne podczas długich przerw między wiadomościami.

> 🦟 [Mosquitto od Eclipse Foundation](https://mosquitto.org) oferuje darmowy broker MQTT, który możesz uruchomić samodzielnie, aby eksperymentować z MQTT, oraz publiczny broker MQTT, który możesz używać do testowania swojego kodu, dostępny pod adresem [test.mosquitto.org](https://test.mosquitto.org).

Połączenia MQTT mogą być publiczne i otwarte lub szyfrowane i zabezpieczone za pomocą nazw użytkowników i haseł, lub certyfikatów.

> 💁 MQTT komunikuje się za pomocą TCP/IP, tego samego podstawowego protokołu sieciowego co HTTP, ale na innym porcie. Możesz również używać MQTT przez websockets, aby komunikować się z aplikacjami webowymi działającymi w przeglądarce lub w sytuacjach, gdy zapory sieciowe lub inne reguły sieciowe blokują standardowe połączenia MQTT.

## Telemetria

Słowo telemetria pochodzi z greckich korzeni oznaczających zdalne mierzenie. Telemetria to proces zbierania danych z czujników i wysyłania ich do chmury.

> 💁 Jedno z pierwszych urządzeń telemetrycznych zostało wynalezione we Francji w 1874 roku i przesyłało w czasie rzeczywistym dane pogodowe i głębokość śniegu z Mont Blanc do Paryża. Wykorzystywało fizyczne przewody, ponieważ technologie bezprzewodowe nie były wtedy dostępne.

Przyjrzyjmy się ponownie przykładowi inteligentnego termostatu z Lekcji 1.

![Termostat podłączony do Internetu, używający wielu czujników w pomieszczeniach](../../../../../translated_images/pl/telemetry.21e5d8b97649d2eb.webp)

Termostat posiada czujniki temperatury do zbierania telemetrii. Najprawdopodobniej miałby jeden wbudowany czujnik temperatury, a także mógłby łączyć się z wieloma zewnętrznymi czujnikami temperatury za pomocą protokołu bezprzewodowego, takiego jak [Bluetooth Low Energy](https://wikipedia.org/wiki/Bluetooth_Low_Energy) (BLE).

Przykładem danych telemetrii, które mógłby wysyłać, mogłyby być:

| Nazwa | Wartość | Opis |
| ---- | ----- | ----------- |
| `thermostat_temperature` | 18°C | Temperatura zmierzona przez wbudowany czujnik temperatury termostatu |
| `livingroom_temperature` | 19°C | Temperatura zmierzona przez zdalny czujnik temperatury nazwany `livingroom`, aby zidentyfikować pomieszczenie, w którym się znajduje |
| `bedroom_temperature` | 21°C | Temperatura zmierzona przez zdalny czujnik temperatury nazwany `bedroom`, aby zidentyfikować pomieszczenie, w którym się znajduje |

Usługa w chmurze może następnie wykorzystać te dane telemetrii do podejmowania decyzji dotyczących poleceń sterujących ogrzewaniem.

### Wysyłanie telemetrii z urządzenia IoT

Kolejnym krokiem w dodaniu kontroli przez Internet do lampki nocnej jest wysyłanie telemetrii poziomu światła do brokera MQTT w temacie telemetrii.

#### Zadanie - wysyłanie telemetrii z urządzenia IoT

Wyślij telemetrię poziomu światła do brokera MQTT.

Dane są wysyłane w formacie JSON – skrót od JavaScript Object Notation, standardu kodowania danych w tekście za pomocą par klucz/wartość.

✅ Jeśli nie spotkałeś się wcześniej z JSON, możesz dowiedzieć się więcej na [dokumentacji JSON.org](https://www.json.org/).

Wykonaj odpowiedni krok poniżej, aby wysłać telemetrię ze swojego urządzenia do brokera MQTT:

* [Arduino - Wio Terminal](wio-terminal-telemetry.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie IoT](single-board-computer-telemetry.md)

### Odbieranie telemetrii z brokera MQTT

Nie ma sensu wysyłać telemetrii, jeśli nikt jej nie odbiera. Telemetria poziomu światła potrzebuje czegoś, co będzie jej słuchać i przetwarzać dane. Kod 'serwera' to rodzaj kodu, który wdrożysz w usłudze chmurowej jako część większej aplikacji IoT, ale tutaj uruchomisz ten kod lokalnie na swoim komputerze (lub na Pi, jeśli kodujesz bezpośrednio na nim). Kod serwera składa się z aplikacji w Pythonie, która nasłuchuje wiadomości telemetrii przez MQTT z poziomami światła. Później w tej lekcji sprawisz, że odpowie wiadomością polecenia z instrukcjami, czy włączyć, czy wyłączyć diodę LED.

✅ Zrób badania: Co dzieje się z wiadomościami MQTT, jeśli nie ma odbiorcy?

#### Zainstaluj Python i VS Code

Jeśli nie masz zainstalowanego Pythona i VS Code lokalnie, będziesz musiał je zainstalować, aby napisać kod serwera. Jeśli używasz wirtualnego urządzenia IoT lub pracujesz na Raspberry Pi, możesz pominąć ten krok, ponieważ powinieneś już mieć to zainstalowane i skonfigurowane.

##### Zadanie - zainstaluj Python i VS Code

Zainstaluj Python i VS Code.

1. Zainstaluj Python. Odwiedź [stronę pobierania Pythona](https://www.python.org/downloads/), aby uzyskać instrukcje dotyczące instalacji najnowszej wersji Pythona.

1. Zainstaluj Visual Studio Code (VS Code). To edytor, którego będziesz używać do pisania kodu w Pythonie dla wirtualnego urządzenia. Odwiedź [dokumentację VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn), aby uzyskać instrukcje dotyczące instalacji VS Code.
💁 Możesz korzystać z dowolnego edytora lub IDE dla Pythona, jeśli masz ulubione narzędzie, ale lekcje będą zawierały instrukcje oparte na używaniu VS Code.
1. Zainstaluj rozszerzenie Pylance dla VS Code. Jest to rozszerzenie dla VS Code, które zapewnia wsparcie dla języka Python. Zapoznaj się z [dokumentacją rozszerzenia Pylance](https://marketplace.visualstudio.com/items?WT.mc_id=academic-17441-jabenn&itemName=ms-python.vscode-pylance), aby dowiedzieć się, jak je zainstalować w VS Code.

#### Skonfiguruj wirtualne środowisko Pythona

Jedną z potężnych funkcji Pythona jest możliwość instalowania [pakietów pip](https://pypi.org) - są to pakiety kodu napisane przez innych i opublikowane w Internecie. Możesz zainstalować pakiet pip na swoim komputerze za pomocą jednego polecenia, a następnie używać go w swoim kodzie. W tym przypadku użyjesz pip do zainstalowania pakietu do komunikacji przez MQTT.

Domyślnie, gdy instalujesz pakiet, jest on dostępny wszędzie na twoim komputerze, co może prowadzić do problemów z wersjami pakietów - na przykład jedna aplikacja może wymagać jednej wersji pakietu, która przestaje działać po zainstalowaniu nowej wersji dla innej aplikacji. Aby obejść ten problem, możesz użyć [wirtualnego środowiska Pythona](https://docs.python.org/3/library/venv.html), które jest zasadniczo kopią Pythona w dedykowanym folderze. W takim środowisku pakiety pip są instalowane tylko w tym folderze.

##### Zadanie - skonfiguruj wirtualne środowisko Pythona

Skonfiguruj wirtualne środowisko Pythona i zainstaluj pakiety pip dla MQTT.

1. W terminalu lub wierszu poleceń uruchom poniższe polecenia w wybranej lokalizacji, aby utworzyć i przejść do nowego katalogu:

    ```sh
    mkdir nightlight-server
    cd nightlight-server
    ```

1. Teraz uruchom poniższe polecenie, aby utworzyć wirtualne środowisko w folderze `.venv`:

    ```sh
    python3 -m venv .venv
    ```

    > 💁 Musisz wyraźnie wywołać `python3`, aby utworzyć wirtualne środowisko, na wypadek gdybyś miał zainstalowanego Pythona 2 obok Pythona 3 (najnowszej wersji). Jeśli masz zainstalowanego Pythona 2, wywołanie `python` użyje wersji 2 zamiast 3.

1. Aktywuj wirtualne środowisko:

    * Na Windowsie:
        * Jeśli używasz Command Prompt lub Command Prompt przez Windows Terminal, uruchom:

            ```cmd
            .venv\Scripts\activate.bat
            ```

        * Jeśli używasz PowerShell, uruchom:

            ```powershell
            .\.venv\Scripts\Activate.ps1
            ```

    * Na macOS lub Linux uruchom:

        ```cmd
        source ./.venv/bin/activate
        ```

    > 💁 Te polecenia powinny być uruchamiane z tej samej lokalizacji, w której uruchomiłeś polecenie tworzące wirtualne środowisko. Nigdy nie musisz wchodzić do folderu `.venv`, zawsze uruchamiaj polecenie aktywacji i wszelkie polecenia instalacji pakietów lub uruchamiania kodu z folderu, w którym utworzyłeś wirtualne środowisko.

1. Po aktywacji wirtualnego środowiska domyślne polecenie `python` uruchomi wersję Pythona, która została użyta do utworzenia środowiska. Uruchom poniższe polecenie, aby sprawdzić wersję:

    ```sh
    python --version
    ```

    Wynik będzie podobny do poniższego:

    ```output
    (.venv) ➜  nightlight-server python --version
    Python 3.9.1
    ```

    > 💁 Twoja wersja Pythona może być inna - o ile jest to wersja 3.6 lub nowsza, wszystko jest w porządku. Jeśli nie, usuń ten folder, zainstaluj nowszą wersję Pythona i spróbuj ponownie.

1. Uruchom poniższe polecenia, aby zainstalować pakiet pip dla [Paho-MQTT](https://pypi.org/project/paho-mqtt/), popularnej biblioteki MQTT.

    ```sh
    pip install paho-mqtt
    ```

    Ten pakiet pip zostanie zainstalowany tylko w wirtualnym środowisku i nie będzie dostępny poza nim.

#### Napisz kod serwera

Teraz możesz napisać kod serwera w Pythonie.

##### Zadanie - napisz kod serwera

Napisz kod serwera.

1. W terminalu lub wierszu poleceń uruchom poniższe polecenie wewnątrz wirtualnego środowiska, aby utworzyć plik Pythona o nazwie `app.py`:

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

1. Po uruchomieniu VS Code aktywuje ono wirtualne środowisko Pythona. Informacja o tym pojawi się na dolnym pasku stanu:

    ![VS Code pokazujący wybrane wirtualne środowisko](../../../../../translated_images/pl/vscode-virtual-env.8ba42e04c3d533cf.webp)

1. Jeśli terminal VS Code jest już uruchomiony podczas startu VS Code, wirtualne środowisko nie zostanie w nim aktywowane. Najprostszym rozwiązaniem jest zamknięcie terminala za pomocą przycisku **Kill the active terminal instance**:

    ![Przycisk VS Code Kill the active terminal instance](../../../../../translated_images/pl/vscode-kill-terminal.1cc4de7c6f25ee08.webp)

1. Uruchom nowy terminal w VS Code, wybierając *Terminal -> New Terminal* lub naciskając `` CTRL+` ``. Nowy terminal załaduje wirtualne środowisko, a polecenie aktywacji pojawi się w terminalu. Nazwa wirtualnego środowiska (`.venv`) będzie również widoczna w prompt:

    ```output
    ➜  nightlight-server source .venv/bin/activate
    (.venv) ➜  nightlight 
    ```

1. Otwórz plik `app.py` w eksploratorze VS Code i dodaj poniższy kod:

    ```python
    import json
    import time
    
    import paho.mqtt.client as mqtt
    
    id = '<ID>'
    
    client_telemetry_topic = id + '/telemetry'
    client_name = id + 'nightlight_server'
    
    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('test.mosquitto.org')
    
    mqtt_client.loop_start()
    
    def handle_telemetry(client, userdata, message):
        payload = json.loads(message.payload.decode())
        print("Message received:", payload)
    
    mqtt_client.subscribe(client_telemetry_topic)
    mqtt_client.on_message = handle_telemetry
    
    while True:
        time.sleep(2)
    ```

    Zamień `<ID>` w linii 6 na unikalny identyfikator, którego użyłeś podczas tworzenia kodu urządzenia.

    ⚠️ To **musi** być ten sam identyfikator, którego użyłeś na swoim urządzeniu, w przeciwnym razie kod serwera nie będzie subskrybował ani publikował na właściwym temacie.

    Ten kod tworzy klienta MQTT z unikalną nazwą i łączy się z brokerem *test.mosquitto.org*. Następnie uruchamia pętlę przetwarzania, która działa w tle, nasłuchując wiadomości na dowolnych subskrybowanych tematach.

    Klient subskrybuje wiadomości na temacie telemetrycznym i definiuje funkcję, która jest wywoływana, gdy wiadomość zostanie odebrana. Gdy wiadomość telemetryczna zostanie odebrana, funkcja `handle_telemetry` zostanie wywołana, drukując odebraną wiadomość w konsoli.

    Na koniec nieskończona pętla utrzymuje aplikację w działaniu. Klient MQTT nasłuchuje wiadomości w wątku w tle i działa przez cały czas, gdy główna aplikacja działa.

1. W terminalu VS Code uruchom poniższe polecenie, aby uruchomić swoją aplikację w Pythonie:

    ```sh
    python app.py
    ```

    Aplikacja zacznie nasłuchiwać wiadomości z urządzenia IoT.

1. Upewnij się, że twoje urządzenie działa i wysyła wiadomości telemetryczne. Dostosuj poziomy światła wykrywane przez swoje fizyczne lub wirtualne urządzenie. Odbierane wiadomości będą drukowane w terminalu.

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Message received: {'light': 400}
    ```

    Plik `app.py` w wirtualnym środowisku nightlight musi być uruchomiony, aby plik `app.py` w wirtualnym środowisku nightlight-server mógł odbierać wysyłane wiadomości.

> 💁 Ten kod znajdziesz w folderze [code-server/server](../../../../../1-getting-started/lessons/4-connect-internet/code-server/server).

### Jak często należy wysyłać dane telemetryczne?

Jednym z ważnych aspektów danych telemetrycznych jest częstotliwość ich pomiaru i wysyłania. Odpowiedź brzmi - to zależy. Jeśli mierzysz często, możesz szybciej reagować na zmiany, ale zużywasz więcej energii, więcej przepustowości, generujesz więcej danych i potrzebujesz więcej zasobów chmurowych do ich przetwarzania. Musisz mierzyć wystarczająco często, ale nie za często.

Dla termostatu pomiar co kilka minut prawdopodobnie wystarczy, ponieważ temperatura nie zmienia się tak często. Jeśli mierzysz tylko raz dziennie, możesz skończyć z ogrzewaniem domu na nocne temperatury w środku słonecznego dnia, podczas gdy pomiar co sekundę wygeneruje tysiące niepotrzebnie zduplikowanych pomiarów, które obciążą prędkość i przepustowość Internetu użytkownika (problem dla osób z ograniczonymi planami), zużyją więcej energii, co może być problemem dla urządzeń zasilanych bateryjnie, takich jak zdalne czujniki, i zwiększą koszty zasobów chmurowych dostawcy przetwarzających i przechowujących te dane.

Jeśli monitorujesz dane dotyczące maszyny w fabryce, której awaria mogłaby spowodować katastrofalne szkody i miliony dolarów strat, pomiar kilka razy na sekundę może być konieczny. Lepiej zmarnować przepustowość niż przegapić dane telemetryczne wskazujące, że maszyna wymaga zatrzymania i naprawy, zanim się zepsuje.

> 💁 W takiej sytuacji możesz rozważyć użycie urządzenia brzegowego do wstępnego przetwarzania danych telemetrycznych, aby zmniejszyć zależność od Internetu.

### Utrata łączności

Połączenia internetowe mogą być zawodnymi, a przerwy w dostępie są powszechne. Co powinno zrobić urządzenie IoT w takich okolicznościach - czy powinno utracić dane, czy przechować je do czasu przywrócenia łączności? Odpowiedź brzmi - to zależy.

Dla termostatu dane mogą zostać utracone, gdy tylko zostanie wykonany nowy pomiar temperatury. System grzewczy nie przejmuje się, że 20 minut temu było 20,5°C, jeśli teraz jest 19°C - to obecna temperatura decyduje, czy ogrzewanie powinno być włączone czy wyłączone.

Dla maszyn możesz chcieć zachować dane, zwłaszcza jeśli są one używane do analizy trendów. Istnieją modele uczenia maszynowego, które mogą wykrywać anomalie w strumieniach danych, analizując dane z określonego okresu czasu (np. ostatniej godziny) i identyfikując anomalne wartości. Jest to często używane do predykcyjnej konserwacji, szukając wskazówek, że coś może się wkrótce zepsuć, aby można było to naprawić lub wymienić, zanim to nastąpi. Możesz chcieć, aby każde dane telemetryczne maszyny zostały przesłane, aby mogły zostać przetworzone pod kątem wykrywania anomalii, więc gdy urządzenie IoT odzyska połączenie, wyśle wszystkie dane telemetryczne wygenerowane podczas przerwy w dostępie do Internetu.

Projektanci urządzeń IoT powinni również rozważyć, czy urządzenie IoT może być używane podczas przerwy w dostępie do Internetu lub utraty sygnału spowodowanej lokalizacją. Inteligentny termostat powinien być w stanie podejmować pewne ograniczone decyzje dotyczące sterowania ogrzewaniem, jeśli nie może wysyłać danych telemetrycznych do chmury z powodu przerwy.

[![Ten ferrari został "zbrickowany", ponieważ ktoś próbował go zaktualizować pod ziemią, gdzie nie ma zasięgu](../../../../../translated_images/pl/bricked-car.dc38f8efadc6c59d.webp)](https://twitter.com/internetofshit/status/1315736960082808832)

Aby MQTT mogło obsłużyć utratę łączności, kod urządzenia i serwera będzie musiał być odpowiedzialny za zapewnienie dostarczenia wiadomości, jeśli jest to konieczne, na przykład poprzez wymaganie, aby wszystkie wysłane wiadomości były potwierdzane dodatkowymi wiadomościami na temacie odpowiedzi, a jeśli nie, były ręcznie kolejkowane do ponownego wysłania później.

## Polecenia

Polecenia to wiadomości wysyłane przez chmurę do urządzenia, instruujące je, aby coś zrobiło. Najczęściej polega to na generowaniu jakiegoś rodzaju wyjścia za pomocą aktuatora, ale może to być również instrukcja dla samego urządzenia, na przykład aby się zrestartowało lub zebrało dodatkowe dane telemetryczne i zwróciło je jako odpowiedź na polecenie.

![Termostat podłączony do Internetu odbierający polecenie włączenia ogrzewania](../../../../../translated_images/pl/commands.d6c06bbbb3a02cce.webp)

Termostat mógłby otrzymać polecenie z chmury, aby włączyć ogrzewanie. Na podstawie danych telemetrycznych ze wszystkich czujników, jeśli usługa chmurowa zdecyduje, że ogrzewanie powinno być włączone, wysyła odpowiednie polecenie.

### Wysyłanie poleceń do brokera MQTT

Kolejnym krokiem dla naszej nocnej lampki sterowanej przez Internet jest to, aby kod serwera wysyłał polecenie z powrotem do urządzenia IoT, aby sterować światłem na podstawie wykrywanych poziomów światła.

1. Otwórz kod serwera w VS Code.

1. Dodaj poniższą linię po deklaracji `client_telemetry_topic`, aby zdefiniować, na którym temacie wysyłać polecenia:

    ```python
    server_command_topic = id + '/commands'
    ```

1. Dodaj poniższy kod na końcu funkcji `handle_telemetry`:

    ```python
    command = { 'led_on' : payload['light'] < 300 }
    print("Sending message:", command)
    
    client.publish(server_command_topic, json.dumps(command))
    ```

    To wysyła wiadomość JSON na temat polecenia z wartością `led_on` ustawioną na true lub false w zależności od tego, czy światło jest mniejsze niż 300, czy nie. Jeśli światło jest mniejsze niż 300, wysyłane jest true, aby nakazać urządzeniu włączenie diody LED.

1. Uruchom kod jak wcześniej.

1. Dostosuj poziomy światła wykrywane przez swoje fizyczne lub wirtualne urządzenie. Odbierane wiadomości i wysyłane polecenia będą zapisywane w terminalu:

    ```output
    (.venv) ➜  nightlight-server python app.py
    Message received: {'light': 0}
    Sending message: {'led_on': True}
    Message received: {'light': 400}
    Sending message: {'led_on': False}
    ```

> 💁 Telemetria i polecenia są wysyłane na pojedynczym temacie każde. Oznacza to, że telemetria z wielu urządzeń pojawi się na tym samym temacie telemetrycznym, a polecenia do wielu urządzeń pojawią się na tym samym temacie poleceń. Jeśli chciałbyś wysłać polecenie do konkretnego urządzenia, możesz użyć wielu tematów, nazwanych unikalnym identyfikatorem urządzenia, takich jak `/commands/device1`, `/commands/device2`. W ten sposób urządzenie może nasłuchiwać wiadomości przeznaczonych tylko dla niego.

> 💁 Ten kod znajdziesz w folderze [code-commands/server](../../../../../1-getting-started/lessons/4-connect-internet/code-commands/server).

### Obsługa poleceń na urządzeniu IoT

Teraz, gdy polecenia są wysyłane z serwera, możesz dodać kod do urządzenia IoT, aby je obsługiwało i sterowało diodą LED.

Wykonaj odpowiedni krok poniżej, aby nasłuchiwać poleceń z brokera MQTT:

* [Arduino - Wio Terminal](wio-terminal-commands.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie IoT](single-board-computer-commands.md)

Gdy ten kod zostanie napisany i uruchomiony, eksperymentuj z zmianą poziomów światła. Obserwuj dane wyjściowe z serwera i urządzenia oraz obserwuj diodę LED, gdy zmieniasz poziomy światła.

### Utrata łączności

Co powinna zrobić usługa chmurowa, jeśli musi wysłać polecenie do urządzenia IoT, które jest offline? Odpowiedź brzmi - to zależy.

Jeśli najnowsze polecenie zastępuje wcześniejsze, wcześniejsze mogą zostać prawdopodobnie zignorowane. Jeśli usługa chmurowa wysyła polecenie włączenia ogrzewania, a następnie polecenie wyłączenia, polecenie włączenia może zostać zignorowane i nie wysłane ponownie.

Jeśli polecenia muszą być przetwarzane w kolejności, na przykład przesunięcie ramienia robota w górę, a następnie zamknięcie chwytaka, muszą być wysyłane w odpowiedniej kolejności po przywróceniu łączności.

✅ Jak kod urządzenia lub serwera mógłby zapewnić, że polecenia są zawsze wysyłane i obsługiwane w odpowiedniej kolejności za pomocą MQTT, jeśli jest to konieczne?

---

## 🚀 Wyzwanie

Wyzwanie z ostatnich trzech lekcji polegało na wymienieniu jak największej liczby urządzeń IoT, które znajdują się w twoim domu, szkole lub miejscu pracy, oraz określeniu, czy są one oparte na mikrokontrolerach, komputerach jednopłytkowych, czy może na mieszance obu, a także
Dla tych urządzeń zastanów się, jakie wiadomości mogą wysyłać lub odbierać. Jaką telemetrię wysyłają? Jakie wiadomości lub polecenia mogą otrzymywać? Czy uważasz, że są bezpieczne?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/8)

## Przegląd i samodzielna nauka

Przeczytaj więcej o MQTT na [stronie Wikipedii o MQTT](https://wikipedia.org/wiki/MQTT).

Spróbuj uruchomić samodzielnie broker MQTT, korzystając z [Mosquitto](https://www.mosquitto.org), i połącz się z nim za pomocą swojego urządzenia IoT oraz kodu serwera.

> 💁 Wskazówka - domyślnie Mosquitto nie pozwala na anonimowe połączenia (czyli połączenia bez nazwy użytkownika i hasła) oraz nie pozwala na połączenia spoza komputera, na którym działa.
> Możesz to zmienić za pomocą [pliku konfiguracyjnego `mosquitto.conf`](https://www.mosquitto.org/man/mosquitto-conf-5.html) z następującą zawartością:
>
> ```sh
> listener 1883 0.0.0.0
> allow_anonymous true
> ```

## Zadanie

[Porównaj i zestaw MQTT z innymi protokołami komunikacyjnymi](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.