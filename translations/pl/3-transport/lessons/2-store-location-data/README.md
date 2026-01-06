<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e345843ccfeb7261d81500d19c64d476",
  "translation_date": "2025-08-26T07:34:59+00:00",
  "source_file": "3-transport/lessons/2-store-location-data/README.md",
  "language_code": "pl"
}
-->
# Przechowywanie danych o lokalizacji

![Szkicowy przegląd tej lekcji](../../../../../translated_images/lesson-12.ca7f53039712a3ec14ad6474d8445361c84adab643edc53fa6269b77895606bb.pl.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/23)

## Wprowadzenie

W poprzedniej lekcji nauczyłeś się, jak korzystać z czujnika GPS do zbierania danych o lokalizacji. Aby wykorzystać te dane do wizualizacji lokalizacji ciężarówki przewożącej żywność i jej trasy, dane te muszą zostać przesłane do usługi IoT w chmurze, a następnie gdzieś przechowywane.

W tej lekcji dowiesz się o różnych sposobach przechowywania danych IoT oraz jak przechowywać dane z usługi IoT za pomocą kodu bezserwerowego.

W tej lekcji omówimy:

* [Dane strukturalne i niestrukturalne](../../../../../3-transport/lessons/2-store-location-data)
* [Wysyłanie danych GPS do IoT Hub](../../../../../3-transport/lessons/2-store-location-data)
* [Ścieżki gorące, ciepłe i zimne](../../../../../3-transport/lessons/2-store-location-data)
* [Obsługa zdarzeń GPS za pomocą kodu bezserwerowego](../../../../../3-transport/lessons/2-store-location-data)
* [Konta magazynu Azure](../../../../../3-transport/lessons/2-store-location-data)
* [Połączenie kodu bezserwerowego z magazynem](../../../../../3-transport/lessons/2-store-location-data)

## Dane strukturalne i niestrukturalne

Systemy komputerowe przetwarzają dane, które mogą przybierać różne formy i rozmiary. Mogą to być pojedyncze liczby, duże ilości tekstu, filmy, obrazy czy dane IoT. Dane te można zazwyczaj podzielić na dwie kategorie - *strukturalne* i *niestrukturalne*.

* **Dane strukturalne** to dane o dobrze zdefiniowanej, sztywnej strukturze, która się nie zmienia i zazwyczaj odpowiada tabelom danych z relacjami. Przykładem mogą być dane osobowe, takie jak imię, data urodzenia i adres.

* **Dane niestrukturalne** to dane bez dobrze zdefiniowanej, sztywnej struktury, które mogą często zmieniać swoją formę. Przykładem mogą być dokumenty, takie jak teksty pisane czy arkusze kalkulacyjne.

✅ Zrób małe badanie: Czy potrafisz wymyślić inne przykłady danych strukturalnych i niestrukturalnych?

> 💁 Istnieją również dane półstrukturalne, które mają strukturę, ale nie pasują do sztywnych tabel danych.

Dane IoT są zazwyczaj uważane za dane niestrukturalne.

Wyobraź sobie, że dodajesz urządzenia IoT do floty pojazdów dużego gospodarstwa rolnego. Możesz chcieć używać różnych urządzeń dla różnych typów pojazdów. Na przykład:

* Dla pojazdów rolniczych, takich jak traktory, chcesz zbierać dane GPS, aby upewnić się, że pracują na właściwych polach.
* Dla ciężarówek dostawczych przewożących żywność do magazynów chcesz zbierać dane GPS, a także dane o prędkości i przyspieszeniu, aby upewnić się, że kierowca jeździ bezpiecznie, oraz dane o tożsamości kierowcy i rozpoczęciu/zakończeniu pracy, aby zapewnić zgodność z lokalnymi przepisami dotyczącymi godzin pracy.
* Dla ciężarówek chłodniczych chcesz również zbierać dane o temperaturze, aby upewnić się, że żywność nie przegrzewa się ani nie zamarza podczas transportu.

Te dane mogą się stale zmieniać. Na przykład, jeśli urządzenie IoT znajduje się w kabinie ciężarówki, dane, które wysyła, mogą się zmieniać w zależności od zmiany przyczepy, np. wysyłając dane o temperaturze tylko wtedy, gdy używana jest przyczepa chłodnicza.

✅ Jakie inne dane IoT mogłyby być zbierane? Pomyśl o rodzajach ładunków, które mogą przewozić ciężarówki, a także o danych dotyczących konserwacji.

