<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "f74f4ccb61f00e5f7e9f49c3ed416e36",
  "translation_date": "2025-08-26T06:38:02+00:00",
  "source_file": "4-manufacturing/lessons/4-trigger-fruit-detector/README.md",
  "language_code": "pl"
}
-->
# Uruchamianie wykrywania jakości owoców za pomocą czujnika

![Szkicowy przegląd tej lekcji](../../../../../translated_images/lesson-18.92c32ed1d354caa5a54baa4032cf0b172d4655e8e326ad5d46c558a0def15365.pl.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/35)

## Wprowadzenie

Aplikacja IoT to nie tylko pojedyncze urządzenie zbierające dane i wysyłające je do chmury. Często składa się z wielu urządzeń współpracujących ze sobą, aby zbierać dane ze świata fizycznego za pomocą czujników, podejmować decyzje na podstawie tych danych i wchodzić w interakcję ze światem fizycznym za pomocą siłowników lub wizualizacji.

W tej lekcji dowiesz się więcej o projektowaniu złożonych aplikacji IoT, uwzględniających wiele czujników, różne usługi chmurowe do analizy i przechowywania danych oraz reakcje za pomocą siłowników. Nauczysz się, jak zaprojektować prototyp systemu kontroli jakości owoców, w tym jak używać czujników zbliżeniowych do uruchamiania aplikacji IoT oraz jak wygląda architektura tego prototypu.

W tej lekcji omówimy:

* [Projektowanie złożonych aplikacji IoT](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Projektowanie systemu kontroli jakości owoców](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Uruchamianie sprawdzania jakości owoców za pomocą czujnika](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Dane używane w detektorze jakości owoców](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Symulowanie wielu urządzeń IoT za pomocą urządzeń deweloperskich](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)
* [Przejście do produkcji](../../../../../4-manufacturing/lessons/4-trigger-fruit-detector)

> 🗑 To ostatnia lekcja w tym projekcie, więc po jej ukończeniu i wykonaniu zadania nie zapomnij usunąć swoich usług chmurowych. Będziesz ich potrzebować do ukończenia zadania, więc upewnij się, że najpierw je wykonasz.
>
> W razie potrzeby zapoznaj się z [przewodnikiem dotyczącym czyszczenia projektu](../../../clean-up.md), aby uzyskać instrukcje, jak to zrobić.

## Projektowanie złożonych aplikacji IoT

Aplikacje IoT składają się z wielu komponentów, w tym różnych urządzeń i usług internetowych.

Aplikacje IoT można opisać jako *urządzenia* (rzeczy) wysyłające dane, które generują *wnioski*. Te *wnioski* prowadzą do *działań*, które poprawiają biznes lub proces. Przykładem może być silnik (urządzenie) wysyłający dane o temperaturze. Dane te są wykorzystywane do oceny, czy silnik działa zgodnie z oczekiwaniami (wniosek). Na podstawie wniosku można proaktywnie zaplanować harmonogram konserwacji silnika (działanie).

* Różne urządzenia zbierają różne dane.
* Usługi IoT dostarczają wniosków na podstawie tych danych, czasami wzbogacając je o dane z dodatkowych źródeł.
* Te wnioski prowadzą do działań, takich jak sterowanie siłownikami w urządzeniach lub wizualizacja danych.

### Referencyjna architektura IoT

![Referencyjna architektura IoT](../../../../../translated_images/iot-reference-architecture.2278b98b55c6d4e89bde18eada3688d893861d43507641804dd2f9d3079cfaa0.pl.png)

Powyższy diagram przedstawia referencyjną architekturę IoT.

> 🎓 *Referencyjna architektura* to przykład architektury, którą można wykorzystać jako wzór przy projektowaniu nowych systemów. W tym przypadku, jeśli budujesz nowy system IoT, możesz skorzystać z tej architektury, zastępując urządzenia i usługi swoimi własnymi.

* **Urządzenia** to sprzęty zbierające dane z czujników, czasami współpracujące z usługami brzegowymi, aby interpretować te dane, np. klasyfikatory obrazów do interpretacji danych wizualnych. Dane z urządzeń są przesyłane do usługi IoT.
* **Wnioski** pochodzą z aplikacji bezserwerowych lub z analiz przeprowadzanych na przechowywanych danych.
* **Działania** mogą obejmować wysyłanie poleceń do urządzeń lub wizualizację danych, aby ludzie mogli podejmować decyzje.

