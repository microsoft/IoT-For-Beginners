# Uruchom swój detektor owoców na urządzeniach brzegowych

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-17.bc333c3c35ba8e42.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ten film przedstawia przegląd klasyfikatorów obrazów uruchamianych na urządzeniach IoT, co jest tematem tej lekcji.

[![Custom Vision AI na Azure IoT Edge](https://img.youtube.com/vi/_K5fqGLO8us/0.jpg)](https://www.youtube.com/watch?v=_K5fqGLO8us)

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/33)

## Wprowadzenie

W poprzedniej lekcji użyłeś swojego klasyfikatora obrazów do rozróżniania dojrzałych i niedojrzałych owoców, przesyłając obraz z kamery na urządzeniu IoT przez internet do usługi w chmurze. Takie operacje zajmują czas, generują koszty, a w zależności od rodzaju danych obrazowych mogą mieć konsekwencje związane z prywatnością.

W tej lekcji dowiesz się, jak uruchamiać modele uczenia maszynowego (ML) na urządzeniach brzegowych – na urządzeniach IoT działających w Twojej własnej sieci, a nie w chmurze. Poznasz korzyści i wady obliczeń brzegowych w porównaniu z obliczeniami w chmurze, nauczysz się wdrażać model AI na urządzeniach brzegowych oraz uzyskiwać do niego dostęp z urządzenia IoT.

W tej lekcji omówimy:

* [Obliczenia brzegowe](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Azure IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Rejestracja urządzenia IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Konfiguracja urządzenia IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Eksportowanie modelu](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Przygotowanie kontenera do wdrożenia](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Wdrożenie kontenera](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)
* [Użycie urządzenia IoT Edge](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge)

## Obliczenia brzegowe

Obliczenia brzegowe polegają na przetwarzaniu danych IoT jak najbliżej miejsca ich generowania. Zamiast przetwarzać dane w chmurze, operacje te są przenoszone na krawędź chmury – do Twojej wewnętrznej sieci.

![Schemat architektury pokazujący usługi internetowe w chmurze i urządzenia IoT w lokalnej sieci](../../../../../translated_images/pl/cloud-without-edge.b4da641f6022c95e.webp)

W dotychczasowych lekcjach urządzenia zbierały dane i przesyłały je do chmury w celu analizy, uruchamiając funkcje bezserwerowe lub modele AI w chmurze.

![Schemat architektury pokazujący urządzenia IoT w lokalnej sieci łączące się z urządzeniami brzegowymi, które z kolei łączą się z chmurą](../../../../../translated_images/pl/cloud-with-edge.1e26462c62c126fe.webp)

Obliczenia brzegowe polegają na przeniesieniu części usług chmurowych na komputery działające w tej samej sieci co urządzenia IoT, komunikując się z chmurą tylko w razie potrzeby. Na przykład można uruchamiać modele AI na urządzeniach brzegowych, aby analizować dojrzałość owoców, a do chmury przesyłać jedynie dane analityczne, takie jak liczba dojrzałych i niedojrzałych owoców.

✅ Zastanów się nad aplikacjami IoT, które stworzyłeś do tej pory. Które ich części mogłyby zostać przeniesione na urządzenia brzegowe?

### Zalety

Zalety obliczeń brzegowych to:

1. **Szybkość** – obliczenia brzegowe są idealne dla danych wymagających szybkiej reakcji, ponieważ operacje są wykonywane w tej samej sieci co urządzenie, zamiast przesyłać dane przez internet. Dzięki temu osiąga się wyższe prędkości, ponieważ sieci wewnętrzne mogą działać znacznie szybciej niż połączenia internetowe, a dane pokonują znacznie krótsze odległości.

    > 💁 Mimo że połączenia internetowe wykorzystują kable optyczne, które pozwalają na przesyłanie danych z prędkością światła, przesyłanie danych na całym świecie do dostawców chmurowych zajmuje czas. Na przykład przesyłanie danych z Europy do usług chmurowych w USA zajmuje co najmniej 28 ms, aby pokonać Atlantyk w kablu optycznym, nie uwzględniając czasu potrzebnego na przesłanie danych do kabla transatlantyckiego, konwersję sygnałów elektrycznych na świetlne i odwrotnie po drugiej stronie, a następnie przesłanie danych z kabla optycznego do dostawcy chmurowego.

    Obliczenia brzegowe również wymagają mniej ruchu sieciowego, zmniejszając ryzyko spowolnienia danych z powodu przeciążenia ograniczonej przepustowości dostępnej dla połączenia internetowego.

1. **Dostępność w odległych lokalizacjach** – obliczenia brzegowe działają w przypadku ograniczonej lub braku łączności, albo gdy łączność jest zbyt kosztowna, aby używać jej ciągle. Na przykład w obszarach dotkniętych katastrofami humanitarnymi, gdzie infrastruktura jest ograniczona, lub w krajach rozwijających się.

1. **Niższe koszty** – zbieranie, przechowywanie, analizowanie danych i wyzwalanie działań na urządzeniach brzegowych zmniejsza wykorzystanie usług chmurowych, co może obniżyć całkowity koszt aplikacji IoT. W ostatnim czasie pojawiły się urządzenia zaprojektowane do obliczeń brzegowych, takie jak akceleratory AI, np. [Jetson Nano od NVIDIA](https://developer.nvidia.com/embedded/jetson-nano-developer-kit), które mogą uruchamiać obciążenia AI na sprzęcie GPU w urządzeniach kosztujących mniej niż 100 USD.

1. **Prywatność i bezpieczeństwo** – w przypadku obliczeń brzegowych dane pozostają w Twojej sieci i nie są przesyłane do chmury. Jest to często preferowane w przypadku danych wrażliwych i umożliwiających identyfikację osób, zwłaszcza że dane nie muszą być przechowywane po ich analizie, co znacznie zmniejsza ryzyko wycieku danych. Przykłady obejmują dane medyczne i nagrania z kamer bezpieczeństwa.

1. **Obsługa niebezpiecznych urządzeń** – jeśli masz urządzenia z znanymi lukami w zabezpieczeniach, których nie chcesz podłączać bezpośrednio do swojej sieci lub internetu, możesz podłączyć je do oddzielnej sieci za pomocą brzegowego urządzenia IoT Edge. To urządzenie brzegowe może mieć również połączenie z szerszą siecią lub internetem i zarządzać przepływem danych w obie strony.

1. **Obsługa niekompatybilnych urządzeń** – jeśli masz urządzenia, które nie mogą łączyć się z IoT Hub, na przykład urządzenia, które mogą łączyć się tylko za pomocą połączeń HTTP lub urządzenia, które mają tylko Bluetooth, możesz użyć urządzenia IoT Edge jako urządzenia brzegowego, które przekazuje wiadomości do IoT Hub.

✅ Zrób badania: Jakie inne zalety mogą mieć obliczenia brzegowe?

### Wady

Obliczenia brzegowe mają również wady, które mogą sprawić, że chmura będzie preferowaną opcją:

1. **Skalowalność i elastyczność** – obliczenia w chmurze mogą dostosowywać się do potrzeb sieci i danych w czasie rzeczywistym, dodając lub redukując serwery i inne zasoby. Dodanie większej liczby komputerów brzegowych wymaga ręcznego dodawania kolejnych urządzeń.

1. **Niezawodność i odporność** – obliczenia w chmurze zapewniają wiele serwerów, często w wielu lokalizacjach, dla redundancji i odzyskiwania danych po awarii. Aby osiągnąć ten sam poziom redundancji na urządzeniach brzegowych, potrzebne są duże inwestycje i wiele pracy konfiguracyjnej.

1. **Konserwacja** – dostawcy usług chmurowych zapewniają konserwację systemów i aktualizacje.

✅ Zrób badania: Jakie inne wady mogą mieć obliczenia brzegowe?

Wady są w zasadzie przeciwieństwem zalet korzystania z chmury – musisz samodzielnie budować i zarządzać tymi urządzeniami, zamiast polegać na wiedzy i skali dostawców chmurowych.

Niektóre ryzyka są łagodzone przez samą naturę obliczeń brzegowych. Na przykład, jeśli masz urządzenie brzegowe działające w fabryce, które zbiera dane z maszyn, nie musisz myśleć o niektórych scenariuszach odzyskiwania danych po awarii. Jeśli w fabryce zabraknie prądu, nie potrzebujesz zapasowego urządzenia brzegowego, ponieważ maszyny generujące dane, które urządzenie brzegowe przetwarza, również będą pozbawione zasilania.

W przypadku systemów IoT często będziesz chciał połączyć obliczenia w chmurze i na urządzeniach brzegowych, wykorzystując każdą usługę w zależności od potrzeb systemu, jego użytkowników i osób odpowiedzialnych za jego utrzymanie.

## Azure IoT Edge

![Logo Azure IoT Edge](../../../../../translated_images/pl/azure-iot-edge-logo.c1c076749b5cba2e.webp)

Azure IoT Edge to usługa, która może pomóc w przeniesieniu obciążeń z chmury na urządzenia brzegowe. Konfigurujesz urządzenie jako urządzenie brzegowe, a z chmury możesz wdrażać kod na to urządzenie brzegowe. Pozwala to na połączenie możliwości chmury i urządzeń brzegowych.

> 🎓 *Obciążenia* to termin określający każdą usługę wykonującą jakąś pracę, taką jak modele AI, aplikacje czy funkcje bezserwerowe.

Na przykład możesz wytrenować klasyfikator obrazów w chmurze, a następnie wdrożyć go z chmury na urządzenie brzegowe. Twoje urządzenie IoT przesyła wtedy obrazy do urządzenia brzegowego w celu klasyfikacji, zamiast przesyłać je przez internet. Jeśli potrzebujesz wdrożyć nową wersję modelu, możesz wytrenować ją w chmurze i użyć IoT Edge do zaktualizowania modelu na urządzeniu brzegowym.

> 🎓 Oprogramowanie wdrażane na IoT Edge jest nazywane *modułami*. Domyślnie IoT Edge uruchamia moduły komunikujące się z IoT Hub, takie jak moduły `edgeAgent` i `edgeHub`. Gdy wdrażasz klasyfikator obrazów, jest on wdrażany jako dodatkowy moduł.

IoT Edge jest wbudowany w IoT Hub, więc możesz zarządzać urządzeniami brzegowymi za pomocą tej samej usługi, której używasz do zarządzania urządzeniami IoT, z tym samym poziomem bezpieczeństwa.

IoT Edge uruchamia kod z *kontenerów* – samodzielnych aplikacji uruchamianych w izolacji od reszty aplikacji na Twoim komputerze. Gdy uruchamiasz kontener, działa on jak oddzielny komputer wewnątrz Twojego komputera, z własnym oprogramowaniem, usługami i aplikacjami. Większość czasu kontenery nie mają dostępu do niczego na Twoim komputerze, chyba że zdecydujesz się udostępnić im coś, na przykład folder. Kontener udostępnia wtedy usługi za pomocą otwartego portu, do którego możesz się podłączyć lub udostępnić go w swojej sieci.

![Żądanie sieciowe przekierowane do kontenera](../../../../../translated_images/pl/container-web-browser.4ee81dd4f0d8838c.webp)

Na przykład możesz mieć kontener z witryną internetową działającą na porcie 80, domyślnym porcie HTTP, i możesz go udostępnić ze swojego komputera również na porcie 80.

✅ Zrób badania: Przeczytaj o kontenerach i usługach takich jak Docker czy Moby.

Możesz użyć Custom Vision, aby pobrać klasyfikatory obrazów i wdrożyć je jako kontenery, uruchamiane bezpośrednio na urządzeniu lub wdrażane za pomocą IoT Edge. Gdy działają w kontenerze, można uzyskać do nich dostęp za pomocą tego samego API REST, co w wersji chmurowej, ale z punktem końcowym wskazującym na urządzenie brzegowe uruchamiające kontener.

## Rejestracja urządzenia IoT Edge

Aby używać urządzenia IoT Edge, musi ono zostać zarejestrowane w IoT Hub.

### Zadanie – rejestracja urządzenia IoT Edge

1. Utwórz IoT Hub w grupie zasobów `fruit-quality-detector`. Nadaj mu unikalną nazwę opartą na `fruit-quality-detector`.

1. Zarejestruj urządzenie IoT Edge o nazwie `fruit-quality-detector-edge` w swoim IoT Hub. Polecenie do tego jest podobne do polecenia używanego do rejestracji urządzenia niebrzegowego, z wyjątkiem użycia flagi `--edge-enabled`.

    ```sh
    az iot hub device-identity create --edge-enabled \
                                      --device-id fruit-quality-detector-edge \
                                      --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę swojego IoT Hub.

1. Pobierz ciąg połączenia dla swojego urządzenia, używając następującego polecenia:

    ```sh
    az iot hub device-identity connection-string show --device-id fruit-quality-detector-edge \
                                                      --output table \
                                                      --hub-name <hub_name>
    ```

    Zamień `<hub_name>` na nazwę swojego IoT Hub.

    Skopiuj ciąg połączenia wyświetlony w wyniku.

## Konfiguracja urządzenia IoT Edge

Po utworzeniu rejestracji urządzenia brzegowego w IoT Hub możesz skonfigurować urządzenie brzegowe.

### Zadanie – Instalacja i uruchomienie środowiska IoT Edge

**Środowisko IoT Edge obsługuje tylko kontenery Linux.** Może być uruchamiane na Linuxie lub na Windowsie za pomocą maszyn wirtualnych Linux.

* Jeśli używasz Raspberry Pi jako swojego urządzenia IoT, to działa ono na wspieranej wersji Linuxa i może hostować środowisko IoT Edge. Postępuj zgodnie z [instrukcją instalacji Azure IoT Edge dla Linuxa w dokumentacji Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn), aby zainstalować IoT Edge i ustawić ciąg połączenia.

    > 💁 Pamiętaj, Raspberry Pi OS to wariant Linuxa Debian.

* Jeśli nie używasz Raspberry Pi, ale masz komputer z Linuxem, możesz uruchomić środowisko IoT Edge. Postępuj zgodnie z [instrukcją instalacji Azure IoT Edge dla Linuxa w dokumentacji Microsoft](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge?WT.mc_id=academic-17441-jabenn), aby zainstalować IoT Edge i ustawić ciąg połączenia.

* Jeśli używasz Windowsa, możesz zainstalować środowisko IoT Edge w maszynie wirtualnej Linux, postępując zgodnie z [sekcją instalacji i uruchomienia środowiska IoT Edge w szybkim starcie wdrożenia pierwszego modułu IoT Edge na urządzeniu z Windows w dokumentacji Microsoft](https://docs.microsoft.com/azure/iot-edge/quickstart?WT.mc_id=academic-17441-jabenn#install-and-start-the-iot-edge-runtime). Możesz zatrzymać się, gdy dojdziesz do sekcji *Wdrożenie modułu*.

* Jeśli używasz macOS, możesz utworzyć maszynę wirtualną (VM) w chmurze do użycia jako swoje urządzenie IoT Edge. Są to komputery, które możesz utworzyć w chmurze i uzyskać do nich dostęp przez internet. Możesz utworzyć maszynę wirtualną Linux z zainstalowanym IoT Edge. Postępuj zgodnie z [instrukcją tworzenia maszyny wirtualnej z IoT Edge](vm-iotedge.md), aby uzyskać szczegółowe instrukcje.

## Eksportowanie modelu

Aby uruchomić klasyfikator na urządzeniu brzegowym, musi on zostać wyeksportowany z Custom Vision. Custom Vision może generować dwa typy modeli – standardowe i kompaktowe. Modele kompaktowe wykorzystują różne techniki, aby zmniejszyć rozmiar modelu, dzięki czemu jest on wystarczająco mały, aby można go było pobrać i wdrożyć na urządzeniach IoT.

Podczas tworzenia klasyfikatora obrazów użyłeś domeny *Food*, wersji modelu zoptymalizowanej do trenowania na obrazach jedzenia. W Custom Vision możesz zmienić domenę swojego projektu, używając swoich danych treningowych do wytrenowania nowego modelu w nowej domenie. Wszystkie domeny obsługiwane przez Custom Vision są dostępne zarówno jako standardowe, jak i kompaktowe.

### Zadanie – wytrenuj swój model,
1. Uruchom portal Custom Vision na stronie [CustomVision.ai](https://customvision.ai) i zaloguj się, jeśli nie masz go już otwartego. Następnie otwórz swój projekt `fruit-quality-detector`.

1. Wybierz przycisk **Settings** (ikona ⚙).

1. Na liście *Domains* wybierz *Food (compact)*.

1. W sekcji *Export Capabilities* upewnij się, że wybrano *Basic platforms (Tensorflow, CoreML, ONNX, ...)*.

1. Na dole strony ustawień wybierz **Save Changes**.

1. Przeprowadź ponowne trenowanie modelu, klikając przycisk **Train** i wybierając opcję *Quick training*.

### Zadanie - eksportuj swój model

Po przetrenowaniu modelu należy go wyeksportować jako kontener.

1. Wybierz zakładkę **Performance** i znajdź najnowszą iterację, która została przetrenowana przy użyciu kompaktowej domeny.

1. Kliknij przycisk **Export** u góry.

1. Wybierz **DockerFile**, a następnie wybierz wersję pasującą do Twojego urządzenia brzegowego:

    * Jeśli używasz IoT Edge na komputerze z systemem Linux, Windows lub maszynie wirtualnej, wybierz wersję *Linux*.
    * Jeśli używasz IoT Edge na Raspberry Pi, wybierz wersję *ARM (Raspberry Pi 3)*.

> 🎓 Docker to jedno z najpopularniejszych narzędzi do zarządzania kontenerami, a DockerFile to zestaw instrukcji dotyczących konfiguracji kontenera.

1. Kliknij **Export**, aby Custom Vision utworzył odpowiednie pliki, a następnie **Download**, aby pobrać je w formie pliku zip.

1. Zapisz pliki na swoim komputerze, a następnie rozpakuj folder.

## Przygotowanie kontenera do wdrożenia

![Kontenery są budowane, a następnie przesyłane do rejestru kontenerów, skąd są wdrażane na urządzenie brzegowe za pomocą IoT Edge](../../../../../translated_images/pl/container-edge-flow.c246050dd60ceefd.webp)

Po pobraniu modelu należy go zbudować jako kontener, a następnie przesłać do rejestru kontenerów - miejsca online, w którym można przechowywać kontenery. IoT Edge może następnie pobrać kontener z rejestru i przesłać go na Twoje urządzenie.

![Logo Azure Container Registry](../../../../../translated_images/pl/azure-container-registry-logo.09494206991d4b29.webp)

Rejestr kontenerów, którego użyjesz w tej lekcji, to Azure Container Registry. Nie jest to usługa darmowa, więc aby zaoszczędzić pieniądze, upewnij się, że [posprzątasz swój projekt](../../../clean-up.md) po zakończeniu pracy.

> 💁 Koszty korzystania z Azure Container Registry można sprawdzić na stronie [cennika Azure Container Registry](https://azure.microsoft.com/pricing/details/container-registry/?WT.mc_id=academic-17441-jabenn).

### Zadanie - zainstaluj Docker

Aby zbudować i wdrożyć klasyfikator, może być konieczne zainstalowanie [Docker](https://www.docker.com/).

Musisz to zrobić tylko wtedy, gdy planujesz zbudować kontener na innym urządzeniu niż to, na którym zainstalowano IoT Edge - podczas instalacji IoT Edge Docker jest instalowany automatycznie.

1. Jeśli budujesz kontener Docker na innym urządzeniu niż Twoje urządzenie IoT Edge, postępuj zgodnie z instrukcjami instalacji Docker na stronie [Docker install page](https://www.docker.com/products/docker-desktop), aby zainstalować Docker Desktop lub silnik Docker. Upewnij się, że działa po instalacji.

### Zadanie - utwórz zasób rejestru kontenerów

1. Uruchom następujące polecenie w terminalu lub wierszu poleceń, aby utworzyć zasób Azure Container Registry:

    ```sh
    az acr create --resource-group fruit-quality-detector \
                  --sku Basic \
                  --name <Container registry name>
    ```

    Zastąp `<Container registry name>` unikalną nazwą dla swojego rejestru kontenerów, używając tylko liter i cyfr. Opartą na `fruitqualitydetector`. Ta nazwa stanie się częścią URL do dostępu do rejestru kontenerów, więc musi być globalnie unikalna.

1. Zaloguj się do Azure Container Registry za pomocą następującego polecenia:

    ```sh
    az acr login --name <Container registry name>
    ```

    Zastąp `<Container registry name>` nazwą, którą użyłeś dla swojego rejestru kontenerów.

1. Włącz tryb administratora dla rejestru kontenerów, aby móc wygenerować hasło, za pomocą następującego polecenia:

    ```sh
    az acr update --admin-enabled true \
                 --name <Container registry name>
    ```

    Zastąp `<Container registry name>` nazwą, którą użyłeś dla swojego rejestru kontenerów.

1. Wygeneruj hasła dla swojego rejestru kontenerów za pomocą następującego polecenia:

    ```sh
     az acr credential renew --password-name password \
                             --output table \
                             --name <Container registry name>
    ```

    Zastąp `<Container registry name>` nazwą, którą użyłeś dla swojego rejestru kontenerów.

    Skopiuj wartość `PASSWORD`, ponieważ będzie Ci potrzebna później.

### Zadanie - zbuduj swój kontener

To, co pobrałeś z Custom Vision, to DockerFile zawierający instrukcje dotyczące budowy kontenera, wraz z kodem aplikacji, który będzie uruchamiany wewnątrz kontenera, aby obsługiwać Twój model Custom Vision oraz REST API do jego wywoływania. Możesz użyć Docker, aby zbudować oznaczony kontener z DockerFile, a następnie przesłać go do rejestru kontenerów.

> 🎓 Kontenery są oznaczane tagiem, który definiuje ich nazwę i wersję. Gdy musisz zaktualizować kontener, możesz zbudować go z tym samym tagiem, ale nowszą wersją.

1. Otwórz terminal lub wiersz poleceń i przejdź do rozpakowanego modelu, który pobrałeś z Custom Vision.

1. Uruchom następujące polecenie, aby zbudować i oznaczyć obraz:

    ```sh
    docker build --platform <platform> -t <Container registry name>.azurecr.io/classifier:v1 .
    ```

    Zastąp `<platform>` platformą, na której będzie działał ten kontener. Jeśli używasz IoT Edge na Raspberry Pi, ustaw to na `linux/armhf`, w przeciwnym razie ustaw to na `linux/amd64`.

    > 💁 Jeśli uruchamiasz to polecenie z urządzenia, na którym działa IoT Edge, na przykład z Raspberry Pi, możesz pominąć część `--platform <platform>`, ponieważ domyślnie używana jest bieżąca platforma.

    Zastąp `<Container registry name>` nazwą, którą użyłeś dla swojego rejestru kontenerów.

    > 💁 Jeśli używasz systemu Linux lub Raspberry Pi OS, może być konieczne użycie `sudo`, aby uruchomić to polecenie.

    Docker zbuduje obraz, konfigurując całe potrzebne oprogramowanie. Obraz zostanie oznaczony jako `classifier:v1`.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker build --platform linux/amd64 -t  fruitqualitydetectorjimb.azurecr.io/classifier:v1 .
    [+] Building 102.4s (11/11) FINISHED
     => [internal] load build definition from Dockerfile
     => => transferring dockerfile: 131B
     => [internal] load .dockerignore
     => => transferring context: 2B
     => [internal] load metadata for docker.io/library/python:3.7-slim
     => [internal] load build context
     => => transferring context: 905B
     => [1/6] FROM docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => resolve docker.io/library/python:3.7-slim@sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6
     => => sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda 27.15MB / 27.15MB
     => => sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9 2.77MB / 2.77MB
     => => sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8 10.06MB / 10.06MB
     => => sha256:b21b91c9618e951a8cbca5b696424fa5e820800a88b7e7afd66bba0441a764d6 1.86kB / 1.86kB
     => => sha256:44073386687709c437586676b572ff45128ff1f1570153c2f727140d4a9accad 1.37kB / 1.37kB
     => => sha256:3d94f0f2ca798607808b771a7766f47ae62a26f820e871dd488baeccc69838d1 8.31kB / 8.31kB
     => => sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41 233B / 233B
     => => sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f 2.64MB / 2.64MB
     => => extracting sha256:b4d181a07f8025e00e0cb28f1cc14613da2ce26450b80c54aea537fa93cf3bda
     => => extracting sha256:de8ecf497b753094723ccf9cea8a46076e7cb845f333df99a6f4f397c93c6ea9
     => => extracting sha256:707b80804672b7c5d8f21e37c8396f319151e1298d976186b4f3b76ead9f10c8
     => => extracting sha256:283715715396fd56d0e90355125fd4ec57b4f0773f306fcd5fa353b998beeb41
     => => extracting sha256:8353afd48f6b84c3603ea49d204bdcf2a1daada15f5d6cad9cc916e186610a9f
     => [2/6] RUN pip install -U pip
     => [3/6] RUN pip install --no-cache-dir numpy~=1.17.5 tensorflow~=2.0.2 flask~=1.1.2 pillow~=7.2.0
     => [4/6] RUN pip install --no-cache-dir mscviplib==2.200731.16
     => [5/6] COPY app /app
     => [6/6] WORKDIR /app
     => exporting to image
     => => exporting layers
     => => writing image sha256:1846b6f134431f78507ba7c079358ed66d944c0e185ab53428276bd822400386
     => => naming to fruitqualitydetectorjimb.azurecr.io/classifier:v1
    ```

### Zadanie - prześlij swój kontener do rejestru kontenerów

1. Użyj następującego polecenia, aby przesłać swój kontener do rejestru kontenerów:

    ```sh
    docker push <Container registry name>.azurecr.io/classifier:v1
    ```

    Zastąp `<Container registry name>` nazwą, którą użyłeś dla swojego rejestru kontenerów.

    > 💁 Jeśli używasz systemu Linux, może być konieczne użycie `sudo`, aby uruchomić to polecenie.

    Kontener zostanie przesłany do rejestru kontenerów.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux docker push fruitqualitydetectorjimb.azurecr.io/classifier:v1
    The push refers to repository [fruitqualitydetectorjimb.azurecr.io/classifier]
    5f70bf18a086: Pushed 
    8a1ba9294a22: Pushed 
    56cf27184a76: Pushed 
    b32154f3f5dd: Pushed 
    36103e9a3104: Pushed 
    e2abb3cacca0: Pushed 
    4213fd357bbe: Pushed 
    7ea163ba4dce: Pushed 
    537313a13d90: Pushed 
    764055ebc9a7: Pushed 
    v1: digest: sha256:ea7894652e610de83a5a9e429618e763b8904284253f4fa0c9f65f0df3a5ded8 size: 2423
    ```

1. Aby zweryfikować przesłanie, możesz wyświetlić listę kontenerów w swoim rejestrze za pomocą następującego polecenia:

    ```sh
    az acr repository list --output table \
                           --name <Container registry name> 
    ```

    Zastąp `<Container registry name>` nazwą, którą użyłeś dla swojego rejestru kontenerów.

    ```output
    ➜  d4ccc45da0bb478bad287128e1274c3c.DockerFile.Linux az acr repository list --name fruitqualitydetectorjimb --output table
    Result
    ----------
    classifier
    ```

    W wynikach zobaczysz swój klasyfikator.

## Wdrożenie kontenera

Twój kontener może teraz zostać wdrożony na urządzeniu IoT Edge. Aby go wdrożyć, musisz zdefiniować manifest wdrożenia - dokument JSON, który zawiera listę modułów, które zostaną wdrożone na urządzeniu brzegowym.

### Zadanie - utwórz manifest wdrożenia

1. Utwórz nowy plik o nazwie `deployment.json` gdzieś na swoim komputerze.

1. Dodaj do tego pliku następujący kod:

    ```json
    {
        "content": {
            "modulesContent": {
                "$edgeAgent": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "runtime": {
                            "type": "docker",
                            "settings": {
                                "minDockerVersion": "v1.25",
                                "loggingOptions": "",
                                "registryCredentials": {
                                    "ClassifierRegistry": {
                                        "username": "<Container registry name>",
                                        "password": "<Container registry password>",
                                        "address": "<Container registry name>.azurecr.io"
                                      }
                                }
                            }
                        },
                        "systemModules": {
                            "edgeAgent": {
                                "type": "docker",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-agent:1.1",
                                    "createOptions": "{}"
                                }
                            },
                            "edgeHub": {
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "mcr.microsoft.com/azureiotedge-hub:1.1",
                                    "createOptions": "{\"HostConfig\":{\"PortBindings\":{\"5671/tcp\":[{\"HostPort\":\"5671\"}],\"8883/tcp\":[{\"HostPort\":\"8883\"}],\"443/tcp\":[{\"HostPort\":\"443\"}]}}}"
                                }
                            }
                        },
                        "modules": {
                            "ImageClassifier": {
                                "version": "1.0",
                                "type": "docker",
                                "status": "running",
                                "restartPolicy": "always",
                                "settings": {
                                    "image": "<Container registry name>.azurecr.io/classifier:v1",
                                    "createOptions": "{\"ExposedPorts\": {\"80/tcp\": {}},\"HostConfig\": {\"PortBindings\": {\"80/tcp\": [{\"HostPort\": \"80\"}]}}}"
                                }
                            }
                        }
                    }
                },
                "$edgeHub": {
                    "properties.desired": {
                        "schemaVersion": "1.1",
                        "routes": {
                            "upstream": "FROM /messages/* INTO $upstream"
                        },
                        "storeAndForwardConfiguration": {
                            "timeToLiveSecs": 7200
                        }
                    }
                }
            }
        }
    }
    ```

    > 💁 Ten plik można znaleźć w folderze [code-deployment/deployment](../../../../../4-manufacturing/lessons/3-run-fruit-detector-edge/code-deployment/deployment).

    Zastąp trzy wystąpienia `<Container registry name>` nazwą, którą użyłeś dla swojego rejestru kontenerów. Jedno znajduje się w sekcji modułu `ImageClassifier`, a dwa pozostałe w sekcji `registryCredentials`.

    Zastąp `<Container registry password>` w sekcji `registryCredentials` hasłem do swojego rejestru kontenerów.

1. Z folderu zawierającego manifest wdrożenia uruchom następujące polecenie:

    ```sh
    az iot edge set-modules --device-id fruit-quality-detector-edge \
                            --content deployment.json \
                            --hub-name <hub_name>
    ```

    Zastąp `<hub_name>` nazwą swojego IoT Hub.

    Moduł klasyfikatora obrazów zostanie wdrożony na Twoje urządzenie brzegowe.

### Zadanie - zweryfikuj działanie klasyfikatora

1. Połącz się z urządzeniem IoT Edge:

    * Jeśli używasz Raspberry Pi do uruchamiania IoT Edge, połącz się za pomocą ssh z terminala lub zdalnej sesji SSH w VS Code.
    * Jeśli uruchamiasz IoT Edge w kontenerze Linux na Windows, postępuj zgodnie z krokami w przewodniku [verify successful configuration guide](https://docs.microsoft.com/azure/iot-edge/how-to-install-iot-edge-on-windows?WT.mc_id=academic-17441-jabenn&view=iotedge-2018-06&tabs=powershell#verify-successful-configuration), aby połączyć się z urządzeniem IoT Edge.
    * Jeśli uruchamiasz IoT Edge na maszynie wirtualnej, możesz połączyć się z maszyną za pomocą ssh, używając `adminUsername` i `password`, które ustawiłeś podczas tworzenia VM, oraz używając adresu IP lub nazwy DNS:

        ```sh
        ssh <adminUsername>@<IP address>
        ```

        Lub:

        ```sh
        ssh <adminUsername>@<DNS Name>
        ```

        Wprowadź swoje hasło, gdy zostaniesz o to poproszony.

1. Po połączeniu uruchom następujące polecenie, aby uzyskać listę modułów IoT Edge:

    ```sh
    iotedge list
    ```

    > 💁 Może być konieczne uruchomienie tego polecenia z `sudo`.

    Zobaczysz działające moduły:

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge list
    NAME             STATUS           DESCRIPTION      CONFIG
    ImageClassifier  running          Up 42 minutes    fruitqualitydetectorjimb.azurecr.io/classifier:v1
    edgeAgent        running          Up 42 minutes    mcr.microsoft.com/azureiotedge-agent:1.1
    edgeHub          running          Up 42 minutes    mcr.microsoft.com/azureiotedge-hub:1.1
    ```