Te dane różnią się w zależności od pojazdu, ale wszystkie są przesyłane do tej samej usługi IoT w celu przetworzenia. Usługa IoT musi być w stanie przetwarzać te niestrukturalne dane, przechowując je w sposób umożliwiający ich wyszukiwanie lub analizę, ale jednocześnie obsługując różne struktury tych danych.

### Magazyn SQL vs NoSQL

Bazy danych to usługi umożliwiające przechowywanie i przeszukiwanie danych. Bazy danych dzielą się na dwa typy - SQL i NoSQL.

#### Bazy danych SQL

Pierwsze bazy danych to Relacyjne Systemy Zarządzania Bazami Danych (RDBMS), znane również jako bazy danych SQL, od języka Structured Query Language (SQL), który służy do interakcji z nimi w celu dodawania, usuwania, aktualizowania lub przeszukiwania danych. Te bazy danych składają się ze schematu - dobrze zdefiniowanego zestawu tabel danych, podobnych do arkusza kalkulacyjnego. Każda tabela ma wiele nazwanych kolumn. Wstawiając dane, dodajesz wiersz do tabeli, umieszczając wartości w każdej z kolumn. To utrzymuje dane w bardzo sztywnej strukturze - chociaż możesz pozostawić kolumny puste, jeśli chcesz dodać nową kolumnę, musisz to zrobić w bazie danych, uzupełniając wartości dla istniejących wierszy. Te bazy danych są relacyjne - jedna tabela może mieć relację z inną.

![Relacyjna baza danych z ID tabeli użytkowników powiązanym z kolumną ID użytkownika w tabeli zakupów oraz ID tabeli produktów powiązanym z kolumną ID produktu w tabeli zakupów](../../../../../translated_images/sql-database.be160f12bfccefd3.pl.png)

Na przykład, jeśli przechowujesz dane osobowe użytkowników w tabeli, miałbyś jakiś wewnętrzny unikalny identyfikator dla każdego użytkownika, który jest używany w wierszu tabeli zawierającej imię i adres użytkownika. Jeśli chciałbyś przechowywać inne szczegóły dotyczące tego użytkownika, takie jak jego zakupy, w innej tabeli, miałbyś jedną kolumnę w nowej tabeli dla identyfikatora tego użytkownika. Gdy wyszukujesz użytkownika, możesz użyć jego identyfikatora, aby uzyskać jego dane osobowe z jednej tabeli i jego zakupy z innej.

Bazy danych SQL są idealne do przechowywania danych strukturalnych i do sytuacji, gdy chcesz zapewnić zgodność danych ze schematem.