![Referencyjna architektura IoT w Azure](../../../../../translated_images/iot-reference-architecture-azure.0b8d2161af924cb18ae48a8558a19541cca47f27264851b5b7e56d7b8bb372ac.pl.png)

Powyższy diagram przedstawia niektóre z komponentów i usług omówionych w tych lekcjach oraz ich powiązania w referencyjnej architekturze IoT.

* **Urządzenia** - pisałeś kod urządzeń do zbierania danych z czujników i analizy obrazów za pomocą Custom Vision, działającego zarówno w chmurze, jak i na urządzeniu brzegowym. Dane te były przesyłane do IoT Hub.
* **Wnioski** - używałeś Azure Functions do reagowania na wiadomości przesyłane do IoT Hub i przechowywałeś dane do późniejszej analizy w Azure Storage.
* **Działania** - sterowałeś siłownikami na podstawie decyzji podejmowanych w chmurze i poleceń wysyłanych do urządzeń oraz wizualizowałeś dane za pomocą Azure Maps.

✅ Pomyśl o innych urządzeniach IoT, z których korzystałeś, takich jak inteligentne urządzenia domowe. Jakie urządzenia, wnioski i działania są związane z tymi urządzeniami i ich oprogramowaniem?

Ten wzorzec można skalować w górę lub w dół, w zależności od potrzeb, dodając więcej urządzeń i usług.

### Dane i bezpieczeństwo

Projektując architekturę swojego systemu, musisz stale brać pod uwagę dane i bezpieczeństwo.

* Jakie dane wysyła i odbiera Twoje urządzenie?
* Jak te dane powinny być zabezpieczone i chronione?
* Jak powinien być kontrolowany dostęp do urządzenia i usługi chmurowej?

✅ Pomyśl o bezpieczeństwie danych w urządzeniach IoT, które posiadasz. Jakie dane są osobiste i powinny być chronione, zarówno podczas przesyłania, jak i przechowywania? Jakie dane nie powinny być przechowywane?

## Projektowanie systemu kontroli jakości owoców

Przełóżmy teraz koncepcję urządzeń, wniosków i działań na nasz detektor jakości owoców, aby zaprojektować większą aplikację end-to-end.

Wyobraź sobie, że otrzymałeś zadanie zbudowania detektora jakości owoców do wykorzystania w zakładzie przetwórczym. Owoce poruszają się na taśmie transportowej, gdzie obecnie pracownicy ręcznie sprawdzają ich jakość i usuwają niedojrzałe owoce. Aby obniżyć koszty, właściciel zakładu chce zautomatyzować ten proces.

✅ Jednym z trendów związanych z rozwojem IoT (i technologii ogólnie) jest zastępowanie prac manualnych maszynami. Zrób badania: Ile miejsc pracy szacuje się, że zostanie utraconych przez IoT? Ile nowych miejsc pracy zostanie stworzonych przy budowie urządzeń IoT?

Musisz zbudować system, w którym owoce są wykrywane, gdy docierają na taśmę, następnie są fotografowane i sprawdzane za pomocą modelu AI działającego na urządzeniu brzegowym. Wyniki są przesyłane do chmury, a jeśli owoc jest niedojrzały, wyświetlane jest powiadomienie, aby można było go usunąć.

|   |   |
| - | - |
| **Urządzenia** | Czujnik wykrywający owoce na taśmie<br>Aparat fotograficzny do robienia zdjęć i klasyfikacji owoców<br>Urządzenie brzegowe uruchamiające klasyfikator<br>Urządzenie powiadamiające o niedojrzałych owocach |
| **Wnioski** | Decyzja o sprawdzeniu dojrzałości owoców<br>Przechowywanie wyników klasyfikacji<br>Określenie potrzeby powiadomienia o niedojrzałych owocach |
| **Działania** | Wysłanie polecenia do urządzenia, aby sfotografować owoce i sprawdzić je za pomocą klasyfikatora obrazów<br>Wysłanie polecenia do urządzenia, aby powiadomić o niedojrzałych owocach |

### Prototypowanie aplikacji

