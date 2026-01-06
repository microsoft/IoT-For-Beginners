<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "1c9e5fa8b7be726c75a97232b1e41c97",
  "translation_date": "2025-08-26T06:26:33+00:00",
  "source_file": "5-retail/lessons/2-check-stock-device/README.md",
  "language_code": "pl"
}
-->
# Sprawdź zapasy za pomocą urządzenia IoT

![Szkicowy przegląd tej lekcji](../../../../../translated_images/lesson-20.0211df9551a8abb300fc8fcf7dc2789468dea2eabe9202273ac077b0ba37f15e.pl.jpg)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obrazek, aby zobaczyć większą wersję.

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/39)

## Wprowadzenie

W poprzedniej lekcji dowiedziałeś się o różnych zastosowaniach detekcji obiektów w handlu detalicznym. Nauczyłeś się również, jak trenować detektor obiektów do identyfikacji zapasów. W tej lekcji dowiesz się, jak używać swojego detektora obiektów z urządzenia IoT do liczenia zapasów.

W tej lekcji omówimy:

* [Liczenie zapasów](../../../../../5-retail/lessons/2-check-stock-device)
* [Wywołanie detektora obiektów z urządzenia IoT](../../../../../5-retail/lessons/2-check-stock-device)
* [Ramki ograniczające](../../../../../5-retail/lessons/2-check-stock-device)
* [Ponowne trenowanie modelu](../../../../../5-retail/lessons/2-check-stock-device)
* [Liczenie zapasów](../../../../../5-retail/lessons/2-check-stock-device)

> 🗑 To jest ostatnia lekcja w tym projekcie, więc po jej ukończeniu oraz wykonaniu zadania, nie zapomnij posprzątać swoje usługi w chmurze. Będziesz potrzebować tych usług do ukończenia zadania, więc upewnij się, że najpierw je wykonasz.
>
> Jeśli potrzebujesz instrukcji, zapoznaj się z [przewodnikiem czyszczenia projektu](../../../clean-up.md).

## Liczenie zapasów

Detektory obiektów mogą być używane do sprawdzania zapasów, zarówno do ich liczenia, jak i upewniania się, że znajdują się tam, gdzie powinny. Urządzenia IoT z kamerami mogą być rozmieszczone w całym sklepie, aby monitorować zapasy, zaczynając od miejsc, gdzie uzupełnianie towarów jest szczególnie ważne, takich jak obszary z niewielką ilością produktów o wysokiej wartości.

Na przykład, jeśli kamera skierowana jest na półki, które mogą pomieścić 8 puszek koncentratu pomidorowego, a detektor obiektów wykrywa tylko 7 puszek, oznacza to, że jedna brakuje i należy ją uzupełnić.

![7 puszek koncentratu pomidorowego na półce, 4 na górnym rzędzie, 3 na dolnym](../../../../../translated_images/stock-7-cans-tomato-paste.f86059cc573d7bec.pl.png)

Na powyższym obrazku detektor obiektów wykrył 7 puszek koncentratu pomidorowego na półce, która może pomieścić 8 puszek. Urządzenie IoT może nie tylko wysłać powiadomienie o konieczności uzupełnienia zapasów, ale także wskazać lokalizację brakującego produktu, co jest istotne, jeśli używasz robotów do uzupełniania półek.

> 💁 W zależności od sklepu i popularności produktu, uzupełnianie zapasów prawdopodobnie nie nastąpi, jeśli brakuje tylko jednej puszki. Musisz zbudować algorytm, który określi, kiedy należy uzupełnić zapasy, biorąc pod uwagę produkt, klientów i inne kryteria.

✅ W jakich innych scenariuszach można połączyć detekcję obiektów z robotami?

