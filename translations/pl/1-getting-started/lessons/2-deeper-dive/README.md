<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "9dd7f645ad1c6f20b72fee512987f772",
  "translation_date": "2025-08-26T07:09:50+00:00",
  "source_file": "1-getting-started/lessons/2-deeper-dive/README.md",
  "language_code": "pl"
}
-->
# Głębsze spojrzenie na IoT

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-2.324b0580d620c25e0a24fb7fddfc0b29a846dd4b82c08e7a9466d580ee78ce51.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ta lekcja była częścią serii [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) prowadzonej przez [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcja została podzielona na dwa filmy: godzinny wykład oraz godzinne konsultacje, podczas których szczegółowo omówiono wybrane zagadnienia i odpowiadano na pytania.

[![Lekcja 2: Głębsze spojrzenie na IoT](https://img.youtube.com/vi/t0SySWw3z9M/0.jpg)](https://youtu.be/t0SySWw3z9M)

[![Lekcja 2: Głębsze spojrzenie na IoT - Konsultacje](https://img.youtube.com/vi/tTZYf9EST1E/0.jpg)](https://youtu.be/tTZYf9EST1E)

> 🎥 Kliknij obrazy powyżej, aby obejrzeć filmy

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/3)

## Wprowadzenie

W tej lekcji zagłębimy się w niektóre z koncepcji omówionych w poprzedniej lekcji.

W tej lekcji omówimy:

* [Komponenty aplikacji IoT](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Głębsze spojrzenie na mikrokontrolery](../../../../../1-getting-started/lessons/2-deeper-dive)
* [Głębsze spojrzenie na komputery jednopłytkowe](../../../../../1-getting-started/lessons/2-deeper-dive)

## Komponenty aplikacji IoT

Dwa główne komponenty aplikacji IoT to *Internet* i *urządzenie*. Przyjrzyjmy się im bliżej.

### Urządzenie

![Raspberry Pi 4](../../../../../translated_images/pl/raspberry-pi-4.fd4590d308c3d456.webp)

Część **Urządzenie** w IoT odnosi się do urządzenia, które może wchodzić w interakcję ze światem fizycznym. Są to zazwyczaj małe, niedrogie komputery, działające z niską prędkością i zużywające niewiele energii – na przykład proste mikrokontrolery z kilobajtami pamięci RAM (w porównaniu do gigabajtów w komputerach PC), działające z częstotliwością kilkuset megaherców (w porównaniu do gigaherców w komputerach PC), ale zużywające tak mało energii, że mogą działać przez tygodnie, miesiące, a nawet lata na bateriach.

Urządzenia te wchodzą w interakcję ze światem fizycznym, używając czujników do zbierania danych z otoczenia lub kontrolując wyjścia czy siłowniki, aby wprowadzać zmiany fizyczne. Typowym przykładem jest inteligentny termostat – urządzenie wyposażone w czujnik temperatury, sposób ustawiania pożądanej temperatury, np. za pomocą pokrętła lub ekranu dotykowego, oraz połączenie z systemem grzewczym lub chłodzącym, który można włączyć, gdy wykryta temperatura jest poza zakresem docelowym. Czujnik temperatury wykrywa, że w pomieszczeniu jest za zimno, a siłownik włącza ogrzewanie.

![Schemat pokazujący temperaturę i pokrętło jako wejścia do urządzenia IoT oraz kontrolę grzejnika jako wyjście](../../../../../translated_images/pl/basic-thermostat.a923217fd1f37e5a6f3390396a65c22a387419ea2dd17e518ec24315ba6ae9a8.png)

Istnieje ogromna różnorodność urządzeń, które mogą działać jako urządzenia IoT – od dedykowanego sprzętu wykrywającego jedno zjawisko, po urządzenia ogólnego przeznaczenia, a nawet Twój smartfon! Smartfon może używać czujników do wykrywania otoczenia i siłowników do interakcji ze światem – na przykład używając czujnika GPS do określenia lokalizacji i głośnika do przekazywania instrukcji nawigacyjnych.

✅ Pomyśl o innych systemach wokół Ciebie, które odczytują dane z czujnika i wykorzystują je do podejmowania decyzji. Jednym z przykładów może być termostat w piekarniku. Czy znajdziesz więcej?

### Internet

Część **Internet** w aplikacji IoT obejmuje aplikacje, z którymi urządzenie IoT może się łączyć, aby wysyłać i odbierać dane, a także inne aplikacje, które mogą przetwarzać dane z urządzenia IoT i pomagać w podejmowaniu decyzji dotyczących żądań wysyłanych do siłowników urządzenia IoT.

Typowym rozwiązaniem jest korzystanie z jakiejś usługi w chmurze, z którą urządzenie IoT się łączy. Taka usługa zajmuje się kwestiami bezpieczeństwa, odbieraniem wiadomości od urządzenia IoT i wysyłaniem wiadomości z powrotem do urządzenia. Usługa w chmurze może następnie łączyć się z innymi aplikacjami, które mogą przetwarzać lub przechowywać dane z czujników, albo wykorzystywać te dane wraz z danymi z innych systemów do podejmowania decyzji.

Urządzenia nie zawsze łączą się bezpośrednio z Internetem za pomocą WiFi lub połączeń przewodowych. Niektóre urządzenia korzystają z sieci kratowych, aby komunikować się ze sobą za pomocą technologii takich jak Bluetooth, łącząc się przez urządzenie centralne, które ma połączenie z Internetem.

W przypadku inteligentnego termostatu, termostat łączyłby się z domową siecią WiFi i usługą w chmurze. Wysyłałby dane o temperaturze do tej usługi, a stamtąd byłyby one zapisywane w bazie danych, umożliwiając właścicielowi domu sprawdzenie aktualnej i przeszłej temperatury za pomocą aplikacji na telefonie. Inna usługa w chmurze wiedziałaby, jaką temperaturę chce właściciel domu, i wysyłałaby wiadomości z powrotem do urządzenia IoT za pośrednictwem usługi w chmurze, aby poinformować system grzewczy, czy ma się włączyć lub wyłączyć.

![Schemat pokazujący temperaturę i pokrętło jako wejścia do urządzenia IoT, urządzenie IoT z dwukierunkową komunikacją z chmurą, która z kolei ma dwukierunkową komunikację z telefonem, oraz kontrolę grzejnika jako wyjście z urządzenia IoT](../../../../../translated_images/pl/mobile-controlled-thermostat.4a994010473d8d6a52ba68c67e5f02dc8928c717e93ca4b9bc55525aa75bbb60.png)

Jeszcze bardziej zaawansowana wersja mogłaby korzystać ze sztucznej inteligencji w chmurze, wykorzystując dane z innych czujników podłączonych do innych urządzeń IoT, takich jak czujniki obecności wykrywające, które pomieszczenia są używane, a także dane takie jak pogoda czy Twój kalendarz, aby inteligentnie ustawiać temperaturę. Na przykład mogłaby wyłączyć ogrzewanie, jeśli z kalendarza wynika, że jesteś na wakacjach, lub wyłączać ogrzewanie w poszczególnych pomieszczeniach w zależności od tego, które z nich są używane, ucząc się na podstawie danych, aby z czasem być coraz bardziej precyzyjną.

![Schemat pokazujący wiele czujników temperatury i pokrętło jako wejścia do urządzenia IoT, urządzenie IoT z dwukierunkową komunikacją z chmurą, która z kolei ma dwukierunkową komunikację z telefonem, kalendarzem i usługą pogodową, oraz kontrolę grzejnika jako wyjście z urządzenia IoT](../../../../../translated_images/pl/smarter-thermostat.a75855f15d2d9e63.webp)

✅ Jakie inne dane mogłyby pomóc w stworzeniu inteligentniejszego termostatu podłączonego do Internetu?

### IoT na krawędzi

Chociaż litera "I" w IoT oznacza Internet, urządzenia te nie muszą łączyć się z Internetem. W niektórych przypadkach urządzenia mogą łączyć się z urządzeniami brzegowymi – urządzeniami bramkowymi działającymi w Twojej lokalnej sieci, co pozwala na przetwarzanie danych bez konieczności korzystania z połączenia internetowego. Może to być szybsze, gdy masz dużo danych lub wolne połączenie internetowe, pozwala działać offline w miejscach, gdzie połączenie z Internetem nie jest możliwe, takich jak statek czy obszar dotknięty katastrofą podczas akcji humanitarnej, a także pozwala zachować prywatność danych. Niektóre urządzenia zawierają kod przetwarzający stworzony za pomocą narzędzi chmurowych i uruchamiają go lokalnie, aby zbierać i reagować na dane bez użycia połączenia internetowego do podejmowania decyzji.

Przykładem może być inteligentne urządzenie domowe, takie jak Apple HomePod, Amazon Alexa czy Google Home, które nasłuchuje Twojego głosu za pomocą modeli AI wytrenowanych w chmurze, ale działających lokalnie na urządzeniu. Urządzenia te "budzą się", gdy wypowiesz określone słowo lub frazę, i dopiero wtedy przesyłają Twoją mowę przez Internet do przetworzenia. Urządzenie przestaje przesyłać mowę w odpowiednim momencie, na przykład gdy wykryje pauzę w Twojej wypowiedzi. Wszystko, co powiesz przed obudzeniem urządzenia za pomocą słowa kluczowego, i wszystko, co powiesz po tym, jak urządzenie przestanie słuchać, nie zostanie przesłane przez Internet do dostawcy urządzenia, a zatem pozostanie prywatne.

✅ Pomyśl o innych scenariuszach, w których prywatność jest ważna, więc przetwarzanie danych byłoby lepsze na krawędzi niż w chmurze. Podpowiedź – pomyśl o urządzeniach IoT z kamerami lub innymi urządzeniami obrazującymi.

### Bezpieczeństwo IoT

W przypadku każdego połączenia z Internetem bezpieczeństwo jest ważnym zagadnieniem. Istnieje stare powiedzenie, że "litera S w IoT oznacza bezpieczeństwo" – w IoT nie ma litery "S", co sugeruje, że nie jest ono bezpieczne.

Urządzenia IoT łączą się z usługą w chmurze, a zatem są tak bezpieczne, jak ta usługa w chmurze – jeśli Twoja usługa w chmurze pozwala na połączenie dowolnego urządzenia, może dojść do przesyłania złośliwych danych lub ataków wirusowych. Może to mieć bardzo realne konsekwencje, ponieważ urządzenia IoT wchodzą w interakcję i kontrolują inne urządzenia. Na przykład [robak Stuxnet](https://wikipedia.org/wiki/Stuxnet) manipulował zaworami w wirówkach, aby je uszkodzić. Hakerzy wykorzystali również [słabe zabezpieczenia, aby uzyskać dostęp do monitorów dla dzieci](https://www.npr.org/sections/thetwo-way/2018/06/05/617196788/s-c-mom-says-baby-monitor-was-hacked-experts-say-many-devices-are-vulnerable) i innych urządzeń monitorujących w domach.

> 💁 Czasami urządzenia IoT i urządzenia brzegowe działają w sieci całkowicie odizolowanej od Internetu, aby zachować prywatność i bezpieczeństwo danych. Jest to znane jako [air-gapping](https://wikipedia.org/wiki/Air_gap_(networking)).

## Głębsze spojrzenie na mikrokontrolery

W poprzedniej lekcji wprowadziliśmy mikrokontrolery. Teraz przyjrzyjmy się im bliżej.

### CPU

CPU to "mózg" mikrokontrolera. Jest to procesor, który uruchamia Twój kod i może wysyłać dane do oraz odbierać dane od podłączonych urządzeń. CPU może zawierać jeden lub więcej rdzeni – w zasadzie jeden lub więcej procesorów, które mogą współpracować, aby uruchamiać Twój kod.

CPU opiera się na zegarze, który tyka miliony lub miliardy razy na sekundę. Każde tyknięcie, czyli cykl, synchronizuje działania, które CPU może wykonać. Przy każdym tyknięciu CPU może wykonać instrukcję z programu, na przykład pobrać dane z urządzenia zewnętrznego lub wykonać obliczenie matematyczne. Ten regularny cykl pozwala na zakończenie wszystkich działań przed przetworzeniem kolejnej instrukcji.

Im szybszy cykl zegara, tym więcej instrukcji można przetworzyć w ciągu sekundy, a zatem tym szybszy jest CPU. Prędkości CPU mierzy się w [hercach (Hz)](https://wikipedia.org/wiki/Hertz), standardowej jednostce, gdzie 1 Hz oznacza jeden cykl lub tyknięcie zegara na sekundę.

> 🎓 Prędkości CPU często podaje się w MHz lub GHz. 1 MHz to 1 milion Hz, 1 GHz to 1 miliard Hz.

> 💁 CPU wykonuje programy za pomocą [cyklu pobierania-dekodowania-wykonywania](https://wikipedia.org/wiki/Instruction_cycle). Przy każdym tyknięciu zegara CPU pobiera kolejną instrukcję z pamięci, dekoduje ją, a następnie wykonuje, na przykład używając jednostki arytmetyczno-logicznej (ALU) do dodania dwóch liczb. Niektóre instrukcje wymagają wielu cykli do wykonania, więc kolejny cykl rozpoczyna się przy następnym tyknięciu po zakończeniu instrukcji.

![Cykl pobierania-dekodowania-wykonywania pokazujący pobieranie instrukcji z programu przechowywanego w RAM, a następnie dekodowanie i wykonywanie jej na CPU](../../../../../translated_images/pl/fetch-decode-execute.2fd6f150f6280392807f4475382319abd0cee0b90058e1735444d6baa6f2078c.png)

Mikrokontrolery mają znacznie niższe prędkości zegara niż komputery stacjonarne, laptopy czy nawet większość smartfonów. Na przykład Wio Terminal ma CPU działający z prędkością 120 MHz, czyli 120 000 000 cykli na sekundę.

✅ Przeciętny komputer PC lub Mac ma CPU z wieloma rdzeniami działającymi z prędkością kilku gigaherców, co oznacza, że zegar tyka miliardy razy na sekundę. Sprawdź prędkość zegara swojego komputera i porównaj, ile razy jest szybszy od Wio Terminal.

Każdy cykl zegara zużywa energię i generuje ciepło. Im szybsze tyknięcia, tym więcej zużywanej energii i więcej generowanego ciepła. Komputery PC mają radiatory i wentylatory do odprowadzania ciepła, bez których przegrzałyby się i wyłączyły w ciągu kilku sekund. Mikrokontrolery często nie mają ani jednego, ani drugiego, ponieważ działają znacznie chłodniej, a zatem znacznie wolniej. Komputery PC działają na zasilaniu sieciowym lub dużych bateriach przez kilka godzin, mikrokontrolery mogą działać przez dni, miesiące, a nawet lata na małych bateriach. Mikrokontrolery mogą również mieć rdzenie działające z różnymi prędkościami, przełączając się na wolniejsze rdzenie o niskim poborze mocy, gdy obciążenie CPU jest niskie, aby zmniejszyć zużycie energii.

> 💁 Niektóre komputery PC i Maci przyjmują podobne podejście, łącząc szybkie rdzenie o wysokiej wydajności z wolniejszymi rdzeniami o niskim poborze mocy, przełączając się, aby oszczędzać baterię. Na przykład chip M1 w najnowszych laptopach Apple może przełączać się między 4 rdzeniami wydajnościowymi a 4 rdzeniami efektywnościowymi, aby zoptymalizować żywotność baterii lub prędkość w zależności od wykonywanego zadania.

✅ Zrób małe badanie: Przeczytaj o CPU w [artykule na Wikipedii o procesorach](https://wikipedia.org/wiki/Central_processing_unit).

#### Zadanie

Zbadaj Wio Terminal.

Jeśli używasz Wio Terminal w tych lekcjach, spróbuj znaleźć CPU. Znajdź sekcję *Hardware Overview* na [stronie produktu Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), aby zobaczyć zdjęcie wnętrza, i spróbuj znaleźć CPU przez przezroczyste plastikowe okienko z tyłu.

### Pamięć

Mikrokontrolery zazwyczaj mają dwa rodzaje pamięci – pamięć programu i pamięć o dostępie swobodnym (RAM).

Pamięć programu jest nieulotna, co oznacza, że to, co zostało do niej zapisane, pozostaje, gdy urządzenie jest wyłączone. To właśnie w tej pamięci przechowywany jest Twój kod programu.

RAM to pamięć używana przez program do działania, zawierająca zmienne przydzielone przez Twój program i dane zebrane z urządzeń peryferyjnych. RAM jest ulotna – gdy zasilanie zostanie odłączone,
🎓 Pamięć programu przechowuje Twój kod i pozostaje nawet po odcięciu zasilania.
🎓 RAM jest używana do uruchamiania programu i resetuje się, gdy nie ma zasilania

Podobnie jak w przypadku CPU, pamięć w mikrokontrolerze jest o rzędy wielkości mniejsza niż w komputerze PC lub Mac. Typowy komputer PC może mieć 8 gigabajtów (GB) RAM, czyli 8 000 000 000 bajtów, gdzie każdy bajt to wystarczająca ilość miejsca na przechowanie jednej litery lub liczby od 0 do 255. Mikrokontroler ma zazwyczaj tylko kilobajty (KB) RAM, gdzie kilobajt to 1 000 bajtów. Wspomniany wcześniej terminal Wio ma 192 KB RAM, czyli 192 000 bajtów - ponad 40 000 razy mniej niż przeciętny komputer PC!

Poniższy diagram pokazuje względną różnicę wielkości między 192 KB a 8 GB - mała kropka w środku reprezentuje 192 KB.

![Porównanie między 192 KB a 8 GB - ponad 40 000 razy większe](../../../../../translated_images/pl/ram-comparison.6beb73541b42ac6f.webp)

Pamięć na programy również jest mniejsza niż w komputerze PC. Typowy komputer PC może mieć dysk twardy o pojemności 500 GB na przechowywanie programów, podczas gdy mikrokontroler może mieć tylko kilobajty lub może kilka megabajtów (MB) pamięci (1 MB to 1 000 KB, czyli 1 000 000 bajtów). Terminal Wio ma 4 MB pamięci na programy.

✅ Zrób małe badanie: Ile RAM i pamięci ma komputer, którego używasz do czytania tego tekstu? Jak to się ma do mikrokontrolera?

### Wejście/Wyjście

Mikrokontrolery potrzebują połączeń wejścia i wyjścia (I/O), aby odczytywać dane z czujników i wysyłać sygnały sterujące do siłowników. Zazwyczaj zawierają one kilka uniwersalnych pinów wejścia/wyjścia (GPIO). Piny te można skonfigurować w oprogramowaniu jako wejście (czyli odbierają sygnał) lub wyjście (wysyłają sygnał).

🧠⬅️ Piny wejściowe służą do odczytu wartości z czujników

🧠➡️ Piny wyjściowe wysyłają instrukcje do siłowników

✅ Dowiesz się więcej na ten temat w kolejnej lekcji.

#### Zadanie

Zbadaj terminal Wio.

Jeśli używasz terminala Wio w tych lekcjach, znajdź piny GPIO. Znajdź sekcję *Pinout diagram* na [stronie produktu terminala Wio](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), aby dowiedzieć się, które piny są które. Terminal Wio jest dostarczany z naklejką, którą można zamontować z tyłu z numerami pinów, więc dodaj ją teraz, jeśli jeszcze tego nie zrobiłeś.

### Rozmiar fizyczny

Mikrokontrolery są zazwyczaj małe, a najmniejszy, [Freescale Kinetis KL03 MCU, jest wystarczająco mały, aby zmieścić się w wgłębieniu piłki golfowej](https://www.edn.com/tiny-arm-cortex-m0-based-mcu-shrinks-package/). Sam procesor w komputerze PC może mieć wymiary 40 mm x 40 mm, nie licząc radiatorów i wentylatorów potrzebnych do zapewnienia, że procesor może działać dłużej niż kilka sekund bez przegrzania, co jest znacznie większe niż kompletny mikrokontroler. Zestaw deweloperski terminala Wio z mikrokontrolerem, obudową, ekranem i szeregiem połączeń i komponentów nie jest dużo większy niż sam procesor Intel i9, a znacznie mniejszy niż procesor z radiatorem i wentylatorem!

| Urządzenie                      | Rozmiar               |
| ------------------------------- | --------------------- |
| Freescale Kinetis KL03          | 1,6 mm x 2 mm x 1 mm  |
| Terminal Wio                    | 72 mm x 57 mm x 12 mm |
| Intel i9 CPU, radiator i wentylator | 136 mm x 145 mm x 103 mm |

### Frameworki i systemy operacyjne

Ze względu na niską prędkość i rozmiar pamięci, mikrokontrolery nie uruchamiają systemu operacyjnego (OS) w sensie znanym z komputerów stacjonarnych. System operacyjny, który sprawia, że Twój komputer działa (Windows, Linux lub macOS), potrzebuje dużo pamięci i mocy obliczeniowej do wykonywania zadań, które są całkowicie zbędne dla mikrokontrolera. Pamiętaj, że mikrokontrolery są zazwyczaj programowane do wykonywania jednego lub kilku bardzo specyficznych zadań, w przeciwieństwie do komputerów ogólnego przeznaczenia, takich jak PC czy Mac, które muszą obsługiwać interfejs użytkownika, odtwarzać muzykę lub filmy, zapewniać narzędzia do pisania dokumentów lub kodu, grać w gry czy przeglądać Internet.

Aby zaprogramować mikrokontroler bez systemu operacyjnego, potrzebujesz narzędzi umożliwiających budowanie kodu w sposób, który mikrokontroler może uruchomić, korzystając z API umożliwiających komunikację z peryferiami. Każdy mikrokontroler jest inny, więc producenci zazwyczaj wspierają standardowe frameworki, które pozwalają na stosowanie standardowego "przepisu" do budowania kodu i uruchamiania go na dowolnym mikrokontrolerze obsługującym ten framework.

Możesz programować mikrokontrolery używając systemu operacyjnego - często nazywanego systemem operacyjnym czasu rzeczywistego (RTOS), ponieważ są one zaprojektowane do obsługi przesyłania danych do i z peryferiów w czasie rzeczywistym. Te systemy operacyjne są bardzo lekkie i oferują funkcje takie jak:

* Wielowątkowość, pozwalająca na uruchamianie więcej niż jednego bloku kodu jednocześnie, albo na wielu rdzeniach, albo na jednym rdzeniu na zmianę
* Sieciowanie, umożliwiające bezpieczną komunikację przez Internet
* Komponenty graficznego interfejsu użytkownika (GUI) do budowy interfejsów na urządzeniach z ekranami.

✅ Przeczytaj o różnych RTOS-ach: [Azure RTOS](https://azure.microsoft.com/services/rtos/?WT.mc_id=academic-17441-jabenn), [FreeRTOS](https://www.freertos.org), [Zephyr](https://www.zephyrproject.org)

#### Arduino

![Logo Arduino](../../../../../images/arduino-logo.svg)

[Arduino](https://www.arduino.cc) jest prawdopodobnie najpopularniejszym frameworkiem dla mikrokontrolerów, szczególnie wśród studentów, hobbystów i twórców. Arduino to otwartoźródłowa platforma elektroniczna łącząca oprogramowanie i sprzęt. Możesz kupić kompatybilne płytki Arduino od samego Arduino lub od innych producentów, a następnie kodować za pomocą frameworka Arduino.

Płytki Arduino są programowane w językach C lub C++. Użycie C/C++ pozwala na kompilację kodu do bardzo małych rozmiarów i szybkie działanie, co jest konieczne na urządzeniach o ograniczonych zasobach, takich jak mikrokontrolery. Rdzeń aplikacji Arduino nazywany jest szkicem i jest to kod C/C++ z 2 funkcjami - `setup` i `loop`. Gdy płytka się uruchamia, kod frameworka Arduino uruchamia funkcję `setup` raz, a następnie uruchamia funkcję `loop` w kółko, aż do wyłączenia zasilania.

Kod inicjalizacyjny umieściłbyś w funkcji `setup`, na przykład łączenie z WiFi i usługami w chmurze lub inicjalizację pinów wejścia/wyjścia. Kod w pętli zawierałby przetwarzanie, na przykład odczyt z czujnika i wysyłanie wartości do chmury. Zazwyczaj dodaje się opóźnienie w każdej pętli, na przykład jeśli chcesz, aby dane z czujnika były wysyłane co 10 sekund, dodajesz opóźnienie 10 sekund na końcu pętli, aby mikrokontroler mógł przejść w stan uśpienia, oszczędzając energię, a następnie uruchomić pętlę ponownie po 10 sekundach.

![Szkic Arduino uruchamiający najpierw setup, a następnie wielokrotnie loop](../../../../../translated_images/pl/arduino-sketch.79590cb837ff7a7c6a68d1afda6cab83fd53d3bb1bd9a8bf2eaf8d693a4d3ea6.png)

✅ Ta architektura programu jest znana jako *pętla zdarzeń* lub *pętla komunikatów*. Wiele aplikacji korzysta z niej w tle i jest to standard dla większości aplikacji desktopowych działających na systemach operacyjnych takich jak Windows, macOS czy Linux. Możesz przeczytać więcej w tym [artykule o pętli zdarzeń](https://wikipedia.org/wiki/Event_loop).

Arduino dostarcza standardowe biblioteki do interakcji z mikrokontrolerami i pinami I/O, z różnymi implementacjami pod spodem, aby działały na różnych mikrokontrolerach. Na przykład funkcja [`delay`](https://www.arduino.cc/reference/en/language/functions/time/delay/) wstrzymuje program na określony czas, a funkcja [`digitalRead`](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) odczytuje wartość `HIGH` lub `LOW` z danego pinu, niezależnie od tego, na której płytce kod jest uruchamiany. Te standardowe biblioteki oznaczają, że kod Arduino napisany dla jednej płytki może być skompilowany dla dowolnej innej płytki Arduino i będzie działał, zakładając, że piny są takie same i płytki obsługują te same funkcje.

Istnieje duży ekosystem bibliotek Arduino od firm trzecich, które pozwalają na dodanie dodatkowych funkcji do projektów Arduino, takich jak używanie czujników i siłowników lub łączenie się z usługami IoT w chmurze.

##### Zadanie

Zbadaj terminal Wio.

Jeśli używasz terminala Wio w tych lekcjach, przeczytaj ponownie kod, który napisałeś w poprzedniej lekcji. Znajdź funkcje `setup` i `loop`. Monitoruj wyjście szeregowe, aby zobaczyć, że funkcja `loop` jest wywoływana wielokrotnie. Spróbuj dodać kod do funkcji `setup`, aby zapisać coś na porcie szeregowym i zaobserwuj, że ten kod jest wywoływany tylko raz przy każdym ponownym uruchomieniu. Spróbuj ponownie uruchomić urządzenie za pomocą przełącznika zasilania z boku, aby pokazać, że funkcja ta jest wywoływana za każdym razem, gdy urządzenie się restartuje.

## Głębsze spojrzenie na komputery jednopłytkowe

W poprzedniej lekcji wprowadziliśmy komputery jednopłytkowe. Teraz przyjrzyjmy się im bliżej.

### Raspberry Pi

![Logo Raspberry Pi](../../../../../translated_images/pl/raspberry-pi-logo.4efaa16605cee054.webp)

[Raspberry Pi Foundation](https://www.raspberrypi.org) to organizacja charytatywna z Wielkiej Brytanii założona w 2009 roku w celu promowania nauki informatyki, szczególnie na poziomie szkolnym. W ramach tej misji opracowali komputer jednopłytkowy, nazwany Raspberry Pi. Raspberry Pi są obecnie dostępne w 3 wariantach - pełnowymiarowym, mniejszym Pi Zero oraz module obliczeniowym, który można wbudować w końcowe urządzenie IoT.

![Raspberry Pi 4](../../../../../translated_images/pl/raspberry-pi-4.fd4590d308c3d456.webp)

Najnowsza wersja pełnowymiarowego Raspberry Pi to Raspberry Pi 4B. Ma czterordzeniowy procesor (4 rdzenie) o taktowaniu 1,5 GHz, 2, 4 lub 8 GB RAM, gigabitowy Ethernet, WiFi, 2 porty HDMI obsługujące ekrany 4k, port wyjścia audio i wideo kompozytowego, porty USB (2 USB 2.0, 2 USB 3.0), 40 pinów GPIO, złącze kamery dla modułu kamery Raspberry Pi oraz gniazdo na kartę SD. Wszystko to na płytce o wymiarach 88 mm x 58 mm x 19,5 mm, zasilanej przez zasilacz USB-C o mocy 3A. Ceny zaczynają się od 35 USD, co jest znacznie tańsze niż PC czy Mac.

> 💁 Jest także Pi400, komputer typu all-in-one z Pi4 wbudowanym w klawiaturę.

![Raspberry Pi Zero](../../../../../translated_images/pl/raspberry-pi-zero.f7a4133e1e7d54bb.webp)

Pi Zero jest znacznie mniejszy i mniej wydajny. Ma jednordzeniowy procesor 1 GHz, 512 MB RAM, WiFi (w modelu Zero W), pojedynczy port HDMI, port micro-USB, 40 pinów GPIO, złącze kamery dla modułu kamery Raspberry Pi oraz gniazdo na kartę SD. Ma wymiary 65 mm x 30 mm x 5 mm i zużywa bardzo mało energii. Pi Zero kosztuje 5 USD, a wersja W z WiFi - 10 USD.

> 🎓 Procesory w obu tych urządzeniach to procesory ARM, w przeciwieństwie do procesorów Intel/AMD x86 lub x64, które znajdziesz w większości komputerów PC i Mac. Są one podobne do procesorów, które znajdziesz w niektórych mikrokontrolerach, a także w prawie wszystkich telefonach komórkowych, Microsoft Surface X i nowych komputerach Mac z Apple Silicon.

Wszystkie warianty Raspberry Pi działają na wersji systemu Debian Linux o nazwie Raspberry Pi OS. Jest on dostępny w wersji lite bez pulpitu, idealnej do projektów "headless", gdzie nie potrzebujesz ekranu, lub w pełnej wersji z pełnym środowiskiem graficznym, przeglądarką internetową, aplikacjami biurowymi, narzędziami do kodowania i grami. Ponieważ system operacyjny jest wersją Debiana, możesz zainstalować dowolną aplikację lub narzędzie, które działa na Debianie i jest zbudowane dla procesora ARM w Pi.

#### Zadanie

Zbadaj Raspberry Pi.

Jeśli używasz Raspberry Pi w tych lekcjach, przeczytaj o różnych komponentach sprzętowych na płytce.

* Możesz znaleźć szczegóły dotyczące procesorów używanych w [dokumentacji sprzętowej Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/). Przeczytaj o procesorze używanym w Twoim Pi.
* Zlokalizuj piny GPIO. Przeczytaj więcej o nich w [dokumentacji GPIO Raspberry Pi](https://www.raspberrypi.org/documentation/hardware/raspberrypi/gpio/README.md). Skorzystaj z [przewodnika po użyciu pinów GPIO](https://www.raspberrypi.org/documentation/usage/gpio/README.md), aby zidentyfikować różne piny na Twoim Pi.

### Programowanie komputerów jednopłytkowych

Komputery jednopłytkowe to pełne komputery, działające na pełnym systemie operacyjnym. Oznacza to, że istnieje szeroka gama języków programowania, frameworków i narzędzi, których możesz używać do ich kodowania, w przeciwieństwie do mikrokontrolerów, które polegają na wsparciu dla płytki w frameworkach takich jak Arduino. Większość języków programowania ma biblioteki umożliwiające dostęp do pinów GPIO w celu wysyłania i odbierania danych z czujników i siłowników.

✅ Jakie języki programowania znasz? Czy są one obsługiwane na Linuksie?

Najczęściej używanym językiem programowania do budowy aplikacji IoT na Raspberry Pi jest Python. Istnieje ogromny ekosystem sprzętu zaprojektowanego dla Pi, a prawie wszystkie z nich zawierają odpowiedni kod potrzebny do ich użycia jako bibliotek Pythona. Niektóre z tych ekosystemów opierają się na "czapkach" - tak nazwanych, ponieważ nakładają się na Pi jak czapka i łączą się z dużym gniazdem do 40 pinów GPIO. Te czapki zapewniają dodatkowe możliwości, takie jak ekrany, czujniki, zdalnie sterowane samochody lub adaptery umożliwiające podłączenie czujników za pomocą standaryzowanych kabli.
### Wykorzystanie komputerów jednopłytkowych w profesjonalnych wdrożeniach IoT

Komputery jednopłytkowe są wykorzystywane w profesjonalnych wdrożeniach IoT, nie tylko jako zestawy deweloperskie. Mogą stanowić potężne narzędzie do sterowania sprzętem i wykonywania złożonych zadań, takich jak uruchamianie modeli uczenia maszynowego. Na przykład istnieje [moduł obliczeniowy Raspberry Pi 4](https://www.raspberrypi.org/blog/raspberry-pi-compute-module-4/), który oferuje wszystkie możliwości Raspberry Pi 4, ale w bardziej kompaktowej i tańszej formie, bez większości portów, zaprojektowany do instalacji w niestandardowym sprzęcie.

---

## 🚀 Wyzwanie

Wyzwanie z ostatniej lekcji polegało na wymienieniu jak największej liczby urządzeń IoT, które znajdują się w Twoim domu, szkole lub miejscu pracy. Dla każdego urządzenia z tej listy zastanów się, czy są one oparte na mikrokontrolerach, komputerach jednopłytkowych, czy może na mieszance obu tych technologii.

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/4)

## Przegląd i samodzielna nauka

* Przeczytaj [przewodnik wprowadzający do Arduino](https://www.arduino.cc/en/Guide/Introduction), aby lepiej zrozumieć platformę Arduino.
* Zapoznaj się z [wprowadzeniem do Raspberry Pi 4](https://www.raspberrypi.org/products/raspberry-pi-4-model-b/), aby dowiedzieć się więcej o Raspberry Pi.
* Dowiedz się więcej o niektórych koncepcjach i akronimach w artykule [What the FAQ are CPUs, MPUs, MCUs, and GPUs w Electrical Engineering Journal](https://www.eejournal.com/article/what-the-faq-are-cpus-mpus-mcus-and-gpus/).

✅ Skorzystaj z tych przewodników oraz z kosztów pokazanych w linkach w [przewodniku sprzętowym](../../../hardware.md), aby zdecydować, jaką platformę sprzętową chcesz użyć, lub czy wolisz skorzystać z wirtualnego urządzenia.

## Zadanie

[Porównaj i skontrastuj mikrokontrolery oraz komputery jednopłytkowe](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.