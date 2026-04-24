# Wprowadzenie do IoT

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-1.2606670fa61ee904.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obrazek, aby zobaczyć większą wersję.

Ta lekcja była częścią serii [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) organizowanej przez [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcja została podzielona na dwa filmy: godzinny wykład oraz godzinne konsultacje, podczas których szczegółowo omówiono wybrane tematy i odpowiadano na pytania.

[![Lekcja 1: Wprowadzenie do IoT](https://img.youtube.com/vi/bVFfcYh6UBw/0.jpg)](https://youtu.be/bVFfcYh6UBw)

[![Lekcja 1: Wprowadzenie do IoT - Konsultacje](https://img.youtube.com/vi/YI772q5v3yI/0.jpg)](https://youtu.be/YI772q5v3yI)

> 🎥 Kliknij powyższe obrazy, aby obejrzeć filmy

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/1)

## Wprowadzenie

Ta lekcja obejmuje podstawowe zagadnienia związane z Internetem Rzeczy (IoT) i pomoże Ci rozpocząć konfigurację sprzętu.

W tej lekcji omówimy:

* [Czym jest 'Internet Rzeczy'?](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Urządzenia IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Konfiguracja urządzenia](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Zastosowania IoT](../../../../../1-getting-started/lessons/1-introduction-to-iot)
* [Przykłady urządzeń IoT wokół Ciebie](../../../../../1-getting-started/lessons/1-introduction-to-iot)

## Czym jest 'Internet Rzeczy'?

Termin 'Internet Rzeczy' został wprowadzony przez [Kevina Ashtona](https://wikipedia.org/wiki/Kevin_Ashton) w 1999 roku, aby opisać połączenie Internetu ze światem fizycznym za pomocą sensorów. Od tego czasu termin ten odnosi się do każdego urządzenia, które wchodzi w interakcję ze światem fizycznym, zbierając dane z sensorów lub wykonując działania w świecie rzeczywistym za pomocą aktuatorów (urządzeń, które wykonują coś, np. włączają przełącznik lub zapalają diodę LED), zazwyczaj połączonych z innymi urządzeniami lub Internetem.

> **Sensory** zbierają informacje ze świata, takie jak pomiar prędkości, temperatury czy lokalizacji.
>
> **Aktuatory** przekształcają sygnały elektryczne w działania w świecie rzeczywistym, takie jak uruchamianie przełącznika, włączanie świateł, wydawanie dźwięków czy wysyłanie sygnałów sterujących do innych urządzeń, np. w celu włączenia gniazdka elektrycznego.

IoT jako dziedzina technologii obejmuje nie tylko urządzenia, ale także usługi w chmurze, które mogą przetwarzać dane z sensorów lub wysyłać polecenia do aktuatorów podłączonych do urządzeń IoT. Obejmuje również urządzenia, które nie mają lub nie potrzebują połączenia z Internetem, często nazywane urządzeniami brzegowymi. Są to urządzenia, które mogą samodzielnie przetwarzać i reagować na dane z sensorów, zazwyczaj korzystając z modeli AI trenowanych w chmurze.

IoT to szybko rozwijająca się dziedzina technologii. Szacuje się, że pod koniec 2020 roku na świecie działało 30 miliardów urządzeń IoT podłączonych do Internetu. Patrząc w przyszłość, przewiduje się, że do 2025 roku urządzenia IoT będą zbierać prawie 80 zettabajtów danych, czyli 80 bilionów gigabajtów. To ogromna ilość danych!

![Wykres pokazujący liczbę aktywnych urządzeń IoT w czasie, z tendencją wzrostową od mniej niż 5 miliardów w 2015 roku do ponad 30 miliardów w 2025 roku](../../../../../images/connected-iot-devices.svg)

✅ Zrób małe badanie: Jak dużo danych generowanych przez urządzenia IoT jest faktycznie wykorzystywanych, a ile jest marnowanych? Dlaczego tak wiele danych jest ignorowanych?

Te dane są kluczem do sukcesu IoT. Aby być skutecznym deweloperem IoT, musisz zrozumieć, jakie dane należy zbierać, jak je zbierać, jak podejmować decyzje na ich podstawie i jak wykorzystać te decyzje do interakcji ze światem fizycznym, jeśli zajdzie taka potrzeba.

## Urządzenia IoT

**T** w IoT oznacza **Rzeczy** - urządzenia, które wchodzą w interakcję ze światem fizycznym, zbierając dane z sensorów lub wykonując działania w świecie rzeczywistym za pomocą aktuatorów.

Urządzenia produkcyjne lub komercyjne, takie jak konsumenckie opaski fitness czy przemysłowe kontrolery maszyn, są zazwyczaj projektowane na zamówienie. Korzystają z niestandardowych płyt obwodowych, a czasem nawet niestandardowych procesorów, zaprojektowanych tak, aby spełniać wymagania konkretnego zadania, czy to w celu zmieszczenia się na nadgarstku, czy wytrzymania wysokich temperatur, dużych obciążeń lub wibracji w środowisku fabrycznym.

Jako deweloper uczący się IoT lub tworzący prototyp urządzenia, będziesz potrzebować zestawu deweloperskiego. Są to uniwersalne urządzenia IoT zaprojektowane dla deweloperów, często z funkcjami, które nie byłyby dostępne w urządzeniach produkcyjnych, takimi jak zestaw zewnętrznych pinów do podłączania sensorów lub aktuatorów, sprzęt wspierający debugowanie czy dodatkowe zasoby, które zwiększyłyby koszt produkcji w dużej skali.

Te zestawy deweloperskie zazwyczaj dzielą się na dwie kategorie - mikrokontrolery i komputery jednopłytkowe. Zostaną one tutaj wprowadzone, a w kolejnej lekcji omówimy je bardziej szczegółowo.

> 💁 Twój telefon również można uznać za uniwersalne urządzenie IoT, z wbudowanymi sensorami i aktuatorami, które różne aplikacje wykorzystują na różne sposoby, współpracując z różnymi usługami w chmurze. Możesz nawet znaleźć niektóre samouczki IoT, które używają aplikacji na telefonie jako urządzenia IoT.

### Mikrokontrolery

Mikrokontroler (często nazywany MCU, od ang. microcontroller unit) to mały komputer składający się z:

🧠 Jednego lub więcej procesorów centralnych (CPU) - "mózgu" mikrokontrolera, który wykonuje Twój program

💾 Pamięci (RAM i pamięci programu) - miejsca, gdzie przechowywane są Twój program, dane i zmienne

🔌 Programowalnych połączeń wejścia/wyjścia (I/O) - do komunikacji z zewnętrznymi urządzeniami peryferyjnymi (podłączonymi urządzeniami), takimi jak sensory i aktuatory

Mikrokontrolery są zazwyczaj tanimi urządzeniami obliczeniowymi, z przeciętnymi cenami dla tych używanych w niestandardowym sprzęcie spadającymi do około 0,50 USD, a niektóre urządzenia kosztują nawet 0,03 USD. Zestawy deweloperskie mogą zaczynać się od 4 USD, a ich koszt rośnie wraz z dodawaniem kolejnych funkcji. [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html), zestaw deweloperski mikrokontrolera od [Seeed studios](https://www.seeedstudio.com), który ma sensory, aktuatory, WiFi i ekran, kosztuje około 30 USD.

![Wio Terminal](../../../../../translated_images/pl/wio-terminal.b8299ee16587db9a.webp)

> 💁 Szukając w Internecie mikrokontrolerów, uważaj na wyszukiwanie terminu **MCU**, ponieważ może to zwrócić wiele wyników dotyczących Marvel Cinematic Universe, a nie mikrokontrolerów.

Mikrokontrolery są zaprojektowane do wykonywania ograniczonej liczby bardzo specyficznych zadań, a nie do bycia komputerami ogólnego przeznaczenia, takimi jak PC czy Mac. Z wyjątkiem bardzo specyficznych scenariuszy, nie można podłączyć do nich monitora, klawiatury i myszy, aby używać ich do ogólnych zadań.

Zestawy deweloperskie mikrokontrolerów zazwyczaj mają dodatkowe sensory i aktuatory na pokładzie. Większość płyt ma jedną lub więcej diod LED, które można zaprogramować, wraz z innymi urządzeniami, takimi jak standardowe złącza do dodawania kolejnych sensorów lub aktuatorów w ekosystemach różnych producentów czy wbudowane sensory (zazwyczaj najpopularniejsze, takie jak sensory temperatury). Niektóre mikrokontrolery mają wbudowaną łączność bezprzewodową, taką jak Bluetooth czy WiFi, lub dodatkowe mikrokontrolery na płytce, aby dodać tę łączność.

> 💁 Mikrokontrolery są zazwyczaj programowane w językach C/C++.

### Komputery jednopłytkowe

Komputer jednopłytkowy to małe urządzenie obliczeniowe, które zawiera wszystkie elementy pełnoprawnego komputera na jednej małej płytce. Są to urządzenia o specyfikacjach zbliżonych do komputerów stacjonarnych lub laptopów, które działają na pełnym systemie operacyjnym, ale są mniejsze, zużywają mniej energii i są znacznie tańsze.

![Raspberry Pi 4](../../../../../translated_images/pl/raspberry-pi-4.fd4590d308c3d456.webp)

Raspberry Pi jest jednym z najpopularniejszych komputerów jednopłytkowych.

Podobnie jak mikrokontroler, komputer jednopłytkowy ma CPU, pamięć i piny wejścia/wyjścia, ale ma dodatkowe funkcje, takie jak układ graficzny umożliwiający podłączenie monitorów, wyjścia audio i porty USB do podłączenia klawiatur, myszy i innych standardowych urządzeń USB, takich jak kamery internetowe czy zewnętrzne pamięci. Programy są przechowywane na kartach SD lub dyskach twardych wraz z systemem operacyjnym, zamiast na wbudowanym chipie pamięci.

> 🎓 Możesz pomyśleć o komputerze jednopłytkowym jako o mniejszej, tańszej wersji PC lub Maca, na którym czytasz ten tekst, z dodatkowymi pinami GPIO (ogólnego przeznaczenia wejścia/wyjścia) do interakcji z sensorami i aktuatorami.

Komputery jednopłytkowe są pełnoprawnymi komputerami, więc można je programować w dowolnym języku. Urządzenia IoT są zazwyczaj programowane w Pythonie.

### Wybór sprzętu na kolejne lekcje

Wszystkie kolejne lekcje zawierają zadania z użyciem urządzenia IoT do interakcji ze światem fizycznym i komunikacji z chmurą. Każda lekcja wspiera 3 opcje urządzeń - Arduino (z użyciem Seeed Studios Wio Terminal) lub komputer jednopłytkowy, fizyczny (Raspberry Pi 4) lub wirtualny komputer jednopłytkowy działający na Twoim PC lub Macu.

Możesz przeczytać o sprzęcie potrzebnym do wykonania wszystkich zadań w [przewodniku sprzętowym](../../../hardware.md).

> 💁 Nie musisz kupować żadnego sprzętu IoT, aby wykonać zadania - wszystko możesz zrobić, używając wirtualnego komputera jednopłytkowego.

Wybór sprzętu zależy od Ciebie - od tego, co masz dostępne w domu lub w szkole, oraz od języka programowania, który znasz lub planujesz się nauczyć. Oba warianty sprzętu będą korzystać z tego samego ekosystemu sensorów, więc jeśli zaczniesz od jednej opcji, możesz przejść na drugą bez konieczności wymiany większości zestawu. Wirtualny komputer jednopłytkowy będzie odpowiednikiem nauki na Raspberry Pi, a większość kodu będzie można przenieść na Pi, jeśli w przyszłości zdobędziesz urządzenie i sensory.

### Zestaw deweloperski Arduino

Jeśli interesuje Cię nauka programowania mikrokontrolerów, możesz wykonać zadania, używając urządzenia Arduino. Będziesz potrzebować podstawowej znajomości programowania w językach C/C++, ponieważ lekcje będą uczyć tylko kodu związanego z frameworkiem Arduino, używanymi sensorami i aktuatorami oraz bibliotekami współpracującymi z chmurą.

Zadania będą korzystać z [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn) z rozszerzeniem [PlatformIO do programowania mikrokontrolerów](https://platformio.org). Możesz również używać Arduino IDE, jeśli masz doświadczenie z tym narzędziem, ponieważ instrukcje nie będą dostarczane.

### Zestaw deweloperski komputera jednopłytkowego

Jeśli interesuje Cię nauka programowania IoT z użyciem komputerów jednopłytkowych, możesz wykonać zadania, używając Raspberry Pi lub wirtualnego urządzenia działającego na Twoim PC lub Macu.

Będziesz potrzebować podstawowej znajomości programowania w Pythonie, ponieważ lekcje będą uczyć tylko kodu związanego z używanymi sensorami i aktuatorami oraz bibliotekami współpracującymi z chmurą.

> 💁 Jeśli chcesz nauczyć się programowania w Pythonie, sprawdź następujące serie wideo:
>
> * [Python dla początkujących](https://channel9.msdn.com/Series/Intro-to-Python-Development?WT.mc_id=academic-17441-jabenn)
> * [Więcej Python dla początkujących](https://channel9.msdn.com/Series/More-Python-for-Beginners?WT.mc_id=academic-7372-jabenn)

Zadania będą korzystać z [Visual Studio Code](https://code.visualstudio.com/?WT.mc_id=academic-17441-jabenn).

Jeśli używasz Raspberry Pi, możesz uruchomić Pi z pełną wersją desktopową Raspberry Pi OS i programować bezpośrednio na Pi, używając [wersji VS Code dla Raspberry Pi OS](https://code.visualstudio.com/docs/setup/raspberry-pi?WT.mc_id=academic-17441-jabenn), lub uruchomić Pi jako urządzenie bezgłowe i programować z PC lub Maca, używając VS Code z rozszerzeniem [Remote SSH](https://code.visualstudio.com/docs/remote/ssh?WT.mc_id=academic-17441-jabenn), które pozwala na połączenie z Pi i edytowanie, debugowanie oraz uruchamianie kodu tak, jakbyś programował bezpośrednio na nim.

Jeśli korzystasz z opcji wirtualnego urządzenia, będziesz programować bezpośrednio na swoim komputerze. Zamiast korzystać z sensorów i aktuatorów, użyjesz narzędzia do symulacji tego sprzętu, które pozwoli Ci definiować wartości sensorów i wyświetlać wyniki aktuatorów na ekranie.

## Konfiguracja urządzenia

Zanim zaczniesz programować swoje urządzenie IoT, musisz wykonać niewielką konfigurację. Postępuj zgodnie z odpowiednimi instrukcjami w zależności od używanego urządzenia.
💁 Jeśli jeszcze nie masz urządzenia, zajrzyj do [przewodnika sprzętowego](../../../hardware.md), aby zdecydować, którego urządzenia będziesz używać i jaki dodatkowy sprzęt musisz zakupić. Nie musisz kupować sprzętu, ponieważ wszystkie projekty można uruchomić na wirtualnym sprzęcie.
Te instrukcje zawierają linki do stron internetowych twórców sprzętu lub narzędzi, których będziesz używać. Ma to na celu zapewnienie, że zawsze korzystasz z najbardziej aktualnych instrukcji dotyczących różnych narzędzi i sprzętu.

Przejdź przez odpowiedni przewodnik, aby skonfigurować swoje urządzenie i ukończyć projekt "Hello World". Będzie to pierwszy krok w tworzeniu nocnej lampki IoT w ciągu 4 lekcji w tej części wprowadzającej.

* [Arduino - Wio Terminal](wio-terminal.md)  
* [Komputer jednopłytkowy - Raspberry Pi](pi.md)  
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device.md)  

✅ Będziesz używać VS Code zarówno dla Arduino, jak i komputerów jednopłytkowych. Jeśli wcześniej go nie używałeś, przeczytaj więcej na stronie [VS Code](https://code.visualstudio.com?WT.mc_id=academic-17441-jabenn).

## Zastosowania IoT

IoT obejmuje ogromny zakres zastosowań, w kilku szerokich grupach:

* Konsumenckie IoT  
* Komercyjne IoT  
* Przemysłowe IoT  
* Infrastrukturalne IoT  

✅ Zrób małe badanie: Dla każdego z opisanych poniżej obszarów znajdź jeden konkretny przykład, który nie został podany w tekście.

### Konsumenckie IoT

Konsumenckie IoT odnosi się do urządzeń IoT, które konsumenci kupują i używają w domu. Niektóre z tych urządzeń są niezwykle przydatne, takie jak inteligentne głośniki, inteligentne systemy grzewcze i robotyczne odkurzacze. Inne budzą wątpliwości co do swojej użyteczności, na przykład krany sterowane głosem, które nie pozwalają ich wyłączyć, gdy sterowanie głosowe nie słyszy cię przez dźwięk płynącej wody.

Urządzenia konsumenckie IoT umożliwiają ludziom osiąganie więcej w ich otoczeniu, szczególnie miliardowi osób z niepełnosprawnościami. Robotyczne odkurzacze mogą zapewnić czyste podłogi osobom z problemami z poruszaniem się, które nie mogą samodzielnie odkurzać, piekarniki sterowane głosem pozwalają osobom z ograniczonym wzrokiem lub kontrolą motoryczną nagrzewać piekarniki tylko za pomocą głosu, a monitory zdrowia umożliwiają pacjentom samodzielne monitorowanie przewlekłych schorzeń z bardziej regularnymi i szczegółowymi aktualizacjami ich stanu. Te urządzenia stają się tak powszechne, że nawet małe dzieci używają ich w codziennym życiu, na przykład uczniowie uczący się zdalnie podczas pandemii COVID ustawiają timery na inteligentnych urządzeniach domowych, aby śledzić swoją naukę lub ustawiać alarmy przypominające o nadchodzących zajęciach.

✅ Jakie urządzenia konsumenckie IoT masz przy sobie lub w swoim domu?

### Komercyjne IoT

Komercyjne IoT obejmuje wykorzystanie IoT w miejscu pracy. W biurze mogą znajdować się czujniki obecności i detektory ruchu, które zarządzają oświetleniem i ogrzewaniem, aby działały tylko wtedy, gdy są potrzebne, co zmniejsza koszty i emisję dwutlenku węgla. W fabryce urządzenia IoT mogą monitorować zagrożenia bezpieczeństwa, takie jak pracownicy nie noszący kasków ochronnych lub hałas osiągający niebezpieczne poziomy. W handlu detalicznym urządzenia IoT mogą mierzyć temperaturę w chłodniach, ostrzegając właściciela sklepu, jeśli lodówka lub zamrażarka przekroczy wymaganą temperaturę, lub monitorować produkty na półkach, aby skierować pracowników do uzupełnienia sprzedanych towarów. Branża transportowa coraz częściej polega na IoT do monitorowania lokalizacji pojazdów, śledzenia przebiegu na drogach w celu naliczania opłat drogowych, monitorowania godzin pracy kierowców i przestrzegania przerw, lub powiadamiania personelu, gdy pojazd zbliża się do magazynu, aby przygotować się do załadunku lub rozładunku.

✅ Jakie urządzenia komercyjne IoT znajdują się w twojej szkole lub miejscu pracy?

### Przemysłowe IoT (IIoT)

Przemysłowe IoT, czyli IIoT, to wykorzystanie urządzeń IoT do kontrolowania i zarządzania maszynami na dużą skalę. Obejmuje to szeroki zakres zastosowań, od fabryk po cyfrowe rolnictwo.

Fabryki wykorzystują urządzenia IoT na wiele różnych sposobów. Maszyny mogą być monitorowane za pomocą wielu czujników, które śledzą takie parametry jak temperatura, wibracje i prędkość obrotowa. Dane te mogą być monitorowane, aby zatrzymać maszynę, jeśli wyjdzie poza określone tolerancje - na przykład, gdy zbytnio się nagrzewa i zostaje wyłączona. Dane te mogą być również gromadzone i analizowane w czasie, aby przeprowadzać konserwację predykcyjną, gdzie modele AI analizują dane prowadzące do awarii i wykorzystują je do przewidywania innych awarii, zanim się wydarzą.

Cyfrowe rolnictwo jest kluczowe, jeśli planeta ma wyżywić rosnącą populację, szczególnie 2 miliardy ludzi w 500 milionach gospodarstw domowych, które utrzymują się z [rolnictwa na własne potrzeby](https://wikipedia.org/wiki/Subsistence_agriculture). Cyfrowe rolnictwo może obejmować zarówno tanie czujniki za kilka dolarów, jak i ogromne komercyjne instalacje. Rolnik może zacząć od monitorowania temperatur i korzystania z [dni stopni wzrostu](https://wikipedia.org/wiki/Growing_degree-day), aby przewidzieć, kiedy plon będzie gotowy do zbioru. Może połączyć monitorowanie wilgotności gleby z automatycznymi systemami nawadniania, aby dostarczyć roślinom tyle wody, ile potrzebują, ale nie więcej, aby zapewnić, że ich uprawy nie wyschną, nie marnując przy tym wody. Rolnicy idą jeszcze dalej, używając dronów, danych satelitarnych i AI do monitorowania wzrostu upraw, chorób i jakości gleby na ogromnych obszarach ziemi uprawnej.

✅ Jakie inne urządzenia IoT mogłyby pomóc rolnikom?

### Infrastrukturalne IoT

Infrastrukturalne IoT to monitorowanie i kontrolowanie lokalnej i globalnej infrastruktury, z której ludzie korzystają na co dzień.

[Smart Cities](https://wikipedia.org/wiki/Smart_city) to obszary miejskie, które wykorzystują urządzenia IoT do zbierania danych o mieście i wykorzystywania ich do poprawy funkcjonowania miasta. Miasta te są zazwyczaj zarządzane we współpracy między lokalnymi władzami, środowiskiem akademickim i lokalnymi firmami, monitorując i zarządzając różnymi aspektami, od transportu po parkowanie i zanieczyszczenie. Na przykład w Kopenhadze w Danii zanieczyszczenie powietrza jest ważne dla lokalnych mieszkańców, więc jest ono mierzone, a dane są wykorzystywane do dostarczania informacji o najczystszych trasach rowerowych i joggingowych.

[Inteligentne sieci energetyczne](https://wikipedia.org/wiki/Smart_grid) pozwalają na lepszą analizę zapotrzebowania na energię dzięki zbieraniu danych o zużyciu na poziomie indywidualnych domów. Dane te mogą kierować decyzjami na poziomie kraju, w tym gdzie budować nowe elektrownie, oraz na poziomie osobistym, dostarczając użytkownikom informacji o tym, ile energii zużywają, kiedy ją zużywają, a nawet sugestii, jak obniżyć koszty, na przykład ładując samochody elektryczne w nocy.

✅ Gdybyś mógł dodać urządzenia IoT do pomiaru czegokolwiek w miejscu, w którym mieszkasz, co by to było?

## Przykłady urządzeń IoT, które mogą być wokół ciebie

Byłbyś zdziwiony, jak wiele urządzeń IoT znajduje się wokół ciebie. Piszę to z domu i mam następujące urządzenia podłączone do Internetu z inteligentnymi funkcjami, takimi jak sterowanie aplikacją, sterowanie głosowe lub możliwość wysyłania danych na mój telefon:

* Wiele inteligentnych głośników  
* Lodówka, zmywarka, piekarnik i mikrofalówka  
* Monitor energii dla paneli słonecznych  
* Inteligentne gniazdka  
* Wideodomofon i kamery bezpieczeństwa  
* Inteligentny termostat z wieloma czujnikami w pomieszczeniach  
* Otwieracz do drzwi garażowych  
* Systemy rozrywki domowej i telewizory sterowane głosem  
* Oświetlenie  
* Trackery fitness i zdrowia  

Wszystkie te urządzenia mają czujniki i/lub siłowniki i komunikują się z Internetem. Mogę sprawdzić na telefonie, czy drzwi garażowe są otwarte, i poprosić inteligentny głośnik, aby je zamknął. Mogę nawet ustawić timer, aby jeśli są otwarte w nocy, zamknęły się automatycznie. Gdy dzwoni mój dzwonek do drzwi, mogę zobaczyć na telefonie, kto tam jest, gdziekolwiek jestem na świecie, i rozmawiać z nimi przez głośnik i mikrofon wbudowany w dzwonek. Mogę monitorować poziom glukozy we krwi, tętno i wzorce snu, szukając wzorców w danych, aby poprawić swoje zdrowie. Mogę sterować oświetleniem przez chmurę i siedzieć w ciemności, gdy połączenie z Internetem przestaje działać.

---

## 🚀 Wyzwanie

Wypisz jak najwięcej urządzeń IoT, które znajdują się w twoim domu, szkole lub miejscu pracy - może być ich więcej, niż myślisz!

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/2)

## Przegląd i samodzielna nauka

Przeczytaj o korzyściach i porażkach projektów konsumenckich IoT. Sprawdź strony z wiadomościami w poszukiwaniu artykułów o przypadkach, gdy coś poszło nie tak, takich jak problemy z prywatnością, problemy sprzętowe lub problemy spowodowane brakiem łączności.

Kilka przykładów:

* Sprawdź konto na Twitterze **[Internet of Sh*t](https://twitter.com/internetofshit)** *(ostrzeżenie o wulgaryzmach)*, aby zobaczyć dobre przykłady porażek w konsumenckim IoT.  
* [c|net - Mój Apple Watch uratował mi życie: 5 osób dzieli się swoimi historiami](https://www.cnet.com/news/apple-watch-lifesaving-health-features-read-5-peoples-stories/)  
* [c|net - Technik ADT przyznaje się do winy za szpiegowanie klientów przez lata](https://www.cnet.com/news/adt-home-security-technician-pleads-guilty-to-spying-on-customer-camera-feeds-for-years/) *(ostrzeżenie o treściach dotyczących niekonsensualnego podglądania)*  

## Zadanie

[Zbadaj projekt IoT](assignment.md)  

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.