Czasami na półkach może znajdować się niewłaściwy towar. Może to być wynikiem błędu ludzkiego podczas uzupełniania zapasów lub decyzji klientów o zmianie zdania i odłożeniu produktu w pierwsze dostępne miejsce. W przypadku produktów trwałych, takich jak konserwy, jest to irytujące. Jeśli jednak chodzi o produkty nietrwałe, takie jak mrożonki lub produkty chłodzone, może to oznaczać, że produkt nie nadaje się już do sprzedaży, ponieważ trudno określić, jak długo był poza zamrażarką.

Detekcja obiektów może być używana do wykrywania nieoczekiwanych produktów, ponownie informując człowieka lub robota o konieczności ich zwrócenia na właściwe miejsce.

![Niepasująca puszka kukurydzy na półce z koncentratem pomidorowym](../../../../../translated_images/stock-rogue-corn.be1f3ada8c457854.pl.png)

Na powyższym obrazku puszka kukurydzy została umieszczona na półce obok koncentratu pomidorowego. Detektor obiektów wykrył to, umożliwiając urządzeniu IoT powiadomienie człowieka lub robota o konieczności zwrócenia puszki na właściwe miejsce.

## Wywołanie detektora obiektów z urządzenia IoT

Detektor obiektów, który trenowałeś w poprzedniej lekcji, może być wywoływany z urządzenia IoT.

### Zadanie - opublikuj iterację swojego detektora obiektów

Iteracje są publikowane z portalu Custom Vision.