![Referencyjna architektura IoT dla sprawdzania jakości owoców](../../../../../translated_images/iot-reference-architecture-fruit-quality.cc705f121c3b6fa71c800d9630935ac34bc08223a04601e35f41d5e9b5dd5207.pl.png)

Powyższy diagram przedstawia referencyjną architekturę dla tego prototypu aplikacji.

* Urządzenie IoT z czujnikiem zbliżeniowym wykrywa pojawienie się owocu. Wysyła wiadomość do chmury, informując o wykryciu owocu.
* Aplikacja bezserwerowa w chmurze wysyła polecenie do innego urządzenia, aby zrobić zdjęcie i przeprowadzić klasyfikację obrazu.
* Urządzenie IoT z kamerą robi zdjęcie i przesyła je do klasyfikatora obrazów działającego na urządzeniu brzegowym. Wyniki są następnie przesyłane do chmury.
* Aplikacja bezserwerowa w chmurze przechowuje te informacje do późniejszej analizy, aby sprawdzić, jaki procent owoców jest niedojrzały. Jeśli owoc jest niedojrzały, wysyła polecenie do innego urządzenia IoT, aby powiadomić pracowników fabryki za pomocą diody LED.

> 💁 Cała ta aplikacja IoT mogłaby być zaimplementowana jako jedno urządzenie, z całą logiką uruchamiania klasyfikacji obrazu i sterowania diodą LED wbudowaną. Mogłaby używać IoT Hub tylko do śledzenia liczby wykrytych niedojrzałych owoców i konfiguracji urządzenia. W tej lekcji aplikacja została rozszerzona, aby pokazać koncepcje dla dużych aplikacji IoT.

W prototypie zaimplementujesz wszystko na jednym urządzeniu. Jeśli używasz mikrokontrolera, będziesz potrzebować oddzielnego urządzenia brzegowego do uruchamiania klasyfikatora obrazów. Większość potrzebnych rzeczy już poznałeś.

## Uruchamianie sprawdzania jakości owoców za pomocą czujnika

Urządzenie IoT potrzebuje jakiegoś wyzwalacza, aby wskazać, kiedy owoc jest gotowy do klasyfikacji. Jednym z takich wyzwalaczy może być pomiar odległości do czujnika, aby sprawdzić, czy owoc znajduje się w odpowiednim miejscu na taśmie.

![Czujniki zbliżeniowe wysyłają wiązki laserowe do obiektów, takich jak banany, i mierzą czas odbicia](../../../../../translated_images/proximity-sensor.f5cd752c77fb62fe.pl.png)

Czujniki zbliżeniowe mogą być używane do pomiaru odległości od czujnika do obiektu. Zazwyczaj wysyłają wiązkę promieniowania elektromagnetycznego, taką jak wiązka laserowa lub światło podczerwone, a następnie wykrywają odbite promieniowanie. Czas między wysłaniem wiązki a odbiciem sygnału może być użyty do obliczenia odległości do czujnika.

> 💁 Prawdopodobnie używałeś czujników zbliżeniowych, nawet o tym nie wiedząc. Większość smartfonów wyłącza ekran, gdy trzymasz je przy uchu, aby zapobiec przypadkowemu zakończeniu połączenia płatkiem ucha. Działa to dzięki czujnikowi zbliżeniowemu, który wykrywa obiekt blisko ekranu podczas rozmowy i wyłącza funkcje dotykowe, dopóki telefon nie znajdzie się w odpowiedniej odległości.

### Zadanie - uruchamianie wykrywania jakości owoców za pomocą czujnika odległości

Przejdź przez odpowiedni przewodnik, aby użyć czujnika zbliżeniowego do wykrywania obiektu za pomocą swojego urządzenia IoT:

* [Arduino - Wio Terminal](wio-terminal-proximity.md)
* [Komputer jednopłytkowy - Raspberry Pi](pi-proximity.md)
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device-proximity.md)

## Dane używane w detektorze jakości owoców

Prototyp detektora owoców składa się z wielu komponentów komunikujących się ze sobą.

![Komponenty komunikujące się ze sobą](../../../../../translated_images/fruit-quality-detector-message-flow.adf2a65da8fd8741ac7af11361574de89adc126785d67606bb4d2ec00467e380.pl.png)