1. Sprawdź logi modułu klasyfikatora obrazów za pomocą następującego polecenia:

    ```sh
    iotedge logs ImageClassifier
    ```

    > 💁 Może być konieczne uruchomienie tego polecenia z `sudo`.

    ```output
    jim@fruit-quality-detector-jimb:~$ iotedge logs ImageClassifier
    2021-07-05 20:30:15.387144: I tensorflow/core/platform/cpu_feature_guard.cc:142] Your CPU supports instructions that this TensorFlow binary was not compiled to use: AVX2 FMA
    2021-07-05 20:30:15.392185: I tensorflow/core/platform/profile_utils/cpu_utils.cc:94] CPU Frequency: 2394450000 Hz
    2021-07-05 20:30:15.392712: I tensorflow/compiler/xla/service/service.cc:168] XLA service 0x55ed9ac83470 executing computations on platform Host. Devices:
    2021-07-05 20:30:15.392806: I tensorflow/compiler/xla/service/service.cc:175]   StreamExecutor device (0): Host, Default Version
    Loading model...Success!
    Loading labels...2 found. Success!
     * Serving Flask app "app" (lazy loading)
     * Environment: production
       WARNING: This is a development server. Do not use it in a production deployment.
       Use a production WSGI server instead.
     * Debug mode: off
     * Running on http://0.0.0.0:80/ (Press CTRL+C to quit)
    ```

