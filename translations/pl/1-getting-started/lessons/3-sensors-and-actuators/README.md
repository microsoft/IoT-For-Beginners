<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "e9ee00eb5fc55922a73762acc542166b",
  "translation_date": "2025-08-26T07:02:13+00:00",
  "source_file": "1-getting-started/lessons/3-sensors-and-actuators/README.md",
  "language_code": "pl"
}
-->
# Interakcja ze światem fizycznym za pomocą czujników i siłowników

![Szkicowy przegląd tej lekcji](../../../../../translated_images/lesson-3.cc3b7b4cd646de598698cce043c0393fd62ef42bac2eaf60e61272cd844250f4.pl.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obraz, aby zobaczyć większą wersję.

Ta lekcja była częścią serii [Hello IoT](https://youtube.com/playlist?list=PLmsFUfdnGr3xRts0TIwyaHyQuHaNQcb6-) organizowanej przez [Microsoft Reactor](https://developer.microsoft.com/reactor/?WT.mc_id=academic-17441-jabenn). Lekcja została przeprowadzona w formie dwóch filmów – godzinnej lekcji oraz godzinnej sesji pytań i odpowiedzi, podczas której omówiono szczegóły i odpowiadano na pytania.

[![Lekcja 3: Interakcja ze światem fizycznym za pomocą czujników i siłowników](https://img.youtube.com/vi/Lqalu1v6aF4/0.jpg)](https://youtu.be/Lqalu1v6aF4)

[![Lekcja 3: Interakcja ze światem fizycznym za pomocą czujników i siłowników - Sesja pytań i odpowiedzi](https://img.youtube.com/vi/qR3ekcMlLWA/0.jpg)](https://youtu.be/qR3ekcMlLWA)

> 🎥 Kliknij powyższe obrazy, aby obejrzeć filmy

## Quiz przed lekcją

[Quiz przed lekcją](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/5)

## Wprowadzenie

W tej lekcji wprowadzimy dwa kluczowe pojęcia dotyczące urządzeń IoT – czujniki i siłowniki. Będziesz mieć okazję praktycznie z nimi pracować, dodając czujnik światła do swojego projektu IoT, a następnie diodę LED sterowaną poziomem światła, tworząc w ten sposób lampkę nocną.

W tej lekcji omówimy:

* [Czym są czujniki?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Jak używać czujnika](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Rodzaje czujników](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Czym są siłowniki?](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Jak używać siłownika](../../../../../1-getting-started/lessons/3-sensors-and-actuators)
* [Rodzaje siłowników](../../../../../1-getting-started/lessons/3-sensors-and-actuators)

## Czym są czujniki?

Czujniki to urządzenia sprzętowe, które wykrywają świat fizyczny – mierzą jedną lub więcej właściwości otoczenia i przesyłają informacje do urządzenia IoT. Istnieje ogromna różnorodność czujników, ponieważ można mierzyć wiele różnych rzeczy, od właściwości naturalnych, takich jak temperatura powietrza, po interakcje fizyczne, takie jak ruch.

Niektóre popularne czujniki to:

* Czujniki temperatury – mierzą temperaturę powietrza lub obiektu, w którym są zanurzone. Dla hobbystów i programistów często łączone są z czujnikami ciśnienia i wilgotności w jednym urządzeniu.
* Przyciski – wykrywają, kiedy zostały naciśnięte.
* Czujniki światła – wykrywają poziomy światła, w tym światło widzialne, UV, IR lub konkretne kolory.
* Kamery – rejestrują wizualną reprezentację świata, robiąc zdjęcia lub przesyłając wideo.
* Akcelerometry – wykrywają ruch w wielu kierunkach.
* Mikrofony – wykrywają dźwięk, zarówno ogólny poziom hałasu, jak i dźwięk kierunkowy.

✅ Zrób małe badanie. Jakie czujniki ma Twój telefon?

Wszystkie czujniki mają jedną wspólną cechę – przekształcają to, co wykrywają, w sygnał elektryczny, który może być interpretowany przez urządzenie IoT. Interpretacja tego sygnału zależy od rodzaju czujnika oraz protokołu komunikacyjnego używanego do komunikacji z urządzeniem IoT.

## Jak używać czujnika

Skorzystaj z odpowiedniego przewodnika, aby dodać czujnik do swojego urządzenia IoT:

* [Arduino - Wio Terminal](wio-terminal-sensor.md)
* [Komputer jednopłytkowy - Raspberry Pi](pi-sensor.md)
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device-sensor.md)

## Rodzaje czujników

Czujniki mogą być analogowe lub cyfrowe.

### Czujniki analogowe

Najprostsze czujniki to czujniki analogowe. Otrzymują napięcie z urządzenia IoT, komponenty czujnika dostosowują to napięcie, a napięcie zwracane przez czujnik jest mierzone, aby uzyskać wartość czujnika.

> 🎓 Napięcie to miara siły, z jaką prąd elektryczny jest przesuwany z jednego miejsca do drugiego, np. z dodatniego bieguna baterii do bieguna ujemnego. Na przykład standardowa bateria AA ma napięcie 1,5V (V to symbol woltów) i może przesuwać prąd z siłą 1,5V. Różne urządzenia elektryczne wymagają różnych napięć, np. dioda LED działa przy napięciu 2-3V, ale żarówka o mocy 100W potrzebuje 240V. Więcej o napięciu przeczytasz na [stronie Wikipedii o napięciu](https://wikipedia.org/wiki/Voltage).

Przykładem jest potencjometr – pokrętło, które można obracać między dwoma pozycjami, a czujnik mierzy obrót.

![Potencjometr ustawiony w połowie, otrzymujący 5 woltów i zwracający 3,8 woltów](../../../../../translated_images/potentiometer.35a348b9ce22f6ec.pl.png)

Urządzenie IoT wysyła sygnał elektryczny do potencjometru o napięciu, np. 5 woltów (5V). W miarę regulacji potencjometru zmienia się napięcie wychodzące z drugiej strony. Wyobraź sobie potencjometr oznaczony jako pokrętło od 0 do [11](https://wikipedia.org/wiki/Up_to_eleven), np. pokrętło głośności w wzmacniaczu. Gdy potencjometr jest w pozycji wyłączonej (0), wychodzi 0V. Gdy jest w pozycji maksymalnej (11), wychodzi 5V.

> 🎓 To uproszczenie. Więcej o potencjometrach i rezystorach zmiennych przeczytasz na [stronie Wikipedii o potencjometrach](https://wikipedia.org/wiki/Potentiometer).

Napięcie wychodzące z czujnika jest następnie odczytywane przez urządzenie IoT, które może na nie odpowiedzieć. W zależności od czujnika napięcie to może być wartością arbitralną lub odpowiadać standardowej jednostce. Na przykład analogowy czujnik temperatury oparty na [termistorze](https://wikipedia.org/wiki/Thermistor) zmienia swoją rezystancję w zależności od temperatury. Napięcie wyjściowe można następnie przeliczyć na temperaturę w kelwinach, a następnie na °C lub °F za pomocą obliczeń w kodzie.

✅ Jak myślisz, co się stanie, jeśli czujnik zwróci wyższe napięcie niż to, które zostało wysłane (np. pochodzące z zewnętrznego źródła zasilania)? ⛔️ NIE testuj tego.

#### Konwersja analogowo-cyfrowa

Urządzenia IoT są cyfrowe – nie mogą pracować z wartościami analogowymi, tylko z 0 i 1. Oznacza to, że wartości czujników analogowych muszą zostać przekształcone na sygnał cyfrowy, zanim będą mogły zostać przetworzone. Wiele urządzeń IoT ma przetworniki analogowo-cyfrowe (ADC), które konwertują wejścia analogowe na cyfrowe reprezentacje ich wartości. Czujniki mogą również współpracować z ADC za pośrednictwem płytki łączącej. Na przykład w ekosystemie Seeed Grove z Raspberry Pi czujniki analogowe podłącza się do określonych portów na „nakładce” (hat), która jest podłączona do pinów GPIO Pi i zawiera ADC do konwersji napięcia na sygnał cyfrowy.

Wyobraź sobie, że masz analogowy czujnik światła podłączony do urządzenia IoT, które działa na 3,3V i zwraca wartość 1V. To 1V nie ma znaczenia w świecie cyfrowym, więc musi zostać przekształcone. Napięcie zostanie przekształcone na wartość analogową w skali zależnej od urządzenia i czujnika. Przykładem jest czujnik światła Seeed Grove, który zwraca wartości od 0 do 1023. Dla tego czujnika działającego na 3,3V wyjście 1V odpowiada wartości 300. Urządzenie IoT nie może obsługiwać 300 jako wartości analogowej, więc wartość zostanie przekształcona na `0000000100101100`, binarną reprezentację liczby 300 przez nakładkę Grove. Następnie zostanie przetworzona przez urządzenie IoT.

✅ Jeśli nie znasz systemu binarnego, zrób małe badanie, aby dowiedzieć się, jak liczby są reprezentowane za pomocą 0 i 1. [Lekcja wprowadzająca do systemu binarnego na BBC Bitesize](https://www.bbc.co.uk/bitesize/guides/zwsbwmn/revision/1) to świetne miejsce na start.

Z perspektywy programowania wszystko to jest zwykle obsługiwane przez biblioteki dostarczane z czujnikami, więc nie musisz martwić się o tę konwersję samodzielnie. Dla czujnika światła Grove użyjesz biblioteki Python i wywołasz właściwość `light`, lub użyjesz biblioteki Arduino i wywołasz `analogRead`, aby uzyskać wartość 300.

### Cyfrowe czujniki

Cyfrowe czujniki, podobnie jak analogowe, wykrywają świat wokół siebie za pomocą zmian napięcia elektrycznego. Różnica polega na tym, że wysyłają sygnał cyfrowy, albo mierząc tylko dwa stany, albo używając wbudowanego ADC. Cyfrowe czujniki stają się coraz bardziej popularne, aby uniknąć konieczności używania ADC w płytce łączącej lub na samym urządzeniu IoT.

Najprostszym cyfrowym czujnikiem jest przycisk lub przełącznik. Jest to czujnik z dwoma stanami: włączony lub wyłączony.

![Przycisk otrzymuje 5 woltów. Gdy nie jest wciśnięty, zwraca 0 woltów, gdy jest wciśnięty, zwraca 5 woltów](../../../../../translated_images/button.eadb560b77ac45e56f523d9d8876e40444f63b419e33eb820082d461fa79490b.pl.png)

Piny w urządzeniach IoT, takie jak piny GPIO, mogą bezpośrednio mierzyć ten sygnał jako 0 lub 1. Jeśli napięcie wysłane jest takie samo jak napięcie zwrócone, odczytana wartość to 1, w przeciwnym razie wartość to 0. Nie ma potrzeby konwersji sygnału, może on być tylko 1 lub 0.

> 💁 Napięcia nigdy nie są dokładne, zwłaszcza że komponenty w czujniku mają pewną rezystancję, więc zwykle istnieje tolerancja. Na przykład piny GPIO w Raspberry Pi działają na 3,3V i odczytują sygnał powyżej 1,8V jako 1, a poniżej 1,8V jako 0.

* 3,3V wchodzi do przycisku. Przycisk jest wyłączony, więc wychodzi 0V, co daje wartość 0.
* 3,3V wchodzi do przycisku. Przycisk jest włączony, więc wychodzi 3,3V, co daje wartość 1.

Bardziej zaawansowane cyfrowe czujniki odczytują wartości analogowe, a następnie konwertują je za pomocą wbudowanych ADC na sygnały cyfrowe. Na przykład cyfrowy czujnik temperatury nadal używa termopary w taki sam sposób jak czujnik analogowy i nadal mierzy zmianę napięcia spowodowaną rezystancją termopary w danej temperaturze. Zamiast zwracać wartość analogową i polegać na urządzeniu lub płytce łączącej w celu konwersji na sygnał cyfrowy, wbudowany w czujnik ADC konwertuje wartość i wysyła ją jako serię 0 i 1 do urządzenia IoT. Te 0 i 1 są wysyłane w taki sam sposób jak sygnał cyfrowy dla przycisku, gdzie 1 oznacza pełne napięcie, a 0 oznacza 0V.

![Cyfrowy czujnik temperatury konwertujący odczyt analogowy na dane binarne z 0 jako 0 woltów i 1 jako 5 woltów przed wysłaniem do urządzenia IoT](../../../../../translated_images/temperature-as-digital.85004491b977bae1.pl.png)

Wysyłanie danych cyfrowych pozwala czujnikom stać się bardziej zaawansowanymi i przesyłać bardziej szczegółowe dane, a nawet zaszyfrowane dane dla bezpiecznych czujników. Przykładem jest kamera. Jest to czujnik, który rejestruje obraz i przesyła go jako dane cyfrowe zawierające ten obraz, zwykle w skompresowanym formacie, takim jak JPEG, do odczytu przez urządzenie IoT. Może nawet przesyłać strumieniowo wideo, rejestrując obrazy i przesyłając je klatka po klatce lub jako skompresowany strumień wideo.

## Czym są siłowniki?

Siłowniki to przeciwieństwo czujników – przekształcają sygnał elektryczny z urządzenia IoT w interakcję ze światem fizycznym, taką jak emitowanie światła lub dźwięku, czy poruszanie silnikiem.

Niektóre popularne siłowniki to:

* Dioda LED – emituje światło po włączeniu.
* Głośnik – emituje dźwięk na podstawie przesłanego sygnału, od prostego brzęczyka po głośnik audio odtwarzający muzykę.
* Silnik krokowy – przekształca sygnał w określoną ilość obrotu, np. obrót pokrętła o 90°.
* Przekaźnik – przełącznik, który można włączyć lub wyłączyć za pomocą sygnału elektrycznego. Pozwala na włączenie większych napięć za pomocą małego napięcia z urządzenia IoT.
* Ekrany – bardziej złożone siłowniki, które wyświetlają informacje na wielosegmentowym wyświetlaczu. Ekrany mogą być od prostych wyświetlaczy LED po wysokiej rozdzielczości monitory wideo.

✅ Zrób małe badanie. Jakie siłowniki ma Twój telefon?

## Jak używać siłownika

Skorzystaj z odpowiedniego przewodnika, aby dodać siłownik do swojego urządzenia IoT, sterowany przez czujnik, aby zbudować lampkę nocną IoT. Będzie ona zbierać poziomy światła z czujnika światła i używać siłownika w postaci diody LED do emitowania światła, gdy wykryty poziom światła będzie zbyt niski.

![Schemat przepływu zadania pokazujący odczyt i sprawdzanie poziomów światła oraz sterowanie diodą LED](../../../../../translated_images/assignment-1-flow.7552a51acb1a5ec858dca6e855cdbb44206434006df8ba3799a25afcdab1665d.pl.png)

* [Arduino - Wio Terminal](wio-terminal-actuator.md)
* [Komputer jednopłytkowy - Raspberry Pi](pi-actuator.md)
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device-actuator.md)

## Rodzaje siłowników

Podobnie jak czujniki, siłowniki mogą być analogowe lub cyfrowe.

### Analogowe siłowniki

Analogowe siłowniki przyjmują sygnał analogowy i przekształcają go w jakąś interakcję, gdzie interakcja zmienia się w zależności od dostarczonego napięcia.

Przykładem jest ściemnialne światło, takie jak te, które możesz mieć w domu. Ilość dostarczonego napięcia decyduje o jasności światła.
![Światło przyciemnione przy niskim napięciu i jaśniejsze przy wyższym napięciu](../../../../../translated_images/dimmable-light.9ceffeb195dec1a849da718b2d71b32c35171ff7dfea9c07bbf82646a67acf6b.pl.png)

Podobnie jak w przypadku czujników, rzeczywiste urządzenie IoT działa na sygnałach cyfrowych, a nie analogowych. Oznacza to, że aby wysłać sygnał analogowy, urządzenie IoT potrzebuje przetwornika cyfrowo-analogowego (DAC), który może być wbudowany bezpośrednio w urządzenie IoT lub znajdować się na płytce połączeniowej. Przetwornik ten zamienia 0 i 1 z urządzenia IoT na napięcie analogowe, które może być używane przez siłownik.

✅ Co Twoim zdaniem się stanie, jeśli urządzenie IoT wyśle napięcie wyższe niż to, które siłownik może obsłużyć?  
⛔️ NIE testuj tego w praktyce.

#### Modulacja szerokości impulsu (PWM)

Inną opcją konwersji sygnałów cyfrowych z urządzenia IoT na sygnał analogowy jest modulacja szerokości impulsu (PWM). Polega to na wysyłaniu wielu krótkich impulsów cyfrowych, które działają jak sygnał analogowy.

Na przykład PWM można użyć do kontrolowania prędkości silnika.

Wyobraź sobie, że sterujesz silnikiem zasilanym napięciem 5V. Wysyłasz krótki impuls do silnika, przełączając napięcie na wysokie (5V) na dwie setne sekundy (0,02s). W tym czasie silnik może wykonać jedną dziesiątą obrotu, czyli 36°. Następnie sygnał pauzuje na dwie setne sekundy (0,02s), wysyłając niski sygnał (0V). Każdy cykl włączania i wyłączania trwa 0,04s. Cykl ten powtarza się.

![Modulacja szerokości impulsu - obrót silnika z prędkością 150 RPM](../../../../../translated_images/pwm-motor-150rpm.83347ac04ca38482.pl.png)

Oznacza to, że w ciągu jednej sekundy wysyłasz 25 impulsów 5V trwających 0,02s, które obracają silnik, a każdy z nich jest poprzedzony 0,02s przerwy przy 0V, gdy silnik się nie obraca. Każdy impuls obraca silnik o jedną dziesiątą obrotu, co oznacza, że silnik wykonuje 2,5 obrotu na sekundę. Użyłeś sygnału cyfrowego, aby obrócić silnik z prędkością 2,5 obrotu na sekundę, czyli 150 [obrotów na minutę](https://wikipedia.org/wiki/Revolutions_per_minute) (niestandardowa jednostka prędkości obrotowej).

```output
25 pulses per second x 0.1 rotations per pulse = 2.5 rotations per second
2.5 rotations per second x 60 seconds in a minute = 150rpm
```

> 🎓 Gdy sygnał PWM jest włączony przez połowę czasu, a wyłączony przez drugą połowę, nazywa się to [cyklem pracy 50%](https://wikipedia.org/wiki/Duty_cycle). Cykl pracy mierzy się jako procent czasu, w którym sygnał jest w stanie włączonym w porównaniu do stanu wyłączonego.

![Modulacja szerokości impulsu - obrót silnika z prędkością 75 RPM](../../../../../translated_images/pwm-motor-75rpm.a5e4c939934b6e14.pl.png)

Możesz zmienić prędkość silnika, zmieniając długość impulsów. Na przykład, przy tym samym silniku możesz zachować ten sam czas cyklu 0,04s, ale skrócić impuls włączony do 0,01s, a impuls wyłączony wydłużyć do 0,03s. Liczba impulsów na sekundę (25) pozostaje taka sama, ale każdy impuls włączony jest o połowę krótszy. Krótszy impuls obraca silnik o jedną dwudziestą obrotu, a przy 25 impulsach na sekundę silnik wykona 1,25 obrotu na sekundę, czyli 75 RPM. Zmieniając prędkość impulsów sygnału cyfrowego, zmniejszyłeś prędkość analogowego silnika o połowę.

```output
25 pulses per second x 0.05 rotations per pulse = 1.25 rotations per second
1.25 rotations per second x 60 seconds in a minute = 75rpm
```

✅ Jak utrzymać płynność obrotów silnika, szczególnie przy niskich prędkościach? Czy użyłbyś małej liczby długich impulsów z długimi przerwami, czy wielu bardzo krótkich impulsów z krótkimi przerwami?

> 💁 Niektóre czujniki również używają PWM do konwersji sygnałów analogowych na cyfrowe.

> 🎓 Więcej o modulacji szerokości impulsu możesz przeczytać na [stronie Wikipedii o PWM](https://wikipedia.org/wiki/Pulse-width_modulation).

### Siłowniki cyfrowe

Siłowniki cyfrowe, podobnie jak czujniki cyfrowe, mają dwa stany kontrolowane przez wysokie lub niskie napięcie albo mają wbudowany DAC, który pozwala na konwersję sygnału cyfrowego na analogowy.

Prostym siłownikiem cyfrowym jest dioda LED. Gdy urządzenie wysyła sygnał cyfrowy 1, wysyłane jest wysokie napięcie, które zapala diodę LED. Gdy wysyłany jest sygnał cyfrowy 0, napięcie spada do 0V i dioda LED gaśnie.

![Dioda LED wyłączona przy 0V i włączona przy 5V](../../../../../translated_images/led.ec6d94f66676a174ad06d9fa9ea49c2ee89beb18b312d5c6476467c66375b07f.pl.png)

✅ Jakie inne proste siłowniki dwustanowe przychodzą Ci do głowy? Jednym z przykładów jest elektromagnes (solenoid), który można aktywować, aby np. przesunąć rygiel drzwi, blokując/odblokowując drzwi.

Bardziej zaawansowane siłowniki cyfrowe, takie jak ekrany, wymagają przesyłania danych cyfrowych w określonych formatach. Zazwyczaj są one dostarczane z bibliotekami, które ułatwiają wysyłanie odpowiednich danych do ich sterowania.

---

## 🚀 Wyzwanie

Wyzwanie z ostatnich dwóch lekcji polegało na wymienieniu jak największej liczby urządzeń IoT znajdujących się w Twoim domu, szkole lub miejscu pracy oraz określeniu, czy są one oparte na mikrokontrolerach, komputerach jednopłytkowych, czy może na mieszance obu.

Dla każdego wymienionego urządzenia zastanów się, z jakimi czujnikami i siłownikami są one połączone. Jaki jest cel każdego czujnika i siłownika podłączonego do tych urządzeń?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/6)

## Przegląd i samodzielna nauka

* Przeczytaj o elektryczności i obwodach na [ThingLearn](http://thinglearn.jenlooper.com/curriculum/).  
* Przeczytaj o różnych typach czujników temperatury w [przewodniku Seeed Studios o czujnikach temperatury](https://www.seeedstudio.com/blog/2019/10/14/temperature-sensors-for-arduino-projects/).  
* Przeczytaj o diodach LED na [stronie Wikipedii o diodach LED](https://wikipedia.org/wiki/Light-emitting_diode).  

## Zadanie

[Zbadaj czujniki i siłowniki](assignment.md)  

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.