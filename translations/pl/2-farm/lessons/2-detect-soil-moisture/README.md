<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "4fb20273d299dc8d07a8f06c9cd0cdd9",
  "translation_date": "2025-08-26T06:50:29+00:00",
  "source_file": "2-farm/lessons/2-detect-soil-moisture/README.md",
  "language_code": "pl"
}
-->
C, wymawiane jako *I-kwadrat-C*, to protokół wielokontrolerowy i wieloperyferyjny, w którym każde podłączone urządzenie może działać jako kontroler lub peryferium, komunikując się za pośrednictwem magistrali I²C (nazwa systemu komunikacyjnego, który przesyła dane). Dane są przesyłane w postaci adresowanych pakietów, z każdym pakietem zawierającym adres urządzenia, do którego są przeznaczone.

> 💁 Ten model był wcześniej określany jako master/slave, ale ta terminologia jest wycofywana ze względu na jej skojarzenia z niewolnictwem. [Open Source Hardware Association przyjęło terminologię kontroler/peryferium](https://www.oshwa.org/a-resolution-to-redefine-spi-signal-names/), ale nadal można spotkać odniesienia do starej terminologii.

Urządzenia mają adres, który jest używany podczas ich podłączania do magistrali I²C i zazwyczaj jest on zakodowany na stałe w urządzeniu. Na przykład każdy typ czujnika Grove od Seeed ma ten sam adres, więc wszystkie czujniki światła mają ten sam adres, wszystkie przyciski mają ten sam adres, który różni się od adresu czujnika światła. Niektóre urządzenia mają możliwość zmiany adresu, na przykład poprzez zmianę ustawień zworki lub lutowanie pinów.

I²C ma magistralę składającą się z 2 głównych przewodów, wraz z 2 przewodami zasilającymi:

| Przewód | Nazwa | Opis |
| ---- | --------- | ----------- |
| SDA | Serial Data (Dane szeregowe) | Ten przewód służy do przesyłania danych między urządzeniami. |
| SCL | Serial Clock (Zegar szeregowy) | Ten przewód przesyła sygnał zegarowy z częstotliwością ustawioną przez kontroler. |
| VCC | Voltage common collector (Wspólny kolektor napięcia) | Zasilanie dla urządzeń. Jest podłączone do przewodów SDA i SCL, aby dostarczać im zasilanie za pośrednictwem rezystora podciągającego, który wyłącza sygnał, gdy żadne urządzenie nie jest kontrolerem. |
| GND | Ground (Masa) | Zapewnia wspólną masę dla obwodu elektrycznego. |

![Magistrala I2C z 3 urządzeniami podłączonymi do przewodów SDA i SCL, współdzieląca wspólny przewód masy](../../../../../translated_images/i2c.83da845dde02256bdd462dbe0d5145461416b74930571b89d1ae142841eeb584.pl.png)

Aby przesłać dane, jedno urządzenie wydaje warunek startu, aby pokazać, że jest gotowe do przesyłania danych. Następnie staje się kontrolerem. Kontroler wysyła adres urządzenia, z którym chce się komunikować, wraz z informacją, czy chce odczytać, czy zapisać dane. Po przesłaniu danych kontroler wysyła warunek stopu, aby wskazać, że zakończył. Po tym inne urządzenie może stać się kontrolerem i przesyłać lub odbierać dane.

I<sup>2</sup>C ma ograniczenia prędkości, z trzema różnymi trybami działającymi z ustalonymi prędkościami. Najszybszy to tryb High Speed z maksymalną prędkością 3,4 Mbps (megabitów na sekundę), choć bardzo niewiele urządzeń obsługuje tę prędkość. Na przykład Raspberry Pi jest ograniczone do trybu fast z prędkością 400 Kbps (kilobitów na sekundę). Tryb standardowy działa z prędkością 100 Kbps.

> 💁 Jeśli używasz Raspberry Pi z nakładką Grove Base jako swojego sprzętu IoT, możesz zobaczyć kilka gniazd I<sup>2</sup>C na płytce, które możesz wykorzystać do komunikacji z czujnikami I<sup>2</sup>C. Analogowe czujniki Grove również korzystają z I<sup>2</sup>C z przetwornikiem ADC, aby przesyłać wartości analogowe jako dane cyfrowe, więc czujnik światła, którego używałeś, symulował pin analogowy, a wartość była przesyłana przez I<sup>2</sup>C, ponieważ Raspberry Pi obsługuje tylko piny cyfrowe.

### Uniwersalny asynchroniczny odbiornik-nadajnik (UART)

UART obejmuje fizyczny układ, który pozwala dwóm urządzeniom komunikować się. Każde urządzenie ma 2 piny komunikacyjne - transmitujący (Tx) i odbierający (Rx), przy czym pin Tx pierwszego urządzenia jest połączony z pinem Rx drugiego urządzenia, a pin Tx drugiego urządzenia jest połączony z pinem Rx pierwszego urządzenia. Dzięki temu dane mogą być przesyłane w obu kierunkach.

* Urządzenie 1 przesyła dane ze swojego pinu Tx, które są odbierane przez urządzenie 2 na jego pinie Rx
* Urządzenie 1 odbiera dane na swoim pinie Rx, które są przesyłane przez urządzenie 2 z jego pinu Tx

![UART z pinem Tx jednego układu połączonym z pinem Rx innego i vice versa](../../../../../translated_images/uart.d0dbd3fb9e3728c6.pl.png)

> 🎓 Dane są przesyłane po jednym bicie na raz, co nazywa się komunikacją *szeregową*. Większość systemów operacyjnych i mikrokontrolerów ma *porty szeregowe*, czyli połączenia umożliwiające przesyłanie i odbieranie danych szeregowych, które są dostępne dla twojego kodu.

Urządzenia UART mają [prędkość transmisji](https://wikipedia.org/wiki/Symbol_rate) (znaną również jako Symbol rate), która określa szybkość przesyłania i odbierania danych w bitach na sekundę. Popularna prędkość transmisji to 9 600, co oznacza, że 9 600 bitów (0 i 1) danych jest przesyłanych każdą sekundę.

UART używa bitów startu i stopu - wysyła bit startu, aby wskazać, że zaraz wyśle bajt (8 bitów) danych, a następnie bit stopu po wysłaniu 8 bitów.

Prędkość UART zależy od sprzętu, ale nawet najszybsze implementacje nie przekraczają 6,5 Mbps (megabitów na sekundę, czyli milionów bitów, 0 lub 1, przesyłanych na sekundę).

Możesz używać UART przez piny GPIO - możesz ustawić jeden pin jako Tx, a inny jako Rx, a następnie połączyć je z innym urządzeniem.

> 💁 Jeśli używasz Raspberry Pi z nakładką Grove Base jako swojego sprzętu IoT, możesz zobaczyć gniazdo UART na płytce, które możesz wykorzystać do komunikacji z czujnikami korzystającymi z protokołu UART.

### Szeregowy interfejs peryferyjny (SPI)

SPI został zaprojektowany do komunikacji na krótkie odległości, na przykład na mikrokontrolerze do komunikacji z urządzeniem pamięci masowej, takim jak pamięć flash. Opiera się na modelu kontroler/peryferium, gdzie pojedynczy kontroler (zazwyczaj procesor urządzenia IoT) komunikuje się z wieloma peryferiami. Kontroler zarządza wszystkim, wybierając peryferium i wysyłając lub żądając danych.

> 💁 Podobnie jak w przypadku I<sup>2</sup>C, terminy kontroler i peryferium to niedawne zmiany, więc możesz spotkać się z użyciem starszych terminów.

Kontrolery SPI używają 3 przewodów, wraz z 1 dodatkowym przewodem na każde peryferium. Peryferia używają 4 przewodów. Te przewody to:

| Przewód | Nazwa | Opis |
| ---- | --------- | ----------- |
| COPI | Wyjście kontrolera, wejście peryferium | Ten przewód służy do przesyłania danych z kontrolera do peryferium. |
| CIPO | Wejście kontrolera, wyjście peryferium | Ten przewód służy do przesyłania danych z peryferium do kontrolera. |
| SCLK | Zegar szeregowy | Ten przewód przesyła sygnał zegarowy z prędkością ustawioną przez kontroler. |
| CS   | Wybór układu | Kontroler ma wiele przewodów, po jednym na każde peryferium, a każdy przewód łączy się z przewodem CS odpowiedniego peryferium. |

![SPI z jednym kontrolerem i dwoma peryferiami](../../../../../translated_images/spi.297431d6f98b386b.pl.png)

Przewód CS jest używany do aktywacji jednego peryferium naraz, komunikując się przez przewody COPI i CIPO. Gdy kontroler musi zmienić peryferium, dezaktywuje przewód CS połączony z obecnie aktywnym peryferium, a następnie aktywuje przewód połączony z peryferium, z którym chce się komunikować.

SPI jest *pełnodupleksowe*, co oznacza, że kontroler może jednocześnie wysyłać i odbierać dane z tego samego peryferium, używając przewodów COPI i CIPO. SPI używa sygnału zegarowego na przewodzie SCLK, aby utrzymać synchronizację urządzeń, więc w przeciwieństwie do przesyłania bezpośrednio przez UART, nie potrzebuje bitów startu i stopu.

Nie ma określonych ograniczeń prędkości dla SPI, a implementacje często mogą przesyłać wiele megabajtów danych na sekundę.

Zestawy deweloperskie IoT często obsługują SPI przez niektóre piny GPIO. Na przykład na Raspberry Pi możesz używać pinów GPIO 19, 21, 23, 24 i 26 do SPI.

### Bezprzewodowe

Niektóre czujniki mogą komunikować się za pomocą standardowych protokołów bezprzewodowych, takich jak Bluetooth (głównie Bluetooth Low Energy, czyli BLE), LoRaWAN (protokół sieciowy o niskim zużyciu energii i dużym zasięgu) lub WiFi. Umożliwia to zdalnym czujnikom działanie bez fizycznego połączenia z urządzeniem IoT.

Przykładem są komercyjne czujniki wilgotności gleby. Mierzą one wilgotność gleby na polu, a następnie przesyłają dane przez LoRaWAN do urządzenia centralnego, które przetwarza dane lub przesyła je przez Internet. Dzięki temu czujnik może znajdować się z dala od urządzenia IoT zarządzającego danymi, co zmniejsza zużycie energii i potrzebę dużych sieci WiFi lub długich kabli.

BLE jest popularne w zaawansowanych czujnikach, takich jak opaski fitness noszone na nadgarstku. Łączą one wiele czujników i przesyłają dane do urządzenia IoT, na przykład telefonu, za pomocą BLE.

✅ Czy masz jakieś czujniki Bluetooth przy sobie, w domu lub w szkole? Mogą to być czujniki temperatury, czujniki obecności, lokalizatory urządzeń lub urządzenia fitness.

Jednym z popularnych sposobów łączenia urządzeń komercyjnych jest Zigbee. Zigbee wykorzystuje WiFi do tworzenia sieci kratowych między urządzeniami, gdzie każde urządzenie łączy się z jak największą liczbą pobliskich urządzeń, tworząc dużą liczbę połączeń przypominających pajęczynę. Gdy jedno urządzenie chce wysłać wiadomość do Internetu, może przesłać ją do najbliższych urządzeń, które następnie przekazują ją dalej do innych pobliskich urządzeń i tak dalej, aż dotrze do koordynatora i zostanie przesłana do Internetu.

> 🐝 Nazwa Zigbee odnosi się do tańca pszczół miodnych po ich powrocie do ula.

## Pomiar poziomu wilgotności gleby

Możesz zmierzyć poziom wilgotności gleby za pomocą czujnika wilgotności gleby, urządzenia IoT i rośliny doniczkowej lub pobliskiego kawałka gleby.

### Zadanie - pomiar wilgotności gleby

Przejdź przez odpowiedni przewodnik, aby zmierzyć wilgotność gleby za pomocą swojego urządzenia IoT:

* [Arduino - Wio Terminal](wio-terminal-soil-moisture.md)
* [Komputer jednopłytkowy - Raspberry Pi](pi-soil-moisture.md)
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device-soil-moisture.md)

## Kalibracja czujników

Czujniki opierają się na pomiarze właściwości elektrycznych, takich jak rezystancja lub pojemność.

> 🎓 Rezystancja, mierzona w omach (Ω), to miara oporu, jaki napotyka prąd elektryczny przepływający przez coś. Gdy napięcie jest przyłożone do materiału, ilość prądu, który przez niego przepływa, zależy od rezystancji materiału. Więcej informacji znajdziesz na [stronie o rezystancji elektrycznej na Wikipedii](https://wikipedia.org/wiki/Electrical_resistance_and_conductance).

> 🎓 Pojemność, mierzona w faradach (F), to zdolność komponentu lub obwodu do gromadzenia i przechowywania energii elektrycznej. Więcej informacji znajdziesz na [stronie o pojemności na Wikipedii](https://wikipedia.org/wiki/Capacitance).

Te pomiary nie zawsze są użyteczne - wyobraź sobie czujnik temperatury, który podaje wynik 22,5 kΩ! Zamiast tego zmierzona wartość musi zostać przekształcona na użyteczną jednostkę poprzez kalibrację - czyli dopasowanie zmierzonych wartości do mierzonej wielkości, aby umożliwić przekształcenie nowych pomiarów na odpowiednią jednostkę.

Niektóre czujniki są fabrycznie skalibrowane. Na przykład czujnik temperatury, którego używałeś w poprzedniej lekcji, był już skalibrowany, aby mógł zwracać pomiar temperatury w °C. W fabryce pierwszy wyprodukowany czujnik był wystawiany na działanie znanych temperatur, a rezystancja była mierzona. Na tej podstawie opracowano obliczenia, które mogą przekształcać wartość zmierzoną w Ω (jednostka rezystancji) na °C.

> 💁 Wzór do obliczania rezystancji na podstawie temperatury to [równanie Steinharta–Harta](https://wikipedia.org/wiki/Steinhart–Hart_equation).

### Kalibracja czujnika wilgotności gleby

Wilgotność gleby jest mierzona za pomocą zawartości wody grawimetrycznej lub objętościowej.

* Grawimetryczna to waga wody w jednostce wagi gleby, mierzona jako liczba kilogramów wody na kilogram suchej gleby
* Objętościowa to objętość wody w jednostce objętości gleby, mierzona jako liczba metrów sześciennych wody na metry sześcienne suchej gleby

> 🇺🇸 Dla Amerykanów, ze względu na spójność jednostek, można to mierzyć w funtach zamiast kilogramów lub stopach sześciennych zamiast metrów sześciennych.

Czujniki wilgotności gleby mierzą rezystancję lub pojemność elektryczną - to zależy nie tylko od wilgotności gleby, ale także od jej rodzaju, ponieważ składniki gleby mogą zmieniać jej właściwości elektryczne. Idealnie czujniki powinny być skalibrowane - czyli odczyty z czujnika powinny być porównywane z pomiarami uzyskanymi bardziej naukową metodą. Na przykład laboratorium może obliczyć grawimetryczną wilgotność gleby, używając próbek z konkretnego pola pobranych kilka razy w roku, a te dane mogą być użyte do kalibracji czujnika, dopasowując odczyty czujnika do grawimetrycznej wilgotności gleby.

![Wykres napięcia w zależności od zawartości wilgoci w glebie](../../../../../translated_images/soil-moisture-to-voltage.df86d80cda158700.pl.png)

Powyższy wykres pokazuje, jak skalibrować czujnik. Napięcie jest rejestrowane dla próbki gleby, która następnie jest mierzona w laboratorium przez porównanie wilgotnej wagi z suchą wagą (mierząc wagę wilgotną, a następnie susząc w piecu i mierząc wagę suchą). Po wykonaniu kilku pomiarów można je nanieść na wykres i dopasować linię do punktów. Ta linia może być następnie użyta do przekształcenia odczytów czujnika wilgotności gleby wykonanych przez urządzenie IoT na rzeczywiste pomiary wilgotności gleby.

💁 W przypadku rezystancyjnych czujników wilgotności gleby napięcie wzrasta wraz ze wzrostem wilgotności gleby. W przypadku pojemnościowych czujników wilgotności gleby napięcie maleje wraz ze wzrostem wilgotności gleby, więc wykresy dla tych czujników będą opadać, a nie wznosić się.

![Wartość wilgotności gleby interpolowana z wykresu](../../../../../translated_images/soil-moisture-to-voltage-with-reading.681cb3e1f8b68caf.pl.png)

Powyższy wykres pokazuje odczyt napięcia z czujnika wilgotności gleby, a poprzez śledzenie tego do linii na wykresie można obliczyć rzeczywistą wilgotność gleby.

To podejście oznacza, że rolnik potrzebuje tylko kilku pomiarów laboratoryjnych dla pola, a następnie może używać urządzeń IoT do pomiaru wilgotności gleby - znacznie przyspieszając czas potrzebny na wykonanie pomiarów.

---

## 🚀 Wyzwanie

Rezystancyjne i pojemnościowe czujniki wilgotności gleby mają szereg różnic. Jakie są te różnice i który typ (jeśli w ogóle) jest najlepszy dla rolnika? Czy odpowiedź na to pytanie zmienia się w zależności od tego, czy mówimy o krajach rozwijających się, czy rozwiniętych?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/12)

## Przegląd i samodzielna nauka

Przeczytaj o sprzęcie i protokołach używanych przez czujniki i siłowniki:

* [Strona Wikipedii o GPIO](https://wikipedia.org/wiki/General-purpose_input/output)
* [Strona Wikipedii o UART](https://wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter)
* [Strona Wikipedii o SPI](https://wikipedia.org/wiki/Serial_Peripheral_Interface)
* [Strona Wikipedii o I<sup>2</sup>C](https://wikipedia.org/wiki/I²C)
* [Strona Wikipedii o Zigbee](https://wikipedia.org/wiki/Zigbee)

## Zadanie

[Skalibruj swój czujnik](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż staramy się zapewnić dokładność, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji krytycznych zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z korzystania z tego tłumaczenia.