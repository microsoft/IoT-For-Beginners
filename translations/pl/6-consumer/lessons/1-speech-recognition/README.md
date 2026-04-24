# Rozpoznawanie mowy za pomocą urządzenia IoT

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-21.e34de51354d6606f.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ten film przedstawia przegląd usługi rozpoznawania mowy Azure, która będzie omawiana w tej lekcji:

[![Jak rozpocząć korzystanie z zasobu Cognitive Services Speech z kanału Microsoft Azure na YouTube](https://img.youtube.com/vi/iW0Fw0l3mrA/0.jpg)](https://www.youtube.com/watch?v=iW0Fw0l3mrA)

> 🎥 Kliknij powyższy obraz, aby obejrzeć film

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/41)

## Wprowadzenie

„Alexa, ustaw minutnik na 12 minut”

„Alexa, jaki jest status minutnika?”

„Alexa, ustaw minutnik na 8 minut i nazwij go gotowanie brokułów na parze”

Inteligentne urządzenia stają się coraz bardziej wszechobecne. Nie tylko jako inteligentne głośniki, takie jak HomePods, Echos i Google Homes, ale także wbudowane w nasze telefony, zegarki, a nawet oprawy oświetleniowe i termostaty.

> 💁 W moim domu mam co najmniej 19 urządzeń z asystentami głosowymi, i to tylko te, o których wiem!

Sterowanie głosem zwiększa dostępność, umożliwiając osobom z ograniczoną mobilnością interakcję z urządzeniami. Niezależnie od tego, czy jest to trwała niepełnosprawność, taka jak brak kończyn od urodzenia, czy tymczasowa, jak złamana ręka, albo sytuacja, gdy masz zajęte ręce zakupami lub opieką nad dziećmi, możliwość sterowania domem za pomocą głosu zamiast rąk otwiera świat nowych możliwości. Krzyknięcie „Hej Siri, zamknij drzwi garażowe” podczas zmiany pieluchy i radzenia sobie z niesfornym maluchem może być małą, ale skuteczną poprawą jakości życia.

Jednym z bardziej popularnych zastosowań asystentów głosowych jest ustawianie minutników, zwłaszcza kuchennych. Możliwość ustawienia wielu minutników za pomocą głosu to ogromna pomoc w kuchni – nie trzeba przerywać wyrabiania ciasta, mieszania zupy czy mycia rąk z nadzienia do pierogów, aby użyć fizycznego minutnika.

W tej lekcji nauczysz się, jak wbudować rozpoznawanie głosu w urządzenia IoT. Dowiesz się o mikrofonach jako czujnikach, jak przechwytywać dźwięk z mikrofonu podłączonego do urządzenia IoT oraz jak używać AI do konwersji tego, co zostało usłyszane, na tekst. W dalszej części projektu zbudujesz inteligentny minutnik kuchenny, który pozwoli ustawiać minutniki za pomocą głosu w wielu językach.

W tej lekcji omówimy:

* [Mikrofony](../../../../../6-consumer/lessons/1-speech-recognition)
* [Przechwytywanie dźwięku z urządzenia IoT](../../../../../6-consumer/lessons/1-speech-recognition)
* [Mowa na tekst](../../../../../6-consumer/lessons/1-speech-recognition)
* [Konwersja mowy na tekst](../../../../../6-consumer/lessons/1-speech-recognition)

## Mikrofony

Mikrofony to analogowe czujniki, które przekształcają fale dźwiękowe w sygnały elektryczne. Wibracje powietrza powodują minimalne ruchy elementów mikrofonu, co z kolei wywołuje niewielkie zmiany w sygnałach elektrycznych. Te zmiany są następnie wzmacniane, aby wygenerować sygnał elektryczny.

### Rodzaje mikrofonów

Mikrofony występują w różnych typach:

* Dynamiczne – Mikrofony dynamiczne mają magnes przymocowany do ruchomej membrany, która porusza się w cewce drutu, tworząc prąd elektryczny. Jest to odwrotność większości głośników, które wykorzystują prąd elektryczny do poruszania magnesem w cewce drutu, poruszając membraną w celu wytworzenia dźwięku. Oznacza to, że głośniki mogą być używane jako mikrofony dynamiczne, a mikrofony dynamiczne jako głośniki. W urządzeniach takich jak domofony, gdzie użytkownik albo słucha, albo mówi, ale nie robi obu rzeczy jednocześnie, jedno urządzenie może działać zarówno jako głośnik, jak i mikrofon.

    Mikrofony dynamiczne nie potrzebują zasilania, aby działać – sygnał elektryczny jest generowany wyłącznie przez mikrofon.

    ![Patti Smith śpiewająca do mikrofonu dynamicznego typu kardioidalnego Shure SM58](../../../../../translated_images/pl/dynamic-mic.8babac890a2d80df.webp)

* Wstęgowe – Mikrofony wstęgowe są podobne do dynamicznych, ale zamiast membrany mają metalową wstęgę. Ta wstęga porusza się w polu magnetycznym, generując prąd elektryczny. Podobnie jak mikrofony dynamiczne, mikrofony wstęgowe nie potrzebują zasilania, aby działać.

    ![Edmund Lowe, amerykański aktor, stojący przy mikrofonie radiowym (oznaczonym jako (NBC) Blue Network), trzymający scenariusz, 1942](../../../../../translated_images/pl/ribbon-mic.eacc8e092c7441ca.webp)

* Pojemnościowe – Mikrofony pojemnościowe mają cienką metalową membranę i stałą metalową płytkę tylną. Do obu tych elementów przykładane jest napięcie, a gdy membrana wibruje, zmienia się ładunek elektrostatyczny między płytkami, generując sygnał. Mikrofony pojemnościowe potrzebują zasilania, aby działać – nazywanego *zasilaniem fantomowym*.

    ![Mikrofon pojemnościowy o małej membranie C451B firmy AKG Acoustics](../../../../../translated_images/pl/condenser-mic.6f6ed5b76ca19e0e.webp)

* MEMS – Mikrofony systemów mikroelektromechanicznych, czyli MEMS, to mikrofony na chipie. Mają one czułą na ciśnienie membranę wytrawioną na krzemowym chipie i działają podobnie do mikrofonu pojemnościowego. Te mikrofony mogą być bardzo małe i zintegrowane z układami elektronicznymi.

    ![Mikrofon MEMS na płytce drukowanej](../../../../../translated_images/pl/mems-microphone.80574019e1f5e4d9.webp)

    Na powyższym obrazie chip oznaczony jako **LEFT** to mikrofon MEMS z membraną o szerokości mniejszej niż milimetr.

✅ Zrób badanie: Jakie mikrofony masz wokół siebie – w komputerze, telefonie, zestawie słuchawkowym lub innych urządzeniach? Jakiego są typu?

### Cyfrowy dźwięk

Dźwięk to sygnał analogowy niosący bardzo szczegółowe informacje. Aby przekształcić ten sygnał na cyfrowy, dźwięk musi być próbkowany tysiące razy na sekundę.

> 🎓 Próbkowanie to proces konwersji sygnału dźwiękowego na wartość cyfrową, która reprezentuje sygnał w danym momencie.

![Wykres liniowy przedstawiający sygnał z dyskretnymi punktami w stałych odstępach](../../../../../translated_images/pl/sampling.6f4fadb3f2d9dfe7.webp)

Cyfrowy dźwięk jest próbkowany za pomocą modulacji kodu impulsowego (PCM). PCM polega na odczytywaniu napięcia sygnału i wybieraniu najbliższej wartości dyskretnej odpowiadającej temu napięciu, zgodnie z określoną rozdzielczością.

> 💁 Możesz myśleć o PCM jako o wersji czujnika modulacji szerokości impulsu (PWM). (PWM było omawiane w [lekcji 3 projektu wprowadzającego](../../../1-getting-started/lessons/3-sensors-and-actuators/README.md#pulse-width-modulation)). PCM konwertuje sygnał analogowy na cyfrowy, a PWM konwertuje sygnał cyfrowy na analogowy.

Na przykład większość serwisów streamingowych oferuje dźwięk 16-bitowy lub 24-bitowy. Oznacza to, że przekształcają napięcie w wartość mieszczącą się w 16-bitowej liczbie całkowitej lub 24-bitowej liczbie całkowitej. Dźwięk 16-bitowy mieści się w zakresie od -32 768 do 32 767, a 24-bitowy w zakresie od -8 388 608 do 8 388 607. Im więcej bitów, tym bliższa próbka jest temu, co faktycznie słyszą nasze uszy.

> 💁 Być może słyszałeś o dźwięku 8-bitowym, często nazywanym LoFi. To dźwięk próbkowany przy użyciu tylko 8 bitów, czyli w zakresie od -128 do 127. Pierwsze komputery obsługiwały dźwięk 8-bitowy z powodu ograniczeń sprzętowych, dlatego często kojarzy się go z retro grami.

Próbki są pobierane tysiące razy na sekundę, przy użyciu dobrze zdefiniowanych częstotliwości próbkowania mierzonych w kHz (tysiące odczytów na sekundę). Serwisy streamingowe używają 48 kHz dla większości dźwięków, ale niektóre formaty „bezstratne” używają nawet 96 kHz lub 192 kHz. Im wyższa częstotliwość próbkowania, tym bliższy oryginałowi będzie dźwięk, do pewnego momentu. Istnieją debaty, czy ludzie są w stanie zauważyć różnicę powyżej 48 kHz.

✅ Zrób badanie: Jeśli korzystasz z serwisu streamingowego, jaka jest częstotliwość próbkowania i rozdzielczość dźwięku, który oferuje? Jeśli używasz płyt CD, jaka jest częstotliwość próbkowania i rozdzielczość dźwięku na płytach CD?

Istnieje wiele różnych formatów danych audio. Prawdopodobnie słyszałeś o plikach mp3 – danych audio skompresowanych w celu zmniejszenia rozmiaru bez utraty jakości. Nieskompresowany dźwięk jest często przechowywany jako plik WAV – to plik zawierający 44 bajty informacji nagłówkowych, a następnie surowe dane audio. Nagłówek zawiera informacje takie jak częstotliwość próbkowania (na przykład 16 000 dla 16 kHz), rozdzielczość próbek (16 dla 16-bitów) i liczba kanałów. Po nagłówku plik WAV zawiera surowe dane audio.

> 🎓 Kanały odnoszą się do liczby różnych strumieni audio składających się na dźwięk. Na przykład dla dźwięku stereo z lewym i prawym kanałem byłyby 2 kanały. Dla dźwięku przestrzennego 7.1 w systemie kina domowego byłoby to 8 kanałów.

### Rozmiar danych audio

Dane audio są stosunkowo duże. Na przykład przechwytywanie nieskompresowanego dźwięku 16-bitowego przy 16 kHz (wystarczająca jakość dla modeli rozpoznawania mowy) zajmuje 32 KB danych na każdą sekundę dźwięku:

* 16-bit oznacza 2 bajty na próbkę (1 bajt to 8 bitów).
* 16 kHz to 16 000 próbek na sekundę.
* 16 000 x 2 bajty = 32 000 bajtów na sekundę.

To może wydawać się niewielką ilością danych, ale jeśli używasz mikrokontrolera z ograniczoną pamięcią, może to być dużo. Na przykład Wio Terminal ma 192 KB pamięci, która musi przechowywać kod programu i zmienne. Nawet jeśli kod programu byłby bardzo mały, nie można by przechwycić więcej niż 5 sekund dźwięku.

Mikrokontrolery mogą uzyskać dostęp do dodatkowej pamięci, takiej jak karty SD lub pamięć flash. Budując urządzenie IoT przechwytujące dźwięk, musisz upewnić się, że masz dodatkową pamięć, a Twój kod zapisuje przechwycony dźwięk bezpośrednio na tę pamięć. Podczas wysyłania danych do chmury należy przesyłać je strumieniowo z pamięci do żądania sieciowego, aby uniknąć wyczerpania pamięci przez próbę przechowywania całego bloku danych audio naraz.

## Przechwytywanie dźwięku z urządzenia IoT

Twoje urządzenie IoT może być podłączone do mikrofonu w celu przechwytywania dźwięku, gotowego do konwersji na tekst. Może być również podłączone do głośników w celu odtwarzania dźwięku. W późniejszych lekcjach będzie to używane do przekazywania informacji zwrotnych w formie dźwiękowej, ale warto skonfigurować głośniki już teraz, aby przetestować mikrofon.

### Zadanie – skonfiguruj mikrofon i głośniki

Przejdź przez odpowiedni przewodnik, aby skonfigurować mikrofon i głośniki dla swojego urządzenia IoT:

* [Arduino – Wio Terminal](wio-terminal-microphone.md)
* [Komputer jednopłytkowy – Raspberry Pi](pi-microphone.md)
* [Komputer jednopłytkowy – urządzenie wirtualne](virtual-device-microphone.md)

### Zadanie – przechwytywanie dźwięku

Przejdź przez odpowiedni przewodnik, aby przechwycić dźwięk na swoim urządzeniu IoT:

* [Arduino – Wio Terminal](wio-terminal-audio.md)
* [Komputer jednopłytkowy – Raspberry Pi](pi-audio.md)
* [Komputer jednopłytkowy – urządzenie wirtualne](virtual-device-audio.md)

## Mowa na tekst

Mowa na tekst, czyli rozpoznawanie mowy, polega na wykorzystaniu AI do konwersji słów z sygnału dźwiękowego na tekst.

### Modele rozpoznawania mowy

Aby przekształcić mowę na tekst, próbki sygnału dźwiękowego są grupowane i przekazywane do modelu uczenia maszynowego opartego na rekurencyjnej sieci neuronowej (RNN). Jest to rodzaj modelu uczenia maszynowego, który może wykorzystać wcześniejsze dane do podejmowania decyzji o nowych danych. Na przykład RNN może rozpoznać jeden blok próbek dźwięku jako dźwięk „Hel”, a gdy otrzyma kolejny blok, który uzna za dźwięk „lo”, może połączyć to z poprzednim dźwiękiem, znaleźć słowo „Hello” i wybrać je jako wynik.

Modele ML zawsze przyjmują dane o tym samym rozmiarze. Klasyfikator obrazów, który zbudowałeś w jednej z wcześniejszych lekcji, zmieniał rozmiar obrazów do ustalonego rozmiaru przed ich przetworzeniem. Podobnie jest z modelami mowy – muszą one przetwarzać bloki dźwięku o stałym rozmiarze. Modele mowy muszą być w stanie łączyć wyniki wielu przewidywań, aby uzyskać odpowiedź, co pozwala im rozróżniać np. „Hi” i „Highway” lub „flock” i „floccinaucinihilipilification”.

Modele mowy są również na tyle zaawansowane, że rozumieją kontekst i mogą korygować wykryte słowa w miarę przetwarzania kolejnych dźwięków. Na przykład, jeśli powiesz „Poszedłem do sklepu, żeby kupić dwa banany i jabłko też”, użyjesz trzech słów brzmiących tak samo, ale pisanych inaczej – to, two i too. Modele mowy są w stanie zrozumieć kontekst i użyć odpowiedniej pisowni słowa.
💁 Niektóre usługi mowy umożliwiają dostosowanie, aby lepiej działały w hałaśliwym środowisku, takim jak fabryki, lub z branżowymi terminami, na przykład nazwami chemikaliów. Te dostosowania są trenowane poprzez dostarczanie próbek audio i transkrypcji, i działają na zasadzie transferu uczenia, podobnie jak trenowanie klasyfikatora obrazów przy użyciu zaledwie kilku obrazów w poprzedniej lekcji.
### Prywatność

Podczas korzystania z funkcji rozpoznawania mowy w urządzeniach IoT dla konsumentów, prywatność jest niezwykle ważna. Te urządzenia stale nasłuchują dźwięków, więc jako użytkownik nie chcesz, aby wszystko, co mówisz, było przesyłane do chmury i zamieniane na tekst. Nie tylko zużywa to dużo przepustowości Internetu, ale ma również ogromne konsekwencje dla prywatności, zwłaszcza gdy niektórzy producenci inteligentnych urządzeń losowo wybierają nagrania audio, aby [ludzie mogli je porównać z wygenerowanym tekstem w celu ulepszenia modelu](https://www.theverge.com/2019/4/10/18305378/amazon-alexa-ai-voice-assistant-annotation-listen-private-recordings).

Chcesz, aby Twoje inteligentne urządzenie przesyłało dźwięk do chmury tylko wtedy, gdy z niego korzystasz, a nie gdy wykrywa dźwięki w Twoim domu, które mogą obejmować prywatne rozmowy czy intymne interakcje. Większość inteligentnych urządzeń działa w oparciu o *słowo wybudzające*, czyli frazę kluczową, taką jak „Alexa”, „Hej Siri” czy „OK Google”, która powoduje, że urządzenie „budzi się” i zaczyna nasłuchiwać tego, co mówisz, aż wykryje przerwę w mowie, co oznacza, że skończyłeś mówić do urządzenia.

> 🎓 Wykrywanie słowa wybudzającego nazywane jest również *rozpoznawaniem słów kluczowych* lub *wykrywaniem słów kluczowych*.

Te słowa wybudzające są wykrywane na urządzeniu, a nie w chmurze. Inteligentne urządzenia mają małe modele AI, które działają lokalnie i nasłuchują słowa wybudzającego. Gdy zostanie ono wykryte, urządzenie zaczyna przesyłać dźwięk do chmury w celu rozpoznania. Modele te są bardzo wyspecjalizowane i służą wyłącznie do wykrywania słowa wybudzającego.

> 💁 Niektóre firmy technologiczne zwiększają prywatność swoich urządzeń, umożliwiając częściową konwersję mowy na tekst na urządzeniu. Apple ogłosiło, że w ramach aktualizacji iOS i macOS w 2021 roku będą wspierać konwersję mowy na tekst na urządzeniu, co pozwoli obsługiwać wiele żądań bez konieczności korzystania z chmury. Jest to możliwe dzięki wydajnym procesorom w ich urządzeniach, które mogą obsługiwać modele ML.

✅ Jakie Twoim zdaniem są konsekwencje dla prywatności i etyki związane z przechowywaniem dźwięku przesyłanego do chmury? Czy takie nagrania powinny być przechowywane, a jeśli tak, to w jaki sposób? Czy uważasz, że wykorzystanie nagrań przez organy ścigania jest dobrą wymianą za utratę prywatności?

Wykrywanie słowa wybudzającego zazwyczaj wykorzystuje technikę znaną jako TinyML, która polega na przekształcaniu modeli ML tak, aby mogły działać na mikrokontrolerach. Modele te są małe i zużywają bardzo mało energii.

Aby uniknąć złożoności związanej z trenowaniem i używaniem modelu wykrywającego słowo wybudzające, inteligentny timer, który budujesz w tej lekcji, będzie używał przycisku do włączania rozpoznawania mowy.

> 💁 Jeśli chcesz spróbować stworzyć model wykrywający słowo wybudzające, który działa na Wio Terminal lub Raspberry Pi, sprawdź ten [samouczek od Edge Impulse dotyczący reagowania na Twój głos](https://docs.edgeimpulse.com/docs/responding-to-your-voice). Jeśli chcesz użyć swojego komputera, możesz wypróbować [szybki start z niestandardowym słowem kluczowym w dokumentacji Microsoft](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Konwersja mowy na tekst

![Logo usług mowy](../../../../../translated_images/pl/azure-speech-logo.a1f08c4befb0159f.webp)

Podobnie jak w przypadku klasyfikacji obrazów w wcześniejszym projekcie, istnieją gotowe usługi AI, które mogą przekształcić mowę z pliku audio na tekst. Jedną z takich usług jest Speech Service, część Cognitive Services, gotowych usług AI, które możesz wykorzystać w swoich aplikacjach.

### Zadanie - skonfiguruj zasób AI do obsługi mowy

1. Utwórz grupę zasobów dla tego projektu o nazwie `smart-timer`.

1. Użyj następującego polecenia, aby utworzyć darmowy zasób mowy:

    ```sh
    az cognitiveservices account create --name smart-timer \
                                        --resource-group smart-timer \
                                        --kind SpeechServices \
                                        --sku F0 \
                                        --yes \
                                        --location <location>
    ```

    Zamień `<location>` na lokalizację, którą wybrałeś podczas tworzenia grupy zasobów.

1. Aby uzyskać klucz API potrzebny do dostępu do zasobu mowy z kodu, uruchom następujące polecenie:

    ```sh
    az cognitiveservices account keys list --name smart-timer \
                                           --resource-group smart-timer \
                                           --output table
    ```

    Skopiuj jeden z kluczy.

### Zadanie - konwersja mowy na tekst

Przejdź przez odpowiedni przewodnik, aby przekształcić mowę na tekst na swoim urządzeniu IoT:

* [Arduino - Wio Terminal](wio-terminal-speech-to-text.md)
* [Komputer jednopłytkowy - Raspberry Pi](pi-speech-to-text.md)
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device-speech-to-text.md)

---

## 🚀 Wyzwanie

Rozpoznawanie mowy istnieje od dawna i stale się rozwija. Zbadaj obecne możliwości i porównaj, jak ewoluowały na przestrzeni lat, w tym jak dokładne są transkrypcje maszynowe w porównaniu z ludzkimi.

Jak myślisz, co przyniesie przyszłość dla rozpoznawania mowy?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/42)

## Przegląd i samodzielna nauka

* Przeczytaj o różnych typach mikrofonów i ich działaniu w artykule [jaka jest różnica między mikrofonami dynamicznymi a pojemnościowymi na Musician's HQ](https://musicianshq.com/whats-the-difference-between-dynamic-and-condenser-microphones/).
* Dowiedz się więcej o usłudze mowy w Cognitive Services w [dokumentacji usługi mowy na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/?WT.mc_id=academic-17441-jabenn).
* Przeczytaj o rozpoznawaniu słów kluczowych w [dokumentacji rozpoznawania słów kluczowych na Microsoft Docs](https://docs.microsoft.com/azure/cognitive-services/speech-service/keyword-recognition-overview?WT.mc_id=academic-17441-jabenn).

## Zadanie

[](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.