### Zadanie - przetestuj klasyfikator obrazów

1. Możesz użyć CURL, aby przetestować klasyfikator obrazów, używając adresu IP lub nazwy hosta komputera, na którym działa agent IoT Edge. Znajdź adres IP:

    * Jeśli jesteś na tym samym urządzeniu, na którym działa IoT Edge, możesz użyć `localhost` jako nazwy hosta.
    * Jeśli używasz maszyny wirtualnej, możesz użyć adresu IP lub nazwy DNS maszyny wirtualnej.
    * W przeciwnym razie możesz uzyskać adres IP urządzenia, na którym działa IoT Edge:
      * Na Windows 10, postępuj zgodnie z przewodnikiem [find your IP address guide](https://support.microsoft.com/windows/find-your-ip-address-f21a9bbc-c582-55cd-35e0-73431160a1b9?WT.mc_id=academic-17441-jabenn).
      * Na macOS, postępuj zgodnie z przewodnikiem [how to find you IP address on a Mac guide](https://www.hellotech.com/guide/for/how-to-find-ip-address-on-mac).
      * Na Linux, postępuj zgodnie z sekcją dotyczącą znajdowania prywatnego adresu IP w przewodniku [how to find your IP address in Linux guide](https://opensource.com/article/18/5/how-find-ip-address-linux).

1. Możesz przetestować kontener za pomocą lokalnego pliku, uruchamiając następujące polecenie curl:

    ```sh
    curl --location \
         --request POST 'http://<IP address or name>/image' \
         --header 'Content-Type: image/png' \
         --data-binary '@<file_Name>' 
    ```

    Zastąp `<IP address or name>` adresem IP lub nazwą hosta komputera, na którym działa IoT Edge. Zastąp `<file_Name>` nazwą pliku do testowania.

    W wynikach zobaczysz wyniki predykcji:

    ```output
    {
        "created": "2021-07-05T21:44:39.573181",
        "id": "",
        "iteration": "",
        "predictions": [
            {
                "boundingBox": null,
                "probability": 0.9995615482330322,
                "tagId": "",
                "tagName": "ripe"
            },
            {
                "boundingBox": null,
                "probability": 0.0004384400090202689,
                "tagId": "",
                "tagName": "unripe"
            }
        ],
        "project": ""
    }
    ```

    > 💁 Nie ma potrzeby podawania klucza predykcji, ponieważ nie korzystasz z zasobu Azure. Zamiast tego bezpieczeństwo byłoby skonfigurowane w sieci wewnętrznej na podstawie wewnętrznych potrzeb bezpieczeństwa, a nie polegało na publicznym punkcie końcowym i kluczu API.

## Użyj swojego urządzenia IoT Edge

Teraz, gdy Twój klasyfikator obrazów został wdrożony na urządzeniu IoT Edge, możesz go używać z urządzenia IoT.

### Zadanie - użyj swojego urządzenia IoT Edge

Przejdź przez odpowiedni przewodnik, aby klasyfikować obrazy za pomocą klasyfikatora IoT Edge:

* [Arduino - Wio Terminal](wio-terminal.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie IoT](single-board-computer.md)

### Ponowne trenowanie modelu

Jednym z minusów uruchamiania klasyfikatorów obrazów na IoT Edge jest brak połączenia z projektem Custom Vision. Jeśli spojrzysz na zakładkę **Predictions** w Custom Vision, nie zobaczysz obrazów, które zostały sklasyfikowane za pomocą klasyfikatora Edge.

To oczekiwane zachowanie - obrazy nie są wysyłane do chmury w celu klasyfikacji, więc nie będą dostępne w chmurze. Jednym z plusów korzystania z IoT Edge jest prywatność, zapewniając, że obrazy nie opuszczają Twojej sieci, innym jest możliwość pracy offline, bez konieczności przesyłania obrazów, gdy urządzenie nie ma połączenia z internetem. Minusem jest poprawa modelu - musiałbyś wdrożyć inny sposób przechowywania obrazów, które można ręcznie sklasyfikować, aby poprawić i ponownie przetrenować klasyfikator obrazów.

✅ Zastanów się nad sposobami przesyłania obrazów w celu ponownego trenowania klasyfikatora.

---

## 🚀 Wyzwanie

Uruchamianie modeli AI na urządzeniach brzegowych może być szybsze niż w chmurze - skok sieciowy jest krótszy. Mogą być również wolniejsze, ponieważ sprzęt, na którym działa model, może nie być tak wydajny jak chmura.

Zrób pomiary czasu i porównaj, czy wywołanie urządzenia brzegowego jest szybsze czy wolniejsze niż wywołanie chmury? Zastanów się nad powodami różnicy lub jej braku. Zbadaj sposoby szybszego uruchamiania modeli AI na urządzeniach brzegowych, korzystając ze specjalistycznego sprzętu.

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/34)

## Przegląd i samodzielna nauka

* Przeczytaj więcej o kontenerach na stronie [OS-level virtualization na Wikipedii](https://wikipedia.org/wiki/OS-level_virtualization).
* Przeczytaj więcej o edge computing, ze szczególnym uwzględnieniem tego, jak technologia 5G może pomóc w rozwoju edge computing, w artykule [czym jest edge computing i dlaczego ma znaczenie? na stronie NetworkWorld](https://www.networkworld.com/article/3224893/what-is-edge-computing-and-how-its-changing-the-network.html)
* Dowiedz się więcej o uruchamianiu usług AI w IoT Edge, oglądając odcinek [dowiedz się, jak używać Azure IoT Edge na gotowej usłudze AI na Edge do wykrywania języka w serii Learn Live na Microsoft Channel9](https://channel9.msdn.com/Shows/Learn-Live/Sharpen-Your-AI-Edge-Skills-Episode-4-Learn-How-to-Use-Azure-IoT-Edge-on-a-Pre-Built-AI-Service-on-t?WT.mc_id=academic-17441-jabenn)

## Zadanie

[Uruchamianie innych usług na edge](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.