✅ Jeśli nigdy wcześniej nie korzystałeś z SQL, poświęć chwilę, aby przeczytać o nim na [stronie SQL w Wikipedii](https://wikipedia.org/wiki/SQL).

Niektóre znane bazy danych SQL to Microsoft SQL Server, MySQL i PostgreSQL.

✅ Zrób małe badanie: Przeczytaj o niektórych z tych baz danych SQL i ich możliwościach.

#### Bazy danych NoSQL

Bazy danych NoSQL nazywane są NoSQL, ponieważ nie mają tej samej sztywnej struktury co bazy danych SQL. Są również znane jako bazy dokumentów, ponieważ mogą przechowywać dane niestrukturalne, takie jak dokumenty.

> 💁 Pomimo swojej nazwy, niektóre bazy danych NoSQL pozwalają na użycie SQL do przeszukiwania danych.

![Dokumenty w folderach w bazie danych NoSQL](../../../../../translated_images/noqsl-database.62d24ccf5b73f60d35c245a8533f1c7147c0928e955b82cb290b2e184bb434df.pl.png)

Bazy danych NoSQL nie mają z góry zdefiniowanego schematu, który ogranicza sposób przechowywania danych. Możesz wstawiać dowolne dane niestrukturalne, zazwyczaj w formacie JSON. Dokumenty te mogą być organizowane w foldery, podobnie jak pliki na komputerze. Każdy dokument może mieć inne pola niż inne dokumenty - na przykład, jeśli przechowujesz dane IoT z pojazdów rolniczych, niektóre mogą mieć pola dla danych z akcelerometru i prędkości, inne mogą mieć pola dla temperatury w przyczepie. Jeśli dodałbyś nowy typ ciężarówki, na przykład z wbudowanymi wagami do śledzenia wagi przewożonych produktów, urządzenie IoT mogłoby dodać to nowe pole, a dane mogłyby być przechowywane bez żadnych zmian w bazie danych.

Niektóre znane bazy danych NoSQL to Azure CosmosDB, MongoDB i CouchDB.

✅ Zrób małe badanie: Przeczytaj o niektórych z tych baz danych NoSQL i ich możliwościach.

W tej lekcji będziesz używać magazynu NoSQL do przechowywania danych IoT.

## Wysyłanie danych GPS do IoT Hub

W poprzedniej lekcji zebrałeś dane GPS z czujnika GPS podłączonego do urządzenia IoT. Aby przechowywać te dane IoT w chmurze, musisz je przesłać do usługi IoT. Ponownie użyjesz Azure IoT Hub, tej samej usługi IoT w chmurze, której używałeś w poprzednim projekcie.

![Wysyłanie telemetrii GPS z urządzenia IoT do IoT Hub](../../../../../translated_images/gps-telemetry-iot-hub.8115335d51cd2c1285d20e9d1b18cf685e59a8e093e7797291ef173445af6f3d.pl.png)

### Zadanie - wysyłanie danych GPS do IoT Hub

1. Utwórz nowy IoT Hub, korzystając z darmowego poziomu.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia IoT Hub z projektu 2, lekcja 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#create-an-iot-service-in-the-cloud), jeśli to konieczne.

    Pamiętaj, aby utworzyć nową grupę zasobów. Nazwij nową grupę zasobów `gps-sensor`, a nowy IoT Hub unikalną nazwą opartą na `gps-sensor`, na przykład `gps-sensor-<twoje imię>`.

    > 💁 Jeśli nadal masz swój IoT Hub z poprzedniego projektu, możesz go ponownie użyć. Pamiętaj, aby użyć nazwy tego IoT Hub i grupy zasobów, w której się znajduje, podczas tworzenia innych usług.

1. Dodaj nowe urządzenie do IoT Hub. Nazwij to urządzenie `gps-sensor`. Pobierz łańcuch połączenia dla urządzenia.

1. Zaktualizuj kod urządzenia, aby wysyłał dane GPS do nowego IoT Hub, używając łańcucha połączenia urządzenia z poprzedniego kroku.

    > ⚠️ Możesz odwołać się do [instrukcji łączenia urządzenia z IoT z projektu 2, lekcja 4](../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md#connect-your-device-to-the-iot-service), jeśli to konieczne.

1. Podczas wysyłania danych GPS, zrób to w formacie JSON w następujący sposób:

    ```json
    {
        "gps" :
        {
            "lat" : <latitude>,
            "lon" : <longitude>
        }
    }
    ```

1. Wysyłaj dane GPS co minutę, aby nie przekroczyć dziennego limitu wiadomości.

Jeśli używasz Wio Terminal, pamiętaj, aby dodać wszystkie niezbędne biblioteki i ustawić czas za pomocą serwera NTP. Twój kod musi również upewnić się, że odczytał wszystkie dane z portu szeregowego przed wysłaniem lokalizacji GPS, używając istniejącego kodu z poprzedniej lekcji. Użyj poniższego kodu, aby skonstruować dokument JSON:

```cpp
DynamicJsonDocument doc(1024);
doc["gps"]["lat"] = gps.location.lat();
doc["gps"]["lon"] = gps.location.lng();
```

Jeśli używasz Wirtualnego urządzenia IoT, pamiętaj, aby zainstalować wszystkie potrzebne biblioteki, korzystając z wirtualnego środowiska.

Dla Raspberry Pi i Wirtualnego urządzenia IoT użyj istniejącego kodu z poprzedniej lekcji, aby uzyskać wartości szerokości i długości geograficznej, a następnie wyślij je w odpowiednim formacie JSON za pomocą poniższego kodu:

```python
message_json = { "gps" : { "lat":lat, "lon":lon } }
print("Sending telemetry", message_json)
message = Message(json.dumps(message_json))
```

> 💁 Ten kod znajdziesz w folderze [code/wio-terminal](../../../../../3-transport/lessons/2-store-location-data/code/wio-terminal), [code/pi](../../../../../3-transport/lessons/2-store-location-data/code/pi) lub [code/virtual-device](../../../../../3-transport/lessons/2-store-location-data/code/virtual-device).

Uruchom kod urządzenia i upewnij się, że wiadomości trafiają do IoT Hub, używając polecenia CLI `az iot hub monitor-events`.

## Ścieżki gorące, ciepłe i zimne

Dane przesyłane z urządzenia IoT do chmury nie zawsze są przetwarzane w czasie rzeczywistym. Niektóre dane wymagają przetwarzania w czasie rzeczywistym, inne mogą być przetwarzane z niewielkim opóźnieniem, a jeszcze inne mogą być przetwarzane znacznie później. Przepływ danych do różnych usług przetwarzających dane w różnym czasie określa się jako ścieżki gorące, ciepłe i zimne.

### Ścieżka gorąca

Ścieżka gorąca odnosi się do danych, które muszą być przetwarzane w czasie rzeczywistym lub niemal w czasie rzeczywistym. Używałbyś danych ze ścieżki gorącej do alertów, takich jak powiadomienia o zbliżaniu się pojazdu do magazynu lub o zbyt wysokiej temperaturze w ciężarówce chłodniczej.

Aby korzystać z danych ze ścieżki gorącej, twój kod reagowałby na zdarzenia natychmiast po ich odebraniu przez usługi w chmurze.

### Ścieżka ciepła

Ścieżka ciepła odnosi się do danych, które mogą być przetwarzane krótko po ich odebraniu, na przykład do raportowania lub krótkoterminowej analizy. Używałbyś danych ze ścieżki ciepłej do codziennych raportów o przebiegu pojazdów, korzystając z danych zebranych poprzedniego dnia.

Dane ze ścieżki ciepłej są przechowywane zaraz po ich odebraniu przez usługę w chmurze w jakimś rodzaju magazynu, który można szybko uzyskać.

### Ścieżka zimna

Ścieżka zimna odnosi się do danych historycznych, przechowywanych długoterminowo, które mogą być przetwarzane w dowolnym momencie. Na przykład, możesz użyć ścieżki zimnej do uzyskania rocznych raportów o przebiegu pojazdów lub przeprowadzenia analizy tras w celu znalezienia najbardziej optymalnej trasy zmniejszającej koszty paliwa.

Dane ze ścieżki zimnej są przechowywane w hurtowniach danych - bazach danych zaprojektowanych do przechowywania dużych ilości danych, które nigdy się nie zmieniają i mogą być szybko i łatwo przeszukiwane. Zazwyczaj w aplikacji chmurowej uruchamiałbyś regularne zadanie, które w określonym czasie każdego dnia, tygodnia lub miesiąca przenosi dane z magazynu ścieżki ciepłej do hurtowni danych.

✅ Pomyśl o danych, które zebrałeś do tej pory w tych lekcjach. Czy są to dane ze ścieżki gorącej, ciepłej czy zimnej?

## Obsługa zdarzeń GPS za pomocą kodu bezserwerowego

Gdy dane trafiają do IoT Hub, możesz napisać kod bezserwerowy, który będzie nasłuchiwał zdarzeń publikowanych na zgodnym z Event-Hub punkcie końcowym. To jest ścieżka ciepła - te dane zostaną przechowane i wykorzystane w następnej lekcji do raportowania trasy.

![Wysyłanie telemetrii GPS z urządzenia IoT do IoT Hub, a następnie do Azure Functions za pomocą wyzwalacza Event Hub](../../../../../translated_images/gps-telemetry-iot-hub-functions.24d3fa5592455e9f4e2fe73856b40c3915a292b90263c31d652acfd976cfedd8.pl.png)

### Zadanie - obsługa zdarzeń GPS za pomocą kodu bezserwerowego

1. Utwórz aplikację Azure Functions za pomocą CLI Azure Functions. Użyj środowiska wykonawczego Python i utwórz ją w folderze o nazwie `gps-trigger`, używając tej samej nazwy dla projektu aplikacji Functions. Upewnij się, że tworzysz wirtualne środowisko do tego celu.
> ⚠️ Możesz odwołać się do [instrukcji dotyczących tworzenia projektu Azure Functions z projektu 2, lekcji 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-a-serverless-application), jeśli zajdzie taka potrzeba.
1. Dodaj wyzwalacz zdarzeń IoT Hub, który korzysta z punktu końcowego zgodnego z Event Hub w IoT Hub.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia wyzwalacza zdarzeń IoT Hub z projektu 2, lekcja 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger), jeśli będzie to potrzebne.

1. Ustaw łańcuch połączenia punktu końcowego zgodnego z Event Hub w pliku `local.settings.json` i użyj klucza dla tego wpisu w pliku `function.json`.

1. Użyj aplikacji Azurite jako lokalnego emulatora pamięci.

1. Uruchom aplikację funkcji, aby upewnić się, że odbiera zdarzenia z Twojego urządzenia GPS. Upewnij się, że Twoje urządzenie IoT również działa i wysyła dane GPS.

    ```output
    Python EventHub trigger processed an event: {"gps": {"lat": 47.73481, "lon": -122.25701}}
    ```

## Konta magazynu Azure

![Logo Azure Storage](../../../../../translated_images/azure-storage-logo.605c0f602c640d482a80f1b35a2629a32d595711b7ab1d7ceea843250615ff32.pl.png)

Konta magazynu Azure to uniwersalna usługa przechowywania danych, która umożliwia przechowywanie danych na różne sposoby. Możesz przechowywać dane jako obiekty blob, w kolejkach, w tabelach lub jako pliki – wszystko jednocześnie.

### Magazyn obiektów blob

Słowo *Blob* oznacza duże obiekty binarne, ale stało się określeniem dla wszelkich danych niestrukturalnych. W magazynie obiektów blob możesz przechowywać dowolne dane, od dokumentów JSON zawierających dane IoT, po pliki graficzne i wideo. Magazyn obiektów blob wprowadza pojęcie *kontenerów*, czyli nazwanych zbiorników, w których można przechowywać dane, podobnie jak tabele w relacyjnej bazie danych. Kontenery mogą zawierać jeden lub więcej folderów do przechowywania obiektów blob, a każdy folder może zawierać inne foldery, podobnie jak pliki są przechowywane na dysku twardym komputera.

W tej lekcji użyjesz magazynu obiektów blob do przechowywania danych IoT.

✅ Zrób badania: Przeczytaj o [Azure Blob Storage](https://docs.microsoft.com/azure/storage/blobs/storage-blobs-overview?WT.mc_id=academic-17441-jabenn)

### Magazyn tabel

Magazyn tabel pozwala przechowywać dane półstrukturalne. Jest to w rzeczywistości baza danych NoSQL, więc nie wymaga z góry zdefiniowanego zestawu tabel, ale jest zaprojektowany do przechowywania danych w jednej lub więcej tabelach, z unikalnymi kluczami definiującymi każdy wiersz.

✅ Zrób badania: Przeczytaj o [Azure Table Storage](https://docs.microsoft.com/azure/storage/tables/table-storage-overview?WT.mc_id=academic-17441-jabenn)

### Magazyn kolejek

Magazyn kolejek pozwala przechowywać wiadomości o rozmiarze do 64 KB w kolejce. Możesz dodawać wiadomości na końcu kolejki i odczytywać je z przodu. Kolejki przechowują wiadomości bezterminowo, o ile jest dostępne miejsce w magazynie, co pozwala na ich długoterminowe przechowywanie i odczyt w razie potrzeby. Na przykład, jeśli chcesz uruchamiać miesięczne zadanie przetwarzania danych GPS, możesz codziennie dodawać je do kolejki, a na koniec miesiąca przetworzyć wszystkie wiadomości z kolejki.

✅ Zrób badania: Przeczytaj o [Azure Queue Storage](https://docs.microsoft.com/azure/storage/queues/storage-queues-introduction?WT.mc_id=academic-17441-jabenn)

### Magazyn plików

Magazyn plików umożliwia przechowywanie plików w chmurze, a aplikacje lub urządzenia mogą się z nim łączyć za pomocą standardowych protokołów. Możesz zapisywać pliki w magazynie plików, a następnie zamontować go jako dysk na swoim komputerze PC lub Mac.

✅ Zrób badania: Przeczytaj o [Azure File Storage](https://docs.microsoft.com/azure/storage/files/storage-files-introduction?WT.mc_id=academic-17441-jabenn)

## Połącz swój kod bezserwerowy z magazynem

Twoja aplikacja funkcji musi teraz połączyć się z magazynem obiektów blob, aby przechowywać wiadomości z IoT Hub. Istnieją dwa sposoby, aby to zrobić:

* Wewnątrz kodu funkcji, połącz się z magazynem obiektów blob za pomocą SDK dla Pythona i zapisz dane jako obiekty blob.
* Użyj powiązania wyjściowego funkcji, aby powiązać wartość zwracaną funkcji z magazynem obiektów blob i automatycznie zapisać obiekt blob.

W tej lekcji użyjesz SDK dla Pythona, aby zobaczyć, jak pracować z magazynem obiektów blob.

![Wysyłanie telemetrii GPS z urządzenia IoT do IoT Hub, następnie do Azure Functions za pomocą wyzwalacza Event Hub, a następnie zapisywanie jej w magazynie obiektów blob](../../../../../translated_images/save-telemetry-to-storage-from-functions.ed3b1820980097f1.pl.png)

Dane zostaną zapisane jako obiekt JSON w następującym formacie:

```json
{
    "device_id": <device_id>,
    "timestamp" : <time>,
    "gps" :
    {
        "lat" : <latitude>,
        "lon" : <longitude>
    }
}
```

### Zadanie - połącz swój kod bezserwerowy z magazynem

1. Utwórz konto magazynu Azure. Nazwij je np. `gps<twoje_imie>`.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia konta magazynu z projektu 2, lekcja 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources), jeśli będzie to potrzebne.

    Jeśli masz już konto magazynu z poprzedniego projektu, możesz je ponownie wykorzystać.

    > 💁 Będziesz mógł użyć tego samego konta magazynu do wdrożenia aplikacji Azure Functions później w tej lekcji.

1. Uruchom następujące polecenie, aby uzyskać łańcuch połączenia dla konta magazynu:

    ```sh
    az storage account show-connection-string --output table \
                                              --name <storage_name>
    ```

    Zamień `<storage_name>` na nazwę konta magazynu, które utworzyłeś w poprzednim kroku.

1. Dodaj nowy wpis do pliku `local.settings.json` dla łańcucha połączenia konta magazynu, używając wartości z poprzedniego kroku. Nazwij go `STORAGE_CONNECTION_STRING`.

1. Dodaj następujące wpisy do pliku `requirements.txt`, aby zainstalować pakiety Pip dla magazynu Azure:

    ```sh
    azure-storage-blob
    ```

    Zainstaluj pakiety z tego pliku w swoim wirtualnym środowisku.

    > Jeśli pojawi się błąd, zaktualizuj wersję Pip w swoim wirtualnym środowisku do najnowszej wersji za pomocą następującego polecenia, a następnie spróbuj ponownie:
    >
    > ```sh
    > pip install --upgrade pip
    > ```

1. W pliku `__init__.py` dla `iot-hub-trigger` dodaj następujące instrukcje importu:

    ```python
    import json
    import os
    import uuid
    from azure.storage.blob import BlobServiceClient, PublicAccess
    ```

    Moduł systemowy `json` będzie używany do odczytu i zapisu JSON, moduł `os` do odczytu łańcucha połączenia, a moduł `uuid` do generowania unikalnego identyfikatora dla odczytu GPS.

    Pakiet `azure.storage.blob` zawiera SDK dla Pythona do pracy z magazynem obiektów blob.

1. Przed metodą `main` dodaj następującą funkcję pomocniczą:

    ```python
    def get_or_create_container(name):
        connection_str = os.environ['STORAGE_CONNECTION_STRING']
        blob_service_client = BlobServiceClient.from_connection_string(connection_str)
    
        for container in blob_service_client.list_containers():
            if container.name == name:
                return blob_service_client.get_container_client(container.name)
        
        return blob_service_client.create_container(name, public_access=PublicAccess.Container)
    ```

    SDK dla obiektów blob w Pythonie nie ma metody pomocniczej do tworzenia kontenera, jeśli nie istnieje. Ten kod załaduje łańcuch połączenia z pliku `local.settings.json` (lub ustawień aplikacji po wdrożeniu w chmurze), a następnie utworzy klasę `BlobServiceClient`, aby współpracować z kontem magazynu obiektów blob. Następnie przechodzi przez wszystkie kontenery w koncie magazynu obiektów blob, szukając takiego o podanej nazwie – jeśli znajdzie, zwróci klasę `ContainerClient`, która może współpracować z kontenerem w celu tworzenia obiektów blob. Jeśli nie znajdzie, kontener zostanie utworzony, a klient dla nowego kontenera zostanie zwrócony.

    Po utworzeniu nowego kontenera, przyznawany jest publiczny dostęp do zapytań o obiekty blob w kontenerze. Będzie to używane w następnej lekcji do wizualizacji danych GPS na mapie.

1. W przeciwieństwie do wilgotności gleby, w tym kodzie chcemy przechowywać każde zdarzenie, więc dodaj następujący kod wewnątrz pętli `for event in events:` w funkcji `main`, poniżej instrukcji `logging`:

    ```python
    device_id = event.iothub_metadata['connection-device-id']
    blob_name = f'{device_id}/{str(uuid.uuid1())}.json'
    ```

    Ten kod pobiera identyfikator urządzenia z metadanych zdarzenia, a następnie używa go do utworzenia nazwy obiektu blob. Obiekty blob mogą być przechowywane w folderach, a identyfikator urządzenia będzie używany jako nazwa folderu, więc każde urządzenie będzie miało wszystkie swoje zdarzenia GPS w jednym folderze. Nazwa obiektu blob to ten folder, a następnie nazwa dokumentu, oddzielone ukośnikami, podobnie jak ścieżki w systemach Linux i macOS (podobnie jak w Windows, ale Windows używa odwrotnych ukośników). Nazwa dokumentu to unikalny identyfikator generowany za pomocą modułu `uuid` w Pythonie, z rozszerzeniem pliku `json`.

    Na przykład, dla identyfikatora urządzenia `gps-sensor`, nazwa obiektu blob może wyglądać tak: `gps-sensor/a9487ac2-b9cf-11eb-b5cd-1e00621e3648.json`.

1. Dodaj następujący kod poniżej tego:

    ```python
    container_client = get_or_create_container('gps-data')
    blob = container_client.get_blob_client(blob_name)
    ```

    Ten kod pobiera klienta kontenera za pomocą klasy pomocniczej `get_or_create_container`, a następnie uzyskuje obiekt klienta obiektu blob za pomocą nazwy obiektu blob. Klienci obiektów blob mogą odnosić się do istniejących obiektów blob lub, jak w tym przypadku, do nowych obiektów blob.

1. Dodaj następujący kod po tym:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    blob_body = {
        'device_id' : device_id,
        'timestamp' : event.iothub_metadata['enqueuedtime'],
        'gps': event_body['gps']
    }
    ```

    Ten kod buduje treść obiektu blob, który zostanie zapisany w magazynie obiektów blob. Jest to dokument JSON zawierający identyfikator urządzenia, czas wysłania telemetrii do IoT Hub oraz współrzędne GPS z telemetrii.

    > 💁 Ważne jest, aby używać czasu zakolejkowania wiadomości zamiast bieżącego czasu, aby uzyskać czas, w którym wiadomość została wysłana. Może ona znajdować się w hubie przez jakiś czas, zanim zostanie odebrana, jeśli aplikacja funkcji nie działa.

1. Dodaj następujący kod poniżej tego:

    ```python
    logging.info(f'Writing blob to {blob_name} - {blob_body}')
    blob.upload_blob(json.dumps(blob_body).encode('utf-8'))
    ```

    Ten kod loguje, że obiekt blob ma zostać zapisany wraz z jego szczegółami, a następnie przesyła treść obiektu blob jako zawartość nowego obiektu blob.

1. Uruchom aplikację funkcji. Zobaczysz, że obiekty blob są zapisywane dla wszystkich zdarzeń GPS w wyjściu:

    ```output
    [2021-05-21T01:31:14.325Z] Python EventHub trigger processed an event: {"gps": {"lat": 47.73092, "lon": -122.26206}}
    ...
    [2021-05-21T01:31:14.351Z] Writing blob to gps-sensor/4b6089fe-ba8d-11eb-bc7b-1e00621e3648.json - {'device_id': 'gps-sensor', 'timestamp': '2021-05-21T00:57:53.878Z', 'gps': {'lat': 47.73092, 'lon': -122.26206}}
    ```

    > 💁 Upewnij się, że nie uruchamiasz jednocześnie monitora zdarzeń IoT Hub.

> 💁 Ten kod znajdziesz w folderze [code/functions](../../../../../3-transport/lessons/2-store-location-data/code/functions).

### Zadanie - zweryfikuj przesłane obiekty blob

1. Aby zobaczyć utworzone obiekty blob, możesz użyć [Azure Storage Explorer](https://azure.microsoft.com/features/storage-explorer/?WT.mc_id=academic-17441-jabenn), darmowego narzędzia umożliwiającego przeglądanie i zarządzanie kontami magazynu, lub CLI.

    1. Aby użyć CLI, najpierw potrzebujesz klucza konta. Uruchom następujące polecenie, aby uzyskać ten klucz:

        ```sh
        az storage account keys list --output table \
                                     --account-name <storage_name>
        ```

        Zamień `<storage_name>` na nazwę konta magazynu.

        Skopiuj wartość `key1`.

    1. Uruchom następujące polecenie, aby wyświetlić listę obiektów blob w kontenerze:

        ```sh
        az storage blob list --container-name gps-data \
                             --output table \
                             --account-name <storage_name> \
                             --account-key <key1>
        ```

        Zamień `<storage_name>` na nazwę konta magazynu, a `<key1>` na wartość `key1`, którą skopiowałeś w poprzednim kroku.

        To wyświetli listę wszystkich obiektów blob w kontenerze:

        ```output
        Name                                                  Blob Type    Blob Tier    Length    Content Type              Last Modified              Snapshot
        ----------------------------------------------------  -----------  -----------  --------  ------------------------  -------------------------  ----------
        gps-sensor/1810d55e-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:27+00:00
        gps-sensor/18293e46-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1844549c-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        gps-sensor/1894d714-b9cf-11eb-9f5b-1e00621e3648.json  BlockBlob    Hot          45        application/octet-stream  2021-05-21T00:54:28+00:00
        ```

    1. Pobierz jeden z obiektów blob za pomocą następującego polecenia:

        ```sh
        az storage blob download --container-name gps-data \
                                 --account-name <storage_name> \
                                 --account-key <key1> \
                                 --name <blob_name> \
                                 --file <file_name>
        ```

        Zamień `<storage_name>` na nazwę konta magazynu, a `<key1>` na wartość `key1`, którą skopiowałeś w poprzednim kroku.

        Zamień `<blob_name>` na pełną nazwę z kolumny `Name` w wyjściu poprzedniego kroku, włącznie z nazwą folderu. Zamień `<file_name>` na nazwę lokalnego pliku, do którego chcesz zapisać obiekt blob.

    Po pobraniu możesz otworzyć plik JSON w VS Code i zobaczysz obiekt blob zawierający szczegóły lokalizacji GPS:

    ```json
    {"device_id": "gps-sensor", "timestamp": "2021-05-21T00:57:53.878Z", "gps": {"lat": 47.73092, "lon": -122.26206}}
    ```

### Zadanie - wdroż swoją aplikację funkcji w chmurze

Teraz, gdy Twoja aplikacja funkcji działa, możesz ją wdrożyć w chmurze.

1. Utwórz nową aplikację Azure Functions, używając konta magazynu, które utworzyłeś wcześniej. Nazwij ją np. `gps-sensor-` i dodaj unikalny identyfikator na końcu, np. losowe słowa lub swoje imię.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia aplikacji Functions z projektu 2, lekcja 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---create-the-cloud-resources), jeśli będzie to potrzebne.

1. Prześlij wartości `IOT_HUB_CONNECTION_STRING` i `STORAGE_CONNECTION_STRING` do ustawień aplikacji.

    > ⚠️ Możesz odwołać się do [instrukcji przesyłania ustawień aplikacji z projektu 2, lekcja 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings), jeśli będzie to potrzebne.

1. Wdróż swoją lokalną aplikację Functions w chmurze.
> ⚠️ Możesz odwołać się do [instrukcji wdrażania aplikacji Functions z projektu 2, lekcji 5](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud), jeśli zajdzie taka potrzeba.
## 🚀 Wyzwanie

Dane GPS nie są idealnie dokładne, a wykrywane lokalizacje mogą być przesunięte o kilka metrów, a nawet więcej, szczególnie w tunelach i obszarach z wysokimi budynkami.

Zastanów się, jak nawigacja satelitarna mogłaby sobie z tym poradzić? Jakie dane posiada Twój system nawigacji, które pozwoliłyby mu lepiej przewidywać Twoją lokalizację?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/24)

## Przegląd i samodzielna nauka

* Przeczytaj o danych strukturalnych na [stronie o modelu danych na Wikipedii](https://wikipedia.org/wiki/Data_model)
* Przeczytaj o danych półstrukturalnych na [stronie o danych półstrukturalnych na Wikipedii](https://wikipedia.org/wiki/Semi-structured_data)
* Przeczytaj o danych niestrukturalnych na [stronie o danych niestrukturalnych na Wikipedii](https://wikipedia.org/wiki/Unstructured_data)
* Dowiedz się więcej o Azure Storage i różnych typach przechowywania danych w [dokumentacji Azure Storage](https://docs.microsoft.com/azure/storage/?WT.mc_id=academic-17441-jabenn)

## Zadanie

[Zbadaj powiązania funkcji](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.