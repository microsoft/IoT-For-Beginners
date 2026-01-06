<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4d8e7a066d75b625e7a979c14157041d",
  "translation_date": "2025-08-26T06:52:47+00:00",
  "source_file": "2-farm/lessons/4-migrate-your-plant-to-the-cloud/README.md",
  "language_code": "pl"
}
-->
# Przenieś swoją roślinę do chmury

![Szkicowy przegląd tej lekcji](../../../../../translated_images/lesson-8.3f21f3c11159e6a0a376351973ea5724d5de68fa23b4288853a174bed9ac48c3.pl.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ta lekcja była częścią [Projektu IoT dla początkujących 2 - Cyfrowe rolnictwo](https://youtube.com/playlist?list=PLmsFUfdnGr3yCutmcVg6eAUEfsGiFXgcx) realizowanego przez [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn).

[![Połącz swoje urządzenie z chmurą za pomocą Azure IoT Hub](https://img.youtube.com/vi/bNxjopXkhvk/0.jpg)](https://youtu.be/bNxjopXkhvk)

## Quiz przed lekcją

[Quiz przed lekcją](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/15)

## Wprowadzenie

W poprzedniej lekcji nauczyłeś się, jak połączyć swoją roślinę z brokerem MQTT i sterować przekaźnikiem za pomocą kodu serwera uruchomionego lokalnie. To stanowi podstawę internetowego, zautomatyzowanego systemu nawadniania, który może być stosowany zarówno w przypadku pojedynczych roślin w domu, jak i na komercyjnych farmach.

Urządzenie IoT komunikowało się z publicznym brokerem MQTT, aby zademonstrować zasady działania, ale nie jest to najbardziej niezawodny ani bezpieczny sposób. W tej lekcji dowiesz się o chmurze i możliwościach IoT oferowanych przez publiczne usługi chmurowe. Nauczysz się również, jak przenieść swoją roślinę z publicznego brokera MQTT do jednej z tych usług chmurowych.

W tej lekcji omówimy:

* [Czym jest chmura?](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Tworzenie subskrypcji chmurowej](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Usługi IoT w chmurze](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Tworzenie usługi IoT w chmurze](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Komunikacja z IoT Hub](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)
* [Łączenie urządzenia z usługą IoT](../../../../../2-farm/lessons/4-migrate-your-plant-to-the-cloud)

## Czym jest chmura?

Przed pojawieniem się chmury, firmy, które chciały zapewnić usługi swoim pracownikom (np. bazy danych czy przechowywanie plików) lub klientom (np. strony internetowe), musiały budować i zarządzać własnymi centrami danych. Mogło to być małe pomieszczenie z kilkoma komputerami lub cały budynek pełen sprzętu. Firma musiała zarządzać wszystkim, w tym:

* Zakupem komputerów
* Konserwacją sprzętu
* Zasilaniem i chłodzeniem
* Siecią
* Bezpieczeństwem, w tym ochroną budynku i oprogramowania
* Instalacją i aktualizacją oprogramowania

Było to bardzo kosztowne, wymagało szerokiego zakresu umiejętności od pracowników i było powolne w dostosowywaniu się do zmian. Na przykład, jeśli sklep internetowy chciał przygotować się na intensywny sezon świąteczny, musiał planować z dużym wyprzedzeniem, aby zakupić więcej sprzętu, skonfigurować go i zainstalować odpowiednie oprogramowanie. Po zakończeniu sezonu świątecznego, gdy sprzedaż spadała, sprzęt pozostawał niewykorzystany do kolejnego szczytu.

✅ Czy uważasz, że taki model pozwalał firmom działać szybko? Jeśli sklep odzieżowy nagle zyskałby popularność dzięki celebrycie noszącemu ich ubrania, czy byłby w stanie szybko zwiększyć moc obliczeniową, aby obsłużyć nagły wzrost zamówień?

### Komputer kogoś innego

Chmura jest często żartobliwie nazywana „komputerem kogoś innego”. Początkowy pomysł był prosty - zamiast kupować komputery, wynajmujesz je od kogoś innego. Dostawca usług chmurowych zarządza ogromnymi centrami danych. To on odpowiada za zakup i instalację sprzętu, zarządzanie zasilaniem i chłodzeniem, siecią, bezpieczeństwem budynku, aktualizacjami sprzętu i oprogramowania. Jako klient wynajmujesz potrzebne komputery, zwiększając ich liczbę w razie wzrostu zapotrzebowania i zmniejszając, gdy zapotrzebowanie spada. Centra danych chmurowych znajdują się na całym świecie.

![Centrum danych Microsoft w chmurze](../../../../../translated_images/azure-region-existing.73f704604f2aa6cb9b5a49ed40e93d4fd81ae3f4e6af4a8ca504023902832f56.pl.png)
![Planowana rozbudowa centrum danych Microsoft w chmurze](../../../../../translated_images/azure-region-planned-expansion.a5074a1e8af74f156a73552d502429e5b126ea5019274d767ecb4b9afdad442b.pl.png)

Te centra danych mogą zajmować powierzchnię kilku kilometrów kwadratowych. Powyższe zdjęcia przedstawiają centrum danych Microsoft sprzed kilku lat, pokazując jego początkowy rozmiar oraz planowaną rozbudowę. Obszar przeznaczony na rozbudowę ma ponad 5 kilometrów kwadratowych.

> 💁 Te centra danych zużywają tak dużo energii, że niektóre mają własne elektrownie. Ze względu na swoją skalę i poziom inwestycji dostawców chmurowych, są one zazwyczaj bardzo przyjazne dla środowiska. Są bardziej efektywne niż wiele małych centrów danych, działają głównie na odnawialnych źródłach energii, a dostawcy chmur ciężko pracują, aby zmniejszyć ilość odpadów, ograniczyć zużycie wody i sadzić lasy w miejsce tych wyciętych pod budowę centrów danych. Więcej o działaniach na rzecz zrównoważonego rozwoju jednego z dostawców chmury możesz przeczytać na [stronie Azure o zrównoważonym rozwoju](https://azure.microsoft.com/global-infrastructure/sustainability/?WT.mc_id=academic-17441-jabenn).

✅ Zrób badania: Przeczytaj o głównych dostawcach chmur, takich jak [Azure od Microsoft](https://azure.microsoft.com/?WT.mc_id=academic-17441-jabenn) czy [GCP od Google](https://cloud.google.com). Ile mają centrów danych i gdzie się znajdują?

Korzystanie z chmury obniża koszty dla firm i pozwala im skupić się na tym, co robią najlepiej, pozostawiając zarządzanie chmurą w rękach dostawcy. Firmy nie muszą już wynajmować lub kupować przestrzeni w centrach danych, płacić różnym dostawcom za łączność i energię ani zatrudniać ekspertów. Zamiast tego płacą jedną miesięczną fakturę dostawcy chmury, który zajmuje się wszystkim.

Dostawca chmury może wykorzystać efekt skali, aby obniżyć koszty, kupując sprzęt hurtowo po niższych cenach, inwestując w narzędzia zmniejszające nakład pracy związany z konserwacją, a nawet projektując i budując własny sprzęt, aby ulepszyć swoją ofertę chmurową.

### Microsoft Azure

Azure to chmura dla programistów od Microsoft, której będziesz używać w tych lekcjach. Poniższy film przedstawia krótki przegląd Azure:

[![Film o Azure](../../../../../translated_images/what-is-azure-video-thumbnail.20174db09e03bbb8.pl.png)](https://www.microsoft.com/videoplayer/embed/RE4Ibng?WT.mc_id=academic-17441-jabenn)

## Tworzenie subskrypcji chmurowej

Aby korzystać z usług w chmurze, musisz założyć subskrypcję u dostawcy chmury. W tej lekcji założysz subskrypcję Microsoft Azure. Jeśli już masz subskrypcję Azure, możesz pominąć to zadanie. Szczegóły subskrypcji opisane tutaj są aktualne w momencie pisania, ale mogą ulec zmianie.

> 💁 Jeśli korzystasz z tych lekcji w ramach szkoły, możesz już mieć dostęp do subskrypcji Azure. Sprawdź to z nauczycielem.

Istnieją dwa rodzaje darmowych subskrypcji Azure, które możesz założyć:

* **Azure dla studentów** - Subskrypcja przeznaczona dla studentów powyżej 18 roku życia. Nie potrzebujesz karty kredytowej, aby się zarejestrować, a do weryfikacji używasz szkolnego adresu e-mail. Po rejestracji otrzymujesz 100 USD na wydatki na zasoby chmurowe oraz darmowe usługi, w tym darmową wersję usługi IoT. Subskrypcja trwa 12 miesięcy i można ją odnawiać co roku, dopóki jesteś studentem.

* **Darmowa subskrypcja Azure** - Subskrypcja dla osób, które nie są studentami. Wymagana jest karta kredytowa do rejestracji, ale karta nie zostanie obciążona - służy jedynie do weryfikacji, że jesteś prawdziwą osobą, a nie botem. Otrzymujesz 200 USD kredytu do wykorzystania w ciągu pierwszych 30 dni na dowolne usługi oraz darmowe poziomy usług Azure. Po wykorzystaniu kredytu karta nie zostanie obciążona, chyba że przejdziesz na subskrypcję płatną.

> 💁 Microsoft oferuje również subskrypcję Azure dla studentów Starter dla osób poniżej 18 roku życia, ale w momencie pisania tego tekstu nie obsługuje ona usług IoT.

### Zadanie - załóż darmową subskrypcję chmurową

Jeśli jesteś studentem powyżej 18 roku życia, możesz założyć subskrypcję Azure dla studentów. Weryfikacja odbywa się za pomocą szkolnego adresu e-mail. Możesz to zrobić na dwa sposoby:

* Zarejestruj się w GitHub Student Developer Pack na stronie [education.github.com/pack](https://education.github.com/pack). Otrzymasz dostęp do wielu narzędzi i ofert, w tym GitHub i Microsoft Azure. Po rejestracji w pakiecie deweloperskim możesz aktywować ofertę Azure dla studentów.

* Zarejestruj się bezpośrednio na konto Azure dla studentów na stronie [azure.microsoft.com/free/students](https://azure.microsoft.com/free/students/?WT.mc_id=academic-17441-jabenn).

> ⚠️ Jeśli Twój szkolny adres e-mail nie jest rozpoznawany, zgłoś [problem w tym repozytorium](https://github.com/Microsoft/IoT-For-Beginners/issues), a sprawdzimy, czy można go dodać do listy dozwolonych adresów Azure dla studentów.

Jeśli nie jesteś studentem lub nie masz ważnego szkolnego adresu e-mail, możesz założyć darmową subskrypcję Azure.

* Zarejestruj się na darmową subskrypcję Azure na stronie [azure.microsoft.com/free](https://azure.microsoft.com/free/?WT.mc_id=academic-17441-jabenn)

## Usługi IoT w chmurze

Publiczny testowy broker MQTT, którego używałeś, jest świetnym narzędziem do nauki, ale ma kilka wad w kontekście zastosowań komercyjnych:

* Niezawodność - to darmowa usługa bez gwarancji, która może zostać wyłączona w dowolnym momencie
* Bezpieczeństwo - jest publiczna, więc każdy może podsłuchiwać Twoje dane telemetryczne lub wysyłać polecenia do sterowania Twoim sprzętem
* Wydajność - jest zaprojektowana do obsługi tylko kilku testowych wiadomości, więc nie poradzi sobie z dużą ilością przesyłanych danych
* Odkrywalność - brak możliwości sprawdzenia, jakie urządzenia są podłączone

Usługi IoT w chmurze rozwiązują te problemy. Są utrzymywane przez dużych dostawców chmurowych, którzy inwestują w niezawodność i są gotowi naprawić wszelkie problemy. Mają wbudowane zabezpieczenia, które chronią przed hakerami odczytującymi Twoje dane lub wysyłającymi fałszywe polecenia. Są również bardzo wydajne, obsługując miliony wiadomości dziennie, korzystając z możliwości skalowania chmury.

> 💁 Chociaż za te korzyści płacisz miesięczną opłatę, większość dostawców chmurowych oferuje darmową wersję swojej usługi IoT z ograniczoną liczbą wiadomości dziennie lub urządzeń, które mogą się połączyć. Ta darmowa wersja zazwyczaj wystarcza programistom do nauki. W tej lekcji będziesz korzystać z darmowej wersji.

Urządzenia IoT łączą się z usługą chmurową za pomocą SDK urządzenia (biblioteki, która dostarcza kod do pracy z funkcjami usługi) lub bezpośrednio za pomocą protokołu komunikacyjnego, takiego jak MQTT lub HTTP. SDK urządzenia jest zazwyczaj najłatwiejszą opcją, ponieważ obsługuje wszystko za Ciebie, np. wie, jakie tematy publikować lub subskrybować i jak obsługiwać bezpieczeństwo.

![Urządzenia łączą się z usługą za pomocą SDK urządzenia. Kod serwera również łączy się z usługą za pomocą SDK](../../../../../translated_images/iot-service-connectivity.7e873847921a5d6fd60d0ba3a943210194518cee0d4e362476624316443275c3.pl.png)

Twoje urządzenie komunikuje się z innymi częściami aplikacji za pośrednictwem tej usługi - podobnie jak przesyłałeś dane telemetryczne i odbierałeś polecenia za pomocą MQTT. Zazwyczaj odbywa się to za pomocą SDK usługi lub podobnej biblioteki. Wiadomości są przesyłane z urządzenia do usługi, gdzie inne komponenty aplikacji mogą je odczytać, a następnie wysyłać wiadomości z powrotem do urządzenia.

![Urządzenia bez ważnego klucza tajnego nie mogą połączyć się z usługą IoT](../../../../../translated_images/iot-service-allowed-denied-connection.818b0063ac213fb84204a7229303764d9b467ca430fb822b4ac2fca267d56726.pl.png)

Te usługi implementują bezpieczeństwo, znając wszystkie urządzenia, które mogą się połączyć i przesyłać dane, albo poprzez wcześniejszą rejestrację urządzeń w usłudze, albo poprzez nadanie urządzeniom kluczy tajnych lub certyfikatów, które mogą wykorzystać do samodzielnej rejestracji przy pierwszym połączeniu. Nieznane urządzenia nie mogą się połączyć - jeśli spróbują, usługa odrzuci połączenie i zignoruje wysyłane przez nie wiadomości.

✅ Zrób badania: Jakie są wady otwartej usługi IoT, do której każde urządzenie lub kod może się połączyć? Czy możesz znaleźć konkretne przykłady hakerów wykorzystujących takie sytuacje?

Inne komponenty Twojej aplikacji mogą łączyć się z usługą IoT, dowiadywać się o wszystkich podłączonych lub zarejestrowanych urządzeniach i komunikować się z nimi bezpośrednio, zarówno masowo, jak i indywidualnie.
💁 Usługi IoT wdrażają również dodatkowe funkcje, a dostawcy chmury oferują dodatkowe usługi i aplikacje, które można połączyć z daną usługą. Na przykład, jeśli chcesz przechowywać wszystkie wiadomości telemetryczne wysyłane przez wszystkie urządzenia w bazie danych, zazwyczaj wystarczy kilka kliknięć w narzędziu konfiguracyjnym dostawcy chmury, aby połączyć usługę z bazą danych i przesyłać dane strumieniowo.
## Utwórz usługę IoT w chmurze

Teraz, gdy masz subskrypcję Azure, możesz zarejestrować się w usłudze IoT. Usługa IoT od Microsoftu nazywa się Azure IoT Hub.

![Logo Azure IoT Hub](../../../../../translated_images/azure-iot-hub-logo.28a19de76d0a1932464d858f7558712bcdace3e5ec69c434d482ed7ce41c3a26.pl.png)

Poniższy film przedstawia krótki przegląd Azure IoT Hub:

[![Film: Przegląd Azure IoT Hub](https://img.youtube.com/vi/smuZaZZXKsU/0.jpg)](https://www.youtube.com/watch?v=smuZaZZXKsU)

> 🎥 Kliknij obrazek powyżej, aby obejrzeć film

✅ Poświęć chwilę na przeprowadzenie badań i przeczytaj przegląd IoT Hub w [dokumentacji Microsoft IoT Hub](https://docs.microsoft.com/azure/iot-hub/about-iot-hub?WT.mc_id=academic-17441-jabenn).

Usługi chmurowe dostępne w Azure można konfigurować za pomocą portalu internetowego lub interfejsu wiersza poleceń (CLI). W tym zadaniu użyjesz CLI.

### Zadanie - zainstaluj Azure CLI

Aby korzystać z Azure CLI, najpierw musisz go zainstalować na swoim komputerze PC lub Mac.

1. Postępuj zgodnie z instrukcjami w [dokumentacji Azure CLI](https://docs.microsoft.com/cli/azure/install-azure-cli?WT.mc_id=academic-17441-jabenn), aby zainstalować CLI.

1. Azure CLI obsługuje wiele rozszerzeń, które dodają funkcje zarządzania szeroką gamą usług Azure. Zainstaluj rozszerzenie IoT, uruchamiając następujące polecenie w wierszu poleceń lub terminalu:

    ```sh
    az extension add --name azure-iot
    ```

1. W wierszu poleceń lub terminalu uruchom następujące polecenie, aby zalogować się do swojej subskrypcji Azure za pomocą Azure CLI.

    ```sh
    az login
    ```

    W przeglądarce zostanie otwarta strona internetowa. Zaloguj się, używając konta, którego użyłeś do rejestracji subskrypcji Azure. Po zalogowaniu możesz zamknąć kartę przeglądarki.

1. Jeśli masz wiele subskrypcji Azure, na przykład subskrypcję zapewnioną przez szkołę oraz własną subskrypcję Azure dla Studentów, musisz wybrać tę, której chcesz używać. Uruchom następujące polecenie, aby wyświetlić listę wszystkich subskrypcji, do których masz dostęp:

    ```sh
    az account list --output table
    ```

    W wynikach zobaczysz nazwę każdej subskrypcji wraz z jej `SubscriptionId`.

    ```output
    ➜  ~ az account list --output table
    Name                    CloudName    SubscriptionId                        State    IsDefault
    ----------------------  -----------  ------------------------------------  -------  -----------
    School-subscription     AzureCloud   cb30cde9-814a-42f0-a111-754cb788e4e1  Enabled  True
    Azure for Students      AzureCloud   fa51c31b-162c-4599-add6-781def2e1fbf  Enabled  False
    ```

    Aby wybrać subskrypcję, której chcesz używać, użyj następującego polecenia:

    ```sh
    az account set --subscription <SubscriptionId>
    ```

    Zamień `<SubscriptionId>` na Id subskrypcji, której chcesz używać. Po uruchomieniu tego polecenia ponownie uruchom polecenie, aby wyświetlić swoje konta. Zobaczysz, że kolumna `IsDefault` będzie oznaczona jako `True` dla subskrypcji, którą właśnie ustawiłeś.

### Zadanie - utwórz grupę zasobów

Usługi Azure, takie jak instancje IoT Hub, maszyny wirtualne, bazy danych czy usługi AI, są określane jako **zasoby**. Każdy zasób musi znajdować się w **grupie zasobów**, czyli logicznej grupie jednego lub więcej zasobów.

> 💁 Korzystanie z grup zasobów pozwala zarządzać wieloma usługami jednocześnie. Na przykład, po ukończeniu wszystkich lekcji tego projektu możesz usunąć grupę zasobów, a wszystkie zasoby w niej zostaną automatycznie usunięte.

1. Istnieje wiele centrów danych Azure na całym świecie, podzielonych na regiony. Tworząc zasób lub grupę zasobów Azure, musisz określić, gdzie chcesz go utworzyć. Uruchom następujące polecenie, aby uzyskać listę lokalizacji:

    ```sh
    az account list-locations --output table
    ```

    Zobaczysz listę lokalizacji. Ta lista będzie długa.

    > 💁 W momencie pisania tego tekstu dostępnych jest 65 lokalizacji, w których można wdrażać zasoby.

    ```output
        ➜  ~ az account list-locations --output table
    DisplayName               Name                 RegionalDisplayName
    ------------------------  -------------------  -------------------------------------
    East US                   eastus               (US) East US
    East US 2                 eastus2              (US) East US 2
    South Central US          southcentralus       (US) South Central US
    ...
    ```

    Zanotuj wartość z kolumny `Name` dla regionu najbliższego Tobie. Możesz znaleźć regiony na mapie na stronie [Azure geographies](https://azure.microsoft.com/global-infrastructure/geographies/?WT.mc_id=academic-17441-jabenn).

1. Uruchom następujące polecenie, aby utworzyć grupę zasobów o nazwie `soil-moisture-sensor`. Nazwy grup zasobów muszą być unikalne w Twojej subskrypcji.

    ```sh
    az group create --name soil-moisture-sensor \
                    --location <location>
    ```

    Zamień `<location>` na lokalizację wybraną w poprzednim kroku.

### Zadanie - utwórz IoT Hub

Teraz możesz utworzyć zasób IoT Hub w swojej grupie zasobów.

1. Użyj następującego polecenia, aby utworzyć zasób IoT Hub:

    ```sh
    az iot hub create --resource-group soil-moisture-sensor \
                      --sku F1 \
                      --partition-count 2 \
                      --name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę swojego huba. Ta nazwa musi być globalnie unikalna - to znaczy, że żaden inny IoT Hub utworzony przez kogokolwiek nie może mieć tej samej nazwy. Ta nazwa jest używana w adresie URL wskazującym na hub, więc musi być unikalna. Użyj czegoś w stylu `soil-moisture-sensor-` i dodaj unikalny identyfikator na końcu, na przykład losowe słowa lub swoje imię.

    Opcja `--sku F1` wskazuje na użycie darmowego poziomu. Darmowy poziom obsługuje 8 000 wiadomości dziennie oraz większość funkcji pełnopłatnych poziomów.

    > 🎓 Różne poziomy cenowe usług Azure są określane jako poziomy. Każdy poziom ma inną cenę i oferuje różne funkcje lub wolumeny danych.

    > 💁 Jeśli chcesz dowiedzieć się więcej o cenach, możesz sprawdzić [przewodnik cenowy Azure IoT Hub](https://azure.microsoft.com/pricing/details/iot-hub/?WT.mc_id=academic-17441-jabenn).

    Opcja `--partition-count 2` definiuje, ile strumieni danych obsługuje IoT Hub. Więcej partycji zmniejsza blokowanie danych, gdy wiele urządzeń odczytuje i zapisuje dane w IoT Hub. Partycje są poza zakresem tych lekcji, ale wartość ta musi być ustawiona, aby utworzyć IoT Hub w darmowym poziomie.

    > 💁 Możesz mieć tylko jeden IoT Hub w darmowym poziomie na subskrypcję.

IoT Hub zostanie utworzony. Może to potrwać minutę lub dwie.

## Komunikacja z IoT Hub

W poprzedniej lekcji używałeś MQTT i wysyłałeś wiadomości w różnych tematach, z różnymi tematami mającymi różne cele. Zamiast wysyłać wiadomości w różnych tematach, IoT Hub ma kilka zdefiniowanych sposobów komunikacji urządzenia z hubem lub huba z urządzeniem.

> 💁 Pod spodem ta komunikacja między IoT Hub a Twoim urządzeniem może korzystać z MQTT, HTTPS lub AMQP.

* Wiadomości od urządzenia do chmury (D2C) - są to wiadomości wysyłane z urządzenia do IoT Hub, takie jak dane telemetryczne. Mogą być następnie odczytywane z IoT Hub przez kod aplikacji.

    > 🎓 Pod spodem IoT Hub korzysta z usługi Azure o nazwie [Event Hubs](https://docs.microsoft.com/azure/event-hubs/?WT.mc_id=academic-17441-jabenn). Pisząc kod do odczytu wiadomości wysyłanych do huba, często nazywa się je zdarzeniami.

* Wiadomości od chmury do urządzenia (C2D) - są to wiadomości wysyłane z kodu aplikacji, przez IoT Hub do urządzenia IoT.

* Żądania metod bezpośrednich - są to wiadomości wysyłane z kodu aplikacji przez IoT Hub do urządzenia IoT w celu zażądania wykonania jakiejś czynności, na przykład sterowania siłownikiem. Wiadomości te wymagają odpowiedzi, aby kod aplikacji mógł stwierdzić, czy zostały pomyślnie przetworzone.

* Bliźniaki urządzeń - są to dokumenty JSON synchronizowane między urządzeniem a IoT Hub, używane do przechowywania ustawień lub innych właściwości zgłaszanych przez urządzenie lub mających być ustawionych na urządzeniu (znanych jako pożądane) przez IoT Hub.

IoT Hub może przechowywać wiadomości i żądania metod bezpośrednich przez konfigurowalny okres czasu (domyślnie jeden dzień), więc jeśli urządzenie lub kod aplikacji straci połączenie, nadal może pobrać wiadomości wysłane podczas jego braku po ponownym połączeniu. Bliźniaki urządzeń są przechowywane na stałe w IoT Hub, więc w dowolnym momencie urządzenie może się ponownie połączyć i uzyskać najnowszy bliźniak urządzenia.

✅ Przeprowadź badania: Przeczytaj więcej o tych typach wiadomości w [przewodniku komunikacji od urządzenia do chmury](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-d2c-guidance?WT.mc_id=academic-17441-jabenn) oraz [przewodniku komunikacji od chmury do urządzenia](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-c2d-guidance?WT.mc_id=academic-17441-jabenn) w dokumentacji IoT Hub.

## Połącz swoje urządzenie z usługą IoT

Po utworzeniu huba Twoje urządzenie IoT może się z nim połączyć. Tylko zarejestrowane urządzenia mogą łączyć się z usługą, więc najpierw musisz zarejestrować swoje urządzenie. Po rejestracji możesz uzyskać ciąg połączenia, który urządzenie może używać do połączenia. Ten ciąg połączenia jest specyficzny dla urządzenia i zawiera informacje o IoT Hub, urządzeniu oraz tajny klucz, który umożliwia temu urządzeniu połączenie.

> 🎓 Ciąg połączenia to ogólny termin oznaczający fragment tekstu zawierający szczegóły połączenia. Są one używane podczas łączenia z IoT Hub, bazami danych i wieloma innymi usługami. Zazwyczaj składają się z identyfikatora usługi, takiego jak URL, oraz informacji o zabezpieczeniach, takich jak tajny klucz. Są przekazywane do SDK w celu połączenia z usługą.

> ⚠️ Ciągi połączenia powinny być przechowywane w bezpiecznym miejscu! Zagadnienia związane z bezpieczeństwem zostaną omówione bardziej szczegółowo w przyszłej lekcji.

### Zadanie - zarejestruj swoje urządzenie IoT

Urządzenie IoT można zarejestrować w IoT Hub za pomocą Azure CLI.

1. Uruchom następujące polecenie, aby zarejestrować urządzenie:

    ```sh
    az iot hub device-identity create --device-id soil-moisture-sensor \
                                      --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

    Spowoduje to utworzenie urządzenia o identyfikatorze `soil-moisture-sensor`.

1. Gdy Twoje urządzenie IoT łączy się z IoT Hub za pomocą SDK, musi używać ciągu połączenia, który podaje URL huba oraz tajny klucz. Uruchom następujące polecenie, aby uzyskać ciąg połączenia:

    ```sh
    az iot hub device-identity connection-string show --device-id soil-moisture-sensor \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

1. Zapisz ciąg połączenia wyświetlony w wynikach, ponieważ będzie Ci potrzebny później.

### Zadanie - połącz swoje urządzenie IoT z chmurą

Przejdź przez odpowiedni przewodnik, aby połączyć swoje urządzenie IoT z chmurą:

* [Arduino - Wio Terminal](wio-terminal-connect-hub.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie IoT](single-board-computer-connect-hub.md)

### Zadanie - monitoruj zdarzenia

Na razie nie będziesz aktualizować kodu serwera. Zamiast tego możesz użyć Azure CLI, aby monitorować zdarzenia z Twojego urządzenia IoT.

1. Upewnij się, że Twoje urządzenie IoT działa i wysyła wartości telemetryczne wilgotności gleby.

1. Uruchom następujące polecenie w wierszu poleceń lub terminalu, aby monitorować wiadomości wysyłane do Twojego IoT Hub:

    ```sh
    az iot hub monitor-events --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

    Zobaczysz wiadomości pojawiające się w wynikach konsoli w miarę ich wysyłania przez Twoje urządzenie IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 376}"
        }
    },
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Zawartość `payload` będzie odpowiadać wiadomości wysłanej przez Twoje urządzenie IoT.

    > W momencie pisania tego tekstu rozszerzenie `az iot` nie działa w pełni na urządzeniach Apple Silicon. Jeśli używasz urządzenia Apple Silicon, będziesz musiał monitorować wiadomości w inny sposób, na przykład korzystając z [Azure IoT Tools dla Visual Studio Code](https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-vscode-iot-toolkit-cloud-device-messaging).

1. Te wiadomości mają automatycznie przypisane różne właściwości, takie jak znacznik czasu ich wysłania. Są one znane jako *adnotacje*. Aby wyświetlić wszystkie adnotacje wiadomości, użyj następującego polecenia:

    ```sh
    az iot hub monitor-events --properties anno --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę, której użyłeś dla swojego IoT Hub.

    Zobaczysz wiadomości pojawiające się w wynikach konsoli w miarę ich wysyłania przez Twoje urządzenie IoT.

    ```output
    Starting event monitor, use ctrl-c to stop...
    {
        "event": {
            "origin": "soil-moisture-sensor",
            "module": "",
            "interface": "",
            "component": "",
            "properties": {},
            "annotations": {
                "iothub-connection-device-id": "soil-moisture-sensor",
                "iothub-connection-auth-method": "{\"scope\":\"device\",\"type\":\"sas\",\"issuer\":\"iothub\",\"acceptingIpFilterRule\":null}",
                "iothub-connection-auth-generation-id": "637553997165220462",
                "iothub-enqueuedtime": 1619976150288,
                "iothub-message-source": "Telemetry",
                "x-opt-sequence-number": 1379,
                "x-opt-offset": "550576",
                "x-opt-enqueued-time": 1619976150277
            },
            "payload": "{\"soil_moisture\": 381}"
        }
    }
    ```

    Wartości czasu w adnotacjach są w [czasie UNIX](https://wikipedia.org/wiki/Unix_time), reprezentującym liczbę sekund od północy 1 stycznia 1970 roku.

    Wyjdź z monitora zdarzeń, gdy skończysz.

### Zadanie - kontroluj swoje urządzenie IoT

Możesz również użyć Azure CLI, aby wywoływać metody bezpośrednie na swoim urządzeniu IoT.

1. Uruchom następujące polecenie w wierszu poleceń lub terminalu, aby wywołać metodę `relay_on` na urządzeniu IoT:

    ```sh
    az iot hub invoke-device-method --device-id soil-moisture-sensor \
                                    --method-name relay_on \
                                    --method-payload '{}' \
                                    --hub-name <hub_name>
    ```

    Zamień `
<hub_name>
` z nazwą, której użyłeś dla swojego IoT Hub.

    To wysyła żądanie metody bezpośredniej dla metody określonej przez `method-name`. Metody bezpośrednie mogą przyjmować ładunek zawierający dane dla metody, który można określić w parametrze `method-payload` jako JSON.

    Zobaczysz, jak przekaźnik się włącza, oraz odpowiadające temu dane wyjściowe z Twojego urządzenia IoT:

    ```output
    Direct method received -  relay_on
    ```

1. Powtórz powyższy krok, ale ustaw `--method-name` na `relay_off`. Zobaczysz, jak przekaźnik się wyłącza, oraz odpowiadające temu dane wyjściowe z urządzenia IoT.

---

## 🚀 Wyzwanie

Darmowy poziom IoT Hub pozwala na 8 000 wiadomości dziennie. Kod, który napisałeś, wysyła wiadomości telemetryczne co 10 sekund. Ile wiadomości dziennie to jedna wiadomość co 10 sekund?

Zastanów się, jak często powinny być wysyłane pomiary wilgotności gleby? Jak możesz zmienić swój kod, aby pozostać w ramach darmowego poziomu, sprawdzając tak często, jak to konieczne, ale nie za często? Co, jeśli chciałbyś dodać drugie urządzenie?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/16)

## Przegląd i samodzielna nauka

SDK IoT Hub jest open source zarówno dla Arduino, jak i Pythona. W repozytoriach kodu na GitHub znajduje się wiele przykładów pokazujących, jak pracować z różnymi funkcjami IoT Hub.

* Jeśli używasz Wio Terminal, sprawdź [przykłady dla Arduino na GitHub](https://github.com/Azure/azure-iot-pal-arduino/tree/master/pal/samples)
* Jeśli używasz Raspberry Pi lub urządzenia wirtualnego, sprawdź [przykłady dla Pythona na GitHub](https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-hub/samples)

## Zadanie

[Dowiedz się więcej o usługach w chmurze](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.