* Czujnik zbliżeniowy mierzący odległość do owocu i wysyłający te dane do IoT Hub
* Polecenie sterujące kamerą wysyłane z IoT Hub do urządzenia z kamerą
* Wyniki klasyfikacji obrazu przesyłane do IoT Hub
* Polecenie sterujące diodą LED, aby powiadomić o niedojrzałym owocu, wysyłane z IoT Hub do urządzenia z diodą LED

Warto zdefiniować strukturę tych wiadomości z wyprzedzeniem, zanim zaczniesz budować aplikację.

> 💁 Praktycznie każdy doświadczony programista przynajmniej raz w swojej karierze spędził godziny, dni, a nawet tygodnie na rozwiązywaniu problemów spowodowanych różnicami między danymi wysyłanymi a oczekiwanymi.

Na przykład - jeśli przesyłasz informacje o temperaturze, jak zdefiniowałbyś JSON? Możesz mieć pole o nazwie `temperature`, albo użyć powszechnego skrótu `temp`.

```json
{
    "temperature": 20.7
}
```

w porównaniu do:

```json
{
    "temp": 20.7
}
```

Musisz także wziąć pod uwagę jednostki - czy temperatura jest w °C czy °F? Jeśli mierzysz temperaturę za pomocą urządzenia konsumenckiego i użytkownik zmienia jednostki wyświetlania, musisz upewnić się, że jednostki przesyłane do chmury pozostają spójne.

✅ Zrób badania: Jak problemy z jednostkami spowodowały katastrofę sondy Mars Climate Orbiter, która kosztowała 125 milionów dolarów?

Pomyśl o danych przesyłanych w detektorze jakości owoców. Jak zdefiniowałbyś każdą wiadomość? Gdzie analizowałbyś dane i podejmował decyzje o tym, jakie dane przesyłać?

Na przykład - uruchamianie klasyfikacji obrazu za pomocą czujnika zbliżeniowego. Urządzenie IoT mierzy odległość, ale gdzie podejmowana jest decyzja? Czy urządzenie decyduje, że owoc jest wystarczająco blisko i wysyła wiadomość do IoT Hub, aby uruchomić klasyfikację? Czy może przesyła pomiary odległości, a decyzja jest podejmowana w IoT Hub?

Odpowiedź na takie pytania brzmi - to zależy. Każdy przypadek użycia jest inny, dlatego jako programista IoT musisz rozumieć system, który budujesz, sposób jego użytkowania i dane, które wykrywa.

* Jeśli decyzja jest podejmowana przez IoT Hub, musisz przesyłać wiele pomiarów odległości.
* Jeśli przesyłasz zbyt wiele wiadomości, zwiększa to koszty IoT Hub i ilość potrzebnej przepustowości urządzeń IoT (szczególnie w fabryce z milionami urządzeń). Może to również spowolnić urządzenie.
* Jeśli decyzja jest podejmowana na urządzeniu, musisz zapewnić sposób konfiguracji urządzenia w celu dostrojenia maszyny.

## Symulowanie wielu urządzeń IoT za pomocą urządzeń deweloperskich

Aby zbudować swój prototyp, będziesz potrzebować swojego zestawu deweloperskiego IoT, aby działał jak wiele urządzeń, przesyłając dane telemetryczne i reagując na polecenia.

### Symulowanie wielu urządzeń IoT na Raspberry Pi lub wirtualnym sprzęcie IoT

Korzystając z komputera jednopłytkowego, takiego jak Raspberry Pi, możesz uruchamiać wiele aplikacji jednocześnie. Oznacza to, że możesz symulować wiele urządzeń IoT, tworząc wiele aplikacji, po jednej na każde "urządzenie IoT". Na przykład możesz zaimplementować każde urządzenie jako oddzielny plik Python i uruchamiać je w różnych sesjach terminala.
> 💁 Pamiętaj, że niektóre urządzenia mogą nie działać, gdy są używane jednocześnie przez wiele aplikacji.
### Symulacja wielu urządzeń na mikrokontrolerze

Symulowanie wielu urządzeń na mikrokontrolerach jest bardziej skomplikowane. W przeciwieństwie do komputerów jednopłytkowych, nie można uruchamiać wielu aplikacji jednocześnie – cała logika dla wszystkich oddzielnych urządzeń IoT musi być zawarta w jednej aplikacji.

Kilka sugestii, które mogą ułatwić ten proces:

