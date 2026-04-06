# Sprawdź jakość owoców za pomocą urządzenia IoT

![Szkicowy przegląd tej lekcji](../../../../../translated_images/pl/lesson-16.215daf18b00631fb.webp)

> Szkic autorstwa [Nitya Narasimhan](https://github.com/nitya). Kliknij obrazek, aby zobaczyć większą wersję.

## Quiz przed wykładem

[Quiz przed wykładem](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/31)

## Wprowadzenie

W poprzedniej lekcji nauczyłeś się o klasyfikatorach obrazów i o tym, jak je trenować, aby wykrywać dobre i złe owoce. Aby użyć tego klasyfikatora obrazów w aplikacji IoT, musisz być w stanie uchwycić obraz za pomocą jakiegoś rodzaju kamery i przesłać ten obraz do chmury w celu klasyfikacji.

W tej lekcji dowiesz się o czujnikach kamer i o tym, jak używać ich z urządzeniem IoT do uchwycenia obrazu. Nauczysz się również, jak wywołać klasyfikator obrazów z urządzenia IoT.

W tej lekcji omówimy:

* [Czujniki kamer](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Uchwycenie obrazu za pomocą urządzenia IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Publikacja klasyfikatora obrazów](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Klasyfikacja obrazów z urządzenia IoT](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)
* [Udoskonalenie modelu](../../../../../4-manufacturing/lessons/2-check-fruit-from-device)

## Czujniki kamer

Czujniki kamer, jak sama nazwa wskazuje, to kamery, które można podłączyć do urządzenia IoT. Mogą robić zdjęcia lub rejestrować strumieniowe wideo. Niektóre zwracają surowe dane obrazowe, inne kompresują dane obrazowe do pliku graficznego, takiego jak JPEG lub PNG. Zazwyczaj kamery współpracujące z urządzeniami IoT są znacznie mniejsze i mają niższą rozdzielczość niż te, do których możesz być przyzwyczajony, ale można znaleźć kamery o wysokiej rozdzielczości, które dorównują najlepszym telefonom. Dostępne są różne wymienne obiektywy, zestawy wielokamerowe, kamery termiczne na podczerwień czy kamery UV.

![Światło ze sceny przechodzi przez obiektyw i jest skupiane na czujniku CMOS](../../../../../translated_images/pl/cmos-sensor.75f9cd74decb1371.webp)

Większość czujników kamer wykorzystuje czujniki obrazu, gdzie każdy piksel jest fotodiodą. Obiektyw skupia obraz na czujniku obrazu, a tysiące lub miliony fotodiod wykrywają światło padające na każdą z nich i zapisują je jako dane pikselowe.

> 💁 Obiektywy odwracają obrazy, a czujnik kamery następnie odwraca obraz z powrotem do właściwej orientacji. To samo dzieje się w twoich oczach - to, co widzisz, jest wykrywane do góry nogami na tylnej części oka, a twój mózg to koryguje.

> 🎓 Czujnik obrazu jest znany jako Aktywny Czujnik Pikseli (APS), a najpopularniejszym typem APS jest czujnik komplementarny metal-oksydowy półprzewodnikowy, czyli CMOS. Możesz znać termin czujnik CMOS używany w odniesieniu do czujników kamer.

Czujniki kamer to czujniki cyfrowe, przesyłające dane obrazowe jako dane cyfrowe, zazwyczaj z pomocą biblioteki zapewniającej komunikację. Kamery łączą się za pomocą protokołów takich jak SPI, aby umożliwić przesyłanie dużych ilości danych - obrazy są znacznie większe niż pojedyncze liczby z czujnika, takiego jak czujnik temperatury.

✅ Jakie są ograniczenia dotyczące rozmiaru obrazu w urządzeniach IoT? Zastanów się nad ograniczeniami, szczególnie w przypadku sprzętu mikroprocesorowego.

## Uchwycenie obrazu za pomocą urządzenia IoT

Możesz użyć swojego urządzenia IoT do uchwycenia obrazu, który ma zostać sklasyfikowany.

### Zadanie - uchwycenie obrazu za pomocą urządzenia IoT

Przejdź przez odpowiedni przewodnik, aby uchwycić obraz za pomocą swojego urządzenia IoT:

* [Arduino - Wio Terminal](wio-terminal-camera.md)
* [Komputer jednopłytkowy - Raspberry Pi](pi-camera.md)
* [Komputer jednopłytkowy - Wirtualne urządzenie](virtual-device-camera.md)

## Publikacja klasyfikatora obrazów

W poprzedniej lekcji wytrenowałeś swój klasyfikator obrazów. Zanim będziesz mógł go używać z urządzenia IoT, musisz opublikować model.

### Iteracje modelu

Podczas trenowania modelu w poprzedniej lekcji mogłeś zauważyć, że zakładka **Performance** pokazuje iteracje z boku. Kiedy po raz pierwszy trenowałeś model, widziałeś *Iteration 1* w trakcie trenowania. Kiedy ulepszyłeś model za pomocą obrazów predykcyjnych, widziałeś *Iteration 2* w trakcie trenowania.

Za każdym razem, gdy trenujesz model, powstaje nowa iteracja. Jest to sposób na śledzenie różnych wersji modelu trenowanych na różnych zestawach danych. Podczas **Quick Test** dostępny jest rozwijany wybór, który pozwala wybrać iterację, aby porównać wyniki między różnymi iteracjami.

Kiedy jesteś zadowolony z iteracji, możesz ją opublikować, aby była dostępna do użycia w aplikacjach zewnętrznych. Dzięki temu możesz mieć opublikowaną wersję używaną przez urządzenia, a następnie pracować nad nową wersją przez wiele iteracji, a następnie opublikować ją, gdy będziesz z niej zadowolony.

### Zadanie - publikacja iteracji

Iteracje są publikowane z portalu Custom Vision.

1. Uruchom portal Custom Vision na [CustomVision.ai](https://customvision.ai) i zaloguj się, jeśli jeszcze tego nie zrobiłeś. Następnie otwórz swój projekt `fruit-quality-detector`.

1. Wybierz zakładkę **Performance** z opcji u góry.

1. Wybierz najnowszą iterację z listy *Iterations* z boku.

1. Wybierz przycisk **Publish** dla iteracji.

    ![Przycisk publikacji](../../../../../translated_images/pl/custom-vision-publish-button.b7174e1977b0c33b.webp)

1. W oknie dialogowym *Publish Model* ustaw *Prediction resource* na zasób `fruit-quality-detector-prediction`, który utworzyłeś w poprzedniej lekcji. Pozostaw nazwę jako `Iteration2` i wybierz przycisk **Publish**.

1. Po opublikowaniu wybierz przycisk **Prediction URL**. Wyświetli to szczegóły dotyczące API predykcji, które będą potrzebne do wywołania modelu z urządzenia IoT. Dolna sekcja jest oznaczona *If you have an image file* i to są szczegóły, które cię interesują. Skopiuj URL, który będzie wyglądał mniej więcej tak:

    ```output
    https://<location>.api.cognitive.microsoft.com/customvision/v3.0/Prediction/<id>/classify/iterations/Iteration2/image
    ```

    Gdzie `<location>` będzie lokalizacją używaną podczas tworzenia zasobu Custom Vision, a `<id>` będzie długim identyfikatorem składającym się z liter i cyfr.

    Skopiuj również wartość *Prediction-Key*. Jest to klucz zabezpieczający, który musisz przekazać podczas wywoływania modelu. Tylko aplikacje, które przekazują ten klucz, mogą korzystać z modelu, inne aplikacje są odrzucane.

    ![Okno dialogowe API predykcji pokazujące URL i klucz](../../../../../translated_images/pl/custom-vision-prediction-key-endpoint.30c569ffd0338864.webp)

✅ Kiedy nowa iteracja zostanie opublikowana, będzie miała inną nazwę. Jak myślisz, jak można zmienić iterację używaną przez urządzenie IoT?

## Klasyfikacja obrazów z urządzenia IoT

Teraz możesz użyć tych szczegółów połączenia, aby wywołać klasyfikator obrazów z urządzenia IoT.

### Zadanie - klasyfikacja obrazów z urządzenia IoT

Przejdź przez odpowiedni przewodnik, aby sklasyfikować obrazy za pomocą swojego urządzenia IoT:

* [Arduino - Wio Terminal](wio-terminal-classify-image.md)
* [Komputer jednopłytkowy - Raspberry Pi/Wirtualne urządzenie IoT](single-board-computer-classify-image.md)

## Udoskonalenie modelu

Możesz zauważyć, że wyniki uzyskane przy użyciu kamery podłączonej do urządzenia IoT nie odpowiadają twoim oczekiwaniom. Predykcje nie zawsze są tak dokładne, jak w przypadku obrazów przesłanych z komputera. Dzieje się tak, ponieważ model był trenowany na innych danych niż te używane do predykcji.

Aby uzyskać najlepsze wyniki dla klasyfikatora obrazów, należy trenować model za pomocą obrazów, które są jak najbardziej podobne do obrazów używanych do predykcji. Na przykład, jeśli użyłeś kamery telefonu do uchwycenia obrazów do trenowania, jakość obrazu, ostrość i kolor będą różne od kamery podłączonej do urządzenia IoT.

![2 zdjęcia bananów, jedno o niskiej rozdzielczości i słabym oświetleniu z urządzenia IoT, drugie o wysokiej rozdzielczości i dobrym oświetleniu z telefonu](../../../../../translated_images/pl/banana-picture-compare.174df164dc326a42.webp)

Na powyższym obrazku zdjęcie banana po lewej zostało zrobione za pomocą kamery Raspberry Pi, a zdjęcie po prawej zostało zrobione tego samego banana w tym samym miejscu za pomocą iPhone'a. Widać zauważalną różnicę w jakości - zdjęcie z iPhone'a jest ostrzejsze, z jaśniejszymi kolorami i większym kontrastem.

✅ Co jeszcze może powodować, że obrazy uchwycone przez twoje urządzenie IoT mają nieprawidłowe predykcje? Zastanów się nad środowiskiem, w którym może być używane urządzenie IoT, jakie czynniki mogą wpływać na uchwycony obraz?

Aby ulepszyć model, możesz go ponownie wytrenować, używając obrazów uchwyconych z urządzenia IoT.

### Zadanie - udoskonalenie modelu

1. Sklasyfikuj wiele obrazów zarówno dojrzałych, jak i niedojrzałych owoców za pomocą swojego urządzenia IoT.

1. W portalu Custom Vision ponownie wytrenuj model, używając obrazów na zakładce *Predictions*.

    > ⚠️ Możesz odwołać się do [instrukcji dotyczących ponownego trenowania klasyfikatora w lekcji 1, jeśli zajdzie taka potrzeba](../1-train-fruit-detector/README.md#retrain-your-image-classifier).

1. Jeśli twoje obrazy wyglądają bardzo inaczej niż oryginalne użyte do trenowania, możesz usunąć wszystkie oryginalne obrazy, wybierając je na zakładce *Training Images* i klikając przycisk **Delete**. Aby wybrać obraz, najedź na niego kursorem, a pojawi się znacznik wyboru, kliknij go, aby wybrać lub odznaczyć obraz.

1. Wytrenuj nową iterację modelu i opublikuj ją, korzystając z powyższych kroków.

1. Zaktualizuj URL punktu końcowego w swoim kodzie i uruchom aplikację ponownie.

1. Powtarzaj te kroki, aż będziesz zadowolony z wyników predykcji.

---

## 🚀 Wyzwanie

Jak bardzo rozdzielczość obrazu lub oświetlenie wpływa na predykcję?

Spróbuj zmienić rozdzielczość obrazów w kodzie swojego urządzenia i zobacz, czy ma to wpływ na jakość obrazów. Spróbuj również zmienić oświetlenie.

Jeśli miałbyś stworzyć urządzenie produkcyjne do sprzedaży na farmach lub w fabrykach, jak zapewniłbyś, że zawsze daje ono spójne wyniki?

## Quiz po wykładzie

[Quiz po wykładzie](https://black-meadow-040d15503.1.azurestaticapps.net/quiz/32)

## Przegląd i samodzielna nauka

Wytrenowałeś swój model Custom Vision za pomocą portalu. To wymaga posiadania dostępnych obrazów - a w rzeczywistości możesz nie być w stanie uzyskać danych treningowych, które odpowiadają temu, co uchwyca kamera na twoim urządzeniu. Możesz obejść ten problem, trenując bezpośrednio z urządzenia za pomocą API treningowego, aby wytrenować model za pomocą obrazów uchwyconych z urządzenia IoT.

* Przeczytaj o API treningowym w [szybkim starcie korzystania z Custom Vision SDK](https://docs.microsoft.com/azure/cognitive-services/custom-vision-service/quickstarts/image-classification?WT.mc_id=academic-17441-jabenn&tabs=visual-studio&pivots=programming-language-python)

## Zadanie

[Reakcja na wyniki klasyfikacji](assignment.md)

**Zastrzeżenie**:  
Ten dokument został przetłumaczony za pomocą usługi tłumaczenia AI [Co-op Translator](https://github.com/Azure/co-op-translator). Chociaż dokładamy wszelkich starań, aby tłumaczenie było precyzyjne, prosimy pamiętać, że automatyczne tłumaczenia mogą zawierać błędy lub nieścisłości. Oryginalny dokument w jego rodzimym języku powinien być uznawany za wiarygodne źródło. W przypadku informacji o kluczowym znaczeniu zaleca się skorzystanie z profesjonalnego tłumaczenia przez człowieka. Nie ponosimy odpowiedzialności za jakiekolwiek nieporozumienia lub błędne interpretacje wynikające z użycia tego tłumaczenia.