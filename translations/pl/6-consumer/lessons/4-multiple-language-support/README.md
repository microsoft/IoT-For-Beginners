# Obsługa wielu języków

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-24.4246968ed058510a.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ten film przedstawia przegląd usług mowy w Azure, obejmując konwersję mowy na tekst i tekstu na mowę z wcześniejszych lekcji, a także tłumaczenie mowy, które jest tematem tej lekcji:

[![Rozpoznawanie mowy za pomocą kilku linii kodu w Pythonie z Microsoft Build 2020](https://img.youtube.com/vi/h6xbpMPSGEA/0.jpg)](https://www.youtube.com/watch?v=h6xbpMPSGEA)

> 🎥 Kliknij obraz powyżej, aby obejrzeć film

## Quiz przed lekcją

[Quiz przed lekcją](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/47)

## Wprowadzenie

W ostatnich trzech lekcjach nauczyłeś się, jak konwertować mowę na tekst, rozumieć język oraz konwertować tekst na mowę, wszystko to dzięki sztucznej inteligencji. Kolejnym obszarem komunikacji międzyludzkiej, w którym AI może pomóc, jest tłumaczenie języka – konwersja z jednego języka na inny, na przykład z angielskiego na francuski.

W tej lekcji dowiesz się, jak używać AI do tłumaczenia tekstu, co pozwoli Twojemu inteligentnemu timerowi na interakcję z użytkownikami w wielu językach.

W tej lekcji omówimy:

* [Tłumaczenie tekstu](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Usługi tłumaczeniowe](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Tworzenie zasobu tłumacza](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Obsługa wielu języków w aplikacjach za pomocą tłumaczeń](../../../../../6-consumer/lessons/4-multiple-language-support)
* [Tłumaczenie tekstu za pomocą usługi AI](../../../../../6-consumer/lessons/4-multiple-language-support)

> 🗑 To jest ostatnia lekcja w tym projekcie, więc po jej ukończeniu i wykonaniu zadania nie zapomnij wyczyścić swoich usług w chmurze. Będziesz potrzebować tych usług do ukończenia zadania, więc upewnij się, że najpierw je wykonasz.
>
> W razie potrzeby zapoznaj się z [przewodnikiem czyszczenia projektu](../../../clean-up.md), aby uzyskać instrukcje, jak to zrobić.

## Tłumaczenie tekstu

Tłumaczenie tekstu było problemem badanym w informatyce przez ponad 70 lat, a dopiero teraz, dzięki postępom w AI i mocy obliczeniowej, zbliża się do poziomu, który jest niemal tak dobry jak tłumacze ludzie.

> 💁 Początki można prześledzić jeszcze dalej, do [Al-Kindiego](https://wikipedia.org/wiki/Al-Kindi), arabskiego kryptografa z IX wieku, który opracował techniki tłumaczenia języków.

### Tłumaczenia maszynowe

Tłumaczenie tekstu rozpoczęło się jako technologia znana jako tłumaczenie maszynowe (MT), która umożliwia tłumaczenie między różnymi parami językowymi. MT działa poprzez zastępowanie słów w jednym języku innymi, dodając techniki wyboru odpowiednich sposobów tłumaczenia fraz lub części zdań, gdy proste tłumaczenie słowo w słowo nie ma sensu.

> 🎓 Gdy tłumacze obsługują tłumaczenie między jednym językiem a innym, nazywa się to *parami językowymi*. Różne narzędzia obsługują różne pary językowe, które mogą nie być kompletne. Na przykład tłumacz może obsługiwać parę językową angielski-hiszpański i hiszpański-włoski, ale nie angielski-włoski.

Na przykład tłumaczenie "Hello world" z angielskiego na francuski można wykonać za pomocą podstawienia – "Bonjour" za "Hello" i "le monde" za "world", co prowadzi do poprawnego tłumaczenia "Bonjour le monde".

Podstawienia nie działają, gdy różne języki używają różnych sposobów wyrażania tego samego. Na przykład angielskie zdanie "My name is Jim" tłumaczy się na francuski jako "Je m'appelle Jim" – dosłownie "Nazywam się Jim". "Je" to francuskie "ja", "moi" to "mnie", ale jest łączone z czasownikiem, ponieważ zaczyna się od samogłoski, więc staje się "m'", "appelle" oznacza "nazywać", a "Jim" nie jest tłumaczone, ponieważ to imię, a nie słowo, które można przetłumaczyć. Kolejność słów również staje się problemem – proste podstawienie "Je m'appelle Jim" staje się "I myself call Jim", z inną kolejnością słów niż w angielskim.

> 💁 Niektóre słowa nigdy nie są tłumaczone – moje imię to Jim, niezależnie od tego, w jakim języku się przedstawiam. Podczas tłumaczenia na języki używające innych alfabetów lub liter dla różnych dźwięków, słowa mogą być *transliterowane*, czyli zapisywane za pomocą liter lub znaków, które oddają odpowiedni dźwięk, aby brzmiały tak samo jak dane słowo.

Idiomy również stanowią problem w tłumaczeniu. Są to frazy, które mają zrozumiałe znaczenie inne niż bezpośrednia interpretacja słów. Na przykład w angielskim idiom "I've got ants in my pants" nie odnosi się dosłownie do posiadania mrówek w ubraniu, ale do bycia niespokojnym. Jeśli przetłumaczysz to na niemiecki, zdezorientujesz słuchacza, ponieważ niemiecka wersja to "Ich habe Hummeln im Hintern" (Mam trzmiele w spodniach).

> 💁 Różne lokalizacje dodają różne zawiłości. W idiomie "ants in your pants" w amerykańskim angielskim "pants" oznacza odzież wierzchnią, a w brytyjskim angielskim "pants" to bielizna.

✅ Jeśli mówisz w kilku językach, pomyśl o frazach, które nie mają bezpośredniego tłumaczenia.

Systemy tłumaczenia maszynowego opierają się na dużych bazach danych reguł opisujących, jak tłumaczyć określone frazy i idiomy, wraz z metodami statystycznymi wybierającymi odpowiednie tłumaczenia spośród możliwych opcji. Te metody statystyczne wykorzystują ogromne bazy danych dzieł przetłumaczonych przez ludzi na wiele języków, aby wybrać najbardziej prawdopodobne tłumaczenie, technikę zwaną *statystycznym tłumaczeniem maszynowym*. Wiele z nich używa pośrednich reprezentacji języka, co pozwala na tłumaczenie jednego języka na pośredni, a następnie z pośredniego na inny język. Dzięki temu dodanie większej liczby języków wymaga tłumaczeń na i z pośredniego języka, a nie na i z wszystkich innych języków.

### Tłumaczenia neuronowe

Tłumaczenia neuronowe wykorzystują moc AI do tłumaczenia, zazwyczaj tłumacząc całe zdania za pomocą jednego modelu. Modele te są trenowane na ogromnych zbiorach danych przetłumaczonych przez ludzi, takich jak strony internetowe, książki i dokumenty ONZ.

Modele tłumaczeń neuronowych są zazwyczaj mniejsze niż modele tłumaczeń maszynowych, ponieważ nie wymagają ogromnych baz danych fraz i idiomów. Nowoczesne usługi AI oferujące tłumaczenia często łączą różne techniki, mieszając statystyczne tłumaczenie maszynowe z tłumaczeniem neuronowym.

Nie istnieje 1:1 tłumaczenie dla żadnej pary językowej. Różne modele tłumaczeń mogą dawać nieco inne wyniki w zależności od danych użytych do ich trenowania. Tłumaczenia nie zawsze są symetryczne – jeśli przetłumaczysz zdanie z jednego języka na inny, a następnie z powrotem na pierwszy język, możesz otrzymać nieco inne zdanie jako wynik.

✅ Wypróbuj różne tłumacze online, takie jak [Bing Translate](https://www.bing.com/translator), [Google Translate](https://translate.google.com) lub aplikację Apple Translate. Porównaj przetłumaczone wersje kilku zdań. Spróbuj także przetłumaczyć w jednym, a następnie przetłumaczyć z powrotem w innym.

## Usługi tłumaczeniowe

Istnieje wiele usług AI, które można wykorzystać w aplikacjach do tłumaczenia mowy i tekstu.

### Cognitive Services Speech Service

![Logo usługi mowy](../../../../../translated_images/pl/azure-speech-logo.a1f08c4befb0159f.webp)

Usługa mowy, z której korzystałeś w ostatnich lekcjach, ma możliwości tłumaczenia w rozpoznawaniu mowy. Podczas rozpoznawania mowy możesz zażądać nie tylko tekstu mowy w tym samym języku, ale także w innych językach.

> 💁 Jest to dostępne tylko w SDK mowy, REST API nie ma wbudowanych tłumaczeń.

### Cognitive Services Translator Service

![Logo usługi tłumacza](../../../../../translated_images/pl/azure-translator-logo.c6ed3a4a433edfd2.webp)

Usługa Translator to dedykowana usługa tłumaczeniowa, która może tłumaczyć tekst z jednego języka na jeden lub więcej języków docelowych. Oprócz tłumaczenia obsługuje szeroki zakres dodatkowych funkcji, takich jak maskowanie wulgaryzmów. Pozwala także na dostarczenie konkretnego tłumaczenia dla danego słowa lub zdania, aby pracować z terminami, których nie chcesz tłumaczyć, lub które mają określone, dobrze znane tłumaczenie.

Na przykład, tłumacząc zdanie "I have a Raspberry Pi", odnosząc się do jednopłytkowego komputera, na inny język, taki jak francuski, chciałbyś zachować nazwę "Raspberry Pi" bez tłumaczenia, co daje "J’ai un Raspberry Pi" zamiast "J’ai une pi aux framboises".

## Tworzenie zasobu tłumacza

Do tej lekcji będziesz potrzebować zasobu Translator. Użyjesz REST API do tłumaczenia tekstu.

### Zadanie – tworzenie zasobu tłumacza

1. W terminalu lub wierszu poleceń uruchom następujące polecenie, aby utworzyć zasób Translator w grupie zasobów `smart-timer`.

    ```sh
    az cognitiveservices account create --name smart-timer-translator \
                                        --resource-group smart-timer \
                                        --kind TextTranslation \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamień `<location>` na lokalizację, której użyłeś podczas tworzenia grupy zasobów.

1. Pobierz klucz dla usługi Translator:

    ```sh
    az cognitiveservices account keys list --name smart-timer-translator \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Skopiuj jeden z kluczy.

## Obsługa wielu języków w aplikacjach za pomocą tłumaczeń

W idealnym świecie cała Twoja aplikacja powinna rozumieć jak najwięcej różnych języków, od rozpoznawania mowy, przez rozumienie języka, po odpowiedzi w mowie. To jednak wymaga dużo pracy, więc usługi tłumaczeniowe mogą przyspieszyć czas dostarczenia aplikacji.

![Architektura inteligentnego timera tłumaczącego japoński na angielski, przetwarzającego w angielskim, a następnie tłumaczącego z powrotem na japoński](../../../../../translated_images/pl/translated-smart-timer.08ac20057fdc5c37.webp)

Wyobraź sobie, że budujesz inteligentny timer, który używa angielskiego od początku do końca, rozumiejąc mowę po angielsku i konwertując ją na tekst, przetwarzając rozumienie języka w angielskim, budując odpowiedzi w angielskim i odpowiadając mową w angielskim. Jeśli chciałbyś dodać obsługę japońskiego, mógłbyś zacząć od tłumaczenia mówionego japońskiego na tekst w języku angielskim, a następnie pozostawić rdzeń aplikacji bez zmian, a na końcu przetłumaczyć tekst odpowiedzi na japoński przed wygenerowaniem odpowiedzi w mowie. Pozwoliłoby to szybko dodać obsługę japońskiego, a pełną obsługę od początku do końca można by dodać później.

> 💁 Wadą polegania na tłumaczeniach maszynowych jest to, że różne języki i kultury mają różne sposoby wyrażania tych samych rzeczy, więc tłumaczenie może nie odpowiadać wyrażeniu, którego oczekujesz.

Tłumaczenia maszynowe otwierają również możliwości dla aplikacji i urządzeń, które mogą tłumaczyć treści tworzone przez użytkowników w czasie rzeczywistym. Science fiction często przedstawia "uniwersalne tłumacze", urządzenia, które mogą tłumaczyć z języków obcych na (zazwyczaj) amerykański angielski. Te urządzenia to już nie tylko science fiction, ale bardziej naukowy fakt, jeśli pominąć część o obcych. Istnieją już aplikacje i urządzenia oferujące tłumaczenie mowy i tekstu w czasie rzeczywistym, wykorzystujące kombinacje usług mowy i tłumaczeń.

Jednym z przykładów jest aplikacja mobilna [Microsoft Translator](https://www.microsoft.com/translator/apps/?WT.mc_id=academic-17441-jabenn), zaprezentowana w tym filmie:

[![Funkcja na żywo Microsoft Translator w akcji](https://img.youtube.com/vi/16yAGeP2FuM/0.jpg)](https://www.youtube.com/watch?v=16yAGeP2FuM)

> 🎥 Kliknij obraz powyżej, aby obejrzeć film

Wyobraź sobie posiadanie takiego urządzenia, zwłaszcza podczas podróży lub interakcji z osobami, których języka nie znasz. Automatyczne urządzenia tłumaczeniowe na lotniskach lub w szpitalach mogłyby znacząco poprawić dostępność.

✅ Zrób badania: Czy istnieją jakieś komercyjnie dostępne urządzenia IoT do tłumaczeń? A co z funkcjami tłumaczenia wbudowanymi w inteligentne urządzenia?

> 👽 Chociaż nie istnieją prawdziwe uniwersalne tłumacze pozwalające nam rozmawiać z obcymi, [Microsoft Translator obsługuje język klingoński](https://www.microsoft.com/translator/blog/2013/05/14/announcing-klingon-for-bing-translator/?WT.mc_id=academic-17441-jabenn). Qapla’!

## Tłumaczenie tekstu za pomocą usługi AI

Możesz użyć usługi AI, aby dodać tę funkcję tłumaczenia do swojego inteligentnego timera.

### Zadanie – tłumaczenie tekstu za pomocą usługi AI

Przejdź przez odpowiedni przewodnik, aby przetłumaczyć tekst na swoim urządzeniu IoT:

* [Arduino - Wio Terminal](wio-terminal-translate-speech.md)
* [Komputer jednopłytkowy - Raspberry Pi](pi-translate-speech.md)
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device-translate-speech.md)

---

## 🚀 Wyzwanie

W jaki sposób tłumaczenia maszynowe mogą przynieść korzyści innym aplikacjom IoT poza inteligentnymi urządzeniami? Pomyśl o różnych sposobach, w jakie tłumaczenia mogą pomóc, nie tylko w przypadku mowy, ale także tekstu.

## Quiz po lekcji

[Quiz po lekcji](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/48)

## Przegląd i samodzielna nauka

* Przeczytaj więcej o tłumaczeniu maszynowym na [stronie o tłumaczeniu maszynowym w Wikipedii](https://wikipedia.org/wiki/Machine_translation)
* Przeczytaj więcej o tłumaczeniu neuronowym na [stronie o tłumaczeniu neuronowym w Wikipedii](https://wikipedia.org/wiki/Neural_machine_translation)
* Sprawdź listę obsługiwanych języków dla usług mowy Microsoft w [dokumentacji o obsłudze języków i głosów dla usługi mowy na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/language-support?WT.mc_id=academic-17441-jabenn)

## Zadanie

[Zbuduj uniwersalny tłumacz](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za autorytatywne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.