* Utwórz jedną lub więcej klas dla każdego urządzenia IoT – na przykład klasy o nazwach `DistanceSensor`, `ClassifierCamera`, `LEDController`. Każda z nich może mieć własne metody `setup` i `loop`, które będą wywoływane przez główne funkcje `setup` i `loop`.
* Obsługuj polecenia w jednym miejscu i kieruj je do odpowiedniej klasy urządzenia w razie potrzeby.
* W głównej funkcji `loop` musisz uwzględnić czas działania każdego urządzenia. Na przykład, jeśli jedna klasa urządzenia musi być przetwarzana co 10 sekund, a inna co 1 sekundę, w głównej funkcji `loop` użyj opóźnienia 1 sekundy. Każde wywołanie `loop` uruchamia odpowiedni kod dla urządzenia, które musi być przetwarzane co sekundę, a licznik zlicza każde wywołanie pętli, przetwarzając inne urządzenie, gdy licznik osiągnie 10 (po czym licznik jest resetowany).

## Przejście do produkcji

Prototyp będzie stanowił podstawę finalnego systemu produkcyjnego. Niektóre różnice, które pojawią się podczas przejścia do produkcji, to:

* Wzmocnione komponenty – używanie sprzętu zaprojektowanego tak, aby wytrzymał hałas, ciepło, wibracje i obciążenia w fabryce.
* Wykorzystanie komunikacji wewnętrznej – niektóre komponenty będą komunikować się bezpośrednio, unikając przesyłania danych do chmury, a dane będą wysyłane do chmury jedynie w celu ich przechowywania. Sposób realizacji tego zależy od konfiguracji fabryki – może to być bezpośrednia komunikacja lub uruchamianie części usługi IoT na brzegu sieci za pomocą urządzenia bramowego.
* Opcje konfiguracji – każda fabryka i przypadek użycia są inne, więc sprzęt musi być konfigurowalny. Na przykład czujnik zbliżeniowy może wymagać wykrywania różnych owoców na różnych odległościach. Zamiast na stałe zakodować odległość wyzwalającą klasyfikację, warto, aby była ona konfigurowalna przez chmurę, na przykład za pomocą bliźniaka urządzenia.
* Automatyczne usuwanie owoców – zamiast używać diody LED do sygnalizowania, że owoc jest niedojrzały, automatyczne urządzenia mogłyby go usuwać.

✅ Zrób badania: W jaki inny sposób urządzenia produkcyjne różnią się od zestawów deweloperskich?

---

## 🚀 Wyzwanie

W tej lekcji nauczyłeś się kilku koncepcji potrzebnych do zaprojektowania systemu IoT. Przypomnij sobie wcześniejsze projekty. Jak wpisują się one w przedstawioną powyżej referencyjną architekturę?

Wybierz jeden z dotychczasowych projektów i zastanów się nad projektem bardziej złożonego rozwiązania, które łączy wiele funkcji wykraczających poza to, co zostało omówione w projektach. Narysuj architekturę i pomyśl o wszystkich urządzeniach i usługach, które byłyby potrzebne.

Na przykład – urządzenie do śledzenia pojazdów, które łączy GPS z czujnikami monitorującymi takie parametry jak temperatura w chłodni, czas włączania i wyłączania silnika oraz tożsamość kierowcy. Jakie urządzenia są zaangażowane, jakie usługi są potrzebne, jakie dane są przesyłane oraz jakie kwestie bezpieczeństwa i prywatności należy uwzględnić?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/36)

## Przegląd i samodzielna nauka

* Przeczytaj więcej o architekturze IoT w [dokumentacji referencyjnej architektury IoT Azure na stronie Microsoft docs](https://docs.microsoft.com/azure/architecture/reference-architectures/iot?WT.mc_id=academic-17441-jabenn)
* Dowiedz się więcej o bliźniakach urządzeń w [dokumentacji IoT Hub na stronie Microsoft docs](https://docs.microsoft.com/azure/iot-hub/iot-hub-devguide-device-twins?WT.mc_id=academic-17441-jabenn)
* Przeczytaj o OPC-UA, protokole komunikacji między maszynami używanym w automatyzacji przemysłowej, na [stronie OPC-UA w Wikipedii](https://wikipedia.org/wiki/OPC_Unified_Architecture)

## Zadanie

[Zbuduj detektor jakości owoców](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.