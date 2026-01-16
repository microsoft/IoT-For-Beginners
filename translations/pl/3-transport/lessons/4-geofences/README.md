<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "078ae664c7b686bf069545e9a5fc95b2",
  "translation_date": "2025-08-26T07:27:50+00:00",
  "source_file": "3-transport/lessons/4-geofences/README.md",
  "language_code": "pl"
}
-->
# Geofences

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-14.63980c5150ae3c153e770fb71d044c1845dce79248d86bed9fc525adf3ede73c.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ten film przedstawia przegląd geofencing i sposobu ich użycia w Azure Maps, tematy, które zostaną omówione w tej lekcji:

[![Geofencing z Azure Maps w programie Microsoft Developer IoT](https://img.youtube.com/vi/nsrgYhaYNVY/0.jpg)](https://www.youtube.com/watch?v=nsrgYhaYNVY)

> 🎥 Kliknij obraz powyżej, aby obejrzeć film

## Quiz przed lekcją

[Quiz przed lekcją](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/27)

## Wprowadzenie

W ostatnich trzech lekcjach używałeś IoT do lokalizowania ciężarówek przewożących produkty z Twojej farmy do centrum przetwarzania. Zarejestrowałeś dane GPS, wysłałeś je do chmury, aby je przechować, i zwizualizowałeś je na mapie. Kolejnym krokiem w zwiększaniu efektywności Twojego łańcucha dostaw jest otrzymanie alertu, gdy ciężarówka zbliża się do centrum przetwarzania, aby załoga potrzebna do rozładunku mogła być gotowa z wózkami widłowymi i innym sprzętem, gdy pojazd dotrze na miejsce. Dzięki temu rozładunek będzie szybki, a Ty nie będziesz płacić za czas oczekiwania ciężarówki i kierowcy.

W tej lekcji dowiesz się o geofencing - zdefiniowanych obszarach geograficznych, takich jak obszar w promieniu 2 km od centrum przetwarzania, oraz o tym, jak sprawdzić, czy współrzędne GPS znajdują się wewnątrz czy na zewnątrz geofence, aby zobaczyć, czy Twój czujnik GPS dotarł do obszaru lub go opuścił.

W tej lekcji omówimy:

* [Czym są geofencing](../../../../../3-transport/lessons/4-geofences)
* [Definiowanie geofence](../../../../../3-transport/lessons/4-geofences)
* [Testowanie punktów względem geofence](../../../../../3-transport/lessons/4-geofences)
* [Użycie geofence w kodzie bezserwerowym](../../../../../3-transport/lessons/4-geofences)

> 🗑 To jest ostatnia lekcja w tym projekcie, więc po jej ukończeniu i wykonaniu zadania, nie zapomnij posprzątać swoich usług w chmurze. Usługi będą potrzebne do ukończenia zadania, więc upewnij się, że najpierw je wykonasz.
>
> Jeśli potrzebujesz instrukcji, zapoznaj się z [przewodnikiem czyszczenia projektu](../../../clean-up.md).

## Czym są Geofencing

Geofence to wirtualny obwód dla rzeczywistego obszaru geograficznego. Geofencing mogą być okręgami zdefiniowanymi jako punkt i promień (na przykład okrąg o średnicy 100 m wokół budynku) lub wielokątami obejmującymi obszar, taki jak strefa szkolna, granice miasta, kampus uniwersytecki lub biurowy.

![Przykłady geofence pokazujące okrągły geofence wokół sklepu Microsoft oraz wielokąt wokół zachodniego kampusu Microsoft](../../../../../translated_images/pl/geofence-examples.172fbc534665769f6e1a1ddcf75e3b25183cd10354c80cc603ba44b635390e1a.png)

> 💁 Mogłeś już korzystać z geofence, nie zdając sobie z tego sprawy. Jeśli ustawiłeś przypomnienie w aplikacji przypomnień iOS lub Google Keep na podstawie lokalizacji, użyłeś geofence. Te aplikacje ustawiają geofence na podstawie podanej lokalizacji i powiadamiają Cię, gdy Twój telefon wejdzie w obszar geofence.

Istnieje wiele powodów, dla których warto wiedzieć, czy pojazd znajduje się wewnątrz czy na zewnątrz geofence:

* Przygotowanie do rozładunku - otrzymanie powiadomienia, że pojazd dotarł na miejsce, pozwala załodze przygotować się do rozładunku, skracając czas oczekiwania pojazdu. Dzięki temu kierowca może wykonać więcej dostaw w ciągu dnia przy mniejszym czasie oczekiwania.
* Zgodność podatkowa - niektóre kraje, takie jak Nowa Zelandia, pobierają podatki drogowe od pojazdów z silnikiem diesla na podstawie ich wagi, ale tylko podczas jazdy po drogach publicznych. Korzystanie z geofence pozwala śledzić przebyty dystans na drogach publicznych w porównaniu do prywatnych, takich jak farmy czy obszary leśne.
* Monitorowanie kradzieży - jeśli pojazd powinien pozostać w określonym obszarze, na przykład na farmie, a opuści geofence, może zostać skradziony.
* Zgodność lokalizacyjna - niektóre części miejsca pracy, farmy lub fabryki mogą być niedostępne dla określonych pojazdów, na przykład utrzymanie pojazdów przewożących sztuczne nawozy i pestycydy z dala od pól uprawiających produkty organiczne. Jeśli geofence zostanie naruszony, pojazd znajduje się poza zgodnością, a kierowca może zostać powiadomiony.

✅ Czy potrafisz wymyślić inne zastosowania geofence?

Azure Maps, usługa, której używałeś w poprzedniej lekcji do wizualizacji danych GPS, pozwala definiować geofence, a następnie sprawdzać, czy punkt znajduje się wewnątrz czy na zewnątrz geofence.

## Definiowanie geofence

Geofencing są definiowane za pomocą GeoJSON, tak samo jak punkty dodane do mapy w poprzedniej lekcji. W tym przypadku, zamiast być `FeatureCollection` wartości `Point`, jest to `FeatureCollection` zawierające `Polygon`.

```json
{
   "type": "FeatureCollection",
   "features": [
     {
       "type": "Feature",
       "geometry": {
         "type": "Polygon",
         "coordinates": [
           [
             [
               -122.13393688201903,
               47.63829579223815
             ],
             [
               -122.13389128446579,
               47.63782047131512
             ],
             [
               -122.13240802288054,
               47.63783312249837
             ],
             [
               -122.13238388299942,
               47.63829037035086
             ],
             [
               -122.13393688201903,
               47.63829579223815
             ]
           ]
         ]
       },
       "properties": {
         "geometryId": "1"
       }
     }
   ]
}
```

Każdy punkt na wielokącie jest definiowany jako para długości i szerokości geograficznej w tablicy, a te punkty znajdują się w tablicy ustawionej jako `coordinates`. W przypadku `Point` w poprzedniej lekcji, `coordinates` było tablicą zawierającą 2 wartości, szerokość i długość geograficzną, dla `Polygon` jest to tablica tablic zawierających 2 wartości, długość i szerokość geograficzną.

> 💁 Pamiętaj, GeoJSON używa `długość, szerokość` dla punktów, a nie `szerokość, długość`

Tablica współrzędnych wielokąta zawsze ma o 1 więcej wpis niż liczba punktów na wielokącie, z ostatnim wpisem będącym takim samym jak pierwszy, zamykającym wielokąt. Na przykład dla prostokąta byłoby 5 punktów.

![Prostokąt z współrzędnymi](../../../../../translated_images/pl/polygon-points.302193da381cb415.webp)

Na powyższym obrazku znajduje się prostokąt. Współrzędne wielokąta zaczynają się w lewym górnym rogu na 47,-122, następnie przesuwają się w prawo do 47,-121, potem w dół do 46,-121, następnie w lewo do 46, -122, a potem z powrotem do punktu początkowego na 47, -122. Daje to wielokąt o 5 punktach - lewy górny, prawy górny, prawy dolny, lewy dolny, a następnie lewy górny, aby go zamknąć.

✅ Spróbuj stworzyć wielokąt GeoJSON wokół swojego domu lub szkoły. Użyj narzędzia takiego jak [GeoJSON.io](https://geojson.io/).

### Zadanie - definiowanie geofence

Aby użyć geofence w Azure Maps, najpierw musi zostać przesłany do Twojego konta Azure Maps. Po przesłaniu otrzymasz unikalny identyfikator, który możesz użyć do testowania punktu względem geofence. Aby przesłać geofencing do Azure Maps, musisz użyć web API map. Możesz wywołać web API Azure Maps za pomocą narzędzia o nazwie [curl](https://curl.se).

> 🎓 Curl to narzędzie wiersza poleceń do wykonywania żądań do punktów końcowych w sieci

1. Jeśli używasz Linuxa, macOS lub najnowszej wersji Windows 10, prawdopodobnie masz curl już zainstalowany. Uruchom następujące polecenie z terminala lub wiersza poleceń, aby sprawdzić:

    ```sh
    curl --version
    ```

    Jeśli nie widzisz informacji o wersji curl, będziesz musiał go zainstalować ze [strony pobierania curl](https://curl.se/download.html).

    > 💁 Jeśli masz doświadczenie z Postmanem, możesz go użyć zamiast curl, jeśli wolisz.

1. Utwórz plik GeoJSON zawierający wielokąt. Będziesz testować go za pomocą swojego czujnika GPS, więc stwórz wielokąt wokół swojej obecnej lokalizacji. Możesz go stworzyć ręcznie, edytując podany powyżej przykład GeoJSON, lub użyć narzędzia takiego jak [GeoJSON.io](https://geojson.io/).

    GeoJSON musi zawierać `FeatureCollection`, zawierające `Feature` z `geometry` typu `Polygon`.

    Musisz również dodać element `properties` na tym samym poziomie co element `geometry`, a ten musi zawierać `geometryId`:

    ```json
    "properties": {
        "geometryId": "1"
    }
    ```

    Jeśli używasz [GeoJSON.io](https://geojson.io/), będziesz musiał ręcznie dodać ten element do pustego `properties`, albo po pobraniu pliku JSON, albo w edytorze JSON w aplikacji.

    Ten `geometryId` musi być unikalny w tym pliku. Możesz przesłać wiele geofencing jako wiele `Features` w `FeatureCollection` w tym samym pliku GeoJSON, pod warunkiem, że każdy z nich ma inny `geometryId`. Wielokąty mogą mieć ten sam `geometryId`, jeśli są przesyłane z innego pliku w innym czasie.

1. Zapisz ten plik jako `geofence.json` i przejdź do miejsca, w którym został zapisany w terminalu lub konsoli.

1. Uruchom następujące polecenie curl, aby utworzyć GeoFence:

    ```sh
    curl --request POST 'https://atlas.microsoft.com/mapData/upload?api-version=1.0&dataFormat=geojson&subscription-key=<subscription_key>' \
         --header 'Content-Type: application/json' \
         --include \
         --data @geofence.json
    ```

    Zamień `<subscription_key>` w URL na klucz API dla swojego konta Azure Maps.

    URL jest używany do przesyłania danych map za pomocą API `https://atlas.microsoft.com/mapData/upload`. Wywołanie zawiera parametr `api-version`, aby określić, której wersji API Azure Maps użyć, co pozwala na zmiany w API w czasie przy zachowaniu kompatybilności wstecznej. Format danych przesyłanych jest ustawiony na `geojson`.

    To uruchomi żądanie POST do API przesyłania i zwróci listę nagłówków odpowiedzi, która zawiera nagłówek o nazwie `location`.

    ```output
    content-type: application/json
    location: https://us.atlas.microsoft.com/mapData/operations/1560ced6-3a80-46f2-84b2-5b1531820eab?api-version=1.0
    x-ms-azuremaps-region: West US 2
    x-content-type-options: nosniff
    strict-transport-security: max-age=31536000; includeSubDomains
    x-cache: CONFIG_NOCACHE
    date: Sat, 22 May 2021 21:34:57 GMT
    content-length: 0
    ```

    > 🎓 Podczas wywoływania punktu końcowego w sieci możesz przekazywać parametry do wywołania, dodając `?` po którym następują pary klucz-wartość jako `klucz=wartość`, oddzielając pary klucz-wartość za pomocą `&`.

1. Azure Maps nie przetwarza tego natychmiast, więc będziesz musiał sprawdzić, czy żądanie przesyłania zostało zakończone, używając URL podanego w nagłówku `location`. Wykonaj żądanie GET do tego URL, aby sprawdzić status. Będziesz musiał dodać swój klucz subskrypcji na końcu URL `location`, dodając `&subscription-key=<subscription_key>` na końcu, zastępując `<subscription_key>` kluczem API dla swojego konta Azure Maps. Uruchom następujące polecenie:

    ```sh
    curl --request GET '<location>&subscription-key=<subscription_key>'
    ```

    Zamień `<location>` na wartość nagłówka `location`, a `<subscription_key>` na klucz API dla swojego konta Azure Maps.

1. Sprawdź wartość `status` w odpowiedzi. Jeśli nie jest `Succeeded`, poczekaj minutę i spróbuj ponownie.

1. Gdy status wróci jako `Succeeded`, spójrz na `resourceLocation` z odpowiedzi. Zawiera szczegóły dotyczące unikalnego identyfikatora (znanego jako UDID) dla obiektu GeoJSON. UDID to wartość po `metadata/`, nie uwzględniając `api-version`. Na przykład, jeśli `resourceLocation` wynosi:

    ```json
    {
      "resourceLocation": "https://us.atlas.microsoft.com/mapData/metadata/7c3776eb-da87-4c52-ae83-caadf980323a?api-version=1.0"
    }
    ```

    Wtedy UDID wynosi `7c3776eb-da87-4c52-ae83-caadf980323a`.

    Zachowaj kopię tego UDID, ponieważ będziesz go potrzebować do testowania geofence.

## Testowanie punktów względem geofence

Po przesłaniu wielokąta do Azure Maps możesz przetestować punkt, aby sprawdzić, czy znajduje się wewnątrz czy na zewnątrz geofence. Robisz to, wykonując żądanie web API, przekazując UDID geofence oraz szerokość i długość geograficzną punktu do testowania.

Podczas wykonywania tego żądania możesz również przekazać wartość zwaną `searchBuffer`. Określa ona, jak dokładne mają być wyniki. Powodem tego jest fakt, że GPS nie jest idealnie dokładny i czasami lokalizacje mogą być przesunięte o metry lub więcej. Domyślnie search buffer wynosi 50 m, ale możesz ustawić wartości od 0 m do 500 m.

Gdy wyniki zostaną zwrócone z wywołania API, jedna z części wyniku to `distance` mierzona do najbliższego punktu na krawędzi geofence, z wartością dodatnią, jeśli punkt znajduje się na zewnątrz geofence, ujemną, jeśli znajduje się wewnątrz geofence. Jeśli ta odległość jest mniejsza niż search buffer, rzeczywista odległość jest zwracana w metrach, w przeciwnym razie wartość wynosi 999 lub -999. 999 oznacza, że punkt znajduje się na zewnątrz geofence o więcej niż search buffer, -999 oznacza, że znajduje się wewnątrz geofence o więcej niż search buffer.

![Geofence z buforem wyszukiwania 50 m wokół niego](../../../../../translated_images/pl/search-buffer-and-distance.e6a79af3898183c7.webp)

Na powyższym obrazku geofence ma bufor wyszukiwania 50 m.

* Punkt w centrum geofence, dobrze wewnątrz bufora wyszukiwania, ma odległość **-999**
* Punkt dobrze poza buforem wyszukiwania ma odległość **999**
* Punkt wewnątrz geofence i wewnątrz bufora wyszukiwania, 6 m od geofence, ma odległość **6 m**
* Punkt na zewnątrz geofence i wewnątrz bufora wyszukiwania, 39 m od geofence, ma odległość **39 m**

Ważne jest, aby znać odległość do krawędzi geofence i łączyć ją z innymi informacjami, takimi jak inne odczyty GPS, prędkość i dane drogowe, podczas podejmowania decyzji na podstawie lokalizacji pojazdu.

Na przykład, wyobraź sobie odczyty GPS pokazujące, że pojazd jechał drogą, która kończy się obok geofence. Jeśli pojedyncza wartość GPS jest niedokładna i umieszcza pojazd wewnątrz geofence, mimo że nie ma tam dostępu dla pojazdów, można ją zignorować.

![Ślad GPS pokazujący pojazd przejeżdżający obok kampusu Microsoft na 520, z odczytami GPS wzdłuż drogi, z wyjątkiem jednego na kampusie, wewnątrz geofence](../../../../../translated_images/pl/geofence-crossing-inaccurate-gps.6a3ed911202ad9cabb66d3964888cec03a42c61d5b8f536ad5bdc99716b370f5.png)
Na powyższym obrazku widoczny jest geofence obejmujący część kampusu Microsoft. Czerwona linia pokazuje trasę ciężarówki jadącej wzdłuż drogi 520, z okręgami oznaczającymi odczyty GPS. Większość z nich jest dokładna i znajduje się wzdłuż drogi 520, ale jeden niedokładny odczyt znajduje się wewnątrz geofence. Nie ma możliwości, aby ten odczyt był poprawny - nie ma dróg, które pozwoliłyby ciężarówce nagle zjechać z drogi 520 na kampus, a potem wrócić na drogę 520. Kod sprawdzający ten geofence będzie musiał uwzględnić poprzednie odczyty przed podjęciem działań na podstawie wyników testu geofence.

✅ Jakie dodatkowe dane byłyby potrzebne, aby sprawdzić, czy odczyt GPS można uznać za poprawny?

### Zadanie - testowanie punktów względem geofence

1. Zacznij od zbudowania URL dla zapytania do API. Format wygląda następująco:

    ```output
    https://atlas.microsoft.com/spatial/geofence/json?api-version=1.0&deviceId=gps-sensor&subscription-key=<subscription-key>&udid=<UDID>&lat=<lat>&lon=<lon>
    ```

    Zamień `<subscription_key>` na klucz API dla swojego konta Azure Maps.

    Zamień `<UDID>` na UDID geofence z poprzedniego zadania.

    Zamień `<lat>` i `<lon>` na szerokość i długość geograficzną, które chcesz przetestować.

    Ten URL używa API `https://atlas.microsoft.com/spatial/geofence/json`, aby zapytać o geofence zdefiniowany za pomocą GeoJSON. Celuje w wersję API `1.0`. Parametr `deviceId` jest wymagany i powinien być nazwą urządzenia, z którego pochodzi szerokość i długość geograficzna.

    Domyślny bufor wyszukiwania wynosi 50 m, ale możesz go zmienić, przekazując dodatkowy parametr `searchBuffer=<distance>`, ustawiając `<distance>` na odległość bufora wyszukiwania w metrach, od 0 do 500.

1. Użyj curl, aby wykonać żądanie GET do tego URL:

    ```sh
    curl --request GET '<URL>'
    ```

    > 💁 Jeśli otrzymasz kod odpowiedzi `BadRequest` z błędem:
    >
    > ```output
    > Invalid GeoJSON: All feature properties should contain a geometryId, which is used for identifying the geofence.
    > ```
    >
    > oznacza to, że Twój GeoJSON nie zawiera sekcji `properties` z `geometryId`. Musisz poprawić swój GeoJSON, a następnie powtórzyć powyższe kroki, aby ponownie przesłać i uzyskać nowy UDID.

1. Odpowiedź będzie zawierać listę `geometries`, po jednej dla każdego wielokąta zdefiniowanego w GeoJSON użytym do stworzenia geofence. Każda geometria ma 3 interesujące pola: `distance`, `nearestLat` i `nearestLon`.

    ```output
    {
        "geometries": [
            {
                "deviceId": "gps-sensor",
                "udId": "7c3776eb-da87-4c52-ae83-caadf980323a",
                "geometryId": "1",
                "distance": 999.0,
                "nearestLat": 47.645875,
                "nearestLon": -122.142713
            }
        ],
        "expiredGeofenceGeometryId": [],
        "invalidPeriodGeofenceGeometryId": []
    }
    ```

    * `nearestLat` i `nearestLon` to szerokość i długość geograficzna punktu na krawędzi geofence, który jest najbliżej testowanej lokalizacji.

    * `distance` to odległość od testowanej lokalizacji do najbliższego punktu na krawędzi geofence. Liczby ujemne oznaczają, że punkt znajduje się wewnątrz geofence, liczby dodatnie - na zewnątrz. Ta wartość będzie mniejsza niż 50 (domyślny bufor wyszukiwania) lub wynosić 999.

1. Powtórz to wielokrotnie z lokalizacjami wewnątrz i na zewnątrz geofence.

## Użycie geofence w kodzie bezserwerowym

Teraz możesz dodać nowy wyzwalacz do swojej aplikacji Functions, aby testować dane GPS z IoT Hub względem geofence.

### Grupy konsumenckie

Jak pamiętasz z poprzednich lekcji, IoT Hub pozwala na odtwarzanie zdarzeń, które zostały odebrane przez hub, ale nie przetworzone. Ale co się stanie, jeśli podłączysz wiele wyzwalaczy? Skąd hub będzie wiedział, które zdarzenia zostały przetworzone przez który wyzwalacz?

Odpowiedź brzmi: nie będzie wiedział! Zamiast tego możesz zdefiniować wiele oddzielnych połączeń do odczytu zdarzeń, a każde z nich może zarządzać odtwarzaniem nieprzeczytanych wiadomości. Są one nazywane *grupami konsumenckimi*. Podczas łączenia się z punktem końcowym możesz określić, z którą grupą konsumencką chcesz się połączyć. Każdy komponent Twojej aplikacji będzie łączył się z inną grupą konsumencką.

![Jeden IoT Hub z 3 grupami konsumenckimi rozdzielającymi te same wiadomości do 3 różnych aplikacji Functions](../../../../../translated_images/pl/consumer-groups.a3262e26fc27ba2092863678ad57af15c7223416e388a23f330c058cf4358630.png)

Teoretycznie do każdej grupy konsumenckiej może podłączyć się do 5 aplikacji, a wszystkie będą otrzymywać wiadomości, gdy tylko się pojawią. Najlepszą praktyką jest, aby tylko jedna aplikacja miała dostęp do każdej grupy konsumenckiej, aby uniknąć duplikacji przetwarzania wiadomości i zapewnić, że po ponownym uruchomieniu wszystkie zakolejkowane wiadomości zostaną poprawnie przetworzone. Na przykład, jeśli uruchomisz swoją aplikację Functions lokalnie, a także w chmurze, obie będą przetwarzać wiadomości, co doprowadzi do duplikacji blobów przechowywanych w koncie magazynu.

Jeśli przejrzysz plik `function.json` dla wyzwalacza IoT Hub, który utworzyłeś we wcześniejszej lekcji, zobaczysz grupę konsumencką w sekcji wiązania wyzwalacza Event Hub:

```json
"consumerGroup": "$Default"
```

Podczas tworzenia IoT Hub, domyślnie tworzona jest grupa konsumencka `$Default`. Jeśli chcesz dodać dodatkowy wyzwalacz, możesz to zrobić, używając nowej grupy konsumenckiej.

> 💁 W tej lekcji użyjesz innej funkcji do testowania geofence niż tej używanej do przechowywania danych GPS. Ma to na celu pokazanie, jak używać grup konsumenckich i rozdzielać kod, aby był łatwiejszy do odczytania i zrozumienia. W aplikacji produkcyjnej istnieje wiele sposobów, w jakie można to zaprojektować - umieszczenie obu w jednej funkcji, użycie wyzwalacza na koncie magazynu do uruchomienia funkcji sprawdzającej geofence lub użycie wielu funkcji. Nie ma "jednego właściwego sposobu", wszystko zależy od reszty Twojej aplikacji i Twoich potrzeb.

### Zadanie - utwórz nową grupę konsumencką

1. Uruchom następujące polecenie, aby utworzyć nową grupę konsumencką o nazwie `geofence` dla swojego IoT Hub:

    ```sh
    az iot hub consumer-group create --name geofence \
                                     --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

1. Jeśli chcesz zobaczyć wszystkie grupy konsumenckie dla IoT Hub, uruchom następujące polecenie:

    ```sh
    az iot hub consumer-group list --output table \
                                   --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub. To polecenie wyświetli wszystkie grupy konsumenckie.

    ```output
    Name      ResourceGroup
    --------  ---------------
    $Default  gps-sensor
    geofence  gps-sensor
    ```

> 💁 Kiedy uruchomiłeś monitor zdarzeń IoT Hub we wcześniejszej lekcji, połączył się on z grupą konsumencką `$Default`. Dlatego nie możesz uruchomić monitora zdarzeń i wyzwalacza zdarzeń jednocześnie. Jeśli chcesz uruchomić oba, możesz użyć innych grup konsumenckich dla wszystkich swoich aplikacji Functions i zachować `$Default` dla monitora zdarzeń.

### Zadanie - utwórz nowy wyzwalacz IoT Hub

1. Dodaj nowy wyzwalacz zdarzeń IoT Hub do swojej aplikacji `gps-trigger`, którą utworzyłeś we wcześniejszej lekcji. Nazwij tę funkcję `geofence-trigger`.

    > ⚠️ Możesz odwołać się do [instrukcji tworzenia wyzwalacza zdarzeń IoT Hub z projektu 2, lekcja 5, jeśli potrzebujesz](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#create-an-iot-hub-event-trigger).

1. Skonfiguruj ciąg połączenia IoT Hub w pliku `function.json`. Plik `local.settings.json` jest współdzielony między wszystkimi wyzwalaczami w aplikacji Functions.

1. Zaktualizuj wartość `consumerGroup` w pliku `function.json`, aby odwoływała się do nowej grupy konsumenckiej `geofence`:

    ```json
    "consumerGroup": "geofence"
    ```

1. Będziesz potrzebować klucza subskrypcji dla swojego konta Azure Maps w tym wyzwalaczu, więc dodaj nowy wpis do pliku `local.settings.json` o nazwie `MAPS_KEY`.

1. Uruchom aplikację Functions, aby upewnić się, że łączy się i przetwarza wiadomości. Wyzwalacz `iot-hub-trigger` z wcześniejszej lekcji również będzie działał i przesyłał bloby do magazynu.

    > Aby uniknąć duplikacji odczytów GPS w magazynie blobów, możesz zatrzymać aplikację Functions, którą masz uruchomioną w chmurze. Aby to zrobić, użyj następującego polecenia:
    >
    > ```sh
    > az functionapp stop --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Zamień `<functions_app_name>` na nazwę, której użyłeś dla swojej aplikacji Functions.
    >
    > Możesz ją później ponownie uruchomić za pomocą następującego polecenia:
    >
    > ```sh
    > az functionapp start --resource-group gps-sensor \
    >                     --name <functions_app_name>
    > ```
    >
    > Zamień `<functions_app_name>` na nazwę, której użyłeś dla swojej aplikacji Functions.

### Zadanie - testowanie geofence z wyzwalacza

We wcześniejszej części lekcji użyłeś curl, aby zapytać o geofence i sprawdzić, czy punkt znajduje się wewnątrz czy na zewnątrz. Możesz wykonać podobne zapytanie webowe z wnętrza swojego wyzwalacza.

1. Aby zapytać o geofence, potrzebujesz jego UDID. Dodaj nowy wpis do pliku `local.settings.json` o nazwie `GEOFENCE_UDID` z tą wartością.

1. Otwórz plik `__init__.py` z nowego wyzwalacza `geofence-trigger`.

1. Dodaj następujący import na początku pliku:

    ```python
    import json
    import os
    import requests
    ```

    Pakiet `requests` pozwala na wykonywanie zapytań do API webowych. Azure Maps nie ma SDK dla Pythona, więc musisz wykonywać zapytania webowe, aby używać go w kodzie Pythona.

1. Dodaj następujące 2 linie na początku metody `main`, aby uzyskać klucz subskrypcji Maps:

    ```python
    maps_key = os.environ['MAPS_KEY']
    geofence_udid = os.environ['GEOFENCE_UDID']    
    ```

1. Wewnątrz pętli `for event in events` dodaj następujący kod, aby uzyskać szerokość i długość geograficzną z każdego zdarzenia:

    ```python
    event_body = json.loads(event.get_body().decode('utf-8'))
    lat = event_body['gps']['lat']
    lon = event_body['gps']['lon']
    ```

    Ten kod konwertuje JSON z treści zdarzenia na słownik, a następnie wyodrębnia `lat` i `lon` z pola `gps`.

1. Podczas używania `requests`, zamiast budować długi URL, jak to robiłeś za pomocą curl, możesz użyć tylko części URL i przekazać parametry jako słownik. Dodaj następujący kod, aby zdefiniować URL do wywołania i skonfigurować parametry:

    ```python
    url = 'https://atlas.microsoft.com/spatial/geofence/json'

    params = {
        'api-version': 1.0,
        'deviceId': 'gps-sensor',
        'subscription-key': maps_key,
        'udid' : geofence_udid,
        'lat' : lat,
        'lon' : lon
    }
    ```

    Elementy w słowniku `params` będą odpowiadać parom klucz-wartość, które używałeś podczas wywoływania API webowego za pomocą curl.

1. Dodaj następujące linie kodu, aby wywołać API webowe:

    ```python
    response = requests.get(url, params=params)
    response_body = json.loads(response.text)
    ```

    To wywołuje URL z parametrami i zwraca obiekt odpowiedzi.

1. Dodaj następujący kod poniżej tego:

    ```python
    distance = response_body['geometries'][0]['distance']

    if distance == 999:
        logging.info('Point is outside geofence')
    elif distance > 0:
        logging.info(f'Point is just outside geofence by a distance of {distance}m')
    elif distance == -999:
        logging.info(f'Point is inside geofence')
    else:
        logging.info(f'Point is just inside geofence by a distance of {distance}m')
    ```

    Ten kod zakłada 1 geometrię i wyodrębnia odległość z tej pojedynczej geometrii. Następnie loguje różne wiadomości w zależności od odległości.

1. Uruchom ten kod. W logach zobaczysz, czy współrzędne GPS znajdują się wewnątrz czy na zewnątrz geofence, z odległością, jeśli punkt znajduje się w odległości 50 m. Wypróbuj ten kod z różnymi geofence w zależności od lokalizacji swojego czujnika GPS, spróbuj przesunąć czujnik (na przykład podłączony do WiFi z telefonu komórkowego lub z różnymi współrzędnymi na wirtualnym urządzeniu IoT), aby zobaczyć tę zmianę.

1. Gdy będziesz gotowy, wdroż ten kod do swojej aplikacji Functions w chmurze. Nie zapomnij wdrożyć nowych ustawień aplikacji.

    > ⚠️ Możesz odwołać się do [instrukcji przesyłania ustawień aplikacji z projektu 2, lekcja 5, jeśli potrzebujesz](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---upload-your-application-settings).

    > ⚠️ Możesz odwołać się do [instrukcji wdrażania aplikacji Functions z projektu 2, lekcja 5, jeśli potrzebujesz](../../../2-farm/lessons/5-migrate-application-to-the-cloud/README.md#task---deploy-your-functions-app-to-the-cloud).

> 💁 Kod ten znajdziesz w folderze [code/functions](../../../../../3-transport/lessons/4-geofences/code/functions).

---

## 🚀 Wyzwanie

W tej lekcji dodałeś jeden geofence za pomocą pliku GeoJSON z jednym wielokątem. Możesz przesłać wiele wielokątów jednocześnie, pod warunkiem, że mają różne wartości `geometryId` w sekcji `properties`.

Spróbuj przesłać plik GeoJSON z wieloma wielokątami i dostosuj swój kod, aby znaleźć, który wielokąt jest najbliższy współrzędnym GPS lub w którym się znajdują.

## Quiz po lekcji

[Quiz po lekcji](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/28)

## Przegląd i samodzielna nauka

* Przeczytaj więcej o geofence i ich zastosowaniach na [stronie Geofencing na Wikipedii](https://en.wikipedia.org/wiki/Geo-fence).
* Przeczytaj więcej o API geofence Azure Maps na [dokumentacji Microsoft Azure Maps Spatial - Get Geofence](https://docs.microsoft.com/rest/api/maps/spatial/getgeofence?WT.mc_id=academic-17441-jabenn).
* Przeczytaj więcej o grupach konsumenckich w [Funkcje i terminologia w Azure Event Hubs - dokumentacja Event consumers na Microsoft docs](https://docs.microsoft.com/azure/event-hubs/event-hubs-features?WT.mc_id=academic-17441-jabenn#event-consumers).

## Zadanie

[Wysyłanie powiadomień za pomocą Twilio](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.