1. Uruchom portal Custom Vision na [CustomVision.ai](https://customvision.ai) i zaloguj się, jeśli nie masz go już otwartego. Następnie otwórz swój projekt `stock-detector`.

1. Wybierz zakładkę **Performance** z opcji u góry.

1. Wybierz najnowszą iterację z listy *Iterations* po lewej stronie.

1. Kliknij przycisk **Publish** dla tej iteracji.

    ![Przycisk publikacji](../../../../../translated_images/custom-vision-object-detector-publish-button.34ee379fc650ccb9856c3868d0003f413b9529f102fc73c37168c98d721cc293.pl.png)

1. W oknie dialogowym *Publish Model* ustaw *Prediction resource* na zasób `stock-detector-prediction`, który utworzyłeś w poprzedniej lekcji. Pozostaw nazwę jako `Iteration2` i kliknij przycisk **Publish**.

1. Po opublikowaniu kliknij przycisk **Prediction URL**. Wyświetli to szczegóły dotyczące API predykcji, które będą potrzebne do wywołania modelu z urządzenia IoT. Dolna sekcja jest oznaczona *If you have an image file* i to są szczegóły, których potrzebujesz. Skopiuj wyświetlony URL, który będzie wyglądał mniej więcej tak:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/detect/iterations/Iteration2/image
    ```

    Gdzie `<location>` to lokalizacja użyta podczas tworzenia zasobu Custom Vision, a `<id>` to długi identyfikator składający się z liter i cyfr.

    Skopiuj również wartość *Prediction-Key*. Jest to klucz zabezpieczający, który musisz przekazać podczas wywoływania modelu. Tylko aplikacje, które przekazują ten klucz, mogą korzystać z modelu, inne aplikacje zostaną odrzucone.

    ![Okno dialogowe API predykcji pokazujące URL i klucz](../../../../../translated_images/custom-vision-prediction-key-endpoint.30c569ffd0338864f319911f052d5e9b8c5066cb0800a26dd6f7ff5713130ad8.pl.png)

✅ Gdy nowa iteracja zostanie opublikowana, będzie miała inną nazwę. Jak myślisz, jak zmienić iterację używaną przez urządzenie IoT?

### Zadanie - wywołaj detektor obiektów z urządzenia IoT

Skorzystaj z odpowiedniego przewodnika poniżej, aby użyć detektora obiektów z urządzenia IoT:

* [Arduino - Wio Terminal](wio-terminal-object-detector.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie](single-board-computer-object-detector.md)

## Ramki ograniczające

Kiedy używasz detektora obiektów, otrzymujesz nie tylko wykryte obiekty z ich etykietami i prawdopodobieństwami, ale także ramki ograniczające dla obiektów. Określają one, gdzie detektor obiektów wykrył obiekt z danym prawdopodobieństwem.

> 💁 Ramka ograniczająca to prostokąt, który definiuje obszar zawierający wykryty obiekt, granice dla obiektu.

Wyniki predykcji w zakładce **Predictions** w Custom Vision mają ramki ograniczające narysowane na obrazie przesłanym do predykcji.

![4 puszki koncentratu pomidorowego na półce z predykcjami dla 4 wykryć: 35.8%, 33.5%, 25.7% i 16.6%](../../../../../translated_images/custom-vision-stock-prediction.942266ab1bcca3410ecdf23643b9f5f570cfab2345235074e24c51f285777613.pl.png)

Na powyższym obrazku wykryto 4 puszki koncentratu pomidorowego. W wynikach nałożono czerwony kwadrat na każdy obiekt wykryty na obrazie, wskazując ramkę ograniczającą dla obrazu.

✅ Otwórz predykcje w Custom Vision i sprawdź ramki ograniczające.

Ramki ograniczające są definiowane za pomocą 4 wartości - top, left, height i width. Wartości te są w skali od 0 do 1, reprezentując pozycje jako procent rozmiaru obrazu. Punkt początkowy (pozycja 0,0) znajduje się w lewym górnym rogu obrazu, więc wartość top to odległość od góry, a dolna granica ramki ograniczającej to wartość top plus height.

![Ramka ograniczająca wokół puszki koncentratu pomidorowego](../../../../../translated_images/bounding-box.1420a7ea0d3d15f71e1ffb5cf4b2271d184fac051f990abc541975168d163684.pl.png)

Powyższy obrazek ma szerokość 600 pikseli i wysokość 800 pikseli. Ramka ograniczająca zaczyna się 320 pikseli w dół, co daje współrzędną top równą 0.4 (800 x 0.4 = 320). Od lewej ramka zaczyna się 240 pikseli w prawo, co daje współrzędną left równą 0.4 (600 x 0.4 = 240). Wysokość ramki wynosi 240 pikseli, co daje wartość height równą 0.3 (800 x 0.3 = 240). Szerokość ramki wynosi 120 pikseli, co daje wartość width równą 0.2 (600 x 0.2 = 120).

| Współrzędna | Wartość |
| ----------- | ------: |
| Top         | 0.4     |
| Left        | 0.4     |
| Height      | 0.3     |
| Width       | 0.2     |

Używanie wartości procentowych od 0 do 1 oznacza, że niezależnie od rozmiaru obrazu, ramka ograniczająca zaczyna się 0.4 długości w dół i w prawo, a jej wysokość to 0.3 wysokości obrazu, a szerokość to 0.2 szerokości obrazu.

Możesz używać ramek ograniczających w połączeniu z prawdopodobieństwami, aby ocenić, jak dokładne jest wykrycie. Na przykład detektor obiektów może wykrywać wiele obiektów, które się nakładają, na przykład wykrywając jedną puszkę wewnątrz drugiej. Twój kod może sprawdzić ramki ograniczające, zrozumieć, że jest to niemożliwe, i zignorować obiekty, które mają znaczące nakładanie się z innymi obiektami.

![Dwie nakładające się ramki ograniczające wokół puszki koncentratu pomidorowego](../../../../../translated_images/overlap-object-detection.d431e03cae75072a2760430eca7f2c5fdd43045bfd72dadcbf12711f7cd6c2ae.pl.png)

W powyższym przykładzie jedna ramka ograniczająca wskazuje przewidywaną puszkę koncentratu pomidorowego z prawdopodobieństwem 78.3%. Druga ramka ograniczająca jest nieco mniejsza i znajduje się wewnątrz pierwszej ramki z prawdopodobieństwem 64.3%. Twój kod może sprawdzić ramki ograniczające, zauważyć, że całkowicie się nakładają, i zignorować niższe prawdopodobieństwo, ponieważ nie ma możliwości, aby jedna puszka znajdowała się wewnątrz drugiej.

✅ Czy możesz wymyślić sytuację, w której wykrycie jednego obiektu wewnątrz drugiego jest uzasadnione?

## Ponowne trenowanie modelu

Podobnie jak w przypadku klasyfikatora obrazów, możesz ponownie trenować swój model, używając danych zebranych przez urządzenie IoT. Korzystanie z tych danych z rzeczywistego świata zapewni, że model będzie działał dobrze, gdy będzie używany z urządzenia IoT.

W przeciwieństwie do klasyfikatora obrazów, nie możesz po prostu oznaczyć obrazu. Zamiast tego musisz przejrzeć każdą ramkę ograniczającą wykrytą przez model. Jeśli ramka jest wokół niewłaściwego obiektu, musi zostać usunięta, jeśli jest w niewłaściwej lokalizacji, musi zostać poprawiona.

### Zadanie - ponowne trenowanie modelu

1. Upewnij się, że zebrałeś różnorodne obrazy za pomocą swojego urządzenia IoT.

1. W zakładce **Predictions** wybierz obraz. Zobaczysz czerwone ramki wskazujące ramki ograniczające wykrytych obiektów.

1. Przejrzyj każdą ramkę ograniczającą. Wybierz ją najpierw, a zobaczysz wyskakujące okienko pokazujące etykietę. Użyj uchwytów na rogach ramki, aby dostosować rozmiar, jeśli to konieczne. Jeśli etykieta jest błędna, usuń ją za pomocą przycisku **X** i dodaj właściwą etykietę. Jeśli ramka nie zawiera obiektu, usuń ją za pomocą przycisku kosza.

1. Zamknij edytor po zakończeniu, a obraz zostanie przeniesiony z zakładki **Predictions** do zakładki **Training Images**. Powtórz proces dla wszystkich predykcji.

1. Użyj przycisku **Train**, aby ponownie wytrenować swój model. Po zakończeniu treningu opublikuj iterację i zaktualizuj swoje urządzenie IoT, aby używało URL nowej iteracji.

1. Ponownie wdroż swój kod i przetestuj urządzenie IoT.

## Liczenie zapasów

Korzystając z kombinacji liczby wykrytych obiektów i ramek ograniczających, możesz policzyć zapasy na półce.

### Zadanie - liczenie zapasów

Skorzystaj z odpowiedniego przewodnika poniżej, aby policzyć zapasy, używając wyników z detektora obiektów z urządzenia IoT:

* [Arduino - Wio Terminal](wio-terminal-count-stock.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie](single-board-computer-count-stock.md)

---

## 🚀 Wyzwanie

Czy potrafisz wykryć niewłaściwe zapasy? Wytrenuj swój model na wielu obiektach, a następnie zaktualizuj swoją aplikację, aby powiadamiała Cię, jeśli wykryte zostaną niewłaściwe zapasy.

Możesz nawet pójść dalej i wykrywać zapasy obok siebie na tej samej półce, sprawdzając, czy coś zostało umieszczone w niewłaściwym miejscu, definiując limity dla ramek ograniczających.

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/40)

## Przegląd i samodzielna nauka

* Dowiedz się więcej o tym, jak zaprojektować kompleksowy system wykrywania zapasów z przewodnika [Out of stock detection at the edge pattern guide on Microsoft Docs](https://docs.microsoft.com/hybrid/app-solutions/pattern-out-of-stock-at-edge?WT.mc_id=academic-17441-jabenn)
* Poznaj inne sposoby budowania kompleksowych rozwiązań dla handlu detalicznego, łącząc różne usługi IoT i chmurowe, oglądając [Behind the scenes of a retail solution - Hands On! video on YouTube](https://www.youtube.com/watch?v=m3Pc300x2Mw).

## Zadanie

[Użyj swojego detektora obiektów na urządzeniu edge](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczeniowej AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby zapewnić poprawność tłumaczenia, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego języku źródłowym powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia wykonanego przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.